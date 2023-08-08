#ifndef CRX__C__HTML___h__
#define CRX__C__HTML___h__

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
#include <stddef.h>
#include "Crx/H/crx/c/char.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()


/* Reference: https://bitbucket.org/cggaertner/cstuff/src/master/entities.c */
/*
	THE USE OF CRX__LIB__PRIVATE_C_CONSTANT() IS KEPT FOR TESTING PURPOSES FOR THE TIME BEING. IN 
			THE FUTURE THIS SHOULD BE MOVED TO A static VARIABLE INSIDE A FUNCTION.
*/
CRX__LIB__PRIVATE_C_CONSTANT(0) char const * const gCRX__C__HTML__NAMED_ENTITIES_TO_UTF8[253][2];
CRX__LIB__PRIVATE_C_FUNCTION() int crx_c_html_getUtf8CharFromHtmlNamedEntity__doCompare(void const * pKey, void const * pValue);
CRX__LIB__PRIVATE_C_FUNCTION() char const * crx_c_html_getUtf8CharFromHtmlNamedEntity(const char * name);
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_html_insertUtf8Character(unsigned long cp, char * buffer, size_t pAvailableLength, 
		bool * pIsNoError);
/*	
(original design)
{
	Takes input from <src> and decodes into <dest>, which should be a buffer
	large enough to hold <strlen(src) + 1> characters.

	If <src> is <NULL>, input will be taken from <dest>, decoding
	the entities in-place.

	The function returns the length of the decoded string.
}
*/
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_html_decodeHtmlEntitiesUsingUtf8(char const * pString,
		size_t pLength, char * pTarget, size_t pAvailableLength, bool * pWasSpaceSufficient);
CRX__LIB__PUBLIC_C_FUNCTION()  size_t crx_c_html_decodeUrl(char const * pSource, size_t pLength,
		char * pTarget, size_t pAvailableLength, bool * pWasSpaceSufficient);

CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/html.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif