/* 7zMain.c - Test application for 7z Decoder
2021-04-29 : Igor Pavlov : Public domain */

#include "7zAlloc.h"

static const ISzAlloc g_Alloc = { SzAlloc, SzFree };
