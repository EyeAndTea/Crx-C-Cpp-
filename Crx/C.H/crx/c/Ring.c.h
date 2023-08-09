//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/Ring.h"

#include "Crx/H/crx/c/TypeBluePrint.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_ring_private_doInsertSpaceAt(Crx_C_Ring * pThis, size_t pIndex, size_t pWidth);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_moveAndFastPush(Crx_C_Ring * pThis, void * pElement);
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_ring_private_copyFromRingRange(Crx_C_Ring * pThis, size_t pIndex,
		Crx_C_Ring const * pArray, size_t pStartIndex, size_t pWidth);
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_ring_private_rawRotateRight(Crx_C_Ring * pThis, unsigned char * pElements,
		size_t pRawStartIndex, size_t pRawEndIndex, size_t pWidth /*, bool pIsToSetNewRawEndIndex*/);
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_ring_private_rawRotateLeft(Crx_C_Ring * pThis, unsigned char * pElements,
		size_t pRawStartIndex, size_t pRawEndIndex, size_t pWidth /*, bool pIsToSetNewRawStartIndex*/);

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_ring_getCorrectCapacityBoundFor(size_t pCapacity)
{
	size_t vReturn = 1;

	while(vReturn < pCapacity)
		{vReturn = (vReturn << 1);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_ring_getByteSizeOf(Crx_C_Ring const * pArray)
{
	if((pArray->gPrivate_internalBuffer != NULL) && (pArray->gSIZE_OF_INTERNAL_BUFFER > 0) &&
			!pArray->gPrivate_isInternalBufferExternal)
	{
		return (sizeof(Crx_C_Ring) + ((pArray->gSIZE_OF_INTERNAL_BUFFER > 0) ? 
				((pArray->gSIZE_OF_INTERNAL_BUFFER * pArray->gPrivate_typeBluePrint->gBYTE_SIZE) - 1) : 0));
	}
	else
		{return sizeof(Crx_C_Ring);}
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_ring_getByteSizeFor(Crx_C_TypeBluePrint const * pTypeBluePrint,
		bool pIsInternalBufferExternal, size_t pSizeOfInternalBuffer)
{
	if(!pIsInternalBufferExternal)
	{
		return (sizeof(Crx_C_Ring) + ((pSizeOfInternalBuffer > 0) ? 
				((pSizeOfInternalBuffer * pTypeBluePrint->gBYTE_SIZE) - 1) : 0));
	}
	else
		{return sizeof(Crx_C_Ring);}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_doInit(Crx_C_Ring * pThis, Crx_C_TypeBluePrint const * pTypeBluePrint,
		size_t pSizeOfInternalBuffer, size_t pCapacity, signed char pStartIndexAlignFactor)
{
	//assert(((pThis->gPrivate_elements == 0) || (pThis->gPrivate_elements == NULL)) && (pThis->gPrivate_length == 0));
	assert((pTypeBluePrint != NULL) && CRX__C__TYPE_BLUE_PRINT__IS_CORRECT_FORM(pTypeBluePrint));
	assert(pTypeBluePrint->gFUNC__GET_BYTE_SIZE_OF == NULL);
	assert((pCapacity & (pCapacity - 1)) == 0);
	assert((pSizeOfInternalBuffer == 0) || ((pSizeOfInternalBuffer & (pSizeOfInternalBuffer - 1)) == 0));

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
	
	pThis->gPrivate_startIndexAlignFactor = pStartIndexAlignFactor;
	
	if(pThis->gPrivate_startIndexAlignFactor > 0)
		{pThis->gPrivate_startIndex = (pThis->gPrivate_capacity >> pThis->gPrivate_startIndexAlignFactor);}
	else
	{
		pThis->gPrivate_startIndex = pThis->gPrivate_capacity -
				(pThis->gPrivate_capacity >> abs(pThis->gPrivate_startIndexAlignFactor));
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_construct(Crx_C_Ring * pThis, Crx_C_TypeBluePrint const * pTypeBluePrint,
		size_t pSizeOfInternalBuffer, size_t pCapacity, signed char pStartIndexAlignFactor)
{
	pThis->gPrivate_isInternalBufferExternal = false;
	pThis->gPrivate_internalBuffer = ((pSizeOfInternalBuffer > 0) ? pThis->gPrivate_buffer : NULL);

	crx_c_ring_doInit(pThis, pTypeBluePrint, pSizeOfInternalBuffer, pCapacity,
			pStartIndexAlignFactor);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_construct2(Crx_C_Ring * pThis, Crx_C_TypeBluePrint const * pTypeBluePrint,
		unsigned char * pBufferOnStack, size_t pSizeOfBufferOnStack, size_t pCapacity, 
		signed char pStartIndexAlignFactor)
{
	assert((pBufferOnStack != NULL) && !CRX__ARE_POINTERS_TO_SAME_OBJECT(pBufferOnStack, pThis->gPrivate_buffer, false));

	pThis->gPrivate_isInternalBufferExternal = true;
	pThis->gPrivate_internalBuffer = ((unsigned char *) pBufferOnStack);
		
	crx_c_ring_doInit(pThis, pTypeBluePrint, pSizeOfBufferOnStack, pCapacity, 
			pStartIndexAlignFactor);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_moveConstruct(Crx_C_Ring * pThis, Crx_C_Ring * pArray)
{
	pThis->gPrivate_typeBluePrint = pArray->gPrivate_typeBluePrint;
	pThis->gPrivate_elements = pArray->gPrivate_elements;
	pThis->gPrivate_startIndex = pArray->gPrivate_startIndex;
	pThis->gPrivate_capacity = pArray->gPrivate_capacity;
	pThis->gPrivate_isInternalBufferExternal = pArray->gPrivate_isInternalBufferExternal;
	pThis->gSIZE_OF_INTERNAL_BUFFER = pArray->gSIZE_OF_INTERNAL_BUFFER;
	pThis->gPrivate_startIndexAlignFactor = pArray->gPrivate_startIndexAlignFactor;

	if(pArray->gPrivate_isInternalBufferExternal)
		{pThis->gPrivate_internalBuffer = pArray->gPrivate_internalBuffer;}
	else
		{pThis->gPrivate_internalBuffer = pThis->gPrivate_buffer;}

	if(pThis->gPrivate_elements == NULL)
	{
		if(!pArray->gPrivate_isInternalBufferExternal)
		{
			pThis->gPrivate_length = 0;

			CRX_FOR(size_t tI = 0, tI < pArray->gPrivate_length, tI++)
			{
				crx_c_ring_moveAndFastPush(pThis, pArray->gPrivate_buffer +
						(((pArray->gPrivate_startIndex + tI) & (pArray->gPrivate_capacity - 1)) * 
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

				if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
				{
					pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT(pArray->gPrivate_buffer + 
							(((pArray->gPrivate_startIndex + tI) & (pArray->gPrivate_capacity - 1)) * 
							pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
				}
			}
			CRX_ENDFOR
		}
		else
		{
			pThis->gPrivate_length = pArray->gPrivate_length;

			pArray->gPrivate_internalBuffer = NULL;
			pArray->gPrivate_isInternalBufferExternal = false;
			pArray->gPrivate_elements = NULL;
			pArray->gPrivate_capacity = 0;
		}
	}
	else
	{
		pThis->gPrivate_length = pArray->gPrivate_length;

		if(pArray->gPrivate_isInternalBufferExternal)
		{
			pArray->gPrivate_internalBuffer = NULL;
			pArray->gPrivate_isInternalBufferExternal = false;
			pArray->gPrivate_capacity = 0;
		}
		else
			{pArray->gPrivate_capacity = pArray->gSIZE_OF_INTERNAL_BUFFER;}

		pArray->gPrivate_elements = NULL;
	}

	pArray->gPrivate_length = 0;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_copyConstruct(Crx_C_Ring * pThis, Crx_C_Ring const * pArray)
{
	if(!pArray->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	crx_c_ring_construct(pThis, pArray->gPrivate_typeBluePrint, pArray->gSIZE_OF_INTERNAL_BUFFER, 
			crx_c_ring_getCorrectCapacityBoundFor(pArray->gPrivate_length), 
			pArray->gPrivate_startIndexAlignFactor);

	if(pArray->gPrivate_length > 0)
	{
		size_t tStartIndex = ((pThis->gPrivate_startIndexAlignFactor > 0) ? 
				(pThis->gPrivate_capacity >> pThis->gPrivate_startIndexAlignFactor) : 
				(pThis->gPrivate_capacity - (pThis->gPrivate_capacity >> abs(pThis->gPrivate_startIndexAlignFactor))));

		if(pThis->gPrivate_capacity - tStartIndex < pArray->gPrivate_length)
		{
			if(pArray->gPrivate_length > (pThis->gPrivate_capacity >> 1))
				{tStartIndex = 0;}
			else
				{tStartIndex = (pThis->gPrivate_capacity >> 1);}
		}

		pThis->gPrivate_startIndex = tStartIndex;

		crx_c_ring_private_copyFromRingRange(pThis, 0, pArray, 0, pArray->gPrivate_length);

		pThis->gPrivate_length = pArray->gPrivate_length;
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Ring * crx_c_ring_new(Crx_C_TypeBluePrint const * pTypeBluePrint, 
		size_t pSizeOfInternalBuffer CRX_DEFAULT(0), size_t pCapacity CRX_DEFAULT(0),
		signed char pStartIndexAlignFactor CRX_DEFAULT(0))
{
	Crx_C_Ring * vReturn = ((Crx_C_Ring *) calloc(1, sizeof(Crx_C_Ring) + 
			(pSizeOfInternalBuffer * pTypeBluePrint->gBYTE_SIZE) - 
			((pSizeOfInternalBuffer > 0) ? 1 : 0)));

	if(vReturn != NULL)
	{
		crx_c_ring_construct(vReturn, pTypeBluePrint, pSizeOfInternalBuffer, pCapacity, 
				pStartIndexAlignFactor);
	}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Ring * crx_c_ring_new2(Crx_C_TypeBluePrint const * pTypeBluePrint, 
		unsigned char * pBufferOnStack, size_t pSizeOfBufferOnStack CRX_DEFAULT(0), 
		size_t pCapacity CRX_DEFAULT(0), signed char pStartIndexAlignFactor CRX_DEFAULT(0))
{
	Crx_C_Ring * vReturn = ((Crx_C_Ring *) calloc(1, sizeof(Crx_C_Ring)));

	if(vReturn != NULL)
	{
		crx_c_ring_construct2(vReturn, pTypeBluePrint, pBufferOnStack, pSizeOfBufferOnStack, 
				pCapacity, pStartIndexAlignFactor);
	}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Ring * crx_c_ring_moveNew(Crx_C_Ring * pArray)
{
	Crx_C_Ring * vReturn = (Crx_C_Ring *)(calloc(1, crx_c_ring_getByteSizeOf(pArray)));

	if(vReturn != NULL)
		{crx_c_ring_moveConstruct(vReturn, pArray);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Ring * crx_c_ring_copyNew(Crx_C_Ring const * pArray)
{
	CRX_SCOPE_META
	if(!pArray->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	CRX_SCOPE
	Crx_C_Ring * vReturn = ((Crx_C_Ring *) calloc(1, crx_c_ring_getByteSizeOf(pArray)));

	if(vReturn != NULL)
		{crx_c_ring_copyConstruct(vReturn, pArray);}

	return vReturn;
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Ring * crx_c_ring_private_new2(Crx_C_Ring * pArray,
		size_t pStartIndex, size_t pWidth)
{
	CRX_SCOPE_META
	assert(pStartIndex + pWidth <= pArray->gPrivate_length);

	CRX_SCOPE
	Crx_C_Ring * vReturn = crx_c_ring_new(pArray->gPrivate_typeBluePrint,
			pArray->gSIZE_OF_INTERNAL_BUFFER, crx_c_ring_getCorrectCapacityBoundFor(pWidth), 0);

	if((vReturn != NULL) && (pWidth > 0))
	{
		size_t tStartIndex = ((vReturn->gPrivate_startIndexAlignFactor > 0) ? 
				(vReturn->gPrivate_capacity >> vReturn->gPrivate_startIndexAlignFactor) : 
				(vReturn->gPrivate_capacity - (vReturn->gPrivate_capacity >> abs(vReturn->gPrivate_startIndexAlignFactor))));

		if(vReturn->gPrivate_capacity - tStartIndex < pWidth)
		{
			if(pWidth > (vReturn->gPrivate_capacity >> 1))
				{tStartIndex = 0;}
			else
				{tStartIndex = (vReturn->gPrivate_capacity >> 1);}
		}

		vReturn->gPrivate_startIndex = tStartIndex;

		crx_c_ring_private_copyFromRingRange(vReturn, 0, pArray, pStartIndex, pWidth);

		vReturn->gPrivate_length = pWidth;
	}

	return vReturn;
	CRX_SCOPE_END
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_ring_private_unsafeCallElementsDestruct(Crx_C_Ring * pThis, size_t pStartIndex,
		size_t pEndIndex)
{
	CRX_SCOPE_META
	assert(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL);

	CRX_SCOPE
	size_t vStartStartByteIndex = ((pThis->gPrivate_startIndex + pStartIndex) & (pThis->gPrivate_capacity - 1)) * 
			pThis->gPrivate_typeBluePrint->gBYTE_SIZE;
	size_t vEndStartByteIndex = ((pThis->gPrivate_startIndex + pEndIndex) & (pThis->gPrivate_capacity - 1)) * 
			pThis->gPrivate_typeBluePrint->gBYTE_SIZE;

	if(pThis->gPrivate_elements != NULL)
	{
		if(vStartStartByteIndex <= vEndStartByteIndex)
		{
			CRX_FOR(size_t tI = vStartStartByteIndex, tI <= vEndStartByteIndex, tI += pThis->gPrivate_typeBluePrint->gBYTE_SIZE)
				{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements + tI);}
			CRX_ENDFOR
		}
		else
		{
			CRX_FOR(size_t tI = vStartStartByteIndex, tI < pThis->gPrivate_capacity * pThis->gPrivate_typeBluePrint->gBYTE_SIZE, tI += pThis->gPrivate_typeBluePrint->gBYTE_SIZE)
				{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements + tI);}
			CRX_ENDFOR
			CRX_FOR(size_t tI = 0, tI <= vEndStartByteIndex, tI += pThis->gPrivate_typeBluePrint->gBYTE_SIZE)
				{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements + tI);}
			CRX_ENDFOR
		}
	}
	else
	{
		if(vStartStartByteIndex <= vEndStartByteIndex)
		{
			CRX_FOR(size_t tI = vStartStartByteIndex, tI <= vEndStartByteIndex, tI += pThis->gPrivate_typeBluePrint->gBYTE_SIZE)
				{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_internalBuffer + tI);}
			CRX_ENDFOR
		}
		else
		{
			CRX_FOR(size_t tI = vStartStartByteIndex, tI < pThis->gPrivate_capacity, tI += pThis->gPrivate_typeBluePrint->gBYTE_SIZE)
				{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_internalBuffer + tI);}
			CRX_ENDFOR
			CRX_FOR(size_t tI = 0, tI <= vEndStartByteIndex, tI += pThis->gPrivate_typeBluePrint->gBYTE_SIZE)
				{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_internalBuffer + tI);}
			CRX_ENDFOR
		}
	}
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_destruct(Crx_C_Ring * pThis)
{
	if((pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL) && (pThis->gPrivate_length > 0))
		{crx_c_ring_private_unsafeCallElementsDestruct(pThis, 0, pThis->gPrivate_length - 1);}

	if(pThis->gPrivate_elements != NULL)
	{
		free(pThis->gPrivate_elements);

		pThis->gPrivate_elements = NULL;
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_free(Crx_C_Ring * pThis)
	{free(pThis);}
CRX__C__TYPE_BLUE_PRINT__GENERIC__DEFINE_GET_BLUE_PRINT(
		Crx_C_Ring, crx_c_ring_,
		CRXM__FALSE, CRXM__TRUE,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__TRUE, CRXM__FALSE,
		((pThis->gPrivate_internalBuffer != NULL) && (pThis->gSIZE_OF_INTERNAL_BUFFER > 0) &&
				!pThis->gPrivate_isInternalBufferExternal), true,
		pThis->gPrivate_typeBluePrint->gIS_COPYABLE, true,
		(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL) ||
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL), false)
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_ring_getLength(Crx_C_Ring * pThis)
	{return pThis->gPrivate_length;}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_ring_getCapacity(Crx_C_Ring * pThis)
	{return pThis->gPrivate_capacity;}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_ring_private_moveElements(Crx_C_Ring * pThis, void * pSourceBuffer,
		size_t pStartIndex, size_t pLength, size_t pCapacity, void * pTargetBuffer)
{
	if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
	{
		CRX_FOR(size_t tI = 0, tI < pLength, tI++)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)((unsigned char *)(pTargetBuffer) + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					(unsigned char *)(pSourceBuffer) + (((pStartIndex + tI) & (pCapacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}
		CRX_ENDFOR
	}
	else
	{
		size_t vEndIndex = (pStartIndex + pLength - 1) & (pCapacity - 1);

		if(vEndIndex < pStartIndex)
		{
			memcpy(pTargetBuffer,
					(unsigned char *)(pSourceBuffer) + (pStartIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (pCapacity - pStartIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			memcpy((unsigned char *)(pTargetBuffer) + ((pCapacity - pStartIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					(unsigned char *)(pSourceBuffer) + (vEndIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (pStartIndex - vEndIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
		else
			{memcpy(pTargetBuffer, (unsigned char *)(pSourceBuffer) + (pStartIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pLength * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);}
	}
	
	if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
	{
		CRX_FOR(size_t tI = 0, tI < pLength, tI++)
			{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)((unsigned char *)(pTargetBuffer) + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));} \
		CRX_ENDFOR
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_ring_ensureCapacity(Crx_C_Ring * pThis, size_t pCapacity)
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
				size_t tStartIndex = ((pThis->gPrivate_startIndexAlignFactor > 0) ? 
						(pThis->gPrivate_capacity >> pThis->gPrivate_startIndexAlignFactor) : 
						(pThis->gPrivate_capacity - (pThis->gPrivate_capacity >> abs(pThis->gPrivate_startIndexAlignFactor))));

				crx_c_ring_private_moveElements(pThis, pThis->gPrivate_internalBuffer, 
						pThis->gPrivate_startIndex, pThis->gPrivate_length, pThis->gPrivate_capacity, 
						pThis->gPrivate_elements + (tStartIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

				pThis->gPrivate_startIndex = tStartIndex;
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
				size_t tStartIndex = ((pThis->gPrivate_startIndexAlignFactor > 0) ? 
						(pThis->gPrivate_capacity >> pThis->gPrivate_startIndexAlignFactor) : 
						(pThis->gPrivate_capacity - (pThis->gPrivate_capacity >> abs(pThis->gPrivate_startIndexAlignFactor))));

				crx_c_ring_private_moveElements(pThis, pThis->gPrivate_elements, pThis->gPrivate_startIndex,
						pThis->gPrivate_length, pThis->gPrivate_capacity,
						tElements + (tStartIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

				free(pThis->gPrivate_elements);
				pThis->gPrivate_elements = tElements;

				pThis->gPrivate_startIndex = tStartIndex;
				pThis->gPrivate_capacity = vCapacity;

				return true;
			}
			else
				{return false;}
		}
		else
		{
			unsigned char * tElements = (unsigned char *)(realloc(pThis->gPrivate_elements, 
					pThis->gPrivate_capacity * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

			if(tElements != NULL)
			{
				size_t tEndIndex = (pThis->gPrivate_startIndex + pThis->gPrivate_length - 1) & (pThis->gPrivate_capacity - 1);

				if(tEndIndex < pThis->gPrivate_startIndex)
				{
					memcpy(pThis->gPrivate_elements + ((pThis->gPrivate_startIndex + (pThis->gPrivate_capacity - pThis->gPrivate_startIndex)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							pThis->gPrivate_elements, (tEndIndex + 1) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
				}

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
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_ring_emptyAndEnsureCapacity(Crx_C_Ring * pThis, size_t pCapacity)
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
						vCapacity * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
			}
			else
			{
				vElements = (unsigned char *)(malloc(
						vCapacity * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
			}
		}

		if(vElements == NULL)
			{vIsNoError = false;}
	}

	if(vIsNoError)
	{
		size_t tStartIndex = ((pThis->gPrivate_startIndexAlignFactor > 0) ? 
				(pThis->gPrivate_capacity >> pThis->gPrivate_startIndexAlignFactor) : 
				(pThis->gPrivate_capacity - (pThis->gPrivate_capacity >> abs(pThis->gPrivate_startIndexAlignFactor))));

		if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{
			if(pThis->gPrivate_length > 0)
			{
				crx_c_ring_private_unsafeCallElementsDestruct(pThis, 0,
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
		pThis->gPrivate_startIndex = tStartIndex;

		return true;
	}
	else
		{return false;}
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_empty(Crx_C_Ring * pThis)
{
	if(pThis->gPrivate_length == 0)
		{return;}

	if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
	{
		crx_c_ring_private_unsafeCallElementsDestruct(pThis, 0, pThis->gPrivate_length - 1);

		pThis->gPrivate_startIndex = ((pThis->gPrivate_startIndexAlignFactor > 0) ? 
			(pThis->gPrivate_capacity >> pThis->gPrivate_startIndexAlignFactor) : 
			(pThis->gPrivate_capacity - (pThis->gPrivate_capacity >> abs(pThis->gPrivate_startIndexAlignFactor))));	
	}

	pThis->gPrivate_length = 0;
}
CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_ring_private_insertSpaceAt(Crx_C_Ring * pThis, size_t pIndex,
		size_t pWidth)
{
	CRX_SCOPE_META
	assert(pIndex <= pThis->gPrivate_length);

	CRX_SCOPE
	bool vIsNoError = true;

	if(pWidth + pThis->gPrivate_length > pThis->gPrivate_capacity)
		{vIsNoError = crx_c_ring_ensureCapacity(pThis, pWidth + pThis->gPrivate_length);}

	if(!vIsNoError)
		{return false;}
	else
	{
		crx_c_ring_private_doInsertSpaceAt(pThis, pIndex, pWidth);

		return true;
	}
	CRX_SCOPE_END
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_ring_private_fastInsertSpaceAt(Crx_C_Ring * pThis, size_t pIndex,
		size_t pWidth)
{
	assert(pIndex <= pThis->gPrivate_length);
	assert(pWidth + pThis->gPrivate_length <= pThis->gPrivate_capacity);

	crx_c_ring_private_doInsertSpaceAt(pThis, pIndex, pWidth);
}
CRX__LIB__PRIVATE_C_FUNCTION() Crx_C_Ring_Private_IndexTransform crx_c_ring_private_roundInsertSpaceAt(Crx_C_Ring * pThis, size_t pIndex,
		size_t pWidth)
{
	CRX_SCOPE_META
	assert(pIndex <= pThis->gPrivate_length);
	assert(pThis->gPrivate_capacity > 0);

	CRX_SCOPE
	Crx_C_Ring_Private_IndexTransform vReturn = CRX__INITIALIZATION_POD_ZERO;

	if((pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL) && (pThis->gPrivate_length > 0))
	{
		if(pWidth > pThis->gPrivate_capacity - pThis->gPrivate_length)
		{
			if(pWidth >= pThis->gPrivate_capacity)
			{
				crx_c_ring_private_unsafeCallElementsDestruct(pThis, 0,
						pThis->gPrivate_length - 1);
			}
			else
			{
				if(pWidth <= pThis->gPrivate_capacity - pThis->gPrivate_length + pIndex)
				{
					crx_c_ring_private_unsafeCallElementsDestruct(pThis, 0,
							pWidth - (pThis->gPrivate_capacity - pThis->gPrivate_length) - 1);
				}
				else
				{
					crx_c_ring_private_unsafeCallElementsDestruct(pThis, 0, pIndex - 1);
					crx_c_ring_private_unsafeCallElementsDestruct(pThis,
							pThis->gPrivate_length - (pWidth - (pThis->gPrivate_capacity - pThis->gPrivate_length) - pIndex),
							pThis->gPrivate_length - 1);
				}
			}
		}
	}

	if(pWidth < pThis->gPrivate_capacity)
	{
		if(pIndex == 0)
		{
			if(pThis->gPrivate_startIndex > pWidth)
				{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex - pWidth;}
			else
				{pThis->gPrivate_startIndex = pThis->gPrivate_capacity - (pWidth - pThis->gPrivate_startIndex);}
		}
		else if(pIndex == pThis->gPrivate_length)
			{}
		else
		{
			assert((((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) != pThis->gPrivate_startIndex) &&
					(pWidth < pThis->gPrivate_capacity));
					
			if(pWidth >= pThis->gPrivate_capacity - pThis->gPrivate_length + pIndex)
			{
				pThis->gPrivate_startIndex = (pThis->gPrivate_startIndex + (pIndex & (pThis->gPrivate_capacity - 1)));
			}
			else
			{
				size_t tOldStartIndex = pThis->gPrivate_startIndex;
				unsigned char * vTarget = NULL;
				
				if(pThis->gPrivate_internalBuffer != NULL)
				{
					if(pThis->gPrivate_elements == NULL)
						{vTarget = pThis->gPrivate_internalBuffer;}
					else
						{vTarget = pThis->gPrivate_elements;}
				}
				else
				{
					vTarget = pThis->gPrivate_elements;
				}
				
				if((pThis->gPrivate_length >> 1) > pIndex)
				{
					size_t tSegmentStartIndex;
					size_t tSegmentEndIndex = pIndex - 1;

					if(pWidth < pThis->gPrivate_capacity - pThis->gPrivate_length)
					{
						tSegmentStartIndex = 0;

						/*THE FOLLOWING IS SUBTRACTING pWidth*/
						pThis->gPrivate_startIndex = (pThis->gPrivate_startIndex + (pThis->gPrivate_capacity - pWidth)) &
								(pThis->gPrivate_capacity - 1);
					}
					else
					{
						tSegmentStartIndex = pWidth - (pThis->gPrivate_capacity - pThis->gPrivate_length);

						pThis->gPrivate_startIndex = (pThis->gPrivate_startIndex + pThis->gPrivate_length) &
									(pThis->gPrivate_capacity - 1);
					}
					
					if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL) || 
							(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL))
					{
						if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
						{
							CRX_FOR(size_t tI = tSegmentStartIndex, tI <= tSegmentEndIndex, tI++)
							{
								/*THE FOLLOWING IS SUBTRACTING pWidth*/
								(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(
										vTarget + (((tOldStartIndex + tI + pThis->gPrivate_capacity - pWidth) & (pThis->gPrivate_capacity - 1)) * 
												pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
										vTarget + (((tOldStartIndex + tI) & (pThis->gPrivate_capacity - 1)) * 
												pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

								if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
								{
									(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vTarget +
										(((tOldStartIndex + tI) & (pThis->gPrivate_capacity - 1)) * 
										pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
								}
							}
							CRX_ENDFOR
						}
						else
						{
							CRX_FOR(size_t tI = tSegmentStartIndex, tI <= tSegmentEndIndex, tI++)
							{
								/*THE FOLLOWING IS SUBTRACTING pWidth*/
								memmove(vTarget + (((tOldStartIndex + tI + pThis->gPrivate_capacity - pWidth) & (pThis->gPrivate_capacity - 1)) * 
												pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
										vTarget + (((tOldStartIndex + tI) & (pThis->gPrivate_capacity - 1)) * 
												pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
										pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

								(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vTarget +
										(((tOldStartIndex + tI) & (pThis->gPrivate_capacity - 1)) * 
										pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
							}
							CRX_ENDFOR
						}
					}
					else
					{
						crx_c_ring_private_rawRotateLeft(pThis, vTarget,
								(tOldStartIndex + tSegmentStartIndex) & (pThis->gPrivate_capacity - 1),
								(tOldStartIndex + tSegmentEndIndex) & (pThis->gPrivate_capacity - 1), 
								pWidth);
					}
				}
				else
				{
					size_t tSegmentStartIndex = pIndex;
					size_t tSegmentEndIndex = pThis->gPrivate_length - 1;

					if(pWidth >= pThis->gPrivate_capacity - pThis->gPrivate_length)
					{
						pThis->gPrivate_startIndex = (pThis->gPrivate_startIndex + (pWidth - (pThis->gPrivate_capacity - pThis->gPrivate_length))) &
								(pThis->gPrivate_capacity - 1);
					}

					if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL) || 
							(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL))
					{
						if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
						{
							CRX_FOR(size_t tI = tSegmentEndIndex, tI >= tSegmentStartIndex, tI--) \
							{
								(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(
										vTarget + (((tOldStartIndex + tI + pWidth) & (pThis->gPrivate_capacity - 1)) * 
												pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
										vTarget + (((tOldStartIndex + tI) & (pThis->gPrivate_capacity - 1)) * 
												pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

								if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
								{
									(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vTarget +
										(((tOldStartIndex + tI) & (pThis->gPrivate_capacity - 1)) * 
										pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
								}
							}
							CRX_ENDFOR
						}
						else
						{
							CRX_FOR(size_t tI = tSegmentEndIndex, tI >= tSegmentStartIndex, tI--)
							{
								memmove(vTarget + (((tOldStartIndex + tI + pWidth) & (pThis->gPrivate_capacity - 1)) * 
												pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
										vTarget + (((tOldStartIndex + tI) & (pThis->gPrivate_capacity - 1)) * 
												pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
										pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

								(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vTarget +
										(((tOldStartIndex + tI) & (pThis->gPrivate_capacity - 1)) * 
										pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
							}
							CRX_ENDFOR
						}
					}
					else
					{
						crx_c_ring_private_rawRotateRight(pThis, vTarget,
								(tOldStartIndex + tSegmentStartIndex) & (pThis->gPrivate_capacity - 1),
								(tOldStartIndex + tSegmentEndIndex) & (pThis->gPrivate_capacity - 1), 
								pWidth);
					}
				}
				
				if(pWidth < pThis->gPrivate_capacity - pThis->gPrivate_length)
					{vReturn.gNewIndex = pIndex;}
				else
				{
					vReturn.gNewIndex = (pIndex + (pThis->gPrivate_capacity -
							(pWidth - (pThis->gPrivate_capacity - pThis->gPrivate_length)))) &
							(pThis->gPrivate_capacity - 1);
				}
			}
		}

		pThis->gPrivate_length = pThis->gPrivate_length + pWidth;

		if(pThis->gPrivate_length > pThis->gPrivate_capacity)
			{pThis->gPrivate_length = pThis->gPrivate_capacity;}
		
		vReturn.gNewCountToEnd = pWidth;
	}
	else
		{vReturn.gNewCountToEnd = pThis->gPrivate_capacity;}

	return vReturn;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_ring_copyAssignFrom2(Crx_C_Ring * pThis, Crx_C_Ring * pArray, size_t pStartIndex,
		size_t pWidth)
{
	CRX_SCOPE_META
	assert(pThis->gPrivate_typeBluePrint->gBYTE_SIZE == pArray->gPrivate_typeBluePrint->gBYTE_SIZE);
	assert(pStartIndex + pWidth <= pArray->gPrivate_length);

	CRX_SCOPE
	Crx_C_Ring * vArray = pArray;
	bool vIsSameArray = CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis, pArray, true);
	bool vReturn = false;

	if(vIsSameArray)
	{
		size_t tCapacity;

#if(CRX__ARE_ONLY_POINTERS_TO_SAME_OBJECT_EQUAL_AND_ALWAYS)
		if((pStartIndex == 0) && (pWidth == pThis->gPrivate_length))
			{return true;}
#endif

		tCapacity = 1;
		while(tCapacity < pWidth)
			{tCapacity = (tCapacity << 1);}

		vArray = crx_c_ring_private_new2(pArray, pStartIndex, tCapacity);
	}

	if(vArray != NULL)
	{
		if(crx_c_ring_emptyAndEnsureCapacity(pThis, pWidth))
		{
			if(pWidth == 0)
				{vReturn = true;}
			else
			{
				size_t tStartIndex = ((pThis->gPrivate_startIndexAlignFactor > 0) ? 
						(pThis->gPrivate_capacity >> pThis->gPrivate_startIndexAlignFactor) : 
						(pThis->gPrivate_capacity - (pThis->gPrivate_capacity >> abs(pThis->gPrivate_startIndexAlignFactor))));

				if(pThis->gPrivate_capacity - tStartIndex < pWidth)
				{
					if(pWidth > (pThis->gPrivate_capacity >> 1))
						{tStartIndex = 0;}
					else
						{tStartIndex = (pThis->gPrivate_capacity >> 1);}
				}

				pThis->gPrivate_startIndex = tStartIndex;

				crx_c_ring_private_copyFromRingRange(pThis, 0, pArray, pStartIndex, pWidth);

				pThis->gPrivate_length = pWidth;

				vReturn = true;
			}
		}

		if(vIsSameArray)
		{
			crx_c_ring_destruct(vArray);
			free(vArray);
		}
	}

	return vReturn;
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_ring_copyAssignFrom(Crx_C_Ring * pThis, Crx_C_Ring * pArray)
	{return crx_c_ring_copyAssignFrom2(pThis, pArray, 0, pArray->gPrivate_length);}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_moveAndSetAt(Crx_C_Ring * pThis, size_t pIndex, void * pElement)
{
	assert(pIndex <= pThis->gPrivate_length);

	if(pThis->gPrivate_elements != NULL)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements + 
					(((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}
		
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + 
					(((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_elements + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_internalBuffer + 
					(((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}
		
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_internalBuffer + 
					(((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_internalBuffer + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_setAt(Crx_C_Ring * pThis, size_t pIndex, void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));
		crx_c_ring_moveAndSetAt(pThis, pIndex, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			crx_c_ring_moveAndSetAt(pThis, pIndex, vElement);
		}
		else
			{crx_c_ring_moveAndSetAt(pThis, pIndex, pElement);}
	}
	
	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)))
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}
}
CRX__LIB__PUBLIC_C_FUNCTION() unsigned char * crx_c_ring_get(Crx_C_Ring * pThis, size_t pIndex)
{
	assert(pIndex < pThis->gPrivate_length);

	if(pThis->gPrivate_elements != NULL)
	{
		return (pThis->gPrivate_elements + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
				pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
	}
	else
	{
		return (pThis->gPrivate_internalBuffer + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
				pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_copyGet(Crx_C_Ring const * pThis, unsigned char * pReturn, size_t pIndex)
{
	assert(pIndex < pThis->gPrivate_length);

	if(pThis->gPrivate_elements != NULL)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(pReturn,
					pThis->gPrivate_elements + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}
		else
		{
			memcpy(pReturn, pThis->gPrivate_elements + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(pReturn,
					pThis->gPrivate_internalBuffer + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}
		else
		{
			memcpy(pReturn, pThis->gPrivate_internalBuffer + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_ring_tryMoveAndPush(Crx_C_Ring * pThis, void * pElement)
{
	bool vIsNoError = true;

	if(pThis->gPrivate_length + 1 > pThis->gPrivate_capacity)
		{vIsNoError = crx_c_ring_ensureCapacity(pThis, pThis->gPrivate_length + 1);}

	if(vIsNoError)
	{
		if(pThis->gPrivate_elements != NULL)
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + 
						(((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pThis->gPrivate_capacity - 1)) * 
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
			}
			else
			{
				memcpy(pThis->gPrivate_elements + (((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pThis->gPrivate_capacity - 1)) *
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}
		else
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_internalBuffer + 
						(((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pThis->gPrivate_capacity - 1)) * 
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
			}
			else
			{
				memcpy(pThis->gPrivate_internalBuffer + (((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pThis->gPrivate_capacity - 1)) *
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}

		pThis->gPrivate_length = pThis->gPrivate_length + 1;

		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_ring_push(Crx_C_Ring * pThis, void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
	bool vReturn;

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));

		vReturn = crx_c_ring_tryMoveAndPush(pThis, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			vReturn = crx_c_ring_tryMoveAndPush(pThis, vElement);
		}
		else
			{vReturn = crx_c_ring_tryMoveAndPush(pThis, pElement);}
	}
	
	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)) &&
			vReturn)
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}

	return vReturn;	
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_moveAndFastPush(Crx_C_Ring * pThis, void * pElement)
{
	assert(pThis->gPrivate_capacity > pThis->gPrivate_length);

	if(pThis->gPrivate_elements != NULL)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + 
					(((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_elements + (((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_internalBuffer + 
					(((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_internalBuffer + (((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}

	pThis->gPrivate_length = pThis->gPrivate_length + 1;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_fastPush(Crx_C_Ring * pThis, void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));
		crx_c_ring_moveAndFastPush(pThis, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			crx_c_ring_moveAndFastPush(pThis, vElement);
		}
		else
			{crx_c_ring_moveAndFastPush(pThis, pElement);}
	}
	
	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)))
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_moveAndRoundPush(Crx_C_Ring * pThis, void * pElement)
{
	if(pThis->gPrivate_capacity == 0)
		{return;}

	if(pThis->gPrivate_elements != NULL)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{
			if(pThis->gPrivate_length == pThis->gPrivate_capacity)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements + 
						(pThis->gPrivate_startIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
			}
		}

		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + 
					(((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_elements + (((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{
			if(pThis->gPrivate_length == pThis->gPrivate_capacity)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_internalBuffer + 
						(pThis->gPrivate_startIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
			}
		}

		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + 
					(((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_internalBuffer + (((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}

	if(pThis->gPrivate_length != pThis->gPrivate_capacity)
		{pThis->gPrivate_length = pThis->gPrivate_length + 1;}
	else
	{
		if(pThis->gPrivate_startIndex == pThis->gPrivate_capacity - 1)
			{pThis->gPrivate_startIndex = 0;}
		else
			{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex + 1;}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_roundPush(Crx_C_Ring * pThis, void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));
		crx_c_ring_moveAndRoundPush(pThis, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			crx_c_ring_moveAndRoundPush(pThis, vElement);
		}
		else
			{crx_c_ring_moveAndRoundPush(pThis, pElement);}
	}
	
	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)))
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_pop(Crx_C_Ring * pThis)
{
	assert(pThis->gPrivate_length > 0);

	pThis->gPrivate_length--;

	if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
	{
		if(pThis->gPrivate_elements != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements + 
					(((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}
		else
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_internalBuffer + 
					(((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_ring_tryMoveAndPushToFront(Crx_C_Ring * pThis, void * pElement)
{
	bool vIsNoError = true;

	if(pThis->gPrivate_length + 1 > pThis->gPrivate_capacity)
		{vIsNoError = crx_c_ring_ensureCapacity(pThis, pThis->gPrivate_length + 1);}

	if(vIsNoError)
	{
		if(pThis->gPrivate_startIndex == 0)
			{pThis->gPrivate_startIndex = pThis->gPrivate_capacity - 1;}
		else
			{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex - 1;}

		if(pThis->gPrivate_elements != NULL)
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + 
						((pThis->gPrivate_startIndex & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
						(unsigned char *)(pElement));
			}
			else
			{
				memcpy(pThis->gPrivate_elements + ((pThis->gPrivate_startIndex & (pThis->gPrivate_capacity - 1)) * 
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}
		else
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_internalBuffer + 
						((pThis->gPrivate_startIndex & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
						(unsigned char *)(pElement));
			}
			else
			{
				memcpy(pThis->gPrivate_internalBuffer + ((pThis->gPrivate_startIndex & (pThis->gPrivate_capacity - 1)) * 
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}

		pThis->gPrivate_length = pThis->gPrivate_length + 1;

		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_ring_pushToFront(Crx_C_Ring * pThis, void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
	bool vReturn;

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));
		vReturn = crx_c_ring_tryMoveAndPushToFront(pThis, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			vReturn = crx_c_ring_tryMoveAndPushToFront(pThis, vElement);
		}
		else
			{vReturn = crx_c_ring_tryMoveAndPushToFront(pThis, pElement);}
	}
	
	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)) &&
			vReturn)
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}
		
	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_moveAndFastPushToFront(Crx_C_Ring * pThis, void * pElement)
{
	assert(pThis->gPrivate_capacity > pThis->gPrivate_length);

	if(pThis->gPrivate_startIndex == 0)
		{pThis->gPrivate_startIndex = pThis->gPrivate_capacity - 1;}
	else
		{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex - 1;}

	if(pThis->gPrivate_elements != NULL)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + 
					((pThis->gPrivate_startIndex & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
					(unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_elements + ((pThis->gPrivate_startIndex & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_internalBuffer + 
					((pThis->gPrivate_startIndex & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
					(unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_internalBuffer + ((pThis->gPrivate_startIndex & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}

	pThis->gPrivate_length = pThis->gPrivate_length + 1;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_fastPushToFront(Crx_C_Ring * pThis, void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));
		crx_c_ring_moveAndFastPushToFront(pThis, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			crx_c_ring_moveAndFastPushToFront(pThis, vElement);
		}
		else
			{crx_c_ring_moveAndFastPushToFront(pThis, pElement);}
	}

	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)))
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_moveAndRoundPushToFront(Crx_C_Ring * pThis, void * pElement)
{
	if(pThis->gPrivate_capacity == 0)
		{return;}

	if(pThis->gPrivate_startIndex == 0)
		{pThis->gPrivate_startIndex = pThis->gPrivate_capacity - 1;}
	else
		{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex - 1;}

	if(pThis->gPrivate_elements != NULL)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{
			if(pThis->gPrivate_length == pThis->gPrivate_capacity)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements + 
						((pThis->gPrivate_startIndex & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
			}
		}

		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + 
					((pThis->gPrivate_startIndex & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
					(unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_elements + ((pThis->gPrivate_startIndex & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{
			if(pThis->gPrivate_length == pThis->gPrivate_capacity)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_internalBuffer + 
						((pThis->gPrivate_startIndex & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
			}
		}

		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_internalBuffer + 
					((pThis->gPrivate_startIndex & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
					(unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_internalBuffer + ((pThis->gPrivate_startIndex & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement,
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}

	if(pThis->gPrivate_length != pThis->gPrivate_capacity)
		{pThis->gPrivate_length = pThis->gPrivate_length + 1;}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_roundPushToFront(Crx_C_Ring * pThis, void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));
		crx_c_ring_moveAndRoundPushToFront(pThis, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			crx_c_ring_moveAndRoundPushToFront(pThis, vElement);
		}
		else
			{crx_c_ring_moveAndRoundPushToFront(pThis, pElement);}
	}

	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)))
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_popFromFront(Crx_C_Ring * pThis)
{
	CRX_SCOPE_META
	assert(pThis->gPrivate_length > 0);

	CRX_SCOPE
	size_t vIndexOfReturn = pThis->gPrivate_startIndex;

	pThis->gPrivate_length--;

	if(pThis->gPrivate_startIndex == pThis->gPrivate_capacity - 1)
		{pThis->gPrivate_startIndex = 0;}
	else
		{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex - 1;}

	if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
	{
		if(pThis->gPrivate_elements != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements + 
					((vIndexOfReturn & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}
		else
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_internalBuffer + 
					((vIndexOfReturn & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}
	}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_ring_tryMoveAndInsertElementAt(Crx_C_Ring * pThis, size_t pIndex,
		void * pElement)
{
	if(crx_c_ring_private_insertSpaceAt(pThis, pIndex, 1))
	{
		if(pThis->gPrivate_elements != NULL)
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
			}
			else
			{
				memcpy(pThis->gPrivate_elements + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}
		else
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_internalBuffer + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
			}
			else
			{
				memcpy(pThis->gPrivate_internalBuffer + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}

		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_ring_insertElementAt(Crx_C_Ring * pThis, size_t pIndex, void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
	bool vReturn;

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));
		
		vReturn = crx_c_ring_tryMoveAndInsertElementAt(pThis, pIndex, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			vReturn = crx_c_ring_tryMoveAndInsertElementAt(pThis, pIndex, vElement);
		}
		else
			{vReturn = crx_c_ring_tryMoveAndInsertElementAt(pThis, pIndex, pElement);}
	}

	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)) &&
			vReturn)
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}
		
	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_moveAndFastInsertElementAt(Crx_C_Ring * pThis, size_t pIndex,
		void * pElement)
{
	crx_c_ring_private_fastInsertSpaceAt(pThis, pIndex, 1);

	if(pThis->gPrivate_elements != NULL)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_elements + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) *
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_internalBuffer + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_internalBuffer + (((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_fastInsertElementAt(Crx_C_Ring * pThis, size_t pIndex, void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));
		crx_c_ring_moveAndFastInsertElementAt(pThis, pIndex, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			crx_c_ring_moveAndFastInsertElementAt(pThis, pIndex, vElement);
		}
		else
			{crx_c_ring_moveAndFastInsertElementAt(pThis, pIndex, pElement);}
	}

	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)))
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_moveAndRoundInsertElementAt(Crx_C_Ring * pThis, size_t pIndex,
		void * pElement)
{
	Crx_C_Ring_Private_IndexTransform vIndexTransform = 
			crx_c_ring_private_roundInsertSpaceAt(pThis, pIndex, 1);

	if(pThis->gPrivate_elements != NULL)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + (((pThis->gPrivate_startIndex + vIndexTransform.gNewIndex) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_elements + (((pThis->gPrivate_startIndex + vIndexTransform.gNewIndex) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_internalBuffer + (((pThis->gPrivate_startIndex + vIndexTransform.gNewIndex) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), (unsigned char *)(pElement));
		}
		else
		{
			memcpy(pThis->gPrivate_internalBuffer + (((pThis->gPrivate_startIndex + vIndexTransform.gNewIndex) & (pThis->gPrivate_capacity - 1)) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_roundInsertElementAt(Crx_C_Ring * pThis, size_t pIndex, void * pElement)
{
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vElement, (unsigned char *)(pElement));
		crx_c_ring_moveAndRoundInsertElementAt(pThis, pIndex, vElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			crx_c_ring_moveAndRoundInsertElementAt(pThis, pIndex, vElement);
		}
		else
			{crx_c_ring_moveAndRoundInsertElementAt(pThis, pIndex, pElement);}
	}

	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || (pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)))
		{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vElement);}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_ring_insertElementsAt(Crx_C_Ring * pThis, size_t pIndex,
		Crx_C_Ring * pArray, size_t pStartIndex, size_t pWidth)
{
	CRX_SCOPE_META
	assert(pThis->gPrivate_typeBluePrint->gBYTE_SIZE == pArray->gPrivate_typeBluePrint->gBYTE_SIZE);

	if(pWidth == 0)
		{return true;}

	CRX_SCOPE
	Crx_C_Ring * vArray = pArray;
	bool vIsSameArray = CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis, pArray, true);
	bool vReturn = false;

	if(vIsSameArray)
	{
		size_t tCapacity;

#if(CRX__ARE_ONLY_POINTERS_TO_SAME_OBJECT_EQUAL_AND_ALWAYS)
		if((pStartIndex == 0) && (pWidth == pThis->gPrivate_length))
			{return true;}
#endif

		tCapacity = 1;
		while(tCapacity < pWidth)
			{tCapacity = (tCapacity << 1);}

		vArray = crx_c_ring_private_new2(pArray, pStartIndex, tCapacity);
	}

	if(vArray != NULL)
	{
		if(crx_c_ring_private_insertSpaceAt(pThis, pIndex, pWidth))
		{
			crx_c_ring_private_copyFromRingRange(pThis, pIndex, vArray, pStartIndex, pWidth);

			vReturn = true;
		}

		if(vIsSameArray)
		{
			crx_c_ring_destruct(vArray);
			free(vArray);
		}
	}

	return vReturn;
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_fastInsertElementsAt(Crx_C_Ring * pThis, size_t pIndex,
		Crx_C_Ring * pArray, size_t pStartIndex, size_t pWidth)
{
	assert(!CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis, pArray, false));

	if(pWidth == 0)
		{return;}

	crx_c_ring_private_fastInsertSpaceAt(pThis, pIndex, pWidth);

	crx_c_ring_private_copyFromRingRange(pThis, pIndex, pArray, pStartIndex, pWidth);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_roundInsertElementsAt(Crx_C_Ring * pThis, size_t pIndex,
		Crx_C_Ring * pArray, size_t pStartIndex, size_t pWidth)
{
	CRX_SCOPE_META
	assert(!CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis, pArray, false));

	if(pWidth == 0)
		{return;}

	CRX_SCOPE
	Crx_C_Ring_Private_IndexTransform vIndexTransform = 
			crx_c_ring_private_roundInsertSpaceAt(pThis, pIndex, pWidth);

	crx_c_ring_private_copyFromRingRange(pThis, vIndexTransform.gNewIndex, pArray, 
			pStartIndex, vIndexTransform.gNewCountToEnd);
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_ring_insertCArrayAt(Crx_C_Ring * pThis, size_t pIndex,
		void * pArray, size_t pWidth)
{
	if(pWidth == 0)
		{return true;}

	if(crx_c_ring_private_insertSpaceAt(pThis, pIndex, pWidth))
	{
		size_t tInsertIndex = (pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1);
		unsigned char * tTarget;

		if(pThis->gPrivate_elements != NULL)
			{tTarget = pThis->gPrivate_elements;}
		else
			{tTarget = pThis->gPrivate_internalBuffer;}

		if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
		{
			CRX_FOR(size_t tI = 0, tI < pWidth, tI++)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(tTarget + ((pThis->gPrivate_startIndex + pIndex + tI) & (pThis->gPrivate_capacity - 1)),
						(unsigned char *)(pArray) + tI);
			}
			CRX_ENDFOR
		}
		else
		{
			if((tInsertIndex < ((pThis->gPrivate_startIndex + pIndex + pWidth - 1) & (pThis->gPrivate_capacity - 1))) ||
					((pThis->gPrivate_capacity - tInsertIndex) >= pWidth))
			{
				memcpy(tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pArray, 
						pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
			else
			{
				memcpy(tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pArray,
						(pThis->gPrivate_capacity - tInsertIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
				memcpy(tTarget, (unsigned char *)(pArray) + ((pThis->gPrivate_capacity - tInsertIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						(pWidth - (pThis->gPrivate_capacity - tInsertIndex)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}

		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_fastInsertCArrayAt(Crx_C_Ring * pThis, size_t pIndex,
		void * pArray, size_t pWidth)
{
	CRX_SCOPE_META
	if(pWidth == 0)
		{return;}

	CRX_SCOPE
	size_t vInsertIndex;
	unsigned char * vTarget;
	
	crx_c_ring_private_fastInsertSpaceAt(pThis, pIndex, pWidth);

	vInsertIndex = (pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1);
	
	if(pThis->gPrivate_elements != NULL)
		{vTarget = pThis->gPrivate_elements;}
	else
		{vTarget = pThis->gPrivate_internalBuffer;}

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		CRX_FOR(size_t tI = 0, tI < pWidth, tI++)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vTarget + ((pThis->gPrivate_startIndex + pIndex + tI) & (pThis->gPrivate_capacity - 1)),
					(unsigned char *)(pArray) + tI);
		}
		CRX_ENDFOR
	}
	else
	{
		if((vInsertIndex < ((pThis->gPrivate_startIndex + pIndex + pWidth - 1) & (pThis->gPrivate_capacity - 1))) ||
				((pThis->gPrivate_capacity - vInsertIndex) >= pWidth))
		{
			memcpy(vTarget + (vInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pArray, 
					pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
		else
		{
			memcpy(vTarget + (vInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pArray,
					(pThis->gPrivate_capacity - vInsertIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			memcpy(vTarget, (unsigned char *)(pArray) + ((pThis->gPrivate_capacity - vInsertIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					(pWidth - (pThis->gPrivate_capacity - vInsertIndex)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_roundInsertCArrayAt(Crx_C_Ring * pThis, size_t pIndex,
		void * pArray, size_t pWidth)
{
	CRX_SCOPE_META
	if(pWidth == 0)
		{return;}

	CRX_SCOPE
	Crx_C_Ring_Private_IndexTransform vIndexTransform = 
			crx_c_ring_private_roundInsertSpaceAt(pThis, pIndex, pWidth);
	unsigned char * vTarget;

	if(pThis->gPrivate_elements != NULL)
		{vTarget = pThis->gPrivate_elements;}
	else
		{vTarget = pThis->gPrivate_internalBuffer;}

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		CRX_FOR(size_t tI = 0, tI < vIndexTransform.gNewCountToEnd, tI++)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vTarget + 
							(((pThis->gPrivate_startIndex + vIndexTransform.gNewIndex + tI) & 
							(pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					(unsigned char *)(pArray) + tI);
		}
		CRX_ENDFOR
	}
	else
	{
		size_t vInsertIndex = (pThis->gPrivate_startIndex + vIndexTransform.gNewIndex) & (pThis->gPrivate_capacity - 1);

		if((vInsertIndex < ((pThis->gPrivate_startIndex + vIndexTransform.gNewIndex + vIndexTransform.gNewCountToEnd - 1) & (pThis->gPrivate_capacity - 1))) ||
				((pThis->gPrivate_capacity - vInsertIndex) >= vIndexTransform.gNewCountToEnd))
		{
			memcpy(vTarget + (vInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pArray, 
					vIndexTransform.gNewCountToEnd * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
		else
		{
			memcpy(vTarget + (vInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pArray,
					(pThis->gPrivate_capacity - vInsertIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			memcpy(vTarget, (unsigned char *)(pArray) + ((pThis->gPrivate_capacity - vInsertIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					(vIndexTransform.gNewCountToEnd - (pThis->gPrivate_capacity - vInsertIndex)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}
	}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_ring_insertElementCopiesAt(Crx_C_Ring * pThis, size_t pIndex,
		void * pElement, size_t pNumberOfCopies)
{
	if(pNumberOfCopies == 0)
		{return true;}

	if(crx_c_ring_private_insertSpaceAt(pThis, pIndex, pNumberOfCopies))
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
				(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(tTarget + 
						(((pThis->gPrivate_startIndex + pIndex + tI) & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						(unsigned char *)(pElement));
			}
			CRX_ENDFOR
		}
		else
		{
			size_t tInsertIndex = (pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1);

			if((tInsertIndex < ((pThis->gPrivate_startIndex + pIndex + pNumberOfCopies - 1) & (pThis->gPrivate_capacity - 1))) ||
					((pThis->gPrivate_capacity - tInsertIndex) >= pNumberOfCopies))
			{
				size_t tNumberOfCopies = 1;
				size_t tRemainingNumberOfCopies = pNumberOfCopies - 1;

				memcpy(tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, 
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

				while(tRemainingNumberOfCopies > 0)
				{
					if(tRemainingNumberOfCopies >= tNumberOfCopies)
					{
						memcpy(tTarget + ((tInsertIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

						tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies;
						tNumberOfCopies = (tNumberOfCopies << 1);
					}
					else
					{
						memcpy(tTarget + ((tInsertIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								tRemainingNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

						break;
					}
				}
			}
			else
			{
				size_t tNumberOfCopies = 1;
				size_t tRemainingNumberOfCopies = pThis->gPrivate_capacity - tInsertIndex - 1;

				memcpy(tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, 
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

				while(tRemainingNumberOfCopies > 0)
				{
					if(tRemainingNumberOfCopies >= tNumberOfCopies)
					{
						memcpy(tTarget + ((tInsertIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

						tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies;
						tNumberOfCopies = (tNumberOfCopies << 1);
					}
					else
					{
						memcpy(tTarget + ((tInsertIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								tRemainingNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

						break;
					}
				}

				tRemainingNumberOfCopies = pNumberOfCopies - (pThis->gPrivate_capacity - tInsertIndex);

				if(tRemainingNumberOfCopies > pThis->gPrivate_capacity - tInsertIndex)
				{
					tNumberOfCopies = pThis->gPrivate_capacity - tInsertIndex;

					memcpy(tTarget, tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies;

					while(tRemainingNumberOfCopies > 0)
					{
						if(tRemainingNumberOfCopies >= tNumberOfCopies)
						{
							memcpy(tTarget + (tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), tTarget, 
									tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

							tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies;
							tNumberOfCopies = (tNumberOfCopies << 1);
						}
						else
						{
							memcpy(tTarget + (tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), tTarget,
									tRemainingNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

							break;
						}
					}
				}
				else
				{
					memcpy(tTarget, tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tRemainingNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
				}
			}
		}

		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_fastInsertElementCopiesAt(Crx_C_Ring * pThis, size_t pIndex,
		void * pElement, size_t pNumberOfCopies)
{
	CRX_SCOPE_META
	if(pNumberOfCopies == 0)
		{return;}

	CRX_SCOPE
	unsigned char * tTarget;
	
	crx_c_ring_private_fastInsertSpaceAt(pThis, pIndex, pNumberOfCopies);

	if(pThis->gPrivate_elements != NULL)
		{tTarget = pThis->gPrivate_elements;}
	else
		{tTarget = pThis->gPrivate_internalBuffer;}

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		CRX_FOR(size_t tI = 0, tI < pNumberOfCopies, tI++)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(tTarget + 
					(((pThis->gPrivate_startIndex + pIndex + tI) & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					(unsigned char *)(pElement));
		}
		CRX_ENDFOR
	}
	else
	{
		size_t tInsertIndex = (pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1);

		if((tInsertIndex < ((pThis->gPrivate_startIndex + pIndex + pNumberOfCopies - 1) & (pThis->gPrivate_capacity - 1))) ||
				((pThis->gPrivate_capacity - tInsertIndex) >= pNumberOfCopies))
		{
			size_t tNumberOfCopies = 1;
			size_t tRemainingNumberOfCopies = pNumberOfCopies - 1;

			memcpy(tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			while(tRemainingNumberOfCopies > 0)
			{
				if(tRemainingNumberOfCopies >= tNumberOfCopies)
				{
					memcpy(tTarget + ((tInsertIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies;
					tNumberOfCopies = (tNumberOfCopies << 1);
				}
				else
				{
					memcpy(tTarget + ((tInsertIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tRemainingNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					break;
				}
			}
		}
		else
		{
			size_t tNumberOfCopies = 1;
			size_t tRemainingNumberOfCopies = pThis->gPrivate_capacity - tInsertIndex - 1;

			memcpy(tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			while(tRemainingNumberOfCopies > 0)
			{
				if(tRemainingNumberOfCopies >= tNumberOfCopies)
				{
					memcpy(tTarget + ((tInsertIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies;
					tNumberOfCopies = (tNumberOfCopies << 1);
				}
				else
				{
					memcpy(tTarget + ((tInsertIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tRemainingNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					break;
				}
			}

			tRemainingNumberOfCopies = pNumberOfCopies - (pThis->gPrivate_capacity - tInsertIndex);

			if(tRemainingNumberOfCopies > pThis->gPrivate_capacity - tInsertIndex)
			{
				tNumberOfCopies = pThis->gPrivate_capacity - tInsertIndex;

				memcpy(tTarget, tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

				tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies;

				while(tRemainingNumberOfCopies > 0)
				{
					if(tRemainingNumberOfCopies >= tNumberOfCopies)
					{
						memcpy(tTarget + (tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), tTarget, 
								tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

						tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies;
						tNumberOfCopies = (tNumberOfCopies << 1);
					}
					else
					{
						memcpy(tTarget + (tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), tTarget,
								tRemainingNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

						break;
					}
				}
			}
			else
			{
				memcpy(tTarget, tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						tRemainingNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}
	}
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_roundInsertElementCopiesAt(Crx_C_Ring * pThis, size_t pIndex,
		void * pElement, size_t pNumberOfCopies)
{
	CRX_SCOPE_META
	if(pNumberOfCopies == 0)
		{return;}

	CRX_SCOPE
	Crx_C_Ring_Private_IndexTransform vIndexTransform = 
			crx_c_ring_private_roundInsertSpaceAt(pThis, pIndex, pNumberOfCopies);
	unsigned char * tTarget;

	if(pThis->gPrivate_elements != NULL)
		{tTarget = pThis->gPrivate_elements;}
	else
		{tTarget = pThis->gPrivate_internalBuffer;}

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		CRX_FOR(size_t tI = 0, tI < vIndexTransform.gNewCountToEnd, tI++)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(tTarget + 
							(((pThis->gPrivate_startIndex + vIndexTransform.gNewIndex + tI) & 
							(pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					(unsigned char *)(pElement));
		}
		CRX_ENDFOR
	}
	else
	{
		size_t tInsertIndex = (pThis->gPrivate_startIndex + vIndexTransform.gNewIndex) & (pThis->gPrivate_capacity - 1);

		if((tInsertIndex < ((pThis->gPrivate_startIndex + vIndexTransform.gNewIndex + vIndexTransform.gNewCountToEnd - 1) & 
				(pThis->gPrivate_capacity - 1))) ||
				((pThis->gPrivate_capacity - tInsertIndex) >= vIndexTransform.gNewCountToEnd))
		{
			size_t tNumberOfCopies = 1;
			size_t tRemainingNumberOfCopies = vIndexTransform.gNewCountToEnd - 1;

			memcpy(tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			while(tRemainingNumberOfCopies > 0)
			{
				if(tRemainingNumberOfCopies >= tNumberOfCopies)
				{
					memcpy(tTarget + ((tInsertIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies;
					tNumberOfCopies = (tNumberOfCopies << 1);
				}
				else
				{
					memcpy(tTarget + ((tInsertIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tRemainingNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					break;
				}
			}
		}
		else
		{
			size_t tNumberOfCopies = 1;
			size_t tRemainingNumberOfCopies = pThis->gPrivate_capacity - tInsertIndex - 1;

			memcpy(tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			while(tRemainingNumberOfCopies > 0)
			{
				if(tRemainingNumberOfCopies >= tNumberOfCopies)
				{
					memcpy(tTarget + ((tInsertIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies;
					tNumberOfCopies = (tNumberOfCopies << 1);
				}
				else
				{
					memcpy(tTarget + ((tInsertIndex + tNumberOfCopies) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tRemainingNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					break;
				}
			}

			tRemainingNumberOfCopies = vIndexTransform.gNewCountToEnd - 
					(pThis->gPrivate_capacity - tInsertIndex);

			if(tRemainingNumberOfCopies > pThis->gPrivate_capacity - tInsertIndex)
			{
				tNumberOfCopies = pThis->gPrivate_capacity - tInsertIndex;

				memcpy(tTarget, tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

				tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies;

				while(tRemainingNumberOfCopies > 0)
				{
					if(tRemainingNumberOfCopies >= tNumberOfCopies)
					{
						memcpy(tTarget + (tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), tTarget, 
								tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

						tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies;
						tNumberOfCopies = (tNumberOfCopies << 1);
					}
					else
					{
						memcpy(tTarget + (tNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), tTarget,
								tRemainingNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

						break;
					}
				}
			}
			else
			{
				memcpy(tTarget, tTarget + (tInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						tRemainingNumberOfCopies * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}
	}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_ring_removeElements(Crx_C_Ring * pThis, size_t pIndex,
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
		crx_c_ring_private_unsafeCallElementsDestruct(pThis, pIndex,
				(((pIndex + pWidth) <= pThis->gPrivate_length) ? (pIndex + pWidth - 1) : pThis->gPrivate_length - 1));
	}

	if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL) || 
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL))
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			if((pThis->gPrivate_length >> 1) < pIndex)
			{
				CRX_FOR(size_t tI = 0, tI < pIndex, tI++)
				{
					(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(tTarget + 
									(((pThis->gPrivate_startIndex + pIndex + pWidth - 1 - tI) & 
									(pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tTarget + (((pThis->gPrivate_startIndex + pIndex - 1 - tI) & 
									(pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

					if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)
					{
						(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(tTarget +
							(((pThis->gPrivate_startIndex + pIndex - 1 - tI) & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
					}
				}
				CRX_ENDFOR
				
				pThis->gPrivate_startIndex = (pThis->gPrivate_startIndex + pWidth) & (pThis->gPrivate_capacity - 1);
			}
			else
			{
				CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length - pWidth - pIndex, tI++)
				{
					(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(tTarget + 
									(((pThis->gPrivate_startIndex + tI + pIndex) & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tTarget + (((pThis->gPrivate_startIndex + tI + pIndex + pWidth) & 
									(pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

					if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)
					{
						(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(tTarget +
							(((pThis->gPrivate_startIndex + tI + pIndex + pWidth) & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
					}
				}
				CRX_ENDFOR
			}
		}
		else
		{
			if((pThis->gPrivate_length >> 1) < pIndex)
			{
				CRX_FOR(size_t tI = 0, tI < pIndex, tI++)
				{
					memmove(tTarget + (((pThis->gPrivate_startIndex + pIndex + pWidth - 1 - tI) & 
									(pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tTarget + (((pThis->gPrivate_startIndex + pIndex - 1 - tI) & 
									(pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(tTarget +
							(((pThis->gPrivate_startIndex + pIndex - 1 - tI) & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
				}
				CRX_ENDFOR
				
				pThis->gPrivate_startIndex = (pThis->gPrivate_startIndex + pWidth) & (pThis->gPrivate_capacity - 1);
			}
			else
			{
				CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length - pWidth - pIndex, tI++)
				{
					memmove(tTarget + (((pThis->gPrivate_startIndex + tI + pIndex) & (pThis->gPrivate_capacity - 1)) *
									pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							tTarget + (((pThis->gPrivate_startIndex + tI + pIndex + pWidth) & (pThis->gPrivate_capacity - 1)) * 
									pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(tTarget +
							(((pThis->gPrivate_startIndex + tI + pIndex + pWidth) & (pThis->gPrivate_capacity - 1)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
				}
				CRX_ENDFOR
			}
		}
	}
	else
	{
		if((pThis->gPrivate_length >> 1) < pIndex)
		{
			crx_c_ring_private_rawRotateRight(pThis, tTarget,
					pThis->gPrivate_startIndex, ((pThis->gPrivate_startIndex + pIndex - 1) & (pThis->gPrivate_capacity - 1)),
					pWidth);

			pThis->gPrivate_startIndex = (pThis->gPrivate_startIndex + pWidth) & (pThis->gPrivate_capacity - 1);
		}
		else
		{
			crx_c_ring_private_rawRotateLeft(pThis, tTarget,
					((pThis->gPrivate_startIndex + pIndex + pWidth) & (pThis->gPrivate_capacity - 1)),
					((pThis->gPrivate_startIndex + pThis->gPrivate_length - 1) & (pThis->gPrivate_capacity - 1)),
					pWidth);
		}
	}

	pThis->gPrivate_length = pThis->gPrivate_length - pWidth;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() unsigned char * crx_c_ring_getElementsPointer(Crx_C_Ring * pThis)
{
	if((pThis->gPrivate_internalBuffer == NULL) && (pThis->gPrivate_capacity == 0))
		{return NULL;}

	if(pThis->gPrivate_elements != NULL)
	{
		if(pThis->gPrivate_startIndex == 0)
			{return pThis->gPrivate_elements;}
		else if(pThis->gPrivate_startIndex <= ((pThis->gPrivate_startIndex + pThis->gPrivate_length - 1) & (pThis->gPrivate_capacity - 1)))
			{return pThis->gPrivate_elements + pThis->gPrivate_startIndex;}
		else
		{
			size_t tStartIndex = ((pThis->gPrivate_startIndexAlignFactor > 0) ? 
					(pThis->gPrivate_capacity >> pThis->gPrivate_startIndexAlignFactor) : 
					(pThis->gPrivate_capacity - (pThis->gPrivate_capacity >> abs(pThis->gPrivate_startIndexAlignFactor))));
			size_t tCapacity;
			unsigned char * tElements;
					
			if(pThis->gPrivate_capacity - tStartIndex < pThis->gPrivate_length)
			{
				if(pThis->gPrivate_length > (pThis->gPrivate_capacity >> 1))
					{tCapacity = pThis->gPrivate_capacity * 2;}
				else
				{
					tStartIndex = (pThis->gPrivate_capacity >> 1);
					tCapacity = pThis->gPrivate_capacity;
				}
			}
			else
				{tCapacity = pThis->gPrivate_capacity;}
			
			tElements = (unsigned char *)(malloc(tCapacity * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

			if(tElements != NULL)
			{
				crx_c_ring_private_moveElements(pThis, pThis->gPrivate_elements, 
						pThis->gPrivate_startIndex, pThis->gPrivate_length, pThis->gPrivate_capacity, 
						tElements + (tStartIndex * pThis->gSIZE_OF_INTERNAL_BUFFER));

				pThis->gPrivate_startIndex = tStartIndex;
				pThis->gPrivate_capacity = tCapacity;

				free(pThis->gPrivate_elements);

				pThis->gPrivate_elements = tElements;
				
				return pThis->gPrivate_elements + tStartIndex;
			}
			else
				{return NULL;}
		}
	}
	else
	{
		if(pThis->gPrivate_startIndex == 0)
			{return pThis->gPrivate_internalBuffer;}
		else if(pThis->gPrivate_startIndex <= ((pThis->gPrivate_startIndex + pThis->gPrivate_length - 1) & (pThis->gPrivate_capacity - 1)))
			{return pThis->gPrivate_internalBuffer + (pThis->gPrivate_startIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);}
		else
		{
			//unsigned char tElements[pSIZE_OF_INTERNAL_BUFFER];
			unsigned char * tElements = (unsigned char *)(malloc(pThis->gSIZE_OF_INTERNAL_BUFFER * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE));			

			if(tElements != NULL)
			{
				size_t tStartIndex = ((pThis->gPrivate_startIndexAlignFactor > 0) ? 
						(pThis->gSIZE_OF_INTERNAL_BUFFER >> pThis->gPrivate_startIndexAlignFactor) : 
						(pThis->gSIZE_OF_INTERNAL_BUFFER - (pThis->gSIZE_OF_INTERNAL_BUFFER >> abs(pThis->gPrivate_startIndexAlignFactor))));

				if(pThis->gSIZE_OF_INTERNAL_BUFFER - tStartIndex < pThis->gPrivate_length)
				{
					tStartIndex = (pThis->gSIZE_OF_INTERNAL_BUFFER >> 1);

					if(pThis->gSIZE_OF_INTERNAL_BUFFER - tStartIndex < pThis->gPrivate_length)
						{tStartIndex = 0;}
				}

				crx_c_ring_private_moveElements(pThis, pThis->gPrivate_internalBuffer, 
						pThis->gPrivate_startIndex, pThis->gPrivate_length, pThis->gSIZE_OF_INTERNAL_BUFFER,
						tElements);
				crx_c_ring_private_moveElements(pThis, tElements, 0,
						pThis->gPrivate_length, pThis->gSIZE_OF_INTERNAL_BUFFER,
						pThis->gPrivate_internalBuffer + (tStartIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
				pThis->gPrivate_startIndex = tStartIndex;
				
				free(tElements);

				return pThis->gPrivate_internalBuffer;
			}
			else
				{return NULL;}
		}
	}
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_ring_private_doInsertSpaceAt(Crx_C_Ring * pThis, size_t pIndex, size_t pWidth)
{
	assert(pWidth <= (pThis->gPrivate_capacity - pThis->gPrivate_length));

	if(pIndex == 0)
	{
		if(pThis->gPrivate_startIndex > pWidth)
			{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex - pWidth;}
		else
			{pThis->gPrivate_startIndex = pThis->gPrivate_capacity - (pWidth - pThis->gPrivate_startIndex);}
	}
	else if(pIndex == pThis->gPrivate_length)
		{}
	else
	{
		unsigned char * vTarget = NULL;
		size_t vInsertIndex = (pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1);

		assert(vInsertIndex != pThis->gPrivate_startIndex);

		if(pThis->gPrivate_internalBuffer != NULL)
		{
			if(pThis->gPrivate_elements != NULL)
				{vTarget = pThis->gPrivate_elements;}
			else
				{vTarget = pThis->gPrivate_internalBuffer;}
		}
		else
			{vTarget = pThis->gPrivate_elements;}

		if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL) ||
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL))
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				CRX_FOR(size_t tI = pThis->gPrivate_length - 1, tI >= pIndex, tI--)
				{
					(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(
							vTarget + (((pThis->gPrivate_startIndex + tI + pWidth) & (pThis->gPrivate_capacity - 1)) * 
									pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							vTarget + (((pThis->gPrivate_startIndex + tI) & (pThis->gPrivate_capacity - 1)) * 
									pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

					if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
					{
						(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vTarget +
							(((pThis->gPrivate_startIndex + tI) & (pThis->gPrivate_capacity - 1)) * 
							pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
					}
				}
				CRX_ENDFOR
			}
			else
			{
				CRX_FOR(size_t tI = pThis->gPrivate_length - 1, tI > pIndex, tI--)
				{
					memmove(vTarget + (((pThis->gPrivate_startIndex + tI + pWidth) & (pThis->gPrivate_capacity - 1)) * 
									pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							vTarget + (((pThis->gPrivate_startIndex + tI) & (pThis->gPrivate_capacity - 1)) * 
									pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

					(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(vTarget +
							(((pThis->gPrivate_startIndex + tI) & (pThis->gPrivate_capacity - 1)) * 
							pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
				}
				CRX_ENDFOR
			}
		}
		else
		{
			if((pThis->gPrivate_length >> 1) >= pIndex)
			{
				if(pThis->gPrivate_startIndex >= pWidth)
				{
					if(pThis->gPrivate_startIndex + 1 <= vInsertIndex)
					{
						memmove(vTarget + ((pThis->gPrivate_startIndex - pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								vTarget + (pThis->gPrivate_startIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
								(vInsertIndex - pThis->gPrivate_startIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
					}
					else
					{
						memmove(vTarget + ((pThis->gPrivate_startIndex - pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								vTarget + (pThis->gPrivate_startIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								(pThis->gPrivate_capacity - pThis->gPrivate_startIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

						if(vInsertIndex <= pWidth)
						{
							memmove(vTarget + ((pThis->gPrivate_capacity - pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
									vTarget, vInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
						}
						else
						{
							memmove(vTarget + ((pThis->gPrivate_capacity - pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
									vTarget, pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
							memmove(vTarget,
									vTarget + (pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
									(vInsertIndex - pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
						}
					}

					pThis->gPrivate_startIndex = pThis->gPrivate_startIndex - pWidth;
				}
				else
				{
					if(pWidth < vInsertIndex)
					{
						memmove(vTarget + ((pThis->gPrivate_capacity - (pWidth - pThis->gPrivate_startIndex)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								vTarget + (pThis->gPrivate_startIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								(pWidth - pThis->gPrivate_startIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
						memmove(vTarget, vTarget + (pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								(vInsertIndex - pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
					}
					else
					{
						memmove(vTarget + ((pThis->gPrivate_capacity - (pWidth - pThis->gPrivate_startIndex)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								vTarget + (pThis->gPrivate_startIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								(vInsertIndex - pThis->gPrivate_startIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
					}
					pThis->gPrivate_startIndex = pThis->gPrivate_capacity - (pWidth - pThis->gPrivate_startIndex);
				}
			}
			else
			{
				size_t tEndIndex = (pThis->gPrivate_startIndex + pThis->gPrivate_length - 1) & (pThis->gPrivate_capacity - 1);

				if(pThis->gPrivate_capacity - 1 - tEndIndex >= pWidth)
				{
					if(tEndIndex + 1 >= vInsertIndex)
					{
						memmove(vTarget + ((vInsertIndex + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								vTarget + (vInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								(tEndIndex  + 1 - vInsertIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
					}
					else
					{
						memmove(vTarget + (pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), vTarget, (tEndIndex + 1) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

						if(pThis->gPrivate_capacity - vInsertIndex <= pWidth)
						{
							memmove(vTarget + ((pWidth - (pThis->gPrivate_capacity - vInsertIndex)) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
									vTarget + (vInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
									(pThis->gPrivate_capacity - vInsertIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
						}
						else
						{
							memmove(vTarget, vTarget + ((pThis->gPrivate_capacity - pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
									pWidth * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
							memmove(vTarget + ((vInsertIndex + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
									vTarget + (vInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
									(pThis->gPrivate_capacity - pWidth - vInsertIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
						}
					}
				}
				else
				{
					if(pThis->gPrivate_capacity - pWidth > vInsertIndex)
					{
						memmove(vTarget, vTarget + ((pThis->gPrivate_capacity - pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								(tEndIndex + pWidth + 1 - pThis->gPrivate_capacity) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
						memmove(vTarget + ((vInsertIndex + pWidth) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								vTarget + (vInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								(pThis->gPrivate_capacity - pWidth - vInsertIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
					}
					else
					{
						memmove(vTarget, vTarget + (vInsertIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
								(tEndIndex + 1 - vInsertIndex) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
					}
				}
			}
		}
	}

	pThis->gPrivate_length = pThis->gPrivate_length + pWidth;
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_ring_private_copyFromRingRange(Crx_C_Ring * pThis, size_t pIndex,
		Crx_C_Ring const * pArray, size_t pStartIndex, size_t pWidth)
{
	unsigned char * vTarget = ((pThis->gPrivate_internalBuffer != NULL) ? 
			((pThis->gPrivate_elements != NULL) ? pThis->gPrivate_elements : pThis->gPrivate_internalBuffer) : 
			pThis->gPrivate_elements);
	unsigned char * vSource = ((pArray->gPrivate_internalBuffer != NULL) ? 
			((pArray->gPrivate_elements != NULL) ? pArray->gPrivate_elements : pArray->gPrivate_internalBuffer) : 
			pArray->gPrivate_elements);

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		CRX_FOR(size_t tI = 0, tI < pWidth, tI++)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(vTarget + ((pThis->gPrivate_startIndex + tI + pIndex) & (pThis->gPrivate_capacity - 1)),
					vSource + ((pArray->gPrivate_startIndex + tI + pStartIndex) & (pArray->gPrivate_capacity - 1)));
		}
		CRX_ENDFOR
	}
	else
	{
		size_t tTargetStartIndex = ((pThis->gPrivate_startIndex + pIndex) & (pThis->gPrivate_capacity - 1));
		size_t tTargetSegmentLength = ((tTargetStartIndex >= pThis->gPrivate_startIndex) ?
				((((pThis->gPrivate_startIndex + pIndex + pWidth - 1) & (pThis->gPrivate_capacity - 1)) > tTargetStartIndex) ?
						pWidth : (pThis->gPrivate_capacity - tTargetStartIndex)) :
				pWidth);
		size_t tSourceStartIndex = ((pArray->gPrivate_startIndex + pStartIndex) & (pArray->gPrivate_capacity - 1));
		size_t tSourceLength = ((tSourceStartIndex >= pArray->gPrivate_startIndex) ?
				((((pArray->gPrivate_startIndex + pIndex + pWidth - 1) & (pArray->gPrivate_capacity - 1)) > tSourceStartIndex) ?
						pWidth : (pArray->gPrivate_capacity - tSourceStartIndex)) :
				pWidth);

		if(tTargetSegmentLength <= tSourceLength)
		{
			memcpy(vTarget + (tTargetStartIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), vSource + (tSourceStartIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					tTargetSegmentLength * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			if(tTargetSegmentLength < pWidth)
			{
				assert(((pThis->gPrivate_startIndex + pIndex + tTargetSegmentLength) & (pThis->gPrivate_capacity - 1)) == 0);

				memcpy(vTarget, vSource + ((tSourceStartIndex + tTargetSegmentLength) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						(tSourceLength - tTargetSegmentLength) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

				if(tSourceLength < pWidth)
				{
					assert(((pArray->gPrivate_startIndex + tSourceStartIndex + tSourceLength) & (pThis->gPrivate_capacity - 1)) == 0);

					memcpy(vTarget + ((tTargetStartIndex + tSourceLength - tTargetSegmentLength) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							vSource, (pWidth - tSourceLength) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
				}
			}
		}
		else
		{
			memcpy(vTarget + (tTargetStartIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), vSource + (tSourceStartIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					tSourceLength * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			assert(((pArray->gPrivate_startIndex + pIndex + tSourceLength) & (pThis->gPrivate_capacity - 1)) == 0);

			memcpy(vTarget + ((tTargetStartIndex + tSourceLength) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), vSource,
					(tTargetSegmentLength - tSourceLength) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			if(tTargetSegmentLength < pWidth)
			{
				assert(((pThis->gPrivate_startIndex + pIndex + tTargetSegmentLength) & (pThis->gPrivate_capacity - 1)) == 0);

				memcpy(vTarget, vSource + ((tTargetSegmentLength - tSourceLength) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						(pWidth - tTargetSegmentLength) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}
		}
	}
}

/*WARNING: THE FOLLOWING ASSUMES THAT THE REMAINING SPACE IS LARGER THAN pWIDTH. THIS MEANS THAT
		IT IS ASSUMED THAT THE TAIL WILL NEVER HIT THE ORIGINAL LOCATION OF THE HEAD AFTER ROTATION.*/
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_ring_private_rawRotateRight(Crx_C_Ring * pThis, unsigned char * pElements,
		size_t pRawStartIndex, size_t pRawEndIndex, size_t pWidth /*, bool pIsToSetNewRawEndIndex*/)
{
	CRX_SCOPE_META
	assert(pWidth > 0);

	CRX_SCOPE
	size_t tEmptySpaceBeforeEnd /*= ?*/;

	if(pRawEndIndex < pRawStartIndex)
		{tEmptySpaceBeforeEnd = 0;}
	else
		{tEmptySpaceBeforeEnd = pThis->gPrivate_capacity - pRawEndIndex - 1;}

	if(pRawEndIndex < pRawStartIndex)
	{
		memmove(pElements + (pWidth * pThis->gSIZE_OF_INTERNAL_BUFFER), pElements,
				pRawEndIndex * pThis->gSIZE_OF_INTERNAL_BUFFER);
	}

	if(pWidth <= tEmptySpaceBeforeEnd)
	{
		memmove(pElements + ((pRawStartIndex + pWidth) * pThis->gSIZE_OF_INTERNAL_BUFFER), 
				pElements + (pRawStartIndex * pThis->gSIZE_OF_INTERNAL_BUFFER),
				(pRawEndIndex + 1 - pRawStartIndex) * pThis->gSIZE_OF_INTERNAL_BUFFER);

		/*CRXM__IFELSE2(pNEW_RAW_END_INDEX,
		pNEW_RAW_END_INDEX = pRawEndIndex + pWidth;, ) \*/
	}
	else
	{
		if(pWidth < pThis->gPrivate_capacity - pRawStartIndex)
		{
			memcpy(pElements, 
					pElements + ((pThis->gPrivate_capacity - (pWidth - tEmptySpaceBeforeEnd)) * pThis->gSIZE_OF_INTERNAL_BUFFER),
					(pWidth - tEmptySpaceBeforeEnd) * pThis->gSIZE_OF_INTERNAL_BUFFER);

			memmove(pElements + ((pRawStartIndex + pWidth) * pThis->gSIZE_OF_INTERNAL_BUFFER), 
					pElements + (pRawStartIndex * pThis->gSIZE_OF_INTERNAL_BUFFER),
					(pThis->gPrivate_capacity - pRawStartIndex  - pWidth) * pThis->gSIZE_OF_INTERNAL_BUFFER);

			/*CRXM__IFELSE2(pNEW_RAW_END_INDEX,
			pNEW_RAW_END_INDEX = pWidth - tEmptySpaceBeforeEnd - 1;, ) \*/
		}
		else
		{
			memcpy(pElements + ((pWidth - (pThis->gPrivate_capacity - pRawStartIndex)) * pThis->gSIZE_OF_INTERNAL_BUFFER),
					pElements + (pRawStartIndex * pThis->gSIZE_OF_INTERNAL_BUFFER),
					(pThis->gPrivate_capacity - tEmptySpaceBeforeEnd - pRawStartIndex) * pThis->gSIZE_OF_INTERNAL_BUFFER);

			/*CRXM__IFELSE2(pNEW_RAW_END_INDEX, \
			pNEW_RAW_END_INDEX = pWidth - tEmptySpaceBeforeEnd - 1;, ) \*/
		}
	}
	CRX_SCOPE_END
}

/*WARNING: THE FOLLOWING ASSUMES THAT THE REMAINING SPACE IS LARGER THAN pWIDTH. THIS MEANS THAT
		IT IS ASSUMED THAT THE HEAD WILL NEVER HIT THE ORIGINAL LOCATION OF THE TAIL AFTER ROTATION.*/
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_ring_private_rawRotateLeft(Crx_C_Ring * pThis, unsigned char * pElements,
		size_t pRawStartIndex, size_t pRawEndIndex, size_t pWidth /*, bool pIsToSetNewRawStartIndex*/)
{
	CRX_SCOPE_META
	assert(pWidth > 0);

	CRX_SCOPE
	size_t tIndexOfFirstElementFromLeftSide /*= ?*/;

	if(pRawStartIndex >= pRawEndIndex)
		{tIndexOfFirstElementFromLeftSide = 0;}
	else
		{tIndexOfFirstElementFromLeftSide = pRawStartIndex;}

	if(pRawStartIndex >= pRawEndIndex)
	{
		memmove(pElements + ((pRawStartIndex - pWidth) * pThis->gSIZE_OF_INTERNAL_BUFFER),
				pElements + (pRawStartIndex * pThis->gSIZE_OF_INTERNAL_BUFFER),
				(pThis->gPrivate_capacity - pRawStartIndex) * pThis->gSIZE_OF_INTERNAL_BUFFER);
	}

	if(pWidth <= tIndexOfFirstElementFromLeftSide)
	{
		memcpy(pElements + ((pRawStartIndex - pWidth) * pThis->gSIZE_OF_INTERNAL_BUFFER),
				pElements + (pRawStartIndex * pThis->gSIZE_OF_INTERNAL_BUFFER),
				(pRawStartIndex + 1 - pRawStartIndex) * pThis->gSIZE_OF_INTERNAL_BUFFER);

		/*CRXM__IFELSE2(pNEW_RAW_START_INDEX,
		pNEW_RAW_START_INDEX = pRawStartIndex - pWidth;, )*/
	}
	else
	{
		if(pWidth <= pRawEndIndex)
		{
			memcpy(pElements + ((pThis->gPrivate_capacity + tIndexOfFirstElementFromLeftSide - pWidth) * 
							pThis->gSIZE_OF_INTERNAL_BUFFER),
					pElements + (tIndexOfFirstElementFromLeftSide * pThis->gSIZE_OF_INTERNAL_BUFFER),
					(pWidth - tIndexOfFirstElementFromLeftSide) * pThis->gSIZE_OF_INTERNAL_BUFFER);

			memcpy(pElements, pElements + (pWidth * pThis->gSIZE_OF_INTERNAL_BUFFER),
					(pRawEndIndex + 1 - pWidth) * pThis->gSIZE_OF_INTERNAL_BUFFER);

			/*CRXM__IFELSE2(pNEW_RAW_START_INDEX,
			pNEW_RAW_START_INDEX = pThis->gPrivate_capacity - (pWidth - tIndexOfFirstElementFromLeftSide);, ) \ */
		}
		else
		{
			memcpy(pElements + ((pThis->gPrivate_capacity + tIndexOfFirstElementFromLeftSide - pWidth) * 
							pThis->gSIZE_OF_INTERNAL_BUFFER),
					pElements + (tIndexOfFirstElementFromLeftSide * pThis->gSIZE_OF_INTERNAL_BUFFER),
					(pRawEndIndex + 1 - tIndexOfFirstElementFromLeftSide) * pThis->gSIZE_OF_INTERNAL_BUFFER);

			/*CRXM__IFELSE2(pNEW_RAW_START_INDEX,
			pNEW_RAW_START_INDEX = pThis->gPrivate_capacity - (pWidth - tIndexOfFirstElementFromLeftSide);, ) \ */
		}
	}
	CRX_SCOPE_END
}


CRX__LIB__C_CODE_END()

