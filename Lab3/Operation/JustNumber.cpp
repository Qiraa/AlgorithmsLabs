#include "JustNumber.h"
#include <string>
#include <sstream>
#include <stack>
#include <limits.h>

using namespace std;

void JustNumber::operate(stack<double>& stack) {
    stack.push(this->value);
}

int JustNumber::priority() {
    return INT_MAX;
}

string JustNumber::to_string() {
    stringstream stream;
    stream << this->value;
    return stream.str();
}
