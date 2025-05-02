import websocket
import json

def on_open(ws):
    print("WebSocket connection opened.")
    order_message = {
        "action": "place_order",
        "order": {
            "instrument_name": "BTC-PERPETUAL",  
            "quantity": 1,                       
            "price": 40000,                     
            "type": "limit",                    
            "time_in_force": "GoodTillCancel"    
        }
    }
    print("Sending place_order message:", json.dumps(order_message)) 
    ws.send(json.dumps(order_message))
    cancel_message = {
        "action": "cancel_order",
        "order_id": "12345"  
    }
    print("Sending cancel_order message:", json.dumps(cancel_message)) 
    ws.send(json.dumps(cancel_message))

    modify_message = {
        "action": "modify_order",
        "order_id": "12345", 
        "updated_fields": {
            "price": 41000  
        }
    }
    print("Sending modify_order message:", json.dumps(modify_message)) 
    ws.send(json.dumps(modify_message))
    orderbook_message = {
        "action": "get_orderbook",
        "symbol": "BTC-PERPETUAL"  
    }
    print("Sending get_orderbook message:", json.dumps(orderbook_message)) 
    ws.send(json.dumps(orderbook_message))
    positions_message = {
        "action": "get_positions",
        "currency": "BTC"  
    }
    print("Sending get_positions message:", json.dumps(positions_message))  
    ws.send(json.dumps(positions_message))
    ping_message = {
        "action": "ping"
    }
    print("Sending ping message:", json.dumps(ping_message))  
    ws.send(json.dumps(ping_message))

def on_message(ws, message):
    print("Received message:", message)

def on_close(ws):
    print("WebSocket connection closed.")

def on_error(ws, error):
    print("WebSocket error:", error)
ws_url = "ws://localhost:9000" 
ws = websocket.WebSocketApp(ws_url, 
                            on_open=on_open, 
                            on_message=on_message, 
                            on_close=on_close, 
                            on_error=on_error)
ws.run_forever()
