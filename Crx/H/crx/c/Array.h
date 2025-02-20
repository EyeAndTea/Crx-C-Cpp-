#if(!defined(CRX__C__ARRAY___h__))
#define CRX__C__ARRAY___h__

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
#include "Crx/H/crx/c/TypeBluePrint.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()

/* IMPORTANT: REFER TO NOTES IN Ring.h */
#if(!CRX_ARE_VARIADIC_MACROS_EMULATED)
	#define CRX__C__Array__DECLARE(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__Array__DECLARE, __VA_ARGS__)
#else
	#define CRX__C__Array__DECLARE(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__Array__DECLARE, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20)
#endif

#define CRX__C__Array__DECLARE__10(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__Array__DECLARE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, CRXM__FALSE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRXM__FALSE, \
		CRXM__OR(pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD), \
		CRX__C__Array__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pThis, \
					pDEFAULT_SIZE_OF_INTERNAL_BUFFER), CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())


#define CRX__C__Array__DECLARE__11(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__Array__DECLARE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, CRXM__TRUE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRXM__AND(CRXM__AND(CRXM_NOT(pFUNC_ELEMENT_DESTRUCTOR), \
						CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR)), \
				CRXM__AND(CRXM_NOT(pFUNC_ELEMENT_MOVE_CONSTRUCTOR), \
						CRXM__NOT(pFUNC_ELEMENT_MOVE_DESTRUCTOR))), \
		CRXM__OR(pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD), \
		CRX__C__Array__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pThis, \
					pDEFAULT_SIZE_OF_INTERNAL_BUFFER), CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())


#define _CRX__C__Array__DECLARE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, pIS_COPYABLE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		pIS_TO_ENABLE_C_ARRAY, pHAS_INTERNAL_BUFFER, pTHIS_SIZE_OF_INTERNAL_BUFFER, PUBLIC, PRIVATE) \
	typedef struct pARRAY_TYPE_NAME \
	{ \
		pELEMENT_TYPE * gPrivate_elements; \
		pSIZE_T gPrivate_length; \
		pSIZE_T gPrivate_capacity; \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
				pSIZE_T gSIZE_OF_INTERNAL_BUFFER;, )\
		CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
				bool gPrivate_isReadyForCArray;, ) \
		CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
				unsigned char _pad743464443[3];, ) \
		CRXM__IFELSE2(pHAS_INTERNAL_BUFFER, \
				pELEMENT_TYPE gPrivate_buffer[CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, 1, pDEFAULT_SIZE_OF_INTERNAL_BUFFER)];, )\
	} pARRAY_TYPE_NAME; \
	\
	CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
	typedef char pARRAY_TYPE_NAME ##__ERROR__INVALID_SIZE_OF_BOOL[2 * !!(sizeof(bool) == 1) - 1];, ) \
	\
	\
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC size_t pARRAY_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf( \
			pARRAY_TYPE_NAME const * CRX_NOT_NULL pArray), ); \
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC size_t pARRAY_MEMBER_FUNCTIONS_PREFIX ## getByteSizeFor(size_t pSizeOfInternalBuffer), ); \
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis, \
			size_t pCapacity, size_t pSizeOfInternalBuffer), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis, \
			size_t pCapacity)); \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveConstruct(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME * CRX_NOT_NULL pArray), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyConstruct(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME const * CRX_NOT_NULL pArray); \
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(size_t pCapacity CRX_DEFAULT(0), \
			size_t pSizeOfInternalBuffer CRX_DEFAULT(0)), \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(size_t pCapacity CRX_DEFAULT(0))); \
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
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## destruct(pARRAY_TYPE_NAME * pThis); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## free(pARRAY_TYPE_NAME * pThis); \
	\
	CRX__C__TYPE_BLUE_PRINT__DECLARE_GET_BLUE_PRINT( \
			pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, \
			CRXM__NOT(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD), CRXM__TRUE, \
			pIS_COPYABLE, CRXM__TRUE, \
			CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), CRXM__FALSE); \
	\
	PUBLIC pSIZE_T pARRAY_MEMBER_FUNCTIONS_PREFIX ## getLength(pARRAY_TYPE_NAME const * pThis); \
	PUBLIC pSIZE_T pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCapacity(pARRAY_TYPE_NAME const * pThis); \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## ensureCapacity(pARRAY_TYPE_NAME * pThis, \
			size_t pCapacity); \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## emptyAndEnsureCapacity(pARRAY_TYPE_NAME * pThis, \
			size_t pCapacity); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## empty(pARRAY_TYPE_NAME * pThis); \
	PRIVATE bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_insertSpaceAt(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, size_t pWidth); \
	PRIVATE void pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt( \
			pARRAY_TYPE_NAME * pThis, size_t pIndex, size_t pWidth); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyAssignFrom2(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME const * CRX_NOT_NULL pArray, size_t pStartIndex, size_t pWidth), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## copyAssignFrom(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME const * CRX_NOT_NULL pArray), ); \
	CRXM__IFELSE2(CRXM__AND(CRXM__NOT(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD), \
			pHAS_INTERNAL_BUFFER), \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryToPilferSwapContentWith( \
			pARRAY_TYPE_NAME * pThis, pARRAY_TYPE_NAME * CRX_NOT_NULL pArray), ); \
	CRXM__IFELSE2(CRXM__NOT(pHAS_INTERNAL_BUFFER), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## pilferSwapContentWith(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME * CRX_NOT_NULL pArray), ); \
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
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryMoveAndPush(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE * CRX_NOT_NULL pElement); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## push(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE const * CRX_NOT_NULL pElement), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPush(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE * CRX_NOT_NULL pElement); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastPush(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE const * CRX_NOT_NULL pElement), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## push2(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE pElement), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastPush2(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE pElement), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## pop(pARRAY_TYPE_NAME * pThis); \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryMoveAndInsertElementAt( \
			pARRAY_TYPE_NAME * pThis, size_t pIndex, pELEMENT_TYPE * CRX_NOT_NULL pElement); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## insertElementAt(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pELEMENT_TYPE const * CRX_NOT_NULL pElement), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastInsertElementAt( \
			pARRAY_TYPE_NAME * pThis, size_t pIndex, pELEMENT_TYPE * CRX_NOT_NULL pElement); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementAt(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pELEMENT_TYPE const * CRX_NOT_NULL pElement), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## insertElementAt2(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pELEMENT_TYPE pElement), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementAt2(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pELEMENT_TYPE pElement), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## insertElementsAt(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pARRAY_TYPE_NAME const * CRX_NOT_NULL pArray, size_t pStartIndex, \
			size_t pWidth), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementsAt(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pARRAY_TYPE_NAME const * CRX_NOT_NULL pArray, size_t pStartIndex, \
			size_t pWidth), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## insertCArrayAt(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pELEMENT_TYPE const * CRX_NOT_NULL pArray, size_t pWidth), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertCArrayAt(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pELEMENT_TYPE const * CRX_NOT_NULL pArray, size_t pWidth), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## insertElementCopiesAt(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pELEMENT_TYPE const * CRX_NOT_NULL pElement, size_t pNumberOfCopies), ); \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementCopiesAt( \
			pARRAY_TYPE_NAME * pThis, size_t pIndex, pELEMENT_TYPE const * CRX_NOT_NULL pElement, \
			size_t pNumberOfCopies), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## insertElementCopiesAt2(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pELEMENT_TYPE pElement, size_t pNumberOfCopies), ); \
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementCopiesAt2( \
			pARRAY_TYPE_NAME * pThis, size_t pIndex, pELEMENT_TYPE pElement, size_t pNumberOfCopies), ); \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## removeElements(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, size_t pWidth); \
	PUBLIC pELEMENT_TYPE * pARRAY_MEMBER_FUNCTIONS_PREFIX ## getElementsPointer( \
			pARRAY_TYPE_NAME * pThis); \
	PUBLIC pELEMENT_TYPE const * pARRAY_MEMBER_FUNCTIONS_PREFIX ## constantGetElementsPointer( \
			pARRAY_TYPE_NAME const * pThis); \
	\
	CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
	PUBLIC pELEMENT_TYPE * pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCArray(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE pElement), ); \
	CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
	PUBLIC pELEMENT_TYPE * pARRAY_MEMBER_FUNCTIONS_PREFIX ## unsafeGetCArray( \
			pARRAY_TYPE_NAME * pThis), ); \
	CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## updateLength(pARRAY_TYPE_NAME * pThis, \
			size_t pLength), ); \
	CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## unsafeUpdateLength(pARRAY_TYPE_NAME * pThis, \
			size_t pLength), );
//#END_DEFINE




#if(!CRX_ARE_VARIADIC_MACROS_EMULATED)
	#define CRX__C__Array__DEFINE(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__Array__DEFINE, __VA_ARGS__)
#else
	#define CRX__C__Array__DEFINE(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__Array__DEFINE, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20)
#endif

#define CRX__C__Array__DEFINE__10(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__Array__DEFINE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, CRXM__FALSE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRXM__FALSE, \
		CRXM__OR(pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD), \
		CRX__C__Array__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pThis, \
					pDEFAULT_SIZE_OF_INTERNAL_BUFFER), CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())


#define CRX__C__Array__DEFINE__11(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__Array__DEFINE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, CRXM__TRUE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRXM__AND(CRXM__AND(CRXM_NOT(pFUNC_ELEMENT_DESTRUCTOR), \
						CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR)), \
				CRXM__AND(CRXM_NOT(pFUNC_ELEMENT_MOVE_CONSTRUCTOR), \
						CRXM__NOT(pFUNC_ELEMENT_MOVE_DESTRUCTOR))), \
		CRXM__OR(pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD), \
		CRX__C__Array__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pThis, \
					pDEFAULT_SIZE_OF_INTERNAL_BUFFER), CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())
		
		
		
#define _CRX__C__Array__DEFINE(pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, pELEMENT_TYPE, \
		pSIZE_T, pSIZE_T_MAX, pDEFAULT_SIZE_OF_INTERNAL_BUFFER, pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pFUNC_ELEMENT_DESTRUCTOR, pIS_COPYABLE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		pIS_TO_ENABLE_C_ARRAY, pHAS_INTERNAL_BUFFER, pTHIS_SIZE_OF_INTERNAL_BUFFER, PUBLIC, PRIVATE) \
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
			size_t pCapacity, size_t pSizeOfInternalBuffer), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pARRAY_TYPE_NAME * pThis, size_t pCapacity)) \
	{ \
		/*assert(((pThis->gPrivate_elements == 0) || (pThis->gPrivate_elements == NULL)) && (pThis->gPrivate_length == 0)); */ \
		assert(pCapacity <= pSIZE_T_MAX); \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		assert(pSizeOfInternalBuffer <= pSIZE_T_MAX); \
		assert((pSizeOfInternalBuffer > 0) || (pDEFAULT_SIZE_OF_INTERNAL_BUFFER > 0));, ) \
	\
		pThis->gPrivate_elements = NULL; \
		pThis->gPrivate_length = 0; \
	\
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
			pThis->gSIZE_OF_INTERNAL_BUFFER = ((pSIZE_T)((pSizeOfInternalBuffer == 0) ? \
					pDEFAULT_SIZE_OF_INTERNAL_BUFFER : pSizeOfInternalBuffer));, )\
	\
			if(pCapacity > pTHIS_SIZE_OF_INTERNAL_BUFFER) \
			{ \
				pThis->gPrivate_elements = (pELEMENT_TYPE *)(malloc(pCapacity * sizeof(pELEMENT_TYPE))); \
	\
				if(pThis->gPrivate_elements != NULL) \
					{pThis->gPrivate_capacity = ((pSIZE_T)pCapacity);} \
				else \
				{ \
					pThis->gPrivate_capacity = pTHIS_SIZE_OF_INTERNAL_BUFFER; \
				} \
			} \
			else \
			{ \
				pThis->gPrivate_capacity = pTHIS_SIZE_OF_INTERNAL_BUFFER; \
			} \
		) \
		( \
			if(pCapacity > 0) \
			{ \
				pThis->gPrivate_elements = ((pELEMENT_TYPE *)malloc(pCapacity * sizeof(pELEMENT_TYPE))); \
	\
				if(pThis->gPrivate_elements != NULL) \
					{pThis->gPrivate_capacity = ((pSIZE_T)pCapacity);} \
				else \
					{pThis->gPrivate_capacity = 0;} \
			} \
			else \
				{pThis->gPrivate_capacity = 0;} \
		) \
	} \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveConstruct(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME * pArray) \
	{ \
		pThis->gPrivate_elements = pArray->gPrivate_elements; \
		pThis->gPrivate_capacity = pArray->gPrivate_capacity; \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
		pThis->gSIZE_OF_INTERNAL_BUFFER = pArray->gSIZE_OF_INTERNAL_BUFFER;, )\
	\
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements == NULL) \
			{ \
				pThis->gPrivate_length = 0; \
	\
				CRX_FOR(size_t tI = 0, tI < pArray->gPrivate_length, tI++) \
				{ \
					pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPush(pThis, pArray->gPrivate_buffer + tI); \
	\
					CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
					pFUNC_ELEMENT_MOVE_DESTRUCTOR(pArray->gPrivate_buffer + tI), ); \
				} \
				CRX_ENDFOR \
			} \
			else \
			{ \
				pThis->gPrivate_length = pArray->gPrivate_length; \
	\
				pArray->gPrivate_elements = NULL; \
				pArray->gPrivate_capacity = CRX__C__Array__ECHO_SIZE_OF_INTERNAL_BUFFER( \
						pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pArray, pDEFAULT_SIZE_OF_INTERNAL_BUFFER); \
			} \
		) \
		( \
			pThis->gPrivate_length = pArray->gPrivate_length; \
	\
			pArray->gPrivate_elements = NULL; \
			pArray->gPrivate_capacity = 0; \
		) \
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
						pArray->gPrivate_capacity, pArray->gSIZE_OF_INTERNAL_BUFFER), \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(pThis, pArray->gPrivate_capacity)); \
	\
		if(pArray->gPrivate_length > 0) \
		{ \
			pELEMENT_TYPE * tTarget = NULL; \
\
			CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
			( \
				if(pThis->gPrivate_elements != NULL) \
					{tTarget = pThis->gPrivate_elements;} \
				else \
					{tTarget = pThis->gPrivate_buffer;}	\
			) \
			( \
				tTarget = pThis->gPrivate_elements; \
			) \
\
			CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
			( \
				if(pArray->gPrivate_elements != NULL) \
				{ \
					CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
					( \
						CRX_FOR(size_t tI = 0, tI < pArray->gPrivate_length, tI++) \
						{ \
							pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + tI, \
									pArray->gPrivate_elements + tI); \
						} \
						CRX_ENDFOR \
					) \
					( \
						memcpy(tTarget, \
								pArray->gPrivate_elements, \
								pArray->gPrivate_length * sizeof(pELEMENT_TYPE)); \
					) \
				} \
				else \
				{ \
					CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
					( \
						CRX_FOR(size_t tI = 0, tI < pArray->gPrivate_length, tI++) \
						{ \
							pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + tI, \
									pArray->gPrivate_buffer + tI); \
						} \
						CRX_ENDFOR \
					) \
					( \
						memcpy(tTarget, \
								pArray->gPrivate_buffer, \
								pArray->gPrivate_length * sizeof(pELEMENT_TYPE)); \
					) \
				} \
			) \
			( \
				CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
				( \
					CRX_FOR(size_t tI = 0, tI < pArray->gPrivate_length, tI++) \
					{ \
						pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + tI, \
								pArray->gPrivate_elements + tI); \
					} \
					CRX_ENDFOR \
				) \
				( \
					memcpy(tTarget, \
							pArray->gPrivate_elements, \
							pArray->gPrivate_length * sizeof(pELEMENT_TYPE)); \
				) \
			) \
\
			pThis->gPrivate_length = pArray->gPrivate_length; \
		} \
	)} \
	CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(size_t pCapacity CRX_DEFAULT(0), \
			size_t pSizeOfInternalBuffer CRX_DEFAULT(0)), \
	PUBLIC pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(size_t pCapacity CRX_DEFAULT(0))) \
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
				{pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(vReturn, pCapacity, pSizeOfInternalBuffer);} \
		) \
		( \
			vReturn = (pARRAY_TYPE_NAME *)(calloc(1, sizeof(pARRAY_TYPE_NAME))); \
	\
			if(vReturn != NULL) \
				{pARRAY_MEMBER_FUNCTIONS_PREFIX ## construct(vReturn, pCapacity);} \
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
	PRIVATE pARRAY_TYPE_NAME * pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_new2(pARRAY_TYPE_NAME const * pArray, \
			size_t pStartIndex, size_t pWidth) \
	{ \
		CRX_SCOPE_META \
		assert(pStartIndex + pWidth <= pArray->gPrivate_length); \
	\
		CRX_SCOPE \
		pARRAY_TYPE_NAME * vReturn = CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(pWidth, 0), \
				pARRAY_MEMBER_FUNCTIONS_PREFIX ## new(pWidth)); \
	\
		if((vReturn != NULL) && (pWidth > 0)) \
		{ \
			pELEMENT_TYPE * tTarget = NULL; \
	\
			CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
			( \
				if(vReturn->gPrivate_elements != NULL) \
					{tTarget = vReturn->gPrivate_elements;} \
				else \
					{tTarget = vReturn->gPrivate_buffer;}	\
			) \
			( \
				tTarget = vReturn->gPrivate_elements; \
			) \
	\
			CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
			( \
				if(pArray->gPrivate_elements != NULL) \
				{ \
					CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
					( \
						CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
						{ \
							pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + tI, \
									pArray->gPrivate_elements + pStartIndex + tI); \
						} \
						CRX_ENDFOR \
					) \
					( \
						memcpy(tTarget, \
								pArray->gPrivate_elements + (pStartIndex * sizeof(pELEMENT_TYPE)), \
								pWidth * sizeof(pELEMENT_TYPE)); \
					) \
				} \
				else \
				{ \
					CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
					( \
						CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
						{ \
							pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + tI, \
									pArray->gPrivate_buffer + pStartIndex + tI); \
						} \
						CRX_ENDFOR \
					) \
					( \
						memcpy(tTarget, \
								pArray->gPrivate_buffer + (pStartIndex * sizeof(pELEMENT_TYPE)), \
								pWidth * sizeof(pELEMENT_TYPE)); \
					) \
				} \
			) \
			( \
				CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
				( \
					CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
					{ \
						pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + tI, \
								pArray->gPrivate_elements + pStartIndex + tI); \
					} \
					CRX_ENDFOR \
				) \
				( \
					memcpy(tTarget, \
							pArray->gPrivate_elements + (pStartIndex * sizeof(pELEMENT_TYPE)), \
							pWidth * sizeof(pELEMENT_TYPE)); \
				) \
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
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements != NULL) \
			{ \
				CRX_FOR(size_t tI = pStartIndex, tI <= pEndIndex, tI++) \
					{pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements + tI);} \
				CRX_ENDFOR \
			} \
			else \
			{ \
				CRX_FOR(size_t tI = pStartIndex, tI <= pEndIndex, tI++) \
					{pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_buffer + tI);} \
				CRX_ENDFOR \
			} \
		) \
		( \
			CRX_FOR(size_t tI = pStartIndex, tI <= pEndIndex, tI++) \
				{pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements + tI);} \
			CRX_ENDFOR \
		) \
	}, )\
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## destruct(pARRAY_TYPE_NAME * pThis) \
	{ \
		CRXM__IFELSE(pFUNC_ELEMENT_DESTRUCTOR) \
		( \
			if(pThis->gPrivate_length > 0) \
				{pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct(pThis, 0, pThis->gPrivate_length - 1);} \
		)() \
	 \
		if(pThis->gPrivate_elements != NULL) \
		{ \
			free(pThis->gPrivate_elements); \
	\
			pThis->gPrivate_elements = NULL; \
		} \
	} \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## free(pARRAY_TYPE_NAME * pThis) \
		{free(pThis);} \
	\
	CRX__C__TYPE_BLUE_PRINT__DEFINE_GET_BLUE_PRINT( \
			pARRAY_TYPE_NAME, pARRAY_MEMBER_FUNCTIONS_PREFIX, \
			CRXM__NOT(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD), CRXM__TRUE, \
			pIS_COPYABLE, CRXM__TRUE, \
			CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), CRXM__FALSE); \
	\
	PUBLIC pSIZE_T pARRAY_MEMBER_FUNCTIONS_PREFIX ## getLength(pARRAY_TYPE_NAME const * pThis) \
		{return pThis->gPrivate_length;} \
	PUBLIC pSIZE_T pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCapacity(pARRAY_TYPE_NAME const * pThis) \
		{return pThis->gPrivate_capacity;} \
	\
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## ensureCapacity(pARRAY_TYPE_NAME * pThis, size_t pCapacity) \
	{ \
		CRX_SCOPE_META \
		assert(pCapacity <= pSIZE_T_MAX); \
	\
		if(pCapacity <= pThis->gPrivate_capacity) \
			{return true;} \
		else if(pCapacity > ((pSIZE_T_MAX >> 1) + 1)) \
			{return false;} \
	\
		CRX_SCOPE \
		pSIZE_T vCapacity = (CRXM__IFELSE2(pHAS_INTERNAL_BUFFER, \
				pThis->gPrivate_capacity, \
				pThis->gPrivate_capacity == 0 ? 1 : pThis->gPrivate_capacity) << 1); \
	\
		while(vCapacity < pCapacity) \
			{vCapacity = (vCapacity << 1);} \
	\
		if(pThis->gPrivate_elements == NULL) \
		{ \
			pThis->gPrivate_elements = (pELEMENT_TYPE *)(malloc(vCapacity * sizeof(pELEMENT_TYPE))); \
	\
			if(pThis->gPrivate_elements != NULL) \
			{ \
				CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
				( \
					CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
					( \
						CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++) \
						{ \
							pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + tI, \
									pThis->gPrivate_buffer + tI); \
						} \
						CRX_ENDFOR \
					) \
					( \
						memcpy(pThis->gPrivate_elements, pThis->gPrivate_buffer, pThis->gPrivate_length * sizeof(pELEMENT_TYPE)); \
					) \
				\
					CRXM__IFELSE(pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
					( \
						CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++) \
							{pFUNC_ELEMENT_MOVE_DESTRUCTOR(pThis->gPrivate_buffer + tI);} \
						CRX_ENDFOR \
					)() \
				)() \
	\
				pThis->gPrivate_capacity = vCapacity; \
	\
				CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
				pThis->gPrivate_isReadyForCArray = false;, ) \
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
				pELEMENT_TYPE * tElements = (pELEMENT_TYPE *)(malloc(vCapacity * sizeof(pELEMENT_TYPE))); \
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
						memcpy(tElements, pThis->gPrivate_elements, pThis->gPrivate_length * sizeof(pELEMENT_TYPE)); \
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
					CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
					pThis->gPrivate_isReadyForCArray = false;, ) \
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
					CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
					pThis->gPrivate_isReadyForCArray = false;, ) \
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
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## emptyAndEnsureCapacity(pARRAY_TYPE_NAME * pThis, \
			size_t pCapacity) \
	{ \
		CRX_SCOPE_META \
		assert(pCapacity <= pSIZE_T_MAX); \
	\
		if((pCapacity <= pThis->gPrivate_capacity) && (pThis->gPrivate_length == 0)) \
			{return true;} \
		else if(pCapacity > ((pSIZE_T_MAX >> 1) + 1)) \
			{return false;} \
	\
		CRX_SCOPE \
		bool vIsNoError = true; \
		pELEMENT_TYPE * vElements = NULL; \
		pSIZE_T vCapacity = pThis->gPrivate_capacity; \
	\
		if(pCapacity > pThis->gPrivate_capacity) \
		{ \
			vCapacity = (CRXM__IFELSE2(pHAS_INTERNAL_BUFFER, \
					pThis->gPrivate_capacity, \
					pThis->gPrivate_capacity == 0 ? 1 : pThis->gPrivate_capacity)); \
	\
			while(vCapacity < pCapacity) \
				{vCapacity = (vCapacity << 1);} \
	\
			CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR)) \
			( \
				vElements = (pELEMENT_TYPE *)(malloc(vCapacity * sizeof(pELEMENT_TYPE))); \
			) \
			( \
				if(pThis->gPrivate_elements != NULL) \
				{ \
					vElements = (pELEMENT_TYPE *)(realloc(pThis->gPrivate_elements, \
							(vCapacity * sizeof(pELEMENT_TYPE)))); \
				} \
				else \
				{ \
					vElements = (pELEMENT_TYPE *)(malloc( \
							(vCapacity * sizeof(pELEMENT_TYPE)))); \
				} \
			) \
\
			if(vElements == NULL) \
				{vIsNoError = false;} \
		} \
	\
		if(vIsNoError) \
		{ \
			CRXM__IFELSE(pFUNC_ELEMENT_DESTRUCTOR) \
			( \
				if(pThis->gPrivate_length > 0) \
				{ \
					pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_unsafeCallElementsDestruct(pThis, 0, \
							pThis->gPrivate_length - 1); \
				} \
			)() \
	\
			if(vElements != NULL) \
			{ \
				free(pThis->gPrivate_elements); \
				pThis->gPrivate_elements = vElements; \
	\
				pThis->gPrivate_capacity = vCapacity; \
	\
				CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
				pThis->gPrivate_isReadyForCArray = false;, ) \
			} \
	\
			pThis->gPrivate_length = 0; \
	\
			return true; \
		} \
		else \
			{return false;} \
		CRX_SCOPE_END \
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
		pThis->gPrivate_length = 0; \
	} \
	\
	PRIVATE bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_insertSpaceAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			size_t pWidth) \
	{ \
		CRX_SCOPE_META \
		assert(pIndex <= pThis->gPrivate_length); \
	\
		CRX_SCOPE \
		bool vIsNoError = true; \
	\
		if(pWidth + pThis->gPrivate_length > pThis->gPrivate_capacity) \
			{vIsNoError = pARRAY_MEMBER_FUNCTIONS_PREFIX ## ensureCapacity(pThis, pWidth + pThis->gPrivate_length);} \
	\
		if(!vIsNoError) \
			{return false;} \
		else \
		{ \
			pELEMENT_TYPE * vTarget = NULL; \
	\
			CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
			( \
				if(pThis->gPrivate_elements != NULL) \
					{vTarget = pThis->gPrivate_elements;} \
				else \
					{vTarget = pThis->gPrivate_buffer;} \
			) \
			( \
				vTarget = pThis->gPrivate_elements; \
			) \
	\
			CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR)) \
			( \
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
				( \
					CRX_FOR(size_t tI = pThis->gPrivate_length - 1, tI >= pIndex, tI--) \
					{ \
						pFUNC_ELEMENT_MOVE_CONSTRUCTOR( \
								vTarget + tI + pWidth, \
								vTarget + tI); \
	\
						CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
						pFUNC_ELEMENT_MOVE_DESTRUCTOR(vTarget + tI);, ) \
					} \
					CRX_ENDFOR \
				) \
				({ \
					size_t tI; \
	\
					CRX_FOR(tI = pThis->gPrivate_length - pWidth, tI >= pIndex + pWidth, tI = tI - pWidth) \
					{ \
						memmove(vTarget + tI + pWidth, vTarget + tI, pWidth * sizeof(pELEMENT_TYPE)); \
	\
						CRX_FOR(size_t tI2 = tI, tI2 < tI + pWidth, tI2++) \
							{pFUNC_ELEMENT_MOVE_DESTRUCTOR(vTarget + tI2);} \
						CRX_ENDFOR \
					} \
					CRX_ENDFOR \
	\
					CRX_FOR(tI = tI + pWidth - 1, tI >= pIndex, tI--) \
					{ \
						memmove(vTarget + tI + pWidth, vTarget + tI, sizeof(pELEMENT_TYPE)); \
	\
						pFUNC_ELEMENT_MOVE_DESTRUCTOR(vTarget + tI); \
					} \
					CRX_ENDFOR \
				}) \
			) \
			( \
				memmove(vTarget + pIndex + pWidth, vTarget + pIndex, \
						(pThis->gPrivate_length - pIndex) * sizeof(pELEMENT_TYPE)); \
			) \
	\
			pThis->gPrivate_length = pThis->gPrivate_length + ((pSIZE_T)pWidth); \
	\
			return true; \
		} \
		CRX_SCOPE_END \
	} \
	\
	PRIVATE void pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			size_t pWidth) \
	{ \
		CRX_SCOPE_META \
		assert(pIndex <= pThis->gPrivate_length); \
		assert(pWidth + pThis->gPrivate_length <= pThis->gPrivate_capacity); \
	\
		CRX_SCOPE \
		pELEMENT_TYPE * vTarget = NULL; \
	\
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements != NULL) \
				{vTarget = pThis->gPrivate_elements;} \
			else \
				{vTarget = pThis->gPrivate_buffer;} \
		) \
		( \
			vTarget = pThis->gPrivate_elements; \
		) \
	\
		CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR)) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				CRX_FOR(size_t tI = pThis->gPrivate_length - 1, tI >= pIndex, tI--) \
				{ \
					pFUNC_ELEMENT_MOVE_CONSTRUCTOR( \
							vTarget + tI + pWidth, \
							vTarget + tI); \
\
					CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
					pFUNC_ELEMENT_MOVE_DESTRUCTOR(vTarget + tI);, ) \
				} \
				CRX_ENDFOR \
			) \
			( \
				size_t tI; \
\
				CRX_FOR(tI = pThis->gPrivate_length - pWidth, tI >= pIndex + pWidth, tI = tI - pWidth) \
				{ \
					memmove(vTarget + tI + pWidth, vTarget + tI, pWidth * sizeof(pELEMENT_TYPE)); \
\
					CRX_FOR(size_t tI2 = tI, tI2 < tI + pWidth, tI2++) \
						{pFUNC_ELEMENT_MOVE_DESTRUCTOR(vTarget + tI2);} \
					CRX_ENDFOR \
				} \
				CRX_ENDFOR \
\
				CRX_FOR(tI = tI + pWidth - 1, tI >= pIndex, tI--) \
				{ \
					memmove(vTarget + tI + pWidth, vTarget + tI, sizeof(pELEMENT_TYPE)); \
\
					pFUNC_ELEMENT_MOVE_DESTRUCTOR(vTarget + tI); \
				} \
				CRX_ENDFOR \
			) \
		) \
		( \
			memmove(vTarget + pIndex + pWidth, vTarget + pIndex, \
					(pThis->gPrivate_length - pIndex) * sizeof(pELEMENT_TYPE)); \
		) \
\
		pThis->gPrivate_length = pThis->gPrivate_length + ((pSIZE_T)pWidth); \
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
			if(pARRAY_MEMBER_FUNCTIONS_PREFIX ## emptyAndEnsureCapacity(pThis, pWidth)) \
			{ \
				if(pWidth == 0) \
					{vReturn = true;} \
				else \
				{ \
					pELEMENT_TYPE * tTarget = NULL; \
	\
					CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
					( \
						if(pThis->gPrivate_elements != NULL) \
							{tTarget = pThis->gPrivate_elements;} \
						else \
							{tTarget = pThis->gPrivate_buffer;}	\
					) \
					( \
						tTarget = pThis->gPrivate_elements; \
					) \
		\
					CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
					( \
						if(vArray->gPrivate_elements != NULL) \
						{ \
							CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
							( \
								CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
								{ \
									pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + tI, \
											vArray->gPrivate_elements + pStartIndex + tI); \
								} \
								CRX_ENDFOR \
							) \
							( \
								memcpy(tTarget, \
										vArray->gPrivate_elements + (pStartIndex * sizeof(pELEMENT_TYPE)), \
										pWidth * sizeof(pELEMENT_TYPE)); \
							) \
						} \
						else \
						{ \
							CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
							( \
								CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
								{ \
									pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + tI, \
											vArray->gPrivate_buffer + pStartIndex + tI); \
								} \
								CRX_ENDFOR \
							) \
							( \
								memcpy(tTarget, \
										vArray->gPrivate_buffer + (pStartIndex * sizeof(pELEMENT_TYPE)), \
										pWidth * sizeof(pELEMENT_TYPE)); \
							) \
						} \
					) \
					( \
						CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
						( \
							CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
							{ \
								pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + tI, \
										vArray->gPrivate_elements + pStartIndex + tI); \
							} \
							CRX_ENDFOR \
						) \
						( \
							memcpy(tTarget, \
									vArray->gPrivate_elements + (pStartIndex * sizeof(pELEMENT_TYPE)), \
									pWidth * sizeof(pELEMENT_TYPE)); \
						) \
					) \
		\
					pThis->gPrivate_length = ((pSIZE_T)pWidth); \
	\
					vReturn = true; \
				} \
			} \
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
	CRXM__IFELSE2(CRXM__AND(CRXM__NOT(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD), \
			pHAS_INTERNAL_BUFFER), \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryToPilferSwapContentWith(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME * pArray) \
	{ \
		if((pThis->gPrivate_elements != NULL) && (pArray->gPrivate_elements != NULL)) \
		{ \
			pELEMENT_TYPE * tElements = pArray->gPrivate_elements; \
			pSIZE_T tLength = pArray->gPrivate_length; \
			pSIZE_T tCapacity = pArray->gPrivate_capacity; \
	\
			pArray->gPrivate_elements = pThis->gPrivate_elements; \
			pArray->gPrivate_length = pThis->gPrivate_length; \
			pArray->gPrivate_capacity = pThis->gPrivate_capacity; \
	\
			pThis->gPrivate_elements = tElements; \
			pThis->gPrivate_length = tLength; \
			pThis->gPrivate_capacity = tCapacity; \
	\
			return true; \
		} \
		else \
			{return false;} \
	}, ) \
	CRXM__IFELSE2(CRXM__NOT(pHAS_INTERNAL_BUFFER), \
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## pilferSwapContentWith(pARRAY_TYPE_NAME * pThis, \
			pARRAY_TYPE_NAME * pArray) \
	{ \
		pELEMENT_TYPE * tElements = pArray->gPrivate_elements; \
		pSIZE_T tLength = pArray->gPrivate_length; \
		pSIZE_T tCapacity = pArray->gPrivate_capacity; \
	\
		pArray->gPrivate_elements = pThis->gPrivate_elements; \
		pArray->gPrivate_length = pThis->gPrivate_length; \
		pArray->gPrivate_capacity = pThis->gPrivate_capacity; \
	\
		pThis->gPrivate_elements = tElements; \
		pThis->gPrivate_length = tLength; \
		pThis->gPrivate_capacity = tCapacity; \
	}, ) \
	\
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndSetAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, pELEMENT_TYPE * pElement) \
	{ \
		assert(pIndex <= pThis->gPrivate_length); \
	\
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements != NULL) \
			{ \
				CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
						pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements + pIndex);, ) \
	\
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
				( \
					pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + pIndex, pElement); \
				) \
				( \
					memcpy(pThis->gPrivate_elements + pIndex, pElement, sizeof(pELEMENT_TYPE)); \
				) \
			} \
			else \
			{ \
				CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
						pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_buffer + pIndex);, ) \
	\
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
				( \
					pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_buffer + pIndex, pElement); \
				) \
				( \
					memcpy(pThis->gPrivate_buffer + pIndex, pElement, sizeof(pELEMENT_TYPE)); \
				) \
			} \
		) \
		( \
			CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
					pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements + pIndex);, ) \
	\
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + pIndex, pElement); \
			) \
			( \
				memcpy(pThis->gPrivate_elements + pIndex, pElement, sizeof(pELEMENT_TYPE)); \
			) \
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
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements != NULL) \
				{return (pThis->gPrivate_elements + pIndex);} \
			else \
				{return (pThis->gPrivate_buffer + pIndex);} \
		) \
		( \
			return (pThis->gPrivate_elements + pIndex); \
		) \
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
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements != NULL) \
			{ \
				CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR)) \
				( \
					CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
					pFUNC_ELEMENT_DESTRUCTOR(pReturn);, ) \
	\
					CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
					( \
						pFUNC_ELEMENT_COPY_CONSTRUCTOR(pReturn, \
								pThis->gPrivate_elements + pIndex); \
					) \
					( \
						memcpy(pReturn, \
								pThis->gPrivate_elements + pIndex, \
								sizeof(pELEMENT_TYPE)); \
					) \
				) \
				( \
					return *(pThis->gPrivate_elements + pIndex); \
				) \
			} \
			else \
			{ \
				CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR)) \
				( \
					CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
					pFUNC_ELEMENT_DESTRUCTOR(pReturn);, ) \
	\
					CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
					( \
						pFUNC_ELEMENT_COPY_CONSTRUCTOR(pReturn, pThis->gPrivate_buffer + pIndex); \
					) \
					( \
						memcpy(pReturn, pThis->gPrivate_buffer + pIndex, sizeof(pELEMENT_TYPE)); \
					) \
				) \
				( \
					return *(pThis->gPrivate_buffer + pIndex); \
				) \
			} \
		) \
		( \
			CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR)) \
			( \
				CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
				pFUNC_ELEMENT_DESTRUCTOR(pReturn);, ) \
	\
				CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
				( \
					pFUNC_ELEMENT_COPY_CONSTRUCTOR(pReturn, \
							pThis->gPrivate_elements + pIndex); \
				) \
				( \
					memcpy(pReturn, \
							pThis->gPrivate_elements + pIndex, \
							sizeof(pELEMENT_TYPE)); \
				) \
			) \
			( \
				return *(pThis->gPrivate_elements + pIndex); \
			) \
		) \
	}, ) \
	\
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryMoveAndPush(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE * pElement) \
	{ \
		bool vIsNoError = true; \
	 \
		if(pThis->gPrivate_length + 1 > pThis->gPrivate_capacity) \
			{vIsNoError = pARRAY_MEMBER_FUNCTIONS_PREFIX ## ensureCapacity(pThis, pThis->gPrivate_length + 1);} \
	\
		if(vIsNoError) \
		{ \
			CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
			( \
				if(pThis->gPrivate_elements != NULL) \
				{ \
					CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
					( \
						pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + pThis->gPrivate_length, pElement); \
					) \
					( \
						memcpy(pThis->gPrivate_elements + pThis->gPrivate_length, pElement, sizeof(pELEMENT_TYPE)); \
					) \
				} \
				else \
				{ \
					CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
					( \
						pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_buffer + pThis->gPrivate_length, pElement); \
					) \
					( \
						memcpy(pThis->gPrivate_buffer + pThis->gPrivate_length, pElement, sizeof(pELEMENT_TYPE)); \
					) \
				} \
			) \
			( \
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
				( \
					pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + pThis->gPrivate_length, pElement); \
				) \
				( \
					memcpy(pThis->gPrivate_elements + pThis->gPrivate_length, pElement, sizeof(pELEMENT_TYPE)); \
				) \
			) \
	\
			pThis->gPrivate_length = pThis->gPrivate_length + 1; \
	\
			return true; \
		} \
		else \
			{return false;} \
	} \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## push(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE const * pElement) \
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
					vReturn = , return) pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryMoveAndPush(pThis, ((pELEMENT_TYPE *)vElement)); \
		) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				memcpy(vElement, pElement, sizeof(pELEMENT_TYPE)); \
	\
				CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), \
						vReturn = , return) pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryMoveAndPush(pThis, ((pELEMENT_TYPE *)vElement)); \
			) \
			( \
				return pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryMoveAndPush(pThis, ((pELEMENT_TYPE *)pElement)); \
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
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastPush(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE * pElement) \
	{ \
		assert(pThis->gPrivate_capacity - pThis->gPrivate_length > 0); \
	\
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements != NULL) \
			{ \
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
				( \
					pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + pThis->gPrivate_length, pElement); \
				) \
				( \
					memcpy(pThis->gPrivate_elements + pThis->gPrivate_length, pElement, sizeof(pELEMENT_TYPE)); \
				) \
			} \
			else \
			{ \
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
				( \
					pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_buffer + pThis->gPrivate_length, pElement); \
				) \
				( \
					memcpy(pThis->gPrivate_buffer + pThis->gPrivate_length, pElement, sizeof(pELEMENT_TYPE)); \
				) \
			} \
		) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + pThis->gPrivate_length, pElement); \
			) \
			( \
				memcpy(pThis->gPrivate_elements + pThis->gPrivate_length, pElement, sizeof(pELEMENT_TYPE)); \
			) \
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
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## push2(pARRAY_TYPE_NAME * pThis, pELEMENT_TYPE pElement) \
	{ \
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
		( \
			if(pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryMoveAndPush(pThis, &pElement)) \
			{ \
				pFUNC_ELEMENT_MOVE_DESTRUCTOR(&pElement); \
	\
				return true; \
			} \
			else \
				{return false;} \
		) \
		( \
			return pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryMoveAndPush(pThis, &pElement); \
		) \
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
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_DESTRUCTOR) \
			( \
				if(pThis->gPrivate_elements != NULL) \
					{pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements + pThis->gPrivate_length);} \
				else \
					{pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_buffer + pThis->gPrivate_length);} \
			)() \
		) \
		( \
			CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
					pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements + pThis->gPrivate_length);, ) \
		) \
	} \
	\
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryMoveAndInsertElementAt(pARRAY_TYPE_NAME * pThis, \
			size_t pIndex, pELEMENT_TYPE * pElement) \
	{ \
		assert(pIndex <= pSIZE_T_MAX); \
	\
		if(pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_insertSpaceAt(pThis, pIndex, 1)) \
		{ \
			CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
			( \
				if(pThis->gPrivate_elements != NULL) \
				{ \
					CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
					( \
						pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + pIndex, pElement); \
					) \
					( \
						memcpy(pThis->gPrivate_elements + pIndex, pElement, sizeof(pELEMENT_TYPE)); \
					) \
				} \
				else \
				{ \
					CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
					( \
						pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_buffer + pIndex, pElement); \
					) \
					( \
						memcpy(pThis->gPrivate_buffer + pIndex, pElement, sizeof(pELEMENT_TYPE)); \
					) \
				} \
			) \
			( \
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
				( \
					pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + pIndex, pElement); \
				) \
				( \
					memcpy(pThis->gPrivate_elements + pIndex, pElement, sizeof(pELEMENT_TYPE)); \
				) \
			) \
	\
			return true; \
		} \
		else \
			{return false;} \
	} \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## insertElementAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pElement) \
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
					vReturn = , return) pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryMoveAndInsertElementAt( \
					pThis, pIndex, ((pELEMENT_TYPE *)vElement)); \
		) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				memcpy(vElement, pElement, sizeof(pELEMENT_TYPE)); \
	\
				CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), \
					vReturn = , return) pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryMoveAndInsertElementAt( \
							pThis, pIndex, ((pELEMENT_TYPE *)vElement)); \
			) \
			( \
				return pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryMoveAndInsertElementAt( \
						pThis, pIndex, ((pELEMENT_TYPE *)pElement)); \
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
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## moveAndFastInsertElementAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE * pElement) \
	{ \
		assert(pIndex <= pSIZE_T_MAX); \
	\
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pThis, pIndex, 1); \
	\
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements != NULL) \
			{ \
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
				( \
					pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + pIndex, pElement); \
				) \
				( \
					memcpy(pThis->gPrivate_elements + pIndex, pElement, sizeof(pELEMENT_TYPE)); \
				) \
			} \
			else \
			{ \
				CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
				( \
					pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_buffer + pIndex, pElement); \
				) \
				( \
					memcpy(pThis->gPrivate_buffer + pIndex, pElement, sizeof(pELEMENT_TYPE)); \
				) \
			} \
		) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + pIndex, pElement); \
			) \
			( \
				memcpy(pThis->gPrivate_elements + pIndex, pElement, sizeof(pELEMENT_TYPE)); \
			) \
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
						CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_CONSTRUCTOR)),  \
				pFUNC_ELEMENT_MOVE_DESTRUCTOR(((pELEMENT_TYPE *)vElement));, ) \
	}, ) \
	\
	CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, CRXM__AND(CRXM__NOT(pFUNC_ELEMENT_COPY_CONSTRUCTOR), \
			CRXM__NOT(pFUNC_ELEMENT_DESTRUCTOR))), \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## insertElementAt2(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE pElement) \
	{ \
		CRXM__IFELSE(pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
		( \
			if(pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryMoveAndInsertElementAt(pThis, pIndex, \
					&pElement)) \
			{ \
				pFUNC_ELEMENT_MOVE_DESTRUCTOR(&pElement); \
	\
				return true; \
			} \
			else \
				{return false;} \
		) \
		( \
			return pARRAY_MEMBER_FUNCTIONS_PREFIX ## tryMoveAndInsertElementAt(pThis, pIndex, \
					&pElement); \
		) \
	}, ) \
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
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## insertElementsAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pARRAY_TYPE_NAME const * pArray, size_t pStartIndex, size_t pWidth) \
	{ \
		CRX_SCOPE_META \
		assert(pIndex <= pSIZE_T_MAX); \
		assert(pStartIndex <= pSIZE_T_MAX); \
		assert(pWidth <= pSIZE_T_MAX); \
	\
		if(pWidth == 0) \
			{return true;} \
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
			if(pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_insertSpaceAt(pThis, pIndex, pWidth)) \
			{ \
				CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
				( \
					pELEMENT_TYPE * tTarget; \
					pELEMENT_TYPE * tSource; \
		\
					if(pThis->gPrivate_elements != NULL) \
						{tTarget = pThis->gPrivate_elements;} \
					else \
						{tTarget = pThis->gPrivate_buffer;} \
		\
					if(vArray->gPrivate_elements != NULL) \
						{tSource = vArray->gPrivate_elements;} \
					else \
						{tSource = vArray->gPrivate_buffer;} \
		\
					CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
					( \
						CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
						{ \
							pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + pIndex + tI, tSource + pStartIndex + tI); \
						} \
						CRX_ENDFOR \
					) \
					( \
						memcpy(tTarget + pIndex, tSource + pStartIndex, pWidth * sizeof(pELEMENT_TYPE)); \
					) \
				) \
				( \
					CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
					( \
						CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
						{ \
							pFUNC_ELEMENT_COPY_CONSTRUCTOR(pThis->gPrivate_elements + pIndex + tI, vArray->gPrivate_elements + pStartIndex + tI); \
						} \
						CRX_ENDFOR \
					) \
					( \
						memcpy(pThis->gPrivate_elements + pIndex, vArray->gPrivate_elements + pStartIndex, pWidth * sizeof(pELEMENT_TYPE)); \
					) \
				) \
		\
				vReturn = true; \
			} \
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
	PUBLIC void pARRAY_MEMBER_FUNCTIONS_PREFIX ## fastInsertElementsAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
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
		CRXM__IFELSE2(pHAS_INTERNAL_BUFFER, \
		pELEMENT_TYPE * tTarget;, ) \
		CRXM__IFELSE2(pHAS_INTERNAL_BUFFER, \
		pELEMENT_TYPE const * tSource;, ) \
	\
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pThis, pIndex, pWidth); \
	\
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements != NULL) \
				{tTarget = pThis->gPrivate_elements;} \
			else \
				{tTarget = pThis->gPrivate_buffer;} \
	\
			if(pArray->gPrivate_elements != NULL) \
				{tSource = pArray->gPrivate_elements;} \
			else \
				{tSource = pArray->gPrivate_buffer;} \
	\
			CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
				{ \
					pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + pIndex + tI, tSource + pStartIndex + tI); \
				} \
				CRX_ENDFOR \
			) \
			( \
				memcpy(tTarget + pIndex, tSource + pStartIndex, pWidth * sizeof(pELEMENT_TYPE)); \
			) \
		) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
				{ \
					pFUNC_ELEMENT_COPY_CONSTRUCTOR(pThis->gPrivate_elements + pIndex + tI, pArray->gPrivate_elements + pStartIndex + tI); \
				} \
				CRX_ENDFOR \
			) \
			( \
				memcpy(pThis->gPrivate_elements + pIndex, pArray->gPrivate_elements + pStartIndex, pWidth * sizeof(pELEMENT_TYPE)); \
			) \
		) \
		CRX_SCOPE_END \
	}, ) \
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## insertCArrayAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pArray, size_t pWidth) \
	{ \
		assert(pIndex <= pSIZE_T_MAX); \
		assert(pWidth <= pSIZE_T_MAX); \
	\
		if(pWidth == 0) \
			{return true;} \
	\
		if(pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_insertSpaceAt(pThis, pIndex, pWidth)) \
		{ \
			pELEMENT_TYPE * tTarget; \
	\
			CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
			( \
				if(pThis->gPrivate_elements != NULL) \
					{tTarget = pThis->gPrivate_elements;} \
				else \
					{tTarget = pThis->gPrivate_buffer;} \
			) \
			( \
				tTarget = pThis->gPrivate_elements; \
			) \
	\
			CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
				{ \
					pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + pIndex + tI, pArray + tI); \
				} \
				CRX_ENDFOR \
			) \
			( \
				memcpy(tTarget + pIndex, pArray, pWidth * sizeof(pELEMENT_TYPE)); \
			) \
	\
			return true; \
		} \
		else \
			{return false;} \
	}, ) \
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
		pELEMENT_TYPE * tTarget; \
	\
		pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_fastInsertSpaceAt(pThis, pIndex, pWidth); \
	\
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements != NULL) \
				{tTarget = pThis->gPrivate_elements;} \
			else \
				{tTarget = pThis->gPrivate_buffer;} \
		) \
		( \
			tTarget = pThis->gPrivate_elements; \
		) \
\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < pWidth, tI++) \
			{ \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + pIndex + tI, pArray + tI); \
			} \
			CRX_ENDFOR \
		) \
		( \
			memcpy(tTarget + pIndex, pArray, pWidth * sizeof(pELEMENT_TYPE)); \
		) \
		CRX_SCOPE_END \
	}, ) \
	\
	CRXM__IFELSE2(pIS_COPYABLE, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## insertElementCopiesAt(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE const * pElement, size_t pNumberOfCopies) \
	{ \
		assert(pIndex <= pSIZE_T_MAX); \
		assert(pNumberOfCopies <= pSIZE_T_MAX); \
	\
		if(pNumberOfCopies == 0) \
			{return true;} \
	\
		if(pARRAY_MEMBER_FUNCTIONS_PREFIX ## private_insertSpaceAt(pThis, pIndex, pNumberOfCopies)) \
		{ \
			pELEMENT_TYPE * tTarget; \
	\
			CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
			( \
				if(pThis->gPrivate_elements != NULL) \
					{tTarget = pThis->gPrivate_elements;} \
				else \
					{tTarget = pThis->gPrivate_buffer;} \
			) \
			( \
				tTarget = pThis->gPrivate_elements; \
			) \
	\
			CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				CRX_FOR(size_t tI = 0, tI < pNumberOfCopies, tI++) \
				{ \
					pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + pIndex + tI, pElement); \
				} \
				CRX_ENDFOR \
			) \
			({ \
				size_t tNumberOfCopies = 1; \
				size_t tRemainingNumberOfCopies = pNumberOfCopies - 1; \
	\
				memcpy(tTarget + pIndex, pElement, sizeof(pELEMENT_TYPE));\
	\
				while(tRemainingNumberOfCopies > 0) \
				{ \
					if(tRemainingNumberOfCopies >= tNumberOfCopies) \
					{ \
						memcpy(tTarget + pIndex + tNumberOfCopies, tTarget + pIndex, \
								tNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
						tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies; \
						tNumberOfCopies = (tNumberOfCopies << 1); \
					} \
					else \
					{ \
						memcpy(tTarget + pIndex + tNumberOfCopies, tTarget + pIndex, \
								tRemainingNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
						break; \
					} \
				} \
			}) \
	\
			return true; \
		} \
		else \
			{return false;} \
	}, ) \
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
		pELEMENT_TYPE * tTarget; \
	\
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements != NULL) \
				{tTarget = pThis->gPrivate_elements;} \
			else \
				{tTarget = pThis->gPrivate_buffer;} \
		) \
		( \
			tTarget = pThis->gPrivate_elements; \
		) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < pNumberOfCopies, tI++) \
			{ \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(tTarget + pIndex + tI, pElement); \
			} \
			CRX_ENDFOR \
		) \
		({ \
			size_t tNumberOfCopies = 1; \
			size_t tRemainingNumberOfCopies = pNumberOfCopies - 1; \
	\
			memcpy(tTarget + pIndex, pElement, sizeof(pELEMENT_TYPE));\
	\
			while(tRemainingNumberOfCopies > 0) \
			{ \
				if(tRemainingNumberOfCopies >= tNumberOfCopies) \
				{ \
					memcpy(tTarget + pIndex + tNumberOfCopies, tTarget + pIndex, \
							tNumberOfCopies * sizeof(pELEMENT_TYPE)); \
	\
					tRemainingNumberOfCopies = tRemainingNumberOfCopies - tNumberOfCopies; \
					tNumberOfCopies = (tNumberOfCopies << 1); \
				} \
				else \
				{ \
					memcpy(tTarget + pIndex + tNumberOfCopies, tTarget + pIndex, \
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
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## insertElementCopiesAt2(pARRAY_TYPE_NAME * pThis, size_t pIndex, \
			pELEMENT_TYPE pElement, size_t pNumberOfCopies) \
	{ \
		return pARRAY_MEMBER_FUNCTIONS_PREFIX ## insertElementCopiesAt(pThis, pIndex, &pElement, pNumberOfCopies); \
	}, ) \
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
		CRX_SCOPE_META \
		assert((pWidth == 0) || ((pIndex < pThis->gPrivate_length) && (pIndex + pWidth <= pThis->gPrivate_length))); \
	\
		if(pWidth == 0) \
			{return;} \
	\
		CRX_SCOPE \
		pELEMENT_TYPE * tTarget; \
	\
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements != NULL) \
				{tTarget = pThis->gPrivate_elements;} \
			else \
				{tTarget = pThis->gPrivate_buffer;} \
		) \
		( \
			tTarget = pThis->gPrivate_elements; \
		) \
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
					pFUNC_ELEMENT_MOVE_CONSTRUCTOR(tTarget + tI + pIndex, \
							tTarget + tI + pIndex + pWidth); \
	\
					CRXM__IFELSE2(pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
							pFUNC_ELEMENT_MOVE_DESTRUCTOR(tTarget + \
							tI + pIndex + pWidth);, ) \
				} \
				CRX_ENDFOR \
			) \
			( \
				CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length - pWidth - pIndex, tI++) \
				{ \
					memmove(tTarget + tI + pIndex, \
							tTarget + tI + pIndex + pWidth, \
							sizeof(pELEMENT_TYPE)); \
	\
					pFUNC_ELEMENT_MOVE_DESTRUCTOR(tTarget + \
							tI + pIndex + pWidth); \
				} \
				CRX_ENDFOR \
			) \
		) \
		( \
			memmove(tTarget + pIndex, tTarget + pIndex + pWidth, \
					(pThis->gPrivate_length + 1 - pIndex - pWidth) * sizeof(pELEMENT_TYPE)); \
		) \
	\
		pThis->gPrivate_length = ((pSIZE_T)(pThis->gPrivate_length - pWidth)); \
		CRX_SCOPE_END \
	} \
	\
	PUBLIC pELEMENT_TYPE * pARRAY_MEMBER_FUNCTIONS_PREFIX ## getElementsPointer(pARRAY_TYPE_NAME * pThis) \
	{ \
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements != NULL) \
				{return pThis->gPrivate_elements;} \
			else \
				{return pThis->gPrivate_buffer;} \
		) \
		( \
			return pThis->gPrivate_elements; \
		) \
	} \
	PUBLIC pELEMENT_TYPE const * pARRAY_MEMBER_FUNCTIONS_PREFIX ## constantGetElementsPointer(pARRAY_TYPE_NAME const * pThis) \
		{return pARRAY_MEMBER_FUNCTIONS_PREFIX ## getElementsPointer((pARRAY_TYPE_NAME *) pThis);} \
	\
	CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
	PUBLIC pELEMENT_TYPE * pARRAY_MEMBER_FUNCTIONS_PREFIX ## getCArray(pARRAY_TYPE_NAME * pThis, \
			pELEMENT_TYPE pElement) \
	{ \
		if(!pThis->gPrivate_isReadyForCArray) \
		{ \
			pARRAY_MEMBER_FUNCTIONS_PREFIX ## insertElementCopiesAt2(pThis, pThis->gPrivate_length, \
					pElement, pThis->gPrivate_capacity - pThis->gPrivate_length); \
	\
			pThis->gPrivate_isReadyForCArray = true; \
		} \
	\
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements != NULL) \
				{return pThis->gPrivate_elements;} \
			else \
				{return pThis->gPrivate_buffer;} \
		) \
		( \
			return pThis->gPrivate_elements; \
		) \
	}, ) \
	CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
	PUBLIC pELEMENT_TYPE * pARRAY_MEMBER_FUNCTIONS_PREFIX ## unsafeGetCArray( \
			pARRAY_TYPE_NAME * pThis) \
	{ \
		CRXM__IFELSE(pHAS_INTERNAL_BUFFER) \
		( \
			if(pThis->gPrivate_elements != NULL) \
				{return pThis->gPrivate_elements;} \
			else \
				{return pThis->gPrivate_buffer;} \
		) \
		( \
			return pThis->gPrivate_elements; \
		) \
	}, ) \
	CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## updateLength(pARRAY_TYPE_NAME * pThis, \
			size_t pLength) \
	{ \
		if((pLength > pThis->gPrivate_capacity) || !pThis->gPrivate_isReadyForCArray) \
			{return false;} \
	\
		pThis->gPrivate_length = pLength; \
	\
		return true; \
	}, ) \
	CRXM__IFELSE2(pIS_TO_ENABLE_C_ARRAY, \
	PUBLIC bool pARRAY_MEMBER_FUNCTIONS_PREFIX ## unsafeUpdateLength(pARRAY_TYPE_NAME * pThis, \
			size_t pLength) \
	{ \
		if(pLength > pThis->gPrivate_capacity) \
			{return false;} \
	\
		pThis->gPrivate_length = pLength; \
	\
		return true; \
	}, ) \
//#END_DEFINE


#define CRX__C__Array__ECHO_SIZE_OF_INTERNAL_BUFFER(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pTHIS, \
				pDEFAULT_SIZE_OF_INTERNAL_BUFFER) \
		CRXM__IFELSE2(pIS_TO_ENABLE_SIZE_OF_INTERNAL_BUFFER_FIELD, pTHIS->gSIZE_OF_INTERNAL_BUFFER, pDEFAULT_SIZE_OF_INTERNAL_BUFFER)



#if(CRX__ARE_ONLY_POINTERS_TO_SAME_OBJECT_EQUAL_AND_ALWAYS)
typedef struct Crx_C_Array
{
	Crx_C_TypeBluePrint const * CRX_NOT_MINE gPrivate_typeBluePrint;
	size_t gSIZE_OF_INTERNAL_BUFFER;
	unsigned char * gPrivate_elements;
	unsigned char * gPrivate_internalBuffer;
	size_t gPrivate_length;
	size_t gPrivate_capacity;
	unsigned char gPrivate_buffer[1 /*N*/]; /*KEEP THIS ALIGNED AT 16 BYTES RELATIVE TO STRUCTURE WHEN 64BIT*/
} Crx_C_Array;

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_array_getByteSizeOf(
		Crx_C_Array const * CRX_NOT_NULL pArray);
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_array_getByteSizeFor(
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint, bool pIsInternalBufferExternal, 
		size_t pSizeOfInternalBuffer);
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_array_private_doInit(Crx_C_Array * pThis, 
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint, size_t pSizeOfInternalBuffer, 
		size_t pCapacity);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_construct(Crx_C_Array * pThis, 
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint, size_t pSizeOfInternalBuffer, 
		size_t pCapacity);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_construct2(Crx_C_Array * pThis, 
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint, 
		unsigned char * CRX_NOT_NULL pBufferOnStack, size_t pSizeOfBufferOnStack, size_t pCapacity);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_moveConstruct(Crx_C_Array * pThis, 
		Crx_C_Array * CRX_NOT_NULL pArray);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_copyConstruct(Crx_C_Array * pThis, 
		Crx_C_Array const * CRX_NOT_NULL pArray);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Array * crx_c_array_new(
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint,
		size_t pSizeOfInternalBuffer CRX_DEFAULT(0), size_t pCapacity CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Array * crx_c_array_new2(
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint, 
		unsigned char * CRX_NOT_NULL pBufferOnStack, size_t pSizeOfInternalBuffer CRX_DEFAULT(0), 
		size_t pCapacity CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Array * crx_c_array_moveNew(Crx_C_Array * CRX_NOT_NULL pArray);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Array * crx_c_array_copyNew(
		Crx_C_Array const * CRX_NOT_NULL pArray);
CRX__LIB__PRIVATE_C_FUNCTION() Crx_C_Array * crx_c_array_private_new2(Crx_C_Array * pArray, 
		size_t pStartIndex, size_t pWidth);
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_array_private_unsafeCallElementsDestruct(
		Crx_C_Array * pThis, size_t pStartIndex, size_t pEndIndex);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_destruct(Crx_C_Array * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_free(Crx_C_Array * pThis);
CRX__C__TYPE_BLUE_PRINT__GENERIC__DECLARE_GET_BLUE_PRINT(
		Crx_C_Array, crx_c_array_,
		CRXM__FALSE, CRXM__TRUE,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__TRUE, CRXM__FALSE);
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_array_getLength(Crx_C_Array * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_array_getCapacity(Crx_C_Array * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_ensureCapacity(Crx_C_Array * pThis, size_t pCapacity);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_emptyAndEnsureCapacity(Crx_C_Array * pThis,
		size_t pCapacity);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_empty(Crx_C_Array * pThis);
CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_array_private_insertSpaceAt(Crx_C_Array * pThis, 
		size_t pIndex, size_t pWidth);
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_array_private_fastInsertSpaceAt(Crx_C_Array * pThis, 
		size_t pIndex, size_t pWidth);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_copyAssignFrom2(Crx_C_Array * pThis, 
		Crx_C_Array * CRX_NOT_NULL pArray, size_t pStartIndex, size_t pWidth);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_copyAssignFrom(Crx_C_Array * pThis, 
		Crx_C_Array * CRX_NOT_NULL pArray);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_moveAndSetAt(Crx_C_Array * pThis, size_t pIndex, 
		void * CRX_NOT_NULL pElement);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_setAt(Crx_C_Array * pThis, size_t pIndex, 
		void * CRX_NOT_NULL pElement);
CRX__LIB__PUBLIC_C_FUNCTION() unsigned char * crx_c_array_get(Crx_C_Array * pThis, size_t pIndex);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_copyGetTo(Crx_C_Array const * pThis, 
		unsigned char * CRX_NOT_NULL pReturn, size_t pIndex);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_tryMoveAndPush(Crx_C_Array * pThis, 
		void * CRX_NOT_NULL pElement);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_push(Crx_C_Array * pThis, 
		void * CRX_NOT_NULL pElement);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_moveAndFastPush(Crx_C_Array * pThis, 
		void * CRX_NOT_NULL pElement);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_fastPush(Crx_C_Array * pThis, 
		void * CRX_NOT_NULL pElement);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_pop(Crx_C_Array * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_tryMoveAndInsertElementAt(Crx_C_Array * pThis, 
		size_t pIndex, void * CRX_NOT_NULL pElement);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_insertElementAt(Crx_C_Array * pThis, size_t pIndex, 
		void * CRX_NOT_NULL pElement);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_moveAndFastInsertElementAt(Crx_C_Array * pThis, 
		size_t pIndex, void * CRX_NOT_NULL pElement);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_fastInsertElementAt(Crx_C_Array * pThis, 
		size_t pIndex, void * CRX_NOT_NULL pElement);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_insertElementsAt(Crx_C_Array * pThis, size_t pIndex,
		Crx_C_Array * CRX_NOT_NULL pArray, size_t pStartIndex, size_t pWidth);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_fastInsertElementsAt(Crx_C_Array * pThis, 
		size_t pIndex, Crx_C_Array * CRX_NOT_NULL pArray, size_t pStartIndex, size_t pWidth);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_insertCArrayAt(Crx_C_Array * pThis, size_t pIndex,
		void * pArray, size_t pWidth);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_fastInsertCArrayAt(Crx_C_Array * pThis, 
		size_t pIndex, void * CRX_NOT_NULL pArray, size_t pWidth);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_array_insertElementCopiesAt(Crx_C_Array * pThis, 
		size_t pIndex, void * CRX_NOT_NULL pElement, size_t pNumberOfCopies);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_fastInsertElementCopiesAt(Crx_C_Array * pThis, 
		size_t pIndex, void * CRX_NOT_NULL pElement, size_t pNumberOfCopies);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_array_removeElements(Crx_C_Array * pThis, size_t pIndex,
		size_t pWidth);
CRX__LIB__PUBLIC_C_FUNCTION() unsigned char * crx_c_array_getElementsPointer(Crx_C_Array * pThis);

#endif


CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/Array.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif