#pragma once
#include <string>
#include "json.hpp" 

class DeribitAPI {
public:
    DeribitAPI(const std::string& key, const std::string& secret);

    nlohmann::json placeOrder(const nlohmann::json& order);
    bool cancelOrder(const std::string& orderId);
    nlohmann::json getOrderbook(const std::string& symbol);
    nlohmann::json getPositions();

private:
    std::string apiKey;
    std::string apiSecret;
    std::string baseUrl;
};