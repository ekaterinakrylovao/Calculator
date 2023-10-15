#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>

#include "Vector.h"
#include "Token.h"
#include "Variables.h"
#include "MyDLLLoader.h"

struct RPN {
    std::map<const std::string, const int> operationWeights = { {"(", 0},
                                                               {"+", 1},
                                                               {"-", 1},
                                                               {"*", 2},
                                                               {"/", 2},
                                                               {"^", 3},
                                                               {"_", 4},
                                                               {"sin", 5},
                                                               {"cos", 5} };
    static bool isNumber(std::string& token);
    static bool isVariable(std::string& token, struct Variables var);
    Vector toPostfix(const std::string& expression, Variables& var);
    static std::stack<double> calcRPN(Vector expRPN);
};