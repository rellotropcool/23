#ifndef INITGFX_H
#define INITGFX_H

#include "game.h"

int		initBitmapBackground(const u16* bitmap, const u16* palette);
int     initTiledBackground(t_room room);
void	initMainSprite(t_sprite *sprite, u8* tiles, const u16* palette);
void    initSpriteGfx(t_sprite *sprite, u8* gfx);

#endif