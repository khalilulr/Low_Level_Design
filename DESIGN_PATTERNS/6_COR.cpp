#include <iostream>
using namespace std;


class Handler {

public:

    virtual void setNext(Handler* next) = 0;

    virtual void handle(int days) = 0;

    virtual ~Handler() = default;
};


class Manager : public Handler {

private:

    Handler* next = nullptr;

public:

    void setNext(Handler* next) override {
        this->next = next;
    }

    void handle(int days) override {

        if (days <= 2) {
            cout << "Manager approved the leave\n";
        }
        else if (next != nullptr) {
            next->handle(days);
        }
    }
};


class Director : public Handler {

private:

    Handler* next = nullptr;

public:

    void setNext(Handler* next) override {
        this->next = next;
    }

    void handle(int days) override {

        if (days <= 5) {
            cout << "Director approved the leave\n";
        }
        else if (next != nullptr) {
            next->handle(days);
        }
    }
};


class VP : public Handler {

private:

    Handler* next = nullptr;

public:

    void setNext(Handler* next) override {
        this->next = next;
    }

    void handle(int days) override {

        if (days <= 10) {
            cout << "VP approved the leave\n";
        }
        else if (next != nullptr) {
            next->handle(days);
        }
    }
};


class CEO : public Handler {

public:

    void setNext(Handler* next) override {
        cout<<"No next after ceo\n";
        return;
    }

    void handle(int days) override {

        cout << "CEO approved the leave\n";
    }
};


int main() {

    Manager manager;
    Director director;
    VP vp;
    CEO ceo;

    manager.setNext(&director);
    director.setNext(&vp);
    vp.setNext(&ceo);

    manager.handle(1);

    return 0;
}