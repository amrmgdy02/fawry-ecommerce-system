#pragma once
#include <ctime>
#include <string>
using namespace std;

class Expiration {
public:
    virtual ~Expiration() = default;
    virtual bool isExpired() const = 0;
};

class Expirable : public Expiration {
    public:
        bool isExpired() const override = 0;
        virtual void setExpiryDate(const std::time_t expiryDate) = 0;
        virtual std::time_t getExpiryDate() const = 0;
};

class ExpirableProduct : public Expirable {
    private:
        std::time_t expiryDate;
    public:
        ExpirableProduct(const std::time_t expiryDate) : expiryDate(expiryDate) {}
        void setExpiryDate(const std::time_t date) override {
            this->expiryDate = date;
        }
        std::time_t getExpiryDate() const override {
            return this->expiryDate;
        }
        bool isExpired() const override {
            // compare current date with the expiry date
            if (std::time(nullptr) > expiryDate) {
                return true;
            }
            return false;
        }
        ~ExpirableProduct() override = default;
};

class NonExpirableProduct : public Expiration {
    public:
        bool isExpired() const override {
            return false;
        };
        ~NonExpirableProduct() override = default;
};