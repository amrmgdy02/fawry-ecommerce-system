#include "Product.h"

// Destructor implementation
Product::~Product() {}

// Setter implementations
void Product::setName(const string& newName) {
    name = newName;
}

void Product::setPrice(const double newPrice) {
    price = newPrice;
}

void Product::setQuantity(const int newQuantity) {
    quantity = newQuantity;
}
