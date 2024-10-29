#if(!defined(CRX__C__FIXED_ARRAY___h__))
#define CRX__C__FIXED_ARRAY___h__

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


/* IMPORTANT: REFER TO NOTES IN Ring.h */
#if(!CRX_ARE_VARIADIC_MACROS_EMULATED)
	#define CRX__C__FixedArray__DECLARE(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__FixedArray__DECLARE, __VA_ARGS__)
#else
	#define CRX__C__FixedArray__DECLARE(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__FixedArray__DECLARE, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20)
#endif

#define CRX__C__FixedArray__DECLARE__10(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__FixedArray__DECLARE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, CRXM__FALSE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRX__C__Ring__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pThis, \
					pDEFAULT_SIZE_OF_INTERNAL_BUFFER), CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())

#define CRX__C__FixedArray__DECLARE__11(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__FixedArray__DECLARE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, CRXM__TRUE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRX__C__Ring__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pThis, \
					pDEFAULT_SIZE_OF_INTERNAL_BUFFER), CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())
		
		
		
#define _CRX__C__FixedArray__DECLARE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, pIS_COPYABLE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		pTHIS_SIZE_OF_INTERNAL_BUFFER, PUBLIC, PRIVATE) \
	typedef struct pARRAY_TYPE_NAME \
	{ \
		pSIZE_T gPrivate_length; \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
				pSIZE_T gSIZE_OF_INTERNAL_BUFFER;, )\
		pELEMENT_TYPE gBuffer[CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, 1, pDEFAULT_SIZE_OF_INTERNAL_BUFFER)]; \
	} pARRAY_TYPE_NAME; \
	\
	\
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC size_t pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCorrectCapacityBoundFor(size_t pCapacity), ); \
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC size_t pARRAY_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf( \
			pARRAY_TYPE_NAME const * CRX_NOT_NULL pArray), ); \
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC size_t pARRAY_MEMBER_FUNCTIONS_PREFIX ## getByteSizeFor(size_t pSizeOfInternalBuffer), ); \
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis, \
			size_t pSizeOfInternalBuffer), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis)); \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveConstruct(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME * CRX_NOT_NULL pArray), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyConstruct(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME const * CRX_NOT_NULL pArray); \
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new( \
			size_t pSizeOfInternalBuffer CRX_DEFAULT(0)), \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(void)); \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveNew( \
			pARRAY_TYPE_NAME * CRX_NOT_NULL pArray); \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyNew( \
			pARRAY_TYPE_NAME const * CRX_NOT_NULL pArray); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PRIVATE pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_new2( \
			pARRAY_TYPE_NAME const * CRX_NOT_NULL pArray, size_t pStartIndex, size_t pWidth), ); \
	CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
	PRIVATE void pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct( \
			pARRAY_TYPE_NAME * pThis, size_t pStartIndex, size_t pEndIndex), ); \
	CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## destruct(pARRAY_TYPE_NAME * pThis), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## free(pARRAY_TYPE_NAME * pThis); \
	PUBLIC pSIZE_T pARRAY_MEMBER_FUNCTIONS_PREFIX ## getLength(pARRAY_TYPE_NAME const * pThis); \
	PUBLIC pSIZE_T pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCapacity(pARRAY_TYPE_NAME const * pThis); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## empty(pARRAY_TYPE_NAME * pThis); \
	PRIVATE void pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt( \
			pARRAY_TYPE_NAME * pThis, size_t pIndex, size_t pWidth); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyAssignFrom2(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME const * CRX_NOT_NULL pArray, size_t pStartIndex, size_t pWidth), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyAssignFrom(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME const * CRX_NOT_NULL pArray), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndSetAt(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pELEMENT_TYPE * CRX_NOT_NULL pElement); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## setAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * CRX_NOT_NULL pElement), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## setAt2(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE pElement), ); \
	PUBLIC pELEMENT_TYPE * pARRAY_MEMBER_FUNCTIONS_PREFIX ## get(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex); \
	PUBLIC pELEMENT_TYPE const * pARRAY_MEMBER_FUNCTIONS_PREFIX ## constantGet( \
			pARRAY_TYPE_NAME const * pThis, size_t pIndex); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyGetTo(pARRAY_TYPE_NAME const * pThis, \
			pELEMENT_TYPE * CRX_NOT_NULL pReturn, size_t pIndex), \
	PUBLIC pELEMENT_TYPE pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyGet(pARRAY_TYPE_NAME const * pThis, \
			size_t pIndex)), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPush(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE * CRX_NOT_NULL pElement); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastPush(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE const * CRX_NOT_NULL pElement), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastPush2(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE pElement), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## pop(pARRAY_TYPE_NAME * pThis); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastInsertElementAt( \
			pARRAY_TYPE_NAME * pThis, size_t pIndex, pELEMENT_TYPE * CRX_NOT_NULL pElement); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementAt(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pELEMENT_TYPE const * CRX_NOT_NULL pElement), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementAt2(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pELEMENT_TYPE pElement), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementsAt(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pARRAY_TYPE_NAME const * CRX_NOT_NULL pArray, size_t pStartIndex, \
			size_t pWidth), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertCArrayAt(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pELEMENT_TYPE const * CRX_NOT_NULL pArray, size_t pWidth), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementCopiesAt( \
			pARRAY_TYPE_NAME * pThis, size_t pIndex, pELEMENT_TYPE const * CRX_NOT_NULL pElement, \
			size_t pNumberOfCopies), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementCopiesAt2( \
			pARRAY_TYPE_NAME * pThis, size_t pIndex, pELEMENT_TYPE pElement, size_t pNumberOfCopies), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## removeElements(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, size_t pWidth); \
	PUBLIC pELEMENT_TYPE * pARRAY_MEMBER_FUNCTIONS_PREFIX ## getElementsPointer( \
			pARRAY_TYPE_NAME * pThis); \
	PUBLIC pELEMENT_TYPE const * pARRAY_MEMBER_FUNCTIONS_PREFIX ## constantGetElementsPointer( \
			pARRAY_TYPE_NAME const * pThis);
//#END_DEFINE





#if(!CRX_ARE_VARIADIC_MACROS_EMULATED)
	#define CRX__C__FixedArray__DEFINE(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__FixedArray__DEFINE, __VA_ARGS__)
#else
	#define CRX__C__FixedArray__DEFINE(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__FixedArray__DEFINE, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20)
#endif

#define CRX__C__FixedArray__DEFINE__10(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__FixedArray__DEFINE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, CRXM__FALSE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRX__C__Ring__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pThis, \
					pDEFAULT_SIZE_OF_INTERNAL_BUFFER), CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())

#define CRX__C__FixedArray__DEFINE__11(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__FixedArray__DEFINE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, CRXM__TRUE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRX__C__Ring__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pThis, \
					pDEFAULT_SIZE_OF_INTERNAL_BUFFER), CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())
		
		
		
#define _CRX__C__FixedArray__DEFINE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, pIS_COPYABLE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		pTHIS_SIZE_OF_INTERNAL_BUFFER, PUBLIC, PRIVATE) \
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC size_t pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCorrectCapacityBoundFor(size_t pCapacity) \
	{ \
		size_t vReturn = 1; \
	\
		while(vReturn < pCapacity) \
			{vReturn = (pCapacity << 1);} \
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
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis, \
			size_t pSizeOfInternalBuffer), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis)) \
	{ \
		/*assert(pThis->gPrivate_length == 0); */ \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		assert(pSizeOfInternalBuffer <= pSIZE_T_MAX); \
		assert((pSizeOfInternalBuffer > 0) || (pDEFAULT_SIZE_OF_INTERNAL_BUFFER > 0));, ) \
	\
		pThis->gPrivate_length == 0; \
	\
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pThis->gSIZE_OF_INTERNAL_BUFFER = ((pSIZE_T)((pSizeOfInternalBuffer == 0) ? \
					pDEFAULT_SIZE_OF_INTERNAL_BUFFER : pSizeOfInternalBuffer));, )\
	} \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveConstruct(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME * pArray) \
	{ \
		pThis->gPrivate_length = 0; \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pThis->gSIZE_OF_INTERNAL_BUFFER = pArray->gSIZE_OF_INTERNAL_BUFFER;, )\
	\
		CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++) \
		{ \
			pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPush(pThis, pArray->gBuffer + tI); \
	\
			CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
			pFUNC_ELEMENT_MOVE_DESTRUCTOR(pArray->gBuffer + tI), ); \
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
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pThis, \
						pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCorrectCapacityBoundFor(pArray->gPrivate_length)), \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pThis)); \
	\
		if(pArray->gPrivate_length > 0) \
		{ \
			CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				CRX_FOR(size_t tI = 0, tI < pArray->gPrivate_length, tI++) \
				{ \
					pFUNC_ELEMENT_COPY_CONSTRUCTOR(pThis->gBuffer + tI, \
							pArray->gBuffer + tI); \
				} \
				CRX_ENDFOR \
			) \
			( \
				memcpy(pThis->gBuffer, \
						pArray->gBuffer, \
						pArray->gPrivate_length * sizeof(pELEMENT_TYPE)); \
			) \
\
			pThis->gPrivate_length = pArray->gPrivate_length; \
		} \
	)} \
	\
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new( \
			size_t pSizeOfInternalBuffer CRX_DEFAULT(0)), \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(void)) \
	{ \
		CRX_SCOPE_META \
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
				{pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(vReturn, pSizeOfInternalBuffer);} \
		) \
		( \
			vReturn = (pARRAY_TYPE_NAME *)(calloc(1, sizeof(pARRAY_TYPE_NAME))); \
	\
			if(vReturn != NULL) \
				{pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(vReturn);} \
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
		pARRAY_TYPE_NAME * vReturn = CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(pWidth), \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## new()); \
	\
		if((vReturn != NULL) && (pWidth > 0)) \
		{ \
			CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
				{ \
					pFUNC_ELEMENT_COPY_CONSTRUCTOR(vReturn->gBuffer + tI, \
							pArray->gBuffer + pStartIndex + tI); \
				} \
				CRX_ENDFOR \
			) \
			( \
				memcpy(vReturn->gBuffer, \
						pArray->gBuffer + (pStartIndex * sizeof(pELEMENT_TYPE)), \
						pWidth * sizeof(pELEMENT_TYPE)); \
			) \
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
		CRX_FOR(size_t tI = pStartIndex, tI <= pEndIndex, tI++) \
			{pFUNC_ELEMENT_DESTRUCTOR(pThis->gBuffer + tI);} \
		CRX_ENDFOR \
	}, )\
	CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## destruct(pARRAY_TYPE_NAME * pThis) \
	{ \
		if(pThis->gPrivate_length > 0) \
			{pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct(pThis, 0, pThis->gPrivate_length - 1);} \
	}, ) \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## free(pARRAY_TYPE_NAME * pThis) \
		{free(pThis);} \
	\
	PUBLIC pSIZE_T pARRAY_MEMBER_FUNCTIONS_PREFIX ## getLength(pARRAY_TYPE_NAME const * pThis) \
		{return pThis->gPrivate_length;} \
	PUBLIC pSIZE_T pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCapacity(pARRAY_TYPE_NAME const * pThis) \
		{return pTHIS_SIZE_OF_INTERNAL_BUFFER;} \
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
		pThis->gPrivate_length = 0; \
	} \
	\
	PRIVATE void pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			size_t pWidth) \
	{ \
		assert(pIndex <= pThis->gPrivate_length); \
		assert(pWidth + pThis->gPrivate_length <= pTHIS_SIZE_OF_INTERNAL_BUFFER); \
	\
		CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR)) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				CRX_FOR(size_t tI = pThis->gPrivate_length - 1, tI >= pIndex, tI--) \
				{ \
					pFUNC_ELEMENT_MOVE_CONSTRUCTOR( \
							pThis->gBuffer + tI + pWidth, \
							pThis->gBuffer + tI); \
	\
					CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
					pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gBuffer + tI);, ) \
				} \
				CRX_ENDFOR \
			) \
			( \
				size_t tI; \
	\
				CRX_FOR(tI = pThis->gPrivate_length - pWidth, tI >= pIndex + pWidth, tI = tI - pWidth) \
				{ \
					memmove(pThis->gBuffer + tI + pWidth, pThis->gBuffer + tI, pWidth * sizeof(pELEMENT_TYPE)); \
	\
					CRX_FOR(size_t tI2 = tI, tI2 < tI + pWidth, tI2++) \
						{pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gBuffer + tI2);} \
					CRX_ENDFOR \
				} \
				CRX_ENDFOR \
	\
				CRX_FOR(tI = tI + pWidth - 1, tI >= pIndex, tI--) \
				{ \
					memmove(pThis->gBuffer + tI + pWidth, pThis->gBuffer + tI, sizeof(pELEMENT_TYPE)); \
	\
					pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gBuffer + tI); \
				} \
				CRX_ENDFOR \
			) \
		) \
		( \
			memmove(pThis->gBuffer + pIndex + pWidth, pThis->gBuffer + pIndex, \
					(pThis->gPrivate_length - pIndex) * sizeof(pELEMENT_TYPE)); \
		) \
	\
		pThis->gPrivate_length = pThis->gPrivate_length + ((pSIZE_T)pWidth); \
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
			CRXM__IFELSE(pFUNC_ELEMENT_DESTRUCTOR) \
			( \
				if(pThis->gPrivate_length > 0) \
					{pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct(pThis, 0, pThis->gPrivate_length - 1);} \
			)() \
	\
			CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
				{ \
					pFUNC_ELEMENT_COPY_CONSTRUCTOR(pThis->gBuffer + tI, \
							vArray->gBuffer + pStartIndex + tI); \
				} \
				CRX_ENDFOR \
			) \
			( \
				memcpy(pThis->gBuffer, \
						vArray->gBuffer + (pStartIndex * sizeof(pELEMENT_TYPE)), \
						pWidth * sizeof(pELEMENT_TYPE)); \
			) \
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
		return vReturn; \
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
				pFUNC_ELEMENT_DESTRUCTOR(pThis->gBuffer + pIndex);, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gBuffer + pIndex, pElement); \
		) \
		( \
			memcpy(pThis->gBuffer + pIndex, pElement, sizeof(pELEMENT_TYPE)); \
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
	\
		CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_DESTRUCTOR(&pElement);, ) \
	}, ) \
	PUBLIC pELEMENT_TYPE * pARRAY_MEMBER_FUNCTIONS_PREFIX ## get(pARRAY_TYPE_NAME * pThis, size_t pIndex) \
	{ \
		assert(pIndex < pThis->gPrivate_length); \
	\
		return (pThis->gBuffer + pIndex); \
	} \
	PUBLIC pELEMENT_TYPE const * pARRAY_MEMBER_FUNCTIONS_PREFIX ## constantGet(pARRAY_TYPE_NAME const * pThis, size_t pIndex) \
		{return pARRAY_MEMBER_FUNCTIONS_PREFIX ## get((pARRAY_TYPE_NAME *) pThis, pIndex);} \
	\
	CRXM__IFELSE2(pIS_COPYABLE, \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyGetTo(pARRAY_TYPE_NAME const * pThis, \
			pELEMENT_TYPE * pReturn, size_t pIndex), \
	PUBLIC pELEMENT_TYPE pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyGet(pARRAY_TYPE_NAME const * pThis, size_t pIndex)) \
	{ \
		assert(pIndex < pThis->gPrivate_length); \
	 \
		CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR)) \
		( \
			CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
			pFUNC_ELEMENT_DESTRUCTOR(pReturn);, ) \
	\
			CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(pReturn, pThis->gBuffer + pIndex); \
			) \
			( \
				memcpy(pReturn, pThis->gBuffer + pIndex, sizeof(pELEMENT_TYPE)); \
			) \
		) \
		( \
			return *(pThis->gBuffer + pIndex); \
		) \
	}, ) \
	\
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPush(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE * pElement) \
	{ \
		assert(pTHIS_SIZE_OF_INTERNAL_BUFFER > pThis->gPrivate_length); \
	 \
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gBuffer + pThis->gPrivate_length, pElement); \
		) \
		( \
			memcpy(pThis->gBuffer + pThis->gPrivate_length, pElement, sizeof(pELEMENT_TYPE)); \
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
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastPush2(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE pElement) \
	{ \
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPush(pThis, &pElement); \
	\
		CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_DESTRUCTOR(&pElement);, ) \
	}, ) \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## pop(pARRAY_TYPE_NAME * pThis) \
	{ \
		assert(pThis->gPrivate_length > 0); \
	\
		pThis->gPrivate_length--; \
	\
		CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
				pFUNC_ELEMENT_DESTRUCTOR(pThis->gBuffer + pThis->gPrivate_length);, ) \
	} \
	\
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastInsertElementAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE * pElement) \
	{ \
		assert(pIndex <= pSIZE_T_MAX); \
	\
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pThis, pIndex, 1); \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
		( \
			pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gBuffer + pIndex, pElement); \
		) \
		( \
			memcpy(pThis->gBuffer + pIndex, pElement, sizeof(pELEMENT_TYPE)); \
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
	\
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementAt2(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE pElement) \
	{ \
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastInsertElementAt(pThis, pIndex, &pElement); \
	\
		CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_DESTRUCTOR(&pElement);, ) \
	}, ) \
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
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pThis, pIndex, pWidth); \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
			{ \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(pThis->gBuffer + pIndex + tI, pArray->gBuffer + pStartIndex + tI); \
			} \
			CRX_ENDFOR \
		) \
		( \
			memcpy(pThis->gBuffer + pIndex, pArray->gBuffer + pStartIndex, pWidth * sizeof(pELEMENT_TYPE)); \
		) \
	}, ) \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertCArrayAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pArray, size_t pWidth) \
	{ \
		assert(pIndex <= pSIZE_T_MAX); \
		assert(pWidth <= pSIZE_T_MAX); \
	\
		if(pWidth == 0) \
			{return;} \
	\
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pThis, pIndex, pWidth); \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
			{ \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(pThis->gBuffer + pIndex + tI, pArray + tI); \
			} \
			CRX_ENDFOR \
		) \
		( \
			memcpy(pThis->gBuffer + pIndex, pArray, pWidth * sizeof(pELEMENT_TYPE)); \
		) \
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
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pThis, pIndex, pNumberOfCopies); \
	\
		CRX_SCOPE \
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < pNumberOfCopies, tI++) \
			{ \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(pThis->gBuffer + pIndex + tI, pElement); \
			} \
			CRX_ENDFOR \
		) \
		({ \
			size_t tNumberOfCopies = 1; \
			size_t tRemainingNumberOfCopies = pNumberOfCopies - 1; \
	\
			memcpy(pThis->gBuffer + pIndex, pElement, sizeof(pELEMENT_TYPE));\
	\
			while(tRemainingNumberOfCopies > 0) \
			{ \
				if(tRemainingNumberOfCopies >= tNumberOfCopies) \
				{ \
					memcpy(pThis->gBuffer + pIndex + tNumberOfCopies, pThis->gBuffer + pIndex, \
							tNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
					tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies; \
					tNumberOfCopies = (tNumberOfCopies << 1); \
				} \
				else \
				{ \
					memcpy(pThis->gBuffer + pIndex + tNumberOfCopies, pThis->gBuffer + pIndex, \
							tRemainingNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
					break; \
				} \
			} \
		}) \
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
				CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length - pWidth - pIndex, tI++) \
				{ \
					pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gBuffer + tI + pIndex, \
							pThis->gBuffer + tI + pIndex + pWidth); \
	\
					CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
							pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gBuffer + \
							tI + pIndex + pWidth);, ) \
				} \
				CRX_ENDFOR \
			) \
			( \
				CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length - pWidth - pIndex, tI++) \
				{ \
					memmove(pThis->gBuffer + tI + pIndex, \
							pThis->gBuffer + tI + pIndex + pWidth, \
							sizeof(pELEMENT_TYPE)); \
	\
					pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gBuffer + \
							tI + pIndex + pWidth); \
				} \
				CRX_ENDFOR \
			) \
		) \
		( \
			memmove(pThis->gBuffer + pIndex, pThis->gBuffer + pIndex + pWidth, \
					(pThis->gPrivate_length + 1 - pIndex - pWidth) * sizeof(pELEMENT_TYPE)); \
		) \
	\
		pThis->gPrivate_length = ((pSIZE_T)(pThis->gPrivate_length - pWidth)); \
	} \
	\
	PUBLIC pELEMENT_TYPE * pARRAY_MEMBER_FUNCTIONS_PREFIX ## getElementsPointer(pARRAY_TYPE_NAME * pThis) \
		{return pThis->gBuffer;} \
	PUBLIC pELEMENT_TYPE const * pARRAY_MEMBER_FUNCTIONS_PREFIX ## constantGetElementsPointer(pARRAY_TYPE_NAME const * pThis) \
		{return pThis->gBuffer;}
//#END_DEFINE


#define CRX__C__FixedArray__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pTHIS, \
				pDEFAULT_SIZE_OF_INTERNAL_BUFFER) \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pTHIS->gSIZE_OF_INTERNAL_BUFFER, pDEFAULT_SIZE_OF_INTERNAL_BUFFER)


CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif