#include "Sum.h"
#include <string>
#include <stack>

using namespace std;

void Sum::operate(stack<double>& stack) {
    double result = 0;
    while (!stack.empty()) {
        result += stack.top();
        stack.pop();
    }
    stack.push(result);
}

int Sum::priority() {
    return 3;
}

string Sum::to_string() {
    return "sum";
}
