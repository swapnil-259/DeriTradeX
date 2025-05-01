#pragma once
#include <string>

struct Order {
    std::string id;
    std::string symbol;
    double price;
    double quantity;
    std::string side;
};