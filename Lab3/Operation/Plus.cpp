#include "Plus.h"
#include <string>
#include <stack>

using namespace std;

void Plus::operate(stack<double>& stack) {
    double a = stack.top();
    stack.pop();
    double b = stack.top();
    stack.pop();
    stack.push(a + b);
}

int Plus::priority() {
    return 0;
}

string Plus::to_string() {
    return "+";
}
