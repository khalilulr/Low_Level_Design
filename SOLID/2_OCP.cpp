#include <iostream>
#include <memory>
#include <string>

using namespace std;

/*
    Open/Closed Principle (OCP)

    Software entities should be:
    - Open for extension
    - Closed for modification

    We can add a new payment method without modifying
    PaymentService.
*/

// Interface / Abstract class
class Payment {
public:
    virtual void pay() = 0;

    // Virtual destructor is important for polymorphic classes
    virtual ~Payment() = default;
};


// Concrete implementation
class GooglePay : public Payment {
public:
    void pay() override {
        cout << "Payment through Google Pay completed\n";
    }
};


// Concrete implementation
class PhonePay : public Payment {
public:
    void pay() override {
        cout << "Payment through PhonePe completed\n";
    }
};


// Service depends on abstraction, not concrete implementations
class PaymentService {
private:
    Payment& paymentMethod;

public:
    explicit PaymentService(Payment& paymentMethod)
        : paymentMethod(paymentMethod) {}

    void pay() {
        paymentMethod.pay();
    }
};


int main() {

    GooglePay googlePay;
    PhonePay phonePay;

    PaymentService googlePayment(googlePay);
    googlePayment.pay();

    PaymentService phonePayment(phonePay);
    phonePayment.pay();

    return 0;
}