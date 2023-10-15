#pragma once

#include <Windows.h>
#include <stdexcept>
#include <string>

class MyDLLLoader {
public:
    MyDLLLoader(const std::string& dllPath);
    ~MyDLLLoader();

    double CallFunction(double arg1, double arg2 = 0.0);

private:
    HMODULE hDLL;
    typedef double (*FuncType)(double, double);
    FuncType funcPointer;
};