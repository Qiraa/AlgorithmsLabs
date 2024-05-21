#include "Calculator.h"
#include "Operation/Operation.h"
#include "Operation/Plus.h"
#include "Operation/Minus.h"
#include "Operation/Times.h"
#include "Operation/DividedBy.h"
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

const char* whitespaces = " \t\n\r\f\v";

inline string rtrim(string s, const char* t = whitespaces)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

inline string ltrim(string s, const char* t = whitespaces)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

inline string trim(string s, const char* t = whitespaces)
{
    return ltrim(rtrim(s, t), t);
}

int power(int n,int m) {
    if(m == 0)
        return 1;
    else
        return n*(power(n,m-1));
}

double parse_number(string part) {
    double result = 0.0;
    int len = part.length();
    int dotpos = 0;
    int sign = 1;
    for (int n = 0; n < len; n++) {
        if (n == 0) {
            if (part[n] == '-') {
                sign = -1;
                continue;
            } else if (part[n] == '+') {
                sign = 1;
                continue;
            }
        }
        if (part[n] == '.') {
            dotpos = len - n - 1;
        } else {
            result = result * 10 + (part[n]-'0');
        }
    }
    result /= power(10,dotpos);
    return sign * result;
}

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool is_number(string part) {
    if (!is_digit(part[0]) && part.size() == 1) {
        return false;
    }
    if (part[0] != '-' && part[0] != '+' && !is_digit(part[0])) {
        return false;
    }
    bool facedPoint = false;
    for (int i = 1; i < part.length(); i++) {
        if (part[i] == '.') {
            if (facedPoint) {
                return false;
            }
            facedPoint = true;
        } else if (!is_digit(part[i])) {
            return false;
        }
    }
    return true;
}

string Calculator::to_rpn(string input) {
    stringstream output;
    stack<string> stack;
    vector<string> parts;

    stringstream part;
    for (char c: input) {
        if (c == '(' || c == ')') {
            if (!part.str().empty()) {
                parts.push_back(part.str());
                part.str("");
            }
            part << c;
            parts.push_back(part.str());
            part.str("");
        } else if (c == ' ' || c == '\t') {
            if (!part.str().empty()) {
                parts.push_back(part.str());
                part.str("");
            }
        } else {
            part << c;
        }
    }
    parts.push_back(part.str());

    for (string part : parts) {
        if (is_number(part)) {
            output << " " << part;
        } else {
            if (stack.empty()) {
                stack.push(part);
            } else if (part == ")") {
                while (!stack.empty()) {
                    string op = stack.top();
                    stack.pop();
                    if (op == "(") {
                        break;
                    }
                    output << " " << op;
                }
            } else if (part == "(") {
                stack.push(part);
            } else {
                string top = stack.top();
                if (top != "(") {                    
                    Operation* last_operation = this->operations[top];
                    Operation* current_operation = this->operations[part];
                    if (current_operation->priority() <= last_operation->priority()) {
                        output << " " << top;
                        stack.pop();
                    }
                }
                stack.push(part);
            }
        }
    }

    while (!stack.empty()) {
        output << " ";
        string op = stack.top();
        stack.pop();
        output << op;
    }

    return trim(output.str()); 
}

Calculator::Calculator() {
    Plus* plus = new Plus();
    Minus* minus = new Minus();
    Times* times = new Times();
    DividedBy* dividedBy = new DividedBy();
    this->registrate("+", plus);
    this->registrate("-", minus);
    this->registrate("*", times);
    this->registrate("/", dividedBy);
}

void Calculator::registrate(string name, Operation* operation)
{
    this->operations[name] = operation;
}

double Calculator::evaluate(string expression) {
    stack<double> stack;
    istringstream stream(to_rpn(expression));
    while (!stream.eof()) {
        string part;
        stream >> part;
        if (is_number(part)) {
            double number = parse_number(part);
            stack.push(number);
        } else {
            Operation* operation = this->operations[part];
            if (operation == nullptr) {
                throw "Unknown operation " + part;
            }
            double result = operation->operate(stack);
            stack.push(result);
        }
    }

    return stack.top();
}