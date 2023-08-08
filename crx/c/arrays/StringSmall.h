#if(!defined(CRX__C__ARRAYS__STRING_SMALL___h__))
#define CRX__C__ARRAYS__STRING_SMALL___h__

#include <boost/version.hpp>
#include "Crx/H/crx/crx.h"
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma push_macro("CRX__LIB__MODE")
	#undef CRX__LIB__MODE
	#if(!defined(CRX__CONFIG__MODE))
		#define CRX__CONFIG__MODE CRX__LIB__MODE__STAND_ALONE
	#endif
	#define CRX__LIB__MODE CRX__CONFIG__MODE
#else
	#undef CRX__LIB__MODE
	#if(!defined(CRX__LIB__C_MODE))
		#define CRX__LIB__C_MODE CRX__LIB__MODE__STAND_ALONE
	#endif
	#define CRX__LIB__MODE CRX__LIB__C_MODE
#endif
//<<START>>	INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/nonCrxed/standard/stdint.h"
#include "Crx/H/crx/c/Array.h"
#include "Crx/H/crx/c/String.h"
//<<END>>

#if(defined(UINT32_MAX))
	#define CRX__C__ARRAYS__STRING_SMALL__PRIVATE__SIZE08_T uint8_t
	#define CRX__C__ARRAYS__STRING_SMALL__PRIVATE__SIZE08_MAX UINT8_MAX
#else
	#ifdef SIZE_MAX
		#define CRX__C__ARRAYS__STRING_SMALL__PRIVATE__SIZE08_T size_t
		#define CRX__C__ARRAYS__STRING_SMALL__PRIVATE__SIZE08_MAX SIZE_MAX
	#else
		#define CRX__C__ARRAYS__STRING_SMALL__PRIVATE__SIZE08_T uint8_t
		#define CRX__C__ARRAYS__STRING_SMALL__PRIVATE__SIZE08_MAX ((uint8_t)(-1))
	#endif
#endif
	
CRX__LIB__C_CODE_BEGIN()

/*
CONTRACT:
	IS FIXED SIZE:			1
	HAS CONSTRUCT:		 	1
	HAS DESTRUCT:		 	1
	IS COPYABLE:			1
	HAS COPY CONSTRUCT:		1
	HAS MOVE CONSTRUCT:		0
	HAS MOVE DESTRUCT:		0
*/
CRX__C__Array__DECLARE(Crx_C_Arrays_StringSmall, crx_c_arrays_stringSmall_, Crx_C_String,
		CRX__C__ARRAYS__STRING_SMALL__PRIVATE__SIZE08_T, CRX__C__ARRAYS__STRING_SMALL__PRIVATE__SIZE08_MAX, 0, 
		CRXM__FALSE, crx_c_string_destruct, crx_c_string_copyConstruct, 
		CRXM__FALSE, CRXM__FALSE)


CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/arrays/StringSmall.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif