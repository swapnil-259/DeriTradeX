#pragma once
#include <string>
#include <unordered_map>
#include <set>
using namespace std;

class WebSocketServer {
public:
    void run(int port);
    void broadcast(const string& symbol, const string& message);

private:
    unordered_map<string, set<int>> subscriptions;
};
