/*
 *  C Header File
 *
 *  Author: Davide Di Carlo
 *  Date:   Octorber 19, 2016
 *  email:  daddinuz@gmail.com
 */

#include <stdio.h>


#ifndef __LOGGER_H__
#define __LOGGER_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NDEBUG
#define NDEBUG 0
#endif

#ifndef NCOLOR
#define NCOLOR 0
#endif

/*
 * logger_level_t declaration
 */
typedef enum log_level_t {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_NOTICE,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL,
} log_level_t;

/*
 * logger_t declaration
 */
typedef struct logger_t logger_t;

extern logger_t * logger_new(const char *identifier, log_level_t level, FILE *stream);
extern void logger_delete(logger_t **logger);

/*
 * log function declaration
 */
extern void log_debug   (logger_t *logger, const char *format, ...);
extern void log_notice  (logger_t *logger, const char *format, ...);
extern void log_info    (logger_t *logger, const char *format, ...);
extern void log_warning (logger_t *logger, const char *format, ...);
extern void log_error   (logger_t *logger, const char *format, ...);
extern void log_fatal   (logger_t *logger, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* __LOGGER_H__ */
