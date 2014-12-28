#ifndef _D_TYPES_H
#define _D_TYPES_H

#include "pubinc.h"

#define FILL 0x01
#define BORDER 0x02

#define SHAPE_CIRCLE 1
#define SHAPE_RECTANGLE 2
#define SHAPE_ELLIPSE 3
#define SHAPE_LINE 4
#define SHAPE_POLYGON 5

typedef struct {
	int x;
	int y;
	int radius;
	int drawmode;
	int borderwidth;
	color_t bordercolor;
	color_t fillcolor;
} CIRCLE;
typedef CIRCLE *PCIRCLE;

typedef struct {
	int left;
	int top;
	int right;
	int bottom;
	int drawmode;
	int borderwidth;
	color_t bordercolor;
	color_t fillcolor;
} RECTANGLE;
typedef RECTANGLE *PRECTANGLE;

typedef struct {
	int x;
	int y;
	int xradius;
	int yradius;
	int drawmode;
	int borderwidth;
	color_t bordercolor;
	color_t fillcolor;
} ELLIPSE;
typedef ELLIPSE *PELLIPSE;

typedef struct {
	int x1;
	int y1;
	int x2;
	int y2;
	int width;
	color_t color;
} LINE;
typedef LINE *PLINE;

typedef struct {
	int type;
	void * shape;
} SHAPE;
typedef SHAPE *PSHAPE;

typedef struct {
	std::vector<std::pair<int, int>> points;
	int drawmode;
	int borderwidth;
	color_t bordercolor;
	color_t fillcolor;
} POLYGON;
typedef POLYGON *PPOLYGON;

#endif