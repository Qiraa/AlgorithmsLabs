#include "Operation.h"

class Plus: public Operation {
    public:
    double operate(std::stack<double>& stack) override;
    int priority() override;
 };