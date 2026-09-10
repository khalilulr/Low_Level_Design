#include <bits/stdc++.h>
using namespace std;

class PaymentStrategy {
public:
    virtual void pay() = 0;

    virtual ~PaymentStrategy() = default;
};

class GPay : public PaymentStrategy {
public:
    void pay() override {
        cout << "Pay through GPay\n";
    }
};

class CreditCard : public PaymentStrategy {
public:
    void pay() override {
        cout << "Pay through Credit Card\n";
    }
};

class PayPal : public PaymentStrategy {
public:
    void pay() override {
        cout << "Pay through PayPal\n";
    }
};

class Payment {
private:
    PaymentStrategy* strategy;

public:
    Payment(PaymentStrategy* strategy)
        : strategy(strategy) {}

    void pay() {
        strategy->pay();
    }
};

int main() {

    GPay gPay;

    Payment payment(&gPay);

    payment.pay();

    return 0;
}