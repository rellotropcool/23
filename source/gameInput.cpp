#include "../include/gameInput.h"

bool	checkColl(int x, int y, int mapColl[16][16])
{
	if (mapColl[y / 16][x / 16] == 0)
		return true;
	return false;
}

bool	handleInput(t_data *data, int *x, int *y, int *targetX, int *targetY, bool moving, int mapColl[16][16], int *PlayState)
{
	scanKeys();

	int keys = keysHeld();
	int stop = keysDown();

	if (keys)
	{
		if(keys & KEY_UP && moving == false)
		{
			if (*targetY > 0 && data->player.state == W_UP)
				*targetY -= 16;
			data->player.state = W_UP;
			moving = true;
		}
		if(keys & KEY_LEFT && moving == false)
		{
			if (*targetX > 0 && data->player.state == W_LEFT) 
				*targetX -= 16;
			data->player.state = W_LEFT;
			moving = true;
		}
		if(keys & KEY_RIGHT && moving == false)
		{
			if (*targetX < 512 - 16 && data->player.state == W_RIGHT) 
				*targetX += 16;
			data->player.state = W_RIGHT;
			moving = true;
		}
		if(keys & KEY_DOWN && moving == false)
		{
			if (*targetY < 512 - 32 && data->player.state == W_DOWN)
				*targetY += 16;
			data->player.state = W_DOWN;
			moving = true;
		}
		if (stop & KEY_A)
		{
			*PlayState = END;
			return (false);
		}
	}
	else 
		data->player.anim_frame = 1;
	if (!checkColl(*targetX, *targetY, mapColl))
	{
		*targetX = *x;
		*targetY = *y;
	}
	return (moving);
}