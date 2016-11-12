liblogger
=========

A logging library written in ANSI C.

## Installation

#### Cloning and CMaking

liblogger uses cmake as its default building system, so **cmake version 3.0 or higher** 
is the only requirement if you don't want to build the library by yourself. 

liblogger comes with its dependencies included, so you just have to:
```bash
git clone https://github.com/daddinuz/liblogger.git && cd ./liblogger/build
cmake .. 
make
```
this will build the liblogger static library under lib/ folder and the examples under the bin/ folder.

By default liblogger is built with colors support.
If you want to turn off this feature just run cmake as below:
```bash
cmake -DDISABLE_COLORS=true ..
```
this will just set the definition: `NCOLORS=1` at compile time.

When you're ready to ship the library in a production environment run 
cmake with the following definitions:
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
```
this will also set the definition: `NDEBUG=1` at compile time turning off 
the logs with level LOG_LEVEL_DEBUG.

#### Using clib package manager

If you are using [clib](https://github.com/clibs/clib):
```bash
$ clib install daddinuz/liblogger
```
unlikely using clib means that no building system is provided and you will 
have to compile liblogger by yourself. 

## Description

Currently liblogger supports 4 types of loggers:

- stream logger (prints to an out stream such as stderr or stdout) 
- file logger (prints to a file without applying any policy)
- rotating logger (prints to a file and rotate every n bytes written)
- buffer logger (prints to a file and overwrites it every n bytes written)

liblogger **will not truncate your logs** this means that if the specified numbers of 
bytes for applying a policy are reached while performing a log function, the policy 
will be applied the next time a log function is called, preserving the integrity of your logs. 

By default, if a stream logger is set to stdout it will use colors;
in order to disable colors define at compile time the macro **NCOLOR**=1

## Log levels

- **LOG_LEVEL_DEBUG**: 0
- **LOG_LEVEL_NOTICE**: 1
- **LOG_LEVEL_INFO**: 2
- **LOG_LEVEL_WARNING**: 3
- **LOG_LEVEL_ERROR**: 4
- **LOG_LEVEL_FATAL**: 5

Setting **NDEBUG**=1 will not log debug messages no matter what the log level is.

## Example

```C
#include "logger.h"

int main(void) {
    logger_t *logger = stream_logger_new("ExampleStreamLogger", LOG_LEVEL_DEBUG, stdout);
    
    log_debug   (logger, "Debug log\n\n");
    log_notice  (logger, "Notice log\n\n");
    log_info    (logger, "Info log\n\n");
    log_warning (logger, "Warning log\n\n");
    log_error   (logger, "Error log\n\n");
    log_fatal   (logger, "Fatal log\n\n");
    
    logger_delete(&logger);
    return 0;
}
```

this will output on stdout:

```bash
DEBUG   [Wed Nov  9 19:58:17 2016 UTC] -- (ExampleStreamLogger): Debug log

NOTICE  [Wed Nov  9 19:58:17 2016 UTC] -- (ExampleStreamLogger): Notice log

INFO    [Wed Nov  9 19:58:17 2016 UTC] -- (ExampleStreamLogger): Info log

WARNING [Wed Nov  9 19:58:17 2016 UTC] -- (ExampleStreamLogger): Warning log

ERROR   [Wed Nov  9 19:58:17 2016 UTC] -- (ExampleStreamLogger): Error log

FATAL   [Wed Nov  9 19:58:17 2016 UTC] -- (ExampleStreamLogger): Fatal log
```

## License 

MIT
