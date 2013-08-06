/*
 * logger.c
 *
 *
 * logging support
 *
 *
 * Copyright (C) 2013  Bryant Moscon - bmoscon@gmail.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution, and in the same 
 *    place and form as other copyright, license and disclaimer information.
 *
 * 3. The end-user documentation included with the redistribution, if any, must 
 *    include the following acknowledgment: "This product includes software 
 *    developed by Bryant Moscon (http://www.bryantmoscon.org/)", in the same 
 *    place and form as other third-party acknowledgments. Alternately, this 
 *    acknowledgment may appear in the software itself, in the same form and 
 *    location as other such third-party acknowledgments.
 *
 * 4. Except as contained in this notice, the name of the author, Bryant Moscon,
 *    shall not be used in advertising or otherwise to promote the sale, use or 
 *    other dealings in this Software without prior written authorization from 
 *    the author.
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
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
  
  fp = fopen("rogue.log", "w");
  
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
  
  if (!fp) {
    return;
  }
  
  ltime = time(NULL);
  
  fprintf(fp, "log ended at %s", asctime(localtime(&ltime)));
  
  fclose(fp);
}


void logger_log(logger_level l, char *loc, char *format, ...)
{
  if (l < level) {
    return;
  }

  va_list args;
  va_start(args, format);

  fprintf(fp, "%s - ", loc);
  vfprintf(fp, format, args);
  fprintf(fp, "\n");
  
  va_end(args);

  fflush(fp);
}

