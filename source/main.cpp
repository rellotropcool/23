#include "../include/game.h"

enum e_GameState GameState = STARTING;

int	main(void)
{
	consoleDemoInit();
	keyboardDemoInit();

	t_data	data;
	bzero(&data, sizeof(data));
	data.myName[0] = 0;
    while(1)
	{
		switch (GameState)
		{
			case STARTING:
				handleStart(&data);
				break;
			case ASK_NAME:
				handleAsk(&data);
				break;
			case END:
				handleEnd(&data);
				break;
			case PLAYING:
				handlePlay(&data);
				break;
		}
		swiWaitForVBlank();
	}
	return 0;
}
