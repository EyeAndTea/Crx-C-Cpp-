//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/rings/UnsignedChar.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()

CRX__C__Ring__DEFINE(Crx_C_Rings_UnsignedChar, crx_c_rings_unsignedChar_, unsigned char,
		size_t, ((size_t)(-1)), 0, CRXM__FALSE, 
		0, CRXM__FALSE
		CRXM__FALSE, CRXM__FALSE, 
		CRXM__FALSE, CRXM__FALSE)
		
CRX__LIB__C_CODE_END()