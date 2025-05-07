#include "../include/game.h"

static int initBitmapBackground(const u16* bitmap, const u16* palette) {
	videoSetMode(MODE_5_2D);
	vramSetBankA(VRAM_A_MAIN_BG);

	int bg = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
	dmaCopy(bitmap, bgGetGfxPtr(bg), 256 * 256);
	dmaCopy(palette, BG_PALETTE, 256 * 2);

	return bg;
}

void	handleStart(t_data *data)
{
	consoleClear();
	initBitmapBackground((const u16*)drunkenlogoBitmap, (const u16*)drunkenlogoPal);

	iprintf("\n\n\tHello DS devers\n");
	iprintf("\twww.drunkencoders.com\n");
	iprintf("\t256 color bitmap demo");

	while (1)
	{
		scanKeys();
		int keys = keysDown();
		if (keys)
		{
			if (keys & KEY_A)
			{
				if (!data->myName[0])
					GameState = ASK_NAME;
				else
					GameState = PLAYING;
				break;
			}
		}
	}
	swiWaitForVBlank();
}

void	handleAsk(t_data *data)
{
	consoleClear();
	initBitmapBackground((const u16*)drunkenlogo_2Bitmap, (const u16*)drunkenlogo_2Pal);

	iprintf("What is your name?\n");

    nget(data->myName, 16);

	iprintf("\nHello %s", data->myName);

	while (1)
	{
		scanKeys();
		int keys = keysDown();
		if (keys)
		{
			if (keys & KEY_A)
			{
				GameState = PLAYING;
				return;
			}
		}
	}
}

void	handleEnd(t_data *t_data)
{
	consoleClear();
	initBitmapBackground((const u16*)the_endBitmap, (const u16*)the_endPal);

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

void initPlayer(t_player *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

	sprite->frame_gfx = (u8*)gfx;
}

void	hidePlayer(t_data *data)
{
	oamSet(&oamMain, 0, 0, 0, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, data->player.sprite_gfx_mem, -1, true, false, false, false, false);
	oamClear(&oamMain, 0, 128);
	oamUpdate(&oamMain);
}

void	displaySpriteBg(int x, int y, t_data *data, int bg)
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
	if (cameraX > 512 - SCREEN_RIGHT)							// handle right side
	{
		playerX = x - (512 - SCREEN_RIGHT);  
		cameraX = 512 - SCREEN_RIGHT;
	}
	if (cameraY > 512 - SCREEN_BOTTOM)							// handle bottom side
	{
		playerY = y - (512 - SCREEN_BOTTOM);  
		cameraY = 512 - SCREEN_BOTTOM;
	}
	consoleClear();
	iprintf("Player name is: %s\n", data->myName);
	iprintf("x: %d y: %d\n", x, y);
	oamSet(&oamMain, 0, playerX, playerY, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, data->player.sprite_gfx_mem, -1, false, false, false, false, false);
	bgSetScroll(bg, cameraX, cameraY);
}

void	displayFrame(int x, int y, int bg, t_data *data, bool moving)
{
	static int frameDelayCounter = 0;
	const int animationDelay = 8;

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

	animateMan(&data->player);
	displaySpriteBg(x, y, data, bg);
	swiWaitForVBlank();
	bgUpdate();
	oamUpdate(&oamMain);
}

void	handlePlay(t_data *data) // test map 32x32 tiles de 1 pixels (oui c'est un fromage)
{
	videoSetMode(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_BG);

	int bg = bgInit(0, BgType_Text8bpp, BgSize_T_512x512, 31, 0);

    dmaCopy(mapTiles, bgGetGfxPtr(bg), mapTilesLen);
    dmaCopy(mapMap, bgGetMapPtr(bg), mapMapLen);
    dmaCopy(mapPal, BG_PALETTE, mapPalLen);
		
	vramSetBankB(VRAM_B_MAIN_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	initPlayer(&data->player, (u8*)manTiles);
	dmaCopy(manPal, SPRITE_PALETTE, 512);

	int x = 0;
	int y = 0;
	int targetX = x;
	int targetY = y;
	bool moving = false;
	
	data->player.state = W_DOWN;
	
	while(1)
	{
		scanKeys();

		int keys = keysHeld();
		int stop = keysDown();

		if (keys)
		{
			if(keys & KEY_UP && moving == false)
			{
				if (targetY > 0)
					targetY -= 16;
				data->player.state = W_UP;
				moving = true;
			}
			if(keys & KEY_LEFT && moving == false)
			{
				if (targetX > 0) 
					targetX -= 16;
				data->player.state = W_LEFT;
				moving = true;
			}
			if(keys & KEY_RIGHT && moving == false)
			{
				if (targetX < 512 - 32) 
					targetX += 16;
				data->player.state = W_RIGHT;
				moving = true;
			}
			if(keys & KEY_DOWN && moving == false)
			{
				if (targetY < 512 - 32) 
					targetY += 16;
				data->player.state = W_DOWN;
				moving = true;
			}
			if (stop & KEY_A)
			{
				hidePlayer(data);
				swiWaitForVBlank();
				oamUpdate(&oamMain);
				GameState = END;
				return;
			}
		}
		while (!(targetX == x && targetY == y))
		{
			if (x < targetX)
				x++;
			else if (x > targetX)
				x--;
			else if (y < targetY)
				y++;
			else if (y > targetY)
				y--;
			displayFrame(x, y, bg, data, moving);
		}
		moving = false;
		data->player.anim_frame = 1;
		displayFrame(x, y, bg, data, moving);
	}
}