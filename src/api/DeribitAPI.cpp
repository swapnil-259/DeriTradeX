#include "api/DeribitAPI.hpp"
#include "utils/Logger.hpp"

DeribitAPI::DeribitAPI(const std::string& key, const std::string& secret)
    : apiKey(key), apiSecret(secret), baseUrl("https://test.deribit.com/api/v2") {}

nlohmann::json DeribitAPI::placeOrder(const nlohmann::json& order) {
    Logger::info("Placing order: " + order.dump());
    return { {"order_id", "dummy_order_123"} };
}

bool DeribitAPI::cancelOrder(const std::string& orderId) {
    Logger::info("Cancelling order ID: " + orderId);
    return true;
}

nlohmann::json DeribitAPI::getOrderbook(const std::string& symbol) {
    Logger::info("Fetching orderbook for: " + symbol);
    return {
        {"bids", {{50000, 1.5}}},
        {"asks", {{50010, 2.0}}}
    };
}

nlohmann::json DeribitAPI::getPositions() {
    Logger::info("Retrieving current positions");
    return {
        {"BTC-PERPETUAL", { {"size", 1.0}, {"entry_price", 49000} }},
        {"ETH-PERPETUAL", { {"size", -0.5}, {"entry_price", 3200} }}
    };
}