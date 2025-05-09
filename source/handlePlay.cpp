#include "../include/handlePlay.h"

void	handlePlay(t_data *data) // test map 32x32 tiles de 8x8 pixels (oui c'est un fromage)
{
	static int			playState = INIT;
	static t_playData	playData;
	static int mapColl[16][16] ={
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1},
		{0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

	switch (playState)
	{
		case INIT:
			playData.x = 16;
			playData.y = 16;
			playData.targetX = playData.x;
			playData.targetY = playData.y;
			playData.room = 0;
			playData.moving = false;
			data->player.state = W_DOWN;

			playState = GFX_INIT;
			break;
		case GFX_INIT:
			playData.bg = initTiledBackground((u16*)mapTiles, (u16*)mapMap, (u16*)mapPal, mapTilesLen, mapMapLen, mapPalLen);
			initMainSprite(&data->player, (u8*)manTiles, manPal);

			playState = PLAYING;
			break;
		case PLAYING:
			playData.moving = handleInput(data, &playData.x, &playData.y, &playData.targetX, &playData.targetY, playData.moving, mapColl, &playState);
			updateFrame(data, &playData.x, &playData.y, playData.targetX, playData.targetY, &playData.moving, playData.bg);
			consoleClear();
			iprintf("Player name is: %s\n", data->myName);
			iprintf("x: %d y: %d\n", playData.x, playData.y);
			iprintf("playerX: %d playerY: %d\n", playData.x / 16, playData.y / 16);
			iprintf("A: %u B: %u\n", (unsigned int)(u16*)mapTiles, (unsigned int)data->rooms[playData.room].tiles);
			break;
		case END:
			hidePlayer(data);

			playState = GFX_INIT;
			GameState = ENDGAME;
			break;
	}
}