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

/* DESIGN NOTES:
	- THE STRING HAS AN INTERNAL BUFFER. AN IMPORTANT IMPLICATION OF THIS, WHICH IS ALSO A 
			REQUIREMENT, IS THAT String::getElementsPointer(), AND ITS DERIVATIVES, 
			NEVER RETURN A NULL.
	- WHEN THE VALUE OF CHARACTERS IS CONSIDERED, ANSI ENCODING OF ASCII AS DEFINED IN MY STANDARD
			IS ASSUMED.
	- IF isEmpty(x) EVALUATES TO true, THEN THE LENGTH OF y, WHERE y = trim(x), MUST BE ZERO. THE
			REVERSE IS NOT NECESSARILY TRUE.
	- lowerTheCase(upperTheCase(x)) == upperTheCase(lowerTheCase(x)) == x FOR ALL x
	- CASE INSENSITIVE COMPARISON MUST BE SUCH AS IT IS EQUIVILANT TO LOWER CASING BOTH
			STRINGS THEN COMPARING, OR UPPER CASING BOTH STRINGS THEN COMPARING.
			
			THE COMPARISON MAY ONLY RETURN A THREE STATE VALUES SUCH AS 1, 0, AND -1. AN IMPLICATION 
			OF THIS IS THAT STRINGS SHUFFLED AND THEN RE ORDERED CASE INSENSITIVELY COULD END UP
			WITH A DIFFERENT ORDERING EACH TIME THIS IS DONE.
			
			THE ALETERNATIVE IS FULL DIFFERENCE RANGE WHICH WOULD REQUIRE ASSIGNING NEW VALUES
			TO CHARACTERS THAT WOULD CAUSE AN AMBIGUOUS ORDER WHILE AIMING NOT TO CONFLICT WITH 
			UNICODE. EFFICETEVLY YOU WOULD BE ORDERING N x N INSTEAD OF N, AND YOU WOULD HAVE TO 
			MAP N x N INTO AN N SPACE, AND YOU WANT THE MAPPING SUCH AS IF A CHARACTER HAS UNICODE 
			CODE POINT c, AND IS NEITHER UPPER CASE NOR LOWER CASE, THEN ITS NEW VALUE IS c x c, 
			AND MAPPED TO N, IT WOULD BE c. OTHERWISE, THE CHARACTER'S NEW VALUE WOULD BE (c, 1), OR 
			(c, 2), WHERE c IS THE CODE POINT OF EITHER THE UPPER CASE OR THE LOWER CASE AND WHEN 
			MAPPING THOSE TO N AND YOU GET x, YOU WANT x TO BE SUCH AS IT IS OUTSIDE THE UNICODE 
			RANGE. NOTE THAT MAPPING WOULD REQUIRE BOTH CASES TO BE MAPPED. FOR EXAMPLE BOTH
			THE RANGE OF a-z AND A-Z WOULD NEED TO BE MAPPED OUTSIDE OF UNICODE'S RANGE BECAUSE
			THE RANGES HAVE OTHER CHARACTERS IN BETWEEN AND THEREFORE CAN NOT BOTH BE KEPT WHERE
			THEY ARE IN THE UNICODE TABLE WHEN MAPPED TO N.
	findAllTokensStartingFromLeft() IS REDUNDANT BUT IS PROVIDED TO ALLOW FOR A NORMAL FORM WHEN
			IT COMES TO TOKENIZING FUNCTIONS IN OTHER LANGUAGES. IT ALSO MIRRORS THE FUNCTION OF
			computeIndicesOfAllOccurancesOf() BUT THAT IS NOT THE PRIMARY REASON FOR ITS EXISTANCE.
	THE StringRange CLASS HAD TO BE BROUGHT BACK AS AN INNER CLASS, WHILE THIS IS THE CORRECT
			SOLUTION, THE ULTIMATE REASON FOR BRINGING IT BACK IS ITS USAGE ON THE STACK IN SOME OF
			THE String FUNCTION MEMBERS.
			OLD NOTE AND CODE IN THE CODE:
					/ *
						THE FOLLOWING IS ILL DEFINED. GIVEN THAT A CIRCULAR DEPENDENCY IS A PROBLEM 
						FOR CRX LIB, CIRCULAR DEPENDENCY BECOMES AN EXISTANCE PROBLEM AS DEFINED IN 
						MY STANDARD. HENCE, "String" MUST BE THE ONE BANNED FROM INCLUDING 
						"StringRange" AND ITS. THE CORRECT SOLUTION FOR THIS EXISTANCE PROBLEM IS 
						FOR "StringRange" TO BE AN INNER CLASS OF "String". HOWEVER I WANTED TO 
						AVOID THE NAME
								Crx_C_String_Range
						BECAUSE "Range" DOES NOT INDICATE STRING, AND AVOID THE NAME
								Crx_C_String_StringRange
						BECAUSE IT RESULS IN VERY LONG FUNCTION NAMES, AND "String" IS A VERY USED 
						TYPE.
						
						I MIGHT STILL TO FIX THIS IN THE FUTURE, MEANING MAKE "StringRange" AN INNER 
						CLASS OF "String" IF THIS ENDS UP WITH OTHER IMPLICATIONS, SUCH AS THE 
						ALREADY EXISTING PROBLEM OF ARRAY OF "StringRange" BELOW.
					* /
					typedef struct Crx_C_StringRange Crx_C_StringRange;
					typedef struct Crx_C_Arrays_StringRange Crx_C_Arrays_StringRange;
			THE FOLLOWING WAS ALSO REQUIRED IN THE SOURCE HEADER CODE FILE:
					void crx_c_stringRange_construct(Crx_C_StringRange * pThis);
					size_t crx_c_stringRange_getLength(Crx_C_StringRange const * pThis);
					char const * crx_c_stringRange_getCharsPointer(Crx_C_StringRange const * pThis);
					size_t crx_c_stringRange_setString2(Crx_C_StringRange * pThis, Crx_C_String const * pString, 
							size_t pStart, size_t pEnd);
					size_t crx_c_stringRange_unsetString(Crx_C_StringRange * pThis);
					void crx_c_arrays_stringRange_empty(Crx_C_Arrays_StringRange * pThis);
					bool crx_c_arrays_stringRange_push(Crx_C_Arrays_StringRange * pThis, 
							Crx_C_StringRange const * CRX_NOT_NULL pElement);
			BUT THE STACK USAGE DID NOT ALLOW THE APPROACH TO WORK.
			
			I ALSO SETTLED ON THE NEW NAME Sub, BECAUSE I WANTED TO AVOID StringRange BECAUSE OF THE
			ADDED LENGTH WHICH IS AN ISSUE BECAUSE String IS A MUCH USED TYPE, WHICH LEAVES US WITH
			Range, BUT Range OFTEN INDICATE A NUMERIC RANGE. I CONSIDERED Span, BUT SEEING ITS USAGE
			IN RECENT C++ STD VERSIONS, I DECIDED OTHERWISE.
	size_t MUST ALSO BE RETURNED WHEN RETURNING AN INDEX, BECAUSE MAXIMUM OF size_t IS USED TO 
			INDICATE NO INDEX.
*/
	
CRX__LIB__C_CODE_BEGIN()

#if(defined(UINT32_MAX))
	#define CRX__C__STRING__PRIVATE__SIZE32_MAX UINT32_MAX
#else
	#define CRX__C__STRING__PRIVATE__SIZE32_MAX ((uint32_t)(-1))
#endif


typedef struct Crx_C_String_Sub Crx_C_String_Sub;
typedef struct Crx_C_String_Arrays_Sub Crx_C_String_Arrays_Sub;

/*
CONTRACT:
	IS FIXED SIZE:			1
	HAS CONSTRUCT:		 	1
	HAS DESTRUCT:		 	1
	IS COPYABLE:			1
	HAS COPY CONSTRUCT:		1
	HAS MOVE CONSTRUCT:		0
	HAS MOVE DESTRUCT:		0
	
REMEMBER THAT THIS TYPE, Crx::C::String, IS NOT NULL TERMINATED. HENCE, ITS SIZE IS EQUAL TO ITS
		LENGTH. FOR char *, HOWEVER, REMEMBER THAT LENGTH INCLUDES THE NULL TERMINATOR,
		WHILE SIZE EXCLUDES IT. THIS IS PER MY FORMAL DEFINITIONS ELSEWHERE.
*/
CRX__C__Array__DECLARE(Crx_C_String, crx_c_string_, char, 
		uint32_t, CRX__C__STRING__PRIVATE__SIZE32_MAX, 
		16, CRXM__FALSE,
		CRXM__FALSE, CRXM__FALSE, CRXM__FALSE, CRXM__FALSE)

CRX__LIB__PRIVATE_C_FUNCTION() int32_t crx_c_string_caseInsensitivelyCompare(
		char const * pChars, char const * pChars__2, size_t pCommonLength);

//MUST MATCH Crx_C_TypeBluePrint_AreObjectsEqual
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_areStringsEqual(void const * pString,
		void const * pString__2);
//MUST MATCH Crx_C_TypeBluePrint_GetHash
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getHash(size_t pSeed, 
		void const * CRX_NOT_NULL pString);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_construct3(Crx_C_String * pThis, char pChar);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_construct4(Crx_C_String * pThis, 
		char const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_construct5(Crx_C_String * pThis, 
		char const * pChars, size_t pSize);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_copyConstruct(Crx_C_String * pThis, 
		Crx_C_String const * CRX_NOT_NULL pString);//DEFINED BY TEMPLATE

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String * crx_c_string_new3(char pChar);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String * crx_c_string_new4(char const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String * crx_c_string_new5(char const * pChars, size_t pSize);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_destruct(Crx_C_String * pThis); //DEFINED BY TEMPLATE
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_free(Crx_C_String * pThis); //DEFINED BY TEMPLATE

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendString(Crx_C_String * pThis, 
		Crx_C_String const * CRX_NOT_NULL pString);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendChar(Crx_C_String * pThis, char pChar);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendCString(Crx_C_String * pThis, 
		char const * CRX_NOT_NULL pString);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendChars(Crx_C_String * pThis, 
		char const * CRX_NOT_NULL pChars, size_t pSize);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendSub(Crx_C_String * pThis, 
		Crx_C_String_Sub const * CRX_NOT_NULL pSub);
/*CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendWideChars(Crx_C_String * pThis, 
		wchar_t const * pWchars, size_t pLength);*/
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendInt(Crx_C_String * pThis, int32_t pInt);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_appendInt2(Crx_C_String * pThis, 
		uint32_t pNumberOfDigits, int32_t pInt);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_looselyAppendFloat(Crx_C_String * pThis, 
		double pDouble);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEmpty(Crx_C_String const * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_trim(Crx_C_String * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEqualTo(Crx_C_String const * pThis,
		Crx_C_String const * CRX_NOT_NULL pString, bool pIsCaseSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEqualTo2(Crx_C_String const * pThis,
		char const * CRX_NOT_NULL pString, bool pIsCaseSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEqualTo3(Crx_C_String const * pThis,
		char const * CRX_NOT_NULL pChars, size_t pSize, bool pIsCaseSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEqualTo4(Crx_C_String const * pThis,
		Crx_C_String_Sub const * CRX_NOT_NULL pSub, bool pIsCaseInSensitive);

CRX__LIB__PUBLIC_C_FUNCTION() char const * crx_c_string_getCString(Crx_C_String * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isBeginningWith(Crx_C_String const * pThis,
		Crx_C_String const * CRX_NOT_NULL pString, bool pIsCaseSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isBeginningWith2(Crx_C_String const * pThis,
		char const * CRX_NOT_NULL pString, bool pIsCaseSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isBeginningWith3(Crx_C_String const * pThis,
		char const * CRX_NOT_NULL pChars, size_t pSize, bool pIsCaseSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isBeginningWith4(Crx_C_String const * pThis,
		Crx_C_String_Sub const * CRX_NOT_NULL pSub, bool pIsCaseInSensitive);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEndingWith(Crx_C_String const * pThis,
		Crx_C_String const * CRX_NOT_NULL pString, bool pIsCaseSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEndingWith2(Crx_C_String const * pThis,
		char const * CRX_NOT_NULL pString, bool pIsCaseSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEndingWith3(Crx_C_String const * pThis,
		char const * CRX_NOT_NULL pChars, size_t pSize, bool pIsCaseSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_isEndingWith4(Crx_C_String const * pThis,
		Crx_C_String_Sub const * CRX_NOT_NULL pSub, bool pIsCaseInSensitive);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_lowerTheCase(Crx_C_String * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_upperTheCase(Crx_C_String * pThis);

/*
NOTE:
	- THE FOLLOWING IS OPTIMIZED FOR FINDING THE FIRST OCCURANCE
*/
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstOccuranceOf(
		Crx_C_String const * pThis, size_t pStartIndex, Crx_C_String const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstOccuranceOf2(
		Crx_C_String const * pThis, size_t pStartIndex, char const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstOccuranceOf3(
		Crx_C_String const * pThis, size_t pStartIndex, char const * pChars__delimiter, 
		size_t pSize, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstOccuranceOf4(
		Crx_C_String const * pThis, size_t pStartIndex, 
		Crx_C_String_Sub const * pSub__delimiter, 
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
		Crx_C_String const * pThis, size_t pInclusiveEndIndex, Crx_C_String const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstReverseOccuranceOf2(
		Crx_C_String const * pThis, size_t pInclusiveEndIndex, char const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstReverseOccuranceOf3(
		Crx_C_String const * pThis, size_t pInclusiveEndIndex, char const * pChars__delimiter, 
		size_t pSize, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_getIndexOfFirstReverseOccuranceOf4(
		Crx_C_String const * pThis, size_t pInclusiveEndIndex, 
		Crx_C_String_Sub const * pSub__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));

/*
	NOTE: NEW BENCHMARKS ARE REQUIRED FOR TESTING. RESULTS ARE LIKELY TO REVERSE BETWEEN
			THE TRIVIAL AND NON TRIVIAL ALGORITHMS. RECHECK PROBABILITY EQUATIONS
			FOR DECIDING ON ALGORITHM.
*/
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllOccurancesOf(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, Crx_C_String const * pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllOccurancesOf2(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, char const * pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllOccurancesOf3(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, char const * pChars__delimiter, size_t pSize,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllOccurancesOf4(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, Crx_C_String_Sub const * pSub__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));

/*
	NOTE: NEW BENCHMARKS ARE REQUIRED FOR TESTING. RESULTS ARE LIKELY TO REVERSE BETWEEN
			THE TRIVIAL AND NON TRIVIAL ALGORITHMS. RECHECK PROBABILITY EQUATIONS
			FOR DECIDING ON ALGORITHM.
*/
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllReverseOccurancesOf(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, Crx_C_String const * pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllReverseOccurancesOf2(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, char const * pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllReverseOccurancesOf3(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, char const * pChars__delimiter, size_t pSize,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_computeIndicesOfAllReverseOccurancesOf4(
		Crx_C_String const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, Crx_C_String_Sub const * pSub__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_replaceOccurancesOfChar(Crx_C_String * pThis,
		size_t pStartingIndex, char pChar, char pReplacementChar, bool pIsToReplaceFirstOnly);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findNextLeftTokenAndUpdateIndex(
		Crx_C_String const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, Crx_C_String const * CRX_NOT_NULL pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findNextLeftTokenAndUpdateIndex2(
		Crx_C_String const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, char const * CRX_NOT_NULL pString,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findNextLeftTokenAndUpdateIndex3(
		Crx_C_String const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, char const * CRX_NOT_NULL pChars__delimiter, size_t pSize,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findNextLeftTokenAndUpdateIndex4(
		Crx_C_String const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, 
		Crx_C_String_Sub const * CRX_NOT_NULL pSub__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findAllTokensStartingFromLeft(
		Crx_C_String const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, Crx_C_String const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findAllTokensStartingFromLeft2(
		Crx_C_String const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, char const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findAllTokensStartingFromLeft3(
		Crx_C_String const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, char const * CRX_NOT_NULL pChars__delimiter, size_t pSize,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_findAllTokensStartingFromLeft4(
		Crx_C_String const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, Crx_C_String_Sub const * pSub__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
		
//---------------------------
//CLASS: String::Sub
//---------------------------
/* DESIGN NOTES:
	- String::Sub::gStartIndex MUST BE SIZE_MAX WHEN Sub::gEndIndex IS
			SIZE_MAX, AND VICE VERSA.
	- String::Sub::gStartIndex MUST BE SIZE_MAX WHEN Sub::gString IS NULL. AN IMPLICATION
			OF THIS IS THAT IF 
					String::Sub::gString == NULL
			THEN
					(pThis->gEndIndex - pThis->gStartIndex) == 0
	- IF String::Sub::gString IS NULL, THEN String::Sub MUST BEHAVE AS AN EMPTY STRING. THIS
			SHOULD NOT CONTRADICT THE FORMAL DEFINITIONS OF NULL AND THEIR IMPLICATIONS IN THE
			STANDARD WHEN COMPARED TO 'EMPTY' AS DEFINED THERE.
	- String::Sub::getEndChar() EXISTS EVEN THOUGH IT IS APPARANTELY REDUNDANT BECAUSE 
			String::Sub::getStartChar() CAN RETURN A NULL. WITH String::Sub::getEndChar(),
			THE CONDITION "currentChar != endChar" CAN CONTINUE TO WORK RELIABLY FOR CODE
			ATTEMPTING TO LOOP. IFF String::Sub::getStartChar() RETURNS NULL, 
			String::Sub::getEndChar() RETURNS NULL. 
			Update: THIS FUNCTION WAS REMOVED AFTER ADDING A char MEMBER TO String::Sub
			TO AVOID RETURNING NULL WHEN String::Sub::getStartChar() IS CALLED AND THE 
			STRING IS EMPTY. NOTE THAT crx::c::String ALSO NEVER RETURNS A NULL WHEN
			SUCH FUNCTIONS ARE CALLED, AS AS crx::c::String::getElementsPointer().
*/


typedef size_t(* Crx_C_String_Range_Select)(char const * pChar, char const * pEndChar);

/*
CONTRACT:
	IS FIXED SIZE:			1
	HAS CONSTRUCT:		 	1
	HAS DESTRUCT:		 	0
	IS COPYABLE:			1
	HAS COPY CONSTRUCT:		0
	HAS MOVE CONSTRUCT:		0
	HAS MOVE DESTRUCT:		0
*/
typedef struct Crx_C_String_Sub
{
	Crx_C_String const * CRX_NOT_MINE gPrivate_string;
	uint32_t gPrivate_startIndex;
	uint32_t gPrivate_endIndex;
	char PRIVATE__CHAR; /*= '\0'*/
} Crx_C_String_Sub;

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_sub_construct(Crx_C_String_Sub * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_sub_construct2(Crx_C_String_Sub * pThis,
		Crx_C_String const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_sub_construct3(Crx_C_String_Sub * pThis,
		Crx_C_String const * pString, size_t pStart, size_t pEnd);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String_Sub * crx_c_string_sub_new();
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String_Sub * crx_c_string_sub_new2(
		Crx_C_String const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_String_Sub * crx_c_string_sub_new3(
		Crx_C_String const * pString, size_t pStart, size_t pEnd);

CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_setRange(Crx_C_String_Sub * pThis,
		size_t pStart, size_t pEnd);

CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_setString(Crx_C_String_Sub * pThis,
		Crx_C_String const * pString);
CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_setString2(Crx_C_String_Sub * pThis,
		Crx_C_String const * pString, size_t pStart, size_t pEnd);

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getSubStartIndex(
		Crx_C_String_Sub const * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getSubEndIndex(Crx_C_String_Sub const * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_sub_setNoRange(Crx_C_String_Sub * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_string_sub_unsetString(Crx_C_String_Sub * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getLength(Crx_C_String_Sub const * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() char const * crx_c_string_sub_getCharsPointer(
		Crx_C_String_Sub const * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() char crx_c_string_sub_copyGet(Crx_C_String_Sub const * pThis, 
		size_t pIndex);

CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_leftCut(Crx_C_String_Sub * pThis, 
		size_t pLength);
CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_rightCut(Crx_C_String_Sub * pThis, 
		size_t pLength);

CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_leftExtend(Crx_C_String_Sub * pThis,
		size_t pLength);
CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_rightExtend(Crx_C_String_Sub * pThis, 
		size_t pLength);


CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEmpty(Crx_C_String_Sub const * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_string_sub_trim(Crx_C_String_Sub * pThis,
		unsigned char pLowerByteValue, unsigned char pUpperByteValue);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEqualTo(Crx_C_String_Sub const * pThis,
		Crx_C_String const * CRX_NOT_NULL pString, bool pIsCaseInSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEqualTo2(Crx_C_String_Sub const * pThis,
		char const * CRX_NOT_NULL pString, bool pIsCaseInSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEqualTo3(Crx_C_String_Sub const * pThis,
		char const * CRX_NOT_NULL pChars, size_t pLength, bool pIsCaseInSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEqualTo4(Crx_C_String_Sub const * pThis,
		Crx_C_String_Sub * CRX_NOT_NULL pSub, bool pIsCaseInSensitive);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isBeginningWith(Crx_C_String_Sub const * pThis,
		Crx_C_String const * CRX_NOT_NULL pString, bool pIsCaseInSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isBeginningWith2(Crx_C_String_Sub const * pThis,
		char const * CRX_NOT_NULL pString, bool pIsCaseInSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isBeginningWith3(Crx_C_String_Sub const * pThis,
		char const * CRX_NOT_NULL pChars, size_t pLength, bool pIsCaseInSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isBeginningWith4(Crx_C_String_Sub const * pThis,
		Crx_C_String_Sub const * CRX_NOT_NULL pSub, bool pIsCaseInSensitive);

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEndingWith(Crx_C_String_Sub const * pThis,
		Crx_C_String const * CRX_NOT_NULL pString, bool pIsCaseInSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEndingWith2(Crx_C_String_Sub const * pThis,
		char const * CRX_NOT_NULL pString, bool pIsCaseInSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEndingWith3(Crx_C_String_Sub const * pThis,
		char const * CRX_NOT_NULL pChars, size_t pLength, bool pIsCaseInSensitive);
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_isEndingWith4(Crx_C_String_Sub const * pThis,
		Crx_C_String_Sub const * CRX_NOT_NULL pSub, bool pIsCaseInSensitive);

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstOccuranceOf(
		Crx_C_String_Sub const * pThis, size_t pStartIndex, 
		Crx_C_String const * CRX_NOT_NULL pDelimiter, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstOccuranceOf2(
		Crx_C_String_Sub const * pThis, size_t pStartIndex, 
		char const * CRX_NOT_NULL pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstOccuranceOf3(
		Crx_C_String_Sub const * pThis, size_t pStartIndex, 
		char const * CRX_NOT_NULL pChars__delimiter, 
		size_t pLength, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstOccuranceOf4(
		Crx_C_String_Sub const * pThis, size_t pStartIndex, 
		Crx_C_String_Sub const * CRX_NOT_NULL pSub__delimiter, 
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstReverseOccuranceOf(
		Crx_C_String_Sub const * pThis, size_t pInclusiveEndIndex, 
		Crx_C_String const * CRX_NOT_NULL pDelimiter, 
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstReverseOccuranceOf2(
		Crx_C_String_Sub const * pThis, size_t pInclusiveEndIndex, 
		char const * CRX_NOT_NULL pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstReverseOccuranceOf3(
		Crx_C_String_Sub const * pThis, size_t pInclusiveEndIndex, 
		char const * CRX_NOT_NULL pChars__delimiter, 
		size_t pLength, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_string_sub_getIndexOfFirstReverseOccuranceOf4(
		Crx_C_String_Sub const * pThis, size_t pInclusiveEndIndex, 
		Crx_C_String_Sub const * CRX_NOT_NULL pSub__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllOccurancesOf(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, Crx_C_String const * CRX_NOT_NULL pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllOccurancesOf2(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, char const * CRX_NOT_NULL pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllOccurancesOf3(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, char const * CRX_NOT_NULL pChars__delimiter, size_t pLength,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllOccurancesOf4(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pStartIndex, Crx_C_String_Sub const * CRX_NOT_NULL pSub__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllReverseOccurancesOf(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, Crx_C_String const * CRX_NOT_NULL pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllReverseOccurancesOf2(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, char const * CRX_NOT_NULL pDelimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllReverseOccurancesOf3(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, char const * CRX_NOT_NULL pChars__delimiter, size_t pLength,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_computeIndicesOfAllReverseOccurancesOf4(
		Crx_C_String_Sub const * pThis, Crx_C_Arrays_Size * CRX_NOT_NULL pReturn,
		size_t pInclusiveEndIndex, Crx_C_String_Sub const * CRX_NOT_NULL pSub__delimiter,
		bool pIsToAllowOverlap, uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findNextLeftTokenAndUpdateIndex(
		Crx_C_String_Sub const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, Crx_C_String const * CRX_NOT_NULL pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findNextLeftTokenAndUpdateIndex2(
		Crx_C_String_Sub const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, char const * CRX_NOT_NULL pString,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findNextLeftTokenAndUpdateIndex3(
		Crx_C_String_Sub const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, char const * CRX_NOT_NULL pChars__delimiter, size_t pLength,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findNextLeftTokenAndUpdateIndex4(
		Crx_C_String_Sub const * pThis, Crx_C_String_Sub * CRX_NOT_NULL pReturn, 
		size_t * CRX_NOT_NULL pIndex, 
		Crx_C_String_Sub const * CRX_NOT_NULL pSub__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findAllTokensStartingFromLeft(
		Crx_C_String_Sub const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, Crx_C_String const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findAllTokensStartingFromLeft2(
		Crx_C_String_Sub const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, char const * pDelimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findAllTokensStartingFromLeft3(
		Crx_C_String_Sub const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, char const * CRX_NOT_NULL pChars__delimiter, size_t pLength,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_string_sub_findAllTokensStartingFromLeft4(
		Crx_C_String_Sub const * pThis, Crx_C_String_Arrays_Sub * CRX_NOT_NULL pReturn,
		size_t pIndex, Crx_C_String_Sub const * pSub__delimiter,
		uint8_t pSizeOfCharacterSet CRX_DEFAULT(0));


		
//---------------------------
//CLASS: String::Arrays_Sub
//---------------------------
#if(defined(UINT32_MAX))
	#define CRX__C__STRING__ARRAYS__SUB__PRIVATE__SIZE32_T uint32_t
	#define CRX__C__STRING__ARRAYS__SUB__PRIVATE__SIZE32_MAX UINT32_MAX
#else
	#ifdef SIZE_MAX
		#define CRX__C__STRING__ARRAYS__SUB__PRIVATE__SIZE32_T size_t
		#define CRX__C__STRING__ARRAYS__SUB__PRIVATE__SIZE32_MAX SIZE_MAX
	#else
		#define CRX__C__STRING__ARRAYS__SUB__PRIVATE__SIZE32_T uint32_t
		#define CRX__C__STRING__ARRAYS__SUB__PRIVATE__SIZE32_MAX ((uint32_t)(-1))
	#endif
#endif



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
CRX__C__Array__DECLARE(Crx_C_String_Arrays_Sub, crx_c_string_arrays_sub_, Crx_C_String_Sub,
		CRX__C__STRING__ARRAYS__SUB__PRIVATE__SIZE32_T, 
				CRX__C__STRING__ARRAYS__SUB__PRIVATE__SIZE32_MAX, 0, CRXM__FALSE, 
		CRXM__FALSE, CRXM__FALSE, 
		CRXM__FALSE, CRXM__FALSE)
		
CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/String.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif