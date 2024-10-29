#if(!defined(CRX__C__SORTED_QUEUE___h__))
#define CRX__C__SORTED_QUEUE___h__

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
#include "Crx/H/crx/c/random/Isaac.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()

#define CRX__C__QUEUE__MODE__QUEUE 0
#define CRX__C__QUEUE__MODE__STACK 1
#define CRX__C__QUEUE__MODE__BIDIRECTIONAL 2

#if(!CRX_ARE_VARIADIC_MACROS_EMULATED)
	#define CRX__C__SortedQueue__DECLARE(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__SortedQueue__DECLARE, __VA_ARGS__)
#else
	#define CRX__C__SortedQueue__DECLARE(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__SortedQueue__DECLARE, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20)
#endif

#define CRX__C__SortedQueue__DECLARE__9(pSORTED_QUEUE_TYPE_NAME, pSORTED_QUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pFUNC_COMPARATOR, pINITIAL_CAPACITY, pIS_TO_ENABLE_INITIAL_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__SortedQueue__DECLARE(pSORTED_QUEUE_TYPE_NAME, pSORTED_QUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pFUNC_COMPARATOR, pINITIAL_CAPACITY, pIS_TO_ENABLE_INITIAL_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__FALSE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())


#define CRX__C__SortedQueue__DECLARE__10(pSORTED_QUEUE_TYPE_NAME, pSORTED_QUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pFUNC_COMPARATOR, pINITIAL_CAPACITY, pIS_TO_ENABLE_INITIAL_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__SortedQueue__DECLARE(pSORTED_QUEUE_TYPE_NAME, pSORTED_QUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pFUNC_COMPARATOR, pINITIAL_CAPACITY, pIS_TO_ENABLE_INITIAL_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__TRUE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())


#define _CRX__C__SortedQueue__DECLARE(pSORTED_QUEUE_TYPE_NAME, pMEMBER_FUNCTIONS_PREFIX, \
		pFUNC_COMPARATOR, pINITIAL_CAPACITY, pIS_TO_ENABLE_INITIAL_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pIS_ELEMENT_COPYABLE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		PUBLIC, PRIVATE) \
	\
	typedef struct pSORTED_QUEUE_TYPE_NAME \
	{ \
		size_t gPrivate_length; \
		size_t gPrivate_capacity; \
		bool gPrivate_isReversed; \
		pELEMENT_TYPE * gPrivate_elements; \
	} pSORTED_QUEUE_TYPE_NAME; \
	/*typedef struct pSORTED_QUEUE_TYPE_NAME ## _Iterator\
	{ \
		pSORTED_QUEUE_TYPE_NAME ## _Private_Node gPrivate_node; \
		uint8_t gPrivate_index; \
	} pSORTED_QUEUE_TYPE_NAME ## _Iterator; */ \
	\
	typedef char pSORTED_QUEUE_TYPE_NAME ##__ERROR__INVALID_INITIAL_CAPACITY[2 * !!( \
			(pINITIAL_CAPACITY == 0) || \
			((pINITIAL_CAPACITY & (pINITIAL_CAPACITY - 1)) == 0)) - 1]; \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## construct(pSORTED_QUEUE_TYPE_NAME * pThis, \
			bool pIsReversed, size_t pCapacity CRX_DEFAULT(0)); \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## copyConstruct(pSORTED_QUEUE_TYPE_NAME * pThis, \
			pSORTED_QUEUE_TYPE_NAME const * pSortedQueue); \
	PUBLIC pSORTED_QUEUE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## new(bool pIsReversed, \
			size_t pCapacity CRX_DEFAULT(0)); \
	PUBLIC pSORTED_QUEUE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## moveNew( \
			pSORTED_QUEUE_TYPE_NAME * pSortedQueue); \
	PUBLIC pSORTED_QUEUE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## copyNew( \
			pSORTED_QUEUE_TYPE_NAME const * pSortedQueue); \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## destruct(pSORTED_QUEUE_TYPE_NAME * pThis); \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## free(pSORTED_QUEUE_TYPE_NAME * pThis); \
	\
	CRX__C__TYPE_BLUE_PRINT__DECLARE_GET_BLUE_PRINT( \
			pSORTED_QUEUE_TYPE_NAME, pMEMBER_FUNCTIONS_PREFIX, \
			CRXM__TRUE, CRXM__TRUE, \
			pIS_ELEMENT_COPYABLE, CRXM__TRUE, \
			CRXM__FALSE, CRXM__FALSE); \
	\
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## ensureCapacity(pSORTED_QUEUE_TYPE_NAME * pThis, \
			size_t pCapacity); \
	\
	PUBLIC size_t pMEMBER_FUNCTIONS_PREFIX ## getLength(pSORTED_QUEUE_TYPE_NAME const * pThis); \
	PUBLIC size_t pMEMBER_FUNCTIONS_PREFIX ## getCapacity(pSORTED_QUEUE_TYPE_NAME const * pThis); \
	\
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## tryMoveAndPush(pSORTED_QUEUE_TYPE_NAME * pThis, \
			pELEMENT_TYPE * pElement); \
	CRXM__IFELSE2(pIS_ELEMENT_COPYABLE, \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## push(pSORTED_QUEUE_TYPE_NAME * pThis, \
			pELEMENT_TYPE * pElement);, ) \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## popFromFront(pSORTED_QUEUE_TYPE_NAME * pThis); \
	\
	PUBLIC pELEMENT_TYPE * pMEMBER_FUNCTIONS_PREFIX ## getFront(pSORTED_QUEUE_TYPE_NAME * pThis); \
	PUBLIC pELEMENT_TYPE const * pMEMBER_FUNCTIONS_PREFIX ## constantGetFront( \
			pSORTED_QUEUE_TYPE_NAME const * pThis); \
	CRXM__IFELSE2(pIS_ELEMENT_COPYABLE, \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## copyGetFrontTo(pSORTED_QUEUE_TYPE_NAME const * pThis, \
			pELEMENT_TYPE * pReturn);, \
	PUBLIC pELEMENT_TYPE pMEMBER_FUNCTIONS_PREFIX ## copyGetFront( \
			pSORTED_QUEUE_TYPE_NAME const * pThis);), ) \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## empty(pSORTED_QUEUE_TYPE_NAME * pThis); \
	\
	\
	
//#END_DEFINE

#if(!CRX_ARE_VARIADIC_MACROS_EMULATED)
	#define CRX__C__SortedQueue__DEFINE(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__SortedQueue__DEFINE, __VA_ARGS__)
#else
	#define CRX__C__SortedQueue__DEFINE(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__SortedQueue__DEFINE, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20)
#endif

#define CRX__C__SortedQueue__DEFINE__9(pSORTED_QUEUE_TYPE_NAME, pSORTED_QUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pFUNC_COMPARATOR, pINITIAL_CAPACITY, pIS_TO_ENABLE_INITIAL_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__SortedQueue__DEFINE(pSORTED_QUEUE_TYPE_NAME, pSORTED_QUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pFUNC_COMPARATOR, pINITIAL_CAPACITY, pIS_TO_ENABLE_INITIAL_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__FALSE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRXM__IFELSE2(pIS_TO_ENABLE_INITIAL_CAPACITY_FIELD, this->gPRIVATE__NODE_CAPACITY, \
		pINITIAL_CAPACITY), CRX__LIB__PUBLIC_C_FUNCTION(), \
		CRX__LIB__PRIVATE_C_FUNCTION())


#define CRX__C__SortedQueue__DEFINE__10(pSORTED_QUEUE_TYPE_NAME, pSORTED_QUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pFUNC_COMPARATOR, pINITIAL_CAPACITY, pIS_TO_ENABLE_INITIAL_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__SortedQueue__DEFINE(pSORTED_QUEUE_TYPE_NAME, pSORTED_QUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pFUNC_COMPARATOR, pINITIAL_CAPACITY, pIS_TO_ENABLE_INITIAL_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__TRUE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRXM__IFELSE2(pIS_TO_ENABLE_INITIAL_CAPACITY_FIELD, this->gPRIVATE__NODE_CAPACITY, \
		pINITIAL_CAPACITY), CRX__LIB__PUBLIC_C_FUNCTION(), \
		CRX__LIB__PRIVATE_C_8FUNCTION())
		
		
#define _CRX__C__SortedQueue__DEFINE(pSORTED_QUEUE_TYPE_NAME, pMEMBER_FUNCTIONS_PREFIX, \
		pFUNC_COMPARATOR, pINITIAL_CAPACITY, pIS_TO_ENABLE_INITIAL_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pIS_ELEMENT_COPYABLE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		pTHIS_NODE_CAPACITY, PUBLIC, PRIVATE) \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## construct(pSORTED_QUEUE_TYPE_NAME * pThis, \
			bool pIsReversed, size_t pCapacity CRX_DEFAULT(0)) \
	{ \
		CRX_SCOPE_META \
		assert((pCapacity == 0) || ((pCapacity & (pCapacity - 1)) == 0)); \
	\
		CRX_SCOPE \
		size_t vCapacity = ((pCapacity > 0) ? pCapacity : pINITIAL_CAPACITY); \
	\
		pThis->gPrivate_length = 0; \
		pThis->gPrivate_isReversed = pIsReversed; \
	\
		if(vCapacity > 0) \
		{ \
			pThis->gPrivate_elements = (pELEMENT_TYPE *)(malloc(vCapacity * sizeof(pELEMENT_TYPE))); \
	\
			if(pThis->gPrivate_elements != NULL) \
				{pThis->gPrivate_capacity = vCapacity;} \
			else \
				{pThis->gPrivate_capacity = 0;} \
		} \
		else \
		{ \
			pThis->gPrivate_elements = NULL; \
			pThis->gPrivate_capacity = 0; \
		} \
		CRX_SCOPE_END \
	} \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## copyConstruct(pSORTED_QUEUE_TYPE_NAME * pThis, \
			pSORTED_QUEUE_TYPE_NAME const * pSortedQueue) \
	{ \
		CRXM__IFELSE2(CRXM__NOT(pIS_ELEMENT_COPYABLE), abort();, \
	\
		pMEMBER_FUNCTIONS_PREFIX ## construct(pThis, pSortedQueue->gPrivate_isReversed, \
						pSortedQueue->gPrivate_capacity); \
	\
		if((pSortedQueue->gPrivate_length > 0) && \
				(pThis->gPrivate_capacity > pSortedQueue->gPrivate_length)) \
		{ \
			CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				CRX_FOR(size_t tI = 0, tI < pSortedQueue->gPrivate_length, tI++) \
				{ \
					pFUNC_ELEMENT_COPY_CONSTRUCTOR(pThis->gPrivate_elements + tI, \
							pSortedQueue->gPrivate_elements + tI); \
				} \
				CRX_ENDFOR \
			) \
			( \
				memcpy(pThis->gPrivate_elements, \
						pSortedQueue->gPrivate_elements, \
						pSortedQueue->gPrivate_length * sizeof(pELEMENT_TYPE)); \
			) \
	\
			pThis->gPrivate_length = pSortedQueue->gPrivate_length; \
		} \
	)} \
	\
	PUBLIC pSORTED_QUEUE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## new( \
			bool pIsReversed, size_t pCapacity CRX_DEFAULT(0)) \
	{ \
		pSORTED_QUEUE_TYPE_NAME * vReturn = (pSORTED_QUEUE_TYPE_NAME *)(calloc(1,\
				sizeof(pSORTED_QUEUE_TYPE_NAME))); \
	\
		if(vReturn != NULL) \
			{pMEMBER_FUNCTIONS_PREFIX ## construct(vReturn, pIsReversed, pCapacity);} \
	\
		return vReturn; \
	} \
	\
	PUBLIC pSORTED_QUEUE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## moveNew( \
			pSORTED_QUEUE_TYPE_NAME * pSortedQueue) \
	{ \
		pSORTED_QUEUE_TYPE_NAME * vReturn = (pSORTED_QUEUE_TYPE_NAME *)(calloc(1,\
				sizeof(pSORTED_QUEUE_TYPE_NAME))); \
	\
		if(vReturn != NULL) \
			{memcpy(vReturn, pSortedQueue, sizeof(pSORTED_QUEUE_TYPE_NAME));} \
	\
		return vReturn; \
	} \
	\
	PUBLIC pSORTED_QUEUE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## copyNew( \
			pSORTED_QUEUE_TYPE_NAME const * pSortedQueue) \
	{ \
		CRXM__IFELSE2(CRXM__NOT(pIS_ELEMENT_COPYABLE), abort();, \
	\
		pSORTED_QUEUE_TYPE_NAME * vReturn = (pSORTED_QUEUE_TYPE_NAME *)(calloc(1,\
				sizeof(pSORTED_QUEUE_TYPE_NAME))); \
	\
		if(vReturn != NULL) \
			{pMEMBER_FUNCTIONS_PREFIX ## copyConstruct(vReturn, pSortedQueue);} \
	\
		return vReturn; \
	)} \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## destruct(pSORTED_QUEUE_TYPE_NAME * pThis) \
	{ \
		if(pThis->gPrivate_elements == NULL) \
			{return;} \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_DESTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++) \
				{pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements + tI);} \
			CRX_ENDFOR \
		)() \
	\
		free(pThis->gPrivate_elements); \
		pThis->gPrivate_elements = NULL; \
	} \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## free(pSORTED_QUEUE_TYPE_NAME * pThis) \
		{free(pThis);} \
	\
	CRX__C__TYPE_BLUE_PRINT__DEFINE_GET_BLUE_PRINT( \
			pSORTED_QUEUE_TYPE_NAME, pMEMBER_FUNCTIONS_PREFIX, \
			CRXM__TRUE, CRXM__TRUE, \
			pIS_ELEMENT_COPYABLE, CRXM__TRUE, \
			CRXM__FALSE, CRXM__FALSE) \
	\
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## ensureCapacity(pSORTED_QUEUE_TYPE_NAME * pThis, \
			size_t pCapacity) \
	{ \
		CRX_SCOPE_META \
		if(pCapacity <= pThis->gPrivate_capacity) \
			{return true;} \
		else if(pCapacity > ((pSIZE_T_MAX >> 1) + 1)) \
			{return false;} \
	\
		CRX_SCOPE \
		size_t vCapacity = ((pThis->gPrivate_capacity == 0 ? 1 : pThis->gPrivate_capacity) << 1); \
	\
		while(vCapacity < pCapacity) \
			{vCapacity = (vCapacity << 1);} \
	\
		if(pThis->gPrivate_elements == NULL) \
		{ \
			pThis->gPrivate_elements = (pELEMENT_TYPE *)(malloc(vCapacity * \
					sizeof(pELEMENT_TYPE))); \
	\
			if(pThis->gPrivate_elements != NULL) \
			{ \
				pThis->gPrivate_capacity = vCapacity; \
	\
				return true; \
			} \
			else \
				{return false;} \
		} \
		else \
		{ \
			CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR)) \
			( \
				pELEMENT_TYPE * tElements = (pELEMENT_TYPE *)(malloc(vCapacity * \
						sizeof(pELEMENT_TYPE))); \
	\
				if(tElements != NULL) \
				{ \
					CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
					( \
						CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++) \
						{ \
							pFUNC_ELEMENT_MOVE_CONSTRUCTOR(tElements + tI, \
									pThis->gPrivate_elements + tI); \
						} \
						CRX_ENDFOR \
					) \
					( \
						memcpy(tElements, pThis->gPrivate_elements, \
								pThis->gPrivate_length * sizeof(pELEMENT_TYPE)); \
					) \
	\
					CRXM__IFELSE(pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
					( \
						CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++) \
							{pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gPrivate_elements + tI);} \
						CRX_ENDFOR \
					)() \
	\
					free(pThis->gPrivate_elements); \
					pThis->gPrivate_elements = tElements; \
	\
					pThis->gPrivate_capacity = vCapacity; \
	\
					return true; \
				} \
				else \
					{return false;} \
			) \
			( \
				pELEMENT_TYPE * tElements = (pELEMENT_TYPE *)(realloc(pThis->gPrivate_elements, \
						vCapacity * sizeof(pELEMENT_TYPE))); \
	\
				if(tElements != NULL) \
				{ \
					pThis->gPrivate_elements = tElements; \
	\
					pThis->gPrivate_capacity = vCapacity; \
	\
					return true; \
				} \
				else \
					{return false;} \
			) \
		} \
		CRX_SCOPE_END \
	} \
	\
	PUBLIC size_t pMEMBER_FUNCTIONS_PREFIX ## getLength(pSORTED_QUEUE_TYPE_NAME const * pThis) \
		{return pThis->gPrivate_length;} \
	PUBLIC size_t pMEMBER_FUNCTIONS_PREFIX ## getCapacity(pSORTED_QUEUE_TYPE_NAME const * pThis) \
		{return pThis->gPrivate_capacity;} \
	\
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## tryMoveAndPush(pSORTED_QUEUE_TYPE_NAME * pThis, \
			pELEMENT_TYPE * pElement) \
	{ \
		CRX_SCOPE_META \
		if((pThis->gPrivate_capacity == pThis->gPrivate_length) && \
				!pMEMBER_FUNCTIONS_PREFIX ## ensureCapacity(pThis, pThis->gPrivate_capacity + 1)) \
			{return false;} \
	\
		CRX_SCOPE \
		size_t vIndexOfCurrentNode = pThis->gPrivate_length; \
	\
		if(vIndexOfCurrentNode > 0) \
		{ \
			size_t tIndexOfParentOfCurrentNode = \
					CRX__C__SortedQueue__GET_PARENT_NODE_INDEX(vIndexOfCurrentNode); \
	\
			if(!pThis->gPrivate_isReversed) \
			{ \
				while(pFUNC_COMPARATOR(pThis->gPrivate_elements + tIndexOfParentOfCurrentNode, \
						pElement) > 0) \
				{ \
					CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
					( \
						pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + vIndexOfCurrentNode, \
								pThis->gPrivate_elements + tIndexOfParentOfCurrentNode); \
					) \
					( \
						memcpy(pThis->gPrivate_elements + vIndexOfCurrentNode, \
								pThis->gPrivate_elements + tIndexOfParentOfCurrentNode, \
								sizeof(pELEMENT_TYPE)); \
					) \
	\
					CRXM__IFELSE(pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
					( \
						pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gPrivate_elements + \
								tIndexOfParentOfCurrentNode); \
					)() \
	\
					vIndexOfCurrentNode = tIndexOfParentOfCurrentNode; \
	\
					if(vIndexOfCurrentNode > 0) \
					{ \
						tIndexOfParentOfCurrentNode = \
								CRX__C__SortedQueue__GET_PARENT_NODE_INDEX(vIndexOfCurrentNode); \
					} \
					else \
						{break;} \
				} \
			} \
			else \
			{ \
				while(pFUNC_COMPARATOR(pThis->gPrivate_elements + tIndexOfParentOfCurrentNode, \
						pElement) < 0) \
				{ \
					CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
					( \
						pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + vIndexOfCurrentNode, \
								pThis->gPrivate_elements + tIndexOfParentOfCurrentNode); \
					) \
					( \
						memcpy(pThis->gPrivate_elements + vIndexOfCurrentNode, \
								pThis->gPrivate_elements + tIndexOfParentOfCurrentNode, \
								sizeof(pELEMENT_TYPE)); \
					) \
	\
					CRXM__IFELSE(pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
					( \
						pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gPrivate_elements + \
								tIndexOfParentOfCurrentNode); \
					)() \
	\
					vIndexOfCurrentNode = tIndexOfParentOfCurrentNode; \
	\
					if(vIndexOfCurrentNode > 0) \
					{ \
						tIndexOfParentOfCurrentNode = \
								CRX__C__SortedQueue__GET_PARENT_NODE_INDEX(vIndexOfCurrentNode); \
					} \
					else \
						{break;} \
				} \
			} \
		} \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + vIndexOfCurrentNode, \
					pElement); \
		) \
		( \
			memcpy(pThis->gPrivate_elements + vIndexOfCurrentNode, \
					pElement, sizeof(pELEMENT_TYPE)); \
		) \
		CRX_SCOPE_END \
	} \
	\
	CRXM__IFELSE2(pIS_ELEMENT_COPYABLE, \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## push(pSORTED_QUEUE_TYPE_NAME * pThis, \
			pELEMENT_TYPE * pElement) \
	{ \
		CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR), \
		unsigned char * vElement = (unsigned char *) CRX__ALLOCA(sizeof(pELEMENT_TYPE));, ) \
		CRXM__IFELSE2(CRXM__AND(CRXM__OR(pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), \
				CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR)), \
		bool vReturn;, )\
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_COPY_CONSTRUCTOR(((pELEMENT_TYPE *)vElement), pElement); \
	\
			CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), \
					vReturn = , return) pMEMBER_FUNCTIONS_PREFIX ## tryMoveAndPush(pThis, \
							((pELEMENT_TYPE *)vElement)); \
		) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				memcpy(vElement, pElement, sizeof(pELEMENT_TYPE)); \
	\
				CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), \
						vReturn = , return) pMEMBER_FUNCTIONS_PREFIX ## tryMoveAndPush(pThis, ((pELEMENT_TYPE *)vElement)); \
			) \
			( \
				return pMEMBER_FUNCTIONS_PREFIX ## tryMoveAndPush(pThis, \
						((pELEMENT_TYPE *)pElement)); \
			) \
		) \
	\
		CRXM__IFELSE(CRXM__AND(CRXM__OR(pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), \
				CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR))) \
		( \
			if(vReturn) \
			{ \
				CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
				pFUNC_ELEMENT_MOVE_DESTRUCTOR(((pELEMENT_TYPE *)vElement));, ) \
			} \
			else \
			{ \
				CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
				pFUNC_ELEMENT_DESTRUCTOR(((pELEMENT_TYPE *)vElement));, ) \
			} \
	\
			return vReturn; \
		)() \
	}, ) \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## popFromFront(pSORTED_QUEUE_TYPE_NAME * pThis) \
	{ \
		CRX_SCOPE_META \
		if(pThis->gPrivate_length == 0) \
			{return true;} \
	\
		CRX_SCOPE \
		size_t vIndexOfCurrentNode = 0; \
	\
		CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements);, ) \
	\
		pThis->gPrivate_length = pThis->gPrivate_length - 1; \
	\
		if(!pThis->gPrivate_isReversed) \
		{ \
			while(vIndexOfCurrentNode < pThis->gPrivate_length) \
			{ \
				size_t tIndexOfChildToMove /*= ?*/; \
	\
				if(pFUNC_COMPARATOR(pThis->gPrivate_elements + \
						CRX__C__SortedQueue__GET_LEFT_CHILD_NODE_INDEX(vIndexOfCurrentNode), \
						pThis->gPrivate_elements + \
						CRX__C__SortedQueue__GET_RIGHT_CHILD_NODE_INDEX(vIndexOfCurrentNode)) < 0) \
				{ \
					tIndexOfChildToMove = \
							CRX__C__SortedQueue__GET_LEFT_CHILD_NODE_INDEX(vIndexOfCurrentNode); \
				} \
				else \
				{ \
					tIndexOfChildToMove = \
							CRX__C__SortedQueue__GET_RIGHT_CHILD_NODE_INDEX(vIndexOfCurrentNode); \
				} \
	\
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
				( \
					pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + vIndexOfCurrentNode, \
							pThis->gPrivate_elements + tIndexOfChildToMove); \
				) \
				( \
					memcpy(pThis->gPrivate_elements + vIndexOfCurrentNode, \
							pThis->gPrivate_elements + tIndexOfChildToMove, \
							sizeof(pELEMENT_TYPE)); \
				) \
	\
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
				( \
					pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gPrivate_elements + \
							tIndexOfChildToMove); \
				)() \
	\
				vIndexOfCurrentNode = tIndexOfChildToMove; \
			} \
		} \
		else \
		{ \
			while(vIndexOfCurrentNode < pThis->gPrivate_length) \
			{ \
				size_t tIndexOfChildToMove /*= ?*/; \
	\
				if(pFUNC_COMPARATOR(pThis->gPrivate_elements + \
						CRX__C__SortedQueue__GET_LEFT_CHILD_NODE_INDEX(vIndexOfCurrentNode), \
						pThis->gPrivate_elements + \
						CRX__C__SortedQueue__GET_RIGHT_CHILD_NODE_INDEX(vIndexOfCurrentNode)) > 0) \
				{ \
					tIndexOfChildToMove = \
							CRX__C__SortedQueue__GET_LEFT_CHILD_NODE_INDEX(vIndexOfCurrentNode); \
				} \
				else \
				{ \
					tIndexOfChildToMove = \
							CRX__C__SortedQueue__GET_RIGHT_CHILD_NODE_INDEX(vIndexOfCurrentNode); \
				} \
	\
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
				( \
					pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + vIndexOfCurrentNode, \
							pThis->gPrivate_elements + tIndexOfChildToMove); \
				) \
				( \
					memcpy(pThis->gPrivate_elements + vIndexOfCurrentNode, \
							pThis->gPrivate_elements + tIndexOfChildToMove, \
							sizeof(pELEMENT_TYPE)); \
				) \
	\
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
				( \
					pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gPrivate_elements + \
							tIndexOfChildToMove); \
				)() \
	\
				vIndexOfCurrentNode = tIndexOfChildToMove; \
			} \
		} \
	\
		CRX_SCOPE_END \
	} \
	\
	PUBLIC pELEMENT_TYPE * pMEMBER_FUNCTIONS_PREFIX ## getFront(pSORTED_QUEUE_TYPE_NAME * pThis) \
	{ \
		assert(pThis->gPrivate_length > 0); \
	\
		return pThis->gPrivate_elements; \
	} \
	PUBLIC pELEMENT_TYPE const * pMEMBER_FUNCTIONS_PREFIX ## constantGetFront( \
			pSORTED_QUEUE_TYPE_NAME const * pThis) \
		{return pMEMBER_FUNCTIONS_PREFIX ## getFront((pSORTED_QUEUE_TYPE_NAME *)pThis);} \
	CRXM__IFELSE2(pIS_ELEMENT_COPYABLE, \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## copyGetFrontTo(pSORTED_QUEUE_TYPE_NAME const * pThis, \
			pELEMENT_TYPE * pReturn), \
	PUBLIC pELEMENT_TYPE pMEMBER_FUNCTIONS_PREFIX ## copyGetFront( \
			pSORTED_QUEUE_TYPE_NAME const * pThis)) \
	{ \
		CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR)) \
		( \
			CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
			pFUNC_ELEMENT_DESTRUCTOR(pReturn);, ) \
	\
			CRXM__IEFLSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(pReturn, pThis->gPrivate_elements + 0); \
			) \
			( \
				memcpy(pReturn, pThis->gPrivate_elements + 0, sizeof(pELEMENT_TYPE)); \
			) \
		) \
		( \
			return *(pThis->gPrivate_elements + 0); \
		) \
	}, ) \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## empty(pSORTED_QUEUE_TYPE_NAME * pThis) \
	{ \
		if(pThis->gPrivate_length == 0) \
			{return;} \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_DESTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++) \
				{pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements + tI);} \
			CRX_ENDFOR \
		)() \
	\
		pThis->gPrivate_length = 0; \
	}
//#END_DEFINE

#define CRX__C__SortedQueue__GET_PARENT_NODE_INDEX(pNODE_INDEX) ((pNODE_INDEX) / 2)
#define CRX__C__SortedQueue__GET_LEFT_CHILD_NODE_INDEX(pNODE_INDEX) ((pNODE_INDEX) << 1)
#define CRX__C__SortedQueue__GET_RIGHT_CHILD_NODE_INDEX(pNODE_INDEX) (((pNODE_INDEX) << 1) + 1)
#define CRX__C__SortedQueue__GET_SIBLING_NODE_INDEX(pNODE_INDEX) ((((pNODE_INDEX) & 1) == 1) ? \
		(pNODE_INDEX - 1) : (pNODE_INDEX + 1))



typedef struct Crx_C_SortedQueue
{
	Crx_C_TypeBluePrint const * CRX_NOT_MINE gPrivate_typeBluePrint;
	size_t gPrivate_capacity;
	bool gPrivate_isReversed;
	pELEMENT_TYPE * gPrivate_elements;
	Crx_C_TypeBluePrint_GetOrderOfObjects gFunc_getOrderOfElements;
} Crx_C_SortedQueue;

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_sortedQueue_construct(Crx_C_SortedQueue * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint, 
		Crx_C_TypeBluePrint_GetOrderOfObjects pFunc_getOrderOfElements, bool pIsReversed, 
		size_t pCapacity CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_sortedQueue_copyConstruct(Crx_C_SortedQueue * pThis,
		Crx_C_SortedQueue const * CRX_NOT_NULL pSortedQueue);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_SortedQueue * crx_c_sortedQueue_new(
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint, 
		Crx_C_TypeBluePrint_GetOrderOfObjects pFunc_getOrderOfElements, 
		bool pIsReversed, size_t pCapacity CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_SortedQueue * crx_c_sortedQueue_moveNew(
		Crx_C_SortedQueue * CRX_NOT_NULL pSortedQueue);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_SortedQueue * crx_c_sortedQueue_copyNew(
		Crx_C_SortedQueue const * CRX_NOT_NULL pSortedQueue);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_sortedQueue_destruct(Crx_C_SortedQueue * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_sortedQueue_free(Crx_C_SortedQueue * pThis);

CRX__C__TYPE_BLUE_PRINT__GENERIC__DECLARE_GET_BLUE_PRINT(
		Crx_C_SortedQueue, crx_c_sortedQueue_,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__FALSE, CRXM__FALSE);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_sortedQueue_ensureCapacity(Crx_C_SortedQueue * pThis,
		size_t pCapacity);

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_sortedQueue_getLength(Crx_C_SortedQueue const * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_sortedQueue_getCapacity(Crx_C_SortedQueue const * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_sortedQueue_tryMoveAndPush(Crx_C_SortedQueue * pThis,
		pELEMENT_TYPE * CRX_NOT_NULL pElement);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_sortedQueue_push(Crx_C_SortedQueue * pThis,
		pELEMENT_TYPE * CRX_NOT_NULL pElement);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_sortedQueue_popFromFront(Crx_C_SortedQueue * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() pELEMENT_TYPE * crx_c_sortedQueue_getFront(Crx_C_SortedQueue * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() pELEMENT_TYPE const * crx_c_sortedQueue_constantGetFront(
		Crx_C_SortedQueue const * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_sortedQueue_copyGetFrontTo(Crx_C_SortedQueue const * pThis,
		pELEMENT_TYPE * CRX_NOT_NULL pReturn);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_sortedQueue_empty(Crx_C_SortedQueue * pThis);


CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/SortedQueue.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif