/*
 * tools.h
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

#ifndef __TOOLS__
#define __TOOLS__

int random_int(int min, int max);

void random_shuffle(int *array, int upper);

void random_string(char *str, size_t len);


#endif
