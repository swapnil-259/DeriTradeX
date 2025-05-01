#pragma once

#include <string>
#include <unordered_map>
#include <set>

class DeriWebSocketServer {
public:
    void run(int port);
    void broadcast(const std::string& symbol, const std::string& message);

private:
    std::unordered_map<std::string, std::set<int>> subscriptions;
};
