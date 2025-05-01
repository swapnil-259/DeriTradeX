#include "ws/WebSocketServer.hpp"
#include "utils/Logger.hpp"

void WebSocketServer::run(int port) {
    Logger::info("WebSocket server running on port " + std::to_string(port));
}

void WebSocketServer::broadcast(const std::string& symbol, const std::string& message) {
    Logger::info("Broadcasting to " + symbol + ": " + message);
}
