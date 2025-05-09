#include "../include/handleStart.h"

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
					GameState = INGAME;
				break;
			}
		}
	}
	swiWaitForVBlank();
}