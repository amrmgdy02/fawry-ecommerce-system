#include "Customer.h"
#include <iostream>
using namespace std;

Customer::Customer(string name, double balance) : name(name), balance(balance), cart(new ShoppingCart()) {}

Customer::~Customer() {
    delete cart;
}

void Customer::addToCart(const shared_ptr<Product>& item, int quantity) {
    cart->add(item, quantity);
}

void Customer::removeFromCart(const shared_ptr<Product>& item) {
    cart->remove(item);
}

bool Customer::checkout() {
    
    if (cart->isEmpty()) {
        cout << "Cart is empty. Please add items to the cart before checkout." << endl;
        return false;
    }

    double totalCost = cart->calculateTotalCost();
    if (totalCost > balance) {
        cout << "Insufficient balance for checkout. Total cost: " << totalCost << ", Balance: " << balance << endl;
        return false;
    }
    
    if (!cart->proceedChecout()) {
        cout << "Checkout failed due to item issues (expired or insufficient quantity)." << endl;
        return false;
    }
    // Checkout successful
    balance -= totalCost;
    cout << endl << "-------------------" << endl;
    cout << "Checkout successful. Remaining balance: " << balance << endl;
    return true;
}
