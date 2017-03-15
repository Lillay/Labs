#include <stdlib.h>
#include "myTerm.h"

int main(int argc, char **argv)
{
	int x, y;
	mt_clrscr();
	mt_gotoXY(10, 10);
	mt_getscreensize (&x, &y);

	mt_setbgcolor(LWHITE);
	mt_setfgcolor(GREEN);

	printf("rows: %d \n", x);
	mt_setbgcolor(RED);
	mt_setfgcolor(YELLOW);
	printf("cols: %d ", y);

	return 0;
}
