#include "main.hpp"
#include "api/DeribitAPI.hpp"
#include "ws/DeriWebSocketServer.hpp"
#include "utils/Logger.hpp"

void startDeriTradeX() {
    Logger::info("Starting DeriTradeX...");

    DeriWebSocketServer ws;
    ws.run(9000);  
}

int main() {
    startDeriTradeX();
    return 0;
}
