#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include "Customer.h"
#include "ShoppingCart.h"
using namespace std;

// Helper function to convert date string to time_t
time_t stringToTimeT(const string& dateStr) {
    struct tm tm = {};
    sscanf(dateStr.c_str(), "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    return mktime(&tm);
}

void printSeparator(const string& title) {
    cout << "\n" << string(50, '=') << endl;
    cout << "  " << title << endl;
    cout << string(50, '=') << endl;
}

int main() {
    printSeparator("E-COMMERCE SYSTEM");

    // SCENARIO 1: Both Expirable and Shippable Products //
    printSeparator("SCENARIO 1: Mixed Product Types");
    cout << "Testing products that are both expirable and shippable..." << endl;
    
    auto cheese = make_shared<Product>("Cheddar Cheese", 12.99, 50, 
        unique_ptr<Expiration>(new ExpirableProduct(stringToTimeT("2025-08-15"))), 
        unique_ptr<ShippingInterface>(new ShippableProduct(0.5, 3.0)));
    
    auto frozenMeat = make_shared<Product>("Premium Beef", 25.50, 30,
        unique_ptr<Expiration>(new ExpirableProduct(stringToTimeT("2025-09-01"))), 
        unique_ptr<ShippingInterface>(new ShippableProduct(2.0, 8.0)));


    // SCENARIO 2: Non-Expirable but Shippable Products //
    auto laptop = make_shared<Product>("Gaming Laptop", 1299.99, 15, 
        unique_ptr<Expiration>(new NonExpirableProduct()), 
        unique_ptr<ShippingInterface>(new ShippableProduct(2.5, 25.0)));
    
    auto books = make_shared<Product>("Books Set", 89.99, 25, 
        unique_ptr<Expiration>(new NonExpirableProduct()), 
        unique_ptr<ShippingInterface>(new ShippableProduct(1.2, 5.0)));


    // SCENARIO 3: No shipping, no expiry //
    auto software = make_shared<Product>("Software License", 199.99, 100, 
        unique_ptr<Expiration>(new NonExpirableProduct()), 
        unique_ptr<ShippingInterface>(new NonShippableProduct()));
    
    auto giftCard = make_shared<Product>("Mobile Gift Card", 50.0, 500, 
        unique_ptr<Expiration>(new NonExpirableProduct()), 
        unique_ptr<ShippingInterface>(new NonShippableProduct()));


    // SCENARIO 4: Expired Products (Should fail in checkout) //
    auto expiredMilk = make_shared<Product>("Expired Milk", 4.99, 20, 
        unique_ptr<Expiration>(new ExpirableProduct(stringToTimeT("2024-01-01"))), // Already expired
        unique_ptr<ShippingInterface>(new ShippableProduct(1.0, 2.0)));


    // TEST CASE 1: Regular Customer with Mixed Cart //
    printSeparator("TEST CASE 1 - Mixed Cart");
    Customer customer1("Amr Magdy", 2000.0);
    
    cout << "\n-> Adding products to cart..." << endl;
    customer1.addToCart(cheese, 3);           // Expirable + Shippable
    customer1.addToCart(laptop, 1);           // Non-expirable + Shippable  
    customer1.addToCart(software, 2);         // Non-shippable
    customer1.addToCart(books, 2);            // Non-expirable + Shippable
    
    customer1.checkout();

    // TEST CASE 2: Customer with Insufficient Balance //
    printSeparator("TEST CASE 2: Insufficient Balance");
    Customer customer2("Ali Ahmed", 100.0); 
    
    cout << "\n-> Attempting to buy expensive items with low balance..." << endl;
    customer2.addToCart(laptop, 2);           // should fail
    customer2.checkout();

    // TEST CASE 3: Quantity Exceeding Stock //
    printSeparator("TEST CASE 3: Quantity Exceeding Available Stock");
    Customer customer3("Ayman Alaa", 3000.0);
    
    cout << "\n-> Attempting to buy more than available stock..." << endl;
    customer3.addToCart(laptop, 20);          // Only 15 available (should fail: Failure in adding to cart not on checkout, so the checkout will succeed)
    customer3.addToCart(cheese, 5);           // Should succeed 
    customer3.checkout();

    // TEST CASE 4: Expired Products in Cart //
    printSeparator("TEST CASE 4: Expired Products Handling");
    Customer customer4("Mahmoud Aly", 1500.0);
    
    cout << "\n-> Adding expired product..." << endl;
    customer4.addToCart(expiredMilk, 2);      // Expired (should be removed)
    customer4.addToCart(frozenMeat, 3);       
    customer4.addToCart(giftCard, 1);   

    cout << "\n-> Checkout will not succeed..." << endl;
    customer4.checkout();

    // TEST CASE 5: (No Shipping) //
    printSeparator("TEST CASE 5: Digital-Only Purchase");
    Customer customer5("Bahaa", 800.0);
    
    cout << "\n-> Buying only digital products (no shipping costs)..." << endl;
    customer5.addToCart(software, 3); 
    customer5.addToCart(giftCard, 4); 
    customer5.checkout();

    return 0;
}