#include "RPN.h"

bool RPN::isVariable(std::string& token, Variables var) {
    for (int i = 0; i < var.variables.index; ++i) {
        if (token == var.variables.arrString[i]) {
            return true;
        }
    }
    return false;
}

bool RPN::isNumber(std::string& token) {
    for (auto& i : token) {
        if ((i < '0' || i > '9') && i != '.') {
            return false;
        }
    }
    return true;
}

Vector RPN::toPostfix(const std::string& expression, Variables& var) {
    int index = 0, sizeExp = expression.size();
    bool may_unary = true;
    std::string token;
    Vector result;
    std::stack<std::string> stackOperations;
    while (index < sizeExp) {
        token = "";
        token = Token::readToken(expression, index);
        if (isVariable(token, var)) {
            result.push_back(var.variableAndMeaning[token]);
            may_unary = false;
        }
        else if (isNumber(token)) {
            result.push_back(token);
            may_unary = false;
        }
        else if (token == "(") {
            stackOperations.push("(");
            may_unary = true;
        }
        else if (token == ")") {
            while (stackOperations.top() != "(") {
                result.push_back(stackOperations.top());
                stackOperations.pop();
                if (stackOperations.empty()) {
                    std::cout << "( missed\n";
                    exit(1);
                }
            }
            may_unary = false;
            stackOperations.pop();
        }
        else {
            if (may_unary && token == "-") token = "_";
            while (!stackOperations.empty() && operationWeights[token] <= operationWeights[stackOperations.top()]) {
                result.push_back(stackOperations.top());
                stackOperations.pop();
            }
            may_unary = true;
            stackOperations.push(token);
        }
    }
    while (!stackOperations.empty()) {
        result.push_back(stackOperations.top());
        stackOperations.pop();
    }
    return result;
}

std::stack<double> RPN::calcRPN(Vector expRPN) {
    std::stack<double> result;
    std::set<std::string> operations = { "+", "-", "*", "/", "^" };
    std::set<std::string> functions = { "_", "sin", "cos"};

    for (int x = 0; x < expRPN.index; ++x) {
        if (isNumber(expRPN.arrString[x])) {
            result.push(atof(expRPN.arrString[x].c_str()));
        }
        else if (operations.count(expRPN.arrString[x])) {
            double a, b;
            b = result.top();
            result.pop();
            a = result.top();
            result.pop();
            if (expRPN.arrString[x] == "+") {
                result.push(a + b);
            }
            else if (expRPN.arrString[x] == "-") {
                result.push(a - b);
            }
            else if (expRPN.arrString[x] == "*") {\
                result.push(a * b);
            }
            else if (expRPN.arrString[x] == "/") {
                result.push(a / b);
            }
            else if (expRPN.arrString[x] == "^") {
                MyDLLLoader Deg("plugins\\DLL_deg.dll");
                result.push(Deg.CallFunction(a, b));

            }
        }
        else if (functions.count(expRPN.arrString[x])) {
            double a;
            a = result.top();
            result.pop();
            if (expRPN.arrString[x] == "_") {
                result.push(-a);
            }
            else if (expRPN.arrString[x] == "sin") {
                MyDLLLoader Sin("plugins\\DLL_sin.dll");
                result.push(Sin.CallFunction(a));
            }
            else if (expRPN.arrString[x] == "cos") {
                MyDLLLoader Cos("plugins\\DLL_cos.dll");
                result.push(Cos.CallFunction(a));
            }
        }
    }
    return result;
}