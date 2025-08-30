#pragma once
#include <OrderBook.h>
#include <vector>
#include <algorithm>

class ArrayOrderBook : public IOrderBook {
    public:
        std::vector<Trade> addOrder(const Order& order, const Side& side) override;
        std::vector<double> getPriceLevels(const Side& side) override;
        std::vector<Order> getOrders(const int priceLevel, const Side& side) override;

        void printOrderBook();

    private:
        std::vector<Order> _bids;
        std::vector<Order> _asks;
};