#include <ixwebsocket/IXWebSocketServer.h>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocketMessageType.h>
#include "api/DeribitAPI.hpp"
#include "utils/Logger.hpp"
#include "json.hpp"
#include "ws/DeriWebSocketServer.hpp"

using json = nlohmann::json;

void DeriWebSocketServer::run(int port) {
    ix::initNetSystem();  

    DeribitAPI api("your_api_key", "your_api_secret");
    ix::WebSocketServer server(port, "0.0.0.0");

    server.setOnClientMessageCallback(
        [&api](std::shared_ptr<ix::ConnectionState> connectionState,
               ix::WebSocket& webSocket,
               const ix::WebSocketMessagePtr& msg) {

            if (msg->type == ix::WebSocketMessageType::Message) {
                try {
                    json message = json::parse(msg->str);
                    json response;

                    std::string action = message["action"];

                    if (action == "place_order") {
                        response = api.placeOrder(message["order"]);
                    } else if (action == "cancel_order") {
                        bool result = api.cancelOrder(message["order_id"]);
                        response = { {"success", result} };
                    } else if (action == "modify_order") {
                        response = api.modifyOrder(message["order_id"], message["updated_fields"]);
                    } else if (action == "get_orderbook") {
                        response = api.getOrderbook(message["symbol"]);
                    } else if (action == "get_positions") {
                        response = api.getPositions();
                    } else {
                        response = { {"error", "Unknown action"} };
                    }

                    webSocket.send(response.dump());  

                } catch (const std::exception& e) {
                    webSocket.send(json{{"error", e.what()}}.dump());
                }
            }
        });

    if (!server.listen().first) {
        Logger::error("Failed to start WebSocket server");
        return;
    }

    Logger::info("WebSocket server running on port " + std::to_string(port));
    server.start();
}
