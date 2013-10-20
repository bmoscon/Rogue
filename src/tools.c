/*
 * tools.c
 *
 *
 * utilities
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

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

static void random_syll(char *syll)
{
  static char con[] = "bcdfghjklmnpqrstvwxyz";
  static char vow[] = "aeiou";

  // -2 because of the implied \0 at end of each string
  syll[0] = con[rand() % (sizeof(con) - 2)];
  syll[1] = vow[rand() % (sizeof(vow) - 2)];
  syll[2] = con[rand() % (sizeof(con) - 2)];
  syll[3] = '\0';
}


int random_int(int min, int max)
{
  if (min == max) {
    return (min);
  }
  
  return ((rand() % (max - min)) + min);
}


// Fisher-Yates Algorithm
void random_shuffle(int *array, int upper)
{
  int i;
  int j;
  int t;
  
  for (i = upper - 1; i != 1; --i) {
    j = rand() % i;
    t = array[i];
    array[i] = array[j];
    array[j] = t;
  }
}


void random_string(char *str, size_t len)
{
  uint32_t i = 0;
  char syll[4];
  
  while (i < len) {
    random_syll(syll);
    // add random syllable to the name
    i += snprintf(&str[i], len, "%s", syll);
    
    // see if we should add a space or not
    if (!(rand() % 3)) {
      i += snprintf(&str[i], len, "%s", " ");
    }
  }
  
  str[len] = '\0';
}

