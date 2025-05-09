#include "../include/handleEnd.h"

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