#include "MyDLLLoader.h"

MyDLLLoader::MyDLLLoader(const std::string& dllPath) {
    hDLL = LoadLibrary(dllPath.c_str());
    if (!hDLL) {
        throw std::runtime_error("Failed to load DLL: " + dllPath);
    }

    funcPointer = reinterpret_cast<FuncType>(GetProcAddress(hDLL, "func"));
    if (!funcPointer) {
        FreeLibrary(hDLL);
        throw std::runtime_error("Failed to get function address in DLL: " + dllPath);
    }
}

MyDLLLoader::~MyDLLLoader() {
    if (hDLL) {
        FreeLibrary(hDLL);
    }
}

double MyDLLLoader::CallFunction(double arg1, double arg2) {
    if (funcPointer) {
        return funcPointer(arg1, arg2);
    }
    else {
        throw std::runtime_error("Function not available.");
    }
}