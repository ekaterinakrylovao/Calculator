#include "Vector.h"
#include "RPN.h"
#include "Variables.h"

int main(int argc, char* argv[]) {

    Variables var;
    RPN rpn;
    std::string exp;

    while (true) {

        var.initVariables();

        var.ReplacementVariables();

        bool expIsArg = false;
        if (exp.empty()) {
            std::getline(std::cin, exp);
            if (exp == "exit()") {
                std::cout << "Finish\n";
                return 0;
            }
        }
        else {
            expIsArg = true;
        }

        if (!exp.empty()) {
            try {
                var.changeVariablesInExpression(exp);
                auto g = rpn.toPostfix(exp, var);
                auto p = RPN::calcRPN(g);
                std::cout << "--> " << p.top();
                std::cout << "\n";
            }
            catch (const std::invalid_argument& error) {
                std::cout << error.what();
            }
        }
        std::cout << "\n";
        exp = "";
        if (expIsArg) {
            break;
        }
    }
}