#include "api/DeribitAPI.hpp"
#include "utils/Logger.hpp"
#include "utils/HttpClient.hpp"

using json = nlohmann::json;

DeribitAPI::DeribitAPI(const std::string& key, const std::string& secret)
    : apiKey(key), apiSecret(secret), baseUrl("https://test.deribit.com/api/v2") {}

void DeribitAPI::authenticate() {
    Logger::info("Authenticating with Deribit API...");

    std::string endpoint = baseUrl + "/public/auth?grant_type=client_credentials"
        + "&client_id=" + apiKey + "&client_secret=" + apiSecret;

    json response = HttpClient::get(endpoint);

    if (response.contains("result") && response["result"].contains("access_token")) {
        access_token = response["result"]["access_token"];
        Logger::info("Authentication successful.");
    } else {
        Logger::error("Authentication failed: " + response.dump());
        throw std::runtime_error("Failed to authenticate with Deribit");
    }
}

json DeribitAPI::makeRequest(const std::string& endpoint, const json& body, bool auth) {
    std::string fullUrl = baseUrl + endpoint;

    if (auth && access_token.empty()) {
        authenticate();
    }

    std::vector<std::string> headers = {
        "Content-Type: application/json"
    };

    if (auth) {
        headers.push_back("Authorization: Bearer " + access_token);
    }

    return HttpClient::post(fullUrl, body, headers);  

}

json DeribitAPI::placeOrder(const json& order, const std::string& side) {
    Logger::info("Placing order: " + order.dump());
    std::string lower_side = side;
    std::transform(lower_side.begin(), lower_side.end(), lower_side.begin(), ::tolower);
    if (lower_side != "buy" && lower_side != "sell") {
        Logger::error("Invalid order side: " + side);
        return { {"error", "Invalid order side: must be 'buy' or 'sell'"} };
    }
    std::string endpoint = "/api/v2/private/" + lower_side;
    json order_cleaned = order;
    if (order_cleaned.contains("side")) {
        order_cleaned.erase("side");
    }
    Logger::info("Endpoint: " + endpoint);
    Logger::info("Request Body: " + order_cleaned.dump());
    return makeRequest(endpoint, order_cleaned, true);
}


bool DeribitAPI::cancelOrder(const std::string& orderId) {
    Logger::info("Cancelling order ID: " + orderId);
    json body = { {"order_id", orderId} };
    std::string endpoint = "/private/cancel";
    Logger::info("Endpoint: " + endpoint);
    Logger::info("Request Body: " + body.dump());

    json response = makeRequest(endpoint, body, true);
    return response.contains("result");
}

json DeribitAPI::modifyOrder(const std::string& orderId, const json& updatedFields) {
    Logger::info("Modifying order ID: " + orderId + " with: " + updatedFields.dump());
    json request = updatedFields;
    request["order_id"] = orderId;
    std::string endpoint = "/private/edit";
    Logger::info("Endpoint: " + endpoint);
    Logger::info("Request Body: " + request.dump());

    return makeRequest(endpoint, request, true);
}

json DeribitAPI::getOrderbook(const std::string& symbol) {
    std::string endpoint = baseUrl + "/public/get_order_book?instrument_name=" + symbol;
    return HttpClient::get(endpoint);
}

json DeribitAPI::getPositions(const std::string& currency) {
    json requestData = {{"currency", currency}};
    json response = HttpClient::post(baseUrl + "/private/get_positions", requestData);
    return response;
}
