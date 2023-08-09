//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/String.h"

#include "Crx/H/crx/c/Array.h"
#include <Math.h>
//<<END>>

CRX__LIB__C_CODE_BEGIN()

#if((defined(_GNU_SOURCE ) || defined(_XOPEN_SOURCE)) && defined(__GLIBC__) && \
		(__GLIBC__ >= 2) && (__GLIBC_MINOR__ >= 1))
	#define CRX__C__STRING__PRIVATE__IS_MEMMEM_AVAILABLE CRXM__TRUE
#else
	#define CRX__C__STRING__PRIVATE__IS_MEMMEM_AVAILABLE CRXM__FALSE
#endif

CRX__C__Array__DEFINE(Crx_C_String, crx_c_string_, char, 
		uint32_t, CRX__C__STRING__PRIVATE__SIZE32_MAX, 
		16, CRXM__FALSE,
		CRXM__FALSE, CRXM__FALSE, CRXM__FALSE, CRXM__FALSE)

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_construct3(Crx_C_String * pThis, char pChar)
{
	crx_c_string_construct(pThis, 1);
	crx_c_string_push2(pThis, pChar);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_construct4(Crx_C_String * pThis, 
		char const * pString)
{
	size_t vLength = ((pString == NULL) ? 0 : strlen(pString));
	
	crx_c_string_construct(pThis, vLength);
	crx_c_string_insertCArrayAt(pThis, 0, pString, vLength);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_construct5(Crx_C_String * pThis, 
		char const * pChars, size_t pLength)
{
	size_t vLength = ((pChars == NULL) ? 0 : pLength);

	crx_c_string_construct(pThis, vLength);
	crx_c_string_insertCArrayAt(pThis, 0, pChars, vLength);
}


CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String * crx_c_string_new3(char pChar)
{
	Crx_C_String * vString = crx_c_string_new(1);
	
	if(vString != NULL)
		{crx_c_string_push2(vString, pChar);}
	
	return vString;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String * crx_c_string_new4(char const * pString)
{
	size_t vLength = ((pString == NULL) ? 0 : strlen(pString));
	Crx_C_String * vString = crx_c_string_new(vLength);
	
	if(vString != NULL)
		{crx_c_string_insertCArrayAt(vString, 0, pString, vLength);}
	
	return vString;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String * crx_c_string_new5(char const * pChars, size_t pLength)
{
	size_t vLength = ((pChars == NULL) ? 0 : pLength);
	Crx_C_String * vString = crx_c_string_new(vLength);
	
	if(vString != NULL)
		{crx_c_string_insertCArrayAt(vString, 0, pChars, vLength);}
	
	return vString;
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendString(Crx_C_String * pThis, 
		Crx_C_String const * pString)
{
	if(pString == NULL)
		{return true;}

	return crx_c_string_insertElementsAt(pThis, crx_c_string_getLength(pThis), pString, 0,
			crx_c_string_getLength(pString));
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendChar(Crx_C_String * pThis, char pChar)
	{return crx_c_string_push2(pThis, pChar);}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendString2(Crx_C_String * pThis, 
		char const * pString)
{
	if(pString == NULL)
		{return true;}

	return crx_c_string_insertCArrayAt(pThis, crx_c_string_getLength(pThis), pString, strlen(pString));
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendChars(Crx_C_String * pThis, char const * pChars, size_t pLength)
{
	if(pChars == NULL)
		{return true;}

	return crx_c_string_insertCArrayAt(pThis, crx_c_string_getLength(pThis), pChars, pLength);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendWideChars(Crx_C_String * pThis, 
		wchar_t const * pWchars, size_t pLength)
{
	if(pWchars == NULL)
		{return true;}

	return crx_c_string_insertCArrayAt(pThis, crx_c_string_getLength(pThis), 
			(char const *)pWchars, pLength * sizeof(wchar_t));
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendInt(Crx_C_String * pThis, int32_t pInt)
{
	char vChars[100] /*= ?*/;
	
	sprintf(vChars, "%d", pInt);
	
	return crx_c_string_appendString2(pThis, vChars);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendInt2(Crx_C_String * pThis, 
		unsigned int pNumberOfDigits, int32_t pInt)
{
	if(pNumberOfDigits < 50)
	{
		char vChars[100] /*= ?*/;
	
		sprintf(vChars, "%.*d", pNumberOfDigits, pInt);
	
		return crx_c_string_appendString2(pThis, vChars);
	}
	else
	{
		size_t tCurrentLength = crx_c_string_getLength(pThis);
		size_t tAvailableSpace = crx_c_string_getCapacity(pThis) - tCurrentLength;

		if((tAvailableSpace < (pNumberOfDigits + 50)) || 
				crx_c_string_ensureCapacity(pThis, tCurrentLength + 50 + pNumberOfDigits))
		{
			crx_c_string_insertElementCopiesAt2(pThis, tCurrentLength, '\0', 51 + pNumberOfDigits);

			sprintf(crx_c_string_getElementsPointer(pThis) + tCurrentLength, "%.*d", pNumberOfDigits,
					pInt);

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
	
	return crx_c_string_appendString2(pThis, vChars);
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEmpty(Crx_C_String const * pThis)
{
	if(crx_c_string_getLength(pThis) == 0)
		{return true;}

	CRX_FOR(size_t tI = 0, tI < crx_c_string_getLength(pThis), tI++)
	{
		if(!(((crx_c_string_copyGet(pThis, tI) >= 0) && (crx_c_string_copyGet(pThis, tI) <= 32)) || 
				(crx_c_string_copyGet(pThis, tI) == 127)))
			{return true;}
	}
	CRX_ENDFOR

	return false;
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEqualTo(Crx_C_String const * pThis,
		Crx_C_String const * pString)
{
	return ((crx_c_string_getLength(pThis) == crx_c_string_getLength(pString)) &&
			(memcmp(crx_c_string_constantGetElementsPointer(pThis),
					crx_c_string_constantGetElementsPointer(pString),
					crx_c_string_getLength(pString)) == 0));
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEqualTo2(Crx_C_String const * pThis,
		char const * pString)
{
	return (strncmp(crx_c_string_constantGetElementsPointer(pThis), pString,
					crx_c_string_getLength(pThis)) == 0);
}

CRX__LIB__PUBLIC_C_FUNCTION() char const * crx_c_string_getCString(Crx_C_String * pThis)
{
	if(crx_c_string_ensureCapacity(pThis, crx_c_string_getLength(pThis) + 4))
	{
		char * tChars = crx_c_string_unsafeGetCArray(pThis); //crx_c_string_getElementsPointer(pThis);

		if(tChars != NULL)
		{
			size_t tLength = crx_c_string_getLength(pThis);

			*(tChars + tLength) = '\0';
			*(tChars + tLength + 1) = '\0';
			*(tChars + tLength + 2) = '\0';
			*(tChars + tLength + 3) = '\0';
		}
		
		return tChars;
	}
	else
		{return NULL;}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isBeginningWith(Crx_C_String const * pThis,
		Crx_C_String const * pString)
{
	return crx_c_string_isBeginningWith3(pThis, crx_c_string_constantGetElementsPointer(pString),
			crx_c_string_getLength(pString));
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isBeginningWith2(Crx_C_String const * pThis,
		char const * pString)
	{return crx_c_string_isBeginningWith3(pThis, pString, strlen(pString));}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isBeginningWith3(Crx_C_String const * pThis,
		char const * pChars, size_t pLength)
{
	if(crx_c_string_getLength(pThis) < pLength)
		{return false;}
	else
		{return (memcmp(crx_c_string_constantGetElementsPointer(pThis), pChars, pLength) == 0);}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEndingWith(Crx_C_String const * pThis,
		Crx_C_String const * pString)
{
	return crx_c_string_isEndingWith3(pThis, crx_c_string_constantGetElementsPointer(pString),
			crx_c_string_getLength(pString));
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEndingWith2(Crx_C_String const * pThis,
		char const * pString)
	{return crx_c_string_isEndingWith3(pThis, pString, strlen(pString));}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEndingWith3(Crx_C_String const * pThis,
		char const * pChars, size_t pLength)
{
	if(crx_c_string_getLength(pThis) < pLength)
		{return false;}
	else
	{
		return (memcmp(crx_c_string_constantGetElementsPointer(pThis) + 
				crx_c_string_getLength(pThis) - pLength, pChars, pLength) == 0);
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_lowerTheCase(Crx_C_String * pThis)
{
	char * vChars = crx_c_string_unsafeGetCArray(pThis);
	char * vChars__end = vChars + crx_c_string_getLength(pThis);

	while(vChars != vChars__end)
	{
		if((*vChars >= 65) && (*vChars <= 90))
			{*vChars = *vChars + 32;}

		vChars++;
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_upperTheCase(Crx_C_String * pThis)
{
	char * vChars = crx_c_string_unsafeGetCArray(pThis);
	char * vChars__end = vChars + crx_c_string_getLength(pThis);

	while(vChars != vChars__end)
	{
		if((*vChars >= 97) && (*vChars <= 122))
			{*vChars = *vChars - 32;}

		vChars++;
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_trim(Crx_C_String * pThis)
{
	char * vChars = crx_c_string_unsafeGetCArray(pThis);
	char * vChars__end = vChars + crx_c_string_getLength(pThis);
	size_t vStartIndex = 0;

	while((vChars != vChars__end) && (((*vChars >= 9) && (*vChars <= 13)) ||
			(*vChars == 32)))
	{
		vChars++;
		vStartIndex++;
	}
	
	if(vChars != vChars__end)
	{
		size_t tEndIndex = crx_c_string_getLength(pThis);

		while((vChars__end != vChars) && (((*vChars__end >= 9) && (*vChars__end <= 13)) ||
				(*vChars__end == 32)))
		{
			vChars__end--;
			tEndIndex--;
		}

		crx_c_string_unsafeUpdateLength(pThis, tEndIndex);
		crx_c_string_removeElements(pThis, 0, tEndIndex - vStartIndex);
	}
	else
		{crx_c_string_unsafeUpdateLength(pThis, 0);}
}

#if(0)
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_splitAndGet(Crx_C_String const * pThis, 
		Crx_C_Arrays_String * CRX_NOT_NULL pReturn, char const * pDelimiter, size_t pLength)
{
	/*
	NOTE: GIVEN A STRING[1..N], THE Nth SUFFIX PREFIX IS THE Nth LARGEST PREFIX OF THE STRING
			THAT IS ALSO ITS SUFFIX. THE LARGEST SUFFIX PREFIX IS THE STRING ITSELF. IN OTHER
			WORDS:
					SUFFIX_PREFIX{n}(STRING) = STRING[N-K+1..N] = STRING[1..K]  ; K IS THE LENGTH OF
							THE nth LARGEST SUFFIX PREFIX.
			NOTE THAT THE LENGTH OF STRING[X..Y] IS Y - X + 1. IN OTHER WORDS
							|STRING[N-K+1..N]| = K
			
			WE ARE FOR THE ALGOIRTHM ONLY INTERESTED IN THE SECOND LARGEST SUFFIC PREFIX.
			
			NOTE THAT IF FOR SUBSTRING STRING[A..B], 
					|SUFFIX_PREFIX{2}(STRING[A..B])| = K, 
			THEN FOR SUBSTRING STRING[A..B+1] 
					|SUFFIX_PREFIX{2}(STRING[A..B+1])| <= K + 1
			BECAUSE OTHERWISE THIS SUFFIX PREFIX WOULD START AT (A-L) FOR L > 0, MAKING IT A 
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
	CRX_SCOPE_META
	if((crx_c_string_getLength(pThis) < pLength) || (crx_c_string_getLength(pThis) == 0) ||
			(pLength == 0))
		{return false;}

	CRX_SCOPE
	size_t vLength = crx_c_string_getLength(pThis);
	size_t * vSecondLargestSuffixPrefixForSubDelimiterUpToIndex = calloc(1, sizeof(size_t) * (pLength + 1)); //ACTUAL VALUE AT i IS vBackTrackValues[i] - 1
	size_t vCurrentIndexInDelimiter = 0;
	
	crx_c_arrays_string_empty(pReturn);

#if(CRX__C__STRING__PRIVATE__IS_MEMMEM_AVAILABLE)
	return memmem(crx_c_string_constantGetElementsPointer(pThis), vLength, pDelimiter, pLength);
#else
    vSecondLargestSuffixPrefixForSubDelimiterUpToIndex[0] = 0;

    CRX_FOR(size_t tI = 1; tI < pLength; tI++)
	{        
        size_t tJ = vSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tI - 1];

		//IF SECOND LARGEST SUFFIX PREFIX DOES NOT HELP, WE SEEK OUT THE THIRD LARGEST
		//		SUFFIX PREFIX WHICH HAPPENS TO BE THE SECOND LARGEST SUFFIX PREFIX OF THE
		//		SECOND LARGEST SUFFIX PREFIX. AND SO FORTH.
        while((tJ != 0) && (*(pDelimiter + tI) != *(pDelimiter + tJ)))
			{tJ = vSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tJ - 1];}

        if(*(pDelimiter + tI) == *(pDelimiter + tJ))
			{tJ += 1;}

        vSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tI] = tJ;
	}
	CRX_ENDFOR

	vCurrentIndexInDelimiter = 0;
	CRX_FOR(size_t tI = 0; tI < vLength; tI++)
	{        
        while((vCurrentIndexInDelimiter != 0) && (a[tI] != b[vCurrentIndexInDelimiter]))
		{
			//SEE * ABOVE.
			vCurrentIndexInDelimiter = 
					vSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
					vCurrentIndexInDelimiter - 1];
		}
        
        if(a[tI] == b[vCurrentIndexInDelimiter])
			{vCurrentIndexInDelimiter += 1;}

        # invariant formally defined below
        assert a[tI + 1 - vCurrentIndexInDelimiter:tI + 1] == b[0:vCurrentIndexInDelimiter]

        if(vCurrentIndexInDelimiter == n)
			{return tI + 1 - n;}
	}
	CRX_ENDFOR
    
	CRX_SCOPE_END
#endif
}
#endif

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstOccuranceOf(
		Crx_C_String const * pThis, size_t pStartIndex, Crx_C_String const * pString__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_getIndexOfFirstOccuranceOf3(pThis, pStartIndex,
			crx_c_string_constantGetElementsPointer(pString__delimiter),
			crx_c_string_getLength(pString__delimiter),
			pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstOccuranceOf2(
		Crx_C_String const * pThis, size_t pStartIndex, char const * pString__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_getIndexOfFirstOccuranceOf3(pThis, pStartIndex,
			pString__delimiter, strlen(pString__delimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstOccuranceOf3(
		Crx_C_String const * pThis, size_t pStartIndex, char const * pDelimiter, 
		size_t pLength, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	CRX_SCOPE_META
	if(((crx_c_string_getLength(pThis) - pStartIndex) < pLength) || 
			(crx_c_string_getLength(pThis) <= pStartIndex) || (pLength == 0))
		{return crx_c_string_getLength(pThis);}

	CRX_SCOPE
	uint32_t vAlgorithm = 0;
	uint8_t vSizeOfCharacterSet = ((pSizeOfCharacterSet == 0) ? 255 : pSizeOfCharacterSet);
	size_t vFullLength = crx_c_string_getLength(pThis);
	size_t vLength = vFullLength - pStartIndex;
	char const * vChars = crx_c_string_constantGetElementsPointer(pThis) + pStartIndex;
	size_t vReturn = vFullLength;
#if(CRX__C__STRING__PRIVATE__IS_MEMMEM_AVAILABLE)
	char * vChars__startOfFoundOccurance = NULL;
#endif
	

#if(CRX__C__STRING__PRIVATE__IS_MEMMEM_AVAILABLE)
	vChars__startOfFoundOccurance = memmem(vChars, vLength, pDelimiter, pLength);

	if(vChars__startOfFoundOccurance != NULL)
		{vReturn = vChars__startOfFoundOccurance - vChars;}
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
	//		FIRST OCCURANCE SEARCH.
	if(pLength <= 8)
		{vAlgorithm = 1;}
	else if(pLength < 32768)
		if(vSizeOfCharacterSet > 16)
			{vAlgorithm = 4;}
		else
			{vAlgorithm = 1;}
	else
		{vAlgorithm = 4;}
	
	if(vAlgorithm == 1)
	{
		char const * tChar = vChars;
		char const * tEndChar = vChars + (vLength - pLength + 1);

		while(tChar < tEndChar)
		{
			tChar = memchr(tChar, *pDelimiter, tEndChar - tChar);

			if(tChar != NULL)
			{
				if(memcmp(tChar, pDelimiter, pLength) == 0)
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
				
				WE ARE FOR THE ALGOIRTHM ONLY INTERESTED IN THE SECOND LARGEST SUFFIC PREFIX.
				
				NOTE THAT IF FOR SUBSTRING STRING[A..B], 
						|SUFFIX_PREFIX{2}(STRING[A..B])| = K, 
				THEN FOR SUBSTRING STRING[A..B+1] 
						|SUFFIX_PREFIX{2}(STRING[A..B+1])| <= K + 1
				BECAUSE OTHERWISE THIS SUFFIX PREFIX WOULD START AT (A-L) FOR L > 0, MAKING IT A 
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
		
		if(pLength + 1 > 80)
		{
			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
					calloc(1, sizeof(size_t) * (pLength + 1));
			tIsToFree = true;
		}
		else
		{
			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
					CRX__ALLOCA(sizeof(size_t) * (pLength + 1));
		}
		
		tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[0] = 0;
		CRX_FOR(size_t tI = 1, tI < pLength, tI++)
		{        
			size_t tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tI - 1];

			//IF SECOND LARGEST SUFFIX PREFIX DOES NOT HELP, WE SEEK OUT THE THIRD LARGEST
			//		SUFFIX PREFIX WHICH HAPPENS TO BE THE SECOND LARGEST SUFFIX PREFIX OF THE
			//		SECOND LARGEST SUFFIX PREFIX. AND SO FORTH.
			while((tJ != 0) && (*(pDelimiter + tI) != *(pDelimiter + tJ)))
				{tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tJ - 1];}

			if(*(pDelimiter + tI) == *(pDelimiter + tJ))
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
						(*(vChars + tI) != *(pDelimiter + tCurrentIndexInDelimiter)))
				{
					//SEE * ABOVE.
					tCurrentIndexInDelimiter = 
							tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
							tCurrentIndexInDelimiter - 1];
				}
				
				if(*(vChars + tI) == *(pDelimiter + tCurrentIndexInDelimiter))
					{tCurrentIndexInDelimiter += 1;}

				/*
					AT THIS POINT, THE FOLLOWING MUST ALWAYS HOLD TRUE
							vChars[tI + 1 - tCurrentIndexInDelimiter:tI + 1] == 
									pDelimiter[0:tCurrentIndexInDelimiter]
					IN OTHER WORDS, THE WINDOW, pDelimiter[0:tCurrentIndexInDelimiter], IS ALWAYS VALID, 
					ALWAYS EQUAL TO THE OVERLAP EVEN AFTER SHIFTING.
				*/

				if(tCurrentIndexInDelimiter == pLength)
				{
					vReturn = tI + 1 - pLength;

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
			char tLastCharacter = *(pDelimiter + pLength - 1);
			
			CRX_FOR(size_t tI = 0, tI < 256, tI++)
				{tReverseIndexOfCharacterLastOccurance[tI] = (uint32_t)pLength;}
			CRX_ENDFOR

			CRX_FOR(size_t tI = 0, tI < pLength, tI++)
			{
				if(tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pDelimiter)  + tI)] > (pLength - tI - 1))
					{tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pDelimiter)  + tI)] = pLength - tI - 1;}
			}
			CRX_ENDFOR
			
			CRX_FOR(size_t tI = 0, tI < vLength, tI++)
			{
				if(tCurrentIndexInDelimiter == 0)
				{
					while((tI <= vLength - pLength) && (*(vChars + tI + pLength - 1) != tLastCharacter))
						{tI = tI + tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)vChars) + tI + pLength - 1)];}
				}
				else
				{
					while((tCurrentIndexInDelimiter != 0) && 
							(*(vChars + tI) != *(pDelimiter + tCurrentIndexInDelimiter)))
					{
						//SEE * ABOVE.
						tCurrentIndexInDelimiter = 
								tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
								tCurrentIndexInDelimiter - 1];
					}
				}


				if(*(vChars + tI) == *(pDelimiter + tCurrentIndexInDelimiter))
					{tCurrentIndexInDelimiter += 1;}

				/*SEE ABOVE*/
				if(tCurrentIndexInDelimiter == pLength)
				{
					vReturn = tI + 1 - pLength;

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
		unsigned char const * tEndChar = vChars + (vLength - pLength) + 1;
		unsigned char tLastCharacter = *(pDelimiter + pLength - 1);
		uint32_t tReverseIndexOfCharacterLastOccurance[256] /*= ?*/;

		CRX_FOR(size_t tI = 0, tI < 256, tI++)
			{tReverseIndexOfCharacterLastOccurance[tI] = (uint32_t)pLength;}
		CRX_ENDFOR
		
		CRX_FOR(size_t tI = 0, tI < pLength, tI++)
		{
			if(tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pDelimiter)  + tI)] > (pLength - tI - 1))
				{tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pDelimiter)  + tI)] = pLength - tI - 1;}
		}
		CRX_ENDFOR

		while(tChar < tEndChar)
		{
			tChar = memchr(tChar, *pDelimiter, tEndChar - tChar);

			if(tChar != NULL)
			{
				while((tChar < tEndChar) && (*(tChar + pLength - 1) != tLastCharacter))
				{
					tChar = tChar + 
							tReverseIndexOfCharacterLastOccurance[*(tChar + pLength - 1)];
				}

				if(tChar < tEndChar)
				{
					if(memcmp(tChar, pDelimiter, pLength) == 0)
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
		CRX_FOR(size_t tI = 0, tI <= vLength - pLength, tI++)
		{
			bool tIsFound = true;

			CRX_FOR(size_t tI2 = 0, tI2 < pLength, tI2++)
			{
				if(*(vChars + tI + tI2) != *(pDelimiter + tI2))
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
		vReturn = TW(pDelimiter, pLength, vChars, vLength);
		
		if(vReturn == vLength)
			{vReturn = vFullLength;}
	}
	else if(vAlgorithm == 7)
	{
		/*
		TWO WAY SEARCH ALGORITHM. SEE PAPER. THE LETTERS IN COMMENT IS TO HELP COMPARE CODE
		TO ALOGIRHTMS IN THE PAPER. 
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
		//pLength //n
		while(tI2 + tOffset <= pLength)
		{
			char tChar = *(pDelimiter + tI + tOffset - 1);
			char tChar2 = *(pDelimiter + tI2 + tOffset - 1);

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
		//pLength //n

		while(tI2 + tOffset <= pLength)
		{
			char tChar = *(pDelimiter + tI + tOffset - 1);
			char tChar2 = *(pDelimiter + tI2 + tOffset - 1);

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
		
		if((tCriticalPosition < (pLength >> 1)) && 
				(memcmp(pDelimiter, pDelimiter + tPotentialPeriod, tCriticalPosition) == 0))
		{
			//BASED ON POSITIONS() FUNCTION IN THE PAPER.
			size_t tPeriod = tPotentialPeriod; //p
			size_t tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;//s
			
			tI2 = 0;//pos
			//tI //i
			//tCriticalPosition //l
			//vLength //|t|
			//pLength //|x|
			
			while(tI2 + pLength <= vLength)
			{
				//assert(pDelimiter[1 : tUpperBoundOfAlreadyVerifiedValuesOnRight] = 
				//		vChars[tI2 + 1 : tI2 + tUpperBoundOfAlreadyVerifiedValuesOnRight]) //right side is exclusive.

				tI = ((tCriticalPosition < tUpperBoundOfAlreadyVerifiedValuesOnRight) ? 
						tUpperBoundOfAlreadyVerifiedValuesOnRight : tCriticalPosition) + 1;
				
				while((tI <= pLength) && (*(pDelimiter + tI - 1) == *(vChars + tI2 + tI - 1)))
					{tI++;}

				if(tI <= pLength)
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
							(*(pDelimiter + tJ - 1) == *(vChars + tI2 + tJ - 1)))
						{tJ = tJ - 1;}

					if(tJ <= tUpperBoundOfAlreadyVerifiedValuesOnRight)
					{
						vReturn = tI2;
						break;
					}
					else 	//IF YOU REMOVE THE break ABOVE, MEANING YOU WANT TO FIND ALL OCCURANCES,
							//	THE FOLLOWING CODE MUST ALWAYS RUN. IN THAT CASE, IF YOU WANT TO FIND
							//	NON OVERLAPPING OCCURANCES AND A MATCH IS FOUND, YOU WOULD INCRMENT 
							//	BY pLength INSTEAD OF tPeriod AND SET tUpperBoundOfAlreadyVerifiedValuesOnRight
							//	TO ZERO, OTHERWISE BY tPeriod AND SET tUpperBoundOfAlreadyVerifiedValuesOnRight
							//	TO pLength - tPeriod, OR IF YOU DO WANT TO FIND OVERLAPPING OCCURANCES, 
							//	YOU WOULD ALWAYS INCREMENT BY tPeriod AND SET 
							//	tUpperBoundOfAlreadyVerifiedValuesOnRight TO pLength - tPeriod
					{
						tI2 = tI2 + tPeriod;
						tUpperBoundOfAlreadyVerifiedValuesOnRight = pLength - tPeriod;
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
			size_t tPeriodLowerBound = ((tCriticalPosition >= pLength - tCriticalPosition) ?
					tCriticalPosition : pLength - tCriticalPosition) + 1; //p OR q IN THE FINAL FORM
			
			tI2 = 0;//pos
			//tI //i
			//tCriticalPosition //l
			//vLength //|t|
			//pLength //|x|

			while(tI2 + pLength <= vLength)
			{
				tI = tCriticalPosition + 1;
				
				while((tI <= pLength) && (*(pDelimiter + tI - 1) == *(vChars + tI2 + tI - 1)))
					{tI++;}

				if(tI <= pLength)
					{tI2 = tI2 + tI - tCriticalPosition;}
				else
				{
					size_t tJ = tCriticalPosition; //ONE BASED INDEX

					while((tJ > 0) && (*(pDelimiter + tJ - 1) == *(vChars + tI2 + tJ - 1)))
						{tJ = tJ - 1;}

					if(tJ == 0)
					{
						vReturn = tI2;
						break;
					}
					else 	//IF YOU REMOVE THE break ABOVE, MEANING YOU WANT TO FIND ALL OCCURANCES,
							//	THE FOLLOWING CODE MUST ALWAYS RUN. IN THAT CASE, IF YOU WANT TO FIND
							//	NON OVERLAPPING OCCURANCES AND A MATCH IS FOUND, YOU WOULD INCRMENT 
							//	BY pLength INSTEAD OF tPeriodLowerBound, OTHERWISE BY tPeriodLowerBound,
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
    
	return ((vReturn != vFullLength) ? (vReturn + pStartIndex) : vFullLength);
	CRX_SCOPE_END
#endif
}


CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstReverseOccuranceOf(
		Crx_C_String const * pThis, size_t pInclusiveEndIndex, Crx_C_String const * pString__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_getIndexOfFirstReverseOccuranceOf3(pThis, pInclusiveEndIndex,
			crx_c_string_constantGetElementsPointer(pString__delimiter),
			crx_c_string_getLength(pString__delimiter),
			pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstReverseOccuranceOf2(
		Crx_C_String const * pThis, size_t pInclusiveEndIndex, char const * pString__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_getIndexOfFirstReverseOccuranceOf3(pThis, pInclusiveEndIndex,
			pString__delimiter, strlen(pString__delimiter), pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstReverseOccuranceOf3(
		Crx_C_String const * pThis, size_t pInclusiveEndIndex, char const * pDelimiter, 
		size_t pLength, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
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
	if((pInclusiveEndIndex < pLength - 1) || 
			(pInclusiveEndIndex >= crx_c_string_getLength(pThis)) || (pLength == 0))
		{return crx_c_string_getLength(pThis);}

	CRX_SCOPE
	uint32_t vAlgorithm = 0;
	uint8_t vSizeOfCharacterSet = ((pSizeOfCharacterSet == 0) ? 255 : pSizeOfCharacterSet);
	size_t vFullLength = crx_c_string_getLength(pThis);
	size_t vLength = pInclusiveEndIndex + 1;
	char const * vChars = crx_c_string_constantGetElementsPointer(pThis);
	size_t vReturn = vFullLength;
	

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
	//		FIRST OCCURANCE SEARCH.
	/*if(pLength <= 8)
		{vAlgorithm = 8;}
	else if(pLength < 32768)
		if(vSizeOfCharacterSet > 16)
			{vAlgorithm = 8;}
		else
			{vAlgorithm = 8;}
	else
		{vAlgorithm = 8;}*/
	
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
				
				WE ARE FOR THE ALGOIRTHM ONLY INTERESTED IN THE SECOND LARGEST SUFFIC PREFIX.
				
				NOTE THAT IF FOR SUBSTRING STRING[A..B], 
						|SUFFIX_PREFIX{2}(STRING[A..B])| = K, 
				THEN FOR SUBSTRING STRING[A..B+1] 
						|SUFFIX_PREFIX{2}(STRING[A..B+1])| <= K + 1
				BECAUSE OTHERWISE THIS SUFFIX PREFIX WOULD START AT (A-L) FOR L > 0, MAKING IT A 
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
		
		if(pLength + 1 > 80)
		{
			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
					calloc(1, sizeof(size_t) * (pLength + 1));
			tIsToFree = true;
		}
		else
		{
			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
					CRX__ALLOCA(sizeof(size_t) * (pLength + 1));
		}
		
		tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[0] = 0;
		CRX_FOR(size_t tI = 1, tI < pLength, tI++)
		{        
			size_t tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[pLength - 1 - (tI - 1)];

			//IF SECOND LARGEST SUFFIX PREFIX DOES NOT HELP, WE SEEK OUT THE THIRD LARGEST
			//		SUFFIX PREFIX WHICH HAPPENS TO BE THE SECOND LARGEST SUFFIX PREFIX OF THE
			//		SECOND LARGEST SUFFIX PREFIX. AND SO FORTH.
			while((tJ != 0) && (*(pDelimiter + pLength - 1 - tI) != *(pDelimiter + pLength - 1 - tJ)))
				{tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tJ - 1];}

			if(*(pDelimiter + pLength - 1 - tI) == *(pDelimiter + pLength - 1 - tJ))
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
						(*(vChars + vLength - 1 - tI) != *(pDelimiter + pLength - 1 - tCurrentIndexInDelimiter)))
				{
					//SEE * ABOVE.
					tCurrentIndexInDelimiter = 
							tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
							tCurrentIndexInDelimiter - 1];
				}
				
				if(*(vChars + vLength - 1 - tI) == *(pDelimiter + pLength - 1 - tCurrentIndexInDelimiter))
					{tCurrentIndexInDelimiter += 1;}

				/*
					AT THIS POINT, THE FOLLOWING MUST ALWAYS HOLD TRUE
							vChars[tI + 1 - tCurrentIndexInDelimiter:tI + 1] == 
									pDelimiter[0:tCurrentIndexInDelimiter]
					IN OTHER WORDS, THE WINDOW, pDelimiter[0:tCurrentIndexInDelimiter], IS ALWAYS VALID, 
					ALWAYS EQUAL TO THE OVERLAP EVEN AFTER SHIFTING.
				*/

				if(tCurrentIndexInDelimiter == pLength)
				{
					vReturn = vLength - 1 - tI;//== vLength - 1 - (tI + 1 - pLength) - (pLength - 1)

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
			char tLastCharacter = *pDelimiter;
			
			CRX_FOR(size_t tI = 0, tI < 256, tI++)
				{tReverseIndexOfCharacterLastOccurance[tI] = (uint32_t)pLength;}
			CRX_ENDFOR

			CRX_FOR(size_t tI = 0, tI < pLength, tI++)
			{
				if(tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pDelimiter) + pLength - 1 - tI)] > (pLength - tI - 1))
					{tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pDelimiter) + pLength - 1 - tI)] = pLength - tI - 1;}
			}
			CRX_ENDFOR
			
			CRX_FOR(size_t tI = 0, tI < vLength, tI++)
			{
				if(tCurrentIndexInDelimiter == 0)
				{
					while((tI <= vLength - pLength) && (*(vChars + vLength - 1 - (tI + pLength - 1)) != tLastCharacter))
						{tI = tI + tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)vChars) + vLength - 1 - (tI + pLength - 1))];}
				}
				else
				{
					while((tCurrentIndexInDelimiter != 0) && 
							(*(vChars + vLength - 1 - tI) != *(pDelimiter + pLength - 1 - tCurrentIndexInDelimiter)))
					{
						//SEE * ABOVE.
						tCurrentIndexInDelimiter = 
								tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
								tCurrentIndexInDelimiter - 1];
					}
				}


				if(*(vChars + vLength - 1 - tI) == *(pDelimiter + pLength - 1 - tCurrentIndexInDelimiter))
					{tCurrentIndexInDelimiter += 1;}

				/*SEE ABOVE*/
				if(tCurrentIndexInDelimiter == pLength)
				{
					vReturn = vLength - 1 - tI; //vLength - 1 - (tI + 1 - pLength) - (pLength - 1)

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
		CRX_FOR(size_t tI = 0, tI <= vLength - pLength, tI++)
		{
			bool tIsFound = true;

			CRX_FOR(size_t tI2 = 0, tI2 < pLength, tI2++)
			{
				if(*(vChars + vLength - 1 - tI - tI2) != *(pDelimiter + pLength - 1 - tI2))
				{
					tIsFound = false;
					break;
				}
			}
			CRX_ENDFOR
					
			if(tIsFound)
			{
				vReturn = vLength - tI - pLength;//vLength - 1 - tI - (pLength - 1)
				break;
			}
		}
		CRX_ENDFOR
	}
	else if(vAlgorithm == 7)
	{
		/*
		TWO WAY SEARCH ALGORITHM. SEE PAPER. THE LETTERS IN COMMENT IS TO HELP COMPARE CODE
		TO ALOGIRHTMS IN THE PAPER. 
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
		//pLength //n
		while(tI2 + tOffset <= pLength)
		{
			char tChar = *(pDelimiter + pLength - 1 - (tI + tOffset - 1));
			char tChar2 = *(pDelimiter + pLength - 1 - (tI2 + tOffset - 1));

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
		//pLength //n

		while(tI2 + tOffset <= pLength)
		{
			char tChar = *(pDelimiter + pLength - 1 - (tI + tOffset - 1));
			char tChar2 = *(pDelimiter + pLength - 1 - (tI2 + tOffset - 1));

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
		
		if((tCriticalPosition < (pLength >> 1)) && 
				(memcmp(pDelimiter + pLength - 1 - (tCriticalPosition - 1), pDelimiter + pLength - 1 - tPotentialPeriod - (tCriticalPosition - 1), tCriticalPosition) == 0))
		{
			//BASED ON POSITIONS() FUNCTION IN THE PAPER.
			size_t tPeriod = tPotentialPeriod; //p
			size_t tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;//s
			
			tI2 = 0;//pos
			//tI //i
			//tCriticalPosition //l
			//vLength //|t|
			//pLength //|x|
			
			while(tI2 + pLength <= vLength)
			{
				//assert(pDelimiter[1 : tUpperBoundOfAlreadyVerifiedValuesOnRight] = 
				//		vChars[tI2 + 1 : tI2 + tUpperBoundOfAlreadyVerifiedValuesOnRight]) //right side is exclusive.

				tI = ((tCriticalPosition < tUpperBoundOfAlreadyVerifiedValuesOnRight) ? 
						tUpperBoundOfAlreadyVerifiedValuesOnRight : tCriticalPosition) + 1;
				
				while((tI <= pLength) && (*(pDelimiter + pLength - 1 - (tI - 1)) == *(vChars + vLength - 1 - (tI2 + tI - 1))))
					{tI++;}

				if(tI <= pLength)
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
							(*(pDelimiter + pLength - 1 - (tJ - 1)) == *(vChars + vLength - 1 - (tI2 + tJ - 1))))
						{tJ = tJ - 1;}

					if(tJ <= tUpperBoundOfAlreadyVerifiedValuesOnRight)
					{
						vReturn = vLength - 1 - tI2 - (pLength - 1);
						break;
					}
					else 	//IF YOU REMOVE THE break ABOVE, MEANING YOU WANT TO FIND ALL OCCURANCES,
							//	THE FOLLOWING CODE MUST ALWAYS RUN. IN THAT CASE, IF YOU WANT TO FIND
							//	NON OVERLAPPING OCCURANCES AND A MATCH IS FOUND, YOU WOULD INCRMENT 
							//	BY pLength INSTEAD OF tPeriod AND SET tUpperBoundOfAlreadyVerifiedValuesOnRight
							//	TO ZERO, OTHERWISE BY tPeriod AND SET tUpperBoundOfAlreadyVerifiedValuesOnRight
							//	TO pLength - tPeriod, OR IF YOU DO WANT TO FIND OVERLAPPING OCCURANCES, 
							//	YOU WOULD ALWAYS INCREMENT BY tPeriod AND SET 
							//	tUpperBoundOfAlreadyVerifiedValuesOnRight TO pLength - tPeriod
					{
						tI2 = tI2 + tPeriod;
						tUpperBoundOfAlreadyVerifiedValuesOnRight = pLength - tPeriod;
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
			size_t tPeriodLowerBound = ((tCriticalPosition >= pLength - tCriticalPosition) ?
					tCriticalPosition : pLength - tCriticalPosition) + 1; //p OR q IN THE FINAL FORM
			
			tI2 = 0;//pos
			//tI //i
			//tCriticalPosition //l
			//vLength //|t|
			//pLength //|x|

			while(tI2 + pLength <= vLength)
			{
				tI = tCriticalPosition + 1;
				
				while((tI <= pLength) && (*(pDelimiter + pLength - 1 - (tI - 1)) == *(vChars + vLength - 1 - (tI2 + tI - 1))))
					{tI++;}

				if(tI <= pLength)
					{tI2 = tI2 + tI - tCriticalPosition;}
				else
				{
					size_t tJ = tCriticalPosition; //ONE BASED INDEX

					while((tJ > 0) && (*(pDelimiter + pLength - 1 - (tJ - 1)) == *(vChars + vLength - 1 - (tI2 + tJ - 1))))
						{tJ = tJ - 1;}

					if(tJ == 0)
					{
						vReturn = vLength - 1 - tI2 - (pLength - 1);
						break;
					}
					else 	//IF YOU REMOVE THE break ABOVE, MEANING YOU WANT TO FIND ALL OCCURANCES,
							//	THE FOLLOWING CODE MUST ALWAYS RUN. IN THAT CASE, IF YOU WANT TO FIND
							//	NON OVERLAPPING OCCURANCES AND A MATCH IS FOUND, YOU WOULD INCRMENT 
							//	BY pLength INSTEAD OF tPeriodLowerBound, OTHERWISE BY tPeriodLowerBound,
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
		size_t tEndIndex = pLength - 1; //One based index
		unsigned char tFirstCharacter = *pDelimiter;
		unsigned char tLastCharacter = *(pDelimiter + pLength - 1);
		uint32_t tIndexOfCharacterFirstOccurance[256] /*= ?*/;
		size_t vI = vLength; //One based index

		CRX_FOR(size_t tI = 0, tI < 256, tI++)
			{tIndexOfCharacterFirstOccurance[tI] = (uint32_t)pLength;}
		CRX_ENDFOR
		
		CRX_FOR(size_t tI = 0, tI < pLength, tI++)
		{
			if(tIndexOfCharacterFirstOccurance[*(((unsigned char const *)pDelimiter)  + tI)] > tI)
				{tIndexOfCharacterFirstOccurance[*(((unsigned char const *)pDelimiter)  + tI)] = tI;}
		}
		CRX_ENDFOR

		while(vI > tEndIndex)
		{
			while((vI > tEndIndex) && (*(vChars + vI - 1) != tLastCharacter))
				{vI--;}

			if(vI > tEndIndex)
			{
				while((vI > tEndIndex) && (*(tChars + vI - pLength) != tFirstCharacter))
					{vI = vI - tIndexOfCharacterFirstOccurance[*(tChars + vI - pLength)];}

				if(vI > tEndIndex)
				{
					if(memcmp(tChars + vI - pLength, pDelimiter, pLength) == 0)
					{
						vReturn = vI - pLength;

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


CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_getIndicesOfAllOccurancesOf(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, Crx_C_String const * pString__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_getIndicesOfAllOccurancesOf3(pThis, pReturn,
			pStartIndex, crx_c_string_constantGetElementsPointer(pString__delimiter),
			crx_c_string_getLength(pString__delimiter),
			pIsToAllowOverlap, pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_getIndicesOfAllOccurancesOf2(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, char const * pString__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_getIndicesOfAllOccurancesOf3(pThis, pReturn,
			pStartIndex, pString__delimiter, strlen(pString__delimiter),
			pIsToAllowOverlap, pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_getIndicesOfAllOccurancesOf3(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, char const * pDelimiter, size_t pLength,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	uint8_t vSizeOfCharacterSet = ((pSizeOfCharacterSet == 0) ? 255 : pSizeOfCharacterSet);
	size_t vFullLength = crx_c_string_getLength(pThis);
	bool vIsNoError = true;

	crx_c_arrays_size_empty(pReturn);

	if(!(((vFullLength - pStartIndex) < pLength) || 
			(vFullLength <= pStartIndex) || (pLength == 0)))
	{
		uint32_t tAlgorithm = 0;
		size_t tLength = vFullLength - pStartIndex;
		char const * tChars = crx_c_string_constantGetElementsPointer(pThis) + pStartIndex;

		/*if(pLength < 5)
			{tAlgorithm = 1;}
		else
		{
			double tSizeOfCharacterSet = ((double)pSizeOfCharacterSet);
			double s2 = (tSizeOfCharacterSet * (1.0 - pow(1.0 - (1.0/tSizeOfCharacterSet), pLength)));//EXPECTED DISTINCT CHARACTERS IN DELIMITER
			double q = 0.4;
			double e = 1.0 / (((1.0 - q) / tSizeOfCharacterSet) + (q / s2));
			
			/*if(e > pLength)
				//{e = pLength;}* /
			
			/*if((pLength < 4) || (pLength * (tLength - pLength) <= 80000 * (1.0 - (1.0/vSizeOfCharacterSet))))* /
			//if(e <= 7)
			//	{tAlgorithm = 7/*6* /;}
			if(e <= 22)
				{tAlgorithm = 4;}
			else if(e <= 40)
				{tAlgorithm = 1;}
			else if(pLength < 7340032)
			{
				/*if(pLength < 16)
					{tAlgorithm = 2;}			
				else
					{tAlgorithm = 3;}* /

				tAlgorithm = 3;
			}
			else
				{tAlgorithm = 4;}
		}
		if(pLength < 5)
			{tAlgorithm = 1;}
		else
		{
			tAlgorithm = 4;
		}*/
		
		tAlgorithm = 4;
		
		if(tAlgorithm == 1)
		{
			char const * tChar = tChars;
			char const * tEndChar = tChars + (tLength - pLength + 1);

			while(tChar < tEndChar)
			{
				tChar = memchr(tChar, *pDelimiter, tEndChar - tChar);

				if(tChar != NULL)
				{
					if(memcmp(tChar, pDelimiter, pLength) == 0)
					{
						if(crx_c_arrays_size_push2(pReturn, tChar - tChars))
						{
							if(!pIsToAllowOverlap)
								{tChar = tChar + pLength;}
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
					
					WE ARE FOR THE ALGOIRTHM ONLY INTERESTED IN THE SECOND LARGEST SUFFIC PREFIX.
					
					NOTE THAT IF FOR SUBSTRING STRING[A..B], 
							|SUFFIX_PREFIX{2}(STRING[A..B])| = K, 
					THEN FOR SUBSTRING STRING[A..B+1] 
							|SUFFIX_PREFIX{2}(STRING[A..B+1])| <= K + 1
					BECAUSE OTHERWISE THIS SUFFIX PREFIX WOULD START AT (A-L) FOR L > 0, MAKING IT A 
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
			
			if(pLength + 1 > 80)
			{
				tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
						calloc(1, sizeof(size_t) * (pLength + 1));
				tIsToFree = true;
			}
			else
			{
				tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
						CRX__ALLOCA(sizeof(size_t) * (pLength + 1));
			}
			
			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[0] = 0;
			CRX_FOR(size_t tI = 1, tI < pLength, tI++)
			{        
				size_t tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tI - 1];

				//IF SECOND LARGEST SUFFIX PREFIX DOES NOT HELP, WE SEEK OUT THE THIRD LARGEST
				//		SUFFIX PREFIX WHICH HAPPENS TO BE THE SECOND LARGEST SUFFIX PREFIX OF THE
				//		SECOND LARGEST SUFFIX PREFIX. AND SO FORTH.
				while((tJ != 0) && (*(pDelimiter + tI) != *(pDelimiter + tJ)))
					{tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tJ - 1];}

				if(*(pDelimiter + tI) == *(pDelimiter + tJ))
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
							(*(tChars + tI) != *(pDelimiter + tCurrentIndexInDelimiter)))
					{
						//SEE * ABOVE.
						tCurrentIndexInDelimiter = 
								tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
								tCurrentIndexInDelimiter - 1];
					}
					
					if(*(tChars + tI) == *(pDelimiter + tCurrentIndexInDelimiter))
						{tCurrentIndexInDelimiter += 1;}

					/*
						AT THIS POINT, THE FOLLOWING MUST ALWAYS HOLD TRUE
								tChars[tI + 1 - tCurrentIndexInDelimiter:tI + 1] == 
										pDelimiter[0:tCurrentIndexInDelimiter]
						IN OTHER WORDS, THE WINDOW, pDelimiter[0:tCurrentIndexInDelimiter], IS ALWAYS VALID, 
						ALWAYS EQUAL TO THE OVERLAP EVEN AFTER SHIFTING.
					*/

					if(tCurrentIndexInDelimiter == pLength)
					{
						if(crx_c_arrays_size_push2(pReturn, tI + 1 - pLength))
						{
							if(pIsToAllowOverlap)
								{tI = tI + 1 - pLength;}

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
				char tLastCharacter = *(pDelimiter + pLength - 1);
				
				CRX_FOR(size_t tI = 0, tI < 256, tI++)
					{tReverseIndexOfCharacterLastOccurance[tI] = (uint32_t)pLength;}
				CRX_ENDFOR

				CRX_FOR(size_t tI = 0, tI < pLength, tI++)
				{
					if(tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pDelimiter)  + tI)] > (pLength - tI - 1))
						{tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pDelimiter)  + tI)] = pLength - tI - 1;}
				}
				CRX_ENDFOR
				
				CRX_FOR(size_t tI = 0, tI < tLength, tI++)
				{
					if(tCurrentIndexInDelimiter == 0)
					{
						while((tI <= tLength - pLength) && (*(tChars + tI + pLength - 1) != tLastCharacter))
							{tI = tI + tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)tChars) + tI + pLength - 1)];}
					}
					else
					{
						while((tCurrentIndexInDelimiter != 0) && 
								(*(tChars + tI) != *(pDelimiter + tCurrentIndexInDelimiter)))
						{
							//SEE * ABOVE.
							tCurrentIndexInDelimiter = 
									tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
									tCurrentIndexInDelimiter - 1];
						}
					}


					if(*(tChars + tI) == *(pDelimiter + tCurrentIndexInDelimiter))
						{tCurrentIndexInDelimiter += 1;}

					/*SEE ABOVE*/
					if(tCurrentIndexInDelimiter == pLength)
					{
						if(crx_c_arrays_size_push2(pReturn, tI + 1 - pLength))
						{
							if(pIsToAllowOverlap)
								{tI = tI + 1 - pLength;}

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
			unsigned char const * tEndChar = tChars + (tLength - pLength) + 1;
			unsigned char tLastCharacter = *(pDelimiter + pLength - 1);
			uint32_t tReverseIndexOfCharacterLastOccurance[256] /*= ?*/;

			CRX_FOR(size_t tI = 0, tI < 256, tI++)
				{tReverseIndexOfCharacterLastOccurance[tI] = (uint32_t)pLength;}
			CRX_ENDFOR
			
			CRX_FOR(size_t tI = 0, tI < pLength, tI++)
			{
				if(tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pDelimiter)  + tI)] > (pLength - tI - 1))
					{tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pDelimiter)  + tI)] = pLength - tI - 1;}
			}
			CRX_ENDFOR

			while(tChar < tEndChar)
			{
				tChar = memchr(tChar, *pDelimiter, tEndChar - tChar);

				if(tChar != NULL)
				{
					while((tChar < tEndChar) && (*(tChar + pLength - 1) != tLastCharacter))
					{
						tChar = tChar + 
								tReverseIndexOfCharacterLastOccurance[*(tChar + pLength - 1)];
					}

					if(tChar < tEndChar)
					{
						if(memcmp(tChar, pDelimiter, pLength) == 0)
						{
							if(crx_c_arrays_size_push2(pReturn, ((char const *)tChar) - tChars))
							{
								if(!pIsToAllowOverlap)
									{tChar = tChar + pLength;}
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
			CRX_FOR(size_t tI = 0, tI <= tLength - pLength, tI++)
			{
				bool tIsFound = true;

				CRX_FOR(size_t tI2 = 0, tI2 < pLength, tI2++)
				{
					if(*(tChars + tI + tI2) != *(pDelimiter + tI2))
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
							{tI = tI + pLength - 1;}
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
			TWO WAY SEARCH ALGORITHM. SEE PAPER. THE LETTERS IN COMMENT IS TO HELP COMPARE CODE
			TO ALOGIRHTMS IN THE PAPER. 
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
			//pLength //n
			while(tI2 + tOffset <= pLength)
			{
				char tChar = *(pDelimiter + tI + tOffset - 1);
				char tChar2 = *(pDelimiter + tI2 + tOffset - 1);

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
			//pLength //n

			while(tI2 + tOffset <= pLength)
			{
				char tChar = *(pDelimiter + tI + tOffset - 1);
				char tChar2 = *(pDelimiter + tI2 + tOffset - 1);

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
			
			if((tCriticalPosition < (pLength >> 1)) && 
					(memcmp(pDelimiter, pDelimiter + tPotentialPeriod, tCriticalPosition) == 0))
			{
				//BASED ON POSITIONS() FUNCTION IN THE PAPER.
				size_t tPeriod = tPotentialPeriod; //p
				size_t tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;//s
				
				tI2 = 0;//pos
				//tI //i
				//tCriticalPosition //l
				//tLength //|t|
				//pLength //|x|
				
				while(tI2 + pLength <= tLength)
				{
					//assert(pDelimiter[1 : tUpperBoundOfAlreadyVerifiedValuesOnRight] = 
					//		tChars[tI2 + 1 : tI2 + tUpperBoundOfAlreadyVerifiedValuesOnRight]) //right side is exclusive.

					tI = ((tCriticalPosition < tUpperBoundOfAlreadyVerifiedValuesOnRight) ? 
							tUpperBoundOfAlreadyVerifiedValuesOnRight : tCriticalPosition) + 1;
					
					while((tI <= pLength) && (*(pDelimiter + tI - 1) == *(tChars + tI2 + tI - 1)))
						{tI++;}

					if(tI <= pLength)
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
								(*(pDelimiter + tJ - 1) == *(tChars + tI2 + tJ - 1)))
							{tJ = tJ - 1;}

						if(tJ <= tUpperBoundOfAlreadyVerifiedValuesOnRight)
						{
							if(crx_c_arrays_size_push2(pReturn, tI2))
							{
								if(!pIsToAllowOverlap)
								{
									tI2 = tI2 + pLength;
									tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;
								}
								else
								{
									tI2 = tI2 + tPeriod;
									tUpperBoundOfAlreadyVerifiedValuesOnRight = pLength - tPeriod;
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
							tUpperBoundOfAlreadyVerifiedValuesOnRight = pLength - tPeriod;
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
				size_t tPeriodLowerBound = ((tCriticalPosition >= pLength - tCriticalPosition) ?
						tCriticalPosition : pLength - tCriticalPosition) + 1; //p OR q IN THE FINAL FORM
				
				tI2 = 0;//pos
				//tI //i
				//tCriticalPosition //l
				//tLength //|t|
				//pLength //|x|

				while(tI2 + pLength <= tLength)
				{
					tI = tCriticalPosition + 1;
					
					while((tI <= pLength) && (*(pDelimiter + tI - 1) == *(tChars + tI2 + tI - 1)))
						{tI++;}

					if(tI <= pLength)
						{tI2 = tI2 + tI - tCriticalPosition;}
					else
					{
						size_t tJ = tCriticalPosition; //ONE BASED INDEX

						while((tJ > 0) && (*(pDelimiter + tJ - 1) == *(tChars + tI2 + tJ - 1)))
							{tJ = tJ - 1;}

						if(tJ == 0)
						{
							if(crx_c_arrays_size_push2(pReturn, tI2))
							{
								if(!pIsToAllowOverlap)
									{tI2 = tI2 + pLength;}
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

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_getIndicesOfAllReverseOccurancesOf(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, Crx_C_String const * pString__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_getIndicesOfAllReverseOccurancesOf3(pThis, pReturn,
			pInclusiveEndIndex, crx_c_string_constantGetElementsPointer(pString__delimiter),
			crx_c_string_getLength(pString__delimiter),
			pIsToAllowOverlap, pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_getIndicesOfAllReverseOccurancesOf2(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, char const * pString__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0))
{
	return crx_c_string_getIndicesOfAllReverseOccurancesOf3(pThis, pReturn,
			pInclusiveEndIndex, pString__delimiter, strlen(pString__delimiter),
			pIsToAllowOverlap, pSizeOfCharacterSet);
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_getIndicesOfAllReverseOccurancesOf3(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, char const * pDelimiter, size_t pLength,
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
	size_t vFullLength = crx_c_string_getLength(pThis);
	bool vIsNoError = true;

	crx_c_arrays_size_empty(pReturn);

	if(!((pInclusiveEndIndex < pLength - 1) || 
			(pInclusiveEndIndex >= vFullLength) || (pLength == 0)))
	{

		uint32_t tAlgorithm = 0;
		size_t tLength = pInclusiveEndIndex + 1;
		char const * tChars = crx_c_string_constantGetElementsPointer(pThis);

		/*if(pLength < 5)
			{tAlgorithm = 1;}
		else
		{
			double tSizeOfCharacterSet = ((double)pSizeOfCharacterSet);
			double s2 = (tSizeOfCharacterSet * (1.0 - pow(1.0 - (1.0/tSizeOfCharacterSet), pLength)));//EXPECTED DISTINCT CHARACTERS IN DELIMITER
			double q = 0.4;
			double e = 1.0 / (((1.0 - q) / tSizeOfCharacterSet) + (q / s2));
			
			/*if(e > pLength)
				//{e = pLength;}* /
			
			/*if((pLength < 4) || (pLength * (tLength - pLength) <= 80000 * (1.0 - (1.0/vSizeOfCharacterSet))))* /
			//if(e <= 7)
			//	{tAlgorithm = 7/*6* /;}
			if(e <= 22)
				{tAlgorithm = 4;}
			else if(e <= 40)
				{tAlgorithm = 1;}
			else if(pLength < 7340032)
			{
				/*if(pLength < 16)
					{tAlgorithm = 2;}			
				else
					{tAlgorithm = 3;}* /

				tAlgorithm = 3;
			}
			else
				{tAlgorithm = 4;}
		}
		if(pLength < 5)
			{tAlgorithm = 1;}
		else
		{
			tAlgorithm = 4;
		}*/

		if(pLength < 7340032)
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
					
					WE ARE FOR THE ALGOIRTHM ONLY INTERESTED IN THE SECOND LARGEST SUFFIC PREFIX.
					
					NOTE THAT IF FOR SUBSTRING STRING[A..B], 
							|SUFFIX_PREFIX{2}(STRING[A..B])| = K, 
					THEN FOR SUBSTRING STRING[A..B+1] 
							|SUFFIX_PREFIX{2}(STRING[A..B+1])| <= K + 1
					BECAUSE OTHERWISE THIS SUFFIX PREFIX WOULD START AT (A-L) FOR L > 0, MAKING IT A 
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
			
			if(pLength + 1 > 80)
			{
				tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
						calloc(1, sizeof(size_t) * (pLength + 1));
				tIsToFree = true;
			}
			else
			{
				tSecondLargestSuffixPrefixForSubDelimiterUpToIndex = 
						CRX__ALLOCA(sizeof(size_t) * (pLength + 1));
			}
			
			tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[0] = 0;
			CRX_FOR(size_t tI = 1, tI < pLength, tI++)
			{        
				size_t tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[pLength - 1 - (tI - 1)];

				//IF SECOND LARGEST SUFFIX PREFIX DOES NOT HELP, WE SEEK OUT THE THIRD LARGEST
				//		SUFFIX PREFIX WHICH HAPPENS TO BE THE SECOND LARGEST SUFFIX PREFIX OF THE
				//		SECOND LARGEST SUFFIX PREFIX. AND SO FORTH.
				while((tJ != 0) && (*(pDelimiter + pLength - 1 - tI) != *(pDelimiter + pLength - 1 - tJ)))
					{tJ = tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[tJ - 1];}

				if(*(pDelimiter + pLength - 1 - tI) == *(pDelimiter + pLength - 1 - tJ))
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
							(*(tChars + tLength - 1 - tI) != *(pDelimiter + pLength - 1 - tCurrentIndexInDelimiter)))
					{
						//SEE * ABOVE.
						tCurrentIndexInDelimiter = 
								tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
								tCurrentIndexInDelimiter - 1];
					}
					
					if(*(tChars + tLength - 1 - tI) == *(pDelimiter + pLength - 1 - tCurrentIndexInDelimiter))
						{tCurrentIndexInDelimiter += 1;}

					/*
						AT THIS POINT, THE FOLLOWING MUST ALWAYS HOLD TRUE
								tChars[tI + 1 - tCurrentIndexInDelimiter:tI + 1] == 
										pDelimiter[0:tCurrentIndexInDelimiter]
						IN OTHER WORDS, THE WINDOW, pDelimiter[0:tCurrentIndexInDelimiter], IS ALWAYS VALID, 
						ALWAYS EQUAL TO THE OVERLAP EVEN AFTER SHIFTING.
					*/

					if(tCurrentIndexInDelimiter == pLength)
					{
						if(crx_c_arrays_size_push2(pReturn, tLength - 1 - tI))/*== tLength - 1 - (tI + 1 - pLength) - (pLength - 1)*/
						{
							if(pIsToAllowOverlap)
								{tI = tI + 1 - pLength;}
							
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
				char tLastCharacter = *pDelimiter;
				
				CRX_FOR(size_t tI = 0, tI < 256, tI++)
					{tReverseIndexOfCharacterLastOccurance[tI] = (uint32_t)pLength;}
				CRX_ENDFOR

				CRX_FOR(size_t tI = 0, tI < pLength, tI++)
				{
					if(tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pDelimiter) + pLength - 1 - tI)] > (pLength - tI - 1))
						{tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)pDelimiter) + pLength - 1 - tI)] = pLength - tI - 1;}
				}
				CRX_ENDFOR
				
				CRX_FOR(size_t tI = 0, tI < tLength, tI++)
				{
					if(tCurrentIndexInDelimiter == 0)
					{
						while((tI <= tLength - pLength) && (*(tChars + tLength - 1 - (tI + pLength - 1)) != tLastCharacter))
							{tI = tI + tReverseIndexOfCharacterLastOccurance[*(((unsigned char const *)tChars) + tLength - 1 - (tI + pLength - 1))];}
					}
					else
					{
						while((tCurrentIndexInDelimiter != 0) && 
								(*(tChars + tLength - 1 - tI) != *(pDelimiter + pLength - 1 - tCurrentIndexInDelimiter)))
						{
							//SEE * ABOVE.
							tCurrentIndexInDelimiter = 
									tSecondLargestSuffixPrefixForSubDelimiterUpToIndex[
									tCurrentIndexInDelimiter - 1];
						}
					}


					if(*(tChars + tLength - 1 - tI) == *(pDelimiter + pLength - 1 - tCurrentIndexInDelimiter))
						{tCurrentIndexInDelimiter += 1;}

					/*SEE ABOVE*/
					if(tCurrentIndexInDelimiter == pLength)
					{
						if(crx_c_arrays_size_push2(pReturn, tLength - 1 - tI))/*== tLength - 1 - (tI + 1 - pLength) - (pLength - 1)*/
						{
							if(pIsToAllowOverlap)
								{tI = tI + 1 - pLength;}
							
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
			CRX_FOR(size_t tI = 0, tI <= tLength - pLength, tI++)
			{
				bool tIsFound = true;

				CRX_FOR(size_t tI2 = 0, tI2 < pLength, tI2++)
				{
					if(*(tChars + tLength - 1 - tI - tI2) != *(pDelimiter + pLength - 1 - tI2))
					{
						tIsFound = false;
						break;
					}
				}
				CRX_ENDFOR
						
				if(tIsFound)
				{
					if(crx_c_arrays_size_push2(pReturn, tLength - tI - pLength))/*== tLength - 1 - tI - (pLength - 1)*/
					{
						if(!pIsToAllowOverlap)
							{tI = tI + pLength - 1;}
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
			TWO WAY SEARCH ALGORITHM. SEE PAPER. THE LETTERS IN COMMENT IS TO HELP COMPARE CODE
			TO ALOGIRHTMS IN THE PAPER. 
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
			//pLength //n
			while(tI2 + tOffset <= pLength)
			{
				char tChar = *(pDelimiter + pLength - 1 - (tI + tOffset - 1));
				char tChar2 = *(pDelimiter + pLength - 1 - (tI2 + tOffset - 1));

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
			//pLength //n

			while(tI2 + tOffset <= pLength)
			{
				char tChar = *(pDelimiter + pLength - 1 - (tI + tOffset - 1));
				char tChar2 = *(pDelimiter + pLength - 1 - (tI2 + tOffset - 1));

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
			
			if((tCriticalPosition < (pLength >> 1)) && 
					(memcmp(pDelimiter + pLength - 1 - (tCriticalPosition - 1), pDelimiter + pLength - 1 - tPotentialPeriod - (tCriticalPosition - 1), tCriticalPosition) == 0))
			{
				//BASED ON POSITIONS() FUNCTION IN THE PAPER.
				size_t tPeriod = tPotentialPeriod; //p
				size_t tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;//s
				
				tI2 = 0;//pos
				//tI //i
				//tCriticalPosition //l
				//tLength //|t|
				//pLength //|x|
				
				while(tI2 + pLength <= tLength)
				{
					//assert(pDelimiter[1 : tUpperBoundOfAlreadyVerifiedValuesOnRight] = 
					//		tChars[tI2 + 1 : tI2 + tUpperBoundOfAlreadyVerifiedValuesOnRight]) //right side is exclusive.

					tI = ((tCriticalPosition < tUpperBoundOfAlreadyVerifiedValuesOnRight) ? 
							tUpperBoundOfAlreadyVerifiedValuesOnRight : tCriticalPosition) + 1;
					
					while((tI <= pLength) && (*(pDelimiter + pLength - 1 - (tI - 1)) == *(tChars + tLength - 1 - (tI2 + tI - 1))))
						{tI++;}

					if(tI <= pLength)
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
								(*(pDelimiter + pLength - 1 - (tJ - 1)) == *(tChars + tLength - 1 - (tI2 + tJ - 1))))
							{tJ = tJ - 1;}

						if(tJ <= tUpperBoundOfAlreadyVerifiedValuesOnRight)
						{
							if(crx_c_arrays_size_push2(pReturn, tLength - 1 - tI2 - (pLength - 1)))
							{
								if(!pIsToAllowOverlap)
								{
									tI2 = tI2 + pLength;
									tUpperBoundOfAlreadyVerifiedValuesOnRight = 0;
								}
								else
								{
									tI2 = tI2 + tPeriod;
									tUpperBoundOfAlreadyVerifiedValuesOnRight = pLength - tPeriod;
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
							tUpperBoundOfAlreadyVerifiedValuesOnRight = pLength - tPeriod;
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
				size_t tPeriodLowerBound = ((tCriticalPosition >= pLength - tCriticalPosition) ?
						tCriticalPosition : pLength - tCriticalPosition) + 1; //p OR q IN THE FINAL FORM
				
				tI2 = 0;//pos
				//tI //i
				//tCriticalPosition //l
				//tLength //|t|
				//pLength //|x|

				while(tI2 + pLength <= tLength)
				{
					tI = tCriticalPosition + 1;
					
					while((tI <= pLength) && (*(pDelimiter + pLength - 1 - (tI - 1)) == *(tChars + tLength - 1 - (tI2 + tI - 1))))
						{tI++;}

					if(tI <= pLength)
						{tI2 = tI2 + tI - tCriticalPosition;}
					else
					{
						size_t tJ = tCriticalPosition; //ONE BASED INDEX

						while((tJ > 0) && (*(pDelimiter + pLength - 1 - (tJ - 1)) == *(tChars + tLength - 1 - (tI2 + tJ - 1))))
							{tJ = tJ - 1;}

						if(tJ == 0)
						{
							if(crx_c_arrays_size_push2(pReturn, tLength - 1 - tI2 - (pLength - 1)))
							{
								if(!pIsToAllowOverlap)
									{tI2 = tI2 + pLength;}
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
			size_t tEndIndex = pLength - 1; //One based index
			unsigned char tFirstCharacter = *pDelimiter;
			unsigned char tLastCharacter = *(pDelimiter + pLength - 1);
			uint32_t tIndexOfCharacterFirstOccurance[256] /*= ?*/;
			size_t vI = tLength; //One based index

			CRX_FOR(size_t tI = 0, tI < 256, tI++)
				{tIndexOfCharacterFirstOccurance[tI] = (uint32_t)pLength;}
			CRX_ENDFOR
			
			CRX_FOR(size_t tI = 0, tI < pLength, tI++)
			{
				if(tIndexOfCharacterFirstOccurance[*(((unsigned char const *)pDelimiter)  + tI)] > tI)
					{tIndexOfCharacterFirstOccurance[*(((unsigned char const *)pDelimiter)  + tI)] = tI;}
			}
			CRX_ENDFOR

			while(vI > tEndIndex)
			{
				while((vI > tEndIndex) && (*(tChars + vI - 1) != tLastCharacter))
					{vI--;}

				if(vI > tEndIndex)
				{
					while((vI > tEndIndex) && (*(tChars__2 + vI - pLength) != tFirstCharacter))
						{vI = vI - tIndexOfCharacterFirstOccurance[*(tChars__2 + vI - pLength)];}

					if(vI > tEndIndex)
					{
						if(memcmp(tChars__2 + vI - pLength, pDelimiter, pLength) == 0)
						{
							if(crx_c_arrays_size_push2(pReturn, vI - pLength))
							{
								if(!pIsToAllowOverlap)
									{vI = vI - pLength;}
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


#undef CRX__C__STRING__PRIVATE__SIZE32_MAX
#undef CRX__C__STRING__PRIVATE__IS_MEMMEM_AVAILABLE

CRX__LIB__C_CODE_END()

