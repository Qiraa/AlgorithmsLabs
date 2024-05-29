#include "Minus.h"
#include <string>
#include <stack>

using namespace std;

void Minus::operate(stack<double>& stack) {
    double a = stack.top();
    stack.pop();
    double b = stack.top();
    stack.pop();
    stack.push(b - a);
}

int Minus::priority() {
    return 0;
}

string Minus::to_string() {
    return "-";
}
