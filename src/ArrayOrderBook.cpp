#include <ArrayOrderBook.h>

/*
    Price Time Priority based FIFO matching structure
*/
std::vector<Trade> ArrayOrderBook::addOrder(const Order& order, const Side& side) {
    std::vector<Order> &restingSide = side == Side::BUY ? _bids : _asks;
    std::vector<Order> &matchingSide = side == Side::BUY ? _asks: _bids;

    auto cmp = Order::getComparator(side);

    int remQuantity = order.getQuantity();

    // Match Agressive Side
    std::vector<Trade> trades;
    while (remQuantity > 0 && matchingSide.size() > 0) {
        Order &matchingOrder = matchingSide[matchingSide.size() - 1];
        int matchingQuantity = matchingOrder.getMatchingQuantity(order, side);

        if (matchingQuantity == 0) {
            break;
        }

        // Handle Trade
        matchingOrder.setQuantity(matchingOrder.getQuantity() - matchingQuantity);
        remQuantity -= matchingQuantity;
        if (matchingOrder.getQuantity() == 0) { // full match
            matchingSide.pop_back();
        }

        trades.emplace_back(Trade(
            side == Side::BUY ? matchingOrder.getParty() : order.getParty(),
            side == Side::BUY ? order.getParty() : matchingOrder.getParty(),
            matchingOrder.getPrice(),
            matchingQuantity
        ));
    }

    // Add Resting Side
    if (remQuantity > 0) {
        Order newOrder(order);
        newOrder.setQuantity(remQuantity);
        const auto& it = std::upper_bound(restingSide.begin(), restingSide.end(), newOrder, cmp);
        restingSide.insert(it, newOrder);
    }
    
    return trades;
}

std::vector<double> ArrayOrderBook::getPriceLevels(const Side& side) {
    std::vector<Order> &orders = side == Side::BUY ? _bids : _asks;


    std::vector<double> priceLevels;
    double prevPrice = -1; // Dummy value to ensure first price level is added
    for (const auto& order : orders) {
        bool isNewPrice = prevPrice != order.getPrice();
        if (isNewPrice) {
            priceLevels.push_back(order.getPrice());
            prevPrice = order.getPrice();
        }
    }
    return priceLevels;
}

std::vector<Order> ArrayOrderBook::getOrders(const int priceLevel, const Side& side) {
    std::vector<Order> &orders = side == Side::BUY ? _bids : _asks;
    auto cmp = Order::getComparator(side);

    Order targetOrder("", priceLevel, 0, std::chrono::time_point<std::chrono::system_clock>::min());
    auto it = std::upper_bound(orders.begin(), orders.end(), targetOrder, cmp);

    std::vector<Order> ordersAtPrice;
    while (it != orders.end() && it->getPrice() == priceLevel) {
        ordersAtPrice.push_back(*it);
        ++it;
    }

    return ordersAtPrice;
}