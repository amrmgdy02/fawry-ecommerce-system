#pragma once
#include <string>
using namespace std;

// Interface for shippable items that the ShippingService can handle
class IShippableItem {
public:
    virtual ~IShippableItem() = default;
    virtual string getName() const = 0;
    virtual double getWeight() const = 0;
};
