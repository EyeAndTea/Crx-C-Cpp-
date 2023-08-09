#include "Crx_stdafx.h"
#include "Crx/H/crx/crx.h"
#if(!defined(CRX__CONFIG__MODE))
	#define CRX__CONFIG__MODE CRX__LIB__MODE__STAND_ALONE
#elif(!CRXM__IS(CRX__CONFIG__MODE, CRX__LIB__MODE__STAND_ALONE) && \
		!CRXM__IS(CRX__CONFIG__MODE, CRX__LIB__MODE__DLL_STAND_ALONE))
	#undef CRX__CONFIG__MODE
	#define CRX__CONFIG__MODE CRX__LIB__MODE__STAND_ALONE
#endif
#if(!defined(CRX__LIB__C_MODE))
	#define CRX__LIB__C_MODE CRX__LIB__MODE__STAND_ALONE
#elif(!CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__STAND_ALONE) && \
		!CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__DLL_STAND_ALONE))
	#undef CRX__LIB__C_MODE
	#define CRX__LIB__C_MODE CRX__LIB__MODE__STAND_ALONE
#endif
//<<START>>	INCLUDE CORRESPONDING ".c.h" FILE
#include "Crx/C.H/crx/c/random/MersenneTwister.c.h"
//<<END>>