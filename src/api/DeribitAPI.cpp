#include "api/DeribitAPI.hpp"
#include "utils/Logger.hpp"
#include "utils/HttpClient.hpp"

DeribitAPI::DeribitAPI(const std::string& key, const std::string& secret)
    : apiKey(key), apiSecret(secret), baseUrl("https://test.deribit.com/api/v2") {}

nlohmann::json DeribitAPI::placeOrder(const nlohmann::json& order) {
    Logger::info("Placing order: " + order.dump());
    std::string endpoint = baseUrl + "/private/buy"; 
    return HttpClient::post(endpoint, order);
}

bool DeribitAPI::cancelOrder(const std::string& orderId) {
    Logger::info("Cancelling order ID: " + orderId);
    std::string endpoint = baseUrl + "/private/cancel";
    nlohmann::json body = { {"order_id", orderId} };
    nlohmann::json response = HttpClient::post(endpoint, body);
    return response.contains("result");
}

nlohmann::json DeribitAPI::modifyOrder(const std::string& orderId, const nlohmann::json& updatedFields) {
    Logger::info("Modifying order ID: " + orderId + " with: " + updatedFields.dump());
    std::string endpoint = baseUrl + "/private/edit";
    nlohmann::json request = updatedFields;
    request["order_id"] = orderId;
    return HttpClient::post(endpoint, request);
}

nlohmann::json DeribitAPI::getOrderbook(const std::string& symbol) {
    Logger::info("Fetching orderbook for: " + symbol);
    std::string endpoint = baseUrl + "/public/get_order_book?instrument_name=" + symbol;
    return HttpClient::get(endpoint);
}

nlohmann::json DeribitAPI::getPositions() {
    Logger::info("Retrieving current positions");
    std::string endpoint = baseUrl + "/private/get_positions?currency=BTC&kind=any";
    return HttpClient::get(endpoint);
}
