#pragma once

#include <stack>
#include <string>

class Operation {
    public:
    virtual double operate(std::stack<double>& stack) = 0;
    virtual int priority() = 0;
};