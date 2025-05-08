#include "../include/handlePlay.h"

void	handlePlay(t_data *data) // test map 32x32 tiles de 8x8 pixels (oui c'est un fromage)
{
	static int			PlayState = INIT;
	static t_PlayData	PlayData;
	static int mapColl[16][16] ={
		{0,2,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1},
		{0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,3},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

	switch (PlayState)
	{
		case INIT:
			PlayData.x = 16;
			PlayData.y = 16;
			PlayData.targetX = PlayData.x;
			PlayData.targetY = PlayData.y;
			PlayData.moving = false;
			data->player.state = W_DOWN;

			PlayState = GFX_INIT;
			break;
		case GFX_INIT:
			videoSetMode(MODE_0_2D);
			vramSetBankA(VRAM_A_MAIN_BG);

			PlayData.bg = bgInit(0, BgType_Text8bpp, BgSize_T_512x512, 31, 0);

			dmaCopy(mapTiles, bgGetGfxPtr(PlayData.bg), mapTilesLen);
			dmaCopy(mapMap, bgGetMapPtr(PlayData.bg), mapMapLen);
			dmaCopy(mapPal, BG_PALETTE, mapPalLen);
			
			vramSetBankB(VRAM_B_MAIN_SPRITE);

			oamInit(&oamMain, SpriteMapping_1D_128, false);
			initPlayer(&data->player, (u8*)manTiles);
			dmaCopy(manPal, SPRITE_PALETTE, 512);

			PlayState = PLAYING;
			break;
		case PLAYING:
			if (!PlayData.moving)
				PlayData.moving = handleInput(data, &PlayData.x, &PlayData.y, &PlayData.targetX, &PlayData.targetY, PlayData.moving, mapColl, &PlayState);
			updateFrame(data, &PlayData.x, &PlayData.y, PlayData.targetX, PlayData.targetY, &PlayData.moving, PlayData.bg);
			consoleClear();
			iprintf("Player name is: %s\n", data->myName);
			iprintf("x: %d y: %d\n", PlayData.x, PlayData.y);
			iprintf("playerX: %d playerY: %d\n", PlayData.x / 16, PlayData.y / 16);
			break;
		case END:
			hidePlayer(data);

			PlayState = GFX_INIT;
			GameState = ENDGAME;
			break;
	}
}