#include "../include/handlePlay.h"

void	handlePlay(t_data *data) // test map 32x32 tiles de 8x8 pixels (oui c'est un fromage)
{
	static int			playState = INIT;
	static t_playData	playData;

	switch (playState)
	{
		case INIT:
			playData.roomId = 0;
			playData.x = data->rooms[playData.roomId].x;
			playData.y = data->rooms[playData.roomId].y;
			playData.targetX = playData.x;
			playData.targetY = playData.y;
			playData.moving = false;
			data->player.state = W_DOWN;

			playState = GFX_INIT;
			break;
		case GFX_INIT:
			playData.bg = initTiledBackground(data->rooms[playData.roomId]);
			initMainSprite(&data->player, (u8*)manTiles, manPal);
			swiWaitForVBlank();

			playState = PLAYING;
			break;
		case PLAYING:
			
			handleInput(data, &playData, &playState);
			updateFrame(data, &playData);
			consoleClear();
			iprintf("Player name is: %s\n", data->myName);
			iprintf("x: %d y: %d\n", playData.x, playData.y);
			iprintf("exitX: %d exitY: %d\n", data->rooms[playData.roomId].exit.tileX, data->rooms[playData.roomId].exit.tileY);

			break;
		case END:
			hidePlayer(data);

			playState = GFX_INIT;
			GameState = ENDGAME;
			break;
	}
}