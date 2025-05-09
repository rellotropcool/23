#ifndef UTILS_H
#define UTILS_H

void    nget(char *dest, int n);
bool getCollisionBit(const uint8_t *collisionMap, int i);
void packCollisionMap(const int mapColl[1024], uint8_t *collisionMap);

#endif