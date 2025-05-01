#pragma once
#include <string>
using namespace std;

class Logger {
public:
    static void info(const string& msg);
    static void error(const string& msg);
};