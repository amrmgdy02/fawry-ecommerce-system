#pragma once

#include "ShoppingCart.h"
#include "Product.h"
#include <string>
#include <memory>
using namespace std;

class Customer {
private:
    string name;
    double balance;
    ShoppingCart* cart;

public:
    Customer(string name, double balance);
    ~Customer();

    void addToCart(const shared_ptr<Product>& item, int quantity);
    void removeFromCart(const shared_ptr<Product>& item);
    bool checkout();
};
