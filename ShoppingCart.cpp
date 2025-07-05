#include "ShoppingCart.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Add item to shopping cart
bool ShoppingCart::add(const shared_ptr<Product>& item, int quantity) {
    if (item->getQuantity() >= quantity) {
        for (auto& cartItem : items) {
            if (cartItem.first == item) {
                cartItem.second += quantity;
                return true;
            }
        }
        items.push_back(make_pair(item, quantity));
        return true;
    } else {
        cout << "Failed to add " << item->getName() << " to the cart." << endl;
        return false;
    }
}
// Remove item from shopping cart
void ShoppingCart::remove(const shared_ptr<Product>& item) {
    items.erase(remove_if(items.begin(), items.end(), 
        [&item](const pair<shared_ptr<Product>, int>& cartItem) {
            return cartItem.first == item;
        }), items.end());
}

bool ShoppingCart::isEmpty() {
    return items.empty();
}

double ShoppingCart::getTotalPrice() const {
    double total = 0.0;
    for (const auto& cartItem : items) {
        total += cartItem.first->getPrice() * cartItem.second;
    }
    return total;
}

double ShoppingCart::getShippingFees() const {
    double totalShipping = 0.0;
    for (const auto& cartItem : items) {
        if (cartItem.first->isShippable())
            totalShipping += cartItem.first->getShippingCost() * cartItem.second;
    }
    return totalShipping;
}

double ShoppingCart::calculateTotalCost() {
    return getTotalPrice() + getShippingFees();
}

void ShoppingCart::displayShippableItems() {
    cout << "** Shipment notice **" << endl;
    vector<pair<shared_ptr<Product>, int>> shippableItems = getShippableItems();
    double totalWeight = 0;
    for (auto& cartItem : shippableItems) {
        double weight = static_cast<double>(cartItem.first->getWeight()) * static_cast<double>(cartItem.second);
        cout << cartItem.second << "x " << cartItem.first->getName()
             << "  " << weight << "g" << endl;
        totalWeight += weight;
    }
    cout << "Total Package weight: " << totalWeight << "g" << endl << endl;
}

void ShoppingCart::displayReceipt() {
    cout << "** Checkout receipt **" << endl;
    for (auto& cartItem : items) {
        cout << cartItem.second << "X " << cartItem.first->getName()
             << "  " << (cartItem.first->getPrice() * cartItem.second) << endl;
    }
    cout << endl;
}

void ShoppingCart::displayCheckOutDetails() {
    displayShippableItems();
    displayReceipt();
    cout << "-------------------" << endl;
    cout << "Subtotal: " << getTotalPrice() << endl;
    cout << "Shipping: " << getShippingFees() << endl;
    cout << "Total Cost: " << calculateTotalCost() << endl << endl;
    cout << "-------------------" << endl;
}

bool ShoppingCart::proceedChecout() {
    bool success = true;
    for (auto& cartItem : items) {
        if (cartItem.first->isExpired() || cartItem.second > cartItem.first->getQuantity()) {
            cout << "Item " << cartItem.first->getName() 
                 << " is either expired or insufficient quantity. Removing from cart." << endl;
            remove(cartItem.first);
            success = false;
        } else {
            // reduce the quantity in stock
            cartItem.first->reduceQuantity(cartItem.second);
        }
    }
    if (success) {
        displayCheckOutDetails();
        processShipment();
        items.clear();
    }
    return success;
}

vector<pair<shared_ptr<Product>, int>> ShoppingCart::getShippableItems() const {
    vector<pair<shared_ptr<Product>, int>> shippableItems;
    for (const auto& item : items) {
        if (item.first->isShippable()) {
            shippableItems.push_back(item);
        }
    }
    return shippableItems;
}

void ShoppingCart::processShipment() {
    ShippingService shippingService;
    for (const auto& item : getShippableItems()) {
        auto shippableItem = make_shared<ShippableItem>(
            item.first->getName(), 
            static_cast<double>(item.first->getWeight() * item.second)
        );
        shippingService.addItem(shippableItem);
    }
    shippingService.processShipment();
}
