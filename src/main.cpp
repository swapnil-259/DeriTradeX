#include "main.hpp"
#include "api/DeribitAPI.hpp"
#include "ws/WebSocketServer.hpp"
#include "utils/Logger.hpp"

void startDeriTradeX() {
    Logger::info("Starting DeriTradeX...");

    DeribitAPI api("demo_key", "demo_secret");
    WebSocketServer ws;

    ws.run(9000);

    auto book = api.getOrderbook("BTC-PERPETUAL");
    ws.broadcast("BTC-PERPETUAL", book.dump());
}

int main() {
    startDeriTradeX();
    return 0;
}
