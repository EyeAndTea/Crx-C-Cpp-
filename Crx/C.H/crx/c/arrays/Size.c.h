//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/arrays/Size.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()

CRX__C__Array__DEFINE(Crx_C_Arrays_Size, crx_c_arrays_size_, size_t,
		size_t, ((size_t)(-1)), 4, CRXM__FALSE, 
		CRXM__FALSE, CRXM__FALSE, 
		CRXM__FALSE, CRXM__FALSE)
		
CRX__LIB__C_CODE_END()