/*
 * logger.c
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

#define _XOPEN_SOURCE_EXTENDED

#include <time.h>
#include <stdio.h>

#include "logger.h"

static FILE *fp = NULL;
static logger_level level = LOGGER_LEVEL_OFF;


int logger_init()
{
    time_t ltime;

    if (level == LOGGER_LEVEL_OFF) {
	return (0);
    }
  
    fp = fopen("rogue.log", "a");
  
    if (!fp) {
	return (-1);
    }
  
    ltime = time(NULL);
  
    fprintf(fp, "log started at %s", asctime(localtime(&ltime)));
 
    return (0);
}

void logger_set_level(logger_level l)
{
    level = l;
}


void logger_stop()
{
    time_t ltime;
  
    if (level == LOGGER_LEVEL_OFF || !fp) {
	return;
    }
  
    ltime = time(NULL);
  
    fprintf(fp, "log ended at %s", asctime(localtime(&ltime)));
  
    fclose(fp);
}


void logger_log(logger_level l, char *loc, char *format, ...)
{
    va_list args;
  
    if (l < level) {
	return;
    }

    if (!fp) {
	if (logger_init() != 0) {
	    return;
	}
    }
    
  
    va_start(args, format);

    fprintf(fp, "%s - ", loc);
    vfprintf(fp, format, args);
    fprintf(fp, "\n");
  
    va_end(args);

    fflush(fp);
}

