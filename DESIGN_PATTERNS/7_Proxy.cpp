#include <bits/stdc++.h>
using namespace std;

class User {
private:
    string role;
    string name;

public:
    User(string name, string role)
        : name(name), role(role) {}

    string getName() {
        return name;
    }

    string getRole() {
        return role;
    }
};


class UserServiceInterface {
public:
    virtual void getAllUser() = 0;
    virtual void deleteUser(string name) = 0;

    virtual ~UserServiceInterface() = default;
};


class UserServiceImp : public UserServiceInterface {
public:
    void getAllUser() override {
        cout << "Get all users is called\n";
    }

    void deleteUser(string name) override {
        cout << "Delete user API is called. "
             << "User with name: " << name << " deleted\n";
    }
};


class UserServiceProxy : public UserServiceInterface {
private:
    UserServiceImp realUserService;
    User* user;

public:
    UserServiceProxy(User* user)
        : user(user) {}

    void getAllUser() override {
        realUserService.getAllUser();
    }

    void deleteUser(string name) override {

        if (user->getRole() != "admin") {
            cout << "You're not eligible\n";
            return;
        }

        realUserService.deleteUser(name);
    }
};


int main() {

    User alice("alice", "admin");
    User bob("bob", "user");

    UserServiceProxy userServiceAlice(&alice);
    UserServiceProxy userServiceBob(&bob);

    userServiceAlice.getAllUser();
    userServiceAlice.deleteUser("alice");

    userServiceBob.getAllUser();
    userServiceBob.deleteUser("bob");

    return 0;
}