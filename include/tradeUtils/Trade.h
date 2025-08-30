#pragma once
#include <string>
#include <string_view>
#include <sstream>
#include <iomanip>

class Trade {
    public:
        Trade(const std::string& buyer, const std::string& seller, double price, int quantity): _buyer(buyer), _seller(seller), _price(price), _quantity(quantity) {}

        std::string_view getBuyer() const { return _buyer; }
        std::string_view getSeller() const { return _seller; }
        double getPrice() const { return _price; }
        int getQuantity() const { return _quantity; }

        std::string toString() const {
            std::stringstream ss;
            ss << "Trade[buyer=" << _buyer 
               << ", seller=" << _seller
               << ", price=" << std::fixed << std::setprecision(2) << _price
               << ", quantity=" << _quantity << "]";
            return ss.str();
        }

    private:
        std::string _buyer;
        std::string _seller;
        double _price;
        int _quantity;
};