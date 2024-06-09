#pragma once

#include <string>

using namespace std;

enum TokenType { Number, Operator, OpeningBracket, ClosingBracket };

class Token {
private:
    TokenType type;
    string value;
public:
    Token(TokenType type, string value): type(type), value(value) { };
    TokenType getType() {
        return type;
    }
    string getValue() {
        return value;
    }
};