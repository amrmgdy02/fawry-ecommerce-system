#pragma once

#include "Product.h"
#include "ShippingService.h"
#include <vector>
#include <memory>

class ShoppingCart {
private:
    std::vector<std::pair<std::shared_ptr<Product>, int>> items;

public:
    bool add(const std::shared_ptr<Product>& item, int quantity = 1);
    void remove(const std::shared_ptr<Product>& item);
    bool isEmpty();
    
    double getTotalPrice() const;
    double getShippingFees() const;
    double calculateTotalCost();

    void displayShippableItems();
    void displayReceipt();
    void displayCheckOutDetails();
    bool proceedChecout();

    std::vector<std::pair<std::shared_ptr<Product>, int>> getShippableItems() const;
    void processShipment();
};
