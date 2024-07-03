#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <iostream>

template<typename... Args>
void terminateMessage(int error_code, const char* format, Args... args) {
    fprintf(stderr, "Error: ");
    fprintf(stderr, format, args...);
    exit(error_code);
}

void terminateMessage(int error_code, const char* message);

#endif//__UTILITIES_H