cmake_minimum_required(VERSION 3.28)

project(order-book-perf)
add_executable(${PROJECT_NAME} src/main.cpp)

add_library(tradeUtils INTERFACE)
target_include_directories(tradeUtils INTERFACE ${PROJECT_SOURCE_DIR}/include/tradeUtils)

add_library(orderbook
    src/OrderBook.cpp
)
target_link_libraries(${PROJECT_NAME} tradeUtils)