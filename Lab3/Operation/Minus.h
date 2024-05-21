#include "Operation.h"

class Minus: public Operation {
    public:
    double operate(std::stack<double>& stack) override;
    int priority() override;
 };