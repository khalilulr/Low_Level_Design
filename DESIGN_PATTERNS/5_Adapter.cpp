#include <iostream>
#include <memory>

using namespace std;


// Target Interface
class Notification {
public:
    virtual void send() = 0;

    virtual ~Notification() = default;
};


// Adaptee 1
class TwilioService {
public:
    void sendNotification() {
        cout << "Notification sent through Twilio\n";
    }
};


// Adaptee 2
class MSG91 {
public:
    void sendMSG() {
        cout << "Notification sent through MSG91\n";
    }
};


// Adapter 1
class TwilioAdapter : public Notification {

private:
    TwilioService twilio;

public:
    void send() override {
        twilio.sendNotification();
    }
};


// Adapter 2
class MSG91Adapter : public Notification {

private:
    MSG91 msg91;

public:
    void send() override {
        msg91.sendMSG();
    }
};


int main() {

    unique_ptr<Notification> notification =
        make_unique<TwilioAdapter>();
    unique_ptr<Notification> notifcationMSG=
        make_unique<MSG91Adapter>();

    notification->send();
    notifcationMSG->send();

    return 0;
}