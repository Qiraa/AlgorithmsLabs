#include "Operation/Operation.h"
#include "Token.h"
#include <string>
#include <map>
#include <vector>

using namespace std;

class Calculator {
    map<string, Operation*> operations;
    vector<Operation*> to_rpn(vector<Token*> tokens);
    public:
    Calculator();
    void registrate(string name, Operation* operation);
    double evaluate(string expression);
};