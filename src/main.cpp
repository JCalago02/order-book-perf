#include <iostream>
#include <Trade.h>

int main() {
    Trade trade("Alice", "Bob", 100.0, 10);
    std::cout << trade.getBuyer() << std::endl;

    return 0;
}