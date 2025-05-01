#include "ws/WebSocketServer.hpp"
#include "utils/Logger.hpp"
using namespace std;

void WebSocketServer::run(int port) {
    Logger::info("WebSocket server running on port " + to_string(port));
}

void WebSocketServer::broadcast(const string& symbol, const string& message) {
    Logger::info("Broadcasting to " + symbol + ": " + message);
}
