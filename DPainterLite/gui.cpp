#include "gui.h"
extern char filename[255];
extern char filetitle[50];

void initpad(void) {
	initgraph(900, 600);
	if (filename[0] == '\0') {
		setcaption("Untitled - Graph Window - DPainter Lite");
	} else {
		char title[70];
		sprintf(title, "%s - Graph Window - DPainter Lite", filetitle);
		setcaption(title);
	}
	setbkcolor(WHITE);
	setcolor(BLUE);
	setfillcolor(BLUE);
	SetForegroundWindow(GetConsoleWindow());
}

void get_coordinate(int &x, int &y, bool* stop) {
	SetForegroundWindow(getHWnd());
	mouse_msg c;
	while (true) {
		c = getmouse();
		if (c.is_left() && c.is_down()) {
			x = c.x;
			y = c.y;
			if (stop != NULL) {
				*stop = false;
			}
			SetForegroundWindow(GetConsoleWindow());
			return;
		} else if (c.is_right() && c.is_down() && (stop != NULL)) {
			*stop = true;
			SetForegroundWindow(GetConsoleWindow());
			return;
		}
	}
}