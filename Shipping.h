#pragma once

// Abstraction for shipping strategy
class ShippingInterface {
    public:
        virtual ~ShippingInterface() = default;
        virtual bool isShippable() const = 0;
};

class Shippable : public ShippingInterface {
public:
    virtual double getShippingCost() const = 0;
    virtual double getWeight() const = 0;
};

class ShippableProduct : public Shippable {
private:
    double weight;
    double shippingCost;
public:
    explicit ShippableProduct(double w, double shippingCost) : weight(w), shippingCost(shippingCost) {}
    bool isShippable() const override { return true; }
    double getShippingCost() const override { return shippingCost; }
    double getWeight() const override { return weight; }
};

class NonShippableProduct : public ShippingInterface {
    public:
        bool isShippable() const override {
            return false;
        };
};
