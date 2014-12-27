#ifndef _D_WINAPI_H
#define _D_WINAPI_H


#include "pubinc.h"

BOOL get_open_filename(char filename[], const char * filetype = "drw", char filetitle[] = NULL);
BOOL get_save_filename(char filename[], const char * filetype = "drw");
color_t get_color(void);

#endif