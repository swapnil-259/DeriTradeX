#include "ws/DeriWebSocketServer.hpp"
#include "utils/Logger.hpp"

int main() {
    Logger::info("Starting DeriTradeX...");
    DeriWebSocketServer server;
    server.run(9000);
    return 0;
}
