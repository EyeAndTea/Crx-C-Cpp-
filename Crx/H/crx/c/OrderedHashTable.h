#if(!defined(CRX__C__ORDERED_HASH_TABLE___h__))
#define CRX__C__ORDERED_HASH_TABLE___h__

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
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>
#include "Crx/H/crx/nonCrxed/standard/stdint.h"
#include "Crx/H/crx/c/TypeBluePrint.h"
#include "Crx/H/crx/c/HashTable.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()

/*
	USAGE: SEE HASHTABLE
*/

#if(UINT32_MAX < SIZE_MAX)
	#define CRX__C__ORDERED_HASH_TABLE__IS_TO_GENERATE_UINT64_RANDOM CRXM__FALSE
#else
	#define CRX__C__ORDERED_HASH_TABLE__IS_TO_GENERATE_UINT64_RANDOM CRXM__TRUE
#endif


#if(!CRX_ARE_VARIADIC_MACROS_EMULATED)
	#define CRX__C__OrderedHashTable__DECLARE(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__OrderedHashTable__DECLARE, __VA_ARGS__)
#else
	#define CRX__C__OrderedHashTable__DECLARE(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__OrderedHashTable__DECLARE, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20)
#endif

/*KEYS ONLY.	(KEYS COPYABLE)*/
#define CRX__C__OrderedHashTable__DECLARE__11(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		pFUNC_KEY_COPY_CONSTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH) \
_CRX__C__OrderedHashTable__DECLARE(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		CRXM__TRUE, pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		CRXM__TRUE, pFUNC_KEY_COPY_CONSTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		CRXM__FALSE, CRXM__FALSE, \
		CRXM__FALSE, CRXM__FALSE, \
		CRXM__FALSE, CRXM__FALSE, \
		\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())

/*KEYS AND ELEMENTS.	(KEYS COPYABLE)*/
#define CRX__C__OrderedHashTable__DECLARE__15(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		pFUNC_KEY_COPY_CONSTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__OrderedHashTable__DECLARE(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		CRXM__FALSE, pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		CRXM__TRUE, pFUNC_KEY_COPY_CONSTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__FALSE, CRXM__FALSE, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())
#define CRX__C__OrderedHashTable__DECLARE__16(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		pFUNC_KEY_COPY_CONSTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__OrderedHashTable__DECLARE(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		CRXM__FALSE, pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		CRXM__TRUE, pFUNC_KEY_COPY_CONSTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__TRUE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())


#if(!CRX_ARE_VARIADIC_MACROS_EMULATED)
	#define CRX__C__OrderedHashTable__DECLARE2(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__OrderedHashTable__DECLARE2, __VA_ARGS__)
#else
	#define CRX__C__OrderedHashTable__DECLARE2(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__OrderedHashTable__DECLARE2, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20)
#endif

/*KEYS ONLY.	(KEYS NOT COPYABLE)*/
#define CRX__C__OrderedHashTable__DECLARE2__10(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH) \
_CRX__C__OrderedHashTable__DECLARE(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		CRXM__TRUE, pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		CRXM__FALSE, CRXM__FALSE, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		CRXM__FALSE, CRXM__FALSE, \
		CRXM__FALSE, CRXM__FALSE, \
		CRXM__FALSE, CRXM__FALSE, \
		\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())

/*KEYS AND ELEMENTS.	(KEYS NOT COPYABLE)*/
#define CRX__C__OrderedHashTable__DECLARE2__14(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__OrderedHashTable__DECLARE(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		CRXM__FALSE, pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		CRXM__FALSE, CRXM__FALSE, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__FALSE, CRXM__FALSE, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())
#define CRX__C__OrderedHashTable__DECLARE2__15(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__OrderedHashTable__DECLARE(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		CRXM__FALSE, pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		CRXM__FALSE, CRXM__FALSE, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__TRUE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())


#define _CRX__C__OrderedHashTable__DECLARE(pHASH_TABLE_TYPE_NAME, pMEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		pIS_KEYS_ONLY, pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		pIS_KEY_COPYABLE, pFUNC_KEY_COPY_CONSTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pIS_ELEMENT_COPYABLE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		PUBLIC, PRIVATE) \
	\
	typedef struct pHASH_TABLE_TYPE_NAME ## _Private_KeyNode \
			pHASH_TABLE_TYPE_NAME ## _Private_KeyNode; \
	\
	typedef struct pHASH_TABLE_TYPE_NAME \
	{ \
		pSIZE_T gPrivate_numberOfBuckets; \
		pSIZE_T gPrivate_size; \
		pSIZE_T gPrivate_numberOfBucketsEverUsed; \
		pSIZE_T gPrivate_upperBoundOfNumberOfBucketsEverUsed; \
		size_t gPrivate_seed; \
		uint32_t * gPrivate_bucketData; \
		pHASH_TABLE_TYPE_NAME ## _Private_KeyNode * gPrivate_rootKeyNode; \
		pHASH_TABLE_TYPE_NAME ## _Private_KeyNode * gPrivate_lastKeyNode; \
		pHASH_TABLE_TYPE_NAME ## _Private_KeyNode * gPrivate_keyNodes; \
		CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
		pELEMENT_TYPE * gPrivate_elements;, ) \
	} pHASH_TABLE_TYPE_NAME; \
	\
	typedef struct pHASH_TABLE_TYPE_NAME ## _Private_KeyNode \
	{ \
		pSIZE_T gPrivate_nextIndex; \
		pSIZE_T gPrivate_previousIndex; \
		pSIZE_T gPrivate_index; \
		pKEY_TYPE gPrivate_key; \
	} pHASH_TABLE_TYPE_NAME ## _Private_KeyNode; \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## copyConstruct(pHASH_TABLE_TYPE_NAME * pThis, \
			pHASH_TABLE_TYPE_NAME const * CRX_NOT_NULL pHashTable); \
	PUBLIC pHASH_TABLE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## new(); \
	PUBLIC pHASH_TABLE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## moveNew( \
			pHASH_TABLE_TYPE_NAME * pHashTable); \
	PUBLIC pHASH_TABLE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## copyNew( \
			pHASH_TABLE_TYPE_NAME const * pHashTable); \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## destruct(pHASH_TABLE_TYPE_NAME * pThis); \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## free(pHASH_TABLE_TYPE_NAME * pThis); \
	\
	CRX__C__TYPE_BLUE_PRINT__DECLARE_GET_BLUE_PRINT( \
			pHASH_TABLE_TYPE_NAME, pMEMBER_FUNCTIONS_PREFIX, \
			CRXM__TRUE, CRXM__TRUE, \
			CRXM__AND(pIS_KEY_COPYABLE, CRXM__OR(pIS_KEYS_ONLY, pIS_ELEMENT_COPYABLE)), CRXM__TRUE, \
			CRXM__FALSE, CRXM__FALSE); \
	\
	PRIVATE pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## private_get(pHASH_TABLE_TYPE_NAME const * pThis, \
			pKEY_TYPE const * pKey); \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## empty(pHASH_TABLE_TYPE_NAME * pThis); \
	PRIVATE bool pMEMBER_FUNCTIONS_PREFIX ## private_setCapacity(pHASH_TABLE_TYPE_NAME * pThis, \
			pSIZE_T pNumberOfBuckets); \
	PRIVATE bool pMEMBER_FUNCTIONS_PREFIX ## private_setCapacity2(pHASH_TABLE_TYPE_NAME * pThis, \
			pSIZE_T pNumberOfBuckets); \
	PRIVATE pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## private_tryMoveKeyAndPrepareBucketFor( \
			pHASH_TABLE_TYPE_NAME * pThis, pKEY_TYPE * pKey, int * pReturn); \
	PRIVATE void pMEMBER_FUNCTIONS_PREFIX ## private_deleteElementAt(pHASH_TABLE_TYPE_NAME * pThis, \
			pSIZE_T pBucketIndex); \
	\
	PUBLIC pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## getSize(pHASH_TABLE_TYPE_NAME const * pThis); \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndElementAndSet( \
			pHASH_TABLE_TYPE_NAME * pThis, pKEY_TYPE * pKey, pELEMENT_TYPE * pElement);, ) \
	CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndSet( \
			pHASH_TABLE_TYPE_NAME * pThis, pKEY_TYPE * pKey, pELEMENT_TYPE * pElement);, \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndSet( \
			pHASH_TABLE_TYPE_NAME * pThis, pKEY_TYPE * pKey);) \
	CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## tryMoveElementAndSet( \
			pHASH_TABLE_TYPE_NAME * pThis, pKEY_TYPE * pKey, pELEMENT_TYPE * pElement);, ) \
	CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## set( \
			pHASH_TABLE_TYPE_NAME * pThis, pKEY_TYPE * pKey, pELEMENT_TYPE * pElement);, \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## set( \
			pHASH_TABLE_TYPE_NAME * pThis, pKEY_TYPE * pKey); ) \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
	PUBLIC pELEMENT_TYPE * pMEMBER_FUNCTIONS_PREFIX ## get(pHASH_TABLE_TYPE_NAME * pThis, \
			pKEY_TYPE const * pKey);, ) \
	CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
	PUBLIC pELEMENT_TYPE const * pMEMBER_FUNCTIONS_PREFIX ## constantGet( \
			pHASH_TABLE_TYPE_NAME const * pThis, pKEY_TYPE const * pKey);, ) \
	CRXM__IFELSE2(CRXM__AND(CRXM__NOT(pIS_KEYS_ONLY), pIS_ELEMENT_COPYABLE), \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## copyGetTo(pHASH_TABLE_TYPE_NAME const * pThis, \
			pELEMENT_TYPE * pReturn, pKEY_TYPE const * pKey);, \
	PUBLIC pELEMENT_TYPE pMEMBER_FUNCTIONS_PREFIX ## copyGet(pHASH_TABLE_TYPE_NAME const * pThis, \
			pKEY_TYPE const * pKey);), ) \
	\
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## hasKey(pHASH_TABLE_TYPE_NAME const * pThis, \
			pKEY_TYPE const * pKey); \
	\
	PUBLIC pKEY_TYPE const * pMEMBER_FUNCTIONS_PREFIX ## getKeyFromIndex( \
			pHASH_TABLE_TYPE_NAME const * pThis, size_t pIndex); \
	PUBLIC pELEMENT_TYPE const * pMEMBER_FUNCTIONS_PREFIX ## getElementFromIndex( \
			pHASH_TABLE_TYPE_NAME const * pThis, size_t pIndex); \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## remove(pHASH_TABLE_TYPE_NAME * pThis, \
			pKEY_TYPE const * pKey); \
	\
	CRX__LIB__PUBLIC_INLINE_C_FUNCTION() pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## getStartIndex( \
			pHASH_TABLE_TYPE_NAME const * pThis); \
	CRX__LIB__PUBLIC_INLINE_C_FUNCTION() pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## getLastIndex( \
			pHASH_TABLE_TYPE_NAME const * pThis); \
	CRX__LIB__PUBLIC_INLINE_C_FUNCTION() pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## getEndIndex( \
			pHASH_TABLE_TYPE_NAME const * pThis); \
	CRX__LIB__PUBLIC_INLINE_C_FUNCTION() pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## getNextIndex( \
			pHASH_TABLE_TYPE_NAME const * pThis, size_t pIndex); \
	CRX__LIB__PUBLIC_INLINE_C_FUNCTION() pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## getPreviousIndex( \
			pHASH_TABLE_TYPE_NAME const * pThis); \
	\
	PRIVATE size_t pMEMBER_FUNCTIONS_PREFIX ## prepareSeedForHash( \
			void const * pPointer, void const * pPointer2);
//#END_DEFINE

#if(!CRX_ARE_VARIADIC_MACROS_EMULATED)
	#define CRX__C__OrderedHashTable__DEFINE(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__OrderedHashTable__DEFINE, __VA_ARGS__)
#else
	#define CRX__C__OrderedHashTable__DEFINE(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__OrderedHashTable__DEFINE, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20)
#endif

/*KEYS ONLY.	(KEYS COPYABLE)*/
#define CRX__C__OrderedHashTable__DEFINE__11(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		pFUNC_KEY_COPY_CONSTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH) \
_CRX__C__OrderedHashTable__DEFINE(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		CRXM__TRUE, pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		CRXM__TRUE, pFUNC_KEY_COPY_CONSTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		CRXM__FALSE, CRXM__FALSE, \
		CRXM__FALSE, CRXM__FALSE, \
		CRXM__FALSE, CRXM__FALSE, \
		\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())

/*KEYS AND ELEMENTS.	(KEYS COPYABLE)*/
#define CRX__C__OrderedHashTable__DEFINE__15(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		pFUNC_KEY_COPY_CONSTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__OrderedHashTable__DEFINE(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		CRXM__FALSE, pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		CRXM__TRUE, pFUNC_KEY_COPY_CONSTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__FALSE, CRXM__FALSE, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())
#define CRX__C__OrderedHashTable__DEFINE__16(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		pFUNC_KEY_COPY_CONSTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__OrderedHashTable__DEFINE(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		CRXM__FALSE, pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		CRXM__TRUE, pFUNC_KEY_COPY_CONSTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__TRUE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())


#if(!CRX_ARE_VARIADIC_MACROS_EMULATED)
	#define CRX__C__OrderedHashTable__DEFINE2(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__OrderedHashTable__DEFINE2, __VA_ARGS__)
#else
	#define CRX__C__OrderedHashTable__DEFINE2(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__OrderedHashTable__DEFINE2, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20)
#endif

/*KEYS ONLY.	(KEYS NOT COPYABLE)*/
#define CRX__C__OrderedHashTable__DEFINE2__10(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH) \
_CRX__C__OrderedHashTable__DEFINE(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		CRXM__TRUE, pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		CRXM__FALSE, CRXM__FALSE, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		CRXM__FALSE, CRXM__FALSE, \
		CRXM__FALSE, CRXM__FALSE, \
		CRXM__FALSE, CRXM__FALSE, \
		\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())

/*KEYS AND ELEMENTS.	(KEYS NOT COPYABLE)*/
#define CRX__C__OrderedHashTable__DEFINE2__14(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__OrderedHashTable__DEFINE(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		CRXM__FALSE, pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		CRXM__FALSE, CRXM__FALSE, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__FALSE, CRXM__FALSE, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())
#define CRX__C__OrderedHashTable__DEFINE2__15(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__OrderedHashTable__DEFINE(pHASH_TABLE_TYPE_NAME, pHASH_TABLE_MEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		CRXM__FALSE, pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		CRXM__FALSE, CRXM__FALSE, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__TRUE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())
		
		
#define _CRX__C__OrderedHashTable__DEFINE(pHASH_TABLE_TYPE_NAME, pMEMBER_FUNCTIONS_PREFIX, \
		pSIZE_T, pSIZE_T_MAX, \
		pIS_KEYS_ONLY, pKEY_TYPE, pFUNC_KEY_DESTRUCTOR, \
		pIS_KEY_COPYABLE, pFUNC_KEY_COPY_CONSTRUCTOR, \
		pFUNC_KEY_MOVE_CONSTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR, \
		pFUNC_ARE_KEYS_EQUAL, pFUNC_COMPUTE_HASH, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pIS_ELEMENT_COPYABLE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		PUBLIC, PRIVATE) \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## copyConstruct(pHASH_TABLE_TYPE_NAME * pThis, \
			pHASH_TABLE_TYPE_NAME const * CRX_NOT_NULL pHashTable) \
	{ \
		CRXM__IFELSE2(CRXM__OR(CRXM__NOT(pIS_KEY_COPYABLE), \
				CRXM__AND(CRXM__NOT(pIS_KEYS_ONLY), \
						CRXM__NOT(pIS_ELEMENT_COPYABLE))), abort();, \
	\
		CRX__SET_TO_ZERO(pHASH_TABLE_TYPE_NAME, *pThis); \
	\
		if(pMEMBER_FUNCTIONS_PREFIX ## private_setCapacity(pThis, pHashTable->gPrivate_size)) \
		{ \
			CRX_FOR(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode * tKeyNode = \
					pHashTable->gPrivate_rootKeyNode, tKeyNode != NULL, \
					tKeyNode = ((tKeyNode->gPrivate_nextIndex != pSIZE_T_MAX) ? \
					(pHashTable->gPrivate_keyNodes + tKeyNode->gPrivate_nextIndex) : NULL)) \
			{ \
				CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
				( \
					pMEMBER_FUNCTIONS_PREFIX ## set(pThis, \
							&((pHashTable->gPrivate_keyNodes + \
									tKeyNode->gPrivate_index)->gPrivate_key), \
							pHashTable->gPrivate_elements + tKeyNode->gPrivate_index); \
				) \
				( \
					pMEMBER_FUNCTIONS_PREFIX ## set(pThis, \
							&((pHashTable->gPrivate_keyNodes + \
									tKeyNode->gPrivate_index)->gPrivate_key)); \
				) \
			} \
			CRX_ENDFOR \
		} \
	)} \
	\
	PUBLIC pHASH_TABLE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## new() \
		{return (pHASH_TABLE_TYPE_NAME *)(calloc(1, sizeof(pHASH_TABLE_TYPE_NAME)));} \
	\
	PUBLIC pHASH_TABLE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## moveNew( \
			pHASH_TABLE_TYPE_NAME * pHashTable) \
	{ \
		pHASH_TABLE_TYPE_NAME * vReturn = (pHASH_TABLE_TYPE_NAME *)(calloc(1,\
				sizeof(pHASH_TABLE_TYPE_NAME))); \
	\
		if(vReturn != NULL) \
			{memcpy(vReturn, pHashTable, sizeof(pHASH_TABLE_TYPE_NAME));} \
	\
		return vReturn; \
	} \
	\
	PUBLIC pHASH_TABLE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## copyNew( \
			pHASH_TABLE_TYPE_NAME const * pHashTable) \
	{ \
		CRXM__IFELSE2(CRXM__OR(CRXM__NOT(pIS_KEY_COPYABLE), \
				CRXM__AND(CRXM__NOT(pIS_KEYS_ONLY), \
						CRXM__NOT(pIS_ELEMENT_COPYABLE))), abort();, \
	\
		pHASH_TABLE_TYPE_NAME * vReturn = (pHASH_TABLE_TYPE_NAME *)(calloc(1,\
				sizeof(pHASH_TABLE_TYPE_NAME))); \
	\
		if(vReturn != NULL) \
			{pMEMBER_FUNCTIONS_PREFIX ## copyConstruct(vReturn, pHashTable);} \
	\
		return vReturn; \
	)} \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## destruct(pHASH_TABLE_TYPE_NAME * pThis) \
	{ \
		CRXM__IFELSE2(CRXM__OR(pFUNC_KEY_DESTRUCTOR, CRXM__AND(CRXM__NOT(pIS_KEYS_ONLY), \
				pFUNC_ELEMENT_DESTRUCTOR)), \
		pMEMBER_FUNCTIONS_PREFIX ## empty(pThis);, ) \
	\
		free((void *) pThis->gPrivate_keyNodes); \
		pThis->gPrivate_keyNodes = NULL; \
		free(pThis->gPrivate_bucketData); \
		pThis->gPrivate_bucketData = NULL; \
	\
		CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
		( \
			free((void *) pThis->gPrivate_elements); \
			pThis->gPrivate_elements = NULL; \
		)() \
	} \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## free(pHASH_TABLE_TYPE_NAME * pThis) \
		{free(pThis);} \
	\
	CRX__C__TYPE_BLUE_PRINT__DEFINE_GET_BLUE_PRINT( \
			pHASH_TABLE_TYPE_NAME, pMEMBER_FUNCTIONS_PREFIX, \
			CRXM__TRUE, CRXM__TRUE, \
			CRXM__AND(pIS_KEY_COPYABLE, CRXM__OR(pIS_KEYS_ONLY, pIS_ELEMENT_COPYABLE)), CRXM__TRUE, \
			CRXM__FALSE, CRXM__FALSE) \
	\
	PRIVATE pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## private_get(pHASH_TABLE_TYPE_NAME const * pThis, \
			pKEY_TYPE const * pKey) \
	{																	\
		if(pThis->gPrivate_numberOfBuckets == 0) \
			{return 0;} \
	\
		pSIZE_T vMask = pThis->gPrivate_numberOfBuckets - 1; \
		pSIZE_T vIndex = ((pSIZE_T)pFUNC_COMPUTE_HASH(pThis->gPrivate_seed, pKey)) & vMask; \
		pSIZE_T vLastIndex = vIndex; \
		pSIZE_T vStep = 0; \
	\
		while(!CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(pThis->gPrivate_bucketData, vIndex) && \
				(CRX__C__OrderedHashTable__IS_BUCKET_CONTENT_DELETED(pThis->gPrivate_bucketData, vIndex) || \
				!pFUNC_ARE_KEYS_EQUAL(&((pThis->gPrivate_keyNodes + vIndex)->gPrivate_key), \
						pKey))) \
		{ \
			vIndex = (vIndex + (++vStep)) & vMask; \
	\
			if(vIndex == vLastIndex) \
				{return pThis->gPrivate_numberOfBuckets;} \
		} \
	\
		return (CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, \
				vIndex) ? pThis->gPrivate_numberOfBuckets : vIndex); \
	} \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## empty(pHASH_TABLE_TYPE_NAME * pThis) \
	{ \
		if(pThis->gPrivate_bucketData != NULL) \
		{ \
			CRXM__IFELSE(CRXM__OR(CRXM__AND(CRXM__NOT(pIS_KEYS_ONLY), \
					pFUNC_ELEMENT_DESTRUCTOR), pFUNC_KEY_DESTRUCTOR)) \
			( \
				CRX_FOR(pSIZE_T tI = 0, \
						tI != pThis->gPrivate_numberOfBuckets, ++tI) \
				{ \
					if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, \
							tI)) \
						{continue;} \
	\
					CRXM__IFELSE(CRXM__AND(CRXM__NOT(pIS_KEYS_ONLY), \
							pFUNC_ELEMENT_DESTRUCTOR)) \
					( \
						pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements + tI); \
					)() \
					CRXM__IFELSE(pFUNC_KEY_DESTRUCTOR) \
					( \
						pFUNC_KEY_DESTRUCTOR(&((pThis->gPrivate_keyNodes + \
								tI)->gPrivate_key)); \
					)() \
				} \
				CRX_ENDFOR \
			)() \
	\
			memset(pThis->gPrivate_bucketData, 0xaa, \
					CRX__C__OrderedHashTable__GET_SIZE_OF_BUCKET_DATA( \
					pThis->gPrivate_numberOfBuckets) * sizeof(uint32_t)); \
			pThis->gPrivate_size = 0; \
			pThis->gPrivate_numberOfBucketsEverUsed = 0; \
			pThis->gPrivate_rootKeyNode = NULL; \
			pThis->gPrivate_lastKeyNode = NULL; \
		} \
	} \
	\
	PRIVATE bool pMEMBER_FUNCTIONS_PREFIX ## private_setCapacity(pHASH_TABLE_TYPE_NAME * pThis, \
			pSIZE_T pNumberOfBuckets) \
	{ /* This function uses 0.25*gPrivate_numberOfBuckets bytes of working space instead of [sizeof(key_t+val_t)+.25]*gPrivate_numberOfBuckets. */ \
		CRX_SCOPE_META \
		if(pNumberOfBuckets > ((pSIZE_T_MAX >> 1) + 1)) \
			{return false;} \
	\
		CRX_SCOPE \
		uint32_t * vBucketData = NULL; \
		pSIZE_T vNumberOfBuckets = CRX__C__OrderedHashTable__ROUND_UP_TO_POWER_OF_TWO( \
				pNumberOfBuckets); \
		bool vIsRehashingRequired = true; \
	\
		{ \
			if(vNumberOfBuckets < 4) \
				{vNumberOfBuckets = 4;} \
	\
			if(pThis->gPrivate_size >= (pSIZE_T)(vNumberOfBuckets * 0.77 + 0.5)) \
				{vIsRehashingRequired = false;}	/* requested gPrivate_size is too small */ \
			else \
			{ /* hash table gPrivate_size to be changed (shrink or expand); rehash */ \
				vBucketData = (uint32_t *)(malloc( \
						CRX__C__OrderedHashTable__GET_SIZE_OF_BUCKET_DATA(vNumberOfBuckets) * \
						sizeof(uint32_t)));	\
	\
				if(vBucketData != NULL) \
				{ \
					memset(vBucketData, 0xaa, \
							CRX__C__OrderedHashTable__GET_SIZE_OF_BUCKET_DATA(vNumberOfBuckets) * \
									sizeof(uint32_t)); \
	\
					if(pThis->gPrivate_numberOfBuckets < vNumberOfBuckets) \
					{	/* expand */ \
						pHASH_TABLE_TYPE_NAME ## _Private_KeyNode * tKeyNodes = \
								(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *)(malloc( \
								vNumberOfBuckets * \
								sizeof(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode))); \
	\
						if(tKeyNodes != NULL) \
						{ \
							bool vIsFirst = true;\
	\
							CRX_FOR(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode * \
									tKeyNode = pThis->gPrivate_rootKeyNode, \
									tKeyNode != NULL, \
									tKeyNode = ((tKeyNode->gPrivate_nextIndex != pSIZE_T_MAX) ? \
											(pThis->gPrivate_keyNodes + \
													tKeyNode->gPrivate_nextIndex) : NULL)) \
							{ \
								CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE(pSIZE_T_MAX, \
										pFUNC_KEY_MOVE_CONSTRUCTOR, pKEY_TYPE, \
										tKeyNodes + tKeyNode->gPrivate_index, \
										tKeyNode); \
	\
								CRXM__IFELSE(pFUNC_KEY_MOVE_DESTRUCTOR) \
								( \
									pFUNC_KEY_MOVE_DESTRUCTOR(&(tKeyNode->gPrivate_key)); \
								)() \
	\
								if(vIsFirst) \
								{ \
									pThis->gPrivate_rootKeyNode = \
											tKeyNodes + tKeyNode->gPrivate_index; \
	\
									vIsFirst = false; \
								} \
								else if(tKeyNode->gPrivate_nextIndex == pSIZE_T_MAX) \
								{ \
									pThis->gPrivate_lastKeyNode = \
											tKeyNodes + tKeyNode->gPrivate_index; \
								} \
	\
								tKeyNode = tKeyNodes + tKeyNode->gPrivate_index; \
							} \
							CRX_ENDFOR \
	\
							free(pThis->gPrivate_keyNodes); \
							pThis->gPrivate_keyNodes = tKeyNodes; \
						} \
						else \
						{ \
							free(vBucketData); \
							vBucketData = NULL; \
						} \
	\
						CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
						( \
							if(tKeyNodes != NULL) \
							{ \
								pELEMENT_TYPE * tElements; \
	\
								tElements = (pELEMENT_TYPE*)(malloc( \
										vNumberOfBuckets * sizeof(pELEMENT_TYPE))); \
	\
								if(tElements != NULL) \
								{ \
									CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
									( \
										CRX_FOR(pSIZE_T tI = 0, tI < pThis->gPrivate_numberOfBuckets, tI++) \
										{ \
											if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY( \
													pThis->gPrivate_bucketData, tI) == 0) \
											{ \
												pFUNC_ELEMENT_MOVE_CONSTRUCTOR(tElements + tI, \
														pThis->gPrivate_elements + tI); \
	\
												CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR,  \
												pFUNC_ELEMENT_MOVE_DESTRUCTOR( \
														pThis->gPrivate_elements + tI);, ) \
											} \
										} \
										CRX_ENDFOR \
									) \
									( \
										memcpy(tElements, pThis->gPrivate_elements, \
												sizeof(pELEMENT_TYPE) * \
												pThis->gPrivate_numberOfBuckets); \
	\
										CRX_FOR(pSIZE_T tI = 0, \
												tI < pThis->gPrivate_numberOfBuckets, tI++) \
										{ \
											if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY( \
													pThis->gPrivate_bucketData, tI) == 0) \
											{ \
												CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR,  \
												pFUNC_ELEMENT_MOVE_DESTRUCTOR( \
														pThis->gPrivate_elements + tI);, ) \
											} \
										} \
										CRX_ENDFOR \
									) \
	\
									free(pThis->gPrivate_elements); \
									pThis->gPrivate_elements = tElements; \
								} \
								else \
								{ \
									free(vBucketData); \
									vBucketData = NULL; \
								} \
							} \
						)() \
					} /* otherwise shrink */ \
				} \
			} \
		} \
	\
		if(vBucketData != NULL) \
		{ \
			if(vIsRehashingRequired) \
			{ /* rehashing is needed */ \
				size_t tSeed = 0; \
				unsigned char * tKeyNode = (unsigned char *) CRX__ALLOCA( \
						sizeof(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode)); \
				unsigned char * tKeyNode_temp = (unsigned char *) CRX__ALLOCA( \
						sizeof(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode)); \
				CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
				unsigned char * tElement = (unsigned char *) CRX__ALLOCA( \
						sizeof(pELEMENT_TYPE));, ) \
				CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
				unsigned char * tElement_tmp = (unsigned char *) CRX__ALLOCA(\
						sizeof(pELEMENT_TYPE));, ) \
				bool tWasRootKeyNodeSet = false; \
				bool tWasLastKeyNodeSet = false; \
	\
				if(pThis->gPrivate_numberOfBuckets <= vNumberOfBuckets) \
				{ \
					CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
					( \
						tSeed = pMEMBER_FUNCTIONS_PREFIX ## prepareSeedForHash(pThis->gPrivate_keyNodes, \
								pThis->gPrivate_elements); \
					) \
					( \
						tSeed = pMEMBER_FUNCTIONS_PREFIX ## prepareSeedForHash(pThis, \
								pThis->gPrivate_keyNodes); \
					) \
				} \
				else \
				{ \
					CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
					( \
						tSeed = pMEMBER_FUNCTIONS_PREFIX ## prepareSeedForHash(pThis->gPrivate_keyNodes, \
								pThis->gPrivate_elements + 101); \
					) \
					( \
						tSeed = pMEMBER_FUNCTIONS_PREFIX ## prepareSeedForHash(pThis, \
								pThis->gPrivate_keyNodes + 101); \
					) \
				} \
	\
				CRX_FOR(pSIZE_T tI = 0, tI != pThis->gPrivate_numberOfBuckets, ++tI) \
				{ \
					if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY( \
							pThis->gPrivate_bucketData, tI) == 0) \
					{ \
						pSIZE_T tNewMask = vNumberOfBuckets - 1; \
	\
						CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE(pSIZE_T_MAX, \
								pFUNC_KEY_MOVE_CONSTRUCTOR, pKEY_TYPE, \
								(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *)tKeyNode, \
								pThis->gPrivate_keyNodes + tI); \
						CRXM__IFELSE2(pFUNC_KEY_MOVE_DESTRUCTOR, \
						pFUNC_KEY_MOVE_DESTRUCTOR( \
								&((pThis->gPrivate_keyNodes + tI)->gPrivate_key)), ); \
	\
						CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
						( \
							CRXM__IFELSE(CRXM__AND(CRXM__AND(pIS_ELEMENT_COPYABLE, \
									CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR)), \
									CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))) \
							( \
								memcpy(tElement, pThis->gPrivate_elements + tI, \
										sizeof(pELEMENT_TYPE)); \
							) \
							( \
								CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
								( \
									pFUNC_ELEMENT_MOVE_CONSTRUCTOR(((pELEMENT_TYPE *)tElement), \
											pThis->gPrivate_elements + tI); \
								) \
								( \
									memcpy(tElement, pThis->gPrivate_elements + tI, \
											sizeof(pELEMENT_TYPE)); \
								) \
	\
								CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
								pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gPrivate_elements + tI);, ) \
							) \
						)() \
	\
						CRX__C__OrderedHashTable__MARK_BUCKET_CONTENT_DELETED( \
								pThis->gPrivate_bucketData, tI); \
	\
						while(true) \
						{ /* kick-out process; sort of like in Cuckoo hashing */ \
							pSIZE_T tIndex = ((pSIZE_T)pFUNC_COMPUTE_HASH(tSeed, \
									&(((pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *)tKeyNode)-> \
											gPrivate_key))) & tNewMask; \
							pSIZE_T tStep = 0; \
	\
							while(!CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(vBucketData, \
									tIndex)) \
								{tIndex = (tIndex + (++tStep)) & tNewMask;} \
	\
							CRX__C__OrderedHashTable__MARK_BUCKET_EVER_FILLED(vBucketData, tIndex);	\
	\
							if((tIndex < pThis->gPrivate_numberOfBuckets) && \
									(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, tIndex) == 0)) \
							{ /* kick out the existing element */ \
								{ \
									CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE(pSIZE_T_MAX, \
											pFUNC_KEY_MOVE_CONSTRUCTOR, pKEY_TYPE, \
											(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *) \
											tKeyNode_temp, pThis->gPrivate_keyNodes + tIndex); \
									CRXM__IFELSE2(pFUNC_KEY_MOVE_DESTRUCTOR, \
									pFUNC_KEY_MOVE_DESTRUCTOR( \
											&((pThis->gPrivate_keyNodes + tIndex)->gPrivate_key));, ) \
	\
									CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE(pSIZE_T_MAX, \
											pFUNC_KEY_MOVE_CONSTRUCTOR, pKEY_TYPE, \
											pThis->gPrivate_keyNodes + tIndex, \
											(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *)\
											tKeyNode); \
									CRXM__IFELSE2(pFUNC_KEY_MOVE_DESTRUCTOR, \
									pFUNC_KEY_MOVE_DESTRUCTOR(\
											&(((pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *) \
											tKeyNode)->gPrivate_key));, ) \
									(pThis->gPrivate_keyNodes + tIndex)->gPrivate_index = \
											tIndex; \
	\
									if((pThis->gPrivate_keyNodes + tIndex)-> \
											gPrivate_previousIndex != pSIZE_T_MAX) \
									{ \
										if((pThis->gPrivate_keyNodes + tIndex)-> \
												gPrivate_previousIndex != tIndex) \
										{ \
											(pThis->gPrivate_keyNodes + \
													(pThis->gPrivate_keyNodes + tIndex)-> \
													gPrivate_previousIndex)->gPrivate_nextIndex = \
													tIndex; \
										} \
										else \
										{ \
											((pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *) \
													tKeyNode_temp)->gPrivate_nextIndex = tIndex; \
										} \
									} \
	\
									if((pThis->gPrivate_keyNodes + tIndex)-> \
											gPrivate_nextIndex != pSIZE_T_MAX) \
									{ \
										if((pThis->gPrivate_keyNodes + tIndex)-> \
												gPrivate_nextIndex != tIndex) \
										{ \
											(pThis->gPrivate_keyNodes + \
													(pThis->gPrivate_keyNodes + tIndex)-> \
													gPrivate_nextIndex)->gPrivate_previousIndex = \
													tIndex; \
										} \
										else \
										{ \
											((pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *) \
													tKeyNode_temp)->gPrivate_previousIndex = tIndex; \
										} \
									} \
	\
									if(!tWasRootKeyNodeSet && \
											(pThis->gPrivate_rootKeyNode == (pThis->gPrivate_keyNodes + \
											((pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *) \
													tKeyNode)->gPrivate_index))) \
									{ \
										pThis->gPrivate_rootKeyNode = pThis->gPrivate_keyNodes + \
												tIndex; \
										tWasRootKeyNodeSet = true; \
									} \
									else if(!tWasLastKeyNodeSet && \
											(pThis->gPrivate_lastKeyNode == (pThis->gPrivate_keyNodes + \
											((pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *) \
													tKeyNode)->gPrivate_index))) \
									{ \
										pThis->gPrivate_lastKeyNode = pThis->gPrivate_keyNodes + \
												tIndex; \
										tWasLastKeyNodeSet = true; \
									} \
	\
									CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE(pSIZE_T_MAX, \
											pFUNC_KEY_MOVE_CONSTRUCTOR, pKEY_TYPE, \
											(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *)tKeyNode, \
											(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *) \
											tKeyNode_temp); \
									CRXM__IFELSE2(pFUNC_KEY_MOVE_DESTRUCTOR, \
									pFUNC_KEY_MOVE_DESTRUCTOR( \
											&(((pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *) \
											tKeyNode_temp)->gPrivate_key));, ) \
								} \
	\
								CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
								( \
									CRXM__IFELSE(CRXM__AND(CRXM__AND(pIS_ELEMENT_COPYABLE, \
											CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR)), \
											CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))) \
									( \
										memcpy(tElement_tmp, pThis->gPrivate_elements + tIndex, \
												sizeof(pELEMENT_TYPE)); \
										memcpy(pThis->gPrivate_elements + tIndex, tElement, \
												sizeof(pELEMENT_TYPE)); \
										memcpy(tElement, tElement_tmp, sizeof(pELEMENT_TYPE)); \
									) \
									( \
										CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
										( \
											pFUNC_ELEMENT_MOVE_CONSTRUCTOR( \
													((pELEMENT_TYPE *)tElement_tmp), \
													pThis->gPrivate_elements + tIndex); \
											CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
											pFUNC_ELEMENT_MOVE_DESTRUCTOR( \
													pThis->gPrivate_elements + tIndex), ); \
	\
											pFUNC_ELEMENT_MOVE_CONSTRUCTOR( \
													pThis->gPrivate_elements + tIndex, \
													((pELEMENT_TYPE *)tElement)); \
											CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
											pFUNC_ELEMENT_MOVE_DESTRUCTOR( \
													((pELEMENT_TYPE *)tElement));, ) \
	\
											pFUNC_ELEMENT_MOVE_CONSTRUCTOR( \
													((pELEMENT_TYPE *)tElement), \
													((pELEMENT_TYPE *)tElement_tmp)); \
											CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
											pFUNC_ELEMENT_MOVE_DESTRUCTOR( \
													((pELEMENT_TYPE *)tElement_tmp));, ) \
										) \
										( \
											memcpy(tElement_tmp, \
													pThis->gPrivate_elements + tIndex, \
													sizeof(pELEMENT_TYPE)); \
											CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
											pFUNC_ELEMENT_MOVE_DESTRUCTOR( \
													pThis->gPrivate_elements + tIndex);, ) \
	\
											memcpy(pThis->gPrivate_elements + tIndex, tElement, \
													sizeof(pELEMENT_TYPE)); \
											CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
											pFUNC_ELEMENT_MOVE_DESTRUCTOR( \
													((pELEMENT_TYPE *)tElement));, ) \
	\
											memcpy(tElement, tElement_tmp, sizeof(pELEMENT_TYPE)); \
											CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
											pFUNC_ELEMENT_MOVE_DESTRUCTOR( \
													((pELEMENT_TYPE *)tElement_tmp));, ) \
										) \
									) \
								)() \
	\
								CRX__C__OrderedHashTable__MARK_BUCKET_CONTENT_DELETED( \
										pThis->gPrivate_bucketData, tIndex); /* mark it as deleted in the old hash table */ \
							} \
							else \
							{ /* write the element and jump out of the loop */ \
								CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE(pSIZE_T_MAX, \
										pFUNC_KEY_MOVE_CONSTRUCTOR, pKEY_TYPE, \
										pThis->gPrivate_keyNodes + tIndex, \
										(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *)tKeyNode); \
	\
								CRXM__IFELSE2(pFUNC_KEY_MOVE_DESTRUCTOR, \
								pFUNC_KEY_MOVE_DESTRUCTOR( \
										&(((pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *) \
										tKeyNode)->gPrivate_key));, ) \
	\
								(pThis->gPrivate_keyNodes + tIndex)->gPrivate_index = \
										tIndex; \
	\
								if((pThis->gPrivate_keyNodes + tIndex)->gPrivate_previousIndex != \
										pSIZE_T_MAX) \
								{ \
									(pThis->gPrivate_keyNodes + \
											(pThis->gPrivate_keyNodes + tIndex)-> \
											gPrivate_previousIndex)->gPrivate_nextIndex = tIndex; \
								} \
	\
								if((pThis->gPrivate_keyNodes + tIndex)->gPrivate_nextIndex != \
										pSIZE_T_MAX) \
								{ \
									(pThis->gPrivate_keyNodes + \
											(pThis->gPrivate_keyNodes + tIndex)-> \
											gPrivate_nextIndex)->gPrivate_previousIndex = tIndex; \
								} \
	\
								if(!tWasRootKeyNodeSet && \
										(pThis->gPrivate_rootKeyNode == (pThis->gPrivate_keyNodes + \
										((pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *) \
												tKeyNode)->gPrivate_index))) \
								{ \
									pThis->gPrivate_rootKeyNode = pThis->gPrivate_keyNodes + \
											tIndex; \
									tWasRootKeyNodeSet = true; \
								} \
								else if(!tWasLastKeyNodeSet && \
										(pThis->gPrivate_lastKeyNode == (pThis->gPrivate_keyNodes + \
										((pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *) \
												tKeyNode)->gPrivate_index))) \
								{ \
									pThis->gPrivate_lastKeyNode = pThis->gPrivate_keyNodes + \
											tIndex; \
									tWasLastKeyNodeSet = true; \
								} \
	\
								CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
								( \
									CRXM__IFELSE(CRXM__AND(CRXM__AND(pIS_ELEMENT_COPYABLE, \
											CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR)), \
											CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))) \
									( \
										memcpy(pThis->gPrivate_elements + tIndex, tElement, \
												sizeof(pELEMENT_TYPE)); \
									) \
									( \
										CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
										( \
											pFUNC_ELEMENT_MOVE_CONSTRUCTOR( \
													pThis->gPrivate_elements + tIndex, \
													((pELEMENT_TYPE *)tElement)); \
										) \
										( \
											memcpy(pThis->gPrivate_elements + tIndex, tElement, \
													sizeof(pELEMENT_TYPE)); \
										) \
	\
										CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
										pFUNC_ELEMENT_MOVE_DESTRUCTOR(((pELEMENT_TYPE *)tElement)), ); \
									) \
								)() \
	\
								break; \
							} \
						} \
					} \
				} \
				CRX_ENDFOR \
	\
				if(pThis->gPrivate_numberOfBuckets > vNumberOfBuckets) \
				{ /* shrink the hash table */ \
					pHASH_TABLE_TYPE_NAME ## _Private_KeyNode * tKeyNodes = \
							(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode*)(malloc(vNumberOfBuckets * \
							sizeof(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode))); \
	\
					if(tKeyNodes != NULL) \
					{ \
						CRX_FOR(pSIZE_T tI = 0, tI < pThis->gPrivate_numberOfBuckets, tI++) \
						{ \
							if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY( \
									pThis->gPrivate_bucketData, tI) == 0) \
							{ \
								CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE(pSIZE_T_MAX, \
										pFUNC_KEY_MOVE_CONSTRUCTOR, pKEY_TYPE, \
										tKeyNodes + tI, pThis->gPrivate_keyNodes + tI); \
	\
								CRXM__IFELSE(pFUNC_KEY_MOVE_DESTRUCTOR) \
								( \
									pFUNC_KEY_MOVE_DESTRUCTOR( \
											&((pThis->gPrivate_keyNodes + tI)->gPrivate_key)); \
								)() \
							} \
						} \
						CRX_ENDFOR \
	\
						free(pThis->gPrivate_keyNodes); \
						pThis->gPrivate_keyNodes = tKeyNodes; \
					} \
	\
					CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
					( \
						if(tKeyNodes != NULL) \
						{ \
							pELEMENT_TYPE * tElements; \
	\
							CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, \
									pFUNC_ELEMENT_MOVE_DESTRUCTOR)) \
							( \
								tElements = (pELEMENT_TYPE*)(malloc( \
										vNumberOfBuckets * sizeof(pELEMENT_TYPE))); \
	\
								if(tElements != NULL) \
								{ \
									CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
									( \
										CRX_FOR(pSIZE_T tI = 0, \
												tI < pThis->gPrivate_numberOfBuckets, tI++) \
										{ \
											if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY( \
													pThis->gPrivate_bucketData, tI) == 0) \
											{ \
												pFUNC_ELEMENT_MOVE_CONSTRUCTOR(tElements + tI, \
														pThis->gPrivate_elements + tI); \
	\
												CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
												pFUNC_ELEMENT_MOVE_DESTRUCTOR( \
														pThis->gPrivate_elements + tI);, ) \
											} \
										} \
										CRX_ENDFOR \
									) \
									( \
										memcpy(tElements, pThis->gPrivate_elements, \
												sizeof(pELEMENT_TYPE) * \
												pThis->gPrivate_numberOfBuckets); \
	\
										CRX_FOR(pSIZE_T tI = 0, \
												tI < pThis->gPrivate_numberOfBuckets, tI++) \
										{ \
											if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY( \
													pThis->gPrivate_bucketData, tI) == 0) \
											{ \
												pFUNC_ELEMENT_MOVE_DESTRUCTOR( \
														pThis->gPrivate_elements + tI); \
											} \
										} \
										CRX_ENDFOR \
									) \
	\
									free(pThis->gPrivate_elements); \
									pThis->gPrivate_elements = tElements; \
								} \
							) \
							( \
								tElements = (pELEMENT_TYPE*)realloc((void *)pThis->gPrivate_elements, \
										vNumberOfBuckets * sizeof(pELEMENT_TYPE)); \
	\
								if(tElements != NULL) \
									{pThis->gPrivate_elements = tElements;} \
							) \
						} \
					)() \
				} \
	\
				free(pThis->gPrivate_bucketData); /* free the working space */ \
				pThis->gPrivate_bucketData = vBucketData; \
				pThis->gPrivate_numberOfBuckets = vNumberOfBuckets; \
				pThis->gPrivate_numberOfBucketsEverUsed = pThis->gPrivate_size; \
				pThis->gPrivate_upperBoundOfNumberOfBucketsEverUsed = \
						(pSIZE_T)(pThis->gPrivate_numberOfBuckets * 0.77 + 0.5); \
				pThis->gPrivate_seed = tSeed; \
			} \
	\
			return true; \
		} \
		else \
			{return false;} \
		CRX_SCOPE_END \
	} \
	\
	PRIVATE bool pMEMBER_FUNCTIONS_PREFIX ## private_setCapacity2(pHASH_TABLE_TYPE_NAME * pThis, \
			pSIZE_T pNumberOfBuckets) \
	{ /* This function uses 0.25*gPrivate_numberOfBuckets bytes of working space instead of [sizeof(key_t+val_t)+.25]*gPrivate_numberOfBuckets. */ \
		CRX_SCOPE_META \
		if(pNumberOfBuckets > ((pSIZE_T_MAX >> 1) + 1)) \
			{return false;} \
	\
		CRX_SCOPE \
		uint32_t * vBucketData = NULL; \
		pSIZE_T vNumberOfBuckets = CRX__C__OrderedHashTable__ROUND_UP_TO_POWER_OF_TWO( \
				pNumberOfBuckets); \
		bool vIsRehashingRequired = true; \
		pHASH_TABLE_TYPE_NAME ## _Private_KeyNode * vKeyNodes = NULL; \
		pELEMENT_TYPE * vElements = NULL; \
	\
		{ \
			if(vNumberOfBuckets < 4) \
				{vNumberOfBuckets = 4;} \
	\
			if(pThis->gPrivate_size >= (pSIZE_T)(vNumberOfBuckets * 0.77 + 0.5)) \
				{vIsRehashingRequired = false;}	/* requested gPrivate_size is too small */ \
			else \
			{ /* hash table gPrivate_size to be changed (shrink or expand); rehash */ \
				vBucketData = (uint32_t *)(malloc( \
						CRX__C__OrderedHashTable__GET_SIZE_OF_BUCKET_DATA(vNumberOfBuckets) * \
						sizeof(uint32_t)));	\
	\
				if(vBucketData != NULL) \
				{ \
					memset(vBucketData, 0xaa, \
							CRX__C__OrderedHashTable__GET_SIZE_OF_BUCKET_DATA(vNumberOfBuckets) * \
							sizeof(uint32_t)); \
	\
					if(pThis->gPrivate_numberOfBuckets != vNumberOfBuckets) \
					{	/* expand OR SHRINK*/ \
						vKeyNodes = (pHASH_TABLE_TYPE_NAME ## _Private_KeyNode *)( \
								malloc(vNumberOfBuckets * \
								sizeof(pHASH_TABLE_TYPE_NAME ## _Private_KeyNode))); \
	\
						if(vKeyNodes != NULL) \
						{ \
							CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
							( \
								vElements = (pELEMENT_TYPE*)(malloc( \
										vNumberOfBuckets * sizeof(pELEMENT_TYPE))); \
	\
								if(vElements == NULL) \
								{ \
									free(vKeyNodes); \
									vKeyNodes = NULL; \
									free(vBucketData); \
									vBucketData = NULL; \
								} \
							)() \
						} \
						else \
						{ \
							free(vBucketData); \
							vBucketData = NULL; \
						} \
					} /* otherwise shrink */ \
				} \
			} \
		} \
		if(vBucketData != NULL) \
		{ \
			if(vIsRehashingRequired) \
			{ /* rehashing is needed */ \
				size_t tSeed = 0; \
				pSIZE_T tNewMask = vNumberOfBuckets - 1; \
	\
				CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
				( \
					tSeed = pMEMBER_FUNCTIONS_PREFIX ## prepareSeedForHash(vKeyNodes, \
							vElements); \
				) \
				( \
					tSeed = pMEMBER_FUNCTIONS_PREFIX ## prepareSeedForHash(pThis, \
							vKeyNodes); \
				) \
	\
				CRX_FOR(pSIZE_T tI = 0, tI != pThis->gPrivate_numberOfBuckets, ++tI) \
				{ \
					if(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, tI) != 0) \
						{continue;} \
	\
					pSIZE_T tCurrentIndex = tI; \
	\
					/*ENSURING THAN GIVEN AN INDEX x, (pThis->gPrivate_bucketData + x) AND \
							(vBucketData + x) ARE NOT BOTH OCCUPIED AT THE SAME TIME. THIS IS NOT \
							NEEDED WHEN USING POINTERS INSTEAD OF INDICES FOR nextIndex AND \
							previousIndex*/ \
					while(true) \
					{ \
						pSIZE_T tI2 = ((pSIZE_T)pFUNC_COMPUTE_HASH(tSeed, \
								&((pThis->gPrivate_keyNodes + tCurrentIndex)->gPrivate_key))) & \
								tNewMask; \
						pSIZE_T tStep = 0; \
	\
						while(!CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(vBucketData, tI2)) \
							{tI2 = (tI2 + (++tStep)) & tNewMask;} \
	\
						CRX__C__OrderedHashTable__MARK_BUCKET_EVER_FILLED(vBucketData, tI2); \
	\
						CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE(pSIZE_T_MAX, \
								pFUNC_KEY_MOVE_CONSTRUCTOR, pKEY_TYPE, \
								vKeyNodes + tI2, pThis->gPrivate_keyNodes + tCurrentIndex); \
	\
						CRXM__IFELSE2(pFUNC_KEY_MOVE_DESTRUCTOR, \
						pFUNC_KEY_MOVE_DESTRUCTOR( \
								&((pThis->gPrivate_keyNodes + tCurrentIndex)->gPrivate_key));, ) \
	\
						CRX__C__OrderedHashTable__MARK_BUCKET_CONTENT_DELETED( \
								pThis->gPrivate_bucketData, tCurrentIndex); \
	\
						(vKeyNodes + tI2)->gPrivate_index = tI2; \
	\
						if((vKeyNodes + tI2)->gPrivate_previousIndex != pSIZE_T_MAX) \
						{ \
							if(((vKeyNodes + tI2)->gPrivate_previousIndex >= \
											pThis->gPrivate_numberOfBuckets) || \
									(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY( \
											pThis->gPrivate_bucketData, \
											(vKeyNodes + tI2)->gPrivate_previousIndex) != 0)) \
							{ \
								(vKeyNodes + (vKeyNodes + tI2)->gPrivate_previousIndex)-> \
										gPrivate_nextIndex = tI2; \
							} \
							else \
							{ \
								(pThis->gPrivate_keyNodes + (vKeyNodes + tI2)-> gPrivate_previousIndex)-> \
										gPrivate_nextIndex = tI2; \
							} \
						} \
	\
						if((vKeyNodes + tI2)->gPrivate_nextIndex != pSIZE_T_MAX) \
						{ \
							if(((vKeyNodes + tI2)->gPrivate_nextIndex >= \
											pThis->gPrivate_numberOfBuckets) || \
									(CRX__C__OrderedHashTable__IS_BUCKET_EMPTY( \
											pThis->gPrivate_bucketData, \
											(vKeyNodes + tI2)->gPrivate_nextIndex) != 0)) \
							{ \
								(vKeyNodes + (vKeyNodes + tI2)->gPrivate_nextIndex)-> \
										gPrivate_previousIndex = tI2; \
							} \
							else \
							{ \
								(pThis->gPrivate_keyNodes + (vKeyNodes + tI2)->gPrivate_nextIndex)-> \
										gPrivate_previousIndex = tI2; \
							} \
						} \
	\
						CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
						( \
							CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
							( \
								pFUNC_ELEMENT_MOVE_CONSTRUCTOR(vElements + tI2, \
										pThis->gPrivate_elements + tCurrentIndex); \
							) \
							( \
								memcpy(vElements + tI2, pThis->gPrivate_elements + tCurrentIndex, \
										sizeof(pELEMENT_TYPE)); \
							) \
	\
							CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
							pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gPrivate_elements + \
									tCurrentIndex);, ) \
						)() \
	\
						if(pThis->gPrivate_rootKeyNode == (pThis->gPrivate_keyNodes + \
								tCurrentIndex)) \
							{pThis->gPrivate_rootKeyNode = vKeyNodes + tI2;} \
	\
						if(pThis->gPrivate_lastKeyNode == (pThis->gPrivate_keyNodes + \
								tCurrentIndex)) \
							{pThis->gPrivate_lastKeyNode = vKeyNodes + tI2;} \
	\
						if((tI2 < pThis->gPrivate_numberOfBuckets) && \
								CRX__C__OrderedHashTable__IS_BUCKET_EMPTY( \
								pThis->gPrivate_bucketData, tI2) == 0) \
							{tCurrentIndex = tI2;} \
						else \
							{break;} \
					} \
				} \
				CRX_ENDFOR \
	\
				pThis->gPrivate_numberOfBuckets = vNumberOfBuckets; \
				pThis->gPrivate_numberOfBucketsEverUsed = pThis->gPrivate_size; \
				pThis->gPrivate_upperBoundOfNumberOfBucketsEverUsed = \
						(pSIZE_T)(pThis->gPrivate_numberOfBuckets * 0.77 + 0.5); \
				pThis->gPrivate_seed = tSeed; \
	\
				free(pThis->gPrivate_bucketData); \
				pThis->gPrivate_bucketData = vBucketData; \
				vBucketData = NULL; \
	\
				free(pThis->gPrivate_keyNodes); \
				pThis->gPrivate_keyNodes = vKeyNodes; \
				vKeyNodes = NULL; \
	\
				CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
				( \
					free(pThis->gPrivate_elements); \
					pThis->gPrivate_elements = vElements; \
					vElements = NULL; \
				)() \
			} \
	\
			return true; \
		} \
		else \
			{return false;} \
		CRX_SCOPE_END \
	} \
	\
	PRIVATE pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## private_tryMoveKeyAndPrepareBucketFor( \
			pHASH_TABLE_TYPE_NAME * pThis, pKEY_TYPE * pKey, int * pReturn) \
	{ \
		pSIZE_T vReturn = 0; \
	\
		if(pThis->gPrivate_numberOfBucketsEverUsed >= pThis->gPrivate_upperBoundOfNumberOfBucketsEverUsed) \
		{ /* update the hash table */ \
			if(pThis->gPrivate_numberOfBuckets > (pThis->gPrivate_size << 1)) \
			{ \
				if(!pMEMBER_FUNCTIONS_PREFIX ## private_setCapacity2(pThis, \
						pThis->gPrivate_numberOfBuckets - 1)) \
				{/* clear "deleted" elements */ \
					*pReturn = -1; \
	\
					vReturn = pThis->gPrivate_numberOfBuckets; \
				} \
			} \
			else if(!pMEMBER_FUNCTIONS_PREFIX ## private_setCapacity2(pThis, \
					pThis->gPrivate_numberOfBuckets + 1)) \
			{ /* expand the hash table */ \
				*pReturn = -1; \
	\
				vReturn = pThis->gPrivate_numberOfBuckets; \
			} \
		} /* TODO: to implement automatically shrinking; private_setCapacity() already support shrinking */ \
	\
		if((vReturn != pThis->gPrivate_numberOfBuckets) || \
				(pThis->gPrivate_numberOfBucketsEverUsed < pThis->gPrivate_numberOfBuckets))\
		{ \
			{ \
				pSIZE_T tMask = pThis->gPrivate_numberOfBuckets - 1; \
				pSIZE_T tIndex = ((pSIZE_T)pFUNC_COMPUTE_HASH(pThis->gPrivate_seed, pKey)) & tMask; \
	\
				if(CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(pThis->gPrivate_bucketData, tIndex)) \
					{vReturn = tIndex;} /* for speed up */ \
				else \
				{ \
					pSIZE_T site = pThis->gPrivate_numberOfBuckets; \
					pSIZE_T tLastIndex = tIndex; \
					pSIZE_T tStep = 0; \
	\
					vReturn = pThis->gPrivate_numberOfBuckets; \
	\
					while(!CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(pThis->gPrivate_bucketData, tIndex) && \
							(CRX__C__OrderedHashTable__IS_BUCKET_CONTENT_DELETED(pThis->gPrivate_bucketData, tIndex) || \
							!pFUNC_ARE_KEYS_EQUAL(&((pThis->gPrivate_keyNodes + tIndex)->gPrivate_key), pKey))) \
					{ \
						if(CRX__C__OrderedHashTable__IS_BUCKET_CONTENT_DELETED(pThis->gPrivate_bucketData, tIndex)) \
							{site = tIndex;} \
	\
						tIndex = (tIndex + (++tStep)) & tMask; \
	\
						if(tIndex == tLastIndex) \
						{ \
							vReturn = site; \
							break; \
						} \
					} \
					if(vReturn == pThis->gPrivate_numberOfBuckets) \
					{ \
						if(CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(pThis->gPrivate_bucketData, tIndex) && \
								site != pThis->gPrivate_numberOfBuckets) \
							{vReturn = site;} \
						else \
							{vReturn = tIndex;} \
					} \
				} \
			} \
	\
			if(CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(pThis->gPrivate_bucketData, vReturn)) \
			{ /* not present at all */ \
				CRXM__IFELSE(pFUNC_KEY_MOVE_CONSTRUCTOR) \
				( \
					pFUNC_KEY_MOVE_CONSTRUCTOR( \
							&((pThis->gPrivate_keyNodes + vReturn)->gPrivate_key), pKey); \
				) \
				( \
					memcpy(&((pThis->gPrivate_keyNodes + vReturn)->gPrivate_key), pKey, \
							sizeof(pKEY_TYPE)); \
				) \
	\
				CRX__C__OrderedHashTable__MARK_BUCKET_NOT_EMPTY(pThis->gPrivate_bucketData, vReturn); \
	\
				++(pThis->gPrivate_size); \
				++(pThis->gPrivate_numberOfBucketsEverUsed); \
	\
				if(pThis->gPrivate_rootKeyNode == NULL) \
				{ \
					pThis->gPrivate_rootKeyNode = (pThis->gPrivate_keyNodes + vReturn); \
					pThis->gPrivate_rootKeyNode->gPrivate_nextIndex = pSIZE_T_MAX; \
					pThis->gPrivate_rootKeyNode->gPrivate_previousIndex = pSIZE_T_MAX; \
				} \
				else \
				{ \
					(pThis->gPrivate_keyNodes + vReturn)->gPrivate_nextIndex = pSIZE_T_MAX; \
	\
					if(pThis->gPrivate_lastKeyNode != NULL) \
					{ \
						(pThis->gPrivate_keyNodes + vReturn)->gPrivate_previousIndex = \
								pThis->gPrivate_lastKeyNode->gPrivate_index; \
						pThis->gPrivate_lastKeyNode->gPrivate_nextIndex = vReturn; \
						pThis->gPrivate_lastKeyNode = (pThis->gPrivate_keyNodes + vReturn); \
					} \
					else \
					{ \
						(pThis->gPrivate_keyNodes + vReturn)->gPrivate_previousIndex = \
								pThis->gPrivate_rootKeyNode->gPrivate_index; \
						pThis->gPrivate_rootKeyNode->gPrivate_nextIndex = vReturn; \
						pThis->gPrivate_lastKeyNode = (pThis->gPrivate_keyNodes + vReturn); \
					} \
				} \
	\
				(pThis->gPrivate_keyNodes + vReturn)->gPrivate_index = vReturn; \
	\
				*pReturn = 1; \
			} \
			else if(CRX__C__OrderedHashTable__IS_BUCKET_CONTENT_DELETED(pThis->gPrivate_bucketData, vReturn)) \
			{ /* deleted */ \
				CRXM__IFELSE(pFUNC_KEY_MOVE_CONSTRUCTOR) \
				( \
					pFUNC_KEY_MOVE_CONSTRUCTOR( \
							&((pThis->gPrivate_keyNodes + vReturn)->gPrivate_key), pKey); \
				) \
				( \
					memcpy(&((pThis->gPrivate_keyNodes + vReturn)->gPrivate_key), pKey, \
							sizeof(pKEY_TYPE)); \
				) \
	\
				CRX__C__OrderedHashTable__MARK_BUCKET_NOT_EMPTY(pThis->gPrivate_bucketData, vReturn); \
	\
				++(pThis->gPrivate_size); \
	\
				if(pThis->gPrivate_rootKeyNode == NULL) \
				{ \
					pThis->gPrivate_rootKeyNode = (pThis->gPrivate_keyNodes + vReturn); \
					pThis->gPrivate_rootKeyNode->gPrivate_nextIndex = pSIZE_T_MAX; \
					pThis->gPrivate_rootKeyNode->gPrivate_previousIndex = pSIZE_T_MAX; \
				} \
				else \
				{ \
					(pThis->gPrivate_keyNodes + vReturn)->gPrivate_nextIndex = pSIZE_T_MAX; \
	\
					if(pThis->gPrivate_lastKeyNode != NULL) \
					{ \
						(pThis->gPrivate_keyNodes + vReturn)->gPrivate_previousIndex = \
								pThis->gPrivate_lastKeyNode->gPrivate_index; \
						pThis->gPrivate_lastKeyNode->gPrivate_nextIndex = vReturn; \
						pThis->gPrivate_lastKeyNode = (pThis->gPrivate_keyNodes + vReturn); \
					} \
					else \
					{ \
						(pThis->gPrivate_keyNodes + vReturn)->gPrivate_previousIndex = \
								pThis->gPrivate_rootKeyNode->gPrivate_index; \
						pThis->gPrivate_rootKeyNode->gPrivate_nextIndex = vReturn; \
						pThis->gPrivate_lastKeyNode = (pThis->gPrivate_keyNodes + vReturn); \
					} \
				} \
	\
				(pThis->gPrivate_keyNodes + vReturn)->gPrivate_index = vReturn; \
	\
				*pReturn = 2; \
			} \
			else \
				{*pReturn = 0;} /* Don't touch pThis->gPrivate_keyNodes[vReturn]->gPrivate_key if present and not deleted */ \
		} \
	\
		return vReturn; \
	} \
	\
	PRIVATE void pMEMBER_FUNCTIONS_PREFIX ## private_deleteElementAt(pHASH_TABLE_TYPE_NAME * pThis, \
			pSIZE_T pBucketIndex) \
	{																	\
		if((pBucketIndex != pThis->gPrivate_numberOfBuckets) && \
				!CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, pBucketIndex)) \
		{ \
			CRX__C__OrderedHashTable__MARK_BUCKET_CONTENT_DELETED(pThis->gPrivate_bucketData, pBucketIndex); \
	\
			CRXM__IFELSE2(pFUNC_KEY_DESTRUCTOR, \
			pFUNC_KEY_DESTRUCTOR(&((pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_key));, ) \
			CRXM__IFELSE2(CRXM__AND(CRXM__NOT(pIS_KEYS_ONLY), pFUNC_ELEMENT_DESTRUCTOR), \
			pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements + pBucketIndex);, ); \
	\
			if((pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_previousIndex != pSIZE_T_MAX) \
			{ \
				(pThis->gPrivate_keyNodes + (pThis->gPrivate_keyNodes + pBucketIndex)-> \
						gPrivate_previousIndex)->gPrivate_nextIndex = \
						(pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_nextIndex; \
			} \
			else \
			{ \
				pThis->gPrivate_rootKeyNode = pThis->gPrivate_keyNodes + \
						(pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_nextIndex; \
			} \
	\
			if((pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_nextIndex != pSIZE_T_MAX) \
			{ \
				(pThis->gPrivate_keyNodes + (pThis->gPrivate_keyNodes + pBucketIndex)-> \
						gPrivate_nextIndex)->gPrivate_previousIndex = \
						(pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_previousIndex; \
			} \
			else \
			{ \
				pThis->gPrivate_lastKeyNode = pThis->gPrivate_keyNodes + \
						(pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_previousIndex; \
			} \
	\
			(pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_nextIndex = pSIZE_T_MAX; \
			(pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_previousIndex = pSIZE_T_MAX; \
			(pThis->gPrivate_keyNodes + pBucketIndex)->gPrivate_index = pSIZE_T_MAX; \
	\
			--(pThis->gPrivate_size); \
		} \
	} \
	\
	PUBLIC pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## getSize(pHASH_TABLE_TYPE_NAME const * pThis) \
		{return pThis->gPrivate_size;} \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndElementAndSet( \
			pHASH_TABLE_TYPE_NAME * pThis, pKEY_TYPE * pKey, pELEMENT_TYPE * pElement) \
	{ \
		int vReturnedCode = 0; \
		pSIZE_T vBucketNumber = \
				pMEMBER_FUNCTIONS_PREFIX ## private_tryMoveKeyAndPrepareBucketFor(pThis, \
				pKey, &vReturnedCode); \
	\
		if(vBucketNumber != pThis->gPrivate_numberOfBuckets) \
		{ \
			if(vReturnedCode > 0) \
				{} \
			else \
			{ \
				CRXM__IFELSE2(pFUNC_KEY_DESTRUCTOR, \
				pFUNC_KEY_DESTRUCTOR(&((pThis->gPrivate_keyNodes + vBucketNumber)->gPrivate_key));, ) \
	\
				CRXM__IFELSE(pFUNC_KEY_MOVE_CONSTRUCTOR) \
				( \
					pFUNC_KEY_MOVE_CONSTRUCTOR( \
							&((pThis->gPrivate_keyNodes + vBucketNumber)->gPrivate_key), pKey); \
				) \
				( \
					memcpy(&((pThis->gPrivate_keyNodes + vBucketNumber)->gPrivate_key), pKey, \
							sizeof(pKEY_TYPE)); \
				) \
	\
				CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
				pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements + vBucketNumber);, ) \
			} \
	\
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + vBucketNumber, pElement); \
			) \
			( \
				memcpy(pThis->gPrivate_elements + vBucketNumber, pElement, sizeof(pELEMENT_TYPE)); \
			) \
	\
			return true; \
		} \
		else \
			{return false;} \
	}, ) \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndSet( \
			pHASH_TABLE_TYPE_NAME * pThis, pKEY_TYPE * pKey, pELEMENT_TYPE * pElement), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndSet( \
			pHASH_TABLE_TYPE_NAME * pThis, pKEY_TYPE * pKey)) \
	{ \
		CRXM__IFELSE2(CRXM__AND(CRXM__NOT(pIS_KEYS_ONLY), \
				CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR)), \
		unsigned char * vElement = (unsigned char *) CRX__ALLOCA(sizeof(pELEMENT_TYPE));, ) \
		CRXM__IFELSE2(CRXM__AND(CRXM__NOT(pIS_KEYS_ONLY), \
				CRXM__AND(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
				CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR))), \
		bool vReturn;, )\
		CRXM__IFELSE2(pIS_KEYS_ONLY, \
		int vReturnedCode = 0;, ) \
		CRXM__IFELSE2(pIS_KEYS_ONLY, \
		pSIZE_T vBucketNumber = \
				pMEMBER_FUNCTIONS_PREFIX ## private_tryMoveKeyAndPrepareBucketFor(pThis, \
				pKey, &vReturnedCode);, ) \
	\
		CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(((pELEMENT_TYPE *)vElement), pElement); \
	\
				CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
						vReturn = , return) pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndElementAndSet( \
						pThis, pKey, ((pELEMENT_TYPE *)vElement)); \
			) \
			( \
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
				( \
					memcpy(vElement, pElement, sizeof(pELEMENT_TYPE)); \
	\
					CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
						vReturn = , return) pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndElementAndSet(pThis, pKey, \
						((pELEMENT_TYPE *)vElement)); \
				) \
				( \
					return pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndElementAndSet(pThis, pKey, \
							((pELEMENT_TYPE *)pElement)); \
				) \
			) \
	\
			CRXM__IFELSE(CRXM__AND(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
					CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR))) \
			( \
				if(vReturn) \
					{pFUNC_ELEMENT_MOVE_DESTRUCTOR(((pELEMENT_TYPE *)vElement));} \
	\
				return vReturn; \
			)() \
		) \
		( \
			if(vBucketNumber != pThis->gPrivate_numberOfBuckets) \
			{ \
				if(vReturnedCode > 0) \
					{} \
				else \
				{ \
					CRXM__IFELSE2(pFUNC_KEY_DESTRUCTOR, \
					pFUNC_KEY_DESTRUCTOR(&((pThis->gPrivate_keyNodes + \
							vBucketNumber)->gPrivate_key));, ) \
	\
					CRXM__IFELSE(pFUNC_KEY_MOVE_CONSTRUCTOR) \
					( \
						pFUNC_KEY_MOVE_CONSTRUCTOR(&((pThis->gPrivate_keyNodes + \
								vBucketNumber)->gPrivate_key), pKey); \
					) \
					( \
						memcpy(&((pThis->gPrivate_keyNodes + vBucketNumber)->gPrivate_key), \
								pKey, sizeof(pKEY_TYPE)); \
					) \
				} \
	\
				return true; \
			} \
			else \
				{return false;} \
		) \
	} \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## tryMoveElementAndSet( \
			pHASH_TABLE_TYPE_NAME * pThis, pKEY_TYPE * pKey, pELEMENT_TYPE * pElement) \
	{ \
		CRXM__IFELSE2(CRXM__OR(pFUNC_KEY_COPY_CONSTRUCTOR, pFUNC_KEY_MOVE_CONSTRUCTOR), \
		unsigned char * vKey = (unsigned char *) CRX__ALLOCA(sizeof(pKEY_TYPE));, ) \
		CRXM__IFELSE2(CRXM__AND(pFUNC_KEY_MOVE_DESTRUCTOR, \
				CRXM__OR(pFUNC_KEY_COPY_CONSTRUCTOR, pFUNC_KEY_MOVE_CONSTRUCTOR)), \
		bool vReturn;, )\
	\
		CRXM__IFELSE(pFUNC_KEY_COPY_CONSTRUCTOR) \
		( \
			pFUNC_KEY_COPY_CONSTRUCTOR(((pKEY_TYPE *)vKey), pKey); \
	\
			CRXM__IFELSE2(pFUNC_KEY_MOVE_DESTRUCTOR, \
					vReturn = , return) pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndElementAndSet(\
					pThis, ((pKEY_TYPE *)vKey), pElement); \
		) \
		( \
			CRXM__IFELSE(pFUNC_KEY_MOVE_CONSTRUCTOR) \
			( \
				memcpy(vKey, pKey, sizeof(pKEY_TYPE)); \
	\
				CRXM__IFELSE2(pFUNC_KEY_MOVE_DESTRUCTOR, \
						vReturn = , return) pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndElementAndSet( \
						pThis, ((pKEY_TYPE *)vKey), pElement); \
			) \
			( \
				return pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndElementAndSet( \
						pThis, pKey, pElement); \
			) \
		) \
	\
		CRXM__IFELSE(CRXM__AND(pFUNC_KEY_MOVE_DESTRUCTOR, \
				CRXM__OR(pFUNC_KEY_COPY_CONSTRUCTOR, pFUNC_KEY_MOVE_CONSTRUCTOR))) \
		( \
			if(vReturn) \
				{pFUNC_KEY_MOVE_DESTRUCTOR(((pKEY_TYPE *)vKey));} \
	\
			return vReturn; \
		)() \
	}, ) \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## set( \
			pHASH_TABLE_TYPE_NAME * pThis, pKEY_TYPE * pKey, pELEMENT_TYPE * pElement), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## set( \
			pHASH_TABLE_TYPE_NAME * pThis, pKEY_TYPE * pKey)) \
	{ \
		unsigned char * vKey = (unsigned char *) CRX__ALLOCA(sizeof(pKEY_TYPE)); \
		CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
		unsigned char * vElement = (unsigned char *) CRX__ALLOCA(sizeof(pELEMENT_TYPE));, ) \
		CRXM__IFELSE2(CRXM__OR(CRXM__OR(pFUNC_KEY_DESTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR), \
				CRXM__AND(CRXM__NOT(pIS_KEYS_ONLY), \
						CRXM__OR(pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR))), \
		bool vReturn;, )\
	\
		CRXM__IFELSE(pFUNC_KEY_COPY_CONSTRUCTOR) \
		( \
			pFUNC_KEY_COPY_CONSTRUCTOR(((pKEY_TYPE *)vKey), pKey); \
		) \
		( \
			memcpy(vKey, pKey, sizeof(pKEY_TYPE)); \
		) \
	\
		CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(((pELEMENT_TYPE *)vElement), pElement); \
			) \
			( \
				memcpy(vElement, pElement, sizeof(pELEMENT_TYPE)); \
			) \
		)() \
	\
		CRXM__IFELSE(CRXM__OR(CRXM__OR(pFUNC_KEY_DESTRUCTOR, pFUNC_KEY_MOVE_DESTRUCTOR), \
				CRXM__AND(CRXM__NOT(pIS_KEYS_ONLY), \
						CRXM__OR(pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR)))) \
		( \
			CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
			( \
				vReturn = pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndElementAndSet(pThis, \
						((pKEY_TYPE *)vKey), ((pELEMENT_TYPE *)vElement)); \
			) \
			( \
				vReturn = pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndSet(pThis, \
						((pKEY_TYPE *)vKey)); \
			) \
	\
			if(vReturn) \
			{ \
				CRXM__IFELSE2(pFUNC_KEY_MOVE_DESTRUCTOR, \
				pFUNC_KEY_MOVE_DESTRUCTOR(((pKEY_TYPE *)vKey));, ); \
				CRXM__IFELSE2(CRXM__AND(CRXM__NOT(pIS_KEYS_ONLY), \
						pFUNC_ELEMENT_MOVE_DESTRUCTOR), \
				pFUNC_ELEMENT_MOVE_DESTRUCTOR(((pELEMENT_TYPE *)vElement));, ); \
			} \
			else \
			{ \
				CRXM__IFELSE2(pFUNC_KEY_DESTRUCTOR, \
				pFUNC_KEY_DESTRUCTOR(((pKEY_TYPE *)vKey));, ); \
				CRXM__IFELSE2(CRXM__AND(CRXM__NOT(pIS_KEYS_ONLY), \
						pFUNC_ELEMENT_DESTRUCTOR), \
				pFUNC_ELEMENT_DESTRUCTOR(((pELEMENT_TYPE *)vElement));, ); \
			} \
	\
			return vReturn; \
		) \
		( \
			CRXM__IFELSE(CRXM__NOT(pIS_KEYS_ONLY)) \
			( \
				return pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndElementAndSet(pThis, \
						((pKEY_TYPE *)vKey), ((pELEMENT_TYPE *)vElement)); \
			) \
			( \
				return pMEMBER_FUNCTIONS_PREFIX ## tryMoveKeyAndSet(pThis, \
						((pKEY_TYPE *)vKey)); \
			) \
		) \
	} \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
	PUBLIC pELEMENT_TYPE * pMEMBER_FUNCTIONS_PREFIX ## get(pHASH_TABLE_TYPE_NAME * pThis, \
			pKEY_TYPE const * pKey) \
	{ \
		pSIZE_T vBucketIndex = pMEMBER_FUNCTIONS_PREFIX ## private_get(pThis, pKey); \
	\
		assert(vBucketIndex != pThis->gPrivate_numberOfBuckets); \
	\
		return (pThis->gPrivate_elements + vBucketIndex); \
	}, ) \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_KEYS_ONLY), \
	PUBLIC pELEMENT_TYPE const * pMEMBER_FUNCTIONS_PREFIX ## constantGet( \
			pHASH_TABLE_TYPE_NAME const * pThis, pKEY_TYPE const * pKey) \
		{return pMEMBER_FUNCTIONS_PREFIX ## get(((pHASH_TABLE_TYPE_NAME *)pThis), pKey);}, ) \
	\
	CRXM__IFELSE2(CRXM__AND(CRXM__NOT(pIS_KEYS_ONLY), pIS_ELEMENT_COPYABLE), \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## copyGetTo(pHASH_TABLE_TYPE_NAME const * pThis, \
			pELEMENT_TYPE * pReturn, pKEY_TYPE const * pKey), \
	PUBLIC pELEMENT_TYPE pMEMBER_FUNCTIONS_PREFIX ## copyGet(pHASH_TABLE_TYPE_NAME const * pThis, \
			pKEY_TYPE const * pKey)) \
	{ \
		pSIZE_T vBucketIndex = pMEMBER_FUNCTIONS_PREFIX ## private_get(pThis, pKey); \
	\
		assert(vBucketIndex != pThis->gPrivate_numberOfBuckets); \
	\
		CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR)) \
		( \
			CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
			pFUNC_ELEMENT_DESTRUCTOR(pReturn);, ) \
	\
			CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(pReturn, pThis->gPrivate_elements + vBucketIndex); \
			) \
			( \
				memcpy(pReturn, pThis->gPrivate_elements + vBucketIndex, \
						sizeof(pHASH_TABLE_TYPE_NAME)); \
			) \
		) \
		( \
			return *(pThis->gPrivate_elements + vBucketIndex); \
		) \
	}, ) \
	\
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## hasKey(pHASH_TABLE_TYPE_NAME const * pThis, \
			pKEY_TYPE const * pKey) \
	{ \
		return (pMEMBER_FUNCTIONS_PREFIX ## private_get(pThis, pKey) != \
				pThis->gPrivate_numberOfBuckets); \
	} \
	\
	PUBLIC pKEY_TYPE const * pMEMBER_FUNCTIONS_PREFIX ## getKeyFromIndex( \
			pHASH_TABLE_TYPE_NAME const * pThis, size_t pIndex) \
	{ \
		assert(pIndex <= pSIZE_T_MAX); \
	\
		if(CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, ((pSIZE_T)pIndex))) \
			{return NULL;} \
	\
		return &((pThis->gPrivate_keyNodes + pIndex)->gPrivate_key); \
	} \
	PUBLIC pELEMENT_TYPE const * pMEMBER_FUNCTIONS_PREFIX ## getElementFromIndex( \
			pHASH_TABLE_TYPE_NAME const * pThis, size_t pIndex) \
	{ \
		assert(pIndex <= pSIZE_T_MAX); \
	\
		if(CRX__C__HashTable__IS_BUCKET_EMPTY(pThis->gPrivate_bucketData, ((pSIZE_T)pIndex))) \
			{return NULL;} \
	\
		return (pThis->gPrivate_elements + pIndex); \
	} \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## remove(pHASH_TABLE_TYPE_NAME * pThis, \
			pKEY_TYPE const * pKey) \
	{ \
		pMEMBER_FUNCTIONS_PREFIX ## private_deleteElementAt(pThis, \
				pMEMBER_FUNCTIONS_PREFIX ## private_get(pThis, pKey)); \
	} \
	\
	CRX__LIB__PUBLIC_INLINE_C_FUNCTION() pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## getStartIndex( \
			pHASH_TABLE_TYPE_NAME const * pThis) \
	{ \
		if((pThis->gPrivate_keyNodes == NULL) || (pThis->gPrivate_rootKeyNode == NULL))\
			{return pThis->gPrivate_numberOfBuckets;} \
	\
		return pThis->gPrivate_rootKeyNode->gPrivate_index; \
	} \
	CRX__LIB__PUBLIC_INLINE_C_FUNCTION() pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## getLastIndex( \
			pHASH_TABLE_TYPE_NAME const * pThis) \
	{ \
		if((pThis->gPrivate_keyNodes == NULL) || (pThis->gPrivate_lastKeyNode == NULL))\
			{return pThis->gPrivate_numberOfBuckets;} \
	\
		return pThis->gPrivate_lastKeyNode->gPrivate_index; \
	} \
	CRX__LIB__PUBLIC_INLINE_C_FUNCTION() pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## getEndIndex( \
			pHASH_TABLE_TYPE_NAME const * pThis) \
		{return pThis->gPrivate_numberOfBuckets;} \
	CRX__LIB__PUBLIC_INLINE_C_FUNCTION() pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## getNextIndex( \
			pHASH_TABLE_TYPE_NAME const * pThis, size_t pIndex) \
	{ \
		if((pThis->gPrivate_keyNodes == NULL) || (pIndex >= pThis->gPrivate_numberOfBuckets) || \
				((pThis->gPrivate_keyNodes + pIndex)->gPrivate_nextIndex == pSIZE_T_MAX)) \
			{return pThis->gPrivate_numberOfBuckets;} \
	\
		return (pThis->gPrivate_keyNodes + (pThis->gPrivate_keyNodes + pIndex)-> \
				gPrivate_nextIndex)->gPrivate_index; \
	} \
	CRX__LIB__PUBLIC_INLINE_C_FUNCTION() pSIZE_T pMEMBER_FUNCTIONS_PREFIX ## getPreviousIndex( \
			pHASH_TABLE_TYPE_NAME const * pThis, size_t pIndex) \
	{ \
		if((pThis->gPrivate_keyNodes == NULL) || (pIndex >= pThis->gPrivate_numberOfBuckets) || \
				((pThis->gPrivate_keyNodes + pIndex)->gPrivate_previousIndex == pSIZE_T_MAX)) \
			{return pThis->gPrivate_numberOfBuckets;} \
	\
		return (pThis->gPrivate_keyNodes + (pThis->gPrivate_keyNodes + pIndex)-> \
				gPrivate_previousIndex)->gPrivate_index; \
	} \
	\
	PRIVATE size_t pMEMBER_FUNCTIONS_PREFIX ## prepareSeedForHash( \
			void const * pPointer, void const * pPointer2) \
	{ \
		Crx_C_Random_Isaac vIsaac; \
		uint32_t vPointerValue = ((uint32_t)(((uintmax_t)pPointer) | \
				(((uintmax_t)pPointer) >> 3) & 0x03)); \
		uint32_t vPointer2Value = ((uint32_t)(((uintmax_t)pPointer2) |  \
				(((uintmax_t)pPointer2) >> 3) & 0x03)); \
	\
		crx_c_random_isaac_construct2(&vIsaac, vPointerValue, vPointer2Value, 0, 0, 0, 0, 0, 0); \
	\
		CRXM__IFELSE(CRX__C__ORDERED_HASH_TABLE__IS_TO_GENERATE_UINT64_RANDOM) \
		( \
			return ((((size_t)crx_c_random_isaac_getRandomUnsignedInt32(&vIsaac)) << 32) && \
					crx_c_random_isaac_getRandomUnsignedInt32(&vIsaac)); \
		) \
		( \
				return crx_c_random_isaac_getRandomUnsignedInt32(&vIsaac); \
		) \
	}
//#END_DEFINE

#define CRX__C__OrderedHashTable__GET_SIZE_OF_BUCKET_DATA(pNumberOfBuckets) \
		((pNumberOfBuckets) < 16 ? 1 : (pNumberOfBuckets)>>4)

#if(!defined(CRX__BOOST_NO_INT64_T))
	#define CRX__C__OrderedHashTable__ROUND_UP_TO_POWER_OF_TWO(pUINT64) \
			__CRX__C__OrderedHashTable__ROUND_UP_TO_POWER_OF_TWO(pUINT64)
	#define __CRX__C__OrderedHashTable__ROUND_UP_TO_POWER_OF_TWO(pUINT64) \
			(--(pUINT64), (pUINT64)|=(pUINT64)>>1, (pUINT64)|=(pUINT64)>>2, \
			(pUINT64)|=(pUINT64)>>4, (pUINT64)|=(pUINT64)>>8, \
			(pUINT64)|=(pUINT64)>>16, (pUINT64)|=((uint64_t)pUINT64)>>32, ++(pUINT64))
#else
	#define CRX__C__OrderedHashTable__ROUND_UP_TO_POWER_OF_TWO(pUINT32) \
			__CRX__C__OrderedHashTable__ROUND_UP_TO_POWER_OF_TWO(pUINT32)
	#define __CRX__C__OrderedHashTable__ROUND_UP_TO_POWER_OF_TWO(pUINT32) \
			(--(pUINT32), (pUINT32)|=(pUINT32)>>1, (pUINT32)|=(pUINT32)>>2, \
			(pUINT32)|=(pUINT32)>>4, (pUINT32)|=(pUINT32)>>8, \
			(pUINT32)|=(pUINT32)>>16, ++(pUINT32))
#endif

#define CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE(pSIZE_T_MAX, \
				pFUNC_KEY_MOVE_CONSTRUCTOR, pKEY_TYPE, pINTERNAL_KEY1, pINTERNAL_KEY2) \
		(pINTERNAL_KEY1)->gPrivate_nextIndex = (pINTERNAL_KEY2)->gPrivate_nextIndex; \
		(pINTERNAL_KEY1)->gPrivate_previousIndex = (pINTERNAL_KEY2)->gPrivate_previousIndex; \
		\
		(pINTERNAL_KEY1)->gPrivate_index = (pINTERNAL_KEY2)->gPrivate_index; \
		\
		CRXM__IFELSE(pFUNC_KEY_MOVE_CONSTRUCTOR) \
		( \
			pFUNC_KEY_MOVE_CONSTRUCTOR(&((pINTERNAL_KEY1)->gPrivate_key), \
					&((pINTERNAL_KEY2)->gPrivate_key)); \
		) \
		( \
			memcpy(&((pINTERNAL_KEY1)->gPrivate_key), \
					&((pINTERNAL_KEY2)->gPrivate_key), sizeof(pKEY_TYPE)); \
		) \
		(pINTERNAL_KEY2)->gPrivate_nextIndex = pSIZE_T_MAX; \
		(pINTERNAL_KEY2)->gPrivate_previousIndex = pSIZE_T_MAX;

/*FOR GENERIC*/
#define CRX__C__OrderedHashTable__DO_KEY_NODE_MOVE2(pTYPE_BLUE_PRINT__KEY, \
				pINTERNAL_KEY1, pINTERNAL_KEY2, pKEY1, pKEY2) \
		(pINTERNAL_KEY1)->gPrivate_nextIndex = (pINTERNAL_KEY2)->gPrivate_nextIndex; \
		(pINTERNAL_KEY1)->gPrivate_previousIndex = (pINTERNAL_KEY2)->gPrivate_previousIndex; \
		\
		(pINTERNAL_KEY1)->gPrivate_index = (pINTERNAL_KEY2)->gPrivate_index; \
		\
		if(pTYPE_BLUE_PRINT__KEY->gFUNC__MOVE_CONSTRUCT != NULL) \
			{pTYPE_BLUE_PRINT__KEY->gFUNC__MOVE_CONSTRUCT((pKEY1), (pKEY2));} \
		else \
			{memcpy((pKEY1), (pKEY2), pTYPE_BLUE_PRINT__KEY->gBYTE_SIZE);} \
		\
		(pINTERNAL_KEY2)->gPrivate_nextIndex = ((size_t)-1); \
		(pINTERNAL_KEY2)->gPrivate_previousIndex = ((size_t)-1);



/*THE FOLLOWING IS USING TWO BITS FOR EACH BUCKET TO REPRESENT EMPTY AND DELETED.*/
#define CRX__C__OrderedHashTable__WAS_BUCKET_NEVER_FILLED(pBUCKET_DATA, pINDEX) ((pBUCKET_DATA[pINDEX>>4]>>((pINDEX&0xfU)<<1))&2)
#define CRX__C__OrderedHashTable__IS_BUCKET_CONTENT_DELETED(pBUCKET_DATA, pINDEX) ((pBUCKET_DATA[pINDEX>>4]>>((pINDEX&0xfU)<<1))&1)
#define CRX__C__OrderedHashTable__IS_BUCKET_EMPTY(pBUCKET_DATA, pINDEX) ((pBUCKET_DATA[pINDEX>>4]>>((pINDEX&0xfU)<<1))&3)
#define CRX__C__OrderedHashTable__MARK_BUCKET_EVER_FILLED(pBUCKET_DATA, pINDEX) (pBUCKET_DATA[pINDEX>>4]&=~(2ul<<((pINDEX&0xfU)<<1)))
#define CRX__C__OrderedHashTable__MARK_BUCKET_NOT_EMPTY(pBUCKET_DATA, pINDEX) (pBUCKET_DATA[pINDEX>>4]&=~(3ul<<((pINDEX&0xfU)<<1)))
#define CRX__C__OrderedHashTable__MARK_BUCKET_CONTENT_DELETED(pBUCKET_DATA, pINDEX) (pBUCKET_DATA[pINDEX>>4]|=1ul<<((pINDEX&0xfU)<<1))





typedef struct Crx_C_OrderedHashTable_Private_KeyNode
{
	size_t gPrivate_nextIndex;
	size_t gPrivate_previousIndex;
	size_t gPrivate_index;
} Crx_C_OrderedHashTable_Private_KeyNode;

typedef struct Crx_C_OrderedHashTable
{
	Crx_C_TypeBluePrint const * CRX_NOT_MINE gPrivate_typeBluePrint__key;
	Crx_C_TypeBluePrint const * CRX_NOT_MINE gPrivate_typeBluePrint__element;
	size_t gPrivate_numberOfBuckets;
	size_t gPrivate_size;
	size_t gPrivate_numberOfBucketsEverUsed;
	size_t gPrivate_upperBoundOfNumberOfBucketsEverUsed;
	size_t gPrivate_seed;
	uint32_t * gPrivate_bucketData;
	Crx_C_OrderedHashTable_Private_KeyNode * gPrivate_rootKeyNode;
	Crx_C_OrderedHashTable_Private_KeyNode * gPrivate_lastKeyNode;
	Crx_C_OrderedHashTable_Private_KeyNode * gPrivate_keyNodes;
	unsigned char * gPrivate_keys;
	unsigned char * gPrivate_elements;
	Crx_C_TypeBluePrint_AreObjectsEqual gPrivate_areKeysEqual;
	Crx_C_HashTable_GetHashForKey gPrivate_getHashForKey;
} Crx_C_OrderedHashTable;

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_construct(Crx_C_OrderedHashTable * pThis,
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__element,
		Crx_C_TypeBluePrint_AreObjectsEqual CRX_NOT_NULL pAreKeysEqual,
		Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_construct2(Crx_C_OrderedHashTable * pThis,
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
		Crx_C_TypeBluePrint_AreObjectsEqual CRX_NOT_NULL pAreKeysEqual,
		Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_copyConstruct(Crx_C_OrderedHashTable * pThis,
		Crx_C_OrderedHashTable const * CRX_NOT_NULL pHashTable);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_OrderedHashTable * crx_c_orderedHashTable_new(
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
		Crx_C_TypeBluePrint const *  pTypeBluePrint__element,
		Crx_C_TypeBluePrint_AreObjectsEqual CRX_NOT_NULL pAreKeysEqual,
		Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_OrderedHashTable * crx_c_orderedHashTable_new2(
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
		Crx_C_TypeBluePrint_AreObjectsEqual CRX_NOT_NULL pAreKeysEqual,
		Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_OrderedHashTable * crx_c_orderedHashTable_moveNew(
		Crx_C_OrderedHashTable * pHashTable);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_OrderedHashTable * crx_c_orderedHashTable_copyNew(
		Crx_C_OrderedHashTable const * pHashTable);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_destruct(Crx_C_OrderedHashTable * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_free(Crx_C_OrderedHashTable * pThis);

CRX__C__TYPE_BLUE_PRINT__GENERIC__DECLARE_GET_BLUE_PRINT(
		Crx_C_OrderedHashTable, crx_c_orderedHashTable_,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__FALSE, CRXM__FALSE);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_private_doInit(Crx_C_OrderedHashTable * pThis,
		Crx_C_TypeBluePrint const *  CRX_NOT_NULL pTypeBluePrint__key, 
		Crx_C_TypeBluePrint_AreObjectsEqual CRX_NOT_NULL pAreKeysEqual,
		Crx_C_HashTable_GetHashForKey CRX_NOT_NULL pGetHashForKey,
		Crx_C_TypeBluePrint const *  pTypeBluePrint__element);

CRX__LIB__PRIVATE_C_FUNCTION() size_t crx_c_orderedHashTable_private_get(Crx_C_OrderedHashTable const * pThis,
		void const * pKey);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_empty(Crx_C_OrderedHashTable * pThis);
CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_orderedHashTable_private_setCapacity(Crx_C_OrderedHashTable * pThis,
		size_t pNumberOfBuckets);
CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_orderedHashTable_private_setCapacity2(Crx_C_OrderedHashTable * pThis,
		size_t pNumberOfBuckets);
CRX__LIB__PRIVATE_C_FUNCTION() size_t crx_c_orderedHashTable_private_tryMoveKeyAndPrepareBucketFor(
		Crx_C_OrderedHashTable * pThis, void * pKey, int * pReturn);
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_orderedHashTable_private_deleteElementAt(Crx_C_OrderedHashTable * pThis,
		size_t pBucketIndex);

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_orderedHashTable_getSize(Crx_C_OrderedHashTable const * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_orderedHashTable_tryMoveKeyAndElementAndSet(
		Crx_C_OrderedHashTable * pThis, void * CRX_NOT_NULL pKey, void * CRX_NOT_NULL pElement);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_orderedHashTable_tryMoveKeyAndSet(
		Crx_C_OrderedHashTable * pThis, void * CRX_NOT_NULL pKey, void * pElement);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_orderedHashTable_tryMoveElementAndSet(
		Crx_C_OrderedHashTable * pThis, void * CRX_NOT_NULL pKey, void * CRX_NOT_NULL pElement);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_orderedHashTable_set(
		Crx_C_OrderedHashTable * pThis, void * CRX_NOT_NULL pKey, void * pElement);

CRX__LIB__PUBLIC_C_FUNCTION() void * crx_c_orderedHashTable_get(Crx_C_OrderedHashTable * pThis,
		void const * CRX_NOT_NULL pKey);
CRX__LIB__PUBLIC_C_FUNCTION() void const * crx_c_orderedHashTable_constantGet(
		Crx_C_OrderedHashTable const * pThis, void const * CRX_NOT_NULL pKey);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_copyGetTo(Crx_C_OrderedHashTable const * pThis, \
		void * CRX_NOT_NULL pReturn, void const * CRX_NOT_NULL pKey);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_orderedHashTable_hasKey(
		Crx_C_OrderedHashTable const * pThis, void const * pKey);
		
CRX__LIB__PUBLIC_C_FUNCTION() void const * crx_c_orderedHashTable_getKeyFromIndex(
		Crx_C_OrderedHashTable const * pThis, size_t pIndex);
CRX__LIB__PUBLIC_C_FUNCTION() void const * crx_c_orderedHashTable_getElementFromIndex(
		Crx_C_OrderedHashTable const * pThis, size_t pIndex);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_orderedHashTable_remove(Crx_C_OrderedHashTable * pThis,
		void const * CRX_NOT_NULL pKey);

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_orderedHashTable_getStartIndex(
		Crx_C_OrderedHashTable const * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_orderedHashTable_getLastIndex(
		Crx_C_OrderedHashTable const * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_orderedHashTable_getEndIndex(
		Crx_C_OrderedHashTable const * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_orderedHashTable_getNextIndex(
		Crx_C_OrderedHashTable const * pThis, size_t pIndex);
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_orderedHashTable_getPreviousIndex(
		Crx_C_OrderedHashTable const * pThis, size_t pIndex);

CRX__LIB__PRIVATE_C_FUNCTION() size_t crx_c_orderedHashTable_private_prepareSeedForHash(
		void const * pPointer, void const * pPointer2);

CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/OrderedHashTable.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif