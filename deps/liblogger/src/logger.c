/*
 *  C Source File
 *
 *  Author: Davide Di Carlo
 *  Date:   Octorber 19, 2016
 *  email:  daddinuz@gmail.com
 */

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#ifdef _WIN32
#include "ansicolor-w32/ansicolor-w32.h"
#endif

#include "logger/logger.h"


/*
 * Colors
 */
#define COLOR_NORMAL    (NCOLOR != 0) ? "" : "\x1B[00m"
#define COLOR_RED       (NCOLOR != 0) ? "" : "\x1B[31m"
#define COLOR_GREEN     (NCOLOR != 0) ? "" : "\x1B[32m"
#define COLOR_YELLOW    (NCOLOR != 0) ? "" : "\x1B[33m"
#define COLOR_BLUE      (NCOLOR != 0) ? "" : "\x1B[34m"
#define COLOR_MAGENTA   (NCOLOR != 0) ? "" : "\x1B[35m"

/*
 * Helper functions
 */
const char * _level2color(log_level_t level) {
    switch(level) {
        case LOG_LEVEL_DEBUG:
            return COLOR_BLUE;
        case LOG_LEVEL_NOTICE:
            return COLOR_NORMAL;
        case LOG_LEVEL_INFO:
            return COLOR_GREEN;
        case LOG_LEVEL_WARNING:
            return COLOR_YELLOW;
        case LOG_LEVEL_ERROR:
            return COLOR_RED;
        case LOG_LEVEL_FATAL:
            return COLOR_MAGENTA;
        default:
            abort();
    }
}

const char * _level2string(log_level_t level) {
    switch(level) {
        case LOG_LEVEL_DEBUG:
            return "DEBUG";
        case LOG_LEVEL_NOTICE:
            return "NOTICE";
        case LOG_LEVEL_INFO:
            return "INFO";
        case LOG_LEVEL_WARNING:
            return "WARNING";
        case LOG_LEVEL_ERROR:
            return "ERROR";
        case LOG_LEVEL_FATAL:
            return "FATAL";
        default:
            abort();
    }
}

char *_string_emplace(const char *data) {
    size_t length = strlen(data) + 1;
    char *str = calloc(length, sizeof(char));
    return strcpy(str, (char *) data);
}

/*
 * logger_t definition
 */
struct logger_t {
    FILE *_stream;
    char *_identifier;
    log_level_t _level;
};

logger_t * logger_new(const char *identifier, log_level_t level, FILE *stream) {
    logger_t *logger = malloc(sizeof(logger_t));
    logger->_stream = (NULL != stream) ? stream : stdout;
    logger->_identifier = (NULL != identifier) ? _string_emplace(identifier) : "unknown";
    logger->_level = (LOG_LEVEL_DEBUG == level && NDEBUG != 0) ? LOG_LEVEL_NOTICE : level;
    return logger;
}

void logger_delete(logger_t **logger) {
    if (NULL != logger) {
        free((*logger)->_identifier);
        free(*logger);
        *logger = NULL;
    }
}

/*
 * Real logging function
 */
void _log(logger_t *logger, log_level_t level, const char *format, va_list args) {
    assert(NULL != logger);

    if (level >= logger->_level) {
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = gmtime(&rawtime);
        char *timestring = asctime(timeinfo);
        size_t len = strlen(timestring);
        timestring[len - 1] = '\0';

        fprintf(logger->_stream, "%s%-7s [%s UTC]%s -- (%s): ", _level2color(level), _level2string(level), timestring, COLOR_NORMAL, logger->_identifier);
        vfprintf(logger->_stream, format, args);
        fflush(logger->_stream);
    }
}

/*
 * Proxies logging functions
 */
#define DEFINE_LOGGER(_Identifier, _Level)                              \
    void log_##_Identifier(logger_t *logger, const char *format, ...) { \
        va_list args;                                                   \
        va_start(args, format);                                         \
        _log(logger, LOG_LEVEL_##_Level, format, args);                 \
        va_end(args);                                                   \
    }

DEFINE_LOGGER(debug, DEBUG);
DEFINE_LOGGER(notice, NOTICE);
DEFINE_LOGGER(info, INFO);
DEFINE_LOGGER(warning, WARNING);
DEFINE_LOGGER(error, ERROR);
DEFINE_LOGGER(fatal, FATAL);

#undef DEFINE_LOGGER
