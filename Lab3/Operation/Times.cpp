#include "Times.h"
#include <string>
#include <stack>

using namespace std;

double Times::operate(stack<double>& stack) {
    double a = stack.top();
    stack.pop();
    double b = stack.top();
    stack.pop();
    return a * b;
}

int Times::priority() {
    return 1;
}