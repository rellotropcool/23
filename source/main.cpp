#include "../include/game.h"

enum e_GameState GameState = PLAYING;

int	main(void)
{
	consoleDemoInit();
	keyboardDemoInit();

	videoSetMode(MODE_5_2D);

	t_data	data;
	bzero(&data, sizeof(data));
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
