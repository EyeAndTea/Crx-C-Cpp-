//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/Array.h"

#include "Crx/H/crx/c/TypeBluePrint.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()

#if(CRX__ARE_ONLY_POINTERS_TO_SAME_OBJECT_EQUAL_AND_ALWAYS)
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_array_getByteSizeOf(Crx_C_Array const * pArray)
{
	if((pArray->gPrivate_internalBuffer != NULL) && (pArray->gSIZE_OF_INTERNAL_BUFFER > 0) &&
			CRX__ARE_POINTERS_TO_SAME_OBJECT(pArray->gPrivate_internalBuffer, 
			pArray->gPrivate_buffer, ))
	{
		return (sizeof(Crx_C_Array) + ((pArray->gSIZE_OF_INTERNAL_BUFFER > 0) ? 
				((pArray->gSIZE_OF_INTERNAL_BUFFER * pArray->gPrivate_typeBluePrint->gBYTE_SIZE) - 1) : 0));
	}
	else
		{return sizeof(Crx_C_Array);}
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_array_getByteSizeFor(
		Crx_C_TypeBluePrint const * pTypeBluePrint, bool pIsInternalBufferExternal, 
		size_t pSizeOfInternalBuffer)
{
	if(!pIsInternalBufferExternal)
	{
		return (sizeof(Crx_C_Array) + ((pSizeOfInternalBuffer > 0) ? 
				((pSizeOfInternalBuffer * pTypeBluePrint->gBYTE_SIZE) - 1) : 0));
	}
	else
		{return sizeof(Crx_C_Array);}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_private_doInit(Crx_C_Array * pThis, 
		Crx_C_TypeBluePrint const *  pTypeBluePrint, size_t pSizeOfInternalBuffer, size_t pCapacity)
{
	//assert(((pThis->gPrivate_elements == 0) || (pThis->gPrivate_elements == NULL)) && (pThis->gPrivate_length == 0));
	assert((pTypeBluePrint != NULL) && CRX__C__TYPE_BLUE_PRINT__IS_CORRECT_FORM(pTypeBluePrint));
	assert(pTypeBluePrint->gFUNC__GET_BYTE_SIZE_OF == NULL);

	pThis->gPrivate_typeBluePrint = pTypeBluePrint;
	pThis->gSIZE_OF_INTERNAL_BUFFER = pSizeOfInternalBuffer;
	pThis->gPrivate_elements = NULL;
	pThis->gPrivate_length = 0;

	if(pThis->gPrivate_internalBuffer != NULL)
	{
		if(pCapacity > pThis->gSIZE_OF_INTERNAL_BUFFER)
		{
			pThis->gPrivate_elements = (unsigned char *)(malloc(pCapacity * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

			if(pThis->gPrivate_elements != NULL)
				{pThis->gPrivate_capacity = pCapacity;}
			else
				{pThis->gPrivate_capacity = pThis->gSIZE_OF_INTERNAL_BUFFER;}
		}
		else
			{pThis->gPrivate_capacity = pThis->gSIZE_OF_INTERNAL_BUFFER;}
	}
	else
	{
		/*assert(pCapacity > 0);*/
		if(pCapacity > 0)
		{
			pThis->gPrivate_elements = (unsigned char *)(malloc(pCapacity * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

			if(pThis->gPrivate_elements != NULL)
				{pThis->gPrivate_capacity = pCapacity;}
			else
				{pThis->gPrivate_capacity = 0;}
		}
		else
			{pThis->gPrivate_capacity = 0;}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_construct(Crx_C_Array * pThis, 
		Crx_C_TypeBluePrint const *  pTypeBluePrint, size_t pSizeOfInternalBuffer, size_t pCapacity)
{
	pThis->gPrivate_internalBuffer = ((pSizeOfInternalBuffer > 0) ? (pThis->gPrivate_buffer) : NULL);

	crx_c_array_private_doInit(pThis, pTypeBluePrint, pSizeOfInternalBuffer, pCapacity);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_construct2(Crx_C_Array * pThis, 
		Crx_C_TypeBluePrint const *  pTypeBluePrint, unsigned char * pBufferOnStack, 
		size_t pSizeOfBufferOnStack, size_t pCapacity)
{
	assert((pBufferOnStack != NULL) && !CRX__ARE_POINTERS_TO_SAME_OBJECT(pBufferOnStack, pThis->gPrivate_buffer, ));

	pThis->gPrivate_internalBuffer = ((unsigned char *) pBufferOnStack);
		
	crx_c_array_private_doInit(pThis, pTypeBluePrint, pSizeOfBufferOnStack, pCapacity);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_moveConstruct(Crx_C_Array * pThis, Crx_C_Array * pArray)
{
	pThis->gPrivate_typeBluePrint = pArray->gPrivate_typeBluePrint;
	pThis->gPrivate_elements = pArray->gPrivate_elements;
	pThis->gPrivate_capacity = pArray->gPrivate_capacity;
	pThis->gSIZE_OF_INTERNAL_BUFFER = pArray->gSIZE_OF_INTERNAL_BUFFER;

	if(!CRX__ARE_POINTERS_TO_SAME_OBJECT(pArray->gPrivate_internalBuffer, pArray->gPrivate_buffer, ))
		{pThis->gPrivate_internalBuffer = pArray->gPrivate_internalBuffer;}
	else
		{pThis->gPrivate_internalBuffer = pThis->gPrivate_buffer;}

	if(pThis->gPrivate_elements == NULL)
	{
		if(CRX__ARE_POINTERS_TO_SAME_OBJECT(pArray->gPrivate_internalBuffer, pArray->gPrivate_buffer, ))
		{
			pThis->gPrivate_length = 0;

			CRX_FOR(size_t tI = 0, tI < pArray->gPrivate_length, tI++)
			{
				crx_c_array_moveAndFastPush(pThis, pArray->gPrivate_buffer + 
						(tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

				if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
				{
					pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT(pArray->gPrivate_buffer + 
							(tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
				}
			}
			CRX_ENDFOR
		}
		else
		{
			pThis->gPrivate_length = pArray->gPrivate_length;

			pArray->gPrivate_internalBuffer = NULL;
			pArray->gPrivate_elements = NULL;
			pArray->gPrivate_capacity = 0;
		}
	}
	else
	{
		pThis->gPrivate_length = pArray->gPrivate_length;

		if(!CRX__ARE_POINTERS_TO_SAME_OBJECT(pArray->gPrivate_internalBuffer, pArray->gPrivate_buffer, ))
		{
			pArray->gPrivate_internalBuffer = NULL;
			pArray->gPrivate_capacity = 0;
		}
		else
			{pArray->gPrivate_capacity = pArray->gSIZE_OF_INTERNAL_BUFFER;}

		pArray->gPrivate_elements = NULL;
	}

	pArray->gPrivate_length = 0;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_copyConstruct(Crx_C_Array * pThis, Crx_C_Array const * pArray)
{
	if(!pArray->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	crx_c_array_construct(pThis, pArray->gPrivate_typeBluePrint, 
			pArray->gSIZE_OF_INTERNAL_BUFFER, pArray->gPrivate_length);

	if(pArray->gPrivate_length > 0)
	{
		unsigned char * tTarget = NULL;

		if(pThis->gPrivate_elements != NULL)
			{tTarget = pThis->gPrivate_elements;}
		else
			{tTarget = pThis->gPrivate_internalBuffer;}

		if(pArray->gPrivate_elements != NULL)
		{
			if(pArray->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
			{
				CRX_FOR(size_t tI = 0, tI < pArray->gPrivate_length, tI++)
				{
					pArray->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT(
							tTarget + (tI * pArray->gPrivate_typeBluePrint->gBYTE_SIZE),
							pArray->gPrivate_elements + (tI * pArray->gPrivate_typeBluePrint->gBYTE_SIZE));
				}
				CRX_ENDFOR
			}
			else
			{
				memcpy(tTarget,
						pArray->gPrivate_elements,
						pArray->gPrivate_length * pArray->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}
		else
		{
			if(pArray->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
			{
				CRX_FOR(size_t tI = 0, tI < pArray->gPrivate_length, tI++)
				{
					pArray->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT(
							tTarget + (tI * pArray->gPrivate_typeBluePrint->gBYTE_SIZE),
							pArray->gPrivate_internalBuffer + (tI * pArray->gPrivate_typeBluePrint->gBYTE_SIZE));
				}
				CRX_ENDFOR
			}
			else
			{
				memcpy(tTarget,
						pArray->gPrivate_internalBuffer,
						pArray->gPrivate_length * pArray->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}

		pThis->gPrivate_length = pArray->gPrivate_length;
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Array * crx_c_array_new(Crx_C_TypeBluePrint const *  pTypeBluePrint,
		size_t pSizeOfInternalBuffer CRX_DEFAULT(0), size_t pCapacity CRX_DEFAULT(0))
{
	Crx_C_Array * vReturn = ((Crx_C_Array *) calloc(1, sizeof(Crx_C_Array) + 
			(pSizeOfInternalBuffer * pTypeBluePrint->gBYTE_SIZE) - 
			((pSizeOfInternalBuffer > 0) ? 1 : 0)));

	if(vReturn != NULL)
		{crx_c_array_construct(vReturn, pTypeBluePrint, pSizeOfInternalBuffer, pCapacity);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Array * crx_c_array_new2(Crx_C_TypeBluePrint const *  pTypeBluePrint, 
		unsigned char * pBufferOnStack, size_t pSizeOfInternalBuffer CRX_DEFAULT(0), 
		size_t pCapacity CRX_DEFAULT(0))
{
	Crx_C_Array * vReturn = ((Crx_C_Array *) calloc(1, sizeof(Crx_C_Array)));

	if(vReturn != NULL)
		{crx_c_array_construct2(vReturn, pTypeBluePrint, pBufferOnStack, pSizeOfInternalBuffer, pCapacity);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Array * crx_c_array_moveNew(Crx_C_Array * pArray)
{
	Crx_C_Array * vReturn = (Crx_C_Array *)(calloc(1, crx_c_array_getByteSizeOf(pArray)));

	if(vReturn != NULL)
		{crx_c_array_moveConstruct(vReturn, pArray);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Array * crx_c_array_copyNew(Crx_C_Array const * pArray)
{
	CRX_SCOPE_META
	if(!pArray->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	CRX_SCOPE
	Crx_C_Array * vReturn = ((Crx_C_Array *) calloc(1, crx_c_array_getByteSizeOf(pArray)));

	if(vReturn != NULL)
		{crx_c_array_copyConstruct(vReturn, pArray);}

	return vReturn;
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Array * crx_c_array_private_new2(Crx_C_Array * pArray, size_t pStartIndex, 
		size_t pWidth)
{
	CRX_SCOPE_META
	assert(pStartIndex + pWidth <= pArray->gPrivate_length);

	CRX_SCOPE
	Crx_C_Array * vReturn = crx_c_array_new(pArray->gPrivate_typeBluePrint, 
			pArray->gSIZE_OF_INTERNAL_BUFFER, pWidth);

	if((vReturn != NULL) && (pWidth > 0))
	{
		unsigned char * tTarget = NULL;

		if(vReturn->gPrivate_elements != NULL)
			{tTarget = vReturn->gPrivate_elements;}
		else
			{tTarget = vReturn->gPrivate_internalBuffer;}
		
		if(pArray->gPrivate_elements != NULL)
		{
			if(pArray->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
			{
				CRX_FOR(size_t tI = 0, tI < pWidth, tI++)
				{
					pArray->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT(
							tTarget + (tI * pArray->gPrivate_typeBluePrint->gBYTE_SIZE),
							pArray->gPrivate_elements + ((pStartIndex + tI) * pArray->gPrivate_typeBluePrint->gBYTE_SIZE));
				}
				CRX_ENDFOR
			}
			else
			{
				memcpy(tTarget,
						pArray->gPrivate_elements + (pStartIndex * pArray->gPrivate_typeBluePrint->gBYTE_SIZE),
						pWidth * pArray->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}
		else
		{
			if(pArray->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
			{
				CRX_FOR(size_t tI = 0, tI < pWidth, tI++)
				{
					pArray->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT(
							tTarget + (tI * pArray->gPrivate_typeBluePrint->gBYTE_SIZE),
							pArray->gPrivate_internalBuffer + ((pStartIndex + tI) * pArray->gPrivate_typeBluePrint->gBYTE_SIZE));
				}
				CRX_ENDFOR
			}
			else
			{
				memcpy(tTarget,
						pArray->gPrivate_internalBuffer + (pStartIndex * pArray->gPrivate_typeBluePrint->gBYTE_SIZE),
						pWidth * pArray->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}

		vReturn->gPrivate_length = pWidth;
	}

	return vReturn;
	CRX_SCOPE_END
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_array_private_unsafeCallElementsDestruct(Crx_C_Array * pThis, size_t pStartIndex,
		size_t pEndIndex)
{
	CRX_SCOPE_META
	assert(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL);
	
	CRX_SCOPE
	size_t vStartStartByteIndex = pStartIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE;
	size_t vEndStartByteIndex = pEndIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE;

	if(pThis->gPrivate_elements != NULL)
	{
		CRX_FOR(size_t tI = vStartStartByteIndex, tI <= vEndStartByteIndex, tI += pThis->gPrivate_typeBluePrint->gBYTE_SIZE)
			{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements + tI);}
		CRX_ENDFOR
	}
	else
	{
		CRX_FOR(size_t tI = vStartStartByteIndex, tI <= vEndStartByteIndex, tI += pThis->gPrivate_typeBluePrint->gBYTE_SIZE)
			{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_internalBuffer + tI);}
		CRX_ENDFOR
	}
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_destruct(Crx_C_Array * pThis)
{
	if((pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL) && (pThis->gPrivate_length > 0))
		{crx_c_array_private_unsafeCallElementsDestruct(pThis, 0, pThis->gPrivate_length - 1);}

	if(pThis->gPrivate_elements != NULL)
	{
		free(pThis->gPrivate_elements);

		pThis->gPrivate_elements = NULL;
	}
	
	CRX__C__TYPE_BLUE_PRINT__GENERIC__FINALIZE(pThis->gPrivate_typeBluePrint);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_free(Crx_C_Array * pThis)
	{free(pThis);}
CRX__C__TYPE_BLUE_PRINT__GENERIC__DEFINE_GET_BLUE_PRINT(
		Crx_C_Array, crx_c_array_,
		CRXM__FALSE, CRXM__TRUE,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__TRUE, CRXM__FALSE,
		((pThis->gPrivate_internalBuffer != NULL) && (pThis->gSIZE_OF_INTERNAL_BUFFER > 0) &&
				CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis->gPrivate_internalBuffer, 
				pThis->gPrivate_buffer, )), true,
		pThis->gPrivate_typeBluePrint->gIS_COPYABLE, true,
		(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL) ||
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL), false)
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_array_getLength(Crx_C_Array * pThis)
	{return pThis->gPrivate_length;}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_array_getCapacity(Crx_C_Array * pThis)
	{return pThis->gPrivate_capacity;}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_ensureCapacity(Crx_C_Array * pThis, size_t pCapacity)
{
	CRX_SCOPE_META
	if(pCapacity <= pThis->gPrivate_capacity)
		{return true;}
	else if(pCapacity > ((((size_t)-1) >> 1) + 1))
		{return false;}

	CRX_SCOPE
	size_t vCapacity = ((pThis->gPrivate_capacity == 0 ? 1 : pThis->gPrivate_capacity) << 1);

	while(vCapacity < pCapacity)
		{vCapacity = (vCapacity << 1);}

	if(pThis->gPrivate_elements == NULL)
	{
		pThis->gPrivate_elements = (unsigned char *)(malloc(vCapacity * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

		if(pThis->gPrivate_elements != NULL)
		{
			if(pThis->gPrivate_internalBuffer != NULL)
			{
				if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
				{
					CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++)
					{
						(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								pThis->gPrivate_internalBuffer + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
					}
					CRX_ENDFOR
				}
				else
					{memcpy(pThis->gPrivate_elements, pThis->gPrivate_internalBuffer, pThis->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);}
				
				if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
				{
					CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++)
						{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(pThis->gPrivate_internalBuffer + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));}
					CRX_ENDFOR
				}
			}

			pThis->gPrivate_capacity = vCapacity;

			return true;
		}
		else
			{return false;}
	}
	else
	{
		if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL))
		{
			unsigned char * tElements = (unsigned char *)(malloc(vCapacity * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

			if(tElements != NULL)
			{
				if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
				{
					CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++)
					{
						(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(tElements + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								pThis->gPrivate_elements + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
					}
					CRX_ENDFOR
				}
				else
					{memcpy(tElements, pThis->gPrivate_elements, pThis->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);}

				if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
				{
					CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++)
						{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(pThis->gPrivate_elements + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));}
					CRX_ENDFOR
				}

				free(pThis->gPrivate_elements);
				pThis->gPrivate_elements = tElements;

				pThis->gPrivate_capacity = vCapacity;

				return true;
			}
			else
				{return false;}
		}
		else
		{
			unsigned char * tElements = (unsigned char *)(realloc(pThis->gPrivate_elements,
					vCapacity * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

			if(tElements != NULL)
			{
				pThis->gPrivate_elements = tElements;

				pThis->gPrivate_capacity = vCapacity;

				return true;
			}
			else
				{return false;}
		}
	}
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_emptyAndEnsureCapacity(Crx_C_Array * pThis,
		size_t pCapacity)
{
	CRX_SCOPE_META
	if((pCapacity <= pThis->gPrivate_capacity) && (pThis->gPrivate_length == 0))
		{return true;}
	else if(pCapacity > ((((size_t)-1) >> 1) + 1))
		{return false;}

	CRX_SCOPE
	bool vIsNoError = true;
	unsigned char * vElements = NULL;
	size_t vCapacity = pThis->gPrivate_capacity;

	if(pCapacity > pThis->gPrivate_capacity)
	{
		vCapacity = (pThis->gPrivate_capacity == 0 ? 1 : pThis->gPrivate_capacity);

		while(vCapacity < pCapacity)
			{vCapacity = (vCapacity << 1);}

		if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL))
		{
			vElements = (unsigned char *)(malloc(vCapacity * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}
		else
		{
			if(pThis->gPrivate_elements != NULL)
			{
				vElements = (unsigned char *)(realloc(pThis->gPrivate_elements,
						(vCapacity * pThis->gPrivate_typeBluePrint->gBYTE_SIZE)));
			}
			else
			{
				vElements = (unsigned char *)(malloc(
						(vCapacity * pThis->gPrivate_typeBluePrint->gBYTE_SIZE)));
			}
		}

		if(vElements == NULL)
			{vIsNoError = false;}
	}

	if(vIsNoError)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{
			if(pThis->gPrivate_length > 0)
			{
				crx_c_array_private_unsafeCallElementsDestruct(pThis, 0,
						pThis->gPrivate_length - 1);
			}
		}

		if(vElements != NULL)
		{
			free(pThis->gPrivate_elements);
			pThis->gPrivate_elements = vElements;

			pThis->gPrivate_capacity = vCapacity;
		}

		pThis->gPrivate_length = 0;

		return true;
	}
	else
		{return false;}
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_empty(Crx_C_Array * pThis)
{
	if(pThis->gPrivate_length == 0)
		{return;}

	if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{crx_c_array_private_unsafeCallElementsDestruct(pThis, 0, pThis->gPrivate_length - 1);}

	pThis->gPrivate_length = 0;
}


CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_array_private_insertSpaceAt(Crx_C_Array * pThis, size_t pIndex,
		size_t pWidth)
{
	CRX_SCOPE_META
	assert(pIndex <= pThis->gPrivate_length);

	CRX_SCOPE
	bool vIsNoError = true;

	if(pWidth + pThis->gPrivate_length > pThis->gPrivate_capacity)
		{vIsNoError = crx_c_array_ensureCapacity(pThis, pWidth + pThis->gPrivate_length);}

	if(!vIsNoError)
		{return false;}
	else
	{
		unsigned char * vTarget = NULL;

		if(pThis->gPrivate_elements != NULL)
			{vTarget = pThis->gPrivate_elements;}
		else
			{vTarget = pThis->gPrivate_internalBuffer;}

		if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL))
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				CRX_FOR(size_t tI = pThis->gPrivate_length - 1, tI >= pIndex, tI--)
				{
					(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(
							vTarget + ((tI + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							vTarget + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

					if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
						{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vTarget + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));}
				}
				CRX_ENDFOR
			}
			else
			{
				size_t tI;

				CRX_FOR(tI = pThis->gPrivate_length - pWidth, tI >= pIndex + pWidth, tI = tI - pWidth)
				{
					memmove(vTarget + ((tI + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
							vTarget + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					CRX_FOR(size_t tI2 = tI, tI2 < tI + pWidth, tI2++)
						{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vTarget + (tI2 * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));}
					CRX_ENDFOR
				}
				CRX_ENDFOR

				CRX_FOR(tI = tI + pWidth - 1, tI >= pIndex, tI--)
				{
					memmove(vTarget + ((tI + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
							vTarget + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vTarget + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
				}
				CRX_ENDFOR
			}
		}
		else
		{
			memmove(vTarget + ((pIndex + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
					vTarget + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					(pThis->gPrivate_length - pIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}

		pThis->gPrivate_length = pThis->gPrivate_length + pWidth;

		return true;
	}
	CRX_SCOPE_END
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_array_private_fastInsertSpaceAt(Crx_C_Array * pThis, size_t pIndex,
		size_t pWidth)
{
	CRX_SCOPE_META
	assert(pIndex <= pThis->gPrivate_length);
	assert(pWidth + pThis->gPrivate_length <= pThis->gPrivate_capacity);

	CRX_SCOPE
	unsigned char * vTarget = NULL;

	if(pThis->gPrivate_elements != NULL)
		{vTarget = pThis->gPrivate_elements;}
	else
		{vTarget = pThis->gPrivate_internalBuffer;}

	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL))
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			CRX_FOR(size_t tI = pThis->gPrivate_length - 1, tI >= pIndex, tI--)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(
						vTarget + ((tI + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						vTarget + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

				if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
					{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vTarget + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));}
			}
			CRX_ENDFOR
		}
		else
		{
			size_t tI;

			CRX_FOR(tI = pThis->gPrivate_length - pWidth, tI >= pIndex + pWidth, tI = tI - pWidth)
			{
				memmove(vTarget + ((tI + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
						vTarget + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

				CRX_FOR(size_t tI2 = tI, tI2 < tI + pWidth, tI2++)
					{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vTarget + (tI2 * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));}
				CRX_ENDFOR
			}
			CRX_ENDFOR

			CRX_FOR(tI = tI + pWidth - 1, tI >= pIndex, tI--)
			{
				memmove(vTarget + ((tI + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
						vTarget + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vTarget + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
			}
			CRX_ENDFOR
		}
	}
	else
	{
		memmove(vTarget + ((pIndex + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
				vTarget + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
				(pThis->gPrivate_length - pIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
	}

	pThis->gPrivate_length = pThis->gPrivate_length + pWidth;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_copyAssignFrom2(Crx_C_Array * pThis, Crx_C_Array * pArray,
		size_t pStartIndex, size_t pWidth)
{
	CRX_SCOPE_META
	assert(pThis->gPrivate_typeBluePrint->gBYTE_SIZE == pArray->gPrivate_typeBluePrint->gBYTE_SIZE);
	assert(pStartIndex + pWidth <= pArray->gPrivate_length);

	CRX_SCOPE
	Crx_C_Array * vArray = pArray;
	bool vIsSameArray = CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis, pArray, true);
	bool vReturn = false;

	if(vIsSameArray) 
	{
#if(CRX__ARE_ONLY_POINTERS_TO_SAME_OBJECT_EQUAL_AND_ALWAYS)
		if((pStartIndex == 0) && (pWidth == pThis->gPrivate_length))
			{return true;}
#endif

		vArray = crx_c_array_private_new2(pArray, pStartIndex, pWidth);
	}

	if(vArray != NULL)
	{
		if(crx_c_array_emptyAndEnsureCapacity(pThis, pWidth))
		{
			if(pWidth == 0)
				{return true;}
			else
			{
				unsigned char * vTarget = NULL;

				if(pThis->gPrivate_elements != NULL)
					{vTarget = pThis->gPrivate_elements;}
				else
					{vTarget = pThis->gPrivate_internalBuffer;}

				if(vArray->gPrivate_elements != NULL)
				{
					if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
					{
						CRX_FOR(size_t tI = 0, tI < pWidth, tI++)
						{
							pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT(
									vTarget + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
									vArray->gPrivate_elements + ((pStartIndex + tI) * 
											pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
						}
						CRX_ENDFOR
					}
					else
					{
						memcpy(vTarget, 
								vArray->gPrivate_elements + 
										(pStartIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
					}
				}
				else
				{
					if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
					{
						CRX_FOR(size_t tI = 0, tI < vArray->gPrivate_length, tI++)
						{
							pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT(
									vTarget + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
									vArray->gPrivate_internalBuffer + ((pStartIndex + tI) * 
											pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
						}
						CRX_ENDFOR
					}
					else
					{
						memcpy(vTarget, 
								vArray->gPrivate_internalBuffer + 
										(pStartIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
					}
				}

				pThis->gPrivate_length = pWidth;

				vReturn = true;
			}
		}

		if(vIsSameArray)
		{
			crx_c_array_destruct(vArray);
			free(vArray);
		}
	}

	return vReturn;
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_copyAssignFrom(Crx_C_Array * pThis, Crx_C_Array * pArray)
	{return crx_c_array_copyAssignFrom2(pThis, pArray, 0, pArray->gPrivate_length);}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_moveAndSetAt(Crx_C_Array * pThis, size_t pIndex, void * pElement)
{
	assert(pIndex <= pThis->gPrivate_length);

	if(pThis->gPrivate_elements != NULL)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
			{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));}

		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
					(unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_elements + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),  pElement, 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
			{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_internalBuffer + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));}

		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_internalBuffer + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
					(unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_internalBuffer + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement,
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_setAt(Crx_C_Array * pThis, size_t pIndex, void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));
		crx_c_array_moveAndSetAt(pThis, pIndex, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			crx_c_array_moveAndSetAt(pThis, pIndex, vElement);
		}
		else
			{crx_c_array_moveAndSetAt(pThis, pIndex, pElement);}
	}
	
	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)))
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}
}
CRX__LIB__PUBLIC_C_FUNCTION() unsigned char * crx_c_array_get(Crx_C_Array * pThis, size_t pIndex)
{
	assert(pIndex < pThis->gPrivate_length);

	if(pThis->gPrivate_elements != NULL)
		{return (pThis->gPrivate_elements + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));}
	else
		{return (pThis->gPrivate_internalBuffer + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_copyGet(Crx_C_Array const * pThis, unsigned char * pReturn, size_t pIndex)
{
	assert(pIndex < pThis->gPrivate_length);

	if(pThis->gPrivate_elements != NULL)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(pReturn, 
					pThis->gPrivate_elements + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}
		else
		{
			memcpy(pReturn, pThis->gPrivate_elements + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(pReturn, 
					pThis->gPrivate_internalBuffer + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}
		else
		{
			memcpy(pReturn, pThis->gPrivate_internalBuffer + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_tryMoveAndPush(Crx_C_Array * pThis, void * pElement)
{
	bool vIsNoError = true;

	if(pThis->gPrivate_length + 1 > pThis->gPrivate_capacity)
		{vIsNoError = crx_c_array_ensureCapacity(pThis, pThis->gPrivate_length + 1);}

	if(vIsNoError)
	{
		if(pThis->gPrivate_elements != NULL)
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements +
						(pThis->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
			}
			else
			{
				memcpy(pThis->gPrivate_elements + (pThis->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}
		else
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_internalBuffer +
						(pThis->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
			}
			else
			{
				memcpy(pThis->gPrivate_internalBuffer + (pThis->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}

		pThis->gPrivate_length = pThis->gPrivate_length + 1;

		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_push(Crx_C_Array * pThis, void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
	bool vReturn;

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));

		vReturn = crx_c_array_tryMoveAndPush(pThis, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			vReturn = crx_c_array_tryMoveAndPush(pThis, vElement);
		}
		else
			{vReturn = crx_c_array_tryMoveAndPush(pThis, pElement);}
	}
	
	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)) &&
			vReturn)
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}

	return vReturn;	
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_moveAndFastPush(Crx_C_Array * pThis, void * pElement)
{
	assert(pThis->gPrivate_capacity > pThis->gPrivate_length);

	if(pThis->gPrivate_elements != NULL)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements +
					(pThis->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_elements + (pThis->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_internalBuffer +
					(pThis->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_internalBuffer + (pThis->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}

	pThis->gPrivate_length = pThis->gPrivate_length + 1;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_fastPush(Crx_C_Array * pThis, void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));

		crx_c_array_moveAndFastPush(pThis, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			crx_c_array_moveAndFastPush(pThis, vElement);
		}
		else
			{crx_c_array_moveAndFastPush(pThis, pElement);}
	}
	
	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)))
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_pop(Crx_C_Array * pThis)
{
	assert(pThis->gPrivate_length > 0);

	pThis->gPrivate_length--;

	if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
	{
		if(pThis->gPrivate_elements != NULL)
			{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements + (pThis->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));}
		else
			{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_internalBuffer + (pThis->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));}
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_tryMoveAndInsertElementAt(Crx_C_Array * pThis, size_t pIndex,
		void * pElement)
{
	if(crx_c_array_private_insertSpaceAt(pThis, pIndex, 1))
	{
		if(pThis->gPrivate_elements != NULL)
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
			}
			else
			{
				memcpy(pThis->gPrivate_elements + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}
		else
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_internalBuffer + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
			}
			else
			{
				memcpy(pThis->gPrivate_internalBuffer + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}

		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_insertElementAt(Crx_C_Array * pThis, size_t pIndex, void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
	bool vReturn;

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));
		
		vReturn = crx_c_array_tryMoveAndInsertElementAt(pThis, pIndex, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			vReturn = crx_c_array_tryMoveAndInsertElementAt(pThis, pIndex, vElement);
		}
		else
			{vReturn = crx_c_array_tryMoveAndInsertElementAt(pThis, pIndex, pElement);}
	}

	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)) &&
			vReturn)
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}
		
	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_moveAndFastInsertElementAt(Crx_C_Array * pThis, size_t pIndex,
		void * pElement)
{
	crx_c_array_private_fastInsertSpaceAt(pThis, pIndex, 1);

	if(pThis->gPrivate_elements != NULL)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_elements + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_internalBuffer + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_internalBuffer + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_fastInsertElementAt(Crx_C_Array * pThis, size_t pIndex, 
		void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));
		
		crx_c_array_moveAndFastInsertElementAt(pThis, pIndex, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			crx_c_array_moveAndFastInsertElementAt(pThis, pIndex, vElement);
		}
		else
			{crx_c_array_moveAndFastInsertElementAt(pThis, pIndex, pElement);}
	}

	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)))
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_insertElementsAt(Crx_C_Array * pThis, size_t pIndex,
		Crx_C_Array * pArray, size_t pStartIndex, size_t pWidth)
{
	CRX_SCOPE_META
	if(pWidth == 0)
		{return true;}

	CRX_SCOPE
	Crx_C_Array * vArray = pArray;
	bool vIsSameArray = CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis, pArray, true);
	bool vReturn = false;

	if(vIsSameArray) 
	{
#if(CRX__ARE_ONLY_POINTERS_TO_SAME_OBJECT_EQUAL_AND_ALWAYS)
		if((pStartIndex == 0) && (pWidth == pThis->gPrivate_length))
			{return true;}
#endif

		vArray = crx_c_array_private_new2(pArray, pStartIndex, pWidth);
	}

	if(vArray != NULL)
	{
		if(crx_c_array_private_insertSpaceAt(pThis, pIndex, pWidth))
		{
			unsigned char * tTarget;
			unsigned char * tSource;

			if(pThis->gPrivate_elements != NULL)
				{tTarget = pThis->gPrivate_elements;}
			else
				{tTarget = pThis->gPrivate_internalBuffer;}

			if(vArray->gPrivate_elements != NULL)
				{tSource = vArray->gPrivate_elements;}
			else
				{tSource = vArray->gPrivate_internalBuffer;}

			if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
			{
				CRX_FOR(size_t tI = 0, tI < pWidth, tI++)
				{
					(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(tTarget + pIndex + tI,
							tSource + pStartIndex + tI);
				}
				CRX_ENDFOR
			}
			else
			{
				memcpy(tTarget + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), tSource + (pStartIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}

			vReturn = true;
		}

		if(vIsSameArray)
		{
			crx_c_array_destruct(vArray);
			free(vArray);
		}
	}

	return vReturn;
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_fastInsertElementsAt(Crx_C_Array * pThis, size_t pIndex,
		Crx_C_Array * pArray, size_t pStartIndex, size_t pWidth)
{
	CRX_SCOPE_META
	assert(!CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis, pArray, false));

	if(pWidth == 0)
		{return;}

	CRX_SCOPE
	unsigned char * tTarget;
	unsigned char * tSource;

	crx_c_array_private_fastInsertSpaceAt(pThis, pIndex, pWidth);

	if(pThis->gPrivate_elements != NULL)
		{tTarget = pThis->gPrivate_elements;}
	else
		{tTarget = pThis->gPrivate_internalBuffer;}

	if(pArray->gPrivate_elements != NULL)
		{tSource = pArray->gPrivate_elements;}
	else
		{tSource = pArray->gPrivate_internalBuffer;}

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		CRX_FOR(size_t tI = 0, tI < pWidth, tI++)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(tTarget + pIndex + tI,
					tSource + pStartIndex + tI);
		}
		CRX_ENDFOR
	}
	else
	{
		memcpy(tTarget + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), tSource + (pStartIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
				pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
	}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_insertCArrayAt(Crx_C_Array * pThis, size_t pIndex,
		void * pArray, size_t pWidth)
{
	if(pWidth == 0)
		{return true;}
	
	if(crx_c_array_private_insertSpaceAt(pThis, pIndex, pWidth))
	{
		unsigned char * tTarget;

		if(pThis->gPrivate_elements != NULL)
			{tTarget = pThis->gPrivate_elements;}
		else
			{tTarget = pThis->gPrivate_internalBuffer;}

		if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
		{
			CRX_FOR(size_t tI = 0, tI < pWidth, tI++)
				{(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(tTarget + pIndex + tI, (unsigned char *)(pArray) + tI);}
			CRX_ENDFOR
		}
		else
		{
			memcpy(tTarget + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pArray, 
					pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}

		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_fastInsertCArrayAt(Crx_C_Array * pThis, size_t pIndex,
		void * pArray, size_t pWidth)
{
	CRX_SCOPE_META
	if(pWidth == 0)
		{return;}

	CRX_SCOPE
	unsigned char * tTarget;

	crx_c_array_private_fastInsertSpaceAt(pThis, pIndex, pWidth);

	if(pThis->gPrivate_elements != NULL)
		{tTarget = pThis->gPrivate_elements;}
	else
		{tTarget = pThis->gPrivate_internalBuffer;}

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		CRX_FOR(size_t tI = 0, tI < pWidth, tI++)
			{(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(tTarget + pIndex + tI, (unsigned char *)(pArray) + tI);}
		CRX_ENDFOR
	}
	else
	{
		memcpy(tTarget + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pArray, 
				pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
	}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_insertElementCopiesAt(Crx_C_Array * pThis, size_t pIndex,
		void * pElement, size_t pNumberOfCopies)
{
	if(pNumberOfCopies == 0)
		{return true;}

	if(crx_c_array_private_insertSpaceAt(pThis, pIndex, pNumberOfCopies))
	{
		unsigned char * tTarget;

		if(pThis->gPrivate_elements != NULL)
			{tTarget = pThis->gPrivate_elements;}
		else
			{tTarget = pThis->gPrivate_internalBuffer;}

		if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
		{
			CRX_FOR(size_t tI = 0, tI < pNumberOfCopies, tI++)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(tTarget + ((pIndex + tI) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						(unsigned char *)(pElement));
			}
			CRX_ENDFOR
		}
		else
		{
			size_t tNumberOfCopies = 1;
			size_t tRemainingNumberOfCopies = pNumberOfCopies - 1;

			memcpy(tTarget + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			while(tRemainingNumberOfCopies > 0)
			{
				if(tRemainingNumberOfCopies >= tNumberOfCopies)
				{
					memcpy(tTarget + ((pIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tTarget + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies;
					tNumberOfCopies = (tNumberOfCopies << 1);
				}
				else
				{
					memcpy(tTarget + ((pIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tTarget + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tRemainingNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					break;
				}
			}
		}

		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_fastInsertElementCopiesAt(Crx_C_Array * pThis, size_t pIndex,
		void * pElement, size_t pNumberOfCopies)
{
	CRX_SCOPE_META
	if(pNumberOfCopies == 0)
		{return;}

	crx_c_array_private_fastInsertSpaceAt(pThis, pIndex, pNumberOfCopies);

	CRX_SCOPE
	unsigned char * tTarget;

	if(pThis->gPrivate_elements != NULL)
		{tTarget = pThis->gPrivate_elements;}
	else
		{tTarget = pThis->gPrivate_internalBuffer;}

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		CRX_FOR(size_t tI = 0, tI < pNumberOfCopies, tI++)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(tTarget + ((pIndex + tI) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					(unsigned char *)(pElement));
		}
		CRX_ENDFOR
	}
	else
	{
		size_t tNumberOfCopies = 1;
		size_t tRemainingNumberOfCopies = pNumberOfCopies - 1;

		memcpy(tTarget + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

		while(tRemainingNumberOfCopies > 0)
		{
			if(tRemainingNumberOfCopies >= tNumberOfCopies)
			{
				memcpy(tTarget + ((pIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						tTarget + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

				tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies;
				tNumberOfCopies = (tNumberOfCopies << 1);
			}
			else
			{
				memcpy(tTarget + ((pIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						tTarget + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						tRemainingNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

				break;
			}
		}
	}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_removeElements(Crx_C_Array * pThis, size_t pIndex,
		size_t pWidth)
{
	CRX_SCOPE_META
	assert((pWidth == 0) || ((pIndex < pThis->gPrivate_length) && (pIndex + pWidth <= pThis->gPrivate_length)));

	if(pWidth == 0)
		{return;}

	CRX_SCOPE	
	unsigned char * tTarget;
	
	if(pThis->gPrivate_elements != NULL)
		{tTarget = pThis->gPrivate_elements;}
	else
		{tTarget = pThis->gPrivate_internalBuffer;}

	if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
	{
		crx_c_array_private_unsafeCallElementsDestruct(pThis, pIndex,
				(((pIndex + pWidth) <= pThis->gPrivate_length) ? (pIndex + pWidth - 1) : pThis->gPrivate_length - 1));
	}
	
	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL) || 
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL))
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length - pWidth - pIndex, tI++)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(tTarget + 
						((tI + pIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						tTarget + ((tI + pIndex + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

				if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)
				{
					(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(tTarget +
						((tI + pIndex + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
				}
			}
			CRX_ENDFOR
		}
		else
		{
			CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length - pWidth - pIndex, tI++)
			{
				memmove(tTarget + ((tI + pIndex) *
								pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						tTarget + ((tI + pIndex + pWidth) * 
								pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(tTarget +
						((tI + pIndex + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
			}
			CRX_ENDFOR
		}
	}
	else
	{
		memmove(tTarget + (pIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
				tTarget + ((pIndex + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
				(pThis->gPrivate_length + 1 - pIndex - pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
	}

	pThis->gPrivate_length = pThis->gPrivate_length - pWidth;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() unsigned char * crx_c_array_getElementsPointer(Crx_C_Array * pThis)
{
	if(pThis->gPrivate_elements != NULL)
		{return pThis->gPrivate_elements;}
	else
		{return pThis->gPrivate_internalBuffer;}
}
#endif


CRX__LIB__C_CODE_END()

