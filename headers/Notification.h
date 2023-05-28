//
// Created by comme on 5/28/2023.
//

#ifndef YELLOW_BELT_CPP_NOTIFICATION_H
#define YELLOW_BELT_CPP_NOTIFICATION_H
#include <iostream>

class INotifier {
public:
    virtual void Notify(const std::string& message) = 0;
};

class SmsNotifier : public INotifier {
public:
    SmsNotifier(const std::string& phone_number_): phone_number(phone_number_) {
    }

    void SendSms(const std::string& number, const std::string& message) {
        std::cout << "Send '" << message << "' to number " << number << std::endl;
    }

    void Notify(const std::string& message) override {
        SendSms(this->phone_number, message);
    }

private:
    const std::string phone_number;
};

class EmailNotifier : public INotifier {
public:

    EmailNotifier(const std::string& email_): email(email_) {
    }

    void SendEmail(const std::string& email, const std::string& message) {
        std::cout << "Send '" << message << "' to e-mail "  << email << std::endl;
    }

    void Notify(const std::string& message) override {
        SendEmail(this->email, message);
    }

private:
    const std::string email;
};

void Notify(INotifier& notifier, const std::string& message) {
    notifier.Notify(message);
}

void test() {
    SmsNotifier sms{"+7-495-777-77-77"};
    EmailNotifier email{"na-derevnyu@dedushke.ru"};

    Notify(sms, "I have White belt in C++");
    Notify(email, "And want a Yellow one");
}


#endif //YELLOW_BELT_CPP_NOTIFICATION_H
