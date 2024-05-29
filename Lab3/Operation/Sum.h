#include "Operation.h"
#include <string>

using namespace std;

class Sum: public Operation {
    public:
    void operate(std::stack<double>& stack) override;
    int priority() override;
    string to_string() override;
 };