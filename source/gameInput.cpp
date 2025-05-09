#include "../include/gameInput.h"

bool	checkColl(int x, int y, uint8_t mapColl[128], int len)
{
	if (getCollisionBit(mapColl, y * len + x) == 0)
		return true;
	return false;
}

void	setNextRoom(t_data *data, t_playData *playData, int *playState)
{
	playData->x = data->rooms[playData->roomId].exit.destX;
	playData->y = data->rooms[playData->roomId].exit.destY;
	playData->targetX = playData->x;
	playData->targetY = playData->y;
	playData->roomId = data->rooms[playData->roomId].exit.destIndex;
	*playState = GFX_INIT;
}

void	handleInput(t_data *data, t_playData *playData, int *playState)
{
	scanKeys();

	int keys = keysHeld();
	int stop = keysDown();

	if (keys)
	{
		if(keys & KEY_UP && playData->moving == false)
		{
			data->player.state = W_UP;
			if ((playData->x == data->rooms[playData->roomId].exit.tileX) && (playData->y - 1 == data->rooms[playData->roomId].exit.tileY))
			{
				setNextRoom(data, playData, playState);
				return;
			}
			if (playData->targetY > 0 && data->player.state == W_UP)
				playData->targetY -= 1;
			playData->moving = true;
		}
		if(keys & KEY_LEFT && playData->moving == false)
		{
			data->player.state = W_LEFT;
			if ((playData->x - 1 == data->rooms[playData->roomId].exit.tileX) && (playData->y == data->rooms[playData->roomId].exit.tileY))
			{
				setNextRoom(data, playData, playState);
				return;
			}
			if (playData->targetX > 0 && data->player.state == W_LEFT) 
				playData->targetX -= 1;
			playData->moving = true;
		}
		if(keys & KEY_RIGHT && playData->moving == false)
		{
			data->player.state = W_RIGHT;
			if ((playData->x + 1 == data->rooms[playData->roomId].exit.tileX) && (playData->y == data->rooms[playData->roomId].exit.tileY))
			{
				setNextRoom(data, playData, playState);
				return;
			}
			if (playData->targetX < data->rooms[playData->roomId].mapX - 1 && data->player.state == W_RIGHT) 
				playData->targetX += 1;
			playData->moving = true;
		}
		if(keys & KEY_DOWN && playData->moving == false)
		{
			data->player.state = W_DOWN;
			if ((playData->x == data->rooms[playData->roomId].exit.tileX) && (playData->y + 1 == data->rooms[playData->roomId].exit.tileY))
			{
				setNextRoom(data, playData, playState);
				return;
			}
			if (playData->targetY < data->rooms[playData->roomId].mapY - 1 && data->player.state == W_DOWN)
				playData->targetY += 1;
			playData->moving = true;
		}
		if (stop & KEY_B)
		{
			*playState = END;
			return ;
		}
	}
	else 
		data->player.anim_frame = 1;
	if (!checkColl(playData->targetX, playData->targetY, data->rooms[playData->roomId].mapColl, data->rooms[playData->roomId].mapY))
	{
		playData->targetX = playData->x;
		playData->targetY = playData->y;
	}
}