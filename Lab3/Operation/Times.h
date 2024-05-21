#include "Operation.h"

class Times: public Operation {
    public:
    double operate(std::stack<double>& stack) override;
    int priority() override;
 };