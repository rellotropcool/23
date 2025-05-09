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
