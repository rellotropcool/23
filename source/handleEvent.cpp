#include "../include/game.h"

void	handleStart(t_data *t_data)
{
	consoleClear();
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);

	scanKeys();
	int keys = keysDown();

	iprintf("\n\n\tHello DS devers\n");
	iprintf("\twww.drunkencoders.com\n");
	iprintf("\t256 color bitmap demo");

	int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);

	dmaCopy(drunkenlogoBitmap, bgGetGfxPtr(bg3), 256*256);
	dmaCopy(drunkenlogoPal, BG_PALETTE, 256*2);

	if (keys)
	{
		if (keys & KEY_A)
			GameState = ASK_NAME;
	}
}

void	handleAsk(t_data *data)
{
	consoleClear();

	int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);

	dmaCopy(drunkenlogo_2Bitmap, bgGetGfxPtr(bg3), 256*256);
	dmaCopy(drunkenlogo_2Pal, BG_PALETTE, 256*2);

	iprintf("What is your name?\n");

    nget(data->myName, 16);

	iprintf("\nHello %s", data->myName);

	GameState = PLAYING;
}

void	handleEnd(t_data *t_data)
{
	consoleClear();
	iprintf("THE END GROS FDP");
	scanKeys();
		int keys = keysDown();
	if (keys)
	{
		if (keys & KEY_A)
			GameState = STARTING;
	}
}



void animateMan(t_player *sprite)
{
	int frame = sprite->anim_frame + sprite->state * FRAMES_PER_ANIMATION;

	u8* offset = sprite->frame_gfx + frame * 32*32;

	dmaCopy(offset, sprite->sprite_gfx_mem, 32*32);
}

void initMan(t_player *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	
	sprite->frame_gfx = (u8*)gfx;
}

void	handlePlay(t_data *data)
{
	vramSetBankB(VRAM_B_MAIN_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	initMan(&data->player, (u8*)manTiles);
	dmaCopy(manPal, SPRITE_PALETTE, 512);

	while(1)
	{
		consoleClear();
		iprintf("Player name is: %s\n", data->myName);
		iprintf("player_x: %d  player_y: %d\n",  data->player.y, data->player.x);

		scanKeys();

		int keys = keysHeld();

		if (keys)
		{
			if(keys & KEY_UP)
			{
				if(data->player.y > SCREEN_TOP) 
					data->player.y--;
				data->player.state = W_UP;
			}
			if(keys & KEY_LEFT)
			{
				if(data->player.x > SCREEN_LEFT) 
					data->player.x--;
				data->player.state = W_LEFT;
			}
			if(keys & KEY_RIGHT)
			{
				if(data->player.x < SCREEN_RIGHT - 32) 
					data->player.x++;
				data->player.state = W_RIGHT;
			}
			if(keys & KEY_DOWN)
			{
				if(data->player.y < SCREEN_BOTTOM - 32) 
					data->player.y++;
				data->player.state = W_DOWN;
			}
			if (keys & KEY_A)
			{
				GameState = END;
				break;
			}
			
			data->player.anim_frame++;

			if(data->player.anim_frame >= FRAMES_PER_ANIMATION) 
				data->player.anim_frame = 0;
		}

		animateMan(&data->player);

		oamSet(&oamMain, 0, data->player.x, data->player.y, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, data->player.sprite_gfx_mem, -1, false, false, false, false, false);
			
		swiWaitForVBlank();

		oamUpdate(&oamMain);
	}
}