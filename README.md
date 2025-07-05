# E-Commerce System in C++

## Overview
A comprehensive C++ e-commerce system supporting multiple product types (digital, shippable, expirable), customer management, shopping cart functionality, and shipping services.

## Features
- **Product Types**: Digital, Shippable, Expirable products with support for combined attributes
- **Shopping Cart**: Add/remove items, quantity management, stock validation
- **Customer Management**: Balance tracking, purchase history
- **Shipping Service**: Weight-based shipping cost calculation
- **Validation**: Stock limits, expiration dates, insufficient balance handling

## Compilation Instructions

### Using g++
```bash
g++ -std=c++11 -o ecommerce main.cpp Product.cpp Customer.cpp ShoppingCart.cpp
```

### Using Visual Studio (Windows)
```cmd
cl /EHsc main.cpp Product.cpp Customer.cpp ShoppingCart.cpp
```

## Running the Application
```bash
./ecommerce
```

## Test Scenarios
The main.cpp includes comprehensive test scenarios:
1. Mixed cart with digital, shippable, and expirable products
2. Insufficient balance handling
3. Stock limit validation
4. Expired product detection
5. Digital-only purchases
6. Heavy shipping calculations
7. Empty cart handling
8. Large order processing

## File Structure
- `main.cpp` - Main application with test scenarios
- `Product.h/cpp` - Product class hierarchy and implementations
- `Customer.h/cpp` - Customer class for user management
- `ShoppingCart.h/cpp` - Shopping cart functionality
- `Expiration.h` - Interface for expirable products
- `Shipping.h` - Interface for shippable products
- `ShippingService.h` - Shipping cost calculation service

## Requirements
- C++11 or later
- Standard C++ library support
