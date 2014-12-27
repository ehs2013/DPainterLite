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