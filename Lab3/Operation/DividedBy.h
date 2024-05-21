#include "Operation.h"

class DividedBy: public Operation {
    public:
    double operate(std::stack<double>& stack) override;
    int priority() override;
 };