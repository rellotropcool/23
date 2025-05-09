#ifndef INITGFX_H
#define INITGFX_H

#include "game.h"

int		initBitmapBackground(const u16* bitmap, const u16* palette);
int     initTiledBackground(const u16* tiles, const u16* map, const u16* palette, const int tilesLen, const int mapLen, const int paletteLen);
void	initMainSprite(t_sprite *sprite, u8* tiles, const u16* palette);
void    initSpriteGfx(t_sprite *sprite, u8* gfx);

#endif