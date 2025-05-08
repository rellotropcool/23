#ifndef GAME_H
#define GAME_H

// INCLUDES

#include <nds.h>
#include <stdio.h>

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

// DEFINE

// ENUM

enum e_tileType
{
	WALK = 0 >> 1,

};

enum e_GameState 
{
	STARTING,
	ASK_NAME,
	INGAME,
	ENDGAME
};

// STRUCTURES

typedef struct	s_room
{
	int2	roomSize;
}	t_room;

typedef struct	s_player
{
	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;
}	t_player;

typedef struct  s_data
{
    char    myName[16];
	t_player	player;
}   t_data;

// GLOBAL VARIABLES

extern  enum e_GameState GameState;

// PROTOTYPES

void    nget(char *dest, int n);
int		initBitmapBackground(const u16* bitmap, const u16* palette);

void    handleStart(t_data *data);
void    handleAsk(t_data *data);
void    handleEnd(t_data *data);
void	handlePlay(t_data *data);

#endif