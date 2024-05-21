#include "Sum.h"
#include <string>
#include <stack>

using namespace std;

double Sum::operate(stack<double>& stack) {
    double result = 0;
    while (!stack.empty()) {
        result += stack.top();
        stack.pop();
    }
    return result;
}

int Sum::priority() {
    return 3;
}