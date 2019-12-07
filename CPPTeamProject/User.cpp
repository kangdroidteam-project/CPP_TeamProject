#include "User.h"

User::User() {
    this->name = "NULL";
    this->money_value = 0;
    this->saved_value = 0;
}

string User::getName() {
    return this->name;
}

int User::getMoneyValue() {
    return this->money_value;
}

int User::getSavedValue() {
    return this->saved_value;
}

void User::setMoneyValue(int val) {
    this->money_value = val;
}

void User::setName(string val) {
    this->name = val;
}

void User::setSave(int val) {
    this->saved_value = val;
}

void User::init() {
    cout << "Input User Name: ";
    cin >> this->name;

    this->money_value = 0;
    this->saved_value = 0;
}
