#include "../include/main.h"

enum e_GameState GameState = INGAME;

int	main(void)
{
	consoleDemoInit();
	keyboardDemoInit();

	t_data	data;
	bzero(&data, sizeof(data));
	data.myName[0] = 0;
	t_room	rooms[5];
	roomInit(rooms);
	data.rooms = rooms;
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
			case ENDGAME:
				handleEnd(&data);
				break;
			case INGAME:
				handlePlay(&data);
				break;
		}
		swiWaitForVBlank();
	}
	return 0;
}
