#include "Crx_stdafx.h"
#include "Crx/H/crx/crx.h"
#if(!defined(CRX__CONFIG__MODE))
	#define CRX__CONFIG__MODE CRX__LIB__MODE__STAND_ALONE
#elif(!CRXM__IS(CRX__CONFIG__MODE, CRX__LIB__MODE__STAND_ALONE) && \
		!CRXM__IS(CRX__CONFIG__MODE, CRX__LIB__MODE__DLL_STAND_ALONE))
	#undef CRX__CONFIG__MODE
	#define CRX__CONFIG__MODE CRX__LIB__MODE__STAND_ALONE
#endif
//<<START>>	INCLUDE CORRESPONDING ".cpp.h" FILE
#include "Crx/CPP.H/crx/web/SecurityDefaultProtocol.cpp.h"
//<<END>>


//... INSTANTIATE TEMPLATES DEFINED IN THE CORRESPONDING ".cpp.h" IF DESIRED