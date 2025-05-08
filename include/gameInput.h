#ifndef GAMEINPUT_H
#define GAMEINPUT_H

#include "handlePlay.h"

bool	checkColl(int x, int y, int mapColl[16][16]);
bool	handleInput(t_data *data, int *x, int *y, int *targetX, int *targetY, bool moving, int mapColl[16][16], int *PlayState);

#endif