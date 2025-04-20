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
	pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__UNSET;
	pThis->gSpace = 0;
	pThis->gCode = 0;
	pThis->uPrivate_string.gCString = NULL;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct2(
		Crx_C_Error_ErrorElement * pThis, uint32_t pCode, 
		Crx_C_String const * pString)
{
	pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING;
	pThis->gCode = pCode;
	pThis->uPrivate_string.gString = crx_c_string_copyNew(pString);

	if(pThis->uPrivate_string.gString == NULL)
	{
		pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING;
		pThis->uPrivate_string.gCString = NULL;
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct3(
		Crx_C_Error_ErrorElement * pThis, uint32_t pCode, char const * pCString,
		bool pIsCStringAPermanentConstant)
{
	pThis->gCode = pCode;

	if(!pIsCStringAPermanentConstant)
	{
		pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING;
		pThis->uPrivate_string.gString = crx_c_string_new2(pCString);

		if(pThis->uPrivate_string.gString == NULL)
		{
			pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING;
			pThis->uPrivate_string.gCString = NULL;
		}
	}
	else
	{
		pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING;
		pThis->uPrivate_string.gCString = pCString;
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_construct4(
		Crx_C_Error_ErrorElement * pThis, uint32_t pCode, char const * pChars, size_t pLength)
{
	pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING;
	pThis->gCode = pCode;
	pThis->uPrivate_string.gString = crx_c_string_new3(pChars, pLength);

	if(pThis->uPrivate_string.gString == NULL)
	{
		pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING;
		pThis->uPrivate_string.gCString = NULL;
	}
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_error_errorElement_private_takeStringAndConstruct(
		Crx_C_Error_ErrorElement * pThis, uint16_t pSpace, uint32_t pCode, 
		Crx_C_String * pString)
{
	pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING;
	pThis->gSpace = pSpace;
	pThis->gCode = pCode;
	pThis->uPrivate_string.gString = pString;
	
	if(pThis->uPrivate_string.gString == NULL)
	{
		pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING;
		pThis->uPrivate_string.gCString = NULL;
	}
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_error_errorElement_private_takeCStringAndConstruct(
		Crx_C_Error_ErrorElement * pThis, uint16_t pSpace, uint32_t pCode, char const * pCString)
{
	pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING;
	pThis->gSpace = pSpace;
	pThis->gCode = pCode;
	pThis->uPrivate_string.gCString = pCString;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_copyConstruct(
		Crx_C_Error_ErrorElement * pThis, Crx_C_Error_ErrorElement const * pErrorElement)
{
	pThis->gPrivate_internalMode = pErrorElement->gPrivate_internalMode;
	pThis->gCode = pErrorElement->gCode;

	if(pErrorElement->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING)
		{pThis->uPrivate_string.gCString = pErrorElement->uPrivate_string.gCString;}
	else if(pErrorElement->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING)
	{
		if(pErrorElement->uPrivate_string.gString != NULL)
		{
			pThis->uPrivate_string.gString = crx_c_string_copyNew(
					pErrorElement->uPrivate_string.gString);
		}
		else
			{pThis->uPrivate_string.gString = NULL;}
		
		if(pThis->uPrivate_string.gString == NULL)
		{
			pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING;
			pThis->uPrivate_string.gCString = NULL;
		}
	}
	else
		{pThis->uPrivate_string.gCString = NULL;}
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
		uint32_t pCode, Crx_C_String const * pString)
{
	Crx_C_Error_ErrorElement * vReturn = 
			((Crx_C_Error_ErrorElement *)malloc(sizeof(Crx_C_Error_ErrorElement)));

	if(vReturn != NULL)
		{crx_c_error_errorElement_construct2(vReturn, pCode, pString);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_new3(
		uint32_t pCode, char const * pCString, bool pIsCStringAPermanentConstant)
{
	Crx_C_Error_ErrorElement * vReturn = 
			((Crx_C_Error_ErrorElement *)malloc(sizeof(Crx_C_Error_ErrorElement)));

	if(vReturn != NULL)
	{
		crx_c_error_errorElement_construct3(vReturn, pCode, pCString, 
				pIsCStringAPermanentConstant);
	}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_new4(
		uint32_t pCode, char const * pChars, size_t pLength)
{
	Crx_C_Error_ErrorElement * vReturn = 
			((Crx_C_Error_ErrorElement *)malloc(sizeof(Crx_C_Error_ErrorElement)));

	if(vReturn != NULL)
		{crx_c_error_errorElement_construct4(vReturn, pCode, pChars, pLength);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_moveNew(
		Crx_C_Error_ErrorElement * CRX_NOT_NULL pErrorElement)
{
	Crx_C_Error_ErrorElement * vReturn = 
			((Crx_C_Error_ErrorElement *)malloc(sizeof(Crx_C_Error_ErrorElement)));

	if(vReturn != NULL)
		{memcpy(vReturn, pErrorElement, sizeof(Crx_C_Error_ErrorElement));}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_ErrorElement * crx_c_error_errorElement_copyNew(
		Crx_C_Error_ErrorElement const * CRX_NOT_NULL pErrorElement)
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
	if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING)
	{
		if(pThis->uPrivate_string.gString != NULL)
		{
			crx_c_string_destruct(pThis->uPrivate_string.gString);
			crx_c_string_free(pThis->uPrivate_string.gString);
			pThis->uPrivate_string.gString = NULL;
			pThis->gCode = 0;
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_errorElement_free(Crx_C_Error_ErrorElement * pThis)
	{free(pThis);}
	
CRX__LIB__PUBLIC_C_FUNCTION() char const * crx_c_error_errorElement_getMessage(
		Crx_C_Error_ErrorElement const * pThis)
{
	if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__UNSET)
		{return NULL;}
	else if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING)
		{return pThis->uPrivate_string.gCString;}
	//REMEMBER: ErrorElement::uPrivate_string.gString IS ENSURED TO BE NULL CHARACTER TERMINATED AND
	//		NEVER NULL.
	else if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING)
		{return crx_c_string_constantGetCharsPointer(pThis->uPrivate_string.gString);}
	else
		{assert(false); return NULL;}
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_error_errorElement_private_unsafeUnsetMessage(
		Crx_C_Error_ErrorElement * pThis)
	{pThis->uPrivate_string.gCString = NULL;}

/*CLASS: Error*/
/*CRX__C__Array__DEFINE(Crx_C_Error_Error, crx_c_error_error_private_trail_, Crx_C_Error_ErrorElement, 
		CRX__C__ERROR__PRIVATE__SIZE_T, CRX__C__ERROR__PRIVATE__SIZE_MAX, 
		0, CRXM__FALSE,
		crx_c_error_errorElement_destruct, crx_c_error_errorElement_copyConstruct, CRXM__FALSE, CRXM__FALSE)*/
CRX__C__Queue__DEFINE(Crx_C_Error_Error_Private_Trail, crx_c_error_error_private_trail_,
		CRX__C__QUEUE__MODE__BIDIRECTIONAL, 8, CRXM__FALSE,
		Crx_C_Error_ErrorElement, crx_c_error_errorElement_destruct,
		crx_c_error_errorElement_copyConstruct,
		CRXM__FALSE, CRXM__FALSE)
		
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_construct(
		Crx_C_Error_Error * pThis, uint32_t pMode)
{
	pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__UNSET;
	pThis->gPrivate_mode = pMode;
	pThis->gPrivate_space = 0;
	pThis->gPrivate_code = 0;
	pThis->uPrivate_data.gCString = NULL;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_copyConstruct(
		Crx_C_Error_Error * pThis, Crx_C_Error_Error const * pError)
{
	pThis->gPrivate_internalMode = pError->gPrivate_internalMode;
	pThis->gPrivate_mode = pError->gPrivate_mode;
	pThis->gPrivate_space = pError->gPrivate_space;
	pThis->gPrivate_code = pError->gPrivate_code;
	
	if(pError->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING)
		{pThis->uPrivate_data.gCString = pError->uPrivate_data.gCString;}
	else if(pError->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING)
	{
		if(pError->uPrivate_data.gString != NULL)
			{pThis->uPrivate_data.gString = crx_c_string_copyNew(pError->uPrivate_data.gString);}
	}
	else if(pError->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_TRAIL)
	{
		if(pError->uPrivate_data.gTrail != NULL)
		{
			pThis->uPrivate_data.gTrail = crx_c_error_error_private_trail_copyNew(
					pError->uPrivate_data.gTrail);
		}
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Error * crx_c_error_error_new(uint32_t pMode)
{
	Crx_C_Error_Error * vReturn = 
			((Crx_C_Error_Error *)malloc(sizeof(Crx_C_Error_Error)));

	if(vReturn != NULL)
		{crx_c_error_error_construct(vReturn, pMode);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Error * crx_c_error_error_moveNew(
		Crx_C_Error_Error * pError)
{
	Crx_C_Error_Error * vReturn = 
			((Crx_C_Error_Error *)malloc(sizeof(Crx_C_Error_Error)));

	if(vReturn != NULL)
		{memcpy(vReturn, pError, sizeof(Crx_C_Error_Error));}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Error * crx_c_error_error_copyNew(
		Crx_C_Error_Error const * pError)
{
	Crx_C_Error_Error * vReturn = 
			((Crx_C_Error_Error *)malloc(sizeof(Crx_C_Error_Error)));

	if(vReturn != NULL)
		{crx_c_error_error_copyConstruct(vReturn, pError);}

	return vReturn;
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_destruct(
		Crx_C_Error_Error const * pThis)
{
	if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING)
	{
		if(pThis->uPrivate_data.gString != NULL)
		{
			crx_c_string_destruct(pThis->uPrivate_data.gString);
			crx_c_string_free(pThis->uPrivate_data.gString);
		}
	}
	else if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_TRAIL)
	{
		crx_c_error_error_private_trail_destruct(pThis->uPrivate_data.gTrail);
		crx_c_error_error_private_trail_free(pThis->uPrivate_data.gTrail);
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_error_error_isError(Crx_C_Error_Error * pThis)
	{return (pThis->gPrivate_internalMode != CRX__C__ERROR__PRIVATE__INTERNAL_MODE__UNSET);}
CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_error_error_private_prepareTrace(
		Crx_C_Error_Error * pThis)
{
	assert(pThis->gPrivate_mode == CRX__C__ERROR__MODE__TRACE);

	if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__UNSET)
	{
		pThis->uPrivate_data.gTrail = crx_c_error_error_private_trail_new();

		if(pThis->uPrivate_data.gTrail != NULL)
			{pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_TRAIL;}
	}
	else if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_TRAIL)
		{assert(pThis->uPrivate_data.gTrail != NULL);}
	else
	{
		CRX_SCOPE_META
		assert((pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING) || 
				(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING));

		CRX_SCOPE
		Crx_C_Error_Error_Private_Trail * tTrail = crx_c_error_error_private_trail_new();

		if(tTrail != NULL)
		{
			Crx_C_Error_ErrorElement tErrorElement;

			if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING)
			{
				crx_c_error_errorElement_private_takeCStringAndConstruct(&tErrorElement, 
						pThis->gPrivate_space, pThis->gPrivate_code, pThis->uPrivate_data.gCString);
				pThis->uPrivate_data.gCString == NULL;
			}
			else
			{
				crx_c_error_errorElement_private_takeStringAndConstruct(&tErrorElement, 
						pThis->gPrivate_space, pThis->gPrivate_code, pThis->uPrivate_data.gString);
				pThis->uPrivate_data.gString == NULL;
			}

			if(!crx_c_error_error_private_trail_tryMoveAndPush(tTrail, &tErrorElement))
			{
				crx_c_error_errorElement_private_unsafeUnsetMessage(&tErrorElement);
				crx_c_error_errorElement_destruct(&tErrorElement);
				
				crx_c_error_error_private_trail_destruct(tTrail);
				crx_c_error_error_private_trail_free(tTrail);
			}
			else
			{
				pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_TRAIL;
				pThis->uPrivate_data.gTrail = tTrail;
			}

			tTrail = NULL;
		}

		CRX_SCOPE_END
	}

	return (pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_TRAIL);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_private_doPushTrace(
		Crx_C_Error_Error * pThis, 
		uint32_t pCode, char const * pChars, size_t pLength)
{
	pThis->gPrivate_space = 0;
	pThis->gPrivate_code = pCode;

	if(pThis->gPrivate_mode == CRX__C__ERROR__MODE__TRACE)
	{
		if(crx_c_error_error_private_prepareTrace(pThis))
		{
			Crx_C_Error_ErrorElement tErrorElement;
			
			crx_c_error_errorElement_construct4(&tErrorElement, pCode, pChars, pLength);

			if((crx_c_error_error_private_trail_getLength(pThis->uPrivate_data.gTrail) > 32766) || 
					!crx_c_error_error_private_trail_tryMoveAndPush(pThis->uPrivate_data.gTrail, 
					&tErrorElement))
			{
				if(crx_c_error_error_private_trail_getLength(pThis->uPrivate_data.gTrail) > 0)
				{
					//crx_c_error_error_private_trail_removeElements(pThis->uPrivate_data.gTrail, 0, 1);
					crx_c_error_error_private_trail_popFromFront(pThis->uPrivate_data.gTrail);

					while(!crx_c_error_error_private_trail_tryMoveAndPush(
							pThis->uPrivate_data.gTrail, &tErrorElement) &&
							(crx_c_error_error_private_trail_getLength(
							pThis->uPrivate_data.gTrail) > 0))
						{crx_c_error_error_private_trail_popFromFront(pThis->uPrivate_data.gTrail);}
				}

				if(crx_c_error_error_private_trail_getLength(pThis->uPrivate_data.gTrail) == 0)
				{
					crx_c_error_error_private_trail_destruct(pThis->uPrivate_data.gTrail);
					crx_c_error_error_private_trail_free(pThis->uPrivate_data.gTrail);
					pThis->uPrivate_data.gTrail = NULL;
					pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__UNSET;
					crx_c_error_errorElement_destruct(&tErrorElement);
				}
			}
		}
	}

	if(pThis->gPrivate_internalMode != CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_TRAIL)
	{
		if((pThis->gPrivate_mode != CRX__C__ERROR__MODE__SINGULAR_AND_NO_HEAP) &&
				(pThis->gPrivate_internalMode != CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING))
		{
			pThis->uPrivate_data.gString = crx_c_string_new();

			if(pThis->uPrivate_data.gString != NULL)
				{pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING;}
		}

		if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING)
		{
			crx_c_string_empty(pThis->uPrivate_data.gString);

			if(pChars != NULL)
				{crx_c_string_appendChars(pThis->uPrivate_data.gString, pChars, pLength);}
		}
		else
		{
			assert((pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__UNSET) ||
					(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING));

			pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING;
			pThis->uPrivate_data.gCString = NULL;
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_pushTrace2(Crx_C_Error_Error * pThis, 
		uint32_t pCode, Crx_C_String const * pString)
{
	crx_c_error_error_private_doPushTrace(pThis, pCode, 
			crx_c_string_constantGetCharsPointer(pString), crx_c_string_getSize(pString));
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_pushTrace3(Crx_C_Error_Error * pThis, 
		uint32_t pCode, char const * pCString, bool pIsCStringAPermanentConstant)
{
	if(!pIsCStringAPermanentConstant)
		{crx_c_error_error_private_doPushTrace(pThis, pCode, pCString, strlen(pCString));}
	else
	{
		pThis->gPrivate_space = 0;
		pThis->gPrivate_code = pCode;

		if(pThis->gPrivate_mode == CRX__C__ERROR__MODE__TRACE)
		{
			if(crx_c_error_error_private_prepareTrace(pThis))
			{
				Crx_C_Error_ErrorElement tErrorElement;
			
				crx_c_error_errorElement_construct3(&tErrorElement, pCode, pCString, true);

				if((crx_c_error_error_private_trail_getLength(pThis->uPrivate_data.gTrail) > 32766) || 
						!crx_c_error_error_private_trail_tryMoveAndPush(pThis->uPrivate_data.gTrail, 
						&tErrorElement))
				{
					if(crx_c_error_error_private_trail_getLength(pThis->uPrivate_data.gTrail) > 0)
					{
						//crx_c_error_error_private_trail_removeElements(pThis->uPrivate_data.gTrail, 0, 1);
						crx_c_error_error_private_trail_popFromFront(pThis->uPrivate_data.gTrail);

						while(!crx_c_error_error_private_trail_tryMoveAndPush(
								pThis->uPrivate_data.gTrail, &tErrorElement) &&
								(crx_c_error_error_private_trail_getLength(
								pThis->uPrivate_data.gTrail) > 0))
						{
							crx_c_error_error_private_trail_popFromFront(
									pThis->uPrivate_data.gTrail);
						}
					}

					if(crx_c_error_error_private_trail_getLength(pThis->uPrivate_data.gTrail) == 0)
					{
						crx_c_error_error_private_trail_destruct(pThis->uPrivate_data.gTrail);
						crx_c_error_error_private_trail_free(pThis->uPrivate_data.gTrail);
						pThis->uPrivate_data.gTrail = NULL;
						pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__UNSET;
						crx_c_error_errorElement_destruct(&tErrorElement);
					}
				}
			}
		}

		if(pThis->gPrivate_internalMode != CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_TRAIL)
		{
			if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING)
			{
				if(pThis->uPrivate_data.gString != NULL)
				{
					crx_c_string_destruct(pThis->uPrivate_data.gString);
					crx_c_string_free(pThis->uPrivate_data.gString);
					pThis->uPrivate_data.gString = NULL;
				}
			}

			pThis->uPrivate_data.gCString = pCString;
			pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING;
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_pushTrace4(Crx_C_Error_Error * pThis, 
		uint32_t pCode, char const * pChars, size_t pLength)
	{crx_c_error_error_private_doPushTrace(pThis, pCode, pChars, pLength);}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_error_clear(Crx_C_Error_Error * pThis)
{
	if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__UNSET)
		{return;}

	if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING)
		{pThis->uPrivate_data.gCString = NULL;}	
	else if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING)
	{
		if(pThis->uPrivate_data.gString != NULL)
		{
			crx_c_string_destruct(pThis->uPrivate_data.gString);
			crx_c_string_free(pThis->uPrivate_data.gString);
			pThis->uPrivate_data.gString = NULL;
		}
	}
	else if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_TRAIL)
	{
		assert(pThis->uPrivate_data.gTrail != NULL);

		crx_c_error_error_private_trail_destruct(pThis->uPrivate_data.gTrail);
		crx_c_error_error_private_trail_free(pThis->uPrivate_data.gTrail);
		pThis->uPrivate_data.gTrail = NULL;
	}

	pThis->gPrivate_internalMode = CRX__C__ERROR__PRIVATE__INTERNAL_MODE__UNSET;
}

CRX__LIB__PUBLIC_C_FUNCTION() uint16_t crx_c_error_error_getSpaceId(Crx_C_Error_Error * pThis)
{
	if(pThis->gPrivate_internalMode != CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_TRAIL)
		{return pThis->gPrivate_space;}	
	else
	{
		Crx_C_Error_ErrorElement * tErrorElement = crx_c_error_error_private_trail_get(
				pThis->uPrivate_data.gTrail);

		return tErrorElement->gSpace;
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() int32_t crx_c_error_error_getCode(Crx_C_Error_Error * pThis)
{
	if(pThis->gPrivate_internalMode != CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_TRAIL)
		{return pThis->gPrivate_code;}	
	else
	{
		Crx_C_Error_ErrorElement * tErrorElement = crx_c_error_error_private_trail_get(
				pThis->uPrivate_data.gTrail);

		return tErrorElement->gCode;
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() char const * crx_c_error_error_getMessage(Crx_C_Error_Error * pThis)
{
	if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__UNSET)
		{return NULL;}
	else if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_CSTRING)
		{return pThis->uPrivate_data.gCString;}
	//REMEMBER: ErrorElement::uPrivate_string.gString IS ENSURED TO BE NULL CHARACTER TERMINATED.
	else if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_STRING)
	{
		if(pThis->uPrivate_data.gString != NULL)
			{return crx_c_string_constantGetCharsPointer(pThis->uPrivate_data.gString);}
		else
			{return NULL;}
	}
	else if(pThis->gPrivate_internalMode == CRX__C__ERROR__PRIVATE__INTERNAL_MODE__SET_WITH_TRAIL)
	{
		Crx_C_Error_ErrorElement * tErrorElement = crx_c_error_error_private_trail_get(
				pThis->uPrivate_data.gTrail);

		return crx_c_error_errorElement_getMessage(tErrorElement);
	}
	else
		{assert(false); return NULL;}
}



CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_construct(Crx_C_Error_Iterator * pThis,
		Crx_C_Error_Error * pError)
	{_crx_c_error_iterator_construct(pThis, false, pError);}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_construct2(Crx_C_Error_Iterator * pThis,
		Crx_C_Error_Error const * pError)
	{_crx_c_error_iterator_construct(pThis, true, (Crx_C_Error_Error *)pError);}
CRX__LIB__PRIVATE_C_FUNCTION() void _crx_c_error_iterator_construct(Crx_C_Error_Iterator * pThis,
		bool pIsConstant, Crx_C_Error_Error * pError)
{
	pThis->gPrivate_internalMode = 2;
	pThis->gPrivate_isConstant = pIsConstant;
	pThis->gPrivate_error = pError;
	
	if((pError != NULL) && (pError->gPrivate_internalMode == 3))
	{
		if(pIsConstant)
		{
			crx_c_error_error_private_trail_iterator_construct2(&(pThis->gPrivate_iterator), 
					pError->uPrivate_data.gTrail);
		}
		else
		{
			crx_c_error_error_private_trail_iterator_construct(&(pThis->gPrivate_iterator), 
					pError->uPrivate_data.gTrail);
		}
	}
	else
	{
		if(pIsConstant)
		{
			crx_c_error_error_private_trail_iterator_construct2(&(pThis->gPrivate_iterator), 
					NULL);
		}
		else
		{
			crx_c_error_error_private_trail_iterator_construct(&(pThis->gPrivate_iterator), 
					NULL);
		}
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Iterator * crx_c_error_iterator_new(
		Crx_C_Error_Error * pError)
{
	Crx_C_Error_Iterator * vReturn = 
			((Crx_C_Error_Iterator *)malloc(sizeof(Crx_C_Error_Iterator)));

	if(vReturn != NULL)
		{crx_c_error_iterator_construct(vReturn, pError);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Iterator * crx_c_error_iterator_new2(
		Crx_C_Error_Error const * pError)
{
	Crx_C_Error_Iterator * vReturn = 
			((Crx_C_Error_Iterator *)malloc(sizeof(Crx_C_Error_Iterator)));

	if(vReturn != NULL)
		{crx_c_error_iterator_construct2(vReturn, pError);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Iterator * crx_c_error_iterator_moveNew(
		Crx_C_Error_Iterator * pIterator)
{
	Crx_C_Error_Iterator * vReturn = 
			((Crx_C_Error_Iterator *)malloc(sizeof(Crx_C_Error_Iterator)));

	if(vReturn != NULL)
		{memcpy(vReturn, pIterator, sizeof(Crx_C_Error_Iterator));}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Error_Iterator * crx_c_error_iterator_copyNew(
		Crx_C_Error_Iterator const * pIterator)
{
	Crx_C_Error_Iterator * vReturn = 
			((Crx_C_Error_Iterator *)malloc(sizeof(Crx_C_Error_Iterator)));

	if(vReturn != NULL)
		{memcpy(vReturn, pIterator, sizeof(Crx_C_Error_Iterator));}

	return vReturn;
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_free(Crx_C_Error_Iterator * pThis)
	{free(pThis);}
	
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_associateWith(Crx_C_Error_Iterator * pThis,
		Crx_C_Error_Error * pError)
	{crx_c_error_iterator_private_doAssociateWith(pThis, false, pError);}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_constantAssociateWith(
		Crx_C_Error_Iterator * pThis, bool pIsConstant,
		Crx_C_Error_Error const * pError)
	{crx_c_error_iterator_private_doAssociateWith(pThis, true, pError);}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_error_iterator_private_doAssociateWith(
		Crx_C_Error_Iterator * pThis, bool pIsConstant, Crx_C_Error_Error const * pError)
{
	pThis->gPrivate_internalMode = 2;
	pThis->gPrivate_isConstant = pIsConstant;
	pThis->gPrivate_error = ((Crx_C_Error_Error *)pError);
	
	if((pError != NULL) && (pError->gPrivate_internalMode == 3))
	{
		if(pIsConstant)
		{
			crx_c_error_error_private_trail_iterator_constantAssociateWith(
					&(pThis->gPrivate_iterator), pError->uPrivate_data.gTrail);
		}
		else
		{
			crx_c_error_error_private_trail_iterator_associateWith(&(pThis->gPrivate_iterator), 
					pError->uPrivate_data.gTrail);
		}
	}
	else
	{
		if(pIsConstant)
		{
			crx_c_error_error_private_trail_iterator_constantAssociateWith(
					&(pThis->gPrivate_iterator), NULL);
		}
		else
		{
			crx_c_error_error_private_trail_iterator_associateWith(&(pThis->gPrivate_iterator), 
					NULL);
		}
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_reset(Crx_C_Error_Iterator * pThis)
{
	if((pThis->gPrivate_error == NULL) || (pThis->gPrivate_error->gPrivate_internalMode == 0))
		{pThis->gPrivate_internalMode = 2;}
	else
	{
		if((pThis->gPrivate_error->gPrivate_internalMode == 1) || 
				(pThis->gPrivate_error->gPrivate_internalMode == 2))
			{pThis->gPrivate_internalMode = 0;}
		else
		{
			assert(pThis->gPrivate_error->gPrivate_internalMode == 3);

			crx_c_error_error_private_trail_iterator_reset(&(pThis->gPrivate_iterator));
			pThis->gPrivate_internalMode = 3;
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_resetToBack(
		Crx_C_Error_Iterator * pThis)
{
	if((pThis->gPrivate_error == NULL) || (pThis->gPrivate_error->gPrivate_internalMode == 0))
		{pThis->gPrivate_internalMode = 2;}
	else
	{
		if((pThis->gPrivate_error->gPrivate_internalMode == 1) || 
				(pThis->gPrivate_error->gPrivate_internalMode == 2))
			{pThis->gPrivate_internalMode = 1;}
		else
		{
			assert(pThis->gPrivate_error->gPrivate_internalMode == 3);

			crx_c_error_error_private_trail_iterator_resetToBack(&(pThis->gPrivate_iterator));
			pThis->gPrivate_internalMode = 3;
		}
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_next(Crx_C_Error_Iterator * pThis)
{
	if(pThis->gPrivate_internalMode == 2)
		{return;}
	else if(pThis->gPrivate_internalMode == 3)
	{
		crx_c_error_error_private_trail_iterator_next(&(pThis->gPrivate_iterator));

		if(!crx_c_error_error_private_trail_iterator_isValid(&(pThis->gPrivate_iterator)))
			{pThis->gPrivate_internalMode = 2;}
	}
	else
	{
		assert((pThis->gPrivate_error->gPrivate_internalMode == 0) || 
				(pThis->gPrivate_error->gPrivate_internalMode == 1));

		pThis->gPrivate_internalMode = 2;
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_error_iterator_prev(Crx_C_Error_Iterator * pThis)
{
	if(pThis->gPrivate_internalMode == 2)
		{return;}
	else if(pThis->gPrivate_internalMode == 3)
	{
		crx_c_error_error_private_trail_iterator_prev(&(pThis->gPrivate_iterator));

		if(!crx_c_error_error_private_trail_iterator_isValid(&(pThis->gPrivate_iterator)))
			{pThis->gPrivate_internalMode = 2;}
	}
	else
	{
		assert((pThis->gPrivate_error->gPrivate_internalMode == 0) || 
				(pThis->gPrivate_error->gPrivate_internalMode == 1));

		pThis->gPrivate_internalMode = 2;
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_error_iterator_isValid(Crx_C_Error_Iterator * pThis)
	{return (pThis->gPrivate_internalMode != 2);}

CRX__LIB__PUBLIC_C_FUNCTION() uint16_t crx_c_error_iterator_getSpaceId(
		Crx_C_Error_Iterator * pThis)
{
	if(pThis->gPrivate_internalMode == 2)
		{return 0;}
	else if((pThis->gPrivate_internalMode == 0) || (pThis->gPrivate_internalMode == 1))
		{return pThis->gPrivate_error->gPrivate_space;}
	else
	{
		CRX_SCOPE_META
		assert(pThis->gPrivate_internalMode == 3);

		CRX_SCOPE
		Crx_C_Error_ErrorElement const * tErrorElement = 
				crx_c_error_error_private_trail_iterator_get(&(pThis->gPrivate_iterator));

		if(tErrorElement != NULL)
			{return tErrorElement->gSpace;}
		else
			{return 0;}
		CRX_SCOPE_END
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() int32_t crx_c_error_iterator_getCode(Crx_C_Error_Iterator * pThis)
{
	if(pThis->gPrivate_internalMode == 2)
		{return 0;}
	else if((pThis->gPrivate_internalMode == 0) || (pThis->gPrivate_internalMode == 1))
		{return pThis->gPrivate_error->gPrivate_code;}
	else
	{
		CRX_SCOPE_META
		assert(pThis->gPrivate_internalMode == 3);

		CRX_SCOPE
		Crx_C_Error_ErrorElement const * tErrorElement = 
				crx_c_error_error_private_trail_iterator_constantGet(&(pThis->gPrivate_iterator));
		
		if(tErrorElement != NULL)
			{return tErrorElement->gCode;}
		else
			{return 0;}
		CRX_SCOPE_END
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() char const * crx_c_error_iterator_getMessage(
		Crx_C_Error_Iterator * pThis)
{
	if(pThis->gPrivate_internalMode == 2)
		{return 0;}
	else if((pThis->gPrivate_internalMode == 0) || (pThis->gPrivate_internalMode == 1))
		{return crx_c_error_error_getMessage(pThis->gPrivate_error);}
	else
	{
		CRX_SCOPE_META
		assert(pThis->gPrivate_internalMode == 3);

		CRX_SCOPE
		Crx_C_Error_ErrorElement const * tErrorElement = 
				crx_c_error_error_private_trail_iterator_constantGet(&(pThis->gPrivate_iterator));
		
		if(tErrorElement != NULL)
			{return crx_c_error_errorElement_getMessage(tErrorElement);}
		else
			{return 0;}
		CRX_SCOPE_END
	}	
}

		
#undef CRX__C__ERROR__PRIVATE__SIZE_T
#undef CRX__C__ERROR__PRIVATE__SIZE_MAX


CRX__LIB__C_CODE_END()

