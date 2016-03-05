/*
 * rogue.h
 *
 *
 * definitions for the game
 *
 *
 * Copyright (C) 2013-2016  Bryant Moscon - bmoscon@gmail.com
 * 
 * Please see the LICENSE file for the terms and conditions 
 * associated with this software.
 *
 */

#ifndef __ROGUE__
#define __ROGUE__


#ifdef __APPLE__
#include <ncurses.h>
#elif __linux__
#include <ncursesw/curses.h> 
#endif

#include <stdbool.h>
#include <stdint.h>

#include "chars.h"


#define MIN_COL 80
#define MIN_ROW 24

// set map size
#define MAP_COL MIN_COL
// - 2 because we reserve top row for messages
// and bottom row for stats
#define MAP_ROW MIN_ROW - 2

// min/max # of rooms, and minimum room dimensions
#define ROOMS_MAX 9
#define ROOMS_MIN 3
#define ROOM_DIM_MIN 4

// max number of doors per room
#define MAX_DOORS 4

// max items per room
#define MAX_ITEMS 5

// inventory max
#define INVENTORY_MAX 15

// item name length
#define ITEM_NAME_MAX 20



typedef enum {
    I_NONE = 0,
    I_GOLD = GOLD,
    I_SCROLL = SCROLL,
    I_POTION = POTION,
    I_WEAPON = WEAPON,
    I_ARMOR = ARMOR,
    I_RING = RING,
    I_FOOD = FOOD,
    I_WAND = WAND,
    I_TRAP = TRAP,
    I_AMULET = AMULET
} items_e;


typedef enum {
    BLINDNESS = 0,
    CONFUSION,
    EXTRA_HEALING,
    STRENGTH,
    HASTE,
    HEALING,
    MAGIC_DETECT,
    MONSTER_DETECT,
    PARALYZE,
    POISON,
    LEVEL_UP,
    RESTORE_STRENGTH,
    THIRST_QUENCH,
    NO_MAGIC,
    NUM_POTIONS
} potion_type_e;

typedef enum {
    ADD_STRENGTH = 0,
    AGG_MONSTER,
    DEXTERITY,
    ADD_DAMAGE,
    ADD_ARMOR,
    PROTECTION,
    HEAL,
    SEARCHING,
    SLOW_DIGEST,
    STEALTH,
    SUSTAIN_STR,
    ADORNMENT,
    NUM_RINGS
} ring_type_e;

typedef enum {
    AGG_MONSTERS = 0,
    CREATE_MONSTER,
    ENCHANT_ARMOR,
    ENCHANT_WEAPON,
    FOOD_DETECT,
    HOLD_MONSTER,
    IDENTIFY,
    MAP,
    CONFUSE_MONSTER,
    SCARE_MONSTER,
    SLEEP,
    TELEPORT,
    REMOVE_CURSE,
    BLANK,
    NUM_SCROLLS
} scroll_type_e;

typedef enum {
    REVEAL_MONSTER = 0,
    FREEZE,
    LIFE_DRAIN,
    HASTE_MONSTER,
    LIGHT,
    LIGHTNING,
    MAGIC_MISSILE,
    POLYMORPH,
    SLOW,
    STRIKING,
    TELEPORT_AWAY,
    TELEPORT_TO,
    NOTHING,
    NUM_WANDS
} wand_type_e;


typedef struct coord_st {
    int x;
    int y;
} coord_st;


typedef struct inv_slot_st {
    items_e   type;
    char      name[ITEM_NAME_MAX];
    union {
	potion_type_e  p_type;
	scroll_type_e  s_type;
	ring_type_e    r_type;
	wand_type_e    w_type;
	char           dice[3];
    } attr;

} inv_slot_st;


typedef struct item_st {
    coord_st  pos;
    items_e   type;
} item_st;


typedef struct door_t {
    coord_st  pos;
    bool      hidden;
} door_st;


typedef struct tunnel_st {
    int       len;
    coord_st  *pos;
} tunnel_st;


typedef struct room_t {
    coord_st   pos;
    int        x_len;
    int        y_len;
    tunnel_st  tunnels[MAX_DOORS];
    door_st    doors[MAX_DOORS];
    item_st    items[MAX_ITEMS];
} room_st;


typedef struct map_t {
    coord_st    stairs;
    int         num_rooms;
    room_st    *rooms;
} map_st;


#define MAX_UPDATES 5

// Game State
typedef struct state_st {
    WINDOW *game;
    WINDOW *help;
    WINDOW *inventory;

    bool running;

    // current game message
    char message[MIN_COL]; 
  
    // rogue's name
    char *name;

    // stats
    uint32_t hp;
    uint32_t hp_max;
    uint32_t str;
    uint32_t str_max;
    uint32_t armor;
  
    uint32_t gold;
    uint32_t level;
    uint32_t rank;
    uint32_t food;
  
    // rogue map position
    int x;
    int y;

    // rogue's inventory
    inv_slot_st inv[INVENTORY_MAX];

    // lookup tables for item names
    char *scroll_names[NUM_SCROLLS];
    char *ring_names[NUM_RINGS];
    char *potion_names[NUM_POTIONS];
    char *wand_names[NUM_WANDS];

  
    // map data
    map_st map;
} state_st;




void free_state(state_st *state);

void roll_rogue(state_st *state);

void random_string(char *str, size_t len);

void rings_init(state_st *state);

void potions_init(state_st *state);

void wands_init(state_st *state);

void state_log(const state_st *state);

#endif

