#include "../include/handleAsk.h"

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
				GameState = INGAME;
				return;
			}
		}
	}
}
