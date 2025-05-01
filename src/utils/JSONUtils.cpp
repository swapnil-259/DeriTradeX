#include "utils/JSONUtils.hpp"

nlohmann::json serializeOrder(const Order& order) {
    return {
        {"id", order.id},
        {"symbol", order.symbol},
        {"price", order.price},
        {"quantity", order.quantity},
        {"side", order.side}
    };
}

Order deserializeOrder(const nlohmann::json& j) {
    return Order {
        j.at("id").get<std::string>(),
        j.at("symbol").get<std::string>(),
        j.at("price").get<double>(),
        j.at("quantity").get<double>(),
        j.at("side").get<std::string>()
    };
}

nlohmann::json serializePosition(const Position& pos) {
    return {
        {"symbol", pos.symbol},
        {"size", pos.size},
        {"entry_price", pos.entryPrice}
    };
}

Position deserializePosition(const nlohmann::json& j) {
    return Position {
        j.at("symbol").get<std::string>(),
        j.at("size").get<double>(),
        j.at("entry_price").get<double>()
    };
}
