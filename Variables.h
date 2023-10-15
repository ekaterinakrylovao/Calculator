#pragma once

#include <iostream>
#include <map>
#include <string>
#include <algorithm>

#include "Vector.h"
#include "RPN.h"
#include "Token.h"

typedef struct Variables {
    Vector variables;
    std::map<std::string, std::string> variableAndMeaning;

    void initVariables();
    void ReplacementVariables();
    bool isVariable(std::string& token);
    void changeVariablesInExpression(std::string& exp);
} Variables;