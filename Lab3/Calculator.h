#include "Operation/Operation.h"
#include <string>
#include <map>

using namespace std;

class Calculator {
    map<string, Operation*> operations;
    string to_rpn(string input);
    public:
    Calculator();
    void registrate(string name, Operation* operation);
    double evaluate(std::string expression);
};