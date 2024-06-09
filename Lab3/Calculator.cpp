#include "Calculator.h"
#include "Operation/Operation.h"
#include "Operation/Plus.h"
#include "Operation/Minus.h"
#include "Operation/Times.h"
#include "Operation/DividedBy.h"
#include "Operation/JustNumber.h"
#include "Token.h"
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

Token* to_token(string str) {
    if (is_number(str)) {
        return new Token(Number, str);
    } else if (str == "(") {
        return new Token(OpeningBracket, str);
    } else if (str == ")") {
        return new Token(ClosingBracket, str);
    } else {
        return new Token(Operator, str);
    }
}

vector<Token*> tokenize(string input) {
    vector<Token*> result;
    stringstream token;

    for (char c: input) {
        switch (c) {
        case ' ':
        case ',':
            if (!token.str().empty()) {
                result.push_back(to_token(token.str()));
                token.str("");
            }
            break;
        case '(':
            if (!token.str().empty()) {
                result.push_back(to_token(token.str()));
                token.str("");
            }
            result.push_back(new Token(OpeningBracket, "("));
            break;
        case ')':
            if (!token.str().empty()) {
                result.push_back(to_token(token.str()));
                token.str("");
            }
            result.push_back(new Token(ClosingBracket, ")"));
            break;
        default:
            token << c;
            break;
        }
    }
    if (!token.str().empty()) {
        result.push_back(to_token(token.str()));
        token.str("");
    }

    return result;
}

vector<Operation*> Calculator::to_rpn(vector<Token*> tokens) {
    vector<Operation*> result;
    stack<Token*> stack;

    for (auto token: tokens) {
        TokenType type = token->getType();
        switch (type) {
        case Number:
            result.push_back(new JustNumber(parse_number(token->getValue())));
            break;
        case OpeningBracket:
            stack.push(token);
            break;
        case ClosingBracket:
            while (!stack.empty()) {
                Token* top = stack.top();
                stack.pop();
                if (top->getType() == OpeningBracket) {
                    break;
                } else if (top->getType() == Number) {
                    result.push_back(new JustNumber(parse_number(top->getValue())));
                } else if (top->getType() == Operator) {
                    result.push_back(this->operations[top->getValue()]);
                }
            }
            break;
        case Operator:
            if (!stack.empty()) {
                Token* top = stack.top();
                if (top->getType() != OpeningBracket) {
                    Operation* last_operation = this->operations[top->getValue()];
                    Operation* current_operation = this->operations[token->getValue()];
                    if (current_operation->priority() <= last_operation->priority()) {
                        result.push_back(last_operation);
                        stack.pop();
                    }
                }
            }
            stack.push(token);
            break;
        }
    }

    while (!stack.empty()) {
        Token* token = stack.top();
        stack.pop();
        if (token->getType() == Number) {
            result.push_back(new JustNumber(parse_number(token->getValue())));
        } else if (token->getType() == Operator) {
            result.push_back(this->operations[token->getValue()]);
        }
    }

    return result;
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
    vector<Token*> tokens = tokenize(expression);
    vector<Operation*> operations = this->to_rpn(tokens);
    for (Operation* operation: operations) {
        operation->operate(stack);
    }
    return stack.top();
}