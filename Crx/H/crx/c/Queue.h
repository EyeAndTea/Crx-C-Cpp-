#if(!defined(CRX__C__QUEUE___h__))
#define CRX__C__QUEUE___h__

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
	#define CRX__C__Queue__DECLARE(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__Queue__DECLARE, __VA_ARGS__)
#else
	#define CRX__C__Queue__DECLARE(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__Queue__DECLARE, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20)
#endif

#define CRX__C__Queue__DECLARE__9(pQUEUE_TYPE_NAME, pQUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pMODE, pNUMBER_OF_ELEMENTS_PER_NODE, pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__Queue__DECLARE(pQUEUE_TYPE_NAME, pQUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pMODE, pNUMBER_OF_ELEMENTS_PER_NODE, pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__FALSE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())


#define CRX__C__Queue__DECLARE__10(pQUEUE_TYPE_NAME, pQUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pMODE, pNUMBER_OF_ELEMENTS_PER_NODE, pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__Queue__DECLARE(pQUEUE_TYPE_NAME, pQUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pMODE, pNUMBER_OF_ELEMENTS_PER_NODE, pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__TRUE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRX__LIB__PUBLIC_C_FUNCTION(), CRX__LIB__PRIVATE_C_FUNCTION())


#define _CRX__C__Queue__DECLARE(pQUEUE_TYPE_NAME, pMEMBER_FUNCTIONS_PREFIX, \
		pMODE, pNUMBER_OF_ELEMENTS_PER_NODE, pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pIS_ELEMENT_COPYABLE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		PUBLIC, PRIVATE) \
	\
	typedef struct pQUEUE_TYPE_NAME ## _Private_Node pQUEUE_TYPE_NAME ## _Private_Node; \
	\
	typedef struct pQUEUE_TYPE_NAME \
	{ \
		pQUEUE_TYPE_NAME ## _Private_Node * gPrivate_rootNode; \
		CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
		pQUEUE_TYPE_NAME ## _Private_Node * gPrivate_lastNode;, ) \
		size_t gPrivate_length; \
		CRXM__IFELSE2(pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		uint8_t gPRIVATE__NODE_CAPACITY;, ) \
	} pQUEUE_TYPE_NAME; \
	\
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_NODE_CAPACITY_FIELD), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## construct(pQUEUE_TYPE_NAME * pThis);, \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## construct(pQUEUE_TYPE_NAME * pThis, \
			size_t pNodeCapacity CRX_DEFAULT(0));) \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## copyConstruct(pQUEUE_TYPE_NAME * pThis, \
			pQUEUE_TYPE_NAME const * CRX_NOT_NULL pQueue); \
	CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_NODE_CAPACITY_FIELD), \
	PUBLIC pQUEUE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## new();, \
	PUBLIC pQUEUE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## new( \
			size_t pNodeCapacity CRX_DEFAULT(0));) \
	PUBLIC pQUEUE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## moveNew( \
			pQUEUE_TYPE_NAME * CRX_NOT_NULL pQueue); \
	PUBLIC pQUEUE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## copyNew( \
			pQUEUE_TYPE_NAME const * CRX_NOT_NULL pQueue); \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## destruct(pQUEUE_TYPE_NAME * pThis); \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## free(pQUEUE_TYPE_NAME * pThis); \
	\
	CRX__C__TYPE_BLUE_PRINT__DECLARE_GET_BLUE_PRINT( \
			pQUEUE_TYPE_NAME, pMEMBER_FUNCTIONS_PREFIX, \
			CRXM__TRUE, CRXM__TRUE, \
			pIS_ELEMENT_COPYABLE, CRXM__TRUE, \
			CRXM__FALSE, CRXM__FALSE); \
	\
	CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK), \
	PRIVATE pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_copyNodes( \
			pQUEUE_TYPE_NAME * pThis, pQUEUE_TYPE_NAME ## _Private_Node * pNode__start);, \
	PRIVATE pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_copyNodes( \
			pQUEUE_TYPE_NAME * pThis, pQUEUE_TYPE_NAME ## _Private_Node * pNode__start, \
			pQUEUE_TYPE_NAME ## _Private_Node * * pNode__lastNode);) \
	\
	PRIVATE pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_removeNodes( \
			pQUEUE_TYPE_NAME * pThis, pQUEUE_TYPE_NAME ## _Private_Node * pNode__start); \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## empty(pQUEUE_TYPE_NAME * pThis); \
	\
	PUBLIC size_t pMEMBER_FUNCTIONS_PREFIX ## getLength(pQUEUE_TYPE_NAME const * pThis); \
	\
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## tryMoveAndPush(pQUEUE_TYPE_NAME * pThis, \
			pELEMENT_TYPE * pElement);, ) \
	CRXM__IFELSE2(CRXM__AND(pIS_ELEMENT_COPYABLE, \
			CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK))), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## push(pQUEUE_TYPE_NAME * pThis, \
			pELEMENT_TYPE * pElement);, ) \
	\
	CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__BIDIRECTIONAL), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## pop(pQUEUE_TYPE_NAME * pThis);, ) \
	\
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__QUEUE)), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## tryMoveAndPushToFront(pQUEUE_TYPE_NAME * pThis, \
			pELEMENT_TYPE * pElement);, ) \
	CRXM__IFELSE2(CRXM__AND(pIS_ELEMENT_COPYABLE, \
			CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__QUEUE))), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## pushToFront(pQUEUE_TYPE_NAME * pThis, \
			pELEMENT_TYPE * pElement);, ) \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## popFromFront(pQUEUE_TYPE_NAME * pThis); \
	\
	CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__BIDIRECTIONAL), \
	PUBLIC pELEMENT_TYPE * pMEMBER_FUNCTIONS_PREFIX ## get(pQUEUE_TYPE_NAME * pThis);, ) \
	CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__BIDIRECTIONAL), \
	PUBLIC pELEMENT_TYPE const * pMEMBER_FUNCTIONS_PREFIX ## constantGet( \
			pQUEUE_TYPE_NAME const * pThis);, ) \
	CRXM__IFELSE2(CRXM__AND(pIS_ELEMENT_COPYABLE, \
			CRXM__IS(pMODE, CRX__C__QUEUE__MODE__BIDIRECTIONAL)), \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## copyGetTo(pQUEUE_TYPE_NAME const * pThis, \
			pELEMENT_TYPE * pReturn);, \
	PUBLIC pELEMENT_TYPE pMEMBER_FUNCTIONS_PREFIX ## copyGet(pQUEUE_TYPE_NAME const * pThis);), ) \
	\
	PUBLIC pELEMENT_TYPE * pMEMBER_FUNCTIONS_PREFIX ## getFront(pQUEUE_TYPE_NAME * pThis); \
	PUBLIC pELEMENT_TYPE const * pMEMBER_FUNCTIONS_PREFIX ## constantGetFront( \
			pQUEUE_TYPE_NAME const * pThis); \
	CRXM__IFELSE2(pIS_ELEMENT_COPYABLE, \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## copyGetFrontTo(pQUEUE_TYPE_NAME const * pThis, \
			pELEMENT_TYPE * pReturn);, \
	PUBLIC pELEMENT_TYPE pMEMBER_FUNCTIONS_PREFIX ## copyGetFront( \
			pQUEUE_TYPE_NAME const * pThis);), ) \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## empty(pQUEUE_TYPE_NAME * pThis); \
	\
	\
	\
	typedef struct pQUEUE_TYPE_NAME ## _Private_Node\
	{ \
		CRX_FRIEND_CLASS(pQUEUE_TYPE_NAME); \
	\
		pQUEUE_TYPE_NAME ## _Private_Node * gPrivate_next; \
		CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
		pQUEUE_TYPE_NAME ## _Private_Node * gPrivate_prev;, ) \
		uint8_t gPrivate_length; \
		CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
		uint8_t gPrivate_startIndex;, ) \
		CRXM__IFELSE2(pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		uint8_t gPRIVATE__NODE_CAPACITY;, ) \
		pELEMENT_TYPE gPrivate_elements[CRXM__IFELSE2(pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
				1, pNUMBER_OF_ELEMENTS_PER_NODE)]; \
	} pQUEUE_TYPE_NAME ## _Private_Node; \
	\
	\
	CRXM__IFELSE2(pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
	PUBLIC size_t pMEMBER_FUNCTIONS_PREFIX ## private_node_getByteSizeOf( \
			pQUEUE_TYPE_NAME ## _Private_Node const * CRX_NOT_NULL pNode), ); \
	CRXM__IFELSE2(pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
	PUBLIC size_t pMEMBER_FUNCTIONS_PREFIX ## private_node_getByteSizeFor( \
			uint8_t pNodeCapacity), ); \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_NODE_CAPACITY_FIELD), \
			CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_construct( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis);, \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_construct( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis, uint8_t pStartIndex);), \
			CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_construct( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis, uint8_t pNodeCapacity);, \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_construct( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis, uint8_t pStartIndex, uint8_t pNodeCapacity);)) \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_copyConstruct( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis, \
			pQUEUE_TYPE_NAME ## _Private_Node const * CRX_NOT_NULL pNode); \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_NODE_CAPACITY_FIELD), \
			CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK), \
	PUBLIC pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_node_new(void);, \
	PUBLIC pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_node_new( \
			uint8_t pStartIndex);), \
			CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK), \
	PUBLIC pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_node_new( \
			uint8_t pNodeCapacity);, \
	PUBLIC pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_node_new( \
			uint8_t pStartIndex, uint8_t pNodeCapacity);)) \
	PUBLIC pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_node_copyNew( \
			pQUEUE_TYPE_NAME ## _Private_Node const * pNode); \
	\
	CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_destruct( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis);, ) \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_free( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis); \
	\
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## private_node_tryMoveAndPush( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis, \
			pELEMENT_TYPE * pElement);, ) \
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## private_node_hasRoomForPush( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis);, ) \
	\
	CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__BIDIRECTIONAL), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_pop( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis);, ) \
	\
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__QUEUE)), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## private_node_tryMoveAndPushToFront( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis, \
			pELEMENT_TYPE * pElement);, ) \
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__QUEUE)), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## private_node_hasRoomForPushToFront( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis);, ) \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_popFromFront( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis); \
	\
	\
	\
	typedef struct pQUEUE_TYPE_NAME ## _Iterator \
	{ \
		pQUEUE_TYPE_NAME * CRX_NOT_MINE gPrivate_queue; \
		pQUEUE_TYPE_NAME ## _Private_Node * CRX_NOT_MINE gPrivate_node; \
		uint8_t gPrivate_index; \
		bool gPrivate_isConstant; \
	} pQUEUE_TYPE_NAME ## _Iterator; \
	\
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_construct( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis, pQUEUE_TYPE_NAME * pQueue); \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_construct2( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis, pQUEUE_TYPE_NAME const * pQueue); \
	PRIVATE void _ ## pMEMBER_FUNCTIONS_PREFIX ## iterator_construct( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis, \
			bool pIsConstant, pQUEUE_TYPE_NAME * pQueue); \
	\
	PUBLIC pQUEUE_TYPE_NAME ## _Iterator * pMEMBER_FUNCTIONS_PREFIX ## iterator_new( \
			pQUEUE_TYPE_NAME * pQueue); \
	PUBLIC pQUEUE_TYPE_NAME ## _Iterator * pMEMBER_FUNCTIONS_PREFIX ## iterator_new2( \
			pQUEUE_TYPE_NAME const * pQueue); \
	PUBLIC pQUEUE_TYPE_NAME ## _Iterator * pMEMBER_FUNCTIONS_PREFIX ## iterator_moveNew( \
			pQUEUE_TYPE_NAME ## _Iterator * pIterator); \
	PUBLIC pQUEUE_TYPE_NAME ## _Iterator * pMEMBER_FUNCTIONS_PREFIX ## iterator_copyNew( \
			pQUEUE_TYPE_NAME ## _Iterator const * pIterator); \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_free( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis); \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_associateWith( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis, pQUEUE_TYPE_NAME const * pQueue); \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_constantAssociateWith( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis, pQUEUE_TYPE_NAME const * pQueue); \
	PRIVATE void pMEMBER_FUNCTIONS_PREFIX ## iterator_private_doAssociateWith( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis, bool pIsConstant, \
			pQUEUE_TYPE_NAME const * pQueue); \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_reset(pQUEUE_TYPE_NAME ## _Iterator * pThis); \
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_resetToBack( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis);, ) \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_next(pQUEUE_TYPE_NAME ## _Iterator * pThis); \
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_prev( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis);, ) \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## iterator_isValid( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis); \
	\
	PUBLIC pELEMENT_TYPE * pMEMBER_FUNCTIONS_PREFIX ## iterator_get( \
			pQUEUE_TYPE_NAME ## _Iterator const * pThis); \
	PUBLIC pELEMENT_TYPE const * pMEMBER_FUNCTIONS_PREFIX ## iterator_constantGet( \
			pQUEUE_TYPE_NAME ## _Iterator const * pThis); \
	PRIVATE pELEMENT_TYPE * pMEMBER_FUNCTIONS_PREFIX ## iterator_private_doGet( \
			pQUEUE_TYPE_NAME ## _Iterator const * pThis); \
			
	
//#END_DEFINE

#if(!CRX_ARE_VARIADIC_MACROS_EMULATED)
	#define CRX__C__Queue__DEFINE(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__Queue__DEFINE, __VA_ARGS__)
#else
	#define CRX__C__Queue__DEFINE(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRX__C__Queue__DEFINE, p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20)
#endif

#define CRX__C__Queue__DEFINE__9(pQUEUE_TYPE_NAME, pQUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pMODE, pNUMBER_OF_ELEMENTS_PER_NODE, pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__Queue__DEFINE(pQUEUE_TYPE_NAME, pQUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pMODE, pNUMBER_OF_ELEMENTS_PER_NODE, pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__FALSE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRXM__IFELSE2(pIS_TO_ENABLE_NODE_CAPACITY_FIELD, this->gPRIVATE__NODE_CAPACITY, \
		pNUMBER_OF_ELEMENTS_PER_NODE), CRX__LIB__PUBLIC_C_FUNCTION(), \
		CRX__LIB__PRIVATE_C_FUNCTION())


#define CRX__C__Queue__DEFINE__10(pQUEUE_TYPE_NAME, pQUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pMODE, pNUMBER_OF_ELEMENTS_PER_NODE, pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR) \
_CRX__C__Queue__DEFINE(pQUEUE_TYPE_NAME, pQUEUE_MEMBER_FUNCTIONS_PREFIX, \
		pMODE, pNUMBER_OF_ELEMENTS_PER_NODE, pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		CRXM__TRUE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
\
		CRXM__IFELSE2(pIS_TO_ENABLE_NODE_CAPACITY_FIELD, this->gPRIVATE__NODE_CAPACITY, \
		pNUMBER_OF_ELEMENTS_PER_NODE), CRX__LIB__PUBLIC_C_FUNCTION(), \
		CRX__LIB__PRIVATE_C_FUNCTION())
		
		
#define _CRX__C__Queue__DEFINE(pQUEUE_TYPE_NAME, pMEMBER_FUNCTIONS_PREFIX, \
		pMODE, pNUMBER_OF_ELEMENTS_PER_NODE, pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		pELEMENT_TYPE, pFUNC_ELEMENT_DESTRUCTOR, \
		pIS_ELEMENT_COPYABLE, pFUNC_ELEMENT_COPY_CONSTRUCTOR, \
		pFUNC_ELEMENT_MOVE_CONSTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR, \
		pTHIS_NODE_CAPACITY, PUBLIC, PRIVATE) \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_NODE_CAPACITY_FIELD), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## construct(pQUEUE_TYPE_NAME * pThis), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## construct(pQUEUE_TYPE_NAME * pThis, \
			size_t pNodeCapacity CRX_DEFAULT(0))) \
	{ \
		CRXM__IFELSE2(pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		assert(pNodeCapacity < 256), ); \
	\
		pThis->gPrivate_rootNode = NULL; \
		CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
		pThis->gPrivate_lastNode = NULL;, ) \
		pThis->gPrivate_length = 0; \
		CRXM__IFELSE2(pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		pThis->gPRIVATE__NODE_CAPACITY = ((pNodeCapacity == 0) ? 4 : pNodeCapacity);, ) \
	} \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## copyConstruct(pQUEUE_TYPE_NAME * pThis, \
			pQUEUE_TYPE_NAME const * CRX_NOT_NULL pQueue) \
	{ \
		CRXM__IFELSE2(CRXM__NOT(pIS_ELEMENT_COPYABLE), abort();, \
	\
		if(pQueue->gPrivate_rootNode != NULL) \
		{ \
			CRXM__IFELSE(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)) \
			( \
				pThis->gPrivate_rootNode = pMEMBER_FUNCTIONS_PREFIX ## private_copyNodes(pThis, \
						pQueue->gPrivate_rootNode); \
			) \
			( \
				pThis->gPrivate_lastNode = NULL; \
				pThis->gPrivate_rootNode = pMEMBER_FUNCTIONS_PREFIX ## private_copyNodes(pThis, \
						pQueue->gPrivate_rootNode, &(pThis->gPrivate_lastNode)); \
			) \
		} \
		else \
		{ \
			pThis->gPrivate_rootNode = NULL; \
			pThis->gPrivate_lastNode = NULL; \
		} \
	\
		if(pThis->gPrivate_rootNode != NULL) \
			{pThis->gPrivate_length = pQueue->gPrivate_length;} \
		else \
		{ \
			CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
			pThis->gPrivate_lastNode = NULL;, ) \
			pThis->gPrivate_length = 0; \
		} \
		\
		CRXM__IFELSE2(pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		pThis->gPRIVATE__NODE_CAPACITY = pQueue->gPRIVATE__NODE_CAPACITY;, ) \
	\
	)} \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_NODE_CAPACITY_FIELD), \
	PUBLIC pQUEUE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## new(), \
	PUBLIC pQUEUE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## new( \
			size_t pNodeCapacity CRX_DEFAULT(0))) \
	{ \
		pQUEUE_TYPE_NAME * vReturn = (pQUEUE_TYPE_NAME *)(calloc(1,\
				sizeof(pQUEUE_TYPE_NAME))); \
	\
		if(vReturn != NULL) \
		{ \
			CRXM__IFELSE(CRXM__NOT(pIS_TO_ENABLE_NODE_CAPACITY_FIELD)) \
			( \
				pMEMBER_FUNCTIONS_PREFIX ## construct(vReturn); \
			) \
			( \
				pMEMBER_FUNCTIONS_PREFIX ## construct(vReturn, pNodeCapacity); \
			) \
		} \
	\
		return vReturn; \
	} \
	\
	PUBLIC pQUEUE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## moveNew( \
			pQUEUE_TYPE_NAME * CRX_NOT_NULL pQueue) \
	{ \
		pQUEUE_TYPE_NAME * vReturn = (pQUEUE_TYPE_NAME *)(calloc(1,\
				sizeof(pQUEUE_TYPE_NAME))); \
	\
		if(vReturn != NULL) \
			{memcpy(vReturn, pQueue, sizeof(pQUEUE_TYPE_NAME));} \
	\
		return vReturn; \
	} \
	\
	PUBLIC pQUEUE_TYPE_NAME * pMEMBER_FUNCTIONS_PREFIX ## copyNew( \
			pQUEUE_TYPE_NAME const * CRX_NOT_NULL pQueue) \
	{ \
		CRXM__IFELSE2(CRXM__NOT(pIS_ELEMENT_COPYABLE), abort();, \
	\
		pQUEUE_TYPE_NAME * vReturn = (pQUEUE_TYPE_NAME *)(calloc(1,\
				sizeof(pQUEUE_TYPE_NAME))); \
	\
		if(vReturn != NULL) \
			{pMEMBER_FUNCTIONS_PREFIX ## copyConstruct(vReturn, pQueue);} \
	\
		return vReturn; \
	)} \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## destruct(pQUEUE_TYPE_NAME * pThis) \
	{ \
		if(pThis->gPrivate_rootNode != NULL) \
			{pMEMBER_FUNCTIONS_PREFIX ## private_removeNodes(pThis, pThis->gPrivate_rootNode);} \
	} \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## free(pQUEUE_TYPE_NAME * pThis) \
		{free(pThis);} \
	\
	CRX__C__TYPE_BLUE_PRINT__DEFINE_GET_BLUE_PRINT( \
			pQUEUE_TYPE_NAME, pMEMBER_FUNCTIONS_PREFIX, \
			CRXM__TRUE, CRXM__TRUE, \
			pIS_ELEMENT_COPYABLE, CRXM__TRUE, \
			CRXM__FALSE, CRXM__FALSE) \
	\
	CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK), \
	PRIVATE pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_copyNodes( \
			pQUEUE_TYPE_NAME * pThis, pQUEUE_TYPE_NAME ## _Private_Node * pNode__start), \
	PRIVATE pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_copyNodes( \
			pQUEUE_TYPE_NAME * pThis, pQUEUE_TYPE_NAME ## _Private_Node * pNode__start, \
			pQUEUE_TYPE_NAME ## _Private_Node * * pNode__lastNode)) \
	{ \
		CRX_SCOPE_META \
		if(pNode__start != NULL) \
			{return NULL;} \
		\
		CRX_SCOPE \
		pQUEUE_TYPE_NAME ## _Private_Node * vCurrentNode = pNode__start->gPrivate_next; \
		pQUEUE_TYPE_NAME ## _Private_Node * vCurrentNode__out = \
				pMEMBER_FUNCTIONS_PREFIX ## private_node_copyNew(pNode__start); \
		pQUEUE_TYPE_NAME ## _Private_Node * vReturn = vCurrentNode__out; \
	\
		while(vCurrentNode != NULL) \
		{ \
			vCurrentNode__out->gPrivate_next = \
					pMEMBER_FUNCTIONS_PREFIX ## private_node_copyNew(vCurrentNode); \
		\
			if(vCurrentNode__out->gPrivate_next != NULL) \
			{ \
				CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
				vCurrentNode__out->gPrivate_next->gPrivate_prev = vCurrentNode__out;, ) \
			\
				vCurrentNode = vCurrentNode->gPrivate_next; \
				vCurrentNode__out = vCurrentNode__out->gPrivate_next; \
			} \
			else \
				{break;} \
		} \
	\
		CRXM__IFELSE(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK))) \
		( \
			if(vCurrentNode__out != NULL) \
			{ \
				if(pNode__lastNode != NULL) \
					{*pNode__lastNode = vCurrentNode__out;} \
			} \
			else \
			{ \
				pMEMBER_FUNCTIONS_PREFIX ## private_removeNodes(pThis, vReturn); \
				vReturn = NULL; \
			} \
		) \
		( \
			if(vCurrentNode__out == NULL) \
			{ \
				pMEMBER_FUNCTIONS_PREFIX ## private_removeNodes(pThis, vReturn); \
				vReturn = NULL; \
			} \
		) \
	\
		return vReturn; \
		CRX_SCOPE_END; \
	} \
	\
	PRIVATE pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_removeNodes( \
			pQUEUE_TYPE_NAME * pThis, pQUEUE_TYPE_NAME ## _Private_Node * pNode__start) \
	{ \
		pQUEUE_TYPE_NAME ## _Private_Node * vCurrentNode = pNode__start; \
		pQUEUE_TYPE_NAME ## _Private_Node * vNextNode = NULL; \
	\
		CRXM__IFELSE(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK))) \
		( \
			if(pNode__start->gPrivate_prev != NULL) \
				{pNode__start->gPrivate_prev->gPrivate_next = NULL;} \
		)() \
	\
		while(vCurrentNode != NULL) \
		{ \
			vNextNode = pNode__start->gPrivate_next; \
	\
			CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
			pMEMBER_FUNCTIONS_PREFIX ## private_node_destruct(vCurrentNode);, ) \
			pMEMBER_FUNCTIONS_PREFIX ## private_node_free(vCurrentNode); \
	\
			vCurrentNode = vNextNode; \
		} \
	} \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## empty(pQUEUE_TYPE_NAME * pThis) \
	{ \
		if(pThis->gPrivate_rootNode != NULL) \
		{ \
			pMEMBER_FUNCTIONS_PREFIX ## private_removeNodes(pThis, pThis->gPrivate_rootNode); \
	\
			pThis->gPrivate_rootNode = NULL; \
			CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
			pThis->gPrivate_lastNode = NULL;, ) \
			pThis->gPrivate_length = 0; \
		} \
	} \
	\
	PUBLIC size_t pMEMBER_FUNCTIONS_PREFIX ## getLength(pQUEUE_TYPE_NAME const * pThis) \
		{return pThis->gPrivate_length;} \
	\
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## tryMoveAndPush(pQUEUE_TYPE_NAME * pThis, \
			pELEMENT_TYPE * pElement) \
	{ \
		if((pThis->gPrivate_lastNode == NULL) || \
				!pMEMBER_FUNCTIONS_PREFIX ## private_node_hasRoomForPush(pThis->gPrivate_lastNode)) \
		{ \
			pQUEUE_TYPE_NAME ## _Private_Node * tNode = NULL; \
	\
			CRXM__IFELSE(CRXM__NOT(pIS_TO_ENABLE_NODE_CAPACITY_FIELD)) \
			( \
				CRXM__IFELSE(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__QUEUE)) \
				( \
					tNode = pMEMBER_FUNCTIONS_PREFIX ## private_node_new(0); \
				) \
				( \
					tNode = pMEMBER_FUNCTIONS_PREFIX ## private_node_new( \
							(uint8_t)((pThis->gPrivate_lastNode == NULL) ? \
									(pNUMBER_OF_ELEMENTS_PER_NODE / 2) : 0)); \
				) \
			) \
			( \
				CRXM__IFELSE(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__QUEUE)) \
				( \
					tNode = pMEMBER_FUNCTIONS_PREFIX ## private_node_new(0, \
							pThis->gPRIVATE__NODE_CAPACITY); \
				) \
				( \
					tNode = pMEMBER_FUNCTIONS_PREFIX ## private_node_new( \
							(uint8_t)((pThis->gPrivate_lastNode == NULL) ? \
									(pThis->gPRIVATE__NODE_CAPACITY / 2) : 0), \
							pThis->gPRIVATE__NODE_CAPACITY); \
				) \
			) \
	\
			if(tNode != NULL) \
			{ \
				if(pThis->gPrivate_lastNode != NULL) \
				{ \
					pThis->gPrivate_lastNode->gPrivate_next = tNode; \
					tNode->gPrivate_prev = pThis->gPrivate_lastNode->gPrivate_prev; \
				} \
				else \
					{pThis->gPrivate_rootNode = tNode;} \
	\
				pThis->gPrivate_lastNode = tNode; \
			} \
		} \
	\
		if((pThis->gPrivate_lastNode != NULL) && \
				pMEMBER_FUNCTIONS_PREFIX ## private_node_hasRoomForPush(pThis->gPrivate_lastNode)) \
		{ \
			if(pMEMBER_FUNCTIONS_PREFIX ## private_node_tryMoveAndPush( \
					pThis->gPrivate_lastNode, pElement)) \
			{ \
				pThis->gPrivate_length = pThis->gPrivate_length + 1; \
	\
				return true; \
			} \
			else \
				{return false;} \
		} \
		else \
			{return false;} \
	\
	}, ) \
	\
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## push(pQUEUE_TYPE_NAME * pThis, \
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
	CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__BIDIRECTIONAL), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## pop(pQUEUE_TYPE_NAME * pThis) \
	{ \
		if(pThis->gPrivate_length > 0) \
		{ \
			if((pThis->gPrivate_lastNode->gPrivate_length == 0) && \
					(pThis->gPrivate_lastNode != pThis->gPrivate_rootNode))\
			{ \
				pQUEUE_TYPE_NAME ## _Private_Node * tNode = \
						pThis->gPrivate_lastNode->gPrivate_prev; \
	\
				tNode->gPrivate_next = NULL; \
	\
				CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
				pMEMBER_FUNCTIONS_PREFIX ## private_node_destruct(pThis->gPrivate_lastNode);, ) \
				pMEMBER_FUNCTIONS_PREFIX ## private_node_free(pThis->gPrivate_lastNode); \
	\
				pThis->gPrivate_lastNode = tNode; \
			} \
	\
			pMEMBER_FUNCTIONS_PREFIX ## private_node_pop(pThis->gPrivate_lastNode); \
			pThis->gPrivate_length = pThis->gPrivate_length - 1; \
		} \
	}, ) \
	\
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__QUEUE)), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## tryMoveAndPushToFront(pQUEUE_TYPE_NAME * pThis, \
			pELEMENT_TYPE * pElement) \
	{ \
		if((pThis->gPrivate_lastNode == NULL) || \
				!pMEMBER_FUNCTIONS_PREFIX ## private_node_hasRoomForPush(pThis->gPrivate_lastNode)) \
		{ \
			pQUEUE_TYPE_NAME ## _Private_Node * tNode = NULL; \
	\
			CRXM__IFELSE(CRXM__NOT(pIS_TO_ENABLE_NODE_CAPACITY_FIELD)) \
			( \
				CRXM__IFELSE(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)) \
				( \
					tNode = pMEMBER_FUNCTIONS_PREFIX ## private_node_new( \
							pNUMBER_OF_ELEMENTS_PER_NODE - 1); \
				) \
				( \
					tNode = pMEMBER_FUNCTIONS_PREFIX ## private_node_new( \
							(uint8_t)((pThis->gPrivate_lastNode == NULL) ? \
									(pNUMBER_OF_ELEMENTS_PER_NODE / 2) : \
									pNUMBER_OF_ELEMENTS_PER_NODE - 1)); \
				) \
			) \
			( \
				CRXM__IFELSE(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__QUEUE)) \
				( \
					tNode = pMEMBER_FUNCTIONS_PREFIX ## private_node_new( \
							pThis->gPRIVATE__NODE_CAPACITY - 1, \
							pThis->gPRIVATE__NODE_CAPACITY); \
				) \
				( \
					tNode = pMEMBER_FUNCTIONS_PREFIX ## private_node_new( \
							(uint8_t)((pThis->gPrivate_lastNode == NULL) ? \
									(pThis->gPRIVATE__NODE_CAPACITY / 2) : \
									pThis->gPRIVATE__NODE_CAPACITY - 1), \
							pThis->gPRIVATE__NODE_CAPACITY); \
				) \
			) \
	\
			if(tNode != NULL) \
			{ \
				if(pThis->gPrivate_rootNode != NULL) \
				{ \
					tNode->gPrivate_next = pThis->gPrivate_rootNode; \
					CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
					pThis->gPrivate_rootNode->gPrivate_prev = tNode;, ) \
				} \
				else \
				{ \
					CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
					pThis->gPrivate_lastNode = tNode;, ) \
				} \
	\
				pThis->gPrivate_rootNode = tNode; \
			} \
		} \
	\
		if((pThis->gPrivate_rootNode != NULL) && \
				pMEMBER_FUNCTIONS_PREFIX ## private_node_hasRoomForPushToFront( \
						pThis->gPrivate_rootNode)) \
		{ \
			if(pMEMBER_FUNCTIONS_PREFIX ## private_node_tryMoveAndPushToFront( \
					pThis->gPrivate_rootNode, pElement)) \
			{ \
				pThis->gPrivate_length = pThis->gPrivate_length + 1; \
	\
				return true; \
			} \
			else \
				{return false;} \
		} \
		else \
			{return false;} \
	\
	}, ) \
	\
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__QUEUE)), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## pushToFront(pQUEUE_TYPE_NAME * pThis, \
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
					vReturn = , return) pMEMBER_FUNCTIONS_PREFIX ## tryMoveAndPushToFront( \
							pThis, ((pELEMENT_TYPE *)vElement)); \
		) \
		( \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				memcpy(vElement, pElement, sizeof(pELEMENT_TYPE)); \
	\
				CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_DESTRUCTOR, pFUNC_ELEMENT_MOVE_DESTRUCTOR), \
						vReturn = , return) pMEMBER_FUNCTIONS_PREFIX ## tryMoveAndPushToFront( \
								pThis, ((pELEMENT_TYPE *)vElement)); \
			) \
			( \
				return pMEMBER_FUNCTIONS_PREFIX ## tryMoveAndPushToFront(pThis, \
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
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## popFromFront(pQUEUE_TYPE_NAME * pThis) \
	{ \
		if(pThis->gPrivate_length > 0) \
		{ \
			if((pThis->gPrivate_rootNode->gPrivate_length == 0) && \
					(pThis->gPrivate_rootNode != pThis->gPrivate_lastNode)) \
			{ \
				pQUEUE_TYPE_NAME ## _Private_Node * tNode = \
						pThis->gPrivate_rootNode->gPrivate_next; \
	\
				tNode->gPrivate_prev = NULL; \
	\
				CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
				pMEMBER_FUNCTIONS_PREFIX ## private_node_destruct(pThis->gPrivate_rootNode);, ) \
				pMEMBER_FUNCTIONS_PREFIX ## private_node_free(pThis->gPrivate_rootNode); \
	\
				pThis->gPrivate_rootNode = tNode; \
			} \
	\
			pMEMBER_FUNCTIONS_PREFIX ## private_node_popFromFront(pThis->gPrivate_rootNode); \
			pThis->gPrivate_length = pThis->gPrivate_length - 1; \
		} \
	} \
	\
	CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__BIDIRECTIONAL), \
	PUBLIC pELEMENT_TYPE * pMEMBER_FUNCTIONS_PREFIX ## get(pQUEUE_TYPE_NAME * pThis) \
	{ \
		assert(pThis->gPrivate_length > 0); \
	\
		pQUEUE_TYPE_NAME ## _Private_Node * vNode = \
				((pThis->gPrivate_lastNode->gPrivate_length != 0) ? pThis->gPrivate_lastNode : \
				pThis->gPrivate_lastNode->gPrivate_prev); \
	\
		return (vNode->gPrivate_elements + vNode->gPrivate_startIndex + \
				vNode->gPrivate_length - 1); \
	}, ) \
	\
	CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__BIDIRECTIONAL), \
	PUBLIC pELEMENT_TYPE const * pMEMBER_FUNCTIONS_PREFIX ## constantGet( \
			pQUEUE_TYPE_NAME const * pThis) \
		{return pMEMBER_FUNCTIONS_PREFIX ## get((pQUEUE_TYPE_NAME *)pThis);}, ) \
	\
	CRXM__IFELSE2(CRXM__AND(pIS_ELEMENT_COPYABLE, \
			CRXM__IS(pMODE, CRX__C__QUEUE__MODE__BIDIRECTIONAL)), \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## copyGetTo(pQUEUE_TYPE_NAME const * pThis, \
			pELEMENT_TYPE * pReturn), \
	PUBLIC pELEMENT_TYPE pMEMBER_FUNCTIONS_PREFIX ## copyGet(pQUEUE_TYPE_NAME const * pThis)) \
	{ \
		pELEMENT_TYPE * vElement = pMEMBER_FUNCTIONS_PREFIX ## get((pQUEUE_TYPE_NAME *)pThis); \
	\
		CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR)) \
		( \
			CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
			pFUNC_ELEMENT_DESTRUCTOR(pReturn);, ) \
	\
			CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(pReturn, vElement); \
			) \
			( \
				memcpy(pReturn, vElement, sizeof(pELEMENT_TYPE)); \
			) \
		) \
		( \
			return *vElement; \
		) \
	}, ) \
	\
	PUBLIC pELEMENT_TYPE * pMEMBER_FUNCTIONS_PREFIX ## getFront(pQUEUE_TYPE_NAME * pThis) \
	{ \
		assert(pThis->gPrivate_length > 0); \
	\
		pQUEUE_TYPE_NAME ## _Private_Node * vNode = \
				((pThis->gPrivate_rootNode->gPrivate_length != 0) ? pThis->gPrivate_rootNode : \
				pThis->gPrivate_rootNode->gPrivate_next); \
	\
		return (vNode->gPrivate_elements + vNode->gPrivate_startIndex); \
	} \
	PUBLIC pELEMENT_TYPE const * pMEMBER_FUNCTIONS_PREFIX ## constantGetFront( \
			pQUEUE_TYPE_NAME const * pThis) \
		{return pMEMBER_FUNCTIONS_PREFIX ## getFront((pQUEUE_TYPE_NAME *)pThis);} \
	CRXM__IFELSE2(pIS_ELEMENT_COPYABLE, \
	CRXM__IFELSE2(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## copyGetFrontTo(pQUEUE_TYPE_NAME const * pThis, \
			pELEMENT_TYPE * pReturn), \
	PUBLIC pELEMENT_TYPE pMEMBER_FUNCTIONS_PREFIX ## copyGetFront( \
			pQUEUE_TYPE_NAME const * pThis)) \
	{ \
		pELEMENT_TYPE * vElement = pMEMBER_FUNCTIONS_PREFIX ## getFront((pQUEUE_TYPE_NAME *)pThis); \
	\
		CRXM__IFELSE(CRXM__OR(pFUNC_ELEMENT_COPY_CONSTRUCTOR, pFUNC_ELEMENT_DESTRUCTOR)) \
		( \
			CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
			pFUNC_ELEMENT_DESTRUCTOR(pReturn);, ) \
	\
			CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
			( \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(pReturn, vElement); \
			) \
			( \
				memcpy(pReturn, vElement, sizeof(pELEMENT_TYPE)); \
			) \
		) \
		( \
			return *vElement; \
		) \
	}, ) \
	\
	\
	\
	CRXM__IFELSE2(pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
	PUBLIC size_t pMEMBER_FUNCTIONS_PREFIX ## private_node_getByteSizeOf( \
			pQUEUE_TYPE_NAME ## _Private_Node const * CRX_NOT_NULL pNode) \
	{ \
		return (sizeof(pQUEUE_TYPE_NAME ## _Private_Node) + \
				((pNode->gPRIVATE__NODE_CAPACITY - 1) * sizeof(pELEMENT_TYPE))); \
	}, ); \
	CRXM__IFELSE2(pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
	PUBLIC size_t pMEMBER_FUNCTIONS_PREFIX ## private_node_getByteSizeFor( \
			uint8_t pNodeCapacity) \
	{ \
		return (sizeof(pQUEUE_TYPE_NAME ## _Private_Node) + \
				((pNodeCapacity - 1) * sizeof(pELEMENT_TYPE))); \
	}, ); \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_NODE_CAPACITY_FIELD), \
			CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_construct( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_construct( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis, uint8_t pStartIndex)), \
			CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_construct( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis, uint8_t pNodeCapacity), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_construct( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis, uint8_t pStartIndex, uint8_t pNodeCapacity))) \
	{ \
		pThis->gPrivate_next = NULL; \
		CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
		pThis->gPrivate_prev = NULL;, ) \
		pThis->gPrivate_length = 0; \
		CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
		pThis->gPrivate_startIndex = pStartIndex;, ) \
		CRXM__IFELSE2(pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		pThis->gPRIVATE__NODE_CAPACITY = pNodeCapacity;, ) \
	} \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_copyConstruct( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis, \
			pQUEUE_TYPE_NAME ## _Private_Node const * CRX_NOT_NULL pNode) \
	{ \
		CRXM__IFELSE2(CRXM__NOT(pIS_ELEMENT_COPYABLE), abort();, \
	\
		pThis->gPrivate_next = NULL; \
		CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
		pThis->gPrivate_prev = NULL;, ) \
		pThis->gPrivate_length = pNode->gPrivate_length; \
		CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
		pThis->gPrivate_startIndex = pNode->gPrivate_startIndex;, ) \
		CRXM__IFELSE2(pIS_TO_ENABLE_NODE_CAPACITY_FIELD, \
		pThis->gPRIVATE__NODE_CAPACITY = pNode->gPRIVATE__NODE_CAPACITY;, ) \
	\
		CRXM__IFELSE(pFUNC_ELEMENT_COPY_CONSTRUCTOR) \
		( \
			CRX_FOR(size_t tI = 0, tI < pNode->gPrivate_length, tI++) \
			{ \
				pFUNC_ELEMENT_COPY_CONSTRUCTOR(pThis->gPrivate_elements + \
								pThis->gPrivate_startIndex + tI, \
						pNode->gPrivate_elements + pThis->gPrivate_startIndex + tI); \
			} \
			CRX_ENDFOR \
		) \
		( \
			memcpy(pThis->gPrivate_elements + \
							(pThis->gPrivate_startIndex * sizeof(pELEMENT_TYPE)), \
					pNode->gPrivate_elements + \
							(pThis->gPrivate_startIndex * sizeof(pELEMENT_TYPE)), \
					pThis->gPrivate_length * sizeof(pELEMENT_TYPE)); \
		) \
	\
	)} \
	\
	CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_NODE_CAPACITY_FIELD), \
			CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK), \
	PUBLIC pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_node_new(void), \
	PUBLIC pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_node_new( \
			uint8_t pStartIndex)), \
			CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK), \
	PUBLIC pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_node_new( \
			uint8_t pNodeCapacity), \
	PUBLIC pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_node_new( \
			uint8_t pStartIndex, uint8_t pNodeCapacity))) \
	{ \
		pQUEUE_TYPE_NAME ## _Private_Node * vReturn = \
				((pQUEUE_TYPE_NAME ## _Private_Node *) calloc(1, \
				CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_NODE_CAPACITY_FIELD), \
				sizeof(pQUEUE_TYPE_NAME ## _Private_Node), \
				pMEMBER_FUNCTIONS_PREFIX ## private_node_getByteSizeFor(pNodeCapacity)))); \
	\
		if(vReturn != NULL) \
		{ \
			CRXM__IFELSE(CRXM__NOT(pIS_TO_ENABLE_NODE_CAPACITY_FIELD)) \
			( \
				CRXM__IFELSE(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)) \
				( \
					pMEMBER_FUNCTIONS_PREFIX ## private_node_construct(vReturn); \
				) \
				( \
					pMEMBER_FUNCTIONS_PREFIX ## private_node_construct(vReturn, pStartIndex); \
				) \
			) \
			( \
				CRXM__IFELSE(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)) \
				( \
					pMEMBER_FUNCTIONS_PREFIX ## private_node_construct(vReturn, pNodeCapacity); \
				) \
				( \
					pMEMBER_FUNCTIONS_PREFIX ## private_node_construct(vReturn, pStartIndex, \
							pNodeCapacity); \
				) \
			) \
		} \
	\
		return vReturn; \
	} \
	PUBLIC pQUEUE_TYPE_NAME ## _Private_Node * pMEMBER_FUNCTIONS_PREFIX ## private_node_copyNew( \
			pQUEUE_TYPE_NAME ## _Private_Node const * pNode) \
	{ \
		CRXM__IFELSE2(CRXM__NOT(pIS_ELEMENT_COPYABLE), abort();, \
	\
		pQUEUE_TYPE_NAME ## _Private_Node * vReturn = \
				((pQUEUE_TYPE_NAME ## _Private_Node *) calloc(1, \
				CRXM__IFELSE2(CRXM__NOT(pIS_TO_ENABLE_NODE_CAPACITY_FIELD), \
				sizeof(pQUEUE_TYPE_NAME ## _Private_Node), \
				pMEMBER_FUNCTIONS_PREFIX ## private_node_getByteSizeOf(pNode)))); \
	\
		if(vReturn != NULL) \
		{ \
			pMEMBER_FUNCTIONS_PREFIX ## private_node_copyConstruct(vReturn, pNode); \
		} \
	\
		return vReturn; \
	)} \
	\
	CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_destruct( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis) \
	{ \
		CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++) \
		{ \
			pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements + \
					pThis->gPrivate_startIndex + tI); \
		} \
		CRX_ENDFOR \
	}, ) \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_free( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis) \
		{free(pThis);} \
	\
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## private_node_tryMoveAndPush( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis, pELEMENT_TYPE * pElement) \
	{ \
		if((pThis->gPrivate_startIndex + pThis->gPrivate_length) < (pTHIS_NODE_CAPACITY - 1)) \
		{ \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + \
						pThis->gPrivate_startIndex + 1, pElement); \
			) \
			( \
				memcpy(pThis->gPrivate_elements + pThis->gPrivate_startIndex + 1, \
						pElement, sizeof(pELEMENT_TYPE)); \
			) \
	\
			return true; \
		} \
		else \
			{return false;} \
	}, ) \
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## private_node_hasRoomForPush( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis) \
	{ \
		return ((pThis->gPrivate_startIndex + pThis->gPrivate_length) < \
				(pTHIS_NODE_CAPACITY - 1)); \
	}, ) \
	\
	CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__BIDIRECTIONAL), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_pop( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis) \
	{ \
		if(pThis->gPrivate_length > 0) \
		{ \
			CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
			pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements + pThis->gPrivate_startIndex + \
					pThis->gPrivate_length - 1), ); \
	\
			pThis->gPrivate_length = pThis->gPrivate_length - 1; \
		} \
	}, ) \
	\
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__QUEUE)), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## private_node_tryMoveAndPushToFront( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis, pELEMENT_TYPE * pElement) \
	{ \
		if(pThis->gPrivate_startIndex > 0) \
		{ \
			CRXM__IFELSE(pFUNC_ELEMENT_MOVE_CONSTRUCTOR) \
			( \
				pFUNC_ELEMENT_MOVE_CONSTRUCTOR(pThis->gPrivate_elements + \
						pThis->gPrivate_startIndex - 1, pElement); \
			) \
			( \
				memcpy(pThis->gPrivate_elements + pThis->gPrivate_startIndex - 1, \
						pElement, sizeof(pELEMENT_TYPE)); \
			) \
	\
			return true; \
		} \
		else \
			{return false;} \
	}, ) \
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__QUEUE)), \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## private_node_hasRoomForPushToFront( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis) \
		{return (pThis->gPrivate_startIndex > 0);}, ) \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## private_node_popFromFront( \
			pQUEUE_TYPE_NAME ## _Private_Node * pThis) \
	{ \
		if(pThis->gPrivate_length > 0) \
		{ \
			CRXM__IFELSE2(pFUNC_ELEMENT_DESTRUCTOR, \
			pFUNC_ELEMENT_DESTRUCTOR(pThis->gPrivate_elements + pThis->gPrivate_startIndex), ); \
	\
			pThis->gPrivate_length = pThis->gPrivate_length - 1; \
	\
			if(pThis->gPrivate_startIndex < (pTHIS_NODE_CAPACITY - 1)) \
				{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex + 1;} \
		} \
	} \
	\
	\
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_construct( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis, pQUEUE_TYPE_NAME * pQueue) \
		{_ ## pMEMBER_FUNCTIONS_PREFIX ## iterator_construct(pThis, false, pQueue);}  \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_construct2( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis, pQUEUE_TYPE_NAME const * pQueue) \
	{ \
		_ ## pMEMBER_FUNCTIONS_PREFIX ## iterator_construct(pThis, false, \
				((pQUEUE_TYPE_NAME *)pQueue)); \
	} \
	PRIVATE void _ ## pMEMBER_FUNCTIONS_PREFIX ## iterator_construct( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis, \
			bool pIsConstant, pQUEUE_TYPE_NAME * pQueue) \
	{ \
		pThis->gPrivate_queue = pQueue; \
		pThis->gPrivate_node = NULL; \
		pThis->gPrivate_index = 0; \
		pThis->gPrivate_isConstant = pIsConstant; \
	} \
	\
	PUBLIC pQUEUE_TYPE_NAME ## _Iterator * pMEMBER_FUNCTIONS_PREFIX ## iterator_new( \
			pQUEUE_TYPE_NAME * pQueue) \
	{ \
		pQUEUE_TYPE_NAME ## _Iterator * vReturn = (pQUEUE_TYPE_NAME ## _Iterator *)(calloc(1, \
				sizeof(pQUEUE_TYPE_NAME ## _Iterator))); \
	\
		if(vReturn != NULL) \
			{pMEMBER_FUNCTIONS_PREFIX ## iterator_construct(vReturn, pQueue);} \
	\
		return vReturn; \
	} \
	PUBLIC pQUEUE_TYPE_NAME ## _Iterator * pMEMBER_FUNCTIONS_PREFIX ## iterator_new2( \
			pQUEUE_TYPE_NAME const * pQueue) \
	{ \
		pQUEUE_TYPE_NAME ## _Iterator * vReturn = (pQUEUE_TYPE_NAME ## _Iterator *)(calloc(1, \
				sizeof(pQUEUE_TYPE_NAME ## _Iterator))); \
	\
		if(vReturn != NULL) \
			{pMEMBER_FUNCTIONS_PREFIX ## iterator_construct2(vReturn, pQueue);} \
	\
		return vReturn; \
	} \
	PUBLIC pQUEUE_TYPE_NAME ## _Iterator * pMEMBER_FUNCTIONS_PREFIX ## iterator_moveNew( \
			pQUEUE_TYPE_NAME ## _Iterator * pIterator) \
	{ \
		pQUEUE_TYPE_NAME ## _Iterator * vReturn = (pQUEUE_TYPE_NAME ## _Iterator *)(calloc(1, \
				sizeof(pQUEUE_TYPE_NAME ## _Iterator))); \
	\
		if(vReturn != NULL) \
			{memcpy(vReturn, pIterator, sizeof(pQUEUE_TYPE_NAME ## _Iterator));} \
	\
		return vReturn; \
	} \
	PUBLIC pQUEUE_TYPE_NAME ## _Iterator * pMEMBER_FUNCTIONS_PREFIX ## iterator_copyNew( \
			pQUEUE_TYPE_NAME ## _Iterator const * pIterator) \
	{ \
		pQUEUE_TYPE_NAME ## _Iterator * vReturn = (pQUEUE_TYPE_NAME ## _Iterator *)(calloc(1, \
				sizeof(pQUEUE_TYPE_NAME ## _Iterator))); \
	\
		if(vReturn != NULL) \
			{memcpy(vReturn, pIterator, sizeof(pQUEUE_TYPE_NAME ## _Iterator));} \
	\
		return vReturn; \
	} \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_free( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis) \
		{free(pThis);} \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_associateWith( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis, pQUEUE_TYPE_NAME const * pQueue) \
		{pMEMBER_FUNCTIONS_PREFIX ## iterator_private_doAssociateWith(pThis, false, pQueue);} \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_constantAssociateWith( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis, pQUEUE_TYPE_NAME const * pQueue) \
		{pMEMBER_FUNCTIONS_PREFIX ## iterator_private_doAssociateWith(pThis, true, pQueue);} \
	PRIVATE void pMEMBER_FUNCTIONS_PREFIX ## iterator_private_doAssociateWith( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis, bool pIsConstant, \
			pQUEUE_TYPE_NAME const * pQueue) \
	{ \
		pThis->gPrivate_queue = ((pQUEUE_TYPE_NAME *)pQueue); \
		pThis->gPrivate_node = NULL; \
		pThis->gPrivate_index = 0; \
		pThis->gPrivate_isConstant = pIsConstant; \
	} \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_reset(pQUEUE_TYPE_NAME ## _Iterator * pThis) \
	{ \
		if((pThis->gPrivate_queue == NULL) || \
				(pThis->gPrivate_queue->gPrivate_length == 0)) \
			{return; } \
	\
		pThis->gPrivate_node = pThis->gPrivate_queue->gPrivate_rootNode; \
	\
		if(pThis->gPrivate_node->gPrivate_length == 0) \
			{pThis->gPrivate_node = pThis->gPrivate_node->gPrivate_next;} \
	\
		pThis->gPrivate_index = CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK), \
				0, pThis->gPrivate_node->gPrivate_startIndex); \
	} \
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_resetToBack( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis) \
	{ \
		if((pThis->gPrivate_queue == NULL) || \
				(pThis->gPrivate_queue->gPrivate_length == 0)) \
			{return;} \
	\
		pThis->gPrivate_node = pThis->gPrivate_queue->gPrivate_lastNode; \
	\
		if(pThis->gPrivate_node->gPrivate_length == 0) \
			{pThis->gPrivate_node = pThis->gPrivate_node->gPrivate_prev;} \
	\
		pThis->gPrivate_index = CRXM__IFELSE2(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK), \
				0, pThis->gPrivate_node->gPrivate_length - 1); \
	}, ) \
	\
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_next(pQUEUE_TYPE_NAME ## _Iterator * pThis) \
	{ \
		if((pThis->gPrivate_queue != NULL) && (pThis->gPrivate_queue->gPrivate_length != 0)) \
		{ \
			pThis->gPrivate_index = pThis->gPrivate_index + 1; \
	\
			if(pThis->gPrivate_index >= pThis->gPrivate_node->gPrivate_length) \
			{ \
				pThis->gPrivate_index = 0; \
				pThis->gPrivate_node = pThis->gPrivate_node->gPrivate_next; \
	\
				if(pThis->gPrivate_node->gPrivate_length == 0) \
					{pThis->gPrivate_node = NULL;} \
			} \
		} \
	} \
	CRXM__IFELSE2(CRXM__NOT(CRXM__IS(pMODE, CRX__C__QUEUE__MODE__STACK)), \
	PUBLIC void pMEMBER_FUNCTIONS_PREFIX ## iterator_prev( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis) \
	{ \
		if((pThis->gPrivate_queue != NULL) && (pThis->gPrivate_queue->gPrivate_length != 0)) \
		{ \
			if(pThis->gPrivate_index > 0) \
				{pThis->gPrivate_index = pThis->gPrivate_index - 1;} \
			else \
			{ \
				pThis->gPrivate_node = pThis->gPrivate_node->gPrivate_prev; \
	\
				if(pThis->gPrivate_node != NULL) \
				{ \
					if(pThis->gPrivate_node->gPrivate_length != 0) \
						{pThis->gPrivate_index = pThis->gPrivate_node->gPrivate_length - 1;} \
					else \
						{pThis->gPrivate_node = NULL;} \
				} \
			} \
		} \
	}, ) \
	PUBLIC bool pMEMBER_FUNCTIONS_PREFIX ## iterator_isValid( \
			pQUEUE_TYPE_NAME ## _Iterator * pThis) \
		{return (pThis->gPrivate_node != NULL);} \
	\
	PUBLIC pELEMENT_TYPE * pMEMBER_FUNCTIONS_PREFIX ## iterator_get( \
			pQUEUE_TYPE_NAME ## _Iterator const * pThis) \
	{ \
		if(pThis->gPrivate_isConstant) \
			{return NULL;} \
	\
		return pMEMBER_FUNCTIONS_PREFIX ## iterator_private_doGet(pThis); \
	} \
	PUBLIC pELEMENT_TYPE const * pMEMBER_FUNCTIONS_PREFIX ## iterator_constantGet( \
			pQUEUE_TYPE_NAME ## _Iterator const * pThis) \
		{return pMEMBER_FUNCTIONS_PREFIX ## iterator_private_doGet(pThis);} \
	PRIVATE pELEMENT_TYPE * pMEMBER_FUNCTIONS_PREFIX ## iterator_private_doGet( \
			pQUEUE_TYPE_NAME ## _Iterator const * pThis) \
	{ \
		if(pThis->gPrivate_node != NULL) \
			{return pThis->gPrivate_node->gPrivate_elements + pThis->gPrivate_index;} \
	}

//#END_DEFINE







typedef struct Crx_C_Queue_Private_Node Crx_C_Queue_Private_Node;
typedef struct Crx_C_Queue
{
	Crx_C_TypeBluePrint const * CRX_NOT_MINE gPrivate_typeBluePrint;
	Crx_C_Queue_Private_Node * gPrivate_rootNode;
	Crx_C_Queue_Private_Node * gPrivate_lastNode;
	size_t gPrivate_length;
	uint8_t gPRIVATE__NODE_CAPACITY;
} Crx_C_Queue;
/*typedef struct Crx_C_Queue_Iterator
{
	Crx_C_Queue_Private_Node gPrivate_node;
	uint8_t gPrivate_index;
} Crx_C_Queue_Iterator; */

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_construct(Crx_C_Queue * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint, 
		size_t pNodeCapacity CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_copyConstruct(Crx_C_Queue * pThis,
		Crx_C_Queue const * CRX_NOT_NULL pQueue);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Queue * crx_c_queue_new(
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint, 
		size_t pNodeCapacity CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Queue * crx_c_queue_moveNew(
		Crx_C_Queue * CRX_NOT_NULL pQueue);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Queue * crx_c_queue_copyNew(
		Crx_C_Queue const * CRX_NOT_NULL pQueue);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_destruct(Crx_C_Queue * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_free(Crx_C_Queue * pThis);

CRX__C__TYPE_BLUE_PRINT__GENERIC__DECLARE_GET_BLUE_PRINT(
		Crx_C_Queue, crx_c_queue_,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__FALSE, CRXM__FALSE);

CRX__LIB__PRIVATE_C_FUNCTION() Crx_C_Queue_Private_Node * crx_c_queue_private_copyNodes(
		Crx_C_Queue * pThis, Crx_C_Queue_Private_Node * pNode__start,
		Crx_C_Queue_Private_Node * * pNode__lastNode);

CRX__LIB__PRIVATE_C_FUNCTION() Crx_C_Queue_Private_Node * crx_c_queue_private_removeNodes(
		Crx_C_Queue * pThis, Crx_C_Queue_Private_Node * pNode__start);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_empty(Crx_C_Queue * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_queue_getLength(Crx_C_Queue const * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_tryMoveAndPush(Crx_C_Queue * pThis,
		void * pElement);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_push(Crx_C_Queue * pThis,
		void * pElement);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_pop(Crx_C_Queue * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_tryMoveAndPushToFront(Crx_C_Queue * pThis, \
		void * pElement);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_pushToFront(Crx_C_Queue * pThis,
		void * pElement);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_popFromFront(Crx_C_Queue * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() unsigned char * crx_c_queue_get(Crx_C_Queue * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() unsigned char const * crx_c_queue_constantGet(
		Crx_C_Queue const * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_copyGetTo(Crx_C_Queue const * pThis,
		void * pReturn);

CRX__LIB__PUBLIC_C_FUNCTION() unsigned char * crx_c_queue_getFront(Crx_C_Queue * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() unsigned char const * crx_c_queue_constantGetFront(
		Crx_C_Queue const * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_copyGetFrontTo(Crx_C_Queue const * pThis,
		void * pReturn);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_empty(Crx_C_Queue * pThis);



typedef struct Crx_C_Queue_Private_Node
{
	CRX_FRIEND_CLASS(Crx_C_Queue);

	Crx_C_TypeBluePrint const * CRX_NOT_MINE gPrivate_typeBluePrint;
	Crx_C_Queue_Private_Node * gPrivate_next;
	Crx_C_Queue_Private_Node * gPrivate_prev;
	uint8_t gPrivate_length;
	uint8_t gPrivate_startIndex;
	uint8_t gPRIVATE__NODE_CAPACITY;
	uint8_t _gfddgier[5];
	unsigned char gPrivate_elements[1/*N*/]; /*KEEP THIS ALIGNED AT 16 BYTES RELATIVE TO STRUCTURE WHEN 64BIT*/
} Crx_C_Queue_Private_Node;

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_queue_private_node_getByteSizeOf(
		Crx_C_Queue_Private_Node const * CRX_NOT_NULL pNode);
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_queue_private_node_getByteSizeFor(
		Crx_C_TypeBluePrint const * pTypeBluePrint, uint8_t pNodeCapacity);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_private_node_construct(
		Crx_C_Queue_Private_Node * pThis, Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint,
		uint8_t pStartIndex, uint8_t pNodeCapacity);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_private_node_copyConstruct(
		Crx_C_Queue_Private_Node * pThis,
		Crx_C_Queue_Private_Node const * CRX_NOT_NULL pNode);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Queue_Private_Node * crx_c_queue_private_node_new(
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint,
		uint8_t pStartIndex, uint8_t pNodeCapacity);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Queue_Private_Node * crx_c_queue_private_node_copyNew( \
		Crx_C_Queue_Private_Node const * pNode);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_private_node_destruct(
		Crx_C_Queue_Private_Node * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_private_node_free(
		Crx_C_Queue_Private_Node * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_private_node_tryMoveAndPush(
		Crx_C_Queue_Private_Node * pThis, void * pElement);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_private_node_hasRoomForPush(
		Crx_C_Queue_Private_Node * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_private_node_pop(
		Crx_C_Queue_Private_Node * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_private_node_tryMoveAndPushToFront(
		Crx_C_Queue_Private_Node * pThis, void * pElement);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_private_node_hasRoomForPushToFront(
		Crx_C_Queue_Private_Node * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_private_node_popFromFront(
		Crx_C_Queue_Private_Node * pThis);



CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/Queue.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif