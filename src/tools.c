/*
 * tools.c
 *
 *
 * utilities
 *
 *
 * Copyright (C) 2013-2016  Bryant Moscon - bmoscon@gmail.com
 * 
 * Please see the LICENSE file for the terms and conditions 
 * associated with this software.
 *
 */

#define _XOPEN_SOURCE_EXTENDED

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "logger.h"

static void random_syll(char *syll)
{
    log_func_enter;
  
    static char con[] = "bcdfghjklmnpqrstvwxyz";
    static char vow[] = "aeiou";

    // -2 because of the implied \0 at end of each string
    syll[0] = con[rand() % (sizeof(con) - 2)];
    syll[1] = vow[rand() % (sizeof(vow) - 2)];
    syll[2] = con[rand() % (sizeof(con) - 2)];
    syll[3] = '\0';
  
    log_func_exit;
}


int random_int(int min, int max)
{
    log_func_enter;
  
    if (min == max) {
	return (min);
    }
  
    log_func_exit;
    return ((rand() % (max - min)) + min);
}


// Fisher-Yates Algorithm
void random_shuffle(int *array, int upper)
{
    log_func_enter;
  
    int i;
    int j;
    int t;
  
    for (i = upper - 1; i != 1; --i) {
	j = rand() % i;
	t = array[i];
	array[i] = array[j];
	array[j] = t;
    }

    log_func_exit;
}


void random_string(char *str, size_t len)
{
    log_func_enter;

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

    log_func_exit;
}


