# DeriTradeX

DeriTradeX is a high-performance modular C++ trading system for interacting with the Deribit cryptocurrency exchange (Testnet). It features real-time WebSocket communication and RESTful API integration, supporting core trading functionalities such as order placement, modification, cancellation, and market data retrieval.

## 🚀 Features

* Modular C++ architecture
* Real-time WebSocket client (using `ixwebsocket`)
* REST API integration (using `libcurl`)
* Trading operations: `buy`, `sell`, `edit`, `cancel`
* Market data via `get_positions`, `get_orderbook`
* Object-oriented design with clean separation of concerns

---

## 📁 Project Structure

```plaintext
DeriTradeX/
├── include/
│   ├── DeribitAPI.h            # HTTP API interactions (using libcurl)
│   ├── DeribitWSClient.h       # WebSocket logic (ixwebsocket)
│   ├── Order.h                 # Order model class
│   └── Utility.h               # Common utility functions
├── src/
│   ├── DeribitAPI.cpp
│   ├── DeribitWSClient.cpp
│   ├── Order.cpp
│   └── main.cpp
├── CMakeLists.txt              # CMake build configuration
├── README.md                   # Project documentation
└── .env                        # (Optional) API credentials
```

---

## ⚙️ Build Instructions

### Prerequisites

* CMake ≥ 3.10
* g++ or clang++
* `libcurl` and `ixwebsocket` installed

### Build

```bash
git clone https://github.com/swapnil-259/DeriTradeX.git
cd DeriTradeX
mkdir build && cd build
cmake ..
make
```

---

## 🔌 WebSocket Commands

DeriTradeX supports the following WebSocket commands on Deribit Testnet:

### `private/buy`

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "private/buy",
  "params": {
    "instrument_name": "BTC-PERPETUAL",
    "amount": 10,
    "type": "limit",
    "price": 30000
  }
}
```

### `private/sell`

```json
{
  "jsonrpc": "2.0",
  "id": 2,
  "method": "private/sell",
  "params": {
    "instrument_name": "BTC-PERPETUAL",
    "amount": 5,
    "type": "limit",
    "price": 32000
  }
}
```

### `private/edit`

```json
{
  "jsonrpc": "2.0",
  "id": 3,
  "method": "private/edit",
  "params": {
    "order_id": "order-uuid",
    "price": 31500
  }
}
```

### `private/cancel`

```json
{
  "jsonrpc": "2.0",
  "id": 4,
  "method": "private/cancel",
  "params": {
    "order_id": "order-uuid"
  }
}
```

### `private/get_positions`

```json
{
  "jsonrpc": "2.0",
  "id": 5,
  "method": "private/get_positions",
  "params": {
    "currency": "BTC",
    "kind": "future"
  }
}
```

### `public/get_order_book`

```json
{
  "jsonrpc": "2.0",
  "id": 6,
  "method": "public/get_order_book",
  "params": {
    "instrument_name": "BTC-PERPETUAL"
  }
}
```

---

## 🧠 Code Documentation

### `DeribitAPI.h` / `DeribitAPI.cpp`

Handles HTTP communication using libcurl.

* `getAccessToken()` – Authenticates with client ID/secret.
* `getOrderBook(instrument)` – Gets real-time order book via REST.
* `getPositions(currency)` – Fetches current user positions.

### `DeribitWSClient.h` / `DeribitWSClient.cpp`

Manages WebSocket connection, sending/receiving messages.

* `connect()` – Establishes connection to Deribit WebSocket.
* `authenticate()` – Sends auth message using access token.
* `sendBuyOrder()`, `sendSellOrder()` – Submits trades.
* `editOrder()`, `cancelOrder()` – Modifies/cancels open orders.
* `getPositions()`, `getOrderBook()` – Gets position/orderbook data.

### `Order.h` / `Order.cpp`

Represents an order object with fields like instrument, amount, type, and price.

### `main.cpp`

Example usage and testing logic for placing/editing/canceling orders.

---

## 📢 Contact

Author: **Swapnil Agrawal**
Email: [swapnilagrawal259@gmail.com](mailto:swapnilagrawal259@gmail.com)
GitHub: [https://github.com/swapnil-259](https://github.com/swapnil-259)

---

## 📜 License

This project is licensed under the MIT License.
