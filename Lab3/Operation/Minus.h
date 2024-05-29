#include "Operation.h"
#include <string>

class Minus: public Operation {
    public:
    void operate(std::stack<double>& stack) override;
    int priority() override;
    string to_string() override;
 };