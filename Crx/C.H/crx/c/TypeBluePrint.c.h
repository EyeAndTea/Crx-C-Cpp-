//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/TypeBluePrint.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()

/*-------------------*/
/*-------------------*/						
/*FOR PRIMITIVES*/
/*-------------------*/
/*-------------------*/
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_TypeBluePrint const * crx_c_getTypeBluePrintForUint8()
{
	static bool vIsNotFirstTime = false;
	static Crx_C_TypeBluePrint vReturn;

	if(!vIsNotFirstTime)
	{
		vReturn.gBYTE_SIZE = 1;
		vReturn.gIS_COPYABLE = true;
		vReturn.gIS_GENERIC = false;
		vReturn.gFUNC__DESTRUCT = NULL;
		vReturn.gFUNC__COPY_CONSTRUCT = NULL;
		vReturn.gFUNC__MOVE_CONSTRUCT = NULL;
		vReturn.gFUNC__MOVE_DESTRUCT = NULL;
		vReturn.gFUNC__GET_BYTE_SIZE_OF = NULL;

		vIsNotFirstTime = true;
	}

	return &vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_TypeBluePrint const * crx_c_getTypeBluePrintForUint16()
{
	static bool vIsNotFirstTime = false;
	static Crx_C_TypeBluePrint vReturn;

	if(!vIsNotFirstTime)
	{
		vReturn.gBYTE_SIZE = 2;
		vReturn.gIS_COPYABLE = true;
		vReturn.gIS_GENERIC = false;
		vReturn.gFUNC__DESTRUCT = NULL;
		vReturn.gFUNC__COPY_CONSTRUCT = NULL;
		vReturn.gFUNC__MOVE_CONSTRUCT = NULL;
		vReturn.gFUNC__MOVE_DESTRUCT = NULL;
		vReturn.gFUNC__GET_BYTE_SIZE_OF = NULL;

		vIsNotFirstTime = true;
	}

	return &vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_TypeBluePrint const * crx_c_getTypeBluePrintForUint32()
{
	static bool vIsNotFirstTime = false;
	static Crx_C_TypeBluePrint vReturn;

	if(!vIsNotFirstTime)
	{
		vReturn.gBYTE_SIZE = 4;
		vReturn.gIS_COPYABLE = true;
		vReturn.gIS_GENERIC = false;
		vReturn.gFUNC__DESTRUCT = NULL;
		vReturn.gFUNC__COPY_CONSTRUCT = NULL;
		vReturn.gFUNC__MOVE_CONSTRUCT = NULL;
		vReturn.gFUNC__MOVE_DESTRUCT = NULL;
		vReturn.gFUNC__GET_BYTE_SIZE_OF = NULL;

		vIsNotFirstTime = true;
	}

	return &vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_TypeBluePrint const * crx_c_getTypeBluePrintForUint64()
{
	static bool vIsNotFirstTime = false;
	static Crx_C_TypeBluePrint vReturn;

	if(!vIsNotFirstTime)
	{
		vReturn.gBYTE_SIZE = 8;
		vReturn.gIS_COPYABLE = true;
		vReturn.gIS_GENERIC = false;
		vReturn.gFUNC__DESTRUCT = NULL;
		vReturn.gFUNC__COPY_CONSTRUCT = NULL;
		vReturn.gFUNC__MOVE_CONSTRUCT = NULL;
		vReturn.gFUNC__MOVE_DESTRUCT = NULL;
		vReturn.gFUNC__GET_BYTE_SIZE_OF = NULL;

		vIsNotFirstTime = true;
	}

	return &vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_TypeBluePrint const * crx_c_getTypeBluePrintForVoidPointer()
{
	static bool vIsNotFirstTime = false;
	static Crx_C_TypeBluePrint vReturn;

	if(!vIsNotFirstTime)
	{
		vReturn.gBYTE_SIZE = sizeof(void *);
		vReturn.gIS_COPYABLE = true;
		vReturn.gIS_GENERIC = false;
		vReturn.gFUNC__DESTRUCT = NULL;
		vReturn.gFUNC__COPY_CONSTRUCT = NULL;
		vReturn.gFUNC__MOVE_CONSTRUCT = NULL;
		vReturn.gFUNC__MOVE_DESTRUCT = NULL;
		vReturn.gFUNC__GET_BYTE_SIZE_OF = NULL;

		vIsNotFirstTime = true;
	}

	return &vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_TypeBluePrint const * crx_c_getTypeBluePrintForVoidFunctionPointer()
{
	static bool vIsNotFirstTime = false;
	static Crx_C_TypeBluePrint vReturn;

	if(!vIsNotFirstTime)
	{
		vReturn.gBYTE_SIZE = sizeof(void(*)(void));
		vReturn.gIS_COPYABLE = true;
		vReturn.gIS_GENERIC = false;
		vReturn.gFUNC__DESTRUCT = NULL;
		vReturn.gFUNC__COPY_CONSTRUCT = NULL;
		vReturn.gFUNC__MOVE_CONSTRUCT = NULL;
		vReturn.gFUNC__MOVE_DESTRUCT = NULL;
		vReturn.gFUNC__GET_BYTE_SIZE_OF = NULL;

		vIsNotFirstTime = true;
	}

	return &vReturn;
}





CRX__LIB__C_CODE_END()

