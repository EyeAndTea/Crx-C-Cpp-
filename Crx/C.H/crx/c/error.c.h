//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/error.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "Crx/H/crx/c/Array.h"
#include "Crx/H/crx/c/String.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()

/*CLASS: ErrorElement*/
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct(
		Crx_C_Error_ErrorElement * pThis)
{
	pThis->gCode = 0;
	pThis->gMessage = NULL;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct2(
		Crx_C_Error_ErrorElement * pThis, unsigned int pCode, 
		Crx_C_String const * pString)
{
	pThis->gCode = pCode;
	pThis->gMessage = crx_c_string_copyNew(pString);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct3(
		Crx_C_Error_ErrorElement * pThis, unsigned int pCode, char const * pString)
{
	pThis->gCode = pCode;
	pThis->gMessage = crx_c_string_new4(pString);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct4(
		Crx_C_Error_ErrorElement * pThis, unsigned int pCode, char const * pChars, size_t pLength)
{
	pThis->gCode = pCode;
	pThis->gMessage = crx_c_string_new5(pChars, pLength);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_copyConstruct(
		Crx_C_Error_ErrorElement * pThis, Crx_C_Error_ErrorElement const * pErrorElement)
{
	pThis->gCode = 0;
	pThis->gMessage = crx_c_string_copyNew(pErrorElement->gMessage);
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_new()
{
	Crx_C_Error_ErrorElement * vReturn = 
			((Crx_C_Error_ErrorElement *)malloc(sizeof(Crx_C_Error_ErrorElement)));

	if(vReturn != NULL)
		{crx_c_error_errorElement_construct(vReturn);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_new2(
		unsigned int pCode, Crx_C_String const * pString)
{
	Crx_C_Error_ErrorElement * vReturn = 
			((Crx_C_Error_ErrorElement *)malloc(sizeof(Crx_C_Error_ErrorElement)));

	if(vReturn != NULL)
		{crx_c_error_errorElement_construct2(vReturn, pCode, pString);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_new3(
		unsigned int pCode, char const * pString)
{
	Crx_C_Error_ErrorElement * vReturn = 
			((Crx_C_Error_ErrorElement *)malloc(sizeof(Crx_C_Error_ErrorElement)));

	if(vReturn != NULL)
		{crx_c_error_errorElement_construct3(vReturn, pCode, pString);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_new4(
		unsigned int pCode, char const * pChars, size_t pLength)
{
	Crx_C_Error_ErrorElement * vReturn = 
			((Crx_C_Error_ErrorElement *)malloc(sizeof(Crx_C_Error_ErrorElement)));

	if(vReturn != NULL)
		{crx_c_error_errorElement_construct4(vReturn, pCode, pChars, pLength);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_copyNew(
		Crx_C_Error_ErrorElement const * pErrorElement)
{
	Crx_C_Error_ErrorElement * vReturn = 
			((Crx_C_Error_ErrorElement *)malloc(sizeof(Crx_C_Error_ErrorElement)));

	if(vReturn != NULL)
		{crx_c_error_errorElement_copyConstruct(vReturn, pErrorElement);}

	return vReturn;
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_destruct(
		Crx_C_Error_ErrorElement * pThis)
{
	if(pThis->gMessage != NULL)
	{
		crx_c_string_destruct(pThis->gMessage);
		pThis->gCode = 0;
		pThis->gMessage = NULL;
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_free(Crx_C_Error_ErrorElement * pThis)
	{free(pThis);}


/*CLASS: Error*/
CRX__C__Array__DEFINE(Crx_C_Error_Error, crx_c_error_error_, Crx_C_Error_ErrorElement, 
		CRX__C__ERROR__PRIVATE__SIZE_T, CRX__C__ERROR__PRIVATE__SIZE_MAX, 
		0, CRXM__FALSE,
		crx_c_error_errorElement_destruct, crx_c_error_errorElement_copyConstruct, CRXM__FALSE, CRXM__FALSE)

extern bool crx_c_error_error_isError(Crx_C_Error_Error * pThis)
	{return (crx_c_error_error_getLength(pThis) != 0);}
extern void crx_c_error_error_pushTrace2(Crx_C_Error_Error * pThis, unsigned int pCode, 
		Crx_C_String const * pString)
{
	Crx_C_Error_ErrorElement vErrorElement;
	
	crx_c_error_errorElement_construct2(&vErrorElement, pCode, pString);

	if(!crx_c_error_error_tryMoveAndPush(pThis, &vErrorElement))
		{crx_c_error_errorElement_destruct(&vErrorElement);}
}
extern void crx_c_error_error_pushTrace3(Crx_C_Error_Error * pThis, unsigned int pCode, 
		char const * pString)
{
	Crx_C_Error_ErrorElement vErrorElement;
	
	crx_c_error_errorElement_construct3(&vErrorElement, pCode, pString);

	if(!crx_c_error_error_tryMoveAndPush(pThis, &vErrorElement))
		{crx_c_error_errorElement_destruct(&vErrorElement);}
}
extern void crx_c_error_error_pushTrace4(Crx_C_Error_Error * pThis, unsigned int pCode, 
		char const * pChars, size_t pLength)
{
	Crx_C_Error_ErrorElement vErrorElement;
	
	crx_c_error_errorElement_construct4(&vErrorElement, pCode, pChars, pLength);

	if(!crx_c_error_error_tryMoveAndPush(pThis, &vErrorElement))
		{crx_c_error_errorElement_destruct(&vErrorElement);}
}


#undef CRX__C__ERROR__PRIVATE__SIZE_T
#undef CRX__C__ERROR__PRIVATE__SIZE_MAX


CRX__LIB__C_CODE_END()

