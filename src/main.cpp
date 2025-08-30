#include <iostream>
#include <Trade.h>
#include <Order.h>
#include <Side.h>
#include <vector>
#include <ArrayOrderBook.h>

int main() {
    std::chrono::time_point<std::chrono::system_clock> dummyTime = std::chrono::system_clock::now();
    ArrayOrderBook orderBook;

    std::vector<Order> orders = {
        Order("Alice", 101.0, 10, dummyTime),
        Order("Jane", 100.0, 15, dummyTime),
        Order("Alice", 99.0, 10, dummyTime),
        Order("Alice", 99.12, 10, dummyTime),
        Order("Bob", 99.0, 100, dummyTime),
    };
    std::vector<Side> sides = {Side::BUY, Side::BUY, Side::BUY, Side::SELL, Side::SELL};
    for (int i = 0; i < orders.size(); i++) {
        std::cout << "Adding Order: " << orders[i].toString() << " Side: " << (sides[i] == Side::SELL ? "SELL" : "BUY") << std::endl;
        std::vector<Trade> trades = orderBook.addOrder(orders[i], sides[i]);
        for (const auto& trade : trades) {
            std::cout << "Trade: " << trade.toString() << std::endl;
        }
    }

    std::vector<double> priceLevels = orderBook.getPriceLevels(Side::BUY);
    for (const auto& priceLevel : priceLevels) {
        std::cout << "Price Level: " << priceLevel << std::endl;

        std::vector<Order> orders = orderBook.getOrders(priceLevel, Side::BUY);
        for (const auto& order : orders) {
            std::cout << "Order: " << order.toString() << std::endl;
        }
    }


    priceLevels = orderBook.getPriceLevels(Side::SELL);
    for (const auto& priceLevel : priceLevels) {
        std::cout << "Price Level: " << priceLevel << std::endl;


        std::vector<Order> orders = orderBook.getOrders(priceLevel, Side::SELL);
        for (const auto& order : orders) {
            std::cout << "Order: " << order.toString() << std::endl;
        }
    }
    return 0;
}