#include "utils.h"

void throwMessage(const char* message) {
    char strbuff[512] = {0};
    snprintf(strbuff, 512, "[ERR] %s", message);
    throw strbuff;
}