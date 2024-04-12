#include <stdio.h>

#include <gamefu/gamefu.h>

void gfu_log(gfu_log_level level, const char* format) {
    fprintf(stderr, "test log: %s\n", format);
}
