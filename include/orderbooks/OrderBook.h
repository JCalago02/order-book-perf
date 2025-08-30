#pragma once
#include <Order.h>
#include <Side.h>
#include <Trade.h>

#include <vector>

class IOrderBook {
    public:
        virtual std::vector<Trade> addOrder(const Order& order, const Side& side) = 0;
        virtual std::vector<double> getPriceLevels(const Side& side) = 0;
        virtual std::vector<Order> getOrders(const int priceLevel, const Side& side) = 0;
};