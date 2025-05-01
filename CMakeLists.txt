cmake_minimum_required(VERSION 3.10)
project(DeriTradeX)

set(CMAKE_CXX_STANDARD 17)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third-party  
    ${CURL_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR}
)


link_directories(/opt/homebrew/opt/openssl/lib)

find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
find_package(ixwebsocket REQUIRED)


add_executable(DeriTradeX
    src/main.cpp
    src/api/DeribitAPI.cpp
    src/ws/DeriWebSocketServer.cpp
    src/utils/HttpClient.cpp
    src/utils/Logger.cpp
    src/utils/JSONUtils.cpp
)

target_link_libraries(DeriTradeX
    ${CURL_LIBRARIES}
    OpenSSL::SSL
    OpenSSL::Crypto
    ixwebsocket::ixwebsocket)

