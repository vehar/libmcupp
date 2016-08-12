#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __DEBUG__

#include <stdarg.h>

#define DEBUG_PRINT(...)								printf(__VA_ARGS__)
#define DEBUG_CHECK(condition, errfcn, ...)				if(condition) { DEBUG_PRINT(__VA_ARGS__); ##errfcn; }
#define DEBUG_TRY_BEGIN()								try {
#define DEBUG_TRY_END()									}
#define DEBUG_CATCH(exception, fcn)						catch(exception) { ##fcn; }
#define DEBUG_CATCH(fcn)								catch(...) { ##fcn; }

#else

#define DEBUG_PRINT(...)								
#define DEBUG_CHECK(condition, errfcn, ...)	
#define DEBUG_TRY_BEGIN()
#define DEBUG_TRY_END()
#define DEBUG_CATCH(exception, fcn)
#define DEBUG_CATCH(fcn)

#endif
