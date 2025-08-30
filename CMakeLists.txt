cmake_minimum_required(VERSION 3.28)

project(order-book-perf)

# Trade utilities library (core data structures)
add_library(tradeUtils INTERFACE)
target_include_directories(tradeUtils INTERFACE ${PROJECT_SOURCE_DIR}/include/tradeUtils)

# Order book library (depends on tradeUtils)
add_library(orderbook
    src/OrderBook.cpp
    src/ArrayOrderBook.cpp
)
target_include_directories(orderbook PUBLIC ${PROJECT_SOURCE_DIR}/include/orderbooks)
target_link_libraries(orderbook PUBLIC tradeUtils)

# Main executable
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} orderbook tradeUtils)