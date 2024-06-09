#include "Times.h"
#include <string>
#include <stack>

using namespace std;

void Times::operate(stack<double>& stack) {
    double a = stack.top();
    stack.pop();
    double b = stack.top();
    stack.pop();
    stack.push(a * b);
}

int Times::priority() {
    return 1;
}

string Times::to_string() {
    return "*";
}
