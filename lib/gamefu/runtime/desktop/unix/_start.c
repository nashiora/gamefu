#include <gamefu/gamefu.h>

// undefine the macro intended for the developer entry point, we implement the real one here.
#undef main

int main(int argc, char** argv) {
    gfu_log(GFU_VERBOSE, "Starting GameFU Native Executable on a Unix system.");
    _gfu_main();
    return 0;
}
