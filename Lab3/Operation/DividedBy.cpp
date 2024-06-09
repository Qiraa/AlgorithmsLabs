#include "DividedBy.h"
#include <string>
#include <stack>

using namespace std;

void DividedBy::operate(stack<double>& stack) {
    double a = stack.top();
    stack.pop();
    double b = stack.top();
    stack.pop();
    if (a == 0) {
        throw "Error: division by zero!";
    }
    stack.push(b / a);
}

int DividedBy::priority() {
    return 1;
}

string DividedBy::to_string() {
    return "/";
}
