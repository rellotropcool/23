#ifndef HANDLEPLAY_H
#define HANDLEPLAY_H

#include "game.h"
#include "gameInput.h"
#include "gameGraphic.h"

enum e_PlayState
{
    INIT = 0,
    GFX_INIT = 1,
    PLAYING = 2,
    MENU = 3,
    END = 4
};

typedef struct s_PlayData
{
    int                 PlayState;
    int                 bg;
    int                 x;
	int                 y;
	int                 targetX;
	int                 targetY;
	bool                moving;
}   t_PlayData;

#endif