#include "Plus.h"
#include <string>
#include <stack>

using namespace std;

double Plus::operate(stack<double>& stack) {
    double a = stack.top();
    stack.pop();
    double b = stack.top();
    stack.pop();
    return a + b;
}

int Plus::priority() {
    return 0;
}