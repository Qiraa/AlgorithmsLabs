#pragma once

#include <stack>
#include <string>

using namespace std;

class Operation {
    public:
    virtual void operate(std::stack<double>& stack) = 0;
    virtual int priority() = 0;
    virtual string to_string() = 0;
};