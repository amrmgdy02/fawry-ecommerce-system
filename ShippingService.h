#pragma once
#include <vector>
#include <iostream>
#include <memory>
using namespace std;

class shippedItem {
public:
    virtual ~shippedItem() = default;
    virtual string getName() const = 0;
    virtual double getWeight() const = 0;
};

class ShippableItem : public shippedItem {
private:
    double weight;
    string name;
public:
    ShippableItem(const string& n, double w) : name(n), weight(w) {}
    string getName() const override {
        return name;
    }
    double getWeight() const override {
        return weight;
    }
};

class ShippingService {
private:
    vector<shared_ptr<shippedItem>> items;
public:
    void addItem(const shared_ptr<shippedItem>& item) {
        items.push_back(item);
    }

    void processShipment() const {
        for (const auto& item : items) {
            cout << "Processing Shipment for Item Name: " << item->getName() << ", Weight: " << item->getWeight() << endl;
        }
    }
};
