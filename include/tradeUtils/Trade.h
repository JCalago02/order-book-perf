#pragma once
#include <string>

class Trade {
    public:
        Trade(std::string buyer, std::string seller, double price, int quantity): _buyer(buyer), _seller(seller), _price(price), _quantity(quantity) {}

        std::string getBuyer() const { return _buyer; }
        std::string getSeller() const { return _seller; }
        double getPrice() const { return _price; }
        int getQuantity() const { return _quantity; }

    private:
        std::string _buyer;
        std::string _seller;
        double _price;
        int _quantity;
};