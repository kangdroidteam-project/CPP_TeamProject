#pragma once
#include <iostream>
#include <string>

using namespace std;
class User {
private:
    string name;
    int money_value;
    int saved_value;

public:
    User();
    string getName();
    int getMoneyValue();
    int getSavedValue();

    void setMoneyValue(int val);
    void setName(string val);
    void setSave(int val);
    void init();
};

