/*
 * logger.h
 *
 *
 * logging support
 *
 *
 * Copyright (C) 2013-2016  Bryant Moscon - bmoscon@gmail.com
 *
 * Please see the LICENSE file for the terms and conditions 
 * associated with this software.
 *
 */

#ifndef __LOGGER__
#define __LOGGER__

#include <stdarg.h>


typedef enum logger_level {
    LOGGER_LEVEL_VERBOSE = 0,
    LOGGER_LEVEL_DEBUG,
    LOGGER_LEVEL_WARN,
    LOGGER_LEVEL_ERROR,
    LOGGER_LEVEL_OFF
} logger_level;


#define _STR(x) __STR(x)
#define __STR(x) #x

#define log_verbose(...) \
  logger_log(LOGGER_LEVEL_VERBOSE, __FILE__ ":" _STR(__LINE__), __VA_ARGS__)

#define log_debug(...) \
  logger_log(LOGGER_LEVEL_DEBUG, __FILE__ ":" _STR(__LINE__), __VA_ARGS__)

#define log_warn(...) \
  logger_log(LOGGER_LEVEL_WARN, __FILE__ ":" _STR(__LINE__), __VA_ARGS__)

#define log_error(...) \
  logger_log(LOGGER_LEVEL_ERROR, __FILE__ ":" _STR(__LINE__), __VA_ARGS__)


#define log_func_enter \
    log_verbose("Entering %s", __func__);

#define log_func_exit \
    log_verbose("Leaving %s", __func__);

int logger_init();

void logger_set_level(logger_level l);

void logger_stop();

void logger_log(logger_level l, char *loc, char *format, ...);


#endif
