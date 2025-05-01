#pragma once
#include "json.hpp"
#include "models/Order.hpp"
#include "models/Position.hpp"

nlohmann::json serializeOrder(const Order& order);
Order deserializeOrder(const nlohmann::json& j);

nlohmann::json serializePosition(const Position& pos);
Position deserializePosition(const nlohmann::json& j);