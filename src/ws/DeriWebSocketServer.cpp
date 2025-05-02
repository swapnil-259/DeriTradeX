#include <ixwebsocket/IXWebSocketServer.h>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocketMessageType.h>
#include "api/DeribitAPI.hpp"
#include "utils/Logger.hpp"
#include "json.hpp"
#include "ws/DeriWebSocketServer.hpp"

void DeriWebSocketServer::run(int port) {
    ix::initNetSystem();

    DeribitAPI api("DERIBIT_API_KEY", "DERIBIT_API_SECRET");
    api.authenticate();
    Logger::info("Authenticated. Access token: " + api.getAccessToken());

    server_ = std::make_unique<ix::WebSocketServer>(port, "0.0.0.0");

    server_->setOnClientMessageCallback(
        [&api](std::shared_ptr<ix::ConnectionState> connectionState,
               ix::WebSocket& webSocket,
               const ix::WebSocketMessagePtr& msg) {

            if (msg->type == ix::WebSocketMessageType::Message) {
                try {
                    auto message = nlohmann::json::parse(msg->str);
                    nlohmann::json response;

                    std::string action = message.value("action", "");

                    if (action == "place_order") {
                        auto order = message["order"];

                        if (order.contains("quantity")) {
                            order["amount"] = order["quantity"];
                            order.erase("quantity");
                        }

                        if (!order.contains("type")) {
                            order["type"] = "limit";
                        }

                        std::string side = "buy";
                        if (order.contains("side")) {
                            side = order["side"].get<std::string>();
                            order.erase("side");
                        }

                        response = api.placeOrder(order, side);
                    
                    } else if (action == "cancel_order") {
                        bool result = api.cancelOrder(message["order_id"]);
                        response = { {"success", result} };
                    } else if (action == "modify_order") {
                        response = api.modifyOrder(message["order_id"], message["updated_fields"]);
                    } else if (action == "get_orderbook") {
                        response = api.getOrderbook(message["symbol"]);
                    } else if (action == "get_positions") {
                        std::string currency = message.value("currency", "BTC");
                        response = api.getPositions(currency);
                    } else if (action == "ping") {
                        response = { {"action", "pong"} };
                    } else {
                        response = { {"error", "Unknown action"} };
                    }

                    webSocket.send(response.dump());
                } catch (const std::exception& e) {
                    webSocket.send(nlohmann::json{{"error", e.what()}}.dump());
                }
            }
        });

    auto [ok, errMsg] = server_->listen();
    if (!ok) {
        Logger::error("WebSocket listen failed on port " + std::to_string(port) + ": " + errMsg);
        return;
    }

    Logger::info("WebSocket server running on port " + std::to_string(port));
    server_->start(); 
    Logger::info("WebSocket event loop started.");

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}
