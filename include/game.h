#ifndef GAME_H
#define GAME_H

// INCLUDES

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// test_osterone

#include "int2.hpp"

// TEXTURES

#include "drunkenlogo.h"
#include "drunkenlogo_2.h"
#include "the_end.h"
#include "cheese.h"
#include "map.h"
#include "map2.h"

// SPRITES

#include "man.h"

// ENUM

enum e_GameState 
{
	STARTING,
	ASK_NAME,
	INGAME,
	ENDGAME
};

// STRUCTURES

typedef struct s_exit
{
    int		tileX;
    int		tileY;
    t_room*	destination;
    int		destX;
    int		destY;
}	t_exit;

typedef struct s_room
{
    // GFX

    const   u16* tiles;
    const   u16* map;
    const   u16* palette;
    int     tilesLen;
    int     mapLen;
    int     paletteLen;

    // Collisions

    int   	mapColl[4096];
	int		mapX;
	int		mapY;

	// Links to other rooms


    int     x;
    int     y;
}   t_room;

typedef struct	s_sprite
{
	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;
}	t_sprite;

typedef struct  s_data
{
    char    	myName[16];
	t_sprite	player;
	t_room*		rooms;
}   t_data;

// GLOBAL VARIABLES

extern  enum e_GameState GameState;

#endif