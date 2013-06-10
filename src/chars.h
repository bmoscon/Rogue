/*
 * chars.h
 *
 *
 * ASCII character abstraction
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
#ifndef __ROGUE_CHARS__
#define __ROGUE_CHARS__


// horizontal double line
#define HORIZ 0x2550
// for unicode 
#define HORIZU "\u2550"


// vertical double line
#define VERT 0x2551
#define VERTU "\u2551"


// top left corner 
#define TLCORNER 0x2554
#define TLCORNERU "\u2554"


// top right corner
#define TRCORNER 0x2557
#define TRCORNERU "\u2557"


// bottom left corner
#define BLCORNER 0x255A
#define BLCORNERU "\u255A"


// bottom right corner
#define BRCORNER 0x255D
#define BRCORNERU "\u255D"


// left T
#define LTEE 0x2560
#define LTEEU "\u2560"


// right T
#define RTEE 0x2563
#define RTEEU "\u2563"


// door
#define DOOR 0x256C
#define DOORU "\u256C"


// floor
#define FLOOR 0x2E
#define FLOORU "\x2E"


// tunnel
#define TUNNEL 0x2588
#define TUNNELU "\u2588"


// rogue
#define ROGUE 0x40
#define ROGUEU "\u0040"


// stairs
#define STAIRS 0x018E
#define STAIRSU "\u018E"


// gold
#define GOLD 0x2A
#define GOLDU "\x2A"


// scroll
#define SCROLL 0x221E
#define SCROLLU "\u221E"


// potion
#define POTION 0xA1
#define POTIONU "\u00A1"


// food
#define FOOD 0x00A4
#define FOODU "\u00A4"


// armor
#define ARMOR 0x25D8
#define ARMORU "\u25D8"


// amulet
#define AMULET 0x0194
#define AMULETU "\u0194"


// trap
#define TRAP 0x25CA
#define TRAPU "\u25CA"


// ring
#define RING 0x00BA
#define RINGU "\u00BA"


// wand
#define WAND 0x017F
#define WANDU "\u017F"


// weapon
#define WEAPON 0x2191
#define WEAPONU "\u2191"


#endif
