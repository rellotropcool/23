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

bool getCollisionBit(const uint8_t *collisionMap, int i) 
{
    return (collisionMap[i / 8] >> (i % 8)) & 1;
}

void packCollisionMap(const int mapColl[1024], uint8_t *collisionMap) 
{
    for (int i = 0; i < 128; i++) 
    {
        collisionMap[i] = 0;
    }

    for (int i = 0; i < 1024; i++) 
    {
        if (mapColl[i])
            collisionMap[i / 8] |= (1 << (i % 8));
    }
}
