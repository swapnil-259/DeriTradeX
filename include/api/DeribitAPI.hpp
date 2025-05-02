#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::json;

class DeribitAPI {
public:
    DeribitAPI(const std::string& key, const std::string& secret);

    void authenticate();
    nlohmann::json makeRequest(const std::string& endpoint, const nlohmann::json& body, bool auth);
    json placeOrder(const json& order, const std::string& side = "buy");
    bool cancelOrder(const std::string& orderId);
    json modifyOrder(const std::string& orderId, const json& updatedFields);
    json getOrderbook(const std::string& symbol);
    json getPositions(const std::string& currency = "BTC");

    std::string getAccessToken() const { return access_token; }

private:
    std::string apiKey;
    std::string apiSecret;
    std::string baseUrl;
    std::string access_token;
};
