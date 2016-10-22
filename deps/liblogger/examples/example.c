#include "logger/logger.h"


#define _str(x)  #x
#define str(x)  _str(x)

#define TRACE(_Msg)  "In file: " str(__FILE__) ", line: " str(__LINE__) "\n=> " _Msg

/*
 *
 */
int main(void) {
    /*
     * Stream Logger - Stdout
     */
    logger_t *stream_logger_stdout = stream_logger_new("StreamLogger - Stdout", LOG_LEVEL_DEBUG, stdout);
    log_debug   (stream_logger_stdout, TRACE("%s\n\n"), "Debug log");
    log_notice  (stream_logger_stdout, TRACE("%s\n\n"), "Notice log");
    log_info    (stream_logger_stdout, TRACE("%s\n\n"), "Info log");
    log_warning (stream_logger_stdout, TRACE("%s\n\n"), "Warning log");
    log_error   (stream_logger_stdout, TRACE("%s\n\n"), "Error log");
    log_fatal   (stream_logger_stdout, TRACE("%s\n\n"), "Fatal log");
    logger_delete(&stream_logger_stdout);

    /*
     * Stream Logger - Stderr
     */
    logger_t *stream_logger_stderr = stream_logger_new("StreamLogger - Stderr", LOG_LEVEL_DEBUG, stderr);
    log_debug   (stream_logger_stderr, TRACE("%s\n\n"), "Debug log");
    log_notice  (stream_logger_stderr, TRACE("%s\n\n"), "Notice log");
    log_info    (stream_logger_stderr, TRACE("%s\n\n"), "Info log");
    log_warning (stream_logger_stderr, TRACE("%s\n\n"), "Warning log");
    log_error   (stream_logger_stderr, TRACE("%s\n\n"), "Error log");
    log_fatal   (stream_logger_stderr, TRACE("%s\n\n"), "Fatal log");
    logger_delete(&stream_logger_stderr);

    /*
     * File Logger
     */
    logger_t *file_logger_none_policy = file_logger_new("FileLogger", LOG_LEVEL_DEBUG, "/tmp/file-logger.log", LOG_MODE_WRITE);
    log_debug   (file_logger_none_policy, TRACE("%s\n\n"), "Debug log");
    log_notice  (file_logger_none_policy, TRACE("%s\n\n"), "Notice log");
    log_info    (file_logger_none_policy, TRACE("%s\n\n"), "Info log");
    log_warning (file_logger_none_policy, TRACE("%s\n\n"), "Warning log");
    log_error   (file_logger_none_policy, TRACE("%s\n\n"), "Error log");
    log_fatal   (file_logger_none_policy, TRACE("%s\n\n"), "Fatal log");
    logger_delete(&file_logger_none_policy);

    /*
     * Rotating File Logger
     */
    logger_t *file_logger_rotate_policy = rotating_logger_new("RotatingFileLogger", LOG_LEVEL_DEBUG, "/tmp/rotating-file-logger.log", 15);
    log_debug   (file_logger_rotate_policy, TRACE("%s\n\n"), "Debug log");
    log_notice  (file_logger_rotate_policy, TRACE("%s\n\n"), "Notice log");
    log_info    (file_logger_rotate_policy, TRACE("%s\n\n"), "Info log");
    log_warning (file_logger_rotate_policy, TRACE("%s\n\n"), "Warning log");
    log_error   (file_logger_rotate_policy, TRACE("%s\n\n"), "Error log");
    log_fatal   (file_logger_rotate_policy, TRACE("%s\n\n"), "Fatal log");
    logger_delete(&file_logger_rotate_policy);

    /*
     * Buffer File Logger
     */
    logger_t *file_logger_buffer_policy = buffer_logger_new("BufferFileLogger", LOG_LEVEL_DEBUG, "/tmp/buffer-file-logger.log", LOG_MODE_WRITE, 15);
    log_debug   (file_logger_buffer_policy, TRACE("%s\n\n"), "Debug log");
    log_notice  (file_logger_buffer_policy, TRACE("%s\n\n"), "Notice log");
    log_info    (file_logger_buffer_policy, TRACE("%s\n\n"), "Info log");
    log_warning (file_logger_buffer_policy, TRACE("%s\n\n"), "Warning log");
    log_error   (file_logger_buffer_policy, TRACE("%s\n\n"), "Error log");
    log_fatal   (file_logger_buffer_policy, TRACE("%s\n\n"), "Fatal log");
    logger_delete(&file_logger_buffer_policy);

    return 0;
}
