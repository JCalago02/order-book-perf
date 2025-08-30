#pragma once
#include <Side.h>
#include <string>
#include <string_view>
#include <chrono>
#include <functional>
#include <sstream>
#include <iomanip>

class Order {
    public:
        Order(const std::string& party, double price, int quantity, std::chrono::time_point<std::chrono::system_clock> timestamp): 
            _party(party), _price(price), _quantity(quantity), _timestamp(timestamp) {}

        std::string getParty() const { return _party; }

        double getPrice() const { return _price; }

        int getQuantity() const { return _quantity; }

        void setQuantity(int quantity) { _quantity = quantity; }

        std::chrono::time_point<std::chrono::system_clock> getTimestamp() const { return _timestamp; }

        std::string toString() const {
            // Convert timestamp to readable format
            auto time_t = std::chrono::system_clock::to_time_t(_timestamp);
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(_timestamp.time_since_epoch()).count() % 1000;
            
            std::stringstream ss;
            ss << "Order[party=" << _party 
               << ", price=" << std::fixed << std::setprecision(2) << _price
               << ", quantity=" << _quantity 
               << ", timestamp=" << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S")
               << "." << std::setfill('0') << std::setw(3) << ms << "]";
            return ss.str();
        }

        int getMatchingQuantity(const Order& aggressingOrder, const Side& aggressingSide) const {
            if (aggressingSide == Side::BUY && aggressingOrder.getPrice() >= _price) {
                return std::min(_quantity, aggressingOrder.getQuantity());
            } else if (aggressingSide == Side::SELL && aggressingOrder.getPrice() <= _price) {
                return std::min(_quantity, aggressingOrder.getQuantity());
            }
            return 0;
        }

        static std::function<bool(const Order&, const Order&)> getBuyComparator() {
            return [](const Order& a, const Order& b) {
                return (a.getPrice() < b.getPrice() ||
                    (a.getPrice() == b.getPrice() && a.getTimestamp() < b.getTimestamp())
                );
            };
        }

        static std::function<bool(const Order&, const Order&)> getSellComparator() {
            return [](const Order& a, const Order& b) {
                return (a.getPrice() > b.getPrice() ||
                    (a.getPrice() == b.getPrice() && a.getTimestamp() < b.getTimestamp())
                );
            };
        }

        static std::function<bool(const Order&, const Order&)> getComparator(const Side& side) {
            return side == Side::BUY ? getBuyComparator() : getSellComparator();
        }
    private:
        std::string _party;
        double _price;
        int _quantity;
        std::chrono::time_point<std::chrono::system_clock> _timestamp;
};