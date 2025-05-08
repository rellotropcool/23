#include "../include/gameGraphic.h"

void	animatePlayer(t_player *sprite)
{
	int frame = sprite->anim_frame + sprite->state * FRAMES_PER_ANIMATION;

	u8* offset = sprite->frame_gfx + frame * 32*32;

	dmaCopy(offset, sprite->sprite_gfx_mem, 32*32);
}

void	initPlayer(t_player *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

	sprite->frame_gfx = (u8*)gfx;
}

void	hidePlayer(t_data *data)
{
	oamSet(&oamMain, 0, 0, 0, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, data->player.sprite_gfx_mem, -1, true, false, false, false, false);
	oamClear(&oamMain, 0, 128);
    swiWaitForVBlank();
	oamUpdate(&oamMain);
}

void	displayPlayerBg(int x, int y, t_data *data, int bg)
{
	int playerX = x;
	int playerY = y - 16;
	int cameraX = 0;
	int cameraY = 0;

	if (playerX > X_OFFSET)										// handle left side
	{
		cameraX = playerX - X_OFFSET;
		playerX = X_OFFSET;
	}
	if (playerY > Y_OFFSET)										// handle top side
	{
		cameraY = playerY - Y_OFFSET;
		playerY = Y_OFFSET;
	}
	if (cameraX > 256 - SCREEN_RIGHT)							// handle right side
	{
		playerX = x - (256 - SCREEN_RIGHT);  
		cameraX = 256 - SCREEN_RIGHT;
	}
	if (cameraY > 256 - SCREEN_BOTTOM)							// handle bottom side
	{
		playerY = y - (256 - SCREEN_BOTTOM);  
		cameraY = 256 - SCREEN_BOTTOM;
	}
	oamSet(&oamMain, 0, playerX - 8, playerY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, data->player.sprite_gfx_mem, -1, false, false, false, false, false);
	bgSetScroll(bg, cameraX, cameraY);
}

void	displayFrame(int x, int y, int bg, t_data *data, bool moving, int animationDelay)
{
	static int frameDelayCounter = 0;
	//const int animationDelay = 8;

	if (moving)
	{
		frameDelayCounter++;
		if (frameDelayCounter >= animationDelay) 
		{
			data->player.anim_frame++;
			if (data->player.anim_frame >= FRAMES_PER_ANIMATION)
				data->player.anim_frame = 0;
			frameDelayCounter = 0;
		}
	}

	animatePlayer(&data->player);
	displayPlayerBg(x, y, data, bg);
	swiWaitForVBlank();
	bgUpdate();
	oamUpdate(&oamMain);
}

void	updateFrame(t_data *data, int *x, int *y, int targetX, int targetY, bool *moving, int bg)
{
	if (!(targetX == *x && targetY == *y))
	{
		if (*x < targetX)
			*x += 2;
		else if (*x > targetX)
			*x -= 2;
		else if (*y < targetY)
			*y += 2;
		else if (*y > targetY)
			*y -= 2;
		displayFrame(*x, *y, bg, data, *moving, 4);
	}
	else
	{
		displayFrame(*x, *y, bg, data, *moving, 8);
		*moving = false;
	}
}