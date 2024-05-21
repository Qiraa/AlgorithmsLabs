#include "Minus.h"
#include <string>
#include <stack>

using namespace std;

double Minus::operate(stack<double>& stack) {
    double a = stack.top();
    stack.pop();
    double b = stack.top();
    stack.pop();
    return b - a;
}

int Minus::priority() {
    return 0;
}