#ifndef _D_FILE_H
#define _D_FILE_H

#include "pubinc.h"
#include "types.h"
#include "winapi.h"
#include "draw.h"

void writejson(CIRCLE);
void writejson(RECTANGLE);
void writejson(ELLIPSE);
void writejson(LINE);
void writejson(PCIRCLE);
void writejson(PRECTANGLE);
void writejson(PELLIPSE);
void writejson(PLINE);
void writejson(POLYGON);
void writejson(PPOLYGON);
void writejson(SHAPE);
void writejson(PSHAPE);

void finalwrite(void);
void readjson(void);
void readcircle(rapidjson::Value&);
void readline(rapidjson::Value&);
void readrectangle(rapidjson::Value&);
void readellipse(rapidjson::Value&);
void readpolygon(rapidjson::Value&);

#endif