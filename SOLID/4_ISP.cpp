#include <iostream>
using namespace std;


/*
    ISP (Interface Segregation Principle)

    A class should not be forced to depend on methods
    that it does not need.
*/


/*
    Every bird can say something.
*/
class Bird {
public:
    virtual void say() = 0;

    virtual ~Bird() = default;
};


/*
    Only birds that can fly implement Flyable.
*/
class Flyable {
public:
    virtual void fly() = 0;

    virtual ~Flyable() = default;
};


/*
    Only birds that can swim implement Swimable.
*/
class Swimable {
public:
    virtual void swim() = 0;

    virtual ~Swimable() = default;
};


/*
    Penguin:
    - Is a Bird
    - Can Swim
    - Cannot Fly

    Therefore, Penguin does NOT inherit from Flyable.

    This is ISP:
    Penguin is not forced to implement fly().
*/
class Penguin : public Bird, public Swimable {
public:

    void say() override {
        cout << "Penguin says\n";
    }

    void swim() override {
        cout << "Penguin can swim\n";
    }
};


int main() {

    Penguin penguin;

    penguin.say();
    penguin.swim();

    return 0;
}