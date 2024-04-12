#if !defined(CC)
#    if defined(__layec__)
#        define CC                                           "layec"
#        define NOB_REBUILD_URSELF(binary_path, source_path) "layec", "-o", binary_path, source_path
#    elif defined(__clang__)
#        define CC                                           "clang"
#        define NOB_REBUILD_URSELF(binary_path, source_path) "clang", "-o", binary_path, source_path
#    elif defined(__GNUC__)
#        define CC                                           "gcc"
#        define NOB_REBUILD_URSELF(binary_path, source_path) "gcc", "-o", binary_path, source_path
#    elif defined(_MSC_VER)
#        define CC                                           "cl.exe"
#        define NOB_REBUILD_URSELF(binary_path, source_path) "cl.exe", source_path
#    else
#        define CC                                           "cc"
#        define NOB_REBUILD_URSELF(binary_path, source_path) "cc", "-o", binary_path, source_path
#    endif
#endif

#if !defined(LD)
#    if defined(__layec__)
#        define LD "clang"
#    elif defined(__clang__)
#        define LD "clang"
#    elif defined(__GNUC__)
#        define LD "gcc"
#    elif defined(_MSC_VER)
#        define LD "link"
#    else
#        define LD "ld"
#    endif
#endif

#define NOB_IMPLEMENTATION
#include "nob.h"

typedef enum gamefu_platform {
    PLATFORM_NONE = 0,
    PLATFORM_GAMEFU = 1 << 0,
    PLATFORM_DESKTOP = 1 << 1,
    PLATFORM_UNIX = 1 << 2,
    PLATFORM_WINDOWS = 1 << 3,
} gamefu_platform;

typedef struct build_config {
    gamefu_platform target_platform;
    bool debug;
} build_config;

static bool is_gcc_compatible(const char* exe) {
    return 0 == strcmp(exe, "clang") || 0 == strcmp(exe, "gcc");
}

static void path_get_file_name(const char** path_ref, int* length, bool remove_extension) {
    const char* path = *path_ref;
    *length = (int)strlen(path);

    if (remove_extension) {
        for (int i = *length; i >= 0; i--) {
            if (path[i] == '.') {
                *length = i;
                break;
            }
        }
    }

    for (int i = *length; i >= 0; i--) {
        if (path[i] == '/' || path[i] == '\\') {
            int index = i + 1;
            *length -= index;
            *path_ref += index;
            break;
        }
    }
}

static void cflags(Nob_Cmd* cmd, build_config config) {
    nob_cmd_append(cmd, "-std=c2x");
    nob_cmd_append(cmd, "-pedantic");
    nob_cmd_append(cmd, "-pedantic-errors");
    nob_cmd_append(cmd, "-D__USE_POSIX");
    nob_cmd_append(cmd, "-D_XOPEN_SOURCE=600");
    if (is_gcc_compatible(CC)) {
        nob_cmd_append(cmd, "-fdata-sections");
        nob_cmd_append(cmd, "-ffunction-sections");
        nob_cmd_append(cmd, "-Werror=return-type");
    }

    if (config.debug) {
        if (is_gcc_compatible(CC)) {
            nob_cmd_append(cmd, "-fsanitize=address");
            nob_cmd_append(cmd, "-ggdb");
        }
    } else {
        nob_cmd_append(cmd, "-Os");
    }
}

static void layeflags(Nob_Cmd* cmd, build_config config) {
    if (config.debug) {
    } else {
    }
}

static void ldflags(Nob_Cmd* cmd, build_config config) {
    nob_cmd_append(cmd, "-Lout");

    if (is_gcc_compatible(LD)) {
        nob_cmd_append(cmd, "-Wl,--gc-sections");
        nob_cmd_append(cmd, "-Wl,--as-needed");
    }

    if (config.debug) {
        if (is_gcc_compatible(LD)) {
            nob_cmd_append(cmd, "-fsanitize=address");
        }
    } else {
        nob_cmd_append(cmd, "-Os");
    }
}

static bool rebuild_c(const char** includes, const char* source_file, const char* object_file, build_config config) {
    bool result = true;
    Nob_Cmd cmd = {0};

    Nob_File_Paths dependencies = {0};
    nob_da_append(&dependencies, source_file);

    for (int i = 0; includes[i] != NULL && i < 32; i++) {
        nob_read_entire_dir_recursively(includes[i], &dependencies);
    }

    if (!nob_needs_rebuild(object_file, dependencies.items, dependencies.count)) {
        nob_return_defer(true);
    }

    nob_cmd_append(&cmd, CC);
    cflags(&cmd, config);
    for (int i = 0; includes[i] != NULL && i < 32; i++) {
        nob_cmd_append(&cmd, "-I", includes[i]);
    }
    nob_cmd_append(&cmd, "-o", object_file);
    nob_cmd_append(&cmd, "-c", source_file);

    nob_return_defer(nob_cmd_run_sync(cmd));

defer:;
    nob_da_free(dependencies);
    nob_cmd_free(cmd);
    return result;
}

static bool build_gamefu_system_library(build_config config) {
    bool result = true;

    Nob_Cmd cmd = {0};

    static const char* system_includes[] = {
        "./include/sys",
        "./include/api",
        NULL, // sentinel
    };

    if ((config.target_platform & PLATFORM_DESKTOP) && (config.target_platform & PLATFORM_UNIX)) {
        static const char* system_sources_unix[] = {
            //"./lib/gamefu/sys/desktop/",
            NULL, // sentinel
        };

        Nob_File_Paths object_files = {0};
        for (int i = 0; system_sources_unix[i] != NULL && i < 256; i++) {
            const char* file_name = system_sources_unix[i];
            int file_name_length = 0;
            path_get_file_name(&file_name, &file_name_length, true);
            
            char* object_file = nob_temp_sprintf("./out/o/gfusys_%.*s.o", file_name_length, file_name);
            nob_da_append(&object_files, object_file);

            rebuild_c(system_includes, system_sources_unix[i], object_file, config);
        }

        nob_cmd_append(&cmd, LD);
        ldflags(&cmd, config);
        nob_cmd_append(&cmd, "-o", "gfusys_unix.a");
        for (size_t i = 0; i < object_files.count; i++) {
            nob_cmd_append(&cmd, object_files.items[i]);
        }

        bool cmd_status = nob_cmd_run_sync(cmd);
        nob_da_free(object_files);
        nob_return_defer(cmd_status);
    } else {
        nob_log(NOB_ERROR, "Unsupported target for GameFU system library");
        nob_return_defer(false);
    }

defer:;
    nob_cmd_free(cmd);

    return result;
}

static bool build_gamefu_runtime_library(build_config config) {
    bool result = true;

    Nob_Cmd cmd = {0};

    static const char* runtime_includes[] = {
        "./include/sys",
        "./include/api",
        NULL, // sentinel
    };

    if ((config.target_platform & PLATFORM_DESKTOP) && (config.target_platform & PLATFORM_UNIX)) {
        static const char* runtime_sources_unix[] = {
            "./include/sys",
            "./include/api",
            NULL, // sentinel
        };
    } else {
        nob_log(NOB_ERROR, "Unsupported target for GameFU runtime library");
        nob_return_defer(false);
    }

defer:;
    nob_cmd_free(cmd);

    return result;
}

static bool build_gamefu_emulator(build_config config) {
    bool result = true;

defer:;
    return result;
}

static bool build_pong(build_config config) {
    bool result = true;

    Nob_Cmd cmd = {0};

    static const char* pong_includes[] = {
        "./include/sys",
        "./include/api",
        NULL, // sentinel
    };

    build_gamefu_system_library(config);
    build_gamefu_runtime_library(config);

    rebuild_c(pong_includes, "./examples/pong.c", "./out/pong.o", config);

    nob_cmd_append(&cmd, LD);
    ldflags(&cmd, config);
    nob_cmd_append(&cmd, "-lgfusys_unix");
    nob_cmd_append(&cmd, "-lgfurun_unix");
    nob_cmd_append(&cmd, "-o", "pong");
    nob_cmd_append(&cmd, "./out/pong.o");
    nob_return_defer(nob_cmd_run_sync(cmd));

defer:;
    nob_cmd_free(cmd);

    return result;
}

int main(int argc, char** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);

    int result = 0;

    build_config config = {
        .debug = true,
        .target_platform = PLATFORM_DESKTOP | PLATFORM_UNIX,
    };

    if (!nob_mkdir_if_not_exists("./out")) {
        nob_return_defer(false);
    }

    if (!nob_mkdir_if_not_exists("./out/o")) {
        nob_return_defer(false);
    }

    if (!build_pong(config)) {
        nob_return_defer(1);
    }

defer:;
    return result;
}
