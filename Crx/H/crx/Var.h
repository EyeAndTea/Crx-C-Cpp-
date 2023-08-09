#if(!defined(CRX__VAR___h__))
#define CRX__VAR___h__
#pragma once

/*
The following is to disable a warning caused by deprecated names of POSIX functions,
and these have been deprecated since 2005 if not before. In particular, the function
strdup() which is popular. The following is a temporary solution to stop the warning
which is getting treated as an error because in the project settings I have
"SDL Checks" enabled, and I wish to keep it that way. Unfortuanely disabling the
macro for a single line using "#pragma supress" is not possible in my case because
the call to strdup() is part of a macro. I would have to use a macro provided
by C++11 (__Pragma), or a macro provided by Microsoft (__pragma), to be able
to use #pragma inside macros. For backward compatibility, I am avoiding this
for now.

update: decided to use a macro instead. It appears ::_strdup() is found
in older windows and thus Visual Studio 6. However, I could still be wrong.
See CRX__VAR__KHASH__PRIVATE__STRDUP
*/
//#pragma warning(disable : 4996)

#include <boost/version.hpp>
#include "Crx/H/crx/crx.h"
#pragma push_macro("CRX__LIB__MODE")
#undef CRX__LIB__MODE
#if(!defined(CRX__CONFIG__MODE))
	#define CRX__CONFIG__MODE CRX__LIB__MODE__STAND_ALONE
#endif
#define CRX__LIB__MODE CRX__CONFIG__MODE
//<<START>>	INCLUDE ".h" OF NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE.
#include "Crx/OPTION.H/crx/Var.option.h"
//#include <boost/cstdint.hpp>
#include <doubleConversion/double-conversion.h>
#include <deque>
//#include <boost/algorithm/searching/boyer_moore.hpp>
#if(defined(BOOST_VERSION) && (BOOST_VERSION >= 105500))
	#include <boost/core/explicit_operator_bool.hpp>
#endif
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/predef.h>
#include <boost/type_traits/remove_cv.hpp>
#include <locale>
#include <string>
#include <vector>
#include <cmath>
#include <cstddef>
#include <klib/khash.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <cstdio>
#include "Crx/H/crx/ClassUnorderedMap.h"
#include "Crx/H/crx/c/Ring.h"
#include "Crx/H/crx/c/char.h"
//<<END>>




namespace crx
{
	#pragma region MACROS: PUBLIC //{
		
		#pragma region MACROS: CONFIG //{

#if(!defined(CRX__VAR__CONFIG__ARE_EXCEPTIONS_ENABLED))
	#define CRX__VAR__CONFIG__ARE_EXCEPTIONS_ENABLED CRXM__TRUE
#endif
#if(!defined(CRX__VAR__CONFIG__INT_MODE))
	#define CRX__VAR__CONFIG__INT_MODE CRX__VAR__OPTION__INT_MODE__32BIT
#endif
#if(!defined(CRX__VAR__CONFIG__HASH_TABLE_IMPLEMENTATION))
	#define CRX__VAR__CONFIG__HASH_TABLE_IMPLEMENTATION CRX__VAR__OPTION__HASH_TABLE_IMPLEMENTATION__SORTED_KHASH
#endif
#if(!defined(CRX__VAR__CONFIG__ERROR_MODE))
	#define CRX__VAR__CONFIG__ERROR_MODE CRX__VAR__OPTION__ERROR_MODE__PROPOGATER
#endif
#if(!defined(CRX__VAR__CONFIG__ARRAY_IMPLEMENTATION))
	#define CRX__VAR__CONFIG__ARRAY_IMPLEMENTATION CRX__VAR__OPTION__ARRAY_IMPLEMENTATION__VARRING
#endif
#if(!defined(CRX__VAR__CONFIG__IS_ERROR_TYPE_AVAILABLE_FOR_PUBLIC_USE))
	#define CRX__VAR__CONFIG__IS_ERROR_TYPE_AVAILABLE_FOR_PUBLIC_USE CRXM__TRUE
#endif

		#pragma endregion MACROS: CONFIG //}

	/*
		IMPORTANT MUST BE ONE 'LESS' ON EACH SIDE THAN WHAT DOUBLE CAN SUPPORT. THIS
		IS USEFUL FOR MACHINES WHERE WE DOUBLE TO SUPPORT INTEGERS LARGER THAN 32BIT, AND
		ON THOSE MACHINES WE CAN NOT USE 64BIT INTEGERS TO DETECT OVERFLOWS WHEN THE INNER TYPE
		OF VAR IS DOUBLE. FOR EXAMPLE, THE MAXIMUM INTEGER VALUE THAT IS INDEED SAFE TO 
		STORE IN A DOUBLE IS 9007199254740992. IF WE CONVERT THAT TO INT64 AND ADD 1, WE CAN DETECT
		THE OVERFLOW BECAUSE WE WILL GET 9007199254740993. IF WE CAN USE INT64, AND KEEP IT A DOUBLE,
		AND ADD 1, THE VALUE WILL NOT CHANGE AND WE WILL CONTINUE TO GET 9007199254740992.
	*/
	#define CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE 4503599627370494
	#define CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE -4503599627370494
		
#if(CRX__FALSE && defined(__cplusplus) && (__cplusplus >= 201103L))
	#define CRX__VAR__FOREACH(pA, pB) \
	{ \
		for(pA : pB) \
		{ 

	#define CRX__VAR__END_FOREACH \
		} \
	}
#else
	#define CRX__VAR__FOREACH(pA, pB, pD) \
	{ \
		::crx::Var & _tVar ## pD = pB; \
		::crx::Var::iterator _tI ## pD = _tVar ## pD.begin(); \
		::crx::Var::iterator _tEnd ## pD = _tVar ## pD.end(); \
\
		for(; _tI ## pD != _tEnd ## pD; ++_tI ## pD) \
		{ \
			pA = *_tI ## pD;

	#define CRX__VAR__END_FOREACH \
		} \
	}
#endif
		

	#pragma endregion MACROS: PUBLIC //}

	/*
	NOTE: NAME NAMESPCAES OF MACROS IN THE FOLLOWING REGION DO NOT REFLECT NAMESPACES. AN 
			UNFORTUANTE LIMITATION OF NAME NAMESPACES WHERE ONE CAN NOT DIFFERENTIATE BETWEEN
			WHAT MAPS TO NAMESPACES, OR CLASSES, OR FUNCTIONS, OR OTHER NAME SPACES, ALL AS
			DEFINED IN MY STANDARD.
	*/
	#pragma region MACROS: PRIVATE //{

		#pragma region VAR: MASKS //{

	#define CRX__VAR__TYPE_NULL  0x00
	#define CRX__VAR__TYPE_UNDEFINED 0x01
	#define CRX__VAR__TYPE_STRING 0x02
	#define CRX__VAR__TYPE_HASH_TABLE 0x03
	#define CRX__VAR__TYPE_ARRAY 0x04
	#define CRX__VAR__TYPE_UNSIGNED_CHAR 0x05
	#define CRX__VAR__TYPE_SIGNED_INT32 0x06
	#define CRX__VAR__TYPE_SIGNED_INT64 0x07
	#define CRX__VAR__TYPE_EMULATED_INT 0x08
	#define CRX__VAR__TYPE_DOUBLE 0x09
	#define CRX__VAR__TYPE_BOOL 0x0A
	#define CRX__VAR__TYPE_POINTER 0x0B
	#define CRX__VAR__TYPE_ERROR 0x0C
	
	//10000000b
	#define CRX__VAR__DATA_BIT_MASK__THREAD_POSSIBLE	0x80
	//00011111b
	#define CRX__VAR__DATA_BIT_MASK__TYPE	0x1F
	//10000000b
	#define CRX__VAR__THREAD_MODE_POSSIBLE 0x80

	/*
	THE FOLLOWING ARE NEEDED IN CASE I SWITCH BACK TO USING FULL FIELDS, LIKE THE OLD gDataType,
			BUT INSIDE gInfo, INSTEAD OF BIT MASKS. CURRENTLY AVOIDING THAT TO KEEP
			THE SIZE OF THE INTERNAL BUFFERS AS LARGE AS POSSIBLE.
	*/
	#define CRX__VAR__GET_TYPE1(pVarObject) (CRX__VAR__DATA_BIT_MASK__TYPE & pVarObject->gData.uInfo.gInfo)
	#define CRX__VAR__GET_TYPE2(pVarObject) (CRX__VAR__DATA_BIT_MASK__TYPE & pVarObject.gData.uInfo.gInfo)
	#define CRX__VAR__SET_TYPE(pVarObject, pType) pVarObject->gData.uInfo.gInfo = \
			((pVarObject->gData.uInfo.gInfo & ~CRX__VAR__DATA_BIT_MASK__TYPE) | pType)
	#define CRX__VAR__SET_TYPE2(pVarObject, pType) pVarObject.gData.uInfo.gInfo = \
			((pVarObject.gData.uInfo.gInfo & ~CRX__VAR__DATA_BIT_MASK__TYPE) | pType)
	//VC6: TO AVOID WARNINGS
	//#define CRX__VAR__GET_IS_THREAD_POSSIBLE1(pVarObject) (CRX__VAR__DATA_BIT_MASK__THREAD_POSSIBLE & pVarObject->gData.uInfo.gInfo)
	//#define CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVarObject) (CRX__VAR__DATA_BIT_MASK__THREAD_POSSIBLE & pVarObject.gData.uInfo.gInfo)
	#define CRX__VAR__GET_IS_THREAD_POSSIBLE1(pVarObject) ((CRX__VAR__DATA_BIT_MASK__THREAD_POSSIBLE & pVarObject->gData.uInfo.gInfo) != 0)
	#define CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVarObject) ((CRX__VAR__DATA_BIT_MASK__THREAD_POSSIBLE & pVarObject.gData.uInfo.gInfo) != 0)
	
		#pragma endregion VAR: MASKS //}

		#pragma region VAR: INTEGERS //{

	/*CRX__VAR__INT_MODE */
	#if(CRX__VAR__CONFIG__INT_MODE == CRX__VAR__OPTION__INT_MODE__64BIT)
		#if(!defined(CRX__BOOST_NO_INT64_T))
			#define CRX__VAR__INT_MODE  CRX__VAR__OPTION__INT_MODE__64BIT
		#else
			#define CRX__VAR__INT_MODE  CRX__VAR__OPTION__INT_MODE__32BIT
		#endif
	#elif(CRX__VAR__CONFIG__INT_MODE == CRX__VAR__OPTION__INT_MODE__32BIT)
		#define CRX__VAR__INT_MODE  CRX__VAR__OPTION__INT_MODE__32BIT
	#else
		#define CRX__VAR__INT_MODE  CRX__VAR__OPTION__INT_MODE__EMULATED
	#endif

	#if((defined(_M_X64) || defined(_M_AMD64) || defined(_WIN64) || defined(WIN64) || \
			defined(__amd64__) || defined(__amd64) || \
			defined(__x86_64) || defined(__x86_64__) || defined(_LP64) || defined(__LP64__) || \
			(defined(INTPTR_MAX) && (INTPTR_MAX == INT64_MAX))) && !defined(__ILP32__))
		#define CRX__VAR__IS_MACHINE_64BIT CRXM__TRUE
		#define CRX__VAR__IS_MACHINE_32BIT CRXM__FALSE
	#else
		#define CRX__VAR__IS_MACHINE_64BIT CRXM__FALSE
		#define CRX__VAR__IS_MACHINE_32BIT CRXM__TRUE
	#endif

	#if(CRX__VAR__IS_MACHINE_64BIT)
		#define CRX__VAR__MACHINE_SIGNED_INT int64_t
		#define CRX__VAR__MACHINE_SIGNED_INT_MAX INT64_MAX
		#define CRX__VAR__MACHINE_SIGNED_INT_MIN INT64_MIN

		#define CRX__VAR__MACHINE_UNSIGNED_INT uint64_t
		#define CRX__VAR__MACHINE_UNSIGNED_INT_MAX UINT64_MAX
	#else
		#define CRX__VAR__MACHINE_SIGNED_INT int32_t
		#define CRX__VAR__MACHINE_SIGNED_INT_MAX INT32_MAX
		#define CRX__VAR__MACHINE_SIGNED_INT_MIN INT32_MIN

		#define CRX__VAR__MACHINE_UNSIGNED_INT uint32_t
		#define CRX__VAR__MACHINE_UNSIGNED_INT_MAX UINT32_MAX
	#endif
	
	#define CRX__VAR__IS_TWOS_COMPLEMENT_MACHINE (-1 == ~0)
	#define CRX__VAR__IS_ONES_COMPLEMENT_MACHINE (-1 != ~0) && (~0 != -CRX__VAR__MACHINE_SIGNED_INT_MAX)
	#define CRX__VAR__IS_SIGN_MAGNITUDE_MACHINE (~0 == -CRX__VAR__MACHINE_SIGNED_INT_MAX)

	/*WARNING: THE FOLLOWING FOUR CHECKS ASSUME 2'S COMPLEMENT*/
	#define CRX__VAR__WILL_ADD_ON_INT64_OVERFLOW(T1, T2) (((T2 > 0) && (T1 > INT64_MAX - T2)) || \
			((T2 < 0) && (T1 < INT64_MIN - T2)))
	#define CRX__VAR__WILL_SUBTRACT_ON_INT64_OVERFLOW(T1, T2) (((T2 < 0) && (T1 > INT64_MAX + T2)) || \
			((T2 > 0) && (T1 < INT64_MIN + T2)))
	#define CRX__VAR__WILL_MULTIPLY_ON_INT64_OVERFLOW(T1, T2) (T1 != 0) && (T2 != 0) && \
			(((T1 == -1) && (T2 == INT64_MIN)) || \
			((T2 == -1) && (T1 == INT64_MIN)) || \
			(T1 > INT64_MAX / T2) || \
			((T1 < INT64_MIN / T2)))
	#define CRX__VAR__WILL_DIVISION_ON_INT64_OVERFLOW(T1, T2) (((T1 == INT64_MIN) && (T2 == -1)) || \
			(T2 == 0))

	/*WARNING: THE FOLLOWING FOUR CHECKS ASSUME 2'S COMPLEMENT*/
	#define CRX__VAR__WILL_ADD_ON_INT32_OVERFLOW(T1, T2) (((T2 > 0) && (T1 > INT32_MAX - T2)) || \
			((T2 < 0) && (T1 < INT32_MIN - T2)))
	#define CRX__VAR__WILL_SUBTRACT_ON_INT32_OVERFLOW(T1, T2) (((T2 < 0) && (T1 > INT32_MAX + T2)) || \
			((T2 > 0) && (T1 < INT32_MIN + T2)))
	#define CRX__VAR__WILL_MULTIPLY_ON_INT32_OVERFLOW(T1, T2) (T1 != 0) && (T2 != 0) && \
			(((T1 == -1) && (T2 == INT32_MIN)) || \
			((T2 == -1) && (T1 == INT32_MIN)) || \
			(T1 > INT32_MAX / T2) || \
			((T1 < INT32_MIN / T2)))
	#define CRX__VAR__WILL_DIVISION_ON_INT32_OVERFLOW(T1, T2) (((T1 == INT32_MIN) && (T2 == -1)) || \
			(T2 == 0))
	
	/*
	NOTES:
		- "UNIFIED SIGNED INTEGER" IS THE TYPE OF THE INTERNAL INTEGER WHEN IT IS AN ACTUAL INTEGRAL. CURRENTLY,
				THIS MEANS INT64 OR INT32.
		- "INTERNAL INTEGER" IS THE TYPE OF THE INTERNAL INTEGER WHETHER IT IS AN ACTUAL INTEGER OR NOT. CURRENTLY,
				THIS MEANS INT64 OR INT32 OR DOUBLE.
				IN THE PAST TRYING TO TREAT ALL INTEGERS IN THE CODE WITH ONE CODE PROVED IMPOSSIBLE, BUT
				PROVED ALMOST POSSIBLE FOR THE INT64 AND INT32. FOR EXAMPLE, CODE CHECKS FOR WPG, SUCH AS RANGE 
				AND OVERFLOW CHECKS, ARE DIFFERENT WHEN THE INTERNAL INTEGER IS A DOUBLE FROM WHEN IT IS AN 
				INT64 OR INT32. CURRENTLY, SOME LIKE "CRX__VAR__INTERNAL_INT" IS ONLY NEEDED FOR WHEN
				MORPHING IS REQUIRED FROM DOUBLES TO THE INTERNAL INTEGER, IN OTHER WORDS, THE VAR TYPE INTEGER.
				CURRENTLY THIS ONLY HAPPENS FOR THE BIT OPERATORS, & AND | AND ^.
	*/
	#if(CRX__VAR__INT_MODE == CRX__VAR__OPTION__INT_MODE__64BIT)
		#define CRX__VAR__IS_EMULATED_INT_USED CRXM__FALSE
		#define CRX__VAR__UNIFIED_SIGNED_INT int64_t
		#define CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64 CRXM__TRUE
		#define CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32 CRX__VAR__TYPE_SIGNED_INT64
		#define CRX__VAR__GET_UNIFIED_INT_VARIABLE1(T1) T1->gData.uIntegral.uSignedInt64
		#define CRX__VAR__GET_UNIFIED_INT_VARIABLE2(T1) T1.gData.uIntegral.uSignedInt64
		#define CRX__VAR__GET_INTERNAL_INT_VARIABLE1(T1) T1->gData.uIntegral.uSignedInt64
		#define CRX__VAR__GET_INTERNAL_INT_VARIABLE2(T2) T1.gData.uIntegral.uSignedInt64
		#define CRX__VAR__CONVERT_TO_UNIFIED_INT Var::convertToSignedInt64
		#define CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT Var::looseConvertToSignedInt64
		#define CRX__VAR__STRINGIFY_UNIFIED_INT Var::stringifyInt64
		#define CRX__VAR__INTERNAL_INT int64_t
		#define CRX__VAR__INTERNAL_INT_MAX INT64_MAX
		#define CRX__VAR__INTERNAL_INT_MIN INT64_MIN

		/*WARNING: THE FOLLOWING FOUR CHECKS ASSUME 2'S COMPLEMENT*/
		#define CRX__VAR__WILL_ADD_ON_UNIFIED_INT_OVERFLOW(T1, T2) CRX__VAR__WILL_ADD_ON_INT64_OVERFLOW(T1, T2) 
		#define CRX__VAR__WILL_SUBTRACT_ON_UNIFIED_INT_OVERFLOW(T1, T2) CRX__VAR__WILL_SUBTRACT_ON_INT64_OVERFLOW(T1, T2)
		#define CRX__VAR__WILL_MULTIPLY_ON_UNIFIED_INT_OVERFLOW(T1, T2) CRX__VAR__WILL_MULTIPLY_ON_INT64_OVERFLOW(T1, T2)
		#define CRX__VAR__WILL_DIVISION_ON_UNIFIED_INT_OVERFLOW(T1, T2) CRX__VAR__WILL_DIVISION_ON_INT64_OVERFLOW(T1, T2)

		/*THE ASSUMPTION WHEN THESE ARE CALLED IS THAT THE CURRENT TYPE IS EITHER DOUBLE OR EMULATED INT*/
		#define CRX__VAR_SET_TYPE_TO_DOUBLE_FROM_EMULATED_INT(T1) 
		#define CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(T1) \
				CRX__VAR__SET_TYPE(T1, CRX__VAR__TYPE_SIGNED_INT64);
	#elif(CRX__VAR__INT_MODE == CRX__VAR__OPTION__INT_MODE__32BIT)
		#define CRX__VAR__IS_EMULATED_INT_USED CRXM__FALSE
		#define CRX__VAR__UNIFIED_SIGNED_INT int32_t
		#define CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64 CRXM__FALSE
		#define CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32 CRX__VAR__TYPE_SIGNED_INT32
		#define CRX__VAR__GET_UNIFIED_INT_VARIABLE1(T1) T1->gData.uIntegral.uSignedInt32
		#define CRX__VAR__GET_UNIFIED_INT_VARIABLE2(T1) T1.gData.uIntegral.uSignedInt32
		#define CRX__VAR__GET_INTERNAL_INT_VARIABLE1(T1) T1->gData.uIntegral.uSignedInt32
		#define CRX__VAR__GET_INTERNAL_INT_VARIABLE2(T2) T1.gData.uIntegral.uSignedInt32
		#define CRX__VAR__CONVERT_TO_UNIFIED_INT Var::convertToSignedInt32
		#define CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT Var::looseConvertToSignedInt32
		#define CRX__VAR__STRINGIFY_UNIFIED_INT Var::stringifyInt32
		#define CRX__VAR__INTERNAL_INT int32_t
		#define CRX__VAR__INTERNAL_INT_MAX INT32_MAX
		#define CRX__VAR__INTERNAL_INT_MIN INT32_MIN

		/*WARNING: THE FOLLOWING FOUR CHECKS ASSUME 2'S COMPLEMENT*/
		#define CRX__VAR__WILL_ADD_ON_UNIFIED_INT_OVERFLOW(T1, T2) CRX__VAR__WILL_ADD_ON_INT32_OVERFLOW(T1, T2) 
		#define CRX__VAR__WILL_SUBTRACT_ON_UNIFIED_INT_OVERFLOW(T1, T2) CRX__VAR__WILL_SUBTRACT_ON_INT32_OVERFLOW(T1, T2)
		#define CRX__VAR__WILL_MULTIPLY_ON_UNIFIED_INT_OVERFLOW(T1, T2) CRX__VAR__WILL_MULTIPLY_ON_INT32_OVERFLOW(T1, T2)
		#define CRX__VAR__WILL_DIVISION_ON_UNIFIED_INT_OVERFLOW(T1, T2) CRX__VAR__WILL_DIVISION_ON_INT32_OVERFLOW(T1, T2)

		/*THE ASSUMPTION WHEN THESE ARE CALLED IS THAT THE CURRENT TYPE IS EITHER DOUBLE OR EMULATED INT*/
		#define CRX__VAR_SET_TYPE_TO_DOUBLE_FROM_EMULATED_INT(T1) 
		#define CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(T1) \
				CRX__VAR__SET_TYPE(T1, CRX__VAR__TYPE_SIGNED_INT32);
	#else
		#define CRX__VAR__IS_EMULATED_INT_USED CRXM__TRUE
		#define CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64 CRXM__FALSE
		#define CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32 CRX__VAR__TYPE_SIGNED_INT32
		#define CRX__VAR__GET_UNIFIED_INT_VARIABLE1(T1) T1->gData.uIntegral.uSignedInt32
		#define CRX__VAR__GET_UNIFIED_INT_VARIABLE2(T1) T1.gData.uIntegral.uSignedInt32
		#define CRX__VAR__GET_INTERNAL_INT_VARIABLE1(T1) T1->gData.uIntegral.uDouble
		#define CRX__VAR__GET_INTERNAL_INT_VARIABLE2(T2) T1.gData.uIntegral.uDouble
		#define CRX__VAR__CONVERT_TO_UNIFIED_INT Var::convertToSignedInt32
		#define CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT Var::looseConvertToSignedInt32
		#define CRX__VAR__STRINGIFY_UNIFIED_INT Var::stringifyInt32
		#define CRX__VAR__INTERNAL_INT double
		#define CRX__VAR__INTERNAL_INT_MAX CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE
		#define CRX__VAR__INTERNAL_INT_MIN CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE

		/*THE ASSUMPTION WHEN THESE ARE CALLED IS THAT THE CURRENT TYPE IS EITHER DOUBLE OR EMULATED INT*/
		#define CRX__VAR_SET_TYPE_TO_DOUBLE_FROM_EMULATED_INT(T1) \
				if(CRX__VAR__GET_TYPE1(T1) == CRX__VAR__TYPE_EMULATED_INT) \
					{CRX__VAR__SET_TYPE(T1, CRX__VAR__TYPE_DOUBLE);}
		#define CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(T1) \
				CRX__VAR__SET_TYPE(T1, CRX__VAR__TYPE_EMULATED_INT);
	#endif
	
	#define CRX__VAR__INT_STRING_MAX CRX__VAR__INTERNAL_INT_MAX
	#define CRX__VAR__INT_STRING_MIN CRX__VAR__INTERNAL_INT_MIN
	
		#pragma endregion VAR: INTEGERS //}
	
		#pragma region VAR: STRINGS //{

	#define CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING CRXM__FALSE

	/*
	THE FOLLOWING CAN BE DECREASED TO 13 WHILE STILL BENEFITING. HOWEVER, ANYTHING LOWER THAN
	29 GIVES NO BENEFIT IF THE ARRAY IMPLEMENTATION IS A VarRing INSTANCE ON THE VAR ITSELF,
	MEANING THAT CRX__VAR__CONFIG__ARRAY_IMPLEMENTATION IS SET TO 
	CRX__VAR__OPTION__ARRAY_IMPLEMENTATION__VARRING
	ANYTHING LOWER THAN 13 WILL GIVE WRONG RESULT TO THE CALCULATION OF THE FILLER SIZE
	IN THE Var::Data union. NOTE THAT IT IS ASSUMED THAT double IS EIGHT BYTE ALIGNED.
	*/
	#define CRX__VAR__SIZE_OF_STRING_STRING_BUFFER 29
	/*	24 BYTES ARE NEEDED TO FIT ANY MINIMAL DOUBLE STRING REPRESENTATION THAT CAN ROUNDTRIP 
			BACK TO THE THE ORIGINAL DOUBLE, WITHOUT THE NULL CHARACTER. I HAD TO USE LESS
			BECAUSE OTHERWISE THE sizeof(Var) WILL BE LARGER THAN 32
		BECAUSE THE FOLLOWING IS ONLY USEFULL IN NOT THREAD POSSIBLE MODE, AND
			BECAUSE OF THE INABILITY TO CONDITIONALY USE THE STACK INSTEAD IN THAT CASE,
			THE FOLLOWING IS REMOVED.
	*/
	//#define CRX__VAR__SIZE_OF_TEMPORARY_STRING_BUFFER 23

	//WARNING: SMALL BUFFER MODE MUST REMAIN 0
	#define CRX__VAR__STRING__MODE__SMALL_BUFFER 0x00
	#define CRX__VAR__STRING__MODE__LARGE_BUFFER 0x40
	#define CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT 0x80
	#define CRX__VAR__STRING__MODE__ROPE 0xC0
	#define CRX__VAR__STRING__BIT_MASK__MODE 0xC0
	#define CRX__VAR__STRING__LIMITS__START_SIZE_FOR_COPY_ROPE 1000000

	#define CRX__VAR__STRING__GET_MODE1(pVarObject) (CRX__VAR__STRING__BIT_MASK__MODE & pVarObject->gData.uString.uStringInfo.gMode)
	#define CRX__VAR__STRING__GET_MODE2(pVarObject) (CRX__VAR__STRING__BIT_MASK__MODE & pVarObject.gData.uString.uStringInfo.gMode)
	#define CRX__VAR__STRING__SET_MODE(pVarObject, pMode) pVarObject->gData.uString.uStringInfo.gMode = \
			((pVarObject->gData.uString.uStringInfo.gMode & ~CRX__VAR__STRING__BIT_MASK__MODE) | pMode)
	#define CRX__VAR__STRING__SET_MODE2(pVarObject, pMode) pVarObject.gData.uString.uStringInfo.gMode = \
			((pVarObject.gData.uString.uStringInfo.gMode & ~CRX__VAR__STRING__BIT_MASK__MODE) | pMode)

	#define CRX__VAR__STRING__CORRECT_CAPACITY(CAPACITY, MINIMAL_CAPACITY) \
		while(CAPACITY - ::crx::Var::String::LENGTH_OF_OVERHEAD < MINIMAL_CAPACITY) \
				{CAPACITY = CAPACITY << 1;}

		#pragma endregion VAR: STRINGS //}

		#pragma region VAR: HASH TABLES //{

	/*CRX__VAR__HASH_TABLE_IMPLEMENTATION */
	#if(CRX__VAR__CONFIG__HASH_TABLE_IMPLEMENTATION == CRX__VAR__OPTION__HASH_TABLE_IMPLEMENTATION__KHASH)
		#define CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH CRXM__TRUE
		#define CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_HASH_TABLE_SORTED CRXM__FALSE
	#elif(CRX__VAR__CONFIG__HASH_TABLE_IMPLEMENTATION == CRX__VAR__OPTION__HASH_TABLE_IMPLEMENTATION__SORTED_KHASH)
		#define CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH CRXM__TRUE
		#define CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_HASH_TABLE_SORTED CRXM__TRUE
	#else
		#define CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH CRXM__FALSE
		#define CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_HASH_TABLE_SORTED CRXM__FALSE
	#endif
	
			#pragma region VAR: KHASH //{

#if defined(BOOST_OS_WINDOWS)
	#define CRX__VAR__KHASH__PRIVATE__STRDUP(I) ::_strdup(I)
#else
	#define CRX__VAR__KHASH__PRIVATE__STRDUP(I) ::strdup(I);
#endif

				#pragma region UNSORTED HASH TABLE //{

	#define CRX__VAR__VarKHash khash_t(crx_Var)
	#define CRX__VAR__VarKHash_new(RETURN) RETURN = kh_init(crx_Var)
	#define CRX__VAR__VarKHash_copyAddDifferenceFromVarKHash(_pThis, _pVarKHash, \
			_pArePossiblyCreatedVarsThreadPossible) \
	{ \
		CRX__VAR__VarKHash * pThis = _pThis; \
		CRX__VAR__VarKHash const * pVarKHash = _pVarKHash; \
		bool pArePossiblyCreatedVarsThreadPossible = _pArePossiblyCreatedVarsThreadPossible; \
		khiter_t vKhiter; \
	\
		if(pThis != pVarKHash) \
		{ \
			for(vKhiter = kh_begin(pVarKHash); \
					vKhiter != kh_end(pVarKHash); ++vKhiter) \
			{ \
				if(!kh_exist(pVarKHash, vKhiter)) \
					{continue;} \
	\
				const char * tKey = kh_key(pVarKHash, vKhiter); \
				int tReturnedCode = 0; \
				khiter_t tKhiter = kh_put(crx_Var, pThis, \
						tKey, &tReturnedCode); \
	\
				if(tReturnedCode > 0) \
				{ \
					Var * tVar = kh_value(pVarKHash, vKhiter); \
\
					kh_key(pThis, tKhiter) = CRX__VAR__KHASH__PRIVATE__STRDUP(tKey); \
					kh_value(pThis, tKhiter) = new Var(*tVar, pArePossiblyCreatedVarsThreadPossible); \
				} \
			} \
		} \
	}
	#define CRX__VAR__VarKHash_copyImpressFromVarKHash(_pThis, _pVarKHash) \
	{ \
		CRX__VAR__VarKHash * pThis = _pThis; \
		CRX__VAR__VarKHash const * pVarKHash__64556 = _pVarKHash; \
\
		if(pThis != pVarKHash__64556) \
		{ \
			khiter_t tKhiter; \
\
			for(tKhiter = kh_begin(pThis); tKhiter != kh_end(pThis); ++tKhiter) \
			{ \
				if(!kh_exist(pThis, tKhiter)) \
					{continue;} \
\
				if(kh_get(crx_Var, pVarKHash__64556, kh_key(pThis, tKhiter)) == \
						kh_end(pVarKHash__64556)) \
				{ \
					char * tKey = (char *)(kh_key(pThis, tKhiter)); \
					Var * tVar = kh_val(pThis, tKhiter); \
\
					kh_del(crx_Var, pThis, tKhiter); \
\
					free(tKey); \
					delete tVar; \
				} \
			} \
\
			for(tKhiter = kh_begin(pVarKHash__64556); tKhiter != kh_end(pVarKHash__64556); ++tKhiter) \
			{ \
				if(!kh_exist(pVarKHash__64556, tKhiter)) \
					{continue;} \
\
				if(kh_get(crx_Var, pThis, kh_key(pVarKHash__64556, tKhiter)) == kh_end(pThis)) \
				{ \
					int tReturnedCode = 0; \
					khiter_t tKhiter2 = kh_put(crx_Var, pThis, \
							CRX__VAR__KHASH__PRIVATE__STRDUP(kh_key(pVarKHash__64556, tKhiter)), \
							&tReturnedCode); \
\
					kh_value(pThis, tKhiter2) = new Var(*(kh_value(pVarKHash__64556, tKhiter))); \
				} \
			} \
		} \
	}
	#define CRX__VAR__VarKHash_copyUpdateFromVarKHash(_pThis, _pVarKHash) \
	{ \
		CRX__VAR__VarKHash * pThis = _pThis; \
		CRX__VAR__VarKHash const * pVarKHash__64556 = _pVarKHash; \
\
		if(pThis != pVarKHash__64556) \
		{ \
			khiter_t tKhiter; \
\
			for(tKhiter = kh_begin(pThis); tKhiter != kh_end(pThis); ++tKhiter) \
			{ \
				if(!kh_exist(pThis, tKhiter)) \
					{continue;} \
\
				khiter_t tKhiter2 = kh_get(crx_Var, pVarKHash__64556, kh_key(pThis, tKhiter)); \
\
				if(tKhiter2 != kh_end(pVarKHash__64556)) \
					{*(kh_val(pThis, tKhiter)) = *(kh_val(pVarKHash__64556, tKhiter2));} \
			} \
		} \
	}
	#define CRX__VAR__VarKHash_set(_pThis, _pKey, _pVar, _pIsPossiblyCreatedVarThreadPossible) \
	{ \
		CRX__VAR__VarKHash * pThis = _pThis; \
		char const * pKey__64556 = _pKey; \
		Var const * pVar__64556 = _pVar; \
		bool pIsPossiblyCreatedVarThreadPossible = _pIsPossiblyCreatedVarThreadPossible; \
		int vReturnedCode = 0; \
		khiter_t vKhiter = kh_put(crx_Var, pThis, pKey__64556, &vReturnedCode); /* add the key */ \
\
		if(vReturnedCode == 0) \
		{ \
			Var * tVar = kh_val(pThis, vKhiter); \
\
			delete tVar; \
		} \
		else \
			{kh_key(pThis, vKhiter) = CRX__VAR__KHASH__PRIVATE__STRDUP(pKey__64556);} \
\
		kh_value(pThis, vKhiter) = new Var(*pVar__64556, pIsPossiblyCreatedVarThreadPossible); /* set the value */ \
	}
	#define CRX__VAR__VarKHash_pilferDifferenceFromVarKHash(_pThis, _pVarKHash) \
	{ \
		CRX__VAR__VarKHash * pThis = _pThis; \
		CRX__VAR__VarKHash * pVarKHash__64556 = _pVarKHash; \
		khiter_t vKhiter; \
	\
		if(pThis != pVarKHash__64556) \
		{ \
			for(vKhiter = kh_begin(pVarKHash__64556); \
					vKhiter != kh_end(pVarKHash__64556); ++vKhiter) \
			{ \
				if(!kh_exist(pVarKHash__64556, vKhiter)) \
					{continue;} \
		\
				const char * tKey = kh_key(pVarKHash__64556, vKhiter); \
				Var * tVar = kh_value(pVarKHash__64556, vKhiter); \
				int tReturnedCode = 0; \
				khiter_t tKhiter = kh_put(crx_Var, pThis, \
						tKey, &tReturnedCode); \
		\
				if(tReturnedCode > 0) \
				{ \
					kh_value(pThis, tKhiter) = tVar; \
					kh_del(crx_Var, pVarKHash__64556, vKhiter); \
				} \
			} \
		} \
	}
	#define CRX__VAR__VarKHash_copyFromVarHashTable(_pThis, _pUnorderedMap) \
	{ \
		CRX__VAR__VarKHash * pThis = _pThis; \
		::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap__5645 = _pUnorderedMap; \
		::crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator vIterator = \
				pUnorderedMap__5645.begin(); \
	\
		while(vIterator != pUnorderedMap__5645.end()) \
		{\
			int tReturnedCode = 0; \
			khiter_t tKhiter = kh_put(crx_Var, pThis, \
					(*vIterator).first.c_str(), &tReturnedCode); \
	\
			if(tReturnedCode > 0) \
			{ \
				kh_key(pThis, tKhiter) = CRX__VAR__KHASH__PRIVATE__STRDUP((*vIterator).first.c_str()); \
				kh_value(pThis, tKhiter) = new Var((*vIterator).second); \
			} \
	\
			vIterator++;\
		} \
	}
	#define CRX__VAR__VarKHash_copyFromVarHashTable2(_pThis, _pUnorderedMap, \
			_pIsPossiblyCreatedVarThreadPossible) \
	{ \
		CRX__VAR__VarKHash * pThis = _pThis; \
		bool pIsPossiblyCreatedVarThreadPossible = _pIsPossiblyCreatedVarThreadPossible; \
		::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap__5645 = _pUnorderedMap; \
		::crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator vIterator = \
				pUnorderedMap__5645.begin(); \
	\
		while(vIterator != pUnorderedMap__5645.end()) \
		{\
			int tReturnedCode = 0; \
			khiter_t tKhiter = kh_put(crx_Var, pThis, \
					(*vIterator).first.c_str(), &tReturnedCode); \
	\
			if(tReturnedCode > 0) \
			{ \
				kh_key(pThis, tKhiter) = CRX__VAR__KHASH__PRIVATE__STRDUP((*vIterator).first.c_str()); \
				kh_value(pThis, tKhiter) = new Var((*vIterator).second, \
						pIsPossiblyCreatedVarThreadPossible); \
			} \
	\
			vIterator++;\
		} \
	}
	#define CRX__VAR__VarKHash_copyImpressFromVarHashTable(_pThis, _pUnorderedMap) \
	{ \
		CRX__VAR__VarKHash * pThis = _pThis; \
		::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap__5645 = _pUnorderedMap; \
		khiter_t vKhiter; \
		crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator vIterator = \
				pUnorderedMap__5645.begin(); \
\
		for(vKhiter = kh_begin(pThis); vKhiter != kh_end(pThis); ++vKhiter) \
		{ \
			if(!kh_exist(pThis, vKhiter) || \
					(pUnorderedMap__5645.count(kh_key(pThis, vKhiter)) == 1)) \
				{continue;} \
\
			char * tKey = const_cast<char *>(kh_key(pThis, vKhiter)); \
			Var * tVar = kh_val(pThis, vKhiter); \
\
			kh_del(crx_Var, pThis, vKhiter); \
\
			::free(tKey); \
			delete tVar; \
		} \
\
		while(vIterator != pUnorderedMap__5645.end()) \
		{ \
			if(kh_get(crx_Var, pThis, (*vIterator).first.c_str()) != kh_end(pThis)) \
				{continue;} \
\
			int tReturnedCode = 0; \
			khiter_t tKhiter = kh_put(crx_Var, pThis, \
					CRX__VAR__KHASH__PRIVATE__STRDUP((*vIterator).first.c_str()), &tReturnedCode); \
\
			kh_value(pThis, tKhiter) = new Var((*vIterator).second); \
\
			vIterator++; \
		} \
	}
	//VC6 COULD NOT USE at() FOR THE UNORDERED MAP FROM STLPORT
	#define CRX__VAR__VarKHash_copyUpdateFromVarHashTable(_pThis, _pUnorderedMap) \
	{ \
		CRX__VAR__VarKHash * pThis = _pThis; \
		::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap__5645 = _pUnorderedMap; \
		khiter_t vKhiter; \
		crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator vIterator = \
				pUnorderedMap__5645.begin(); \
\
		for(vKhiter = kh_begin(pThis); vKhiter != kh_end(pThis); ++vKhiter) \
		{ \
			if(!kh_exist(pThis, vKhiter) || \
					(pUnorderedMap__5645.count(kh_key(pThis, vKhiter)) == 0)) \
				{continue;} \
\
			*(kh_value(pThis, vKhiter)) = (*(pUnorderedMap__5645.find(kh_key(pThis, vKhiter)))).second; \
		} \
	}
	#define CRX__VAR__VarKHash_forceGet(_pThis, RETURN, _pKey, _pIsPossiblyCreatedVarThreadPossible) \
	{ \
		CRX__VAR__VarKHash * pThis = _pThis; \
		char const * pKey__5645 = _pKey; \
		bool pIsPossiblyCreatedVarThreadPossible = _pIsPossiblyCreatedVarThreadPossible; \
		::khiter_t vKhiter = kh_get(crx_Var, pThis, pKey__5645); \
	\
		if(vKhiter == kh_end(pThis)) \
		{ \
			Var * tVar = new Var(Var::Nil(), pIsPossiblyCreatedVarThreadPossible); \
			int tReturnedCode = 0; \
			::khiter_t tKhiter = kh_put(crx_Var, pThis, pKey__5645, &tReturnedCode); \
	\
			kh_key(pThis, tKhiter) = CRX__VAR__KHASH__PRIVATE__STRDUP(pKey__5645); \
			kh_value(pThis, tKhiter) = tVar; \
	\
			RETURN = tVar; \
		} \
		else \
		{ \
			RETURN = (kh_value(pThis, vKhiter)); \
		} \
	}
	#define CRX__VAR__VarKHash_getKeys(_pThis, RETURN) \
	{ \
		CRX__VAR__VarKHash * pThis = _pThis; \
		::std::vector<::std::string> vReturn; \
\
		for(khiter_t tKhiter = kh_begin(pThis); tKhiter != kh_end(pThis); ++tKhiter) \
		{ \
			if(!kh_exist(pThis, tKhiter)) \
				{continue;} \
\
			vReturn.push_back(const_cast<char const *>(kh_key(pThis, tKhiter))); \
		} \
\
		RETURN = vReturn; \
	}
	#define CRX__VAR__VarKHash_getIteratorStart(_pThis, RETURN) \
	{ \
		CRX__VAR__VarKHash * pThis = _pThis; \
		khiter_t vKhiter_543673; \
\
		for(vKhiter_543673 = kh_begin(pThis); vKhiter_543673 != kh_end(pThis); ++vKhiter_543673) \
		{ \
			if(kh_exist(pThis, vKhiter_543673)) \
				{break;} \
		} \
\
		RETURN = vKhiter_543673; \
	}
	#define CRX__VAR__VarKHash_getIteratorEnd(_pThis, RETURN) \
		{RETURN = kh_end(_pThis);}
	#define CRX__VAR__VarKHash_removeElementAt(_pThis, _pKey) \
	{ \
		CRX__VAR__VarKHash * pThis = _pThis; \
		char const * pKey__5645 = _pKey; \
		::khiter_t vKhiter = kh_get(crx_Var, pThis, pKey__5645); \
\
		if(vKhiter != kh_end(pThis)) \
		{ \
			char * tKey = (char *)(kh_key(pThis, vKhiter)); \
			Var * tVar = kh_val(pThis, vKhiter); \
\
			kh_del(crx_Var, pThis, vKhiter); \
\
			free(tKey); \
			delete tVar; \
		} \
	}
	#define CRX__VAR__VarKHash_empty(_pThis) \
	{ \
		CRX__VAR__VarKHash * pThis = _pThis; \
		\
		for(khiter_t tKhiter = kh_begin(pThis); \
				tKhiter != kh_end(pThis); ++tKhiter) \
		{ \
			if(!kh_exist(pThis, tKhiter)) \
				{continue;} \
\
			Var * tVar = kh_value(pThis, tKhiter); \
\
			free((char *)kh_key(pThis, tKhiter)); \
			delete tVar; \
		} \
\
		kh_clear(crx_Var, pThis); \
	}
	#define CRX__VAR__VarKHash_delete(_pVarKHash) \
	{ \
		CRX__VAR__VarKHash * pVarKHash__44543 = _pVarKHash; \
\
		CRX__VAR__KHash_empty(pVarKHash__44543); \
\
		kh_destroy(crx_Var, pVarKHash__44543); \
	}

				#pragma endregion UNSORTED HASH TABLE //}
	
				#pragma region SORTED HASH TABLE //{

	#define CRX__VAR__SortedKHash khash_t(crx_Var_Sorted)
	#define CRX__VAR__SortedVarKHash_new(RETURN) \
	{ \
		SortedVarKHash * vSortedVarKHash = new SortedVarKHash(); \
	\
		vSortedVarKHash->gPrivate_kHash = kh_init(crx_Var_Sorted); \
		vSortedVarKHash->gPrivate_start = NULL; \
		vSortedVarKHash->gPrivate_end = NULL; \
	\
		RETURN = vSortedVarKHash; \
	}
	#define CRX__VAR__SortedVarKHash_copyAddDifferenceFromSortedVarKHash(_pThis, _pSortedVarKHash, \
			_pArePossiblyCreatedVarsThreadPossible) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		SortedVarKHash const * pSortedVarKHash = _pSortedVarKHash; \
		bool pArePossiblyCreatedVarsThreadPossible = _pArePossiblyCreatedVarsThreadPossible; \
	\
		if(pThis != pSortedVarKHash) \
		{ \
			SortedVarKHashNode * tSortedVarKHashNode__current = pSortedVarKHash->gPrivate_start; \
\
			while(tSortedVarKHashNode__current != NULL) \
			{ \
				int tReturnedCode = 0; \
				khiter_t tKhiter = kh_put(crx_Var_Sorted, pThis->gPrivate_kHash, \
						tSortedVarKHashNode__current->gKey, &tReturnedCode); \
\
				if(tReturnedCode > 0) \
				{ \
					SortedVarKHashNode * tSortedVarKHashNode = new SortedVarKHashNode(); \
\
					tSortedVarKHashNode->gNext = NULL; \
					tSortedVarKHashNode->gKey = CRX__VAR__KHASH__PRIVATE__STRDUP( \
							tSortedVarKHashNode__current->gKey); \
					tSortedVarKHashNode->gVar = new Var(*(tSortedVarKHashNode__current->gVar), \
							pArePossiblyCreatedVarsThreadPossible); \
\
					if(pThis->gPrivate_start == NULL) \
					{ \
						tSortedVarKHashNode->gPrevious = NULL; \
\
						pThis->gPrivate_start = tSortedVarKHashNode; \
						pThis->gPrivate_end = tSortedVarKHashNode; \
					} \
					else \
					{ \
						tSortedVarKHashNode->gPrevious = pThis->gPrivate_end; \
\
						pThis->gPrivate_end->gNext = tSortedVarKHashNode; \
						pThis->gPrivate_end = tSortedVarKHashNode; \
					} \
\
					kh_key(pThis->gPrivate_kHash, tKhiter) = tSortedVarKHashNode->gKey; \
					kh_value(pThis->gPrivate_kHash, tKhiter) = tSortedVarKHashNode; \
				} \
\
				tSortedVarKHashNode__current = tSortedVarKHashNode__current->gNext; \
			} \
		} \
	}
	#define CRX__VAR__SortedVarKHash_copyImpressFromSortedVarKHash(_pThis, _pSortedVarKHash) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		SortedVarKHash const * pSortedVarKHash__64556 = _pSortedVarKHash; \
\
		if(pThis != pSortedVarKHash__64556) \
		{ \
			SortedVarKHashNode * tSortedVarKHashNode__current = pThis->gPrivate_start; \
\
			while(tSortedVarKHashNode__current != NULL) \
			{ \
				if(kh_get(crx_Var_Sorted, pSortedVarKHash__64556->gPrivate_kHash, \
						tSortedVarKHashNode__current->gKey) == kh_end(pVarKHash__64556->gPrivate_kHash)) \
				{ \
					SortedVarKHashNode * tSortedVarKHashNode__next = tSortedVarKHashNode__current->gNext; \
\
					kh_del(crx_Var_Sorted, pThis->gPrivate_kHash, kh_get(crx_Var_Sorted, \
							pThis->gPrivate_kHash, tSortedVarKHashNode__current->gKey)); \
\
					::free(tSortedVarKHashNode__current->gKey); \
					delete tSortedVarKHashNode__current->gVar; \
\
					if(tSortedVarKHashNode__current->gPrevious != NULL) \
					{ \
						tSortedVarKHashNode__current->gPrevious->gNext = \
								tSortedVarKHashNode__current->gNext; \
					} \
					else \
						{pThis->gPrivate_start = tSortedVarKHashNode__current->gNext;} \
\
					if(tSortedVarKHashNode__current->gNext != NULL) \
					{ \
						tSortedVarKHashNode__current->gNext->gPrevious = \
								tSortedVarKHashNode__current->gPrevious; \
					} \
					else \
						{pThis->gPrivate_end = tSortedVarKHashNode__current->gPrevious;} \
\
					::free(tSortedVarKHashNode__current); \
\
					tSortedVarKHashNode__current = tSortedVarKHashNode__next; \
				} \
				else \
					{tSortedVarKHashNode__current = tSortedVarKHashNode__current->gNext;} \
			} \
\
			tSortedVarKHashNode__current = pVarKHash__64556->gPrivate_start; \
			while(tSortedVarKHashNode__current != NULL) \
			{ \
				if(kh_get(crx_Var_Sorted, pThis->gPrivate_kHash, \
						tSortedVarKHashNode__current->gKey) == kh_end(pThis->gPrivate_kHash)) \
				{ \
					int tReturnedCode = 0; \
					khiter_t tKhiter2 = kh_put(crx_Var_Sorted, pThis->gPrivate_kHash, \
							CRX__VAR__KHASH__PRIVATE__STRDUP(tSortedVarKHashNode__current->gKey), \
							&tReturnedCode); \
\
					kh_value(pThis->gPrivate_kHash, tKhiter2) = \
							new Var(*(tSortedVarKHashNode__current->gVar)); \
				} \
\
				tSortedVarKHashNode__current = tSortedVarKHashNode__current->gNext; \
			} \
		} \
	}
	#define CRX__VAR__SortedVarKHash_copyUpdateFromSortedVarKHash(_pThis, _pSortedVarKHash) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		SortedVarKHash const * pSortedVarKHash__64556 = _pSortedVarKHash; \
\
		if(pThis != pSortedVarKHash__64556) \
		{ \
			SortedVarKHashNode * tSortedVarKHashNode__current = pThis->gPrivate_start; \
\
			while(tSortedVarKHashNode__current != NULL) \
			{ \
				khiter_t tKhiter = kh_get(crx_Var_Sorted, pSortedVarKHash__64556->gPrivate_kHash, \
						tSortedVarKHashNode__current->gKey); \
\
				if(tKhiter != kh_end(pSortedVarKHash__64556->gPrivate_kHash)) \
				{ \
					*(tSortedVarKHashNode__current->gVar) = \
							*((kh_value(pSortedVarKHash__64556->gPrivate_kHash, tKhiter))->gVar); \
				} \
\
				tSortedVarKHashNode__current = tSortedVarKHashNode__current->gNext; \
			} \
		} \
	}
	#define CRX__VAR__SortedKHash_set(_pThis, _pKey, _pVar, _pIsPossiblyCreatedVarThreadPossible) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		char const * pKey__64556 = _pKey; \
		Var const * pVar__64556 = _pVar; \
		bool pIsPossiblyCreatedVarThreadPossible = _pIsPossiblyCreatedVarThreadPossible; \
		int vReturnedCode = 0; \
		khiter_t vKhiter = kh_put(crx_Var_Sorted, pThis->gPrivate_kHash, pKey__64556, \
				&vReturnedCode); /* add the key */ \
		SortedVarKHashNode * vSortedVarKHashNode = new SortedVarKHashNode(); \
\
		vSortedVarKHashNode->gNext = NULL; \
\
		if(vReturnedCode == 0) \
		{ \
			SortedVarKHashNode * vSortedVarKHashNode = kh_val(pThis->gPrivate_kHash, vKhiter); \
\
			delete vSortedVarKHashNode; \
\
			vSortedVarKHashNode->gKey = ((char *) kh_key(pThis->gPrivate_kHash, vKhiter)); \
		} \
		else \
			{vSortedVarKHashNode->gKey = CRX__VAR__KHASH__PRIVATE__STRDUP(pKey__64556);} \
\
		vSortedVarKHashNode->gVar = new Var(*pVar__64556, pIsPossiblyCreatedVarThreadPossible); \
\
		if(pThis->gPrivate_start == NULL) \
		{ \
			vSortedVarKHashNode->gPrevious = NULL; \
\
			pThis->gPrivate_start = vSortedVarKHashNode; \
			pThis->gPrivate_end = vSortedVarKHashNode; \
		} \
		else \
		{ \
			vSortedVarKHashNode->gPrevious = pThis->gPrivate_end; \
\
			pThis->gPrivate_end->gNext = vSortedVarKHashNode; \
			pThis->gPrivate_end = vSortedVarKHashNode; \
		} \
\
		kh_key(pThis->gPrivate_kHash, vKhiter) = vSortedVarKHashNode->gKey; \
		kh_value(pThis->gPrivate_kHash, vKhiter) = vSortedVarKHashNode; /* set the value */ \
	}
	#define CRX__VAR__SortedVarKHash_pilferDifferenceFromSortedVarKHash(_pThis, _pSortedVarKHash) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		SortedVarKHash * pSortedVarKHash__64556 = _pSortedVarKHash; \
	\
		if(pThis != pSortedVarKHash__64556) \
		{ \
			SortedVarKHashNode * tSortedVarKHashNode__current = pSortedVarKHash__64556->gPrivate_start; \
\
			while(tSortedVarKHashNode__current != NULL) \
			{ \
				SortedVarKHashNode * tSortedVarKHashNode__next = tSortedVarKHashNode__current->gNext; \
				int tReturnedCode = 0; \
				khiter_t tKhiter = kh_put(crx_Var_Sorted, pThis->gPrivate_kHash, \
						tSortedVarKHashNode__current->gKey, &tReturnedCode); \
		\
				if(tReturnedCode > 0) \
				{ \
					khiter_t tKhiter__2 = kh_get(crx_Var_Sorted, \
							pSortedVarKHash__64556->gPrivate_kHash, \
							tSortedVarKHashNode__current->gKey); \
\
					kh_del(crx_Var_Sorted, pSortedVarKHash__64556->gPrivate_kHash, tKhiter__2); \
\
					if(tSortedVarKHashNode__current->gPrevious != NULL) \
					{ \
						tSortedVarKHashNode__current->gPrevious->gNext = \
								tSortedVarKHashNode__current->gNext; \
					} \
					else \
						{pSortedVarKHash__64556->gPrivate_start = tSortedVarKHashNode__current->gNext;} \
\
					if(tSortedVarKHashNode__current->gNext != NULL) \
					{ \
						tSortedVarKHashNode__current->gNext->gPrevious = \
								tSortedVarKHashNode__current->gPrevious; \
					} \
					else \
						{pSortedVarKHash__64556->gPrivate_end = tSortedVarKHashNode__current->gPrevious;} \
\
					if(pSortedVarKHash__64556.gPrivate_start == tSortedVarKHashNode__current) \
						{pSortedVarKHash__64556.gPrivate_start = tSortedVarKHashNode__current->gNextNode;} \
					if(pSortedVarKHash__64556.gPrivate_end == tSortedVarKHashNode__current) \
						{pSortedVarKHash__64556.gPrivate_end = tSortedVarKHashNode__current->gPreviousNode;} \
\
					tSortedVarKHashNode__current->gNext = NULL; \
\
					if(pThis->gPrivate_start == NULL) \
					{ \
						tSortedVarKHashNode__current->gPrevious = NULL; \
\
						pThis->gPrivate_start = tSortedVarKHashNode__current; \
						pThis->gPrivate_end = tSortedVarKHashNode__current; \
					} \
					else \
					{ \
						tSortedVarKHashNode__current->gPrevious = pThis->gPrivate_end; \
\
						pThis->gPrivate_end->gNext =  tSortedVarKHashNode__current; \
						pThis->gPrivate_end = tSortedVarKHashNode__current; \
					} \
\
					kh_value(pThis->gPrivate_kHash, tKhiter) = tSortedVarKHashNode__current; \
				} \
\
				tSortedVarKHashNode__current = tSortedVarKHashNode__next; \
			} \
		} \
	}
	#define CRX__VAR__SortedVarKHash_copyFromVarHashTable(_pThis, _pUnorderedMap) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap__5645 = _pUnorderedMap; \
		::crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator vIterator = \
				pUnorderedMap__5645.begin(); \
	\
		while(vIterator != pUnorderedMap__5645.end()) \
		{\
			int tReturnedCode = 0; \
			khiter_t tKhiter = kh_put(crx_Var_Sorted, pThis->gPrivate_kHash, \
					(*vIterator).first.c_str(), &tReturnedCode); \
	\
			if(tReturnedCode > 0) \
			{ \
				SortedVarKHashNode * tSortedVarKHashNode = new SortedVarKHashNode(); \
\
				tSortedVarKHashNode->gNext = NULL; \
				tSortedVarKHashNode->gKey = CRX__VAR__KHASH__PRIVATE__STRDUP((*vIterator).first.c_str()); \
				tSortedVarKHashNode->gVar = new Var((*vIterator).second); \
\
				if(pThis->gPrivate_start == NULL) \
				{ \
					tSortedVarKHashNode->gPrevious = NULL; \
\
					pThis->gPrivate_start = tSortedVarKHashNode; \
					pThis->gPrivate_end = tSortedVarKHashNode; \
				} \
				else \
				{ \
					tSortedVarKHashNode->gPrevious = pThis->gPrivate_end; \
\
					pThis->gPrivate_end->gNext = tSortedVarKHashNode; \
					pThis->gPrivate_end = tSortedVarKHashNode; \
				} \
\
				kh_key(pThis->gPrivate_kHash, tKhiter) = tSortedVarKHashNode->gKey; \
				kh_value(pThis->gPrivate_kHash, tKhiter) = tSortedVarKHashNode; \
			} \
	\
			vIterator++;\
		} \
	}
	#define CRX__VAR__SortedVarKHash_copyFromVarHashTable2(_pThis, _pUnorderedMap, \
			_pIsPossiblyCreatedVarThreadPossible) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		bool pIsPossiblyCreatedVarThreadPossible = _pIsPossiblyCreatedVarThreadPossible;\
		::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap__5645 = _pUnorderedMap; \
		::crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator vIterator = \
				pUnorderedMap__5645.begin(); \
	\
		while(vIterator != pUnorderedMap__5645.end()) \
		{\
			int tReturnedCode = 0; \
			khiter_t tKhiter = kh_put(crx_Var_Sorted, pThis->gPrivate_kHash, \
					(*vIterator).first.c_str(), &tReturnedCode); \
	\
			if(tReturnedCode > 0) \
			{ \
				SortedVarKHashNode * tSortedVarKHashNode = new SortedVarKHashNode(); \
\
				tSortedVarKHashNode->gNext = NULL; \
				tSortedVarKHashNode->gKey = CRX__VAR__KHASH__PRIVATE__STRDUP((*vIterator).first.c_str()); \
				tSortedVarKHashNode->gVar = new Var((*vIterator).second, \
						pIsPossiblyCreatedVarThreadPossible); \
\
				if(pThis->gPrivate_start == NULL) \
				{ \
					tSortedVarKHashNode->gPrevious = NULL; \
\
					pThis->gPrivate_start = tSortedVarKHashNode; \
					pThis->gPrivate_end = tSortedVarKHashNode; \
				} \
				else \
				{ \
					tSortedVarKHashNode->gPrevious = pThis->gPrivate_end; \
\
					pThis->gPrivate_end->gNext = tSortedVarKHashNode; \
					pThis->gPrivate_end = tSortedVarKHashNode; \
				} \
\
				kh_key(pThis->gPrivate_kHash, tKhiter) = tSortedVarKHashNode->gKey; \
				kh_value(pThis->gPrivate_kHash, tKhiter) = tSortedVarKHashNode; \
			} \
	\
			vIterator++;\
		} \
	}
	#define CRX__VAR__SortedVarKHash_copyImpressFromVarHashTable(_pThis, _pUnorderedMap) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap = _pUnorderedMap; \
		SortedVarKHashNode * vSortedVarKHashNode__current = pThis->gPrivate_start; \
		crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator vIterator = \
				pUnorderedMap.begin(); \
\
		while(vSortedVarKHashNode__current != NULL) \
		{ \
			if(pUnorderedMap.count(vSortedVarKHashNode__current->gKey) == 1) \
				{vSortedVarKHashNode__current = vSortedVarKHashNode__current->gNext;} \
			else \
			{ \
				SortedVarKHashNode * vSortedVarKHashNode__next = vSortedVarKHashNode__current->gNext; \
\
				kh_del(crx_Var_Sorted, pThis->gPrivate_kHash, kh_get(crx_Var_Sorted, \
						pThis->gPrivate_kHash, vSortedVarKHashNode__current->gKey)); \
\
				::free(vSortedVarKHashNode__current->gKey); \
				delete vSortedVarKHashNode__current->gVar; \
\
				if(vSortedVarKHashNode__current->gPrevious != NULL) \
				{ \
					vSortedVarKHashNode__current->gPrevious->gNext = \
							vSortedVarKHashNode__current->gNext; \
				} \
				else \
					{pThis->gPrivate_start = vSortedVarKHashNode__current->gNext;} \
\
				if(vSortedVarKHashNode__current->gNext != NULL) \
				{ \
					vSortedVarKHashNode__current->gNext->gPrevious = \
							vSortedVarKHashNode__current->gPrevious; \
				} \
				else \
					{pThis->gPrivate_end = vSortedVarKHashNode__current->gPrevious;} \
\
				::free(vSortedVarKHashNode__current); \
\
				vSortedVarKHashNode__current = vSortedVarKHashNode__next; \
			} \
		} \
\
		while(vIterator != pUnorderedMap.end()) \
		{ \
			if(kh_get(crx_Var_Sorted, pThis->gPrivate_kHash, \
					(*vIterator).first.c_str()) != kh_end(pThis->gPrivate_kHash)) \
				{continue;} \
\
			SortedVarKHashNode * tSortedVarKHashNode = new SortedVarKHashNode(); \
			int tReturnedCode = 0; \
			khiter_t tKhiter = kh_put(crx_Var_Sorted, pThis->gPrivate_kHash, \
					(*vIterator).first.c_str(), &tReturnedCode); \
\
			tSortedVarKHashNode->gNext = NULL; \
			tSortedVarKHashNode->gKey = \
					CRX__VAR__KHASH__PRIVATE__STRDUP((*vIterator).first.c_str()); \
			tSortedVarKHashNode->gVar = new Var((*vIterator).second); \
\
			if(pThis->gPrivate_start == NULL) \
			{ \
				tSortedVarKHashNode->gPrevious = NULL; \
\
				pThis->gPrivate_start = tSortedVarKHashNode; \
				pThis->gPrivate_end = tSortedVarKHashNode; \
			} \
			else \
			{ \
				tSortedVarKHashNode->gPrevious = pThis->gPrivate_end; \
\
				pThis->gPrivate_end->gNext = tSortedVarKHashNode; \
				pThis->gPrivate_end = tSortedVarKHashNode; \
			} \
\
			kh_key(pThis->gPrivate_kHash, tKhiter) = tSortedVarKHashNode->gKey; \
			kh_value(pThis->gPrivate_kHash, tKhiter) = tSortedVarKHashNode; \
\
			vIterator++; \
		} \
	}
	//VC6 COULD NOT USE at() FOR THE UNORDERED MAP FROM STLPORT
	#define CRX__VAR__SortedVarKHash_copyUpdateFromVarHashTable(_pThis, _pUnorderedMap) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap_4523 = _pUnorderedMap; \
		SortedVarKHashNode * vSortedVarKHashNode__current = pThis->gPrivate_start; \
		crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator vIterator = \
				pUnorderedMap_4523.begin(); \
\
		while(vSortedVarKHashNode__current != NULL) \
		{ \
			if(pUnorderedMap_4523.count(vSortedVarKHashNode__current->gKey) == 0) \
				{vSortedVarKHashNode__current = vSortedVarKHashNode__current->gNext;} \
			else \
			{ \
				*(vSortedVarKHashNode__current->gVar) = \
						(*(pUnorderedMap_4523.find(vSortedVarKHashNode__current->gKey))).second; \
\
				vSortedVarKHashNode__current = vSortedVarKHashNode__current->gNext; \
			} \
		} \
	}
	#define CRX__VAR__SortedVarKHash_forceGet(_pThis, RETURN, _pKey, _pIsPossiblyCreatedVarThreadPossible) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		char const * pKey__5645 = _pKey; \
		bool pIsPossiblyCreatedVarThreadPossible = _pIsPossiblyCreatedVarThreadPossible; \
		::khiter_t vKhiter = kh_get(crx_Var_Sorted, pThis->gPrivate_kHash, pKey__5645); \
	\
		if(vKhiter == kh_end(pThis->gPrivate_kHash)) \
		{ \
			SortedVarKHashNode * tSortedVarKHashNode = new SortedVarKHashNode(); \
			int tReturnedCode = 0; \
			::khiter_t tKhiter = kh_put(crx_Var_Sorted, pThis->gPrivate_kHash, pKey__5645, &tReturnedCode); \
\
			tSortedVarKHashNode->gNext = NULL; \
			tSortedVarKHashNode->gKey = CRX__VAR__KHASH__PRIVATE__STRDUP(pKey__5645); \
			tSortedVarKHashNode->gVar = new Var(Var::Undefined(), pIsPossiblyCreatedVarThreadPossible); \
\
			if(pThis->gPrivate_start == NULL) \
			{ \
				tSortedVarKHashNode->gPrevious = NULL; \
\
				pThis->gPrivate_start = tSortedVarKHashNode; \
				pThis->gPrivate_end = tSortedVarKHashNode; \
			} \
			else \
			{ \
				tSortedVarKHashNode->gPrevious = pThis->gPrivate_end; \
\
				pThis->gPrivate_end->gNext = tSortedVarKHashNode; \
				pThis->gPrivate_end = tSortedVarKHashNode; \
			} \
\
			kh_key(pThis->gPrivate_kHash, tKhiter) = tSortedVarKHashNode->gKey; \
			kh_value(pThis->gPrivate_kHash, tKhiter) = tSortedVarKHashNode; \
\
			RETURN = tSortedVarKHashNode->gVar; \
		} \
		else \
		{ \
			RETURN = (kh_value(pThis->gPrivate_kHash, vKhiter))->gVar; \
		} \
	}
	#define CRX__VAR__SortedVarKHash_getKeys(_pThis, RETURN) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		::std::vector<::std::string> vReturn(kh_size(pThis->gPrivate_kHash)); \
		SortedVarKHashNode * vSortedVarKHashNode__current = pThis->gPrivate_start; \
		\
		while(vSortedVarKHashNode__current != NULL) \
		{ \
			vReturn.push_back(const_cast<char const *>(vSortedVarKHashNode__current->gKey)); \
\
			vSortedVarKHashNode__current = vSortedVarKHashNode__current->gNext; \
		} \
\
		RETURN = vReturn; \
	}
	#define CRX__VAR__SortedVarKHash_getIteratorStart(_pThis, RETURN) \
	{ \
		SortedVarKHash * pThis = _pThis; \
\
		if(pThis->gPrivate_start == NULL) \
			{RETURN = SortedVarKHash_SortedVarKHashIterator<false>(SortedVarKHashNode(), true);} \
		else \
			{RETURN = SortedVarKHash_SortedVarKHashIterator<false>(*(pThis->gPrivate_start), false);} \
	}
	#define CRX__VAR__SortedVarKHash_getIteratorEnd(_pThis, RETURN) \
	{ \
		SortedVarKHash * pThis = _pThis; \
\
		if(pThis->gPrivate_end == NULL) \
			{RETURN = SortedVarKHash_SortedVarKHashIterator<false>(SortedVarKHashNode(), true);} \
		else \
			{RETURN = SortedVarKHash_SortedVarKHashIterator<false>(*(pThis->gPrivate_end), true);} \
	}
	#define CRX__VAR__SortedVarKHash_removeElementAt(_pThis, _pKey) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		char const * pKey__5645 = _pKey; \
		::khiter_t vKhiter = kh_get(crx_Var_Sorted, pThis->gPrivate_kHash, pKey__5645); \
\
		if(vKhiter != kh_end(pThis->gPrivate_kHash)) \
		{ \
			char * tKey = (char *)(kh_key(pThis->gPrivate_kHash, vKhiter)); \
			SortedVarKHashNode * tSortedVarKHashNode = kh_val(pThis->gPrivate_kHash, vKhiter); \
\
			kh_del(crx_Var_Sorted, pThis->gPrivate_kHash, vKhiter); \
\
			if(tSortedVarKHashNode->gPrevious != NULL) \
			{ \
				tSortedVarKHashNode->gPrevious->gNext = \
						tSortedVarKHashNode->gNext; \
			} \
			else \
				{pThis->gPrivate_start = tSortedVarKHashNode->gNext;} \
\
			if(tSortedVarKHashNode->gNext != NULL) \
			{ \
				tSortedVarKHashNode->gNext->gPrevious = \
						tSortedVarKHashNode->gPrevious; \
			} \
			else \
				{pThis->gPrivate_end = tSortedVarKHashNode->gPrevious;} \
\
			::free(tKey); \
			delete tSortedVarKHashNode->gVar; \
			::free(tSortedVarKHashNode); \
		} \
	}
	#define CRX__VAR__SortedVarKHash_removeElementsAt(_pThis, RETURN, _pKey, _pNumberOfElements) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		char const * pKey__5645 = _pKey; \
		size_t pNumberOfElements_5645 = _pNumberOfElements; \
		size_t vNumberOfElements = _pNumberOfElements; \
		::khiter_t vKhiter = kh_get(crx_Var_Sorted, pThis->gPrivate_kHash, pKey__5645); \
\
		if(vKhiter != kh_end(pThis->gPrivate_kHash)) \
		{ \
			SortedVarKHashNode * tSortedVarKHashNode__current = kh_val(pThis->gPrivate_kHash, vKhiter); \
\
			while((vNumberOfElements > 0) && (tSortedVarKHashNode__current != NULL)) \
			{ \
				SortedVarKHashNode * tSortedVarKHashNode__next = tSortedVarKHashNode__current->gNext; \
				::khiter_t tKhiter = kh_get(crx_Var_Sorted, pThis->gPrivate_kHash, \
						tSortedVarKHashNode__current->gKey); \
\
				kh_del(crx_Var_Sorted, pThis->gPrivate_kHash, tKhiter); \
\
				if(tSortedVarKHashNode__current->gPrevious != NULL) \
				{ \
					tSortedVarKHashNode__current->gPrevious->gNext = \
							tSortedVarKHashNode__current->gNext; \
				} \
				else \
					{pThis->gPrivate_start = tSortedVarKHashNode__current->gNext;} \
\
				if(tSortedVarKHashNode__current->gNext != NULL) \
				{ \
					tSortedVarKHashNode__current->gNext->gPrevious = \
							tSortedVarKHashNode__current->gPrevious; \
				} \
				else \
					{pThis->gPrivate_end = tSortedVarKHashNode__current->gPrevious;} \
\
				::free(tSortedVarKHashNode__current->gKey); \
				delete tSortedVarKHashNode__current->gVar; \
				::free(tSortedVarKHashNode__current); \
\
				tSortedVarKHashNode__current = tSortedVarKHashNode__next; \
				vNumberOfElements = vNumberOfElements - 1; \
			} \
		} \
\
		RETURN = pNumberOfElements_5645 - vNumberOfElements; \
	}
	#define CRX__VAR__SortedVarKHash_insertElementAfterKey(_pThis, RETURN, _pKey1, _pKey2, _pVar) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		const char * pKey1__5645 = _pKey1; \
		const char * pKey2__5645 = _pKey2; \
		Var const * pVar__5645 = _pVar; \
		::khiter_t vKhiter = kh_get(crx_Var_Sorted, pThis->gPrivate_kHash, pKey2__5645); \
\
		if(vKhiter == kh_end(pThis->gPrivate_kHash)) \
			{RETURN = false;} \
		else \
		{ \
			bool tIsValid = true; \
\
			if(pKey1__5645 != NULL) \
			{ \
				vKhiter = kh_get(crx_Var_Sorted, pThis->gPrivate_kHash, pKey1__5645); \
\
				if(vKhiter == kh_end(pThis->gPrivate_kHash)) \
					{tIsValid = false;} \
			} \
\
			if(tIsValid) \
			{ \
				SortedVarKHashNode * tSortedVarKHashNode = new SortedVarKHashNode(); \
				int tReturnedCode = 0; \
				khiter_t tKhiter; \
\
				tSortedVarKHashNode->gKey = CRX__VAR__KHASH__PRIVATE__STRDUP(pKey1__5645); \
				tSortedVarKHashNode->gVar = new Var(*pVar__5645); \
\
				if(pKey1__5645 != NULL) \
				{ \
					SortedVarKHashNode * tSortedVarKHashNode2 = kh_val(pThis->gPrivate_kHash, vKhiter); \
\
					tSortedVarKHashNode->gNext = tSortedVarKHashNode2->gNext; \
					tSortedVarKHashNode->gPrevious = tSortedVarKHashNode2; \
\
					tSortedVarKHashNode2->gNext->gPrevious = tSortedVarKHashNode; \
					tSortedVarKHashNode2->gNext = tSortedVarKHashNode; \
				} \
				else \
				{ \
					if(pThis->gPrivate_start == NULL) \
					{ \
						tSortedVarKHashNode->gNext = NULL; \
						tSortedVarKHashNode->gPrevious = NULL; \
\
						pThis->gPrivate_start = tSortedVarKHashNode; \
						pThis->gPrivate_end = tSortedVarKHashNode; \
					} \
					else \
					{ \
						tSortedVarKHashNode->gNext = pThis->gPrivate_start; \
						tSortedVarKHashNode->gPrevious = NULL; \
\
						pThis->gPrivate_start->gPrevious = tSortedVarKHashNode; \
						pThis->gPrivate_start = tSortedVarKHashNode; \
					} \
				} \
\
				tKhiter = kh_put(crx_Var_Sorted, pThis->gPrivate_kHash, \
						tSortedVarKHashNode->gKey, &tReturnedCode); \
				kh_value(pThis->gPrivate_kHash, tKhiter) = tSortedVarKHashNode; \
\
				RETURN = true; \
			} \
			else \
				{RETURN = false;} \
		} \
\
	}
	#define CRX__VAR__SortedVarKHash_insertElementBeforeKey(_pThis, RETURN, _pKey1, _pKey2, _pVar) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		const char * pKey1__5645 = _pKey1; \
		const char * pKey2__5645 = _pKey2; \
		Var const * pVar__5645 = _pVar; \
		::khiter_t vKhiter = kh_get(crx_Var_Sorted, pThis->gPrivate_kHash, pKey2__5645); \
\
		if(vKhiter == kh_end(pThis->gPrivate_kHash)) \
			{RETURN = false;} \
		else \
		{ \
			bool tIsValid = true; \
\
			if(pKey1__5645 != NULL) \
			{ \
				vKhiter = kh_get(crx_Var_Sorted, pThis->gPrivate_kHash, pKey1__5645); \
\
				if(vKhiter == kh_end(pThis->gPrivate_kHash)) \
					{tIsValid = false;} \
			} \
\
			if(tIsValid) \
			{ \
				SortedVarKHashNode * tSortedVarKHashNode = new SortedVarKHashNode(); \
				int tReturnedCode = 0; \
				khiter_t tKhiter; \
\
				tSortedVarKHashNode->gKey = CRX__VAR__KHASH__PRIVATE__STRDUP(pKey1__5645); \
				tSortedVarKHashNode->gVar = new Var(*pVar__5645); \
\
				if(pKey1__5645 != NULL) \
				{ \
					SortedVarKHashNode * tSortedVarKHashNode2 = kh_val(pThis->gPrivate_kHash, vKhiter); \
\
					tSortedVarKHashNode->gPrevious = tSortedVarKHashNode2->gPrevious; \
					tSortedVarKHashNode->gNext = tSortedVarKHashNode2; \
\
					tSortedVarKHashNode2->gPrevious->gNext = tSortedVarKHashNode; \
					tSortedVarKHashNode2->gPrevious = tSortedVarKHashNode; \
				} \
				else \
				{ \
					if(pThis->gPrivate_end == NULL) \
					{ \
						tSortedVarKHashNode->gNext = NULL; \
						tSortedVarKHashNode->gPrevious = NULL; \
\
						pThis->gPrivate_start = tSortedVarKHashNode; \
						pThis->gPrivate_end = tSortedVarKHashNode; \
					} \
					else \
					{ \
						tSortedVarKHashNode->gPrevious = pThis->gPrivate_end; \
						tSortedVarKHashNode->gNext = NULL; \
\
						pThis->gPrivate_end->gNext = tSortedVarKHashNode; \
						pThis->gPrivate_end = tSortedVarKHashNode; \
					} \
				} \
\
				tKhiter = kh_put(crx_Var_Sorted, pThis->gPrivate_kHash, \
						tSortedVarKHashNode->gKey, &tReturnedCode); \
				kh_value(pThis->gPrivate_kHash, tKhiter) = tSortedVarKHashNode; \
\
				RETURN = true; \
			} \
			else \
				{RETURN = false;} \
		} \
\
	}
	#define CRX__VAR__SortedVarKHash_empty(_pThis) \
	{ \
		SortedVarKHash * pThis = _pThis; \
		SortedVarKHashNode * vSortedVarKHashNode__current = pThis->gPrivate_start; \
		\
		while(vSortedVarKHashNode__current != NULL) \
		{ \
			SortedVarKHashNode * tSortedVarKHashNode__next = vSortedVarKHashNode__current->gNext; \
\
			::free(vSortedVarKHashNode__current->gKey); \
			delete vSortedVarKHashNode__current->gVar; \
			::free(vSortedVarKHashNode__current); \
\
			vSortedVarKHashNode__current = tSortedVarKHashNode__next; \
		} \
\
		kh_clear(crx_Var_Sorted, pThis->gPrivate_kHash); \
\
		pThis->gPrivate_start = NULL; \
		pThis->gPrivate_end = NULL; \
	}
	#define CRX__VAR__SortedKHash_delete(_pSortedVarKHash) \
	{ \
		SortedVarKHash * pSortedVarKHash__44543 = _pSortedVarKHash; \
\
		CRX__VAR__SortedVarKHash_empty(pSortedVarKHash__44543); \
\
		kh_destroy(crx_Var_Sorted, pSortedVarKHash__44543->gPrivate_kHash); \
	}

				#pragma endregion SORTED HASH TABLE //}

#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_HASH_TABLE_SORTED)
	#define CRX__VAR__KHash  CRX__VAR__VarKHash
	#define CRX__VAR__KHash_new(RETURN)  CRX__VAR__VarKHash_new(RETURN)
	#define CRX__VAR__KHash_copyAddDifferenceFromKHash(pThis, pKHash, pArePossiblyCreatedVarsThreadPossible)  \
			CRX__VAR__VarKHash_copyAddDifferenceFromVarKHash(pThis, pKHash, pArePossiblyCreatedVarsThreadPossible)
	#define CRX__VAR__KHash_copyImpressFromKHash(pThis, pKHash) \
			CRX__VAR__VarKHash_copyImpressFromVarKHash(pThis, pKHash)
	#define CRX__VAR__KHash_copyUpdateFromKHash(pThis, pKHash) \
			CRX__VAR__VarKHash_copyUpdateFromVarKHash(pThis, pKHash)
	#define CRX__VAR__KHash_set(pThis, pKey, pVar, pIsPossiblyCreatedVarThreadPossible) \
			CRX__VAR__VarKHash_set(pThis, pKey, pVar, pIsPossiblyCreatedVarThreadPossible)
	#define CRX__VAR__KHash_pilferDfferenceFromKHash(pThis, pKHash)  \
			CRX__VAR__VarKHash_pilferDifferenceFromVarKHash(pThis, pKHash)
	#define CRX__VAR__KHash_copyFromVarHashTable(pThis, pUnorderedMap) \
			CRX__VAR__VarKHash_copyFromVarHashTable(pThis, pUnorderedMap)
	#define CRX__VAR__KHash_copyFromVarHashTable2(pThis, pUnorderedMap, \
					pIsPossiblyCreatedVarThreadPossible) \
			CRX__VAR__VarKHash_copyFromVarHashTable2(pThis, pUnorderedMap, \
							pIsPossiblyCreatedVarThreadPossible)
	#define CRX__VAR__KHash_copyImpressFromVarHashTable(pThis, pUnorderedMap) \
			CRX__VAR__VarKHash_copyImpressFromVarHashTable(pThis, pUnorderedMap)
	#define CRX__VAR__KHash_copyUpdateFromVarHashTable(pThis, pUnorderedMap) \
			CRX__VAR__VarKHash_copyUpdateFromVarHashTable(pThis, pUnorderedMap)
	#define CRX__VAR__KHash_forceGet(pThis, RETURN, pKey, pIsPossiblyCreatedVarThreadPossible) \
			CRX__VAR__VarKHash_forceGet(pThis, RETURN, pKey, pIsPossiblyCreatedVarThreadPossible)
	#define CRX__VAR__KHash_getIteratorStart(pThis, RETURN) \
			CRX__VAR__VarKHash_getIteratorStart(pThis, RETURN)
	#define CRX__VAR__KHash_getIteratorEnd(pThis, RETURN) \
			CRX__VAR__VarKHash_getIteratorEnd(pThis, RETURN)
	#define CRX__VAR__KHash_removeElementAt(pThis, pKey) \
			CRX__VAR__VarKHash_removeElementAt(pThis, pKey)
	#define CRX__VAR__KHash_empty(pThis)  CRX__VAR__VarKHash_empty(pThis)
	#define CRX__VAR__KHash_getKeys(pThis, RETURN)  CRX__VAR__VarKHash_getKeys(pThis, RETURN)
	#define CRX__VAR__KHash_delete(pKHash)  CRX__VAR__VarKHash_delete(pKHash)
	
	#define CRX__VAR__KHASH__ITERATOR khiter_t
	#define CRX__VAR__KHASH__SIZE(pKHASH_POINTER)  kh_size(pKHASH_POINTER)
	#define CRX__VAR__KHASH__HAS_KEY(pKHASH_POINTER, pCHAR_POINTER)  \
			(kh_get(crx_Var, pKHASH_POINTER, pCHAR_POINTER) != kh_end(pKHASH_POINTER))
	#define CRX__VAR__KHASH__GET_KEY_FROM_ITERATOR(pKHASH_POINTER, pKHASH_ITERATOR) \
			kh_key(pKHASH_POINTER, pKHASH_ITERATOR)
	#define CRX__VAR__KHASH__GET_VALUE_FROM_ITERATOR(pKHASH_POINTER, pKHASH_ITERATOR) \
			kh_value(pKHASH_POINTER, pKHASH_ITERATOR)
	#define CRX__VAR__KHASH__INCREMENT_ITERATOR(pKHASH_POINTER, pKHASH_ITERATOR) \
			pKHASH_ITERATOR++; \
	\
			while(pKHASH_ITERATOR != kh_end(pKHASH_POINTER)) \
			{ \
				if(kh_exist(pKHASH_POINTER, pKHASH_ITERATOR)) \
					{break;} \
	\
				pKHASH_ITERATOR++; \
			}
#else
	#define CRX__VAR__KHash  SortedVarKHash
	#define CRX__VAR__KHash_new(RETURN)  CRX__VAR__SortedVarKHash_new(RETURN)
	#define CRX__VAR__KHash_copyAddDifferenceFromKHash(pThis, pKHash, pArePossiblyCreatedVarsThreadPossible)  \
			CRX__VAR__SortedVarKHash_copyAddDifferenceFromSortedVarKHash(pThis, pKHash, \
					pArePossiblyCreatedVarsThreadPossible)
	#define CRX__VAR__KHash_copyImpressFromKHash(pThis, pKHash) \
			CRX__VAR__SortedVarKHash_copyImpressFromSortedVarKHash(pThis, pKHash)
	#define CRX__VAR__KHash_copyUpdateFromKHash(pThis, pKHash) \
			CRX__VAR__SortedVarKHash_copyUpdateFromSortedVarKHash(pThis, pKHash)
	#define CRX__VAR__KHash_set(pThis, pKey, pVar, pIsPossiblyCreatedVarThreadPossible) \
			CRX__VAR__SortedKHash_set(pThis, pKey, pVar, pIsPossiblyCreatedVarThreadPossible)
	#define CRX__VAR__KHash_pilferDfferenceFromKHash(pThis, pKHash)  \
			CRX__VAR__SortedVarKHash_pilferDifferenceFromSortedVarKHash(pThis, pKHash)
	#define CRX__VAR__KHash_copyFromVarHashTable(pThis, pUnorderedMap) \
			CRX__VAR__SortedVarKHash_copyFromVarHashTable(pThis, pUnorderedMap)
	#define CRX__VAR__KHash_copyFromVarHashTable2(pThis, pUnorderedMap, \
					pIsPossiblyCreatedVarThreadPossible) \
			CRX__VAR__SortedVarKHash_copyFromVarHashTable2(pThis, pUnorderedMap, \
							pIsPossiblyCreatedVarThreadPossible)
	#define CRX__VAR__KHash_copyImpressFromVarHashTable(pThis, pUnorderedMap) \
			CRX__VAR__SortedVarKHash_copyImpressFromVarHashTable(pThis, pUnorderedMap)
	#define CRX__VAR__KHash_copyUpdateFromVarHashTable(pThis, pUnorderedMap) \
			CRX__VAR__SortedVarKHash_copyUpdateFromVarHashTable(pThis, pUnorderedMap)
	#define CRX__VAR__KHash_forceGet(pThis, RETURN, pKey, pIsPossiblyCreatedVarThreadPossible) \
			CRX__VAR__SortedVarKHash_forceGet(pThis, RETURN, pKey, pIsPossiblyCreatedVarThreadPossible)
	#define CRX__VAR__KHash_getIteratorStart(pThis, RETURN) \
			CRX__VAR__SortedVarKHash_getIteratorStart(pThis, RETURN)
	#define CRX__VAR__KHash_getIteratorEnd(pThis, RETURN) \
			CRX__VAR__SortedVarKHash_getIteratorEnd(pThis, RETURN)
	#define CRX__VAR__KHash_removeElementAt(pThis, pKey) \
			CRX__VAR__SortedVarKHash_removeElementAt(pThis, pKey)
	#define CRX__VAR__KHash_removeElementsAt(pThis, RETURN, pKey, pNumberOfElements) \
			CRX__VAR__SortedVarKHash_removeElementsAt(pThis, RETURN, pKey, pNumberOfElements)
	#define CRX__VAR__KHash_insertElementAfterKey(pThis, RETURN, pKey1, pKey2, pVar) \
			CRX__VAR__SortedVarKHash_insertElementAfterKey(pThis, RETURN, pKey1, pKey2, pVar)
	#define CRX__VAR__KHash_insertElementBeforeKey(pThis, RETURN, pKey1, pKey2, pVar) \
			CRX__VAR__SortedVarKHash_insertElementBeforeKey(pThis, RETURN, pKey1, pKey2, pVar)
	#define CRX__VAR__KHash_empty(pThis)  CRX__VAR__SortedVarKHash_empty(pThis)
	#define CRX__VAR__KHash_getKeys(pThis, RETURN)  CRX__VAR__SortedVarKHash_getKeys(pThis, RETURN)
	#define CRX__VAR__KHash_delete(pKHash)  CRX__VAR__SortedKHash_delete(pKHash)

	#define CRX__VAR__KHASH__ITERATOR SortedVarKHash_SortedVarKHashIterator<false>
	#define CRX__VAR__KHASH__SIZE(pKHASH_POINTER)  kh_size((pKHASH_POINTER)->gPrivate_kHash)
	#define CRX__VAR__KHASH__HAS_KEY(pKHASH_POINTER, pCHAR_POINTER)  \
			(kh_get(crx_Var_Sorted, pKHASH_POINTER->gPrivate_kHash, pCHAR_POINTER) != \
			kh_end(pKHASH_POINTER->gPrivate_kHash))
	#define CRX__VAR__KHASH__GET_KEY_FROM_ITERATOR(pKHASH_POINTER, pKHASH_ITERATOR) \
			pKHASH_ITERATOR.getKey()
	#define CRX__VAR__KHASH__GET_VALUE_FROM_ITERATOR(pKHASH_POINTER, pKHASH_ITERATOR) \
			pKHASH_ITERATOR.getValue()
	#define CRX__VAR__KHASH__INCREMENT_ITERATOR(pKHASH_POINTER, pKHASH_ITERATOR) \
			pKHASH_ITERATOR.advanceSelfByOne()
#endif

			#pragma endregion VAR: KHASH //}

		#pragma endregion VAR: HASH TABLES //}

		#pragma region VAR: ARRAYS //{

	/*CRX__VAR__ARRAY_IMPLEMENTATION */
	#if(CRX__VAR__CONFIG__ARRAY_IMPLEMENTATION == CRX__VAR__OPTION__ARRAY_IMPLEMENTATION__VARRING)
		#define CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING CRXM__TRUE
		#define CRX__VAR__ARRAY_IMPLEMENTATION__IS_VARRING_A_POINTER CRXM__FALSE
	
		#define CRX__VAR__GET_VARRING(T) &(T->gData.uArray.gVarRing)
		#define CRX__VAR__GET_VARRING2(T) &(T.gData.uArray.gVarRing)
		//VC6 #define CRX__VAR__ZERO_VARRING_BLOCK(T) T = CRX__INITIALIZATION_POD_ZERO
		#define CRX__VAR__ZERO_VARRING_BLOCK(T) CRX__SET_TO_ZERO(Crx_VarRing, T)
		#define CRX__VAR__CONSTRUCT_VARRING(T, T2) crx_varRing_construct(&(T), (T2))
		#define CRX__VAR__DELETE_VARRING(T) crx_varRing_destruct(&(T))
		#define CRX__VAR__IS_VARRING_NULL(T) false
	#elif(CRX__VAR__CONFIG__ARRAY_IMPLEMENTATION == CRX__VAR__OPTION__ARRAY_IMPLEMENTATION__VARRING_POINTER)
		#define CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING CRXM__TRUE
	#define CRX__VAR__ARRAY_IMPLEMENTATION__IS_VARRING_A_POINTER CRXM__TRUE

		#define CRX__VAR__GET_VARRING(T) T->gData.uArray.gVarRing
		#define CRX__VAR__GET_VARRING2(T) T.gData.uArray.gVarRing
		#define CRX__VAR__ZERO_VARRING_BLOCK(T)
		#define CRX__VAR__CONSTRUCT_VARRING(T, T2) T = crx_varRing_new(T2)
		#define CRX__VAR__DELETE_VARRING(T) \
				crx_varRing_destruct(T);  \
				free(T); \
				T = NULL
		#define CRX__VAR__IS_VARRING_NULL(T) (T == NULL)
	#else
		#define CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING CRXM__FALSE
	#endif
	
	#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		#if(CRX__VAR__CONFIG__INT_MODE == CRX__VAR__OPTION__INT_MODE__64BIT)
			#define CRX__VAR__ARRAY__SIZE_TYPE int64_t
		#else
			#define CRX__VAR__ARRAY__SIZE_TYPE int32_t
		#endif
	#else
		#define CRX__VAR__ARRAY__SIZE_TYPE int32_t
	#endif

		#pragma endregion VAR: ARRAYS //}
		
		#pragma region VAR: FLOATS //{

	//#define CRX__VAR__DOUBLE__ERROR	9218996113850331260llu
	#define CRX__VAR__DOUBLE__ERROR strtod("NAN(6789A)",0)

	#if((CRX__VAR__INT_MODE == CRX__VAR__OPTION__INT_MODE__64BIT) || \
			(CRX__VAR__INT_MODE == CRX__VAR__OPTION__INT_MODE__32BIT))
		#define CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(T1) \
				T1->gData.uIntegral.uDouble = NAN;
	#else
		#define CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(T1) \
				T1->gData.uIntegral.uDouble = NAN; \
				if(CRX__VAR__GET_TYPE1(T1) == CRX__VAR__TYPE_EMULATED_INT) \
					{CRX__VAR__SET_TYPE(T1, CRX__VAR__TYPE_DOUBLE);}
	#endif

//VC6 USING ::floor() INSTEAD OF ::std::floor()
	#define CRX__VAR_SET_TYPE_TO_DOUBLE_FROM_EMULATED_INT_IF_NO_LONGER_WHOLE(T1) \
			if((CRX__VAR__GET_TYPE1(T1) == CRX__VAR__TYPE_EMULATED_INT) && \
					!::isnan(T1->gData.uIntegral.uDouble) && \
					!::isinf(T1->gData.uIntegral.uDouble) && \
					(T1->gData.uIntegral.uDouble != \
							::floor(T1->gData.uIntegral.uDouble))) \
				{CRX__VAR__SET_TYPE(T1, CRX__VAR__TYPE_DOUBLE);}
				
	#define CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(T1, T2, T3) \
			((T1 >= (T2)) && (T1 <= (T3)) && (T1 != ::floor(T1)))
				
	#ifdef CRX__BOOST_NO_INT64_T
		#define CRX__VAR__DOUBLE__ERROR_HIGH_BITS_IN_INT32 0x7FF0741F
		#define CRX__VAR__DOUBLE__ERROR_LOW_BITS_IN_INT32 0x07C1707C
	#endif

	#ifndef CRX__BOOST_NO_INT64_T
		#define CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(T1) ((int64_t)T1 == CRX__VAR__DOUBLE__ERROR)
	#else
		#define CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(T1) var_isDoubleEqualTo(T1, \
				CRX__VAR__DOUBLE__ERROR_HIGH_BITS_IN_INT32, \
				CRX__VAR__DOUBLE__ERROR_LOW_BITS_IN_INT32)
	#endif
				
		#pragma endregion VAR: FLOATS //}

		#pragma region VAR: MISC //{

	//#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)

	#define CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_CHAR 5
	#define CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR 4
	#define CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT 18
	#define CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT32 12
	#define CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_INT32 11
	#define CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT64 22
	#if(CRX__VAR__INT_MODE == CRX__VAR__OPTION__INT_MODE__64BIT)	
		#define CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT \
				CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT64
	#elif(CRX__VAR__INT_MODE == CRX__VAR__OPTION__INT_MODE__32BIT)
		#define CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT \
				CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT32
	#else
		#define CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT \
				CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT
	#endif
	#define CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE 25

	#define CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(LENGTH) \
			static_cast<int>(LENGTH <= INT32_MAX ? LENGTH : 0)
			
	#ifndef CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
		#define CRX__VAR__TYPE_FOR_MOVE(pTYPE) pTYPE &&
	#else
		#define CRX__VAR__TYPE_FOR_MOVE(pTYPE) pTYPE
	#endif
	
	/*INTENDED FOR USE WITH THE MOVE CONSTRUCTORS ONLY TO TAKE ADVANTAGE
			OF STL CONTAINERS. WHETHER WILL GIVE PERFORMANCE BOOST,
			REMAINS TO BE SEEN FOR (< C++17) WHERE noexcept IS LIKE throw()
			WITH NO PARAMETERS AND CAN BE EXPENSIVE. 

			NOTE THAT THERE IS AN ASSUMPION THAT IF noexcept IS SUPPORTED,
			RVALUE REFERENCE ARE SUPPORTED. IF THIS IS NOT TRUE,
			CRX__BOOST_NO_CXX11_RVALUE_REFERENCES NEEDS TO BE ADDED
			TO THE CHECKS BELOW.*/
	#if(!defined(BOOST_VERSION) || (BOOST_VERSION < 104700))
		#define CRX__VAR__PRIVATE__NOEXCEPT
	#else
		#if(BOOST_VERSION < 104900)
			#if(defined(BOOST_NO_NOEXCEPT))
				#define CRX__VAR__PRIVATE__NOEXCEPT
			#else
				#define CRX__VAR__PRIVATE__NOEXCEPT  noexcept
			#endif
		#else
			#define CRX__VAR__PRIVATE__NOEXCEPT  BOOST_NOEXCEPT
		#endif
	#endif

		#pragma endregion VAR: MISC //}

		#pragma region VAR: ERRORS //{
			
	#define CRX__VAR__MERGE_TOKENS(T1, T2) T1 ## T2

	/*
	NOTE: IF CRX__VAR__REPORT_ERROR() IS USED IN A NON OPERATOR, THE CODE WOULD BE WRONG.
	*/
	#if(CRX__VAR__CONFIG__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__SWALLOW)
		#define CRX__VAR__ERROR_MODE CRX__VAR__OPTION__ERROR_MODE__SWALLOW
		#define CRX__VAR__REPORT_ERROR(pVAR_POINTER, pMacroPrefix, T) T
		#define CRX__VAR__REPORT_ERROR2(pVAR_POINTER, pMacroPrefix, STD_STRING, T) T

		#define CRX__VAR__REPORT_ERROR_FROM_CAST2(pMacroPrefix, T) \
				CRX__VAR__REPORT_ERROR(this, pMacroPrefix, T)
	#elif(CRX__VAR__CONFIG__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__EXCEPTION)
		#define CRX__VAR__ERROR_MODE CRX__VAR__OPTION__ERROR_MODE__EXCEPTION
		#define CRX__VAR__REPORT_ERROR(pVAR_POINTER, pMacroPrefix, T) \
				throw CRX__VAR__MERGE_TOKENS(pMacroPrefix, _MSG)
		#define CRX__VAR__REPORT_ERROR2(pVAR_POINTER, pMacroPrefix, STD_STRING, T) \
				throw (::std::string(CRX__VAR__MERGE_TOKENS(pMacroPrefix, _MSG)) + "\n" + STD_STRING)
		
		#define CRX__VAR__REPORT_ERROR_FROM_CAST2(pMacroPrefix, T) \
				CRX__VAR__REPORT_ERROR(this, pMacroPrefix, T)
	#elif(CRX__VAR__CONFIG__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
		#define CRX__VAR__ERROR_MODE CRX__VAR__OPTION__ERROR_MODE__PROPOGATER
		#define CRX__VAR__REPORT_ERROR(pVAR_POINTER, pMacroPrefix, T) \
				(pVAR_POINTER)->setPrivateError(CRX__VAR__MERGE_TOKENS(pMacroPrefix, _CODE), \
				CRX__VAR__MERGE_TOKENS(pMacroPrefix, _MSG)); T
		#define CRX__VAR__REPORT_ERROR2(pVAR_POINTER, pMacroPrefix, STD_STRING, T) \
				(pVAR_POINTER)->safeSetPrivateError(CRX__VAR__MERGE_TOKENS(pMacroPrefix, _CODE), \
				::std::string(CRX__VAR__MERGE_TOKENS(pMacroPrefix, _MSG)) + "\n" + STD_STRING); T
		
		#define CRX__VAR__REPORT_ERROR_FROM_CAST2(pMacroPrefix, T) CRX__VAR__GUARD(false)
	#elif(defined(CRX__VAR__ERROR_MODE__ERROR_CODE) && (CRX__VAR__CONFIG__ERROR_MODE == CRX__VAR__ERROR_MODE__ERROR_CODE))
		#define CRX__VAR__ERROR_MODE CRX__VAR__ERROR_MODE__ERROR_CODE
		#define CRX__VAR__REPORT_ERROR(pVAR_POINTER, pMacroPrefix, T) \
				if(gVar_errorCode != 0) \
					{gVar_errorCode = CRX__VAR__MERGE_TOKENS(pMacroPrefix, _CODE);} T
		#define CRX__VAR__REPORT_ERROR2(pVAR_POINTER, pMacroPrefix, STD_STRING, T) \
				if(gVar_errorCode != 0) \
					{gVar_errorCode = CRX__VAR__MERGE_TOKENS(pMacroPrefix, _CODE);} T
		
		#define CRX__VAR__REPORT_ERROR_FROM_CAST2(pMacroPrefix, T) \
				CRX__VAR__REPORT_ERROR(this, pMacroPrefix, T)
	#endif
	
	#if(CRX__VAR__CONFIG__IS_ERROR_TYPE_AVAILABLE_FOR_PUBLIC_USE)
		#define CRX__VAR__IS_ERROR_TYPE_AVAILABLE_FOR_PUBLIC_USE CRXM__TRUE
	#else
		#define CRX__VAR__IS_ERROR_TYPE_AVAILABLE_FOR_PUBLIC_USE CRXM__FALSE
	#endif
	
	#if((CRX__VAR__CONFIG__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER) || \
			CRX__VAR__CONFIG__IS_ERROR_TYPE_AVAILABLE_FOR_PUBLIC_USE)
		#define CRX__VAR__DOES_ERROR_TYPE_EXISTS CRXM__TRUE
	#else
		#define CRX__VAR__DOES_ERROR_TYPE_EXISTS CRXM__FALSE
	#endif

	#define CRX__VAR__NO_OP_FOR_ERROR

	/*NOTE: '0' IS FOR NO ERROR.*/
	#define CRX__VAR__ERROR__ILLEGAL_CAST CRX__VAR__ERROR__E01
	#define CRX__VAR__ERROR__E01_MSG "ILLEGAL CAST"
	#define CRX__VAR__ERROR__E01_CODE 1

	#define CRX__VAR__ERROR__ILLEGAL_OPERATION	CRX__VAR__ERROR__E02
	#define CRX__VAR__ERROR__E02_MSG "ILLEGAL OPERATION"
	#define CRX__VAR__ERROR__E02_CODE 2

	#define CRX__VAR__ERROR__INVALID_OPERAND CRX__VAR__ERROR__E03
	#define CRX__VAR__ERROR__E03_MSG "INVALID OPERAND"
	#define CRX__VAR__ERROR__E03_CODE 3

	#define CRX__VAR__ERROR__INTEGER_OVERFLOW CRX__VAR__ERROR__E04
	#define CRX__VAR__ERROR__E04_MSG "INTEGER OVERFLOW"
	#define CRX__VAR__ERROR__E04_CODE 4

	#define CRX__VAR__ERROR__VAR_FUNCTION_CALL_ON_INVALID_INTERNAL_TYPE CRX__VAR__ERROR__E05
	#define CRX__VAR__ERROR__E05_MSG "::crx::Var MEMBER FUNCTION CALL ON INVALID INTERNAL TYPE"
	#define CRX__VAR__ERROR__E05_CODE 5

	#define CRX__VAR__ERROR__OUT_OF_RANGE CRX__VAR__ERROR__E06
	#define CRX__VAR__ERROR__E06_MSG "OUT OF RANGE"
	#define CRX__VAR__ERROR__E06_CODE 6

	#define CRX__VAR__ERROR__OUT_OF_MEMORY CRX__VAR__ERROR__E07
	#define CRX__VAR__ERROR__E07_MSG "OUT OF MEMORY"
	#define CRX__VAR__ERROR__E07_CODE 7

	#define CRX__VAR__ERROR__MALFORMED_VARJSON CRX__VAR__ERROR__E08
	#define CRX__VAR__ERROR__E08_MSG "VARJSON PARSE ERROR"
	#define CRX__VAR__ERROR__E08_CODE 8

	#define CRX__VAR__ERROR__INDEX_OUT_OF_BOUNDS CRX__VAR__ERROR__E09
	#define CRX__VAR__ERROR__E09_MSG "INDEX OUT OF BOUNDS"
	#define CRX__VAR__ERROR__E09_CODE 9

	#define CRX__VAR__ERROR__VARJSON_FORMATION_ENCOUNTERED_POINTER CRX__VAR__ERROR__E10
	#define CRX__VAR__ERROR__E10_MSG "VARJSON FORMATION ENCOUNTERED POINTER"
	#define CRX__VAR__ERROR__E10_CODE 10

	#define CRX__VAR__ERROR__VARJSON_FORMATION_ENCOUNTERED_UNDEFINED CRX__VAR__ERROR__E11
	#define CRX__VAR__ERROR__E11_MSG "VARJSON FORMATION ENCOUNTERED POINTER"
	#define CRX__VAR__ERROR__E11_CODE 11

	
	#define CRX__VAR__GUARD(pT) if(!(pT)){abort();}
	#define CRX__VAR__GUARD2(pT, pT2) if(!(pT)){abort();} return pT2;
	
	#define CRX__VAR__LARGEST_RESERVED_ERROR_CODE 268435455

	#if(CRX__VAR__CONFIG__ARE_EXCEPTIONS_ENABLED)
		#define CRX__VAR__TRY	try {
		#define CRX__VAR__END_TRY	}
		#define CRX__VAR__CATCH	 catch(...) {
		#define CRX__VAR__END_CATCH }
	#else
		#define CRX__VAR__TRY	try
		#define CRX__VAR__END_TRY
		#define CRX__VAR__CATCH	 if(false){
		#define CRX__VAR__END_CATCH }
	#endif
		
		#pragma endregion VAR: ERRORS //}

		#pragma region OTHER //{
	/*
	THE FOLLOWING ARE TO AVOID ISSUES WITH MACROS min AND max THAT MIGHT BE DEFINED BY
			THE WINDOW HEADERS.
	*/
	#define CRX__VAR__PRIVATE__MAX	(::std::max)
	#define CRX__VAR__PRIVATE__MIN	(::std::min)
		#pragma endregion //}

		#pragma region VAR_ITERATOR_DATA//{
#ifndef CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		#define CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR(pTHIS) (pTHIS->gIterator.uIterator__unorderedMap)
		#define CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(pTHIS) (pTHIS.gIterator.uIterator__unorderedMap)
	#else
		#define CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR(pTHIS) (pTHIS->gIterator.uKhiter)
		#define CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(pTHIS) (pTHIS.gIterator.uKhiter)
	#endif
#else
	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		#define CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR(pTHIS) \
				(*((::crx::ClassUnorderedMap<::std::string, Var>::t::iterator *) \
						(&(pTHIS->gIterator.gShared[0]))))
		#define CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(pTHIS) \
				(*((::crx::ClassUnorderedMap<::std::string, Var>::t::iterator *) \
						(&(pTHIS.gIterator.gShared[0]))))
	#else
		#define CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR(pTHIS) \
				(*((CRX__VAR__KHASH__ITERATOR *)(&(pTHIS->gIterator.gShared[0]))))
		#define CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(pTHIS) \
				(*((CRX__VAR__KHASH__ITERATOR *)(&(pTHIS.gIterator.gShared[0]))))
	#endif
#endif
		#pragma endregion //}

	#pragma endregion MACROS:  PRIVATE //}


	class Var;
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
	class Var_DeuqueIterator;
	class Var_DeuqueConstantIterator;
#else
	//class Var_VarRingIterator;
	//class Var_VarRingConstantIterator;
#endif
	template<bool T> class Var_VarIterator;
	template<bool T> class Var_StringIterator;
	void var_private_destruct(Var * pVar);
	void var_private_copyConstruct(Var * pVar, Var const * pVar2);

	KHASH_MAP_INIT_STR(crx_Var, ::crx::Var *);
	
	typedef struct SortedVarKHashNode
	{
		SortedVarKHashNode * CRX_NOT_MINE gNext;
		SortedVarKHashNode * CRX_NOT_MINE gPrevious;
		char * gKey;
		Var * gVar;
	} SortedVarKHashNode;

	KHASH_MAP_INIT_STR(crx_Var_Sorted, ::crx::SortedVarKHashNode *);
	
	typedef struct SortedVarKHash
	{
		CRX__VAR__SortedKHash * gPrivate_kHash;
		SortedVarKHashNode * gPrivate_start;
		SortedVarKHashNode * gPrivate_end;
	} SortedVarKHash;


	#pragma region Var pointer	//{
	
	/*THE FOLLOWING TEMPORARY UNTIL FUNCTIONALITY FROM BOOST IS ADOPTED*/
	//VC6: DO NOT EXPECT THE RTTI WITH STLPORT
	#define CRX__VAR__PRIVATE__RTTI_EXISTS CRXM__FALSE
	#define CRX__VAR__TYPE_ID(T)	&(Var_TypeId<T>::id)
		
	class Var_TypeUsingGuid
	{
		public: void * CRX_NOT_MINE gP;
		public: bool gIsConstant;

		public: bool isEqualTo(Var_TypeUsingGuid * pTypeUsingGuid)
		{
			return ((this->getA() == pTypeUsingGuid->getA()) && (this->getB() == pTypeUsingGuid->getB()) &&
					(this->getC() == pTypeUsingGuid->getC()) && (this->getD() == pTypeUsingGuid->getD()));
		}
		public: ::std::string getAsString()
		{
			char vChars[64];
			
			::sprintf(vChars, "{-{GUID: %u %u %u %u}-}", this->getA(), this->getB(), this->getC(),
					this->getD());
			
			return ::std::string(vChars);
		}
		public: virtual Var_TypeUsingGuid * CRX_PASSING clone() = 0;
		public: virtual int getA() = 0;
		public: virtual int getB() = 0;
		public: virtual int getC() = 0;
		public: virtual int getD() = 0;
	};
	class Var_TypeUsingTypeId
	{
		public: void * CRX_NOT_MINE gP;
		public: bool gIsConstant;

		public: virtual bool isEqualTo(Var_TypeUsingTypeId * pTypeUsingTypeId) = 0;
		public: virtual Var_TypeUsingTypeId * CRX_PASSING clone() = 0;
		public: virtual ::std::string getAsString() = 0;
		public: virtual void const * getTypeInfo() = 0;
	};
	class Var_Pointer
	{
		private: Var_TypeUsingGuid * gTypeUsingGuid;
		private: Var_TypeUsingTypeId * gTypeUsingTypeId;
		
		public: Var_Pointer(): gTypeUsingGuid(NULL), gTypeUsingTypeId(NULL)
			{}
		public: Var_Pointer(Var_TypeUsingGuid * pTypeUsingGuid) : gTypeUsingGuid(pTypeUsingGuid), 
				gTypeUsingTypeId(NULL)
			{}
		public: Var_Pointer(Var_TypeUsingTypeId * pTypeUsingTypeId) : gTypeUsingGuid(NULL), 
				gTypeUsingTypeId(pTypeUsingTypeId)
			{}

		public: virtual bool isEqualTo(Var_Pointer * t)
		{
			if((this->gTypeUsingGuid != NULL) && (t->gTypeUsingGuid != NULL))
				{return this->gTypeUsingGuid->isEqualTo(t->gTypeUsingGuid);}
			else if((this->gTypeUsingTypeId != NULL) && (t->gTypeUsingTypeId != NULL))
				{return this->gTypeUsingTypeId->isEqualTo(t->gTypeUsingTypeId);}
			else
				{return false;}
		}
		public: virtual bool isConstant()
		{
			if(this->gTypeUsingGuid != NULL)
				{return this->gTypeUsingGuid->gIsConstant;}
			else if(this->gTypeUsingTypeId != NULL)
				{return this->gTypeUsingTypeId->gIsConstant;}
			else
				{return false;}
		}
		
		private: void empty(void)
		{
			if(this->gTypeUsingGuid != NULL)
				{delete this->gTypeUsingGuid; this->gTypeUsingGuid = NULL;}
			else if(this->gTypeUsingTypeId != NULL)
				{delete this->gTypeUsingTypeId; this->gTypeUsingTypeId = NULL;}
		}
		
		public: ::std::string getAsString()
		{
			if(this->gTypeUsingGuid != NULL)
				{return this->gTypeUsingGuid->getAsString();}
			else if(this->gTypeUsingTypeId != NULL)
				{return this->gTypeUsingTypeId->getAsString();}
			else
				{return "{-{GUID: 0 0 0 0}-}";}
		}

		public: Var_Pointer * CRX_PASSING clone(void)
		{
			if(this->gTypeUsingGuid != NULL)
				{return new Var_Pointer(this->gTypeUsingGuid);}
			else if(this->gTypeUsingTypeId != NULL)
				{return new Var_Pointer(this->gTypeUsingTypeId);}
			else
				{return new Var_Pointer();}
		}
		
		public: void * getPointer(void)
		{
			if(this->gTypeUsingGuid != NULL)
				{return this->gTypeUsingGuid->gP;}
			else if(this->gTypeUsingTypeId != NULL)
				{return this->gTypeUsingTypeId->gP;}
			else
				{return NULL;}
		}
		
		public: void set(Var_TypeUsingGuid * CRX_PASSING pTypeUsingGuid)
		{
			this->empty();

			this->gTypeUsingGuid = pTypeUsingGuid;
		}		
		public: void set(Var_TypeUsingTypeId * CRX_PASSING pTypeUsingGuid)
		{
			this->empty();

			this->gTypeUsingTypeId = gTypeUsingTypeId;
		}
		
		
		public: ~Var_Pointer()
			{this->empty();}
	};

	
	#if(CRX__VAR__PRIVATE__RTTI_EXISTS || CRX__ARE_ONLY_POINTERS_TO_SAME_OBJECT_EQUAL_AND_ALWAYS)
		#if(!CRX__VAR__PRIVATE__RTTI_EXISTS && CRX__ARE_ONLY_POINTERS_TO_SAME_OBJECT_EQUAL_AND_ALWAYS)
	template<typename T>
	struct Var_TypeId
		{static T const * id;};

	template<typename T>
	T const * Var_TypeId<T>::id = NULL;
		#endif
	
	/*VC6 template<typename T>
	class UIsConstant
	{
		enum
		{
			VALUE = false
		};
		public: typedef T TYPE;
	};
	template<typename T>
	class UIsConstant<T const>
	{
		enum
		{
			VALUE = true
		};
		public: typedef T TYPE;
	};*/


	template<class T>
	class Var_UnRegisteredTypeUsingTypeId : public Var_TypeUsingTypeId
	{
		public: Var_UnRegisteredTypeUsingTypeId()
		{
			this->gP = NULL;
			this->gIsConstant = false;
		}
		//VC6 public: Var_UnRegisteredTypeUsingTypeId(typename UIsConstant<T>::TYPE * pT)
		public: Var_UnRegisteredTypeUsingTypeId(typename boost::remove_cv<T>::type * pT)
		{
			this->gP = pT;
			this->gIsConstant = false;
		}
		//VC6 public: Var_UnRegisteredTypeUsingTypeId(typename UIsConstant<T>::TYPE const * pT)
		public: Var_UnRegisteredTypeUsingTypeId(typename boost::remove_cv<T>::type const * pT)
		{
			//VC6 this->gP = const_cast<typename UIsConstant<T>::TYPE *>(pT);
			this->gP = const_cast<typename boost::remove_cv<T>::type *>(pT);
			this->gIsConstant = true;
		}
			
		public: virtual Var_TypeUsingTypeId * CRX_PASSING clone()
			{return new Var_UnRegisteredTypeUsingTypeId(static_cast<T *>(this->gP));}
			
		#if(CRX__VAR__PRIVATE__RTTI_EXISTS)
		public: virtual ::std::string getAsString()
			{return (typeid(T)).name();}
		public: bool isEqualTo(Var_TypeUsingTypeId * ua)
			{return (typeid(T) == *((::std::type_info *) ua->getTypeInfo()));}
			/*{typeid(T).hash_code() == (*((::std::type_info *) ua->getTypeInfo())).hash_code();} (>= C++11)*/
		public: void const * getTypeInfo()
			{return &(typeid(T));}
		#else
		/* ALTERNATIVE CODE USING THE TYPEID TRICK, BUT IT IS UNREIABLE ON OLD
				COMPILERS BECAUSE IT USES A STATIC CONST. FURTHER MORE IT RELIES ON POINTER EQUALITY
				COMPARISON WHICH IS ALSO UNRELIABLE.*/
		public: virtual ::std::string getAsString()
			{return "{-{+OBJECT+}-}";}
		public: bool isEqualTo(Var_TypeUsingTypeId * ua)
			{return (CRX__ARE_POINTERS_TO_SAME_OBJECT(CRX__VAR__TYPE_ID(T), ua->getTypeInfo(), false));}
		public: void const * getTypeInfo()
			{return CRX__VAR__TYPE_ID(T);}
		#endif
	};
	#endif

	template<class T>
	class Var_RegisteredType : public Var_TypeUsingGuid
	{
		public: enum
		{
			RegisteredType_A = 0,
			RegisteredType_B = 0,
			RegisteredType_C = 0,
			RegisteredType_D = 0
		};

		public: Var_RegisteredType()
		{
			this->gP = NULL;
			this->gIsConstant = false;
		}
		public: Var_RegisteredType(T * pT)
		{
			this->gP = pT;
			this->gIsConstant = false;
		}
		public: Var_RegisteredType(T const * pT)
		{
			this->gP = pT;
			this->gIsConstant = true;
		}
			
		public: virtual Var_TypeUsingGuid * CRX_PASSING clone()
			{return new Var_RegisteredType<T>(this->gP);}

		public: virtual int getA()
			{return 0;}
		public: virtual int getB()
			{return 0;}
		public: virtual int getC()
			{return 0;}
		public: virtual int getD()
			{return 0;}
	};

	template<class T>
	class Var_InfoIsPointerTypeRegistered
	{
		public: enum
			{VALUE = false};
	};
	
	/*
	THE FOLLOWING IS FOR EXPLICIT REGISTRATION OF TYPES THAT THE Var CAN HOLD A POITNER TO. THIS ALLOWS
	THESE TYPES TO WORK RELIABLY WHEN THE RTTI IS DISABLED.
	*/
	#define CRX__VAR__REGISTER_POINTER_TYPE(TYPE, A, B, C, D) \
	template<> \
	class ::crx::Var_InfoIsPointerTypeRegistered<TYPE> \
	{ \
		public: enum \
		{ \
			VALUE = true \
		}; \
	}; \
	template<> \
	class ::crx::Var_RegisteredType<TYPE> : public ::crx::Var_TypeUsingGuid \
	{ \
		public: enum \
		{ \
			RegisteredType_A = A, \
			RegisteredType_B = B, \
			RegisteredType_C = C, \
			RegisteredType_D = D \
		}; \
	\
		public: Var_RegisteredType() \
			{this->gP = NULL;} \
		public: Var_RegisteredType(TYPE * pT) \
			{this->gP = pT;} \
	\
		public: virtual Var_TypeUsingGuid * CRX_PASSING clone() \
			{return new Var_RegisteredType<TYPE>(static_cast<TYPE *>(this->gP));} \
	\
		public: virtual int getA(void) \
			{return A;} \
		public: virtual int getB(void) \
			{return B;} \
		public: virtual int getC(void) \
			{return C;} \
		public: virtual int getD(void) \
			{return D;} \
	};

	template<bool T>
	class UWrapper
		{};
	template<>
	class UWrapper<true>
	{
		public: template<typename T>
		class UType
			{public: typedef Var_RegisteredType<T> Type;};
	};
	template<>
	class UWrapper<false>
	{
		public: template<typename T>
		class UType
			{public: typedef Var_UnRegisteredTypeUsingTypeId<T> Type;};
	};

	/*template<typename T>
	class Var_PointerPasser
		{};

	template<typename T>
	class Var_PointerPasser
	{
		public: T * gT;

		public: Var_PointerPasser(T * pT)
			{this->gT = pT;}
	};*/
	
	/*
	THE FOLLOWING WHICH IS MEANT FOR VC6 STILL DOES NOT WORK IF IT WAS
			#define MyClass_GetP(TYPE) 	getP<TYPE>(static_cast<TYPE *>(NULL))
	INSTEAD ONE MUST REMOVE "<TYPE>" AS BELOW
	
	HOWEVER, REMEMBER VC6 DOES NOT HAVE VAR ARGS MACROS, AND YOU WOULD HAVE TO USE
	THE SPECIAL TRICK FOR THAT, WHICH ENDS UP CAUSING TROUBLE IN NEWER COMPILERS BECAUSE
	OF UNUSED MACRO VARIABLES. (SEE crx.h). THIS IS IMPORTANT BECAUSE YOU WANT THIS TO WORK
	WITH TEMPLATES.
	
	(NOTE THAT getP IS A FUNCTION ON Var
	*/
	#define CRX__VAR__GETP(TYPE) getP(static_cast<TYPE *>(NULL))

	//RE(int, 1, 0, 0, 0);

	#pragma endregion Var pointer //}
	
	CRX__C__Ring__DECLARE(Crx_VarRing, 
			crx_varRing_, Var, uint32_t, ((uint32_t)(-1)), 0, CRXM__FALSE, 4, CRXM__FALSE,
			var_private_destruct, var_private_copyConstruct, CRXM__FALSE, CRXM__FALSE)

	//VC6: HAD TO MOVE THE CLASS OUT OF VAR BECAUSE VC6 COMPILER DOES NOT SEE VAR WHILE IN
	//		IT IT SEEMS WHEN USING SOMETHING LIKE Var::String. USING String ALONE, WHICH
	//		IS AGAINST MY STANDRD, PROVED AMBIGUOUS LEADING TO ERRORS.
	class Var_String /*SIZE MUST BE 24 BYTES IF SEEKING 32BIT SIZED VAR*/
	{
		public: size_t gLength;
		public: size_t gCapacity;
		public: int32_t gCount;
		public: char gChars[4 /*N*/]; //4 IS TO AVOID EMPTY SPACE AFTER ARRAY DUE TO ALIGMENT

		public: enum {LENGTH_OF_OVERHEAD = sizeof(size_t) + sizeof(size_t) + sizeof(int32_t)};

		private: Var_String()
			{}
		public: static /*VC6 Var::*/Var_String * newString(size_t pSizeOfBuffer)
		{
			CRX__BOOST_ASSERT(pSizeOfBuffer > 4);

			void * vPointer = ::operator new(sizeof(Var_String) +
					(pSizeOfBuffer - 4) * sizeof(char));
			Var_String * vString = new(vPointer) Var_String();
			
			if(vString == NULL) //FOR WHEN EXCEPTIONS ARE DISABLED
				{::exit(EXIT_FAILURE); /*::abort()*/}

			vString->gLength = 1;
			vString->gCapacity = pSizeOfBuffer;
			vString->gCount = 1;
			vString->gChars[0] = '\0';

			return vString;
		}

		CRX_DISABLE_METHOD(/*VC6 Var::*/Var_String(/*VC6 Var::*/Var_String const &))
		CRX_DISABLE_METHOD(/*VC6 Var::*/Var_String & operator=(/*VC6 Var::*/Var_String const &))


		CRX_DISABLE_METHOD(~Var_String())
		public: static void deleteString(/*VC6 Var::*/Var_String * pString)
			{::operator delete(pString);}
	};
	
	class Var
	{
		/*VC6 template<bool T> friend class Var_VarIterator;
		template<bool T> friend class Var_StringIterator;*/
		friend class Var_VarIterator<true>;
		friend class Var_VarIterator<false>;
		friend class Var_StringIterator<true>;
		friend class Var_StringIterator<false>;

		/** STRING
		ISSUES TO CONSIDER FOR THE STRING IMPLEMENTATION:
			- ENCODING.
			- MUTABLE OR NOT.
				- IF NOT MUTABLE, COPY ON WRITE HAS MORE ADVANTAGES
			- ON DYNAMIC ONLY OR ON STACK ONLY, OR BOTH ALLOWED.
			- SMALL STRING OPTIMIZATION, WHICH WOULD USE STACK, OR NO SMALL STRING OPTMIZATION.
			- VERY LARGE STRING OPTIMIZATION, WHICH WOULD USE A ROPE STRUCTURE (A BINARY TREE),
					OR NO VERY LARGE STRING OPTIMIZATION.
			- OPERATOR BEHAVIOR.
			- USE MOVE SEMANTICS OR NOT.
				- IF NO, COPY ON WRITE CAN BE USEFUL.
				- IF YES, COPY ON WRITE CAN BE EXPENSIVE WHEN IT COMES TO THREAD SAFETY.
			- COPY ON WRITE, OR NO COPY ON WRITE.
				- IF YES, BUT WITH MUTABILITY, THREAD SAFETY BECOMES AN ISSUE TO SOLVE.
				- CAME UP WITH COPY ON WRITE USING A SECONDARY IMMUTABLE BUFFER FOR A LOCKLESS MECHANISM,
						BUT LOGIC INDICATES THAT THIS IS UNLIKELY TO BE FASTER THAN MOVE SEMANTICS.
				- TESTS ONLINE, ON THE GOTW SITE, INDICATE COPY ON WRITE TO BE NEVER FASTER FOR MULTITHREADED
						ENVIRONMENTS USING BOTH LOCK AND LOCKFREE ALGORITHMS FROM WHAT I COULD TELL AND THIS IS
						WITHOUT THE AVAILABILITY OF MOVE SEMANTICS. HOWEVER OTHER LANGUAGES, SUCH AS PHP AND
						SWIFT CONTINUE TO USE COPY ON WRITE FOR STRINGS. FACEBOOK C++ STRING WORK INDICATES
						THAT COPY ON WRITE CAN BE FASTER FOR LARGE ENOUGH STRINGS, ROUGHLY LARGER THAN 
						250 BYTES, BUT I THINK IT WOULD DEPEND ON THE HARDWARE.
				- THE MULTITHREADING OF COPY ON WRITE IS NOT AN ISSUE OF THE STRING CLASS BEING THREAD SAFE. THE
						STANDARD STRING CLASS IS NOT THREAD SAFE, BUT BY USING LOCKS WE CAN USE IT SAFELY. HOWEVER,
						IF COPY ON WRITE IS USED BY THE CLASS, LOCKS DO NOT HELP BECAUSE THE COPY ON WRITE
						MECHANISM ITSELF NEEDS TO BE THREAD SAFE.
		CURRENT DECISIONS:
			- SUPPORT UTF8 AND UTF32
			- BOTH DYNAMIC ONLY, AND STACK ONLY IMPLEMENTATION ALLOWED. THIS SHOULD BE USEFUL FOR
					EMBEDDED SYSTEMS.
			- OPERATOR BEHAVIOR SHOULD FOLLOW WHAT I CALL "LHS SEMANTICS". THIS MEANS WITH
					a + b, WHERE + IS ANY OPERATOR, THE RESULT OF THE EXPRESSION IS DETERMINED
					BY THE IMPLMENTATION OF 'a'. IN OUR CASE, THE IMPLEMENTATION IS SUCH AS
					THE TYPE OF THE EXPRESSION MUST BE THE TYPE OF a, AND WHEN CASES WHERE
					CONVERTING 'b' TO THE TYPE OF 'a' IS NOT WELL DEFINED, AND SENSICAL,
					THE OPERATION SHOULD GIVE AN ERROR.
			- NO COPY ON WRITE.
				- FACE BOOK STRING IMPLEMENTATION, fbString, WHICH HAS COPY ON WRITE, GAVE 1% INCREASE IN
						PERFORMANCE FOR THEIR WEBSITE. HOWEVER THERE IMPLEMENTATION WAS FASTER THAN GCC STRINGS
						(GCC 4) I THINK, FOR THE STRING LENGTH RANGE WHERE COPY ON WRITE IS USED BY AROUND 60%.
						GOOGLE'S OWN STRING IN THE EARLY (DAYS EARLY 2000S AND BEFORE) RUN THEIR PROGRAMS FASTER
						THAN WHEN USING GCC STRINGS (GCC 3 I THINK) BY 2%. I AM ACTUALLY UNSURE IF IS THE ENTIRE
						PROGRAM THAT WAS BENCHMARKED, LIKE I SAID, OR JUST OPERATIONS ON THE STRING CLASSES.
						FACEBOOK MOVED TO USE STD STRING FOR ITS "folly::dynamic" TYPE.
				- IN THE END, I NEVER REALY GOT A REAL RESULT AS TO WHETHER COW CAN BE MADE BETTER THAN NO
						COPY ON WRITE AT ALL WITH MOVE SEMANTICS.
			- MOVE SEMANTICS: BECAUSE NO COPY ON WRITE.

		THE IDEAL STRING CLASS BASED ON MY BEST CONCLUSION
			- SUPPORTS UTF8 AND UTF32.
			- LHS OPERATOR SEMANTICS.
			- 32 (OR 31) BYTE SIZE TO FIT CPU CACHE.
			- AN INTERNAL BUFFER FOR SMALL STRING OPTIMIZATION THAT IS AS LARGE AS POSSIBLE.
			- A ROPE IMPLEMENTATION FOR VERY LARGE STRINGS. (PERHAPS, > 0.5 MEGA BYTES)
			- A CUSTOM OPTIMIZED ALLOCATOR.

		THE IDEAL STRING IMPLEMENTATION INSIDE Var
			- SUPPORTS UTF8 AND UTF32.
			- LHS OPERATOR SEMANTICS.
			- 32 (OR 31) BYTE SIZE TO FIT CPU CACHE.
			- AN INTERNAL BUFFER FOR SMALL STRING OPTIMIZATION THAT IS AS LARGE AS POSSIBLE.
				- SOULD BE LARGER THAN, OR EQUAL TO, 25 BYTES TO BE ABLE TO REPRESENT
						ANY DOUBLE. (SEE BELOW).
					- BECAUSE 25 BYTES PROVED IMPOSSIBLE TO PROVIDE, WE HAVE TRY EACH CONVERSION
							OF A DOUBLE IF WE ARE USING THE BUFFER SPACE, AND IF IT NOT ENOUGH
							WE ALLOCATE A LARGER SIZE ON THE HEAP.
			- A NON COPY ON WRITE IMPLEMENTATION FOR STRINGS UP TO 255 BYTES.
			- A CONDITIONAL COPY ON WRITE IMPLEMENTATION FOR STRINGS LARGER THAN 255 BYTES. 
				- THE Var RUNS ON TWO MODES, NEITHER ARE THREAD SAFE.
					- MODE 1: INSTANCE IS INDENTED TO BE USED ACROSS THREADS. IN THIS CASE, NO COPY
							ON WRITE IS USED.
					- MODE 2: INSTANCE IS INDENTED TO BE USED ON A SINGLE THREAD. IN THIS CASE,
							COPY ON WRITE IS USED, WITHOUT ANY THREAD SAFETY AT ALL.
				- THE CONDITION OF WHETHER COPY ON WRITE IS USED IS SET BY EITHER AN EXPLICIT
						CONSTRUCTOR CALL WITH AN EXTRA BOOLEAN PARAMATER, OR IMPLICIT
						DEPENDING ON THE TYPE PASSED TO CONSTRUCTOR. A CHOICE BETWEEN "std::string"
						AND "char *", WHERE ONE OF THE TWO WILL CAUSE MODE 2.
				- ONCE CONSTRUCTED, THE MODE CAN NOT BE CHANGED.
			- A ROPE IMPLEMENTATION FOR VERY LARGE STRINGS. (PERHAPS, > 0.5 MEGA BYTES)
			- A CUSTOM OPTIMIZED ALLOCATOR.
				- IT IS NOT WORTH HAVING AN ALLOCATOR SPECIFIC TO THE STRING CLASS. INSTEAD
						A GOOD ALLOCATOR THAT REPLACES C'S malloc FAMILY OF FUNCTIONS IS
						BETTER. GIVEN MY OWN DECISIONS OF WHAT A GOOD ALLOCATOR
						WOULD BE CAPABLE OF DOING, AT LEAST jemalloc BY FACEBOOK ALREADY
						ACCOUNTS FOR ALL MY DECISIONS WHETHER DIRECTLY OR INDIRECTLY, AND
						HENCE BUILDING A CUSTOM ALLOCATOR IS NOT WORTH. NOTE THAT
						MICROSOFT'S memalloc IS ALSO LIKELY TO BE FAST THAN jemalloc, BUT
						I AM UNSURE IF IT ALREADY USES MY DESIGN DECISIONS. MY DECISIONS
						INCLUDED:
					- TAKE ADVANTAGE OF FIXED SIZE STRUCTURES OF 32BYTES.
					- TAKE ADVANTAGE OF VARIABLE SIZE STRUCTURES THAT HAVE SIZES THAT
							ARE MULTIPLES OF 32.
					- USE THE EMPTY SPACE ITSELF TO KEEP TRACK OF THE EMPTY SPACE.
					- AVOID LOCKS, OR SYNCRHONIZATION ISSUES ALL TOGETHER FOR
							THREAD SAFETY.

		*/
		/** NUMBERS


		IT IS NOT WORTH THE TROUBLE TO SUPPORT EVERY INTEGRAL TYPE. ONE LARGER TYPES CAN EASILY HOLD SMALLER
				TYPES. AND TWO, PERFORMANCE DIFFERENCE BETWEEN THE FLOAT, 'DOUBLE', AND LONG LONG INT IS
				MINIMAL. I SAW A GOOD NUMBER OF CASES WHERE 'DOUBLE' OPERATIONS WERE EVEN FASTER. LONG DOUBLE
				ARE LIKELY TO BE SLOWER, BUT I HAVE NOT SEEN ANY BENCHMARKS. 

		FOR ACCURACY, IT SEEMS BEST TO INSTRUCT THE COMPILER TO USE SSE INSTRUCTIONS
				FOR FLOATING POINT ARIUTHMETICS ON X86 AND X64. ON X64 COMPILERS 
				(MOST IF NOT ALL) DO USE SSE INSTRUCTION. THIS SHOULD GUARANTEE
				SAME BEHAVIOR ON ALL MACHINES, HOWEVER BREAKS SOME BACKWARD
				COMPATIBILITY WITH HARDWARE. WITH THIS, COMPATIBILITY FOR SINGLE
				PRECISION IS ROUGHLY PENTIUM 3 AND UP, AND INCLUDES ATHLON XP. FOR
				DOUBLE PRECISION IT IS PENTIUM 4 AND UP, AND EXCLUDES ATHLONG XP. 
				AN OPTION FOR USING DOUBLE PRECISION SSE MIGHT END UP USING '387'
				INSTRUCTIONS FOR THOSE OLDER MACHINES, WHICH ARE MORE ACCURATE, 
				BUT SLOWER, THAN SSE WITH DOUBLE PRECISION, AND BREAK
				THE REQUIREMENTS OF SAME BEHAVIOR ACROSS ALL MACHINES. FOR DOUBLE
				PRECISION ONE HAVE TO THEN USE '387' ON ALL MACHINES, X86 AND X64,
				IF TO KEEP THE SAME BEHAVIOR.

		FOR ACCURACY AND PERFORMANCE WE WANT OUR SHORT STRING OPTIMIZATION TO BE
				AT LEAST 18 BYTES. THIS IS BECAUSE DOUBLE PRECISION NUMBERS "double"
				CAN BE CORRECTLY REPRESENTED BY 17 DIGIT BASE 10 NUMBER, AND STILL
				CONVERTED BACK ACCURATELY. ANY LESS THAN 17, AND WE NO LONGER
				GET THIS GUARANTEE, WHICH IS CALLED "ROUND TRIP". HOWEVER, DUE
				TO BUGS, EVEN WITH ENOUGH DIGITS, ROUND TRIP MIGHT BE IMPOSSIBLE. I
				HAVE SEEN A TALK ABOUT THIS HAPPENING ON THE TRIP BACK FROM THE 
				17 DIGIT NUMBER TO MACHINE FLOAT ON A MICROSOFT C++ COMPILER.

		FOR ACCURACY, CONVERSION FROM INT TO STRING AND BACK TO INT MUST YIELD THE SAME RESULT.
				CURRENT ALGORITHM CANDIDATES FOR INT TO STRING ARE THE ONE BY 
				'user434507' FOR GCC AND THE ONE BY 'Timo' FOR VC. HOWEVER, 
				BENCHMARKS PROVIDED BY 'milo' SUGGEST FASTER IMPLEMENTATIONS.

		FOR ACCURACY, CONVERSION FROM DOUBLE TO STRING AND BACK TO DOUBLE MUST YIELD THE SAME RESULT.
				CURRENT ALGORITHM CANDIDATE IS THE ONE BY GOOGLE BY THE NAME 'double conversion'. 
				THERE IS ALSO AN ALGORITHM BY 'milo' BUT PROBABLY SAFER TO AVOID.
				ALGORITHMS THAT CONVERT TO STRING INCLUDE:
				grisu2, grisu3: THESE ALGORITHMS ARE FAST, AND 'double conversion' USED grisu3. 
						HOWEVER THESE ALGORITHM FAIL FOR SOME NUMBER, AND A FALL BACK NEEDS
						TO BE USED SUCH AS THE Dragon4 ALGORITHM.
				Dragon4: THIS IS ALGORITHM IS SLOWER, BUT COVERS ALL POSSIBLE NUMBERS.
				Ryu: THIS ALGORITHM IS SLOWER THAN grisu2, grisu3, BUT SOME PAPER SUGGESTED
						IT IS FASTER.


		DECISIONS:
			- STICK TO DOUBLE AND 64 BITS INTEGERS FOR NUMBERS.
			- HOWEVER CHECKS MUST BE MADE FOR TYPES LIKE LONG LONG WHERE THE DOUBLE HAS A 
					SMALLER WHOLE NUMBER RANGE. 
			- WHEN A 64BIT INTEGER IS AVAILABLE A 64BIT INTEGER WILL BE USED FOR STORAGE. 
					BUT WHERE IT IS NOT, A DOUBLE SHALL BE USED. 
			- IT IS ASSUMED THAT A DOUBLE WILL ALWAYS BE 64BIT AND LARGER.
			- INTEGER OPERATIONS WHEN A DOUBLE IS USED MUST BE ENSURED TO BE SAFE, WHERE SAFE
					MEANS THAT THEY ARE ALWAYS PRECISE ENOUGH FOR THE OPERATION. THIS MEANS, FOR
					EXAMPLE A + 1 > A, WHERE A IS A DOUBLE, AND "A + 1" PERFORMED N TIMES IS EXACTLY
					"A + N", WHEN A IS A DOUBLE HOLDING A WHOLE NUMBER.
			- ROUND TRIPS FOR DOUBLES TO STRINGS AND BACK, AND INTEGERS TO STRINGS AND BACK (TRIVIAL)
					MUST BE GUARANTEED FOR BASE 10 NUMBERS.
			- NO HEX SUPPORT FOR NUMBERS IN STRING FORMAT DUE TO THEM REQUIRING MORE THAN 24 CHARACTERS
			- NO SUPPORT FOR UNSIGNED INT64, BUT SUPPORT FOR SIGNED INT64. THIS IS DUE TO AMBIGUITY
					WHEN CONVERTING BACK FROM STRING, AND WANTING TO AVOID ANY NON STANDARD
					STRING REPRESENTATION OF NUMBERS. REMEMBER THAT LARGER INTEGERS CAN NOT BE STORED
					IN A DOUBLE IF WE ARE TO ENFORCE WPG (SEE BELOW.), AND SO WE WOULD USE
					INT64 FOR MAXIMUM RANGE. THE PROBLEM, HOWEVER, IS THAT UINT64 HAS A LARGER
					POSITIVE RANGE. ON THE OTHER HAND, WHEN INT64 IS NOT AVAILABLE WE CAN STILL
					SUPPORT UINT32 BECAUSE IT CAN STILL BE STORED ON A DOUBLE WHILE MEETING WPG.
			- I DO NOT SUPPORT HARDWARE WITH SATURATING ARITHMETICS. THIS IS HARDWARE WHERE
					INTEGER OVERFLOWS DO CAUSE INTEGERS TO WRAP AROUND, BUT INSTEAD INTEGERS
					CLAMPED AT THE MAXIMUM OR MINIMUM VALUE.
		*/
		/*
			ISSUES:
				- WHEN THERE IS NO INT64, CURRENTLY INTEGER OVERFLOWS DO NOT BEHAVE THE SAME
						WAY WHEN OVERFLOW HAPPEN WHEN THE UNDERLYING TYPE IS INT64 IN VAR. REMEMBER
						THAT WHEN INT64 IS NOT AVAILABLE A DOUBLE IS USED, AND CURRENTLY WHEN
						THE VALUE GOES OUTSIDE THE STABLE RANGE OF DOUBLES FOR INTEGER DUE TO
						AN OPERATION WITH AN INTEGER, THE UNDERLYING VALUE IS SET TO NAN. IN
						THE FUTURE THE VALUE WOULD HAVE TO BE SET TO APPEARS AS IF IT HAS
						WRAPPED AROUND LIKE WHAT HAPPENS WITH INT64.
				- WHEN THERE IS NOT INT64, CURRENTLY ENDIANES CHECK, WHERE IT IS NEEDED, IS
						ONLY FOR ENDIANESS GIVE BYTE SWAP, AND NOT WORD SWAP. IN THE FUTURE
						YOU NEED TO TAKE INTO ACCOUNT WORD SWAP.
				- WHEN ARRAYS ARE IMPLEMENTED USING Crx_VarRing, ERRORS, PARTICULARLY OUT OF MEMORY
						ONES, BEHAVE DIFFERENTLY WHEN Crx_VarRing ITSELF IS STORED AS PART OF
						Var, INSTEAD OF A POINTER TO IT STORED AS PART OF Var. 
						THIS PROBLEM LIKELY ALSO EXISTS FOR THE USAGE OF std::string
				- WHEN ARRAYS ARE IMPLEMENTED USING std::deque ERRORS WHERE THE std::deque FUNCTIONS
						WOULD THROW AN EXCEPTION BEHAVE DIFFERENTLY THAN WHEN USING Crx_VarRing.
						THIS IS BECAUSE Crx_VarRing FUNCTIONS DO NOT USE EXCEPTIONS, WHEN EXCEPTIONS
						ARE DISABLED, LIKE WHEN THEY ARE ENABLED, THEY CAN SIMPLY RETURN TRUE OR FALSE.
						WITH std::deque TRY-CATCH BLOCKS WORK TO TRANSLATE THAT TO TRUE OR FALSE.
						HOWEVER, IF EXCEPTIONS ARE DISABLED, AND THIS IS NOT TO BE CONFUSED WITH THE
						VAR ERROR MODES, BUT THIS IS WHEN EXCEPTIONS ARE DISABLED AT THE COMPILER
						LEVEL, THEN THE std::deque CAN NOT THROW AN EXCEPTION, AND THE BEHAVIOR
						IS UNDEFINED IF THERE IS AN ERROR. HOWEVER STD IMPLEMENTATIONS ARE LIKELY TO
						ABORT THE PROGRAM.
				- WHEN THE INTERNAL NUMBER IS REPRESENTED USING A DOUBLE, AND THE INTERNAL INTEGER
						MODE IS INT64, OPERATORS CAN BEHAVE DIFFERENTLY WHEN IT COMES TO THE ALLOWED 
						RANGE OF INT NUMBER STRINGS.
						FOR EXAMPLE IF THE INTERNAL INTEGER MODE IS INT64,
								5.0 + "36028797018963968"
						WOULD NOT WORK, WHILE
								5 + "36028797018963968"
						WOULD. THIS IS TO EASE DEVELOPMENT. WHEN THE INTERNAL TYPE IS A DOUBLE,
						NO ATTEMPT IS MADE TO CHECK WHETHER THE NUMBER STRING IS AN INT NUMBER
						STRING OR NOT, AND INSTEAD PARSING IS DONE STRAIGHT TO A DOUBLE, AND 
						HENCE WHEN THE UNDERLYING TYPE IS INT64, WHICH IS LARGER THAN THE SAFE
						INTEGER RANGE OF DOUBLE, THE STRING WOULD STILL BE SEEN AS NOT PARSED
						CORRECTLY WHEN THE NUMBER IT REPRESENTS IS LARGER THAN THE SAFE INTEGER
						RANGE ON DOUBLE YET SMALLER THAN INT64 RANGE. NOTE THAT THIS DOES NOT 
						VIOLATE MORPHING RULES. ON THE OTHER HAND IF THE INTERNAL NUMBER IS
						REPRESENTED USING THE INT64, THE NUMERIC STRING IS CHECKED TO SEE IF IT
						IS AN INT NUMBER STRING, AND INSTEAD IT IS PARSED TO INT64 INSTEAD.
						

						
						UPDATE: I SEEM TO HAVE MADE A MISTAKE, OR PERHAPS A DEFINITION, SUCH AS
						THAT OF THE VAR + OPERATOR CHANGED. THE ABOVE IS NOT AN ISSUE, AND 
						THE BEHAVIOR DESCRIBED ABOVE IS EXACTLY PER THE MORPHING RULES.
						THE FOLLOWING
										5.0 + "36028797018963968"
						IS ONLY VALID IF "36028797018963968" CAN BE LOOSE MORPHED TO DOUBLE,
						AND IT CAN NOT EVEN WHEN THE INTERNAL TYPE IS INT64. SEE THE DESIGN
						OF THE + OPERATOR BELOW, AND THE DESIGN OF THE TYPE RELATIONS (THE 
						LOOSE MORPH GROUPS)
				- WHEN THE INTERNAL STRING IS NOT STD STRING, AND IS RUNNING IN LARGE BUFFER SEGMENT
						MODE, THE BENEFIT IS LOST WHEN THE VAR IS USED AS KEY TO THE OPERATOR [].
				- KEYS USED FOR [] CAN NOT CONTAIN A NULL. THEY WORK UNDER CERTAIN CIRCUMSTANCES,
						AND NOT OTHERS. IF Khash IS USED, THEY DO NOT WORK, FOR EXAMPLE. CURRENTLY
						THE CODE IS WRITTEN TO ANTICIPATE SUCH KEYS WORKING ALL THE TIME, BUT THIS
						MIGHT CHANGE IN THE FUTURE. IF CHANGED IN THE FUTURE, THE OPERATOR []
						THAT TAKES A std::string WOULD END UP FARWARDING TO THE OPERATOR []
						THAT TAKES A NULL TERMINATED char ARRAY. THIS ALSO AFFECTS hasKey()
				- CURRENTLY, THE IMPLEMENTATION OF THE [] OPERATOR LEADS TO SITUATIONS WHERE THE
						PROGRAM IS ABORTED WHEN THE ERROR MODE IS SWALLOWING. REMEMBER THAT
						ABORTING PROGRAM SHOULD NOT HAPPEN WHEN THE MODE IS SWALLOWING.
				- WHEN THE INTERNAL ARRAY OR HASH TABLE IMPLEMENTATION USES TYPES FROM std,
						LIST INITIALIZATION OF THE VAR CAN ACT DIFFERENTLY WHEN THE PARAMETER
						pIsToBeThreadPossible IS false. WHEN A std CONTAINER TYPE, EACH VAR
						CREATED TO BE IN THE CONTAINER, WILL EITHER BE THREAD POSSIBLE OR NOT 
						POSSIBLE DEPENDING ON THE THREAD POSSIBILITY OF THE VAR BEING COPIED. WHEN 
						THE COLLECTION IS NOT BASED ON A TYPE FROM std, THE VAR CREATED WILL 
						ALWAYS BE NOT THREAD POSSIBLE. NOTE THAT THE ASSUMPTION IS THAT THE std
						CONTAINERS WILL USE THE Var::Var(Var) CONSTRUCTOR.
				- LIST INITIALIZATION WILL LIKELY REQUIRE GIVING HINTS TO THE COMPILER TO LET IT
						DECIDE WHICH VAR CONSTRUCTOR TO USE. THE HINT IS IN THE FORM OF EXPLICITY
						USING A std::pair FOR THE FIRST PARAMETER IS THE LIST INITIALIZATION IS
						MEANT TO BE FOR A VAR WITH VAR TYPE HASH TABLE.
				- SOMETHING LIKE THE FOLLOWING
								class Test
								{
									public: typedef deque<Test>::iterator t;
								};
						FAILS IN MSVC. IT IS AS IF THE COMPILER IS TRYING TO INSTANTIATE THE TEMPLATE
						deque<Test> AT THE LINE OF typedef WHICH THEN FAILS BECAUSE test IS INCOMPLETE AT
						THAT POINT. EVEN THE FOLLOWING FAILS:
								class Test
								{
									public: deque<Test>::iterator doSomething();
								};
						REMEMBER THAT THE CODE ABOUT Test::doSomething() IS JUST A DECLERATION, BUT THE
						COMPILATION STILL FAILS. BECAUSE OF THIS, IN CASES WHERE ONE NEED TO typedef AN ITERATOR
						BASED ON A COMPILATION OPTION, ONE CAN NEITHER RELY ON typedef NOR A MACRO TO DEFINE
						A GENERIC MEMBER FUNCTION. NO ONLY THAT, ONE CAN NOT EVEN DEFINE A FUNCTION USING
						SUCH AN ITERATOR AS PART OF THE CLASS!
						NOTE THAT IN THE PAST, STL CONTAINERS COULD ALSO THEMSELVES NOT BE USED THIS, AND
						NOT WHAT IS DEFINED IN THEM. HOWEVER AT SOME POINT THIS STOPPED BEING THE CASE
						AND FOLLOWING BECAME VALID
								class Test
								{
									public: typedef deque<Test> t;
								};
						HOWEVER, THIS DOES NOT SEEM TO BE GUARANTEED BY THE STANDARD. IN ANY CASE, WHERE
						THIS HAS PROVEN A PROBLEM, A PROXY ITERATOR WAS CREATED TO HIDE THE STL CONTAINER 
						ITERATOR SO FAR, THIS HAS ONLY AFFECTED std::deque. THE PROXY ITERATORS WOULD BE
						USED BY THE VAR ITSELF. HOWEVER, THE ACTUAL ITERATORS THAT THE CLIENT NEEDS TO USE,
						MEANING THE STL CONTAINER ITERATORS CAN STILL NOT BE DEFINED ON VAR. INSTEAD A GLOBAL
						NAMESPACE typedef MUST BE USED. FOR EXAMPLE, IN THE PAST Var::ArrayStlIterator WAS
						PUBLIC, BUT NOW IT IS PRIVATE, AND INSTEAD THE USER MUST USE Var_ArrayStlIterator. AS
						FOR Var::ArrayStlIterator, INSTEAD OF POINTING TO THE STL ITERATOR, IT INSTEAD
						POINTS TO THE PROXY ITERATOR, Var_DeuqueIterator, AND Var_ArrayStlIterator WOULD POINT
						TO THE STL ITERATOR.
				-THE CONSTRUCTOR 
								public: template<typename T>
								Var(T * pT, bool pIsToBeThreadPossible CRX_DEFAULT(false))
						CAN END UP HIDING ERRORS IF THE USER INCORRECTLY PASSES A POINTER OF A TYPE INSTEAD
						OF THE VALUE ITSELF. THIS ESPECIALLY HAPPENS WHEN THE TYPE IS Var.
				- IN VC6, THE VAR CONSTRUCTOR FOR POINTER TYPE AND THE VAR CONSTRUCTOR THAT TAKE A 
						char const * TYPE COULD NOT BE MADE TO WORK TOGETHER. THE ORIGINAL, WITH POINTER
						CONSTRUCTOR TEMPLATED, AND char const * CONSTRUCTOR NOT TEMPLATED, DID NOT
						WORK. TRIED WITH THE POINTER CONSTRUCTOR TEMPLATED, AND THE char const * CONSTRUCTOR
						BEING A SPECIALIZED TEMPLATE, ALSO DID NOT WORK. TRIED WITH REMOVING THE
						char const * CONSTRUCTOR COMPLETELY, BUT THAT PROVED FAR MORE INCONVENIENT THAN
						WHEN DISABLING THE POINTER CONSTRUCTOR. FOR COMPATIBLE CODE, TO CREATE
						A POINTER, INSTEAD OF DOING,
								Var vPointer = new MyClass(3);
						ONE CAN DO FOR COMPATIBILITY
								Var vPointer;
								vPointer.setP(new MyClass(3));
			SIZE:
				- THE VARRING IS SET TO HAVE SIZE 32 BYTES. HOWEVER, LATER IT WAS DEDUCED THAT THIS
						MIGHT NOT BE AS BENEFICIAL AS IT IS FOR A STRING ONLY CLASS. THEREFORE
						THE VARRING IS DESIGNED SUCH AS THE USER CAN LOWER ITS SIZE THROUGH
						CONFIGURATION DOWN TO 16 BYTES.

			ARRAYS:
				- CURRENTLY A DEQUE IS USED FOR AN ARRAY. ALTHOUGH A CIRULAR BUFFER MIGHT
						BE IDEAL, THERE ARE SOME ISSUES TO CONSIDER:
					- A CIRCULAR BUFFER CAN INVALIDATE ALL REFERENCES WHEN ADDING ELEMENTS TO
							EITHER END, UNLIKE A DEQUE.
				- DUE TO THESE ISSUES, THE CURRENT IMPLEMENTATION KEEPS USE OF DEQUES.
				- BECAUSE THE OPERATOR [] IS USED TO ACCESS ARRAY ELEMENTS, COPY ON WRITE CAN
						NOT BE USED ON THE ARRAY. REMEMBER THAT THE OPERATOR [] MUST RETURN A
						REFERENCE IF THE STATEMENT 
								varInstance[int] = value;
						IS VALID.
			
			INTEGER:
				- THE CODE IS WRITTEN ASSUMING THAT THE SMALLER INTEGER IN THE COMPILATION OPTIONS
						IS INT32. IF YOU EVER DECIDE TO ADD SUPPORT FOR SMALLER INTEGERS, THE CODE
						WILL BECOMES INVALID. AT THE TIME OF THIS WRITING, THE COMPILIATION
						OPTIONS GIVE INT32, INT64, AND INT52 (EMULATED INT)

			HASHTABLE
				- LIKE THE SITUATION WITH ARRAYS, COPY ON WRITE CAN NOT BE USED BECAUSE THE DESIGN
						IS TO ALLOW USAGE OF THE OPERATOR [];
				- INSERTION ORDERED KEYS OR NOT:
					- LANGUAGE SURVEY:
						- AUTOHOTKEY: NO, IT SEEMS. THERE MIGHT BE SOME OTHER ORDERING, BUT NOT BASED
								ON INSERTION.
						- RUBY: YES. (SINCE 2014 ROUGHLY)
						- PHP: YES.
						- PYTHON: YES SINCE v3.7, BUT BECAUSE MY REFERENCE THERE IS 2.7, THE ANSWER IS NO.
								HOWEVER THERE EXISTS IN THAT VERSION, 2.7, A TYPE THAT PRESERVES ORDERING.
						- JAVASCRIPT: YES FOR NON NUMERIC STRINGS, AND YES FOR SYMBOL KEYS. FOR NUMERIC
								STRINGS, SUCH AS "1", THE BEHAVIOR CAN DIFFER BETWEEN BROWSERS INCLUDING
								THOSE SINCE MY REFERENCE POINT IN THAT LANGUAGE, IE8.
					- IT APPEARS BEST TO DESIGN WITHOUT INSERTION ORDER, BECAUSE INSERTION ORDERED 
							HASHTABLE ALWAYS APPEAR TO USE SECODNARY STRUCTURE FOR PRESERVING
							THE ORDER. THIS MAKES ADDING THE FUNCTIONALITY POSSIBLE AFTER THE FACT,
							AND THAT SUCH FUNCTIONAILITY IS SLOWER.
							THE DESIGN, HOWEVER, GIVEN THE LANGUAGE SURVEY, SHALL HAVE AN INSERTION ORDERED
							HASHTABLE OPTION THAT THE USER CAN SET AT RUNTIME, AND ORDER IN THAT CASE SHALL
							LIKELY BE KEPT BY MEANS OF AN EXTRA LINKED LIST, OR POSSIBLY AN ARRAY USING MY
							C ARRAYS.
				- IF INITIALIZED FROM A LITERAL/INITILIZATION LIST, AND A DUPLICATE KEY EXISTS,
							THE VALUE FROM THE LAST KEY ENTRY IS THE ONE THAT HOLDS. I DID A SURVEY
							OF OTHER LANGUAGES, RUBY, PHP, PYTHON, AND JAVASCRIPT, AND THEY ALL
							BEHAVE THE SAME WAY.
			ALLOCATOR:
				- IDEALY A SPECIALIZED ALLOCATOR THAT TAKES ADVANTAGE OF 32BYTES FIXED SIZE,
						AND SUPPORTS NOTHING ELSE, AND REPLACES THE C malloc FAMILY OF FUNCTIONS
						WOULD BE IMPLEMENTED TO BE USED EXCLUSIVELY BY THE Var CLASS, AND THIS
						IS ALMOST CERTAIN TO BE FAR MORE EFFICIENT THAN jemalloc AND OTHER
						SUCH IMPLEMENTATIONS. HOWEVER DUE TO THE FACT THAT IT IS UNLIKELY
						FOR Var TO BE USED ON THE HEAP, IT IS UNLIKELY TO HAVE VERY
						SIGNIFICANT ADVANTAGE FROM THE SPEED UP OF SUCH A SPECIALIZED ALLOCATOR.
				- THE OTHER CONCERN IS WHEN VAR MUST USE THE HEAP, MEANING WHEN IT IS IN STRING
						MORE. IN THIS CASE, THE SITUATION IS LIKE WITH THE STRING CLASS DESIGN
						(SEE ABOVE), AND THE SUMMARY IS THAT THERE IS NO BENEFIT TO IMPLEMENTING
						A CUSTOM ALLOCATOR, AND INSTEAD ONE CAN SIMPLY MAKE USE OF jemalloc
						AND OTHER SIMILAR IMPLEMENTATIONS THAT REPLACE THE C malloc FAMILY
						OF FUNCTIONS. HOWEVER, THE STRING DYNAMIC MEMORY MUST STILL
						BE ALLOCATED AS A MULTIPLE OF 32 BYTES. THIS IS ALSO PER THE ASSUMPTIONS
						OF MY DESIGN DECISIONS, AND WHEN AN ALLOCATOR SUCH AS jcmalloc, WHICH
						ADDRESSES MY DESIGN DECISIONS, IS USED, IT IS GOOD.
						WHAT REMAINS IS THE ARRAY IMPLEMENTATION, AND HASH TABLE IMPLEMENTATION
						FOR WHICH I HAVE NO CONTROL OVER, BUT IF POSSIBLE, IT WOULD BE IDEAL TO
						HAVE THESE BE A MULTIPLE OF 32 BYTES.
			BYTES:
				- IN THE PAST I HAD AN unsigned char, AND signed char TYPES IN THE VAR. THEY WERE MEANT
						FOR BYTES. AS TIME WENT BY THEIR ROLE WAS LEFT FOR BIT MANIPULATION FROM 
						WHAT I COULD TELL FROM THE CODE. THE NUMBER TYPE WAS NOT ALLOWED FOR BIT
						MANIPULATION. FURTHER MORE THE NUMBER TYPE COULD NOT BE CAST TO THE BYTE
						TYPE AT ALL. LATER I BELIEVE I WAS TO FIX THE MORPH FUNCTION AND ALSO DISALLOW
						MORPHING A VAR WITH NUMBER IN IT TO A VAR WITH A SIGNED CHAR OR UNSIGNED
						CHAR IN IT.
						AT SOME POINT I REMOVED THE SIGNED CHAR, KEEPING THE UNSIGNED CHAR FOR ITS
						RELIABILITY TO ACT AS A BYTE. AS I AM WRITING THIS, I AM STILL UNEASY ABOUT
						THE REMOVAL AND SOMETHING TELLS ME THAT I AM FORGETTING SOMETHING.
			OPERATORS:
				- MORPH: 
					- HISTORY:
						- AT FIRST I THOUGHT I USE MORPH TO DEFINE OPERATORS. THEN I REALIZED THAT
								IT WOULD BE TOO RESTRICTIVE. FOR EXAMPLE, IF A MORPH GROUP ALLOWS
								STRING TO CONVERT TO INTEGER, THEN I MAY ONLY PICK ONE STRING FOR
								EACH INTEGER. HENCE THE FOLLOWING WOULD WORK FOR EXAMPLE,
										2 + "2"
								BUT THE FOLLOWING WOULD NOT
										2 + " 2"
								SO I DECIDED TO DEFINE THE OPERATORS WITH THE FOLLOWING RULES:
								IF 
										VAR{T1} @ VAR{T2}
								IS VALID FOR CERTAIN VALUES OF TYPES T1 AND T2 AND IF THE T2 VALUE
								CAN BE MORPHED TO THEN THE FOLLOWING MUST HOLD
										VAR{T1} @ VAR{T2} == VAR{T1} @ VAR{T2 MORPHED TO T1}
								AND THAT WAS IT. WITH THIS I WOULD ALLOW MYSELF TO DEFINE OPERATORS
								SUCH AS BOTH OF 
										2 + "2"
										2 + " 2"
								ARE VALID. I JUST HAD TO MAKE THAT FOR THE FIRST CASE, WHERE MORPHING
								OF "2" TO INT IS VALID, THE RESULT SHOULD BE THE SAME AFTER SAID MORPH.
								HOWEVER, THE PROBLEM WITH THIS IS THAT I EFFICETIVELY REMOVED THE USEFUL
								LOGIAL CRITERIA THAT WOULD BAN MORPHING BOOLEAN TO INTEGER. REMEMBER WITH
								BOOLEANS, I WOULD LIKE true TO CONVERT TO "TRUE" AS A STRING, AND I WOULD
								LIKE true TO CONVERT TO 1 AS AN INT, AND WOULD LIKE 1 TO CONVERT TO "1"
								AS A STRING, WHICH IS NOT THE SAME AS "TRUE". BY ANNULING THE STRICT
								CRITERIA OF MORPHING, THERE WAS NO OTHER CRITERIA THAT WOULD BAN SUCH
								CONVERSION DEFINITIONS, AND HENCE SUCH OPERATION. IN OTHER WORDS, I COULD
								NOT DO
										2 + "TRUE"
								YET I COULD DO
										2 + true
								
						- LATER I DECIDED TO GO WITH LOOSE MORPHING. LOOSE MORPHING ALLOWED ME NOW TO 
								DEFINE THINGS LIKE
										2 + " 2"
								AND WITH FOLLOWING THE STRICT RULES OF MORPHING. HOWEVER NOW I HAD A
								PROBLEM. WITH LOOSE MORPHING IF
										a @ b == a @ c
								THE FOLLOWING IS NOT GUARANTEED TO HOLD TRUE
											b == c
								UNLESS == IS DEFINED TO BE EQUALITY UNDER THE LOOSE MORPH. FURTHER MORE,
								I COULD NOT RELY ON SIMPLY HAVING A FUNCTION FOR EQUALITY UNDER THE
								LOOSE MORPH, AND KEEPING == TO BE EQUALITY UNDER THR MORPH, MEANING
								EQUALITY THAT CONSIDER THE PRIMARY VALUE SETS ONLY OF THE LOOSE MORPH
								GROUPS, BECAUSE DEVELOPERS ARE LIKELY TO USE == TO DO THEIR COMPARISON
								AND IT WOULD CAUSE WEIRD BUGS I THOUGHT IF
										a + b == a + c
								AND SOMEWHERE ELSE IN THE CODE
											b != c
								THEREFORE == WOULD HAVE TO BE EQUALITY UNDER THE LOOSE MORPH, AND THAT OPERATION
								IS VERY EXPENSIVE.
						- LATER I DECIDED TO GO BACK TO USING MORPH, INSTEAD OF LOSE MORPH, AND FORGETTING ABOUT
								THE CONVENIENCE THAT LOOSE MORPH GIVES. AND WITH THIS,
										2 + "2"
								WOULD BE VALID, BUT
										2 + " 2"
								WOULD NOT BE. HOWEVER NOW I HAD ANOTHER PROBLEM, DOUBLES. A DOUBLE CAN BE
								REPRESENTED IN INIFINITE WAYS AS A STRING. FOR EXAMPLE, 1e100 COULD BE
								"1e100" OR "10e99" OR "100e98", ECCETRA, AND THIS IS ALL WITHOUT TRAILING
								AND LEADING SPACES. NOW I FIND MYSELF BACK WHERE I STARTED, AND UNABLE TO
								MAKE A DECISION. IT WOULD BE ABSURD TO ALLOW
										2 + "1e100"
								BUT NOT ALLOW
										2 + "1e99"

								IT APPEARS THAT I SHALL BE DEFINING THE OPERATORS BASED ON LOOSE MORPHING,
								AND WILL DEFINE THE == OPERATOR SUCH AS IF THE TWO OPERANDS ARE OF THE SAME
								TYPE, NORMAL (NON MORPH) COMPARISON IS USED, OTHER WISE 
								COMPARISON UNDER LOOSE MORPHING IS USED. THE RULES OF MORPHING MAKE
								IT SUCH AS ONLY THE RIGHT HAND SIDE NEED TO BE MORPHED TO THE TYPE OF THE LEFT
								HAND SIDE AND THEN COMPARED, AND THIS WOULD BE SUFFICIENT. THERE WOULD
								BE NO NEED TO SEARCH FOR EVERY POSSIBILITY OF MORPHING BOTH OPERANDS.
								FURTHERMORE, I SHALL BE ADDING EQUALITY FUNCTIONS FOR LOOSE MORPHING
								AND MORPHING, AND MORPH FUNCTIONS AND LOOSE MORPH FUNCTIONS, AND ONE
								FUNCTION TO CHECK IF BOTH SIDES ARE OF THE SAME TYPE.
					- MORPHING IS DEFINED PER MY STANDARD. MORPH IS DEFINED HERE OVER THE TYPE
							HELD BY THE VAR. THE VAR IS BASED ON LOOSE MORPH, AND IMPLEMENTS MORPH AS WELL.
					- LOOSE MORPH GROUPS:
						- G1:
							- PRIMARY TYPE: BOOLEAN
							- TYPES: {BOOLEAN, STRING}
							- PRIMARY VALUE SETS: {{true}}
							- CONVERSION FUNCTIONS:
								- C: BOOLEAN -> STRING
										true	=>		"TRUE"
									THE SUBSET OF STRINGS THAT CONVERT BACK TO true CONSISTS
									OF ALL STRINGS THAT IF TRIMMED AND THEN UPPER CASED, COMPARE EQUAL
									TO "TRUE"
										false	=>		"FALSE"
									THE SUBSET OF STRINGS THAT CONVERT BACK TO false CONSISTS
									OF ALL STRINGS THAT IF TRIMMED AND THEN UPPER CASED, COMPARE EQUAL
									TO OF "FALSE"
						- G2:
							- PRIMARY TYPE: INTEGER
							- TYPES: {INTEGER, DOUBLE, STRING, BYTE}
							- PRIMARY VALUE SETS:	ALL INTEGERS THAT CAN BE REPRESENTED AS BYTE
							- CONVERSION FUNCTIONS:
								- C: INTEGER -> DOUBLE
										CONVERTS AN INTEGER TO THE EQUIVILANT WHOLE NUMBER DOUBLE
										ONLY ONE DOUBLE CONVERTS BACK TO EACH INTEGER
								- C: INTEGER -> STRING
										CONVERTS THE INTEGER TO THE EQUIVILANT TRIMMED INTEGER
										TEXT.
										THE SUBSET OF STRINGS THAT CONVERT BACK TO INTEGER CONSISTS
										OF ALL STRINGS THAT WHEN TRIMMED BEGIN WITH '-' FORLLOWED BY
										ONE DIGIT OR MORE, OR BEGIN WITH '+' FOLLOWED BY ONE DIGIT
										OR MORE, OR BEGIN WITH ONE OR MORE DIGITS. THEY ARE ALSO THE
										STRINGS THAT MORPH BACK TO DOUBLE AND REPRESENT WHOLE NUMBERS.
								- C: INTEGER -> BYTE
										CONVERTS THE INTEGER TO THE EQUIVILANT BYTE.
								- C: DOUBLE -> STRING
										STRINGS THAT CONVERT BACK TO DOUBLE CONSISTS OF STRINGS THAT
										IF AFTER TRIMMING AND LOWER CASING, BEGIN, WITH EMPHASIS ON 
										BEGIN, WITH A TEXTUAL REPRESENTATION OF A NUMBER THAT HAS AT 
										LEAST ONE DIGIT AFTER THE DECIMAL, AND POSSIBLY HAS AN 
										EXPONENT PART.
								- C: DOUBLE -> BYTE
										DOUBLES THAT CONVERT BACK TO BYTE CONSISTS OF WHOLE NUMBER
										DOUBLES.
								- C: STRING -> BYTE
										THE SUBSET OF STRINGS THAT CONVERT BACK TO BYTE CONSISTS
										OF STRINGS THAT CONVERT BACK TO INTEGER
						- G3:
							- PRIMARY TYPE: INTEGER
							- TYPES: {INTEGER, DOUBLE, STRING}
							- PRIMARY VALUE SETS:	ALL INTEGERS THAT ARE NOT PART OF G2 AND
									CAN BE REPRESENTED AS DOUBLE UNDER THE WHOLE NUMBER PRECISION
									GUARANTEE. EACH INTEGER IS ITS OWN SET
							- CONVERSION FUNCTIONS:
								- C: INTEGER -> DOUBLE
										CONVERTS AN INTEGER TO THE EQUIVILANT WHOLE NUMBER DOUBLE
										ONLY ONE DOUBLE CONVERTS BACK TO EACH INTEGER
								- C: INTEGER -> STRING
										CONVERTS THE INTEGER TO THE EQUIVILANT TRIMMED INTEGER
										TEXT.
										THE SUBSET OF STRINGS THAT CONVERT BACK TO INTEGER CONSISTS
										OF ALL STRINGS THAT WHEN TRIMMED BEGIN WITH '-' FORLLOWED BY
										ONE DIGIT OR MORE, OR BEGIN WITH '+' FOLLOWED BY ONE DIGIT
										OR MORE, OR BEGIN WITH ONE OR MORE DIGITS. THEY ARE ALSO THE
										STRINGS THAT MORPH BACK TO DOUBLE AND REPRESENT WHOLE NUMBERS.
								- C: DOUBLE -> STRING
										STRINGS THAT CONVERT BACK TO DOUBLE CONSISTS OF STRINGS THAT
										IF AFTER TRIMMING AND LOWER CASING, BEGIN, WITH EMPHASIS ON 
										BEGIN, WITH A TEXTUAL REPRESENTATION OF A NUMBER THAT HAS AT 
										LEAST ONE DIGIT AFTER THE DECIMAL, AND POSSIBLY HAS AN 
										EXPONENT PART.
						- G4:
							- PRIMARY TYPE: INTEGER
							- TYPES: {INTEGER, STRING}
							- PRIMARY VALUE SETS: ALL INTEGERS NOT PART OF G2 AND G3, WHERE EACH
									INTEGER IS ITS OWN SET.
							- CONVERSION FUNCTIONS:
								- C: INTEGER -> STRING
										CONVERTS THE INTEGER TO THE EQUIVILANT TRIMMED INTEGER
										TEXT.
										THE SUBSET OF STRINGS THAT CONVERT BACK TO INTEGER CONSISTS
										OF ALL STRINGS THAT WHEN TRIMMED BEGIN WITH '-' FORLLOWED BY
										ONE DIGIT OR MORE, OR BEGIN WITH '+' FOLLOWED BY ONE DIGIT
										OR MORE, OR BEGIN WITH ONE OR MORE DIGITS.
						- G6:
							- PRIMARY TYPE: DOUBLE
							- TYPES: {DOUBLE, STRING}
							- PRIMARY VALUE SETS: ALL DOUBLES THAT ARE NOT PART OF G2 AND G3
							- CONVERSION FUNCTIONS:
								- C: DOUBLE -> STRING
										CONVERTS DOUBLE TO THE SMALLEST STRING THAT CAN CONTAIN THE
										DOUBLE WITH THE GUARANTEE THAT THE STRING CONTAINS AT LEAST
										ONE DIGIT AFTER THE DECIMAL.
										NaN => 	"NAN"
										inf =>	"INF"
								
										STRINGS THAT CONVERT BACK TO DOUBLE CONSISTS OF STRINGS THAT
										IF AFTER TRIMMING AND LOWER CASING, BEGIN, WITH EMPHASIS ON 
										BEGIN, WITH A TEXTUAL REPRESENTATION OF A NUMBER THAT HAS AT 
										LEAST ONE DIGIT AFTER THE DECIMAL, AND POSSIBLY HAS AN 
										EXPONENT PART, AND STRINGS THAT WHEN UPPER CASED EQUAL TO
										"NAN" OR "INF".
					- MORPH GROUPS:
						- G1:
							- PRIMARY TYPE: BOOLEAN
							- TYPES: {BOOLEAN, STRING}
							- PRIMARY VALUE SET: {true, false}
							- CONVERSION FUNCTIONS:
								- C: BOOLEAN -> STRING
										true	=>		"TRUE"
										false	=>		"FALSE"
						- G2:
							- PRIMARY TYPE: INTEGER
							- TYPES: {INTEGER, DOUBLE, STRING}
							- PRIMARY VALUE SETS:	ALL INTEGERS THAT CAN BE REPRESENTED AS 
									DOUBLE UNDER THE WHOLE NUMBER PRECISION GUARANTEE.
							- CONVERSION FUNCTIONS:
								- C: INTEGER -> DOUBLE
										CONVERTS AN INTEGER TO THE EQUIVILANT WHOLE NUMBER DOUBLE.
										ONLY ONE DOUBLE, THE ONE WITH THE SMALLEST EXPONENT, CONVERTS 
										BACK TO EACH INTEGER (NOTE THAT CURRENTLY THIS IS NOT 
										ENFORCED BY THE Var TYPE. THIS MEANS THAT AT THE BINARY 
										LEVEL, DIFFERENT DOUBLES CAN CONVERT BACK TO THE SAME 
										INTEGER.)
								- C: INTEGER -> STRING
										CONVERTS THE INTEGER TO THE EQUIVILANT TRIMMED INTEGER
										TEXT.
										THE SUBSET OF STRINGS THAT CONVERT BACK TO INTEGER CONSISTS
										OF ALL STRINGS THAT WHEN TRIMMED BEING WITH '-' OR A DIGIT
										AND THE REST OF CHARACTERS ARE ONLY DIGITS, AND THE STRING
										CONTAINS AT LEAST ONE DIGIT.
						- G3:
							- PRIMARY TYPE: INTEGER
							- TYPES: {INTEGER, STRING}
							- PRIMARY VALUE SETS: ALL INTEGERS NOT PART OF G2.
							- CONVERSION FUNCTIONS:
								- C: INTEGER -> STRING
										CONVERTS THE INTEGER TO THE EQUIVILANT TRIMMED INTEGER
										TEXT.
										THE SUBSET OF STRINGS THAT CONVERT BACK TO INTEGERS CONSISTS
										OF ALL STRINGS THAT WHEN TRIMMED CONTAIN ONLY DIGITS.
						- G4:
							- PRIMARY TYPE: DOUBLE
							- TYPES: {DOUBLE, STRING}
							- PRIMARY VALUE SETS: ALL DOUBLES THAT ARE NOT PART OF G2
							- CONVERSION FUNCTIONS:
								- C: DOUBLE -> STRING
										CONVERTS DOUBLE TO THE SMALLEST STRING THAT CAN CONTAIN THE
										DOUBLE WITH THE GUARANTEE THAT THE STRING CONTAINS AT LEAST
										ONE DIGIT AFTER THE DECIMAL.
										NaN => 	"NAN"
										inf =>	"INF"
								
										STRINGS THAT CONVERT BACK TO DOUBLE CONSISTS OF STRINGS THAT
										IF AFTER TRIMMING AND LOWER CASING, CONTAIN A TEXTUAL
										REPRESENTATION OF A NUMBER THAT HAS AT LEAST ONE DIGIT AFTER
										THE DECIMAL, OR CONTAINS "nan" OR "inf".
				- BINARY OPERATORS 
					- BINARY OPERATORS MUST FOLLOW LEFT HAND SIDE SEMANTICS, AND ARE SUBJECT TO MORPH RULES
							PER MY STANDARD. THE BINARY OPERATOR == IS AN EXCEPTION, AND IS AN IREGULAR OPERATOR.
							(SEE MY STANDARD)
					- FOR EACH OPERATOR @, AND GIVEN VAR WITH INTERNAL TYPE T LABELLED AS VAR{T},
							AND GIVEN THE GENERAL FORM 	
									VAR{T1} @ VAR{T2}
							NOTE THE FOLLOWING:
						- IF 
										VAR{T1} @ VAR{T2}
								IS VALID FOR CERTAIN VALUES OF TYPES T1 AND T2 THEN THE VALUE OF T2 CAN BE MORPHED 
								TO T1, AND THE RESULTS OF
										VAR{T1} @ VAR{T2}
								MUST EQUAL THE RESULT OF
										VAR{T1} @ VAR{T2 LOOSE MORPHED TO T1}
								AND MUST EQUAL THE RESULT OF
										VAR{T1} @ VAR{T2} 'CAST' TO T1  (SEE BELOW; CAREFUL WITH WORD CAST HERE.)
						- TRANSFORMATIONS:
							- THE FOLOWING TRANSFORMATIONS FOLLOW FROM THE SEMI TRIVIAL CASE OF LEFT HAND SIDE
									SEMANTICS:
								- A @ B				=>		A @ A
										FOR ALL OPERATORS EXCEPT FOR || AND &&
								- A || B			=>		bool || bool
								- A && B			=>		bool && bool
							- THE FOLLOWING PRIMARY FORMS AND TRANSFORMATIONS ARE AN EXCEPTION TO THE 
									SEMI TRIVIAL CASE OF LEFT HAND SIDE SEMANTICS, EITHER BECAUSE
									THE PRIMARY FORMS ARE THEMSELVES AN EXCEPTION, OR BECAUSE THEIR
									TRANSFORMATIONS ARE AN EXCEPTION.
								- LIST:
									1- PRIMARY FORM		
											double + double = double
										TRANSFORMATIONS
											(int, double) + (double, double string) =>	double + double
									2- PRIMARY FORM
											double - double = double
										TRANSFORMATIONS
											(int, double) - (double, double string) =>	double - double
									3- PRIMARY FORM
											double * double = double
										TRANSFORMATIONS
											(int, double) * (double, double string) =>	double * double
									4- PRIMARY FORM
											double / double = double
										TRANSFORMATIONS
											(int, double) / B						  =>	double / double
									5- PRIMARY FORM
											double % double = double
										TRANSFORMATIONS
											(int, double) % (double, double string)   =>	double % double
									6- PRIMARY FORM
											int & int = int
										TRANSFORMATIONS
											(int, double) & B						  =>	int & int
										NOTE THAT THE RANGE FOR INT IS BETWEEN 0 AND MAX OF INT32
									7- PRIMARY FORM
											int | int = int
										TRANSFORMATIONS
											(int, double) | B						  =>	int | int
										NOTE THAT THE RANGE FOR INT IS BETWEEN 0 AND MAX OF INT32
									8- PRIMARY FORM
											int % int = int
										TRANSFORMATIONS
											(int, double) % B						  =>	int % int
										NOTE THAT THE RANGE FOR INT IS BETWEEN 0 AND MAX OF INT32
									9- PRIMARY FORM
											int >> int = int
										TRANSFORMATIONS
											(int, double) >> B						  =>	int >> int
										NOTE THAT THE RANGE FOR INT IS BETWEEN 0 AND MAX OF INT32
									10- PRIMARY FORM
											int << int = int
										TRANSFORMATIONS
											(int, double) << B						  =>	int << int
										NOTE THAT THE RANGE FOR INT IS BETWEEN 0 AND MAX OF INT32
								- SOME REASONS:
									ONE PROBLEM ARISES FROM THE OPERATORS,
											+=, -=, *=, /=
									TAKING += AS AN EXAMPLE, A CHOICE HAS TO BE MADE IN THE CASE OF
									int WITH double. ONE COULD TAKE THE OPERATOR TO FOLLOW THE STEPS
											double = int + double		TRANSFORM TO
											double = double + double
									OR TO TAKE THE STEPS
											double = int + double		=>
											double = 0.0 + int + double
									NOTE HOW IN BOTH CASES THE int NEEDS TO MORPH TO double. IN THE FIRST CASE BECAUSE
									OF TRANSFORMATION, AND IN THE SECOND CASE BECAUSE OF THE 0.0, WHICH IS A double,
									THAT GETS INTRODUCED. NOTE THAT IN THS SECOND CASE WE ARE ASSUMING THE PRIMARY FORM
									OF LEFT HAND SIDE SEMANTICS TRIVIAL CASE,
											T = T @ T
									HENCE THE 0.0 + int, GIVES US A double.
									CAN WE NOT ASSUME JUST
											double = int += double
									REMEMBERING THAT += IS A BINARY OPERATOR. MEANING THE ABOVE IS A PRIMARY FORM.
									YES, WE CAN, BUT THE DECISION WAS TO STICK TO MORPHING AS MUCH AS POSSIBLE.
							- THE FOLLOWING PRIMARY FORMS AND TRANSFORMS FOR THE GIVEN OPERATORS DO NOT
									FOLLOW LEFT HAND SEMANTICS AT ALL. IN OTHER WORDS, THE FOLLOWING ARE NOT
									EXCEPTIONS, AND ARE INSTEAD THE FULL COMPLETE RULES FOR THE GIVEN OPERATORS.
								- OPERATORS '<' AND '>'
									- PRIMARY FORM:
											bool = int @ int
										TRANSFORMATIONS:
											int @ (int, intger string, byte)		=>  int @ int
									- PRIMARY FORM:
											bool = double @ double
										TRANSFORMATIONS:
											double @ B								=>	double @ double
											int @ (double, double string)			=>	double @ double
									- PRIMARY FORM:
											bool = string @ string
									- PRIMARY FORM:
											bool = byte @ byte
										TRANSFORMATIONS:
											byte @ B								=>	byte @ byte
							- THE OPERATOR '==' IS AN IREGULAR OPERATOR
								- PRIMARY FORM:
										bool = T @ T
								- BEING AN IREGULAR OPERATOR, THE OPERATOR DOES NOT FOLLOW MORPHING AT ALL.
								- IF THE OPERANDS PASSED TO THIS OPERATOR ARE OF DIFFERENT VAR TYPES, THE 
										OPERATOR EVALUATES TO FALSE.
								- Var::weakCompareTo(T)
									- THIS FUNCTIONS IMPLEMENTES THE EQUALITY USING MORPHING RULES
											BUT REMEMBER THAT THIS IS A FUNCTION, NOT AN OPERATOR.
									- IF T IS EQUAL TO THE INTERNAL TYPE OF VAR, NORMAL COMPARISON
											IS DONE FOR THAT TYPE (NOT COMPARISON UNDER THE LOOSE MORPH).
									- IF T IS NOT EQUAL TO THE INTERNAL TYPE BUT CAN BE LOOSE MORPHED
											TO IT, IT IS LOOSED MORPHED TO IT, AND THEN NORMAL COMPARISON
											IS DONE.
									- OTHERWISE, false IS RETURNED.
									- IN THE CODE, THE OPERATOR '==' IS DEFINED IN TERMS OF Var::weakCompareTo()
							- AN EXAMPLE OF HOW MORPHING APPLIES, TAKE
											A || B
									WHICH HAS TO TRANFORM TO
											bool || bool
									IN THIS CASE, IT MUST BE THAT BOTH A AND B CAN BE MORPHED TO bool
							- FOR MORE INFORMATION SEE MY STANDARD
				- UNARY OPERATORS:
					- OPERATOR '~': THIS OEPRATOR IS ONLY VALID FOR INTEGERS, OR WHOLE NUMBER DOUBLES
							BETWEEN 0 AND MAXIMUM OF INT32
					- OPERATORS '++', POSTFIX '++', '--', POSTFIX '--', '-': 
							THESE OPERATORS ARE ONLY VALID WHEN THE VAR TYPE IS "NUMBER".
				- OPERATOR []
					- THIS OPERATOR CAN NOT BE MODELED AS A BINARY OPERATOR. THIS IS BECAUSE
							IN C++ IT HAS TO RETURN A REFERENCE TO ALLOW CODE SUCH AS
									a[x] = y;
							WHILE A BINARY OPERATOR RETURNS SOMETHING NEW. AN IMPORTANT IMPLICATION OF THIS
							IS THAT FOR A BINARY OPERATOR, WHETHER THE OPERANDS ARE CONSTANT OR NOT IS
							IRELEVANT, WHILE FOR THE [] OPERATOR, IT MAKES A DIFFERENCE WHETHER THE LEFT
							OPERAND, MEANING 'a' IN THE ABOVE EXAMPLE, IS CONSTANT. THINK OF ERROR PROPOGATION.
					- WHEN THE INPUT IS AN ACTUAL INT, OR SOMETHING THE COMPILER CAN AUTOMATICALLY CAST TO INT,
							THE OPERATOR IS ONLY VALID IF THE VAR TYPE IS NUMBER.
					- WHEN THE INPUT IS AN ACTUAL STRING, OR SOMETHING THE COMPILER CAN AUTOMATICALLY CAST TO 
							STRING, THE OPERATOR IS ONLY VALID IF THE VAR TYPE IS HASH TABLE.
					- WHEN THE INPUT IS A VAR
						- IF INTERNAL TYPE IS AN ARRAY, AND THE INPUT VAR TYPE CAN BE LOOSE MORPHED TO INT,
								THE BEHAVIOR IS VALID.
						- IF INTERNAL TYPE IS A HASHTABLE, AND THE INPUT VAR TYPE CAN BE LOOSE MORPHED TO STRING,
								THE BEHAVIOR IS VALID.
				- OPERATOR OVERRIDES:
					- THIS CONCERNS THE EXPLICIT TYPES ON THE RIGHT HAND SIDE THAT ARE OTHER THAN VAR{X}.
					- THE CHOICE OF WHICH OVERRIDES FOR THE OPERATORS ARE DEFINED IS BASED ON THREE REQUIREMENTS
						- ALLOWING LITERALS BE USED TO REPRESENT THE INTERNAL TYPES OF THE INTEGER. THIS
								IS WHY OVERRIDES INCLUDE INT64 WHEN IT IS AVAILABLE BECAUSE IT IS LARGE
								ENOUGH TO HOLD ANY INTEGER LITERAL.
						- ALLOWING FARWARD UPGRADE OPTIONS. THIS MEANS THAT CODE THAT WAS WORKING
								ON SETTINGS FOR OLDER HARDWARE, SHOULD CONTINUE WORKING LATER WHEN
								SETTINGS SWITCH FOR NEWER HARDWARE. THIS IS WHY OVERRIDES INCLUDE INT32,
								WHICH EVEN THOUGH IT IS NOT NEEDED ON INT64 SYSTEMS, BECAUSE
								INT64 IS LARGE ENOUGH TO HOLD ALL THE LITERALS, ON ALL OLDER
								SYSTEM IT WOULD HAVE BEEN DEFINED, AND THEREFORE IT MUST CONTINUE BEING
								DEFINED.
						- ALLOWING THE USE OF COMMON STL TYPES TO REPRESENT THE INTERNAL TYPES
								WHEN LITERALS CAN NOT PROVIDE SUPPORT.
					- ALL INTEGER TYPES, SUCH AS INT64 AND INT32, ARE SEEN AS 'INT', WHICH IS WHATEVER
							THE COMPILATION OPTIONS FOR THE INTEGER IN THE VAR IS. THIS COULD BE
							INT32, INT64, AND INT52. THIS MEANS THAT WHETHER THE OPERATOR IS PASSED
							ON INT64 OR INT32, IT HAS TO MAKE SURE THAT IT CAN FIT IN THE INTERNAL
							INT TYPE BEFORE THE OPERATION IS EVEN ALLOWED. TO THE VAR, THESE EXTERNAL
							INT32 AND INT64, ARE JUST PLACEHOLDER FOR EXTERNAL CODE TO USE, AND AGAIN THEY
							ARE PRIMARILY FOR LITERALS. 
							THIS IS WHY OPERATORS ALSO HAVE AN OVERRIDE FOR UINT32. THIS IS TO ACCOMADATE
							THE CASE WHEN THE COMPILER DOES NOT PROVIDE INT64, AND THE INTERNAL INTEGER
							MODE OF THE VAR IS INT52.
					- BE CAREFULY WITH THE OVERRIDE FOR char. THE char IS JUST A STRING WITH ONE CHARACTER,
							TO THE VAR.
					- THE unsigned char OVERRIDES ARE FOR THE "BYTE" INTERNAL TYPE, NOT FOR INTEGERS.
					- std::deque IS USED FOR THE ARRAY INTERNAL TYPE. REMEMBER THIS IS HOW CODE OUTSIDE
							THE "VAR WORLD" COMMUNICATES TO THE "VAR WORLD". LIKE WITH THE INTEGERS CASE,
							THIS TYPE IS NOT NECESSARY THE SAME TYPE ACTUALLY USED WITHIN THE VAR TO REPRESNT
							ARRAYS.
					- std:unordered_map IS USED FOR THE HASH TABLE INTERNAL TYPE. REMEMBER THIS IS HOW CODE 
							OUTSIDE THE "VAR WORLD" COMMUNICATES TO THE "VAR WORLD". LIKE WITH THE INTEGERS CASE,
							THIS TYPE IS NOT NECESSARY THE SAME TYPE ACTUALLY USED WITHIN THE VAR TO REPRESNT
							HASH TABLES.
				- CASTING VAR TO OTHER TYPES, IF VALID AND THE OTHER TYPES ARE FORM THE INTERNAL TYPES,
						MUST ALSO BE THE RESULT OF MORPHING ITS INTERNAL TYPE TO THE OTHER TYPES. 
						APART FROM unsigned char, ALL INTEGER TYPES, REGARDLESS OF THEIR SIZE, ARE 
						SEEN TO BE DIFFERENT STORAGES OF THE SAME TYPE, THE INTEGER TYPE THAT THE 
						VAR HOLDS INTERNALLY, WHICH INCLUDES THE "EMULATED INT" WHICH CURRENTLY
						AMOUNTS TO INT52.
						CAREFUL WITH WORD 'CAST' HERE. IT DOES NOT MEAN WHAT IT MEANS IN MY STANDARD.
						CASTING	HERE SIMPLY MEANS THE CASTING THAT A COMPILER CAN DO AUTOMATICALLY
						FROM OVERLOADED CAST OPERATORS.
						
						NOTE FROM THE ABOVE LOOSE MORPHING GROUPS THAT STRINGS THAT ARE MADE OF DIGITS
						ONLY CAN NOT BE CAST TO INTEGERS UNLESS THE INTERNAL MODE OF THE VAR FOR INTEGERS
						CAN HOLD THE INTEGER REPRESENTED BY THE STRING, EVEN IF THE TARGET INTEGER
						TYPE WE ARE CASTING TO IS LARGE ENOUGH TO HOLD THE VALUE. FOR EXAMPLE IF THE
						INTEGER MODE IS INT32, THEN A VAR HOLDING THE STRING "8589934592" CAN NOT
						BE CAST TO INT64 BECAUSE INT32 ITSELF CAN NOT HOLD THE NUMBER 8589934592. ON 
						THE OTHER HAND IF THE STRING IS "8589934592.0" THEN THE CAST TO INT64 WOULD 
						WORK. SEE LOOSE MORPH GROUPS, G2, G3, G4, G5. IT IS GOOD TO REMEMBER THAT WE 
						WOULD BE NOT BE MORPHING THE VAR TO INT32, BUT TO "NUMBER" INSTEAD. IF THE 
						INTEGER MODE IS INT32, AND WE MORPH THE VAR HOLDING "8589934592.0" TO NUMBER, 
						THE INTERNAL REPRESENTATION ENDS UP BECOMING A DOUBLE, BUT IF WE MORPH 
						"8589934592" THE MORPH FAILS COMPLETELY AND THE INTERNAL REPRESENTATION DOES 
						NOT SWITCH TO DOUBLE. THE CAST BEING BASED ON THE MORPH, WE WOULD LIKE
						IT ALSO TO FAIL FOR "8589934592".
						
			ERRORS:
				- THREE MECHANISM EXIST FOR ERRORS. 
					1- ONE THAT 'SWALLOS' THEM WHICH ROUGHLY AMOUNTS TO EITHER 
						TYPE 2 ERROR HANDLING IN MY STANDARD OR TYPE 1. 
					2- ONE THAT THROWSE EXCEPTIONS, WHICH AMOUNT TO TYPE 4 IN MY STANDARD. 
					3- ANOTHER THAT MAKES USE OF THE Var ITSELF TURNING ITS INTERNAL TYPE TO "Error" AND 
						DEFINING ALL OPERATIONS SUCH AS THEY PROPOGATE THE ERROR. FOR EXAMPLE, IF gVar IS
						CURRENTL AN ERROR THEN IN
										Var gVar3 = gVar + gVar2 + 32;
						gVar3 AND ALL TEMPORARIES CREATED TO EVALUATE THE EXPRESSION TURN INTO AN ERROR.
						
						NOTE THAT STRICTLY, PROPOGATION HAPPENS ON ASSIGNMENT ONLY. THAT MEANS AN ERROR
						IS CREATED ON A NEW INSTANCE OF VAR, AND PROPOGATED TO AN EXISTING INSTANCE.
						BECAUSE OF THIS OPERATORS OF THE FORM @= AFFECT THE INSTANCE ITSELF BECAUSE
										A @= B
						AMOUNTS TO
										A = A @ B
						ANOTHER IMPLICATION OF THIS IS THAT ONLY IN OPERATORS CAN THE TYPE CHANGE TO
						AN ERROR. THIS CAN NEVER HAPPEN INSIDE FUNCTIONS. NOTE THAT FUNCTIONS AND 
						OPERATORS ARE AS DEFINED IN MY STANDARD.
						
						PROPOGATION DOES NOT ENGAGE FOR CONTAINERS, MEANING THE ARRAY AND HASHTABLE.
						THIS IS BECAUSE OF THE [] OPERATOR. CONSIDER THE FOLLOWING
										gVar['key'] = gVar2;
						ORIGINALLY THE AIM WAS THAT IF gVar2 IS AN ERROR, THE WHOLE CONTAINER, gVar, 
						BECOMES AN ERROR. HOWEVER THIS IS NOT POSSIBLE BECAUSE THE OPERATOR [] SIMPLY
						RETURNS A REFERENCE TO THE VAR THAT IS AT THAT KEY TO DO ITS WORK, AND THAT 
						VAR DOES NOT KNOW THAT IT IS INSIDE A CONTAINER.
						EVEN THE PROBLEM WITH [] DID NOT EXIST, THIS MECHANISM IS LIKELY ILL DEFINED,
						BUT REMAINS THE BEST MECHANISM SO FAR TO REPORT AN ERROR IN STEAD OF EXCEPTIONS.
				- ANOTHER MECHANISM EXISTED THAT SWALLOWS THE ERROR AND REPORTS IT USING AN ERROR CODE. THIS
						WAS BEFPRE THE PROPOGATION MECHANISM WAS INVENTED. THIS MECHANISM ROUGHLY MAPS, 
						IF NOT EXACTLY (CONSIDER THE CASE OF NANs) TO A HYBRID OF TYPE 3 
						AND TYPE 1 IN MY STANDARD. BUT STRICTLY SPEAKING IT IS ILL DEFINED. IN ANY CASE IT SOLVED
						THE ISSUE WITH ERROR REPORTING WHEN IT COMES TO OPERATORS. THE MECHANISM IS ESSENTIALY
						LIKE THE ONE IN C, AND REQUIRES A THREAD LOCAL VARIABLES MECHANISM. HOWEVER, THERE WERE
						ALREADY	KNOWN ISSUES:
							- BACKWARD COMPATIBILTY: AND I INVESTIGATED BOOST.
							- PERFORMANCE: THE ERROR VARIABLE WOULD NEED TO BE RESET EVENTUALLY.
									FURTHER MORE BECAUSE THE MECHANISM IS INHERNTLY ILL DEFINED PER MY STANDARD,
									OTHER AWKWARD SOLUTIONS NEEDED TO EXIST FOR TRACKING THE ERROR. CONSIDER
											(x + 5) * y
									AND IMAGINE BOTH THE PLUS AND MULTIPLY GAVE AN ERROR. THE USER WOULD NOT
									HAVE TIME TO CHECK THE ERROR CODE UNTILL THE ABOVE FULLY EXECUTED. IN OTHER
									WORDS MY OPERATORS WOULD HAVE TO BEHAVE IN A WAY THAT IF THE ERROR CODE
									IS SET THEY DO NOT SET ANOTHER. IT ALSO MEANS THAT THE USER MUST NOT FORGET
									TO UNSET THE ERROR CODE HIMSELF WHEN HE WANTS TO KNOW IF THERE IS AN ERROR.
									OUR CODE CAN NOT UNSET IT BECAUSE IT COULD UNSET AN ERROR CODE THAT THE USER
									HAD NOT A CHANCE TO CHECK YET LIKE POSSIBLE IN THE ABOVE EXAMPLE.
									
						LATER THIS MECHANISM WAS REJECTED. AND EVEN LATER, THE NEW ERROR PROPOGATION MECHANISM
						WAS INVENTED, WHICH ITSELF ALSO IS LIKELY ILL DEFINED.
				- ERROR RELATED TO WPH AND NUMBER OVERFLOW SIMPLY SET THE NUMBER TO NAN. THIS IS REGARDLESS
						OF WHAT ERROR MECHANISM IS IN USE.
				- WHEN THE ERROR MECHANISM IS THE ONE THAT SWALLOWS:
					- <DEPRECATED
							IF THE ERROR IS RELATED TO WPG, OR NUMBER OPERATIONS IN GENERAL, NUMBERS ARE SET TO NAN
						/>
					- ALL OTHER ERRORS MUST NOT SET NUMBERS TO NAN, SUCH AS PARSING A STRING TO INT, OR
							VIOLATIONS OF MORPH RULES.
					- CURRENTLY FOR THE OPERATORS +, -, *, /, IF THE OPERATOR REQUIRES TRANSFORMATION
							AND THE LEFT HAND SIDE CAN NOT BE TRANSFORMED FOR CERTAIN SUB SETS OF ITS
							VALUES, A SUBSET SMALLER THAN ITS ENTIRE SET, THE ERROR IS SEEN AS ILLEGAL
							OPERATIONS, NOT AS AN INVALID OPERAND. THIS IS TO KEEP THE 'OPERAND' REFERING
							TO THE RIGHT HAND SIDE.
				- OPERATOR []
					- THE BEHVAIOR OF THIS OPERATOR WHEN AN ERROR IS NOT STRAIGHT FARWARD.
					- IF THE INPUT IS AN ACTUAL INTEGER
						- IF THE INTERNAL TYPE IS ERROR, this IS RETURNED
						- IF THE INTERNAL TYPE IS NOT AN ERROR NOR ARRAY, ERROR HANDLING WORKS AS USUAL. BUT
								IF this IS CONSTANT, THEN IF THE ERROR MODE IS PROPOGATION, THE PROGRAM
								IS ABORTED.
						- IF THE INTERNAL TYPE IS AN ARRAY BUT THE INPUT IS OUT OF BOUND:
							- IF THE MODE IS SWALLOWING, THE LAST ELEMENT IS RETURNED, AND IF THE ARRAY
									IS EMPTY, AN ELEMENT IS ADDED OF VALUE Var::Nil AND IT IS RETURNED,
									BUT IF this IS CONSTANT, THE PROGRAM IS ABORTED.
							- IF THE MODE IS EXCEPTION, THIS WORKS AS USUAL.
							- IF THE MODE IS PROPOGATION, THIS WORKS AS USUAL, UNLESS this IS CONSTANT, IN
									WHICH CASE THE PROGRAM IS ABORTED.
					- IF THE INPUT IS AN ACTUAL STRING
						- IF THE INTERNAL TYPE IS ERROR, this IS RETURNED
						- IF THE INTERNAL TYPE IS NOT AN ERROR NOR A HASHTABLE, ERROR HANDLING WORKS AS USUAL. 
								BUT IF this IS CONSTANT, THEN IF THE ERROR MODE IS PROPOGATION, THE PROGRAM
								IS ABORTED.
						- IF THE KEY IS NOT FOUND
							- IF this IS NOT CONSTANT, A NEW ENTRY IS CREATED WITH THAT KEY AND RETURNED
							- IF this IS CONSTANT, THEN IF THE ERROR MODE IS SWALLOING OR PROPOGATION,
									THE PROGRAM IS ABORTED, OTHERWISE ERROR HANDLNG WORKS AS USUAL.
					- IF THE INPUT IS AN ACTUAL BOOLEAN
						- IF THE INTERNAL TYPE IS ERROR, this IS RETURNED
						- IF THE INTERNAL TYPE IS NOT AN ERROR BUT IT IS AN ARRAY OR A HASHTABLE,
								ERROR HANDLING WORKS AS USUAL. BUT IF this IS CONSTANT, THEN IF THE ERROR
								MODE IS PROPOGATION, THE PROGRAM IS ABORTED
						- IF THE INTERNAL TYPE IS NOT AN ERROR, NOR AN ARRAY, NOR A HASHTABLE, BUT THE
								INPUT IS false, MEANING OUT OF BOUND.
							- IF THE MODE IS SWALLOWING, this IS RETURNED.
							- IF THE MODE IS EXCEPTION, THIS WORKS AS USUAL.
							- IF THE MODE IS PROPOGATION, THIS WORKS AS USUAL, UNLESS this IS CONSTANT, IN
									WHICH CASE THE PROGRAM IS ABORTED.
					- IF THE INPUT IS A VAR
						- IF THE INTERNAL TYPE IS ERROR, this IS RETURNED
						- IF THE INTERNAL TYPE OF THE INPUT VAR IS ERROR, THEN IF this IS CONSTANT,
								THE PROGRAM IS ABORTED, OTHERWISE ERROR HANDLING WORKS AS USUAL.
						- IF THE INTERNAL TYPE IS AN ARRAY, AND THERE IS AN ERROR UNDER MORPHING RULES
							- IF THE ERROR MODE IS TO SWALLOW, THE EFFECT IS THE SAME AS PASSING -1 TO THE 
									OPERATOR []. -1 MEANS A VALUE OUT OF RANGE.
							- IF THE ERROR MODE IS TO PROPOGATE AND this IS CONSTANT, THE PROGRAM IS
									ABORTED, OTHERWISE ERROR HANDLING WORKS AS USUAL.
							- IF THE ERROR MODE IS EXCEPTION, THIS WORKS AS USUAL.
						- IF THE INTERNAL TYPES IS A HASHTABLE, AND THERE IS AN ERROR UNDER MORPHING RULES
							- IF THE ERROR MODE IS TO SWALLOW, THE INPUT VAR IS FORCED CONVERTED TO STRING.
							- IF THE ERROR MODE IS TO PROPOGATE AND this IS CONSTANT, THE PROGRAM IS
									ABORTED, OTHERWISE ERROR HANDLING WORKS AS USUAL.
							- IF THE ERROR MODE IS EXCEPTION, THIS WORKS AS USUAL.
						- IF THE INTERNAL TYPE IS ERROR, this IS RETURNED
						- IF THE INTERNAL TYPE IS NEITHER ERROR NOR ARRAY NOR HASHTABLE AND THESE IS AN ERROR
								UNDER MORPHING RULES
							- IF THE ERROR MODE IS TO SWALLOW, THE INPUT VAR IS FORCE CONVERTED TO BOOLEAN
							- IF THE ERROR MODE IS TO PROPOGATE, AND this IS CONSTANT, THE PROGRAM IS
									ABORTED, OTHERWISE ERROR HANDLING WORKS AS USUAL.
							- IF THE ERROR MODE IS EXCEPTION, THIS WORKS AS USUAL.
					- TO UNDERSTAND THE ABOVE, REMEMBER
						- CREATION OF ERROR HAPPENS ON A NEW INSTANCE OF VAR, BUT AN EXCEPTION IS MADE FOR
								THE [] OPERATOR. ROUGHLY,
										x[a]
								IS TREATED AS IF
										x []= a
								REMEMBER THAT THIS IS NOT EXACTLY TRUE BECAUSE
										x[a]
								CAN NOT BE THE SAME AS
										x [] a
								BECAUSE SUCH OPERATOR RETURNS A TEMPORARY, WHILE THE [] OPERATOR ALWAYS RETURNS
								A REFERENCE
						- CREATION OF ERROR CAN NOT TAKE PLACE ON this IF this IS CONSTANT.
						- IF THE ERROR MODE IS NOT PROPOGATION, THEN THE ERROR MODE IS NOT PROPOGATION. THIS
								MEANS THAT VAR WILL NOT USE THE ERROR TYPE TO REPORT ERRORS EVEN IF THE VAR TYPE
								ERROR IS ENABLED.
						- THE BEHAVIOR OF THE OPERATOR MUST BE THE SAME WHETHER THE INSTANCE IS CONSTANT
								OR NOT, WHEN THERE IS NO ERROR AND "NO ERROR" INCLUDES THE SWALLOWING ERROR
								MODE.
						- THE OPERATOR IS DESIGNED FOR USAGE WITH THE VAR GENERIC ITERATOR WHICH MUST
								WORK FOR ALL THE VAR TYPES. HENCE THE USE OF A BOOLEAN IDNEX. HISTORICALLY,
								THIS WAS NOT REQUIRED WHEN THE GENERIC ITERATOR RETURNED ::std::pair<Var, Var>
				- CURRENTLY, THE VAR TYPE ERROR IS ONLY ENABLED WHEN THE ERROR MODE IS PROPOGATION. HOWEVER
						THE CODE IS STILL WRITTEN IN A WAY TO ANTICIPATE ITS EXISTANCE EVEN IF THE MODE IS NOT
						PROPOGATION. THIS IS BECAUSE IN THE FUTURE, THE ERROR TYPE MIGHT BE MADE AVAILABLE
						TO USER CUSTOM ERRORS AND EVEN WHEN THE MODE IS NOT PROPOGATION.
				- NOTE THAT THE SETTING OF THE ERROR TYPE AND READING MAY NOT ITSELF FAIL. CURRENTLY, IF
						HEAP ALLOCATION FOR THE STRING TO HOLD THE MESSAGE FAILS, THE FAILURE IS NOT
						TREATED AS FAILURE, AND THIS IS VALID BECAUSE THE IDENTITY OF THE ERROR IS THE ERROR CODE,
						NOT THE MESSAGE.
			
			ITERATORS:
				- HISTORY
					- std::pair APPROACH
						- THE ITERATOR MUST WORK THE SAME REGARDLESS OF THE VAR TYPE. ORIGINALY	THE ITERATOR
								WAS RETURNING ROUGHLY ::std::pair<Var, Var>, WHERE THE FIRST
								IN THE PAIR IS THE KEY, AND THE SECOND IS THE VALUE. THIS COULD HAVE ALSO WORKED
								NICELY WITH C++17 IN THEORY, A FEATURE THAT ALLOWED DECLERATION OF A KEY AND
								VALUE USING "STRUCTURED BINDING DECLERATION". NOTE THAT THIS IS FORBIDDEN
								IN MY STANDARD IN GENERAL, BUT WOULD HAVE BEEN TREATED IN THIS CASE AS PART
								OF THE SYNTAX OF THE LOOP.
								THE VALUE WAS A COPY. THIS WAS BECAUSE A NEW VAR COULD BE CREATED JUST
								THEN CONTAINING Var::Undefined. THIS WAS BECAUSE THE DESIGN REQUIRED THAT
								THE ITERATOR NEVER FAILS. IN OTHER WORDS, IF THE VAR ITERATED OVER 
								SUDDENLY CHANGED TYPE, CLIENT CODE WOULD CONTINUE WORKING AS LONG AS IT IS
								RELYING ON THE ITERATOR ONLY. THIS MEANT CLIENT CODE COULD NOT
								WRITE, BUT ONLY READ, BECAUSE WRITING WOULD REQUIRE USING THE [] OPERATOR.
								AT THE TIME, I DID NOT KNOW HOW TO MAKE THE ITERATOR SAFE FOR WRITING. NOTE
								THAT FAIL SAFETY MEANT THAT THE CODE NEVER REPORTS AN ERROR.
								IT SIMPLY SWALLOWS THE ERROR REGARDLESS OF THE CHOSEN VAR ERROR MECHANISM.
								THE ITERATOR WORKED FOR ALL VAR TYPES INCLUDING NON CONTAINER TYPES.
						- THE GENERIC ITERATOR DID NOT SUPPORT ITERING OVER STRING CHARACTERS BECAUSE IT WAS 
								NOT POSSIBLE. FOR BOTH ARRAY AND HASHTABLE THE VALUE PART OF THE std::pair 
								IS INDEED A VAR, AND THE STRING IS NOT AN ARRAY OF VARS. IF TO SUPPORT STRINGS, 
								THE VALUE PART IS SET TO A VAR CONTAINING A STRING THAT REPRESENTS THE 
								CHARACTER, THIS WOULD BE AMBIGUOUS BECAUSE NOW IT LOOKS LIKE AN ARRAY OR 
								HASHTABLE OF VARS ALL HOLDING STRINGS.
								REMEMBER THAT THE GENERIC ITERATOR COULD STILL ITERATE OVER THE STRING AS A 
								SINGLE VALUE, LIKE IT COULD OVER OTHER NON CONTAINER VAR TYPES.
						- THE GENERIC ITERATOR WHEN DEREFERENCED RETURNS ROUGHLY ::std::pair<Var, Var> AS
								MENTIONED ABOVE. THE SECOND VAR IN THE PAIR IS THE VALUE, AND THIS VAR COULD NOT BE
								USED TO DIRECTLY MODIFY THE ACTUAL VALUE IN THE CONTAINER. THIS WAS BECAUSE THE
								VALUE MIGHT BE A NEWLY CREATED VALUE THAT IS NOT IN THE CONTAINER. THIS HAPPENS 
								WHEN THERE IS AN ERROR SUCH AS THE CONTAINER NO LONGER EXISTS. THE VALUE
								USED TO BE THE NULL TYPE, AND LATER IT WAS CHANGED TO THE UNDEFINED TYPE
								BECAUSE THE NULL TYPE IS WRONG IN THIS CASE. REMEMBER THAT PART OF THE DESIGN
								GOALS WAS TO MAKE THE ITERATOR COMPLETELY FAIL SAFE. SEE ABOVE.								
								THIS WAS NOT AN ISSUE BECAUE THIS MAPPED TO OTHER LANGUAGES. LIKE IN THE FOR EACH 
								LOOP IN PHP, WHEN THE VALUE IS PART OF THE LOOP, MODIFYING IT DOES NOT MODIFY THE 
								ACTUAL VALUE IN THE CONTAINER, AT LEAST NOT WITH EXPLICIT REQUEST LIKE THAT THAT 
								CAN BE DONE IN PHP. HOWEVER IT IS POSSIBLE THAT I AM WRONG BECAUSE SIMILAR MAPPING
								I THINK COULD BE ACHIEVED WITH auto AND auto& AND I MOST LIKELY WAS AWARE OF THIS.
						- AT SOME POINT THE GENERIC ITERATOR HAD AN ERASE MODE. THE ITERATOR PROVIDED A FUNCTION
								TO REMOVE THE ELEMENT THE ITERATOR IS ON. INTERNALLY THE ITERATOR SETS A FLAG,
								AND THE NEXT TIME IT IS INCREMENTED IT UNSETS THE FLAG INSTEAD OF INCREMENTING.
								THIS LEAD TO CONTRADICTION, BUT I FORGOT WHAT IT WAS. IN ANY CASE, THE SOLUTION
								ASSUMED THE C++11 "FOR LOOP". HOWEVER, IF THE MECHANISM WAS USED WITH A WHILE
								LOOP, IT CAN LEAD TO UNEXPECTED RESULTS. I THINK THIS WAS FROM WHY I REMOVED
								THE MECHANISM. OTHER REASONS MIGHT HAVE BEEN ITS CONSIDERABLE ASSUMPTION. FOR
								EXAMPLE, THE USER COULD ASSIGN THE ITERATOR, THEN CALL REMOVE ON THE NEW 
								ITERATOR, AND THE OLD ITERATOR WOULD REMAIN UNWARE. OR THE USER COULD REMOVE 
								THE PREVIOUS ELEMENT, INSTEAD OF THE ELEMENT POINTED TO BY THE ITERATOR, AND 
								SO FORTH.
						- EVENTUALLY, THE GENERIC ITERATOR WAS MEANT TO ALLOW THE FOLLOWING USAGES:
							- 	for(auto tKeyValuePair : vVar)
								{
									Var tKey = tKeyValuePair.first;
									Var tValue = tKeyValuePair.second;
									
									//REMOVAL OF ELEMENTS HERE IS NOT SUPPORTED
									//ADDITION OF ELEMENTS HERE IS NOT SUPPORTED
									//MODIFYING ELEMENTS, WHICH CAN ONLY DONE USING THE [] OPERATOR CAN BE 
									//		DONE, BUT DISCOURAGED BECAUSE IT LOWERS THE FAIL SAFETY OF THE
									//		ITERATOR.
									
									//IF INTERNAL TYPE IS NO LONGER A COLLECTION OR THE SAME COLLECTION
									//		INSTANCE, THE LOOP WILL HALT. HOWEVER, THIS IS NOT GUARANTEED
									//		AND PERTAINING CHECK MIGHT BE REMOVED IN THE FUTURE.
								}
							-	Var::iterator tI = vVar.begin();
								Var::iterator tEnd = vVar.end();
								
								while(tI != tEnd)
								{
									Var tKey = (*tI).first;
									Var tValue = (*tI).second;

									if(...)
									{
										//REMOVE ELEMENT
									}
									else
										{++tI;}

									//OR
									
									if(...)
									{
										//ADD ELEMENT
									}
									++tI;
									
									
									//IF INTERNAL TYPE IS NO LONGER A COLLECTION OR THE SAME COLLECTION
									//		INSTANCE, THE LOOP WILL HALT. HOWEVER, THIS IS NOT GUARANTEED
									//		AND PERTAINING CHECK MIGHT BE REMOVED IN THE FUTURE.
								}
						- REMOVAL AND ADDITION OF ELEMENTS WHILE ITERATING
								I WANTED THE GENERIC ITERATOR TO ALLOW REMOVAL OF ELEMENTS. IN THE OLD DESIGN,
								THIS WAS A METHOD ON THE ITERATOR (SEE ABOVE). LATER THE ATTEMPT WAS TO
								MAKE THE FOLLOWING WORK:
										while(tI != tEnd)
										{
											...

											if(...)
											{
												vVar.someMethodToRemoveElement(tI);
											}
											else
												{++tI;}
										}
								AND THIS WAS FOR BOTH THE OLD DESIGN, AND THE NEW. HOWEVER, GETTING THE ABOVE WORKING
								FOR ALL INTERNAL TYPES IS DIFFICULT, IF NOT IMPOSSIBLE. IF THE TYPE IS ARRAY, THEN
								NO INCREMENT IS NECESSARY, BUT IF HASHTABLE, THE INCREMENT NEEDS TO HAPPEN BEFORE
								REMOVAL, AND REMOVAL NEEDS TO HAPPEN ON THE ITERATOR VALUE BEFORE IT WAS INCREMENTED.
								ALSO WHAT IF ONE WANTS TO REMOVE MORE THAN ONE ELEMENT
								LATER THE AIM WAS FOR THE FOLLOWING TO WORK
										while(tI != tEnd)
										{
											...

											if(...)
											{
												tI = vVar.someMethodToRemoveElement(tI);
											}
											else
												{++tI;}
										}
								HOWEVER NOW THE ISSUE BECAME ON THAT OF Var::someMethodToRemoveElement(). SHOULD IT BE
								PASSED THE NUMBER OF ELEMENTS TO BE REMOVED, OR AN END ITERATOR? I THEN REALIZED THAT
								I WAS REIMPLEMENTING ITERATORS I HAD ELSEWHERE. GIVEN MY CONCLUSION WHEN WORKING ON
								MY C ARRAYS, THE CORRECT APPROACH IS TO USE NUMBER OF ELEMENTS BECAUSE OF THE UNRELIABILITY
								OF POINTERS AMONG POSSIBLY OTHER THINGS. HOWEVER, AN END ITERATOR IS USEFULY FOR
								COMPATIBILITY WITH STL, BUT THEN AGAIN, THIS IS WHAT THE VAR STL ITERATORS ARE FOR.							
								FURTHERMORE, Var::someMethodToRemoveElement() COULD NEVER BE USED INSIDE THE C++11 FOR 
								RANGE LOOP WHICH IS THE PRIMARY AIM OF THE GENERIC ITERATOR. FINALLY, 
								Var::someMethodToRemoveElement() NEEDS TO WORK SEAMLESSLY FOR ALL VAR TYPES INCLUDING NON
								COLLECTIONS, WHICH ALSO INCLUDES THE 'ERROR' TYPE. THIS IS ALL A HEADACHE I WANTED TO AVOID
								FOR THE TIME BEING, AND BECAUSE THIS CAN ONLY WORK IN THE WHILE LOOP, AND THERE ARE ALREADY
								OTHER ITERATORS ONE CAN USE IN THE WHILE LOOP WHILE REMOVING ELEMENTS, THIS SEEMED TO
								BE A WASTE OF TIME. HOWEVER, I STILL WISHED FOR THE GENERIC NATURE OF THE GENERIC ITERATOR
								IN THE WHILE LOOP WHILE REMOVING ELEMENTS. 
								
								LATER, THIS WAS RESOLVED FOR REMOVAL, BUT NOT FOR INSERTIONS. SEE THE DESIGN BELOW.
				- STL COMPTAIBLE ITERATORS:
					- TO MAKE AN ITERATOR COMPATIBLE WITH STL, ONE OF THE REQUIREMENTS IS THE FOLLOWING:
									ITERATOR + INTEGER == INTEGER + ITERATOR
							GIVEN MY STANDARD THE ABOVE IS IMPOSSIBLE FOR ME TO IMPLEMENT WITHOUT A SERIOUS
							VIOLATION. BECAUSE OF THIS, STL COMPATIBLE ITERATORS FOR THE VAR ARE
							ACTUAL POINTERS TO AVOID A CUSTOM IMPLEMENTATION, AND THEREFORE THEY ARE NOT 
							SAFE AT ALL.
		*/
		/* VAR
			- TERMINOLOGY RELATED CHAR *:
				- LENGTH: REFERES TO THE LENGTH OF THE ENTIRE CHARACTER ARRAY.
				- SIZE: REFERS TO THE LENGTH OF THE CHARACTER ARRAY UP TO, BUT
						EXCLUDING THE FIRST NULL CHARACTER.
				- STRING: REFERS TO A NULL CHARACTER TERMINATED CHARACTER ARRAY.
						THE NAME STRING CAN NOT BE USED ON AN OUTPUT PARAMETER,
						MEANING A BUFFER PASSED AS A PARAMETER, EVEN IF THE RETURN
						SHALL BE A NULL CHARACTER TERMINATED CHARACTER ARRAY.
						INSTEAD ONE MUST USE THE NAME CHARS.
				- CHARS: REFERS TO A CHARACTER ARRAY THAT MAY OR MAY NOT BE
						NULL CHARACTER TERMINATED.
			- CODE CORRECTNES PER MY STANDARD:
				- SOME RULES ARE VIOLATED FOR EFFICIENCY. REMEMBER THAT VIOLATIONS CAUSE 
						ILL DEFINITIONS, WHICH CAN CAUSE IN DETERMINISM
				- VIOLATED RULES:
					- VARIABLES ARE NOT ALWAYS INITIALIZED. THIS HAPPENS IN BOTH
							LOCAL VARIABLES AND CLASS VARIABLES.
					- A LOT OF CODE REPITITION TO AVOID UNNECESSARY CALLS, AND MANY RUNTIME
							CHECKS FOR THE VAR INTERNAL TYPE.
					- INITILIALIZATION WITHOUT '='. IN OTHER WORDS, DIRECT INITILIZATION SYNTAX.
			- CONST CORRECTNESS:
				- CONST CORRECTNESS IS NOT GUARANTEED AT THE BYTE LEVEL. THAT MEANS THAT THERE
						EXISTS OPERATIONS THAT MODIFY THE DATA INSIDE VAR, BUT ARE STILL
						CONSIDERED NON CHANGING.
			- TYPES:
				- STRING
					- USES CHAR *, OR STD::STRING BEHIND THE SCENES. STD::STRING IS ONLY
							USED FOR DEVELOPMENT
					- WHEN USING STD::STRING, IT IS ASSUMED SAFE TO WRITE DIRECTLY TO THE STRING'S
							INTERNAL BUFFER.
				- SIGNED CHAR, UNSIGNED CHAR (BYTES)
					- DUE TO NOT KNOWING WHETHER A VALID NUMBER STRING IS SIGNED OR UNSIGNED NUMBER,
							IT IS NOT POSSIBLE TO CHECK THE CORRECT RANGES, WHICH ARE NOT THE SAME
							FOR SIGNED AND UNSIGNED CHARS. THEREFORE, STRING OPERATIONS WITH CHARS
							ARE NOT ALLOWED.
					- OPERATIONS ON THESE ARE NOT THE SAME AS THOSE OF THE C++ STANDARD WHEN
							IT COMES TO WIDENING OF TYPES BEHAVIOR. FOR EXAMPLE, THE FOLLOWING
									char + int + char
							WILL NOT YIELD THE SAME RESULT AS
									Var{char} + Var{int} + Var{char}
							THIS IS BECAUSE IN THE FIRST CASE THE COMPILER WILL EVLUATE EVERYTHING
							AS AN INT, AND IF THE VALUE IS STORED IN THE INTEGER WE WOULD NOT HAVE
							LOST BITS. IN THE SECOND CASE, WE WOULD LOSE BITS, BECAUSE THE
							LEFT MOST IS A CHAR, AND SO THE WHOLE THING BECOMES A CHAR BEFORE THE
							FINAL CAST TO INT IF STORING IN AN INT. HOWEVER, THIS IS TO BE EXPECTED
							FROM MY LEFT HAND SIDE SEMANTICS.
				- NUMBER
					- USES DOUBLE AND INT64 BEHIND THE SCENES
					- DUE TO WPG (SEE BELOW), THE RANGE OF THE NUMBER DEPENDS ON THE OPERANDS TO THE NUMBER
					- DUE TO WPG (SEE BELOW), AN OVERFLOW WHILE ENFORCING WPG MUST EVLUATE TO A 'NAN', 
							WHETHER THE UNDERLYING TYPE HAPPENS TO BE DOUBLE, OR INT ALREADY.
						((****WARNING****
							CURRENTLY, OVERFLOWS ARE DETECTED OPERATIONS WHEN THE UNDERLYING TYPE IS AN
							INT AND WPG APPLIES, IE, THE OPERAND ON THE RIGHT IS AN INTEGER. 
							
							HOWEVER, THE CHECKS ARE UNDEFINED BEHAVIOR DUE TO THEM HAPPENING AFTER THE FACT.
							WHEN OVERFLOWS HAPPEN THE PROGRAM IS UNSTABLE ACCORDING TO C AND C++ STANDARDS, 
							AND A FORMAL PAPER ON THE SUBJECT. IT WOULD APPEAR THAT IT WOULD BE BEST TO
							ABANDON THE USE OF INT64 ALTOGETHER. IF NOT, REMEMBER THAT YOU NEED TO CHECK FOR
							OVERFLOWS BEFORE THEY HAPPEN.

							ALSO NOTE THAT CURRENT CHECKS FOR MULTIPLICATION AND DIVISION OVERFLOWS ONLY
							WORK WHEN THE UNDERLYING REPRESENTATION OF SIGNED NUMBERS IS 2'S COMPLEMENT
							(AS FAR AS I CURRENTLY KNOW). THIS MEANS THAT YOU SHALL ALSO HAVE TO CHECK THE
							UNDERLYING REPRESENTATION AT RUNTIME IN THE FUTURE. ALTHOUGH THEY WILL
							LIKELY WORK, CHECK FOR ADD AND SUBTRACT ALSO NEED TO CHECKED WHETHER THEY WORK
							FOR OTHER PRESENTATIONS. FURTHER MORE, THESE CAUSE TO AN OVERFLOW TO HAPPEN
							CURRENTLY, AND WOULD NEED TO BE REWRITTEN TO AVOID UNDEFINED BEHAVIOR.
						****WARNING****))
					- CLIENT CODE INDICATES INTENT FOR WPG BY USING INTEGER OR DOUBLES. THIS IS ALSO THE CASE
							FOR "STRING". A NUMER'S STRING REPRESENTATION WILL TELL WHERHER IT IS A DOUBLE OR
							INTEGER, AND EVEN IF THE STRING PARSE CORRECTLY, IF THE VALUE IS OUTSIDE THE RANGE
							OF THE CURRENT TYPE USED FOR THE WHOLE NUMBER (SEE BELOW), IT MUST BE CONSIDERED A
							PARSE ERROR.
					- WHOLE NUMBER MODES:
						- WHOLE NUMBERS CAN BE COMPILED IN THREE DIFFERENT MODES:
							- INT32: SIGNED INT32 IS USED FOR REPRESENTING THE WHOLE NUMBER.
							- INT64: SIGNED INT64 IS USED FOR REPRESENTING THE WHOLE NUMBER, AND FALLS BACK TO
									SIGNED INT32 IF THE COMPILER HAS NO SUPPORT.
							- EMULATED INT: A DOUBLE IS USED TO REPRESENT THE WHOLE NUMBER
						- AN UPGRADE PATH SHOULD EXIST FOR A PERSON USING INT32 MODE ON 32BIT SYSTEMS
								THEN SWTICHING TO A 64 BIT SYSTEM, AND A PERSON USING EMULATED INT MODE
								ON 32BIT SYSTEMS THEN SWTICHING TO A 64 BIT SYSTEM.
								THIS LEADS TO THE FOLLOWING RULES:
							- IF A MACHINE SUPPORTS INT64, ALL OPERATIONS, ASIDE FROM ASSIGNMENT
									AND THE CONSTRUCTORS MUST SUPPORT INT64. IN OTHER WORDS
									WE WANT ALL TYPES SUPPORTED BY THE MACHINE TO WORK WITH VAR.
							- IF THE MACHINE SUPPORTS INT64, ASSIGNMENT OF INT64 TO VAR,
									AND THE CONSTRUCTOR WITH INT64 IS SUPPORTED IF THE WHOLE NUMBER
									MODE IS EITHER INT64 OR EMULATED INT.
							- ASSIGNMENTS OF UINT32 TO VAR, AND THE CONSTRUCTOR THAT ACCEPTS
									UINT32 IS SUPPORTED IF THE WHOLE NUMBER MODE OF VAR IS EMULATED INT
									OR INT64.
				- BOOLEAN
				- HASHTABLE
				- POINTER
					- THIS DOES NOT MORPH TO ANY OTHER TYPE. BECAUSE OF THIS, THE CASTING SYNTAX MAY NOT
							WORK WITH THIS.
					- WHEN A POINTER, IT CAN NOT BE NULL. THIS IS BECAUSE THE Var ITSELF IS HANDLING THE SEMANTICS
							OF NULL AS DEFINED IN MY STANDARD. OTHERWISE THE VAR NULL WOULD BE NULL AS DEFINED
							IN MY STANDARD, AND THE POINTER WHEN SET TO NULL WOULD BE EMPTY AS DEFINED
							IN MY STANDARD, WHICH IS NOT SOMETHING I WISH TO DO. THIS IS THE REASON WHY
							MAKING THIS MORPH TO OTHER TYPES WAS DIFFICULT, IF NOT IMPOSSIBLE.
					- THIS IS NOT A MANAGED POINTER. IT IS THE USER'S RESPONSIBILITY TO EMPTY RESOURCES.
				- ERROR
					- THIS DOES NOT MORPH TO ANY OTHER TYPE. BECAUSE OF THIS, THE CASTING SYNTAX MAY NOT
							WORK WITH THIS.
					- THIS IS MEANT FOR THE CASE WHERE THE COMPILATION OPTIONS ARE SET TO USE ERROR PROPOGATING
							MODE. PROPOGATION IS THE REASON WHY THE CASTING SYNTAX IS NOT ALLOWED ON THIS TYPE,
							AND ALSO NO MORPHING ALLOWED. CONSIDER THE FOLLOWING CASE:
								Var gVar = Var(5) + Var("cat"); //gVar AT THIS POINTER CONTAINS AN ERROR
								Var gVar2 = gVar + 20; //gVar2 AT THIS POINTER ALSO CONTAIN THE SAME ERROR WHICH PROPOGATED
								
								return ((int)gVar2); //IF THIS WAS ALLOWED, THE ERROR WOULD BE LOST.
			- WHOLE PRECISION GUARANTEE (WPG):
				- DEFINITION: ((X + WHOLE_NUMBER) == (FLOOR(X) + WHOLE_NUMBER + RESIDUE)) IS ALWAYS TRUE,
						WHERE ABS(RESIDUE) < 1
				- THE GUARANTEE IS MAINTAINED STRICTLY FOR '+' AND '-' AND '*'.
				- WPG IS TRIGGERED WHEN THE LEFT HAND SIDE IS A NUMBER (INTEGER OR DOUBLE) AND THE RIGHT HAND 
						SIDE OF THE OPERATION IS AN INTEGER, OR AN INTEGER STRING, OR A BYTE.
				- MORPH GROUPS AND SEMI MORPH GROUPS ARE DESIGNED TO ENFORCE WPG, BUT THEY ARE NOT SUFFICIENT.
						FOR EXAMPLE, FOR 
								double + int
						THE GROUPS ENSURE THAT int CAN BE CONVERTED TO double WITHOUT LOSS OF INFORMATION, 
						BUT THEY DO NOT ENSURE THAT THE RESULT OF THE OPERATION IS WITHIN THE RANGE SAFE FOR WPG.
			- IF "ZERO INITIALIZED", ROUGHLY SPEAKING, Var MUST CORRECTLY REPRESENT "NULL TYPE",
					AND BEING NOT THREAD POSSIBLE.
			- INITIALIZATION FROM JSON LIKE REPRESENTATIONS:
				- THERE EXISTS TWO SYNTAX. ONE FOR PRE C++11, AND ONE FOR C++11 AND UP.
				- C++11 AND UP
					- KEY VALUE PAIRS ARE REPRESENTED USING: {"key", value}
					- EXAMPLE:
						-	Var x = 
							{
								5,
								2.2,
								false,
								{
									{"key1", true}
									{"key2", 
									{
										{subKey1, 4},
										{subKey1, 5},
									}}
								}
							}
				- PRE C++11
					- KEY VALUE PAIRS ARE REPRESENTED USING: var_varArgsKeyValue("key", value)
					- ARRAYS AND HASH TABLES ARE REPRESENTED USING: var_varArgs(...);
					- ARRAYS MUST END WITH Var::TYPE__UNDEFINED
					- HASHTABLED MUST END WITH var_varArgsKeyValue()
					- EXAMPLE:
						-	Var x = var_varArgs
							(
								Var(5),
								Var(2.2),
								Var(false),
								var_varArgs
								(
									var_varArgsKeyValue("key1", true)
									var_varArgsKeyValue("key2", var_varArgs
									(
										var_varArgsKeyValue(subKey1, 4),
										var_varArgsKeyValue(subKey1, 5)
										var_varArgsKeyValue()
									)),
									var_varArgsKeyValue()
								),
								Var(Var::TYPE__UNDEFINED)
							)
			- ITERATORS:
				- THERE EXISTS TWO TYPES OF ITERATORS, GENERIC, AND NON GENERIC. 
					- THE GENERIC ITERATOR
						- ALLOWS ITERATION OVER ALL INTERNAL TYPES
						- IS MEANT TO BE USED BY THE C++11 FOR RANGE LOOPS.
						- THERE CAN ONLY BE ONE GENERIC ITERATOR
						- COMPATIBILITY OF THE GENERIC ITERATOR WITH STD IS NOT SOUGHT AFTER.
						- THE * OPERATOR ON THE ITERATOR RETURNS A KEY OR INDEX THAT CAN BE USED
								BY THE [] OPERATOR.
						- THE GENERIC ITERATOR TRIES TO BE AS FORGIVING AS POSSIBLE, BUT IT
								SHOULD BE TREATED AS NON FORIGIVING. THIS MEANS ANY CHANGE
								TO Var CAN PUT THE ITERATOR IN UNDEFINED STATE.
								HOWEVER NOTE THAT THEN YOU WOULD STILL NEED TO ADDRESS THE CASE
								WHEN THE ITERATOR IS ITERATING OVER A VAR WHOSE INTERNAL TYPE
								TURNED TO "ERROR".
						- THE GENERIC ITERATOR DOES NOT SUPPORT ITERATING OVER STRING CHARACTERS.
								BESIDE THE REASONS MENTIONED IN THE ITERATOR HISTORY SECTION
								ABOUT THE OLD ::std::pair<Var, Var> BASED GENERIC ITERATOR, 
								THE [] OPERATOR WOULD HAVE TO SUPPORT STRINGS. THIS IS TO KEEP
								THE SYNTAX OF USAGE OF THIS ITERATOR THE SAME NO MATTER THE VAR TYPE.
						- THE GENERIC ITERATOR ALLOWS FOR THE FOLLOWING USAGES:
							- 	for(auto tKey : vVar)
								{
									Var tValue = vVar[tKey];
									
									//REMOVAL OF ELEMENTS HERE IS NOT SUPPORTED
									//ADDITION OF ELEMENTS HERE IS NOT SUPPORTED
									
									//IF INTERNAL TYPE IS NO LONGER A COLLECTION OR THE SAME COLLECTION
									//		INSTANCE, THE LOOP WILL HALT. HOWEVER, THIS IS NOT GUARANTEED
								}
							-	Var::iterator tI = vVar.begin();
								Var::iterator tEnd = vVar.end();
								
								while(tI != tEnd)
								{
									Var tKey = (*tI);
									Var tValue = vVar[tKey];

									if(...)
									{
										tI->removeElementsAndUpdateSelf(1);
										//or
										tI->removeElementAndUpdateSelf();
									}
									else
										{++tI;}
									
									//ADDITION OF ELEMENTS HERE IS NOT SUPPORTED BUT THERE
									//		IS THE FUNCTION advanceSelfBy() ON THE ITERATOR
									//		WHICH CAN HELP IN ADDITION, AND ALSO THE FUNCTION
									//		Var::insertElementAfterKey() WHEN THE SORTED HASH TABLE
									//		IS USED.

									
									//IF INTERNAL TYPE IS NO LONGER A COLLECTION OR THE SAME COLLECTION
									//		INSTANCE, THE LOOP WILL HALT. HOWEVER, THIS IS NOT GUARANTEED
								}
					- NON GENERIC ITERATORS
						- EACH ALLOWS ITERATION ONLY ON A SPECIFIC TYPE.
						- THERE ARE THREE DIFFERENT TYPES:
							- GENERIC ITERATOR ALTERNATIVE ITERATORS
								- THESE ARE MEANT TO ACT AS FORGIVINGLY, OR UNFORGIVINGLY,
										AS THE GENERIC ITERATOR OVER TYPES THAT I WAS UNABLE
										TO SUPPORT ON THE GENERIC ITERATOR. CURRENTLY
										I PROVIDE SUCH ITERATOR FOR THE STRING TYPE.
										THESE ITERATORS, LIKE THE GENERIC ITERATORS, ARE
										ITERATORS OVER KEYS OR INDICES, AND NOT ITERATORS OVER
										VALUES.
								- THESE ARE:
									- THE STRING GENERIC ITERATOR ALTERNATIVE ITERATOR WHICH ALLOWS THE 
											FOLLOWING USAGES:
										- 	Var::StringIterator tI = vVar.getStringStartIterator();
											Var::StringIterator tEnd = vVar.getStringEndIterator();
											
											while(tI != tEnd)
											{
												Var tValue = vVar.getCharAt(tI);

												vVar.setCharAt(tI, 'r');

												if(...)
												{
													tI->removeElementsAndUpdateSelf(1);
													//or
													tI->removeElementAndUpdateSelf();
												}
												else
													{++tI;}
												
												//ADDITION OF ELEMENTS HERE IS NOT SUPPORTED BUT THERE
												//		IS THE FUNCTION advanceSelfBy() ON THE ITERATOR
												//		WHICH CAN HELP IN ADDITION.


												//IF INTERNAL TYPE IS NO LONGER A COLLECTION OR THE SAME COLLECTION
												//		INSTANCE, THE LOOP WILL HALT. HOWEVER, THIS IS NOT GUARANTEED
											}	
							- STL COMPATIBLE ITERATORS: 
								- THESE ARE MEANT TO BE COMPATIBLE WITH STL. 
								- THESE ITERATORS DEREFERENCE AS VALUES. 
								- THESE ITERATORS ARE NOT SAFE, BUT SOME SAFETY IS ATTEMPTED
										USING FUNCTIONS THAT CHECK IF THE ITERATION IS FINISHED.
								- THESE ARE:
									- ArrayStlIterator
									- StringStlIterator
								- USAGES:
									- TO REMOVE ELEMENTS:
													tI = Var::unsafeRemoveElementsAtRange(tI, tI + 1)
											WHERE tI IS AN 	ArrayStlIterator OR StringStlIterator
											Var::unsafeRemoveElementsAtRange() IS MEANT TO BE USED FOR
											THE ERASE-REMOVE IDIOM
									- OTHER USAGES SHOULD BE THROUGH STL ONLY. NON STL USAGE IS POSSIBLE
											BY IMPLICATION, BUT IS NOT RECOMMENDED. FOR EXAMPLE, THE FUNCTIONS
											Var::hasStringStlIteratorEnded() AND Var::hasArrayStlIteratorEnded()
											EXIST FOR NON STL SAFE USAGE OF StringStlIterator AND 
											ArrayStlIterator, BUT THEY DO NOT GUARANTEE SAFETY.
							- INDIRECT ITERATORS:
								- THESE ITERATORS DO NOT HAVE EXPLICIT "START" AND "END" FUNCTIONS.
								- STRICTLY, THESE MIGHT NOT EVEN BE ITERATORS. THIS MEANS THAT THEY
										HAVE NO DEREFERENCING.
								- "NUMERIC INDEX": 
									- THIS IS SIMPLY size_t BASED INDEX USED TO ITERATE
											OVER THE ARRAY OR THE STRING. 
									- USAGE RELIES ON
										- Var::getSize()
										- Var::operator[]()
										- Var::getCharAt()
										- Var::setCharAt()
										- Var::removeCharsAt()
										- Var::removeCharAt() 
										- Var::removeElementsAt()
									- FUNCTIONS THAT ALLOWS REMOVING ELEMENTS RETURN THE NUMBER OF ELEMENTS
											REMOVED TO ALLOW PROPER UPDATING OF ITERATORS AND SIMILAR IF
											NEEDED.
								- "KEY INDEX":
									- USAGE RELIES ON 
													Var::getHashTableKeys()
											WHICH RETURNS A std::vector CONTAINING A COPY OF ALL THE KEYS.
											THIS ALLOWS REMOVAL AND INSERTION DURING ITERATION WITHOUT
											AFFECTING THE ITERATION.
									- INDENTED USAGE:
											::std::vector<::std::string> tKeys = vVar.getHashTableKeys();
											for(tKey : tKeys)
											{
												if(!vVar.hasKey(tKey))
													{continue;}

												Var tValue = vVar[tKey];

												vVar[tKey] = "new value";
												
												//REMOVAL CAN BE DONE USING Var::removeElementAt(tKey)
												
												//IN THE EVENT OF ERRORS, THE BEHAVIOR IS DELEGATED
												//		TO THE BEHAVIOR OF Var::operator[]()
											}
			- THREAD POSSIBILITY
				- WHEN THE VAR IS A CONTAINER OF OTHER VARS, SUCH AS AN ARRAY OR A HASH TABLE, THEN WHEN
					- THE VAR IS THREAD POSSIBLE, THE CONTAINER IS GUARANTEED TO ONLY HOLD THREAD POSSIBLE
							VARS.
					- THE VAR IS NOT THREAD POSSIBLE, THE CONTAINER MAY CONTAIN EITHER OF THEAD POSSIBLE VARS
							AND NOT THREAD POSSIBLE VARS. THIS CAN HAPPEN FROM ASSIGNING NON VARS TO VARS. THIS
							INCLUDES ASSIGNMENT OF std::deque AND std::unordered_map TO VAR.
			- VARJSON
				- THE PRIMARY AIM OF THIS IS TO ALLOW MORE JSON LIKE SYNTAX FOR OLDER COMPILERS. THIS ALSO
						ALLOWS INITIALIZATON WITH NUMBERS TOO LARGE FOR INT32 BUT STILL FIT IN THE VAR
						WHEN USING EMULATED INTEGER MODE, AND NO INT64 IS AVAILABLE.
				- THIS IS BASED ON JSON, AND MUST BE ABLE TO PARSE JSON. SUCCESSFULL PARSING, HOWEVER, 
						DOES NOT MEAN SUCCESSFUL CONVERSION TO VAR INSTANCES.
				- THIS ADDS ON TOP OF JSON THE FOLLOWING FEATURES:
					- COMMENTS;
						- COMMENTS ARE OF THE MULTI LINE COMMENTS FORM USED IN C++. HOWEVER, THESE
								COMMENTS MAY NOT BREAK UP A TOKEN. FOR EXAMPLE:
										false
								WOULC BE VALID, BUT
										fal/*... * /se
								WOULD FAIL PARSING.
					- IDENTIFIERS LIKE false AND true, ARE CASE INSENSITIVE.
					- SUPPORT FOR nan, inf, -inf, infinity, -infinity.
					- SUUPORT FOR BINARY FORMAT OF THE FORM bXXXXXXXX WHERE X IS 1 OR 0.
							THIS IS USED FOR THE BYTE TYPE.
					- STRINGS MAY USE " OR ' OR `. 
						- THIS IS BECAUSE VARJSON IS PRIMARILY INTENDED
								FOR LITERAL ASSIGNMENT TO VARS USING A STRING LITERAL, AND " IS WHAT
								C++ USES FOR STRINGS. HENCE, FOR CONVENIENCE, SUPPORT FOR ' AND ` IS
								ADDED.
						- WHEN STRINGS USE `, THEY ARE ABLE TO ACCEPT EXTRA SYNTAX:
							- \u:ZZZZZZZ
									THIS IS FOR UNICODE CODE POINTS USING BASE 10 NUMBERS. NOTICE THAT
									THERE ARE 7 DIGITS ONLY.
							- \u:xZZZZZ
									THIS IS FOR UNICODE CODE POINTS USING BASE 16 NUMBER. NOTICE THAT
									THERE ARE 5 DIGITS ONLY.
					- CURRENTLY AN EMPTY STRING THAT REPRESENTS JSON AMOUNTS TO 'UNDEFINED'. IN
							THE FUTURE THIS MIGHT BECOME AN ERROR LIKE IT IS IN JSON.
		*/
		/* TO BE DONE:
			- STRING, NOT STD STRING, DOES NOT CURRENTLY ACCOUNT FOR ERRORS IN CONSTRUCTING ITSELF. YOU
					MIGHT WANT TO HANDLE THIS IN THE FUTURE, BUT IT IS NOT HIGH PRIORITY.
		*/
		public: typedef enum Type
		{
			TYPE__NIL = 0,
			TYPE__UNDEFINED,
			TYPE__POINTER,
			TYPE__STRING,
			TYPE__HASH_TABLE,
			TYPE__ARRAY,
			TYPE__BYTE,
			//TYPE__SIGNED_CHAR,
			TYPE__NUMBER,
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			TYPE__ERROR,
#endif
			TYPE__BOOL
		} Type;
		/*
		IF THIS WAS C99, WE COULD JUST DO:
		typedef struct var__String
		{
			int gCount;
			size_t gLength;
			size_t gCapacity;
			char gBuffer[];
		} var__String;

		var__String * var__newString(size_t pLengthOfBuffer)
		{
			var__String * vString = (var__String)(malloc(sizeof(Var__String) + 
					pLengthOfBuffer * sizeof(char)));

			vString->gLength = 1;
			vString->gCapacity = pLengthOfBuffer;
			vString->gChars[0] = '/n';

			return vString;
		}
		void var__deleteString(var__String * pString)
			{free((char *)(pString));}


		IF THIS WAS C89, WE COULD JUST DO:
		typedef struct var__String
		{
			int gCount;
			size_t gLength;
			size_t gCapacity;
			char gBuffer[1]; //OR char gBuffer[0] MIGHT WORK
		} var__String;

		var__String * var__newString(size_t pLengthOfBuffer)
		{
			var__String * vString = (var__String)(malloc(sizeof(var__String) + 
					pLengthOfBuffer * sizeof(char)));
			//OR var__String * vString = (var__String)(malloc(sizeof(var__String) +
			//		(pLengthOfBuffer - 1) * sizeof(char)));

			vString->gLength = 1;
			vString->gCapacity = pLengthOfBuffer;
			vString->gChars[0] = '/n';

			return vString;
		}
		void var__deleteString(var__String * pString)
			{free((char *)(pString));}

		*/
		public: typedef Var_String String;
		public: typedef struct Nil{} Nil;
		public: typedef struct Undefined{} Undefined;
		public: typedef struct ARRAY_DEFINITION{} ARRAY_DEFINITION;
		public: typedef ::crx::ClassUnorderedMap<::std::string, Var>::t VarUnorderedMap;
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		public: typedef ::crx::ClassUnorderedMap<::std::string, Var>::t HashTable;
#else	
		//public: typedef CRX__VAR__KHash HashTable;
		public: typedef CRX__VAR__KHash HashTable;
#endif
		//typedef Var_HashTableIterator<false> HashTableIterator;
		//typedef Var_HashTableIterator<true> HashTableConstantIterator;
		public: typedef Var_VarIterator<false> iterator; //STICKING TO STD CONVENTION
		public: typedef Var_VarIterator<true> const_iterator; //STICKING TO STD CONVENTION
		public: typedef Var_StringIterator<false> StringIterator;
		public: typedef Var_StringIterator<true> StringConstantIterator;
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		public: typedef ::std::string::iterator StringStlIterator;
		public: typedef ::std::string::const_iterator StringConstantStlIterator;
#else
		public: typedef char * StringStlIterator;
		public: typedef char const * StringConstantStlIterator;
#endif
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		//public: typedef ::std::deque<Var>::iterator ArrayStlIterator;
		//public: typedef ::std::deque<Var>::const_iterator ArrayConstantStlIterator;
		private: typedef Var_DeuqueIterator ArrayStlIterator;
		private: typedef Var_DeuqueConstantIterator ArrayConstantStlIterator;
#else
		public: typedef Var * ArrayStlIterator;
		public: typedef Var const * ArrayConstantStlIterator;
		//private: typedef Var_VarRingIterator ArrayStlIterator;
		//private: typedef Var_VarRingConstantIterator ArrayConstantStlIterator;
#endif
		//public: typedef ::std::deque<Var> Array;
		private: typedef union Data // sizeof(Var::Data) WAS ORIGINALLY MEANT TO EQUAL 32BYTES
		{
			/*
			THE FOLLOWING IS FOR ALLOWING ZEROING
			FOR THE CALCULATION OF THE SIZE, IT IS ASSUMED THAT CRX__VAR__SIZE_OF_STRING_STRING_BUFFER
					IS NOT SMALLER THAN 13
			*/
			unsigned char _gFiller[/*32*/ 1 + 
					CRXM__IFELSE2(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING, 
							sizeof(::std::string) < CRXM__IFELSE2(
									CRX__VAR__ARRAY_IMPLEMENTATION__IS_VARRING_A_POINTER, 8, 24) ?
									7 + CRXM__IFELSE2(
									CRX__VAR__ARRAY_IMPLEMENTATION__IS_VARRING_A_POINTER, 8, 24) : 
									7 + sizeof(::std::string), 
							(3 + CRX__VAR__SIZE_OF_STRING_STRING_BUFFER) < (8 + CRXM__IFELSE2(
									CRX__VAR__ARRAY_IMPLEMENTATION__IS_VARRING_A_POINTER, 8, 
									24)) ? 31 : (2 + CRX__VAR__SIZE_OF_STRING_STRING_BUFFER))];
			struct
			{
				/*
				BIT 0: INDICATES IF THREAD POSSIBLE;
				BITS 1 -> 2: <<RESERVED>>
				BIT 3 -> 7: INDICATE TYPE
				*/
				unsigned char gInfo;
			} uInfo;
			//Var::DataType gDataType;
			/*struct string							//KEEPING LARGEST AT FIRST FOR 
													//PROPER ZERO INITIALIZATION USING
													//THE {} SYNTAX.
			{
				unsigned char _uInfo__filler;
				/*
				BITS 1 -> 2: INDICATES STRING OPERATION MODE
				BITS 
				* /
				unsigned char gMode;
				union
				{
					uint32_t uLength;					//USING THIS INSTEAD OF size_t TO SAVE
														//ON MEMORY, AND TO HAVE WELL DEFINED
														//BYTE LENGTH REQUIREMENTS ON ALL HARDWARE.
														//WARNING: THIS INCLUDES THE NULL CHARACTER
														//WARNING: IT IS ASSUMED THAT uint32_t <= size_t
					uint32_t uSegmentLength;
				} gLength;
				union
				{
					char uSmallString[CRX__VAR__SIZE_OF_STRING_STRING_BUFFER];
					struct
					{
						Var::String * gString;
						size_t gOffset;
					} uLargeString;
				} gBytes;
			} uString;*/
			union String							//KEEPING LARGEST AT FIRST FOR 
													//PROPER ZERO INITIALIZATION USING
													//THE {} SYNTAX.
			{	
				struct
				{
					unsigned char _gInfo__filler;
					/*
					BITS 1 -> 2: INDICATES STRING OPERATION MODE
					BITS 
					*/
					unsigned char gMode;
				} uStringInfo;	
				union Data
				{
					struct smallString
					{
						unsigned char _gInfo__filler;
						unsigned char _uMode_filler;
						unsigned char gLength;
						//unsigned char _pad_54378;
						char gBytes[CRX__VAR__SIZE_OF_STRING_STRING_BUFFER];
					} uSmallString;
					struct largeString
					{
						unsigned char _gInfo__filler;
						unsigned char _uMode_filler;
						char _pad_984356[6];
						size_t gSegmentLength;
						size_t gOffset;
						Var_String * gString;
					} uLargeString;
				} uData;
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
				struct
				{
					unsigned char _gInfo__filler;
					::std::string gString /*= ""*/;
				} uStd;

				//IMPLICIT DEFAULT CONSTRUCTORS ARE BEING REMOVED BECAUSE std::string HAS ALSO NON DEFAULT CONSTRUCTORS
				//		AND IT IS USED INSIDE A UNION.
				public: String() {memset(this, 0, sizeof(String));}
				public: ~String(){}
#endif
			} uString;
			/*unsigned long long int uUnSignedLongLongInt;
			unsigned char uUnsignedChar;
			signed char uSignedChar;
			unsigned short int uUnsignedShortInt;
			signed short int uSignedShortInt;
			unsigned int uUnsignedInt;
			signed int uSignedInt;
			unsigned long int uUnsignedLongInt;
			signed long int uSignedLongInt;
			//unsigned long long int uUnSignedLongLongInt;
			signed long long int uSignedLongLongInt;
			float uFloat;
			double uDouble;
			long double uLongDouble;
			bool uBool;*/
			struct 
			{
				unsigned char _uInfo__filler;
				//char uStringBuffer[CRX__VAR__SIZE_OF_TEMPORARY_STRING_BUFFER];
				union
				{
#if(!CRX__VAR__IS_EMULATED_INT_USED)
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					int64_t uSignedInt64;
	#else
					int32_t uSignedInt32;
					unsigned char uPdsafds[4];
	#endif
#else
					unsigned char uPdsafds[8];
#endif
					double uDouble;
					unsigned char uUnsignedChar;
					signed char uSignedChar;
					bool uBool;
				};
			} uIntegral;
			//Will be switching to khash if compatibility with old compilers is good. Otherwise
			//		to google's dense hash if comptability with old compilers is good. Otherwise,
			//		to will have to stick to this or use a hybrid binary tree along unordered map
			//		approach.
			struct
			{
				unsigned char _uInfo__filler;
				uint32_t gNumericIndex;
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
				::crx::ClassUnorderedMap<::std::string, Var>::t * gUnorderedMap;
#else
				CRX__VAR__KHash * gKHash;
#endif
			} uHashTable;
			struct
			{
				unsigned char _uInfo__filler;
				char _pad_027694[7];
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
				::std::deque<Var> * gDeque;
#else
	#if(CRX__VAR__CONFIG__ARRAY_IMPLEMENTATION == CRX__VAR__OPTION__ARRAY_IMPLEMENTATION__VARRING_POINTER)
				Crx_VarRing * gVarRing;
	#else
				Crx_VarRing gVarRing; /*WARNING THIS STILL REQUIRES INITIALIZATION*/
	#endif
#endif
			} uArray;
			struct
			{
				unsigned char _uInfo__filler;
				char _pad_027694[7];
				Var_Pointer * gPointer; //THIS SHOULD NEVER BE NULL WHEN INTERNAL TYPE IS POINTER.
			} uPointer;
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			struct
			{
				unsigned char _uInfo__filler;
				/*char _pad_0276952[3];
				uint32_t gCode;
				::std::string * gString;*/
				char _pad_0276952[1];
				uint16_t gLength;
				uint32_t gCode;
				char * gString;
			} uError;
#endif
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			//IMPLICIT DEFAULT CONSTRUCTORS ARE BEING REMOVED BECAUSE std::string HAS ALSO NON DEFAULT CONSTRUCTORS
			//		AND IT IS USED INSIDE A UNION.
			public: Data() {memset(this, 0, sizeof(Data));}
			public: Data(Data const &) {memset(this, 0, sizeof(Data));} //THIS IS TO ALLOW FOR THE {} SYNTAX
			public: ~Data(){}

			//THE FOLLOWING DOES NOT WORK. I TRIED ALL COMBINATIONS OF ENABLING ONE HERE, AND DISABLING THE EXPLICT
			//		ONE ABOVE. IN OTHER WORDS, YOU CAN RELIED ON THESE IN C++11
			//public: Data() = default;
			//public: Data(Data const &) = default;
#endif
		} Data;
		private: typedef struct VarJsonData
		{
			char const * gCurrentChar;
			size_t gRemainingSize;
			char const * gChars;
		} VarJsonData;
		protected: typedef class VarBoolean
		{
			public: bool gBool;
			public: VarBoolean(bool pBool): gBool(pBool)
				{}
		}VarBoolean;
		

#if(CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_H())
		//...THIS IS ONLY NEEDED IF "CRX__LIB__CONFIG__FAVOR_STATIC_INLINE" IS DEFINED. THIS ...
		//...		ESSENTIALLY FAVORS FEATURES OF C++17 WHEN USING C++17 OR HIGHER. ...
#else
		//...THIS IS ONLY NEEDED IF SUPPORT FOR PRE C++17 IS NEEDED, OR ...
		//...		"CRX__LIB__CONFIG__FAVOR_STATIC_INLINE" IS NOT DEFINED.  ...
		CRX__LIB__PUBLIC_STATIC_VARS_START(Var)
			CRX__LIB__PUBLIC_STATIC_VAR() Var const gVAR_NULL;
		CRX__LIB__PUBLIC_STATIC_VARS_END()

		CRX__LIB__PRIVATE_STATIC_VARS_START(Var)
			CRX__LIB__PRIVATE_STATIC_VAR() char const gINFINITY_SYMBOL[4];
			CRX__LIB__PRIVATE_STATIC_VAR() char const gNAN_SYMBOL[4];
			CRX__LIB__PRIVATE_STATIC_VAR() ::double_conversion::DoubleToStringConverter * gDoubleToStringConverter;
			CRX__LIB__PRIVATE_STATIC_VAR() ::double_conversion::StringToDoubleConverter * gStringToDoubleConverter;
			CRX__LIB__PRIVATE_STATIC_VAR() ::double_conversion::StringToDoubleConverter * gStringToDoubleConverter__loose;
			CRX__LIB__PRIVATE_STATIC_VAR() int gHexCharacterToValueArray[256];
			/*CRX__LIB__PRIVATE_STATIC_VAR() double gERROR_VALUE_FOR_DOUBLE;*/
		CRX__LIB__PRIVATE_STATIC_VARS_END()
#endif
		protected: Var::Data gData /*={} */;
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		//private: ::std::string gString /*= ""*/;
#endif

		#pragma region STATIC FUNCTIONS //{
		/*WARNING: THIS FUNCTION MUST NOT BE USED TO CHECK IF THE NUMBER STRING IS FOR A WHOLE NUMBER*/
		private: static bool isNumberStringAnIntegerIfValid(char const * pChars, size_t pLength);
		private: static int32_t convertToSignedInt32(char const * pString, bool * pIsError);
		private: static int32_t convertToSignedInt32(char const * pChars, size_t pLength, bool * pIsError);
		private: static int32_t looseConvertToSignedInt32(char const * pString, bool * pIsError);
		private: static int32_t looseConvertToSignedInt32(char const * pChars, size_t pLength, bool * pIsError);
#ifndef CRX__BOOST_NO_INT64_T		
		private: static int64_t convertToSignedInt64(char const * pString, bool * pIsError);
		private: static int64_t convertToSignedInt64(char const * pChars, size_t pLength, bool * pIsError);
		private: static int64_t looseConvertToSignedInt64(char const * pString, bool * pIsError);
		private: static int64_t looseConvertToSignedInt64(char const * pChars, size_t pLength, bool * pIsError);
#endif
		private: static bool stringifyInt32(int32_t pInt32, char * pChars, size_t pAvailableLength);
		private: static size_t stringifyInt32AndGetSize(int32_t pInt32, char * pChars, size_t pAvailableLength);
		private: static bool stringifyUnsignedInt32(uint32_t pUnsignedInt32, char * pChars, size_t pAvailableLength);
		private: static size_t stringifyUnsignedInt32AndGetSize(uint32_t pUnsignedInt32, char * pChars, 
				size_t pAvailableLength);
		private: static bool stringifyEmulatedInt(double pDouble, char * pChars, size_t pAvailableLength);
		private: static size_t stringifyEmulatedIntAndGetSize(double pDouble, char * pChars, size_t pAvailableLength);
#ifndef CRX__BOOST_NO_INT64_T
		private: static bool stringifyInt64(int64_t pInt64, char * pChars, size_t pAvailableLength);
		private: static size_t stringifyInt64AndGetSize(int64_t pInt64, char * pChars, size_t pAvailableLength);
#endif
		private: static bool convertStringToBool(char const * pString, bool * pIsError);
		private: static bool convertStringToBool(char const * pChars, size_t pLength, bool * pIsError);
		private: static bool looseConvertStringToBool(char const * pString, bool * pIsError);
		private: static bool looseConvertStringToBool(char const * pChars, size_t pLength, bool * pIsError);
		//private: static size_t convertStringToNumericIndex(char const * pChars, size_t pLength, bool * pIsError) const; //TO BE IMPLEMENTED ?
		private: static bool isNan(double pDouble);
		#pragma endregion STATIC FUNCTIONS //}

		#pragma region BASIC CONSTRUCTOR //{
		/*PRE C++11*/
		//Remember in Pre C++11 we can not call one constructor from 
		//		another constructor in the same class
		/*private: inline void crxConstruct(Var::DataType pDataType = Var::DataType::NIL, 
				Var::Data pIntegral = {}, CRX_PASSING unsigned char* pBytes = NULL,
				unsigned int gBytesLength = 0)
		{

			this->gDataType = pDataType;
			this->gData = pIntegral;	//{};	//EMPTY WOULD NOT WORK IN C (EXCEPT IN GCC MAYBE
												//	DUE TO AN EXTENSION THERE), BUT
												//	C NOT RELEVANT HERE.
												//	YOU COULD USE {0} BUT WOULD NOT WORK PRE C++11
			this->gBytes = pBytes;
			this->gBytesLength = gBytesLength;
		}
		private: inline void Var::crxConstruct(Var::DataType pDataType CRX_DEFAULT(CRX__VAR__TYPE_NULL), 
				bool pIsToSetData CRX_DEFAULT(true))
		{
			//this->gDataType = pDataType;
			
			if(pIsToSetData)
				{this->gData = {};}
		}
		*/

		/*POST C++11*/
		//Remember in C++11 and above we can call one constructor from 
		//		another constructor in the same class, and the following
		//		would have to be called by every constructor of this class
		/*private: inline Var(Var::DataType pDataType = Var::DataType::NIL, 
				Var::Data pIntegral = {}, unsigned char* pBytes = NULL) : 
				gDataType(pDataType), gData(pIntegral),
				gBytes(pBytes)
			{}*/
		
		/*The following created the 'Null'/'Nil' type, with the Var being not thread possible*/
		public: Var();

		public: Var(/*VC6 Var::*/Nil pNil, bool pIsToBeThreadPossible = false);
		public: Var(/*VC6 Var::*/Undefined pUndefined, bool pIsToBeThreadPossible = false);
		public: Var(bool pIsToBeThreadPossible, /*VC6 Var::*/Type pType);
		#pragma endregion BASIC CONSTRUCTOR //}

		#pragma region COPY CONSTRUCTOR //{
		public: Var(Var const & pVar);
		public: Var(Var const & pVar, bool pIsToBeThreadPossible);
#if(defined(_MSC_VER) && (_MSC_VER <= 1200))
#else
		public: template<typename T>
				Var(T * pT, bool pIsToBeThreadPossible = false) : gData(/*VC6 {}*/ Data())
		{
			if(pT != NULL)
			{
				if(pIsToBeThreadPossible)
				{
					this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
							CRX__VAR__TYPE_POINTER;
				}
				else
					{this->gData.uInfo.gInfo = CRX__VAR__TYPE_POINTER;}

				/*VC6 this->gData.uPointer.gPointer = new Var_Pointer(
						new typename UWrapper<Var_InfoIsPointerTypeRegistered<UIsConstant<T>::TYPE>::VALUE>::template UType<T>::Type(pT));*/
				this->gData.uPointer.gPointer = new Var_Pointer(
						new typename UWrapper<Var_InfoIsPointerTypeRegistered<boost::remove_cv<T>::type>::VALUE>::template UType<T>::Type(pT));
			}
			else
			{
				if(pIsToBeThreadPossible)
				{
					this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
							CRX__VAR__TYPE_NULL;
				}
				else
					{this->gData.uInfo.gInfo = CRX__VAR__TYPE_NULL;}
			}
		}
#endif
#if(defined(_MSC_VER) && (_MSC_VER <= 1200))
		/*
		(THE FOLLOWING WAS AN ATTEMPT TO KEEP THE POINTER CONSTRUCTOR WORKING ALONG WITH THE CONSTANT CHAR
		POINTER IN VC6)
		DOES NOT WORK WITH const MAKING IT NOT USEFUL. NOTE THAT VC6 DOES NOT SUPPORT PARTIAL ORDERING
		ON FUNCTION TEMPLATES AS IT FIGURES OUT WHICH FUNCTION TO CALL. MEANING IF f() IS A TEMPLATED FUNCTION,
		VC6 CAN NOT SEE THE DIFFERENCE, FOR EXAMPLE, BETWEEN
				template<> f(char const *)
		AND
				template<> f(char *)
		MAKING ANY ANY CALL WITH A char const * AMBIGUOUS DURING RESOLUTION BECAUSE BOTH FUNCTION ARE EQUALLY
		QUALIFIED.
		public: template<>
				Var(char const * pString, bool pIsToBeThreadPossible /*= false. shouls still work* /) : gData(/*VC6 {}* / Data())
			{this->doVar(pString, pIsToBeThreadPossible);}
		*/
#endif
		/*public: template<typename T>
				Var(Var_PointerPasser<T> pT, bool pIsToBeThreadPossible = false) : gData({})
		{
			if(pT.gT != NULL)
			{
				if(pIsToBeThreadPossible)
				{
					this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
							CRX__VAR__TYPE_POINTER;
				}
				else
					{this->gData.uInfo.gInfo = CRX__VAR__TYPE_POINTER;}

				this->gData.uPointer.gPointer = new Var_Pointer(
						new typename UWrapper<Var_InfoIsPointerTypeRegistered<UIsConstant<T>::TYPE>::VALUE>::template UType<T>::Type(pT.gT));
			}
			else
			{
				if(pIsToBeThreadPossible)
				{
					this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
							CRX__VAR__TYPE_NULL;
				}
				else
					{this->gData.uInfo.gInfo = CRX__VAR__TYPE_NULL;}
			}
		}*/
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || !CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		public: Var(::std::string const & pString, bool pIsToBeThreadPossible = false);
#endif
//#if(defined(_MSC_VER) && (_MSC_VER <= 1200))
		//DID NOT WORK. SEE THE SPECIALIZED TEMPLATED VAR CONSTRUCTOR FOR DETAIL.
		//private: void doVar(char const * pString, bool pIsToBeThreadPossible = false);
//#else
		public: Var(char const * pString, bool pIsToBeThreadPossible = false);
//#endif
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		public: Var(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap, 
				bool pIsToBeThreadPossible = false);
#endif
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		public: Var(::std::deque<Var> const & pDeque, bool pIsToBeThreadPossible = false);
#endif
		public: Var(unsigned char const & pUnsignedChar, bool pIsToBeThreadPossible = false);
#if((!CRX__VAR__IS_EMULATED_INT_USED && CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64) || CRX__VAR__IS_EMULATED_INT_USED)
		public: Var(uint32_t pUnsignedInt32, bool pIsToBeThreadPossible = false);
#else
		CRX_DISABLE_METHOD(Var(uint32_t pUnsignedInt32))
#endif
		public: Var(int32_t const & pSignedInt, bool pIsToBeThreadPossible = false);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var(uint64_t pUnsignedInt64))
	#if(CRX__VAR__IS_EMULATED_INT_USED || CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
		public: Var(int64_t pSignedInt64, bool pIsToBeThreadPossible = false);
	#else
		CRX_DISABLE_METHOD(Var(int64_t pSignedInt64))
	#endif
#endif
		public: Var(float const & pFloat, bool pIsToBeThreadPossible = false);
		public: Var(double const & pDouble, bool pIsToBeThreadPossible = false);
#if(CRX__VAR__IS_ERROR_TYPE_AVAILABLE_FOR_PUBLIC_USE)
		public: Var(uint32_t gCode, ::std::string const pMessage, bool pIsToBeThreadPossible = false);
		public: Var(uint32_t gCode, char const * pMessage, bool pIsToBeThreadPossible = false);
#endif
		// /* //UNSAFE PRE C++11, BUT SAFE AFTERWARDS
		public: Var(bool pBool, bool pIsToBeThreadPossible = false); // */
		//THE FOLLOWING WAS MEANT TO PROTECT FROM THINGS LIKE
		//				Var(vSomeUserClassWithImplicitConversionToBoolean)
		//		IN PRE C++11 BUT IT DID NOT WORK BECAUSE C++ WILL TRY STANDARD CONVERSIONS
		//		FIRST
		//public: Var(Var::VarBoolean pVarBoolean, bool pIsToBeThreadPossible = false);
		#pragma endregion COPY CONSTRUCTOR //}

		#pragma region LIST INITIALIZATION CONSTRUCTOR //{
#ifndef CRX__BOOST_NO_CXX11_HDR_INITIALIZER_LIST
		public: Var(::std::initializer_list<::std::pair<::std::string const, Var>> pInitializerList);
		public: Var(::std::initializer_list<::std::pair<::std::string const, Var>> pInitializerList, 
				bool pIsToBeThreadPossible);
		public: Var(Var::ARRAY_DEFINITION _s, ::std::initializer_list<Var> pInitializerList);
		public: Var(Var::ARRAY_DEFINITION _s, ::std::initializer_list<Var> pInitializerList,
				bool pIsToBeThreadPossible);
		
		/*public: Var(bool pIsToBeThreadPossible, const ::std::string pKey, Var pVar)
		{
			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_HASH_TABLE;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_HASH_TABLE;}

			this->gData.uHashTable.gUnorderedMap = new ::crx::ClassUnorderedMap<::std::string, Var>::t();//pInitializerList);

			if(!pVar.isHashTable)
			{
				(*(this->gData.uHashTable.gUnorderedMap))[pKey] = pVar;
			}
			else
			{
				::crx::ClassUnorderedMap<::std::string, Var>::t::iterator vIterator = 
						pVar.gData.uHashTable.gUnorderedMap->begin();

				while(vIterator != pVar.gData.uHashTable.gUnorderedMap->end())
				{
					(*(this->gData.uHashTable.gUnorderedMap))[(*vIterator).first] = (*vIterator).second;

					vIterator++;
				}
			}
		}*/
		/*public: Var(bool pIsToBeThreadPossible, 
				::std::initializer_list<::std::tuple<bool, const ::std::string, Var>> pInitializerList)
				//::std::initializer_list<::std::pair<const ::std::string, Var>> pInitializerList)
		{
			::std::initializer_list<::std::tuple<bool, const ::std::string, Var>>::iterator vIterator = 
					pInitializerList.begin();

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_HASH_TABLE;
			}
			else
			{
				this->gData.uInfo.gInfo = CRX__VAR__TYPE_HASH_TABLE;
			}

			this->gData.uHashTable.gUnorderedMap = new ::crx::ClassUnorderedMap<::std::string, Var>::t();//pInitializerList);

			while(vIterator != pInitializerList.end())
			{
				(*(this->gData.uHashTable.gUnorderedMap))[::std::get<1>(*vIterator)] = 
						Var(::std::get<2>(*vIterator), ::std::get<0>(*vIterator));

				vIterator++;
			}
		}*/
		/*public: Var(::std::initializer_list<::std::tuple<bool, const ::std::string, Var>> pInitializerList)
				//::std::initializer_list<::std::pair<const ::std::string, Var>> pInitializerList)
		{
			::std::initializer_list<::std::tuple<bool, const ::std::string, Var>>::iterator vIterator = 
					pInitializerList.begin();

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_HASH_TABLE;
			}
			else
			{
				this->gData.uInfo.gInfo = CRX__VAR__TYPE_HASH_TABLE;
			}

			this->gData.uHashTable.gUnorderedMap = new ::crx::ClassUnorderedMap<::std::string, Var>::t();//pInitializerList);

			while(vIterator != pInitializerList.end())
			{
				(*(this->gData.uHashTable.gUnorderedMap))[::std::get<1>(*vIterator)] = 
						Var(::std::get<2>(*vIterator), ::std::get<0>(*vIterator));

				vIterator++;
			}
		}*/
#endif
		#pragma endregion LIST INITIALIZATION CONSTRUCTOR //}

		#pragma region MOVE CONSTRUCTOR //{
#ifndef CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
		public: Var(Var && pVar) CRX__VAR__PRIVATE__NOEXCEPT;
		public: Var(Var && pVar, bool pIsToBeThreadPossible) CRX__VAR__PRIVATE__NOEXCEPT;
	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		public: Var(::std::string && pString, bool pIsToBeThreadPossible = false) CRX__VAR__PRIVATE__NOEXCEPT;
	#endif
	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		public: Var(::crx::ClassUnorderedMap<::std::string, Var>::t && pUnorderedMap, 
				bool pIsToBeThreadPossible = true) CRX__VAR__PRIVATE__NOEXCEPT;
	#endif
	#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		public: Var(::std::deque<Var> && pDeque, bool pIsToBeThreadPossible = true) CRX__VAR__PRIVATE__NOEXCEPT;
	#endif
#else
		/*
			REMEMBER THAT IN THIS CASE THE CONSTRUCTORS ARE MEANT TO BE BOTH MOVE CONSTRUCTORS AND 
				COPY CONSTRUCTORS, BUT ONLY IF 'MOVING' IS APPLICABLE, MEANING THE INTERNAL TYPE
				IMPLEMENTATION IS VALID FOR MOVING.
		*/
	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		public: Var(::std::string pString, bool pIsToBeThreadPossible = false) CRX__VAR__PRIVATE__NOEXCEPT;
	#endif
	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		public: Var(::crx::ClassUnorderedMap<::std::string, Var>::t pUnorderedMap, 
				bool pIsToBeThreadPossible = true) CRX__VAR__PRIVATE__NOEXCEPT;
	#endif
	#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		public: Var(::std::deque<Var> pDeque, bool pIsToBeThreadPossible = true) CRX__VAR__PRIVATE__NOEXCEPT;
	#endif
#endif
		#pragma endregion MOVE CONSTRUCTOR //}

		#pragma region UTILITIES //{
		/*
		THIS INSTANCE MUST ALREADY HAVE ITS RESOURCES PROPERLY CLEANED 
				BEFORE CALLING THIS FUNCTION
		*/
		private: void unsafeCopyInitializeFromVar(Var const & pVar);
#ifndef CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
		/*
		THIS INSTANCE MUST ALREADY HAVE ITS RESOURCES PROPERLY CLEANED 
				BEFORE CALLING THIS FUNCTION
		THE FUNCTION MIGHT CHANGE THE INTERNAL TYPE OF pVar BUT IT WILL TRY NOT TO.
		*/
		private: void unsafeMoveInitializeFromVar(Var & pVar) CRX__VAR__PRIVATE__NOEXCEPT;
#endif
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
		private: void copyInitializeErrorFrom(Var const & pVar) CRX__VAR__PRIVATE__NOEXCEPT;
		private: void pilferErrorFrom(Var & pVar) CRX__VAR__PRIVATE__NOEXCEPT;

		private: bool assignPropogateErrorFrom(Var const & pVar) CRX__VAR__PRIVATE__NOEXCEPT;
#endif
		/*
		WARNING: IF pType IS NOT EQUAL TO THE INTERNAL TYPE, THE FOLLOWING DELETES ANY EXTERNAL 
				RESOURCES, AND REINITIALIZES THE INSTANCE TO THE NEW TYPE. OTHERWISE, THE 
				INSTANCE IS KEPT AS IS. HOWEVER IF THE NEW TYPE IS "ERROR" REINIALIZATION DOES NOT
				TAKE PLACE.
				THEREFORE CODE MUST NOT ASSUME THAT WHATEVER THE INTERNAL TYPE IS, THE VALUE WILL
				BE EMPTY AFTER CALLING THE FUNCTION. FOR EXAMPLE, IF pType IS STRING, CODE
				CAN ONLY ASSUME THAT THE INSTANCE WILL BE A STRING, BUT CAN NOT ASSUME
				IT WILL BE EMPTY. HENCE WHY THE FUNCTION IS MEANT FOR EVENTUAL ASSIGNMENT.
				
				ALSO NOTE THAT IF pType IS CRX__VAR__TYPE_POINTER, AND IT IS NOT EQUAL TO THE
				INTERNAL TYPE, THE INTERNAL TYPE IS INSTEAD SET TO CRX__VAR__TYPE_NULL,
				AND NOT TO CRX__VAR__TYPE_POINTER.
		*/
		private: CRX__BOOST_FORCEINLINE void emptyDynamicResourcesIfNecessaryForAssigment(unsigned char pType);

		/*WARNING: pVar MUST NOT BE THE SAME INSTANCE AS this*/
		private: void unsafeMoveAssignFromVar(Var & pVar);
		#pragma endregion UTILITIES //}

		#pragma region STRING FUNCTIONS //{
		//WARNING: 
		//	- MAY ONLY BE CALLED IF INSTANCE CURRENTLY HOLDS A STRING
		private: CRX__BOOST_FORCEINLINE char * getCharPointerAndInfo(size_t * CRX_NOT_NULL pLength, 
				bool * CRX_NOT_NULL pIsNullTerminated);
		private: CRX__BOOST_FORCEINLINE char const * getCharPointerAndInfo(size_t * CRX_NOT_NULL pLength, 
				bool * CRX_NOT_NULL pIsNullTerminated) const;
		private: CRX__BOOST_FORCEINLINE size_t getStringSize() const;
		private: CRX__BOOST_FORCEINLINE size_t getStringCapacity();
		/*
		WARNING: pIndex MUST BE SMALLER THAN THE LENGTH OF THE INTERNAL STRING
		WARNING: pChars MUST BE NOT PART OF THE SAME INTERNAL STRING.

		THIS FUNCTION COPIES pChars INTO THE STRING STARTING AT pIndex. A NEW STRING IS MADE FROM 
		THE OLD STRING UP TO, AND EXCLUDING, pIndex, PLUS THE NEW STRING IN pChars. IF THE SIZE OF THE 
		NEW STRING IS SMALLER THAN THE ORIGINAL STRING, THEN THE EXTRA BYTES FROM THE ORIGINAL
		STRING ARE ALSO ADDED TO IT MAKING THE FINAL STRING. OTHERWISE, THE NEW STRING IS THE FINAL
		STRING.
		*/
		private: void addStringIntoIndex(size_t pIndex, 
				char const * CRX_NOT_NULL pChars, size_t pLength /*INCLUDES '/0'*/, 
				bool pIsNullTerminated);

		/*
		WARNING: pIndex MUST BE SMALLER THAN THE LENGTH OF THE INTERNAL STRING. THE FUNCTION
				AVOIDS USING THE LENGTH PROPERTIES FROM THE INTERNAL STRING ASSUMING IT UNDEFINED.
		WARNING: pChars MUST BE NOT PART OF THE SAME INTERNAL STRING.
				
		THIS FUNCTION COPIES pChars INTO THE STRING STARTING AT pIndex. THE FINAL STRING IS THE OLD
		STRING UP TO, AND EXCLUDING, pIndex, PLUS THE NEW STRING IN pChars.
		*/
		private: void addStringEndIntoIndex(size_t pIndex, 
				char const * CRX_NOT_NULL pChars, size_t pLength /*INCLUDES '/0'*/, 
				bool pIsNullTerminated);
		
		/*WARNING: pVar MUST BE CONTAINING A STRING*/
		private: void addStringFromVarIntoIndex(size_t pIndex, Var const & pVar);

		/*WARNING: pVar MUST BE CONTAINING A STRING*/
		private: void addStringEndFromVarIntoIndex(size_t pIndex, Var const & pVar);

		/*WARNING: INSTANCE MUST BE CONTAINING A STRING*/
		private: void ensureStringIsNotInLargeBufferSegmentMode();

		/*
		THIS FUNCTION ENSURES THAT THE STRING IS OWNED AND ALSO NOT IN LARGE 
		BUFFER SEGMENT MODE. IN OTHER WORDS, THE FUNCTION ENSURES THAT THE STRING
		CAN BE WRITTENT TO. REMEMBER, IF THE STRING IS IN LARGE BUFFER SEGMENT MODE
		THEN IT MUST BE THAT AT SOME POINT IT WAS SHARED (NOT OWNED), EVEN IF IT
		IS NOT SHARED CURRENTLY.

		WARNING: INSTANCE MUST BE CONTAINING A STRING
		*/
		private: void ensureStringIsOwned();

		/*WARNING: INSTANCE MUST BE CONTAINING A STRING*/
		private: size_t removeCharactersAt(size_t pIndex, size_t pWidth);
		#pragma endregion STRING FUNCTIONS //}

		#pragma region UTILITIES: STRING DEVELOPMENT //{
		private: CRX__BOOST_FORCEINLINE ::std::string development_getStdString() const;
		private: CRX__BOOST_FORCEINLINE bool development_isInternalNumberStringAnIntegerIfValid() const;
		private: CRX__BOOST_FORCEINLINE double development_looseConvertInternalStringToDouble() const;
		private: CRX__BOOST_FORCEINLINE double development_convertInternalStringToDouble(bool * pIsError) const;
		private: CRX__BOOST_FORCEINLINE bool development_convertInternalStringToBool(bool * pIsError) const;
		private: CRX__BOOST_FORCEINLINE bool development_looseConvertInternalStringToBool(bool * pIsError) const;
		private: CRX__BOOST_FORCEINLINE int development_doStrcmpOnInternalStringAnd(
				char const * pChars, size_t pSize) const;
#if(!CRX__VAR__IS_EMULATED_INT_USED)
		private: CRX__BOOST_FORCEINLINE CRX__VAR__UNIFIED_SIGNED_INT 
				development_convertInternalStringToUnifiedSignedInt(bool * pIsError) const;
		private: CRX__BOOST_FORCEINLINE CRX__VAR__UNIFIED_SIGNED_INT 
				development_looseConvertInternalStringToUnifiedSignedInt(bool * pIsError) const;
#endif
		private: char * development_unsafeGetStringAsChars(bool * CRX_NOT_NULL pIsPassing) const;

		#pragma endregion UTILITIES: STRING DEVELOPMENT //}

		#pragma region operator = //{
/*
			TO ALLOW ARBITRARY SELF ASSIGNMENT, SUCH AS
							Var gHashTable(false, Var::TYPE__HASH_TABLE);
									
									gHashTable['A'] = "dddd";
									gHashTable = gHashTable['A']; //SELF ASSIGNMENT
					THE OPERATOR ALWAYS EXPECTS A COPY PASSED TO IT WHICH THE VAR WILL THEN PROCEED TO PILFER.
#ifndef CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
		public: Var & operator=(Var && pVar);
		public: Var & operator=(Var const & pVar);
#else
		public: Var & operator=(Var pVar);
#endif
*/
		public: Var & operator=(Var pVar);
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
	#ifndef CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
		public: Var & operator=(::std::string && pString);
	#else
		public: Var & operator=(::std::string pString);
	#endif
#endif
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || !CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		public: Var & operator=(::std::string const & pString);
#endif
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
	#ifndef CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
		public: Var & operator=(::crx::ClassUnorderedMap<::std::string, Var>::t && pUnorderedMap);
	#else
		public: Var & operator=(::crx::ClassUnorderedMap<::std::string, Var>::t pUnorderedMap);
	#endif
#endif
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		public: Var & operator=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap);
#endif
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
	#ifndef CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
		public: Var & operator=(::std::deque<Var> && pDeque);
	#else
		public: Var & operator=(::std::deque<Var> pDeque);
	#endif
#endif
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		public: Var & operator=(::std::deque<Var> const & pDeque);
#endif
		public: Var & operator=(char const * pString);
		public: Var & operator=(unsigned char const & pUnsignedChar);
		public: Var & operator=(signed char const & pChar);
#if((!CRX__VAR__IS_EMULATED_INT_USED && CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64) || CRX__VAR__IS_EMULATED_INT_USED)
		public: Var & operator=(uint32_t const pUnsignedInt32);
#endif
		public: Var & operator=(int32_t const & pSignedInt);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var & operator=(uint64_t pUnsignedInt64))
	#if(CRX__VAR__IS_EMULATED_INT_USED || CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
		public: Var & operator=(int64_t pSignedInt64);
	#else
		CRX_DISABLE_METHOD(Var & operator=(int64_t pSignedInt64))
	#endif
#endif
		public: Var & operator=(float const & pFloat);
		public: Var & operator=(double const & pDouble);
		//DISABLE THE FOLLOWING IF YOU DISABLE THE BOOLEAN COPY CONSTRUCTOR BECAUSE OF PRE C++11 safety
		//		SEE Var(bool pBool, bool pIsToBeThreadPossible = false)
		public: Var & operator=(bool const & pBool);
		#pragma endregion operator = //}

		#pragma region POINTER //{
		public: template<typename T>
		void setP(T * pT)
		{
			//REMEMBER: THIS WILL SET INTERNAL TYPE TO CRX__VAR__TYPE_NULL, NOT CRX__VAR__TYPE_POINTER IF
			//		THE CURRENT TYPE IS NOT ALREADY CRX__VAR__TYPE_POINTER
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_POINTER);

			if(pT != NULL)
			{
				if(this->gData.uPointer.gPointer == NULL)
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_POINTER);
					/*VC6 this->gData.uPointer.gPointer = new Var_Pointer(
							new typename UWrapper<Var_InfoIsPointerTypeRegistered<UIsConstant<T>::TYPE>::VALUE>::template UType<T>::Type(pT));*/
					this->gData.uPointer.gPointer = new Var_Pointer(
							new UWrapper<Var_InfoIsPointerTypeRegistered<boost::remove_cv<T>::type>::VALUE>::template UType<T>::Type(pT));
				}
				else
				{
					/*VC6 this->gData.uPointer.gPointer->set(
							new typename UWrapper<Var_InfoIsPointerTypeRegistered<UIsConstant<T>::TYPE>::VALUE>::template UType<T>::Type(pT));*/
					this->gData.uPointer.gPointer->set(
							new UWrapper<Var_InfoIsPointerTypeRegistered<boost::remove_cv<T>::type>::VALUE>::template UType<T>::Type(pT));
				}
			}
		}
		
		/*
		THE PARAMETER IN THE FOLLOWING IS REQUIRED BECAUSE OF A BUG IN VC6 THAT DOES NOT STORE TEMPLATE
		ARGUMENT NAMES AS PART OF THE FUNCTION NAME FOR THE LINKER, BUT INSTEAD ONLY STORES ARGUMENT NAMES.
		HENCE ADDING THE TEMPLATE PARAMETER AS AN ARGUMENT.
		IF WISHING TO SUPPORT OLD COMPILERS, ONE WOULD USE:
				gVar->CRX__VAR__GETP(someType)
		OTHEERWISE ONE WOULD USE
				gVar->getP<someType>();
		*/
		public: template<typename T>
		T const * getP(T const * pT = NULL) const
		{
			if(CRX__VAR__GET_TYPE1(this) != CRX__VAR__TYPE_POINTER)
				{return NULL;}

			//VC6 typename UWrapper<Var_InfoIsPointerTypeRegistered<UIsConstant<T>::TYPE>::VALUE>::template UType<T>::Type u;
			typename UWrapper<Var_InfoIsPointerTypeRegistered<boost::remove_cv<T>::type>::VALUE>::template UType<T>::Type u;

			if(this->gData.uPointer.gPointer->isEqualTo(new Var_Pointer(&u)))
				{return static_cast<T *>(this->gData.uPointer.gPointer->getPointer());}
			else
				{return NULL;}
		};
		public: template<typename T>
		T * getP(T * pT = NULL)
		{
			if(CRX__VAR__GET_TYPE1(this) != CRX__VAR__TYPE_POINTER)
				{return NULL;}

			//VC6 typename UWrapper<Var_InfoIsPointerTypeRegistered<UIsConstant<T>::TYPE>::VALUE>::template UType<T>::Type u;
			typename UWrapper<Var_InfoIsPointerTypeRegistered<boost::remove_cv<T>::type>::VALUE>::template UType<T>::Type u;

			if(this->gData.uPointer.gPointer->isEqualTo(new Var_Pointer(&u)) &&
						!this->gData.uPointer.gPointer->isConstant())
				{return static_cast<T *>(this->gData.uPointer.gPointer->getPointer());}
			else
				{return NULL;}
		};
		
		
		/*
		THE FOLLOWING IS ANOTHER APPROACH FOR VS6 COMPATIBILITY, WHICH SHOULD WORK FOR OTHER COMPILERS
		TO USE:
				Var::GetP<someType>::call(gVar)
		*/
		public:template<typename T>
		class GetP
		{
			public: static T * call(Var & pThis)
				{return pThis.getP(static_cast<T *>(NULL));}
			public: static T * call(Var * pThis)
				{return pThis->getP(static_cast<T *>(NULL));}
		};
		public:template<typename T>
		class GetP<T const>
		{
			public: static T * call(Var const & pThis)
				{return pThis.getP(static_cast<T const *>(NULL));}
			public: static T * call(Var const * pThis)
				{return pThis->getP(static_cast<T const *>(NULL));}
		};
		#pragma endregion POINTER //}
		
		#pragma region LOOSE MORPH //{
			#pragma region Loose Morph //{
		public: bool looseMorphToString();
		public: bool looseMorphToByte();
		public: bool looseMorphToNumber();
		public: bool looseMorphToBool();
			#pragma endregion Loose Morph //}

			#pragma region "CAST" (LOOSE MORPH) //{
		/*
		<REMOVED
				CAST OPERATOR IMPLEMENT STRING CONVERSIONS ONLY. THESE INCLUDE
					- STRINGS THAT CAN BE SERIALIZED TO THE DESIRED TYPE.
					- TYPES THAT CAN BE WIDENED. MAINLY BYTE, I.E. SIGNED CHAR OR UNSIGNED CHAR, TO
							ANY OTHER SUPPORTED INTEGRAL TYPE.
					- 'NULL' TO FALSE.

				EXAMPLES OF CONVERSIONS THAT WOULD VIOLATE THE ABOVE, INCLUDE:
					- STRING TO BOOL BASED ON WHETHER THE STRING IS EMPTY.
					- NUMBER, OR BYTE TO BOOL BASED ON WHETHER THEY ARE ZERO.

				OPERATORS DEFINED LATER MUST WORK SUCH AS
					VAR_WITH_TYPE1_INNER @ TYPE2_VARIABLE = VAR_WITH_TYPE1_INNER @ 
							static_cast<TYPE1>(VAR_WITH_TYPE2_INNER);

					WHEN THE OPERATION IS ON A char, TYPE2 ABOVE WOULD BE std::string, NOT char

				CASTS ARE MEANT TO TAKE A VARIABLE 'OUTSIDE' A Var FIRST PROGRAM. WHERE OPERATORS ARE SPECIFIED
						SUCH AS THEY ARE USED 'INSIDE' A Var FIRST PROGRAM. HENCE WHY OPERATIONS ARE NOT DEFINED
						FOR Var WITH float FOR EXAMPLE, BUT CASTS ARE.
		>
		*/
		public: operator ::std::string() const;
		public: operator ::crx::ClassUnorderedMap<::std::string, Var>::t() const;
		public: operator ::std::deque<Var>() const;
		public: operator unsigned char() const;
		public: operator signed char() const;
		public: operator uint16_t() const;
		public: operator int16_t() const;
		public: operator uint32_t() const;
		public: operator int32_t() const;
		CRX_DISABLE_METHOD(operator uint64_t() const)
#ifndef CRX__BOOST_NO_INT64_T
		public: operator int64_t() const;
#endif
		public: operator float() const;
		public: operator double() const;
/*#if(BOOST_VERSION >= 105500)
		public: BOOST_EXPLICIT_OPERATOR_BOOL();
#endif*/
		public: CRX__BOOST_EXPLICIT_OPERATOR_BOOL();
		public: bool operator!() const;
			#pragma endregion "CAST" (LOOSE MORPH) //}

			#pragma region CastTo functions (LOOSE MORPH) //{

		public: ::std::string castToString(bool * pIsError) const;
		public: ::crx::ClassUnorderedMap<::std::string, Var>::t 
				castToUnorderedMap(bool * pIsError) const;
		public: ::std::deque<Var> castToDeque(bool * pIsError) const;
		public: unsigned char castToUnsignedChar(bool * pIsError) const;
		public: uint32_t castToUnsignedInt32(bool * pIsError) const;
		public: int32_t castToSignedInt32(bool * pIsError) const;
#ifndef CRX__BOOST_NO_INT64_T
		public: int64_t castToSignedInt64 (bool * pIsError) const;
#endif
		public: double castToDouble(bool * pIsError) const;
		public: bool castToBool(bool * pIsError) const;
			#pragma endregion CastTo functions (LOOSE MORPH) //}
		#pragma endregion LOOSE MORPH //}

		#pragma region FORCED CONVERSIONS //{
		public: ::std::string forceGetAsStdString();
		public: ::crx::ClassUnorderedMap<::std::string, Var>::t forceGetAsVarHashTable();
		public: ::std::deque<Var> forceGetAsArray();
		public: unsigned char forceGetAsUnsignedChar();
		public: signed char forceGetAsSignedChar();
		public: uint16_t forceGetAsUnsignedInt16();
		public: int16_t forceGetAsSignedInt16();
		public: uint32_t forceGetAsUnsignedInt32();
		public: int32_t forceGetAsSignedInt32();
#ifndef CRX__BOOST_NO_INT64_T
		public: int64_t forceGetAsSignedInt64();
#endif
		public: float forceGetAsFloat();
		public: double forceGetAsDouble();
		public: bool forceGetAsBool();
		#pragma endregion FORCED CONVERSIONS //}

		/*	TEMPLATE FOR EASY COPY PASTE.
		CRX__VAR__TYPE_STRING
		CRX__VAR__TYPE_HASH_TABLE
		CRX__VAR__TYPE_ARRAY
		CRX__VAR__TYPE_UNSIGNED_CHAR
		CRX__VAR__TYPE_SIGNED_INT32
		CRX__VAR__TYPE_SIGNED_INT64
		CRX__VAR__TYPE_EMULATED_INT
		CRX__VAR__TYPE_DOUBLE
		CRX__VAR__TYPE_BOOL
		CRX__VAR__TYPE_POINTER
		CRX__VAR__TYPE_NULL
		CRX__VAR__TYPE_UNDEFINED


		public: Var & operator+=(Var const & pVar)
		public: Var & operator+=(::std::string const & pString)	
		public: Var & operator+=(char const * pString)
		public: Var & operator+=(char const & pChar)
		public: Var & operator+=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap)
		public: Var & operator+=(::std::deque<Var> & pDeque)
		public: Var & operator+=(unsigned char const & pUnsignedChar)
#ifndef CRX__BOOST_NO_INT64_T
		public: Var & operator+=(uint32_t const & pUnsignedInt32)
#else
		CRX_DISABLE_METHOD(Var & operator+=(uint32_t const & pUnsignedInt32))
#endif
		public: Var & operator+=(int32_t const & pSignedInt32)
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var & operator+=(uint64_t const & pUnsignedInt64))
		public: Var & operator+=(int64_t const & pSignedInt64)
#endif
		public: Var & operator+=(float const & pFloat)
		public: Var & operator+=(double const & pDouble)
		public: Var & operator+=(bool const & pBool)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
#else
#endif
					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
#else
#endif
					break;
				}
				case CRX__VAR__TYPE_ARRAY:
				{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
#else
#endif
					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					break;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					break;
				}
				case CRX__VAR__TYPE_BOOL:
				{
					break;
				}
				case CRX__VAR__TYPE_POINTER:
				{
					break;
				}
				case CRX__VAR__TYPE_NULL:
				{
					break;
				}
				case CRX__VAR__TYPE_UNDEFINED:
				{
					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		*/

		#pragma region operator += //{
		public: Var & operator+=(Var const & pVar);
		public: Var & operator+=(::std::string const & pString);
		public: Var & operator+=(char const * pString);
		private: Var & doOperatorPlusEqual(char const * pChars, size_t pSize);
		public: Var & operator+=(char const & pChar);
		public: Var & operator+=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap);
#if(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		private: Var & doOperatorPlusEqual(CRX__VAR__KHash const * pKHash);
#endif
		public: Var & operator+=(::std::deque<Var> & pDeque);
#if(CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		private: Var & doOperatorPlusEqual(Crx_VarRing const * pVarRing);
#endif
		public: Var & operator+=(unsigned char const & pUnsignedChar);
		public: Var & operator+=(uint32_t const & pUnsignedInt32);
		public: Var & operator+=(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var & operator+=(uint64_t const & pUnsignedInt64))
		public: Var & operator+=(int64_t const & pSignedInt64);
#endif
#if(CRX__VAR__IS_EMULATED_INT_USED)
		private: Var & doOperatorPlusEqualForEmulatedInt(double const & pDouble);
#endif
		public: Var & operator+=(double const & pDouble);
		public: Var & operator+=(bool const & pBool);
		#pragma endregion operator += //}

		//-----------------------------------

		#pragma region operator -= //{
		public: Var & operator-=(Var const & pVar);
		public: Var & operator-=(::std::string const & pString);
		public: Var & operator-=(char const * pString);
		private: Var & doOperatorMinusEqual(char const * pChars, size_t pSize);
		public: Var & operator-=(char const & pChar);
		CRX_DISABLE_METHOD(Var & operator-=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var & operator-=(::std::deque<Var> & pDeque))
		public: Var & operator-=(unsigned char const & pUnsignedChar);
		public: Var & operator-=(uint32_t const & pUnsignedInt32);
		public: Var & operator-=(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var & operator-=(uint64_t const & pUnsignedInt64))
		public: Var & operator-=(int64_t const & pSignedInt64);
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		public: Var & doOperatorMinusEqualForEmulatedInt(double const & pDouble);
#endif
		public: Var & operator-=(double const & pDouble);
		CRX_DISABLE_METHOD(Var & operator-=(bool const & pBool))
		#pragma endregion operator -= //}
	
		//-----------------------------------

		#pragma region operator *= //{
		public: Var & operator*=(Var const & pVar);
		public: Var & operator*=(::std::string const & pString);
		public: Var & operator*=(char const * pString);
		private: Var & doOperatorMultiplyEqual(char const * pChars, size_t pSize);
		public: Var & operator*=(char const & pChar);
		CRX_DISABLE_METHOD(Var & operator*=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var & operator*=(::std::deque<Var> & pDeque))
		public: Var & operator*=(unsigned char const & pUnsignedChar);
		public: Var & operator*=(uint32_t const & pUnsignedInt32);
		public: Var & operator*=(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var & operator*=(uint64_t const & pUnsignedInt64))
		public: Var & operator*=(int64_t const & pSignedInt64);
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		public: Var & doOperatorMultiplyEqualForEmulatedInt(double const & pDouble);
#endif
		public: Var & operator*=(double const & pDouble);
		CRX_DISABLE_METHOD(Var & operator*=(bool const & pBool))
		#pragma endregion operator *= //}
			
		//-----------------------------------

		#pragma region operator /= //{
		public: Var & operator/=(Var const & pVar);
		public: Var & operator/=(::std::string const & pString);
		public: Var & operator/=(char const * pString);
		private: Var & doOperatorDivideEqual(char const * pChars, size_t pSize);
		public: Var & operator/=(char const & pChar);
		CRX_DISABLE_METHOD(Var & operator/=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var & operator/=(::std::deque<Var> & pDeque))
		public: Var & operator/=(unsigned char const & pUnsignedChar);
		public: Var & operator/=(uint32_t const & pUnsignedInt32);
		public: Var & operator/=(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var & operator/=(uint64_t const & pUnsignedInt64))
		public: Var & operator/=(int64_t const & pSignedInt64);
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		public: Var & doOperatorDivideEqualForEmulatedInt(double const & pDouble);
#endif
		public: Var & operator/=(double const & pDouble);
		CRX_DISABLE_METHOD(Var & operator/=(bool const & pBool))
		#pragma endregion operator /= //}
	
		//-----------------------------------

		#pragma region operator %= //{
		public: Var & operator%=(Var const & pVar);
		public: Var & operator%=(::std::string const & pString);
		public: Var & operator%=(char const * pString);
		private: Var & doOperatorModulusEqual(char const * pChars, size_t pSize);
		public: Var & operator%=(char const & pChar);
		public: Var & operator%=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap);
#if(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		private: Var & doOperatorModulusEqual(CRX__VAR__KHash const * pKHash);
#endif
		CRX_DISABLE_METHOD(Var & operator%=(::std::deque<Var> & pDeque))
		public: Var & operator%=(unsigned char const & pUnsignedChar);
		public: Var & operator%=(uint32_t const & pUnsignedInt32);
		public: Var & operator%=(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var & operator%=(uint64_t const & pUnsignedInt64))
		public: Var & operator%=(int64_t const & pSignedInt64);
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		public: Var & doOperatorModulusEqualForEmulatedInt(double const & pDouble);
#endif
		public: Var & operator%=(double const & pDouble);
		CRX_DISABLE_METHOD(Var & operator%=(bool const & pBool))
		#pragma endregion operator %= //}
		
		//-----------------------------------

		#pragma region operator < //{
		public: Var operator<(Var const & pVar);
		public: Var operator<(::std::string const & pString);
		public: Var operator<(char const * pString);
		private: Var doOperatorLessThan(char const * pChars, size_t pSize);
		public: Var operator<(char const & pChar);
		CRX_DISABLE_METHOD(Var operator<(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var operator<(::std::deque<Var> & pDeque))
		public: Var operator<(unsigned char const & pUnsignedChar);
		public: Var operator<(uint32_t const & pUnsignedInt32);
		public: Var operator<(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var operator<(uint64_t const & pUnsignedInt64))
		public: Var operator<(int64_t const & pSignedInt64);
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		private: Var doOperatorLessThanForEmulatedInt(double const & pDouble);
#endif
		public: Var operator<(double const & pDouble);
		CRX_DISABLE_METHOD(Var operator<(bool const & pBool))
		#pragma endregion operator < //}
	
		//-----------------------------------

		#pragma region operator > //{
		public: Var operator>(Var const & pVar);
		public: Var operator>(::std::string const & pString);
		public: Var operator>(char const * pString);
		private: Var doOperatorGreaterThan(char const * pChars, size_t pSize);
		public: Var operator>(char const & pChar);
		CRX_DISABLE_METHOD(Var operator>(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var operator>(::std::deque<Var> & pDeque))
		public: Var operator>(unsigned char const & pUnsignedChar);
		public: Var operator>(uint32_t const & pUnsignedInt32);
		public: Var operator>(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var operator>(uint64_t const & pUnsignedInt64))
		public: Var operator>(int64_t const & pSignedInt64);
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		private: Var doOperatorGreaterThanForEmulatedInt(double const & pDouble);
#endif
		public: Var operator>(double const & pDouble);
		CRX_DISABLE_METHOD(Var operator>(bool const & pBool))
		#pragma endregion operator > //}
	
		//-----------------------------------

		#pragma region operator &= //{
		public: Var & operator&=(Var const & pVar);
		public: Var & operator&=(::std::string const & pString);
		public: Var & operator&=(char const * pString);
		private: Var & doOperatorLogicAndEqual(char const * pChars, size_t pSize);
		public: Var & operator&=(char const & pChar);
		CRX_DISABLE_METHOD(Var & operator&=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var & operator&=(::std::deque<Var> & pDeque))
		public: Var & operator&=(unsigned char const & pUnsignedChar);
		public: Var & operator&=(uint32_t const & pUnsignedInt32);
		public: Var & operator&=(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var & operator&=(uint64_t const & pUnsignedInt64))
		public: Var & operator&=(int64_t const & pSignedInt64);
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		private: Var & doOperatorLogicAndEqualForEmulatedInt(double const & pDouble);
#endif
		public: Var & operator&=(double const & pDouble);
		CRX_DISABLE_METHOD(Var & operator&=(bool const & pBool))
		#pragma endregion operator &= //}
	
		//-----------------------------------

		#pragma region operator |= //{
		public: Var & operator|=(Var const & pVar);
		public: Var & operator|=(::std::string const & pString);
		public: Var & operator|=(char const * pString);
		private: Var & doOperatorLogicOrEqual(char const * pChars, size_t pSize);
		public: Var & operator|=(char const & pChar);
		CRX_DISABLE_METHOD(Var & operator|=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var & operator|=(::std::deque<Var> & pDeque))
		public: Var & operator|=(unsigned char const & pUnsignedChar);
		public: Var & operator|=(uint32_t const & pUnsignedInt32);
		public: Var & operator|=(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var & operator|=(uint64_t const & pUnsignedInt64))
		public: Var & operator|=(int64_t const & pSignedInt64);
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		private: Var & doOperatorLogicOrEqualForEmulatedInt(double const & pDouble);
#endif
		public: Var & operator|=(double const & pDouble);
		CRX_DISABLE_METHOD(Var & operator|=(bool const & pBool))
		#pragma endregion operator |= //}
	
		//-----------------------------------

		#pragma region operator ^= //{
		public: Var & operator^=(Var const & pVar);
		public: Var & operator^=(::std::string const & pString);
		public: Var & operator^=(char const * pString);
		private: Var & doOperatorLogicXOrEqual(char const * pChars, size_t pSize);
		public: Var & operator^=(char const & pChar);
		CRX_DISABLE_METHOD(Var & operator^=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var & operator^=(::std::deque<Var> & pDeque))
		public: Var & operator^=(unsigned char const & pUnsignedChar);
		public: Var & operator^=(uint32_t const & pUnsignedInt32);
		public: Var & operator^=(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var & operator^=(uint64_t const & pUnsignedInt64))
		public: Var & operator^=(int64_t const & pSignedInt64);
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		private: Var & doOperatorLogicXOrEqualForEmulatedInt(double const & pDouble);
#endif
		public: Var & operator^=(double const & pDouble);
		CRX_DISABLE_METHOD(Var & operator^=(bool const & pBool))
		#pragma endregion operator ^= //}
	
		//-----------------------------------

		#pragma region operator >>= //{
		public: Var & operator>>=(Var const & pVar);
		public: Var & operator>>=(::std::string const & pString);
		public: Var & operator>>=(char const * pString);
		private: Var & doOperatorLogicBitShiftRightEqual(char const * pChars, size_t pSize);
		public: Var & operator>>=(char const & pChar);
		CRX_DISABLE_METHOD(Var & operator>>=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var & operator>>=(::std::deque<Var> & pDeque))
		public: Var & operator>>=(unsigned char const & pUnsignedChar);
		public: Var & operator>>=(uint32_t const & pUnsignedInt32);
		public: Var & operator>>=(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var & operator>>=(uint64_t const & pUnsignedInt64))
		public: Var & operator>>=(int64_t const & pSignedInt64);
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		private: Var & doOperatorLogicBitShiftRightEqualForEmulatedInt(double const & pDouble);
#endif
		public: Var & operator>>=(double const & pDouble);
		CRX_DISABLE_METHOD(Var & operator>>=(bool const & pBool))
		#pragma endregion operator >>= //}
	
		//-----------------------------------

		#pragma region operator <<= //{
		public: Var & operator<<=(Var const & pVar);
		public: Var & operator<<=(::std::string const & pString);
		public: Var & operator<<=(char const * pString);
		private: Var & doOperatorLogicBitShiftLeftEqual(char const * pChars, size_t pSize);
		public: Var & operator<<=(char const & pChar);
		CRX_DISABLE_METHOD(Var & operator<<=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var & operator<<=(::std::deque<Var> & pDeque))
		public: Var & operator<<=(unsigned char const & pUnsignedChar);
		public: Var & operator<<=(uint32_t const & pUnsignedInt32);
		public: Var & operator<<=(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var & operator<<=(uint64_t const & pUnsignedInt64))
		public: Var & operator<<=(int64_t const & pSignedInt64);
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		private: Var & doOperatorLogicBitShiftLeftEqualForEmulatedInt(double const & pDouble);
#endif
		public: Var & operator<<=(double const & pDouble);
		CRX_DISABLE_METHOD(Var & operator<<=(bool const & pBool));
		#pragma endregion operator <<= //}
	
		//-----------------------------------

		#pragma region weakCompareTo //{
		public: bool weakCompareTo(Var const & pVar);
		public: bool weakCompareTo(::std::string const & pString);
		public: bool weakCompareTo(char const * pString);
		public: bool weakCompareTo(char const * pChars, size_t pSize);
		public: bool weakCompareTo(char const & pChar);
		public: bool weakCompareTo(unsigned char const & pUnsignedChar);
		public: bool weakCompareTo(uint32_t const & pUnsignedInt32);
		public: bool weakCompareTo(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		public: bool weakCompareTo(int64_t const & pSignedInt64);
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		private: bool weakCompareToEmulatedInt(double const & pDouble);
#endif
		public: bool weakCompareTo(double const & pDouble);
		public: bool weakCompareTo(bool const & pBool);
		#pragma endregion weakCompareTo //}
		
		//-----------------------------------
		
		#pragma region operator + //{
		public: Var operator+(Var const & pVar);
		public: Var operator+(::std::string const & pString);
		public: Var operator+(char const * pString);
		public: Var operator+(char const & pChar);
		public: Var operator+(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap);
		public: Var operator+(::std::deque<Var> & pDeque);
		public: Var operator+(unsigned char const & pUnsignedChar);
		public: Var operator+(uint32_t const & pUnsignedInt32);
		public: Var operator+(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var operator+(uint64_t const & pUnsignedInt64))
		public: Var operator+(int64_t const & pSignedInt64);
#endif
		public: Var operator+(double const & pDouble);
		public: Var operator+(bool const & pBool);
		#pragma endregion operator + //}
			
		//-----------------------------------

		#pragma region operator - //{
		public: Var operator-(Var const & pVar);
		public: Var operator-(::std::string const & pString);
		public: Var operator-(char const * pString);
		public: Var operator-(char const & pChar);
		CRX_DISABLE_METHOD(Var operator-(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var operator-(::std::deque<Var> & pDeque))
		public: Var operator-(unsigned char const & pUnsignedChar);
		public: Var operator-(uint32_t const & pUnsignedInt32);
		public: Var operator-(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var operator-(uint64_t const & pUnsignedInt64))
		public: Var operator-(int64_t const & pSignedInt64);
#endif
		public: Var operator-(double const & pDouble);
		CRX_DISABLE_METHOD(Var operator-(bool const & pBool))
		#pragma endregion operator - //}

		//-----------------------------------

		#pragma region operator * //{
		public: Var operator*(Var const & pVar);
		public: Var operator*(::std::string const & pString);
		public: Var operator*(char const * pString);
		public: Var operator*(char const & pChar);
		CRX_DISABLE_METHOD(Var operator*(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var operator*(::std::deque<Var> & pDeque))
		public: Var operator*(unsigned char const & pUnsignedChar);
		public: Var operator*(uint32_t const & pUnsignedInt32);
		public: Var operator*(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var operator*(uint64_t const & pUnsignedInt64))
		public: Var operator*(int64_t const & pSignedInt64);
#endif
		public: Var operator*(double const & pDouble);
		CRX_DISABLE_METHOD(Var operator*(bool const & pBool))
		#pragma endregion operator * //}

		//-----------------------------------

		#pragma region operator / //{
		public: Var operator/(Var const & pVar);
		public: Var operator/(::std::string const & pString);
		public: Var operator/(char const * pString);
		public: Var operator/(char const & pChar);
		CRX_DISABLE_METHOD(Var operator/(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var operator/(::std::deque<Var> & pDeque))
		public: Var operator/(unsigned char const & pUnsignedChar);
		public: Var operator/(uint32_t const & pUnsignedInt32);
		public: Var operator/(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var operator/(uint64_t const & pUnsignedInt64))
		public: Var operator/(int64_t const & pSignedInt64);
#endif
		public: Var operator/(double const & pDouble);
		CRX_DISABLE_METHOD(Var operator/(bool const & pBool))
		#pragma endregion operator - //}

		//-----------------------------------

		#pragma region operator % //{
		public: Var operator%(Var const & pVar);
		public: Var operator%(::std::string const & pString);
		public: Var operator%(char const * pString);
		public: Var operator%(char const & pChar);
		public: Var operator%(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap);
		CRX_DISABLE_METHOD(Var operator%(::std::deque<Var> & pDeque))
		public: Var operator%(unsigned char const & pUnsignedChar);
		public: Var operator%(uint32_t const & pUnsignedInt32);
		public: Var operator%(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var operator%(uint64_t const & pUnsignedInt64))
		public: Var operator%(int64_t const & pSignedInt64);
#endif
		public: Var operator%(double const & pDouble);
		CRX_DISABLE_METHOD(Var operator%(bool const & pBool))
		#pragma endregion operator % //}

		//-----------------------------------

		#pragma region operator <= //{
		public: bool operator<=(Var const & pVar);
		public: bool operator<=(::std::string const & pString);
		public: bool operator<=(char const * pString);
		public: bool operator<=(char const & pChar);
		CRX_DISABLE_METHOD(bool operator<=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(bool operator<=(::std::deque<Var> & pDeque))
		public: bool operator<=(unsigned char const & pUnsignedChar);
		public: bool operator<=(uint32_t const & pUnsignedInt32);
		public: bool operator<=(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(bool operator<=(uint64_t const & pUnsignedInt64))
		public: bool operator<=(int64_t const & pSignedInt64);
#endif;
		public: bool operator<=(double const & pDouble);
		CRX_DISABLE_METHOD(bool operator<=(bool const & pBool))
		#pragma endregion operator <= //}
		
		//-----------------------------------

		#pragma region operator >= //{
		public: bool operator>=(Var const & pVar);
		public: bool operator>=(::std::string const & pString);
		public: bool operator>=(char const * pString);
		public: bool operator>=(char const & pChar);
		CRX_DISABLE_METHOD(bool operator>=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(bool operator>=(::std::deque<Var> & pDeque))
		public: bool operator>=(unsigned char const & pUnsignedChar);
		public: bool operator>=(uint32_t const & pUnsignedInt32);
		public: bool operator>=(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(bool operator>=(uint64_t const & pUnsignedInt64))
		public: bool operator>=(int64_t const & pSignedInt64);
#endif;
		public: bool operator>=(double const & pDouble);
		CRX_DISABLE_METHOD(bool operator>=(bool const & pBool))
		#pragma endregion operator >= //}
	
		//-----------------------------------

		#pragma region operator & //{
		public: Var operator&(Var const & pVar);
		public: Var operator&(::std::string const & pString);
		public: Var operator&(char const * pString);
		public: Var operator&(char const & pChar);
		CRX_DISABLE_METHOD(Var operator&(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var operator&(::std::deque<Var> & pDeque))
		public: Var operator&(unsigned char const & pUnsignedChar);
		public: Var operator&(uint32_t const & pUnsignedInt32);
		public: Var operator&(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var operator&(uint64_t const & pUnsignedInt64))
		public: Var operator&(int64_t const & pSignedInt64);
#endif
		CRX_DISABLE_METHOD(Var operator&(float const & pFloat))
		CRX_DISABLE_METHOD(Var operator&(double const & pDouble))
		CRX_DISABLE_METHOD(Var operator&(bool const & pBool))
		#pragma endregion operator & //}

		//-----------------------------------

		#pragma region operator | //{
		public: Var operator|(Var const & pVar);
		public: Var operator|(::std::string const & pString);
		public: Var operator|(char const * pString);
		public: Var operator|(char const & pChar);
		CRX_DISABLE_METHOD(Var operator|(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var operator|(::std::deque<Var> & pDeque))
		public: Var operator|(unsigned char const & pUnsignedChar);
		public: Var operator|(uint32_t const & pUnsignedInt32);
		public: Var operator|(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var operator|(uint64_t const & pUnsignedInt64))
		public: Var operator|(int64_t const & pSignedInt64);
#endif
		CRX_DISABLE_METHOD(Var operator|(float const & pFloat))
		CRX_DISABLE_METHOD(Var operator|(double const & pDouble))
		CRX_DISABLE_METHOD(Var operator|(bool const & pBool))
		#pragma endregion operator | //}

		//-----------------------------------

		#pragma region operator ^ //{
		public: Var operator^(Var const & pVar);
		public: Var operator^(::std::string const & pString);
		public: Var operator^(char const * pString);
		public: Var operator^(char const & pChar);
		CRX_DISABLE_METHOD(Var operator^(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var operator^(::std::deque<Var> & pDeque))
		public: Var operator^(unsigned char const & pUnsignedChar);
		public: Var operator^(uint32_t const & pUnsignedInt32);
		public: Var operator^(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var operator^(uint64_t const & pUnsignedInt64))
		public: Var operator^(int64_t const & pSignedInt64);
#endif
		CRX_DISABLE_METHOD(Var operator^(float const & pFloat))
		CRX_DISABLE_METHOD(Var operator^(double const & pDouble))
		CRX_DISABLE_METHOD(Var operator^(bool const & pBool))
		#pragma endregion operator ^ //}

		//-----------------------------------

		#pragma region operator >> //{
		public: Var operator>>(Var const & pVar);
		public: Var operator>>(::std::string const & pString);
		public: Var operator>>(char const * pString);
		public: Var operator>>(char const & pChar);
		CRX_DISABLE_METHOD(Var operator>>(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var operator>>(::std::deque<Var> & pDeque))
		public: Var operator>>(unsigned char const & pUnsignedChar);
		public: Var operator>>(uint32_t const & pUnsignedInt32);
		public: Var operator>>(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var operator>>(uint64_t const & pUnsignedInt64))
		public: Var operator>>(int64_t const & pSignedInt64);
#endif
		CRX_DISABLE_METHOD(Var operator>>(float const & pFloat))
		CRX_DISABLE_METHOD(Var operator>>(double const & pDouble))
		CRX_DISABLE_METHOD(Var operator>>(bool const & pBool))
		#pragma endregion operator >> //}

		//-----------------------------------

		#pragma region operator << //{
		public: Var operator<<(Var const & pVar);
		public: Var operator<<(::std::string const & pString);
		public: Var operator<<(char const * pString);
		public: Var operator<<(char const & pChar);
		CRX_DISABLE_METHOD(Var operator<<(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var operator<<(::std::deque<Var> & pDeque))
		public: Var operator<<(unsigned char const & pUnsignedChar);
		public: Var operator<<(uint32_t const & pUnsignedInt32);
		public: Var operator<<(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var operator<<(uint64_t const & pUnsignedInt64))
		public: Var operator<<(int64_t const & pSignedInt64);
#endif
		CRX_DISABLE_METHOD(Var operator<<(float const & pFloat))
		CRX_DISABLE_METHOD(Var operator<<(double const & pDouble))
		CRX_DISABLE_METHOD(Var operator<<(bool const & pBool))
		#pragma endregion operator << //}

		//-----------------------------------

		#pragma region operator == //{
		public: Var operator==(Var const & pVar);
		public: Var operator==(::std::string const & pString);
		public: Var operator==(char const * pString);
		private: Var doOperatorEqual(char const * pChars, size_t pSize);
		public: Var operator==(char const & pChar);
		CRX_DISABLE_METHOD(Var operator==(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(Var operator==(::std::deque<Var> & pDeque))
		public: Var operator==(unsigned char const & pUnsignedChar);
		public: Var operator==(uint32_t const & pUnsignedInt32);
		public: Var operator==(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var operator==(uint64_t const & pUnsignedInt64))
		public: Var operator==(int64_t const & pSignedInt64);
#endif;
		public: Var operator==(double const & pDouble);
		public: Var operator==(bool const & pBool);
		#pragma endregion operator == //}
		
		//-----------------------------------

		#pragma region operator != //{
		public: bool operator!=(Var const & pVar);
		public: bool operator!=(::std::string const & pString);
		public: bool operator!=(char const * pString);
		public: bool operator!=(char const & pChar);
		CRX_DISABLE_METHOD(bool operator!=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLE_METHOD(bool operator!=(::std::deque<Var> & pDeque))
		public: bool operator!=(unsigned char const & pUnsignedChar);
		public: bool operator!=(uint32_t const & pUnsignedInt32);
		public: bool operator!=(int32_t const & pSignedInt32);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(bool operator!=(uint64_t const & pUnsignedInt64))
		public: bool operator!=(int64_t const & pSignedInt64);
#endif;
		public: bool operator!=(double const & pDouble);
		public: bool operator!=(bool const & pBool);
		#pragma endregion operator != //}

		//-----------------------------------

		#pragma region operator ++ //{
		public: Var & operator++();
		public: Var operator++(int);
		#pragma endregion operator ++ //}

		//-----------------------------------

		#pragma region operator -- //{
		public: Var & operator--();
		public: Var operator--(int);
		#pragma endregion operator -- //}

		//-----------------------------------

		#pragma region operator ~ //{
		public: Var operator~();
		#pragma endregion operator ~ //}

		//-----------------------------------

		#pragma region operator + (unary) //{
		/*THIS OPERATOR WILL NOT BE DEFINED*/
		#pragma endregion operator + (unary) //}

		//-----------------------------------

		#pragma region operator - (unary) //{
		public: Var operator-();
		#pragma endregion operator - (unary) //}

		//-----------------------------------

		#pragma region operator && //{
		/*ORIGINALLY: "THIS OPERATOR WILL NOT BE EXPLICITLY DEFINED, HOWEVER SHOULD SILL WORK"
				HOWEVER, DECIDED TO DEFINE THESE FOR THE BENEFIT OF VC6 AND POSSIBLY OTHER COMPILERS.
		*/
		public: bool operator&&(Var const & pVar);
		public: bool operator&&(bool const & pBool);
		#pragma endregion operator && //}

		//-----------------------------------

		#pragma region operator || //{
		/*ORIGINALLY: "THIS OPERATOR WILL NOT BE EXPLICITLY DEFINED, HOWEVER SHOULD SILL WORK"
				HOWEVER, DECIDED TO DEFINE THESE FOR THE BENEFIT OF VC6 AND POSSIBLY OTHER COMPILERS.
		*/
		public: bool operator||(Var const & pVar);
		public: bool operator||(bool const & pBool);
		#pragma endregion operator || //}

		//-----------------------------------

		#pragma region operator [] //{
		public: Var & operator[](::std::size_t pIndex);
		public: Var const & operator[](::std::size_t pIndex) const;

		/*
		THE FOLLOWING ARE TO AVOID AMBIGUITY ISSUES WITH INTEGER LITERALS
		WHICH AMOUNT TO INT. A USAGE LIKE vVar[0] IS AMBIGUOUS TO THE COMPILER
		AND IT DOES NOT KNOW WHETHER TO USE THE size_t OVERLOAD, OR THE BOOLEAN
		OVERLOAD OR THE char * OVERLOAD. WITH THE FOLLOWING ONE COULD ATLEAST
		WRITE SOMETHING LIKE vVar[0u] INSTEAD.
		*/
#if(CRX__VAR__IS_MACHINE_64BIT)
		public: Var & Var::operator[](unsigned int pIndex);
		public: Var const & Var::operator[](unsigned int pIndex) const;
#endif

		public: Var & operator[](::std::string const & pKey);
		public: Var const & operator[](::std::string const & pKey) const;
		public: Var & operator[](char const * pKey);
		public: Var const & operator[](char const * pKey) const;

		public: Var & operator[](bool pIndex);
		public: Var const & operator[](bool pIndex) const;

		public: Var & operator[](Var & pVar);
		public: Var const & operator[](Var & pVar) const;
		public: Var & operator[](Var const & pVar);
		public: Var const & operator[](Var const & pVar) const;
		private: CRX__BOOST_FORCEINLINE Var & doOperatorSquareBrackets(bool pIsThisConstant, 
				Var * CRX_NOT_NULL pVar, bool pIsConstant);
		#pragma endregion operator [] //}
		
		//-----------------------------------

		#pragma region Morph //{
		public: bool morphToString();
		public: bool morphToByte();
		public: bool morphToNumber();
		public: bool morphToBool();
		#pragma endregion Morph //}
		
		//-----------------------------------

		#pragma region Public Utilities //{
			#pragma region Types //{
		public: bool isString() const;
		public: bool isHashTable() const;
		public: bool isArray() const;
		public: bool isUnsignedChar() const;
		public: bool isSignedChar() const;
		public: bool isNumber() const;
		public: bool isBool() const;
		public: bool isPointer() const;
		public: bool isPointerOrNull() const;
		public: bool isNull() const;
		public: bool isUndefined() const;
		public: bool isError() const;
		public: bool isError(uint32_t pErrorCode) const;

		public: Var::Type getType();
		public: bool setType(Var::Type pType);
			#pragma endregion Types //}

		//-----------------------------------

			#pragma region Number //{
		public: bool isNan() const;
		public: bool isInf() const;
		public: bool isFinite() const; //UNSURE WHETHER I SHOULD KEEP THIS FUNCTION
			#pragma endregion Number //}

		//-----------------------------------

			#pragma region Error //{
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
		private: void setPrivateError(uint32_t pCode, ::std::string const & pMessage = "");
		private: void safeSetPrivateError(uint32_t pCode, ::std::string const & pMessage = "");
#endif
#if(CRX__VAR__IS_ERROR_TYPE_AVAILABLE_FOR_PUBLIC_USE)
		private: void setError(uint32_t pCode, ::std::string pMessage = "");
#endif
		public: void clearError();
		public: uint32_t getErrorCode();
		public: ::std::string getErrorMessage();
			#pragma endregion Error //}
		
		//-----------------------------------

			#pragma region Generic //{
		/*
		THIS FUNCTION MUST HAVE THE ALLOWANCE OF += . BUT REMEMBER THAT THIS IS A FUNCTION,
				NOT AN OPERATOR, AND HENCE BEHAVES DIFFERENTLY ON THE ERROR TYPE.
		*/
		public: bool append(char const * pChars, size_t pSize);

		public: Var getSub(size_t pStartIndex, size_t pMaxSize) const;
		public: size_t getSize() const;
		public: size_t getCapacity();

		public: size_t removeElementsAt(size_t pIndex, size_t pNumberOfElements = 1);
#if(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_HASH_TABLE_SORTED)
		public: size_t removeElementsAt(::std::string const & pKey, size_t pNumberOfElements = 1);
		public: size_t removeElementsAt(char const * pKey, size_t pNumberOfElements = 1);
#endif
		public: size_t removeElementsAt(size_t pIndex, Var const & pVar__numberOfElements);
#if(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_HASH_TABLE_SORTED)
		public: size_t removeElementsAt(::std::string const & pKey, Var const & pVar__numberOfElements);
		public: size_t removeElementsAt(char const * pKey, Var const & pVar__numberOfElements);
#endif
		public: size_t removeElementsAt(Var const & pVar, Var const & pVar__numberOfElements = 1);

		/*
		NOTE: CURRENTLY THIS FUNCTIONS EXISTS, EVEN THOUGH IT APPEARS REDUNDANT, BECUASE
				REMOVING ELEMENTS FROM THE HASH TABLE USING Var::removeElementsAt() IS ONLY 
				POSSIBLE IF THE HASHTABLE SUPPORTS INSERTION ORDER.
		*/
		public: void removeElementAt(size_t pIndex);
		public: void removeElementAt(::std::string const & pKey);
		public: void removeElementAt(char const * pKey);
		public: void removeElementAt(Var const & pVar);

		/*
		THESE ARE MEANT TO ACT THE erase() FUNCTIONS IN THE STL, FOR WHEN ALLOWING THE EFFICIENT
				SO CALLED ERASE-REMOVE IDIOM.
		*/
		public: Var::ArrayStlIterator unsafeRemoveElementsAtRange(Var::ArrayStlIterator pStartIterator,
				Var::ArrayStlIterator pEndIterator);
		public: Var::StringStlIterator unsafeRemoveElementsAtRange(Var::StringStlIterator pStartIterator,
				Var::StringStlIterator pEndIterator);
			#pragma endregion Generic //}
		
		//-----------------------------------

			#pragma region String //{
		public: Var getLowerCased() const;
		public: Var getLowerCased(::std::locale const & pLocale) const;

		public: Var getUpperCased() const;
		public: Var getUpperCased(::std::locale const & pLocale) const;

		public: Var getTrimmed() const;
		public: Var getTrimmed(::std::locale const & pLocale) const;

		public: char getCharAt(size_t pIndex) const;
		public: bool setCharAt(char pChar, size_t pIndex);
		public: size_t removeCharAt(size_t pIndex);
		public: size_t removeCharsAt(size_t pStartIndex, size_t pEndIndex);
			#pragma endregion String //}
		
		//-----------------------------------

			#pragma region HashTable //{
		public: bool hasKey(Var const & pVar);
		public: bool hasKey(::std::string const & pString);
		public: bool hasKey(char const * pString);

#if(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_HASH_TABLE_SORTED)
		/*THE FOLLOWING FUNCTIONS HELP USE THE HASHTABLE AS AN INDEXED LINKED LIST*/

		public: bool insertElementAfterKey(Var const & pVar__key, Var const & pVar__key2, 
				Var const & pVar__value);
		public: bool insertElementAfterKey(::std::string const & pKey1, ::std::string const & pKey2, 
				Var const & pVar__value);
		public: bool insertElementAfterKey(char const * pKey1, ::std::string const & pKey2, 
				Var const & pVar__value);
		public: bool insertElementAfterKey(::std::string const & pKey1, char const * pKey2, 
				Var const & pVar__value);
		public: bool insertElementAfterKey(char const * pKey1, char const * pKey2, 
				Var const & pVar__value);

		public: bool insertElementBeforeKey(Var const & pVar__key, Var const & pVar__key2, 
				Var const & pVar__value);
		public: bool insertElementBeforeKey(::std::string const & pKey1, ::std::string const & pKey2, 
				Var const & pVar__value);
		public: bool insertElementBeforeKey(char const * pKey1, ::std::string const & pKey2, 
				Var const & pVar__value);
		public: bool insertElementBeforeKey(::std::string const & pKey1, char const * pKey2, 
				Var const & pVar__value);
		public: bool insertElementBeforeKey(char const * pKey1, char const * pKey2, 
				Var const & pVar__value);
#endif
			#pragma endregion HashTable //}

		//-----------------------------------

			#pragma region Array //{
		public: bool push(Var const & pVar);
		public: Var popAndGet();
		public: bool pushToFront(Var const & pVar);
		public: Var popFromFrontAndGet();

		public: bool insertElementAt(size_t pIndex, Var const & pVar);
		public: bool insertElementAt(Var pVar__index, Var const & pVar);

		public: bool insertElementsAt(size_t pIndex, Var const & pVar__array, 
				size_t pStartIndex, size_t pWidth);
		public: bool insertElementsAt(Var const & pVar__index, Var const & pVar__array, 
				Var const & pVar__startIndex, Var const &  pVar__width);
			#pragma endregion Array //}

		//-----------------------------------

		public: void removeElement(Var const & pVar); //TO BE IMPLEMENTED
		public: Var * getElementAt(Var const & pVar); //TO BE IMPLEMENTED
		//public: void getElementAt(Var const & pVar); //TO BE IMPLEMENTED
		public: bool ensureCapacity(size_t pCapacity); //TO BE IMPLEMENTED
		
		#pragma endregion Public Utilities //}
		//-----------------------------------

		#pragma region ITERATOR SUPPORT //{
			#pragma region STL ITERATORS //{
				#pragma region STRING //{
		public: Var::StringStlIterator getStringStartStlIterator();
		public: Var::StringConstantStlIterator getStringStartConstantStlIterator() const;
		
		/*
		NOTE: THIS RELIES ON POINTER COMPARISON, WHICH IS IMPLICITLY USED TO DETECT THE SITUATION,
				WHEN THE TYPE IS STILL STRING, THAT THE STRING CHANGED COMPLETELY DURING ITERATION.
				THIS IS HOWEVER UNSPECIFIED BEHAVIOR UNDER C++, BUT SHOULD LIKELY WORK CORRECTLY
				UNDER ALL HARDWARE WHERE USING Var IS USEFULL.
		*/
		public: bool hasStringStlIteratorEnded(Var::StringConstantStlIterator pChar) const;
		/*
		NOTE: THIS IS UNSAFER WAY TO CHECK END OF ITERATION, BUT IS MORE EFFICIENT, AND STL COMPATIBLE.
				A SAFER WAY IS TO USE Var::hasStringStlIteratorEnded()
		*/
		public: Var::StringStlIterator getStringEndStlIterator();
		public: Var::StringConstantStlIterator getStringEndConstantStlIterator() const;
				#pragma endregion STRING //}

				#pragma region ARRAY //{
		public: Var::ArrayStlIterator getArrayStartStlIterator();
		public: Var::ArrayConstantStlIterator getArrayStartConstantStlIterator() const;

		public: bool hasArrayStlIteratorEnded(Var::ArrayConstantStlIterator pArrayConstantStlIterator) const;

		public: Var::ArrayStlIterator getArrayEndStlIterator();
		public: Var::ArrayConstantStlIterator getArrayEndStlIterator() const;
				#pragma endregion ARRAY //}
		//-----------------------------------

			#pragma endregion STL ITERATORS //}

		//-----------------------------------

			#pragma region GENERIC ITERATOR AND ALTERNATIVES //{

				#pragma region MAIN ITERATOR //{
		public: Var::iterator begin();
		public: Var::iterator end();

		public: Var::const_iterator cbegin() const;
		public: Var::const_iterator cend() const;
				#pragma endregion MAIN ITERATOR //}

		//-----------------------------------

				#pragma region ALTERNATIVE ITERATOR: STRING //{
		public: Var::StringIterator getStringStartIterator();
		public: Var::StringIterator getStringEndIterator();

		public: Var::StringConstantIterator getStringStartConstantIterator() const;
		public: Var::StringConstantIterator getStringEndConstantIterator() const;
				#pragma endregion ALTERNATIVE ITERATOR: STRING //}
			#pragma endregion GENERIC ITERATOR AND ALTERNATIVES //}

		//-----------------------------------

			#pragma region OTHERS //{
		/*
		THIS ALLOWS ITERATION BEHAVIOR SUCH AS ITERATION OVER THE HASHTABLE CONTINUES
		OVER ALL THE ORIGINAL KEYS UNAFFECTED BY INSERTION OR REMOVAL. THIS IS THE
		SAME BEHAVIOR IN Javascript FOR EXAMPLE.

		A SAFE LOOP WOULD LOOK LIKE:

		for(::std::string tKey in gVar.getHashTableKeys())
		{
			if(gVar.hasKey(tKey)) //ONLY TRULY NECESSARY IN VERY RARE CASES
				{continue;}

			..do the work here, which includes removal and addition of elements..
		}
		*/
		public: ::std::vector<::std::string> getHashTableKeys();
			#pragma endregion OTHERS //}
		/*
		REMOVED BECAUSE NO SAFE ITERATOR EXISTS FOR HASH TABLES SUCH AS
				INVALIDITY COULD BE CORRECTLY DETECTED AND EFFICIENTLY

		CRX_PUBLIC Var::HashTableIterator Var::getHashTableStartIterator()
		{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			return Var::HashTableIterator(this);
#else
			return Var::HashTableIterator(this);
#endif
		}
		CRX_PUBLIC Var::HashTableConstantIterator Var::getHashTableConstantStartIterator() const
		{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			return Var::HashTableConstantIterator(this);
#else
			return Var::HashTableConstantIterator(this);
#endif
		}
		CRX_PUBLIC bool Var::isHashTableIteratorValid(Var::HashTableIterator const & pUnorderedSetIterator) const
		{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			return pUnorderedSetIterator.isValid();
#else
			return pUnorderedSetIterator.isValid();
#endif
		}*/

		#pragma endregion ITERATOR SUPPORT //}

		//-----------------------------------

		#pragma region VARJSON //{
		public: static Var parseVarJson(Var const & pVar__string);
		public: static Var parseVarJson(::std::string const & pString);
		public: static Var parseVarJson(char const * pString);
		public: static Var parseVarJson(char const * pChars, size_t pSize);
		private: static bool parseVarJsonValue(Var::VarJsonData * CRX_NOT_NULL const pVarJsonData, 
				Var * CRX_NOT_NULL pVar);
		private: static void parseVarJsonValue__skipWhiteSpacesAndComments(
				Var::VarJsonData * CRX_NOT_NULL const pVarJsonData);
		private: static void reportVarJsonError(Var::VarJsonData * const pVarJsonData, 
				char const * CRX_NOT_NULL pMessage, Var * CRX_NOT_NULL pVar);
				
		public: Var convertToVarJsonUtf8String();
		private: void _convertToVarJsonUtf8String(Var * CRX_NOT_NULL pString);

		public: Var convertToJsonUtf8String() const;
		private: void _convertToJsonUtf8String(Var * CRX_NOT_NULL pString) const;
		#pragma endregion VARJSON //}

		//-----------------------------------

		public: ~Var();
	};

	class VarThreadPossible : public Var
	{
		public: VarThreadPossible();

		public: VarThreadPossible(Var::Nil pNil);
		public: VarThreadPossible(Var::Undefined pUndefined);
		public: VarThreadPossible(Var::Type pType);

		#pragma region COPY CONSTRUCTOR //{
		public: VarThreadPossible(Var const & pVar);
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || !CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		public: VarThreadPossible(::std::string const & pString);
#endif
		public: VarThreadPossible(char const * pString);
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		public: VarThreadPossible(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap);
#endif
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		public: VarThreadPossible(::std::deque<Var> const & pDeque);
#endif
		public: VarThreadPossible(unsigned char const & pUnsignedChar);
		public: VarThreadPossible(signed char const & pChar);
#if((!CRX__VAR__IS_EMULATED_INT_USED && CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64) || CRX__VAR__IS_EMULATED_INT_USED)
		public: VarThreadPossible(uint32_t pUnsignedInt32);
#else
		CRX_DISABLE_METHOD(VarThreadPossible(uint32_t pUnsignedInt32))
#endif
		public: VarThreadPossible(int32_t const & pSignedInt);
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(VarThreadPossible(uint64_t pUnsignedInt64))
	#if(CRX__VAR__IS_EMULATED_INT_USED || CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
		public: VarThreadPossible(int64_t pSignedInt64);
	#else
		CRX_DISABLE_METHOD(VarThreadPossible(int64_t pSignedInt64))
	#endif
#endif
		public: VarThreadPossible(float const & pFloat);
		public: VarThreadPossible(double const & pDouble);
#if(CRX__VAR__IS_ERROR_TYPE_AVAILABLE_FOR_PUBLIC_USE)
		public: VarThreadPossible(uint32_t gCode, ::std::string const pMessage);
		public: VarThreadPossible(uint32_t gCode, char const * pMessage);
#endif
		public: VarThreadPossible(bool pBool);
		//public: VarThreadPossible(Var::VarBoolean pVarBoolean);
		#pragma endregion COPY CONSTRUCTOR //}

#ifndef CRX__BOOST_NO_CXX11_HDR_INITIALIZER_LIST
		public: VarThreadPossible(
				::std::initializer_list<::std::pair<::std::string const, Var>> pInitializerList);
		public: VarThreadPossible(Var::ARRAY_DEFINITION _s, ::std::initializer_list<Var> pInitializerList);
#endif

		#pragma region operator = //{
#ifndef CRX__BOOST_NO_CXX11_DELETED_FUNCTIONS
		//NOTE THAT THE CHECK FOR CRX__BOOST_NO_CXX11_DELETED_FUNCTIONS IS NEEDED BEFORE OF using IN THE 
		//		CLASS VarThreadPossible. OTHERWISE THE CODE DOES NOT WORK PRE C++11
		using Var::operator=;
#else
		public: Var & operator=(Var pVar);
	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		#ifndef CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
		public: Var & operator=(::std::string && pString);
		#else
		public: Var & operator=(::std::string pString);
		#endif
	#endif
	#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || !CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		public: Var & operator=(::std::string const & pString);
	#endif
	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		#ifndef CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
		public: Var & operator=(::crx::ClassUnorderedMap<::std::string, Var>::t && pUnorderedMap);
		#else
		public: Var & operator=(::crx::ClassUnorderedMap<::std::string, Var>::t pUnorderedMap);
		#endif
	#endif
	#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		public: Var & operator=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap);
	#endif
	#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		#ifndef CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
		public: Var & operator=(::std::deque<Var> && pDeque);
		#else
		public: Var & operator=(::std::deque<Var> pDeque);
		#endif
	#endif
	#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		public: Var & operator=(::std::deque<Var> const & pDeque);
	#endif
		public: Var & operator=(char const * pString);
		public: Var & operator=(unsigned char const & pUnsignedChar);
		public: Var & operator=(signed char const & pChar);
	#if((!CRX__VAR__IS_EMULATED_INT_USED && CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64) || CRX__VAR__IS_EMULATED_INT_USED)
		public: Var & operator=(uint32_t const pUnsignedInt32);
	#endif
		public: Var & operator=(int32_t const & pSignedInt);
	#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLE_METHOD(Var & operator=(uint64_t pUnsignedInt64))
		#if(CRX__VAR__IS_EMULATED_INT_USED || CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
		public: Var & operator=(int64_t pSignedInt64);
		#else
		CRX_DISABLE_METHOD(Var & operator=(int64_t pSignedInt64))
		#endif
	#endif
		public: Var & operator=(float const & pFloat);
		public: Var & operator=(double const & pDouble);
		//DISABLE THE FOLLOWING IF YOU DISABLE THE BOOLEAN COPY CONSTRUCTOR BECAUSE OF PRE C++11 safety
		//		SEE Var(bool pBool, bool pIsToBeThreadPossible = false)
		public: Var & operator=(bool const & pBool);
#endif
		#pragma endregion operator = //}
	};

	#pragma region Var iterators //{

		#pragma region Var Sorted KHash Iterator //{

	/*
	FOR BACK WARD COMPATIBILITY WITH VS6 AT LEAST
		- THESE TEMPLATES ARE NOT DEFINED INSIDE CLASSES, IN OTHER WORDS INSIDE THE Var CLASS
		- SFINAE IS AVOIDED, HENCE THE DUMMY CLASS Var_VarIterator_DummyStructure
	*/

	class SortedVarKHash_SortedVarKHashIterator_DummyStructure
	{
		public: SortedVarKHashNode gSortedVarKHashNode;
		public: bool gIsEnd;
	};
	template<bool T> class SortedVarKHash_SortedVarKHashIterator;
	template<bool T_bool>
			class SortedVarKHash_SortedVarKHash_Info
		{};
	template<> 
			class SortedVarKHash_SortedVarKHash_Info<true>
	{
		public: typedef Var const t;
		public: typedef SortedVarKHash_SortedVarKHashIterator<false> t2;
	};
	template<> 
			class SortedVarKHash_SortedVarKHash_Info<false>
	{
		public: typedef Var t;
		public: typedef SortedVarKHash_SortedVarKHashIterator_DummyStructure t2;
	};
	template<bool T> 
			class SortedVarKHash_SortedVarKHashIterator
	{
		private: SortedVarKHashNode gSortedVarKHashNode;
		private: bool gIsEnd;


		public: SortedVarKHash_SortedVarKHashIterator() :
				gSortedVarKHashNode(SortedVarKHashNode()), gIsEnd(true)
		{
			this->gSortedVarKHashNode.gNext = NULL;
			this->gSortedVarKHashNode.gPrevious = NULL;
			this->gSortedVarKHashNode.gKey = NULL;
			this->gSortedVarKHashNode.gVar = NULL;
		}
		public: SortedVarKHash_SortedVarKHashIterator(SortedVarKHashNode pSortedVarKHash,
				bool pIsEnd = false) : gSortedVarKHashNode(pSortedVarKHash), gIsEnd(pIsEnd)
			{}

		/* THIS IS NOT MEANT TO EXIST WHEN T IS false.
				ALLOW ASSIGNMENT OF ITERATOR TO CONSTANT ITERATOR, BUT NOT THE OTHER WAY AROUND.
				ALSO NOTE THAT DEFAULT CONSTRUCTOR IS ASSUMED CREATED.
		*/
		public: SortedVarKHash_SortedVarKHashIterator(
				typename SortedVarKHash_SortedVarKHash_Info<T>::t2 & pSortedVarKHashIterator) : 
				gSortedVarKHashNode(pSortedVarKHashIterator.gSortedVarKHashNode), 
				gIsEnd(pSortedVarKHashIterator.gIsEnd)
			{}

		public: SortedVarKHash_SortedVarKHashIterator & operator++()
		{
			if(this->gIsEnd)
				{return *this;}

			if(this->gSortedVarKHashNode.gNext == NULL)
				{this->gIsEnd = true;}
			else
				{this->gSortedVarKHashNode = *(this->gSortedVarKHashNode->gNext);}
			
			return (*this);
		}

		/*NOTE: ALL END ITERATORS ARE CONSIDERED EQUAL.*/
		public: bool operator!=(
				const SortedVarKHash_SortedVarKHashIterator & pSortedVarKHashIterator) const
		{
			if(this->gIsEnd)
				{return (pSortedVarKHashIterator.gIsEnd == false);}
			else
			{
				if(pSortedVarKHashIterator.gIsEnd)
					{return true;}
				else
				{
					return !((this->gSortedVarKHashNode.gNext == pSortedVarKHashIterator.gSortedVarKHashNode.gNext) &&
							(this->gSortedVarKHashNode.gPrevious == pSortedVarKHashIterator.gSortedVarKHashNode.gPrevious) &&
							(this->gSortedVarKHashNode.gVar == pSortedVarKHashIterator.gSortedVarKHashNode.gVar) &&
							(this->gSortedVarKHashNode.gKey == pSortedVarKHashIterator.gSortedVarKHashNode.gKey));
				}
			}
		}
		const ::std::pair<::std::string const, 
				typename ::crx::SortedVarKHash_SortedVarKHash_Info<T>::t> operator*() const
		{
			assert(!this->gIsEnd);

			return ::std::pair<::std::string const, ::crx::SortedVarKHash_SortedVarKHash_Info<T>::t>(
					this->gSortedVarKHashNode.gKey, *(this->gSortedVarKHashNode.gVar));
		}
		
		public: ::std::string getKey() const
		{
			assert(!this->gIsEnd);
			
			return this->gSortedVarKHashNode.gKey;
		}

		public: typename ::crx::SortedVarKHash_SortedVarKHash_Info<T>::t* getValue()
		{
			assert(!this->gIsEnd);
			
			return this->gSortedVarKHashNode.gVar;
		}

		public: bool advanceSelfByOne()
		{
			if(this->gIsEnd)
				{return false;}

			if(this->gSortedVarKHashNode.gNext != NULL)
				{this->gSortedVarKHashNode = *(this->gSortedVarKHashNode.gNext);}
			else
				{this->gIsEnd = true;}

			return true;
		}
	};

		#pragma endregion Var Sorted KHash Iterator //}
	
		#pragma region Var String Generic Iterator Alternative Iterator //{
	/*
	FOR BACK WARD COMPATIBILITY WITH VS6 AT LEAST
		- THESE TEMPLATES ARE NOT DEFINED INSIDE CLASSES, IN OTHER WORDS INSIDE THE Var CLASS
		- SFINAE IS AVOIDED, HENCE THE DUMMY CLASS Var_StringIterator_DummyStructure
	*/

	class Var_StringIterator_DummyStructure
	{
		public: Var * CRX_NOT_MINE gVar;
		private: size_t gIndex;
		public: bool gIsVoid;
	};
	template<bool T> class Var_StringIterator;
	template<bool T_bool>
			class Var_StringIterator_Info
		{};
	template<> 
			class Var_StringIterator_Info<true>
	{
		public: typedef Var const t;
		public: typedef Var_StringIterator<false> t2;
	};
	template<> 
			class Var_StringIterator_Info<false>
	{
		public: typedef Var t;
		public: typedef Var_StringIterator_DummyStructure t2;
	};
	template<bool T> 
			class Var_StringIterator
	{
		friend class Var;
		
		private: typename Var_StringIterator_Info<T>::t * CRX_NOT_MINE gVar;
		private: size_t gIndex;
		private: bool gIsVoid;


		public: Var_StringIterator(typename Var_StringIterator_Info<T>::t * pVar, 
				bool pIsToGetEnd = false) : gVar(pVar), gIsVoid(false)
		{
			if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_STRING)
			{
				if(!pIsToGetEnd)
					{this->gIndex = 0;}
				else
					{this->gIndex = this->gVar->getSize();}
			}
			else
				{this->gIsVoid = true;}
		}

		/* THIS IS NOT MEANT TO EXIST WHEN T IS false.
				ALLOW ASSIGNMENT OF ITERATOR TO CONSTANT ITERATOR, BUT NOT THE OTHER WAY AROUND.
				ALSO NOTE THAT DEFAULT CONSTRUCTOR IS ASSUMED CREATED.
		*/
		public: Var_StringIterator(typename Var_StringIterator_Info<T>::t2 & pVarIterator) : 
				gVar(pVarIterator.gVar), gIndex(pVarIterator.gIndex), 
				gIsVoid(pVarIterator.gIsVoid)
			{}

		public: Var_StringIterator & operator++()
		{
			if(this->gIsVoid)
				{return *this;}

			if((CRX__VAR__GET_TYPE1(this->gVar) == CRX__VAR__TYPE_STRING) &&
					(this->gIndex < this->gVar->getSize()))
				{this->gIndex++;}
			else
				{this->gIsVoid = true;}

			return *this;
		}
		/*
			WARNING: This operator is not to be used to test for equality
					between iterators. It does not work as expected. The
					sole purpose of this operator is to halt an iterator loop.
					Its effective name is "isToProceedWithLoop()"
					If you need to test for actual equality, use 
					Var_StringIterator::isEqualTo(). 
		*/
		public: bool operator!=(const Var_StringIterator & pVarIterator) const
		{
			if((CRX__VAR__GET_TYPE1(this->gVar) == CRX__VAR__TYPE_STRING) &&
					(CRX__VAR__GET_TYPE1(pVarIterator.gVar) == CRX__VAR__TYPE_STRING) &&
					(this->gVar == pVarIterator.gVar) &&
					!this->gIsVoid && !pVarIterator.gIsVoid)
				{return (this->gIndex != pVarIterator.gIndex);}
			else
				{return false;}
		}
		size_t operator*() const;

		public: size_t removeElementsAndUpdateSelf(size_t pWidth)
		{
			if(this->gIsVoid || (CRX__VAR__GET_TYPE1(this->gVar) != CRX__VAR__TYPE_STRING) ||
					(pWidth == 0))
				{return 0;}

			size_t tWidthOfRemovedElements = this->gVar->removeCharsAt(this->gIndex, pWidth);

			/*this->gIndex = this->gIndex + tWidthOfRemovedElements;*/

			return tWidthOfRemovedElements;
		}

		public: bool removeElementAndUpdateSelf()
			{return (this->removeElementsAndUpdateSelf(1) > 0);}

		public: size_t advanceSelfBy(size_t pNumberOfSteps)
		{
			if(this->gIsVoid || (CRX__VAR__GET_TYPE1(this->gVar) != CRX__VAR__TYPE_STRING) ||
					(pNumberOfSteps == 0))
				{return 0;}

			size_t tNumberOfSteps /*= 0*/;

			if(this->gIndex + pNumberOfSteps <= this->gVar->getSize())
				{tNumberOfSteps = pNumberOfSteps;}
			else
				{tNumberOfSteps = this->gVar->getSize() - this->gIndex;}

			this->gIndex = this->gIndex + tNumberOfSteps;

			return tNumberOfSteps;
		}
	};

		#pragma endregion Var String Generic Iterator Alternative Iterator //}

		#pragma region Var Generic Iterators //{
	/*
	FOR BACK WARD COMPATIBILITY WITH VS6 AT LEAST
		- THESE TEMPLATES ARE NOT DEFINED INSIDE CLASSES, IN OTHER WORDS INSIDE THE Var CLASS
		- SFINAE IS AVOIDED, HENCE THE DUMMY CLASS Var_VarIterator_DummyStructure
	*/

	/*
		REMOVED BECAUSE NO SAFE ITERATOR EXISTS FOR HASH TABLES SUCH AS
				INVALIDITY COULD BE CORRECTLY DETECTED AND EFFICIENTLY
				TO UNDERSTAND THIS, THINK OF THE SITUATION WHERE THE HASHTABLE
				INSTANCE ITSELF WAS DESTROYED AND THEN CREATED AGAIN BETWEEN 
				AN ITERATION AND THE NEXT, WHILE ENDING UP WITH THE SAME POINTER
				VALUE TO IT.

	class Var_HashTableIterator_DummyStructure
	{
		private: Var * gVar;
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		private: ::crx::ClassUnorderedMap<::std::string, Var>::t * gUnorderedList;
		private: ::crx::ClassUnorderedMap<::std::string, Var>::t::iterator gIterator;
#else
		private: CRX__VAR__KHash * gKHash;
		private: khiter_t gKhiter;
#endif
		private: mutable bool gIsVoid;
	};
	template<bool T> class Var_HashTableIterator;
	template<bool T_bool>
			class Var_HashTableIterator_Info
		{};
	template<> 
			class Var_HashTableIterator_Info<true>
	{
		public: typedef const Var t;
		public: typedef Var_HashTableIterator<false> t2;
	};
	template<> 
			class Var_HashTableIterator_Info<false>
	{
		public: typedef Var t;
		public: typedef Var_HashTableIterator_DummyStructure t2;
	};
	template<bool T>
			class Var_HashTableIterator
	{
		friend class Var;

		private: Var_HashTableIterator_Info<T>::t * CRX_NOT_MINE gVar;
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		private: ::crx::ClassUnorderedMap<::std::string, Var>::t * gUnorderedList;
		private: ::crx::ClassUnorderedMap<::std::string, Var>::t::iterator gIterator;
#else
		private: CRX__VAR__KHash * CRX_NOT_MINE gKHash;
		private: khiter_t gKhiter;
#endif
		private: mutable bool gIsVoid;
			

		private: Var_HashTableIterator(Var_HashTableIterator_Info<T>::t * pVar, 
				bool pIsNotStart = false) : gVar(pVar), gIsVoid(false)
		{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_HASH_TABLE)
			{
				this->gUnorderedList = pVar->gData.uHashTable.gUnorderedMap;

				if(!pIsNotStart)
					{this->gIterator = this->gUnorderedList->begin();}
				else
					{this->gIterator = this->gUnorderedList->end();}
			}
			else
			{
				this->gUnorderedList = NULL;
				this->gIsVoid = true;
			}
#else
			if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_HASH_TABLE)
			{
				this->gKHash = pVar->gData.uHashTable.gKHash;

				if(!pIsNotStart)
					{this->gKhiter = kh_begin(pVar->gData.uHashTable.gKHash);}
				else
					{this->gKhiter = kh_end(pVar->gData.uHashTable.gKHash);}
			}
			else
			{
				this->gKHash = NULL;
				this->gIsVoid = true;
			}
#endif
		}
		private: Var_HashTableIterator(Var_HashTableIterator_Info<T>::t2 & pHashTableIterator) :
				gVar(pHashTableIterator.gVar),
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
				gUnorderedList(pHashTableIterator.gUnorderedList), gIterator(pHashTableIterator.gIterator),
#else
				gKHash(pHashTableIterator.gKHash), gKhiter(pHashTableIterator.gKhiter),
#endif
				gIsVoid(pHashTableIterator.gIsVoid)
			{}

		public: Var_HashTableIterator operator++()
		{
			if(this->gIsVoid)
				{return *this;}
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			if((CRX__VAR__GET_TYPE1(this->gVar) == CRX__VAR__TYPE_HASH_TABLE) &&
					(this->gUnorderedList == this->gVar->gData.uHashTable.gUnorderedMap))
				{this->gIterator++;}
			else
				{this->gIsVoid = true;}
#else
			if((CRX__VAR__GET_TYPE1(this->gVar) == CRX__VAR__TYPE_HASH_TABLE) &&
					(this->gKHash == this->gVar->gData.uHashTable.gKHash))
				{this->gKhiter++;}
			else
				{this->gIsVoid = true;}
#endif

			return *this;
		}
		public: bool operator!=(const Var_HashTableIterator & pUnorderedSetIterator) const
		{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			return (this->gIsVoid != pUnorderedSetIterator.gIsVoid) ||
					(!this->gIsVoid && !pUnorderedSetIterator.gIsVoid &&
					(this->gIterator != pUnorderedSetIterator.gIterator));
#else
			return (this->gIsVoid != pUnorderedSetIterator.gIsVoid) ||
					(!this->gIsVoid && !pUnorderedSetIterator.gIsVoid &&
					(this->gKhiter != pUnorderedSetIterator.gKhiter));
#endif
		}
		::std::pair<::std::string const, ::crx::Var_HashTableIterator_Info<T>::t> operator*() const
		{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			if(this->gIsVoid)
				{return ::std::pair<::std::string const,::crx::Var_HashTableIterator_Info<T>::t>(::std::string(), Var(Var::Nil()));}

			if((CRX__VAR__GET_TYPE1(this->gVar) == CRX__VAR__TYPE_HASH_TABLE) &&
					(this->gUnorderedList == this->gVar->gData.uHashTable.gUnorderedMap))
				{return *(this->gIterator);}
			else
			{
				const_cast<Var::Var_HashTableIterator *>(this)->gIsVoid = true;

				return ::std::pair<::std::string const, ::crx::Var_HashTableIterator_Info<T>::t>(::std::string(), Var(Var::Nil()));
			}
#else
			if(this->gIsVoid)
				{return ::std::pair<::std::string const, ::crx::Var_HashTableIterator_Info<T>::t>(::std::string(), Var(Var::Nil()));}

			if((CRX__VAR__GET_TYPE1(this->gVar) == CRX__VAR__TYPE_HASH_TABLE) &&
					(this->gKHash == this->gVar->gData.uHashTable.gKHash))
			{
				return ::std::pair<::std::string const, ::crx::Var const>(kh_key(this->gKHash, 
						this->gKhiter), *(kh_value(this->gKHash, this->gKhiter)));
			}
			else
			{
				const_cast<Var::Var_HashTableIterator *>(this)->gIsVoid = true;

				return ::std::pair<::std::string const, ::crx::Var_HashTableIterator_Info<T>::t>(::std::string(), Var(Var::Nil()));
			}
#endif
		}
		public: bool isValid() const
		{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			if(this->gIsVoid)
				{return false;}

			if((CRX__VAR__GET_TYPE1(this->gVar) == CRX__VAR__TYPE_HASH_TABLE) &&
					(this->gUnorderedList == this->gVar->gData.uHashTable.gUnorderedMap))
				{return true;}
			else
			{
				const_cast<Var::Var_HashTableIterator *>(this)->gIsVoid = true;

				return false;
			}
#else
			if(this->gIsVoid)
				{return false;}

			if((CRX__VAR__GET_TYPE1(this->gVar) == CRX__VAR__TYPE_HASH_TABLE) &&
					(this->gKHash == this->gVar->gData.uHashTable.gKHash))
				{return true;}
			else
			{
				const_cast<Var::Var_HashTableIterator *>(this)->gIsVoid = true;

				return false;
			}
#endif
		}
	};
	*/
	typedef struct Var_VarIterator_Data
	{
		//char _ufgbdksfj[sizeof(void *)];
		union gIterator
		{
#ifndef CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
			//char * uStringIterator;
	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			::crx::ClassUnorderedMap<::std::string, Var>::t::iterator uIterator__unorderedMap;
	#else
			CRX__VAR__KHASH__ITERATOR uKhiter;
	#endif
#else
	#ifndef CRX__BOOST_NO_INT64_T
			int64_t _fgud9;
	#else
			int32_t _fgud8;
	#endif
			unsigned char gShared[((sizeof(CRXM__IFELSE(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					(CRX__VAR__KHASH__ITERATOR)(::crx::ClassUnorderedMap<::std::string, Var>::t::iterator)) > 
					sizeof(CRXM__IFELSE2(CRX__BOOST_NO_INT64_T, uint32_t, uint64_t))) ? 
					sizeof(CRXM__IFELSE(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
							(CRX__VAR__KHASH__ITERATOR)(::crx::ClassUnorderedMap<::std::string, Var>::t::iterator)) : 
							sizeof(CRXM__IFELSE2(CRX__BOOST_NO_INT64_T, uint32_t, uint64_t)))];
#endif
			//private: ::std::deque<Var>::iterator gIterator__deque;
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
	#if(CRX__VAR__CONFIG__INT_MODE == CRX__VAR__OPTION__INT_MODE__64BIT)
			//uint64_t uIterator__deque;
			//int64_t uIterator__deque;
	#else
			//uint32_t uIterator__deque;
			//int32_t uIterator__deque;
	#endif
			CRX__VAR__ARRAY__SIZE_TYPE uIterator__deque;
#else
			//uint32_t uIterator__varRing;
			//int32_t uIterator__varRing;
			CRX__VAR__ARRAY__SIZE_TYPE uIterator__varRing;
#endif
			bool uIsEnd; //INDEX FOR NON CONTAINERS

//#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			public: gIterator(){}	//NEEDED BECAUSE THE UNORDERED MAP ITERATOR DELETES THIS CONSTRUCTOR
									//	SANE PROBLEM OCCURS WITH IF SortedVarKHash_SortedVarKHashIterator
									//	IS USED.
			public: ~gIterator(){} //FROM COMPILER WHEN USED unordered_map:
									//	"'crx::Var_VarIterator_Data::~Var_VarIterator_Data(void)': function was 
									//			implicitly deleted because a data member invokes a deleted or
									//			inaccessible function 
									//			'crx::Var_VarIterator_Data::gIterator::~gIterator(void)'"
//#endif
		}gIterator;
		union gData
		{
			union uCollection
			{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
				::crx::ClassUnorderedMap<::std::string, Var>::t * CRX_NOT_MINE uUnorderedMap;
#else
				CRX__VAR__KHash * CRX_NOT_MINE uKHash;
#endif
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
				::std::deque<Var> * uDeque;
#else
				//NOT USEFUL BECAUSE THE VarRing IS CURRENTLY HELD WITHIN Var, AND NOT A POITNER IN IT.
				//Crx_VarRing * uVarRing;
#endif
			}uCollection;
		}gData;
	}Var_VarIterator_Data;
	class Var_VarIterator_DummyStructure
	{
		/*
		private: Var * CRX_NOT_MINE gVar;
		private: Var_VarIterator_Data gData;
		private: bool gIsVoid;
		private: int gType;
		private: bool gIsInEraseMode;
		*/
		public: Var * CRX_NOT_MINE gVar;
		public: Var_VarIterator_Data gData;
		public: bool gIsVoid;
		public: int gType;
	};
	template<bool T> class Var_VarIterator;
	template<bool T_bool>
			class Var_VarIterator_Info
		{};
	template<> 
			class Var_VarIterator_Info<true>
	{
		public: typedef Var const t;
		public: typedef Var_VarIterator<false> t2;
	};
	template<> 
			class Var_VarIterator_Info<false>
	{
		public: typedef Var t;
		public: typedef Var_VarIterator_DummyStructure t2;
	};
	template<bool T> 
			class Var_VarIterator
	{
		friend class Var;
		
		private: typename Var_VarIterator_Info<T>::t * CRX_NOT_MINE gVar;
		private: Var_VarIterator_Data gData;
		private: bool gIsVoid;
		private: int gType;


		public: Var_VarIterator(typename Var_VarIterator_Info<T>::t * pVar, 
				bool pIsToGetEnd = false) : gVar(pVar), gIsVoid(false)
		{
			this->gType = CRX__VAR__GET_TYPE1(pVar);

			switch(this->gType)
			{
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					this->gData.gData.uCollection.uUnorderedMap = pVar->gData.uHashTable.gUnorderedMap;

					if(!pIsToGetEnd)
					{
						//this->gData.gIterator.uIterator__unorderedMap = this->gData.gData.uCollection.uUnorderedMap->begin();
						new (&(CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData)))
								::crx::ClassUnorderedMap<::std::string, Var>::t::iterator(
								this->gData.gData.uCollection.uUnorderedMap->begin());
					}
					else
					{
						//this->gData.gIterator.uIterator__unorderedMap = this->gData.gData.uCollection.uUnorderedMap->end();
						new (&(CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData)))
								::crx::ClassUnorderedMap<::std::string, Var>::t::iterator(
								this->gData.gData.uCollection.uUnorderedMap->end());
					}
#else
					this->gData.gData.uCollection.uKHash = pVar->gData.uHashTable.gKHash;
	#if(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_HASH_TABLE_SORTED)
					new (&(CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData))) CRX__VAR__KHASH__ITERATOR();
	#endif
					if(!pIsToGetEnd)
					{
						CRX__VAR__KHash_getIteratorStart(pVar->gData.uHashTable.gKHash,
								CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData));
					}
					else
					{
						CRX__VAR__KHash_getIteratorEnd(pVar->gData.uHashTable.gKHash,
								CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData));
					}
#endif
					break;
				}
				case CRX__VAR__TYPE_ARRAY:
				{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					this->gData.gData.uCollection.uDeque = pVar->gData.uArray.gDeque;

					if(!pIsToGetEnd)
					{
						//this->gData.gIterator.uIterator__deque = pVar->gData.uArray.gDeque->begin();
						this->gData.gIterator.uIterator__deque = 0;
					}
					else
					{
						//this->gData.gIterator.uIterator__deque = pVar->gData.uArray.gDeque->end();
						this->gData.gIterator.uIterator__deque = pVar->gData.uArray.gDeque->size();
					}
#else
					//this->gData.gData.uCollection.uVarRing = &(pVar->gData.uArray.gVarRing);

					if(!pIsToGetEnd)
						{this->gData.gIterator.uIterator__varRing = 0;}
					else
					{
						this->gData.gIterator.uIterator__varRing = crx_varRing_getLength(
								CRX__VAR__GET_VARRING(pVar));
					}
#endif

					break;
				}
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
				{
					if(!pIsToGetEnd)
						{this->gData.gIterator.uIsEnd = false;}
					else
						{this->gData.gIterator.uIsEnd = true;}

					break;
				}
				default:
					{CRX__BOOST_ASSERT(false);}
			}
		}

		public: Var_VarIterator(Var_VarIterator & pVarIterator) : 
				gVar(pVarIterator.gVar), gData(pVarIterator.gData),
				gIsVoid(pVarIterator.gIsVoid),
				gType(pVarIterator.gType)
			{}
		/* THIS IS NOT MEANT TO EXIST WHEN T IS false.
				ALLOW ASSIGNMENT OF ITERATOR TO CONSTANT ITERATOR, BUT NOT THE OTHER WAY AROUND.
				ALSO NOTE THAT DEFAULT CONSTRUCTOR IS ASSUMED CREATED.
		*/
		public: Var_VarIterator(typename Var_VarIterator_Info<T>::t2 & pVarIterator) : 
				gVar(pVarIterator.gVar), gData(pVarIterator.gData),
				gIsVoid(pVarIterator.gIsVoid),
				gType(pVarIterator.gType)
			{}

		public: Var_VarIterator & operator++()
		{
			if(this->gIsVoid)
				{return *this;}

			if(CRX__VAR__GET_TYPE1(this->gVar) == this->gType)
			{
				switch(this->gType)
				{
					case CRX__VAR__TYPE_HASH_TABLE:
					{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
						if(this->gData.gData.uCollection.uUnorderedMap == 
								this->gVar->gData.uHashTable.gUnorderedMap)
							{CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData)++;}
						else
							{this->gIsVoid = true;}
#else
						if(this->gData.gData.uCollection.uKHash == 
								this->gVar->gData.uHashTable.gKHash)
						{
							CRX__VAR__KHASH__INCREMENT_ITERATOR(this->gData.gData.uCollection.uKHash,
									CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData));
						}
						else
							{this->gIsVoid = true;}
#endif
						break;
					}
					case CRX__VAR__TYPE_ARRAY:
					{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
						if((this->gData.gData.uCollection.uDeque ==
										this->gVar->gData.uArray.gDeque) &&
								(this->gData.gIterator.uIterator__deque <
										this->gData.gData.uCollection.uDeque->size()))
							{this->gData.gIterator.uIterator__deque++;}
						else
							{this->gIsVoid = true;}
#else
						if(this->gData.gIterator.uIterator__varRing <
								static_cast<CRX__VAR__ARRAY__SIZE_TYPE>(
										crx_varRing_getLength(CRX__VAR__GET_VARRING(this->gVar))))
							{this->gData.gIterator.uIterator__varRing++;}
						else
							{this->gIsVoid = true;}
#endif

						break;
					}
					case CRX__VAR__TYPE_STRING:
					case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
					case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
					case CRX__VAR__TYPE_EMULATED_INT:
#endif
					case CRX__VAR__TYPE_DOUBLE:
					case CRX__VAR__TYPE_BOOL:
					case CRX__VAR__TYPE_POINTER:
					case CRX__VAR__TYPE_NULL:
					case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
					case CRX__VAR__TYPE_ERROR:
#endif
					{
						if(!this->gData.gIterator.uIsEnd)
							{this->gData.gIterator.uIsEnd = true;}
						else
							{this->gIsVoid = true;}

						break;
					}
					default:
					{
						CRX__BOOST_ASSERT(false);
					}
				}
			}
			else
				{this->gIsVoid = true;}

			return *this;
		}

		/*
			WARNING: This operator is not to be used to test for equality
					between iterators. It does not work as expected. The
					sole purpose of this operator is to halt an iterator loop.
					Its effective name is "isToProceedWithLoop()"
					If you need to test for actual equality, use 
					Var_VarIterator::isEqualTo(). 
		*/
		public: bool operator!=(const Var_VarIterator & pVarIterator) const
		{
			if((CRX__VAR__GET_TYPE1(this->gVar) == this->gType) &&
					(this->gType == pVarIterator.gType) &&
					(this->gVar == pVarIterator.gVar) &&
					!this->gIsVoid && !pVarIterator.gIsVoid)
			{
				switch(this->gType)
				{
					case CRX__VAR__TYPE_HASH_TABLE:
					{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
						if((this->gData.gData.uCollection.uUnorderedMap ==
								this->gVar->gData.uHashTable.gUnorderedMap) &&
								(this->gData.gData.uCollection.uUnorderedMap ==
								pVarIterator.gData.gData.uCollection.uUnorderedMap))
						{
							return (CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData) != 
									CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(pVarIterator.gData));
						}
						else
							{return false;}
#else
						if((this->gData.gData.uCollection.uKHash == 
								this->gVar->gData.uHashTable.gKHash) && 
							(this->gData.gData.uCollection.uKHash ==
								pVarIterator.gData.gData.uCollection.uKHash))
						{
							return (CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData) !=
									CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(pVarIterator.gData));
						}
						else
							{return false;}
#endif
					}
					case CRX__VAR__TYPE_ARRAY:
					{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
						if((this->gData.gData.uCollection.uDeque ==
										this->gVar->gData.uArray.gDeque) &&
								(this->gData.gData.uCollection.uDeque ==
										pVarIterator.gData.gData.uCollection.uDeque) &&
								(this->gData.gIterator.uIterator__deque <=
										this->gData.gData.uCollection.uDeque->size()) &&
								(pVarIterator.gData.gIterator.uIterator__deque <=
										this->gData.gData.uCollection.uDeque->size()))
						{
							return (this->gData.gIterator.uIterator__deque !=
									pVarIterator.gData.gIterator.uIterator__deque);
						}
						else
							{return false;}
#else
						if((this->gVar == pVarIterator.gVar) &&
								(this->gData.gIterator.uIterator__varRing <=
										static_cast<CRX__VAR__ARRAY__SIZE_TYPE>(
										crx_varRing_getLength(CRX__VAR__GET_VARRING(this->gVar)))) &&
								(pVarIterator.gData.gIterator.uIterator__varRing <=
										static_cast<CRX__VAR__ARRAY__SIZE_TYPE>(
										crx_varRing_getLength(CRX__VAR__GET_VARRING(this->gVar)))))
						{
							return (this->gData.gIterator.uIterator__varRing !=
									pVarIterator.gData.gIterator.uIterator__varRing);
						}
						else
							{return false;}
#endif
					}
					case CRX__VAR__TYPE_STRING:
					case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
					case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
					case CRX__VAR__TYPE_EMULATED_INT:
#endif
					case CRX__VAR__TYPE_DOUBLE:
					case CRX__VAR__TYPE_BOOL:
					case CRX__VAR__TYPE_POINTER:
					case CRX__VAR__TYPE_NULL:
					case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
					case CRX__VAR__TYPE_ERROR:
#endif
						{return (this->gData.gIterator.uIsEnd != pVarIterator.gData.gIterator.uIsEnd);}
					default:
						{CRX__BOOST_ASSERT(false); return false;}
				}
			}
			else
				{return false;}
		}
		Var operator*() const;
		
		public: size_t removeElementsAndUpdateSelf(size_t pWidth)
		{
			if(this->gIsVoid || (pWidth == 0) ||
					(CRX__VAR__GET_TYPE1(this->gVar) != this->gType))
				{return 0;}

			switch(this->gType)
			{
				case CRX__VAR__TYPE_HASH_TABLE:
				{
					size_t tRemainingWidth = pWidth;

#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					if(this->gData.gData.uCollection.uUnorderedMap == 
							this->gVar->gData.uHashTable.gUnorderedMap)
					{
						::crx::ClassUnorderedMap<::std::string, Var>::t::iterator tIterator = 
								this->gData.gData.uCollection.uUnorderedMap.end();

						while((tRemainingWidth > 0) && 
								(CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData) != tIterator))
						{
							CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData) = 
									this->gData.gData.uCollection.uUnorderedMap.erase(
									CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData));
							tRemainingWidth = tRemainingWidth - 1;
						}
					}
					else
						{this->gIsVoid = true;}
#else
					if(this->gData.gData.uCollection.uKHash == 
							this->gVar->gData.uHashTable.gKHash)
					{
						CRX__VAR__KHASH__ITERATOR tKhiter /*= ?*/;

						CRX__VAR__KHash_getIteratorEnd(this->gData.gData.uCollection.uKHash, tKhiter);

						while((tRemainingWidth > 0) && 
								(CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData) != tKhiter))
						{
							char const * tKey = CRX__VAR__KHASH__GET_KEY_FROM_ITERATOR(
									this->gData.gData.uCollection.uKHash,
									CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData));

							CRX__VAR__KHASH__INCREMENT_ITERATOR(this->gData.gData.uCollection.uKHash,
									CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData));
							CRX__VAR__KHash_removeElementAt(this->gData.gData.uCollection.uKHash, 
									tKey);
							tKey = NULL;
							tRemainingWidth = tRemainingWidth - 1;
						}
					}
					else
						{this->gIsVoid = true;}
#endif
					return (pWidth - tRemainingWidth);
				}
				case CRX__VAR__TYPE_ARRAY:
				{
					size_t tWidth = 0;
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					if((this->gData.gData.uCollection.uDeque ==
									this->gVar->gData.uArray.gDeque) &&
							(this->gData.gIterator.uIterator__deque <
									this->gData.gData.uCollection.uDeque->size()))
					{
						if((this->gData.gIterator.uIterator__deque + pWidth) <= 
								this->gVar->gData.uArray.gDeque.size())
							{tWidth = pWidth;}
						else
						{
							tWidth = this->gVar->gData.uArray.gDeque.size() - 
									this->gData.gIterator.uIterator__deque;
						}

						this->gData.gData.uCollection.uDeque->erase(
								this->gData.gIterator.uIterator__deque,
								this->gData.gIterator.uIterator__deque + tWidth);

						/*this->gData.gIterator.uIterator__deque = 
								this->gData.gIterator.uIterator__deque + tWidth;*/
					}
					else
						{this->gIsVoid = true;}
#else
					if(this->gData.gIterator.uIterator__varRing <
							static_cast<CRX__VAR__ARRAY__SIZE_TYPE>(
							crx_varRing_getLength(CRX__VAR__GET_VARRING(this->gVar))))
					{
						if((this->gData.gIterator.uIterator__varRing + pWidth) <=
								crx_varRing_getLength(CRX__VAR__GET_VARRING(this->gVar)))
							{tWidth = pWidth;}
						else
						{
							tWidth = crx_varRing_getLength(CRX__VAR__GET_VARRING(this->gVar)) - 
									this->gData.gIterator.uIterator__varRing;
						}

						crx_varRing_removeElements(CRX__VAR__GET_VARRING(this->gVar),
								this->gData.gIterator.uIterator__varRing, tWidth);

						/*this->gData.gIterator.uIterator__varRing = 
								this->gData.gIterator.uIterator__varRing + tWidth;*/
					}
					else
						{this->gIsVoid = true;}
#endif
					return tWidth;
				}
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
				{
					if(!this->gData.gIterator.uIsEnd)
					{
						this->gData.gIterator.uIsEnd = true;

						if(this->gVar->setType(Var::TYPE__NIL))
							{return 1;}
						else
							{return 0;}
					}
					else
					{
						this->gIsVoid = true;

						return 0;
					}
				}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
		}
		public: bool removeElementAndUpdateSelf()
			{return (this->removeElementsAndUpdateSelf(1) > 0);}

		public: size_t advanceSelfBy(size_t pNumberOfSteps)
		{
			if(this->gIsVoid || (pNumberOfSteps == 0) ||
					(CRX__VAR__GET_TYPE1(this->gVar) != this->gType))
				{return 0;}

			switch(this->gType)
			{
				case CRX__VAR__TYPE_HASH_TABLE:
				{
					size_t tRemainingWidth = pNumberOfSteps;

#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					if(this->gData.gData.uCollection.uUnorderedMap == 
							this->gVar->gData.uHashTable.gUnorderedMap)
					{
						::crx::ClassUnorderedMap<::std::string, Var>::t::iterator tIterator = 
								this->gData.gData.uCollection.uUnorderedMap.end();

						while((tRemainingWidth > 0) && 
								(CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData) != tIterator))
						{
							CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData)++;
							tRemainingWidth = tRemainingWidth - 1;
						}
					}
					else
						{this->gIsVoid = true;}
#else
					if(this->gData.gData.uCollection.uKHash == 
							this->gVar->gData.uHashTable.gKHash)
					{
						CRX__VAR__KHASH__ITERATOR tKhiter /*= ?*/;

						CRX__VAR__KHash_getIteratorEnd(this->gData.gData.uCollection.uKHash, tKhiter);

						while((tRemainingWidth > 0) && 
								(CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData) != tKhiter))
						{
							CRX__VAR__KHASH__INCREMENT_ITERATOR(this->gData.gData.uCollection.uKHash,
									CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData));
							tRemainingWidth = tRemainingWidth - 1;
						}
					}
					else
						{this->gIsVoid = true;}
#endif
					return (pNumberOfSteps - tRemainingWidth);
				}
				case CRX__VAR__TYPE_ARRAY:
				{
					size_t tWidth = 0;
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					if((this->gData.gData.uCollection.uDeque ==
									this->gVar->gData.uArray.gDeque) &&
							(this->gData.gIterator.uIterator__deque <
									this->gData.gData.uCollection.uDeque->size()))
					{
						if((this->gData.gIterator.uIterator__deque + pNumberOfSteps) <= 
								this->gVar->gData.uArray.gDeque.size())
							{tWidth = pNumberOfSteps;}
						else
						{
							tWidth = this->gVar->gData.uArray.gDeque.size() - 
									this->gData.gIterator.uIterator__deque;
						}

						this->gData.gIterator.uIterator__deque = 
								this->gData.gIterator.uIterator__deque + tWidth;
					}
					else
						{this->gIsVoid = true;}
#else
					if(this->gData.gIterator.uIterator__varRing <
							crx_varRing_getLength(CRX__VAR__GET_VARRING(this->gVar)))
					{
						if((this->gData.gIterator.uIterator__varRing + pNumberOfSteps) <=
								crx_varRing_getLength(CRX__VAR__GET_VARRING(this->gVar)))
							{tWidth = pNumberOfSteps;}
						else
						{
							tWidth = crx_varRing_getLength(CRX__VAR__GET_VARRING(this->gVar)) - 
									this->gData.gIterator.uIterator__varRing;
						}
						this->gData.gIterator.uIterator__varRing = 
								this->gData.gIterator.uIterator__varRing + tWidth;
					}
					else
						{this->gIsVoid = true;}
#endif
					return tWidth;
				}
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
				{
					if(!this->gData.gIterator.uIsEnd)
					{
						this->gData.gIterator.uIsEnd = true;

						return 1;
					}
					else
					{
						this->gIsVoid = true;

						return 0;
					}
				}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
		}

		public: ~Var_VarIterator()
		{
			switch(this->gType)
			{
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					typedef ::crx::ClassUnorderedMap<::std::string, Var>::t::iterator Tewrewrwe; 

					CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData).~Tewrewrwe();
#else
					CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData).~CRX__VAR__KHASH__ITERATOR();
#endif
					break;
				}
				case CRX__VAR__TYPE_ARRAY:
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{break;}
				default:
				{
					CRX__BOOST_ASSERT(false);
				}
			}
		}
	};

		#pragma endregion Var Generic Iterators //}

	#pragma endregion Var iterators //}

	
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
	typedef ::std::deque<Var>::iterator DequeIterator;
	typedef ::std::deque<Var>::const_iterator ConstantDequeIterator;
	class Var_DeuqueIterator
	{
		::std::deque<Var>::iterator gIterator;
		
		public: Var_DeuqueIterator(::std::deque<Var>::iterator pIterator)
			{this->gIterator = pIterator;}

		public: operator DequeIterator()
			{return this->gIterator;}
		public: operator ConstantDequeIterator()
			{return this->gIterator;}
	};
	class Var_DeuqueConstantIterator
	{
		::std::deque<Var>::const_iterator gIterator;
		
		public: Var_DeuqueConstantIterator(::std::deque<Var>::const_iterator pIterator)
			{this->gIterator = pIterator;}
		public: Var_DeuqueConstantIterator(::std::deque<Var>::iterator pIterator)
			{this->gIterator = pIterator;}

		public: operator ConstantDequeIterator()
			{return this->gIterator;}
	};
	
	typedef ::std::deque<Var>::iterator Var_ArrayStlIterator;
	typedef ::std::deque<Var>::const_iterator Var_ArrayConstantStlIterator;
#else
	/*
	Var_VarRingIterator AND Var_VarRingConstantIterator SUFFER FROM AMBIGUITY PROBLEMS WITH
		NULL. FOR EXAMPLE,
				Var_VarRingConstantIterator tVarRingConstantIterator = NULL;
		IS AMBIGUOUS BECAUSE THE COMPILER DOES NOT KNOW WHETHER TO TREAT NULL AS
		"Var const *" "Var *". TO SOLVE THE ISSUE SUPPORT FOR nullptr WAS ADDED, BUT FOR OLDER
		COMPILERS, ONE WOULD HAVE TO USE
				Var_VarRingConstantIterator tVarRingConstantIterator = static_cast<Var *>(NULL);
		WHEN IT COMES TO CLIENT CODE, THIS SIMPLY MEANT THAT THEY COULD NOT SIMPLY PASS NULL
		TO VAR FUNCTIONS THAT EXPECT Var::ArrayStlIterator pStartIterator. WHEN IT COMES TO
		THE RETURN, HOWEVER, THIS WOULD NOT BE THE CLIENT'S PROBLEM, BECAUSE THE CLIENT
		WOULD BE EXPECTED TO US Var_ArrayStlIterator WHICH WOULD EVALUTE TO "Var *",
		NOT TO "Var_VarRingIterator"
				
		NOTE THAT THE CODE BARELY LIVED FOR A DAY BEFORE RELIAZING THAT IT WAS NOT NECESSARY. 
		BUT IT IS KEPT FOR REFERENCE.
	*/
	/*typedef Var * VarPointer;
	typedef Var const * ConstantVarPointer;
	class Var_VarRingIterator
	{
		Var * gIterator;
		
		public: Var_VarRingIterator(Var * pIterator)
		{
			this->gIterator = pIterator;
		}

		public: operator VarPointer()
		{
			return this->gIterator;
		}
		/*
		//DISABLED TO AVOID AMBIGUITY WITH NULL. FOR EXAMPLE:
		//				tVarRingIterator != NULL
		//	BECOMES AMBIGUOUS IF THE FOLLOWING IS ENABLED.
		public: operator ConstantVarPointer()
		{
			return this->gIterator;
		}* /
	};
	class Var_VarRingConstantIterator
	{
		Var const * gIterator;

		public: Var_VarRingConstantIterator(Var const * pIterator)
			{this->gIterator = pIterator;}
		public: Var_VarRingConstantIterator(Var * pIterator)
			{this->gIterator = pIterator;}

	#if(__cplusplus <= 199711L)
		public: Var_VarRingConstantIterator(::std::nullptr_t r)
			{this->gIterator = NULL;}
	#endif

		public: operator ConstantVarPointer()
		{
			return this->gIterator;
		}
	};
	
	typedef Var * Var_ArrayStlIterator;
	typedef Var const * Var_ArrayConstantStlIterator;*/
#endif
	
	CRX__LIB__PRIVATE_FUNCTION() void var_private_destruct(Var * pVar);
	CRX__LIB__PRIVATE_FUNCTION() void var_private_copyConstruct(Var * pVar, Var const * pVar2);
	
	CRX__LIB__PUBLIC_FUNCTION() void crx_varRing_constructFromDeque(Crx_VarRing * pThis, 
			::std::deque<Var> * pDeque);
	CRX__LIB__PUBLIC_FUNCTION() void crx_varRing_constructFromDeque2(Crx_VarRing * pThis, 
			::std::deque<Var> * pDeque, bool pArePossiblyCreatedVarsThreadPossible);

	#ifdef CRX__BOOST_NO_INT64_T
	union Var_BitsOfDouble
	{
		double uDouble;
		unsigned char uBytes[8];
	};
	#endif

	typedef struct VarVarArgsKeyValue
	{
		char const * CRX_NOT_MINE gString;
		Var gVar;
	}VarVarArgsKeyValue;
	

	const bool VAR__IS_CHAR_SIGNED = (char)-1 < 0;
	#if(defined(CRX__VAR__ERROR_MODE__ERROR_CODE) && (CRX__VAR__CONFIG__ERROR_MODE == CRX__VAR__ERROR_MODE__ERROR_CODE))
	CRX_THREAD_LOCAL_POD int gVar_errorCode = 0;
	#endif


	#ifdef CRX__BOOST_NO_INT64_T
	//WARNING: THIS IS FOR BIG ENDIAN BY BYTE, NOT WORD
	static bool var_isMachineUsingBigEndian()
	{
		union
		{
			uint32_t i;
			char c[4];
		} vBits = {0x01020304};

		return (vBits.c[0] == 1);
	}
	CRX__BOOST_FORCEINLINE Var_BitsOfDouble var_getBitsOfDouble(uint32_t pHighBits, uint32_t pLowBits)
	{
		//VC6 Var_BitsOfDouble vBitsOfDouble = {};
		Var_BitsOfDouble vBitsOfDouble; CRX__SET_TO_ZERO(Var_BitsOfDouble, vBitsOfDouble);
		
		if(var_isMachineUsingBigEndian()) //big endian
		{
			vBitsOfDouble.uBytes[0] = (pHighBits >> 24) & 0xFF;
			vBitsOfDouble.uBytes[1] = (pHighBits >> 16) & 0xFF;
			vBitsOfDouble.uBytes[2] = (pHighBits >> 8) & 0xFF;
			vBitsOfDouble.uBytes[3] = pHighBits & 0xFF;
			vBitsOfDouble.uBytes[4] = (pLowBits >> 24) & 0xFF;
			vBitsOfDouble.uBytes[5] = (pLowBits >> 16) & 0xFF;
			vBitsOfDouble.uBytes[6] = (pLowBits >> 8) & 0xFF;
			vBitsOfDouble.uBytes[7] = pLowBits & 0xFF;
		}
		else	//little endian
		{
			vBitsOfDouble.uBytes[7] = (pHighBits >> 24) & 0xFF;
			vBitsOfDouble.uBytes[6] = (pHighBits >> 16) & 0xFF;
			vBitsOfDouble.uBytes[5] = (pHighBits >> 8) & 0xFF;
			vBitsOfDouble.uBytes[4] = pHighBits & 0xFF;
			vBitsOfDouble.uBytes[3] = (pLowBits >> 24) & 0xFF;
			vBitsOfDouble.uBytes[2] = (pLowBits >> 16) & 0xFF;
			vBitsOfDouble.uBytes[1] = (pLowBits >> 8) & 0xFF;
			vBitsOfDouble.uBytes[0] = pLowBits & 0xFF;
		}

		return vBitsOfDouble;
	}
	CRX__BOOST_FORCEINLINE bool var_isDoubleEqualTo(double pDouble, uint32_t pHighBits, uint32_t pLowBits)
	{
		//VC6 Var_BitsOfDouble vBitsOfDouble = {};
		Var_BitsOfDouble vBitsOfDouble; CRX__SET_TO_ZERO(Var_BitsOfDouble, vBitsOfDouble);


		vBitsOfDouble.uDouble = pDouble;

		if(var_isMachineUsingBigEndian())
		{
			return ((vBitsOfDouble.uBytes[0] == ((pHighBits >> 24) & 0xFF)) &&
					(vBitsOfDouble.uBytes[1] == ((pHighBits >> 16) & 0xFF)) &&
					(vBitsOfDouble.uBytes[2] == ((pHighBits >> 8) & 0xFF)) &&
					(vBitsOfDouble.uBytes[3] == (pHighBits & 0xFF)) &&
					(vBitsOfDouble.uBytes[4] == ((pLowBits >> 24) & 0xFF)) &&
					(vBitsOfDouble.uBytes[5] == ((pLowBits >> 16) & 0xFF)) &&
					(vBitsOfDouble.uBytes[6] == ((pLowBits >> 8) & 0xFF)) &&
					(vBitsOfDouble.uBytes[7] == (pLowBits & 0xFF)));
		}
		else
		{
			return ((vBitsOfDouble.uBytes[7] == ((pHighBits >> 24) & 0xFF)) &&
					(vBitsOfDouble.uBytes[6] == ((pHighBits >> 16) & 0xFF)) &&
					(vBitsOfDouble.uBytes[5] == ((pHighBits >> 8) & 0xFF)) &&
					(vBitsOfDouble.uBytes[4] == (pHighBits & 0xFF)) &&
					(vBitsOfDouble.uBytes[3] == ((pLowBits >> 24) & 0xFF)) &&
					(vBitsOfDouble.uBytes[2] == ((pLowBits >> 16) & 0xFF)) &&
					(vBitsOfDouble.uBytes[1] == ((pLowBits >> 8) & 0xFF)) &&
					(vBitsOfDouble.uBytes[0] == (pLowBits  & 0xFF)));
		}
	}
	#endif
	
	CRX__LIB__PUBLIC_FUNCTION() Var::iterator begin(Var & pVar);
	CRX__LIB__PUBLIC_FUNCTION() Var::iterator end(Var & pVar);
	CRX__LIB__PUBLIC_FUNCTION() Var::const_iterator cbegin(Var const & pVar);
	CRX__LIB__PUBLIC_FUNCTION() Var::const_iterator cend(Var const & pVar);

	template<bool T> 
	Var Var_VarIterator<T>::operator*() const
	{
		if(this->gIsVoid)
			{return Var(Var::Undefined());}

		if(CRX__VAR__GET_TYPE1(this->gVar) == this->gType)
		{
			switch(this->gType)
			{
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					if((this->gData.gData.uCollection.uUnorderedMap ==
							this->gVar->gData.uHashTable.gUnorderedMap))
					{
						return Var((*(CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData))).first);
					}
					else
					{
						const_cast<Var_VarIterator<T> *>(this)->gIsVoid = true;

						return Var(Var::Undefined());
					}
#else
					if(this->gData.gData.uCollection.uKHash == 
							this->gVar->gData.uHashTable.gKHash)
					{
						return Var(CRX__VAR__KHASH__GET_KEY_FROM_ITERATOR(this->gData.gData.uCollection.uKHash, 
								CRX__VAR__VAR_ITERATOR_DATA___MAP_ITERATOR2(this->gData)));
					}
					else
					{
						const_cast<Var_VarIterator<T> *>(this)->gIsVoid = true;

						return Var(Var::Undefined());
					}
#endif
				}
				case CRX__VAR__TYPE_ARRAY:
				{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					if((this->gData.gData.uCollection.uDeque == this->gVar->gData.uArray.gDeque) &&
							(this->gData.gIterator.uIterator__deque <
									this->gData.gData.uCollection.uDeque->size()))
						{return Var(this->gData.gIterator.uIterator__deque);}
					else
					{
						const_cast<Var_VarIterator<T> *>(this)->gIsVoid = true;

						return Var(Var::Undefined());
					}
#else
					if(this->gData.gIterator.uIterator__varRing <
							static_cast<CRX__VAR__ARRAY__SIZE_TYPE>(
							crx_varRing_getLength(&(this->gVar->gData.uArray.gVarRing))))
					{
						/*return ::std::pair<::crx::Var const, typename ::crx::Var_VarIterator_Info<T>::t>(
								Var(this->gData.gIterator.uIterator__varRing), 
								Var(*(crx_varRing_get(&(this->gVar->gData.uArray.gVarRing), 
										this->gData.gIterator.uIterator__varRing))));*/
						return this->gData.gIterator.uIterator__varRing;
					}
					else
					{
						const_cast<Var_VarIterator<T> *>(this)->gIsVoid = true;

						return Var(Var::Undefined());
					}
#endif
				}
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
				{
					if(!this->gData.gIterator.uIsEnd)
						{return Var(true);}
					else
					{
						const_cast<Var_VarIterator<T> *>(this)->gIsVoid = true;

						return Var(Var::Undefined());
					}
				}
				default:
					{CRX__BOOST_ASSERT(false); return Var(Var::Undefined());}
			}
		}
		else
		{
			const_cast<Var_VarIterator<T> *>(this)->gIsVoid = true;

			return Var(Var::Undefined());
		}
	}

	template<bool T> 
	size_t Var_StringIterator<T>::operator*() const
	{
		/*
		NOTE THAT IT IS NOT POSSIBLE FOR THE STRING TO HAVE A SIZE EQUAL TO 
				"CRX__VAR__MACHINE_UNSIGNED_INT_MAX" EVEN ON 32BIT, BECAUSE 
				THE STRING WOULD BE PART OF THE VAR, AND THE VAR HAS AN 
				OVERHEAD LARGER THAN ZERO.
		*/
		if(this->gIsVoid)
			{return CRX__VAR__MACHINE_UNSIGNED_INT_MAX;}

		if(CRX__VAR__GET_TYPE1(this->gVar) == CRX__VAR__TYPE_STRING)
		{
			if(this->gIndex < this->gVar->getSize())
				{return this->gIndex;}
			else
			{
				const_cast<Var_StringIterator<T> *>(this)->gIsVoid = true;

				return CRX__VAR__MACHINE_UNSIGNED_INT_MAX;
			}
		}
		else
		{
			const_cast<Var_StringIterator<T> *>(this)->gIsVoid = true;

			return CRX__VAR__MACHINE_UNSIGNED_INT_MAX;
		}
	}

	
	/*template<I1>
	class VarN : Var
	{
		protected: virtual bool gIsFixedSize()
			{return true;}
		private: unsigned char _gBytes[I1];

		public: VarN() : Var(&_gBytes, I1)
			{}
		template<I2>
		public: operator=(const & VarN<I2>)
		{
			
		}
	};*/
	
	/*SUPPORT FOR JSON LIKE SYNTAX FOR PRE C++11 COMPILERS*/
	CRX__LIB__PUBLIC_FUNCTION() VarVarArgsKeyValue var_varArgsKeyValue(char const * pString, Var const pVar);
	CRX__LIB__PUBLIC_FUNCTION() VarVarArgsKeyValue var_varArgsKeyValue();
	CRX__LIB__PUBLIC_FUNCTION() Var var_varArgs(VarVarArgsKeyValue pVarVarArgsKeyValue__1, ...);
	CRX__LIB__PUBLIC_FUNCTION() Var var_varArgs(Var pVar__1, ...);
	CRX__LIB__PUBLIC_FUNCTION() Var var_varArgs(bool pIsToBeThreadPossible, VarVarArgsKeyValue pVarVarArgsKeyValue__1, ...);
	CRX__LIB__PUBLIC_FUNCTION() Var var_varArgs(bool pIsToBeThreadPossible, Var pVar__1, ...);
}



#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .cpp.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/CPP.H/crx/Var.cpp.h"
#endif
#pragma pop_macro("CRX__LIB__MODE")

#endif