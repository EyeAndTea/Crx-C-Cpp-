//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/HashTable.h"

#include "Crx/H/crx/c/TypeBluePrint.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()

CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_hashTable_compute32BitsHash(
		size_t pSeed, void const * CRX_NOT_NULL pBytes, size_t pSize)
{
	//SEE MY MATLAB SCRIPT WRITTEN FOR GNU OCTAVE FOR FURTHER ANALYSIS
	//		DETAILS. IT APPEARS THAT THE ORIGINAL KHASH HASH FUNCTION 
	//		WHICH APPEARS TO BE A SLIGHT VARIATION OF THE HASH FUNCTION
	//		CALLED DJB, WHICH APPEARS TO BE NAMED AFTER ITS MAKER, 
	//		PROFESSOR DANIEL J. BERNSTEIN, REMAINS THE BEST BUT IS NOT 
	//		SAFE. ANY INPUT OF TWO BYTES ONLY, WITH	EQUAL VALUES CAN BE
	//		USED TO ATTACK SMALL HASH TABLES, BASED ON MY TESTING AND 
	//		ANALYSIS, CAUSING ONLY ONE BUCKET TO BE FILLED NO MATTER 
	//		THE GENERATED HASH. 
	//		NOTE THAT THE ORIGINAL DJB ALGORITHM MULTIPLIED BY 33 RATHER THAN
	//		31.
	unsigned char * vBytes = ((unsigned char *)pBytes);
	uint32_t vUInt32 = 0;

	for(; pSize; --pSize)
		{vUInt32 = (vUInt32 << 5) - vUInt32 + ((uint32_t)(*(vBytes++)));}
	
	
	
	/*uint32_t vUInt32 = 0; //((uint32_t)*pBytes);
	size_t vCount = pSize;
	uint32_t vStep = 1;

	for(; vCount; ++pBytes)
	{
		//vUInt32 = (vUInt32 << 5) - vUInt32 + ((uint32_t)*pBytes);	REFERENCE
		vUInt32 = (vUInt32 << 5) - vUInt32 + ((((uint32_t)*pBytes) + ++vStep) & 0xff);
		vCount--;
	}
	
	vUInt32 = (vUInt32 << 5) - vUInt32 + (pSize & 0xff);

	return vUInt32;
	
	/*
	vUInt32 += ~(vUInt32 << 15);
    vUInt32 ^=  (vUInt32 >> 10);
    vUInt32 +=  (vUInt32 << 3);
    vUInt32 ^=  (vUInt32 >> 6);
    vUInt32 += ~(vUInt32 << 11);
    vUInt32 ^=  (vUInt32 >> 16);

    return vUInt32;*/
	
	
	//"Paul Larson of Microsoft Research"
	/*unsigned vUInt32 = salt;
    while (*pBytes)
        vUInt32 = vUInt32 * 101 + (unsigned) *pBytes++;
    return vUInt32;* / */
}

CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_hashTable_computeSafer32BitsHash(
		size_t pSeed, void const * CRX_NOT_NULL pBytes, size_t pSize)
{
	//SEE MY MATLAB SCRIPT WRITTEN FOR GNU OCTAVE FOR FURTHER ANALYSIS
	//		DETAILS. A SAFER IMPLEMENTATION FOR GENERIC DATA.
	unsigned char * vBytes = ((unsigned char *)pBytes);
	uint32_t vUInt32 = (uint32_t)pSeed;

	for(; pSize; --pSize)
		{vUInt32 = (vUInt32 << 5) - vUInt32 + ((uint32_t)(*(vBytes++)));}
	
	vUInt32 += ~(vUInt32 << 15);
    vUInt32 ^=  (vUInt32 >> 10);
    vUInt32 +=  (vUInt32 << 3);
    vUInt32 ^=  (vUInt32 >> 6);
    vUInt32 += ~(vUInt32 << 11);
    vUInt32 ^=  (vUInt32 >> 16);

	return vUInt32;
}


CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_hashTable_areUint8sEqual(void const * pUint8,
		void const * pUint8__2)
	{return *((uint8_t *)pUint8) == *((uint8_t *)pUint8__2);}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_hashTable_getHashKeyForUint8(void const * pUint8)
	{return *((uint8_t *)pUint8);}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_hashTable_areUint16sEqual(void const * pUint16,
		void const * pUint16__2)
	{return *((uint16_t *)pUint16) == *((uint16_t *)pUint16__2);}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_hashTable_getHashKeyForUint16(void const * pUint16)
	{return *((uint16_t *)pUint16);}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_hashTable_areUint32sEqual(void const * pUint32,
		void const * pUint32__2)
	{return ((*((uint32_t *)pUint32)) == (*((uint32_t *)pUint32__2)));}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_hashTable_getHashKeyForUint32(void const * pUint32)
	{return *((uint32_t *)pUint32);}

#if(!defined(CRX__BOOST_NO_INT64_T))
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_hashTable_areUint64sEqual(void const * pUint64,
		void const * pUint64__2)
	{return ((*((uint64_t *)pUint64)) == (*((uint64_t *)pUint64__2)));}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_hashTable_getHashKeyForUint64(void const * pUint64)
	{return (size_t)(*((uint64_t *)pUint64));}
#endif
	
////////////
////////////

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_hashTable_construct(Crx_C_HashTable * pThis,
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__element,
		Crx_C_TypeBluePrint_AreObjectsEqual CRX_NOT_NULL pAreKeysEqual,
		Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey)
{
	crx_c_hashTable_private_doInit(pThis, pTypeBluePrint__key, pAreKeysEqual,
			pGetHashForKey, pTypeBluePrint__element);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_hashTable_construct2(Crx_C_HashTable * pThis,
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
		Crx_C_TypeBluePrint_AreObjectsEqual CRX_NOT_NULL pAreKeysEqual,
		Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey)
{
	crx_c_hashTable_private_doInit(pThis, pTypeBluePrint__key, pAreKeysEqual,
			pGetHashForKey, NULL);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_hashTable_copyConstruct(
		Crx_C_HashTable * pThis, Crx_C_HashTable const * CRX_NOT_NULL pHashTable)
{
	if(!pHashTable->gPrivate_typeBluePrint__key->gIS_COPYABLE ||
			((pHashTable->gPrivate_typeBluePrint__element != NULL) &&
			!pHashTable->gPrivate_typeBluePrint__element->gIS_COPYABLE))
		{abort();}

	CRX__SET_TO_ZERO(Crx_C_HashTable, *pThis);

	if(crx_c_hashTable_private_setCapacity(pThis, pHashTable->gPrivate_size))
	{
		CRX_FOR(size_t tI = 0, tI != pHashTable->gPrivate_numberOfBuckets, ++tI)
		{
			if(CRX__C__HashTable__IS_BUCKET_EMPTY(pHashTable->gPrivate_bucketData, tI))
				{continue;}

			
			if(pHashTable->gPrivate_typeBluePrint__element != NULL)
			{
				crx_c_hashTable_set(pThis, pHashTable->gPrivate_keys + 
						(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE),
						pHashTable->gPrivate_elements + 
						(tI * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
			}
			else
			{
				crx_c_hashTable_set(pThis, pHashTable->gPrivate_keys + 
						(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), NULL);
			}
		}
		CRX_ENDFOR
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_HashTable * crx_c_hashTable_new(
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
		Crx_C_TypeBluePrint const *  pTypeBluePrint__element,
		Crx_C_TypeBluePrint_AreObjectsEqual CRX_NOT_NULL pAreKeysEqual,
		Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey)
{
	Crx_C_HashTable * vReturn = (Crx_C_HashTable *)(calloc(1,
			sizeof(Crx_C_HashTable)));

	if(vReturn != NULL)
	{
		crx_c_hashTable_construct(vReturn, pTypeBluePrint__key, pTypeBluePrint__element,
				pAreKeysEqual, pGetHashForKey);
	}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_HashTable * crx_c_hashTable_new2(
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
		Crx_C_TypeBluePrint_AreObjectsEqual CRX_NOT_NULL pAreKeysEqual,
		Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey)
{
	Crx_C_HashTable * vReturn = (Crx_C_HashTable *)(calloc(1,
			sizeof(Crx_C_HashTable)));

	if(vReturn != NULL)
	{
		crx_c_hashTable_construct2(vReturn, pTypeBluePrint__key, pAreKeysEqual,
				pGetHashForKey);
	}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_HashTable * crx_c_hashTable_moveNew(
		Crx_C_HashTable * CRX_NOT_NULL pHashTable)
{
	Crx_C_HashTable * vReturn = (Crx_C_HashTable *)(calloc(1,
			sizeof(Crx_C_HashTable)));

	if(vReturn != NULL)
		{memcpy(vReturn, pHashTable, sizeof(Crx_C_HashTable));}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_HashTable * crx_c_hashTable_copyNew(
		Crx_C_HashTable const * CRX_NOT_NULL pHashTable)
{
	CRX_SCOPE_META
	if(!pHashTable->gPrivate_typeBluePrint__key->gIS_COPYABLE ||
			((pHashTable->gPrivate_typeBluePrint__element != NULL) &&
			!pHashTable->gPrivate_typeBluePrint__element->gIS_COPYABLE))
		{abort();}

	CRX_SCOPE
	Crx_C_HashTable * vReturn = (Crx_C_HashTable *)(calloc(1,
			sizeof(Crx_C_HashTable)));

	if(vReturn != NULL)
		{crx_c_hashTable_copyConstruct(vReturn, pHashTable);}

	return vReturn;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_hashTable_destruct(Crx_C_HashTable * pThis)
{
	if((pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT != NULL) ||
			((pThis->gPrivate_typeBluePrint__element != NULL) &&
			(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)))
		{crx_c_hashTable_empty(pThis);}

	free((void *) pThis->gPrivate_keys);
	pThis->gPrivate_keys = NULL;
	free(pThis->gPrivate_bucketData);
	pThis->gPrivate_bucketData = NULL;

	if(pThis->gPrivate_typeBluePrint__element != NULL)
	{
		free((void *) pThis->gPrivate_elements);
		pThis->gPrivate_elements = NULL;
	}
	
	CRX__C__TYPE_BLUE_PRINT__GENERIC__FINALIZE(pThis->gPrivate_typeBluePrint__key);
	if(pThis->gPrivate_typeBluePrint__element != NULL)
		{CRX__C__TYPE_BLUE_PRINT__GENERIC__FINALIZE(pThis->gPrivate_typeBluePrint__element);}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_hashTable_free(Crx_C_HashTable * pThis)
	{free(pThis);}

CRX__C__TYPE_BLUE_PRINT__GENERIC__DEFINE_GET_BLUE_PRINT(
		Crx_C_HashTable, crx_c_hashTable_,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__FALSE, CRXM__FALSE,
		true, true,
		(!pThis->gPrivate_typeBluePrint__key->gIS_COPYABLE ||
				((pThis->gPrivate_typeBluePrint__element != NULL) &&
				!pThis->gPrivate_typeBluePrint__element->gIS_COPYABLE)), true,
		false, false)

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_hashTable_private_doInit(Crx_C_HashTable * pThis,
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
		Crx_C_TypeBluePrint_AreObjectsEqual CRX_NOT_NULL pAreKeysEqual,
		Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey,
		Crx_C_TypeBluePrint const *  pTypeBluePrint__element)
{
	assert((pTypeBluePrint__key != NULL) && CRX__C__TYPE_BLUE_PRINT__IS_CORRECT_FORM(
			pTypeBluePrint__key) && (pAreKeysEqual != NULL) && (pGetHashForKey != NULL) &&
			(pTypeBluePrint__key->gFUNC__GET_BYTE_SIZE_OF == NULL));
	assert((pTypeBluePrint__element == NULL) || (CRX__C__TYPE_BLUE_PRINT__IS_CORRECT_FORM(
			pTypeBluePrint__element) && 
			(pTypeBluePrint__element->gFUNC__GET_BYTE_SIZE_OF == NULL)));

	CRX__SET_TO_ZERO(Crx_C_HashTable, *pThis);

	pThis->gPrivate_typeBluePrint__key = pTypeBluePrint__key;
	pThis->gPrivate_typeBluePrint__element = pTypeBluePrint__element;
	pThis->gPrivate_bucketData = NULL;
	pThis->gPrivate_keys = NULL;
	pThis->gPrivate_elements = NULL;
	pThis->gPrivate_areKeysEqual = pAreKeysEqual;
	pThis->gPrivate_getHashForKey = pGetHashForKey;
}

CRX__LIB__PRIVATE_C_FUNCTION() size_t crx_c_hashTable_private_get(Crx_C_HashTable const * pThis,
		void const * CRX_NOT_NULL pKey)
{
	CRX_SCOPE_META
	if(pThis->gPrivate_numberOfBuckets == 0)
		{return 0;}

	CRX_SCOPE
	size_t vMask = pThis->gPrivate_numberOfBuckets - 1;
	size_t vIndex = (*(pThis->gPrivate_getHashForKey))(pThis->gPrivate_seed, pKey) & vMask;
	size_t vLastIndex = vIndex;
	size_t vStep = 0;

	while(!CRX__C__HashTable__WAS_BUCKET_NEVER_FILLED(pThis->gPrivate_bucketData, vIndex) &&
			(CRX__C__HashTable__IS_BUCKET_CONTENT_DELETED(pThis->gPrivate_bucketData, vIndex) ||
			!(*(pThis->gPrivate_areKeysEqual))(pThis->gPrivate_keys + 
			(vIndex * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), pKey)))
	{
		vIndex = (vIndex + (++vStep)) & vMask;

		if(vIndex == vLastIndex)
			{return pThis->gPrivate_numberOfBuckets;}
	}

	return (CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, vIndex) ?
			pThis->gPrivate_numberOfBuckets : vIndex);
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_hashTable_empty(Crx_C_HashTable * pThis)
{
	if(pThis->gPrivate_bucketData != NULL)
	{
		if(((pThis->gPrivate_typeBluePrint__element != NULL) &&
				(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)) ||
				(pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT != NULL))
		{
			CRX_FOR(size_t tI = 0,
					tI != pThis->gPrivate_numberOfBuckets, ++tI)
			{
				if(CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData,
						tI))
					{continue;}

				if((pThis->gPrivate_typeBluePrint__element != NULL) &&
						(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL))
				{
					pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT(
							pThis->gPrivate_elements + 
							(tI * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
				}
				if(pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT != NULL)
				{
					pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT(
							pThis->gPrivate_keys + 
							(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
				}
			}
			CRX_ENDFOR
		}

		memset(pThis->gPrivate_bucketData, 0xaa,
				CRX__C__HashTable__GET_SIZE_OF_BUCKET_DATA(
				pThis->gPrivate_numberOfBuckets) * sizeof(uint32_t));
		pThis->gPrivate_size = 0;
		pThis->gPrivate_numberOfBucketsEverUsed = 0;
	}
}

CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_hashTable_private_setCapacity(Crx_C_HashTable * pThis,
		size_t pNumberOfBuckets)
{ /* This function uses 0.25*gPrivate_numberOfBuckets bytes of working space instead of [sizeof(key_t+val_t)+.25]*gPrivate_numberOfBuckets. */
	CRX_SCOPE_META
	if(pNumberOfBuckets > ((((size_t)-1) >> 1) + 1))
		{return false;}

	CRX_SCOPE
	uint32_t * vBucketData = NULL;
	size_t vNumberOfBuckets = CRX__C__HashTable__ROUND_UP_TO_POWER_OF_TWO(
			pNumberOfBuckets);
	bool vIsRehashingRequired = true;

	{
		if(vNumberOfBuckets < 4)
			{vNumberOfBuckets = 4;}

		if(pThis->gPrivate_size >= (size_t)(vNumberOfBuckets * 0.77 + 0.5))
			{vIsRehashingRequired = false;}	/* requested gPrivate_size is too small */
		else
		{ /* hash table gPrivate_size to be changed (shrink or expand); rehash */
			vBucketData = (uint32_t *)(malloc(
					CRX__C__HashTable__GET_SIZE_OF_BUCKET_DATA(vNumberOfBuckets) *
					sizeof(uint32_t)));

			if(vBucketData != NULL)
			{
				memset(vBucketData, 0xaa,
						CRX__C__HashTable__GET_SIZE_OF_BUCKET_DATA(vNumberOfBuckets) *
						sizeof(uint32_t));

				if(pThis->gPrivate_numberOfBuckets < vNumberOfBuckets)
				{	/* expand */
					unsigned char * tKeys;

					if((pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL) || 
							(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL))
					{
						tKeys = (void*)(malloc(vNumberOfBuckets * 
								pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));

						if(tKeys != NULL)
						{
							if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL)
							{
								CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_numberOfBuckets, tI++)
								{
									if(CRX__C__HashTable__IS_BUCKET_EMPTY(
											pThis->gPrivate_bucketData, tI))
										{continue;}

									pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT(
											tKeys + (tI * 
													pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), 
											pThis->gPrivate_keys + (tI * 
													pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));

									if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != 
											NULL)
									{
										pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(
												pThis->gPrivate_keys + 
												(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
									}
								} 
								CRX_ENDFOR
							}
							else
							{
								memcpy(tKeys, pThis->gPrivate_keys, 
										pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE *
										pThis->gPrivate_numberOfBuckets);

								CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_numberOfBuckets, tI++)
								{
									if(CRX__C__HashTable__IS_BUCKET_EMPTY(
											pThis->gPrivate_bucketData, tI))
										{continue;}

									pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(
											pThis->gPrivate_keys + 
											(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
								}
								CRX_ENDFOR
							}

							free(pThis->gPrivate_keys);
							pThis->gPrivate_keys = tKeys;
						}
						else
						{
							free(vBucketData);
							vBucketData = NULL;
						}
					}
					else
					{
						tKeys = (void*)realloc((void *)pThis->gPrivate_keys, 
								vNumberOfBuckets * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);

						if(!tKeys)
						{
							free(vBucketData);
							vBucketData = NULL;
						}
						else
							{pThis->gPrivate_keys = tKeys;}
					}

					if(pThis->gPrivate_typeBluePrint__element != NULL)
					{
						if(tKeys != NULL)
						{
							unsigned char * tElements;

							if((pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != 
									NULL) || 
									(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != 
									NULL))
							{
								tElements = malloc(vNumberOfBuckets * 
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

								if(tElements != NULL)
								{
									if(pThis->gPrivate_typeBluePrint__element->
											gFUNC__MOVE_CONSTRUCT != NULL)
									{
										CRX_FOR(size_t tI = 0, 
												tI < pThis->gPrivate_numberOfBuckets, tI++)
										{
											if(CRX__C__HashTable__IS_BUCKET_EMPTY(
													pThis->gPrivate_bucketData, tI) == 0)
											{
												pThis->gPrivate_typeBluePrint__element->
														gFUNC__MOVE_CONSTRUCT(tElements + (tI * 
														pThis->gPrivate_typeBluePrint__element->
														gBYTE_SIZE),
														pThis->gPrivate_elements + (tI * 
														pThis->gPrivate_typeBluePrint__element->
														gBYTE_SIZE));

												if(pThis->gPrivate_typeBluePrint__element->
														gFUNC__MOVE_DESTRUCT != NULL)
												{
													pThis->gPrivate_typeBluePrint__element->
														gFUNC__MOVE_DESTRUCT(
														pThis->gPrivate_elements + (tI * 
														pThis->gPrivate_typeBluePrint__element->
														gBYTE_SIZE));
												}
											}
										}
										CRX_ENDFOR
									}
									else
									{
										memcpy(tElements, pThis->gPrivate_elements,
												pThis->gPrivate_numberOfBuckets *
												pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

										CRX_FOR(size_t tI = 0, 
												tI < pThis->gPrivate_numberOfBuckets, tI++)
										{
											if(CRX__C__HashTable__IS_BUCKET_EMPTY(
													pThis->gPrivate_bucketData, tI) == 0)
											{
												pThis->gPrivate_typeBluePrint__element->
														gFUNC__MOVE_DESTRUCT(
														pThis->gPrivate_elements + (tI * 
														pThis->gPrivate_typeBluePrint__element->
														gBYTE_SIZE));
											}
										}
										CRX_ENDFOR 
									}

									free(pThis->gPrivate_elements);
									pThis->gPrivate_elements = tElements;
								}
								else
								{
									free(vBucketData);
									vBucketData = NULL;
								}
							}
							else
							{
								tElements = realloc(
										(void *)pThis->gPrivate_elements, vNumberOfBuckets * 
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

								if(!tElements)
								{
									free(vBucketData);
									vBucketData = NULL;
								}
								else
									{pThis->gPrivate_elements = tElements;}
							}
						}
					}
				} /* otherwise shrink */ \
			}
		}
	}

	if(vBucketData != NULL)
	{
		if(vIsRehashingRequired)
		{ /* rehashing is needed */
			size_t tSeed = 0;
			unsigned char * tKey = (unsigned char *) CRX__ALLOCA(
					pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
			unsigned char * tKey_temp = (unsigned char *) CRX__ALLOCA(
					pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
			unsigned char * tElement = NULL;
			unsigned char * tElement_tmp = NULL;

			if(pThis->gPrivate_typeBluePrint__element != NULL)
			{
				tElement = (unsigned char *) CRX__ALLOCA(
						pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
				tElement_tmp = (unsigned char *) CRX__ALLOCA(
						pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
			}

			if(pThis->gPrivate_numberOfBuckets <= vNumberOfBuckets)
			{
				if(pThis->gPrivate_typeBluePrint__element != NULL)
				{
					tSeed = crx_c_hashTable_private_prepareSeedForHash(pThis->gPrivate_keys,
							pThis->gPrivate_elements);
				}
				else
				{
					tSeed = crx_c_hashTable_private_prepareSeedForHash(pThis,
							pThis->gPrivate_keys);
				}
			}
			else
			{
				if(pThis->gPrivate_typeBluePrint__element != NULL)
				{
					tSeed = crx_c_hashTable_private_prepareSeedForHash(pThis->gPrivate_keys,
							pThis->gPrivate_elements + 101);
				}
				else
				{
					tSeed = crx_c_hashTable_private_prepareSeedForHash(pThis,
							pThis->gPrivate_keys + 101);
				}
			}

			CRX_FOR(size_t tI = 0, tI != pThis->gPrivate_numberOfBuckets, ++tI)
			{
				if(CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, tI) == 0)
				{
					size_t tNewMask = vNumberOfBuckets - 1;

					if(pThis->gPrivate_typeBluePrint__key->gIS_COPYABLE &&
							(pThis->gPrivate_typeBluePrint__key->gFUNC__COPY_CONSTRUCT == NULL) &&
							(pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT == NULL))
					{
						memcpy(tKey, pThis->gPrivate_keys + 
										(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), 
								pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
					}
					else
					{
						if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL)
						{
							pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT(
									tKey, pThis->gPrivate_keys + 
									(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
						}
						else
						{
							memcpy(tKey, pThis->gPrivate_keys + 
									(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), 
									pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
						}

						if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != 
								NULL)
						{
							pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(
									pThis->gPrivate_keys + 
									(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
						}
					}

					if(pThis->gPrivate_typeBluePrint__element != NULL)
					{
						if(pThis->gPrivate_typeBluePrint__element->gIS_COPYABLE &&
								(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT == 
										NULL) &&
								(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT == NULL))
						{
							memcpy(tElement, pThis->gPrivate_elements + 
									(tI * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE), 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
						}
						else
						{
							if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != 
									NULL)
							{
								pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT(
										tElement, pThis->gPrivate_elements + 
										(tI * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
							}
							else
							{
								memcpy(tElement, pThis->gPrivate_elements + 
										(tI * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE), 
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
							}

							if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL)
							{
								pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT(
										pThis->gPrivate_elements + 
										(tI * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
							}
						}
					}

					CRX__C__HashTable__MARK_BUCKET_CONTENT_DELETED(
							pThis->gPrivate_bucketData, tI);

					while(true)
					{ /* kick-out process; sort of like in Cuckoo hashing */
						size_t tIndex = (*(pThis->gPrivate_getHashForKey))(tSeed,
								tKey) & tNewMask;
						size_t tStep = 0;

						while(!CRX__C__HashTable__WAS_BUCKET_NEVER_FILLED(vBucketData,
								tIndex))
							{tIndex = (tIndex + (++tStep)) & tNewMask;}

						CRX__C__HashTable__MARK_BUCKET_EVER_FILLED(vBucketData, tIndex);

						if((tIndex < pThis->gPrivate_numberOfBuckets) &&
								(CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, 
										tIndex) == 0))
						{ /* kick out the existing element */
							{
								if(pThis->gPrivate_typeBluePrint__key->gIS_COPYABLE &&
										(pThis->gPrivate_typeBluePrint__key->
												gFUNC__COPY_CONSTRUCT == NULL) &&
										(pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT == 
												NULL))
								{
									memcpy(tKey_temp, pThis->gPrivate_keys + 
											(tIndex * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE),
											pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
									memcpy(pThis->gPrivate_keys + 
											(tIndex * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE),
											tKey, pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
									memcpy(tKey, tKey_temp, 
											pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
								}
								else
								{
									if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != 
											NULL)
									{
										pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT(
												tKey_temp, pThis->gPrivate_keys + (tIndex * 
												pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));

										if(pThis->gPrivate_typeBluePrint__key->
												gFUNC__MOVE_DESTRUCT != NULL)
										{
											pThis->gPrivate_typeBluePrint__key->
													gFUNC__MOVE_DESTRUCT(pThis->gPrivate_keys +
													(tIndex * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
										}

										pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT(
												pThis->gPrivate_keys + (tIndex * 
												pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), 
												tKey);

										if(pThis->gPrivate_typeBluePrint__key->
												gFUNC__MOVE_DESTRUCT != NULL)
										{
											pThis->gPrivate_typeBluePrint__key->
													gFUNC__MOVE_DESTRUCT(tKey);
										}

										pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT(
												tKey, tKey_temp);

										if(pThis->gPrivate_typeBluePrint__key->
												gFUNC__MOVE_DESTRUCT != NULL)
										{
											pThis->gPrivate_typeBluePrint__key->
													gFUNC__MOVE_DESTRUCT(tKey_temp);
										}
									}
									else
									{
										memcpy(tKey_temp, pThis->gPrivate_keys + (tIndex * 
												pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE),
												pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
										if(pThis->gPrivate_typeBluePrint__key->
												gFUNC__MOVE_DESTRUCT != NULL)
										{
											pThis->gPrivate_typeBluePrint__key->
													gFUNC__MOVE_DESTRUCT(
													pThis->gPrivate_keys + (tIndex * 
													pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
										}

										memcpy(pThis->gPrivate_keys + (tIndex * 
												pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE),
												tKey,
												pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
										if(pThis->gPrivate_typeBluePrint__key->
												gFUNC__MOVE_DESTRUCT != NULL)
										{
											pThis->gPrivate_typeBluePrint__key->
													gFUNC__MOVE_DESTRUCT(tKey);
										}

										memcpy(tKey, tKey_temp, 
												pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
										if(pThis->gPrivate_typeBluePrint__key->
												gFUNC__MOVE_DESTRUCT != NULL)
										{
											pThis->gPrivate_typeBluePrint__key->
													gFUNC__MOVE_DESTRUCT(tKey_temp);
										}
									}
								}
							}

							if(pThis->gPrivate_typeBluePrint__element != NULL)
							{
								if(pThis->gPrivate_typeBluePrint__element->gIS_COPYABLE &&
										(pThis->gPrivate_typeBluePrint__element->
												gFUNC__COPY_CONSTRUCT == NULL) &&
										(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT == 
												NULL))
								{
									memcpy(tElement_tmp, pThis->gPrivate_elements + (tIndex * 
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
									memcpy(pThis->gPrivate_elements + (tIndex * 
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE), 
											tElement,
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
									memcpy(tElement, tElement_tmp, 
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
								}
								else
								{
									if(pThis->gPrivate_typeBluePrint__element->
											gFUNC__MOVE_CONSTRUCT != NULL)
									{
										pThis->gPrivate_typeBluePrint__element->
												gFUNC__MOVE_CONSTRUCT(
												tElement_tmp, pThis->gPrivate_elements + (tIndex * 
												pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));

										if(pThis->gPrivate_typeBluePrint__element->
												gFUNC__MOVE_DESTRUCT != NULL)
										{
											pThis->gPrivate_typeBluePrint__element->
													gFUNC__MOVE_DESTRUCT(
													pThis->gPrivate_elements + (tIndex * 
													pThis->gPrivate_typeBluePrint__element->
													gBYTE_SIZE));
										}

										pThis->gPrivate_typeBluePrint__element->
												gFUNC__MOVE_CONSTRUCT(
												pThis->gPrivate_elements + (tIndex * 
												pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
												tElement);

										if(pThis->gPrivate_typeBluePrint__element->
												gFUNC__MOVE_DESTRUCT != NULL)
										{
											pThis->gPrivate_typeBluePrint__element->
													gFUNC__MOVE_DESTRUCT(tElement);
										}

										pThis->gPrivate_typeBluePrint__element->
												gFUNC__MOVE_CONSTRUCT(
												tElement, tElement_tmp);

										if(pThis->gPrivate_typeBluePrint__element->
												gFUNC__MOVE_DESTRUCT != NULL)
										{
											pThis->gPrivate_typeBluePrint__element->
													gFUNC__MOVE_DESTRUCT(tElement_tmp);
										}
									}
									else
									{
										memcpy(tElement_tmp,
												pThis->gPrivate_elements + (tIndex * 
												pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
												pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

										if(pThis->gPrivate_typeBluePrint__element->
												gFUNC__MOVE_DESTRUCT != NULL)
										{
											pThis->gPrivate_typeBluePrint__element->
													gFUNC__MOVE_DESTRUCT(
													pThis->gPrivate_elements + (tIndex * 
													pThis->gPrivate_typeBluePrint__element->
													gBYTE_SIZE));
										}

										memcpy(pThis->gPrivate_elements + (tIndex * 
												pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
												tElement,
												pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

										if(pThis->gPrivate_typeBluePrint__element->
												gFUNC__MOVE_DESTRUCT != NULL)
										{
											pThis->gPrivate_typeBluePrint__element->
													gFUNC__MOVE_DESTRUCT(tElement);
										}

										memcpy(tElement, tElement_tmp, 
												pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

										if(pThis->gPrivate_typeBluePrint__element->
												gFUNC__MOVE_DESTRUCT != NULL)
										{
											pThis->gPrivate_typeBluePrint__element->
													gFUNC__MOVE_DESTRUCT(tElement_tmp);
										}
									}
								}
							}

							CRX__C__HashTable__MARK_BUCKET_CONTENT_DELETED(pThis->gPrivate_bucketData, tIndex); /* mark it as deleted in the old hash table */ \
						}
						else
						{ /* write the element and jump out of the loop */
							if(pThis->gPrivate_typeBluePrint__key->gIS_COPYABLE &&
									(pThis->gPrivate_typeBluePrint__key->gFUNC__COPY_CONSTRUCT == 
											NULL) &&
									(pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT == NULL))
							{
								memcpy(pThis->gPrivate_keys + (tIndex * 
										pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), tKey, 
										pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
							}
							else
							{
								if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != 
										NULL)
								{
									pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT(
											pThis->gPrivate_keys + (tIndex * 
											pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), tKey);
								}
								else
								{
									memcpy(pThis->gPrivate_keys + (tIndex * 
											pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), tKey,
											pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
								}

								if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL)
								{
									pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(
											((void *)tKey));
								}
							}

							if(pThis->gPrivate_typeBluePrint__element != NULL)
							{
								if(pThis->gPrivate_typeBluePrint__element->gIS_COPYABLE &&
										(pThis->gPrivate_typeBluePrint__element->
												gFUNC__COPY_CONSTRUCT == NULL) &&
										(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT == 
												NULL))
								{
									memcpy(pThis->gPrivate_elements + (tIndex * 
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
											tElement,
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
								}
								else
								{
									if(pThis->gPrivate_typeBluePrint__element->
											gFUNC__MOVE_CONSTRUCT != NULL)
									{
										pThis->gPrivate_typeBluePrint__element->
												gFUNC__MOVE_CONSTRUCT(
												pThis->gPrivate_elements + (tIndex * 
												pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
												tElement);
									}
									else
									{
										memcpy(pThis->gPrivate_elements + (tIndex * 
												pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
												tElement,
												pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
									}

									if(pThis->gPrivate_typeBluePrint__element->
											gFUNC__MOVE_DESTRUCT != NULL)
									{
										pThis->gPrivate_typeBluePrint__element->
													gFUNC__MOVE_DESTRUCT(tElement);
									}
								}
							}

							break;
						}
					}
				}
			}
			CRX_ENDFOR

			if(pThis->gPrivate_numberOfBuckets > vNumberOfBuckets)
			{ /* shrink the hash table */
				unsigned char * tKeys;

				if((pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL) || 
						(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL))
				{
					tKeys = (void*)(malloc(vNumberOfBuckets * 
							pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));

					if(tKeys != NULL)
					{
						if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL)
						{
							CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_numberOfBuckets, tI++)
							{
								if(CRX__C__HashTable__IS_BUCKET_EMPTY(
										pThis->gPrivate_bucketData, tI) == 0)
								{
									pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT(
											tKeys + (tI * 
											pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), 
											pThis->gPrivate_keys + (tI * 
											pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));

									if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != 
											NULL)
									{
										pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(
												pThis->gPrivate_keys + (tI * 
												pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
									}
								}
							}
							CRX_ENDFOR
						}
						else
						{
							memcpy(tKeys, pThis->gPrivate_keys, pThis->gPrivate_numberOfBuckets *
									pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);

							CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_numberOfBuckets, tI++)
							{
								if(CRX__C__HashTable__IS_BUCKET_EMPTY(
										pThis->gPrivate_bucketData, tI) == 0)
								{
									pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(
											pThis->gPrivate_keys + 
											(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
								}
							}
							CRX_ENDFOR
						}

						free(pThis->gPrivate_keys);
						pThis->gPrivate_keys = tKeys;
					}
				}
				else
				{
					tKeys = (void*)realloc((void *)pThis->gPrivate_keys, vNumberOfBuckets * 
							pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);

					if(tKeys != NULL)
						{pThis->gPrivate_keys = tKeys;}
				}

				if(pThis->gPrivate_typeBluePrint__element != NULL)
				{
					if(tKeys != NULL)
					{
						unsigned char * tElements;

						if((pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != 
										NULL) || 
								(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != 
										NULL))
						{
							tElements = (malloc(vNumberOfBuckets * 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));

							if(tElements != NULL)
							{
								if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != 
										NULL)
								{
									CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_numberOfBuckets, 
											tI++)
									{
										if(CRX__C__HashTable__IS_BUCKET_EMPTY(
												pThis->gPrivate_bucketData, tI) == 0)
										{
											pThis->gPrivate_typeBluePrint__element->
													gFUNC__MOVE_CONSTRUCT(tElements + (tI * 
													pThis->gPrivate_typeBluePrint__element->
													gBYTE_SIZE), 
													pThis->gPrivate_elements + (tI * 
													pThis->gPrivate_typeBluePrint__element->
													gBYTE_SIZE));

											if(pThis->gPrivate_typeBluePrint__element->
													gFUNC__MOVE_DESTRUCT != NULL)
											{
												pThis->gPrivate_typeBluePrint__element->
														gFUNC__MOVE_DESTRUCT(
														pThis->gPrivate_elements + (tI * 
														pThis->gPrivate_typeBluePrint__element->
														gBYTE_SIZE));
											}
										}
									}
									CRX_ENDFOR
								}
								else
								{
									memcpy(tElements, pThis->gPrivate_elements,
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE * 
											pThis->gPrivate_numberOfBuckets);

									CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_numberOfBuckets, 
											tI++)
									{
										if(CRX__C__HashTable__IS_BUCKET_EMPTY(
												pThis->gPrivate_bucketData, tI) == 0)
										{
											pThis->gPrivate_typeBluePrint__element->
													gFUNC__MOVE_DESTRUCT(
													pThis->gPrivate_elements + (tI * 
													pThis->gPrivate_typeBluePrint__element->
													gBYTE_SIZE));
										}
									}
									CRX_ENDFOR
								}

								free(pThis->gPrivate_elements);
								pThis->gPrivate_elements = tElements;
							}
						}
						else
						{
							tElements = realloc(pThis->gPrivate_elements, vNumberOfBuckets * 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

							if(tElements != NULL)
								{pThis->gPrivate_elements = tElements;}
						}
					}
				}
			}

			free(pThis->gPrivate_bucketData); /* free the working space */
			pThis->gPrivate_bucketData = vBucketData;
			pThis->gPrivate_numberOfBuckets = vNumberOfBuckets;
			pThis->gPrivate_numberOfBucketsEverUsed = pThis->gPrivate_size;
			pThis->gPrivate_upperBoundOfNumberOfBucketsEverUsed =
					(size_t)(pThis->gPrivate_numberOfBuckets * 0.77 + 0.5);
			pThis->gPrivate_seed = tSeed;
		}

		return true;
	}
	else
		{return false;}
	CRX_SCOPE_END
}

CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_hashTable_private_setCapacity2(Crx_C_HashTable * pThis,
		size_t pNumberOfBuckets)
{ /* This function uses 0.25*gPrivate_numberOfBuckets bytes of working space instead of [sizeof(key_t+val_t)+.25]*gPrivate_numberOfBuckets. */ \
	CRX_SCOPE_META
	if(pNumberOfBuckets > ((((size_t)-1) >> 1) + 1))
		{return false;}

	CRX_SCOPE
	uint32_t * vBucketData = NULL;
	size_t vNumberOfBuckets = CRX__C__HashTable__ROUND_UP_TO_POWER_OF_TWO(
			pNumberOfBuckets);
	bool vIsRehashingRequired = true;
	unsigned char * vKeys = NULL;
	unsigned char * vElements = NULL;

	{
		if(vNumberOfBuckets < 4)
			{vNumberOfBuckets = 4;}

		if(pThis->gPrivate_size >= (size_t)(vNumberOfBuckets * 0.77 + 0.5))
			{vIsRehashingRequired = false;}	/* requested gPrivate_size is too small */
		else
		{ /* hash table gPrivate_size to be changed (shrink or expand); rehash */
			vBucketData = (uint32_t *)(malloc(
					CRX__C__HashTable__GET_SIZE_OF_BUCKET_DATA(vNumberOfBuckets) *
					sizeof(uint32_t)));

			if(vBucketData != NULL)
			{
				bool tIsToExpandOrPossiblyShrink = false;

				memset(vBucketData, 0xaa,
						CRX__C__HashTable__GET_SIZE_OF_BUCKET_DATA(vNumberOfBuckets) *
						sizeof(uint32_t));

				if(!((pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL) ||
						(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL) ||
						(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL) ||
						(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL)))
				{
					tIsToExpandOrPossiblyShrink = 
							(pThis->gPrivate_numberOfBuckets < vNumberOfBuckets);
				}
				else
				{
					tIsToExpandOrPossiblyShrink = 
							(pThis->gPrivate_numberOfBuckets != vNumberOfBuckets);
				}
						
				if(tIsToExpandOrPossiblyShrink)
				{	/* expand OR POSSIBLY SHRINK NOW*/
					void * tKeys;

					if((pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL) ||
							(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL) ||
							(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != 
									NULL) ||
							(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL))
					{
						vKeys = (malloc(vNumberOfBuckets * 
								pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));

						if(vKeys != NULL)
						{
							if(pThis->gPrivate_typeBluePrint__element != NULL)
							{
								vElements = malloc(vNumberOfBuckets * 
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

								if(vElements == NULL)
								{
									free(vKeys);
									vKeys = NULL;
									free(vBucketData);
									vBucketData = NULL;
								}
							}
						}
						else
						{
							free(vBucketData);
							vBucketData = NULL;
						}
					}
					else
					{
						tKeys = realloc((void *)pThis->gPrivate_keys, vNumberOfBuckets * 
								pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);

						if(!tKeys)
						{
							free(vBucketData);
							vBucketData = NULL;
						}
						else
						{
							pThis->gPrivate_keys = tKeys;

							if(pThis->gPrivate_typeBluePrint__element != NULL)
							{
								void * tElements = realloc(pThis->gPrivate_elements, 
										vNumberOfBuckets * 
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

								if(!tElements)
								{
									free(vBucketData);
									vBucketData = NULL;
								}
								else
									{pThis->gPrivate_elements = tElements;}
							}
						}
					}
				} /* otherwise shrink */
			}
		}
	}
	if(vBucketData != NULL)
	{
		if(vIsRehashingRequired)
		{ /* rehashing is needed */
			size_t tSeed = 0;
			size_t tNewMask = vNumberOfBuckets - 1;

			if((pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL) ||
					(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL) ||
					(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL) ||
					(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL))
			{
				if(pThis->gPrivate_typeBluePrint__element != NULL)
				{
					tSeed = crx_c_hashTable_private_prepareSeedForHash(vKeys,
							vElements);
				}
				else
				{
					tSeed = crx_c_hashTable_private_prepareSeedForHash(pThis,
							vKeys);
				}

				CRX_FOR(size_t tI = 0, tI != pThis->gPrivate_numberOfBuckets, ++tI)
				{
					CRX_SCOPE_META
					if(CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, tI) != 0)
						{continue;}

					CRX_SCOPE
					size_t tI2 = (*(pThis->gPrivate_getHashForKey))(tSeed,
							pThis->gPrivate_keys + 
							(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE)) & tNewMask;
					size_t tStep = 0;

					while(!CRX__C__HashTable__WAS_BUCKET_NEVER_FILLED(vBucketData, tI2))
						{tI2 = (tI2 + (++tStep)) & tNewMask;}

					CRX__C__HashTable__MARK_BUCKET_EVER_FILLED(vBucketData, tI2);

					if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL)
					{
						pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT(vKeys + 
								(tI2 * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), 
								pThis->gPrivate_keys + 
								(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
					}
					else
					{
						memcpy(vKeys + (tI2 * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), 
								pThis->gPrivate_keys + 
								(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), 
								pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
					}

					if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL)
					{
						pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(
								pThis->gPrivate_keys + 
								(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
					}

					if(pThis->gPrivate_typeBluePrint__element != NULL)
					{
						if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)
						{
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT(
									vElements + (tI2 * 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE), 
									pThis->gPrivate_elements + 
									(tI * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
						}
						else
						{
							memcpy(vElements + (tI2 * 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE), 
									pThis->gPrivate_elements + 
									(tI * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
						}

						if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL)
						{
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT(
									pThis->gPrivate_elements + 
									(tI * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
						}
					}
					CRX_SCOPE_END
				}
				CRX_ENDFOR

				pThis->gPrivate_numberOfBuckets = vNumberOfBuckets;
				pThis->gPrivate_numberOfBucketsEverUsed = pThis->gPrivate_size;
				pThis->gPrivate_upperBoundOfNumberOfBucketsEverUsed =
						(size_t)(pThis->gPrivate_numberOfBuckets * 0.77 + 0.5);
				pThis->gPrivate_seed = tSeed;

				free(pThis->gPrivate_bucketData);
				pThis->gPrivate_bucketData = vBucketData;
				vBucketData = NULL;

				free(pThis->gPrivate_keys);
				pThis->gPrivate_keys = vKeys;
				vKeys = NULL;

				if(pThis->gPrivate_typeBluePrint__element != NULL)
				{
					free(pThis->gPrivate_elements);
					pThis->gPrivate_elements = vElements;
					vElements = NULL;
				}
			}
			else
			{
				unsigned char * tKey = (unsigned char *) CRX__ALLOCA(
						pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
				unsigned char * tKey_temp = (unsigned char *) CRX__ALLOCA(
						pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
				unsigned char * tElement = NULL;
				unsigned char * tElement_tmp = NULL;

				if(pThis->gPrivate_typeBluePrint__element != NULL)
				{
					tElement = (unsigned char *) CRX__ALLOCA(
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
					tElement_tmp = (unsigned char *) CRX__ALLOCA(
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
				}

				if(pThis->gPrivate_numberOfBuckets <= vNumberOfBuckets)
				{
					if(pThis->gPrivate_typeBluePrint__element != NULL)
					{
						tSeed = crx_c_hashTable_private_prepareSeedForHash(pThis->gPrivate_keys,
								pThis->gPrivate_elements);
					}
					else
					{
						tSeed = crx_c_hashTable_private_prepareSeedForHash(pThis,
								pThis->gPrivate_keys);
					}
				}
				else
				{
					if(pThis->gPrivate_typeBluePrint__element != NULL)
					{
						tSeed = crx_c_hashTable_private_prepareSeedForHash(pThis->gPrivate_keys,
								pThis->gPrivate_elements + 101);
					}
					else
					{
						tSeed = crx_c_hashTable_private_prepareSeedForHash(pThis,
								pThis->gPrivate_keys + 101);
					}
				}

				CRX_FOR(size_t tI = 0, tI != pThis->gPrivate_numberOfBuckets, ++tI)
				{
					if(CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, tI) == 0)
					{
						memcpy(tKey, pThis->gPrivate_keys + 
								(tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), 
								pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);

						if(pThis->gPrivate_typeBluePrint__element != NULL)
						{
							memcpy(tElement, pThis->gPrivate_elements + 
									(tI * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
						}

						CRX__C__HashTable__MARK_BUCKET_CONTENT_DELETED(
								pThis->gPrivate_bucketData, tI);

						while(true)
						{ /* kick-out process; sort of like in Cuckoo hashing */
							size_t tIndex = (*(pThis->gPrivate_getHashForKey))(tSeed, ((void *)tKey))
									& tNewMask;
							size_t tStep = 0;

							while(!CRX__C__HashTable__WAS_BUCKET_NEVER_FILLED(vBucketData, tIndex))
								{tIndex = (tIndex + (++tStep)) & tNewMask;}

							CRX__C__HashTable__MARK_BUCKET_EVER_FILLED(vBucketData, tIndex);

							if((tIndex < pThis->gPrivate_numberOfBuckets) &&
									(CRX__C__HashTable__IS_BUCKET_EMPTY(
									pThis->gPrivate_bucketData, tIndex) == 0))
							{ /* kick out the existing element */
								{
									memcpy(tKey_temp, pThis->gPrivate_keys + (tIndex * 
											pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), 
											pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
									memcpy(pThis->gPrivate_keys + (tIndex * 
											pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), 
											tKey, 
											pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
									memcpy(tKey, tKey_temp, 
											pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
								}

								if(pThis->gPrivate_typeBluePrint__element != NULL)
								{
									memcpy(tElement_tmp, pThis->gPrivate_elements + (tIndex * 
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
									memcpy(pThis->gPrivate_elements + (tIndex * 
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE), 
											tElement,
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
									memcpy(tElement, tElement_tmp, 
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
								}

								CRX__C__HashTable__MARK_BUCKET_CONTENT_DELETED(
										pThis->gPrivate_bucketData, tIndex); /* mark it as deleted in the old hash table */
							}
							else
							{ /* write the element and jump out of the loop */
								memcpy(pThis->gPrivate_keys + (tIndex * 
										pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), tKey, 
										pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);

								if(pThis->gPrivate_typeBluePrint__element != NULL)
								{
									memcpy(pThis->gPrivate_elements + (tIndex * 
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE), 
											tElement,
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
								}

								break;
							}
						}
					}
				}
				CRX_ENDFOR
			}

			if((pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL) ||
					(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL) ||
					(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL) ||
					(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL))
			{
				if(pThis->gPrivate_numberOfBuckets > vNumberOfBuckets)
				{ /* shrink the hash table */
					void * tKeys = realloc((void *)pThis->gPrivate_keys, vNumberOfBuckets * 
							pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);

					if(tKeys != NULL)
						{pThis->gPrivate_keys = tKeys;}

					if(pThis->gPrivate_typeBluePrint__element != NULL)
					{
						if(tKeys != NULL)
						{
							void * tElements = realloc(pThis->gPrivate_elements, vNumberOfBuckets * 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

							if(vElements != NULL)
								{pThis->gPrivate_elements = vElements;}
						}
					}
				}

				free(pThis->gPrivate_bucketData); /* free the working space */
				pThis->gPrivate_bucketData = vBucketData;
				pThis->gPrivate_numberOfBuckets = vNumberOfBuckets;
				pThis->gPrivate_numberOfBucketsEverUsed = pThis->gPrivate_size;
				pThis->gPrivate_upperBoundOfNumberOfBucketsEverUsed =
						(size_t)(pThis->gPrivate_numberOfBuckets * 0.77 + 0.5);
				pThis->gPrivate_seed = tSeed;
			}
		}

		return true;
	}
	else
		{return false;}
	CRX_SCOPE_END
}

CRX__LIB__PRIVATE_C_FUNCTION() size_t crx_c_hashTable_private_tryMoveKeyAndPrepareBucketFor(
		Crx_C_HashTable * pThis, void * CRX_NOT_NULL pKey, int * CRX_NOT_NULL pReturn)
{
	size_t vReturn = 0;

	if(pThis->gPrivate_numberOfBucketsEverUsed >= pThis->gPrivate_upperBoundOfNumberOfBucketsEverUsed) \
	{ /* update the hash table */
		if(pThis->gPrivate_numberOfBuckets > (pThis->gPrivate_size << 1))
		{
			if(!crx_c_hashTable_private_setCapacity(pThis,
					pThis->gPrivate_numberOfBuckets - 1))
			{/* clear "deleted" elements */
				*pReturn = -1;

				vReturn = pThis->gPrivate_numberOfBuckets;
			}
		}
		else if(!crx_c_hashTable_private_setCapacity(pThis,
				pThis->gPrivate_numberOfBuckets + 1))
		{ /* expand the hash table */
			*pReturn = -1;

			vReturn = pThis->gPrivate_numberOfBuckets;
		}
	} /* TODO: to implement automatically shrinking; private_setCapacity() already support shrinking */

	if((vReturn != pThis->gPrivate_numberOfBuckets) ||
			(pThis->gPrivate_numberOfBucketsEverUsed < pThis->gPrivate_numberOfBuckets))
	{
		{
			size_t tMask = pThis->gPrivate_numberOfBuckets - 1;
			size_t tIndex = (*(pThis->gPrivate_getHashForKey))(pThis->gPrivate_seed, pKey) & tMask;

			if(CRX__C__HashTable__WAS_BUCKET_NEVER_FILLED(pThis->gPrivate_bucketData, tIndex))
				{vReturn = tIndex;} /* for speed up */
			else
			{
				size_t site = pThis->gPrivate_numberOfBuckets;
				size_t tLastIndex = tIndex;
				size_t tStep = 0;

				vReturn = pThis->gPrivate_numberOfBuckets;

				while(!CRX__C__HashTable__WAS_BUCKET_NEVER_FILLED(pThis->gPrivate_bucketData, tIndex) &&
						(CRX__C__HashTable__IS_BUCKET_CONTENT_DELETED(pThis->gPrivate_bucketData, tIndex) ||
						!(*(pThis->gPrivate_areKeysEqual))(pThis->gPrivate_keys + 
						(tIndex * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), pKey)))
				{
					if(CRX__C__HashTable__IS_BUCKET_CONTENT_DELETED(pThis->gPrivate_bucketData, tIndex))
						{site = tIndex;}

					tIndex = (tIndex + (++tStep)) & tMask;

					if(tIndex == tLastIndex)
					{
						vReturn = site;
						break;
					}
				}
				if(vReturn == pThis->gPrivate_numberOfBuckets)
				{
					if(CRX__C__HashTable__WAS_BUCKET_NEVER_FILLED(pThis->gPrivate_bucketData, tIndex) &&
							site != pThis->gPrivate_numberOfBuckets)
						{vReturn = site;}
					else
						{vReturn = tIndex;}
				}
			}
		}

		if(CRX__C__HashTable__WAS_BUCKET_NEVER_FILLED(pThis->gPrivate_bucketData, vReturn))
		{ /* not present at all */
			if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT(
						pThis->gPrivate_keys + 
						(vReturn * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), pKey);
			}
			else
			{
				memcpy(pThis->gPrivate_keys + 
						(vReturn * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), pKey, 
						pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
			}

			CRX__C__HashTable__MARK_BUCKET_NOT_EMPTY(pThis->gPrivate_bucketData, vReturn);

			++(pThis->gPrivate_size);
			++(pThis->gPrivate_numberOfBucketsEverUsed);

			*pReturn = 1;
		}
		else if(CRX__C__HashTable__IS_BUCKET_CONTENT_DELETED(pThis->gPrivate_bucketData, vReturn))
		{ /* deleted */
			if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT(
						pThis->gPrivate_keys + 
						(vReturn * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), pKey);
			}
			else
			{
				memcpy(pThis->gPrivate_keys + 
						(vReturn * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), pKey, 
						pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
			}

			CRX__C__HashTable__MARK_BUCKET_NOT_EMPTY(pThis->gPrivate_bucketData, vReturn);
			++(pThis->gPrivate_size);

			*pReturn = 2;
		}
		else
			{*pReturn = 0;} /* Don't touch pThis->gPrivate_keys[vReturn] if present and not deleted */
	}

	return vReturn;
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_hashTable_private_deleteElementAt(Crx_C_HashTable * pThis,
		size_t pBucketIndex)
{
	if((pBucketIndex != pThis->gPrivate_numberOfBuckets) &&
			!CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, pBucketIndex))
	{
		CRX__C__HashTable__MARK_BUCKET_CONTENT_DELETED(pThis->gPrivate_bucketData, pBucketIndex);

		if(pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT != NULL)
		{
			pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT(
					pThis->gPrivate_keys + 
					(pBucketIndex * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
		}
		if((pThis->gPrivate_typeBluePrint__element != NULL) &&
				(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL))
		{
			pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT(
					pThis->gPrivate_elements + 
					(pBucketIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
		}

		--(pThis->gPrivate_size);
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_hashTable_getSize(Crx_C_HashTable const * pThis)
	{return pThis->gPrivate_size;}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_hashTable_tryMoveKeyAndElementAndSet(
		Crx_C_HashTable * pThis, void * CRX_NOT_NULL pKey, void * CRX_NOT_NULL pElement)
{
	CRX_SCOPE_META
	if(pThis->gPrivate_typeBluePrint__element == NULL)
		{return false;}
	
	CRX_SCOPE
	int vReturnedCode = 0;
	size_t vBucketNumber =
			crx_c_hashTable_private_tryMoveKeyAndPrepareBucketFor(pThis,
			pKey, &vReturnedCode);

	if(vBucketNumber != pThis->gPrivate_numberOfBuckets)
	{
		if(vReturnedCode > 0)
			{}
		else
		{
			if(pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT != NULL)
			{
				pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT(
						pThis->gPrivate_keys + 
						(vBucketNumber * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
			}

			if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT(
						pThis->gPrivate_keys + 
						(vBucketNumber * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), pKey);
			}
			else
			{
				memcpy(pThis->gPrivate_keys + 
						(vBucketNumber * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), pKey, 
						pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
			}

			if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
			{
				pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT(
						pThis->gPrivate_elements + 
						(vBucketNumber * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
			}
		}

		if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT(
					pThis->gPrivate_elements + 
					(vBucketNumber * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE), pElement);
		}
		else
		{
			memcpy(pThis->gPrivate_elements + 
					(vBucketNumber * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE), pElement, 
					pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
		}

		return true;
	}
	else
		{return false;}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_hashTable_tryMoveKeyAndSet(
		Crx_C_HashTable * pThis, void * CRX_NOT_NULL pKey, void const * pElement)
{
	CRX_SCOPE_META
	if((pThis->gPrivate_typeBluePrint__element == NULL) || (pElement == NULL))
		{return false;}

	CRX_SCOPE
	unsigned char * vElement = NULL;
	bool vReturn = false;
	int vReturnedCode = 0;
	size_t vBucketNumber = 0;

	if((pThis->gPrivate_typeBluePrint__element != NULL) &&
			((pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != NULL) ||
					(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)))
	{
		vElement = (unsigned char *) CRX__ALLOCA(
				pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
	}
	
	if(pThis->gPrivate_typeBluePrint__element == NULL)
	{
		vBucketNumber = crx_c_hashTable_private_tryMoveKeyAndPrepareBucketFor(pThis,
			pKey, &vReturnedCode);
	}

	if(pThis->gPrivate_typeBluePrint__element != NULL)
	{
		if(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != NULL)
		{
			pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT(vElement, pElement);

			vReturn = crx_c_hashTable_tryMoveKeyAndElementAndSet(pThis, pKey, vElement);
		}
		else
		{
			if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				memcpy(vElement, pElement, 
						pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

				vReturn = crx_c_hashTable_tryMoveKeyAndElementAndSet(pThis, pKey, vElement);
			}
			else
			{
				vReturn = crx_c_hashTable_tryMoveKeyAndElementAndSet(pThis, pKey, 
						((void *)pElement));
			}
		}

		if(((pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL) ||
				(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)) &&
				((pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != NULL) ||
				(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)))
		{
			if(vReturn)
			{
				if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL)
					{pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT(vElement);}
			}
			else
			{
				if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
					{pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT(vElement);}
			}
		}
	}
	else
	{
		if(vBucketNumber != pThis->gPrivate_numberOfBuckets)
		{
			if(vReturnedCode > 0)
				{}
			else
			{
				if(pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT != NULL)
				{
					pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT(
							pThis->gPrivate_keys + 
							(vBucketNumber * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
				}

				if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL)
				{
					pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT(
							pThis->gPrivate_keys + 
							(vBucketNumber * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), pKey);
				}
				else
				{
					memcpy(pThis->gPrivate_keys + 
							(vBucketNumber * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), pKey, 
							pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
				}
			}

			vReturn = true;
		}
		else
			{vReturn = false;}
	}

	return vReturn;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_hashTable_tryMoveElementAndSet(
		Crx_C_HashTable * pThis, void const * CRX_NOT_NULL pKey, void * CRX_NOT_NULL pElement)
{
	CRX_SCOPE_META
	if(pThis->gPrivate_typeBluePrint__element == NULL)
		{return false;}

	CRX_SCOPE
	unsigned char * vKey = NULL;
	bool vReturn = false;

	if((pThis->gPrivate_typeBluePrint__key->gFUNC__COPY_CONSTRUCT != NULL) ||
			(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL))
		{vKey = (unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);}
	
	if(pThis->gPrivate_typeBluePrint__key->gFUNC__COPY_CONSTRUCT != NULL)
	{
		pThis->gPrivate_typeBluePrint__key->gFUNC__COPY_CONSTRUCT(vKey, pKey);

		vReturn = crx_c_hashTable_tryMoveKeyAndElementAndSet(pThis, vKey, pElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vKey, pKey, pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);

			vReturn = crx_c_hashTable_tryMoveKeyAndElementAndSet(pThis, vKey, pElement);
		}
		else
			{vReturn = crx_c_hashTable_tryMoveKeyAndElementAndSet(pThis, ((void *)pKey), pElement);}
	}

	if(((pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL) ||
			(pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT != NULL)) &&
			((pThis->gPrivate_typeBluePrint__key->gFUNC__COPY_CONSTRUCT != NULL) ||
			(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL)))
	{
		if(vReturn)
		{
			if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL)
				{pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(vKey);}
		}
		else
		{
			if(pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT != NULL)
				{pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT(vKey);}
		}
	}

	return vReturn;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_hashTable_set(
		Crx_C_HashTable * pThis, void const * CRX_NOT_NULL pKey, void const * pElement)
{
	CRX_SCOPE_META
	if((pThis->gPrivate_typeBluePrint__element == NULL) || (pElement == NULL))
		{return false;}

	CRX_SCOPE
	unsigned char * vKey = (unsigned char *) CRX__ALLOCA(
			pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
	unsigned char * vElement = NULL;
	bool vReturn;

	if(pThis->gPrivate_typeBluePrint__element != NULL)
	{
		vElement = (unsigned char *) CRX__ALLOCA(
			pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
	}

	if(pThis->gPrivate_typeBluePrint__key->gFUNC__COPY_CONSTRUCT != NULL)
		{pThis->gPrivate_typeBluePrint__key->gFUNC__COPY_CONSTRUCT(vKey, pKey);}
	else
		{memcpy(vKey, pKey, pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);}

	if(pThis->gPrivate_typeBluePrint__element != NULL)
	{
		if(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != NULL)
			{pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT(vElement, pElement);}
		else
			{memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);}
	}

	if(pThis->gPrivate_typeBluePrint__element != NULL)
		{vReturn = crx_c_hashTable_tryMoveKeyAndElementAndSet(pThis, vKey, vElement);}
	else
		{vReturn = crx_c_hashTable_tryMoveKeyAndSet(pThis, vKey, NULL);}

	if(vReturn)
	{
		if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL)
			{pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(vKey);}

		if((pThis->gPrivate_typeBluePrint__element != NULL) &&
				(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL))
			{pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT(vElement);}
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT != NULL)
			{pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT(vKey);}

		if((pThis->gPrivate_typeBluePrint__element != NULL) &&
				(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL))
			{pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT(vElement);}
	}

	return vReturn;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void * crx_c_hashTable_get(Crx_C_HashTable * pThis,
		void const * CRX_NOT_NULL pKey)
{
	CRX_SCOPE_META
	if(pThis->gPrivate_typeBluePrint__element == NULL)
		{return NULL;}

	CRX_SCOPE
	size_t vBucketIndex = crx_c_hashTable_private_get(pThis, pKey);

	assert(vBucketIndex != pThis->gPrivate_numberOfBuckets);

	return (pThis->gPrivate_elements + 
			(vBucketIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() void const * crx_c_hashTable_constantGet(
		Crx_C_HashTable const * pThis, void const * CRX_NOT_NULL pKey)
{
	if(pThis->gPrivate_typeBluePrint__element == NULL)
		{return NULL;}

	return crx_c_hashTable_get(((Crx_C_HashTable *)pThis), pKey);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_hashTable_copyGetTo(Crx_C_HashTable const * pThis,
		void * CRX_NOT_NULL pReturn, void const * CRX_NOT_NULL pKey)
{
	CRX_SCOPE_META
	if((pThis->gPrivate_typeBluePrint__element == NULL) ||
			(!pThis->gPrivate_typeBluePrint__element->gIS_COPYABLE))
		{return;}

	CRX_SCOPE
	size_t vBucketIndex = crx_c_hashTable_private_get(pThis, pKey);

	assert(vBucketIndex != pThis->gPrivate_numberOfBuckets);
	
	if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
		{(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT)(pReturn);}

	if(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != NULL)
	{
		pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT(pReturn, 
				pThis->gPrivate_elements + 
				(vBucketIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
	}
	else
	{
		memcpy(pReturn, pThis->gPrivate_elements + 
				(vBucketIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
				pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
	}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_hashTable_hasKey(
		Crx_C_HashTable const * pThis, void const * pKey)
{
	return (crx_c_hashTable_private_get(pThis, pKey) !=
			pThis->gPrivate_numberOfBuckets);
}

CRX__LIB__PUBLIC_C_FUNCTION() void const * crx_c_hashTable_getKeyFromIndex(
		Crx_C_HashTable const * pThis, size_t pIndex)
{
	if(CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, pIndex))
		{return NULL;}

	return (pThis->gPrivate_keys + (pIndex * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
}
CRX__LIB__PUBLIC_C_FUNCTION() void * crx_c_hashTable_getElementFromIndex(
		Crx_C_HashTable * pThis, size_t pIndex)
{
	if(CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, pIndex))
		{return NULL;}

	return (pThis->gPrivate_elements + 
			(pIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
}
CRX__LIB__PUBLIC_C_FUNCTION() void const * crx_c_hashTable_constantGetElementFromIndex(
		Crx_C_HashTable const * pThis, size_t pIndex)
	{return ((void const *)crx_c_hashTable_getElementFromIndex((Crx_C_HashTable *)pThis, pIndex));}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_hashTable_remove(Crx_C_HashTable * pThis,
		void const * CRX_NOT_NULL pKey)
{
	crx_c_hashTable_private_deleteElementAt(pThis,
			crx_c_hashTable_private_get(pThis, pKey));
}

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_hashTable_getStartIndex(Crx_C_HashTable const * pThis)
{
	size_t vIndex = pThis->gPrivate_numberOfBuckets;

	while((vIndex < pThis->gPrivate_numberOfBuckets) &&
			CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, vIndex))
		{vIndex = vIndex + 1;}

	return vIndex;
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_hashTable_getLastIndex(Crx_C_HashTable const * pThis)
{
	size_t vIndex = pThis->gPrivate_numberOfBuckets - 1;

	while(CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, vIndex))
	{
		if(vIndex > 0)
			{vIndex = vIndex - 1;}
		else
		{
			vIndex = pThis->gPrivate_numberOfBuckets;

			break;
		}
	}

	return vIndex;
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_hashTable_getEndIndex(Crx_C_HashTable const * pThis)
	{return pThis->gPrivate_numberOfBuckets;}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_hashTable_getNextIndex(Crx_C_HashTable const * pThis,
		size_t pIndex)
{
	CRX_SCOPE_META
	if(pIndex >= pThis->gPrivate_numberOfBuckets)
		{return pThis->gPrivate_numberOfBuckets;}

	CRX_SCOPE
	size_t vIndex = pIndex + 1;

	while((vIndex < pThis->gPrivate_numberOfBuckets) &&
			CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, vIndex))
		{vIndex = vIndex + 1;}

	return vIndex;
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_hashTable_getPreviousIndex(Crx_C_HashTable const * pThis,
		size_t pIndex)
{
	CRX_SCOPE_META
	if((pIndex == 0) || (pIndex >= pThis->gPrivate_numberOfBuckets))
		{return 0;}

	CRX_SCOPE
	size_t vIndex = pIndex - 1;

	while(CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, vIndex))
	{
		if(vIndex > 0)
			{vIndex = vIndex - 1;}
		else
		{
			vIndex = pThis->gPrivate_numberOfBuckets;

			return vIndex;
		}
	}

	return vIndex;
	CRX_SCOPE_END
}

CRX__LIB__PRIVATE_C_FUNCTION() size_t crx_c_hashTable_private_prepareSeedForHash(
		void const * pPointer, void const * pPointer2)
{
	Crx_C_Random_Isaac vIsaac /*= ?*/;
	uint32_t vPointerValue = ((uint32_t)(((uintmax_t)pPointer) |
			(((uintmax_t)pPointer) >> 3) & 0x03));
	uint32_t vPointer2Value = ((uint32_t)(((uintmax_t)pPointer2) | 
			(((uintmax_t)pPointer2) >> 3) & 0x03));


	crx_c_random_isaac_construct2(&vIsaac, vPointerValue, vPointer2Value, 0,
			0, 0, 0, 0, 0);

#if(UINT32_MAX < SIZE_MAX)
	return ((((size_t)crx_c_random_isaac_getRandomUnsignedInt32(&vIsaac)) << 32) &&
			crx_c_random_isaac_getRandomUnsignedInt32(&vIsaac));
#else
	return crx_c_random_isaac_getRandomUnsignedInt32(&vIsaac);
#endif
}



CRX__LIB__C_CODE_END()

