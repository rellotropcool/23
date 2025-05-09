#include "../include/gameGraphic.h"

void	animatePlayer(t_sprite *sprite)
{
	int frame = sprite->anim_frame + sprite->state * FRAMES_PER_ANIMATION;

	u8* offset = sprite->frame_gfx + frame * 32*32;

	dmaCopy(offset, sprite->sprite_gfx_mem, 32*32);
}

void	hidePlayer(t_data *data)
{
	oamSet(&oamMain, 0, 0, 0, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, data->player.sprite_gfx_mem, -1, true, false, false, false, false);
	oamClear(&oamMain, 0, 128);
    swiWaitForVBlank();
	oamUpdate(&oamMain);
}

void	displayPlayerBg(int x, int y, t_data *data, int bg, t_playData *playData)
{
	int playerX = x;
	int playerY = y;
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
	if (cameraX > data->rooms[playData->roomId].mapX * 16 - SCREEN_RIGHT)							// handle right side
	{
		playerX = x - (data->rooms[playData->roomId].mapX * 16 - SCREEN_RIGHT);  
		cameraX = data->rooms[playData->roomId].mapX * 16 - SCREEN_RIGHT;
	}
	if (cameraY > data->rooms[playData->roomId].mapY * 16 - SCREEN_BOTTOM)							// handle bottom side
	{
		playerY = y - (data->rooms[playData->roomId].mapY * 16 - SCREEN_BOTTOM);  
		cameraY = data->rooms[playData->roomId].mapY * 16 - SCREEN_BOTTOM;
	}
	//iprintf("mapX: %d mapY: %d\nplayerX: %d playerY: %d\ncameraX: %d cameraY: %d\n",data->rooms[playData->roomId].mapX, data->rooms[playData->roomId].mapY, playerX, playerY, cameraX, cameraY);
	oamSet(&oamMain, 0, playerX - 8, playerY - 16, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, data->player.sprite_gfx_mem, -1, false, false, false, false, false);
	bgSetScroll(bg, cameraX, cameraY);
}

void	displayFrame(int x, int y, int bg, t_data *data, bool moving, int animationDelay, t_playData *playData)
{
	static int frameDelayCounter = 0;

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
	displayPlayerBg(x, y, data, bg, playData);
	swiWaitForVBlank();
	bgUpdate();
	oamUpdate(&oamMain);
}

void	updateFrame(t_data *data, t_playData *playData)
{
	static int x = 0;
	static int y = 0;

	if (!(playData->targetX * 16 == playData->x * 16 + x && playData->targetY * 16 == playData->y * 16 + y))
	{
		if (playData->x < playData->targetX)
			x += 2;
		else if (playData->x > playData->targetX)
			x -= 2;
		else if (playData->y < playData->targetY)
			y += 2;
		else if (playData->y > playData->targetY)
			y -= 2;
		displayFrame(playData->x * 16 + x, playData->y * 16 + y, playData->bg, data, playData->moving, 4, playData);
	}
	else
	{
		x = 0;
		y = 0;
		playData->x = playData->targetX;
		playData->y = playData->targetY;
		displayFrame(playData->x * 16, playData->y * 16, playData->bg, data, playData->moving, 10, playData);
		playData->moving = false;
	}
}