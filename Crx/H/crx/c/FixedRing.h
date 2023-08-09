#if(!defined(CRX__C__FIXED_RING___h__))
#define CRX__C__FIXED_RING___h__

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
//<<END>>
	
CRX__LIB__C_CODE_BEGIN()


typedef struct Crx_C_FixedRing_Private_IndexTransform
{
	size_t gNewIndex;
	size_t gNewCountToEnd;
} Crx_C_FixedRing_Private_IndexTransform;

/* IMPORTANT: REFER TO NOTES IN Ring.h */

#if(!CRX_ARE_VARIADIC_MACROS_EMULATED)
	#define CRX__C__FixedRing__DECLARE(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__FixedRing__DECLARE, __VA_ARGS__)
#else
	#define CRX__C__FixedRing__DECLARE(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__FixedRing__DECLARE, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20)
#endif

#define CRX__C__FixedRing__DECLARE__12(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__FixedRing__DECLARE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, CRXM__FALSE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pThis, \
				pDEFAULT_SIZE_OF_INTERNAL_BUFFER), \
		CRXM__OR(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, pSTART_INDEX_DEFAULT_ALIGN_FACTOR),  \
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())

#define CRX__C__FixedRing__DECLARE__13(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__FixedRing__DECLARE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, CRXM__TRUE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pThis, \
				pDEFAULT_SIZE_OF_INTERNAL_BUFFER), \
		CRXM__OR(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, pSTART_INDEX_DEFAULT_ALIGN_FACTOR), \
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())


#define _CRX__C__FixedRing__DECLARE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, pIS_COPYABLE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		pTHIS_SIZE_OF_INTERNAL_BUFFER, pHAS_ALIGN_FACTOR, PUBLIC, PRIVATE) \
	typedef struct pARRAY_TYPE_NAME \
	{ \
		pSIZE_T gPrivate_startIndex; \
		pSIZE_T gPrivate_length; \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
				pSIZE_T gSIZE_OF_INTERNAL_BUFFER;, )\
		CRXM__IFELSE2(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
				signed char gPrivate_startIndexAlignFactor;, )\
		pELEMENT_TYPE gBuffer[CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, 1, pDEFAULT_SIZE_OF_INTERNAL_BUFFER)];\
	} pARRAY_TYPE_NAME; \
	\
	typedef char pARRAY_TYPE_NAME ##__ERROR__INVALID_DEFAULT_SIZE_OF_INTERNAL_BUFFER[2 * !!( \
			(pDEFAULT_SIZE_OF_INTERNAL_BUFFER == 0) || \
			((pDEFAULT_SIZE_OF_INTERNAL_BUFFER & (pDEFAULT_SIZE_OF_INTERNAL_BUFFER - 1)) == 0)) - 1]; \
	\
	\
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC size_t pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCorrectCapacityBoundFor(size_t pCapacity), ); \
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC size_t pARRAY_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf(pARRAY_TYPE_NAME const * pArray), ); \
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC size_t pARRAY_MEMBER_FUNCTIONS_PREFIX ## getByteSizeFor(size_t pSizeOfInternalBuffer), ); \
	CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD),  \
			CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis, size_t pSizeOfInternalBuffer)), \
			CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis, size_t pSizeOfInternalBuffer, \
			signed char pStartIndexAlignFactor), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis, \
			signed char pStartIndexAlignFactor))); \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveConstruct(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME * pArray), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyConstruct(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME const * pArray); \
	CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD),  \
			CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD), \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(void), \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(size_t pSizeOfInternalBuffer CRX_DEFAULT(0))), \
			CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(size_t pSizeOfInternalBuffer CRX_DEFAULT(0), \
			signed char pStartIndexAlignFactor CRX_DEFAULT(0)), \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(signed char pStartIndexAlignFactor CRX_DEFAULT(0)))); \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveNew(pARRAY_TYPE_NAME * pArray); \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyNew(pARRAY_TYPE_NAME const * pArray); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_new2(pARRAY_TYPE_NAME const * pArray, \
			size_t pStartIndex, size_t pWidth), ); \
	CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
	PRIVATE void pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct(pARRAY_TYPE_NAME * pThis, size_t pStartIndex, \
			size_t pEndIndex), ); \
	CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## destruct(pARRAY_TYPE_NAME * pThis), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## free(pARRAY_TYPE_NAME * pThis); \
	PUBLIC pSIZE_T pARRAY_MEMBER_FUNCTIONS_PREFIX ## getLength(pARRAY_TYPE_NAME const * pThis); \
	PUBLIC pSIZE_T pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCapacity(pARRAY_TYPE_NAME const * pThis); \
	PRIVATE void pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_moveElements(pELEMENT_TYPE * pSourceBuffer, \
			size_t pStartIndex, size_t pLength, size_t pCapacity, pELEMENT_TYPE * pTargetBuffer); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## empty(pARRAY_TYPE_NAME * pThis); \
	PRIVATE void pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			size_t pWidth); \
	PRIVATE Crx_C_FixedRing_Private_IndexTransform pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_roundInsertSpaceAt( \
			pARRAY_TYPE_NAME * pThis, size_t pIndex, size_t pWidth); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyAssignFrom2(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME const * pArray, size_t pStartIndex, size_t pWidth), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyAssignFrom(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME const * pArray), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndSetAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, pELEMENT_TYPE * pElement); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## setAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pElement), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## setAt2(pARRAY_TYPE_NAME * pThis, size_t pIndex, pELEMENT_TYPE pElement), ); \
	PUBLIC pELEMENT_TYPE * pARRAY_MEMBER_FUNCTIONS_PREFIX ## get(pARRAY_TYPE_NAME * pThis, size_t pIndex); \
	PUBLIC pELEMENT_TYPE const * pARRAY_MEMBER_FUNCTIONS_PREFIX ## constantGet(pARRAY_TYPE_NAME const * pThis, size_t pIndex); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	CRXM__IFELSE2(pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyGet(pARRAY_TYPE_NAME const * pThis, \
			pELEMENT_TYPE * pReturn, size_t pIndex), \
	PUBLIC pELEMENT_TYPE pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyGet(pARRAY_TYPE_NAME const * pThis, size_t pIndex)), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPush(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE * pElement); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastPush(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE const * pElement), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundPush(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE * pElement); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundPush(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE const * pElement), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastPush2(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE pElement), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundPush2(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE pElement), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## pop(pARRAY_TYPE_NAME * pThis); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPushToFront(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE * pElement); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastPushToFront(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE const * pElement), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundPushToFront(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE * pElement); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundPushToFront(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE const * pElement), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastPushToFront2(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE pElement), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundPushToFront2(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE pElement), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## popFromFront(pARRAY_TYPE_NAME * pThis); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastInsertElementAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE * pElement); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pElement), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundInsertElementAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE * pElement); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundInsertElementAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pElement), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementAt2(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE pElement), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundInsertElementAt2(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE pElement), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementsAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pARRAY_TYPE_NAME const * pArray, size_t pStartIndex, size_t pWidth), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundInsertElementsAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pARRAY_TYPE_NAME const * pArray, size_t pStartIndex, size_t pWidth), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertCArrayAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pArray, size_t pWidth), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundInsertCArrayAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pArray, size_t pWidth), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementCopiesAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pElement, size_t pNumberOfCopies), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundInsertElementCopiesAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pElement, size_t pNumberOfCopies), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementCopiesAt2(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE pElement, size_t pNumberOfCopies), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundInsertElementCopiesAt2(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE pElement, size_t pNumberOfCopies), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## removeElements(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			size_t pWidth); \
	PUBLIC pELEMENT_TYPE * pARRAY_MEMBER_FUNCTIONS_PREFIX ## getElementsPointer(pARRAY_TYPE_NAME * pThis); \
	PUBLIC pELEMENT_TYPE const * pARRAY_MEMBER_FUNCTIONS_PREFIX ## constantGetElementsPointer(pARRAY_TYPE_NAME const * pThis);
//#END_DEFINE
		
		


#if(!CRX_ARE_VARIADIC_MACROS_EMULATED)
	#define CRX__C__FixedRing__DEFINE(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__FixedRing__DEFINE, __VA_ARGS__)
#else
	#define CRX__C__FixedRing__DEFINE(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__FixedRing__DEFINE, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20)
#endif

#define CRX__C__FixedRing__DEFINE__12(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__FixedRing__DEFINE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, CRXM__FALSE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pThis, \
				pDEFAULT_SIZE_OF_INTERNAL_BUFFER), \
		CRXM__OR(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, pSTART_INDEX_DEFAULT_ALIGN_FACTOR), \
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())

#define CRX__C__FixedRing__DEFINE__13(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__FixedRing__DEFINE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, CRXM__TRUE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pThis, \
				pDEFAULT_SIZE_OF_INTERNAL_BUFFER), \
		CRXM__OR(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, pSTART_INDEX_DEFAULT_ALIGN_FACTOR), \
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())


#define _CRX__C__FixedRing__DEFINE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, pIS_COPYABLE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		pTHIS_SIZE_OF_INTERNAL_BUFFER, pHAS_ALIGN_FACTOR, PUBLIC, PRIVATE) \
	typedef char pARRAY_TYPE_NAME ##__ERROR__INVALID_DEFAULT_SIZE_OF_INTERNAL_BUFFER__2[2 * !!( \
			(pDEFAULT_SIZE_OF_INTERNAL_BUFFER == 0) || \
			((pDEFAULT_SIZE_OF_INTERNAL_BUFFER & (pDEFAULT_SIZE_OF_INTERNAL_BUFFER - 1)) == 0)) - 1]; \
	\
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC size_t pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCorrectCapacityBoundFor(size_t pCapacity) \
	{ \
		size_t vReturn = 1; \
	\
		while(vReturn < pCapacity) \
			{vReturn = (vReturn << 1);} \
	\
		return vReturn; \
	}, ) \
	\
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC size_t pARRAY_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf(pARRAY_TYPE_NAME const * pArray) \
	{ \
		return (sizeof(pARRAY_TYPE_NAME) + \
				(pArray->gSIZE_OF_INTERNAL_BUFFER - 1) * sizeof(pELEMENT_TYPE)); \
	}, ) \
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC size_t pARRAY_MEMBER_FUNCTIONS_PREFIX ## getByteSizeFor(size_t pSizeOfInternalBuffer) \
	{ \
		assert((pSizeOfInternalBuffer > 0) || (pDEFAULT_SIZE_OF_INTERNAL_BUFFER > 0)); \
	\
		return (sizeof(pARRAY_TYPE_NAME) + ((((pSizeOfInternalBuffer == 0) ? \
				pDEFAULT_SIZE_OF_INTERNAL_BUFFER : pSizeOfInternalBuffer) - 1) * sizeof(pELEMENT_TYPE))); \
	}, ) \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD),  \
			CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis, size_t pSizeOfInternalBuffer)), \
			CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis, size_t pSizeOfInternalBuffer, \
			signed char pStartIndexAlignFactor), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis, \
			signed char pStartIndexAlignFactor))) \
	{ \
		/* assert(pThis->gPrivate_length == 0); */ \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		assert((pSizeOfInternalBuffer == 0) || ((pSizeOfInternalBuffer & (pSizeOfInternalBuffer - 1)) == 0)); \
		assert(pSizeOfInternalBuffer <= pSIZE_T_MAX); \
		assert((pSizeOfInternalBuffer > 0) || (pDEFAULT_SIZE_OF_INTERNAL_BUFFER > 0));, ) \
	\
		pThis->gPrivate_length == 0; \
	\
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pThis->gSIZE_OF_INTERNAL_BUFFER = ((pSIZE_T)((pSizeOfInternalBuffer == 0) ? \
					pDEFAULT_SIZE_OF_INTERNAL_BUFFER : pSizeOfInternalBuffer));, )\
	\
		CRXM__IFELSE(pHAS_ALIGN_FACTOR) \
		( \
			CRXM__IFELSE(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD) \
			( \
				if(pStartIndexAlignFactor == 0) \
					{pThis->gPrivate_startIndexAlignFactor = pSTART_INDEX_DEFAULT_ALIGN_FACTOR;} \
				else \
					{pThis->gPrivate_startIndexAlignFactor = pStartIndexAlignFactor;} \
		\
				if(pThis->gPrivate_startIndexAlignFactor > 0) \
					{pThis->gPrivate_startIndex = (pTHIS_SIZE_OF_INTERNAL_BUFFER >> pThis->gPrivate_startIndexAlignFactor);} \
				else \
				{ \
					pThis->gPrivate_startIndex = pTHIS_SIZE_OF_INTERNAL_BUFFER - \
							pTHIS_SIZE_OF_INTERNAL_BUFFER >> abs(pThis->gPrivate_startIndexAlignFactor); \
				} \
			) \
			( \
				if(pSTART_INDEX_DEFAULT_ALIGN_FACTOR > 0) \
					{pThis->gPrivate_startIndex = (pTHIS_SIZE_OF_INTERNAL_BUFFER >> pSTART_INDEX_DEFAULT_ALIGN_FACTOR);} \
				else \
				{ \
					pThis->gPrivate_startIndex = pTHIS_SIZE_OF_INTERNAL_BUFFER - \
							(pTHIS_SIZE_OF_INTERNAL_BUFFER >> abs(pSTART_INDEX_DEFAULT_ALIGN_FACTOR)); \
				} \
			) \
		) \
		( \
			pThis->gPrivate_startIndex = 0; \
		) \
	} \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveConstruct(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME * pArray) \
	{ \
		pThis->gPrivate_startIndex = pArray->gPrivate_startIndex; \
		pThis->gPrivate_length = 0; \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pThis->gSIZE_OF_INTERNAL_BUFFER = pArray->gSIZE_OF_INTERNAL_BUFFER;, )\
		CRXM__IFELSE2(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
		pThis->gPrivate_startIndexAlignFactor = pArray->gPrivate_startIndexAlignFactor;, )\
	\
		CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++) \
		{ \
			pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPush(pThis, pArray->gBuffer + \
					((pArray->gPrivate_startIndex + tI) & \
					(CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER( \
							pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pArray, \
							pDEFAULT_SIZE_OF_INTERNAL_BUFFER) - 1))); \
	\
			CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
			pFUNC_ELEMENT_MOVE_DESTRUCTOR(pArray->gBuffer + ((pArray->gPrivate_startIndex + tI) & \
					(CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER( \
							pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pArray, \
							pDEFAULT_SIZE_OF_INTERNAL_BUFFER) - 1))), ); \
		} \
		CRX_ENDFOR \
	\
		pArray->gPrivate_length = 0; \
	}, ) \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyConstruct(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME const * pArray) \
	{ \
		CRXM__IFELSE2(CRXM__NOT(pIS_COPYABLE), abort();, \
	\
		CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD),  \
				CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD), \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pThis), \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pThis, \
						pArray->gSIZE_OF_INTERNAL_BUFFER)), \
				CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pThis, \
						pArray->gSIZE_OF_INTERNAL_BUFFER, pArray->gPrivate_startIndexAlignFactor), \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pThis, \
						pArray->gPrivate_startIndexAlignFactor))); \
	\
		if(pArray->gPrivate_length > 0) \
		{ \
			CRXM__IFELSE2(pHAS_ALIGN_FACTOR, \
			pSIZE_T tStartIndex = 0;, )\
	\
			CRX__C__FixedRing__DEFINE___SET_TO_ALIGN_FACTOR(pTHIS_SIZE_OF_INTERNAL_BUFFER, \
					pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
					pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pThis, tStartIndex) \
	\
			CRXM__IFELSE(pHAS_ALIGN_FACTOR) \
			( \
				if(pTHIS_SIZE_OF_INTERNAL_BUFFER - tStartIndex < pArray->gPrivate_length) \
				{ \
					if(pArray->gPrivate_length > (pTHIS_SIZE_OF_INTERNAL_BUFFER >> 1)) \
						{tStartIndex = 0;} \
					else \
						{tStartIndex = (pTHIS_SIZE_OF_INTERNAL_BUFFER >> 1);} \
				} \
			)() \
	\
			pThis->gPrivate_startIndex = 0 CRXM__IFELSE2(pHAS_ALIGN_FACTOR, + tStartIndex, ); \
	\
			CRX__C__FIXED_RING__ECHO__COPY_FROM_RING_RANGE(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pELEMENT_TYPE, \
					pThis->gBuffer, pThis->gPrivate_startIndex, \
					pTHIS_SIZE_OF_INTERNAL_BUFFER, \
					0, pArray->gBuffer, pArray->gPrivate_startIndex, \
					CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER( \
							pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pArray, \
							pDEFAULT_SIZE_OF_INTERNAL_BUFFER), \
					0, pArray->gPrivate_length) \
	\
			pThis->gPrivate_length = pArray->gPrivate_length; \
		} \
	)} \
	CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD),  \
			CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD), \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(void), \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(size_t pSizeOfInternalBuffer CRX_DEFAULT(0))), \
			CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(size_t pSizeOfInternalBuffer CRX_DEFAULT(0), \
			signed char pStartIndexAlignFactor CRX_DEFAULT(0)), \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(signed char pStartIndexAlignFactor CRX_DEFAULT(0)))) \
	{ \
		CRX_SCOPE_META \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		assert((pSizeOfInternalBuffer == 0) || \
				((pSizeOfInternalBuffer & (pSizeOfInternalBuffer - 1)) == 0));, ) \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		assert(pSizeOfInternalBuffer <= pSIZE_T_MAX);, ) \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		assert((pSizeOfInternalBuffer > 0) || (pDEFAULT_SIZE_OF_INTERNAL_BUFFER > 0));, ) \
	\
		CRX_SCOPE \
		pARRAY_TYPE_NAME * vReturn; \
	\
		CRXM__IFELSE(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD) \
		( \
			vReturn = (pARRAY_TYPE_NAME *)(calloc(1, \
					sizeof(pARRAY_TYPE_NAME) + ((((pSizeOfInternalBuffer > 0) ? \
					pSizeOfInternalBuffer : pDEFAULT_SIZE_OF_INTERNAL_BUFFER) - 1) * sizeof(pELEMENT_TYPE)))); \
	\
			if(vReturn != NULL) \
			{ \
				CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD), \
						pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(vReturn, pSizeOfInternalBuffer), \
						pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(vReturn, pSizeOfInternalBuffer, \
								pStartIndexAlignFactor)); \
			} \
		) \
		( \
			vReturn = (pARRAY_TYPE_NAME *)(calloc(1, sizeof(pARRAY_TYPE_NAME))); \
	\
			if(vReturn != NULL) \
			{ \
				CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD), \
						pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(vReturn), \
						pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(vReturn, pStartIndexAlignFactor)); \
			} \
		) \
	\
		return vReturn; \
		CRX_SCOPE_END \
	} \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveNew(pARRAY_TYPE_NAME * pArray) \
	{ \
		pARRAY_TYPE_NAME * vReturn = ((pARRAY_TYPE_NAME *) calloc(1, \
				CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf(pArray), \
				sizeof(pARRAY_TYPE_NAME)))); \
	\
		if(vReturn != NULL) \
		{ \
			CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR)) \
			( \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveConstruct(vReturn, pArray); \
			) \
			( \
				memcpy(vReturn, pArray, CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
						pARRAY_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf(pArray), \
						sizeof(pARRAY_TYPE_NAME))); \
			) \
		} \
	\
		return vReturn; \
	} \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyNew(pARRAY_TYPE_NAME const * pArray) \
	{ \
		CRXM__IFELSE2(CRXM__NOT(pIS_COPYABLE), abort();, \
	\
		pARRAY_TYPE_NAME * vReturn = ((pARRAY_TYPE_NAME *) calloc(1, \
				CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf(pArray), \
				sizeof(pARRAY_TYPE_NAME)))); \
	\
		if(vReturn != NULL) \
			{pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyConstruct(vReturn, pArray);} \
	\
		return vReturn; \
	)} \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_new2(pARRAY_TYPE_NAME const * pArray, \
			size_t pStartIndex, size_t pWidth) \
	{ \
		CRX_SCOPE_META \
		assert(pStartIndex + pWidth <= pArray->gPrivate_length); \
	\
		CRX_SCOPE \
		pARRAY_TYPE_NAME * vReturn = CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD),  \
				CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD), \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(), \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## new( \
						pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCorrectCapacityBoundFor(pWidth))), \
				CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## new( \
						pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCorrectCapacityBoundFor(pWidth), 0), \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(0))); \
	\
		if((vReturn != NULL) && (pWidth > 0)) \
		{ \
			CRXM__IFELSE2(pHAS_ALIGN_FACTOR, \
			pSIZE_T tStartIndex = 0;, )\
	\
			CRX__C__FixedRing__DEFINE___SET_TO_ALIGN_FACTOR( \
					CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER( \
							pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, vReturn, \
							pDEFAULT_SIZE_OF_INTERNAL_BUFFER), \
					pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
					pSTART_INDEX_DEFAULT_ALIGN_FACTOR, vReturn, tStartIndex) \
	\
			CRXM__IFELSE(pHAS_ALIGN_FACTOR) \
			( \
				if(CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER( \
						pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, vReturn, \
						pDEFAULT_SIZE_OF_INTERNAL_BUFFER) - tStartIndex < pWidth) \
				{ \
					if(pWidth > (CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER( \
								pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, vReturn, \
								pDEFAULT_SIZE_OF_INTERNAL_BUFFER) >> 1)) \
						{tStartIndex = 0;} \
					else \
					{ \
						tStartIndex = (CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER( \
								pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, vReturn, \
								pDEFAULT_SIZE_OF_INTERNAL_BUFFER) >> 1); \
					} \
				} \
			)() \
	\
			vReturn->gPrivate_startIndex = 0 CRXM__IFELSE2(pHAS_ALIGN_FACTOR, + tStartIndex, ); \
	\
			CRX__C__FIXED_RING__ECHO__COPY_FROM_RING_RANGE(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pELEMENT_TYPE, \
					vReturn->gBuffer, vReturn->gPrivate_startIndex, \
					CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER( \
							pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, vReturn, \
							pDEFAULT_SIZE_OF_INTERNAL_BUFFER), \
					0, pArray->gBuffer, pArray->gPrivate_startIndex, \
					CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER( \
							pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pArray, \
							pDEFAULT_SIZE_OF_INTERNAL_BUFFER), \
					pStartIndex, pWidth) \
	\
			vReturn->gPrivate_length = (pSIZE_T)pWidth; \
		} \
	\
		return vReturn; \
		CRX_SCOPE_END \
	}, ) \
	CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
	PRIVATE void pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct(pARRAY_TYPE_NAME * pThis, size_t pStartIndex, \
			size_t pEndIndex) \
	{ \
		size_t vStartIndex = (pThis->gPrivate_startIndex + pStartIndex) & \
				(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1); \
		size_t vEndIndex = (pThis->gPrivate_startIndex + pEndIndex) & \
				(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1); \
	\
		if(vStartIndex <= vEndIndex) \
		{ \
			CRX_FOR(size_t tI = vStartIndex, tI <= vEndIndex, tI++) \
				{pFUNC_ELEMENT_DESTRUCTOR(pThis->gBuffer + tI);} \
			CRX_ENDFOR \
		} \
		else \
		{ \
			CRX_FOR(size_t tI = vStartIndex, tI < pTHIS_SIZE_OF_INTERNAL_BUFFER, tI++) \
				{pFUNC_ELEMENT_DESTRUCTOR(pThis->gBuffer + tI);} \
			CRX_ENDFOR \
			CRX_FOR(size_t tI = 0, tI <= vEndIndex, tI++) \
				{pFUNC_ELEMENT_DESTRUCTOR(pThis->gBuffer + tI);} \
			CRX_ENDFOR \
		} \
	}, )\
	CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## destruct(pARRAY_TYPE_NAME * pThis) \
	{ \
		if(pThis->gPrivate_length > 0) \
			{pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct(pThis);} \
	}, ) \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## free(pARRAY_TYPE_NAME * pThis) \
		{free(pThis);} \
	\
	PUBLIC pSIZE_T pARRAY_MEMBER_FUNCTIONS_PREFIX ## getLength(pARRAY_TYPE_NAME const * pThis) \
		{return pThis->gPrivate_length;} \
	PUBLIC pSIZE_T pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCapacity(pARRAY_TYPE_NAME const * pThis) \
		{return pTHIS_SIZE_OF_INTERNAL_BUFFER;} \
	\
	PRIVATE void pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_moveElements(pELEMENT_TYPE * pSourceBuffer, \
			size_t pStartIndex, size_t pLength, size_t pCapacity, pELEMENT_TYPE * pTargetBuffer) \
	{ \
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < pLength, tI++) \
			{ \
				pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pTargetBuffer + tI, \
						pSourceBuffer + ((pStartIndex + tI) & (pCapacity - 1))); \
			} \
			CRX_ENDFOR \
		) \
		( \
			size_t tEndIndex = (pStartIndex + pLength - 1) & (pCapacity - 1); \
	\
			if(tEndIndex < pStartIndex) \
			{ \
				memcpy(pTargetBuffer, \
						pSourceBuffer + pStartIndex, (pCapacity - pStartIndex) * sizeof(pELEMENT_TYPE)); \
				memcpy(pTargetBuffer + (pCapacity - pStartIndex), \
						pSourceBuffer, (tEndIndex + 1) * sizeof(pELEMENT_TYPE)); \
			} \
			else \
				{memcpy(pTargetBuffer, pSourceBuffer + pStartIndex, pLength * sizeof(pELEMENT_TYPE));} \
		) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < pLength, tI++) \
				{pFUNC_ELEMENT_MOVE_DESTRUCTOR(pSourceBuffer + ((pStartIndex + tI) & (pCapacity - 1)));} \
			CRX_ENDFOR \
		)() \
	} \
	\
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## empty(pARRAY_TYPE_NAME * pThis) \
	{ \
		CRXM__IFELSE(pFUNC_ELEMENT_DESTRUCTOR) \
		( \
			if(pThis->gPrivate_length == 0) \
				{return;} \
	\
			pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct(pThis, 0, pThis->gPrivate_length - 1); \
		)() \
	\
		CRXM__IFELSE(pHAS_ALIGN_FACTOR) \
		( \
			CRX__C__FixedRing__DEFINE___SET_TO_ALIGN_FACTOR(pTHIS_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
					pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pThis, pThis->gPrivate_startIndex) \
		) \
		( \
			pThis->gPrivate_startIndex = 0; \
		) \
	\
		pThis->gPrivate_length = 0; \
	} \
	\
	PRIVATE void pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			size_t pWidth) \
	{ \
		assert(pIndex <= pThis->gPrivate_length); \
		assert(pWidth + pThis->gPrivate_length <= pTHIS_SIZE_OF_INTERNAL_BUFFER); \
	\
		CRX__C__FixedRing__ECHO_INSERT_SPACE_AT(pSIZE_T, pELEMENT_TYPE, pTHIS_SIZE_OF_INTERNAL_BUFFER, \
				pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, pThis, pIndex, pWidth) \
	} \
	PRIVATE Crx_C_FixedRing_Private_IndexTransform pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_roundInsertSpaceAt( \
			pARRAY_TYPE_NAME * pThis, size_t pIndex, size_t pWidth) \
	{ \
		CRX_SCOPE_META \
		assert(pIndex <= pThis->gPrivate_length); \
	\
		CRX_SCOPE \
		Crx_C_FixedRing_Private_IndexTransform vReturn; \
	\
		CRX__SET_TO_ZERO(Crx_C_FixedRing_Private_IndexTransform, vReturn); \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_DESTRUCTOR) \
		( \
			if(pThis->gPrivate_length > 0) \
			{ \
				if(pWidth > pTHIS_SIZE_OF_INTERNAL_BUFFER - pThis->gPrivate_length) \
				{ \
					if(pWidth >= pTHIS_SIZE_OF_INTERNAL_BUFFER) \
					{ \
						pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct(pThis, 0, \
								pThis->gPrivate_length - 1); \
					} \
					else \
					{ \
						if(pWidth <= pTHIS_SIZE_OF_INTERNAL_BUFFER - pThis->gPrivate_length + pIndex) \
						{ \
							pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct(pThis, 0, \
									pWidth - (pTHIS_SIZE_OF_INTERNAL_BUFFER - pThis->gPrivate_length) - 1); \
						} \
						else \
						{ \
							pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct(pThis, 0, pIndex - 1); \
							pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct(pThis, \
									pThis->gPrivate_length - (pWidth - (pTHIS_SIZE_OF_INTERNAL_BUFFER - pThis->gPrivate_length) - pIndex), \
									pThis->gPrivate_length - 1); \
						} \
					} \
				} \
			} \
		)() \
	\
		if(pWidth < pTHIS_SIZE_OF_INTERNAL_BUFFER) \
		{ \
			if(pIndex == 0) \
			{ \
				if(pThis->gPrivate_startIndex > pWidth) \
					{pThis->gPrivate_startIndex = ((pSIZE_T)(pThis->gPrivate_startIndex - pWidth));} \
				else \
					{pThis->gPrivate_startIndex = ((pSIZE_T)(pTHIS_SIZE_OF_INTERNAL_BUFFER - (pWidth - pThis->gPrivate_startIndex)));} \
			} \
			else if(pIndex == pThis->gPrivate_length) \
				{} \
			else \
			{ \
				assert((((pThis->gPrivate_startIndex + pIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)) != pThis->gPrivate_startIndex) && \
						(pWidth < pTHIS_SIZE_OF_INTERNAL_BUFFER)); \
	\
				if(pWidth >= pTHIS_SIZE_OF_INTERNAL_BUFFER - pThis->gPrivate_length + pIndex) \
				{ \
					pThis->gPrivate_startIndex = ((pSIZE_T)(pThis->gPrivate_startIndex + (pIndex & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)))); \
				} \
				else \
				{ \
					size_t tOldStartIndex = pThis->gPrivate_startIndex; \
	\
					if((pThis->gPrivate_length >> 1) > pIndex) \
					{ \
						size_t tSegmentStartIndex; \
						size_t tSegmentEndIndex = pIndex - 1; \
	\
						if(pWidth < pTHIS_SIZE_OF_INTERNAL_BUFFER - pThis->gPrivate_length) \
						{ \
							tSegmentStartIndex = 0; \
	\
							/*THE FOLLOWING IS SUBTRACTING pWidth*/ \
							pThis->gPrivate_startIndex = ((pSIZE_T)((pThis->gPrivate_startIndex + (pTHIS_SIZE_OF_INTERNAL_BUFFER - pWidth)) & \
									(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
						} \
						else \
						{ \
							tSegmentStartIndex = pWidth - (pTHIS_SIZE_OF_INTERNAL_BUFFER - pThis->gPrivate_length); \
	\
							pThis->gPrivate_startIndex = ((pSIZE_T)((pThis->gPrivate_startIndex + pThis->gPrivate_length) & \
									(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
						} \
	\
						CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR)) \
						( \
							CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
							( \
								CRX_FOR(size_t tI = tSegmentStartIndex, tI <= tSegmentEndIndex, tI++) \
								{ \
									/*THE FOLLOWING IS SUBTRACTING pWidth*/ \
									pFUNC_ELEMENT_MOVE_CONSTRUCTOR( \
											pThis->gBuffer + ((tOldStartIndex + tI + pTHIS_SIZE_OF_INTERNAL_BUFFER - pWidth) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
											pThis->gBuffer + ((tOldStartIndex + tI) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
	\
									CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, \
									pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gBuffer + \
											((tOldStartIndex + tI) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)));, ) \
								} \
								CRX_ENDFOR \
							) \
							( \
								CRX_FOR(size_t tI = tSegmentStartIndex, tI <= tSegmentEndIndex, tI++) \
								{ \
									/*THE FOLLOWING IS SUBTRACTING pWidth*/ \
									memmove(pThis->gBuffer + ((tOldStartIndex + tI + pTHIS_SIZE_OF_INTERNAL_BUFFER - pWidth) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
											pThis->gBuffer + ((tOldStartIndex + tI) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
											sizeof(pELEMENT_TYPE)); \
	\
									pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gBuffer + \
											((tOldStartIndex + tI) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
								} \
								CRX_ENDFOR \
							) \
						) \
						( \
							CRX__C__FIXED_RING__ECHO__RAW_ROTATE_LEFT(pELEMENT_TYPE, pThis->gBuffer, \
									(tOldStartIndex + tSegmentStartIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1), \
									(tOldStartIndex + tSegmentEndIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1), \
									pTHIS_SIZE_OF_INTERNAL_BUFFER, pWidth, CRXM__FALSE) \
						) \
					} \
					else \
					{ \
						size_t tSegmentStartIndex = pIndex; \
						size_t tSegmentEndIndex = pThis->gPrivate_length - 1; \
	\
						if(pWidth >= pTHIS_SIZE_OF_INTERNAL_BUFFER - pThis->gPrivate_length) \
						{ \
							pThis->gPrivate_startIndex = ((pSIZE_T)((pThis->gPrivate_startIndex + (pWidth - (pTHIS_SIZE_OF_INTERNAL_BUFFER - pThis->gPrivate_length))) & \
									(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
						} \
	\
						CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR)) \
						( \
							CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
							( \
								CRX_FOR(size_t tI = tSegmentEndIndex, tI >= tSegmentStartIndex, tI--) \
								{ \
									pFUNC_ELEMENT_MOVE_CONSTRUCTOR( \
											pThis->gBuffer + ((tOldStartIndex + tI + pWidth) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
											pThis->gBuffer + ((tOldStartIndex + tI) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
	\
									CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, \
									pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gBuffer + \
											((tOldStartIndex + tI) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)));, ) \
								} \
								CRX_ENDFOR \
							) \
							( \
								CRX_FOR(size_t tI = tSegmentEndIndex, tI >= tSegmentStartIndex, tI--) \
								{ \
									memmove(pThis->gBuffer + ((tOldStartIndex + tI + pWidth) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
											pThis->gBuffer + ((tOldStartIndex + tI) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
											sizeof(pELEMENT_TYPE)); \
	\
									pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gBuffer + \
											((tOldStartIndex + tI) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
								} \
								CRX_ENDFOR \
							) \
						) \
						( \
							CRX__C__FIXED_RING__ECHO__RAW_ROTATE_RIGHT(pELEMENT_TYPE, pThis->gBuffer, \
									(tOldStartIndex + tSegmentStartIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1), \
									(tOldStartIndex + tSegmentEndIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1), \
									pTHIS_SIZE_OF_INTERNAL_BUFFER, pWidth, CRXM__FALSE) \
						) \
					} \
	\
					if(pWidth < pTHIS_SIZE_OF_INTERNAL_BUFFER - pThis->gPrivate_length) \
						{vReturn.gNewIndex = pIndex;} \
					else \
					{ \
						vReturn.gNewIndex = (pIndex + (pTHIS_SIZE_OF_INTERNAL_BUFFER - \
								(pWidth - (pTHIS_SIZE_OF_INTERNAL_BUFFER - pThis->gPrivate_length)))) & \
								(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1); \
					} \
				} \
			} \
	\
			pThis->gPrivate_length = pThis->gPrivate_length + ((pSIZE_T)pWidth); \
	\
			if(pThis->gPrivate_length > pTHIS_SIZE_OF_INTERNAL_BUFFER) \
				{pThis->gPrivate_length = pTHIS_SIZE_OF_INTERNAL_BUFFER;} \
	\
			vReturn.gNewCountToEnd = pWidth; \
		} \
		else \
			{vReturn.gNewCountToEnd = pTHIS_SIZE_OF_INTERNAL_BUFFER;} \
	\
		return vReturn; \
		CRX_SCOPE_END \
	} \
	\
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyAssignFrom2(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME const * pArray, size_t pStartIndex, size_t pWidth) \
	{ \
		CRX_SCOPE_META \
		assert(pStartIndex + pWidth <= pArray->gPrivate_length); \
	\
		CRXM__IFELSE(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD) \
		( \
		if(pWidth > pThis->gSIZE_OF_INTERNAL_BUFFER) \
			{return false;} \
		)() \
	\
		CRX_SCOPE \
		pARRAY_TYPE_NAME * vArray = ((pARRAY_TYPE_NAME *)pArray); \
		bool vIsSameArray = CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis, pArray, true); \
		bool vReturn = false; \
	\
		if(vIsSameArray) \
		{ \
			CRXM__IFELSE(CRX__ARE_ONLY_POINTERS_TO_SAME_OBJECT_EQUAL_AND_ALWAYS) \
			( \
				if((pStartIndex == 0) && (pWidth == pThis->gPrivate_length)) \
					{return true;} \
			)() \
	\
			vArray = pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_new2(pArray, pStartIndex, pWidth); \
		} \
	\
		if(vArray != NULL) \
		{ \
			CRXM__IFELSE2(pHAS_ALIGN_FACTOR, \
			pSIZE_T tStartIndex = 0;, )\
	\
			CRX__C__FixedRing__DEFINE___SET_TO_ALIGN_FACTOR(pTHIS_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
					pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pThis, tStartIndex) \
	\
			CRXM__IFELSE(pFUNC_ELEMENT_DESTRUCTOR) \
			( \
				if(pThis->gPrivate_length > 0) \
					{pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct(pThis, 0, pThis->gPrivate_length - 1);} \
			)() \
	\
			CRXM__IFELSE(pHAS_ALIGN_FACTOR) \
			( \
				if(pTHIS_SIZE_OF_INTERNAL_BUFFER - tStartIndex < pWidth) \
				{ \
					if(pWidth > (pTHIS_SIZE_OF_INTERNAL_BUFFER >> 1)) \
						{tStartIndex = 0;} \
					else \
						{tStartIndex = (pTHIS_SIZE_OF_INTERNAL_BUFFER >> 1);} \
				} \
			)() \
	\
			pThis->gPrivate_startIndex = 0 CRXM__IFELSE2(pHAS_ALIGN_FACTOR, + tStartIndex, ); \
	\
			CRX__C__FIXED_RING__ECHO__COPY_FROM_RING_RANGE(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pELEMENT_TYPE, \
					pThis->gBuffer, pThis->gPrivate_startIndex, pTHIS_SIZE_OF_INTERNAL_BUFFER, 0, \
					pArray->gBuffer, pArray->gPrivate_startIndex, \
					CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER( \
							pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pArray, \
							pDEFAULT_SIZE_OF_INTERNAL_BUFFER), \
					pStartIndex, pWidth) \
	\
			pThis->gPrivate_length = ((pSIZE_T)pWidth); \
	\
			vReturn = true; \
	\
			if(vIsSameArray) \
			{ \
				CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## destruct(vArray);, ) \
				free(vArray); \
			} \
		} \
	\
		return true; \
		CRX_SCOPE_END \
	}, ) \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyAssignFrom(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME const * pArray) \
	{ \
		return pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyAssignFrom2(pThis, pArray, 0, \
				pArray->gPrivate_length); \
	}, ) \
	\
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndSetAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, pELEMENT_TYPE * pElement) \
	{ \
		assert(pIndex <= pThis->gPrivate_length); \
	\
		CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
				pFUNC_ELEMENT_DESTRUCTOR(pThis->gBuffer + ((pThis->gPrivate_startIndex + pIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)));, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gBuffer + \
					((pThis->gPrivate_startIndex + pIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), pElement); \
		) \
		( \
			memcpy(pThis->gBuffer + ((pThis->gPrivate_startIndex + pIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), pElement, sizeof(pELEMENT_TYPE)); \
		) \
	} \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## setAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pElement) \
	{ \
		CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR), \
		unsigned char * vElement = (unsigned char *) CRX__ALLOCA(sizeof(pELEMENT_TYPE));, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_COPY_CONSTRUCTOR(((pELEMENT_TYPE *)vElement), pElement); \
			pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndSetAt(pThis, pIndex, ((pELEMENT_TYPE *)vElement)); \
		) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				memcpy(vElement, pElement, sizeof(pELEMENT_TYPE)); \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndSetAt(pThis, pIndex, ((pELEMENT_TYPE *)vElement)); \
			) \
			( \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndSetAt(pThis, pIndex, ((pELEMENT_TYPE *)pElement)); \
			) \
		) \
	\
		CRXM__IFELSE2(CRXM__AND(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
						CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR)), \
				pFUNC_ELEMENT_MOVE_DESTRUCTOR(((pELEMENT_TYPE *)vElement));, ) \
	}, ) \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## setAt2(pARRAY_TYPE_NAME * pThis, size_t pIndex, pELEMENT_TYPE pElement) \
	{ \
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndSetAt(pThis, pIndex, &pElement); \
	}, ) \
	PUBLIC pELEMENT_TYPE * pARRAY_MEMBER_FUNCTIONS_PREFIX ## get(pARRAY_TYPE_NAME * pThis, size_t pIndex) \
	{ \
		assert(pIndex < pThis->gPrivate_length); \
	\
		return (pThis->gBuffer + ((pThis->gPrivate_startIndex + pIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
	} \
	PUBLIC pELEMENT_TYPE const * pARRAY_MEMBER_FUNCTIONS_PREFIX ## constantGet(pARRAY_TYPE_NAME const * pThis, size_t pIndex) \
		{return pARRAY_MEMBER_FUNCTIONS_PREFIX ## get((pARRAY_TYPE_NAME *) pThis, pIndex);} \
	CRXM__IFELSE2(pIS_COPYABLE, \
	CRXM__IFELSE2(pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyGet(pARRAY_TYPE_NAME const * pThis, \
			pELEMENT_TYPE * pReturn, size_t pIndex), \
	PUBLIC pELEMENT_TYPE pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyGet(pARRAY_TYPE_NAME const * pThis, size_t pIndex)) \
	{ \
		assert(pIndex < pThis->gPrivate_length); \
	 \
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_COPY_CONSTRUCTOR(pReturn, \
					pThis->gBuffer + ((pThis->gPrivate_startIndex + pIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
		) \
		( \
			return *(pThis->gBuffer + ((pThis->gPrivate_startIndex + pIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
		) \
	}, ) \
	\
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPush(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE * pElement) \
	{ \
		assert(pTHIS_SIZE_OF_INTERNAL_BUFFER > pThis->gPrivate_length); \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gBuffer + \
					((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), pElement); \
		) \
		( \
			memcpy(pThis->gBuffer + ((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), pElement, sizeof(pELEMENT_TYPE)); \
		) \
	\
		pThis->gPrivate_length = pThis->gPrivate_length + 1; \
	} \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastPush(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE const * pElement) \
	{ \
		CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR), \
		unsigned char * vElement = (unsigned char *) CRX__ALLOCA(sizeof(pELEMENT_TYPE));, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_COPY_CONSTRUCTOR(((pELEMENT_TYPE *)vElement), pElement); \
			pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPush(pThis, ((pELEMENT_TYPE *)vElement)); \
		) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				memcpy(vElement, pElement, sizeof(pELEMENT_TYPE)); \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPush(pThis, ((pELEMENT_TYPE *)vElement)); \
			) \
			( \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPush(pThis, ((pELEMENT_TYPE *)pElement)); \
			) \
		) \
	\
		CRXM__IFELSE2(CRXM__AND(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
						CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR)), \
				pFUNC_ELEMENT_MOVE_DESTRUCTOR(((pELEMENT_TYPE *)vElement));, ) \
	}, ) \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundPush(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE * pElement) \
	{ \
		CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
		if(pThis->gPrivate_length == pTHIS_SIZE_OF_INTERNAL_BUFFER) \
			{pFUNC_ELEMENT_DESTRUCTOR(pThis->gBuffer + pThis->gPrivate_startIndex);}, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gBuffer + ((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), pElement); \
		) \
		( \
			memcpy(pThis->gBuffer + ((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), pElement, sizeof(pELEMENT_TYPE)); \
		) \
	\
		if(pThis->gPrivate_length != pTHIS_SIZE_OF_INTERNAL_BUFFER) \
			{pThis->gPrivate_length = pThis->gPrivate_length + 1;} \
		else \
		{ \
			if(pThis->gPrivate_startIndex == pTHIS_SIZE_OF_INTERNAL_BUFFER - 1) \
				{pThis->gPrivate_startIndex = 0;} \
			else \
				{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex + 1;} \
		} \
	} \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundPush(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE const * pElement) \
	{ \
		CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR), \
		unsigned char * vElement = (unsigned char *) CRX__ALLOCA(sizeof(pELEMENT_TYPE));, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_COPY_CONSTRUCTOR(((pELEMENT_TYPE *)vElement), pElement); \
			pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundPush(pThis, ((pELEMENT_TYPE *)vElement)); \
		) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				memcpy(vElement, pElement, sizeof(pELEMENT_TYPE)); \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundPush(pThis, ((pELEMENT_TYPE *)vElement)); \
			) \
			( \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundPush(pThis, ((pELEMENT_TYPE *)pElement)); \
			) \
		) \
	\
		CRXM__IFELSE2(CRXM__AND(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
						CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR)), \
				pFUNC_ELEMENT_MOVE_DESTRUCTOR(((pELEMENT_TYPE *)vElement));, ) \
	}, ) \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastPush2(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE pElement) \
	{ \
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPush(pThis, &pElement); \
	}, ) \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundPush2(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE pElement) \
	{ \
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundPush(pThis, &pElement); \
	}, ) \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## pop(pARRAY_TYPE_NAME * pThis) \
	{ \
		assert(pThis->gPrivate_length > 0); \
	\
		pThis->gPrivate_length--; \
	\
		CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
				pFUNC_ELEMENT_DESTRUCTOR(pThis->gBuffer + ((pThis->gPrivate_startIndex + pThis->gPrivate_length) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)));, ) \
	} \
	\
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPushToFront(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE * pElement) \
	{ \
		assert(pTHIS_SIZE_OF_INTERNAL_BUFFER > pThis->gPrivate_length); \
	\
		if(pThis->gPrivate_startIndex == 0) \
			{pThis->gPrivate_startIndex = pTHIS_SIZE_OF_INTERNAL_BUFFER - 1;} \
		else \
			{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex - 1;} \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gBuffer + (pThis->gPrivate_startIndex & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), pElement); \
		) \
		( \
			memcpy(pThis->gBuffer + (pThis->gPrivate_startIndex & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), pElement, sizeof(pELEMENT_TYPE)); \
		) \
	\
		pThis->gPrivate_length = pThis->gPrivate_length + 1; \
	} \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastPushToFront(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE const * pElement) \
	{ \
		CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR), \
		unsigned char * vElement = (unsigned char *) CRX__ALLOCA(sizeof(pELEMENT_TYPE));, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_COPY_CONSTRUCTOR(((pELEMENT_TYPE *)vElement), pElement); \
			pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPushToFront(pThis, ((pELEMENT_TYPE *)vElement)); \
		) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				memcpy(vElement, pElement, sizeof(pELEMENT_TYPE)); \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPushToFront(pThis, ((pELEMENT_TYPE *)vElement)); \
			) \
			( \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPushToFront(pThis, ((pELEMENT_TYPE *)pElement)); \
			) \
		) \
	\
		CRXM__IFELSE2(CRXM__AND(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
						CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR)), \
				pFUNC_ELEMENT_MOVE_DESTRUCTOR(((pELEMENT_TYPE *)vElement));, ) \
	}, ) \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundPushToFront(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE * pElement) \
	{ \
		if(pThis->gPrivate_startIndex == 0) \
		{ \
			pThis->gPrivate_startIndex = pTHIS_SIZE_OF_INTERNAL_BUFFER - 1; \
		} \
		else \
			{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex - 1;} \
	\
		CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
		if(pThis->gPrivate_length == pTHIS_SIZE_OF_INTERNAL_BUFFER) \
		{ \
			pFUNC_ELEMENT_DESTRUCTOR(pThis->gBuffer + (pThis->gPrivate_startIndex & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
		}, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gBuffer + (pThis->gPrivate_startIndex & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), pElement); \
		) \
		( \
			memcpy(pThis->gBuffer + (pThis->gPrivate_startIndex & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), pElement, sizeof(pELEMENT_TYPE)); \
		) \
	\
		if(pThis->gPrivate_length != pTHIS_SIZE_OF_INTERNAL_BUFFER) \
			{pThis->gPrivate_length = pThis->gPrivate_length + 1;} \
	} \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundPushToFront(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE const * pElement) \
	{ \
		CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR), \
		unsigned char * vElement = (unsigned char *) CRX__ALLOCA(sizeof(pELEMENT_TYPE));, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_COPY_CONSTRUCTOR(((pELEMENT_TYPE *)vElement), pElement); \
			pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundPushToFront(pThis, ((pELEMENT_TYPE *)vElement)); \
		) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				memcpy(vElement, pElement, sizeof(pELEMENT_TYPE)); \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundPushToFront(pThis, ((pELEMENT_TYPE *)vElement)); \
			) \
			( \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundPushToFront(pThis, ((pELEMENT_TYPE *)pElement)); \
			) \
		) \
	\
		CRXM__IFELSE2(CRXM__AND(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
						CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR)), \
				pFUNC_ELEMENT_MOVE_DESTRUCTOR(((pELEMENT_TYPE *)vElement));, ) \
	}, ) \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastPushToFront2(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE pElement) \
	{ \
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPushToFront(pThis, &pElement); \
	}, ) \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundPushToFront2(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE pElement) \
	{ \
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundPushToFront(pThis, &pElement); \
	}, ) \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## popFromFront(pARRAY_TYPE_NAME * pThis) \
	{ \
		assert(pThis->gPrivate_length > 0); \
	\
		size_t vIndexOfReturn = pThis->gPrivate_startIndex; \
	\
		pThis->gPrivate_length--; \
	\
		if(pThis->gPrivate_startIndex == pTHIS_SIZE_OF_INTERNAL_BUFFER - 1) \
			{pThis->gPrivate_startIndex = 0;} \
		else \
			{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex - 1;} \
	\
		CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
				pFUNC_ELEMENT_DESTRUCTOR(pThis->gBuffer + (vIndexOfReturn & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)));, ) \
	} \
	\
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastInsertElementAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE * pElement) \
	{ \
		assert(pIndex <= pSIZE_T_MAX); \
	\
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pThis, pIndex, 1);\
	\
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gBuffer + ((pThis->gPrivate_startIndex + pIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), pElement); \
		) \
		( \
			memcpy(pThis->gBuffer + ((pThis->gPrivate_startIndex + pIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), pElement, sizeof(pELEMENT_TYPE)); \
		) \
	} \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pElement) \
	{ \
		CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR), \
		unsigned char * vElement = (unsigned char *) CRX__ALLOCA(sizeof(pELEMENT_TYPE));, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_COPY_CONSTRUCTOR(((pELEMENT_TYPE *)vElement), pElement); \
			pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastInsertElementAt(pThis, pIndex, ((pELEMENT_TYPE *)vElement)); \
		) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				memcpy(vElement, pElement, sizeof(pELEMENT_TYPE)); \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastInsertElementAt(pThis, pIndex, ((pELEMENT_TYPE *)vElement)); \
			) \
			( \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastInsertElementAt(pThis, pIndex, ((pELEMENT_TYPE *)pElement)); \
			) \
		) \
	\
		CRXM__IFELSE2(CRXM__AND(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
						CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR)), \
				pFUNC_ELEMENT_MOVE_DESTRUCTOR(((pELEMENT_TYPE *)vElement));, ) \
	}, ) \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundInsertElementAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE * pElement) \
	{ \
		assert(pIndex <= pSIZE_T_MAX); \
	\
		Crx_C_FixedRing_Private_IndexTransform vIndexTransform = \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_roundInsertSpaceAt(pThis, pIndex, 1); \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gBuffer + ((pThis->gPrivate_startIndex + vIndexTransform.gNewIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), pElement); \
		) \
		( \
			memcpy(pThis->gBuffer + ((pThis->gPrivate_startIndex + vIndexTransform.gNewIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), pElement, sizeof(pELEMENT_TYPE)); \
		) \
	} \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundInsertElementAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pElement) \
	{ \
		CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR), \
		unsigned char * vElement = (unsigned char *) CRX__ALLOCA(sizeof(pELEMENT_TYPE));, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_COPY_CONSTRUCTOR(((pELEMENT_TYPE *)vElement), pElement); \
			pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundInsertElementAt(pThis, pIndex, ((pELEMENT_TYPE *)vElement)); \
		) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				memcpy(vElement, pElement, sizeof(pELEMENT_TYPE)); \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundInsertElementAt(pThis, pIndex, ((pELEMENT_TYPE *)vElement)); \
			) \
			( \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundInsertElementAt(pThis, pIndex, ((pELEMENT_TYPE *)pElement)); \
			) \
		) \
	\
		CRXM__IFELSE2(CRXM__AND(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
						CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR)), \
				pFUNC_ELEMENT_MOVE_DESTRUCTOR(((pELEMENT_TYPE *)vElement));, ) \
	}, ) \
	\
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementAt2(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE pElement) \
		{pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastInsertElementAt(pThis, pIndex, &pElement);}, ) \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundInsertElementAt2(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE pElement) \
		{pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndRoundInsertElementAt(pThis, pIndex, &pElement);}, ) \
	\
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementsAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pARRAY_TYPE_NAME const * pArray, size_t pStartIndex, size_t pWidth) \
	{ \
		assert(pIndex <= pSIZE_T_MAX); \
		assert(pStartIndex <= pSIZE_T_MAX); \
		assert(pWidth <= pSIZE_T_MAX); \
		assert(!CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis, pArray, false)); \
	\
		if(pWidth == 0) \
			{return;} \
	\
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pThis, pIndex, pWidth);\
	\
		CRX__C__FIXED_RING__ECHO__COPY_FROM_RING_RANGE(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pELEMENT_TYPE, pThis->gBuffer, pThis->gPrivate_startIndex, \
				pTHIS_SIZE_OF_INTERNAL_BUFFER, pIndex, pArray->gBuffer, pArray->gPrivate_startIndex, \
				CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pArray, \
				pDEFAULT_SIZE_OF_INTERNAL_BUFFER), \
				pStartIndex, pWidth) \
	}, ) \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundInsertElementsAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pARRAY_TYPE_NAME const * pArray, size_t pStartIndex, size_t pWidth) \
	{ \
		CRX_SCOPE_META \
		assert(pIndex <= pSIZE_T_MAX); \
		assert(pStartIndex <= pSIZE_T_MAX); \
		assert(pWidth <= pSIZE_T_MAX); \
		assert(!CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis, pArray, false)); \
	\
		if(pWidth == 0) \
			{return;} \
	\
		CRX_SCOPE \
		Crx_C_FixedRing_Private_IndexTransform vIndexTransform = \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_roundInsertSpaceAt(pThis, pIndex, pWidth);\
	\
		CRX__C__FIXED_RING__ECHO__COPY_FROM_RING_RANGE(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pELEMENT_TYPE, pThis->gBuffer, pThis->gPrivate_startIndex, \
				pTHIS_SIZE_OF_INTERNAL_BUFFER, vIndexTransform.gNewIndex, pArray->gBuffer, pArray->gPrivate_startIndex, \
				CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pArray, \
				pDEFAULT_SIZE_OF_INTERNAL_BUFFER), \
				pStartIndex, vIndexTransform.gNewCountToEnd) \
		CRX_SCOPE_END \
	}, ) \
	\
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertCArrayAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pArray, size_t pWidth) \
	{ \
		CRX_SCOPE_META \
		assert(pIndex <= pSIZE_T_MAX); \
		assert(pWidth <= pSIZE_T_MAX); \
	\
		if(pWidth == 0) \
			{return;} \
	\
		CRX_SCOPE \
		CRXM__IFELSE2(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
		size_t vInsertIndex;, ) \
	\
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pThis, pIndex, pWidth);\
	\
		CRXM__IFELSE2(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
		vInsertIndex = (pThis->gPrivate_startIndex + pIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1);, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
			{ \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(pThis->gBuffer + ((pThis->gPrivate_startIndex + pIndex + tI) & \
							(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
						pArray + tI); \
			} \
			CRX_ENDFOR \
		) \
		( \
			if((vInsertIndex < ((pThis->gPrivate_startIndex + pIndex + pWidth - 1) & \
					(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))) || \
					((pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex) >= pWidth)) \
				{memcpy(pThis->gBuffer + vInsertIndex, pArray, pWidth * sizeof(pELEMENT_TYPE));} \
			else \
			{ \
				memcpy(pThis->gBuffer + vInsertIndex, pArray, \
						(pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex) * sizeof(pELEMENT_TYPE)); \
				memcpy(pThis->gBuffer, pArray + pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex, \
						(pWidth - (pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex)) * sizeof(pELEMENT_TYPE)); \
			} \
		) \
		CRX_SCOPE_END \
	}, ) \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundInsertCArrayAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pArray, size_t pWidth) \
	{ \
		CRX_SCOPE_META \
		assert(pIndex <= pSIZE_T_MAX); \
		assert(pWidth <= pSIZE_T_MAX); \
	\
		if(pWidth == 0) \
			{return;} \
	\
		CRX_SCOPE \
		Crx_C_FixedRing_Private_IndexTransform vIndexTransform = \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_roundInsertSpaceAt(pThis, pIndex, pWidth);\
		CRXM__IFELSE2(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
		size_t vInsertIndex = (pThis->gPrivate_startIndex + vIndexTransform.gNewIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1);, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < vIndexTransform.gNewCountToEnd, tI++) \
			{ \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(pThis->gBuffer + \
								((pThis->gPrivate_startIndex + vIndexTransform.gNewIndex + tI) & \
								(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
						pArray + tI); \
			} \
			CRX_ENDFOR \
		) \
		( \
			if((vInsertIndex < ((pThis->gPrivate_startIndex + vIndexTransform.gNewIndex + \
							vIndexTransform.gNewCountToEnd - 1) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))) || \
					((pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex) >= vIndexTransform.gNewCountToEnd)) \
			{ \
				memcpy(pThis->gBuffer + vInsertIndex, pArray, \
						vIndexTransform.gNewCountToEnd * sizeof(pELEMENT_TYPE)); \
			} \
			else \
			{ \
				memcpy(pThis->gBuffer + vInsertIndex, pArray, \
						(pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex) * sizeof(pELEMENT_TYPE)); \
				memcpy(pThis->gBuffer, pArray + pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex, \
						(vIndexTransform.gNewCountToEnd - (pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex)) * sizeof(pELEMENT_TYPE)); \
			} \
		) \
		CRX_SCOPE_END \
	}, ) \
	\
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementCopiesAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pElement, size_t pNumberOfCopies) \
	{ \
		CRX_SCOPE_META \
		assert(pIndex <= pSIZE_T_MAX); \
		assert(pNumberOfCopies <= pSIZE_T_MAX); \
	\
		if(pNumberOfCopies == 0) \
			{return;} \
	\
		CRX_SCOPE \
		CRXM__IFELSE2(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
		size_t vInsertIndex = (pThis->gPrivate_startIndex + pIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1);, ) \
	\
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pThis, pIndex, pNumberOfCopies); \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < pNumberOfCopies, tI++) \
			{ \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(pThis->gBuffer + ((pThis->gPrivate_startIndex + pIndex + tI) & \
						(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
						pElement); \
			} \
			CRX_ENDFOR \
		) \
		( \
			if((vInsertIndex < ((pThis->gPrivate_startIndex + pIndex + pNumberOfCopies - 1) & \
					(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))) || \
					((pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex) >= pNumberOfCopies)) \
			{ \
				size_t tNumberOfCopies = 1; \
				size_t tRemainingNumberOfCopies = pNumberOfCopies - 1; \
	\
				memcpy(pThis->gBuffer + vInsertIndex, pElement, sizeof(pELEMENT_TYPE));\
	\
				while(tRemainingNumberOfCopies > 0) \
				{ \
					if(tRemainingNumberOfCopies >= tNumberOfCopies) \
					{ \
						memcpy(pThis->gBuffer + vInsertIndex + tNumberOfCopies, pThis->gBuffer + vInsertIndex, \
								tNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
						tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies; \
						tNumberOfCopies = (tNumberOfCopies << 1); \
					} \
					else \
					{ \
						memcpy(pThis->gBuffer + vInsertIndex + tNumberOfCopies, pThis->gBuffer + vInsertIndex, \
								tRemainingNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
						break; \
					} \
				} \
			} \
			else \
			{ \
				size_t tNumberOfCopies = 1; \
				size_t tRemainingNumberOfCopies = pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex - 1; \
	\
				memcpy(pThis->gBuffer + vInsertIndex, pElement, sizeof(pELEMENT_TYPE));\
	\
				while(tRemainingNumberOfCopies > 0) \
				{ \
					if(tRemainingNumberOfCopies >= tNumberOfCopies) \
					{ \
						memcpy(pThis->gBuffer + vInsertIndex + tNumberOfCopies, pThis->gBuffer + vInsertIndex, \
								tNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
						tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies; \
						tNumberOfCopies = (tNumberOfCopies << 1); \
					} \
					else \
					{ \
						memcpy(pThis->gBuffer + vInsertIndex + tNumberOfCopies, pThis->gBuffer + vInsertIndex, \
								tRemainingNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
						break; \
					} \
				} \
	\
				tRemainingNumberOfCopies = pNumberOfCopies - (pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex); \
	\
				if(tRemainingNumberOfCopies > pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex) \
				{ \
					tNumberOfCopies = pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex; \
	\
					memcpy(pThis->gBuffer, pThis->gBuffer + vInsertIndex, tNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
					tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies; \
	\
					while(tRemainingNumberOfCopies > 0) \
					{ \
						if(tRemainingNumberOfCopies >= tNumberOfCopies) \
						{ \
							memcpy(pThis->gBuffer + tNumberOfCopies, pThis->gBuffer, tNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
							tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies; \
							tNumberOfCopies = (tNumberOfCopies << 1); \
						} \
						else \
						{ \
							memcpy(pThis->gBuffer + tNumberOfCopies, pThis->gBuffer, tRemainingNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
							break; \
						} \
					} \
				} \
				else \
					{memcpy(pThis->gBuffer, pThis->gBuffer + vInsertIndex, tRemainingNumberOfCopies * sizeof(pELEMENT_TYPE));} \
	\
			} \
		) \
		CRX_SCOPE_END \
	}, ) \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundInsertElementCopiesAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pElement, size_t pNumberOfCopies) \
	{ \
		CRX_SCOPE_META \
		assert(pIndex <= pSIZE_T_MAX); \
		assert(pNumberOfCopies <= pSIZE_T_MAX); \
	\
		if(pNumberOfCopies == 0) \
			{return;} \
	\
		CRX_SCOPE \
		Crx_C_FixedRing_Private_IndexTransform vIndexTransform = \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_roundInsertSpaceAt(pThis, pIndex, pNumberOfCopies); \
		CRXM__IFELSE2(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
		size_t tInsertIndex = (pThis->gPrivate_startIndex + vIndexTransform.gNewIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1);, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < vIndexTransform.gNewCountToEnd, tI++) \
			{ \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(pThis->gBuffer + \
								((pThis->gPrivate_startIndex + vIndexTransform.gNewIndex + tI) & \
						(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
						pElement); \
			} \
			CRX_ENDFOR \
		) \
		( \
			if((tInsertIndex < ((pThis->gPrivate_startIndex + vIndexTransform.gNewIndex + vIndexTransform.gNewCountToEnd - 1) & \
					(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))) || \
					((pTHIS_SIZE_OF_INTERNAL_BUFFER - tInsertIndex) >= vIndexTransform.gNewCountToEnd)) \
			{ \
				size_t tNumberOfCopies = 1; \
				size_t tRemainingNumberOfCopies = vIndexTransform.gNewCountToEnd - 1; \
	\
				memcpy(pThis->gBuffer + tInsertIndex, pElement, sizeof(pELEMENT_TYPE));\
	\
				while(tRemainingNumberOfCopies > 0) \
				{ \
					if(tRemainingNumberOfCopies >= tNumberOfCopies) \
					{ \
						memcpy(pThis->gBuffer + tInsertIndex + tNumberOfCopies, pThis->gBuffer + tInsertIndex, \
								tNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
						tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies; \
						tNumberOfCopies = (tNumberOfCopies << 1); \
					} \
					else \
					{ \
						memcpy(pThis->gBuffer + tInsertIndex + tNumberOfCopies, pThis->gBuffer + tInsertIndex, \
								tRemainingNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
						break; \
					} \
				} \
			} \
			else \
			{ \
				size_t tNumberOfCopies = 1; \
				size_t tRemainingNumberOfCopies = pTHIS_SIZE_OF_INTERNAL_BUFFER - tInsertIndex - 1; \
	\
				memcpy(pThis->gBuffer + tInsertIndex, pElement, sizeof(pELEMENT_TYPE));\
	\
				while(tRemainingNumberOfCopies > 0) \
				{ \
					if(tRemainingNumberOfCopies >= tNumberOfCopies) \
					{ \
						memcpy(pThis->gBuffer + tInsertIndex + tNumberOfCopies, pThis->gBuffer + tInsertIndex, \
								tNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
						tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies; \
						tNumberOfCopies = (tNumberOfCopies << 1); \
					} \
					else \
					{ \
						memcpy(pThis->gBuffer + tInsertIndex + tNumberOfCopies, pThis->gBuffer + tInsertIndex, \
								tRemainingNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
						break; \
					} \
				} \
	\
				tRemainingNumberOfCopies = vIndexTransform.gNewCountToEnd - \
						(pTHIS_SIZE_OF_INTERNAL_BUFFER - tInsertIndex); \
	\
				if(tRemainingNumberOfCopies > pTHIS_SIZE_OF_INTERNAL_BUFFER - tInsertIndex) \
				{ \
					tNumberOfCopies = pTHIS_SIZE_OF_INTERNAL_BUFFER - tInsertIndex; \
	\
					memcpy(pThis->gBuffer, pThis->gBuffer + tInsertIndex, tNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
					tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies; \
	\
					while(tRemainingNumberOfCopies > 0) \
					{ \
						if(tRemainingNumberOfCopies >= tNumberOfCopies) \
						{ \
							memcpy(pThis->gBuffer + tNumberOfCopies, pThis->gBuffer, \
									tNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
							tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies; \
							tNumberOfCopies = (tNumberOfCopies << 1); \
						} \
						else \
						{ \
							memcpy(pThis->gBuffer + tNumberOfCopies, pThis->gBuffer, \
									tRemainingNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
							break; \
						} \
					} \
				} \
				else \
					{memcpy(pThis->gBuffer, pThis->gBuffer + tInsertIndex, tRemainingNumberOfCopies * sizeof(pELEMENT_TYPE));} \
	\
			} \
		) \
		CRX_SCOPE_END \
	}, ) \
	\
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementCopiesAt2(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE pElement, size_t pNumberOfCopies) \
	{ \
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementCopiesAt(pThis, pIndex, &pElement, pNumberOfCopies); \
	}, ) \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundInsertElementCopiesAt2(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE pElement, size_t pNumberOfCopies) \
	{ \
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## roundInsertElementCopiesAt(pThis, pIndex, &pElement, pNumberOfCopies); \
	}, ) \
	\
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## removeElements(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			size_t pWidth) \
	{ \
		assert((pWidth == 0) || ((pIndex < pThis->gPrivate_length) && (pIndex + pWidth <= pThis->gPrivate_length))); \
	\
		if(pWidth == 0) \
			{return;} \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_DESTRUCTOR) \
		( \
			pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct(pThis, pIndex, \
					(((pIndex + pWidth) <= pThis->gPrivate_length) ? (pIndex + pWidth - 1) : pThis->gPrivate_length - 1)); \
		)() \
	\
		CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR)) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				if((pThis->gPrivate_length >> 1) < pIndex) \
				{ \
					CRX_FOR(size_t tI = 0, tI < pIndex, tI++) \
					{ \
						pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gBuffer + \
										((pThis->gPrivate_startIndex + pIndex + pWidth - 1 - tI) & \
										(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
								pThis->gBuffer + ((pThis->gPrivate_startIndex + pIndex - 1 - tI) & \
										(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
		\
						CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
								pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gBuffer + \
								((pThis->gPrivate_startIndex + pIndex - 1 - tI) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)));, ) \
					} \
					CRX_ENDFOR \
		\
					pThis->gPrivate_startIndex = ((pSIZE_T)((pThis->gPrivate_startIndex + pWidth) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
				} \
				else \
				{ \
					CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length - pWidth - pIndex, tI++) \
					{ \
						pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gBuffer + \
										((pThis->gPrivate_startIndex + tI + pIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
								pThis->gBuffer + ((pThis->gPrivate_startIndex + tI + pIndex + pWidth) & \
										(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
		\
						CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
								pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gBuffer + \
								((pThis->gPrivate_startIndex + tI + pIndex + pWidth) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)));, ) \
					} \
					CRX_ENDFOR \
				} \
			) \
			( \
				if((pThis->gPrivate_length >> 1) < pIndex) \
				{ \
					CRX_FOR(size_t tI = 0, tI < pIndex, tI++) \
					{ \
						memmove(pThis->gBuffer + ((pThis->gPrivate_startIndex + pIndex + pWidth - 1 - tI) & \
										(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
								pThis->gBuffer + ((pThis->gPrivate_startIndex + pIndex - 1 - tI) & \
										(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
								sizeof(pELEMENT_TYPE)); \
		\
						pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gBuffer + \
								((pThis->gPrivate_startIndex + pIndex - 1 - tI) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
					} \
					CRX_ENDFOR \
		\
					pThis->gPrivate_startIndex = ((pSIZE_T)((pThis->gPrivate_startIndex + pWidth) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
				} \
				else \
				{ \
					CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length - pWidth - pIndex, tI++) \
					{ \
						memmove(pThis->gBuffer + ((pThis->gPrivate_startIndex + tI + pIndex) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
								pThis->gBuffer + ((pThis->gPrivate_startIndex + tI + pIndex + pWidth) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
								sizeof(pELEMENT_TYPE)); \
	\
						pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gBuffer + \
								((pThis->gPrivate_startIndex + tI + pIndex + pWidth) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
					} \
					CRX_ENDFOR \
				} \
			) \
		) \
		( \
			if((pThis->gPrivate_length >> 1) < pIndex) \
			{ \
				CRX__C__RING__ECHO__RAW_ROTATE_RIGHT(pELEMENT_TYPE, pThis->gBuffer, \
						pThis->gPrivate_startIndex, ((pThis->gPrivate_startIndex + pIndex - 1) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
						pTHIS_SIZE_OF_INTERNAL_BUFFER, pWidth, CRXM__FALSE) \
	\
				pThis->gPrivate_startIndex = ((pSIZE_T)((pThis->gPrivate_startIndex + pWidth) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
			} \
			else \
			{ \
				CRX__C__RING__ECHO__RAW_ROTATE_LEFT(pELEMENT_TYPE, pThis->gBuffer, \
						((pThis->gPrivate_startIndex + pIndex + pWidth) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
						((pThis->gPrivate_startIndex + pThis->gPrivate_length - 1) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
						pTHIS_SIZE_OF_INTERNAL_BUFFER, pWidth, CRXM__FALSE) \
			} \
		) \
	\
		pThis->gPrivate_length = ((pSIZE_T)(pThis->gPrivate_length - pWidth)); \
	} \
	\
	PUBLIC pELEMENT_TYPE * pARRAY_MEMBER_FUNCTIONS_PREFIX ## getElementsPointer(pARRAY_TYPE_NAME * pThis) \
	{ \
		if(pThis->gPrivate_startIndex == 0) \
			{return pThis->gBuffer;} \
		else if(pThis->gPrivate_startIndex <= ((pThis->gPrivate_startIndex + pThis->gPrivate_length - 1) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))) \
			{return pThis->gBuffer + pThis->gPrivate_startIndex;} \
		else \
		{ \
			pELEMENT_TYPE CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
					* tElements = CRX__ALLOCA(pThis->gSIZE_OF_INTERNAL_BUFFER),  \
					tElements[pDEFAULT_SIZE_OF_INTERNAL_BUFFER]); \
	\
			CRXM__IFELSE2(pHAS_ALIGN_FACTOR, \
			pSIZE_T tStartIndex = 0;, )\
	\
			CRX__C__FixedRing__DEFINE___SET_TO_ALIGN_FACTOR(pTHIS_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, \
					pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pThis, tStartIndex) \
	\
			CRXM__IFELSE2(pHAS_ALIGN_FACTOR, \
			if(pTHIS_SIZE_OF_INTERNAL_BUFFER - tStartIndex < pThis->gPrivate_length) \
			{ \
				tStartIndex = (pTHIS_SIZE_OF_INTERNAL_BUFFER >> 1); \
	\
				if(pTHIS_SIZE_OF_INTERNAL_BUFFER - tStartIndex < pThis->gPrivate_length) \
					{tStartIndex = 0;} \
			}, ) \
	\
			pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_moveElements(pThis->gBuffer, pThis->gPrivate_startIndex, \
					pThis->gPrivate_length, pTHIS_SIZE_OF_INTERNAL_BUFFER, tElements); \
			pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_moveElements(tElements, 0, \
					pThis->gPrivate_length, pTHIS_SIZE_OF_INTERNAL_BUFFER, \
					pThis->gBuffer CRXM__IFELSE2(pHAS_ALIGN_FACTOR, + tStartIndex, )); \
			pThis->gPrivate_startIndex = 0 CRXM__IFELSE2(pHAS_ALIGN_FACTOR, + tStartIndex, ); \
	\
			return pThis->gBuffer; \
		} \
	} \
	PUBLIC pELEMENT_TYPE const * pARRAY_MEMBER_FUNCTIONS_PREFIX ## constantGetElementsPointer(pARRAY_TYPE_NAME const * pThis) \
		{return pARRAY_MEMBER_FUNCTIONS_PREFIX ## getElementsPointer((pARRAY_TYPE_NAME *) pThis);}
//#END_DEFINE


#define CRX__C__FixedRing__DEFINE___SET_TO_ALIGN_FACTOR(pTHIS_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, pSTART_INDEX_DEFAULT_ALIGN_FACTOR, pTHIS, T) \
		CRXM__IFELSE(CRXM__OR(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD, pSTART_INDEX_DEFAULT_ALIGN_FACTOR)) \
	( \
		CRXM__IFELSE(pIS_TO_ENABLE_ALIGN_FACTOR_FIELD) \
		( \
			if(pTHIS->gPrivate_startIndexAlignFactor > 0) \
			{ \
				T = (pTHIS_SIZE_OF_INTERNAL_BUFFER >> pTHIS->gPrivate_startIndexAlignFactor); \
			} \
			else \
			{ \
				T = pTHIS_SIZE_OF_INTERNAL_BUFFER - \
						(pTHIS_SIZE_OF_INTERNAL_BUFFER >> abs(pTHIS->gPrivate_startIndexAlignFactor)); \
			} \
		) \
		( \
			if(pSTART_INDEX_DEFAULT_ALIGN_FACTOR > 0) \
			{ \
				T = (pTHIS_SIZE_OF_INTERNAL_BUFFER >> pSTART_INDEX_DEFAULT_ALIGN_FACTOR); \
			} \
			else \
			{ \
				T = pTHIS_SIZE_OF_INTERNAL_BUFFER - \
						(pTHIS_SIZE_OF_INTERNAL_BUFFER >> abs(pSTART_INDEX_DEFAULT_ALIGN_FACTOR)); \
			} \
		) \
	)()
//#END_DEFINE
		
/*#define pTHIS_SIZE_OF_INTERNAL_BUFFER \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pTHIS->gSIZE_OF_INTERNAL_BUFFER, pSIZE_OF_INTERNAL_BUFFER)*/
#define CRX__C__FixedRing__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pTHIS, \
				pDEFAULT_SIZE_OF_INTERNAL_BUFFER) \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pTHIS->gSIZE_OF_INTERNAL_BUFFER, pDEFAULT_SIZE_OF_INTERNAL_BUFFER)
		
		
/*
WARNING:
	- It is assumed that there is sufficient space left for the insertion, otherwise the behavior is undefined.
	- It is assumed that the capacity is smaller than half the largest size_t value representable by the machine.
*/
#define CRX__C__FixedRing__ECHO_INSERT_SPACE_AT(pSIZE_T, pELEMENT_TYPE, pTHIS_SIZE_OF_INTERNAL_BUFFER, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, pTHIS, pINDEX, pWIDTH) \
	{ \
		assert(pWIDTH <= (pTHIS_SIZE_OF_INTERNAL_BUFFER - pTHIS->gPrivate_length)); \
	\
		if(pINDEX == 0) \
		{ \
			if(pTHIS->gPrivate_startIndex > pWIDTH) \
				{pTHIS->gPrivate_startIndex = ((pSIZE_T)(pTHIS->gPrivate_startIndex - pWIDTH));} \
			else \
				{pTHIS->gPrivate_startIndex = ((pSIZE_T)(pTHIS_SIZE_OF_INTERNAL_BUFFER - (pWIDTH - pTHIS->gPrivate_startIndex)));} \
		} \
		else if(pINDEX == pTHIS->gPrivate_length) \
			{} \
		else \
		{ \
			size_t vInsertIndex = (pTHIS->gPrivate_startIndex + pINDEX) & \
					(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1); \
	\
			assert(vInsertIndex != pTHIS->gPrivate_startIndex); \
	\
			CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR)) \
			( \
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
				( \
					CRX_FOR(size_t tI = pTHIS->gPrivate_length - 1, tI >= pINDEX, tI--) \
					{ \
						pFUNC_ELEMENT_MOVE_CONSTRUCTOR( \
								pTHIS->gBuffer + ((pTHIS->gPrivate_startIndex + tI + pWIDTH) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
								pTHIS->gBuffer + ((pTHIS->gPrivate_startIndex + tI) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1))); \
	\
						CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
						pFUNC_ELEMENT_MOVE_DESTRUCTOR(pTHIS->gBuffer + \
								((pTHIS->gPrivate_startIndex + tI) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)));, ) \
					} \
					CRX_ENDFOR \
				) \
				( \
					/*THIS CODE IS NOT OPTIMAL.*/ \
					CRX_FOR(size_t tI = pTHIS->gPrivate_length - 1, tI >= pINDEX, tI--) \
					{ \
						memmove(pTHIS->gBuffer + ((pTHIS->gPrivate_startIndex + tI + pWIDTH) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
								pTHIS->gBuffer + ((pTHIS->gPrivate_startIndex + tI) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1)), \
								sizeof(pELEMENT_TYPE)); \
	\
						pFUNC_ELEMENT_MOVE_DESTRUCTOR(pTHIS->gBuffer + \
								((pTHIS->gPrivate_startIndex + tI) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1));, ) \
					} \
					CRX_ENDFOR \
				) \
			) \
			( \
				if((pTHIS->gPrivate_length >> 1) >= pINDEX) \
				{ \
					if(pTHIS->gPrivate_startIndex >= pWIDTH) \
					{ \
						if(pTHIS->gPrivate_startIndex + 1 <= vInsertIndex) \
						{ \
							memmove(pTHIS->gBuffer + pTHIS->gPrivate_startIndex - pWIDTH, \
									pTHIS->gBuffer + pTHIS->gPrivate_startIndex, (vInsertIndex - pTHIS->gPrivate_startIndex) * sizeof(pELEMENT_TYPE)); \
						} \
						else \
						{ \
							memmove(pTHIS->gBuffer + pTHIS->gPrivate_startIndex - pWIDTH, \
									pTHIS->gBuffer + pTHIS->gPrivate_startIndex, (pTHIS_SIZE_OF_INTERNAL_BUFFER - pTHIS->gPrivate_startIndex) * sizeof(pELEMENT_TYPE)); \
		\
							if(vInsertIndex <= pWIDTH) \
							{ \
								memmove(pTHIS->gBuffer + pTHIS_SIZE_OF_INTERNAL_BUFFER - pWIDTH, \
										pTHIS->gBuffer, vInsertIndex * sizeof(pELEMENT_TYPE)); \
							} \
							else \
							{ \
								memmove(pTHIS->gBuffer + pTHIS_SIZE_OF_INTERNAL_BUFFER - pWIDTH, \
										pTHIS->gBuffer, pWIDTH * sizeof(pELEMENT_TYPE)); \
								memmove(pTHIS->gBuffer, \
										pTHIS->gBuffer + pWIDTH, \
										(vInsertIndex - pWIDTH) * sizeof(pELEMENT_TYPE)); \
							} \
						} \
		\
						pTHIS->gPrivate_startIndex = ((pSIZE_T)(pTHIS->gPrivate_startIndex - pWIDTH)); \
					} \
					else \
					{ \
						if(pWIDTH < vInsertIndex) \
						{ \
							memmove(pTHIS->gBuffer + pTHIS_SIZE_OF_INTERNAL_BUFFER - (pWIDTH - pTHIS->gPrivate_startIndex), \
									pTHIS->gBuffer + pTHIS->gPrivate_startIndex, \
									(pWIDTH - pTHIS->gPrivate_startIndex) * sizeof(pELEMENT_TYPE)); \
							memmove(pTHIS->gBuffer, pTHIS->gBuffer + pWIDTH, \
									(vInsertIndex - pWIDTH) * sizeof(pELEMENT_TYPE)); \
						} \
						else \
						{ \
							memmove(pTHIS->gBuffer + pTHIS_SIZE_OF_INTERNAL_BUFFER - (pWIDTH - pTHIS->gPrivate_startIndex), \
									pTHIS->gBuffer + pTHIS->gPrivate_startIndex, \
									(vInsertIndex - pTHIS->gPrivate_startIndex) * sizeof(pELEMENT_TYPE)); \
						} \
						pTHIS->gPrivate_startIndex = ((pSIZE_T)(pTHIS_SIZE_OF_INTERNAL_BUFFER - (pWIDTH - pTHIS->gPrivate_startIndex))); \
					} \
				} \
				else \
				{ \
					size_t tEndIndex = (pTHIS->gPrivate_startIndex + pTHIS->gPrivate_length - 1) & (pTHIS_SIZE_OF_INTERNAL_BUFFER - 1); \
		\
					if(pTHIS_SIZE_OF_INTERNAL_BUFFER - 1 - tEndIndex >= pWIDTH) \
					{ \
						if(tEndIndex + 1 >= vInsertIndex) \
						{ \
							memmove(pTHIS->gBuffer + vInsertIndex + pWIDTH, \
									pTHIS->gBuffer + vInsertIndex, \
									(tEndIndex  + 1 - vInsertIndex) * sizeof(pELEMENT_TYPE)); \
						} \
						else \
						{ \
							memmove(pTHIS->gBuffer + pWIDTH, pTHIS->gBuffer, (tEndIndex + 1) * sizeof(pELEMENT_TYPE)); \
		\
							if(pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex <= pWIDTH) \
							{ \
								memmove(pTHIS->gBuffer + pWIDTH - (pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex), \
										pTHIS->gBuffer + vInsertIndex, \
										(pTHIS_SIZE_OF_INTERNAL_BUFFER - vInsertIndex) * sizeof(pELEMENT_TYPE)); \
							} \
							else \
							{ \
								memmove(pTHIS->gBuffer, pTHIS->gBuffer + pTHIS_SIZE_OF_INTERNAL_BUFFER - pWIDTH, \
										pWIDTH * sizeof(pELEMENT_TYPE)); \
								memmove(pTHIS->gBuffer + vInsertIndex + pWIDTH, pTHIS->gBuffer + vInsertIndex, \
										(pTHIS_SIZE_OF_INTERNAL_BUFFER - pWIDTH - vInsertIndex) * sizeof(pELEMENT_TYPE)); \
							} \
						} \
					} \
					else \
					{ \
						if(pTHIS_SIZE_OF_INTERNAL_BUFFER - pWIDTH > vInsertIndex) \
						{ \
							memmove(pTHIS->gBuffer, pTHIS->gBuffer + pTHIS_SIZE_OF_INTERNAL_BUFFER - pWIDTH, \
									(tEndIndex + pWIDTH + 1 - pTHIS_SIZE_OF_INTERNAL_BUFFER) * sizeof(pELEMENT_TYPE)); \
							memmove(pTHIS->gBuffer + vInsertIndex + pWIDTH, pTHIS->gBuffer + vInsertIndex, \
									(pTHIS_SIZE_OF_INTERNAL_BUFFER - pWIDTH - vInsertIndex) * sizeof(pELEMENT_TYPE)); \
						} \
						else \
						{ \
							memmove(pTHIS->gBuffer, pTHIS->gBuffer + vInsertIndex, \
									(tEndIndex + 1 - vInsertIndex) * sizeof(pELEMENT_TYPE)); \
						} \
					} \
				} \
			) \
		} \
	\
		pTHIS->gPrivate_length = pTHIS->gPrivate_length + ((pSIZE_T)pWIDTH); \
	}
//#END_DEFINE
		
#define CRX__C__FIXED_RING__ECHO__COPY_FROM_RING_RANGE(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pELEMENT_TYPE, pTHIS_ELEMENTS, \
				pTHIS_START_INDEX, pTHIS_CAPACITY, pINDEX, pARRAY_ELEMENTS, \
				pARRAY_START_INDEX, pARRAY_CAPACITY, pSTART_INDEX, pWIDTH)  \
	{ \
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < pWIDTH, tI++) \
			{ \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(pTHIS_ELEMENTS + ((pTHIS_START_INDEX + tI + pINDEX) & (pTHIS_CAPACITY - 1)), \
						pARRAY_ELEMENTS + ((pARRAY_START_INDEX + tI + pSTART_INDEX) & (pARRAY_CAPACITY - 1))); \
			} \
			CRX_ENDFOR \
		) \
		( \
			size_t tTargetStartIndex = ((pTHIS_START_INDEX + pINDEX) & (pTHIS_CAPACITY - 1)); \
			size_t tTargetSegmentLength = ((tTargetStartIndex >= pTHIS_START_INDEX) ? \
					((((pTHIS_START_INDEX + pINDEX + pWIDTH - 1) & (pTHIS_CAPACITY - 1)) > tTargetStartIndex) ? \
							pWIDTH : (pTHIS_CAPACITY - tTargetStartIndex)) : \
					pWIDTH); \
			size_t tSourceStartIndex = ((pARRAY_START_INDEX + pSTART_INDEX) & (pARRAY_CAPACITY - 1)); \
			size_t tSourceLength = ((tSourceStartIndex >= pARRAY_START_INDEX) ? \
					((((pARRAY_START_INDEX + pINDEX + pWIDTH - 1) & (pARRAY_CAPACITY - 1)) > tSourceStartIndex) ? \
							pWIDTH : (pARRAY_CAPACITY - tSourceStartIndex)) : \
					pWIDTH); \
	\
			if(tTargetSegmentLength <= tSourceLength) \
			{ \
				memcpy(pTHIS_ELEMENTS + tTargetStartIndex, pARRAY_ELEMENTS + tSourceStartIndex, \
						tTargetSegmentLength * sizeof(pELEMENT_TYPE)); \
	\
				if(tTargetSegmentLength < pWIDTH) \
				{ \
					assert(((pTHIS_START_INDEX + pINDEX + tTargetSegmentLength) & (pTHIS_CAPACITY - 1)) == 0); \
	\
					memcpy(pTHIS_ELEMENTS, pARRAY_ELEMENTS + tSourceStartIndex + tTargetSegmentLength, \
							(tSourceLength - tTargetSegmentLength) * sizeof(pELEMENT_TYPE)); \
	\
					if(tSourceLength < pWIDTH) \
					{ \
						assert(((pARRAY_START_INDEX + tSourceStartIndex + tSourceLength) & (pTHIS_CAPACITY - 1)) == 0); \
	\
						memcpy(pTHIS_ELEMENTS + tTargetStartIndex + tSourceLength - tTargetSegmentLength, \
								pARRAY_ELEMENTS, (pWIDTH - tSourceLength) * sizeof(pELEMENT_TYPE)); \
					} \
				} \
			} \
			else \
			{ \
				memcpy(pTHIS_ELEMENTS + tTargetStartIndex, pARRAY_ELEMENTS + tSourceStartIndex, \
						tSourceLength * sizeof(pELEMENT_TYPE)); \
	\
				assert(((pARRAY_START_INDEX + pINDEX + tSourceLength) & (pTHIS_CAPACITY - 1)) == 0); \
	\
				memcpy(pTHIS_ELEMENTS + tTargetStartIndex + tSourceLength, pARRAY_ELEMENTS, \
						(tTargetSegmentLength - tSourceLength) * sizeof(pELEMENT_TYPE)); \
	\
				if(tTargetSegmentLength < pWIDTH) \
				{ \
					assert(((pTHIS_START_INDEX + pINDEX + tTargetSegmentLength) & (pTHIS_CAPACITY - 1)) == 0); \
	\
					memcpy(pTHIS_ELEMENTS, pARRAY_ELEMENTS + tTargetSegmentLength - tSourceLength, \
							(pWIDTH - tTargetSegmentLength) * sizeof(pELEMENT_TYPE)); \
				} \
			} \
		) \
	}
//#END_DEFINE

/*WARNING: THE FOLLOWING ASSUMES THAT THE REMAINING SPACE IS LARGER THAN pWIDTH. THIS MEANS THAT
		IT IS ASSUMED THAT THE TAIL WILL NEVER HIT THE ORIGINAL LOCATION OF THE HEAD AFTER ROTATION.*/
#define CRX__C__FIXED_RING__ECHO__RAW_ROTATE_RIGHT(pELEMENT_TYPE, pELEMENTS, \
		pRAW_START_INDEX, pRAW_END_INDEX, pCAPACITY, pWIDTH, pNEW_RAW_END_INDEX) \
	{ \
		assert(pWIDTH > 0); \
\
		size_t tStartIndex = pRAW_START_INDEX; \
		size_t tEndIndex = pRAW_END_INDEX; \
		size_t tEmptySpaceBeforeEnd; \
\
		if(tEndIndex < tStartIndex) \
			{tEmptySpaceBeforeEnd = 0;} \
		else \
			{tEmptySpaceBeforeEnd = pCAPACITY - tEndIndex - 1;} \
\
		if(tEndIndex < tStartIndex) \
		{ \
			memmove(pELEMENTS + pWIDTH, pELEMENTS, \
					tEndIndex * sizeof(pELEMENT_TYPE)); \
		} \
\
		if(pWIDTH <= tEmptySpaceBeforeEnd) \
		{ \
			memmove(pELEMENTS + tStartIndex + pWIDTH, pELEMENTS + tStartIndex, \
					(tEndIndex + 1 - tStartIndex) * sizeof(pELEMENT_TYPE)); \
\
			CRXM__IFELSE2(pNEW_RAW_END_INDEX, \
			pNEW_RAW_END_INDEX = tEndIndex + pWIDTH;, ) \
		} \
		else \
		{ \
			if(pWIDTH < pCAPACITY - tStartIndex) \
			{ \
				memcpy(pELEMENTS, pELEMENTS + pCAPACITY - (pWIDTH - tEmptySpaceBeforeEnd), \
							(pWIDTH - tEmptySpaceBeforeEnd) * sizeof(pELEMENT_TYPE)); \
\
				memmove(pELEMENTS + tStartIndex + pWIDTH, pELEMENTS + tStartIndex, \
						(pCAPACITY - tStartIndex  - pWIDTH) * sizeof(pELEMENT_TYPE)); \
\
				CRXM__IFELSE2(pNEW_RAW_END_INDEX, \
				pNEW_RAW_END_INDEX = pWIDTH - tEmptySpaceBeforeEnd - 1;, ) \
			} \
			else \
			{ \
				memcpy(pELEMENTS + pWIDTH - (pCAPACITY - tStartIndex), pELEMENTS + tStartIndex, \
						(pCAPACITY - tEmptySpaceBeforeEnd - tStartIndex) * sizeof(pELEMENT_TYPE)); \
\
				CRXM__IFELSE2(pNEW_RAW_END_INDEX, \
				pNEW_RAW_END_INDEX = pWIDTH - tEmptySpaceBeforeEnd - 1;, ) \
			} \
		} \
	}
//#END_DEFINE

/*WARNING: THE FOLLOWING ASSUMES THAT THE REMAINING SPACE IS LARGER THAN pWIDTH. THIS MEANS THAT
		IT IS ASSUMED THAT THE HEAD WILL NEVER HIT THE ORIGINAL LOCATION OF THE TAIL AFTER ROTATION.*/
#define CRX__C__FIXED_RING__ECHO__RAW_ROTATE_LEFT(pELEMENT_TYPE, pELEMENTS, \
		pRAW_START_INDEX, pRAW_END_INDEX, pCAPACITY, pWIDTH, pNEW_RAW_START_INDEX) \
	{ \
		assert(pWIDTH > 0); \
\
		size_t tStartIndex = pRAW_START_INDEX; \
		size_t tEndIndex = pRAW_END_INDEX; \
		size_t tIndexOfFirstElementFromLeftSide; \
\
		if(tStartIndex > tEndIndex) \
			{tIndexOfFirstElementFromLeftSide = 0;} \
		else \
			{tIndexOfFirstElementFromLeftSide = tStartIndex;} \
\
		if(tStartIndex > tEndIndex) \
		{ \
			memmove(pELEMENTS + tStartIndex - pWIDTH, pELEMENTS + tStartIndex, \
					(pCAPACITY - tStartIndex) * sizeof(pELEMENT_TYPE)); \
		} \
\
		if(pWIDTH <= tIndexOfFirstElementFromLeftSide) \
		{ \
			memcpy(pELEMENTS + tStartIndex - pWIDTH, pELEMENTS + tStartIndex, \
					(tStartIndex + 1 - tStartIndex) * sizeof(pELEMENT_TYPE)); \
\
			CRXM__IFELSE2(pNEW_RAW_START_INDEX, \
			pNEW_RAW_START_INDEX = tStartIndex - pWIDTH;, ) \
		} \
		else \
		{ \
			if(pWIDTH <= tEndIndex) \
			{ \
				memcpy(pELEMENTS + pCAPACITY + tIndexOfFirstElementFromLeftSide - pWIDTH, \
						pELEMENTS + tIndexOfFirstElementFromLeftSide, \
						(pWIDTH - tIndexOfFirstElementFromLeftSide) * sizeof(pELEMENT_TYPE)); \
\
				memcpy(pELEMENTS, pELEMENTS + pWIDTH, \
						(tEndIndex + 1 - pWIDTH) * sizeof(pELEMENT_TYPE)); \
\
				CRXM__IFELSE2(pNEW_RAW_START_INDEX, \
				pNEW_RAW_START_INDEX = pCAPACITY - (pWIDTH - tIndexOfFirstElementFromLeftSide);, ) \
			} \
			else \
			{ \
				memcpy(pELEMENTS + pCAPACITY + tIndexOfFirstElementFromLeftSide - pWIDTH, \
						pELEMENTS + tIndexOfFirstElementFromLeftSide, \
						(tEndIndex + 1 - tIndexOfFirstElementFromLeftSide) * sizeof(pELEMENT_TYPE)); \
\
				CRXM__IFELSE2(pNEW_RAW_START_INDEX, \
				pNEW_RAW_START_INDEX = pCAPACITY - (pWIDTH - tIndexOfFirstElementFromLeftSide);, ) \
			} \
		} \
	}
//#END_DEFINE


CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif