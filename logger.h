#pragma once
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>  // FILE, stdin, stdout, stderr, fprintf, printf, vfprintf, vprintf
#include <stdlib.h> // abort
#include <stdarg.h> // va_list, va_start, va_arg, va_end

#include "macro.h"      // MACRO, ENDM
#include "position.h"   // Position, new_position

typedef enum LogLevel {
    LOG_PANIC,          // always abort after printing panic message
    LOG_ASSERT,         // print assert message and abort only if condition is met
    LOG_ERROR,          // print error message and abort if COLLECT_ERRORS or COLLECT_LOGGER not defined
    LOG_DEPRACTED,      // always abort after printing depraction message
    LOG_UNSUPPORTED,    // always abort after printing unsupported message
    LOG_UNIMPLEMENTED,  // always abort after printing unimplemented message
    LOG_DBG,            // print debug message only if NODEBUG not defined
    LOG_TODO,           // always abort after printing todo message
    LOG_WARNING,        // print warning message and abort only if ABORT_WARNING is defined or
                        // collect warning message if COLLECT_WARNING or COLLECT_LOGGER is defined
    LOG_INFO,           // print info message and abort only if ABORT_INFO is defined or
                        // collect info message if COLLECT_INFO or COLLECT_LOGGER is defined
    LOG_NONE,           // print default logging message or collect message if COLLECT_LOGGER is defined
} LogLevel;

#ifndef COLLECT_PATH
#define COLLECT_PATH "tmp.txt"
#endif // COLLECT_PATH

#define LOGGER(level, fmt, ...) (__logger_print(level, fmt __VA_OPT__(,) __VA_ARGS__))

#define PANIC(fmt, ...)                                         \
MACRO                                                           \
    LOGGER(LOG_PANIC, fmt __VA_OPT__(,) __VA_ARGS__);           \
    abort();                                                    \
ENDM

#define ASSERT(cond, fmt, ...)                                  \
MACRO                                                           \
    if (cond) {                                                 \
        LOGGER(LOG_ASSERT, fmt __VA_OPT__(,) __VA_ARGS__);      \
        abort();                                                \
    }                                                           \
ENDM

#if defined(COLLECT_ERRORS) || defined(COLLECT_LOGGER)
#ifndef COLLECT_PATH
#error "COLLECT_PATH not defiend!"
#endif // COLLECT_PATH
#define ERROR(fmt, ...)                                         \
MACRO                                                           \
    LoggerInfo info = get_logger_info();                        \
    LoggerInfo logging_info = info;                             \
    logging_info.fd = fopen(COLLECT_PATH, "w");                 \
    set_logger_info(logging_info);                              \
    LOGGER(LOG_ERROR, fmt, __VA_OPT__(,) __VA_ARGS__);          \
    fclose(logging_info.fd);                                    \
    set_logger_info(info);                                      \
ENDM
#else // defined(COLLECT_ERRORS) || defined(COLLECT_LOGGER)
#define ERROR(fmt, ...)                                         \
MACRO                                                           \
    LOGGER(LOG_ERROR, fmt __VA_OPT__(,) __VA_ARGS__);           \
    abort();                                                    \
ENDM
#endif // defiend(COLLECT_ERRORS) || defined(COLLECT_LOGGER)

#define DEPRACTED(fmt, ...)                                     \
MACRO                                                           \
    LOGGER(LOG_DEPRACTED, fmt __VA_OPT__(,) __VA_ARGS__);       \
    abort();                                                    \
ENDM

#define UNSUPPORTED(fmt, ...)                                   \
MACRO                                                           \
    LOGGER(LOG_UNSUPPORTED, fmt __VA_OPT__(,) __VA_ARGS__);     \
    abort();                                                    \
ENDM

#define UNIMPLEMENTED(fmt, ...)                                 \
MACRO                                                           \
    LOGGER(LOG_UNIMPLEMENTED, fmt __VA_OPT__(,) __VA_ARGS__);   \
    abort();                                                    \
ENDM

#ifdef NODEBUG
#define LOG_DBG(...)
#else // NODEBUG
#define LOG_DBG(fmt, ...) (LOGGER(LOG_DBG, fmt __VA_OPT__(,) __VA_ARGS__))
#endif // NODEBUG

#define TODO(fmt, ...)                                          \
MACRO                                                           \
    LOGGER(LOG_TODO, fmt __VA_OPT__(,) __VA_ARGS__);            \
    abort();                                                    \
ENDM

#if defined(COLLECT_WARNINGS) || defined(COLLECT_LOGGER)
#ifndef COLLECT_PATH
#error "COLLECT_PATH not defined!"
#endif // COLLECT_PATH
#define WARNING(fmt, ...)                                       \
MACRO                                                           \
    LoggerInfo info = get_logger_info();                        \
    LoggerInfo logging_info = info;                             \
    logging_info.fd = fopen(COLLECT_PATH, "w");                 \
    set_logger_info(logging_info);                              \
    LOGGER(LOG_WARNING, fmt, __VA_OPT__(,) __VA_ARGS__);        \
    fclose(logging_info.fd);                                    \
    set_logger_info(info);                                      \
ENDM
#else // defined(COLLECT_WARNINGS) || defined(COLLECT_LOGGER)
#define WARNING(fmt, ...)                                       \
MACRO                                                           \
    LOGGER(LOG_WARNING, fmt __VA_OPT__(,) __VA_ARGS__);         \
    abort();                                                    \
ENDM
#endif // defined(COLLECT_WARNINGS) || defiend(COLLECT_LOGGER)

#if defiend(COLLECT_INFOS) || defined(COLLECT_LOGGER)
#ifndef COLLECT_PATH
#error "COLLECT_PATH not defined!"
#endif // COLLECT_PATH
#define INFO(fmt, ...)                                          \
MACRO                                                           \
    LoggerInfo info = get_logger_info();                        \
    LoggerInfo logging_info = info;                             \
    logging_info.fd = fopen(COLLECT_PATH, "w");                 \
    set_logger_info(logging_info);                              \
    LOGGER(LOG_INFO, fmt, __VA_OPT__(,) __VA_ARGS__);           \
    fclose(logging_info.fd);                                    \
    set_logger_info(info);                                      \
ENDM
#else // defined(COLLECT_INFOS) || defined(COLLECT_LOGGER)
#define INFO(fmt, ...)                                          \
MACRO                                                           \
    LOGGER(LOG_INFO, fmt __VA_OPT__(,) __VA_ARGS__);            \
    abrot();                                                    \
ENDM
#endif

typedef struct LoggerInfo {
    FILE     *fd;
    LogLevel level;
    char     *path;
    char     *text;
    char     *text_end;
    Position position;
} LoggerInfo;

static LoggerInfo __logger_info = (LoggerInfo){
    .fd       = stderr,
    .level    = LOG_NONE,
    .path     = NULL,
    .text     = NULL,
    .text_end = NULL,
    .position = new_position(NULL, NULL, NULL, 0),
};

LoggerInfo get_logger_info(void);
void set_logget_info(LoggerInfo info);
void __logger_print(LogLevel level, char *fmt, ...);

#ifndef NO_LOGGER_IMPLEMENTATION

LoggerInfo get_logger_info(void) {
    return __logger_info;
}

void set_logger_info(LoggerInfo info) {
    __logger_info = info;
}

static void __diag_print(void) {
    if (__logger_info.position.line && __logger_info.position.begin && __logger_info.position.offset) {
        size_t column = ((size_t)__logger_info.position.begin) - ((size_t)__logger_info.position.offset) + 1;
        fprintf(__logger_info.fd, ":%zu:%zu", (size_t)__logger_info.position.line, column);
    }
    if (__logger_info.path) {
        fprintf(__logger_info.fd, ":%s", __logger_info.path);
    }
}

void __logger_print(LogLevel level, char *fmt, ...) {
    switch (level) {
    case LOG_PANIC:         fprintf(__logger_info.fd, "[Panic");         break;
    case LOG_ASSERT:        fprintf(__logger_info.fd, "[Assert");        break;
    case LOG_ERROR:         fprintf(__logger_info.fd, "[Error");         break;
    case LOG_DEPRACTED:     fprintf(__logger_info.fd, "[Depracted");     break;
    case LOG_UNSUPPORTED:   fprintf(__logger_info.fd, "[Unsupported");   break;
    case LOG_UNIMPLEMENTED: fprintf(__logger_info.fd, "[Unimplemented"); break;
    case LOG_DBG:           fprintf(__logger_info.fd, "[Debug");         break;
    case LOG_TODO:          fprintf(__logger_info.fd, "[Todo");          break;
    case LOG_WARNING:       fprintf(__logger_info.fd, "[Warning");       break;
    case LOG_INFO:          fprintf(__logger_info.fd, "[Info");          break;
    default:                fprintf(__logger_info.fd, "[Logger");        break;
    }
    __diag_print();
    fprintf(__logger_info.fd, "] ");
    va_list args;
    va_start(args, fmt);
    vfprintf(__logger_info.fd, fmt, args);
    va_end(args);
}

#else // NO_LOGGER_IMPLEMENTATION
#endif // __LOGGER_H__
