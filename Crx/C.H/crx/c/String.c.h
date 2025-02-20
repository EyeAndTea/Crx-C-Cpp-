//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/String.h"

#include "Crx/H/crx/c/Array.h"
#include "Crx/H/crx/c/HashTable.h"
#include <Math.h>
//<<END>>

/*
SEARCH ALGORITHMS:
ALGORITHM 1: 	memchr, and memcmp. 
				IN REVERSE WOULD REQUIRE memrchr WHICH DOES NOT EXIST IN VC6
ALGORITHM 2: 	KMP. BASED ON "string(FOR KMP ALGORITHM).pdf" IF I REMEMBER CORRECTLY.
ALGORITHM 3: 	KMP BUT WITH AN OPTIMIZATION BASED ON THE WINDOW TRICK
ALGORITHM 4:	USES THE WINDOW TRICK WITH memchr AND memcmp. 
				IN REVERSE WOULD REQUIRE memrchr WHICH DOES NOT EXIST IN VC6
ALGORITHM 5: 	BRUTE FORCE SEARCH
ALGORITHM 6: 	TWO WAY SEARCH MATCHING IMPLEMENTATION FOUND ONLINE. MEANT FOR SANITY CHECKS.
				ONLY FARWARD, NO REVERSE.
ALGORITHM 7: 	TWO WAY SEARCH ALGORITHM
ALGORITHM 8: 	USES THE WINDOW TRICK WITH memcmp ONLY. MEANT AS A REPLACEMENT FOR ALGORITHM
						4 WHEN IN REVERSE.
				FAILED TO RANK AS GOOD AS ALGORITHM 4 (IF I REMEMBER, AND DEDUCED CORRECTLY).
*/

CRX__LIB__C_CODE_BEGIN()

#if((defined(_GNU_SOURCE ) || defined(_XOPEN_SOURCE)) && defined(__GLIBC__) && \
		(__GLIBC__ >= 2) && (__GLIBC_MINOR__ >= 1))
	#define CRX__C__STRING__PRIVATE__IS_MEMMEM_AVAILABLE CRXM__TRUE
#else
	#define CRX__C__STRING__PRIVATE__IS_MEMMEM_AVAILABLE CRXM__FALSE
#endif


CRX__C__Array__DEFINE(Crx_C_String, crx_c_string_classProtected_, char, 
		uint32_t, CRX__C__STRING__PRIVATE__SIZE32_MAX, 
		16, CRXM__FALSE,
		CRXM__FALSE, CRXM__FALSE, CRXM__FALSE, CRXM__FALSE)

CRX__LIB__PRIVATE_C_FUNCTION() int32_t crx_c_string_caseInsensitivelyCompare(
		char const * pChars, char const * pChars__2, size_t pCommonLength)
{
	char const * vCurrentChar = pChars;
	char const * vEndChar = vCurrentChar + pCommonLength;
	char const * vCurrentChar2 = pChars__2;
	int32_t vReturn = 0;

	while((vCurrentChar != vEndChar) && (vReturn == 0))
	{
		if(*vCurrentChar != *vCurrentChar2)
		{
			int32_t tChar = ((int32_t)(*((unsigned char const *)vCurrentChar)));
			int32_t tChar2 = ((int32_t)(*((unsigned char const *)vCurrentChar2)));

			if((tChar >= 65) && (tChar2 <= 90))
				{tChar = tChar + 32;}
			if((tChar2 >= 65) && (tChar2 <= 90))
				{tChar2 = tChar2 + 32;}

			vReturn = tChar - tChar2;
		}

		vCurrentChar++;
		vCurrentChar2++;
	}
	
	if(vReturn == 0)
		{return 0;}
	else
		{return ((vReturn > 0) ? 1 : -1);}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_areStringsEqual(void const * pString,
		void const * pString__2)
{
	if((pString != NULL) && (pString__2 != NULL))
	{
		return crx_c_string_isEqualTo((Crx_C_String const *)pString, 
				(Crx_C_String const *)pString__2, false);
	}
	else
		{return false;}//TWO NULLS ARE NOT EQUAL
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getHash(size_t pSeed, 
		void const * CRX_NOT_NULL pString)
{
	return crx_c_hashTable_compute32BitsHash(pSeed, 
			crx_c_string_classProtected_constantGetElementsPointer(pString),
			crx_c_string_classProtected_getLength(pString));
}


CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_construct(Crx_C_String * pThis)
{
	crx_c_string_classProtected_construct(pThis, 4);
	crx_c_string_silentlyAppendNullTerminator(pThis);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_construct2(Crx_C_String * pThis, 
		char const * pString)
{
	size_t vLength = ((pString == NULL) ? 0 : strlen(pString));
	
	crx_c_string_construct(pThis, vLength + 4);
	crx_c_string_insertCharsAt(pThis, 0, pString, vLength);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_construct3(Crx_C_String * pThis, 
		char const * pChars, size_t pSize)
{
	size_t vLength = ((pChars == NULL) ? 0 : pSize);

	crx_c_string_construct(pThis, vLength);
	crx_c_string_insertCharsAt(pThis, 0, pChars, vLength);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_construct5(Crx_C_String * pThis, char pChar)
{
	crx_c_string_construct(pThis, 1);
	crx_c_string_classProtected_push2(pThis, pChar);//WE ARE ASSUMING 12 EMPTY SPACES ALREADY
	crx_c_string_silentlyAppendNullTerminator(pThis);
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_copyConstruct(Crx_C_String * pThis, 
		Crx_C_String const * CRX_NOT_NULL pString)
	{crx_c_string_classProtected_copyConstruct(pThis, pString);}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String * crx_c_string_new()
{
	Crx_C_String * vString = crx_c_string_classProtected_new(1);

	if(vString != NULL)
		{crx_c_string_silentlyAppendNullTerminator(pThis);}
	
	return vString;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String * crx_c_string_new2(char const * pString)
{
	size_t vLength = ((pString == NULL) ? 0 : strlen(pString));
	Crx_C_String * vString = crx_c_string_classProtected_new(vLength + 4);
	
	if(vString != NULL)
		{crx_c_string_insertCharsAt(vString, 0, pString, vLength);}
	
	return vString;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String * crx_c_string_new3(char const * pChars, size_t pSize)
{
	size_t vLength = ((pChars == NULL) ? 0 : pSize);
	Crx_C_String * vString = crx_c_string_classProtected_new(vLength + 4);
	
	if(vString != NULL)
		{crx_c_string_insertCharsAt(vString, 0, pChars, vLength);}
	
	return vString;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String * crx_c_string_new5(char pChar)
{
	Crx_C_String * vString = crx_c_string_classProtected_new(1);
	
	if(vString != NULL)
		{crx_c_string_insertCharsAt(vString, 0, &pChar, 1);}
	
	return vString;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_moveNew(Crx_C_String * CRX_NOT_NULL pString)
	{crx_c_string_classProtected_moveNew(pString);}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_copyNew(Crx_C_String const * CRX_NOT_NULL pString)
	{crx_c_string_classProtected_copyNew(pString);}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_destruct(Crx_C_String * pThis)
	{crx_c_string_classProtected_destruct(pThis);}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_free(Crx_C_String * pThis)
	{crx_c_string_classProtected_free(pThis);}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_getSize(Crx_C_String * pThis)
	{return crx_c_string_classProtected_getLength(pThis);}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_getCapacity(Crx_C_String * pThis)
	{return crx_c_string_classProtected_getCapacity(pThis) - 4;}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_ensureCapacity(Crx_C_String * pThis,
		size_t pCapacity)
	{return crx_c_string_classProtected_ensureCapacity(pThis, pCapacity + 4);}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_empty(Crx_C_String * pThis)
	{return crx_c_string_classProtected_empty(pThis);}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_copyAssignFrom(Crx_C_String * pThis,
		Crx_C_String const * CRX_NOT_NULL pString)
{
	if(crx_c_string_classProtected_ensureCapacity(pThis, 
			crx_c_string_classProtected_getLength(pString) + 4))
	{
		crx_c_string_classProtected_copyAssignFrom(pThis, pString);
		crx_c_string_silentlyAppendNullTerminator(pThis);
		
		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_trySwapContentWith(
		Crx_C_String * pThis, Crx_C_String * CRX_NOT_NULL pString)
{
	bool vReturn = true;

	if(!crx_c_string_classProtected_tryToPilferSwapContentWith(pThis, pString));
	{
		if((crx_c_string_classProtected_getCapacity(pThis) <= 16) &&
				(crx_c_string_classProtected_getCapacity(pString) <= 16))
		{
			unsigned char vBuffer01[16] /*= ?*/;
			size_t tLength = crx_c_string_classProtected_getLength(pThis);

			memcpy(&(vBuffer01[0]), crx_c_string_classProtected_getElementsPointer(pThis), tLength);
			
			crx_c_string_classProtected_empty(pThis);
			crx_c_string_appendString(pThis, pString);
				
			crx_c_string_empty(pString);
			crx_c_string_appendChars(pString, &(vBuffer01[0]), tLength);
		}
		else
		{
			if(crx_c_string_classProtected_getCapacity(pThis) <= 16)
				{vReturn = crx_c_string_classProtected_ensureCapacity(pThis, 32);}
			if(vReturn && crx_c_string_classProtected_getCapacity(pString) <= 16)
				{vReturn = crx_c_string_classProtected_ensureCapacity(pString, 32);}
			
			if(vReturn)
			{
				vReturn = crx_c_string_classProtected_tryToPilferSwapContentWith(pThis, pString);
				
				assert(vReturn);
			}
		}
	}

	if(vReturn)
	{
		vReturn = crx_c_string_silentlyAppendNullTerminator(pThis) &&
				crx_c_string_silentlyAppendNullTerminator(pString);

		assert(vReturn);
	}
	
	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() char crx_c_string_copyGet(Crx_C_String const * pThis, size_t pIndex);
	{return crx_c_string_classProtected_copyGet(pThis, pIndex);}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_insertCharCopiesAt(Crx_C_String * pThis,
		size_t pIndex, char const pChar, size_t pNumberOfCopies)
{
	if(crx_c_string_classProtected_ensureCapacity(crx_c_string_classProtected_getLength(pThis) + 
			pNumberOfCopies + 4))
	{
		crx_c_string_classProtected_insertElementCopiesAt2(pThis, pIndex, pChar, pNumberOfCopies);
		crx_c_string_silentlyAppendNullTerminator(pThis);

		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_insertCharsAt(Crx_C_String * pThis,
		size_t pIndex, char const * CRX_NOT_NULL pChars, size_t pWidth)
{
	if(crx_c_string_classProtected_ensureCapacity(crx_c_string_classProtected_getLength(pThis) + 
			pWidth + 4))
	{
		crx_c_string_classProtected_insertCArrayAt(pThis, pIndex, pChars, pWidth);
		crx_c_string_silentlyAppendNullTerminator(pThis);
		
		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_removeChars(Crx_C_String * pThis,
		size_t pIndex, size_t pWidth)
{
	crx_c_string_classProtected_removeElements(pThis, pIndex, pWidth);
	crx_c_string_silentlyAppendNullTerminator(pThis);
}
CRX__LIB__PUBLIC_C_FUNCTION() char * crx_c_string_getCharsPointer(Crx_C_String * pThis)
	{return crx_c_string_classProtected_getElementsPointer(pThis);}
CRX__LIB__PUBLIC_C_FUNCTION() char const * crx_c_string_constantGetCharsPointer(
		Crx_C_String const * pThis)
	{return crx_c_string_classProtected_constantGetElementsPointer(pThis);}
CRX__LIB__PUBLIC_C_FUNCTION() char * crx_c_string_getCArray(Crx_C_String * pThis, char pChar)
	{return crx_c_string_classProtected_getCArray(pThis, pChar);}
CRX__LIB__PUBLIC_C_FUNCTION() char * crx_c_string_unsafeGetCArray(Crx_C_String * pThis)
	{return crx_c_string_classProtected_unsafeGetCArray(pThis);}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_updateLength(Crx_C_String * pThis,
		size_t pLength)
{
	if(pLength > (crx_c_string_classProtected_getCapacity(pThis) - 4))
		{return false;}
	
	if(crx_c_string_classProtected_updateLength(pThis, pLength))
	{
		crx_c_string_silentlyAppendNullTerminator(pThis);
	
		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_unsafeUpdateLength(Crx_C_String * pThis,
		size_t pLength)
{
	if(pLength > (crx_c_string_classProtected_getCapacity(pThis) - 4))
		{return false;}
	
	if(crx_c_string_classProtected_unsafeUpdateLength(pThis, pLength))
	{
		crx_c_string_silentlyAppendNullTerminator(pThis);
		
		return true;
	}
	else
		{return false;}
}


CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendString(Crx_C_String * pThis, 
		Crx_C_String const * CRX_NOT_NULL pString)
{
	return crx_c_string_insertCharsAt(pThis, crx_c_string_classProtected_getLength(pThis), 
			crx_c_string_classProtected_constantGetElementsPointer(pString), 
			crx_c_string_classProtected_getLength(pString));
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendChar(Crx_C_String * pThis, char pChar)
{
	return crx_c_string_insertCharsAt(pThis, crx_c_string_classProtected_getLength(pThis), 
			&pChar, 1);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendCString(Crx_C_String * pThis, 
		char const * pString)
{
	return crx_c_string_insertCharsAt(pThis, crx_c_string_classProtected_getLength(pThis), pString, 
			strlen(pString));
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendChars(Crx_C_String * pThis, 
		char const * CRX_NOT_NULL pChars, size_t pSize)
{
	return crx_c_string_insertCharsAt(pThis, crx_c_string_classProtected_getLength(pThis), pChars, 
			pSize);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendSub(Crx_C_String * pThis, 
		Crx_C_String_Sub const * CRX_NOT_NULL pSub)
{
	return crx_c_string_appendChars(pThis, crx_c_string_sub_getCharsPointer(pSub),
			crx_c_string_sub_getLength(pSub));
}
/*CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendWideChars(Crx_C_String * pThis, 
		wchar_t const * pWchars, size_t pSize)
{
	if(pWchars == NULL)
		{return true;}

	return crx_c_string_insertCharsAt(pThis, crx_c_string_classProtected_getLength(pThis), 
			(char const *)pWchars, pSize * sizeof(wchar_t));
}*/
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendInt(Crx_C_String * pThis, int32_t pInt)
{
	char vChars[100] /*= ?*/;
	
	sprintf(vChars, "%d", pInt);
	
	return crx_c_string_appendCString(pThis, vChars);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendInt2(Crx_C_String * pThis, 
		uint32_t pNumberOfDigits, int32_t pInt)
{
	if(pNumberOfDigits < 50)
	{
		char vChars[100] /*= ?*/;
	
		sprintf(vChars, "%.*d", pNumberOfDigits, pInt);
	
		return crx_c_string_appendCString(pThis, vChars);
	}
	else
	{
		size_t tCurrentLength = crx_c_string_classProtected_getLength(pThis);
		size_t tAvailableSpace = crx_c_string_getCapacity(pThis) - tCurrentLength;

		if((tAvailableSpace < (pNumberOfDigits + 50 + 4)) || 
				crx_c_string_ensureCapacity(pThis, tCurrentLength + 50 + 4 + pNumberOfDigits))
		{
			crx_c_string_classProtected_insertElementCopiesAt2(pThis, tCurrentLength, '\0', 
					50 + 4 + pNumberOfDigits);

			sprintf(crx_c_string_classProtected_getElementsPointer(pThis) + tCurrentLength, 
					"%.*d", pNumberOfDigits, pInt);

			return true;
		}
		else
			{return false;}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_looselyAppendFloat(Crx_C_String * pThis, double pDouble)
{
	char vChars[100] /*= ?*/;
	
	sprintf(vChars, "%#.32G", pDouble);
	
	return crx_c_string_appendCString(pThis, vChars);
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_silentlyAppendNullTerminator(Crx_C_String * pThis)
{//THIS ASSUMES THERE ARE ALWAYS FOUR SPACES LEFT
	char * tChars = crx_c_string_classProtected_unsafeGetCArray(pThis); //crx_c_string_classProtected_getElementsPointer(pThis);

	size_t tLength = crx_c_string_classProtected_getLength(pThis);

	*(tChars + tLength) = '\0';
	*(tChars + tLength + 1) = '\0';
	*(tChars + tLength + 2) = '\0';
	*(tChars + tLength + 3) = '\0';
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEmpty(Crx_C_String const * pThis)
{
	if(crx_c_string_classProtected_getLength(pThis) == 0)
		{return true;}

	CRX_FOR(size_t tI = 0, tI < crx_c_string_classProtected_getLength(pThis), tI++)
	{
		if(!(((crx_c_string_classProtected_copyGet(pThis, tI) >= 0) && 
				(crx_c_string_classProtected_copyGet(pThis, tI) <= 32)) || 
				(crx_c_string_classProtected_copyGet(pThis, tI) == 127)))
			{return false;}
	}
	CRX_ENDFOR

	return true;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_trim(Crx_C_String * pThis)
{
	char * vChars = crx_c_string_classProtected_unsafeGetCArray(pThis);
	char * vChars__end = vChars + crx_c_string_classProtected_getLength(pThis);
	size_t vStartIndex = 0;

	/*while((vChars != vChars__end) && (((*vChars >= 9) && (*vChars <= 13)) ||
			(*vChars == 32) || (*vChars == 127)))*/
	while((vChars != vChars__end) && (((*vChars >= 0) && (*vChars <= 32)) ||
			(*vChars == 127)))
	{
		vChars++;
		vStartIndex++;
	}
	
	if(vChars != vChars__end)
	{
		char * tChars = vChars__end - 1;
		size_t tEndIndex = crx_c_string_classProtected_getLength(pThis);

		/*while(((*tChars >= 9) && (*tChars <= 13)) ||
				(*tChars == 32) || (*vChars == 127))*/
		while(((*tChars >= 0) && (*tChars <= 32)) || (*vChars == 127))
		{
			tEndIndex--;

			if(tChars != vChars)
				{tChars--;}
			else
				{break;}
		}

		crx_c_string_unsafeUpdateLength(pThis, tEndIndex);
		crx_c_string_removeChars(pThis, 0, vStartIndex);
	}
	else
		{crx_c_string_unsafeUpdateLength(pThis, 0);}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_leftTrim(Crx_C_String * pThis)
{
	char * vChars = crx_c_string_classProtected_unsafeGetCArray(pThis);
	char * vChars__end = vChars + crx_c_string_classProtected_getLength(pThis);
	size_t vStartIndex = 0;

	/*while((vChars != vChars__end) && (((*vChars >= 9) && (*vChars <= 13)) ||
			(*vChars == 32) || (*vChars == 127)))*/
	while((vChars != vChars__end) && (((*vChars >= 0) && (*vChars <= 32)) ||
			(*vChars == 127)))
	{
		vChars++;
		vStartIndex++;
	}

	crx_c_string_removeChars(pThis, 0, vStartIndex);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_rightTrim(Crx_C_String * pThis)
{
	CRX_SCOPE_META
	if(crx_c_string_classProtected_getLength(pThis) == 0)
		{return;}

	CRX_SCOPE
	char * vChars = crx_c_string_classProtected_unsafeGetCArray(pThis);
	char * vChars__last = vChars + crx_c_string_classProtected_getLength(pThis) - 1;
	size_t tEndIndex = crx_c_string_classProtected_getLength(pThis);

	/*while(((*vChars__last >= 9) && (*vChars__last <= 13)) ||
			(*vChars__last == 32) || (*vChars == 127))*/
	while(((*vChars__last >= 0) && (*vChars__last <= 32)) ||
			(*vChars == 127))
	{
		tEndIndex--;

		if(vChars__last != vChars)
			{vChars__last--;}
		else
			{break;}
	}

	crx_c_string_unsafeUpdateLength(pThis, tEndIndex);
	CRX_SCOPE_END
}


CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEqualTo(Crx_C_String const * pThis,
		Crx_C_String const * CRX_NOT_NULL pString, bool pIsCaseInSensitive)
{
	return crx_c_string_isEqualTo3(pThis, 
			crx_c_string_classProtected_constantGetElementsPointer(pString),
			crx_c_string_classProtected_getLength(pString), pIsCaseInSensitive);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEqualTo2(Crx_C_String const * pThis,
		char const * CRX_NOT_NULL pString, bool pIsCaseInSensitive)
	{return crx_c_string_isEqualTo3(pThis, pString, strlen(pString), pIsCaseInSensitive);}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEqualTo3(Crx_C_String const * pThis,
		char const * CRX_NOT_NULL pChars, size_t pSize, bool pIsCaseInSensitive)
{
	if(crx_c_string_classProtected_getLength(pThis) != pSize)
		{return false;}
	else
	{
		if(!pIsCaseInSensitive)
		{
			return (memcmp(crx_c_string_classProtected_constantGetElementsPointer(pThis), pChars, 
					pSize) == 0);
		}
		else
		{
			return (crx_c_string_caseInsensitivelyCompare(
					crx_c_string_classProtected_constantGetElementsPointer(pThis), pChars, 
					pSize) == 0);
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEqualTo4(Crx_C_String const * pThis,
		Crx_C_String_Sub const * CRX_NOT_NULL pSub, bool pIsCaseInSensitive)
{
	return crx_c_string_isEqualTo3(pThis, crx_c_string_sub_getCharsPointer(pSub),
			crx_c_string_sub_getLength(pSub), pIsCaseInSensitive);
}

CRX__LIB__PUBLIC_C_FUNCTION() char const * crx_c_string_getCString(Crx_C_String const * pThis)
{
	char const * tChars = crx_c_string_classProtected_constantGetElementsPointer(pThis);	//crx_c_string_classProtected_unsafeGetCArray(pThis); 
																					//crx_c_string_classProtected_getElementsPointer(pThis); <== was this first

	//THIS PROTECTS FROM USER GETTING CHARS, WHETHER SAFELY OR UNSAFELY, THEN CALLING THIS BEFORE 
	//		UPDATING LENGTH
	if((tChars != NULL) && (*(tChars + tLength) == '\0') &&  (*(tChars + tLength + 1) == '\0') &&
			(*(tChars + tLength + 2) == '\0') && (*(tChars + tLength + 3) == '\0'))
		{return tChars;}
	else
		{return NULL;}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isBeginningWith(Crx_C_String const * pThis,
		Crx_C_String const * CRX_NOT_NULL pString, bool pIsCaseInSensitive)
{
	return crx_c_string_isBeginningWith3(pThis, 
			crx_c_string_classProtected_constantGetElementsPointer(pString),
			crx_c_string_classProtected_getLength(pString), pIsCaseInSensitive);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isBeginningWith2(Crx_C_String const * pThis,
		char const * CRX_NOT_NULL pString, bool pIsCaseInSensitive)
	{return crx_c_string_isBeginningWith3(pThis, pString, strlen(pString), pIsCaseInSensitive);}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isBeginningWith3(Crx_C_String const * pThis,
		char const * CRX_NOT_NULL pChars, size_t pSize, bool pIsCaseInSensitive)
{
	if(crx_c_string_classProtected_getLength(pThis) < pSize)
		{return false;}
	else
	{
		if(!pIsCaseInSensitive)
		{
			return (memcmp(crx_c_string_classProtected_constantGetElementsPointer(pThis), 
					pChars, pSize) == 0);
		}
		else
		{
			return (crx_c_string_caseInsensitivelyCompare(
					crx_c_string_classProtected_constantGetElementsPointer(pThis), pChars, 
					pSize) == 0);
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isBeginningWith4(Crx_C_String const * pThis,
		Crx_C_String_Sub const * pSub, bool pIsCaseInSensitive)
{
	if(crx_c_string_sub_getLength(pSub) == 0)
		{return true;} //BASED ON THE BEHAVIOR OF memcmp(x, y, 0)
	else
	{
		return crx_c_string_isBeginningWith3(pThis, crx_c_string_sub_getCharsPointer(pSub),
				crx_c_string_sub_getLength(pSub), pIsCaseInSensitive);
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEndingWith(Crx_C_String const * pThis,
		Crx_C_String const * CRX_NOT_NULL pString, bool pIsCaseInSensitive)
{
	return crx_c_string_isEndingWith3(pThis, 
			crx_c_string_classProtected_constantGetElementsPointer(pString),
			crx_c_string_classProtected_getLength(pString), pIsCaseInSensitive);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEndingWith2(Crx_C_String const * pThis,
		char const * CRX_NOT_NULL pString, bool pIsCaseInSensitive)
	{return crx_c_string_isEndingWith3(pThis, pString, strlen(pString), pIsCaseInSensitive);}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEndingWith3(Crx_C_String const * pThis,
		char const * CRX_NOT_NULL pChars, size_t pSize, bool pIsCaseInSensitive)
{
	if(crx_c_string_classProtected_getLength(pThis) < pSize)
		{return false;}
	else
	{
		if(!pIsCaseInSensitive)
		{
			return (memcmp(crx_c_string_classProtected_constantGetElementsPointer(pThis) + 
					crx_c_string_classProtected_getLength(pThis) - pSize, pChars, pSize) == 0);
		}
		else
		{
			return (crx_c_string_caseInsensitivelyCompare(
					crx_c_string_classProtected_constantGetElementsPointer(pThis) + 
					crx_c_string_classProtected_getLength(pThis) - pSize, pChars, pSize) == 0);
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEndingWith4(Crx_C_String const * pThis,
		Crx_C_String_Sub const * CRX_NOT_NULL pSub, bool pIsCaseInSensitive)
{
	if(crx_c_string_sub_getLength(pSub) == 0)
		{return true;} //BASED ON THE BEHAVIOR OF memcmp(x, y, 0)
	else
	{
		return crx_c_string_isEndingWith3(pThis, crx_c_string_sub_getCharsPointer(pSub),
				crx_c_string_sub_getLength(pSub), pIsCaseInSensitive);
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_lowerTheCase(Crx_C_String * pThis)
{
	char * vChars = crx_c_string_classProtected_unsafeGetCArray(pThis);
	char * vChars__end = vChars + crx_c_string_classProtected_getLength(pThis);

	while(vChars != vChars__end)
	{
		if((*vChars >= 65) && (*vChars <= 90))
			{*vChars = *vChars + 32;}

		vChars++;
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_upperTheCase(Crx_C_String * pThis)
{
	char * vChars = crx_c_string_classProtected_unsafeGetCArray(pThis);
	char * vChars__end = vChars + crx_c_string_classProtected_getLength(pThis);

	while(vChars != vChars__end)
	{
		if((*vChars >= 97) && (*vChars <= 122))
			{*vChars = *vChars - 32;}

		vChars++;
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstOccuranceOf(
		Crx_C_String const * pThis, size_t pStartIndex, Crx_C_String const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_getIndexOfFirstOccuranceOf3(pThis, pStartIndex,
			crx_c_string_classProtected_constantGetElementsPointer(pDelimiter),
			crx_c_string_classProtected_getLength(pDelimiter),
			pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstOccuranceOf2(
		Crx_C_String const * pThis, size_t pStartIndex, char const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_getIndexOfFirstOccuranceOf3(pThis, pStartIndex,
			pDelimiter, strlen(pDelimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstOccuranceOf3(
		Crx_C_String const * pThis, size_t pStartIndex, char const * pChars__delimiter, 
		size_t pSize, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	CRX_SCOPE_META
	if((crx_c_string_classProtected_getLength(pThis) <= pStartIndex) ||
			((crx_c_string_classProtected_getLength(pThis) - pStartIndex) < pSize) || (pSize == 0))
		{return ((size_t)(-1));}

	CRX_SCOPE
	uint32_t vAlgorithm = 0;
	uint8_t vSizeOfCharacterSet = ((pSizeOfCharacterSet == 0) ? 255 : pSizeOfCharacterSet);
	size_t vFullLength = crx_c_string_classProtected_getLength(pThis);
	size_t vLength = vFullLength - pStartIndex;
	char const * vChars = crx_c_string_classProtected_constantGetElementsPointer(pThis) + 
			pStartIndex;
	size_t vReturn = vFullLength;
#if(CRX__C__STRING__PRIVATE__IS_MEMMEM_AVAILABLE)
	char * vChars__startOfFoundOccurance = NULL;
#endif
	

#if(CRX__C__STRING__PRIVATE__IS_MEMMEM_AVAILABLE)
	vChars__startOfFoundOccurance = memmem(vChars, vLength, pChars__delimiter, pSize);

	if(vChars__startOfFoundOccurance != NULL)
		{vReturn = vChars__startOfFoundOccurance - vChars;}
	else
		{vReturn = ((size_t)(-1));}

	return vReturn;
#else
	/*
	NOTE: CURRENTLY, THE FOLLOWING IS PER THE ASSUMPTION THAT THE USER IS USING THE FUNCTION TO FIND
			THE FIRST OCCURANCE ONLY
	*/
	/*if(pLength < 5)
		{vAlgorithm = 1;}
	else
	{
		double tSizeOfCharacterSet = ((double)pSizeOfCharacterSet);
		double s2 = (tSizeOfCharacterSet * (1.0 - pow(1.0 - (1.0/tSizeOfCharacterSet), pLength)));//EXPECTED DISTINCT CHARACTERS IN DELIMITER
		double q = 0.4;
		double e = 1.0 / (((1.0 - q) / tSizeOfCharacterSet) + (q / s2));
		
		/*if(e > pLength)
			//{e = pLength;}* /
		
		/*if((pLength < 4) || (pLength * (vLength - pLength) <= 80000 * (1.0 - (1.0/vSizeOfCharacterSet))))* /
		//if(e <= 7)
		//	{vAlgorithm = 7/*6* /;}
		if(e <= 22)
			{vAlgorithm = 4;}
		else if(e <= 40)
			{vAlgorithm = 1;}
		else if(pLength < 7340032)
		{
			/*if(pLength < 16)
				{vAlgorithm = 2;}			
			else
				{vAlgorithm = 3;}* /

			vAlgorithm = 3;
		}
		else
			{vAlgorithm = 4;}
	}
	if(pLength < 5)
		{vAlgorithm = 1;}
	else
	{
		vAlgorithm = 4;
	}*/
	
	//THE FOLLOWING WAS PER THE BENCHMARKS. NOTE THIS SHOULD BE ASSUMED VALID ONLY FOR
	//		FARWARD FIRST OCCURANCE SEARCH.
	if(pSize <= 8)
		{vAlgorithm = 1;}
	else if(pSize < 32768)
	{
		if(vSizeOfCharacterSet > 16)
			{vAlgorithm = 4;}
		else
			{vAlgorithm = 1;}
	}
	else
		{vAlgorithm = 4;}
	
	if(vAlgorithm == 1)
	{
		char const * tChar = vChars;
		char const * tEndChar = vChars + (vLength - pSize + 1);

		while(tChar < tEndChar)
		{
			tChar = memchr(tChar, *pChars__delimiter, tEndChar - tChar);

			if(tChar != NULL)
			{
				if(memcmp(tChar, pChars__delimiter, pSize) == 0)
				{
					vReturn = tChar - vChars;

					break;
				}
				else
					{tChar++;}
			}
			else
				{break;}
		}
	}
#if(0)	
	else if(vAlgorithm <= 3)
	{
		/*
		KMP ALOGIRTHM

		NOTE: GIVEN A STRING[1..N], THE Nth SUFFIX PREFIX IS THE Nth LARGEST PREFIX OF THE STRING
				THAT IS ALSO ITS SUFFIX. THE LARGEST SUFFIX PREFIX IS THE STRING ITSELF. IN OTHER
				WORDS:
						SUFFIX_PREFIX{n}(STRING) = STRING[N-K+1..N] = STRING[1..K]  ; K IS THE LENGTH OF
								THE nth LARGEST SUFFIX PREFIX.
				NOTE THAT THE LENGTH OF STRING[X..Y] IS Y - X + 1. IN OTHER WORDS
								|STRING[N-K+1..N]| = K
				
				WE ARE FOR THE ALGOIRTHM ONLY INTERESTED IN THE SECOND LARGEST SUFFIX PREFIX.
				
				NOTE THAT IF FOR SUBSTRING STRING[A..B], 
						|SUFFIX_PREFIX{2}(STRING[A..B])| = K, 
				THEN FOR SUBSTRING STRING[A..B+1] 
						|SUFFIX_PREFIX{2}(STRING[A..B+1])| <= K + 1
				BECAUSE OTHERWISE THIS SUFFIX PREFIX WOULD END AT (A + K + L) FOR L > 0, MAKING IT A 
				CONTRADITCTION BECUASE THEN K WOULD NOT HAVE BEEN THE LENGTH OF THE SECOND LARGEST 
				SUFFIX PREFIX OF STRING[A..B].

				*NOTE THAT THE THIRD LARGEST SUFFIX PREFIX OF STRING[1..N], MEANING
						SUFFIX_PREFIX{3}(STRING[1..N])
				WOULD BE A SUBSTRING AND A SUFFIX PREFIX OF STRING[N-K+1..N], THE SECOND LARGEST 
				SUFFIX PREFIX, MEANING A SUBTRING OF
						SUFFIX_PREFIX{2}(STRING[1..N]) = STRING[N-K+1..N]
				AND BECAUSE STRING[N-K+1..N] IS EQUAL TO STRING[1..K], IT FOLLOWS THAT THIS THIRD 
				LARGEST SUFFIX PREFIX IS ALSO THE SECOND LARGEST SUFFIX PREFIX OF STRING[1..K]. IN OTHER
				WORDS
						SUFFIX_PREFIX{3}(STRING[1..N]) = SUFFIX_PREFIX{2}(SUFFIX_PREFIX{2}(STRING[1..N]))
													   = SUFFIX_PREFIX{2}(STRING[N-K+1..N])
													   = SUFFIX_PREFIX{2}(STRING[1..K])
				IF THIS WAS NOT THE CASE IT WOULD BE A CONTRADICTION. FOR EXAMPLE, IF THE LENGTH OF THE 
				THIRD LARGEST SUFFIX PREFIX OF STRING[1..N] IS L, THEN WE KNOW L < K AND WE KNOW THAT 
				THERE CAN BE NO OTHER SUFFIX PREFIX WHOSE LENGTH Y IS L < Y < K, AND NOW IF THIS SUFFIX 
				PREFIX IS NOT THE SECOND LARGEST SUFFIX PREFIX OF STRING[1..K], SUCH AS IT IS THE THIRD 
				LARGEST FOR EXAMPLE, THEN THERE EXISTS A SUFFIX PREFIX FOR STRING[1..K] WHOSE LENGTH 
				M > L. HOWEVER THIS SUFFIX PREFIX WOULD BE A SUFFIX PREFIX OF STRING[1..N], YET ITS 
				LENGTH M > L WHILE NOT BEING M = K, MEANING L < M < K WHICH IS A CONTRADICTION.
		*/
		size_t tCurrentIndexInDelimiter = 0;
		size_t * tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = NULL;
		bool tIsToFree = false;
		
		if(pSize + 1 > 80)
		{
			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
					calloc(1, sizeof(size_t) * (pSize + 1));
			tIsToFree = true;
		}
		else
		{
			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
					CRX__ALLOCA(sizeof(size_t) * (pSize + 1));
		}
		
		tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[0] = 0;
		CRX_FOR(size_t tI = 1, tI < pSize, tI++)
		{        
			size_t tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tI - 1];

			//IF SECOND LARGEST SUFFIX PREFIX DOES NOT HELP, WE SEEK OUT THE THIRD LARGEST
			//		SUFFIX PREFIX WHICH HAPPENS TO BE THE SECOND LARGEST SUFFIX PREFIX OF THE
			//		SECOND LARGEST SUFFIX PREFIX. AND SO FORTH.
			while((tJ != 0) && (*(pChars__delimiter + tI) != *(pChars__delimiter + tJ)))
				{tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tJ - 1];}

			if(*(pChars__delimiter + tI) == *(pChars__delimiter + tJ))
				{tJ += 1;}

			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tI] = tJ;
		}
		CRX_ENDFOR

		if(vAlgorithm == 2)
		{
			//NOTE: THIS ALGORITHM DOES NOT EXIT EARLY.

			CRX_FOR(size_t tI = 0, tI < vLength, tI++)
			{
				while((tCurrentIndexInDelimiter != 0) && 
						(*(vChars + tI) != *(pChars__delimiter + tCurrentIndexInDelimiter)))
				{
					//SEE * ABOVE.
					tCurrentIndexInDelimiter = 
							tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
							tCurrentIndexInDelimiter - 1];
				}
				
				if(*(vChars + tI) == *(pChars__delimiter + tCurrentIndexInDelimiter))
					{tCurrentIndexInDelimiter += 1;}

				/*
					AT THIS POINT, THE FOLLOWING MUST ALWAYS HOLD TRUE
							vChars[tI + 1 - tCurrentIndexInDelimiter:tI + 1] == 
									pChars__delimiter[0:tCurrentIndexInDelimiter]
					IN OTHER WORDS, THE WINDOW, pChars__delimiter[0:tCurrentIndexInDelimiter], IS ALWAYS VALID, 
					ALWAYS EQUAL TO THE OVERLAP EVEN AFTER SHIFTING.
				*/

				if(tCurrentIndexInDelimiter == pSize)
				{
					vReturn = tI + 1 - pSize;

					break;
				}
			}
			CRX_ENDFOR
		}
		else
		{
			//NOTE: THIS ALGORITHM DOES NOT EXIT EARLY, BUT IS SAFE.
			//OLD NOTE: WHEN THE CHARACTER SET IS VERY SMALL, THIS IS THE FASTEST, BUT STILL TWICE 
			//		AS SLOW	FOR RANDOM INPUT, AND MORE SLOW FOR HIGHLY PATTERNED INTPUT UP TO THREE 
			//		TIMES AS SLOW
			uint32_t tReverseIndexOfCharacterLastOccurance[256] /*= ?*/;
			char tLastCharacter = *(pChars__delimiter + pSize - 1);
			
			CRX_FOR(size_t tI = 0, tI < 256, tI++)
				{tReverseIndexOfCharacterLastOccurance[tI] = (uint32_t)pSize;}
			CRX_ENDFOR

			CRX_FOR(size_t tI = 0, tI < pSize, tI++)
			{
				if(tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pChars__delimiter)  + tI)] > (pSize - tI - 1))
					{tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pChars__delimiter)  + tI)] = pSize - tI - 1;}
			}
			CRX_ENDFOR
			
			CRX_FOR(size_t tI = 0, tI < vLength, tI++)
			{
				if(tCurrentIndexInDelimiter == 0)
				{
					while((tI <= vLength - pSize) && (*(vChars + tI + pSize - 1) != tLastCharacter))
						{tI = tI + tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)vChars) + tI + pSize - 1)];}
				}
				else
				{
					while((tCurrentIndexInDelimiter != 0) && 
							(*(vChars + tI) != *(pChars__delimiter + tCurrentIndexInDelimiter)))
					{
						//SEE * ABOVE.
						tCurrentIndexInDelimiter = 
								tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
								tCurrentIndexInDelimiter - 1];
					}
				}


				if(*(vChars + tI) == *(pChars__delimiter + tCurrentIndexInDelimiter))
					{tCurrentIndexInDelimiter += 1;}

				/*SEE ABOVE*/
				if(tCurrentIndexInDelimiter == pSize)
				{
					vReturn = tI + 1 - pSize;

					break;
				}
			}
			CRX_ENDFOR
		}

		if(tIsToFree)
		{
			free(tSecondLargestSuffixPrefixForSubDelimiterUpToIndex);
			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = NULL;
		}
	}
#endif
	else if(vAlgorithm == 4)
	{
		//OLD NOTE: WHEN THE CHARACTER SET IS VERY SMALL, THIS IS THE SLOWEST
		unsigned char const * tChar = vChars;
		unsigned char const * tEndChar = vChars + (vLength - pSize) + 1;
		unsigned char tLastCharacter = *(pChars__delimiter + pSize - 1);
		uint32_t tReverseIndexOfCharacterLastOccurance[256] /*= ?*/;

		CRX_FOR(size_t tI = 0, tI < 256, tI++)
			{tReverseIndexOfCharacterLastOccurance[tI] = (uint32_t)pSize;}
		CRX_ENDFOR
		
		CRX_FOR(size_t tI = 0, tI < pSize, tI++)
		{
			if(tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pChars__delimiter)  + tI)] > (pSize - tI - 1))
				{tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pChars__delimiter)  + tI)] = pSize - tI - 1;}
		}
		CRX_ENDFOR

		while(tChar < tEndChar)
		{
			tChar = memchr(tChar, *pChars__delimiter, tEndChar - tChar);

			if(tChar != NULL)
			{
				while((tChar < tEndChar) && (*(tChar + pSize - 1) != tLastCharacter))
				{
					tChar = tChar + 
							tReverseIndexOfCharacterLastOccurance[*(tChar + pSize - 1)];
				}

				if(tChar < tEndChar)
				{
					if(memcmp(tChar, pChars__delimiter, pSize) == 0)
					{
						vReturn = ((char const *)tChar) - vChars;

						break;
					}
					else
						{tChar++;}
				}
				else
					{break;}
			}
			else
				{break;}
		}
	}
#if(0)
	else if(vAlgorithm == 5)
	{
		//THIS DID NOT PROVE USEFUL AGAINST ALGORITHM 1, EVEN IF DELIMITER IS VERY
		//		SHORT SUCH AS 1 CHARACTER
		CRX_FOR(size_t tI = 0, tI <= vLength - pSize, tI++)
		{
			bool tIsFound = true;

			CRX_FOR(size_t tI2 = 0, tI2 < pSize, tI2++)
			{
				if(*(vChars + tI + tI2) != *(pChars__delimiter + tI2))
				{
					tIsFound = false;
					break;
				}
			}
			CRX_ENDFOR
					
			if(tIsFound)
			{
				vReturn = tI;
				break;
			}
		}
		CRX_ENDFOR
	}
	else if(vAlgorithm == 6)
	{
		/*TWO WAY SEARCH ALGORITHM IMPLEMENTATION FROM "Two Way algorithm.mht" 
				"http://igm.univ-mlv.fr/~lecroq/string/node26.html" THAT I
				USED FOR COMPARISON WITH THE ALGORITHM THAT I WROTE PER THE ORIGINAL PAPER*/
		vReturn = TW(pChars__delimiter, pSize, vChars, vLength);
		
		if(vReturn == vLength)
			{vReturn = vFullLength;}
	}
	else if(vAlgorithm == 7)
	{
		/*
		TWO WAY SEARCH ALGORITHM. SEE PAPER "CP-1991-jacm". THE LETTERS IN COMMENT IS TO HELP 
		COMPARE CODE TO ALOGIRHTMS IN THE PAPER. 
		*/
		size_t tCriticalPosition = 0; 	//ONE BASED INDEX
		size_t tI = 0; 					//ONE BASED INDEX
		size_t tI2 = 1;					//ONE BASED INDEX
		size_t tOffset = 1;
		size_t tDeltaTi = 1;
		size_t tPotentialPeriod = 0;

		
		//BASED ON MAXIMAL-SUFFIX() FUNCTION IN THE PAPER
		//tI   //i
		//tI2  //j
		//tOffset //k
		//tDeltaTi //p
		//pSize //n
		while(tI2 + tOffset <= pSize)
		{
			char tChar = *(pChars__delimiter + tI + tOffset - 1);
			char tChar2 = *(pChars__delimiter + tI2 + tOffset - 1);

			if(tChar > tChar2)
			{
				tI2 = tI2 + tOffset;
				tOffset = 1;
				tDeltaTi = tI2 - tI;
			}
			else if(tChar == tChar2)
			{
				if(tOffset == tDeltaTi)
				{
					tI2 = tI2 + tDeltaTi;
					tOffset = 1;
				}
				else
					{tOffset = tOffset + 1;}
			}
			else //(tChar < tChar2)
			{
				tI = tI2;
				tI2 = tI + 1;
				tOffset = 1;
				tDeltaTi = 1;
			}
		}

		//BASED ON SMALL-PERIOD() FUNCTION IN THE PAPER. THIS APPLIES ONLY TO THE NEXT
		//		TWO ASSIGNMENT STATEMENTS.
		tCriticalPosition = tI; //Alphabatical Maximal Suffix
		tPotentialPeriod = tDeltaTi;

		//BASED ON MAXIMAL-SUFFIX() FUNCTION IN THE PAPER
		tI = 0;   //i
		tI2 = 1;  //j
		tOffset = 1;  //k
		tDeltaTi = 1; //p
		//pSize //n

		while(tI2 + tOffset <= pSize)
		{
			char tChar = *(pChars__delimiter + tI + tOffset - 1);
			char tChar2 = *(pChars__delimiter + tI2 + tOffset - 1);

			if(tChar < tChar2)
			{
				tI2 = tI2 + tOffset;
				tOffset = 1;
				tDeltaTi = tI2 - tI;
			}
			else if(tChar == tChar2)
			{
				if(tOffset == tDeltaTi)
				{
					tI2 = tI2 + tDeltaTi;
					tOffset = 1;
				}
				else
					{tOffset = tOffset + 1;}
			}
			else //(tChar > tChar2)
			{
				tI = tI2;
				tI2 = tI + 1;
				tOffset = 1;
				tDeltaTi = 1;
			}
		}

		//BASED ON SMALL-PERIOD() FUNCTION IN THE PAPER. NOTE HOWEVER, THE NEXT
		//		IF STATEMENT MINGLES THE POSITIONS() FUNCTION IN ITS BRANCHES.
		//		ONE CAN COMPARE THE FINAL RESULT TO THE MATCH() FUNCTION IN THE PAPER.
		//		THE SECOND BRANCH OF THE SAID IF STATEMENT CAN ALSO BE COMPARED TO
		//		THE POSITIONS-BIS() FUNCION IN THE PAPER.
		if(tCriticalPosition < tI)
		{
			tCriticalPosition = tI; //Reverse Alphabatical Maximal Suffix
			tPotentialPeriod = tDeltaTi; 
		}
		
		if((tCriticalPosition < (pSize >> 1)) && 
				(memcmp(pChars__delimiter, pChars__delimiter + tPotentialPeriod, tCriticalPosition) == 0))
		{
			//BASED ON POSITIONS() FUNCTION IN THE PAPER.
			size_t tPeriod = tPotentialPeriod; //p
			size_t tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;//s
			
			tI2 = 0;//pos
			//tI //i
			//tCriticalPosition //l
			//vLength //|t|
			//pSize //|x|
			
			while(tI2 + pSize <= vLength)
			{
				//assert(pChars__delimiter[1 : tUpperBoundOfAlreadyVerifiedValuesOnRight] = 
				//		vChars[tI2 + 1 : tI2 + tUpperBoundOfAlreadyVerifiedValuesOnRight]) //right side is exclusive.

				tI = ((tCriticalPosition < tUpperBoundOfAlreadyVerifiedValuesOnRight) ? 
						tUpperBoundOfAlreadyVerifiedValuesOnRight : tCriticalPosition) + 1;
				
				while((tI <= pSize) && (*(pChars__delimiter + tI - 1) == *(vChars + tI2 + tI - 1)))
					{tI++;}

				if(tI <= pSize)
				{
					if((tUpperBoundOfAlreadyVerifiedValuesOnRight > tPeriod) &&
							((tUpperBoundOfAlreadyVerifiedValuesOnRight - tPeriod + 1) > 
							(tI - tCriticalPosition)))
						{tI2 = tI2 + tUpperBoundOfAlreadyVerifiedValuesOnRight - tPeriod + 1;}
					else
						{tI2 = tI2 + tI - tCriticalPosition;}

					tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;
				}
				else
				{
					size_t tJ = tCriticalPosition;	//ONE BASED INDEX

					//NO NEED TO SEARCH BEFORE tUpperBoundOfAlreadyVerifiedValuesOnRight. SEE ASSERT ABOVE
					while((tJ > tUpperBoundOfAlreadyVerifiedValuesOnRight) && 
							(*(pChars__delimiter + tJ - 1) == *(vChars + tI2 + tJ - 1)))
						{tJ = tJ - 1;}

					if(tJ <= tUpperBoundOfAlreadyVerifiedValuesOnRight)
					{
						vReturn = tI2;
						break;
					}
					else 	//IF YOU REMOVE THE break ABOVE, MEANING YOU WANT TO FIND ALL OCCURANCES,
							//	THE FOLLOWING CODE MUST ALWAYS RUN. IN THAT CASE, IF YOU WANT TO FIND
							//	NON OVERLAPPING OCCURANCES AND A MATCH IS FOUND, YOU WOULD INCRMENT 
							//	BY pSize INSTEAD OF tPeriod AND SET tUpperBoundOfAlreadyVerifiedValuesOnRight
							//	TO ZERO, OTHERWISE BY tPeriod AND SET tUpperBoundOfAlreadyVerifiedValuesOnRight
							//	TO pSize - tPeriod, OR IF YOU DO WANT TO FIND OVERLAPPING OCCURANCES, 
							//	YOU WOULD ALWAYS INCREMENT BY tPeriod AND SET 
							//	tUpperBoundOfAlreadyVerifiedValuesOnRight TO pSize - tPeriod
					{
						tI2 = tI2 + tPeriod;
						tUpperBoundOfAlreadyVerifiedValuesOnRight = pSize - tPeriod;
					}
				}
			}
		}
		else
		{
			//BASED ON POSITIONS() FUNCTION IN THE PAPER.
			/*
			SAME AS ABOVE, BUT THE VALUE OF tUpperBoundOfAlreadyVerifiedValuesOnRight IS SUCH AS ALL CONDITIONS
			AROUND IT EVALUATE TO FALSE, AND THE VALUE IS EFFECTIVELY 0.
			*/
			size_t tPeriodLowerBound = ((tCriticalPosition >= pSize - tCriticalPosition) ?
					tCriticalPosition : pSize - tCriticalPosition) + 1; //p OR q IN THE FINAL FORM
			
			tI2 = 0;//pos
			//tI //i
			//tCriticalPosition //l
			//vLength //|t|
			//pSize //|x|

			while(tI2 + pSize <= vLength)
			{
				tI = tCriticalPosition + 1;
				
				while((tI <= pSize) && (*(pChars__delimiter + tI - 1) == *(vChars + tI2 + tI - 1)))
					{tI++;}

				if(tI <= pSize)
					{tI2 = tI2 + tI - tCriticalPosition;}
				else
				{
					size_t tJ = tCriticalPosition; //ONE BASED INDEX

					while((tJ > 0) && (*(pChars__delimiter + tJ - 1) == *(vChars + tI2 + tJ - 1)))
						{tJ = tJ - 1;}

					if(tJ == 0)
					{
						vReturn = tI2;
						break;
					}
					else 	//IF YOU REMOVE THE break ABOVE, MEANING YOU WANT TO FIND ALL OCCURANCES,
							//	THE FOLLOWING CODE MUST ALWAYS RUN. IN THAT CASE, IF YOU WANT TO FIND
							//	NON OVERLAPPING OCCURANCES AND A MATCH IS FOUND, YOU WOULD INCRMENT 
							//	BY pSize INSTEAD OF tPeriodLowerBound, OTHERWISE BY tPeriodLowerBound,
							//	OR IF YOU DO WANT TO FIND OVERLAPPING OCCURANCES, YOU WOULD ALWAYS INCREMENT
							//	BY tPeriodLowerBound
						{tI2 = tI2 + tPeriodLowerBound;}
				}
			}
		}
	}
	else
		{assert(false);}
#endif
    
	return ((vReturn != vFullLength) ? (vReturn + pStartIndex) : ((size_t)(-1)));
	CRX_SCOPE_END
#endif
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstOccuranceOf4(
		Crx_C_String const * pThis, size_t pStartIndex, 
		Crx_C_String_Sub const * pSub__delimiter, 
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	if(crx_c_string_sub_getLength(pSub__delimiter) == 0)
		{return ((size_t)(-1));}

	return crx_c_string_getIndexOfFirstOccuranceOf3(pThis, pStartIndex,
			crx_c_string_sub_getCharsPointer(pSub__delimiter),
			crx_c_string_sub_getLength(pSub__delimiter),
			pSizeOfCharacterSet);
}


CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstReverseOccuranceOf(
		Crx_C_String const * pThis, size_t pInclusiveEndIndex, Crx_C_String const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_getIndexOfFirstReverseOccuranceOf3(pThis, pInclusiveEndIndex,
			crx_c_string_classProtected_constantGetElementsPointer(pDelimiter),
			crx_c_string_classProtected_getLength(pDelimiter),
			pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstReverseOccuranceOf2(
		Crx_C_String const * pThis, size_t pInclusiveEndIndex, char const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_getIndexOfFirstReverseOccuranceOf3(pThis, pInclusiveEndIndex,
			pDelimiter, strlen(pDelimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstReverseOccuranceOf3(
		Crx_C_String const * pThis, size_t pInclusiveEndIndex, char const * pChars__delimiter, 
		size_t pSize, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	/*
	IMPORTANT: TO AVOID CONFUSION, UNDERSTAND THAT ALGORITHM 8 UNLIKE THE OTHER ALGORITHMS, 
			IS A REVERSE SEARCH ALGORITHM, AND NOT A SEARCH SUCH AS BOTH STRINGS ARE EFFECTIVELY 
			COPIED IN REVERSE BEFORE SEARCHING. IN OTHER WORDS, THE OTHER ALGORITHMS BELOW 
			TRANSFORM THE INDICES AT THE VERY END BEFORE ACCESSING THE STRINGS. THESE ALGORITHMS 
			ARE NOT AWARE OF A REVERSE SEARCH. ALGORITHM 8, HOWEVER, DOES NO SUCH TRANSFORMATION. 
			ALGORITHM 8 IS AWARE OF A REVERSE SEARCH.
			THINGS WERE DONE THIS WAY FOR THE REVERSE OCCURANCE SEARCH ALGORITHMS BELOW, OTHER THAN 
			ALGORITHM 8, TO KEEP THEIR SYMMETRY WITH THE OCCURANCE SEARCH ALGORITHMS ELSEWHERE.
	*/
	CRX_SCOPE_META
	if((pInclusiveEndIndex < pSize - 1) || 
			(pInclusiveEndIndex >= crx_c_string_classProtected_getLength(pThis)) || (pSize == 0))
		{return ((size_t)(-1));}

	CRX_SCOPE
	uint32_t vAlgorithm = 0;
	uint8_t vSizeOfCharacterSet = ((pSizeOfCharacterSet == 0) ? 255 : pSizeOfCharacterSet);
	size_t vFullLength = crx_c_string_classProtected_getLength(pThis);
	size_t vLength = pInclusiveEndIndex + 1;
	char const * vChars = crx_c_string_classProtected_constantGetElementsPointer(pThis);
	size_t vReturn = ((size_t)(-1));
	

	/*
	NOTE: CURRENTLY, THE FOLLOWING IS PER THE ASSUMPTION THAT THE USER IS USING THE FUNCTION TO FIND
			THE FIRST OCCURANCE ONLY
	*/
	/*if(pSize < 5)
		{vAlgorithm = 1;}
	else
	{
		double tSizeOfCharacterSet = ((double)pSizeOfCharacterSet);
		double s2 = (tSizeOfCharacterSet * (1.0 - pow(1.0 - (1.0/tSizeOfCharacterSet), pSize)));//EXPECTED DISTINCT CHARACTERS IN DELIMITER
		double q = 0.4;
		double e = 1.0 / (((1.0 - q) / tSizeOfCharacterSet) + (q / s2));
		
		/*if(e > pSize)
			//{e = pSize;}* /
		
		/*if((pSize < 4) || (pSize * (vLength - pSize) <= 80000 * (1.0 - (1.0/vSizeOfCharacterSet))))* /
		//if(e <= 7)
		//	{vAlgorithm = 7/*6* /;}
		if(e <= 22)
			{vAlgorithm = 4;}
		else if(e <= 40)
			{vAlgorithm = 1;}
		else if(pSize < 7340032)
		{
			/*if(pSize < 16)
				{vAlgorithm = 2;}			
			else
				{vAlgorithm = 3;}* /

			vAlgorithm = 3;
		}
		else
			{vAlgorithm = 4;}
	}
	if(pSize < 5)
		{vAlgorithm = 1;}
	else
	{
		vAlgorithm = 4;
	}*/
	
	//THE FOLLOWING WAS PER THE BENCHMARKS. NOTE THIS SHOULD BE ASSUMED VALID ONLY FOR
	//		FARWARD FIRST OCCURANCE SEARCH.
	//		(THE FOLLOWING WAS ORIGINALLY MODIFIED TO USE '8' FOR ALL BRANCHES, WHICH I ASSUME MEANS 
	//				THAT I TESTED ALGORITHM 8, AND SETTLED ON 3 INSTEAD)
	/*if(pSize <= 8)
		{vAlgorithm = 1;}
	else if(pSize < 32768)
	{
		if(vSizeOfCharacterSet > 16)
			{vAlgorithm = 4;}
		else
			{vAlgorithm = 1;}
	}
	else
		{vAlgorithm = 4;}*/
	
	vAlgorithm = 3;
	
	if(vAlgorithm <= 3)
	{
		/*
		KMP ALOGIRTHM

		NOTE: GIVEN A STRING[1..N], THE Nth SUFFIX PREFIX IS THE Nth LARGEST PREFIX OF THE STRING
				THAT IS ALSO ITS SUFFIX. THE LARGEST SUFFIX PREFIX IS THE STRING ITSELF. IN OTHER
				WORDS:
						SUFFIX_PREFIX{n}(STRING) = STRING[N-K+1..N] = STRING[1..K]  ; K IS THE LENGTH OF
								THE nth LARGEST SUFFIX PREFIX.
				NOTE THAT THE LENGTH OF STRING[X..Y] IS Y - X + 1. IN OTHER WORDS
								|STRING[N-K+1..N]| = K
				
				WE ARE FOR THE ALGOIRTHM ONLY INTERESTED IN THE SECOND LARGEST SUFFIX PREFIX.
				
				NOTE THAT IF FOR SUBSTRING STRING[A..B], 
						|SUFFIX_PREFIX{2}(STRING[A..B])| = K, 
				THEN FOR SUBSTRING STRING[A..B+1] 
						|SUFFIX_PREFIX{2}(STRING[A..B+1])| <= K + 1
				BECAUSE OTHERWISE THIS SUFFIX PREFIX WOULD END AT (A + K + L) FOR L > 0, MAKING IT A 
				CONTRADITCTION BECUASE THEN K WOULD NOT HAVE BEEN THE LENGTH OF THE SECOND LARGEST 
				SUFFIX PREFIX OF STRING[A..B].

				*NOTE THAT THE THIRD LARGEST SUFFIX PREFIX OF STRING[1..N], MEANING
						SUFFIX_PREFIX{3}(STRING[1..N])
				WOULD BE A SUBSTRING AND A SUFFIX PREFIX OF STRING[N-K+1..N], THE SECOND LARGEST 
				SUFFIX PREFIX, MEANING A SUBTRING OF
						SUFFIX_PREFIX{2}(STRING[1..N]) = STRING[N-K+1..N]
				AND BECAUSE STRING[N-K+1..N] IS EQUAL TO STRING[1..K], IT FOLLOWS THAT THIS THIRD 
				LARGEST SUFFIX PREFIX IS ALSO THE SECOND LARGEST SUFFIX PREFIX OF STRING[1..K]. IN OTHER
				WORDS
						SUFFIX_PREFIX{3}(STRING[1..N]) = SUFFIX_PREFIX{2}(SUFFIX_PREFIX{2}(STRING[1..N]))
													   = SUFFIX_PREFIX{2}(STRING[N-K+1..N])
													   = SUFFIX_PREFIX{2}(STRING[1..K])
				IF THIS WAS NOT THE CASE IT WOULD BE A CONTRADICTION. FOR EXAMPLE, IF THE LENGTH OF THE 
				THIRD LARGEST SUFFIX PREFIX OF STRING[1..N] IS L, THEN WE KNOW L < K AND WE KNOW THAT 
				THERE CAN BE NO OTHER SUFFIX PREFIX WHOSE LENGTH Y IS L < Y < K, AND NOW IF THIS SUFFIX 
				PREFIX IS NOT THE SECOND LARGEST SUFFIX PREFIX OF STRING[1..K], SUCH AS IT IS THE THIRD 
				LARGEST FOR EXAMPLE, THEN THERE EXISTS A SUFFIX PREFIX FOR STRING[1..K] WHOSE LENGTH 
				M > L. HOWEVER THIS SUFFIX PREFIX WOULD BE A SUFFIX PREFIX OF STRING[1..N], YET ITS 
				LENGTH M > L WHILE NOT BEING M = K, MEANING L < M < K WHICH IS A CONTRADICTION.
		*/
		size_t tCurrentIndexInDelimiter = 0;
		size_t * tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = NULL;
		bool tIsToFree = false;
		
		if(pSize + 1 > 80)
		{
			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
					calloc(1, sizeof(size_t) * (pSize + 1));
			tIsToFree = true;
		}
		else
		{
			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
					CRX__ALLOCA(sizeof(size_t) * (pSize + 1));
		}
		
		tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[0] = 0;
		CRX_FOR(size_t tI = 1, tI < pSize, tI++)
		{        
			size_t tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[pSize - 1 - (tI - 1)];

			//IF SECOND LARGEST SUFFIX PREFIX DOES NOT HELP, WE SEEK OUT THE THIRD LARGEST
			//		SUFFIX PREFIX WHICH HAPPENS TO BE THE SECOND LARGEST SUFFIX PREFIX OF THE
			//		SECOND LARGEST SUFFIX PREFIX. AND SO FORTH.
			while((tJ != 0) && (*(pChars__delimiter + pSize - 1 - tI) != *(pChars__delimiter + pSize - 1 - tJ)))
				{tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tJ - 1];}

			if(*(pChars__delimiter + pSize - 1 - tI) == *(pChars__delimiter + pSize - 1 - tJ))
				{tJ += 1;}

			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tI] = tJ;
		}
		CRX_ENDFOR

		if(vAlgorithm == 2)
		{
			//NOTE: THIS ALGORITHM DOES NOT EXIT EARLY.

			CRX_FOR(size_t tI = 0, tI < vLength, tI++)
			{
				while((tCurrentIndexInDelimiter != 0) && 
						(*(vChars + vLength - 1 - tI) != *(pChars__delimiter + pSize - 1 - tCurrentIndexInDelimiter)))
				{
					//SEE * ABOVE.
					tCurrentIndexInDelimiter = 
							tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
							tCurrentIndexInDelimiter - 1];
				}
				
				if(*(vChars + vLength - 1 - tI) == *(pChars__delimiter + pSize - 1 - tCurrentIndexInDelimiter))
					{tCurrentIndexInDelimiter += 1;}

				/*
					AT THIS POINT, THE FOLLOWING MUST ALWAYS HOLD TRUE
							vChars[tI + 1 - tCurrentIndexInDelimiter:tI + 1] == 
									pChars__delimiter[0:tCurrentIndexInDelimiter]
					IN OTHER WORDS, THE WINDOW, pChars__delimiter[0:tCurrentIndexInDelimiter], IS ALWAYS VALID, 
					ALWAYS EQUAL TO THE OVERLAP EVEN AFTER SHIFTING.
				*/

				if(tCurrentIndexInDelimiter == pSize)
				{
					vReturn = vLength - 1 - tI;//== vLength - 1 - (tI + 1 - pSize) - (pSize - 1)

					break;
				}
			}
			CRX_ENDFOR
		}
		else
		{
			//NOTE: THIS ALGORITHM DOES NOT EXIT EARLY, BUT IS SAFE.
			//OLD NOTE: WHEN THE CHARACTER SET IS VERY SMALL, THIS IS THE FASTEST, BUT STILL TWICE 
			//		AS SLOW	FOR RANDOM INPUT, AND MORE SLOW FOR HIGHLY PATTERNED INTPUT UP TO THREE 
			//		TIMES AS SLOW
			uint32_t tReverseIndexOfCharacterLastOccurance[256] /*= ?*/;
			char tLastCharacter = *pChars__delimiter;
			
			CRX_FOR(size_t tI = 0, tI < 256, tI++)
				{tReverseIndexOfCharacterLastOccurance[tI] = (uint32_t)pSize;}
			CRX_ENDFOR

			CRX_FOR(size_t tI = 0, tI < pSize, tI++)
			{
				if(tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pChars__delimiter) + pSize - 1 - tI)] > (pSize - tI - 1))
					{tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pChars__delimiter) + pSize - 1 - tI)] = pSize - tI - 1;}
			}
			CRX_ENDFOR
			
			CRX_FOR(size_t tI = 0, tI < vLength, tI++)
			{
				if(tCurrentIndexInDelimiter == 0)
				{
					while((tI <= vLength - pSize) && (*(vChars + vLength - 1 - (tI + pSize - 1)) != tLastCharacter))
						{tI = tI + tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)vChars) + vLength - 1 - (tI + pSize - 1))];}
				}
				else
				{
					while((tCurrentIndexInDelimiter != 0) && 
							(*(vChars + vLength - 1 - tI) != *(pChars__delimiter + pSize - 1 - tCurrentIndexInDelimiter)))
					{
						//SEE * ABOVE.
						tCurrentIndexInDelimiter = 
								tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
								tCurrentIndexInDelimiter - 1];
					}
				}


				if(*(vChars + vLength - 1 - tI) == *(pChars__delimiter + pSize - 1 - tCurrentIndexInDelimiter))
					{tCurrentIndexInDelimiter += 1;}

				/*SEE ABOVE*/
				if(tCurrentIndexInDelimiter == pSize)
				{
					vReturn = vLength - 1 - tI; //vLength - 1 - (tI + 1 - pSize) - (pSize - 1)

					break;
				}
			}
			CRX_ENDFOR
		}

		if(tIsToFree)
		{
			free(tSecondLargestSuffixPrefixForSubDelimiterUpToIndex);
			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = NULL;
		}
	}
	else if(vAlgorithm == 5)
	{
		CRX_FOR(size_t tI = 0, tI <= vLength - pSize, tI++)
		{
			bool tIsFound = true;

			CRX_FOR(size_t tI2 = 0, tI2 < pSize, tI2++)
			{
				if(*(vChars + vLength - 1 - tI - tI2) != *(pChars__delimiter + pSize - 1 - tI2))
				{
					tIsFound = false;
					break;
				}
			}
			CRX_ENDFOR
					
			if(tIsFound)
			{
				vReturn = vLength - tI - pSize;//vLength - 1 - tI - (pSize - 1)
				break;
			}
		}
		CRX_ENDFOR
	}
	else if(vAlgorithm == 7)
	{
		/*
		TWO WAY SEARCH ALGORITHM. SEE PAPER "CP-1991-jacm". THE LETTERS IN COMMENT IS TO HELP 
		COMPARE CODE TO ALOGIRHTMS IN THE PAPER. 
		*/
		size_t tCriticalPosition = 0; 	//ONE BASED INDEX
		size_t tI = 0; 					//ONE BASED INDEX
		size_t tI2 = 1;					//ONE BASED INDEX
		size_t tOffset = 1;
		size_t tDeltaTi = 1;
		size_t tPotentialPeriod = 0;

		
		//BASED ON MAXIMAL-SUFFIX() FUNCTION IN THE PAPER
		//tI   //i
		//tI2  //j
		//tOffset //k
		//tDeltaTi //p
		//pSize //n
		while(tI2 + tOffset <= pSize)
		{
			char tChar = *(pChars__delimiter + pSize - 1 - (tI + tOffset - 1));
			char tChar2 = *(pChars__delimiter + pSize - 1 - (tI2 + tOffset - 1));

			if(tChar > tChar2)
			{
				tI2 = tI2 + tOffset;
				tOffset = 1;
				tDeltaTi = tI2 - tI;
			}
			else if(tChar == tChar2)
			{
				if(tOffset == tDeltaTi)
				{
					tI2 = tI2 + tDeltaTi;
					tOffset = 1;
				}
				else
					{tOffset = tOffset + 1;}
			}
			else //(tChar < tChar2)
			{
				tI = tI2;
				tI2 = tI + 1;
				tOffset = 1;
				tDeltaTi = 1;
			}
		}

		//BASED ON SMALL-PERIOD() FUNCTION IN THE PAPER. THIS APPLIES ONLY TO THE NEXT
		//		TWO ASSIGNMENT STATEMENTS.
		tCriticalPosition = tI; //Alphabatical Maximal Suffix
		tPotentialPeriod = tDeltaTi;

		//BASED ON MAXIMAL-SUFFIX() FUNCTION IN THE PAPER
		tI = 0;   //i
		tI2 = 1;  //j
		tOffset = 1;  //k
		tDeltaTi = 1; //p
		//pSize //n

		while(tI2 + tOffset <= pSize)
		{
			char tChar = *(pChars__delimiter + pSize - 1 - (tI + tOffset - 1));
			char tChar2 = *(pChars__delimiter + pSize - 1 - (tI2 + tOffset - 1));

			if(tChar < tChar2)
			{
				tI2 = tI2 + tOffset;
				tOffset = 1;
				tDeltaTi = tI2 - tI;
			}
			else if(tChar == tChar2)
			{
				if(tOffset == tDeltaTi)
				{
					tI2 = tI2 + tDeltaTi;
					tOffset = 1;
				}
				else
					{tOffset = tOffset + 1;}
			}
			else //(tChar > tChar2)
			{
				tI = tI2;
				tI2 = tI + 1;
				tOffset = 1;
				tDeltaTi = 1;
			}
		}

		//BASED ON SMALL-PERIOD() FUNCTION IN THE PAPER. NOTE HOWEVER, THE NEXT
		//		IF STATEMENT MINGLES THE POSITIONS() FUNCTION IN ITS BRANCHES.
		//		ONE CAN COMPARE THE FINAL RESULT TO THE MATCH() FUNCTION IN THE PAPER.
		//		THE SECOND BRANCH OF THE SAID IF STATEMENT CAN ALSO BE COMPARED TO
		//		THE POSITIONS-BIS() FUNCION IN THE PAPER.
		if(tCriticalPosition < tI)
		{
			tCriticalPosition = tI; //Reverse Alphabatical Maximal Suffix
			tPotentialPeriod = tDeltaTi; 
		}
		
		if((tCriticalPosition < (pSize >> 1)) && 
				(memcmp(pChars__delimiter + pSize - 1 - (tCriticalPosition - 1), pChars__delimiter + pSize - 1 - tPotentialPeriod - (tCriticalPosition - 1), tCriticalPosition) == 0))
		{
			//BASED ON POSITIONS() FUNCTION IN THE PAPER.
			size_t tPeriod = tPotentialPeriod; //p
			size_t tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;//s
			
			tI2 = 0;//pos
			//tI //i
			//tCriticalPosition //l
			//vLength //|t|
			//pSize //|x|
			
			while(tI2 + pSize <= vLength)
			{
				//assert(pChars__delimiter[1 : tUpperBoundOfAlreadyVerifiedValuesOnRight] = 
				//		vChars[tI2 + 1 : tI2 + tUpperBoundOfAlreadyVerifiedValuesOnRight]) //right side is exclusive.

				tI = ((tCriticalPosition < tUpperBoundOfAlreadyVerifiedValuesOnRight) ? 
						tUpperBoundOfAlreadyVerifiedValuesOnRight : tCriticalPosition) + 1;
				
				while((tI <= pSize) && (*(pChars__delimiter + pSize - 1 - (tI - 1)) == *(vChars + vLength - 1 - (tI2 + tI - 1))))
					{tI++;}

				if(tI <= pSize)
				{
					if((tUpperBoundOfAlreadyVerifiedValuesOnRight > tPeriod) &&
							((tUpperBoundOfAlreadyVerifiedValuesOnRight - tPeriod + 1) > 
							(tI - tCriticalPosition)))
						{tI2 = tI2 + tUpperBoundOfAlreadyVerifiedValuesOnRight - tPeriod + 1;}
					else
						{tI2 = tI2 + tI - tCriticalPosition;}

					tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;
				}
				else
				{
					size_t tJ = tCriticalPosition;	//ONE BASED INDEX

					//NO NEED TO SEARCH BEFORE tUpperBoundOfAlreadyVerifiedValuesOnRight. SEE ASSERT ABOVE
					while((tJ > tUpperBoundOfAlreadyVerifiedValuesOnRight) && 
							(*(pChars__delimiter + pSize - 1 - (tJ - 1)) == *(vChars + vLength - 1 - (tI2 + tJ - 1))))
						{tJ = tJ - 1;}

					if(tJ <= tUpperBoundOfAlreadyVerifiedValuesOnRight)
					{
						vReturn = vLength - 1 - tI2 - (pSize - 1);
						break;
					}
					else 	//IF YOU REMOVE THE break ABOVE, MEANING YOU WANT TO FIND ALL OCCURANCES,
							//	THE FOLLOWING CODE MUST ALWAYS RUN. IN THAT CASE, IF YOU WANT TO FIND
							//	NON OVERLAPPING OCCURANCES AND A MATCH IS FOUND, YOU WOULD INCRMENT 
							//	BY pSize INSTEAD OF tPeriod AND SET tUpperBoundOfAlreadyVerifiedValuesOnRight
							//	TO ZERO, OTHERWISE BY tPeriod AND SET tUpperBoundOfAlreadyVerifiedValuesOnRight
							//	TO pSize - tPeriod, OR IF YOU DO WANT TO FIND OVERLAPPING OCCURANCES, 
							//	YOU WOULD ALWAYS INCREMENT BY tPeriod AND SET 
							//	tUpperBoundOfAlreadyVerifiedValuesOnRight TO pSize - tPeriod
					{
						tI2 = tI2 + tPeriod;
						tUpperBoundOfAlreadyVerifiedValuesOnRight = pSize - tPeriod;
					}
				}
			}
		}
		else
		{
			//BASED ON POSITIONS() FUNCTION IN THE PAPER.
			/*
			SAME AS ABOVE, BUT THE VALUE OF tUpperBoundOfAlreadyVerifiedValuesOnRight IS SUCH AS ALL CONDITIONS
			AROUND IT EVALUATE TO FALSE, AND THE VALUE IS EFFECTIVELY 0.
			*/
			size_t tPeriodLowerBound = ((tCriticalPosition >= pSize - tCriticalPosition) ?
					tCriticalPosition : pSize - tCriticalPosition) + 1; //p OR q IN THE FINAL FORM
			
			tI2 = 0;//pos
			//tI //i
			//tCriticalPosition //l
			//vLength //|t|
			//pSize //|x|

			while(tI2 + pSize <= vLength)
			{
				tI = tCriticalPosition + 1;
				
				while((tI <= pSize) && (*(pChars__delimiter + pSize - 1 - (tI - 1)) == *(vChars + vLength - 1 - (tI2 + tI - 1))))
					{tI++;}

				if(tI <= pSize)
					{tI2 = tI2 + tI - tCriticalPosition;}
				else
				{
					size_t tJ = tCriticalPosition; //ONE BASED INDEX

					while((tJ > 0) && (*(pChars__delimiter + pSize - 1 - (tJ - 1)) == *(vChars + vLength - 1 - (tI2 + tJ - 1))))
						{tJ = tJ - 1;}

					if(tJ == 0)
					{
						vReturn = vLength - 1 - tI2 - (pSize - 1);
						break;
					}
					else 	//IF YOU REMOVE THE break ABOVE, MEANING YOU WANT TO FIND ALL OCCURANCES,
							//	THE FOLLOWING CODE MUST ALWAYS RUN. IN THAT CASE, IF YOU WANT TO FIND
							//	NON OVERLAPPING OCCURANCES AND A MATCH IS FOUND, YOU WOULD INCRMENT 
							//	BY pSize INSTEAD OF tPeriodLowerBound, OTHERWISE BY tPeriodLowerBound,
							//	OR IF YOU DO WANT TO FIND OVERLAPPING OCCURANCES, YOU WOULD ALWAYS INCREMENT
							//	BY tPeriodLowerBound
						{tI2 = tI2 + tPeriodLowerBound;}
				}
			}
		}
	}
	else if(vAlgorithm == 8)
	{
		unsigned char const * tChars = vChars;
		size_t tEndIndex = pSize - 1; //One based index
		unsigned char tFirstCharacter = *pChars__delimiter;
		unsigned char tLastCharacter = *(pChars__delimiter + pSize - 1);
		uint32_t tIndexOfCharacterFirstOccurance[256] /*= ?*/;
		size_t vI = vLength; //One based index

		CRX_FOR(size_t tI = 0, tI < 256, tI++)
			{tIndexOfCharacterFirstOccurance[tI] = (uint32_t)pSize;}
		CRX_ENDFOR
		
		CRX_FOR(size_t tI = 0, tI < pSize, tI++)
		{
			if(tIndexOfCharacterFirstOccurance[*(((unsigned char const *)pChars__delimiter)  + tI)] > tI)
				{tIndexOfCharacterFirstOccurance[*(((unsigned char const *)pChars__delimiter)  + tI)] = tI;}
		}
		CRX_ENDFOR

		while(vI > tEndIndex)
		{
			while((vI > tEndIndex) && (*(vChars + vI - 1) != tLastCharacter))
				{vI--;}

			if(vI > tEndIndex)
			{
				while((vI > tEndIndex) && (*(tChars + vI - pSize) != tFirstCharacter))
					{vI = vI - tIndexOfCharacterFirstOccurance[*(tChars + vI - pSize)];}

				if(vI > tEndIndex)
				{
					if(memcmp(tChars + vI - pSize, pChars__delimiter, pSize) == 0)
					{
						vReturn = vI - pSize;

						break;
					}
					else
						{vI--;}
				}
			}
		}
	}
	else
		{assert(false);}
    
	return vReturn;
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstReverseOccuranceOf4(
		Crx_C_String const * pThis, size_t pInclusiveEndIndex, 
		Crx_C_String_Sub const * pSub__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	if(crx_c_string_sub_getLength(pSub__delimiter) == 0)
		{return ((size_t)(-1));}

	return crx_c_string_getIndexOfFirstReverseOccuranceOf3(pThis, pInclusiveEndIndex,
			crx_c_string_sub_getCharsPointer(pSub__delimiter),
			crx_c_string_sub_getLength(pSub__delimiter),
			pSizeOfCharacterSet);
}


CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllOccurancesOf(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, Crx_C_String const * pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_computeIndicesOfAllOccurancesOf3(pThis, pReturn,
			pStartIndex, crx_c_string_classProtected_constantGetElementsPointer(pDelimiter),
			crx_c_string_classProtected_getLength(pDelimiter),
			pIsToAllowOverlap, pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllOccurancesOf2(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, char const * pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_computeIndicesOfAllOccurancesOf3(pThis, pReturn,
			pStartIndex, pDelimiter, strlen(pDelimiter),
			pIsToAllowOverlap, pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllOccurancesOf3(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, char const * pChars__delimiter, size_t pSize,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	uint8_t vSizeOfCharacterSet = ((pSizeOfCharacterSet == 0) ? 255 : pSizeOfCharacterSet);
	size_t vFullLength = crx_c_string_classProtected_getLength(pThis);
	bool vIsNoError = true;

	crx_c_arrays_size_empty(pReturn);

	if(!(((vFullLength - pStartIndex) < pSize) || 
			(vFullLength <= pStartIndex) || (pSize == 0)))
	{
		uint32_t tAlgorithm = 0;
		size_t tLength = vFullLength - pStartIndex;
		char const * tChars = crx_c_string_classProtected_constantGetElementsPointer(pThis) + 
				pStartIndex;

		/*if(pSize < 5)
			{tAlgorithm = 1;}
		else
		{
			double tSizeOfCharacterSet = ((double)pSizeOfCharacterSet);
			double s2 = (tSizeOfCharacterSet * (1.0 - pow(1.0 - (1.0/tSizeOfCharacterSet), pSize)));//EXPECTED DISTINCT CHARACTERS IN DELIMITER
			double q = 0.4;
			double e = 1.0 / (((1.0 - q) / tSizeOfCharacterSet) + (q / s2));
			
			/*if(e > pSize)
				//{e = pSize;}* /
			
			/*if((pSize < 4) || (pSize * (tLength - pSize) <= 80000 * (1.0 - (1.0/vSizeOfCharacterSet))))* /
			//if(e <= 7)
			//	{tAlgorithm = 7/*6* /;}
			if(e <= 22)
				{tAlgorithm = 4;}
			else if(e <= 40)
				{tAlgorithm = 1;}
			else if(pSize < 7340032)
			{
				/*if(pSize < 16)
					{tAlgorithm = 2;}			
				else
					{tAlgorithm = 3;}* /

				tAlgorithm = 3;
			}
			else
				{tAlgorithm = 4;}
		}
		if(pSize < 5)
			{tAlgorithm = 1;}
		else
		{
			tAlgorithm = 4;
		}*/
		
		tAlgorithm = 4;
		
		if(tAlgorithm == 1)
		{
			char const * tChar = tChars;
			char const * tEndChar = tChars + (tLength - pSize + 1);

			while(tChar < tEndChar)
			{
				tChar = memchr(tChar, *pChars__delimiter, tEndChar - tChar);

				if(tChar != NULL)
				{
					if(memcmp(tChar, pChars__delimiter, pSize) == 0)
					{
						if(crx_c_arrays_size_push2(pReturn, tChar - tChars))
						{
							if(!pIsToAllowOverlap)
								{tChar = tChar + pSize;}
							else
								{tChar++;}
						}
						else
						{
							vIsNoError = false;
							break;
						}
					}
					else
						{tChar++;}
				}
				else
					{break;}
			}
		}
		else if(tAlgorithm <= 3)
		{
			/*
			KMP ALOGIRTHM

			NOTE: GIVEN A STRING[1..N], THE Nth SUFFIX PREFIX IS THE Nth LARGEST PREFIX OF THE STRING
					THAT IS ALSO ITS SUFFIX. THE LARGEST SUFFIX PREFIX IS THE STRING ITSELF. IN OTHER
					WORDS:
							SUFFIX_PREFIX{n}(STRING) = STRING[N-K+1..N] = STRING[1..K]  ; K IS THE LENGTH OF
									THE nth LARGEST SUFFIX PREFIX.
					NOTE THAT THE LENGTH OF STRING[X..Y] IS Y - X + 1. IN OTHER WORDS
									|STRING[N-K+1..N]| = K
					
					WE ARE FOR THE ALGOIRTHM ONLY INTERESTED IN THE SECOND LARGEST SUFFIX PREFIX.
					
					NOTE THAT IF FOR SUBSTRING STRING[A..B], 
							|SUFFIX_PREFIX{2}(STRING[A..B])| = K, 
					THEN FOR SUBSTRING STRING[A..B+1] 
							|SUFFIX_PREFIX{2}(STRING[A..B+1])| <= K + 1
					BECAUSE OTHERWISE THIS SUFFIX PREFIX WOULD END AT (A + K + L) FOR L > 0, MAKING IT A 
					CONTRADITCTION BECUASE THEN K WOULD NOT HAVE BEEN THE LENGTH OF THE SECOND LARGEST 
					SUFFIX PREFIX OF STRING[A..B].

					*NOTE THAT THE THIRD LARGEST SUFFIX PREFIX OF STRING[1..N], MEANING
							SUFFIX_PREFIX{3}(STRING[1..N])
					WOULD BE A SUBSTRING AND A SUFFIX PREFIX OF STRING[N-K+1..N], THE SECOND LARGEST 
					SUFFIX PREFIX, MEANING A SUBTRING OF
							SUFFIX_PREFIX{2}(STRING[1..N]) = STRING[N-K+1..N]
					AND BECAUSE STRING[N-K+1..N] IS EQUAL TO STRING[1..K], IT FOLLOWS THAT THIS THIRD 
					LARGEST SUFFIX PREFIX IS ALSO THE SECOND LARGEST SUFFIX PREFIX OF STRING[1..K]. IN OTHER
					WORDS
							SUFFIX_PREFIX{3}(STRING[1..N]) = SUFFIX_PREFIX{2}(SUFFIX_PREFIX{2}(STRING[1..N]))
														   = SUFFIX_PREFIX{2}(STRING[N-K+1..N])
														   = SUFFIX_PREFIX{2}(STRING[1..K])
					IF THIS WAS NOT THE CASE IT WOULD BE A CONTRADICTION. FOR EXAMPLE, IF THE LENGTH OF THE 
					THIRD LARGEST SUFFIX PREFIX OF STRING[1..N] IS L, THEN WE KNOW L < K AND WE KNOW THAT 
					THERE CAN BE NO OTHER SUFFIX PREFIX WHOSE LENGTH Y IS L < Y < K, AND NOW IF THIS SUFFIX 
					PREFIX IS NOT THE SECOND LARGEST SUFFIX PREFIX OF STRING[1..K], SUCH AS IT IS THE THIRD 
					LARGEST FOR EXAMPLE, THEN THERE EXISTS A SUFFIX PREFIX FOR STRING[1..K] WHOSE LENGTH 
					M > L. HOWEVER THIS SUFFIX PREFIX WOULD BE A SUFFIX PREFIX OF STRING[1..N], YET ITS 
					LENGTH M > L WHILE NOT BEING M = K, MEANING L < M < K WHICH IS A CONTRADICTION.
			*/
			size_t tCurrentIndexInDelimiter = 0;
			size_t * tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = NULL;
			bool tIsToFree = false;
			
			if(pSize + 1 > 80)
			{
				tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
						calloc(1, sizeof(size_t) * (pSize + 1));
				tIsToFree = true;
			}
			else
			{
				tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
						CRX__ALLOCA(sizeof(size_t) * (pSize + 1));
			}
			
			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[0] = 0;
			CRX_FOR(size_t tI = 1, tI < pSize, tI++)
			{        
				size_t tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tI - 1];

				//IF SECOND LARGEST SUFFIX PREFIX DOES NOT HELP, WE SEEK OUT THE THIRD LARGEST
				//		SUFFIX PREFIX WHICH HAPPENS TO BE THE SECOND LARGEST SUFFIX PREFIX OF THE
				//		SECOND LARGEST SUFFIX PREFIX. AND SO FORTH.
				while((tJ != 0) && (*(pChars__delimiter + tI) != *(pChars__delimiter + tJ)))
					{tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tJ - 1];}

				if(*(pChars__delimiter + tI) == *(pChars__delimiter + tJ))
					{tJ += 1;}

				tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tI] = tJ;
			}
			CRX_ENDFOR

			if(tAlgorithm == 2)
			{
				//NOTE: THIS ALGORITHM DOES NOT EXIT EARLY.

				CRX_FOR(size_t tI = 0, tI < tLength, tI++)
				{
					while((tCurrentIndexInDelimiter != 0) && 
							(*(tChars + tI) != *(pChars__delimiter + tCurrentIndexInDelimiter)))
					{
						//SEE * ABOVE.
						tCurrentIndexInDelimiter = 
								tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
								tCurrentIndexInDelimiter - 1];
					}
					
					if(*(tChars + tI) == *(pChars__delimiter + tCurrentIndexInDelimiter))
						{tCurrentIndexInDelimiter += 1;}

					/*
						AT THIS POINT, THE FOLLOWING MUST ALWAYS HOLD TRUE
								tChars[tI + 1 - tCurrentIndexInDelimiter:tI + 1] == 
										pChars__delimiter[0:tCurrentIndexInDelimiter]
						IN OTHER WORDS, THE WINDOW, pChars__delimiter[0:tCurrentIndexInDelimiter], IS ALWAYS VALID, 
						ALWAYS EQUAL TO THE OVERLAP EVEN AFTER SHIFTING.
					*/

					if(tCurrentIndexInDelimiter == pSize)
					{
						if(crx_c_arrays_size_push2(pReturn, tI + 1 - pSize))
						{
							if(pIsToAllowOverlap)
								{tI = tI + 1 - pSize;}

							tCurrentIndexInDelimiter = 0;
						}
						else
						{
							vIsNoError = false;
							break;
						}
					}
				}
				CRX_ENDFOR
			}
			else
			{
				//NOTE: THIS ALGORITHM DOES NOT EXIT EARLY, BUT IS SAFE.
				//OLD NOTE: WHEN THE CHARACTER SET IS VERY SMALL, THIS IS THE FASTEST, BUT STILL TWICE 
				//		AS SLOW	FOR RANDOM INPUT, AND MORE SLOW FOR HIGHLY PATTERNED INTPUT UP TO THREE 
				//		TIMES AS SLOW
				uint32_t tReverseIndexOfCharacterLastOccurance[256] /*= ?*/;
				char tLastCharacter = *(pChars__delimiter + pSize - 1);
				
				CRX_FOR(size_t tI = 0, tI < 256, tI++)
					{tReverseIndexOfCharacterLastOccurance[tI] = (uint32_t)pSize;}
				CRX_ENDFOR

				CRX_FOR(size_t tI = 0, tI < pSize, tI++)
				{
					if(tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pChars__delimiter)  + tI)] > (pSize - tI - 1))
						{tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pChars__delimiter)  + tI)] = pSize - tI - 1;}
				}
				CRX_ENDFOR
				
				CRX_FOR(size_t tI = 0, tI < tLength, tI++)
				{
					if(tCurrentIndexInDelimiter == 0)
					{
						while((tI <= tLength - pSize) && (*(tChars + tI + pSize - 1) != tLastCharacter))
							{tI = tI + tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)tChars) + tI + pSize - 1)];}
					}
					else
					{
						while((tCurrentIndexInDelimiter != 0) && 
								(*(tChars + tI) != *(pChars__delimiter + tCurrentIndexInDelimiter)))
						{
							//SEE * ABOVE.
							tCurrentIndexInDelimiter = 
									tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
									tCurrentIndexInDelimiter - 1];
						}
					}


					if(*(tChars + tI) == *(pChars__delimiter + tCurrentIndexInDelimiter))
						{tCurrentIndexInDelimiter += 1;}

					/*SEE ABOVE*/
					if(tCurrentIndexInDelimiter == pSize)
					{
						if(crx_c_arrays_size_push2(pReturn, tI + 1 - pSize))
						{
							if(pIsToAllowOverlap)
								{tI = tI + 1 - pSize;}

							tCurrentIndexInDelimiter = 0;
						}
						else
						{
							vIsNoError = false;
							break;
						}
					}
				}
				CRX_ENDFOR
			}

			if(tIsToFree)
			{
				free(tSecondLargestSuffixPrefixForSubDelimiterUpToIndex);
				tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = NULL;
			}
		}
		else if(tAlgorithm == 4)
		{
			//OLD NOTE: WHEN THE CHARACTER SET IS VERY SMALL, THIS IS THE SLOWEST
			unsigned char const * tChar = tChars;
			unsigned char const * tEndChar = tChars + (tLength - pSize) + 1;
			unsigned char tLastCharacter = *(pChars__delimiter + pSize - 1);
			uint32_t tReverseIndexOfCharacterLastOccurance[256] /*= ?*/;

			CRX_FOR(size_t tI = 0, tI < 256, tI++)
				{tReverseIndexOfCharacterLastOccurance[tI] = (uint32_t)pSize;}
			CRX_ENDFOR
			
			CRX_FOR(size_t tI = 0, tI < pSize, tI++)
			{
				if(tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pChars__delimiter)  + tI)] > (pSize - tI - 1))
					{tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pChars__delimiter)  + tI)] = pSize - tI - 1;}
			}
			CRX_ENDFOR

			while(tChar < tEndChar)
			{
				tChar = memchr(tChar, *pChars__delimiter, tEndChar - tChar);

				if(tChar != NULL)
				{
					while((tChar < tEndChar) && (*(tChar + pSize - 1) != tLastCharacter))
					{
						tChar = tChar + 
								tReverseIndexOfCharacterLastOccurance[*(tChar + pSize - 1)];
					}

					if(tChar < tEndChar)
					{
						if(memcmp(tChar, pChars__delimiter, pSize) == 0)
						{
							if(crx_c_arrays_size_push2(pReturn, ((char const *)tChar) - tChars))
							{
								if(!pIsToAllowOverlap)
									{tChar = tChar + pSize;}
								else
									{tChar++;}
							}
							else
							{
								vIsNoError = false;
								break;
							}
						}
						else
							{tChar++;}
					}
					else
						{break;}
				}
				else
					{break;}
			}
		}
		else if(tAlgorithm == 5)
		{
			//THIS DID NOT PROVE USEFUL AGAINST ALGORITHM 1, EVEN IF DELIMITER IS VERY
			//		SHORT SUCH AS 1 CHARACTER
			CRX_FOR(size_t tI = 0, tI <= tLength - pSize, tI++)
			{
				bool tIsFound = true;

				CRX_FOR(size_t tI2 = 0, tI2 < pSize, tI2++)
				{
					if(*(tChars + tI + tI2) != *(pChars__delimiter + tI2))
					{
						tIsFound = false;
						break;
					}
				}
				CRX_ENDFOR
						
				if(tIsFound)
				{
					if(crx_c_arrays_size_push2(pReturn, tI))
					{
						if(!pIsToAllowOverlap)
							{tI = tI + pSize - 1;}
					}
					else
					{
						vIsNoError = false;
						break;
					}
				}
			}
			CRX_ENDFOR
		}
		else if(tAlgorithm == 7)
		{
			/*
			TWO WAY SEARCH ALGORITHM. SEE PAPER "CP-1991-jacm". THE LETTERS IN COMMENT IS TO HELP
			COMPARE CODE TO ALOGIRHTMS IN THE PAPER. 
			*/
			size_t tCriticalPosition = 0; 	//ONE BASED INDEX
			size_t tI = 0; 					//ONE BASED INDEX
			size_t tI2 = 1;					//ONE BASED INDEX
			size_t tOffset = 1;
			size_t tDeltaTi = 1;
			size_t tPotentialPeriod = 0;

			
			//BASED ON MAXIMAL-SUFFIX() FUNCTION IN THE PAPER
			//tI   //i
			//tI2  //j
			//tOffset //k
			//tDeltaTi //p
			//pSize //n
			while(tI2 + tOffset <= pSize)
			{
				char tChar = *(pChars__delimiter + tI + tOffset - 1);
				char tChar2 = *(pChars__delimiter + tI2 + tOffset - 1);

				if(tChar > tChar2)
				{
					tI2 = tI2 + tOffset;
					tOffset = 1;
					tDeltaTi = tI2 - tI;
				}
				else if(tChar == tChar2)
				{
					if(tOffset == tDeltaTi)
					{
						tI2 = tI2 + tDeltaTi;
						tOffset = 1;
					}
					else
						{tOffset = tOffset + 1;}
				}
				else //(tChar < tChar2)
				{
					tI = tI2;
					tI2 = tI + 1;
					tOffset = 1;
					tDeltaTi = 1;
				}
			}

			//BASED ON SMALL-PERIOD() FUNCTION IN THE PAPER. THIS APPLIES ONLY TO THE NEXT
			//		TWO ASSIGNMENT STATEMENTS.
			tCriticalPosition = tI; //Alphabatical Maximal Suffix
			tPotentialPeriod = tDeltaTi;

			//BASED ON MAXIMAL-SUFFIX() FUNCTION IN THE PAPER
			tI = 0;   //i
			tI2 = 1;  //j
			tOffset = 1;  //k
			tDeltaTi = 1; //p
			//pSize //n

			while(tI2 + tOffset <= pSize)
			{
				char tChar = *(pChars__delimiter + tI + tOffset - 1);
				char tChar2 = *(pChars__delimiter + tI2 + tOffset - 1);

				if(tChar < tChar2)
				{
					tI2 = tI2 + tOffset;
					tOffset = 1;
					tDeltaTi = tI2 - tI;
				}
				else if(tChar == tChar2)
				{
					if(tOffset == tDeltaTi)
					{
						tI2 = tI2 + tDeltaTi;
						tOffset = 1;
					}
					else
						{tOffset = tOffset + 1;}
				}
				else //(tChar > tChar2)
				{
					tI = tI2;
					tI2 = tI + 1;
					tOffset = 1;
					tDeltaTi = 1;
				}
			}

			//BASED ON SMALL-PERIOD() FUNCTION IN THE PAPER. NOTE HOWEVER, THE NEXT
			//		IF STATEMENT MINGLES THE POSITIONS() FUNCTION IN ITS BRANCHES.
			//		ONE CAN COMPARE THE FINAL RESULT TO THE MATCH() FUNCTION IN THE PAPER.
			//		THE SECOND BRANCH OF THE SAID IF STATEMENT CAN ALSO BE COMPARED TO
			//		THE POSITIONS-BIS() FUNCION IN THE PAPER.
			if(tCriticalPosition < tI)
			{
				tCriticalPosition = tI; //Reverse Alphabatical Maximal Suffix
				tPotentialPeriod = tDeltaTi; 
			}
			
			if((tCriticalPosition < (pSize >> 1)) && 
					(memcmp(pChars__delimiter, pChars__delimiter + tPotentialPeriod, tCriticalPosition) == 0))
			{
				//BASED ON POSITIONS() FUNCTION IN THE PAPER.
				size_t tPeriod = tPotentialPeriod; //p
				size_t tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;//s
				
				tI2 = 0;//pos
				//tI //i
				//tCriticalPosition //l
				//tLength //|t|
				//pSize //|x|
				
				while(tI2 + pSize <= tLength)
				{
					//assert(pChars__delimiter[1 : tUpperBoundOfAlreadyVerifiedValuesOnRight] = 
					//		tChars[tI2 + 1 : tI2 + tUpperBoundOfAlreadyVerifiedValuesOnRight]) //right side is exclusive.

					tI = ((tCriticalPosition < tUpperBoundOfAlreadyVerifiedValuesOnRight) ? 
							tUpperBoundOfAlreadyVerifiedValuesOnRight : tCriticalPosition) + 1;
					
					while((tI <= pSize) && (*(pChars__delimiter + tI - 1) == *(tChars + tI2 + tI - 1)))
						{tI++;}

					if(tI <= pSize)
					{
						if((tUpperBoundOfAlreadyVerifiedValuesOnRight > tPeriod) &&
								((tUpperBoundOfAlreadyVerifiedValuesOnRight - tPeriod + 1) > 
								(tI - tCriticalPosition)))
							{tI2 = tI2 + tUpperBoundOfAlreadyVerifiedValuesOnRight - tPeriod + 1;}
						else
							{tI2 = tI2 + tI - tCriticalPosition;}

						tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;
					}
					else
					{
						size_t tJ = tCriticalPosition;	//ONE BASED INDEX

						//NO NEED TO SEARCH BEFORE tUpperBoundOfAlreadyVerifiedValuesOnRight. SEE ASSERT ABOVE
						while((tJ > tUpperBoundOfAlreadyVerifiedValuesOnRight) && 
								(*(pChars__delimiter + tJ - 1) == *(tChars + tI2 + tJ - 1)))
							{tJ = tJ - 1;}

						if(tJ <= tUpperBoundOfAlreadyVerifiedValuesOnRight)
						{
							if(crx_c_arrays_size_push2(pReturn, tI2))
							{
								if(!pIsToAllowOverlap)
								{
									tI2 = tI2 + pSize;
									tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;
								}
								else
								{
									tI2 = tI2 + tPeriod;
									tUpperBoundOfAlreadyVerifiedValuesOnRight = pSize - tPeriod;
								}
							}
							else
							{
								vIsNoError = false;
								break;
							}
						}
						else
						{
							tI2 = tI2 + tPeriod;
							tUpperBoundOfAlreadyVerifiedValuesOnRight = pSize - tPeriod;
						}
					}
				}
			}
			else
			{
				//BASED ON POSITIONS() FUNCTION IN THE PAPER.
				/*
				SAME AS ABOVE, BUT THE VALUE OF tUpperBoundOfAlreadyVerifiedValuesOnRight IS SUCH AS ALL CONDITIONS
				AROUND IT EVALUATE TO FALSE, AND THE VALUE IS EFFECTIVELY 0.
				*/
				size_t tPeriodLowerBound = ((tCriticalPosition >= pSize - tCriticalPosition) ?
						tCriticalPosition : pSize - tCriticalPosition) + 1; //p OR q IN THE FINAL FORM
				
				tI2 = 0;//pos
				//tI //i
				//tCriticalPosition //l
				//tLength //|t|
				//pSize //|x|

				while(tI2 + pSize <= tLength)
				{
					tI = tCriticalPosition + 1;
					
					while((tI <= pSize) && (*(pChars__delimiter + tI - 1) == *(tChars + tI2 + tI - 1)))
						{tI++;}

					if(tI <= pSize)
						{tI2 = tI2 + tI - tCriticalPosition;}
					else
					{
						size_t tJ = tCriticalPosition; //ONE BASED INDEX

						while((tJ > 0) && (*(pChars__delimiter + tJ - 1) == *(tChars + tI2 + tJ - 1)))
							{tJ = tJ - 1;}

						if(tJ == 0)
						{
							if(crx_c_arrays_size_push2(pReturn, tI2))
							{
								if(!pIsToAllowOverlap)
									{tI2 = tI2 + pSize;}
								else
									{tI2 = tI2 + tPeriodLowerBound;}
							}
							else
							{
								vIsNoError = false;
								break;
							}
						}
						else
							{tI2 = tI2 + tPeriodLowerBound;}
					}
				}
			}
		}
		else
			{assert(false);}
	}

	return vIsNoError;
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllOccurancesOf4(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, Crx_C_String_Sub const * pSub__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	if(crx_c_string_sub_getLength(pSub__delimiter) == 0)
	{
		crx_c_arrays_size_empty(pReturn);

		return true;
	}
	else
	{
		return crx_c_string_computeIndicesOfAllOccurancesOf3(pThis, pReturn,
				pStartIndex, crx_c_string_sub_getCharsPointer(pSub__delimiter),
				crx_c_string_sub_getLength(pSub__delimiter),
				pIsToAllowOverlap, pSizeOfCharacterSet);
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllReverseOccurancesOf(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, Crx_C_String const * pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_computeIndicesOfAllReverseOccurancesOf3(pThis, pReturn,
			pInclusiveEndIndex, crx_c_string_classProtected_constantGetElementsPointer(pDelimiter),
			crx_c_string_classProtected_getLength(pDelimiter),
			pIsToAllowOverlap, pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllReverseOccurancesOf2(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, char const * pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_computeIndicesOfAllReverseOccurancesOf3(pThis, pReturn,
			pInclusiveEndIndex, pDelimiter, strlen(pDelimiter),
			pIsToAllowOverlap, pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllReverseOccurancesOf3(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, char const * pChars__delimiter, size_t pSize,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	/*
	IMPORTANT: TO AVOID CONFUSION, UNDERSTAND THAT ALGORITHM 8 UNLIKE THE OTHER ALGORITHMS, 
			IS A REVERSE SEARCH ALGORITHM, AND NOT A SEARCH SUCH AS BOTH STRINGS ARE EFFECTIVELY 
			COPIED IN REVERSE BEFORE SEARCHING. IN OTHER WORDS, THE OTHER ALGORITHMS BELOW 
			TRANSFORM THE INDICES AT THE VERY END BEFORE ACCESSING THE STRINGS. THESE ALGORITHMS 
			ARE NOT AWARE OF A REVERSE SEARCH. ALGORITHM 8, HOWEVER, DOES NO SUCH TRANSFORMATION. 
			ALGORITHM 8 IS AWARE OF A REVERSE SEARCH.
			THINGS WERE DONE THIS WAY FOR THE REVERSE OCCURANCE SEARCH ALGORITHMS BELOW, OTHER THAN 
			ALGORITHM 8, TO KEEP THEIR SYMMETRY WITH THE OCCURANCE SEARCH ALGORITHMS ELSEWHERE.
	*/
	uint8_t vSizeOfCharacterSet = ((pSizeOfCharacterSet == 0) ? 255 : pSizeOfCharacterSet);
	size_t vFullLength = crx_c_string_classProtected_getLength(pThis);
	bool vIsNoError = true;

	crx_c_arrays_size_empty(pReturn);

	if(!((pInclusiveEndIndex < pSize - 1) || 
			(pInclusiveEndIndex >= vFullLength) || (pSize == 0)))
	{

		uint32_t tAlgorithm = 0;
		size_t tLength = pInclusiveEndIndex + 1;
		char const * tChars = crx_c_string_classProtected_constantGetElementsPointer(pThis);

		/*if(pSize < 5)
			{tAlgorithm = 1;}
		else
		{
			double tSizeOfCharacterSet = ((double)pSizeOfCharacterSet);
			double s2 = (tSizeOfCharacterSet * (1.0 - pow(1.0 - (1.0/tSizeOfCharacterSet), pSize)));//EXPECTED DISTINCT CHARACTERS IN DELIMITER
			double q = 0.4;
			double e = 1.0 / (((1.0 - q) / tSizeOfCharacterSet) + (q / s2));
			
			/*if(e > pSize)
				//{e = pSize;}* /
			
			/*if((pSize < 4) || (pSize * (tLength - pSize) <= 80000 * (1.0 - (1.0/vSizeOfCharacterSet))))* /
			//if(e <= 7)
			//	{tAlgorithm = 7/*6* /;}
			if(e <= 22)
				{tAlgorithm = 4;}
			else if(e <= 40)
				{tAlgorithm = 1;}
			else if(pSize < 7340032)
			{
				/*if(pSize < 16)
					{tAlgorithm = 2;}			
				else
					{tAlgorithm = 3;}* /

				tAlgorithm = 3;
			}
			else
				{tAlgorithm = 4;}
		}
		if(pSize < 5)
			{tAlgorithm = 1;}
		else
		{
			tAlgorithm = 4;
		}*/

		if(pSize < 7340032)
			{tAlgorithm = 3;}
		else
			{tAlgorithm = 8;}
		
		if(tAlgorithm <= 3)
		{
			/*
			KMP ALOGIRTHM

			NOTE: GIVEN A STRING[1..N], THE Nth SUFFIX PREFIX IS THE Nth LARGEST PREFIX OF THE STRING
					THAT IS ALSO ITS SUFFIX. THE LARGEST SUFFIX PREFIX IS THE STRING ITSELF. IN OTHER
					WORDS:
							SUFFIX_PREFIX{n}(STRING) = STRING[N-K+1..N] = STRING[1..K]  ; K IS THE LENGTH OF
									THE nth LARGEST SUFFIX PREFIX.
					NOTE THAT THE LENGTH OF STRING[X..Y] IS Y - X + 1. IN OTHER WORDS
									|STRING[N-K+1..N]| = K
					
					WE ARE FOR THE ALGOIRTHM ONLY INTERESTED IN THE SECOND LARGEST SUFFIX PREFIX.
					
					NOTE THAT IF FOR SUBSTRING STRING[A..B], 
							|SUFFIX_PREFIX{2}(STRING[A..B])| = K, 
					THEN FOR SUBSTRING STRING[A..B+1] 
							|SUFFIX_PREFIX{2}(STRING[A..B+1])| <= K + 1
					BECAUSE OTHERWISE THIS SUFFIX PREFIX WOULD END AT (A + K + L) FOR L > 0, MAKING IT A 
					CONTRADITCTION BECUASE THEN K WOULD NOT HAVE BEEN THE LENGTH OF THE SECOND LARGEST 
					SUFFIX PREFIX OF STRING[A..B].

					*NOTE THAT THE THIRD LARGEST SUFFIX PREFIX OF STRING[1..N], MEANING
							SUFFIX_PREFIX{3}(STRING[1..N])
					WOULD BE A SUBSTRING AND A SUFFIX PREFIX OF STRING[N-K+1..N], THE SECOND LARGEST 
					SUFFIX PREFIX, MEANING A SUBTRING OF
							SUFFIX_PREFIX{2}(STRING[1..N]) = STRING[N-K+1..N]
					AND BECAUSE STRING[N-K+1..N] IS EQUAL TO STRING[1..K], IT FOLLOWS THAT THIS THIRD 
					LARGEST SUFFIX PREFIX IS ALSO THE SECOND LARGEST SUFFIX PREFIX OF STRING[1..K]. IN OTHER
					WORDS
							SUFFIX_PREFIX{3}(STRING[1..N]) = SUFFIX_PREFIX{2}(SUFFIX_PREFIX{2}(STRING[1..N]))
														   = SUFFIX_PREFIX{2}(STRING[N-K+1..N])
														   = SUFFIX_PREFIX{2}(STRING[1..K])
					IF THIS WAS NOT THE CASE IT WOULD BE A CONTRADICTION. FOR EXAMPLE, IF THE LENGTH OF THE 
					THIRD LARGEST SUFFIX PREFIX OF STRING[1..N] IS L, THEN WE KNOW L < K AND WE KNOW THAT 
					THERE CAN BE NO OTHER SUFFIX PREFIX WHOSE LENGTH Y IS L < Y < K, AND NOW IF THIS SUFFIX 
					PREFIX IS NOT THE SECOND LARGEST SUFFIX PREFIX OF STRING[1..K], SUCH AS IT IS THE THIRD 
					LARGEST FOR EXAMPLE, THEN THERE EXISTS A SUFFIX PREFIX FOR STRING[1..K] WHOSE LENGTH 
					M > L. HOWEVER THIS SUFFIX PREFIX WOULD BE A SUFFIX PREFIX OF STRING[1..N], YET ITS 
					LENGTH M > L WHILE NOT BEING M = K, MEANING L < M < K WHICH IS A CONTRADICTION.
			*/
			size_t tCurrentIndexInDelimiter = 0;
			size_t * tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = NULL;
			bool tIsToFree = false;
			
			if(pSize + 1 > 80)
			{
				tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
						calloc(1, sizeof(size_t) * (pSize + 1));
				tIsToFree = true;
			}
			else
			{
				tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
						CRX__ALLOCA(sizeof(size_t) * (pSize + 1));
			}
			
			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[0] = 0;
			CRX_FOR(size_t tI = 1, tI < pSize, tI++)
			{        
				size_t tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[pSize - 1 - (tI - 1)];

				//IF SECOND LARGEST SUFFIX PREFIX DOES NOT HELP, WE SEEK OUT THE THIRD LARGEST
				//		SUFFIX PREFIX WHICH HAPPENS TO BE THE SECOND LARGEST SUFFIX PREFIX OF THE
				//		SECOND LARGEST SUFFIX PREFIX. AND SO FORTH.
				while((tJ != 0) && (*(pChars__delimiter + pSize - 1 - tI) != *(pChars__delimiter + pSize - 1 - tJ)))
					{tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tJ - 1];}

				if(*(pChars__delimiter + pSize - 1 - tI) == *(pChars__delimiter + pSize - 1 - tJ))
					{tJ += 1;}

				tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tI] = tJ;
			}
			CRX_ENDFOR

			if(tAlgorithm == 2)
			{
				//NOTE: THIS ALGORITHM DOES NOT EXIT EARLY.

				CRX_FOR(size_t tI = 0, tI < tLength, tI++)
				{
					while((tCurrentIndexInDelimiter != 0) && 
							(*(tChars + tLength - 1 - tI) != *(pChars__delimiter + pSize - 1 - tCurrentIndexInDelimiter)))
					{
						//SEE * ABOVE.
						tCurrentIndexInDelimiter = 
								tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
								tCurrentIndexInDelimiter - 1];
					}
					
					if(*(tChars + tLength - 1 - tI) == *(pChars__delimiter + pSize - 1 - tCurrentIndexInDelimiter))
						{tCurrentIndexInDelimiter += 1;}

					/*
						AT THIS POINT, THE FOLLOWING MUST ALWAYS HOLD TRUE
								tChars[tI + 1 - tCurrentIndexInDelimiter:tI + 1] == 
										pChars__delimiter[0:tCurrentIndexInDelimiter]
						IN OTHER WORDS, THE WINDOW, pChars__delimiter[0:tCurrentIndexInDelimiter], IS ALWAYS VALID, 
						ALWAYS EQUAL TO THE OVERLAP EVEN AFTER SHIFTING.
					*/

					if(tCurrentIndexInDelimiter == pSize)
					{
						if(crx_c_arrays_size_push2(pReturn, tLength - 1 - tI))/*== tLength - 1 - (tI + 1 - pSize) - (pSize - 1)*/
						{
							if(pIsToAllowOverlap)
								{tI = tI + 1 - pSize;}
							
							tCurrentIndexInDelimiter = 0;
						}
						else
						{
							vIsNoError = false;
							break;
						}
					}
				}
				CRX_ENDFOR
			}
			else
			{
				//NOTE: THIS ALGORITHM DOES NOT EXIT EARLY, BUT IS SAFE.
				//OLD NOTE: WHEN THE CHARACTER SET IS VERY SMALL, THIS IS THE FASTEST, BUT STILL TWICE 
				//		AS SLOW	FOR RANDOM INPUT, AND MORE SLOW FOR HIGHLY PATTERNED INTPUT UP TO THREE 
				//		TIMES AS SLOW
				uint32_t tReverseIndexOfCharacterLastOccurance[256] /*= ?*/;
				char tLastCharacter = *pChars__delimiter;
				
				CRX_FOR(size_t tI = 0, tI < 256, tI++)
					{tReverseIndexOfCharacterLastOccurance[tI] = (uint32_t)pSize;}
				CRX_ENDFOR

				CRX_FOR(size_t tI = 0, tI < pSize, tI++)
				{
					if(tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pChars__delimiter) + pSize - 1 - tI)] > (pSize - tI - 1))
						{tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pChars__delimiter) + pSize - 1 - tI)] = pSize - tI - 1;}
				}
				CRX_ENDFOR
				
				CRX_FOR(size_t tI = 0, tI < tLength, tI++)
				{
					if(tCurrentIndexInDelimiter == 0)
					{
						while((tI <= tLength - pSize) && (*(tChars + tLength - 1 - (tI + pSize - 1)) != tLastCharacter))
							{tI = tI + tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)tChars) + tLength - 1 - (tI + pSize - 1))];}
					}
					else
					{
						while((tCurrentIndexInDelimiter != 0) && 
								(*(tChars + tLength - 1 - tI) != *(pChars__delimiter + pSize - 1 - tCurrentIndexInDelimiter)))
						{
							//SEE * ABOVE.
							tCurrentIndexInDelimiter = 
									tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
									tCurrentIndexInDelimiter - 1];
						}
					}


					if(*(tChars + tLength - 1 - tI) == *(pChars__delimiter + pSize - 1 - tCurrentIndexInDelimiter))
						{tCurrentIndexInDelimiter += 1;}

					/*SEE ABOVE*/
					if(tCurrentIndexInDelimiter == pSize)
					{
						if(crx_c_arrays_size_push2(pReturn, tLength - 1 - tI))/*== tLength - 1 - (tI + 1 - pSize) - (pSize - 1)*/
						{
							if(pIsToAllowOverlap)
								{tI = tI + 1 - pSize;}
							
							tCurrentIndexInDelimiter = 0;
						}
						else
						{
							vIsNoError = false;
							break;
						}
					}
				}
				CRX_ENDFOR
			}

			if(tIsToFree)
			{
				free(tSecondLargestSuffixPrefixForSubDelimiterUpToIndex);
				tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = NULL;
			}
		}
		else if(tAlgorithm == 5)
		{
			CRX_FOR(size_t tI = 0, tI <= tLength - pSize, tI++)
			{
				bool tIsFound = true;

				CRX_FOR(size_t tI2 = 0, tI2 < pSize, tI2++)
				{
					if(*(tChars + tLength - 1 - tI - tI2) != *(pChars__delimiter + pSize - 1 - tI2))
					{
						tIsFound = false;
						break;
					}
				}
				CRX_ENDFOR
						
				if(tIsFound)
				{
					if(crx_c_arrays_size_push2(pReturn, tLength - tI - pSize))/*== tLength - 1 - tI - (pSize - 1)*/
					{
						if(!pIsToAllowOverlap)
							{tI = tI + pSize - 1;}
					}
					else
					{
						vIsNoError = false;
						break;
					}
				}
			}
			CRX_ENDFOR
		}
		else if(tAlgorithm == 7)
		{
			/*
			TWO WAY SEARCH ALGORITHM. SEE PAPER "CP-1991-jacm". THE LETTERS IN COMMENT IS TO HELP
			COMPARE CODE TO ALOGIRHTMS IN THE PAPER. 
			*/
			size_t tCriticalPosition = 0; 	//ONE BASED INDEX
			size_t tI = 0; 					//ONE BASED INDEX
			size_t tI2 = 1;					//ONE BASED INDEX
			size_t tOffset = 1;
			size_t tDeltaTi = 1;
			size_t tPotentialPeriod = 0;

			
			//BASED ON MAXIMAL-SUFFIX() FUNCTION IN THE PAPER
			//tI   //i
			//tI2  //j
			//tOffset //k
			//tDeltaTi //p
			//pSize //n
			while(tI2 + tOffset <= pSize)
			{
				char tChar = *(pChars__delimiter + pSize - 1 - (tI + tOffset - 1));
				char tChar2 = *(pChars__delimiter + pSize - 1 - (tI2 + tOffset - 1));

				if(tChar > tChar2)
				{
					tI2 = tI2 + tOffset;
					tOffset = 1;
					tDeltaTi = tI2 - tI;
				}
				else if(tChar == tChar2)
				{
					if(tOffset == tDeltaTi)
					{
						tI2 = tI2 + tDeltaTi;
						tOffset = 1;
					}
					else
						{tOffset = tOffset + 1;}
				}
				else //(tChar < tChar2)
				{
					tI = tI2;
					tI2 = tI + 1;
					tOffset = 1;
					tDeltaTi = 1;
				}
			}

			//BASED ON SMALL-PERIOD() FUNCTION IN THE PAPER. THIS APPLIES ONLY TO THE NEXT
			//		TWO ASSIGNMENT STATEMENTS.
			tCriticalPosition = tI; //Alphabatical Maximal Suffix
			tPotentialPeriod = tDeltaTi;

			//BASED ON MAXIMAL-SUFFIX() FUNCTION IN THE PAPER
			tI = 0;   //i
			tI2 = 1;  //j
			tOffset = 1;  //k
			tDeltaTi = 1; //p
			//pSize //n

			while(tI2 + tOffset <= pSize)
			{
				char tChar = *(pChars__delimiter + pSize - 1 - (tI + tOffset - 1));
				char tChar2 = *(pChars__delimiter + pSize - 1 - (tI2 + tOffset - 1));

				if(tChar < tChar2)
				{
					tI2 = tI2 + tOffset;
					tOffset = 1;
					tDeltaTi = tI2 - tI;
				}
				else if(tChar == tChar2)
				{
					if(tOffset == tDeltaTi)
					{
						tI2 = tI2 + tDeltaTi;
						tOffset = 1;
					}
					else
						{tOffset = tOffset + 1;}
				}
				else //(tChar > tChar2)
				{
					tI = tI2;
					tI2 = tI + 1;
					tOffset = 1;
					tDeltaTi = 1;
				}
			}

			//BASED ON SMALL-PERIOD() FUNCTION IN THE PAPER. NOTE HOWEVER, THE NEXT
			//		IF STATEMENT MINGLES THE POSITIONS() FUNCTION IN ITS BRANCHES.
			//		ONE CAN COMPARE THE FINAL RESULT TO THE MATCH() FUNCTION IN THE PAPER.
			//		THE SECOND BRANCH OF THE SAID IF STATEMENT CAN ALSO BE COMPARED TO
			//		THE POSITIONS-BIS() FUNCION IN THE PAPER.
			if(tCriticalPosition < tI)
			{
				tCriticalPosition = tI; //Reverse Alphabatical Maximal Suffix
				tPotentialPeriod = tDeltaTi; 
			}
			
			if((tCriticalPosition < (pSize >> 1)) && 
					(memcmp(pChars__delimiter + pSize - 1 - (tCriticalPosition - 1), pChars__delimiter + pSize - 1 - tPotentialPeriod - (tCriticalPosition - 1), tCriticalPosition) == 0))
			{
				//BASED ON POSITIONS() FUNCTION IN THE PAPER.
				size_t tPeriod = tPotentialPeriod; //p
				size_t tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;//s
				
				tI2 = 0;//pos
				//tI //i
				//tCriticalPosition //l
				//tLength //|t|
				//pSize //|x|
				
				while(tI2 + pSize <= tLength)
				{
					//assert(pChars__delimiter[1 : tUpperBoundOfAlreadyVerifiedValuesOnRight] = 
					//		tChars[tI2 + 1 : tI2 + tUpperBoundOfAlreadyVerifiedValuesOnRight]) //right side is exclusive.

					tI = ((tCriticalPosition < tUpperBoundOfAlreadyVerifiedValuesOnRight) ? 
							tUpperBoundOfAlreadyVerifiedValuesOnRight : tCriticalPosition) + 1;
					
					while((tI <= pSize) && (*(pChars__delimiter + pSize - 1 - (tI - 1)) == *(tChars + tLength - 1 - (tI2 + tI - 1))))
						{tI++;}

					if(tI <= pSize)
					{
						if((tUpperBoundOfAlreadyVerifiedValuesOnRight > tPeriod) &&
								((tUpperBoundOfAlreadyVerifiedValuesOnRight - tPeriod + 1) > 
								(tI - tCriticalPosition)))
							{tI2 = tI2 + tUpperBoundOfAlreadyVerifiedValuesOnRight - tPeriod + 1;}
						else
							{tI2 = tI2 + tI - tCriticalPosition;}

						tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;
					}
					else
					{
						size_t tJ = tCriticalPosition;	//ONE BASED INDEX

						//NO NEED TO SEARCH BEFORE tUpperBoundOfAlreadyVerifiedValuesOnRight. SEE ASSERT ABOVE
						while((tJ > tUpperBoundOfAlreadyVerifiedValuesOnRight) && 
								(*(pChars__delimiter + pSize - 1 - (tJ - 1)) == *(tChars + tLength - 1 - (tI2 + tJ - 1))))
							{tJ = tJ - 1;}

						if(tJ <= tUpperBoundOfAlreadyVerifiedValuesOnRight)
						{
							if(crx_c_arrays_size_push2(pReturn, tLength - 1 - tI2 - (pSize - 1)))
							{
								if(!pIsToAllowOverlap)
								{
									tI2 = tI2 + pSize;
									tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;
								}
								else
								{
									tI2 = tI2 + tPeriod;
									tUpperBoundOfAlreadyVerifiedValuesOnRight = pSize - tPeriod;
								}
							}
							else
							{
								vIsNoError = false;
								break;
							}
						}
						else
						{
							tI2 = tI2 + tPeriod;
							tUpperBoundOfAlreadyVerifiedValuesOnRight = pSize - tPeriod;
						}
					}
				}
			}
			else
			{
				//BASED ON POSITIONS() FUNCTION IN THE PAPER.
				/*
				SAME AS ABOVE, BUT THE VALUE OF tUpperBoundOfAlreadyVerifiedValuesOnRight IS SUCH AS ALL CONDITIONS
				AROUND IT EVALUATE TO FALSE, AND THE VALUE IS EFFECTIVELY 0.
				*/
				size_t tPeriodLowerBound = ((tCriticalPosition >= pSize - tCriticalPosition) ?
						tCriticalPosition : pSize - tCriticalPosition) + 1; //p OR q IN THE FINAL FORM
				
				tI2 = 0;//pos
				//tI //i
				//tCriticalPosition //l
				//tLength //|t|
				//pSize //|x|

				while(tI2 + pSize <= tLength)
				{
					tI = tCriticalPosition + 1;
					
					while((tI <= pSize) && (*(pChars__delimiter + pSize - 1 - (tI - 1)) == *(tChars + tLength - 1 - (tI2 + tI - 1))))
						{tI++;}

					if(tI <= pSize)
						{tI2 = tI2 + tI - tCriticalPosition;}
					else
					{
						size_t tJ = tCriticalPosition; //ONE BASED INDEX

						while((tJ > 0) && (*(pChars__delimiter + pSize - 1 - (tJ - 1)) == *(tChars + tLength - 1 - (tI2 + tJ - 1))))
							{tJ = tJ - 1;}

						if(tJ == 0)
						{
							if(crx_c_arrays_size_push2(pReturn, tLength - 1 - tI2 - (pSize - 1)))
							{
								if(!pIsToAllowOverlap)
									{tI2 = tI2 + pSize;}
								else
									{tI2 = tI2 + tPeriodLowerBound;}
							}
							else
							{
								vIsNoError = false;
								break;
							}
						}
						else
							{tI2 = tI2 + tPeriodLowerBound;}
					}
				}
			}
		}
		else if(tAlgorithm == 8)
		{
			unsigned char const * tChars__2 = tChars;
			size_t tEndIndex = pSize - 1; //One based index
			unsigned char tFirstCharacter = *pChars__delimiter;
			unsigned char tLastCharacter = *(pChars__delimiter + pSize - 1);
			uint32_t tIndexOfCharacterFirstOccurance[256] /*= ?*/;
			size_t vI = tLength; //One based index

			CRX_FOR(size_t tI = 0, tI < 256, tI++)
				{tIndexOfCharacterFirstOccurance[tI] = (uint32_t)pSize;}
			CRX_ENDFOR
			
			CRX_FOR(size_t tI = 0, tI < pSize, tI++)
			{
				if(tIndexOfCharacterFirstOccurance[*(((unsigned char const *)pChars__delimiter)  + tI)] > tI)
					{tIndexOfCharacterFirstOccurance[*(((unsigned char const *)pChars__delimiter)  + tI)] = tI;}
			}
			CRX_ENDFOR

			while(vI > tEndIndex)
			{
				while((vI > tEndIndex) && (*(tChars + vI - 1) != tLastCharacter))
					{vI--;}

				if(vI > tEndIndex)
				{
					while((vI > tEndIndex) && (*(tChars__2 + vI - pSize) != tFirstCharacter))
						{vI = vI - tIndexOfCharacterFirstOccurance[*(tChars__2 + vI - pSize)];}

					if(vI > tEndIndex)
					{
						if(memcmp(tChars__2 + vI - pSize, pChars__delimiter, pSize) == 0)
						{
							if(crx_c_arrays_size_push2(pReturn, vI - pSize))
							{
								if(!pIsToAllowOverlap)
									{vI = vI - pSize;}
								else
									{vI--;}
							}
							else
							{
								vIsNoError = false;
								break;
							}
						}
						else
							{vI--;}
					}
				}
			}
		}
		else
			{assert(false);}
	}

	return vIsNoError;
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllReverseOccurancesOf4(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, Crx_C_String_Sub const * pSub__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	if(crx_c_string_sub_getLength(pSub__delimiter) == 0)
	{
		crx_c_arrays_size_empty(pReturn);

		return true;
	}
	else
	{
		return crx_c_string_computeIndicesOfAllReverseOccurancesOf3(pThis, pReturn,
				pInclusiveEndIndex, crx_c_string_sub_getCharsPointer(pSub__delimiter),
				crx_c_string_sub_getLength(pSub__delimiter),
				pIsToAllowOverlap, pSizeOfCharacterSet);
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_replaceOccurancesOfChar(Crx_C_String * pThis,
		size_t pStartingIndex, char pChar, char pReplacementChar, bool pIsToReplaceFirstOnly)
{
	CRX_SCOPE_META
	if(crx_c_string_classProtected_getLength(pThis) == 0)
		{return;}

	CRX_SCOPE
	char * vCurrentChar = crx_c_string_classProtected_getElementsPointer(pThis) + pStartingIndex;
	char * vEndChar = vCurrentChar + crx_c_string_classProtected_getLength(pThis);

	vCurrentChar = memchr(vCurrentChar, pChar, vEndChar - vCurrentChar);

	if(!pIsToReplaceFirstOnly)
	{
		while(vCurrentChar != NULL)
		{
			*vCurrentChar = pReplacementChar;
			vCurrentChar = memchr(vCurrentChar, pChar, vEndChar - vCurrentChar);
		}
	}
	else
	{
		if(vCurrentChar != NULL)
			{*vCurrentChar = pReplacementChar;}
	}
		

	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findNextLeftTokenAndUpdateIndex(
		Crx_C_String const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, Crx_C_String const * CRX_NOT_NULL pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_findNextLeftTokenAndUpdateIndex3(pThis, pReturn, pIndex, 
			crx_c_string_classProtected_constantGetElementsPointer(pDelimiter),
			crx_c_string_classProtected_getLength(pDelimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findNextLeftTokenAndUpdateIndex2(
		Crx_C_String const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, char const * CRX_NOT_NULL pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_findNextLeftTokenAndUpdateIndex3(pThis, pReturn, pIndex, 
			pDelimiter, strlen(pDelimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findNextLeftTokenAndUpdateIndex3(
		Crx_C_String const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, char const * CRX_NOT_NULL pChars__delimiter, size_t pSize,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	size_t vEndIndex = crx_c_string_getIndexOfFirstOccuranceOf3(pThis, *pIndex, pChars__delimiter, 
			pSize, pSizeOfCharacterSet);

	if(vEndIndex != ((size_t)(-1)))
	{
		crx_c_string_sub_setString2(pReturn, pThis, *pIndex, vEndIndex);
		*pIndex = vEndIndex + pSize;

		return true;
	}
	else
	{
		if(*pIndex < crx_c_string_classProtected_getLength(pThis))
		{
			crx_c_string_sub_setString2(pReturn, pThis, *pIndex, 
					crx_c_string_classProtected_getLength(pThis));
			*pIndex = crx_c_string_classProtected_getLength(pThis);

			return true;
		}
		else if(*pIndex == crx_c_string_classProtected_getLength(pThis))
		{
			crx_c_string_sub_setString2(pReturn, pThis, 
					crx_c_string_classProtected_getLength(pThis), 
					crx_c_string_classProtected_getLength(pThis));
			*pIndex = ((size_t)(-1));

			return true;
		}
		else
		{
			crx_c_string_sub_unsetString(pReturn);
			*pIndex = ((size_t)(-1));

			return false;
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findNextLeftTokenAndUpdateIndex4(
		Crx_C_String const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, 
		Crx_C_String_Sub const * CRX_NOT_NULL pSub__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_findNextLeftTokenAndUpdateIndex3(pThis, pReturn, pIndex, 
			crx_c_string_sub_getCharsPointer(pSub__delimiter),
			crx_c_string_sub_getLength(pSub__delimiter), pSizeOfCharacterSet);
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findAllTokensStartingFromLeft(
		Crx_C_String const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, Crx_C_String const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_findAllTokensStartingFromLeft3(pThis, pReturn, pIndex, 
			crx_c_string_classProtected_constantGetElementsPointer(pDelimiter), 
			crx_c_string_classProtected_getLength(pDelimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findAllTokensStartingFromLeft2(
		Crx_C_String const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, char const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_findAllTokensStartingFromLeft3(pThis, pReturn, pIndex, 
			pDelimiter, strlen(pDelimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findAllTokensStartingFromLeft3(
		Crx_C_String const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, char const * CRX_NOT_NULL pChars__delimiter, size_t pSize,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	Crx_C_Arrays_Size vIndices /*= ?*/;
	Crx_C_String_Sub vSub /*= ?*/;
	size_t vIndex = pIndex;
			
	crx_c_arrays_size_construct(&vIndices, 2);
	crx_c_string_sub_construct(&vSub);
	
	crx_c_string_arrays_sub_empty(pReturn);

	crx_c_string_computeIndicesOfAllOccurancesOf3(pThis, &vIndices, pIndex, pChars__delimiter, 
			pSize, false, pSizeOfCharacterSet);
	
	CRX_FOR(size_t tI = 0, tI < crx_c_arrays_size_getLength(&vIndices), tI++)
	{
		size_t tIndex = crx_c_arrays_size_copyGet(&vIndices, tI);

		crx_c_string_sub_setString2(&vSub, pThis, vIndex, tIndex);
		vIndex = tIndex + pSize;
		
		crx_c_string_arrays_sub_push(pReturn, &vSub);
	}
	CRX_ENDFOR

	if(vIndex < crx_c_string_classProtected_getLength(pThis))
	{
		crx_c_string_sub_setString2(&vSub, pThis, vIndex, 
				crx_c_string_classProtected_getLength(pThis));
		crx_c_string_arrays_sub_push(pReturn, &vSub);
	}

	crx_c_arrays_size_destruct(&vIndices);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findAllTokensStartingFromLeft4(
		Crx_C_String const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, Crx_C_String_Sub const * pSub__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_findAllTokensStartingFromLeft3(pThis, pReturn, pIndex, 
			crx_c_string_sub_getCharsPointer(pSub__delimiter), 
			crx_c_string_sub_getLength(pSub__delimiter), pSizeOfCharacterSet);
}

//---------------------------
//CLASS: String::Sub
//---------------------------
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_sub_construct(Crx_C_String_Sub * pThis)
{
	pThis->gPrivate_string = NULL;
	pThis->gPrivate_startIndex = ((uint32_t)(-1));
	pThis->gPrivate_endIndex = ((uint32_t)(-1));
	pThis->PRIVATE__CHAR = '\0';
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_sub_construct2(Crx_C_String_Sub * pThis,
		Crx_C_String const * pString)
{
	pThis->gPrivate_string = pString;

	if(pString != NULL)
	{
		pThis->gPrivate_startIndex = 0;
		pThis->gPrivate_endIndex = crx_c_string_getSize(pString);
	}
	else
	{
		pThis->gPrivate_startIndex = ((uint32_t)(-1));
		pThis->gPrivate_endIndex = ((uint32_t)(-1));
	}

	pThis->PRIVATE__CHAR = '\0';
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_sub_construct3(Crx_C_String_Sub * pThis,
		Crx_C_String const * pString, size_t pStart, size_t pEnd)
{
	assert(pStart <= CRX__C__STRING__PRIVATE__SIZE32_MAX);

	pThis->gPrivate_string = pString;

	if(pThis->gPrivate_string != NULL)
	{
		uint32_t tLength = crx_c_string_getSize(pThis->gPrivate_string);

		if(pStart < tLength)
		{
			pThis->gPrivate_startIndex = ((uint32_t)pStart);
			pThis->gPrivate_endIndex = tLength;
		}
		else
		{
			pThis->gPrivate_startIndex = ((uint32_t)(-1));
			pThis->gPrivate_endIndex = ((uint32_t)(-1));
		}
	}
	else
	{
		pThis->gPrivate_startIndex = ((uint32_t)(-1));
		pThis->gPrivate_endIndex = ((uint32_t)(-1));
	}

	pThis->PRIVATE__CHAR = '\0';
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String_Sub * crx_c_string_sub_new()
{
	Crx_C_String_Sub * vReturn = ((Crx_C_String_Sub *) malloc(sizeof(Crx_C_String_Sub)));

	if(vReturn != NULL)
		{crx_c_string_sub_construct(vReturn);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String_Sub * crx_c_string_sub_new2(
		Crx_C_String const * pString)
{
	Crx_C_String_Sub * vReturn = ((Crx_C_String_Sub *) malloc(sizeof(Crx_C_String_Sub)));

	if(vReturn != NULL)
		{crx_c_string_sub_construct2(vReturn, pString);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String_Sub * crx_c_string_sub_new3(
		Crx_C_String const * pString, size_t pStart, size_t pEnd)
{
	Crx_C_String_Sub * vReturn = ((Crx_C_String_Sub *) malloc(sizeof(Crx_C_String_Sub)));

	if(vReturn != NULL)
		{crx_c_string_sub_construct3(vReturn, pString, pStart, pEnd);}

	return vReturn;
}

CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_setRange(Crx_C_String_Sub * pThis,
		size_t pStart, size_t pEnd)
{
	CRX_SCOPE_META
	assert(pStart <= CRX__C__STRING__PRIVATE__SIZE32_MAX);
	assert(pEnd <= CRX__C__STRING__PRIVATE__SIZE32_MAX);

	if(pThis->gPrivate_string == NULL)
		{return 0;}

	CRX_SCOPE
	size_t vLength = crx_c_string_getSize(pThis->gPrivate_string);

	if((pEnd <= vLength) && (pStart <= pEnd))
	{
		pThis->gPrivate_startIndex = ((uint32_t)pStart);
		pThis->gPrivate_endIndex = ((uint32_t)pEnd);
	}
	else
	{
		pThis->gPrivate_startIndex = ((uint32_t)(-1));
		pThis->gPrivate_endIndex = ((uint32_t)(-1));
	}

	return (pThis->gPrivate_endIndex - pThis->gPrivate_startIndex);
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_setString(Crx_C_String_Sub * pThis,
		Crx_C_String const * pString)
{
	pThis->gPrivate_string = pString;

	if(pThis->gPrivate_string != NULL)
	{
		pThis->gPrivate_startIndex = 0;
		pThis->gPrivate_endIndex = crx_c_string_getSize(pThis->gPrivate_string);
	}
	else
	{
		pThis->gPrivate_startIndex = ((uint32_t)(-1));
		pThis->gPrivate_endIndex = ((uint32_t)(-1));
	}

	return (pThis->gPrivate_endIndex - pThis->gPrivate_startIndex);
}
CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_setString2(Crx_C_String_Sub * pThis,
		Crx_C_String const * pString, size_t pStart, size_t pEnd)
{
	assert(pStart <= CRX__C__STRING__PRIVATE__SIZE32_MAX);
	assert(pEnd <= CRX__C__STRING__PRIVATE__SIZE32_MAX);

	pThis->gPrivate_string = pString;

	if(pThis->gPrivate_string != NULL)
	{
		size_t tLength = crx_c_string_getSize(pThis->gPrivate_string);

		if((pStart < tLength) && (pStart <= pEnd))
		{
			pThis->gPrivate_startIndex = ((uint32_t)pStart);
			pThis->gPrivate_endIndex = ((uint32_t)pEnd);
		}
		else
		{
			pThis->gPrivate_startIndex = ((uint32_t)(-1));
			pThis->gPrivate_endIndex = ((uint32_t)(-1));
		}
	}
	else
	{
		pThis->gPrivate_startIndex = ((uint32_t)(-1));
		pThis->gPrivate_endIndex = ((uint32_t)(-1));
	}

	return (pThis->gPrivate_endIndex - pThis->gPrivate_startIndex);
}

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getSubStartIndex(
		Crx_C_String_Sub const * pThis)
{
	return ((pThis->gPrivate_startIndex == ((uint32_t)(-1))) ? 
			((size_t)(-1)) : pThis->gPrivate_startIndex);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getSubEndIndex(Crx_C_String_Sub const * pThis)
{
	return ((pThis->gPrivate_endIndex == ((uint32_t)(-1))) ? 
			((size_t)(-1)) : pThis->gPrivate_endIndex);
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_sub_setNoRange(Crx_C_String_Sub * pThis)
{
	pThis->gPrivate_startIndex = ((uint32_t)(-1));
	pThis->gPrivate_endIndex = ((uint32_t)(-1));
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_sub_unsetString(Crx_C_String_Sub * pThis)
{
	pThis->gPrivate_string = NULL;
	pThis->gPrivate_startIndex = ((uint32_t)(-1));
	pThis->gPrivate_endIndex = ((uint32_t)(-1));
}

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getLength(Crx_C_String_Sub const * pThis)
	{return ((size_t)(pThis->gPrivate_endIndex - pThis->gPrivate_startIndex));}

CRX__LIB__PUBLIC_C_FUNCTION() char const * crx_c_string_sub_getCharsPointer(
		Crx_C_String_Sub const * pThis)
{
	if((pThis->gPrivate_string != NULL) && (pThis->gPrivate_startIndex != ((uint32_t)(-1))))
	{
		return crx_c_string_constantGetCharsPointer(pThis->gPrivate_string) + 
				pThis->gPrivate_startIndex;
	}
	else
		{return &(pThis->PRIVATE__CHAR);}
}
CRX__LIB__PUBLIC_C_FUNCTION() char crx_c_string_sub_copyGet(Crx_C_String_Sub const * pThis, 
		size_t pIndex)
{
	assert((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex) > pIndex);
	
	return pThis->gPrivate_startIndex + pIndex;
}

CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_leftCut(Crx_C_String_Sub * pThis, 
		size_t pLength)
{
	assert(pLength <= CRX__C__STRING__PRIVATE__SIZE32_MAX);

	if(pThis->gPrivate_string != NULL)
	{
		if((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex) > pLength)
			{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex + ((uint32_t)pLength);}
		else
			{pThis->gPrivate_startIndex = pThis->gPrivate_endIndex;}
	}

	return (pThis->gPrivate_endIndex - pThis->gPrivate_startIndex);
}
CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_rightCut(Crx_C_String_Sub * pThis, 
		size_t pLength)
{
	assert(pLength <= CRX__C__STRING__PRIVATE__SIZE32_MAX);

	if(pThis->gPrivate_string != NULL)
	{
		if((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex) > pLength)
			{pThis->gPrivate_endIndex = pThis->gPrivate_endIndex - ((uint32_t)pLength);}
		else
			{pThis->gPrivate_endIndex = pThis->gPrivate_startIndex;}
	}

	return (pThis->gPrivate_endIndex - pThis->gPrivate_startIndex);
}

CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_leftExtend(Crx_C_String_Sub * pThis,
		size_t pLength)
{
	assert(pLength <= CRX__C__STRING__PRIVATE__SIZE32_MAX);

	if((pThis->gPrivate_string != NULL) && (pThis->gPrivate_startIndex != ((uint32_t)(-1))))
	{
		if(pThis->gPrivate_startIndex >= pLength)
			{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex - ((uint32_t)pLength);}
		else
			{pThis->gPrivate_startIndex = 0;}
	}

	return (pThis->gPrivate_endIndex - pThis->gPrivate_startIndex);
}
CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_rightExtend(Crx_C_String_Sub * pThis, 
		size_t pLength)
{
	if((pThis->gPrivate_string != NULL) && (pThis->gPrivate_endIndex != ((uint32_t)(-1))))
	{
		size_t tLength = crx_c_string_getSize(pThis->gPrivate_string);

		if((tLength - pThis->gPrivate_endIndex) > pLength)
			{pThis->gPrivate_endIndex = pThis->gPrivate_endIndex + pLength;}
		else
			{pThis->gPrivate_endIndex = tLength;}
	}

	return (pThis->gPrivate_endIndex - pThis->gPrivate_startIndex);
}


CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEmpty(Crx_C_String_Sub const * pThis)
{
	if((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex) == 0)
		{return true;}

	char const * tCurrentChar = crx_c_string_constantGetCharsPointer(pThis->gPrivate_string) + 
			pThis->gPrivate_startIndex;
	char const * tEndChar = crx_c_string_constantGetCharsPointer(pThis->gPrivate_string) + 
			pThis->gPrivate_endIndex;

	while(tCurrentChar != tEndChar)
	{
		if(!(((*tCurrentChar >= 0) && (*tCurrentChar <= 32)) || (*tCurrentChar == 127)))
			{return false;}
	}

	return true;
}
CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_trim(Crx_C_String_Sub * pThis,
		unsigned char pLowerByteValue, unsigned char pUpperByteValue)
{
	CRX_SCOPE_META
	if(pThis->gPrivate_endIndex - pThis->gPrivate_startIndex == 0)
		{return 0;}

	CRX_SCOPE
	char const * vChars = crx_c_string_constantGetCharsPointer(pThis->gPrivate_string) + 
			pThis->gPrivate_startIndex;
	char const * vChars__end = vChars + pThis->gPrivate_endIndex;

	/*while((vChars != vChars__end) && (((*vChars >= 9) && (*vChars <= 13)) ||
			(*vChars == 32) || (*vChars == 127)))*/
	while((vChars != vChars__end) && (((*vChars >= 0) && (*vChars <= 32)) ||
			(*vChars == 127)))
	{
		vChars++;
		pThis->gPrivate_startIndex = pThis->gPrivate_startIndex + 1;
	}
	
	if(vChars != vChars__end)
	{
		char const * tChars = vChars__end - 1;

		/*while((tChars != vChars) && (((*tChars >= 9) && (*tChars <= 13)) ||
				(*tChars == 32) || (*vChars == 127)))*/
		while((tChars != vChars) && (((*tChars >= 0) && (*tChars <= 32)) ||
				(*vChars == 127)))
		{
			tChars--;
			pThis->gPrivate_endIndex = pThis->gPrivate_endIndex - 1;
		}
	}
	else
	{
		pThis->gPrivate_startIndex = ((uint32_t)(-1));
		pThis->gPrivate_endIndex = ((uint32_t)(-1));
	}


	return (pThis->gPrivate_endIndex - pThis->gPrivate_startIndex);
	CRX_SCOPE_END
}


CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEqualTo(Crx_C_String_Sub const * pThis,
		Crx_C_String const * CRX_NOT_NULL pString, bool pIsCaseInSensitive)
{
	return crx_c_string_sub_isEqualTo3(pThis, crx_c_string_constantGetCharsPointer(pString), 
			crx_c_string_getSize(pString), pIsCaseInSensitive);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEqualTo2(Crx_C_String_Sub const * pThis,
		char const * CRX_NOT_NULL pString, bool pIsCaseInSensitive)
	{return crx_c_string_sub_isEqualTo3(pThis, pString, strlen(pString), pIsCaseInSensitive);}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEqualTo3(Crx_C_String_Sub const * pThis,
		char const * CRX_NOT_NULL pChars, size_t pSize, bool pIsCaseInSensitive)
{
	if((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex) != pSize)
		{return false;}
	else
	{
		if((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex) == 0)
			{return (pSize == 0);}
		else
		{
			if(!pIsCaseInSensitive)
			{
				return (memcmp(crx_c_string_constantGetCharsPointer(pThis->gPrivate_string) + 
						pThis->gPrivate_startIndex, pChars, pSize) == 0);
			}
			else
			{
				return (crx_c_string_caseInsensitivelyCompare(
						crx_c_string_constantGetCharsPointer(pThis->gPrivate_string) + 
						pThis->gPrivate_startIndex, pChars, pSize) == 0);
			}
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEqualTo4(Crx_C_String_Sub const * pThis,
		Crx_C_String_Sub * CRX_NOT_NULL pSub, bool pIsCaseInSensitive)
{
	if((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex) != 
			(pSub->gPrivate_endIndex - pSub->gPrivate_startIndex))
		{return false;}
	else
	{
		if(pThis->gPrivate_endIndex - pThis->gPrivate_startIndex == 0)
			{return true;}
		else
		{
			return crx_c_string_sub_isEqualTo3(pThis, crx_c_string_constantGetCharsPointer(
							pSub->gPrivate_string) + pSub->gPrivate_startIndex,
					pThis->gPrivate_endIndex - pThis->gPrivate_startIndex, pIsCaseInSensitive);
		}
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isBeginningWith(Crx_C_String_Sub const * pThis,
		Crx_C_String const * CRX_NOT_NULL pString, bool pIsCaseInSensitive)
{
	return crx_c_string_sub_isBeginningWith3(pThis, 
			crx_c_string_constantGetCharsPointer(pString), crx_c_string_getSize(pString),
			pIsCaseInSensitive);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isBeginningWith2(Crx_C_String_Sub const * pThis,
		char const * CRX_NOT_NULL pString, bool pIsCaseInSensitive)
{
	return crx_c_string_sub_isBeginningWith3(pThis, pString, strlen(pString), 
			pIsCaseInSensitive);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isBeginningWith3(Crx_C_String_Sub const * pThis,
		char const * CRX_NOT_NULL pChars, size_t pSize, bool pIsCaseInSensitive)
{
	if((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex) < pSize)
		{return false;}
	else
	{
		if((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex) == 0)
			{return (pSize == 0);}
		else
		{
			if(!pIsCaseInSensitive)
			{
				return (memcmp(crx_c_string_constantGetCharsPointer(pThis->gPrivate_string) + 
						pThis->gPrivate_startIndex, pChars, pSize) == 0);
			}
			else
			{
				return (crx_c_string_caseInsensitivelyCompare(
						crx_c_string_constantGetCharsPointer(pThis->gPrivate_string) + 
						pThis->gPrivate_startIndex, pChars, pSize) == 0);
			}
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isBeginningWith4(Crx_C_String_Sub const * pThis,
		Crx_C_String_Sub const * CRX_NOT_NULL pSub, bool pIsCaseInSensitive)
{
	if((pSub->gPrivate_endIndex - pSub->gPrivate_startIndex) == 0)
		{return true;} //BASED ON THE BEHAVIOR OF memcmp(x, y, 0)
	else
	{
		return crx_c_string_sub_isBeginningWith3(pThis, 
				crx_c_string_constantGetCharsPointer(pSub->gPrivate_string) + 
				pSub->gPrivate_startIndex, pSub->gPrivate_endIndex - 
				pSub->gPrivate_startIndex, pIsCaseInSensitive);
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEndingWith(Crx_C_String_Sub const * pThis,
		Crx_C_String const * CRX_NOT_NULL pString, bool pIsCaseInSensitive)
{
	return crx_c_string_sub_isEndingWith3(pThis, 
			crx_c_string_constantGetCharsPointer(pString), crx_c_string_getSize(pString),
			pIsCaseInSensitive);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEndingWith2(Crx_C_String_Sub const * pThis,
		char const * CRX_NOT_NULL pString, bool pIsCaseInSensitive)
{
	return crx_c_string_sub_isEndingWith3(pThis, pString, strlen(pString), 
			pIsCaseInSensitive);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEndingWith3(Crx_C_String_Sub const * pThis,
		char const * CRX_NOT_NULL pChars, size_t pSize, bool pIsCaseInSensitive)
{
	if((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex) < pSize)
		{return false;}
	else
	{
		if((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex) == 0)
			{return (pSize == 0);}
		else
		{
			if(!pIsCaseInSensitive)
			{
				return (memcmp(crx_c_string_constantGetCharsPointer(pThis->gPrivate_string) + 
						pThis->gPrivate_endIndex - pSize, pChars, pSize) == 0);
			}
			else
			{
				return (crx_c_string_caseInsensitivelyCompare(
						crx_c_string_constantGetCharsPointer(pThis->gPrivate_string) + 
						pThis->gPrivate_endIndex - pSize, pChars, pSize) == 0);
			}
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEndingWith4(Crx_C_String_Sub const * pThis,
		Crx_C_String_Sub const * CRX_NOT_NULL pSub, bool pIsCaseInSensitive)
{
	if((pSub->gPrivate_endIndex - pSub->gPrivate_startIndex) == 0)
		{return true;} //BASED ON THE BEHAVIOR OF memcmp(x, y, 0)
	else
	{
		return crx_c_string_sub_isEndingWith3(pThis, 
				crx_c_string_constantGetCharsPointer(pSub->gPrivate_string) + 
				pSub->gPrivate_startIndex, pSub->gPrivate_endIndex - 
				pSub->gPrivate_startIndex, pIsCaseInSensitive);
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstOccuranceOf(
		Crx_C_String_Sub const * pThis, size_t pStartIndex, 
		Crx_C_String const * CRX_NOT_NULL pDelimiter, 
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_sub_getIndexOfFirstOccuranceOf3(pThis, pStartIndex, 
			crx_c_string_constantGetCharsPointer(pDelimiter), 
			crx_c_string_getSize(pDelimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstOccuranceOf2(
		Crx_C_String_Sub const * pThis, size_t pStartIndex, 
		char const * CRX_NOT_NULL pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_sub_getIndexOfFirstOccuranceOf3(pThis, pStartIndex, 
			pDelimiter, strlen(pDelimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstOccuranceOf3(
		Crx_C_String_Sub const * pThis, size_t pStartIndex, 
		char const * CRX_NOT_NULL pChars__delimiter, 
		size_t pSize, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	if((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex == 0) ||
			(((uint32_t)(-1)) - 1 - pStartIndex  <= pThis->gPrivate_startIndex))
		{return ((size_t)(-1));}

	return crx_c_string_getIndexOfFirstOccuranceOf3(pThis->gPrivate_string,
			pThis->gPrivate_startIndex + pStartIndex, pChars__delimiter, pSize, 
			pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstOccuranceOf4(
		Crx_C_String_Sub const * pThis, size_t pStartIndex, 
		Crx_C_String_Sub const * CRX_NOT_NULL pSub__delimiter, 
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	if((pSub__delimiter->gPrivate_endIndex - 
					pSub__delimiter->gPrivate_startIndex == 0))
		{return ((size_t)(-1));}

	return crx_c_string_sub_getIndexOfFirstOccuranceOf3(pThis, pStartIndex, 
			crx_c_string_constantGetCharsPointer(pSub__delimiter->gPrivate_string) + 
					pSub__delimiter->gPrivate_startIndex, 
			pSub__delimiter->gPrivate_endIndex - 
					pSub__delimiter->gPrivate_startIndex,
			pSizeOfCharacterSet);
}

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstReverseOccuranceOf(
		Crx_C_String_Sub const * pThis, size_t pInclusiveEndIndex, 
		Crx_C_String const * CRX_NOT_NULL pDelimiter, 
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_sub_getIndexOfFirstReverseOccuranceOf3(pThis, pInclusiveEndIndex,
			crx_c_string_constantGetCharsPointer(pDelimiter), 
			crx_c_string_getSize(pDelimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstReverseOccuranceOf2(
		Crx_C_String_Sub const * pThis, size_t pInclusiveEndIndex, 
		char const * CRX_NOT_NULL pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_sub_getIndexOfFirstReverseOccuranceOf3(pThis, pInclusiveEndIndex, 
			pDelimiter, strlen(pDelimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstReverseOccuranceOf3(
		Crx_C_String_Sub const * pThis, 
		size_t pInclusiveEndIndex, char const * CRX_NOT_NULL pChars__delimiter, 
		size_t pSize, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	if((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex == 0) ||
			(((uint32_t)(-1)) - 1 - pInclusiveEndIndex  <= pThis->gPrivate_startIndex))
		{return ((size_t)(-1));}

	return crx_c_string_getIndexOfFirstReverseOccuranceOf3(pThis->gPrivate_string,
			pThis->gPrivate_startIndex + pInclusiveEndIndex, pChars__delimiter, pSize, 
			pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstReverseOccuranceOf4(
		Crx_C_String_Sub const * pThis, size_t pInclusiveEndIndex, 
		Crx_C_String_Sub const * CRX_NOT_NULL pSub__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	if((pSub__delimiter->gPrivate_endIndex - 
					pSub__delimiter->gPrivate_startIndex == 0))
		{return ((size_t)(-1));}

	return crx_c_string_sub_getIndexOfFirstReverseOccuranceOf3(pThis, pInclusiveEndIndex, 
			crx_c_string_constantGetCharsPointer(pSub__delimiter->gPrivate_string) + 
					pSub__delimiter->gPrivate_startIndex, 
			pSub__delimiter->gPrivate_endIndex - 
					pSub__delimiter->gPrivate_startIndex,
			pSizeOfCharacterSet);
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllOccurancesOf(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, Crx_C_String const * CRX_NOT_NULL pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_sub_computeIndicesOfAllOccurancesOf3(pThis, pReturn, pStartIndex, 
			crx_c_string_constantGetCharsPointer(pDelimiter), 
			crx_c_string_getSize(pDelimiter), pIsToAllowOverlap, pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllOccurancesOf2(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, char const * CRX_NOT_NULL pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_sub_computeIndicesOfAllOccurancesOf3(pThis, pReturn, pStartIndex, 
			pDelimiter, strlen(pDelimiter), pIsToAllowOverlap, pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllOccurancesOf3(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, char const * CRX_NOT_NULL pChars__delimiter, size_t pSize,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	if((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex == 0) ||
			(((size_t)(-1)) - 1 - pStartIndex  <= pThis->gPrivate_startIndex))
	{
		crx_c_arrays_size_empty(pReturn);

		return true;
	}
	else
	{
		return crx_c_string_computeIndicesOfAllOccurancesOf3(pThis->gPrivate_string, pReturn,
				pThis->gPrivate_startIndex + pStartIndex, pChars__delimiter, pSize, 
				pIsToAllowOverlap, pSizeOfCharacterSet);
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllOccurancesOf4(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, Crx_C_String_Sub const * CRX_NOT_NULL pSub__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	if((pSub__delimiter->gPrivate_endIndex - 
					pSub__delimiter->gPrivate_startIndex == 0))
	{
		crx_c_arrays_size_empty(pReturn);

		return true;
	}
	else
	{
		return crx_c_string_sub_computeIndicesOfAllOccurancesOf3(pThis, pReturn, pStartIndex, 
				crx_c_string_constantGetCharsPointer(pSub__delimiter->gPrivate_string) + 
						pSub__delimiter->gPrivate_startIndex, 
				pSub__delimiter->gPrivate_endIndex - 
							pSub__delimiter->gPrivate_startIndex,
				pIsToAllowOverlap, pSizeOfCharacterSet);
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllReverseOccurancesOf(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, Crx_C_String const * CRX_NOT_NULL pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_sub_computeIndicesOfAllReverseOccurancesOf3(pThis, pReturn, 
			pInclusiveEndIndex, crx_c_string_constantGetCharsPointer(pDelimiter), 
			crx_c_string_getSize(pDelimiter), pIsToAllowOverlap, pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllReverseOccurancesOf2(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, char const * CRX_NOT_NULL pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_sub_computeIndicesOfAllReverseOccurancesOf3(pThis, pReturn, 
			pInclusiveEndIndex, pDelimiter, strlen(pDelimiter), pIsToAllowOverlap, 
			pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllReverseOccurancesOf3(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, char const * CRX_NOT_NULL pChars__delimiter, size_t pSize,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	if((pThis->gPrivate_endIndex - pThis->gPrivate_startIndex == 0) ||
			(((size_t)(-1)) - 1 - pInclusiveEndIndex  <= pThis->gPrivate_startIndex))
	{
		crx_c_arrays_size_empty(pReturn);

		return true;
	}
	else
	{
		return crx_c_string_computeIndicesOfAllReverseOccurancesOf3(pThis->gPrivate_string, pReturn,
				pThis->gPrivate_startIndex + pInclusiveEndIndex, pChars__delimiter, pSize, 
				pIsToAllowOverlap, pSizeOfCharacterSet);
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllReverseOccurancesOf4(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, Crx_C_String_Sub const * CRX_NOT_NULL pSub__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	if((pSub__delimiter->gPrivate_endIndex - 
					pSub__delimiter->gPrivate_startIndex == 0))
	{
		crx_c_arrays_size_empty(pReturn);

		return true;
	}
	else
	{
		return crx_c_string_sub_computeIndicesOfAllReverseOccurancesOf3(pThis, pReturn, 
				pInclusiveEndIndex, 
				crx_c_string_constantGetCharsPointer(pSub__delimiter->gPrivate_string) +
						pSub__delimiter->gPrivate_startIndex, 
				pSub__delimiter->gPrivate_endIndex - 
						pSub__delimiter->gPrivate_startIndex,
				pIsToAllowOverlap, pSizeOfCharacterSet);
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findNextLeftTokenAndUpdateIndex(
		Crx_C_String_Sub const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, Crx_C_String const * CRX_NOT_NULL pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_sub_findNextLeftTokenAndUpdateIndex3(pThis, pReturn, pIndex,
			crx_c_string_constantGetCharsPointer(pDelimiter),
			crx_c_string_getSize(pDelimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findNextLeftTokenAndUpdateIndex2(
		Crx_C_String_Sub const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, char const * CRX_NOT_NULL pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_sub_findNextLeftTokenAndUpdateIndex3(pThis, pReturn, pIndex,
			pDelimiter, strlen(pDelimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findNextLeftTokenAndUpdateIndex3(
		Crx_C_String_Sub const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, char const * CRX_NOT_NULL pChars__delimiter, size_t pSize,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	if(pThis->gPrivate_string == NULL)
	{
		crx_c_string_sub_unsetString(pReturn);
		*pIndex = ((size_t)(-1));

		return false;
	}
	else
	{
		return crx_c_string_findNextLeftTokenAndUpdateIndex3(pThis->gPrivate_string, pReturn, 
				pIndex, pChars__delimiter, pSize, pSizeOfCharacterSet);
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findNextLeftTokenAndUpdateIndex4(
		Crx_C_String_Sub const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, 
		Crx_C_String_Sub const * CRX_NOT_NULL pSub__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_sub_findNextLeftTokenAndUpdateIndex3(pThis, pReturn, pIndex,
			crx_c_string_constantGetCharsPointer(pSub__delimiter->gPrivate_string) + 
					pSub__delimiter->gPrivate_startIndex,
			pSub__delimiter->gPrivate_endIndex - 
					pSub__delimiter->gPrivate_startIndex, 
			pSizeOfCharacterSet);
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findAllTokensStartingFromLeft(
		Crx_C_String_Sub const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, Crx_C_String const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_sub_findAllTokensStartingFromLeft3(pThis, pReturn, pIndex,
			crx_c_string_constantGetCharsPointer(pDelimiter),
			crx_c_string_getSize(pDelimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findAllTokensStartingFromLeft2(
		Crx_C_String_Sub const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, char const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_sub_findAllTokensStartingFromLeft3(pThis, pReturn, pIndex,
			pDelimiter, strlen(pDelimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findAllTokensStartingFromLeft3(
		Crx_C_String_Sub const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, char const * CRX_NOT_NULL pChars__delimiter, size_t pSize,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	if(pThis->gPrivate_string == NULL)
	{
		crx_c_string_arrays_sub_empty(pReturn);

		return false;
	}
	else
	{
		return crx_c_string_findAllTokensStartingFromLeft3(pThis->gPrivate_string, pReturn, pIndex,
				pChars__delimiter, pSize, pSizeOfCharacterSet);
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findAllTokensStartingFromLeft4(
		Crx_C_String_Sub const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, Crx_C_String_Sub const * pSub__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_sub_findAllTokensStartingFromLeft3(pThis, pReturn, pIndex,
			crx_c_string_constantGetCharsPointer(pSub__delimiter->gPrivate_string) + 
					pSub__delimiter->gPrivate_startIndex,
			pSub__delimiter->gPrivate_endIndex - 
					pSub__delimiter->gPrivate_startIndex,
			pSizeOfCharacterSet);
}


//---------------------------
//CLASS: String::Arrays_Sub
//---------------------------

CRX__C__Array__DEFINE(Crx_C_String_Arrays_Sub, crx_c_string_arrays_sub_, Crx_C_String_Sub,
		CRX__C__STRING__ARRAYS__SUB__PRIVATE__SIZE32_T, 
				CRX__C__STRING__ARRAYS__SUB__PRIVATE__SIZE32_MAX, 0, CRXM__FALSE, 
		CRXM__FALSE, CRXM__FALSE, 
		CRXM__FALSE, CRXM__FALSE)




#undef CRX__C__STRING__PRIVATE__SIZE32_MAX
#undef CRX__C__STRING__PRIVATE__IS_MEMMEM_AVAILABLE		
#undef CRX__C__STRING__ARRAYS__SUB__PRIVATE__SIZE32_T
#undef CRX__C__STRING__ARRAYS__SUB__PRIVATE__SIZE32_MAX

CRX__LIB__C_CODE_END()

