#ifndef MYTERM_H
#define MYTERM_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

enum colors {GRAY = 0, RED = 1, GREEN = 2, YELLOW = 3, BLUE = 4, PURPLE = 5, TURQUO = 6, WHITE = 7,
	LGRAY = 8, LRED = 9, LGREEN = 10, LYELLOW = 11, LBLUE = 12, LPURPLE = 13, LTURQUO = 14, LWHITE = 15, BLACK = 16, DEF = 300};

int mt_clrscr (void);
int mt_gotoXY (int x, int y);
int mt_getscreensize (int * rows, int * cols);
int mt_setfgcolor (enum colors color);
int mt_setbgcolor (enum colors color);

#endif
