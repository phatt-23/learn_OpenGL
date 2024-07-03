#include "utils.h"

void terminateMessage(int error_code, const char* message) {
    fprintf(stderr, "Error: %s", message);
    exit(error_code);
}