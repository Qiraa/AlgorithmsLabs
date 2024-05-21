#include "DividedBy.h"
#include <string>
#include <stack>

using namespace std;

double DividedBy::operate(stack<double>& stack) {
    double a = stack.top();
    stack.pop();
    double b = stack.top();
    stack.pop();
    if (a == 0) {
        throw "Error: division by zero!";
    }
    return b / a;
}

int DividedBy::priority() {
    return 1;
}