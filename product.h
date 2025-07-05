#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <ctime>
using namespace std;
#include "Expiration.h"
#include "Shipping.h"

class Product
{
private:
    string name;
    double price;
    int quantity;

    unique_ptr<Expiration> expiration; 
    unique_ptr<ShippingInterface> shipping;

public:
    Product(string name = "product",
    double price = 0.0,
    int quantity = 0,
    unique_ptr<Expiration> expiration = nullptr,
    unique_ptr<ShippingInterface> shipping = nullptr)
        : name(name), price(price), quantity(quantity), expiration(move(expiration)), shipping(move(shipping)) {};

    ~Product();

    void setName(const string& newName);
    void setPrice(const double newPrice);
    void setQuantity(const int newQuantity);
    
    string getName() {
        return name;
    };
    double getPrice() const {
        return price;
    };

    /*************************Expiration*******************************/
    bool isExpired() const
    {
        if (auto* e = dynamic_cast<Expiration*>(expiration.get()))
        {
            return e->isExpired();
        }
            return false;
    }
    std::time_t getExpiryDate() const
    {
        if (auto* e = dynamic_cast<Expirable*>(expiration.get()))
            return e->getExpiryDate();
        return 0;
    }

    /*************************Shipping*******************************/
    double getWeight() const
    {
        if (auto* s = dynamic_cast<Shippable*>(shipping.get()))
            return s->getWeight();
        return 0.0;
    }
    double getShippingCost() const
    {
        if (auto* s = dynamic_cast<Shippable*>(shipping.get()))
            return s->getShippingCost();
        return 0.0f;
    }
    bool isShippable() const
    {
        return shipping && shipping->isShippable();
    }

    /*************************Helpers*******************************/
    bool isAvailable() const
    {
        return quantity > 0;
    }
    int getQuantity() const
    {
        return quantity;
    }
    void reduceQuantity(int amount)
    {
        quantity -= amount;
    }

};
