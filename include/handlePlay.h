#ifndef HANDLEPLAY_H
#define HANDLEPLAY_H

#include "game.h"
#include "initGfx.h"
#include "gameInput.h"
#include "gameGraphic.h"

enum e_playState
{
    INIT = 0,
    GFX_INIT = 1,
    PLAYING = 2,
    MENU = 3,
    END = 4
};

typedef struct s_playData
{
    int                 bg;
    int                 x;
	int                 y;
	int                 targetX;
	int                 targetY;
    int                 roomId;
	bool                moving;
}   t_playData;

void	handlePlay(t_data *data);

#endif