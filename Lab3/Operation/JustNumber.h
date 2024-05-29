#include "Operation.h"
#include <string>

using namespace std;

class JustNumber: public Operation {
    double value;
    public:
    JustNumber(double value): value(value) { };
    void operate(std::stack<double>& stack) override;
    int priority() override;
    string to_string() override;
 };