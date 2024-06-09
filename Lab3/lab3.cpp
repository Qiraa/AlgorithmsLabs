#include "Calculator.h"
#include "Operation/Sum.h"
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

int main() {
    stack<double> stack;
    string input;
    cout << "Enter the evaluation: ";
    getline(cin, input);
    Calculator calculator;
    calculator.registrate("sum", new Sum());
    cout << "Result: " << calculator.evaluate(input) << endl;

    return 0;
}