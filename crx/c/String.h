#if(!defined(CRX__C__STRING___h__))
#define CRX__C__STRING___h__

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
#include "Crx/H/crx/nonCrxed/standard/stdint.h"
#include <stdio.h>
#include "Crx/H/crx/c/Array.h"
#include "Crx/H/crx/c/arrays/Size.h"
//<<END>>
	
CRX__LIB__C_CODE_BEGIN()

#if(defined(UINT32_MAX))
	#define CRX__C__STRING__PRIVATE__SIZE32_MAX UINT32_MAX
#else
	#define CRX__C__STRING__PRIVATE__SIZE32_MAX ((uint32_t)(-1))
#endif

typedef struct Crx_C_Arrays_String Crx_C_Arrays_String;

/*
CONTRACT:
	IS FIXED SIZE:			1
	HAS CONSTRUCT:		 	1
	HAS DESTRUCT:		 	1
	IS COPYABLE:			1
	HAS COPY CONSTRUCT:		1
	HAS MOVE CONSTRUCT:		0
	HAS MOVE DESTRUCT:		0
*/
CRX__C__Array__DECLARE(Crx_C_String, crx_c_string_, char, 
		uint32_t, CRX__C__STRING__PRIVATE__SIZE32_MAX, 
		16, CRXM__FALSE,
		CRXM__FALSE, CRXM__FALSE, CRXM__FALSE, CRXM__FALSE)

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_construct3(Crx_C_String * pThis, char pChar);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_construct4(Crx_C_String * pThis, 
		char const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_construct5(Crx_C_String * pThis, 
		char const * pChars, size_t pLength);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_copyConstruct(Crx_C_String * pThis, 
		Crx_C_String const * pString);//DEFINED BY TEMPLATE

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String * crx_c_string_new3(char pChar);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String * crx_c_string_new4(char const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String * crx_c_string_new5(char const * pChars, size_t pLength);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_destruct(Crx_C_String * pThis); //DEFINED BY TEMPLATE
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_free(Crx_C_String * pThis); //DEFINED BY TEMPLATE

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendString(Crx_C_String * pThis, 
		Crx_C_String const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendChar(Crx_C_String * pThis, char pChar);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendString2(Crx_C_String * pThis, 
		char const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendChars(Crx_C_String * pThis, 
		char const * pChars, size_t pLength);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendWideChars(Crx_C_String * pThis, 
		wchar_t const * pWchars, size_t pLength);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendInt(Crx_C_String * pThis, int32_t pInt);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendInt2(Crx_C_String * pThis, 
		unsigned int pNumberOfDigits, int32_t pInt);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_looselyAppendFloat(Crx_C_String * pThis, 
		double pDouble);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEmpty(Crx_C_String const * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEqualTo(Crx_C_String const * pThis,
		Crx_C_String const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEqualTo2(Crx_C_String const * pThis,
		char const * pString);

CRX__LIB__PUBLIC_C_FUNCTION() char const * crx_c_string_getCString(Crx_C_String * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isBeginningWith(Crx_C_String const * pThis,
		Crx_C_String const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isBeginningWith2(Crx_C_String const * pThis,
		char const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isBeginningWith3(Crx_C_String const * pThis,
		char const * pChars, size_t pLength);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEndingWith(Crx_C_String const * pThis,
		Crx_C_String const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEndingWith2(Crx_C_String const * pThis,
		char const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEndingWith3(Crx_C_String const * pThis,
		char const * pChars, size_t pLength);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_lowerTheCase(Crx_C_String * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_upperTheCase(Crx_C_String * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_trim(Crx_C_String * pThis);

#if(0)
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_splitAndGet(Crx_C_String const * pThis, 
		Crx_C_Arrays_String * CRX_NOT_NULL pReturn, char pChar);
#endif

/*
NOTE:
	- THE FOLLOWING IS OPTIMIZED FOR FINDING THE FIRST OCCURANCE
*/
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstOccuranceOf(
		Crx_C_String const * pThis, size_t pStartIndex, Crx_C_String const * pString__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstOccuranceOf2(
		Crx_C_String const * pThis, size_t pStartIndex, char const * pString__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstOccuranceOf3(
		Crx_C_String const * pThis, size_t pStartIndex, char const * pDelimiter, size_t pLength,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));

/*
THE FOLLOWING WAS REQUIRED BECAUSE OF FIND LAST INDEX FUNCTIONS IN OTHER LANGUAGES.
ALL LANGUAGES THAT CONTAIN SUCH FUNCTION IN THEIR STANDARD LIBRARIES THAT I SURVEYED
HAVE THIS FUNCTION WORK SUCH AS THE LAST RESULT OF A SEARCH USING FIND FIRST OCCURANCE TO 
FIND ALL OCCURANCES IS NOT FORMALLY EQUAL TO THE SEARCH OF FINDING THE LAST OCCURANCE, THE
"LAST INDEX OF". INSTEAD THOSE FUNCTIONS ARE EQUIVILANT OF FINDING THE FIRST REVERSE
OCCURANCE. IN OTHER WORDS getIndexOfFirstReverseOccuranceOf() IS NOT SIMPLY THE RESULTS
OF getIndexOfFirstOccuranceOf() REVERSED.

NOTE THAT THE FOLLOWING WAS NOT BENCHMARKED EXTENSIVELY AS getIndexOfFirstOccuranceOf()
ABOVE. EDUCATED GUESSES WERE MADE INSTEAD, AND CONFIRMED VALID FOR THE LIMITED MANUAL
TESTING. NOTE THAT UNLIKE getIndexOfFirstOccuranceOf(), THERE IS NO STANDARD REFERENCE FUNCTION
TO BE USED TO COMPARE TO, THERE IS NO EUQIVILANT OF C'S strstr() THAT CAN BE USED.
*/
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstReverseOccuranceOf(
		Crx_C_String const * pThis, size_t pExclusiveEndIndex, Crx_C_String const * pString__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstReverseOccuranceOf2(
		Crx_C_String const * pThis, size_t pExclusiveEndIndex, char const * pString__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstReverseOccuranceOf3(
		Crx_C_String const * pThis, size_t pExclusiveEndIndex, char const * pDelimiter, size_t pLength,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));

/*
	NOTE: NEW BENCHMARKS ARE REQUIRED FOR TESTING. RESULTS ARE LIKELY TO REVERSE BETWEEN
			THE TRIVIAL AND NON TRIVIAL ALGORITHMS. RECHECK PROBABILITY EQUATIONS
			FOR DECIDING ON ALGORITHM.
*/
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_getIndicesOfAllOccurancesOf(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, Crx_C_String const * pString__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_getIndicesOfAllOccurancesOf2(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, char const * pString__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_getIndicesOfAllOccurancesOf3(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, char const * pDelimiter, size_t pLength,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));

/*
	NOTE: NEW BENCHMARKS ARE REQUIRED FOR TESTING. RESULTS ARE LIKELY TO REVERSE BETWEEN
			THE TRIVIAL AND NON TRIVIAL ALGORITHMS. RECHECK PROBABILITY EQUATIONS
			FOR DECIDING ON ALGORITHM.
*/
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_getIndicesOfAllReverseOccurancesOf(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, Crx_C_String const * pString__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_getIndicesOfAllReverseOccurancesOf2(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, char const * pString__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_getIndicesOfAllReverseOccurancesOf3(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, char const * pDelimiter, size_t pLength,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));

CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/String.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif