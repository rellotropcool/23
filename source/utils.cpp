#include "../include/game.h"

//n < 256 !!!
void    nget(char *dest, int n)
{
    char    buffer[256];
    int     i = 0;

    keyboardShow();
    while (1)
    {
        char c = keyboardGetChar();
        if (c == '\n' && i == 0)
            ;
        else if (c == '\n')
            break;
        else if (c == 8)
        {
            if (i > 0)
            {
                iprintf("%c", c);
                i--;
            }
        }
        else if (i < n)
        {
            iprintf("%c", c);
            buffer[i] = c;
            i++;
        }
    }
    buffer[i] = 0;
    keyboardHide();
    strncpy(dest, buffer, i + 1);
}

int initBitmapBackground(const u16* bitmap, const u16* palette) 
{
	videoSetMode(MODE_5_2D);
	vramSetBankA(VRAM_A_MAIN_BG);

	int bg = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
	dmaCopy(bitmap, bgGetGfxPtr(bg), 256 * 256);
	dmaCopy(palette, BG_PALETTE, 256 * 2);

	return bg;
}