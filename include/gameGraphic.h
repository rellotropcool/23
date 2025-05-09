#ifndef GAMEGRAPHIC_H
#define GAMEGRAPHIC_H

#include "game.h"

enum 
{
	SCREEN_TOP = 0, 
	SCREEN_BOTTOM = 192, 
	SCREEN_LEFT = 0, 
	SCREEN_RIGHT = 256,
    FRAMES_PER_ANIMATION = 3,
    X_OFFSET = 112,
    Y_OFFSET = 80
};

enum e_SpriteState 
{
	W_UP = 0, 
	W_RIGHT = 1, 
	W_DOWN = 2, 
	W_LEFT = 3
};

void    animatePlayer(t_sprite *sprite);
void	hidePlayer(t_data *data);
void	displaySpriteBg(int x, int y, t_data *data, int bg);
void	displayFrame(int x, int y, int bg, t_data *data, bool moving, int animationDelay);
void	updateFrame(t_data *data, int *x, int *y, int targetX, int targetY, bool *moving, int bg);

#endif