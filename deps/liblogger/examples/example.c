#include "logger.h"


#define _str(_Message)  #_Message
#define str(_Message)  _str(_Message)

#define TRACE(_Format)  "In file: " str(__FILE__) ", line: " str(__LINE__) "\n=> " _Format

/*
 *
 */
int main(void) {
    /*
     * Stream Logger - Stdout
     */
    logger_t *stream_logger_stdout = stream_logger_new("StreamLogger - Stdout", LOG_LEVEL_DEBUG, stdout);
    log_debug   (stream_logger_stdout, TRACE("Debug log\n\n"));
    log_notice  (stream_logger_stdout, TRACE("Notice log\n\n"));
    log_info    (stream_logger_stdout, TRACE("Info log\n\n"));
    log_warning (stream_logger_stdout, TRACE("Warning log\n\n"));
    log_error   (stream_logger_stdout, TRACE("Error log\n\n"));
    log_fatal   (stream_logger_stdout, TRACE("Fatal log\n\n"));
    logger_delete(&stream_logger_stdout);

    /*
     * Stream Logger - Stderr
     */
    logger_t *stream_logger_stderr = stream_logger_new("StreamLogger - Stderr", LOG_LEVEL_DEBUG, stderr);
    log_debug   (stream_logger_stderr, TRACE("Debug log\n\n"));
    log_notice  (stream_logger_stderr, TRACE("Notice log\n\n"));
    log_info    (stream_logger_stderr, TRACE("Info log\n\n"));
    log_warning (stream_logger_stderr, TRACE("Warning log\n\n"));
    log_error   (stream_logger_stderr, TRACE("Error log\n\n"));
    log_fatal   (stream_logger_stderr, TRACE("Fatal log\n\n"));
    logger_delete(&stream_logger_stderr);

    /*
     * File Logger
     */
    logger_t *file_logger_none_policy = file_logger_new("FileLogger", LOG_LEVEL_DEBUG, "/tmp/file-logger.log", LOG_MODE_WRITE);
    log_debug   (file_logger_none_policy, TRACE("Debug log\n\n"));
    log_notice  (file_logger_none_policy, TRACE("Notice log\n\n"));
    log_info    (file_logger_none_policy, TRACE("Info log\n\n"));
    log_warning (file_logger_none_policy, TRACE("Warning log\n\n"));
    log_error   (file_logger_none_policy, TRACE("Error log\n\n"));
    log_fatal   (file_logger_none_policy, TRACE("Fatal log\n\n"));
    logger_delete(&file_logger_none_policy);

    /*
     * Rotating File Logger
     */
    logger_t *file_logger_rotate_policy = rotating_logger_new("RotatingFileLogger", LOG_LEVEL_DEBUG, "/tmp/rotating-file-logger.log", 15);
    log_debug   (file_logger_rotate_policy, TRACE("Debug log\n\n"));
    log_notice  (file_logger_rotate_policy, TRACE("Notice log\n\n"));
    log_info    (file_logger_rotate_policy, TRACE("Info log\n\n"));
    log_warning (file_logger_rotate_policy, TRACE("Warning log\n\n"));
    log_error   (file_logger_rotate_policy, TRACE("Error log\n\n"));
    log_fatal   (file_logger_rotate_policy, TRACE("Fatal log\n\n"));
    logger_delete(&file_logger_rotate_policy);

    /*
     * Buffer File Logger
     */
    logger_t *file_logger_buffer_policy = buffer_logger_new("BufferFileLogger", LOG_LEVEL_DEBUG, "/tmp/buffer-file-logger.log", LOG_MODE_WRITE, 15);
    log_debug   (file_logger_buffer_policy, TRACE("Debug log\n\n"));
    log_notice  (file_logger_buffer_policy, TRACE("Notice log\n\n"));
    log_info    (file_logger_buffer_policy, TRACE("Info log\n\n"));
    log_warning (file_logger_buffer_policy, TRACE("Warning log\n\n"));
    log_error   (file_logger_buffer_policy, TRACE("Error log\n\n"));
    log_fatal   (file_logger_buffer_policy, TRACE("Fatal log\n\n"));
    logger_delete(&file_logger_buffer_policy);

    return 0;
}
