#pragma once
#include <string>
using namespace std;

struct Order {
    string id;
    string symbol;
    double price;
    double quantity;
    string side;
};