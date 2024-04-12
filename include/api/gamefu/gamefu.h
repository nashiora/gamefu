// GameFU system API

#ifndef GAMEFU_API_GAMEFU_H
#define GAMEFU_API_GAMEFU_H

#if defined(__GAMEFU__)

// on gamefu, we're compiling without the standard library at all.
// the entry point for the gamefu is _start, but by default
// the runtime implements _start for you.

#    if !defined(__GAMEFU_NO_RUNTIME__)

// forward declare main so that the runtime _start function has
// something to reference.
void main();

#    endif // !defined(__GAMEFU_NO_RUNTIME__)

typedef signed char i8;
typedef short i16;
typedef int i32;
typedef long i64;

typedef float f32;
typedef double f64;

#elif defined(__unix__)

#    define main _gfu_main

void _gfu_main();

typedef signed char i8;
typedef short i16;
typedef int i32;
typedef long i64;

typedef float f32;
typedef double f64;

#elif defined(_MSC_VER)

#    define main _gfu_main

void _gfu_main();

typedef signed char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

typedef float f32;
typedef double f64;

#else
#    error "The current platform is not a supported GameFU compilation target"
#endif

typedef enum gfu_log_level {
    GFU_VERBOSE = 0,
    GFU_DEBUG = 1,
    GFU_INFO = 2,
    GFU_WARN = 3,
    GFU_ERROR = 4,
    GFU_FATAL = 5,
} gfu_log_level;

/// @brief The type of a logger function.
/// Whenever GameFU logs are generated, they're sent off to various
/// loggers for more specific processing;
/// at least so long as certain preconditions hold.
/// Both the loggers defined by the default GameFU runtime library
/// as well as user-defined custom loggers are expected to adhere to this
/// function signature.
typedef void (*gfu_logger_callback)(gfu_log_level level, const char* log_message);

/// @brief Logs a message to all of the globally configured loggers,
/// if preconditions allow it.
/// @param level What level this log is.
/// This is the most common piece of information used in the precondition
/// checks when filtering out logs.
/// If you're certain a call to this function is executing but you aren't
/// seeing the output where you'd expect, check the configured log level.
/// It may be that the level of log you're sending is being suppressed.
/// @param format The format of the log message.
/// When no format arguments are specified, the format will be identical
/// to the resulting message text unless a log handler explicitly alters it.
/// When format arguments are specified, this format string specifies how
/// they should be formatted in the final log message.
/// See `gfu_format`, the formatter used to format log messages.
/// @see gfu_format
void gfu_log(gfu_log_level level, const char* format);

// TODO(local): I have a feeling that the GameFU API should provide its own
// strings, allocator primitives, etc.
// In which case functions like `gfu_format` should return `gfu_string` instead, most likely.
// Also of note, actually, is that if Laye is the primary supported language (along with C, of course)
// then the values returned here need to be trivially usable in Laye as well.

/// @brief
/// @param format
/// @return The formatted output, as a NUL terminated character string.
char* gfu_format(const char* format);

#endif // !GAMEFU_API_GAMEFU_H
