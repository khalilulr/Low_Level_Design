#include <bits/stdc++.h>

using namespace std;

class Notification {
public:
    virtual void send() = 0;

    virtual ~Notification() = default;
};


class Email : public Notification {
public:
    void send() override {
        cout << "Notification sent through Email\n";
    }
};


class SMS : public Notification {
public:
    void send() override {
        cout << "Notification sent through SMS\n";
    }
};


class PushNotification : public Notification {
public:
    void send() override {
        cout << "Notification sent through Push Notification\n";
    }
};


class NotificationFactory {

public:

    unique_ptr<Notification> createNotification(string type) {

        transform(type.begin(), type.end(), type.begin(),
                  [](unsigned char c) {
                      return tolower(c);
                  });

        if (type == "email") {
            return make_unique<Email>();
        }

        if (type == "sms") {
            return make_unique<SMS>();
        }

        if (type == "push") {
            return make_unique<PushNotification>();
        }

        return nullptr;
    }
};


int main() {

    NotificationFactory factory;

    auto notification =
        factory.createNotification("Email");

    if (notification) {
        notification->send();
    }
}