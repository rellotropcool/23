#include "../include/initGfx.h"

int initBitmapBackground(const u16* bitmap, const u16* palette) 
{
	videoSetMode(MODE_5_2D);
	vramSetBankA(VRAM_A_MAIN_BG);

	int bg = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
	dmaCopy(bitmap, bgGetGfxPtr(bg), 256 * 256);
	dmaCopy(palette, BG_PALETTE, 256 * 2);

	return bg;
}

int	initTiledBackground(const u16* tiles, const u16* map, const u16* palette, const int tilesLen, const int mapLen, const int paletteLen)
{
	videoSetMode(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_BG);

	int bg = bgInit(0, BgType_Text8bpp, BgSize_T_512x512, 31, 0);

	dmaCopy(tiles, bgGetGfxPtr(bg), tilesLen);
	dmaCopy(map, bgGetMapPtr(bg), mapLen);
	dmaCopy(palette, BG_PALETTE, paletteLen);
	return bg;
}

void	initSpriteGfx(t_sprite *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

	sprite->frame_gfx = (u8*)gfx;
}

void	initMainSprite(t_sprite *sprite, u8* tiles, const u16* palette)
{
	vramSetBankB(VRAM_B_MAIN_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	initSpriteGfx(sprite, tiles);
	dmaCopy(palette, SPRITE_PALETTE, 512);
}