#include "Operation.h"

class Sum: public Operation {
    public:
    double operate(std::stack<double>& stack) override;
    int priority() override;
 };