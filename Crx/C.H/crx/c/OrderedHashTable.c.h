//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/OrderedHashTable.h"

#include "Crx/H/crx/c/TypeBluePrint.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_construct(Crx_C_OrderedHashTable * pThis,
	Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
	Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__element,
	Crx_C_HashTable_AreKeysEqual CRX_NOT_NULL pAreKeysEqual,
	Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey)
{
	crx_c_orderedHashTable_private_doInit(pThis, pTypeBluePrint__key, pAreKeysEqual,
			pGetHashForKey, pTypeBluePrint__element);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_construct2(Crx_C_OrderedHashTable * pThis,
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
		Crx_C_HashTable_AreKeysEqual CRX_NOT_NULL pAreKeysEqual,
		Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey)
{
	crx_c_orderedHashTable_private_doInit(pThis, pTypeBluePrint__key, pAreKeysEqual,
			pGetHashForKey, NULL);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_copyConstruct(
		Crx_C_OrderedHashTable * pThis, Crx_C_OrderedHashTable const * pHashTable)
{
	if(!pHashTable->gPrivate_typeBluePrint__key->gIS_COPYABLE ||
			((pHashTable->gPrivate_typeBluePrint__element != NULL) &&
			!pHashTable->gPrivate_typeBluePrint__element->gIS_COPYABLE))
		{abort();}

	CRX__SET_TO_ZERO(Crx_C_OrderedHashTable, *pThis);

	if(crx_c_orderedHashTable_private_setCapacity(pThis, pHashTable->gPrivate_size))
	{
		CRX_FOR(Crx_C_OrderedHashTable_Private_KeyNode * tKeyNode =
				pHashTable->gPrivate_rootKeyNode, tKeyNode != NULL,
				tKeyNode = ((tKeyNode->gPrivate_nextIndex != ((size_t)-1)) ?
				(pHashTable->gPrivate_keyNodes + tKeyNode->gPrivate_nextIndex) : NULL))
		{
			if(pHashTable->gPrivate_typeBluePrint__element != NULL)
			{
				crx_c_orderedHashTable_set(pThis,
						pHashTable->gPrivate_keys + (tKeyNode->gPrivate_index * 
								pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE),
						pHashTable->gPrivate_elements + (tKeyNode->gPrivate_index * 
								pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
			}
			else
			{
				crx_c_orderedHashTable_set(pThis,
						pHashTable->gPrivate_keys + (tKeyNode->gPrivate_index * 
								pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), NULL);
			}
		}
		CRX_ENDFOR
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_OrderedHashTable * crx_c_orderedHashTable_new(
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
		Crx_C_TypeBluePrint const *  pTypeBluePrint__element,
		Crx_C_HashTable_AreKeysEqual CRX_NOT_NULL pAreKeysEqual,
		Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey)
{
	Crx_C_OrderedHashTable * vReturn = (Crx_C_OrderedHashTable *)(calloc(1,
			sizeof(Crx_C_OrderedHashTable)));

	if(vReturn != NULL)
	{
		crx_c_orderedHashTable_construct(vReturn, pTypeBluePrint__key, pTypeBluePrint__element,
				pAreKeysEqual, pGetHashForKey);
	}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_OrderedHashTable * crx_c_orderedHashTable_new2(
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
		Crx_C_HashTable_AreKeysEqual CRX_NOT_NULL pAreKeysEqual,
		Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey)
{
	Crx_C_OrderedHashTable * vReturn = (Crx_C_OrderedHashTable *)(calloc(1,
			sizeof(Crx_C_OrderedHashTable)));

	if(vReturn != NULL)
	{
		crx_c_orderedHashTable_construct2(vReturn, pTypeBluePrint__key, pAreKeysEqual,
				pGetHashForKey);
	}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_OrderedHashTable * crx_c_orderedHashTable_moveNew(
		Crx_C_OrderedHashTable * pHashTable)
{
	Crx_C_OrderedHashTable * vReturn = (Crx_C_OrderedHashTable *)(calloc(1,
			sizeof(Crx_C_OrderedHashTable)));

	if(vReturn != NULL)
		{memcpy(vReturn, pHashTable, sizeof(Crx_C_OrderedHashTable));}

	return vReturn;
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_OrderedHashTable * crx_c_orderedHashTable_copyNew(
		Crx_C_OrderedHashTable const * pHashTable)
{
	CRX_SCOPE_META
	if(!pHashTable->gPrivate_typeBluePrint__key->gIS_COPYABLE ||
			((pHashTable->gPrivate_typeBluePrint__element != NULL) &&
			!pHashTable->gPrivate_typeBluePrint__element->gIS_COPYABLE))
		{abort();}

	CRX_SCOPE
	Crx_C_OrderedHashTable * vReturn = (Crx_C_OrderedHashTable *)(calloc(1,
			sizeof(Crx_C_OrderedHashTable)));

	if(vReturn != NULL)
		{crx_c_orderedHashTable_copyConstruct(vReturn, pHashTable);}

	return vReturn;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_destruct(Crx_C_OrderedHashTable * pThis)
{
	if((pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT != NULL) ||
			(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL))
		{crx_c_orderedHashTable_empty(pThis);}

	free((void *) pThis->gPrivate_keyNodes);
	pThis->gPrivate_keyNodes = NULL;
	free(pThis->gPrivate_bucketData);
	pThis->gPrivate_bucketData = NULL;

	if(pThis->gPrivate_typeBluePrint__element != NULL)
	{
		free((void *) pThis->gPrivate_elements);
		pThis->gPrivate_elements = NULL;
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_free(Crx_C_OrderedHashTable * pThis)
	{free(pThis);}

CRX__C__TYPE_BLUE_PRINT__GENERIC__DEFINE_GET_BLUE_PRINT(
		Crx_C_OrderedHashTable, crx_c_orderedHashTable_,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__FALSE, CRXM__FALSE,
		true, true,
		(!pThis->gPrivate_typeBluePrint__key->gIS_COPYABLE ||
				((pThis->gPrivate_typeBluePrint__element != NULL) &&
				!pThis->gPrivate_typeBluePrint__element->gIS_COPYABLE)), true,
		false, false)

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_private_doInit(Crx_C_OrderedHashTable * pThis,
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
		Crx_C_HashTable_AreKeysEqual CRX_NOT_NULL pAreKeysEqual,
		Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey,
		Crx_C_TypeBluePrint const *  pTypeBluePrint__element)
{
	assert((pTypeBluePrint__key != NULL) && CRX__C__TYPE_BLUE_PRINT__IS_CORRECT_FORM(
			pTypeBluePrint__key) && (pAreKeysEqual != NULL) && (pGetHashForKey != NULL) &&
			(pTypeBluePrint__key->gFUNC__GET_BYTE_SIZE_OF == NULL));
	assert((pTypeBluePrint__element == NULL) || (CRX__C__TYPE_BLUE_PRINT__IS_CORRECT_FORM(
			pTypeBluePrint__element) && 
			(pTypeBluePrint__element->gFUNC__GET_BYTE_SIZE_OF == NULL)));

	CRX__SET_TO_ZERO(Crx_C_OrderedHashTable, *pThis);

	pThis->gPrivate_typeBluePrint__key = pTypeBluePrint__key;
	pThis->gPrivate_typeBluePrint__element = pTypeBluePrint__element;
	pThis->gPrivate_bucketData = NULL;
	pThis->gPrivate_rootKeyNode = NULL;
	pThis->gPrivate_lastKeyNode = NULL;
	pThis->gPrivate_keyNodes = NULL;
	pThis->gPrivate_keys = NULL;
	pThis->gPrivate_elements = NULL;
	pThis->gPrivate_areKeysEqual = pAreKeysEqual;
	pThis->gPrivate_getHashForKey = pGetHashForKey;
}

CRX__LIB__PRIVATE_C_FUNCTION() size_t crx_c_orderedHashTable_private_get(
		Crx_C_OrderedHashTable const * pThis, void const * CRX_NOT_NULL pKey)
{
	CRX_SCOPE_META
	if(pThis->gPrivate_numberOfBuckets == 0)
		{return 0;}

	CRX_SCOPE
	size_t vMask = pThis->gPrivate_numberOfBuckets - 1;
	size_t vIndex = (*(pThis->gPrivate_getHashForKey))(pThis->gPrivate_seed, pKey) & vMask;
	size_t vLastIndex = vIndex;
	size_t vStep = 0;

	while(!CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(pThis->gPrivate_bucketData, vIndex) &&
			(CRX__C__OrderedHashTable__IS_BUCKET_CONTENT_DELETED(pThis->gPrivate_bucketData, vIndex) ||
			!(*(pThis->gPrivate_areKeysEqual))(pThis->gPrivate_keys + (vIndex * 
			pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), pKey)))
	{
		vIndex = (vIndex + (++vStep)) & vMask;

		if(vIndex == vLastIndex)
			{return pThis->gPrivate_numberOfBuckets;}
	}

	return (CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData,
			vIndex) ? pThis->gPrivate_numberOfBuckets : vIndex);
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_empty(Crx_C_OrderedHashTable * pThis)
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
				if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData,
						tI))
					{continue;}

				if((pThis->gPrivate_typeBluePrint__element != NULL) &&
						(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL))
				{
					pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT(
							pThis->gPrivate_elements + (tI * 
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
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
				CRX__C__OrderedHashTable__GET_SIZE_OF_BUCKET_DATA(
				pThis->gPrivate_numberOfBuckets) * sizeof(uint32_t));
		pThis->gPrivate_size = 0;
		pThis->gPrivate_numberOfBucketsEverUsed = 0;
		pThis->gPrivate_rootKeyNode = NULL;
		pThis->gPrivate_lastKeyNode = NULL;
	}
}

CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_orderedHashTable_private_setCapacity(
		Crx_C_OrderedHashTable * pThis, size_t pNumberOfBuckets)
{ /* This function uses 0.25*gPrivate_numberOfBuckets bytes of working space instead of [sizeof(key_t+val_t)+.25]*gPrivate_numberOfBuckets. */
	CRX_SCOPE_META
	if(pNumberOfBuckets > ((((size_t)-1) >> 1) + 1))
		{return false;}

	CRX_SCOPE
	uint32_t * vBucketData = NULL;
	size_t vNumberOfBuckets = CRX__C__OrderedHashTable__ROUND_UP_TO_POWER_OF_TWO(
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
					CRX__C__OrderedHashTable__GET_SIZE_OF_BUCKET_DATA(vNumberOfBuckets) *
					sizeof(uint32_t)));

			if(vBucketData != NULL)
			{
				memset(vBucketData, 0xaa,
						CRX__C__OrderedHashTable__GET_SIZE_OF_BUCKET_DATA(vNumberOfBuckets) *
								sizeof(uint32_t));

				if(pThis->gPrivate_numberOfBuckets < vNumberOfBuckets)
				{	/* expand */
					Crx_C_OrderedHashTable_Private_KeyNode * tKeyNodes =
							(Crx_C_OrderedHashTable_Private_KeyNode *)(malloc(
							vNumberOfBuckets *
							sizeof(Crx_C_OrderedHashTable_Private_KeyNode)));
					unsigned char * tKeys = ((unsigned char *)malloc(vNumberOfBuckets * 
							pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
					

					if((tKeyNodes != NULL) && (tKeys != NULL))
					{
						bool vIsFirst = true;

						CRX_FOR(Crx_C_OrderedHashTable_Private_KeyNode *
								tKeyNode = pThis->gPrivate_rootKeyNode,
								tKeyNode != NULL,
								tKeyNode = ((tKeyNode->gPrivate_nextIndex != ((size_t)-1) ?
										(pThis->gPrivate_keyNodes +
												tKeyNode->gPrivate_nextIndex) : NULL)))
						{
							CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE2(
									pThis->gPrivate_typeBluePrint__key,
									tKeyNodes + tKeyNode->gPrivate_index,
									tKeyNode, tKeys + (tKeyNode->gPrivate_index * 
									pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE),
									pThis->gPrivate_keys + (tKeyNode->gPrivate_index * 
									pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));

							if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL)
							{
								pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(
										pThis->gPrivate_keys + (tKeyNode->gPrivate_index * 
										pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
							}

							if(vIsFirst)
							{
								pThis->gPrivate_rootKeyNode =
										tKeyNodes + tKeyNode->gPrivate_index;

								vIsFirst = false;
							}
							else if(tKeyNode->gPrivate_nextIndex == ((size_t)-1))
							{
								pThis->gPrivate_lastKeyNode =
										tKeyNodes + tKeyNode->gPrivate_index;
							}

							tKeyNode = tKeyNodes + tKeyNode->gPrivate_index;
						}
						CRX_ENDFOR

						free(pThis->gPrivate_keyNodes);
						pThis->gPrivate_keyNodes = tKeyNodes;
						free(pThis->gPrivate_keys);
						pThis->gPrivate_keys = tKeys;
					}
					else
					{
						free(vBucketData);
						vBucketData = NULL;
						free(tKeyNodes);
						tKeyNodes = NULL;
						free(tKeys);
						tKeys = NULL;
					}

					if(pThis->gPrivate_typeBluePrint__element != NULL)
					{
						if(tKeyNodes != NULL)
						{
							unsigned char * tElements;

							tElements = ((unsigned char *)malloc(vNumberOfBuckets * 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));

							if(tElements != NULL)
							{
								if(pThis->gPrivate_typeBluePrint__element->
										gFUNC__MOVE_CONSTRUCT != NULL)
								{
									CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_numberOfBuckets, 
											tI++)
									{
										if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(
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

									CRX_FOR(size_t tI = 0,
											tI < pThis->gPrivate_numberOfBuckets, tI++)
									{
										if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(
												pThis->gPrivate_bucketData, tI) == 0)
										{
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

								free(pThis->gPrivate_elements);
								pThis->gPrivate_elements = tElements;
							}
							else
							{
								free(vBucketData);
								vBucketData = NULL;
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
			Crx_C_OrderedHashTable_Private_KeyNode tKeyNode /*= ?*/;
			Crx_C_OrderedHashTable_Private_KeyNode tKeyNode_temp /*= ?*/;
			unsigned char * tKey = (unsigned char *) CRX__ALLOCA(
					pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
			unsigned char * tKey_temp = (unsigned char *) CRX__ALLOCA(
					pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
			unsigned char * tElement = NULL;
			unsigned char * tElement_tmp = NULL;
			bool tWasRootKeyNodeSet = false;
			bool tWasLastKeyNodeSet = false;

			CRX__SET_TO_ZERO(Crx_C_OrderedHashTable_Private_KeyNode, tKeyNode);
			CRX__SET_TO_ZERO(Crx_C_OrderedHashTable_Private_KeyNode, tKeyNode_temp);

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
					tSeed = crx_c_orderedHashTable_private_prepareSeedForHash(
							pThis->gPrivate_keyNodes, pThis->gPrivate_elements);
				}
				else
				{
					tSeed = crx_c_orderedHashTable_private_prepareSeedForHash(pThis,
							pThis->gPrivate_keyNodes);
				}
			}
			else
			{
				if(pThis->gPrivate_typeBluePrint__element != NULL)
				{
					tSeed = crx_c_orderedHashTable_private_prepareSeedForHash(
							pThis->gPrivate_keyNodes, pThis->gPrivate_elements + 101);
				}
				else
				{
					tSeed = crx_c_orderedHashTable_private_prepareSeedForHash(pThis,
							pThis->gPrivate_keyNodes + 101);
				}
			}

			CRX_FOR(size_t tI = 0, tI != pThis->gPrivate_numberOfBuckets, ++tI)
			{
				if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(
						pThis->gPrivate_bucketData, tI) == 0)
				{
					size_t tNewMask = vNumberOfBuckets - 1;

					CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE2(pThis->gPrivate_typeBluePrint__key,
							&tKeyNode, pThis->gPrivate_keyNodes + tI, 
							&tKey, pThis->gPrivate_keys + (tI * 
							pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));

					if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL)
					{
						pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(
								pThis->gPrivate_keys + (tI * 
								pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
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

					CRX__C__OrderedHashTable__MARK_BUCKET_CONTENT_DELETED(
							pThis->gPrivate_bucketData, tI);

					while(true)
					{ /* kick-out process; sort of like in Cuckoo hashing */
						size_t tIndex = (*(pThis->gPrivate_getHashForKey))(tSeed,
								tKey) & tNewMask;
						size_t tStep = 0;

						while(!CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(vBucketData,
								tIndex))
							{tIndex = (tIndex + (++tStep)) & tNewMask;}

						CRX__C__OrderedHashTable__MARK_BUCKET_EVER_FILLED(vBucketData, tIndex);

						if((tIndex < pThis->gPrivate_numberOfBuckets) &&
								(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(
										pThis->gPrivate_bucketData, tIndex) == 0))
						{ /* kick out the existing element */
							{
								CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE2(
										pThis->gPrivate_typeBluePrint__key,
										&tKeyNode_temp, pThis->gPrivate_keyNodes + tIndex,
										&tKey_temp, pThis->gPrivate_keys + (tIndex * 
										pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));

								if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL)
								{
									pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(
											pThis->gPrivate_keys + (tIndex * 
											pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
								}

								CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE2(
										pThis->gPrivate_typeBluePrint__key,
										pThis->gPrivate_keyNodes + tIndex, &tKeyNode,
										pThis->gPrivate_keys + (tIndex * 
										pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), &tKey);

								if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL)
								{
									pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(tKey);
								}

								(pThis->gPrivate_keyNodes + tIndex)->gPrivate_index =
										tIndex;

								if((pThis->gPrivate_keyNodes + tIndex)->
										gPrivate_previousIndex != ((size_t)-1))
								{
									if((pThis->gPrivate_keyNodes + tIndex)->
											gPrivate_previousIndex != tIndex)
									{
										(pThis->gPrivate_keyNodes +
												(pThis->gPrivate_keyNodes + tIndex)->
												gPrivate_previousIndex)->gPrivate_nextIndex =
												tIndex;
									}
									else
										{tKeyNode_temp.gPrivate_nextIndex = tIndex;}
								}

								if((pThis->gPrivate_keyNodes + tIndex)->
										gPrivate_nextIndex != ((size_t)-1))
								{
									if((pThis->gPrivate_keyNodes + tIndex)->
											gPrivate_nextIndex != tIndex)
									{
										(pThis->gPrivate_keyNodes +
												(pThis->gPrivate_keyNodes + tIndex)->
												gPrivate_nextIndex)->gPrivate_previousIndex =
												tIndex;
									}
									else
										{tKeyNode_temp.gPrivate_previousIndex = tIndex;}
								}

								if(!tWasRootKeyNodeSet &&
										(pThis->gPrivate_rootKeyNode == (pThis->gPrivate_keyNodes +
												tKeyNode.gPrivate_index)))
								{
									pThis->gPrivate_rootKeyNode = pThis->gPrivate_keyNodes +
											tIndex;
									tWasRootKeyNodeSet = true;
								}
								else if(!tWasLastKeyNodeSet &&
										(pThis->gPrivate_lastKeyNode == (pThis->gPrivate_keyNodes +
												tKeyNode.gPrivate_index)))
								{
									pThis->gPrivate_lastKeyNode = pThis->gPrivate_keyNodes +
											tIndex;
									tWasLastKeyNodeSet = true;
								}

								CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE2(
										pThis->gPrivate_typeBluePrint__key,
										&tKeyNode, &tKeyNode_temp,
										&tKey, &tKey_temp);

								if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL)
								{
									pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(
											&tKey_temp);
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
												gFUNC__MOVE_CONSTRUCT(tElement_tmp,
												pThis->gPrivate_elements + (tIndex * 
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
												gFUNC__MOVE_CONSTRUCT(tElement, tElement_tmp);
										
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

							CRX__C__OrderedHashTable__MARK_BUCKET_CONTENT_DELETED(
									pThis->gPrivate_bucketData, tIndex); /* mark it as deleted in the old hash table */
						}
						else
						{ /* write the element and jump out of the loop */
							CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE2(
									pThis->gPrivate_typeBluePrint__key,
									pThis->gPrivate_keyNodes + tIndex, &tKeyNode,
									pThis->gPrivate_keys + (tIndex * 
									pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), &tKey);

							if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL)
								{pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(tKey);}

							(pThis->gPrivate_keyNodes + tIndex)->gPrivate_index = tIndex;

							if((pThis->gPrivate_keyNodes + tIndex)->gPrivate_previousIndex !=
									((size_t)-1))
							{
								(pThis->gPrivate_keyNodes +
										(pThis->gPrivate_keyNodes + tIndex)->
										gPrivate_previousIndex)->gPrivate_nextIndex = tIndex;
							}

							if((pThis->gPrivate_keyNodes + tIndex)->gPrivate_nextIndex !=
									((size_t)-1))
							{
								(pThis->gPrivate_keyNodes +
										(pThis->gPrivate_keyNodes + tIndex)->
										gPrivate_nextIndex)->gPrivate_previousIndex = tIndex;
							}

							if(!tWasRootKeyNodeSet &&
									(pThis->gPrivate_rootKeyNode == (pThis->gPrivate_keyNodes +
									tKeyNode.gPrivate_index)))
							{
								pThis->gPrivate_rootKeyNode = pThis->gPrivate_keyNodes +
										tIndex;
								tWasRootKeyNodeSet = true;
							}
							else if(!tWasLastKeyNodeSet &&
									(pThis->gPrivate_lastKeyNode == (pThis->gPrivate_keyNodes +
									tKeyNode.gPrivate_index)))
							{
								pThis->gPrivate_lastKeyNode = pThis->gPrivate_keyNodes +
										tIndex;
								tWasLastKeyNodeSet = true;
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
				Crx_C_OrderedHashTable_Private_KeyNode * tKeyNodes =
						(Crx_C_OrderedHashTable_Private_KeyNode*)(malloc(vNumberOfBuckets *
						sizeof(Crx_C_OrderedHashTable_Private_KeyNode)));
				unsigned char * tKeys = ((unsigned char *)malloc(vNumberOfBuckets * 
							pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));

				if((tKeyNodes != NULL) && (tKeys != NULL))
				{
					CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_numberOfBuckets, tI++)
					{
						if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(
								pThis->gPrivate_bucketData, tI) == 0)
						{
							CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE2(
									pThis->gPrivate_typeBluePrint__key,
									tKeyNodes + tI, pThis->gPrivate_keyNodes + tI,
									tKeys + (tI * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE),
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

					free(pThis->gPrivate_keyNodes);
					pThis->gPrivate_keyNodes = tKeyNodes;
					free(pThis->gPrivate_keys);
					pThis->gPrivate_keys = tKeys;
				}
				else
				{
					free(tKeyNodes);
					tKeyNodes = NULL;
					free(tKeys);
					tKeys = NULL;
				}

				if(pThis->gPrivate_typeBluePrint__element != NULL)
				{
					if(tKeyNodes != NULL)
					{
						unsigned char * tElements /*= ?*/;

						if((pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != 
										NULL) || 
								(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != 
										NULL))
						{
							tElements = ((unsigned char *)malloc(vNumberOfBuckets * 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));

							if(tElements != NULL)
							{
								if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != 
										NULL)
								{
									CRX_FOR(size_t tI = 0,
											tI < pThis->gPrivate_numberOfBuckets, tI++)
									{
										if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(
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

									CRX_FOR(size_t tI = 0,
											tI < pThis->gPrivate_numberOfBuckets, tI++)
									{
										if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(
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
							tElements = ((unsigned char *)realloc((void *)pThis->gPrivate_elements, vNumberOfBuckets * 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));

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

CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_orderedHashTable_private_setCapacity2(Crx_C_OrderedHashTable * pThis,
		size_t pNumberOfBuckets)
{ /* This function uses 0.25*gPrivate_numberOfBuckets bytes of working space instead of [sizeof(key_t+val_t)+.25]*gPrivate_numberOfBuckets. */
	CRX_SCOPE_META
	if(pNumberOfBuckets > ((((size_t)-1) >> 1) + 1))
		{return false;}

	CRX_SCOPE
	uint32_t * vBucketData = NULL;
	size_t vNumberOfBuckets = CRX__C__OrderedHashTable__ROUND_UP_TO_POWER_OF_TWO(
			pNumberOfBuckets);
	bool vIsRehashingRequired = true;
	Crx_C_OrderedHashTable_Private_KeyNode * vKeyNodes = NULL;
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
					CRX__C__OrderedHashTable__GET_SIZE_OF_BUCKET_DATA(vNumberOfBuckets) *
					sizeof(uint32_t)));

			if(vBucketData != NULL)
			{
				memset(vBucketData, 0xaa,
						CRX__C__OrderedHashTable__GET_SIZE_OF_BUCKET_DATA(vNumberOfBuckets) *
						sizeof(uint32_t));

				if(pThis->gPrivate_numberOfBuckets != vNumberOfBuckets)
				{	/* expand OR SHRINK*/
					vKeyNodes = (Crx_C_OrderedHashTable_Private_KeyNode *)(
							malloc(vNumberOfBuckets *
							sizeof(Crx_C_OrderedHashTable_Private_KeyNode)));
					vKeys = malloc(vNumberOfBuckets * 
							pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);

					if((vKeyNodes != NULL) && (vKeys != NULL))
					{
						if(pThis->gPrivate_typeBluePrint__element != NULL)
						{
							vElements = malloc(vNumberOfBuckets * 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

							if(vElements == NULL)
							{
								free(vKeyNodes);
								vKeyNodes = NULL;
								free(vBucketData);
								vBucketData = NULL;
								free(vKeys);
								vKeys = NULL;
							}
						}
					}
					else
					{
						free(vBucketData);
						vBucketData = NULL;
						free(vKeyNodes);
						vKeyNodes = NULL;
						free(vKeys);
						vKeys = NULL;
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

			if(pThis->gPrivate_typeBluePrint__element != NULL)
			{
				tSeed = crx_c_orderedHashTable_private_prepareSeedForHash(vKeyNodes,
						vElements);
			}
			else
			{
				tSeed = crx_c_orderedHashTable_private_prepareSeedForHash(pThis,
						vKeyNodes);
			}

			CRX_FOR(size_t tI = 0, tI != pThis->gPrivate_numberOfBuckets, ++tI)
			{
				CRX_SCOPE_META
				if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, tI) != 0)
					{continue;}

				CRX_SCOPE
				size_t tCurrentIndex = tI;

				/*ENSURING THAN GIVEN AN INDEX x, (pThis->gPrivate_bucketData + x) AND
							(vBucketData + x) ARE NOT BOTH OCCUPIED AT THE SAME TIME. THIS IS NOT
							NEEDED WHEN USING POINTERS INSTEAD OF INDICES FOR nextIndex AND
							previousIndex*/ \
				while(true)
				{
					size_t tI2 = (*(pThis->gPrivate_getHashForKey))(tSeed,
							pThis->gPrivate_keys + (tCurrentIndex * 
							pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE)) & tNewMask;
					size_t tStep = 0;

					while(!CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(vBucketData, tI2))
						{tI2 = (tI2 + (++tStep)) & tNewMask;}

					CRX__C__OrderedHashTable__MARK_BUCKET_EVER_FILLED(vBucketData, tI2);

					CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE2(
							pThis->gPrivate_typeBluePrint__key,
							vKeyNodes + tI2, pThis->gPrivate_keyNodes + tCurrentIndex,
							vKeys + (tI2 * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), 
							pThis->gPrivate_keys + (tCurrentIndex * 
							pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));

					if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL)
					{
						pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(
								pThis->gPrivate_keys + (tCurrentIndex * 
								pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
					}

					CRX__C__OrderedHashTable__MARK_BUCKET_CONTENT_DELETED(
							pThis->gPrivate_bucketData, tCurrentIndex);

					(vKeyNodes + tI2)->gPrivate_index = tI2;

					if((vKeyNodes + tI2)->gPrivate_previousIndex != ((size_t)-1))
					{
						if(((vKeyNodes + tI2)->gPrivate_previousIndex >=
										pThis->gPrivate_numberOfBuckets) ||
								(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(
										pThis->gPrivate_bucketData,
										(vKeyNodes + tI2)->gPrivate_previousIndex) != 0))
						{
							(vKeyNodes + (vKeyNodes + tI2)->gPrivate_previousIndex)->
									gPrivate_nextIndex = tI2;
						}
						else
						{
							(pThis->gPrivate_keyNodes + (vKeyNodes + tI2)-> gPrivate_previousIndex)->
									gPrivate_nextIndex = tI2;
						}
					}

					if((vKeyNodes + tI2)->gPrivate_nextIndex != ((size_t)-1))
					{
						if(((vKeyNodes + tI2)->gPrivate_nextIndex >=
										pThis->gPrivate_numberOfBuckets) ||
								(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(
										pThis->gPrivate_bucketData,
										(vKeyNodes + tI2)->gPrivate_nextIndex) != 0))
						{
							(vKeyNodes + (vKeyNodes + tI2)->gPrivate_nextIndex)->
									gPrivate_previousIndex = tI2;
						}
						else
						{
							(pThis->gPrivate_keyNodes + (vKeyNodes + tI2)->gPrivate_nextIndex)->
									gPrivate_previousIndex = tI2;
						}
					}

					if(pThis->gPrivate_typeBluePrint__element != NULL)
					{
						if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)
						{
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT(
									vElements + (tI2 * 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE), 
									pThis->gPrivate_elements + (tCurrentIndex * 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
						}
						else
						{
							memcpy(vElements + (tI2 * 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE), 
									pThis->gPrivate_elements + (tCurrentIndex * 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
						}

						if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL)
						{
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT(
									pThis->gPrivate_elements + (tCurrentIndex * 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
						}
					}

					if(pThis->gPrivate_rootKeyNode == (pThis->gPrivate_keyNodes + tCurrentIndex))
						{pThis->gPrivate_rootKeyNode = vKeyNodes + tI2;}

					if(pThis->gPrivate_lastKeyNode == (pThis->gPrivate_keyNodes + tCurrentIndex))
						{pThis->gPrivate_lastKeyNode = vKeyNodes + tI2;}

					if((tI2 < pThis->gPrivate_numberOfBuckets) &&
								CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(
								pThis->gPrivate_bucketData, tI2) == 0)
							{tCurrentIndex = tI2;}
						else
							{break;}
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

			free(pThis->gPrivate_keyNodes);
			pThis->gPrivate_keyNodes = vKeyNodes;
			vKeyNodes = NULL;
			
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

		return true;
	}
	else
		{return false;}
	CRX_SCOPE_END
}

CRX__LIB__PRIVATE_C_FUNCTION() size_t crx_c_orderedHashTable_private_tryMoveKeyAndPrepareBucketFor(
		Crx_C_OrderedHashTable * pThis, void * CRX_NOT_NULL pKey, int * CRX_NOT_NULL pReturn)
{
	size_t vReturn = 0;

	if(pThis->gPrivate_numberOfBucketsEverUsed >= pThis->gPrivate_upperBoundOfNumberOfBucketsEverUsed)
	{ /* update the hash table */
		if(pThis->gPrivate_numberOfBuckets > (pThis->gPrivate_size << 1))
		{
			if(!crx_c_orderedHashTable_private_setCapacity2(pThis,
					pThis->gPrivate_numberOfBuckets - 1))
			{/* clear "deleted" elements */
				*pReturn = -1;

				vReturn = pThis->gPrivate_numberOfBuckets;
			}
		}
		else if(!crx_c_orderedHashTable_private_setCapacity2(pThis,
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

			if(CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(pThis->gPrivate_bucketData, tIndex))
				{vReturn = tIndex;} /* for speed up */
			else
			{
				size_t site = pThis->gPrivate_numberOfBuckets;
				size_t tLastIndex = tIndex;
				size_t tStep = 0;

				vReturn = pThis->gPrivate_numberOfBuckets;

				while(!CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(
								pThis->gPrivate_bucketData, tIndex) &&
						(CRX__C__OrderedHashTable__IS_BUCKET_CONTENT_DELETED(
								pThis->gPrivate_bucketData, tIndex) ||
						!(*(pThis->gPrivate_areKeysEqual))(pThis->gPrivate_keys + 
						(tIndex * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), pKey)))
				{
					if(CRX__C__OrderedHashTable__IS_BUCKET_CONTENT_DELETED(
							pThis->gPrivate_bucketData, tIndex))
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
					if(CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(
							pThis->gPrivate_bucketData, tIndex) &&
							(site != pThis->gPrivate_numberOfBuckets))
						{vReturn = site;}
					else
						{vReturn = tIndex;}
				}
			}
		}

		if(CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(pThis->gPrivate_bucketData, vReturn))
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

			CRX__C__OrderedHashTable__MARK_BUCKET_NOT_EMPTY(pThis->gPrivate_bucketData, vReturn);

			++(pThis->gPrivate_size);
			++(pThis->gPrivate_numberOfBucketsEverUsed);

			if(pThis->gPrivate_rootKeyNode == NULL)
			{
				pThis->gPrivate_rootKeyNode = (pThis->gPrivate_keyNodes + vReturn);
				pThis->gPrivate_rootKeyNode->gPrivate_nextIndex = ((size_t)-1);
				pThis->gPrivate_rootKeyNode->gPrivate_previousIndex = ((size_t)-1);
			}
			else
			{
				(pThis->gPrivate_keyNodes + vReturn)->gPrivate_nextIndex = ((size_t)-1);

				if(pThis->gPrivate_lastKeyNode != NULL)
				{
					(pThis->gPrivate_keyNodes + vReturn)->gPrivate_previousIndex =
							pThis->gPrivate_lastKeyNode->gPrivate_index;
					pThis->gPrivate_lastKeyNode->gPrivate_nextIndex = vReturn;
					pThis->gPrivate_lastKeyNode = (pThis->gPrivate_keyNodes + vReturn);
				}
				else
				{
					(pThis->gPrivate_keyNodes + vReturn)->gPrivate_previousIndex =
							pThis->gPrivate_rootKeyNode->gPrivate_index;
					pThis->gPrivate_rootKeyNode->gPrivate_nextIndex = vReturn;
					pThis->gPrivate_lastKeyNode = (pThis->gPrivate_keyNodes + vReturn);
				}
			}

			(pThis->gPrivate_keyNodes + vReturn)->gPrivate_index = vReturn;

			*pReturn = 1;
		}
		else if(CRX__C__OrderedHashTable__IS_BUCKET_CONTENT_DELETED(pThis->gPrivate_bucketData, 
				vReturn))
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

			CRX__C__OrderedHashTable__MARK_BUCKET_NOT_EMPTY(pThis->gPrivate_bucketData, vReturn);

			++(pThis->gPrivate_size);

			if(pThis->gPrivate_rootKeyNode == NULL)
			{
				pThis->gPrivate_rootKeyNode = (pThis->gPrivate_keyNodes + vReturn);
				pThis->gPrivate_rootKeyNode->gPrivate_nextIndex = ((size_t)-1);
				pThis->gPrivate_rootKeyNode->gPrivate_previousIndex = ((size_t)-1);
			}
			else
			{
				(pThis->gPrivate_keyNodes + vReturn)->gPrivate_nextIndex = ((size_t)-1);

				if(pThis->gPrivate_lastKeyNode != NULL)
				{
					(pThis->gPrivate_keyNodes + vReturn)->gPrivate_previousIndex =
							pThis->gPrivate_lastKeyNode->gPrivate_index;
					pThis->gPrivate_lastKeyNode->gPrivate_nextIndex = vReturn;
					pThis->gPrivate_lastKeyNode = (pThis->gPrivate_keyNodes + vReturn);
				}
				else
				{
					(pThis->gPrivate_keyNodes + vReturn)->gPrivate_previousIndex =
							pThis->gPrivate_rootKeyNode->gPrivate_index;
					pThis->gPrivate_rootKeyNode->gPrivate_nextIndex = vReturn;
					pThis->gPrivate_lastKeyNode = (pThis->gPrivate_keyNodes + vReturn);
				} 
			} 

			(pThis->gPrivate_keyNodes + vReturn)->gPrivate_index = vReturn;

			*pReturn = 2;
		}
		else
			{*pReturn = 0;} /* Don't touch (pThis->gPrivate_keys + vReturn) if present and not deleted */
	}

	return vReturn;
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_orderedHashTable_private_deleteElementAt(
		Crx_C_OrderedHashTable * pThis, size_t pBucketIndex)
{
	if((pBucketIndex != pThis->gPrivate_numberOfBuckets) &&
			!CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, pBucketIndex))
	{
		CRX__C__OrderedHashTable__MARK_BUCKET_CONTENT_DELETED(pThis->gPrivate_bucketData, 
				pBucketIndex);

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
					pThis->gPrivate_elements + pBucketIndex);
		}

		if((pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_previousIndex != ((size_t)-1))
		{
			(pThis->gPrivate_keyNodes + (pThis->gPrivate_keyNodes + pBucketIndex)->
					gPrivate_previousIndex)->gPrivate_nextIndex =
					(pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_nextIndex;
		}
		else
		{
			pThis->gPrivate_rootKeyNode = pThis->gPrivate_keyNodes +
					(pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_nextIndex;
		}

		if((pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_nextIndex != ((size_t)-1))
		{
			(pThis->gPrivate_keyNodes + (pThis->gPrivate_keyNodes + pBucketIndex)->
					gPrivate_nextIndex)->gPrivate_previousIndex =
					(pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_previousIndex;
		}
		else
		{
			pThis->gPrivate_lastKeyNode = pThis->gPrivate_keyNodes +
					(pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_previousIndex;
		}

		(pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_nextIndex = ((size_t)-1);
		(pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_previousIndex = ((size_t)-1);
		(pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_index = ((size_t)-1);

		--(pThis->gPrivate_size);
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_orderedHashTable_getSize(
		Crx_C_OrderedHashTable const * pThis)
	{return pThis->gPrivate_size;}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_orderedHashTable_tryMoveKeyAndElementAndSet(
		Crx_C_OrderedHashTable * pThis, void * pKey, void * pElement)
{
	CRX_SCOPE_META
	if(pThis->gPrivate_typeBluePrint__element == NULL)
		{return false;}
	
	CRX_SCOPE
	int vReturnedCode = 0;
	size_t vBucketNumber =
			crx_c_orderedHashTable_private_tryMoveKeyAndPrepareBucketFor(pThis,
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
						pThis->gPrivate_elements + (vBucketNumber * 
						pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
			}
		}

		if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT(
					pThis->gPrivate_elements + (vBucketNumber * 
					pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE), pElement);
		}
		else
		{
			memcpy(pThis->gPrivate_elements + (vBucketNumber * 
					pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE), pElement, 
					pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
		}

		return true;
	}
	else
		{return false;}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_orderedHashTable_tryMoveKeyAndSet(
		Crx_C_OrderedHashTable * pThis, void * CRX_NOT_NULL pKey, void * pElement)
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
		vBucketNumber = crx_c_orderedHashTable_private_tryMoveKeyAndPrepareBucketFor(pThis,
				pKey, &vReturnedCode);
	}

	if(pThis->gPrivate_typeBluePrint__element != NULL)
	{
		if(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != NULL)
		{
			pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT(vElement, pElement);

			vReturn = crx_c_orderedHashTable_tryMoveKeyAndElementAndSet(
					pThis, pKey, vElement);
		}
		else
		{
			if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

				vReturn = crx_c_orderedHashTable_tryMoveKeyAndElementAndSet(pThis, pKey,
						vElement);
			}
			else
			{
				vReturn = crx_c_orderedHashTable_tryMoveKeyAndElementAndSet(pThis, pKey,
						pElement);
			}
		}

		if((pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL) &&
				((pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != NULL) ||
				(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)))
		{
			if(vReturn)
				{pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT(vElement);}
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
					pThis->gPrivate_typeBluePrint__key->gFUNC__DESTRUCT(pThis->gPrivate_keys +
							(vBucketNumber * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE));
				}

				if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL)
				{
					pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT(pThis->gPrivate_keys +
							(vBucketNumber * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE), pKey);
				}
				else
				{
					memcpy(pThis->gPrivate_keys + 
							(vBucketNumber * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE),
							pKey, pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
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

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_orderedHashTable_tryMoveElementAndSet(
		Crx_C_OrderedHashTable * pThis, void * CRX_NOT_NULL pKey, void * CRX_NOT_NULL pElement)
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

		vReturn = crx_c_orderedHashTable_tryMoveKeyAndElementAndSet(pThis, vKey, pElement);
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vKey, pKey, pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);

			vReturn = crx_c_orderedHashTable_tryMoveKeyAndElementAndSet(pThis, vKey, pElement);
		}
		else
			{vReturn =  crx_c_orderedHashTable_tryMoveKeyAndElementAndSet(pThis, pKey, pElement);}
	}

	if((pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL) &&
			((pThis->gPrivate_typeBluePrint__key->gFUNC__COPY_CONSTRUCT != NULL) ||
			(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_CONSTRUCT != NULL)))
	{
		if(vReturn)
			{pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(vKey);}
	}

	return vReturn;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_orderedHashTable_set(
		Crx_C_OrderedHashTable * pThis, void * CRX_NOT_NULL pKey, void * pElement)
{
	CRX_SCOPE_META
	if((pThis->gPrivate_typeBluePrint__element == NULL) || (pElement == NULL))
		{return false;}

	CRX_SCOPE
	unsigned char * vKey = (unsigned char *) CRX__ALLOCA(
			pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
	unsigned char * vElement = NULL;
	bool vReturn = false;

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
		{vReturn = crx_c_orderedHashTable_tryMoveKeyAndElementAndSet(pThis, vKey, vElement);}
	else
		{vReturn = crx_c_orderedHashTable_tryMoveKeyAndSet(pThis, vKey, NULL);}

	if(vReturn)
	{
		if(pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT != NULL)
			{pThis->gPrivate_typeBluePrint__key->gFUNC__MOVE_DESTRUCT(vKey);}

		if((pThis->gPrivate_typeBluePrint__element != NULL) &&
				(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL))
			{pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT(vElement);}
	}

	return vReturn;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void * crx_c_orderedHashTable_get(Crx_C_OrderedHashTable * pThis,
		void const * CRX_NOT_NULL pKey)
{
	CRX_SCOPE_META
	if(pThis->gPrivate_typeBluePrint__element == NULL)
		{return NULL;}

	CRX_SCOPE
	size_t vBucketIndex = crx_c_orderedHashTable_private_get(pThis, pKey);

	if(vBucketIndex != pThis->gPrivate_numberOfBuckets)
	{
		return (pThis->gPrivate_elements + 
				(vBucketIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
	}
	else
		{return NULL;}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void const * crx_c_orderedHashTable_constantGet(
		Crx_C_OrderedHashTable const * pThis, void const * CRX_NOT_NULL pKey)
{
	if(pThis->gPrivate_typeBluePrint__element == NULL)
		{return NULL;}

	return crx_c_orderedHashTable_get(((Crx_C_OrderedHashTable *)pThis), pKey);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_copyGet(
		Crx_C_OrderedHashTable const * pThis, void * CRX_NOT_NULL pReturn, 
		void const * CRX_NOT_NULL pKey)
{
	CRX_SCOPE_META
	if((pThis->gPrivate_typeBluePrint__element == NULL) ||
			(!pThis->gPrivate_typeBluePrint__element->gIS_COPYABLE))
		{return;}

	CRX_SCOPE
	size_t vBucketIndex = crx_c_orderedHashTable_private_get(pThis, pKey);

	if(vBucketIndex != pThis->gPrivate_numberOfBuckets)
	{
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
	}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_orderedHashTable_hasKey(
		Crx_C_OrderedHashTable const * pThis, void const * pKey)
{
	return (crx_c_orderedHashTable_private_get(pThis, pKey) !=
			pThis->gPrivate_numberOfBuckets);
}

CRX__LIB__PUBLIC_C_FUNCTION() void const * crx_c_orderedHashTable_getKeyFromIndex(
		Crx_C_OrderedHashTable const * pThis, size_t pIndex)
{
	if(CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, ((size_t)pIndex)))
		{return NULL;}

	return pThis->gPrivate_keys + (pIndex * pThis->gPrivate_typeBluePrint__key->gBYTE_SIZE);
}
CRX__LIB__PUBLIC_C_FUNCTION() void const * crx_c_orderedHashTable_getElementFromIndex(
		Crx_C_OrderedHashTable const * pThis, size_t pIndex)
{
	if(CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, ((size_t)pIndex)))
		{return NULL;}

	return (pThis->gPrivate_elements + pIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_remove(Crx_C_OrderedHashTable * pThis,
		void const * CRX_NOT_NULL pKey)
{
	crx_c_orderedHashTable_private_deleteElementAt(pThis,
			crx_c_orderedHashTable_private_get(pThis, pKey));
}

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_orderedHashTable_getStartIndex(
		Crx_C_OrderedHashTable const * pThis)
{
	if((pThis->gPrivate_keyNodes == NULL) || (pThis->gPrivate_rootKeyNode == NULL))
		{return 0;}

	return pThis->gPrivate_rootKeyNode->gPrivate_index;
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_orderedHashTable_getEndIndex(
		Crx_C_OrderedHashTable const * pThis)
	{return pThis->gPrivate_numberOfBuckets;}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_orderedHashTable_getNextIndex(
		Crx_C_OrderedHashTable const * pThis, size_t pIndex)
{
	if((pThis->gPrivate_keyNodes == NULL) || (pIndex >= pThis->gPrivate_numberOfBuckets) ||
			((pThis->gPrivate_keyNodes + pIndex)->gPrivate_nextIndex == ((size_t)-1)))
		{return pThis->gPrivate_numberOfBuckets;}

	return (pThis->gPrivate_keyNodes + (pThis->gPrivate_keyNodes + pIndex)->
			gPrivate_nextIndex)->gPrivate_index;
}

CRX__LIB__PRIVATE_C_FUNCTION() size_t crx_c_orderedHashTable_private_prepareSeedForHash(
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

