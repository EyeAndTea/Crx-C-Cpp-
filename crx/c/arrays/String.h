#if(!defined(CRX__C__ARRAYS__STRING___h__))
#define CRX__C__ARRAYS__STRING___h__

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
	#define CRX__C__ARRAYS__STRING__PRIVATE__SIZE32_T uint32_t
	#define CRX__C__ARRAYS__STRING__PRIVATE__SIZE32_MAX UINT32_MAX
#else
	#ifdef SIZE_MAX
		#define CRX__C__ARRAYS__STRING__PRIVATE__SIZE32_T size_t
		#define CRX__C__ARRAYS__STRING__PRIVATE__SIZE32_MAX SIZE_MAX
	#else
		#define CRX__C__ARRAYS__STRING__PRIVATE__SIZE32_T uint32_t
		#define CRX__C__ARRAYS__STRING__PRIVATE__SIZE32_MAX ((uint32_t)(-1))
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
CRX__C__Array__DECLARE(Crx_C_Arrays_String, crx_c_arrays_string_, Crx_C_String,
		CRX__C__ARRAYS__STRING__PRIVATE__SIZE32_T, CRX__C__ARRAYS__STRING__PRIVATE__SIZE32_MAX, 0, 
		CRXM__FALSE, crx_c_string_destruct, crx_c_string_copyConstruct, 
		CRXM__FALSE, CRXM__FALSE)


CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/arrays/String.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif