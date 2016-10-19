#include "logger/logger.h"


#define _str(x)  #x
#define str(x)  _str(x)

#define TRACE  "In file: " str(__FILE__) ", line: " str(__LINE__) "\n=> "

/*
 *
 */
int main(void) {
    logger_t *logger = logger_new("TEST", LOG_LEVEL_DEBUG, NULL);

    log_debug   (logger, TRACE "%s\n\n", "Debug log");
    log_notice  (logger, TRACE "%s\n\n", "Notice log");
    log_info    (logger, TRACE "%s\n\n", "Info log");
    log_warning (logger, TRACE "%s\n\n", "Warning log");
    log_error   (logger, TRACE "%s\n\n", "Error log");
    log_fatal   (logger, TRACE "%s\n\n", "Fatal log");

    logger_delete(&logger);
    return 0;
}
