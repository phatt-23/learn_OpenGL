#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <iostream>
#include <string>
#include <format>
#include <exception>

template<typename... Args>
void throwMessage(const char* format, Args... args) {
    char strbuff[512] = {0};
    sprintf(strbuff, "[ERR] ");
    sprintf(strbuff, format, args...);
    throw strbuff;
}

void throwMessage(const char* message);

#endif//__UTILITIES_H