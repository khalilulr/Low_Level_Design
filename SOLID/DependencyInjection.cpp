#include <iostream>
using namespace std;


/*
    Concrete dependency
*/
// class EmailService {
// public:
//     void sendEmail() {
//         cout << "Email sent\n";
//     }
// };


/*
    UserService directly creates EmailService.

    This means UserService is tightly coupled to EmailService.
*/
// class UserService {
// public:

//     void registerUser() {

//         cout << "User registered\n";

//         // UserService creates its own dependency
//         EmailService emailService;

//         emailService.sendEmail();
//     }
// };

//-----------------------------WITH Dependency Injection---------------------------------------

/*
    Abstraction
*/
class NotificationService {
public:
    virtual void send() = 0;

    virtual ~NotificationService() = default;
};


/*
    Concrete dependency
*/
class EmailService : public NotificationService {
public:
    void send() override {
        cout << "Email sent\n";
    }
};


/*
    Another concrete dependency
*/
class SmsService : public NotificationService {
public:
    void send() override {
        cout << "SMS sent\n";
    }
};


/*
    High-level class

    UserService does NOT create EmailService or SmsService.

    Instead, the dependency is injected through the constructor.
*/
class UserService {
private:
    NotificationService& notificationService;

public:

    UserService(NotificationService& notificationService)
        : notificationService(notificationService) {}

    void registerUser() {
        cout << "User registered\n";

        notificationService.send();
    }
};


int main() {
    
    // UserService userService;
    
    // userService.registerUser();



    EmailService emailService;
    
    UserService user1(emailService);
    
    user1.registerUser();
    
    
    cout << "\n";
    
    
    SmsService smsService;
    
    UserService user2(smsService);
    
    user2.registerUser();

    return 0;
}