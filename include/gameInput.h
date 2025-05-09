#ifndef GAMEINPUT_H
#define GAMEINPUT_H

#include "handlePlay.h"

struct s_playData;  // <-- forward declaration
typedef struct s_playData t_playData;

bool	checkColl(int x, int y, int mapColl[16][16]);
void	handleInput(t_data *data, t_playData *playData, int *playState);

#endif