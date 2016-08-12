#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __DEBUG__

#include <stdarg.h>

#define DEBUG_PRINT(...)								printf(__VA_ARGS__)
#define DEBUG_CHECK(condition, errfcn, ...)				if(condition) { DEBUG_PRINT(__VA_ARGS__); ##errfcn; }

#else

#define DEBUG_PRINT(...)								
#define DEBUG_CHECK(condition, errfcn, ...)	

#endif
