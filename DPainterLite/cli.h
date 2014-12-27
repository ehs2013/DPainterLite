#ifndef _D_CLI_H
#define _D_CLI_H

#include "pubinc.h"
#include "gui.h"
#include "types.h"
#include "draw.h"
#include "winapi.h"
#include "file.h"

void cli(void);
int entrance(void);

void new_file(void);
void open_file(void);
void show_copyright(void);

void do_file(void);
int file_operation_select(void);

void draw_line(void);
void draw_circle(void);
void draw_rectangle(void);
void draw_ellipse(void);
void draw_polygon(void);
void save(void);

#endif