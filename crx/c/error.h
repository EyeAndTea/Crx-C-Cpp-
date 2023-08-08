#if(!defined(CRX__C__ERROR___h__))
#define CRX__C__ERROR___h__

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
#include "Crx/H/crx/c/Array.h"
#include "Crx/H/crx/c/String.h"
//<<END>>
	
CRX__LIB__C_CODE_BEGIN()

#if(defined(CRX__LAN__C_99) || defined(UINT32_MAX))
	#define CRX__C__ERROR__PRIVATE__SIZE_T uint16_t
	#define CRX__C__ERROR__PRIVATE__SIZE_MAX UINT16_MAX
#else
	#define CRX__C__ERROR__PRIVATE__SIZE_T size_t
	#ifdef SIZE_MAX
		#define CRX__C__ERROR__PRIVATE__SIZE_MAX SIZE_MAX
	#else
		#define CRX__C__ERROR__PRIVATE__SIZE_MAX ((size_t)(-1))
	#endif
#endif

/*CLASS: ErrorElement*/
typedef struct Crx_C_Error_ErrorElement
{
	unsigned int gCode;
	Crx_C_String * gMessage;
}Crx_C_Error_ErrorElement;
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct(
		Crx_C_Error_ErrorElement * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct2(
		Crx_C_Error_ErrorElement * pThis, unsigned int pCode, 
		Crx_C_String const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct3(
		Crx_C_Error_ErrorElement * pThis, unsigned int pCode, char const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct4(
		Crx_C_Error_ErrorElement * pThis, unsigned int pCode, 
		char const * pChars, size_t pLength);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_copyConstruct(
		Crx_C_Error_ErrorElement * pThis, Crx_C_Error_ErrorElement const * pErrorElement);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_new();
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_new2(
		unsigned int pCode, Crx_C_String const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_new3(
		unsigned int pCode, char const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_new4(
		unsigned int pCode, char const * pChars, size_t pLength);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_copyNew(
		Crx_C_Error_ErrorElement const * pErrorElement);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_destruct(
		Crx_C_Error_ErrorElement * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_free(Crx_C_Error_ErrorElement * pThis);


/*CLASS: Error*/
CRX__C__Array__DECLARE(Crx_C_Error_Error, crx_c_error_error_, Crx_C_Error_ErrorElement, 
		CRX__C__ERROR__PRIVATE__SIZE_T, CRX__C__ERROR__PRIVATE__SIZE_MAX, 
		0, CRXM__FALSE,
		crx_c_error_errorElement_destruct, crx_c_error_errorElement_copyConstruct, CRXM__FALSE, CRXM__FALSE)

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_error_error_isError(Crx_C_Error_Error * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_pushTrace2(Crx_C_Error_Error * pThis, 
		unsigned int pCode, Crx_C_String const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_pushTrace3(Crx_C_Error_Error * pThis, 
		unsigned int pCode, char const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_pushTrace4(Crx_C_Error_Error * pThis, 
		unsigned int pCode, char const * pChars, size_t pLength);


CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/error.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif