#ifndef _D_ROOT_H
#define _D_ROOT_H

#ifdef __MINGW32__
#define _WIN32_WINNT 0x0501 // for using common dialog function in MinGW GCC
#endif

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS // for using scanf sprintf in MS CL compiler
#endif

#define SHOW_CONSOLE

#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <commdlg.h>
#include <vector>
#include <utility>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#endif
