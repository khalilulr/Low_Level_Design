#include <iostream>
#include <string>

using namespace std;

/*
an e-commerce order system.

An order needs to:

Calculate the total.
Save the order to the database.
Send a confirmation email.
Generate an invoice.

*/

// =====================================================
// Entity
// Responsibility: Represent an Order
// =====================================================

class Order {
private:
    string customerEmail;
    double price;

public:
    Order(string email, double price)
        : customerEmail(email), price(price) {}

    const string& getCustomerEmail() const {
        return customerEmail;
    }

    double getPrice() const {
        return price;
    }
};


// =====================================================
// Order Calculator
// Responsibility: Calculate order total
// =====================================================

class OrderCalculator {
public:
    double calculateTotal(const Order& order) const {
        double tax = order.getPrice() * 0.18;

        return order.getPrice() + tax;
    }
};


// =====================================================
// Repository
// Responsibility: Persist Order
// =====================================================

class OrderRepository {
public:
    void save(const Order& order) {
        cout << "Saving order to database...\n";
    }
};


// =====================================================
// Email Service
// Responsibility: Send emails
// =====================================================

class EmailService {
public:
    void sendConfirmation(const Order& order) {
        cout << "Sending confirmation email to "
             << order.getCustomerEmail()
             << "\n";
    }
};


// =====================================================
// Invoice Generator
// Responsibility: Generate invoices
// =====================================================

class InvoiceGenerator {
public:
    void generate(
        const Order& order,
        double total
    ) {
        cout << "Generating invoice...\n";

        cout << "Customer: "
             << order.getCustomerEmail()
             << "\n";

        cout << "Total: "
             << total
             << "\n";
    }
};


// =====================================================
// Order Service
// Responsibility: Orchestrate order processing
// =====================================================

class OrderService {
private:
    OrderCalculator calculator;
    OrderRepository repository;
    EmailService emailService;
    InvoiceGenerator invoiceGenerator;

public:
    void processOrder(const Order& order) {

        double total =
            calculator.calculateTotal(order);

        repository.save(order);

        emailService.sendConfirmation(order);

        invoiceGenerator.generate(
            order,
            total
        );
    }
};


// =====================================================
// Main
// =====================================================

int main() {

    Order order(
        "khalil@example.com",
        1000
    );

    OrderService service;

    service.processOrder(order);

    return 0;
}