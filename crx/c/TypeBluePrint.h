#if(!defined(CRX__C__TYPE_BLUE_PRINT___h__))
#define CRX__C__TYPE_BLUE_PRINT___h__

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
#include <stddef.h>
//<<END>>

CRX__LIB__C_CODE_BEGIN()

//INSTANTIATIONS OF TEMPLATES MUST PROVIDE THE FOLLOWING COMMENT BEFORE THE DECLERATION PART
//		OF THE INSTANTIATION, AND FILLED CORRECTLY. IT IS RECOMMENDED THAT THIS IS DONE
//		FOR OTHER TYPES AS WELL:
/*
CONTRACT:
	IS FIXED SIZE:			0
	HAS CONSTRUCT:		 	0
	HAS DESTRUCT:		 	0
	IS COPYABLE:			0
	HAS COPY CONSTRUCT:		0
	HAS MOVE CONSTRUCT:		0
	HAS MOVE DESTRUCT:		0
*/


/*
NOTE: 
	- THE ASSUMPTION IS THAT GENERIC CODE WILL CONSTRUCT NEW OBJECTS ITSELF. HENCE, 
			getByteSizeFor(), construct(), AND new FUNCTIONS ARE NOT PART OF TypeBluePrint
	- IT IS NOT POSSIBLE TO HAVE A TEMPLATE OF A GENERIC. THIS IS BECAUSE A GENERIC
			DOES NOT KNOW ITS BLUE PRINT UNTILL RUNTIME, WHILE A TEMPALTE REQUIRES IT
			AT COMPILE TIME. CONSIDER Crx_C_TypeBluePrint::gIS_COPYABLE. A GENERIC
			WILL ALWAYS HAVE A copyConstruct() EVEN IF Crx_C_TypeBluePrint::gIS_COPYABLE
			IS FALSE, AND WHILE THE EXISTANCE OF copyConstruct() IS KNOWN AT COMPILE TIME
			THE VALUE OF Crx_C_TypeBluePrint::gIS_COPYABLE IS NOT KNOWN UNTIL RUNTIME.
*/
typedef struct Crx_C_TypeBluePrint
{
	size_t gBYTE_SIZE; 	//MUST BE EQUAL TO VALUE OF sizeof() IF THE TYPE HAS A FIXED SIZE, 
						//	OTHERWISE 0
	bool gIS_COPYABLE; 	//IF false, gFUNC__COPY_CONSTRUCT MUST BE NULL
	bool gIS_GENERIC; 	//TYPE IS A GENERIC. THIS IS NOT PART OF THE FORMAL PARAMETERS BUT REUQIRED
						//	TO SUPPORT GENERIC OF GENERIC.
	//void (* gFUNC__DESTRUCT)(unsigned char * pElement);
	void (* gFUNC__DESTRUCT)(void * pElement);
	//void (* gFUNC__COPY_CONSTRUCT)(unsigned char * pElement__to, unsigned char * pElement__from);
	void (* gFUNC__COPY_CONSTRUCT)(void * pElement__to, void const * pElement__from);
	//void (* gFUNC__MOVE_CONSTRUCT)(unsigned char * pElement__to, unsigned char * pElement__from);
	void (* gFUNC__MOVE_CONSTRUCT)(void * pElement__to, void * pElement__from);
	//void (* gFUNC__MOVE_DESTRUCT)(unsigned char * pElement);
	void (* gFUNC__MOVE_DESTRUCT)(void * pElement);
	//size_t (* gFUNC__GET_BYTE_SIZE_OF)(unsigned char * pElement); //MUST BE LARGER THAN, OR EQUAL TO, gBYTE_SIZE
	size_t (* gFUNC__GET_BYTE_SIZE_OF)(void const * pElement); //MUST BE LARGER THAN, OR EQUAL TO, gBYTE_SIZE
} Crx_C_TypeBluePrint;

#define CRX__C__TYPE_BLUE_PRINT__IS_CORRECT_FORM(pTYPE_BLUE_PRINT) \
		(((pTYPE_BLUE_PRINT)->gIS_COPYABLE || \
				(!(pTYPE_BLUE_PRINT)->gIS_COPYABLE && \
				((pTYPE_BLUE_PRINT)->gFUNC__COPY_CONSTRUCT == NULL))) && \
		(((pTYPE_BLUE_PRINT)->gBYTE_SIZE > 0) || \
				(((pTYPE_BLUE_PRINT)->gFUNC__COPY_CONSTRUCT == NULL) && \
						((pTYPE_BLUE_PRINT)->gFUNC__MOVE_CONSTRUCT == NULL) && \
						((pTYPE_BLUE_PRINT)->gFUNC__GET_BYTE_SIZE_OF == NULL)) || \
				((((pTYPE_BLUE_PRINT)->gFUNC__COPY_CONSTRUCT != NULL) || \
						((pTYPE_BLUE_PRINT)->gFUNC__MOVE_CONSTRUCT != NULL)) && \
						((pTYPE_BLUE_PRINT)->gFUNC__GET_BYTE_SIZE_OF != NULL))))


/*-------------------*/
/*-------------------*/						
/*FOR PRIMITIVES*/
/*-------------------*/
/*-------------------*/

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_TypeBluePrint const * crx_c_getTypeBluePrintForUint8();
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_TypeBluePrint const * crx_c_getTypeBluePrintForUint16();
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_TypeBluePrint const * crx_c_getTypeBluePrintForUint32();
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_TypeBluePrint const * crx_c_getTypeBluePrintForUint64();


/*-------------------*/
/*-------------------*/						
/*FOR NON GENERICS ONLY*/
/*-------------------*/
/*-------------------*/
						
/*THE FOLLOWING IS ILL DEFINED, DUE TO THE EXISTANCE OF pIS_COPYABLE AND pHAS_COPY_CONSTRUCT,
		MAKING THE FUNCTION SIGNATURE, MEANING THE MACRO SIGNATURE, ILL DEFINED. HOWEVER
		THERE IS NO SOLUTION BECAUSE TO SOLVE THIS THE MACRO HAS TO BE OVERLOADED, BUT
		THIS MACRO CAN BE USED INSIDE TEMPLATES, AND TEMPLATES USE OVERLOADED MACROS,
		AND OVERLOADED MACROS ARE UNRELIABLE IF THEY CALL EACH OTHER CURRENTLY. SEE crx.h.
		
		THERE ARE SIMILAR ISSUES WITH THE 'GENERIC' DEFINE AND DECLARE MACROS
		*/
#define CRX__C__TYPE_BLUE_PRINT__DECLARE_GET_BLUE_PRINT( \
				pCLASS_NAME, pCLASS_MEMBER_FUNCTIONS_PREFIX, \
				pIS_FIXED_SIZE, pHAS_DESTRUCT, \
				pIS_COPYABLE, pHAS_COPY_CONSTRUCT, \
				pHAS_MOVE_CONSTRUCT, pHAS_MOVE_DESTRUCT) \
		\
		CRXM__IFELSE2(pHAS_DESTRUCT, \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## destruct( \
				void * pThis);, ) \
		CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, pHAS_COPY_CONSTRUCT), \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## copyConstruct( \
				void * pThis, void const * pInstance);, ) \
		CRXM__IFELSE2(pHAS_MOVE_CONSTRUCT, \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveConstruct( \
				void * pThis, void * pInstance);, ) \
		CRXM__IFELSE2(pHAS_MOVE_DESTRUCT, \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveDestruct( \
				void * pThis);, ) \
		CRXM__IFELSE2(CRXM__NOT(pIS_FIXED_SIZE), \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() size_t _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf( \
				void const * pInstance);, ) \
		CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_TypeBluePrint const * pCLASS_MEMBER_FUNCTIONS_PREFIX ## getTypeBluePrint()
//#END_DEFINE

#define CRX__C__TYPE_BLUE_PRINT__DEFINE_GET_BLUE_PRINT( \
				pCLASS_NAME, pCLASS_MEMBER_FUNCTIONS_PREFIX, \
				pIS_FIXED_SIZE, pHAS_DESTRUCT, \
				pIS_COPYABLE, pHAS_COPY_CONSTRUCT, \
				pHAS_MOVE_CONSTRUCT, pHAS_MOVE_DESTRUCT) \
		\
		CRXM__IFELSE2(pHAS_DESTRUCT, \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## destruct( \
				void * pThis) \
			{pCLASS_MEMBER_FUNCTIONS_PREFIX ## destruct((pCLASS_NAME *)pThis);}, ) \
		CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, pHAS_COPY_CONSTRUCT), \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## copyConstruct( \
				void * pThis, void const * pInstance) \
		{ \
			pCLASS_MEMBER_FUNCTIONS_PREFIX ## copyConstruct((pCLASS_NAME *)pThis, \
					(pCLASS_NAME const *) pInstance); \
		}, ) \
		CRXM__IFELSE2(pHAS_MOVE_CONSTRUCT, \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveConstruct( \
				void * pThis, void * pInstance) \
		{ \
			pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveConstruct((pCLASS_NAME *)pThis, \
					(pCLASS_NAME *) pInstance); \
		}, ) \
		CRXM__IFELSE2(pHAS_MOVE_DESTRUCT, \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveDestruct(void * pThis) \
			{pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveDestruct((pCLASS_NAME *)pThis);}, ) \
		CRXM__IFELSE2(CRXM__NOT(pIS_FIXED_SIZE), \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() size_t _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf( \
				void const * pInstance) \
			{return pCLASS_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf((pCLASS_NAME const *)pInstance);}, ) \
		CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_TypeBluePrint const * pCLASS_MEMBER_FUNCTIONS_PREFIX ## getTypeBluePrint() \
		{ \
			static bool vIsNotFirstTime = false; \
			static Crx_C_TypeBluePrint vReturn; \
		\
			if(!vIsNotFirstTime) \
			{ \
				vReturn.gBYTE_SIZE = CRXM__IFELSE2(pIS_FIXED_SIZE, sizeof(pCLASS_NAME), 0); \
				vReturn.gIS_COPYABLE = CRXM__IFELSE2(pIS_COPYABLE, true, false); \
				vReturn.gIS_GENERIC = false; \
				vReturn.gFUNC__DESTRUCT = CRXM__IFELSE2(pHAS_DESTRUCT, \
						&_ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## destruct, NULL); \
				vReturn.gFUNC__COPY_CONSTRUCT = CRXM__IFELSE2(CRXM__AND(pIS_COPYABLE, \
								pHAS_COPY_CONSTRUCT), \
						&_ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## copyConstruct, NULL); \
				vReturn.gFUNC__MOVE_CONSTRUCT = CRXM__IFELSE2(pHAS_MOVE_CONSTRUCT, \
						&_ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveConstruct, NULL); \
				vReturn.gFUNC__MOVE_DESTRUCT = CRXM__IFELSE2(pHAS_MOVE_DESTRUCT, \
						&_ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveDestruct, NULL); \
				vReturn.gFUNC__GET_BYTE_SIZE_OF = CRXM__IFELSE2(CRXM__NOT(pIS_FIXED_SIZE), \
						&_ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf, NULL); \
			} \
		\
			return &vReturn; \
		}
//#END_DEFINE


/*-------------------*/
/*-------------------*/
/*FOR GENERICS ONLY*/
/*-------------------*/
/*-------------------*/

//NOTE YOU ARE FILLING IN THE EXITANCE OF THE FUNDAMENTAL MEMORY FUNCTIONS, AND NOT WHETHER
//		THEY ARE REQUIRED FOR THE PARITCULAR INSTANTIATION OF THE GENERIC.
#define CRX__C__TYPE_BLUE_PRINT__GENERIC__DECLARE_GET_BLUE_PRINT( \
				pCLASS_NAME, pCLASS_MEMBER_FUNCTIONS_PREFIX, \
				pIS_ALWAYS_FIXED_SIZE, pHAS_DESTRUCT, \
				pIS_SOMETIMES_COPYABLE, pHAS_COPY_CONSTRUCT, \
				pHAS_MOVE_CONSTRUCT, pHAS_MOVE_DESTRUCT) \
		CRXM__IFELSE2(pHAS_DESTRUCT, \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## destruct( \
				void * pThis);, ) \
		CRXM__IFELSE2(CRXM__AND(pIS_SOMETIMES_COPYABLE, pHAS_COPY_CONSTRUCT), \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## copyConstruct( \
				void * pThis, void const * pInstance);, ) \
		CRXM__IFELSE2(pHAS_MOVE_CONSTRUCT, \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveConstruct( \
				void * pThis, void * pInstance);, ) \
		CRXM__IFELSE2(pHAS_MOVE_DESTRUCT, \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveDestruct( \
				void * pThis);, ) \
		CRXM__IFELSE2(CRXM__NOT(pIS_ALWAYS_FIXED_SIZE), \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() size_t _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf( \
				void const * pInstance);, ) \
		CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_TypeBluePrint const * \
				pCLASS_MEMBER_FUNCTIONS_PREFIX ## getTypeBluePrint(pCLASS_NAME const * pThis)

//LIKE IN THE DECLARATION CASE, YOU ARE FILLING IN THE EXITANCE OF THE FUNDAMENTAL MEMORY FUNCTIONS, 
//		AND NOT WHETHER THEY ARE REQUIRED FOR THE PARITCULAR INSTANTIATION OF THE GENERIC. 
//		HOWEVER, WHEN IT COMES TO THE PARAMTERS NAME NAMESPACED WITH 'c::code', YOU ARE
//		FILLING IN WHETHER THE PARTICULAR INSTANCE REQUIRES THE CERTAIN FUNDAMENTAL MEMORY
//		FUNCTIONS, AND OTHER INFORMATION. FOR EXAMPLE, UNLIKE WHERE pIS_ALWAYS_FIXED_SIZE
//		IS ASKING ABOUT WHETHER THE GENERIC ITSELF IS ALWAYS FIXED SIZE, 
//		pC_CODE__IS_FIXED_SIZE IS ASKING WHETHER THIS SPECIFIC INSTANCE OF THE GENERIC IS
//		FIXED SIZED.
#define CRX__C__TYPE_BLUE_PRINT__GENERIC__DEFINE_GET_BLUE_PRINT( \
				pCLASS_NAME, pCLASS_MEMBER_FUNCTIONS_PREFIX, \
				pIS_ALWAYS_FIXED_SIZE, pHAS_DESTRUCT, \
				pIS_SOMETIMES_COPYABLE, pHAS_COPY_CONSTRUCT, \
				pHAS_MOVE_CONSTRUCT, pHAS_MOVE_DESTRUCT, \
				pC_CODE__IS_FIXED_SIZE, pC_CODE__HAS_DESTRUCT, \
				pC_CODE__IS_COPYABLE, pC_CODE__HAS_COPY_CONSTRUCT, \
				pC_CODE__HAS_MOVE_CONSTRUCT, pC_CODE__HAS_MOVE_DESTRUCT) \
		CRXM__IFELSE2(pHAS_DESTRUCT, \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## destruct( \
				void * pThis) \
			{pCLASS_MEMBER_FUNCTIONS_PREFIX ## destruct((pCLASS_NAME *)pThis);}, ) \
		CRXM__IFELSE2(CRXM__AND(pIS_SOMETIMES_COPYABLE, pHAS_COPY_CONSTRUCT), \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## copyConstruct( \
				void * pThis, void const * pInstance) \
		{ \
			pCLASS_MEMBER_FUNCTIONS_PREFIX ## copyConstruct((pCLASS_NAME *)pThis, \
					(pCLASS_NAME const *) pInstance); \
		}, ) \
		CRXM__IFELSE2(pHAS_MOVE_CONSTRUCT, \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveConstruct( \
				void * pThis, void * pInstance) \
		{ \
			pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveConstruct((pCLASS_NAME *)pThis, \
					(pCLASS_NAME *) pInstance); \
		}, ) \
		CRXM__IFELSE2(pHAS_MOVE_DESTRUCT, \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() void _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveDestruct(void * pThis) \
			{pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveDestruct((pCLASS_NAME *)pThis);}, ) \
		CRXM__IFELSE2(CRXM__NOT(pIS_ALWAYS_FIXED_SIZE), \
		CRX__LIB__PRIVATE_INLINE_C_FUNCTION() size_t _ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf( \
				void const * pInstance) \
			{return pCLASS_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf((pCLASS_NAME const *)pInstance);}, ) \
		CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_TypeBluePrint const * CRX_PASSING \
				pCLASS_MEMBER_FUNCTIONS_PREFIX ## getTypeBluePrint(pCLASS_NAME const * pThis) \
		{ \
			Crx_C_TypeBluePrint * vReturn = (Crx_C_TypeBluePrint * ) malloc( \
					sizeof(Crx_C_TypeBluePrint)); \
		\
			if(vReturn != NULL) \
			{ \
				vReturn->gBYTE_SIZE = CRXM__IFELSE2(pIS_ALWAYS_FIXED_SIZE, sizeof(pCLASS_NAME), \
						((pC_CODE__IS_FIXED_SIZE) ? sizeof(pCLASS_NAME) : 0)); \
				vReturn->gIS_COPYABLE = CRXM__IFELSE2(pIS_SOMETIMES_COPYABLE, \
						(pC_CODE__IS_COPYABLE), false); \
				vReturn->gIS_GENERIC = true; \
				vReturn->gFUNC__DESTRUCT = CRXM__IFELSE2(pHAS_DESTRUCT, \
						((pC_CODE__HAS_DESTRUCT) ? \
								&(_ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## destruct) : NULL), NULL); \
				vReturn->gFUNC__COPY_CONSTRUCT = CRXM__IFELSE2(CRXM__AND(pIS_SOMETIMES_COPYABLE, \
						pC_CODE__HAS_COPY_CONSTRUCT), \
						(((pC_CODE__IS_COPYABLE) && (pC_CODE__HAS_COPY_CONSTRUCT)) ? \
						&(_ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## copyConstruct) : NULL), NULL); \
				vReturn->gFUNC__MOVE_CONSTRUCT = CRXM__IFELSE2(pHAS_MOVE_CONSTRUCT, \
						((pC_CODE__HAS_MOVE_CONSTRUCT) ? \
						&(_ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveConstruct) : NULL), NULL); \
				vReturn->gFUNC__MOVE_DESTRUCT = CRXM__IFELSE2(pHAS_MOVE_DESTRUCT, \
						((pC_CODE__HAS_MOVE_DESTRUCT) ? \
						&(_ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## moveDestruct) : NULL), NULL); \
				vReturn->gFUNC__GET_BYTE_SIZE_OF = CRXM__IFELSE2(CRXM__NOT(pIS_ALWAYS_FIXED_SIZE), \
						((pC_CODE__IS_FIXED_SIZE) ? \
						&(_ ## pCLASS_MEMBER_FUNCTIONS_PREFIX ## getByteSizeOf) : NULL), NULL); \
			} \
		\
			return vReturn; \
		}

#define CRX__C__TYPE_BLUE_PRINT__GENERIC__FINALIZE(pTYPE_BLUE_PRINT) \
		if(pTYPE_BLUE_PRINT->gIS_GENERIC) \
			{free((void *)pTYPE_BLUE_PRINT);} \
		pTYPE_BLUE_PRINT = NULL;

CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/TypeBluePrint.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif