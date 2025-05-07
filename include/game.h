#ifndef GAME_H
#define GAME_H

// INCLUDES

#include <nds.h>
#include <stdio.h>

// TEXTURES

#include "drunkenlogo.h"
#include "drunkenlogo_2.h"

// SPRITES

#include "man.h"

// DEFINE

#define FRAMES_PER_ANIMATION 3

// ENUM

enum e_GameState 
{
	STARTING,
	ASK_NAME,
	PLAYING,
	END
};

enum e_SpriteState 
{
	W_UP = 0, 
	W_RIGHT = 1, 
	W_DOWN = 2, 
	W_LEFT = 3
};

enum 
{
	SCREEN_TOP = 0, 
	SCREEN_BOTTOM = 192, 
	SCREEN_LEFT = 0, 
	SCREEN_RIGHT = 256
};

// STRUCTURES

typedef struct s_player
{
	int x;
	int y;

	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;
}	t_player;

typedef struct  s_data
{
    char    myName[16];
	t_player	player;
	bool	moving;
}   t_data;

// GLOBAL VARIABLES

extern  enum e_GameState GameState;

// PROTOTYPES

void    handleStart(t_data *data);
void    handleAsk(t_data *data);
void    handleEnd(t_data *data);
void	handlePlay(t_data *data);

void initMan(t_player *sprite, u8* gfx);

void    nget(char *dest, int n);

#endif