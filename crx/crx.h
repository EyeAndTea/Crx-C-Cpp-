#if(!defined(CRX__CRX__h__))
#define CRX__CRX___h__
#pragma once
#if(defined(_MSC_VER) && (_MSC_VER < 1400))
#include "Crx/H/crx/crx_oldCompilers.h"
#else


#if(defined(BOOST_VERSION))
	#if((BOOST_VERSION >= 104700) || defined(__cplusplus) || defined(BOOST_NO_STDLIB_CONFIG))
		#include "boost/config.hpp"
	#endif
#endif

/*
NOTES ABOUT BOOST:
	- BOOST IS USED FOR NORMALIZATION ACROSS COMPILERS. ELSEWHERE IT MAY BE USED FOR NORMALIZATION WITH
			STL CODE, OR NORMALIZATION OF PLATFORM FUNCTIONS.
	- BOOST 1.34.1 IS THE LAST VERSION TO APPEAR WORKING WITH VS6. HOWEVER, LATER VERSIONS MIGHT STILL WORK.
	- AVAILABILITY OF DOCUMENTATION ONLINE BEGAN WITH BOOST 1.31.0  (January 26th, 2004). HOWEVER THEY
			DOCUMENTATION EXIST IN BOOST DOWNLOADS SINCE 1.25.1 AND PROBABLY EARLIER.
	- IMPORTANT PARTS OF BOOST:
		- CONFIG:
			- THIS ALLOWS NORMALIZATION ACROSS C++ VERSIONS. IT ALLOWS DETECTING OF C++ FEATURES
			- THIS DOES EXIST IN BOOST 1.34.1.
			- THE MACROS IN THIS ARE VERY TRICKY BECAUSE INSTEAD OF SPECIFYING WHETHER A C++ FEATURE EXISTS,
					THEY SPECIFY WHETHER IT DOES NOT. THIS MEANS THAT IT IS NOT SUFFICIENT TO CHECK
					FOR THE MACRO, BUT YOU ALSO HAVE TO CHECK FOR WHEN THE MACRO WAS INTRODUCED.
			- BECAUSE DOCUMENTATION BEGAN WITH 1.31.0,  THE RELIABILITY OF MACROS BELOW IS ONLY
					CHECKED STARTING FROM THAT VERSIONS GENERALLY. FURTHER MORE, CRX__BOOST NORMALIZED 
					MACROS
					ARE DONE WITH THAT IN MIND. THIS MEANS THEY CAN GIVE WRONG RESULTS FOR EARLIER
					VERSIONS, BUT SHOULD, AND MUST, STILL ALLOW THE CODE TO COMPILE SAFELY.
			- MACROS THAT START WITH "BOOST_NO_CXX11_" BEGAN WITH 1.50.0. BEFORE THAT THE MACROS
					STARTED WITH "BOOST_NO_0X" WHICH BEGAN WITH 1.40.0. HOWEVER SOME MACROS,
					WHEN EXCLUDING THE PREFIX, HAD ALIASES IN PRIOR VERSION UNDER THE PREFIX
					"BOOST_NO". FOR EXAMPLES, 
					"BOOST_NO_CXX11_HDR_INITIALIZER_LIST" WHEN IT WAS INTRODUCED IN 1.50.0
					REPLACED "BOOST_NO_0X_HDR_INITIALIZER_LIST" WHICH WAS INTRODUCED IN 
					1.40.0 AND ALSO REPLACED "BOOST_NO_INITIALIZER_LISTS" WHICH WAS INTRODUCED
					IN 1.38.0
					"BOOST_NO_CXX11_RVALUE_REFERENCES" DID NOT HAVE AN ALIAS UNDER "BOOST_NO_0X"
					AND INSTEAD WAS CALLED "BOOST_NO_RVALUE_REFERENCES"
					
					
					BOOST MACROS STARTING WITH "BOOST_NO" FOR C++0x WERE INTRODUCED IN 1.36.0
					AND BEFORE THAT THERE WERE OTHER MACROS FOR C++0x THAT STARTED WITH
					"BOOST_HAS" AND WERE INTRODUCED IN 1.35.0
					
					FOR EASE OF IMPLEMENTATION, THIS LIBRARY DEPENDS ON THE "BOOST_NO_CXX11_",
					BUT MIGHT END UP ADDING SUPPORT FOR THE OLDER MACROS IF USEFUL. REMEMBER THAT
					WITHOUT SUPPORT, THIS LIBRARY MUST STILL PROVIDE RESULTS THAT ARE SAFE FOR
					COMPILATION.
			- BOOST CONFIG TRIES TO DETECT THE STL LIBRARY AND THIS CAN TRIGGER SYNTAX ERRORS IF THE
					COMPILER IS NOT A C++ COMPILER. IN VERSIONS 1.47.0 THIS APPEARS TO HAVE
					BEEN FIXED. IN EARLIER VERSIONS, ONE COULD AVOID THE PROBLEM BY DEFINING THE
					MACRO BOOST_NO_STDLIB_CONFIG WHEN CONFIGURING BOOST. THE PROBLEM HAPPENS IN 
					BOOST FILE "select_stdlib_config.hpp" INCLUDED BY config.hpp AT THE ROOT OF
					BOOST. THIS FILE, AND POSSIBLY THE PROBLEM, WAS NOT ALWAYS THERE. IT WAS
					INTRODUCED IN V1.25.0. SUPPORT FOR THE MACRO BOOST_NO_STDLIB_CONFIG
					WAS ALSO INTRODUCED THEN.
					THIS STL DETECTION CAN ALSO TRIGGER ERRORS ON WINDOWS WHEN USING windows.h. IT
					THE STL DETECTION INCLUDES PARTS OF THE STL, AND IT APPEARS THAT NO INCLUDING
					OF THE STL SHOULD HAPPEN BEFORE INCLUDING windows.h
			- RELIABILITY OF MACROS USED:
				- BOOST_VERSION: 	THIS WAS AVAILABLE SINCE 1.25.0 INSIDE "version.hpp".
						BEFORE THAT IT WAS AVAILABLE IN "config.hpp" STARTING FROM 1.21.2.
						BEFORE THAT IT WAS NOT AVAILABLE AT ALL.
				- BOOST_NO_INT64_T: THIS WAS AVAILABLE SINCE 1.21.2 AND POSSIBLY EARLIER.
				- BOOST_NO_CXX11_DELETED_FUNCTIONS: THIS WAS DEFINED IN BOOST 1.51.0
				- BOOST_NO_CXX11_HDR_INITIALIZER_LIST: THIS WAS DEFINED IN 1.50.0
				- BOOST_NO_CXX11_RVALUE_REFERENCES: THIS WAS DEFINED IN 1.51.0
				- BOOST_EXPLICIT_OPERATOR(): THIS WAS DEFINED IN 1.55.0 (NOT SUPPORTED YET BY CRX)
				- BOOST_NO_CXX11_THREAD_LOCAL: THIS WAS DEFINED IN 1.62.0 (NOT SUPPORTED YET BY CRX)
					- THIS IS ABOUT THE KEYWORD thread_local
					- ON xcode, THIS IS AVAILABLE FROM VERSION 8.
					- ON IOS, THIS IS AVAILABLE FROM VERSION 9, EVEN IF USING XCODE 8.
					- FOR BACKWARD COMPATIBILITY, ALTERNATIVES EXIST THAT INCLUDE
						- __thread
						- __declspec(thread): WINDOWS. THIS SEEMS TO WORK ON VS6. HOWEVER, IF TARGETTING
								PRE WINDOWS VISTA, USING THIS WILL CAUSE ERRORS FOR A DLL THAT WILL BE 
								LOADED USING LoadLibrary()
					- BOOST SUPPORT FOR THREAD LOCAL VARIABLES CAUSE BACK TO 1.34.0 AND POSSIBLY BEFORE. 
							HOWEVER, BOOST'S MECHANISM CAN NOT BE CONVERTED TO APPEAR LIKE A KEYWORD, AND
							NEITHER THE IDEA OF USING A NORMALIZING MACRO FUNCTION WORKS BECAUSE YOU WOULD
							NEED TO ADD OTHER CODE IN DIFFERENT OTHER PLACES LIKE THE PLACE WHERE A THREAD
							FIRST RUNS. ALSO NOTE THAT BOOST MECHANISM WORKS FOR NON STATIC VARIABLES ALSO,
							WHICH IS NOT A PROBLEM.
				- BOOST_NO_CXX11_HDR_UNORDERED_MAP
					- BOOST_HAS_TR1_UNORDERED_MAP  	 	1.34.0	[DEPRECATED 1.54.0]	
							CONTINUES TO BE AVAILABLE TO CURRENT VERSION 1.76.0
					- BOOST_NO_STD_UNORDERED		  		1.38.0	[DEPRECATED 1.50.0]
							CONTINUES TO BE AVAILABLE TO CURRENT VERSION 1.76.0
							(NOTE: THIS WAS MISPELLD IN THE DOCUMENTATION AS BOOST_NO_STD_UNORDERD)
					- BOOST_NO_0X_HDR_UNORDERED_MAP 		1.40.0	[DEPRECATED 1.50.0]
							CONTINUES TO BE AVAILABLE TO CURRENT VERSION 1.76.0
					- BOOST_NO_CXX11_HDR_UNORDERED_MAP	1.50.0 	(replaces BOOST_NO_0X_HDR_UNORDERED_MAP)
							IN 1.54.0 REPLACES THE INVERSE OF BOOST_HAS_TR1_UNORDERED_MAP
							CONTINUES TO BE AVAILABLE TO CURRENT VERSION 1.76.0
					- BOOST_NO_CXX11_HDR_UNORDERED_SET	1.50.0 	(replaces BOOST_NO_STD_UNORDERED)
							CONTINUES TO BE AVAILABLE TO CURRENT VERSION 1.76.0
					- BOOST_NO_CXX11_STD_UNORDERD			1.51.0
							MANUALLY CHECKED 1.51.0 AND DID NOT FIND THIS MACRO DEFINED ANYWHERE, BUT
									IT WAS REFERED TO IN A #if STATEMENT OR SIMILAR.
							IN 1.53.0 REPLACED BOOST_NO_STD_UNORDERED
							IN CURENT VERSION, 1.76.0, THE MACRO HAS THE EXPECTED SPELLING
											BOOST_NO_CXX11_STD_UNORDERED 
									AND THE WRONG SPELLING DOES NOT APPEAR ANYWHERE.
				- BOOST_NO_LONG_LONG: THIS WAS DEFINED IN 1.36.0
				- BOOST_NO_CXX11_UNRESTRICTED_UNION: THIS WAS DEFINED IN 1.73.0 OR POSSIBLE 1.72.0 WHICH I WAS
						UNABLE TO CHECK FROM THE ONLINE DOCS, AND DID NOT BOTHER TO CHECK THE ITS CODE EITHER.
				- BOOST_HAS_STDINT_H: THIS WAS FIRST DEFINED IN 1.25.0
		- PREDEF:
			- THIS ALLOWS NORMALIZATION ACROSS 
		- ASSERT:
			- BOOST_ASSERT()
				- THIS LIKE assert() WITH SOME EXTRAS WHEN CERTAIN OPTIONS ARE SET. THIS CAN ALSO BE DISABLED
						INDEPENDENTLY OF assert()
				- DEFINED IN 1.56.0
*/


//THE FOLLOWING ARE FOR C++ CLASS DEFINITIONS
#define CRX_PUBLIC
#define CRX_PRIVATE
#define CRX_PROTECTED
#define CRX_PUBLIC_STATIC
#define CRX_PRIVATE_STATIC
#define CRX_PROTECTED_STATIC
#define CRX_PUBLIC_VIRTUAL
#define CRX_PRIVATE_VIRTUAL
#define CRX_PROTECTED_VIRTUAL
/*
- IMPLEMENTS ONE OF THE TWO EXCEPTION LAWS OF OWNERSHIP AS DEFINED IN MY STANDRD.
- INDICATES THAT WHATEVER THE POINTER POINTS TO IS NOT THE CLASS RESPONSIBILITY TO CLEAN UP.
		"CLASS" IS AS DEFINED IN MY STANDARD.
- FOR POINERS ONLY. CAN BE USED WITH *, OR ** ONLY, AND WITH &*, OR &** ONLY.
*/
#define CRX_NOT_MINE
/*
- IMPLEMENTS ONE OF THE TWO EXCEPTION LAWS OF OWNERSHIP AS DEFINED IN MY STANDRD.
- FOR POINTERS ONLY. CAN BE USED WITH *, OR ** ONLY. AND WITH &*, OR &** ONLY.
*/
#define CRX_PASSING
/*
- IMPLEMENTS NULL SEMANTICS AS DEFINED IN MY STANDRD.
- INDICATES THAT THE POINTER FUNCTION PARAMETER CAN NOT BE NULL.
- PARSING RULES IS SAME AS THAT OF const. EXAMPLES:
	- int * CRX_NOT_NULL * pX
			pX IS A POINTER THAT MAY BE NULL, BUT POITNING TO A POINTER THAT MAY NOT BE NULL
			AND IS POINTING TO AN INT.
	- int * CRX_NOT_NULL * CRX_NOT_NULL pX
			pX IS A POINTER THAT MAY NOT BE NULL, AND IS POITNING TO A POINTER THAT MAY NOT
			BE NULL AND IS POINTING TO AN INT.
*/
#define CRX_NOT_NULL
/*
- INDICATES THE DEFAULT VALUE FOR A PARAMETER. THIS IS NEEDED IN:
	- C++: CPP AND CPP.H FILES BECAUSE THE C++ LANGUAGE DOES NOT ALLOW DEFINING THE DEFAULT
			VARIABLES OF THE PARAMETES IN BOTH THE DECLERATION AND DEFINITION.
	- C: C AND H FILES BECAUSE THE C LANGUAGE DOES NOT ALLOW SPECIFYING DEAULTS AT ALL.
*/
#define CRX_DEFAULT(...)
/*
THE FOLLOWING IS FOR USE INSTEAD OF #pragma region
EXAMPLE:
#if CRX_REGION(section name)
#endif

NOTE: THS WAS REJECTED BECAUSE IT INTRODUCES A COGNITIVE LOAD WHEN TRYING TO PROPERLY INDENT IT. REMEMBER
		THAT REGION INDENTATIONS, MEANING #pragma region, DO NOT FOLLOW OTHER PREPROCESSOR DIRECTIVES INDENTATIONS.
		KEEPING THIS HERE, HOWEVER, IN CASE I FORGET AGAIN WHY I REJECTED THIS APPROACH.
*/
//#define CRX_REGION(...) 1
/*
FOR C ONLY

THE FOLLOWING CONSTRUCT GUARANTEED TO ALSO WELL ON ROUGHLY C89. MORE PRECISELY, IT
IS C89 THAT VISUAL STUDIO 6 AND UP UNDERSTAND, AND GCC C89 MODE WITHOUT -pedantic UNDERSTANDS.
IT IS ALSO GUARANTEED TO WORK VISUAL STUDIO 6 C++ FLAVOR.

EXAMPLE. INSTEAD OF
			for(int tI = 0; tI < 10; tI++)
				{doSomething(tI);}
		WRITE
			CRX_FOR(int tI = 0, tI < 10, tI++)
				doSomething(tI);
			CRX_ENDFOR
		OR
			CRX_FOR(int tI = 0, tI < 10, tI++)
				{doSomething(tI);}
			CRX_ENDFOR
*/
#define CRX_FOR(A, B, ...) \
{ \
	A; \
	for(; B; __VA_ARGS__) \
	{

#define CRX_ENDFOR \
	} \
}
/*
FOR C ONLY

THE FOLLOWING CONSTRUCT GUARANTEED TO ALSO WELL ON ROUGHLY C89. MORE PRECISELY, IT
IS C89 THAT VISUAL STUDIO 6 AND UP UNDERSTAND, AND GCC C89 MODE WITHOUT -pedantic UNDERSTANDS.

THIS IS NEEDED WHEN A SCOPE, THAT WHICH DEFINES
THE SCOPE OF A VARIABLE, AS DEFINED IN MY STANDARD, HAS A BLOCK BEFORE ITS VARIABLE DEFINITION BLOCK SUCH
AS A META BLOCK OR A GUARD BLOCK.

EXAMPLE. INSTEAD OF
				void doSomething(char * pChar)
				{
					if(pChar == NULL)
						{return;}

					int vX = 4;
					
					return pChar + vX;
				}
		DO
				void doSomething(char * pChar)
				{
					CRX_SCOPE_META
					if(pChar == NULL)
						{return;}

					CRX_SCOPE
					int vX = 4;
					
					return pChar + vX;
					CRX_SCOPE_END
				}

*/
#define CRX_SCOPE_META {
#define CRX_SCOPE {
#define CRX_SCOPE_END }}

#pragma region BOOST //{
//CRX__BOOST_NO_INT64_T
#if(!defined(BOOST_VERSION) || ((BOOST_VERSION < 102102) || defined(BOOST_NO_INT64_T)))
	#define CRX__BOOST_NO_INT64_T
#endif
//CRX__BOOST_FORCEINLINE
#if(defined(BOOST_VERSION) && (BOOST_VERSION >= 104900))
	#define CRX__BOOST_FORCEINLINE BOOST_FORCEINLINE
#else
	/*THE FOLLOWING IS BASED ON THE CODE FROM BOOST 1.49.0
		LATER UPDATED WITH BOOST 1.82.0. RESULTING IN THE ONLY CHANGE, 
		THE "__IBMCPP__" PART BEING ADDED
	*/
	#if(defined(_MSC_VER))
		#define CRX__BOOST_FORCEINLINE __forceinline
	#elif(defined(__GNUC__) && (__GNUC__ > 3))
		#define CRX__BOOST_FORCEINLINE inline __attribute__ ((always_inline))
	#elif(defined(__IBMCPP__) && defined(__COMPILER_VER__) && defined(__MVS__) && (__COMPILER_VER__ > 0x42010000) && defined(__IBM_ATTRIBUTES))
		#define CRX__BOOST_FORCEINLINE inline __attribute__ ((__always_inline__))
	#else
		#define CRX__BOOST_FORCEINLINE inline
	#endif
#endif
//CRX__BOOST_NO_CXX11_HDR_UNORDERED_MAP
#if(defined(BOOST_VERSION) && (BOOST_VERSION >= 104000))
	#if(BOOST_VERSION >= 105000)
		#if(defined(BOOST_NO_CXX11_HDR_UNORDERED_MAP))
			#define CRX__BOOST_NO_CXX11_HDR_UNORDERED_MAP
		#endif
	#else
		#if(defined(BOOST_NO_0X_HDR_UNORDERED_MAP))
			#define CRX__BOOST_NO_CXX11_HDR_UNORDERED_MAP
		#endif
	#endif
#else
	#define CRX__BOOST_NO_CXX11_HDR_UNORDERED_MAP
#endif
//CRX__BOOST_NO_CXX11_DELETED_FUNCTIONS
#if(!defined(BOOST_VERSION) || ((BOOST_VERSION < 105100) || defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)))
	#define CRX__BOOST_NO_CXX11_DELETED_FUNCTIONS
#endif
//CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
#if(!defined(BOOST_VERSION) || ((BOOST_VERSION < 105100) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)))
	#define CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
#endif
//CRX__BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#if(!defined(BOOST_VERSION) || ((BOOST_VERSION < 105000) || defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)))
	#define CRX__BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#endif
//CRX__BOOST_ASSERT
#if(!defined(BOOST_VERSION) || (BOOST_VERSION < 105600))
	#if(defined(BOOST_DISABLE_ASSERTS))
		#define CRX__BOOST_ASSERT(T)  ((void)0)
	#else
		#define CRX__BOOST_ASSERT(T)  assert(T)
	#endif
#else
	#define CRX__BOOST_ASSERT(T)  BOOST_ASSERT(T)
#endif
//CRX__BOOST_NOEXCEPT	
/*
	WARNING: CRX__BOOST_NOEXCEPT ONLY GUARANTEES TO INFORM THE COMPILER THAT A FUNCTION 
			DOES NOT THROW EXCEPTIONS, IF COMPILER SUPPORTS IT. INFORM THE COMPILER, MEANS THAT TEMPLATES
			CAN CHECK AT COMPILE TIME TO READ THIS INFO. THE MACRO, HOWEVER, DOES NOT GUARANTEE AN
			ENFORCEMENT OF NOT THROWING EXCEPTION LINKE throw()* USED TO DO IN (< C++17). MOREOVER THE
			MACRO DOES NOT GUARANTEE THAT NO SUCH ENFORCEMENTS TAKE PLACE. IT IS ESSENTIALLY JUST A 
			WRAPPER TO THE INCONSISTANT nothrow IN (>= C++11). nothrow IN (< C++17) BEHAVES LIKE
			throw()*. IN (>= C++17) THE BEHAVIOR IS DIFFERENT, AND INSTEAD OF CODE TERMINATING IF A
			FUNCTION THROWS BY CALLING std::terminate(), OTHER THINGS MIGHT HAPPEN BECAUSE THE 
			COMPILER CALLS "std::unexpected()" LIKE throw() DOES.
		
	*: throw() HERE IS EXPLICITLY WITHOUT PARAMETERS.

	UPDATE: DUE TO THE ABOVE THE CODE IS ILL DEFINED. PERHAPS IN THE FUTURE I DEFINE 
			CRX__BOOST_NOEXCEPT ONLY FOR (>= C++17), BUT I WOULD HAVE TO CALL IT SOMETHING ELSE.
	UPDATE: UNFORTUANETLY THERE IS NO RELIALE WAY TO DETECT (>= C++17) AS RECENTLY AS VS2017.
*/
/*
#if(!defined(BOOST_VERSION) || (BOOST_VERSION < 104700))
	#define CRX__BOOST_NOEXCEPT
	//#define CRX__BOOST_NOEXCEPT_IF(Predicate)
	//#define CRX__BOOST_NOEXCEPT_EXPR(Expression) false
#else
	#if(BOOST_VERSION < 104900)
		#if(defined(BOOST_NO_NOEXCEPT))
			#define CRX__BOOST_NOEXCEPT
			//#define CRX__BOOST_NOEXCEPT_IF(Predicate)
			//#define CRX__BOOST_NOEXCEPT_EXPR(Expression) false
		#else
			#define CRX__BOOST_NOEXCEPT  noexcept
			//#define CRX__BOOST_NOEXCEPT_IF(Predicate)  noexcept((Predicate))
			//#define CRX__BOOST_NOEXCEPT_EXPR(Expression)  noexcept((Expression))
		#endif
	#else
		#define CRX__BOOST_NOEXCEPT  BOOST_NOEXCEPT
		//#define CRX__BOOST_NOEXCEPT_IF(Predicate) BOOST_NOEXCEPT_IF(Predicate)
		//#define CRX__BOOST_NOEXCEPT_EXPR(Predicate)  BOOST_NOEXCEPT_EXPR(Predicate)
	#endif
#endif
*/
#if(!defined(BOOST_VERSION) || (BOOST_VERSION < 105500))
	//THE FOLLOWING IS BASED ON BOOST V1.69

	/*
		NOTES:
			- BOOST V1.51 IS THE EARLIER I COULD FIND USE OF BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS.
					HOWEVER, I DID NOT DO A THROUGH CHECK, AND IT MIGHT HAVE EXISTED BEFORE.
			- CURRENTLY FORCED TO RELY ON BOOST_NOEXCEPT WHICH I FAILED TO ADOPT DUE TO ITS DEFINITION.
					IN THE FUTURE MIGHT HAVE TO COME UP WITH A PRIVATE WORK AROUND FOR THIS PARTICULAR
					CASE ONLY.
	*/
	#if((BOOST_VERSION >= 105100) && !defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS))

		#define CRX__BOOST_EXPLICIT_OPERATOR_BOOL() \
				CRX__BOOST_FORCEINLINE explicit operator bool () const \
					{return !this->operator! ();}

		#if(defined(BOOST_NOEXCEPT))
			#define CRX__BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT() \
					CRX__BOOST_FORCEINLINE explicit operator bool () const BOOST_NOEXCEPT \
						{return !this->operator! ();}

			#if(!defined(BOOST_WORKAROUND) || !BOOST_WORKAROUND(BOOST_GCC, < 40700))
				#define CRX__BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL() \
						CRX__BOOST_FORCEINLINE BOOST_CONSTEXPR explicit operator bool () const \
								BOOST_NOEXCEPT \
							{return !this->operator! ();}
			#else
				#define CRX__BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL() \
						CRX__BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()
			#endif
		#endif
	#else
		#if(!((defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x530)) && !defined(BOOST_NO_COMPILER_CONFIG)))
			#if(defined(__cplusplus))
namespace Crx
{
	struct _UnspecifiedBool
	{
		struct OPERATORS_NOT_ALLOWED;
				#if !defined(_MSC_VER) && !defined(__IBMCPP__)
		static void true_value(OPERATORS_NOT_ALLOWED*) {}
				#else
		// MSVC and VACPP are too eager to convert pointer to functions to void * even though they 
		// 		should not
		void true_value(OPERATORS_NOT_ALLOWED*) {}
				#endif
	};
				#if !defined(_MSC_VER) && !defined(__IBMCPP__)
	typedef void (*_UnspecifiedBoolFunctionPointer)(_UnspecifiedBool::OPERATORS_NOT_ALLOWED*);
				#else
	typedef void (_UnspecifiedBool::*_UnspecifiedBoolFunctionPointer)(_UnspecifiedBool::OPERATORS_NOT_ALLOWED*);
				#endif
}
			#endif

			#define CRX__BOOST_EXPLICIT_OPERATOR_BOOL() \
					CRX__BOOST_FORCEINLINE operator Crx::_UnspecifiedBoolFunctionPointer () const \
					{ \
						return (!this->operator! () ? &Crx::_UnspecifiedBool::true_value : \
								(Crx::_UnspecifiedBoolFunctionPointer)0); \
					}

			#if(defined(BOOST_NOEXCEPT))
				#define CRX__BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT() \
						CRX__BOOST_FORCEINLINE operator Crx::_UnspecifiedBoolFunctionPointer() \
								const BOOST_NOEXCEPT \
						{\
							return (!this->operator! () ? &Crx::_UnspecifiedBool::true_value : \
									(Crx::_UnspecifiedBoolFunctionPointer)0);\
						}
				#define CRX__BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL() \
						CRX__BOOST_FORCEINLINE BOOST_CONSTEXPR operator Crx::_UnspecifiedBoolFunctionPointer() \
								const BOOST_NOEXCEPT\
						{\
							return (!this->operator! () ? &Crx::_UnspecifiedBool::true_value : \
									(Crx::_UnspecifiedBoolFunctionPointer)0); \
						}
			#endif
		#else
			#define CRX__BOOST_EXPLICIT_OPERATOR_BOOL() \
					CRX__BOOST_FORCEINLINE operator bool () const \
						{return !this->operator! ();}
						
			#if(defined(BOOST_NOEXCEPT))
				#define CRX__BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT() \
						CRX__BOOST_FORCEINLINE operator bool () const BOOST_NOEXCEPT \
							{return !this->operator! ();}
				#define CRX__BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL() \
						CRX__BOOST_FORCEINLINE BOOST_CONSTEXPR operator bool () const BOOST_NOEXCEPT \
							{return !this->operator! ();}
			#endif
		#endif
	#endif
#else
	#define CRX__BOOST_EXPLICIT_OPERATOR_BOOL() BOOST_EXPLICIT_OPERATOR_BOOL()
	#define CRX__BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT() BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()
	#define CRX__BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL() BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL()
#endif
//CRX__BOOST_NO_LONG_LONG
#if(!defined(BOOST_VERSION) || ((BOOST_VERSION < 103600) || defined(BOOST_NO_LONG_LONG)))
	#define CRX__BOOST_NO_LONG_LONG
#endif
//CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
#if(defined(BOOST_VERSION) && (BOOST_VERSION >= 107300))
	#if(defined(BOOST_NO_CXX11_UNRESTRICTED_UNION))
		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	#endif
#else
	//THE FOLLOWING IS REFERENCED FROM BOOST V1.73
	/*#if defined __CUDACC__
		//NVIDIA CUDA C++ compiler for GPU "boost/config/compiler/nvcc.hpp" */
	#if(defined(__GCCXML__))
		/*GCC-XML emulates other compilers, it has to appear first here! "boost/config/compiler/gcc_xml.hpp"*/
		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	#elif(defined(_CRAYC))
		//EDG based Cray compiler "boost/config/compiler/cray.hpp"
		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	#elif(defined(__COMO__))
		//Comeau C++ "boost/config/compiler/comeau.hpp"
		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	#elif(defined(__PATHSCALE__)) //&& (__PATHCC__ >= 4))
		//PathScale EKOPath compiler (has to come before clang and gcc) "boost/config/compiler/pathscale.hpp"
		#if((__PATHCC__ < 6) 
			#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
		#else
			//  Clang C++ emulates GCC, so it has to appear early. "boost/config/compiler/clang.hpp"
			/* "When compiling with clang before __has_extension was defined,
				even if one writes 'defined(__has_extension) && __has_extension(xxx)',
				clang reports a compiler error. So the only workaround found is:"*/
			#ifndef __has_extension
				#define __has_extension CRX__has_feature_543786873
			#endif

			#if !CRX__has_feature_543786873(cxx_unrestricted_unions)
				#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
			#endif
		#endif
	/*#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
		//  Intel "boost/config/compiler/intel.hpp" */
	#elif(defined(__clang__) && !defined(__ibmxl__))
		//  Clang C++ emulates GCC, so it has to appear early. "boost/config/compiler/clang.hpp"
		/* "When compiling with clang before __has_extension was defined,
			even if one writes 'defined(__has_extension) && __has_extension(xxx)',
			clang reports a compiler error. So the only workaround found is:"*/
		#ifndef __has_extension
			#define __has_extension CRX__has_feature_543786873
		#endif

		#if !CRX__has_feature_543786873(cxx_unrestricted_unions)
			#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
		#endif
	#elif(defined(__DMC__))
		//  Digital Mars C++ "boost/config/compiler/digitalmars.hpp"
		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	#elif(defined(__DCC__) && !defined(__EDG_VERSION__))
		//Wind River Diab C++ "boost/config/compiler/diab.hpp"
		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	/*#elif defined __DCC__ && defined(__EDG_VERSION__)
		//Wind River Diab C++ "boost/config/compiler/diab.hpp" (AN 'EDGE' COMPILER)*/
	#elif(defined(__PGI))
		//Portland Group Inc. "boost/config/compiler/pgi.hpp"
		#if(((__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) < 50100) || !defined(BOOST_GCC_CXX11))
			#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
		#endif
	#elif(defined(__GNUC__) && !defined(__ibmxl__))
		//  GNU C++: #   define BOOST_COMPILER_CONFIG "boost/config/compiler/gcc.hpp"
		#if(((__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) < 50100) || !defined(BOOST_GCC_CXX11))
			#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
		#endif
	#elif(defined(__KCC))
		//Kai C++ T_COMPILER_CONFIG "boost/config/compiler/kai.hpp"
		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	/*#elif defined __sgi
		//SGI MIPSpro C++ "boost/config/compiler/sgi_mipspro.hpp"  (AN 'EDGE' COMPILER)*/
	/*#elif defined __DECCXX
		//Compaq Tru64 Unix cxx "boost/config/compiler/compaq_cxx.hpp"  (AN 'EDGE' COMPILER)*/
	/*#elif defined __ghs
		//Greenhills C++ "boost/config/compiler/greenhills.hpp"  (AN 'EDGE' COMPILER)*/
	#elif(defined(__CODEGEARC__))
		//CodeGear - must be checked for before Borland "boost/config/compiler/codegear.hpp"
		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	#elif(defined(__BORLANDC__))
		//Borland "boost/config/compiler/borland.hpp"
		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	#elif(defined(__MWERKS__))
		//Metrowerks CodeWarrior "boost/config/compiler/metrowerks.hpp"
		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	#elif(defined(__SUNPRO_CC))
		//Sun Workshop Compiler C++ "boost/config/compiler/sunpro_cc.hpp"
		#if((__SUNPRO_CC < 0x5130) || (__cplusplus < 201100))
			#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
		#endif
	#elif(defined(__HP_aCC) && !defined(__EDG__))
		//HP aCC "boost/config/compiler/hp_acc.hpp"
		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	/*#elif(defined(__HP_aCC) && defined(__EDG__))
		//HP aCC "boost/config/compiler/hp_acc.hpp"  (AN 'EDGE' COMPILER)*/
	#elif(defined(__MRC__) || defined(__SC__))
		//MPW MrCpp or SCpp "boost/config/compiler/mpw.hpp"
		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	#elif(defined(__IBMCPP__) && defined(__COMPILER_VER__) && defined(__MVS__))
		//IBM z/OS XL C/C++ "boost/config/compiler/xlcpp_zos.hpp"
		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	/*#elif defined(__ibmxl__)
		//IBM XL C/C++ for Linux (Little Endian) "boost/config/compiler/xlcpp.hpp" */
	#elif(defined(__IBMCPP__))
		//IBM Visual Age or IBM XL C/C++ for Linux (Big Endian) "boost/config/compiler/vacpp.hpp"
		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	#elif(defined(_MSC_VER))
	//  Microsoft Visual C++ "boost/config/compiler/visualc.hpp"
	//  Must remain the last #elif since some other vendors (Metrowerks, for
	//  example) also #define _MSC_VER
		#if((_MSC_VER < 1310) || (_MSC_FULL_VER < 190023026))
			#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
		#endif
	#else
		//NOTE ALL 'EDGE' COMPILERS "boost/config/compiler/common_edg.hpp" ALSO HAVE 
		//		CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION DEFINED

		#define CRX__BOOST_NO_CXX11_UNRESTRICTED_UNION
	#endif
#endif
//CRX__BOOST_HAS_STDINT_H
#if(defined(BOOST_VERSION) && (BOOST_VERSION >= 102500))
	#if(defined(BOOST_HAS_STDINT_H))
		#define CRX__BOOST_HAS_STDINT_H
	#endif
#endif
#if(!defined(CRX__BOOST_HAS_STDINT_H) && (!defined(BOOST_VERSION) || ((BOOST_VERSION <= 104200) && defined(_MSC_VER))))
	//THIS BRANCH IS ILL DEFINED GIVEN THE PREMISE OF CRX TREATMENT OF BOOST, BUT IT
	//		EXTENDS THE LIFE OF OLDER BOOST. V1.42.0 IS ROUGHLY JUST BEFORE WHEN MSVC 2010 WAS RELEASED
	/* THE FOLLOWING IS BASED ON V1.8.2, BUT IGNORED
			boost\config\detail\posix_features.hpp
			boost\config\detail\suffix.hpp
			boost\config\stdlib\msl.hpp
	*/
	#if(defined(__CUDACC__))
	#elif(defined(__GCCXML__))
		// GCC-XML emulates other compilers, it has to appear first here!
	#elif(defined(_CRAYC))
		#define CRX__BOOST_CRAY_x 9867657 // Arbitrary number
		#define CRX__BOOST_CRAY_APPEND(MACRO) CRX__BOOST_CRAY_APPEND_INTERNAL(MACRO)
		#define CRX__BOOST_CRAY_APPEND_INTERNAL(MACRO) CRX__BOOST_CRAY_##MACRO

		#if(BOOST_CRAY_x == BOOST_CRAY_APPEND(_RELEASE_PATCHLEVEL))
			#define CRX__BOOST_CRAY_VERSION (_RELEASE_MAJOR * 10000 + _RELEASE_MINOR * 100 + 99)
		#else
			#define CRX__BOOST_CRAY_VERSION (_RELEASE_MAJOR * 10000 + _RELEASE_MINOR * 100 + _RELEASE_PATCHLEVEL)
		#endif
		
		#if(CRX__BOOST_CRAY_VERSION >= 80500)
			#if(__cplusplus >= 201103L)
				#define CRX__BOOST_HAS_STDINT_H
			#endif
		#endif

		#undef CRX__BOOST_CRAY_x
		#undef CRX__BOOST_CRAY_APPEND
		#undef CRX__BOOST_CRAY_APPEND_INTERNAL
		#undef CRX__BOOST_CRAY_VERSION
	#elif(defined(__PATHSCALE__) && (__PATHCC__ >= 4))
		// PathScale EKOPath compiler (has to come before clang and gcc)
		#if(__PATHCC__ >= 6)
			#if __has_include(<stdint.h>)
				#define CRX__BOOST_HAS_STDINT_H
			#endif
		#elif(__PATHCC__ >= 4)
			#define CRX__BOOST_HAS_STDINT_H
		#endif
	#elif(defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC))
		#if(!(defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1500) && (defined(_MSC_VER) || defined(__GNUC__))))
			#if(defined(_MSC_VER) && (_MSC_VER >= 1600))
				#define CRX__BOOST_HAS_STDINT_H
			#endif
		#endif
	#elif(defined(__clang__) && !defined(__ibmxl__) && !defined(__CODEGEARC__))
		#if(defined(__clang_major__) && (__clang_major__ >= 4) && defined(__has_include))
			#if(__has_include(<stdint.h>))
				#  define CRX__BOOST_HAS_STDINT_H
			#endif
		#endif
	#elif(defined(__DMC__))
		#define CRX__BOOST_HAS_STDINT_H
	#elif(defined(__CODEGEARC__))
		#if(!defined(__clang__))
			#ifdef _WIN32
				#define CRX__BOOST_HAS_STDINT_H
			#endif
		#endif
	#elif(defined(__BORLANDC__))
		#if((__BORLANDC__ >= 0x561) && defined(_WIN32))
			#define CRX__BOOST_HAS_STDINT_H
		#endif
	#elif(defined(__IBMCPP__) && defined(__COMPILER_VER__) && defined(__MVS__))
		#if defined(__C99) || defined(__TR1)
			#define CRX__BOOST_HAS_STDINT_H
		#endif
	#elif(defined(_MSC_VER))
		#if(_MSC_VER >= 1600)
			#define CRX__BOOST_HAS_STDINT_H
		#endif
	#endif

	#if(!defined(CRX__BOOST_HAS_STDINT_H))
		#if(defined(linux) || defined(__linux) || defined(__linux__) || defined(__GNU__) || defined(__GLIBC__)) && !defined(_CRAYC)
			#if(defined(__GLIBC__) && ((__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 1))))
				#if(defined(__GNUC__) || ((__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 5))))
					#define CRX__BOOST_HAS_STDINT_H
				#endif
			#endif
		#elif(defined(sun) || defined(__sun))
			#define CRX__BOOST_HAS_STDINT_H 
		#elif(defined(__hpux))
			#if(defined(__GNUC__) && (__GNUC__ >= 3)) || defined(__HP_aCC)
				#define CRX__BOOST_HAS_STDINT_H
			#endif
		#elif(defined(__CYGWIN__))
			#if(defined(_STDINT_H) || (__GNUC__ > 5))
				#define CRX__BOOST_HAS_STDINT_H
			#endif
		#elif(defined(_WIN32) || defined(__WIN32__) || defined(WIN32))
			#if defined(__MINGW32__) && ((__MINGW32_MAJOR_VERSION > 2) || ((__MINGW32_MAJOR_VERSION == 2) && (__MINGW32_MINOR_VERSION >= 0)))
				#define CRX__BOOST_HAS_STDINT_H
			#endif
		#elif(defined(__HAIKU__) || (defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)) || (defined(__IBMCPP__) || defined(_AIX)) || defined(__VXWORKS__))
			#define CRX__BOOST_HAS_STDINT_H
		#elif defined(__SYMBIAN32__) 
			#if defined(__S60_3X__)
				#define CRX__BOOST_HAS_STDINT_H
			#endif
		#elif defined(__CloudABI__)
			#define CRX__BOOST_HAS_STDINT_H
		#endif
	#endif
#endif
#pragma endregion BOOST //}


//WARNING: IF YOU USE CRX_DISABLE_METHOD() ON AN OVERLOADED FUNCTION, YOU CAN NO LONGER USE 
//		using BaseClass::someMemberFunction; IN A BASE CLASS. THIS IS BECAUSE IN THE PRE C++11 CASE, 
//		THE DISABLED FUNCTION IS MADE PRIVATE, AND THIS CAUSES THE using STATEMENT TO FAIL BECAUSE 
//		SOME OF THE OVERLOADS ARE NOT ACCESSIBLE BECAUSE THEY ARE PRIVATE. 
//
//CRX_DISABLE_METHOD
#ifndef CRX__BOOST_NO_CXX11_DELETED_FUNCTIONS
/* > C++11*/
	//#define CRX_DISABLE_METHOD(pFunctionSignature) pFunctionSignature = delete;
	#define CRX_DISABLE_METHOD(...) __VA_ARGS__ = delete ;
//OR
	//#define CRX_DISABLE_METHOD__START
	//#define CRX_DISABLE_METHOD__END = delete;
#else
/* < C++11 */
	//#define CRX_DISABLE_METHOD(pFunctionSignature) private: pFunctionSignature ;
	#define CRX_DISABLE_METHOD(...) private: __VA_ARGS__ ;
//OR
	//#define CRX_DISABLE_METHOD__START private:
	//#define CRX_DISABLE_METHOD__END ;
#endif
/*
THIS IS MEANT TO BE USED IN .cpp OR .cpp.h FILES ONLY. INDICATE THAT THE
		CLASS MEMBER FUNCTION IS DISABLED.
*/
#define CRX_DISABLED_METHOD(...)

/*#if(defined(_MSC_VER))
	#define CRX_INLINE_FUNCTION __forceinline
#elif(defined(__GNUC__))
	//#define CRX_INLINE_FUNCTION inline __attribute__((__always_inline__))
	#define CRX_INLINE_FUNCTION __attribute__((__always_inline__))
#elif(defined(__CLANG__))
	#if(__has_attribute(__always_inline__))
		//#define CRX_INLINE_FUNCTION inline __attribute__((__always_inline__))
		#define CRX_INLINE_FUNCTION __attribute__((__always_inline__))
	#else
		//#define CRX_INLINE_FUNCTION inline
	#endif
#else
	//#define CRX_INLINE_FUNCTION inline
	#define CRX_INLINE_FUNCTION
#endif

#if(defined(__cplusplus))
	//also this is valid, because extern is default on inline.
	//#define CRX_CODE_SHARED_FUNCTION inline
	//VALID USED ON BOTH DECLARATION AND DEFINITION, EVEN THOUGH NOT MANDATORY ON DECLARATION.
	#define CRX_CODE_SHARED_FUNCTION extern inline

	//VALID USED ON BOTH DECLARATION AND DEFINITION, EVEN THOUGH NOT MANDATOY ON DECLERATION.
	#define CRX_LOCAL_FUNCTION static

	//VALID USED ON BOTH DECLARATION AND DEFINITION, EVEN THOUGH NOT MANDATOY ON EITHER BECAUSE
	//		THIS IS DEFAULT, AND HENCE MEANINGLESS.
	#define CRX_BINARY_SHARED_FUNCTION extern
#endif*/

//IMPORTANT: 	DO NOT USE THE FOLLOWING IF WRITING CRXed CODE. SEE CRX LIB
//				USE OF THE FOLLOWING IS DISCOURAGED
//CRX__C__EXTERN_INLINE_FUNCTION
//CRX__C__INLINE_FUNCTION
//CRX__C__PRIVATE_FUNCTION
//CRX__C__PUBLIC_FUNCTION
//CRX__C__PRIVATE_INLINE_FUNCTION
//CRX__C__PUBLIC_INLINE_FUNCTION
#if(!defined(__cplusplus))
	//#define CRX__C__LOCAL_BUT_GENERATING_FUNCTION
	/*
		CRX__C__EXTERN_INLINE_FUNCTION: AT A MINIMAL, A FUNCTION THAT MIGHT BE INLINED, 
				AND WHOSE ADDRESS CAN BE TAKEN, AND IS AVAILABLE TO OTHER COMPILATION
				UNITS.
		CRX__C__INLINE_FUNCTION: AT A MINIMAL, A FUNCTION THAT MIGHT BE INLINED,
				AND WHOSE ADDRESS CAN NOT BE ASSUMED TO BE TAKABLE.
	*/
	/*C: gnu89    (gnu compiler options:  -std=gnu89)*/
	#if defined(__GNUC_GNU_INLINE__)
		#define CRX__C__EXTERN_INLINE_FUNCTION inline
		#define CRX__C__INLINE_FUNCTION extern inline
	/*C: c99 on gnu compiler    (gnu compiler options:  -std=c99)*/
	#elif defined(__GNUC_STDC_INLINE__)
		#define CRX__C__EXTERN_INLINE_FUNCTION extern inline
		#define CRX__C__INLINE_FUNCTION inline 
	/*C: c89 on msvc compilers*/
	#elif defined(_MSC_VER)
		#define CRX__C__EXTERN_INLINE_FUNCTION extern __inline
		#define CRX__C__INLINE_FUNCTION __inline
	/*C: c99*/
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
		#define CRX__C__EXTERN_INLINE_FUNCTION extern inline
		#define CRX__C__INLINE_FUNCTION inline 
	#endif

	#define CRX__C__PRIVATE_FUNCTION static
	#if(defined(_MSC_VER))
		#define CRX__C__PRIVATE_INLINE_FUNCTION static __inline
	#else
		#define CRX__C__PRIVATE_INLINE_FUNCTION static inline
	#endif
	#define CRX__C__PUBLIC_FUNCTION extern
	#define CRX__C__PUBLIC_INLINE_FUNCTION CRX__C__EXTERN_INLINE_FUNCTION
#endif

/*
THE FOLLOWING IS FOR BOTH C AND C++. THE FOLLOWING IS ONLY FOR "PLAIN OLD DATA" TYPES

WARNING: THE FOLLOWING DOES NOT GUARANTEE THAT THE MECHANISM WILL WORK. FOR EXAMPLE __declspec(thread),
INCLUDING THE NATIVE thread_local, WILL NOT WORK RELIABLY FOR WINDOWS BEFORE WINDOWS VISTA. SEE THE 
COMMENTS EARLIER IN THIS FILE.

<<THE FOLLOWING IS STILL WORK IN PROGRESS>>
*/
//<<WORK IN PROGRESS. DO NOT USE>>
#if(defined(__cplusplus))
	#if(defined(__unix__) || defined(__CYGWIN32__))
		#define CRX_THREAD_LOCAL_POD __thread
	#elif(defined(__MINGW32__) || defined(_WIN32) || defined(_WIN32_) || defined(_WIN32_WCE) || defined(__BORLANDC__)) 
		//#define __declspec(thread)
		#define CRX_THREAD_LOCAL_POD __declspec(thread)
	#elif(defined(BOOST_VERSION) && (BOOST_VERSION >= 106200) && !defined(BOOST_NO_CXX11_THREAD_LOCAL))
		#define CRX_THREAD_LOCAL_POD thread_local
	#else
		#if(defined(BOOST_STATIC_ASSERT)
			#define CRX_THREAD_LOCAL_POD(T) BOOST_STATIC_ASSERT(false);
		#else
			#define CRX_THREAD_LOCAL_POD(T)	<-- thread_local IS NOT SUPPORTED BY THIS COMPILER -->; 
		#endif
	#endif
#else
	#if(defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112) && !defined __STDC_NO_THREADS__)
		#define CRX_THREAD_LOCAL_POD _Thread_local
	#elif(defined(_WIN32) && (defined(_MSC_VER) || defined(__ICL) || defined(__DMC__) ||  defined(__BORLANDC__)))
		#define CRX_THREAD_LOCAL_POD __declspec(thread) 
	#elif(defined(__GNUC__) || defined(__SUNPRO_C) || defined(__xlC__))
		#define CRX_THREAD_LOCAL_POD __thread
	#else
		#if(defined(BOOST_STATIC_ASSERT)
			#define CRX_THREAD_LOCAL_POD(T) BOOST_STATIC_ASSERT(false);
		#else
			#define CRX_THREAD_LOCAL_POD(T)	<-- thread_local IS NOT SUPPORTED BY THIS COMPILER -->; 
		#endif
	#endif
#endif

/*
	- IN C++, static for const  IS DEFAULT
	- IN C, IT IS NOT.
*/
//<<WORK IN PROGRESS. DO NOT USE>>
#define CRX_CONSTANT_VARIABLE static const

//THE FOLLOWING IS FOR C ONLY
//REQUIRES -fvisibility=hidden ON GCC IF NOT USING CRX_DLL_NO_EXPORT_C_FUNCTION
//CRX_DLL_EXPORT_C_FUNCTION
//CRX_DLL_IMPORT_C_FUNCTION
//CRX_DLL_NO_EXPORT_C_FUNCTION
#if(defined _WIN32 || defined __CYGWIN__)
	#if(defined(__GNUC__))
		#define CRX_DLL_EXPORT_C_FUNCTION __attribute__ ((dllexport))
		#define CRX_DLL_IMPORT_C_FUNCTION __attribute__ ((dllimport))
		#define CRX_DLL_NO_EXPORT_C_FUNCTION
	#else
		#define CRX_DLL_EXPORT_C_FUNCTION __declspec(dllexport)
		#define CRX_DLL_IMPORT_C_FUNCTION __declspec(dllimport)
		#define CRX_DLL_NO_EXPORT_C_FUNCTION
	#endif
#else
	#if(defined(__GNUC__) && (__GNUC__ >= 4))
		#define CRX_DLL_EXPORT_C_FUNCTION __attribute__ ((visibility ("default")))
		#define CRX_DLL_IMPORT_C_FUNCTION __attribute__ ((visibility ("default")))
		#define CRX_DLL_NO_EXPORT_C_FUNCTION  __attribute__ ((visibility ("hidden")))
	#else
		#define CRX_DLL_EXPORT_C_FUNCTION
		#define CRX_DLL_IMPORT_C_FUNCTION
		#define CRX_DLL_NO_EXPORT_C_FUNCTION
	#endif
#endif


#pragma region CRXM //{

/*
THE CRX NAME NAME SPACE IS RESERVED FOR NORMAL MACROS, WHILE THE CRXD NAME NAME SPACE IS FOR ABNORMAL MACROS.
ABNORMAL MACROS ALLOW INDIRECT RECURSION. GIVEN THE ABNORMAL MACROS, 'A', 'B' AND 'C'. 'A' CAN CALL 'B' EVEN
IF 'B' CALLS 'A' BACK. HOWEVER 'A' CAN NOT CALL 'A'.
*/

/**/
#define CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL(pFullMacroCall) pFullMacroCall
//#define CRXM__EVAL(pCode) pCode

//USING "CRXM__RESOLVE_MACRO_CALL2", WHICH IS AN OLDER VERSION, IS NOT RECOMMENDED. USE
//		CRXM__RESOLVE_MACRO_CALL INSTEAD, WHICH IS THE NEWER VERSION.
//ELIMINATES COMPILER DIFFERENCES FOR MACROS WITH VARIABLE NUMBER OF ARGUMENTS, HOWEVER DOES NOT
//		ALLOW MACROS WITH VARIABLE NUMBER OF ARGUMENTS TO BE DEFINED BASED ON OTHER MACROS WITH VARIABLE
//		NUMBER OF ARGUMENTS EXCEPT IN MICROSOFT VISUAL C++* DUE TO A BUG THERE IT SEEMS WHICH I DISCOVERED.
//		EXAMPLE:
//				#define A(a, ...) A: (a), B: (__VA_ARGS__)
//				#define B(...) A(__VA_ARGS__)
//
//				B(1, 2, 3, 4)		OUTPUT(NON MSVC): A: (1), B: (2, 3, 4)
//									OUTPUT(MSVC): A: (1, 2, 3, 4), B: ()
//
//		WE COULD USE CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL:
//				#define A(a, ...) A: (a), B: (__VA_ARGS__)
//				#define B(...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL(A(__VA_ARGS__))
//
//				B(1, 2, 3, 4)		OUTPUT(NON MSVC): A: (1), B: (2, 3, 4)
//									OUTPUT(MSVC): A: (1), B: (2, 3, 4)
//
//		BUT THIS IS TEDIOUS, AS IT WOULD HAVE TO BE DONE WHEREVER 'A' IS CALLED TO BE SAFE. OR WE COULD:
//				#define A(a, ...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL(A__CRXDO(a, __VA_ARGS__))
//				#define A__CRXDO(a, ...): (a), B: (__VA_ARGS__)
//				#define B(...) A(__VA_ARGS__)
//
//				B(1, 2, 3, 4)		OUTPUT(NON MSVC): A: (1), B: (2, 3, 4)
//									OUTPUT(MSVC): A: (1), B: (2, 3, 4)
//		
//		OR
//				#define A(a, ...) CRXM__RESOLVE_MACRO_CALL2(A, a, __VA_ARGS__)
//				#define A__CRXDO(a, ...): (a), B: (__VA_ARGS__)
//				#define B(...) A(__VA_ARGS__)
//
//				B(1, 2, 3, 4)		OUTPUT(NON MSVC)	: A: (1), B: (2, 3, 4)
//									OUTPUT(MSVC)		: A: (1), B: (2, 3, 4)
//
//*AS BUT FOR THE MSVC++ BUG MENTIONED EARLIER TO WORK, THE USER MUST USE THE SAME NAME OF THE MACRO FOR THE
//		PARAMETER pMacroName
//		EXAMPLE:
//				#define MY_MACRO(...) CRXM__RESOLVE_MACRO_CALL2(MY_MACRO, __VA_ARGS__)
//				#define MY_MACRO__CRXDO(...) HGFHFG
//
//		EXAMPLE:
//				#define A(a, ...) CRXM__RESOLVE_MACRO_CALL2(A, a, __VA_ARGS__)
//				#define A__CRXDO(a, ...) A2(a, __VA_ARGS__)
//				#define A2(a, ...) CRXM__RESOLVE_MACRO_CALL2(A2, a, __VA_ARGS__)
//				#define A2__CRXDO(a, ...) A[2]: (a), B[2]: (__VA_ARGS__)
//				#define B(...) A(__VA_ARGS__)
//
//				B(1, 2, 3, 4)		OUTPUT(NON MSVC)	: CRXM__RESOLVE_MACRO_CALL2(A2, 1, 2, 3, 4)
//									OUTPUT(MSVC)		: A[2]: (1), B[2]: (2, 3, 4)
//		
//		AN IMPLEMENTATION THAT DOES NOT TRY TO EXPLOIT THE MSVC++ BUG IS:
//		#define CRXM__RESOLVE_MACRO_CALL2(pMacroName, ...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacroName ## __CRXDO(__VA_ARGS__))
//
//UPDATE(IMPORTANT). THE FOLLOWING ALSO WORKS:
//		#define A(a, ...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL(A__CRXDO( a, __VA_ARGS__))
//		#define A__CRXDO(a, ...) A2(a, __VA_ARGS__)
//		#define A2(a, ...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL(A2__CRXDO(a, __VA_ARGS__))
//		#define A2__CRXDO(a, ...) A[2]: (a), B[2]: (__VA_ARGS__)
//		#define B(...) A(__VA_ARGS__)
//
//		B(1, 2, 3, 4)		OUTPUT(NON MSVC)	: A[2]: (1), B[2]: (2, 3, 4)
//							OUTPUT(MSVC)		: A[2]: (1), B[2]: (2, 3, 4)
//
//		HENCE "CRXM__RESOLVE_MACRO_CALL"	BELOW WHICH WOULD BE USED INSTEAD OF CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL
//		AND HAS NO AUTOMATIC '__CRXDO' APPENDING
#define CRXM__RESOLVE_MACRO_CALL2(pMacroName, ...) CRXM__RESOLVE_MACRO_CALL2__DO1(pMacroName, __CRXDO) (__VA_ARGS__)
#define CRXM__RESOLVE_MACRO_CALL2__DO1(A, B) CRXM__RESOLVE_MACRO_CALL2__DO2(A, B)
#define CRXM__RESOLVE_MACRO_CALL2__DO2(A, B) A ## B
#define CRXM__RESOLVE_MACRO_CALL(pFullMacroCall) pFullMacroCall


#define CRXM__GET_NUMBER_OF_ARGUMENTS(...)  CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		CRXM__GET_NUMBER_OF_ARGUMENTS___DO1(__VA_ARGS__, \
		30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
#define CRXM__GET_NUMBER_OF_ARGUMENTS___DO1(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,p30, \
		pN,...) pN

//ALLOWS OVERLOADING OF MACROS BASED ON NUMBER OF ARGUMENTS, HOWEVER DOES NOT
//		ALLOW MACROS WITH VARIABLE NUMBER OF ARGUMENTS TO BE DEFINED BASED ON OTHER MACROS WITH VARIABLE
//		NUMBER OF ARGUMENTS EXCEPT IN MICROSOFT VISUAL C++ DUE TO A BUG THERE IT SEEMS WHICH I DISCOVERED.
//		BUT FOR THE MSVC++ BUG TO WORK, THE USER MUST USE THE SAME NAME OF THE MACRO WHEN pMacroName
//		EXAMPLE:
//		#define MY_MACRO(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(MY_MACRO, __VA_ARGS__)
//
//EXAMPLE definition for MY_MACRO
//		#define MY_MACRO(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(MY_MACRO, __VA_ARGS__)
//		#define MY_MACRO__1(a) THIS IS 1
//		#define MY_MACRO__2(a, b) THIS IS 2
//		#define MY_MACRO__3(a, b, c) THIS IS 3
//
//IF WITHOUT THE MSVC++ BUG, ONE CAN HAVE THE SAME EFFECT USING CRXMD__CALL USED ON EACH __'N' CALL, THEN USING
//		ONE OF THE CRXMD__EVALUATE_'X'_TIMES MACROS. FOR EXAMPLE:
//		INSTEAD OF, WHICH WILL ONLY WORK CORRECTLY IN MSVC++:
//				#define DO1(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(DO1, __VA_ARGS__)
//				#define DO1__1(a) works and value is a
//				#define DO2(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(DO2, __VA_ARGS__)
//				#define DO2__1(_) DO1(5)
//
//				D02(_)		OUTPUT(NON MSVC)	: CRXM__RESOLVE_OVERLOADED_MACRO_CALL(DO1, 5)
//							OUTPUT(MSVC)		: works and value is 5
//		ONE WOULD WRITE:
//				#define DO1(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(DO1, __VA_ARGS__)
//				#define DO1__1(a) works and value is a
//				#define DO2(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(DO2, __VA_ARGS__)
//				#define DO2__1(_) CRXMD__CALL(DO1)(5)
//
//				CRXMD__EVALUATE_1_TIMES(DO2(_))	OUTPUT(NON MSVC)	: works and value is 5
//													OUTPUT(MSVC)		: works and value is 5
//		BUT NOTE THAT YOU HAVE TO USE 'CRXMD__CALL' FOR THE 'CRXM__RESOLVE_OVERLOADED_MACRO_CALL' CALLS AS
//		WELL IF YOU WANT RECURSSION:
//				#define DO1(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(DO1, __VA_ARGS__)
//				#define DO1__1(a) works and value is a CRXMD__CALL(DO1)(6)
//				#define DO2(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(DO2, __VA_ARGS__)
//				#define DO2__1(_) CRXMD__CALL(DO1)(5)
//
//				CRXMD__EVALUATE_4_TIMES(DO2(_))	OUTPUT(NON MSVC)	: works and value is 5 DO1 (6)
//													OUTPUT(MSVC)		: works and value is 5 works and value is 6 DO1 (6)
//				CRXMD__EVALUATE_8_TIMES(DO2(_))	OUTPUT(NON MSVC)	: works and value is 5 DO1 (6)
//													OUTPUT(MSVC)		: works and value is 5 works and value is 6 works and value is 6 works and value is 6 DO1 (6)
//		NOW WITH USING 'CRXMD__CALL' WRAPPING 'CRXM__RESOLVE_OVERLOADED_MACRO_CALL'
//				#define DO1(...) CRXMD__CALL(CRXM__RESOLVE_OVERLOADED_MACRO_CALL)(DO1, __VA_ARGS__)
//				#define DO1__1(a) works and value is a CRXMD__CALL(DO1)(6)
//				#define DO2(...) CRXMD__CALL(CRXM__RESOLVE_OVERLOADED_MACRO_CALL)(DO2, __VA_ARGS__)
//				#define DO2__1(_) CRXMD__CALL(DO1)(5)
//
//				CRXMD__EVALUATE_4_TIMES(DO2(_))	OUTPUT(NON MSVC)	: works and value is 5 works and value is 6 works and value is 6 DO1 (6)
//													OUTPUT(MSVC)		: works and value is 5 CRXM__RESOLVE_OVERLOADED_MACRO_CALL (DO1, 6)
//				CRXMD__EVALUATE_8_TIMES(DO2(_))	OUTPUT(NON MSVC)	: works and value is 5 works and value is 6 works and value is 6 works and value is 6 works and value is 6 works and value is 6 works and value is 6 DO1 (6)
//													OUTPUT(MSVC)		: works and value is 5 works and value is 6 DO1__1 (6)
//				CRXMD__EVALUATE_16_TIMES(DO2(_))	OUTPUT(MSVC)		: works and value is 5 works and value is 6 works and value is 6 works and value is 6 works and value is 6 CRXM__RESOLVE_OVERLOADED_MACRO_CALL (DO1, 6)
//
//		NOTICE HOW MSVC NEEDS MORE RE EVALUATIONS TO ACHIEVE THE SAME RESULT! ALSO NOTICE HOW IT IS BETTER
//		TO NOT WRAP THE 'CRXM__RESOLVE_OVERLOADED_MACRO_CALL' CALLS WITH 'CRXMD__CALL' FOR MSVC, AS THIS WOULD
//		GIVE RECURSSION AND MUCH MORE EFFICIENTLY. I CURRENTLY DO NOT KNOW WHY. AS THINGS STAND,
//		ONE SHOULD AVOID OVERLOADABLE MACROS.
//
//THE FOLLOWING DOES NOT WORK; BREAKS WHEN WITH ABNORMAL MACROS. THIS APPEARS TO HAPPEN BECAUSE
//		"CRXM__RESOLVE_OVERLOADED_MACRO_CALL2__ASSERT_VARIABLE_ARGUMENTS_CALL" CAUSES AN ANTICIPATED
//		EXTRA EVALUATION THAT BREAKS THE EFFECT OF "CRXMD__CALL"
//#define CRXM__RESOLVE_OVERLOADED_MACRO_CALL2(pMacroName, ...) \
//		CRXM__RESOLVE_OVERLOADED_MACRO_CALL2__ASSERT_VARIABLE_ARGUMENTS_CALL( \
//		CRXM__RESOLVE_OVERLOADED_MACRO_CALL2__DO1(pMacroName, \
//		CRXM__GET_NUMBER_OF_ARGUMENTS(__VA_ARGS__))(__VA_ARGS__))
//#define CRXM__RESOLVE_OVERLOADED_MACRO_CALL2__ASSERT_VARIABLE_ARGUMENTS_CALL(x) x
//#define CRXM__RESOLVE_OVERLOADED_MACRO_CALL2__DO1(pMacroName, pN) CRXM__RESOLVE_OVERLOADED_MACRO_CALL2__DO2(pMacroName, pN)
//#define CRXM__RESOLVE_OVERLOADED_MACRO_CALL2__DO2(pMacroName, pN) pMacroName##__##pN
//
#define CRXM__RESOLVE_OVERLOADED_MACRO_CALL(pMacroName, ...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL__DO1(pMacroName, \
		CRXM__GET_NUMBER_OF_ARGUMENTS(__VA_ARGS__))(__VA_ARGS__)
#define CRXM__RESOLVE_OVERLOADED_MACRO_CALL__DO1(pMacroName, pN) CRXM__RESOLVE_OVERLOADED_MACRO_CALL__DO2(pMacroName, pN)
#define CRXM__RESOLVE_OVERLOADED_MACRO_CALL__DO2(pMacroName, pN) pMacroName##__##pN



	#pragma region booleans //{
#define CRXM__TRUE 1
#define CRXM__FALSE 0

#define CRXM__TO_BOOL(pValue) CRXM__TO_BOOL__APPEND_ONE_AND_GET_SECOND_PARAMETER( \
		CRXM__TO_BOOL__GET_DO(pValue)())
#define CRXM__TO_BOOL__APPEND_ONE_AND_GET_SECOND_PARAMETER(...) \
		CRXM__TO_BOOL__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		CRXM__TO_BOOL__GET_SECOND_PARAMETER(__VA_ARGS__, 1, _))
#define CRXM__TO_BOOL__ASSERT_VARIABLE_ARGUMENTS_CALL(pFullMacroCall) pFullMacroCall
#define CRXM__TO_BOOL__GET_SECOND_PARAMETER(a, b, ...) b
#define CRXM__TO_BOOL__GET_DO(pValue) CRXM__TO_BOOL__DO ## pValue
#define CRXM__TO_BOOL__DO0() _, 0
#define CRXM__TO_BOOL__DOfalse() _, 0
#define CRXM__TO_BOOL__DOnullptr() _, 0
#define CRXM__TO_BOOL__DO() _, 0

#define CRXM__AND(pA, pB) CRXM__AND__GET_DO(CRXM__TO_BOOL(pA), CRXM__TO_BOOL(pB))()
#define CRXM__AND__GET_DO(pOneOrZero1, pOneOrZero2) CRXM__AND__GET_DO__DO(pOneOrZero1, pOneOrZero2)
#define CRXM__AND__GET_DO__DO(pOneOrZero1, pOneOrZero2) CRXM__AND__ ## pOneOrZero1 ## pOneOrZero2
#define CRXM__AND__00() 0
#define CRXM__AND__01() 0
#define CRXM__AND__10() 0
#define CRXM__AND__11() 1

#define CRXM__OR(pA, pB) CRXM__OR__GET_DO(CRXM__TO_BOOL(pA), CRXM__TO_BOOL(pB))()
#define CRXM__OR__GET_DO(pOneOrZero1, pOneOrZero2) CRXM__OR__GET_DO__DO(pOneOrZero1, pOneOrZero2)
#define CRXM__OR__GET_DO__DO(pOneOrZero1, pOneOrZero2) CRXM__OR__ ## pOneOrZero1 ## pOneOrZero2
#define CRXM__OR__00() 0
#define CRXM__OR__01() 1
#define CRXM__OR__10() 1
#define CRXM__OR__11() 1

#define CRXM__NOT(pA) CRXM__NOT__GET_DO(CRXM__TO_BOOL(pA))()
#define CRXM__NOT__GET_DO(pOneOrZero) CRXM__NOT__GET_DO__DO(pOneOrZero)
#define CRXM__NOT__GET_DO__DO(pOneOrZero) CRXM__NOT__ ## pOneOrZero
#define CRXM__NOT__0() 1
#define CRXM__NOT__1() 0

	#pragma endregion //}

	#pragma region Enums //{
//CRXM ENUMS CAN BE DEFINED WITH VALUES 0 TO 9. UNLIKE BOOLEANS, "EMPTY" AND OTHER VALUES DO
//		NOT EVALUATE AS VALID ENUMS
//THE FACILITIES FOR ENUMS CAN NOT DISTINGUISH BETWEEN TWO DIFFERENT ENUMS
#define CRXM__TO_ENUM(pValue) CRXM__TO_ENUM__APPEND_INVALID_AND_GET_SECOND_PARAMETER( \
		CRXM__TO_ENUM__GET_DO(pValue)())
#define CRXM__TO_ENUM__APPEND_INVALID_AND_GET_SECOND_PARAMETER(...) \
		CRXM__TO_ENUM__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		CRXM__TO_ENUM__GET_SECOND_PARAMETER(__VA_ARGS__, INVALID_CRXM_ENUM, _))
#define CRXM__TO_ENUM__ASSERT_VARIABLE_ARGUMENTS_CALL(pFullMacroCall) pFullMacroCall
#define CRXM__TO_ENUM__GET_SECOND_PARAMETER(a, b, ...) b
#define CRXM__TO_ENUM__GET_DO(pValue) CRXM__TO_ENUM__DO ## pValue
#define CRXM__TO_ENUM__DO0() _, 0
#define CRXM__TO_ENUM__DO1() _, 1
#define CRXM__TO_ENUM__DO2() _, 2
#define CRXM__TO_ENUM__DO3() _, 3
#define CRXM__TO_ENUM__DO4() _, 4
#define CRXM__TO_ENUM__DO5() _, 5
#define CRXM__TO_ENUM__DO6() _, 6
#define CRXM__TO_ENUM__DO7() _, 7
#define CRXM__TO_ENUM__DO8() _, 8
#define CRXM__TO_ENUM__DO9() _, 9
#define CRXM__TO_ENUM__DO() _, INVALID_CRXM_ENUM

//REMEMBER: THE FACILITIES FOR ENUMS CAN NOT DISTINGUISH BETWEEN TWO DIFFERENT ENUMS
//FOR EXAMPLE, GIVEN:
//				#define MY_ENUM__CAR 0
//				#define MY_ENUM__PLANE 1
//				#define MY_ENUM2__ORANGE 0
//				#define MY_ENUM2__APPLE 1
//				#define MY_ENUM2__BANNANA 2
//		THE FOLLOWING STATEMENT WOULD EVALUATE TRUE
//				CRXM__IS(MY_ENUM__CAR, MY_ENUM2__ORANGE)
#define CRXM__IS(pA, pB) CRXM__IS__GET__XX(CRXM__TO_ENUM(pA), CRXM__TO_ENUM(pB))()
#define CRXM__IS__GET__XX(pA, pB) CRXM__IS__GET__XX__DO(pA, pB)
#define CRXM__IS__GET__XX__DO(pA, pB) CRXM__IS__ ## pA ## pB
#define CRXM__IS__0INVALID_CRXM_ENUM() 0
#define CRXM__IS__1INVALID_CRXM_ENUM() 0
#define CRXM__IS__2INVALID_CRXM_ENUM() 0
#define CRXM__IS__3INVALID_CRXM_ENUM() 0
#define CRXM__IS__4INVALID_CRXM_ENUM() 0
#define CRXM__IS__5INVALID_CRXM_ENUM() 0
#define CRXM__IS__6INVALID_CRXM_ENUM() 0
#define CRXM__IS__7INVALID_CRXM_ENUM() 0
#define CRXM__IS__8INVALID_CRXM_ENUM() 0
#define CRXM__IS__9INVALID_CRXM_ENUM() 0
#define CRXM__IS__INVALID_CRXM_ENUMINVALID_CRXM_ENUM() 0
#define CRXM__IS__00() 1
#define CRXM__IS__10() 0
#define CRXM__IS__20() 0
#define CRXM__IS__30() 0
#define CRXM__IS__40() 0
#define CRXM__IS__50() 0
#define CRXM__IS__60() 0
#define CRXM__IS__70() 0
#define CRXM__IS__80() 0
#define CRXM__IS__90() 0
#define CRXM__IS__INVALID_CRXM_ENUM0() 0
#define CRXM__IS__01() 0
#define CRXM__IS__11() 1
#define CRXM__IS__21() 0
#define CRXM__IS__31() 0
#define CRXM__IS__41() 0
#define CRXM__IS__51() 0
#define CRXM__IS__61() 0
#define CRXM__IS__71() 0
#define CRXM__IS__81() 0
#define CRXM__IS__91() 0
#define CRXM__IS__INVALID_CRXM_ENUM1() 0
#define CRXM__IS__02() 0
#define CRXM__IS__12() 0
#define CRXM__IS__22() 1
#define CRXM__IS__32() 0
#define CRXM__IS__42() 0
#define CRXM__IS__52() 0
#define CRXM__IS__62() 0
#define CRXM__IS__72() 0
#define CRXM__IS__82() 0
#define CRXM__IS__92() 0
#define CRXM__IS__INVALID_CRXM_ENUM2() 0
#define CRXM__IS__03() 0
#define CRXM__IS__13() 0
#define CRXM__IS__23() 0
#define CRXM__IS__33() 1
#define CRXM__IS__43() 0
#define CRXM__IS__53() 0
#define CRXM__IS__63() 0
#define CRXM__IS__73() 0
#define CRXM__IS__83() 0
#define CRXM__IS__93() 0
#define CRXM__IS__INVALID_CRXM_ENUM3() 0
#define CRXM__IS__04() 0
#define CRXM__IS__14() 0
#define CRXM__IS__24() 0
#define CRXM__IS__34() 0
#define CRXM__IS__44() 1
#define CRXM__IS__54() 0
#define CRXM__IS__64() 0
#define CRXM__IS__74() 0
#define CRXM__IS__84() 0
#define CRXM__IS__94() 0
#define CRXM__IS__INVALID_CRXM_ENUM4() 0
#define CRXM__IS__05() 0
#define CRXM__IS__15() 0
#define CRXM__IS__25() 0
#define CRXM__IS__35() 0
#define CRXM__IS__45() 0
#define CRXM__IS__55() 1
#define CRXM__IS__65() 0
#define CRXM__IS__75() 0
#define CRXM__IS__85() 0
#define CRXM__IS__95() 0
#define CRXM__IS__INVALID_CRXM_ENUM5() 0
#define CRXM__IS__06() 0
#define CRXM__IS__16() 0
#define CRXM__IS__26() 0
#define CRXM__IS__36() 0
#define CRXM__IS__46() 0
#define CRXM__IS__56() 0
#define CRXM__IS__66() 1
#define CRXM__IS__76() 0
#define CRXM__IS__86() 0
#define CRXM__IS__96() 0
#define CRXM__IS__INVALID_CRXM_ENUM6() 0
#define CRXM__IS__07() 0
#define CRXM__IS__17() 0
#define CRXM__IS__27() 0
#define CRXM__IS__37() 0
#define CRXM__IS__47() 0
#define CRXM__IS__57() 0
#define CRXM__IS__67() 0
#define CRXM__IS__77() 1
#define CRXM__IS__87() 0
#define CRXM__IS__97() 0
#define CRXM__IS__INVALID_CRXM_ENUM7() 0
#define CRXM__IS__08() 0
#define CRXM__IS__18() 0
#define CRXM__IS__28() 0
#define CRXM__IS__38() 0
#define CRXM__IS__48() 0
#define CRXM__IS__58() 0
#define CRXM__IS__68() 0
#define CRXM__IS__78() 0
#define CRXM__IS__88() 1
#define CRXM__IS__98() 1
#define CRXM__IS__INVALID_CRXM_ENUM8() 0
#define CRXM__IS__09() 0
#define CRXM__IS__19() 0
#define CRXM__IS__29() 0
#define CRXM__IS__39() 0
#define CRXM__IS__49() 0
#define CRXM__IS__59() 0
#define CRXM__IS__69() 0
#define CRXM__IS__79() 0
#define CRXM__IS__89() 0
#define CRXM__IS__99() 1
#define CRXM__IS__INVALID_CRXM_ENUM9() 0
	#pragma endregion //}

	#pragma region CONTROL STATEMENTS //{
//EXAMPLE USAGE:
//	CRXM__IFELSE(0)
//	(
//		AAA
//	)
//	(
//		BBB
//	)
//	DUE TO 'IF' AND 'ELSE' BEING PARAMETERS TO OTHER MACROS, CRXM__IFELSE CAN BE NESTED.
#define CRXM__IFELSE(pValue) CRXM__IFELSE__GET_DOX(CRXM__TO_BOOL(pValue))
#define CRXM__IFELSE__GET_DOX(pOneOrZero) CRXM__IFELSE__GET_DOX__DO(pOneOrZero)
#define CRXM__IFELSE__GET_DOX__DO(pOneOrZero) CRXM__IFELSE__DO ## pOneOrZero
#define CRXM__IFELSE__DO1(...) __VA_ARGS__ CRXM__IFELSE__DO1__DO_NOTHING
#define CRXM__IFELSE__DO1__DO_NOTHING(...)
#define CRXM__IFELSE__DO0(...) CRXM__IFELSE__DO0__DO
#define CRXM__IFELSE__DO0__DO(...) __VA_ARGS__

//EXAMPLE USAGE:
//	CRXM__IFELSE2(0, AAA, BBB)
//
//NOTE: CRXM__IFELSE2 CAN BE NESTED.
/* WARNING: NEVER USE AN EMPTY SECOND PARAMETER, pOn1 MUST NEVER BE EMPTY
		ALTHOUGH THE FOLLOWING GENERALLY WORKS, IT DOES NOT IF THE FIRST PARAMETER IS EMPTY AND 
		THE BOOLEAN VALUE OF pValue IS TRUE. THIE IS BECAUSE A CALL IN VC6 LIKE
				CRXM__IFELSE2(pValue, , pOn0)
		BECOMES
				CRXM__IFELSE2(pValue, pOn0)
		IT SEEMS.
		HOWEVER THE FUNCTION IS NOT AFFECTED FOR A CALL LIKE
				CRXM__IFELSE2(pValue, pOn1,)
		FOR CLEAR REASONS.
		THIS DOES NOT SEEM TO AFFECT NEWER COMPILERS
*/
#define CRXM__IFELSE2(pValue, pOn1, pOn0) CRXM__IFELSE2__GET_DOX(CRXM__TO_BOOL(pValue))(pOn1, pOn0)
#define CRXM__IFELSE2__GET_DOX(pOneOrZero) CRXM__IFELSE2__GET_DOX_DO(pOneOrZero)
#define CRXM__IFELSE2__GET_DOX_DO(pOneOrZero) CRXM__IFELSE2__DO  ## pOneOrZero
#define CRXM__IFELSE2__DO0(pOn1, pOn0) pOn0
#define CRXM__IFELSE2__DO1(pOn1, pOn0) pOn1

		#pragma region switch macro //{
//EXAMPLE USAGE:
//	CRXM__SWITCH(3)
//	(
//		(0,
//			x = 5;
//		)
//		(1,
//			x = 3;		
//		)
//		(0,
//			x = 11;
//		)
//	)
//NOTE: CRXM__SWITCH CAN BE NESTED
#define CRXM__SWITCH(pPumberOfCases) CRXM__SWITCH__REMOVE_BRACKETSX(pPumberOfCases)
#define CRXM__SWITCH__REMOVE_BRACKETSX(pPumberOfCases) CRXM__SWITCH__REMOVE_BRACKETSX__DO(pPumberOfCases)
#define CRXM__SWITCH__REMOVE_BRACKETSX__DO(pPumberOfCases) CRXM__SWITCH__REMOVE_BRACKETS ## pPumberOfCases
#define CRXM__SWITCH__REMOVE_BRACKETS1(...) CRXM__SWITCH__DO1 __VA_ARGS__
#define CRXM__SWITCH__REMOVE_BRACKETS2(...) CRXM__SWITCH__DO2 __VA_ARGS__
#define CRXM__SWITCH__REMOVE_BRACKETS3(...) CRXM__SWITCH__DO3 __VA_ARGS__
#define CRXM__SWITCH__REMOVE_BRACKETS4(...) CRXM__SWITCH__DO4 __VA_ARGS__
#define CRXM__SWITCH__REMOVE_BRACKETS5(...) CRXM__SWITCH__DO5 __VA_ARGS__
#define CRXM__SWITCH__REMOVE_BRACKETS6(...) CRXM__SWITCH__DO6 __VA_ARGS__
#define CRXM__SWITCH__REMOVE_BRACKETS7(...) CRXM__SWITCH__DO7 __VA_ARGS__
#define CRXM__SWITCH__REMOVE_BRACKETS8(...) CRXM__SWITCH__DO8 __VA_ARGS__
#define CRXM__SWITCH__REMOVE_BRACKETS9(...) CRXM__SWITCH__DO9 __VA_ARGS__
#define CRXM__SWITCH__REMOVE_BRACKETS10(...) CRXM__SWITCH__DO10 __VA_ARGS__
#define CRXM__SWITCH__DOX(pPumberOfCases) CRXM__SWITCH__DO ## pPumberOfCases
#define CRXM__SWITCH__DO10(pValue, ...)	CRXM__SWITCH__DO10__GET_DOX(CRXM__TO_BOOL(pValue))(__VA_ARGS__)
#define CRXM__SWITCH__DO10__GET_DOX(pOneOrZero) CRXM__SWITCH__DO10__GET_DOX__DO(pOneOrZero)
#define CRXM__SWITCH__DO10__GET_DOX__DO(pOneOrZero) CRXM__SWITCH__DO10__DO ## pOneOrZero
#define CRXM__SWITCH__DO10__DO1(...) __VA_ARGS__ CRXM__SWITCH__DO9__DO_FALL_THROUGH
#define CRXM__SWITCH__DO10__DO0(...) CRXM__SWITCH__DO9
#define CRXM__SWITCH__DO10__DO_FALL_THROUGH(...) CRXM__SWITCH__DO9__DO_FALL_THROUGH
#define CRXM__SWITCH__DO9(pValue, ...)	CRXM__SWITCH__DO9__GET_DOX(CRXM__TO_BOOL(pValue))(__VA_ARGS__)
#define CRXM__SWITCH__DO9__GET_DOX(pOneOrZero) CRXM__SWITCH__DO9__GET_DOX__DO(pOneOrZero)
#define CRXM__SWITCH__DO9__GET_DOX__DO(pOneOrZero) CRXM__SWITCH__DO9__DO ## pOneOrZero
#define CRXM__SWITCH__DO9__DO1(...) __VA_ARGS__ CRXM__SWITCH__DO8__DO_FALL_THROUGH
#define CRXM__SWITCH__DO9__DO0(...) CRXM__SWITCH__DO8
#define CRXM__SWITCH__DO9__DO_FALL_THROUGH(...) CRXM__SWITCH__DO8__DO_FALL_THROUGH
#define CRXM__SWITCH__DO8(pValue, ...)	CRXM__SWITCH__DO8__GET_DOX(CRXM__TO_BOOL(pValue))(__VA_ARGS__)
#define CRXM__SWITCH__DO8__GET_DOX(pOneOrZero) CRXM__SWITCH__DO8__GET_DOX__DO(pOneOrZero)
#define CRXM__SWITCH__DO8__GET_DOX__DO(pOneOrZero) CRXM__SWITCH__DO8__DO ## pOneOrZero
#define CRXM__SWITCH__DO8__DO1(...) __VA_ARGS__ CRXM__SWITCH__DO7__DO_FALL_THROUGH
#define CRXM__SWITCH__DO8__DO0(...) CRXM__SWITCH__DO7
#define CRXM__SWITCH__DO8__DO_FALL_THROUGH(...) CRXM__SWITCH__DO7__DO_FALL_THROUGH
#define CRXM__SWITCH__DO7(pValue, ...)	CRXM__SWITCH__DO7__GET_DOX(CRXM__TO_BOOL(pValue))(__VA_ARGS__)
#define CRXM__SWITCH__DO7__GET_DOX(pOneOrZero) CRXM__SWITCH__DO7__GET_DOX__DO(pOneOrZero)
#define CRXM__SWITCH__DO7__GET_DOX__DO(pOneOrZero) CRXM__SWITCH__DO7__DO ## pOneOrZero
#define CRXM__SWITCH__DO7__DO1(...) __VA_ARGS__ CRXM__SWITCH__DO6__DO_FALL_THROUGH
#define CRXM__SWITCH__DO7__DO0(...) CRXM__SWITCH__DO6
#define CRXM__SWITCH__DO7__DO_FALL_THROUGH(...) CRXM__SWITCH__DO6__DO_FALL_THROUGH
#define CRXM__SWITCH__DO6(pValue, ...)	CRXM__SWITCH__DO6__GET_DOX(CRXM__TO_BOOL(pValue))(__VA_ARGS__)
#define CRXM__SWITCH__DO6__GET_DOX(pOneOrZero) CRXM__SWITCH__DO6__GET_DOX__DO(pOneOrZero)
#define CRXM__SWITCH__DO6__GET_DOX__DO(pOneOrZero) CRXM__SWITCH__DO6__DO ## pOneOrZero
#define CRXM__SWITCH__DO6__DO1(...) __VA_ARGS__ CRXM__SWITCH__DO5__DO_FALL_THROUGH
#define CRXM__SWITCH__DO6__DO0(...) CRXM__SWITCH__DO5
#define CRXM__SWITCH__DO6__DO_FALL_THROUGH(...) CRXM__SWITCH__DO5__DO_FALL_THROUGH
#define CRXM__SWITCH__DO5(pValue, ...)	CRXM__SWITCH__DO5__GET_DOX(CRXM__TO_BOOL(pValue))(__VA_ARGS__)
#define CRXM__SWITCH__DO5__GET_DOX(pOneOrZero) CRXM__SWITCH__DO5__GET_DOX__DO(pOneOrZero)
#define CRXM__SWITCH__DO5__GET_DOX__DO(pOneOrZero) CRXM__SWITCH__DO5__DO ## pOneOrZero
#define CRXM__SWITCH__DO5__DO1(...) __VA_ARGS__ CRXM__SWITCH__DO4__DO_FALL_THROUGH
#define CRXM__SWITCH__DO5__DO0(...) CRXM__SWITCH__DO4
#define CRXM__SWITCH__DO5__DO_FALL_THROUGH(...) CRXM__SWITCH__DO4__DO_FALL_THROUGH
#define CRXM__SWITCH__DO4(pValue, ...)	CRXM__SWITCH__DO4__GET_DOX(CRXM__TO_BOOL(pValue))(__VA_ARGS__)
#define CRXM__SWITCH__DO4__GET_DOX(pOneOrZero) CRXM__SWITCH__DO4__GET_DOX__DO(pOneOrZero)
#define CRXM__SWITCH__DO4__GET_DOX__DO(pOneOrZero) CRXM__SWITCH__DO4__DO ## pOneOrZero
#define CRXM__SWITCH__DO4__DO1(...) __VA_ARGS__ CRXM__SWITCH__DO3__DO_FALL_THROUGH
#define CRXM__SWITCH__DO4__DO0(...) CRXM__SWITCH__DO3
#define CRXM__SWITCH__DO4__DO_FALL_THROUGH(...) CRXM__SWITCH__DO3__DO_FALL_THROUGH
#define CRXM__SWITCH__DO3(pValue, ...)	CRXM__SWITCH__DO3__GET_DOX(CRXM__TO_BOOL(pValue))(__VA_ARGS__)
#define CRXM__SWITCH__DO3__GET_DOX(pOneOrZero) CRXM__SWITCH__DO3__GET_DOX__DO(pOneOrZero)
#define CRXM__SWITCH__DO3__GET_DOX__DO(pOneOrZero) CRXM__SWITCH__DO3__DO ## pOneOrZero
#define CRXM__SWITCH__DO3__DO1(...) __VA_ARGS__ CRXM__SWITCH__DO2__DO_FALL_THROUGH
#define CRXM__SWITCH__DO3__DO0(...) CRXM__SWITCH__DO2
#define CRXM__SWITCH__DO3__DO_FALL_THROUGH(...) CRXM__SWITCH__DO2__DO_FALL_THROUGH
#define CRXM__SWITCH__DO2(pValue, ...)	CRXM__SWITCH__DO2__GET_DOX(CRXM__TO_BOOL(pValue))(__VA_ARGS__)
#define CRXM__SWITCH__DO2__GET_DOX(pOneOrZero) CRXM__SWITCH__DO2__GET_DOX__DO(pOneOrZero)
#define CRXM__SWITCH__DO2__GET_DOX__DO(pOneOrZero) CRXM__SWITCH__DO2__DO ## pOneOrZero
#define CRXM__SWITCH__DO2__DO1(...) __VA_ARGS__ CRXM__SWITCH__DO1__DO_FALL_THROUGH
#define CRXM__SWITCH__DO2__DO0(...) CRXM__SWITCH__DO1
#define CRXM__SWITCH__DO2__DO_FALL_THROUGH(...) CRXM__SWITCH__DO1__DO_FALL_THROUGH
#define CRXM__SWITCH__DO1(pValue, ...)	CRXM__SWITCH__DO1__GET_DOX(CRXM__TO_BOOL(pValue))(__VA_ARGS__)
#define CRXM__SWITCH__DO1__GET_DOX(pOneOrZero) CRXM__SWITCH__DO1__GET_DOX__DO(pOneOrZero)
#define CRXM__SWITCH__DO1__GET_DOX__DO(pOneOrZero) CRXM__SWITCH__DO1__DO ## pOneOrZero
#define CRXM__SWITCH__DO1__DO1(...) __VA_ARGS__
#define CRXM__SWITCH__DO1__DO0(...) 
#define CRXM__SWITCH__DO1__DO_FALL_THROUGH(...)
		#pragma endregion //}

//THE F0LLOWING DOES NOT ALLOW NESTED LOOPS. FOR NESTED LOOPS, SEE CRXMD__REPEAT_MACRO
		#pragma region repeat macro //{
#define CRXM__REPEAT_MACRO(pNumber, pMacro, ...)	CRXM__REPEAT_MACRO__GET_DO(pNumber)(pMacro, __VA_ARGS__)
#define CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pFullMacroCall) pFullMacroCall
#define CRXM__REPEAT_MACRO__GET_DO(pNumber) CRXM__REPEAT_MACRO__DO ## pNumber
#define CRXM__REPEAT_MACRO__DO50(pMacro, ...) CRXM__REPEAT_MACRO__DO49(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(50, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO49(pMacro, ...) CRXM__REPEAT_MACRO__DO48(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(49, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO48(pMacro, ...) CRXM__REPEAT_MACRO__DO47(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(48, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO47(pMacro, ...) CRXM__REPEAT_MACRO__DO46(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(47, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO46(pMacro, ...) CRXM__REPEAT_MACRO__DO45(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(46, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO45(pMacro, ...) CRXM__REPEAT_MACRO__DO44(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(45, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO44(pMacro, ...) CRXM__REPEAT_MACRO__DO43(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(44, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO43(pMacro, ...) CRXM__REPEAT_MACRO__DO42(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(43, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO42(pMacro, ...) CRXM__REPEAT_MACRO__DO41(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(42, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO41(pMacro, ...) CRXM__REPEAT_MACRO__DO40(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(41, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO40(pMacro, ...) CRXM__REPEAT_MACRO__DO39(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(40, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO39(pMacro, ...) CRXM__REPEAT_MACRO__DO38(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(39, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO38(pMacro, ...) CRXM__REPEAT_MACRO__DO37(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(38, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO37(pMacro, ...) CRXM__REPEAT_MACRO__DO36(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(37, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO36(pMacro, ...) CRXM__REPEAT_MACRO__DO35(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(36, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO35(pMacro, ...) CRXM__REPEAT_MACRO__DO34(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(35, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO34(pMacro, ...) CRXM__REPEAT_MACRO__DO33(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(34, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO33(pMacro, ...) CRXM__REPEAT_MACRO__DO32(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(33, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO32(pMacro, ...) CRXM__REPEAT_MACRO__DO31(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(32, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO31(pMacro, ...) CRXM__REPEAT_MACRO__DO30(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(31, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO30(pMacro, ...) CRXM__REPEAT_MACRO__DO29(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(30, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO29(pMacro, ...) CRXM__REPEAT_MACRO__DO28(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(29, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO28(pMacro, ...) CRXM__REPEAT_MACRO__DO27(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(28, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO27(pMacro, ...) CRXM__REPEAT_MACRO__DO26(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(27, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO26(pMacro, ...) CRXM__REPEAT_MACRO__DO25(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(26, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO25(pMacro, ...) CRXM__REPEAT_MACRO__DO24(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(25, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO24(pMacro, ...) CRXM__REPEAT_MACRO__DO23(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(24, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO23(pMacro, ...) CRXM__REPEAT_MACRO__DO22(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(23, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO22(pMacro, ...) CRXM__REPEAT_MACRO__DO21(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(22, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO21(pMacro, ...) CRXM__REPEAT_MACRO__DO20(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(21, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO20(pMacro, ...) CRXM__REPEAT_MACRO__DO19(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(20, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO19(pMacro, ...) CRXM__REPEAT_MACRO__DO18(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(19, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO18(pMacro, ...) CRXM__REPEAT_MACRO__DO17(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(18, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO17(pMacro, ...) CRXM__REPEAT_MACRO__DO16(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(17, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO16(pMacro, ...) CRXM__REPEAT_MACRO__DO15(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(16, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO15(pMacro, ...) CRXM__REPEAT_MACRO__DO14(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(15, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO14(pMacro, ...) CRXM__REPEAT_MACRO__DO13(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(14, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO13(pMacro, ...) CRXM__REPEAT_MACRO__DO12(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(13, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO12(pMacro, ...) CRXM__REPEAT_MACRO__DO11(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(12, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO11(pMacro, ...) CRXM__REPEAT_MACRO__DO10(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(11, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO10(pMacro, ...) CRXM__REPEAT_MACRO__DO9(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(10, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO9(pMacro, ...) CRXM__REPEAT_MACRO__DO8(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(9, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO8(pMacro, ...) CRXM__REPEAT_MACRO__DO7(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(8, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO7(pMacro, ...) CRXM__REPEAT_MACRO__DO6(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(7, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO6(pMacro, ...) CRXM__REPEAT_MACRO__DO5(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(6, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO5(pMacro, ...) CRXM__REPEAT_MACRO__DO4(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(5, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO4(pMacro, ...) CRXM__REPEAT_MACRO__DO3(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(4, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO3(pMacro, ...) CRXM__REPEAT_MACRO__DO2(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(3, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO2(pMacro, ...) CRXM__REPEAT_MACRO__DO1(pMacro, __VA_ARGS__) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(2, __VA_ARGS__))
#define CRXM__REPEAT_MACRO__DO1(pMacro, ...) CRXM__REPEAT_MACRO__ASSERT_VARIABLE_ARGUMENTS_CALL(pMacro(1, __VA_ARGS__))
		#pragma endregion //}


// ORIGINALY MEANT FOR "CRXM__TO_C_STRING" WHICH ITSELF DID NOT WORK ON MSVC6, HENCE UNSURE IF IT
//		IS STABLE.
/*
#define CRXM__DO_MACRO_ON_EACH(pMacro, ...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL(CRXM__DO_MACRO_ON_EACH__DO(pMacro, \
		CRXM__GET_NUMBER_OF_ARGUMENTS(__VA_ARGS__), __VA_ARGS__))
#define CRXM__DO_MACRO_ON_EACH__DO(pMacro, pLength, ...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		CRXM__DO_MACRO_ON_EACH__DO__GET_DO(pLength)(pMacro, __VA_ARGS__))
#define CRXM__DO_MACRO_ON_EACH__DO__GET_DO(pNumber) CRXM__DO_MACRO_ON_EACH__DO__DO ## pNumber
#define CRXM__DO_MACRO_ON_EACH__DO__DO2(pMacro, ...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		CRXM__DO_MACRO_ON_EACH__CALL_USER_MACRO(pMacro, 2, CRXM__LISTCONTENT_GET_FIRST(__VA_ARGS__)) \
		CRXM__DO_MACRO_ON_EACH__DO__DO1(pMacro, CRXM__LISTCONTENT_GET_WITHOUT_FIRST(__VA_ARGS__)))
#define CRXM__DO_MACRO_ON_EACH__DO__DO1(pMacro, ...) pMacro(1, __VA_ARGS__)
#define CRXM__DO_MACRO_ON_EACH__CALL_USER_MACRO(pMacro, pN, ...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		pMacro(pN, __VA_ARGS__))
*/

//- COULD NOT GET IT TO WORK ON OLD COMPILERS
//- VERY VERBOSE. NOT WORTH IT; DID NOT WORK ON OLD COMPILERS FOR THE ORIGINAL INTENT IT WAS MADE FOR.
//		SEE CRXM__TO_C_STRING2
/*
#define CRXM__DO_MACRO_ON_EACH2(pMacro, pMacro_onFinish, ...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		CRXM__DO_MACRO_ON_EACH2__DO(pMacro, pMacro_onFinish, CRXM__GET_NUMBER_OF_ARGUMENTS(__VA_ARGS__), __VA_ARGS__))
#define CRXM__DO_MACRO_ON_EACH2__DO(pMacro, pMacro_onFinish, pLength, ...) \
		CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL(CRXM__DO_MACRO_ON_EACH2__DO__CALL_ON_FINISH(pMacro_onFinish, \
		CRXM__DO_MACRO_ON_EACH2__DO__GET_DO(pLength) (pMacro, __VA_ARGS__)))
#define CRXM__DO_MACRO_ON_EACH2__DO__CALL_ON_FINISH(pMacro_onFinish, pCurrentResult) \
		CRXM__DO_MACRO_ON_EACH2__DO__CALL_ON_FINISH__DO(pMacro_onFinish, pCurrentResult)
#define CRXM__DO_MACRO_ON_EACH2__DO__CALL_ON_FINISH__DO(pMacro_onFinish, pCurrentResult) \
		pMacro_onFinish(pCurrentResult)
#define CRXM__DO_MACRO_ON_EACH2__DO__GET_DO(pNumber) CRXM__DO_MACRO_ON_EACH2__DO__DO ## pNumber
#define CRXM__DO_MACRO_ON_EACH2__DO__DO3(pMacro, ...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		CRXM__DO_MACRO_ON_EACH2__DO__DOX__DO_CALL(3, pMacro, CRXM__DO_MACRO_ON_EACH2__DO__DO2(pMacro, \
				CRXM__LISTCONTENT_GET_WITHOUT_FIRST(__VA_ARGS__)), \
				CRXM__LISTCONTENT_GET_FIRST(__VA_ARGS__)))
#define CRXM__DO_MACRO_ON_EACH2__DO__DO2(pMacro, ...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		CRXM__DO_MACRO_ON_EACH2__DO__DOX__DO_CALL(2, pMacro, CRXM__DO_MACRO_ON_EACH2__DO__DO1(pMacro, \
				CRXM__LISTCONTENT_GET_WITHOUT_FIRST(__VA_ARGS__)), \
				CRXM__LISTCONTENT_GET_FIRST(__VA_ARGS__)))
#define CRXM__DO_MACRO_ON_EACH2__DO__DO1(pMacro, ...) pMacro(1,, __VA_ARGS__)
#define CRXM__DO_MACRO_ON_EACH2__DO__DOX__DO_CALL(pN, pMacro, pCurrentResult, ...) \
		CRXM__DO_MACRO_ON_EACH2__DO__DOX__CALL_USER_MACRO(pMacro, pN, pCurrentResult, CRXM__LISTCONTENT_GET_FIRST(__VA_ARGS__))
#define CRXM__DO_MACRO_ON_EACH2__DO__DOX__CALL_USER_MACRO(pMacro, pN, pCurrentResult, ...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		pMacro(pN, pCurrentResult, __VA_ARGS__))
*/

	#pragma endregion //}

	#pragma region tokens functions //{
#define CRXM__IS_EMPTY(pValue, ...) CRXM__IS_EMPTY__APPEND_ONE_AND_GET_SECOND_PARAMETER( \
		CRXM__IS_EMPTY__GET_DO(pValue)())
#define CRXM__IS_EMPTY__APPEND_ONE_AND_GET_SECOND_PARAMETER(...) \
		CRXM__IS_EMPTY__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		CRXM__IS_EMPTY__GET_SECOND_PARAMETER(__VA_ARGS__, 0, _))
#define CRXM__IS_EMPTY__ASSERT_VARIABLE_ARGUMENTS_CALL(pFullMacroCall) pFullMacroCall
#define CRXM__IS_EMPTY__GET_SECOND_PARAMETER(a, b, ...) b
#define CRXM__IS_EMPTY__GET_DO(pValue) CRXM__IS_EMPTY__DO ## pValue
#define CRXM__IS_EMPTY__DO() _, 1


/*
THE FOLLOWING DOES NOT WORK FOR INPUT LIKE ()() UNDER GCC AND GIVES AND ERROR, 
		BUT WORKS UNDER MSVC
*/
#define CRXM__IS_PARENTHESIZED(pValue) CRXM__IS_PARENTHESIZED__DO(CRXM__IS_PARENTHESIZED__ERASE pValue)
#define CRXM__IS_PARENTHESIZED__ERASE(...)
#define CRXM__IS_PARENTHESIZED__DO(pA) CRXM__NOT(pA)

/*
THE FOLLOWING GIVES WRONG RESULT FOR INPUT LIKE ()() UNDER GCC AND MSVC,
RETURNING A '1' INSTEAD OF '0'. HOWEVER IT GIVES THE CORRECT RESULT UNDER MSVC IF NOT
USING 'CRXM__IS_PARENTHESIZED2__ASSERT_VARIABLE_ARGUMENTS_CALL' BUT CONTINUES TO GIVE WRONG
RESULT UNDER GCC
#define CRXM__IS_PARENTHESIZED2(pValue) \
		CRXM__IS_PARENTHESIZED2__CONCATENATE_AND_GET_SECOND_ARGUMENT(CRXM__IS_PARENTHESIZED2_SET_YES pValue)
#define CRXM__IS_PARENTHESIZED2__CONCATENATE_AND_GET_SECOND_ARGUMENT(...) \
		CRXM__IS_PARENTHESIZED2__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		CRXM__IS_PARENTHESIZED2__GET_SECOND_ARGUMENT(__VA_ARGS__, 0,))
#define CRXM__IS_PARENTHESIZED2__ASSERT_VARIABLE_ARGUMENTS_CALL(pFullMacroCall) pFullMacroCall
#define CRXM__IS_PARENTHESIZED2__GET_SECOND_ARGUMENT(x, n, ...) n
#define CRXM__IS_PARENTHESIZED2_SET_YES(...) CRXM__IS_PARENTHESIZED2_SET_YES__DO()
#define CRXM__IS_PARENTHESIZED2_SET_YES__DO() _, 1,
*/

#define CRXM__ARE_TOKENS_EQUAL(pToken1, pToken2) CRXM__ARE_TOKENS_EQUAL2(pToken1, pToken2, CRXM__USER__TOKEN_COMPARATOR__)

#define CRXM__ARE_TOKENS_EQUAL2(pToken1, pToken2, pComparatorPrefix) \
		CRXM__IFELSE2(CRXM__AND(CRXM__ARE_TOKENS_EQUAL2__DOES_COMPARATOR_EXISTS(pToken1, pComparatorPrefix), \
		CRXM__ARE_TOKENS_EQUAL2__DOES_COMPARATOR_EXISTS(pToken2, pComparatorPrefix)), \
		CRXM__ARE_TOKENS_EQUAL2__COMPARE(pToken1, pToken2, pComparatorPrefix), 0)
#define CRXM__ARE_TOKENS_EQUAL2__DOES_COMPARATOR_EXISTS(pToken, pComparatorPrefix) \
		CRXM__IS_PARENTHESIZED(CRXM__ARE_TOKENS_EQUAL2__GET_COMPARATOR(pToken, pComparatorPrefix)(()))
#define CRXM__ARE_TOKENS_EQUAL2__GET_COMPARATOR(pToken, pComparatorPrefix) \
		pComparatorPrefix ## pToken
#define CRXM__ARE_TOKENS_EQUAL2__COMPARE(pToken1, pToken2, pComparatorPrefix) \
		CRXM__NOT(CRXM__IS_PARENTHESIZED(CRXM__ARE_TOKENS_EQUAL2__GET_COMPARATOR(pToken1, pComparatorPrefix)\
		(CRXM__ARE_TOKENS_EQUAL2__GET_COMPARATOR(pToken2, pComparatorPrefix))(())))

//DID NOT WORK ON VS6. THE LINE #pA IS BUGGY, IN PARTICULAR, #. SEEMS TO BE A BUG IN VS6. THE CONTENT
//		OF pA CHANGES TO SOMETHING INEXPLIPICABLE, BUT RECOGNIZABLE, WHEN USING #.
/*
#define CRXM__TO_C_STRING(...) CRXM__TO_C_STRING__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		CRXM__DO_MACRO_ON_EACH(CRXM__TO_C_STRING_do, __VA_ARGS__))
#define CRXM__TO_C_STRING__ASSERT_VARIABLE_ARGUMENTS_CALL(pFullMacroCall) pFullMacroCall
#define CRXM__TO_C_STRING_do(a, pA) #pA
*/


//USES "CRXM__DO_MACRO_ON_EACH2" WHICH IS UNSTABLE ON OLD COMPILERS
/* 
#define CRXM__TO_C_STRING2(...) CRXM__TO_C_STRING2__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		CRXM__DO_MACRO_ON_EACH2(CRXM__TO_C_STRING2_do, CRXM__TO_C_STRING2_do2, __VA_ARGS__))
#define CRXM__TO_C_STRING2__ASSERT_VARIABLE_ARGUMENTS_CALL(pFullMacroCall) pFullMacroCall
#define CRXM__TO_C_STRING2_do(a, b, pA) pA ## b
#define CRXM__TO_C_STRING2_do2(a) #a
*/

/*
#define _CRXM__TO_C_STRING(A, B) _CRXM__TO_C_STRING_do(A, B)
#define _CRXM__TO_C_STRING_do(A, B) _CRXM__TO_C_STRING_do2(A ## B)
#define _CRXM__TO_C_STRING_do2(A) #A
*/

//
//CRXM__TO_C_STRING3 WORKS, BUT DOES NOT INSIDE #include IN MSVC. IT DOES WORK IF USING 
//"CRXM__RESOLVE_OVERLOADED_MACRO_CALL2", BUT THAT ONE IS NOT WELL DEFINED, AND HENCE REMOVED
//CURRENTLY. SEE NOTES ABOVE.
//
/*
#define CRXM__TO_C_STRING3(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRXM__TO_C_STRING3, __VA_ARGS__)
#define CRXM__TO_C_STRING3__1(p1) \
		CRXM__TO_C_STRING3_do(p1)
#define CRXM__TO_C_STRING3__2(p1,p2) \
		CRXM__TO_C_STRING3_do(p1 ## p2)
#define CRXM__TO_C_STRING3__3(p1,p2,p3) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3)
#define CRXM__TO_C_STRING3__4(p1,p2,p3,p4) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4)
#define CRXM__TO_C_STRING3__5(p1,p2,p3,p4,p5) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5)
#define CRXM__TO_C_STRING3__6(p1,p2,p3,p4,p5,p6) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6)
#define CRXM__TO_C_STRING3__7(p1,p2,p3,p4,p5,p6,p7) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6 ## p7)
#define CRXM__TO_C_STRING3__8(p1,p2,p3,p4,p5,p6,p7,p8) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6 ## p7 ## p8)
#define CRXM__TO_C_STRING3__9(p1,p2,p3,p4,p5,p6,p7,p8,p9) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6 ## p7 ## p8 ## p9)
#define CRXM__TO_C_STRING3__10(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6 ## p7 ## p8 ## p9 ## p10)
#define CRXM__TO_C_STRING3__11(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6 ## p7 ## p8 ## p9 ## p10 ## p11)
#define CRXM__TO_C_STRING3__12(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6 ## p7 ## p8 ## p9 ## p10 ## p11 ## p12)
#define CRXM__TO_C_STRING3__13(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6 ## p7 ## p8 ## p9 ## p10 ## p11 ## p12 ## p13)
#define CRXM__TO_C_STRING3__14(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6 ## p7 ## p8 ## p9 ## p10 ## p11 ## p12 ## p13 ## p14)
#define CRXM__TO_C_STRING3__15(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6 ## p7 ## p8 ## p9 ## p10 ## p11 ## p12 ## p13 ## p14 ## p15)
#define CRXM__TO_C_STRING3__16(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6 ## p7 ## p8 ## p9 ## p10 ## p11 ## p12 ## p13 ## p14 ## p15 ## p16)
#define CRXM__TO_C_STRING3__17(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6 ## p7 ## p8 ## p9 ## p10 ## p11 ## p12 ## p13 ## p14 ## p15 ## p16 ## p17)
#define CRXM__TO_C_STRING3__18(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6 ## p7 ## p8 ## p9 ## p10 ## p11 ## p12 ## p13 ## p14 ## p15 ## p16 ## p17 ## p18)
#define CRXM__TO_C_STRING3__19(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6 ## p7 ## p8 ## p9 ## p10 ## p11 ## p12 ## p13 ## p14 ## p15 ## p16 ## p17 ## p18 ## p19)
#define CRXM__TO_C_STRING3__20(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) \
		CRXM__TO_C_STRING3_do(p1 ## p2 ## p3 ## p4 ## p5 ## p6 ## p7 ## p8 ## p9 ## p10 ## p11 ## p12 ## p13 ## p14 ## p15 ## p16 ## p17 ## p18 ## p19 ## p20)
#define CRXM__TO_C_STRING3_do(pA) CRXM__TO_C_STRING3_do2(pA)
#define CRXM__TO_C_STRING3_do2(pA) #pA
*/

//
//CRXM__TO_C_STRING4 WORKS, BUT DOES NOT INSIDE #include IN MSVC. IT DOES WORK IF USING 
//"CRXM__RESOLVE_OVERLOADED_MACRO_CALL2", BUT THAT ONE IS NOT WELL DEFINED, AND HENCE REMOVED
//CURRENTLY. SEE NOTES ABOVE.
//
//FAILS IN MSVC6. FOR pA = abc, LINE 
//		#define CRXM__TO_C_STRING4_do(pA) CRXM__TO_C_STRING4_do2(pA)
//	HAS THE FIRST pA AS abc, BUT THE SECOND AS a!!!
//
/*
#define CRXM__TO_C_STRING4(...) CRXM__RESOLVE_OVERLOADED_MACRO_CALL(CRXM__TO_C_STRING4, __VA_ARGS__)
#define CRXM__TO_C_STRING4__1(p1) \
		CRXM__TO_C_STRING4_do(p1)
#define CRXM__TO_C_STRING4__2(p1,p2) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2))
#define CRXM__TO_C_STRING4__3(p1,p2,p3) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3))
#define CRXM__TO_C_STRING4__4(p1,p2,p3,p4) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4))
#define CRXM__TO_C_STRING4__5(p1,p2,p3,p4,p5) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5))
#define CRXM__TO_C_STRING4__6(p1,p2,p3,p4,p5,p6) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6))
#define CRXM__TO_C_STRING4__7(p1,p2,p3,p4,p5,p6,p7) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6)CRXM__EVAL(p7))
#define CRXM__TO_C_STRING4__8(p1,p2,p3,p4,p5,p6,p7,p8) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6)CRXM__EVAL(p7)CRXM__EVAL(p8))
#define CRXM__TO_C_STRING4__9(p1,p2,p3,p4,p5,p6,p7,p8,p9) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6)CRXM__EVAL(p7)CRXM__EVAL(p8)CRXM__EVAL(p9))
#define CRXM__TO_C_STRING4__10(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6)CRXM__EVAL(p7)CRXM__EVAL(p8)CRXM__EVAL(p9)CRXM__EVAL(p10))
#define CRXM__TO_C_STRING4__11(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6)CRXM__EVAL(p7)CRXM__EVAL(p8)CRXM__EVAL(p9)CRXM__EVAL(p10)CRXM__EVAL(p11))
#define CRXM__TO_C_STRING4__12(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6)CRXM__EVAL(p7)CRXM__EVAL(p8)CRXM__EVAL(p9)CRXM__EVAL(p10)CRXM__EVAL(p11)CRXM__EVAL(p12))
#define CRXM__TO_C_STRING4__13(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6)CRXM__EVAL(p7)CRXM__EVAL(p8)CRXM__EVAL(p9)CRXM__EVAL(p10)CRXM__EVAL(p11)CRXM__EVAL(p12)CRXM__EVAL(p13))
#define CRXM__TO_C_STRING4__14(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6)CRXM__EVAL(p7)CRXM__EVAL(p8)CRXM__EVAL(p9)CRXM__EVAL(p10)CRXM__EVAL(p11)CRXM__EVAL(p12)CRXM__EVAL(p13)CRXM__EVAL(p14))
#define CRXM__TO_C_STRING4__15(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6)CRXM__EVAL(p7)CRXM__EVAL(p8)CRXM__EVAL(p9)CRXM__EVAL(p10)CRXM__EVAL(p11)CRXM__EVAL(p12)CRXM__EVAL(p13)CRXM__EVAL(p14)CRXM__EVAL(p15))
#define CRXM__TO_C_STRING4__16(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6)CRXM__EVAL(p7)CRXM__EVAL(p8)CRXM__EVAL(p9)CRXM__EVAL(p10)CRXM__EVAL(p11)CRXM__EVAL(p12)CRXM__EVAL(p13)CRXM__EVAL(p14)CRXM__EVAL(p15)CRXM__EVAL(p16))
#define CRXM__TO_C_STRING4__17(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6)CRXM__EVAL(p7)CRXM__EVAL(p8)CRXM__EVAL(p9)CRXM__EVAL(p10)CRXM__EVAL(p11)CRXM__EVAL(p12)CRXM__EVAL(p13)CRXM__EVAL(p14)CRXM__EVAL(p15)CRXM__EVAL(p16)CRXM__EVAL(p17))
#define CRXM__TO_C_STRING4__18(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6)CRXM__EVAL(p7)CRXM__EVAL(p8)CRXM__EVAL(p9)CRXM__EVAL(p10)CRXM__EVAL(p11)CRXM__EVAL(p12)CRXM__EVAL(p13)CRXM__EVAL(p14)CRXM__EVAL(p15)CRXM__EVAL(p16)CRXM__EVAL(p17)CRXM__EVAL(p18))
#define CRXM__TO_C_STRING4__19(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6)CRXM__EVAL(p7)CRXM__EVAL(p8)CRXM__EVAL(p9)CRXM__EVAL(p10)CRXM__EVAL(p11)CRXM__EVAL(p12)CRXM__EVAL(p13)CRXM__EVAL(p14)CRXM__EVAL(p15)CRXM__EVAL(p16)CRXM__EVAL(p17)CRXM__EVAL(p18)CRXM__EVAL(p19))
#define CRXM__TO_C_STRING4__20(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20) \
		CRXM__TO_C_STRING4_do(CRXM__EVAL(p1)CRXM__EVAL(p2)CRXM__EVAL(p3)CRXM__EVAL(p4)CRXM__EVAL(p5)CRXM__EVAL(p6)CRXM__EVAL(p7)CRXM__EVAL(p8)CRXM__EVAL(p9)CRXM__EVAL(p10)CRXM__EVAL(p11)CRXM__EVAL(p12)CRXM__EVAL(p13)CRXM__EVAL(p14)CRXM__EVAL(p15)CRXM__EVAL(p16)CRXM__EVAL(p17)CRXM__EVAL(p18)CRXM__EVAL(p19)CRXM__EVAL(p20))
#define CRXM__TO_C_STRING4_do(pA) CRXM__TO_C_STRING4_do2(pA)
#define CRXM__TO_C_STRING4_do2(pA) #pA
*/



	#pragma endregion //}

#pragma endregion //}


#pragma region CRXMD //{
/*
ABNORMAL MACROS ALLOW INDIRECT RECURSSION USING THE MACROS "CRXMD__CALL" AND "CRXMD__EVALUATE_X_TIMES".

AN ABNORMAL MACRO 'M' THAT TAKES PARAMETERS 'pA' and 'pB' CALLED INSIDE A '#define' MUST BE CALLED USING
"CRXMD__CALL". EXAMPLE:
		#define MY_MACRO(pA, pB) CRXMD__CALL(M)(pA, pB)

BUT WHEN CALLED OUTSIDE A '#define', THE MACRO MUST BE CALLED USING "CRXMD__EVALUATE_X_TIMES", WHERE 'X'
SHOULD BE PICKED TO BE AS SMALL AS POSSIBLE. EXAMPLES
		CRXMD__EVALUATE_X_TIMES(M(1, 2))
OR SOMETHING MORE SOPHISTICATED
		CRXMD__EVALUATE_X_TIMES(M(1, 2) + M(1, 2) MY_MACRO(pA, pB))

DUE TO THE FACT THAT CRXMD__CALL DOES NOT WORK THE SAME WAY IT DOES IN OTHER COMPILERS ASIDE FROM MSVC, AND
		DUE TO SOME BEHAVIOR IN MSVC THAT CONTINUES TO ALLOW CRXMD__EVALUATE_X_TIMES TO WORK, ABNORMAL
		MACROS SHOULD BE DEFINED SUCH AS THEY ARE CONVERGENT. THIS IS BECAUSE A FIXED VALUE FOR 'X' WILL LEAD
		TO DIFFERENT OUTPUTS BETWEEN MSVC AND OTHER COMPILERS. FOR EXAMPLE,

				#define DO1() CRXMD__CALL(DO3)(a)
				#define DO2() CRXMD__CALL(DO1)()
				#define DO3(a) a. CRXMD__CALL(DO2)()

				DO3(_)
				CRXMD__EVALUATE_1_TIMES(DO3(_))
				CRXMD__EVALUATE_2_TIMES(DO3(_))
				CRXMD__EVALUATE_3_TIMES(DO3(_))
				CRXMD__EVALUATE_4_TIMES(DO3(_))
				CRXMD__EVALUATE_5_TIMES(DO3(_))
				CRXMD__EVALUATE_6_TIMES(DO3(_))
				CRXMD__EVALUATE_7_TIMES(DO3(_))
				CRXMD__EVALUATE_8_TIMES(DO3(_))
				CRXMD__EVALUATE_9_TIMES(DO3(_))

		DO3 IS A NON CONVERGENT MACRO. A NON MSVC COMPILER OUTPUTS:
				_. DO2 ()
				_. DO1 ()
				_. a. DO2 ()
				_. a. DO3 (a)
				_. a. a. DO1 ()
				_. a. a. a. DO2 ()
				_. a. a. a. DO3 (a)
				_. a. a. a. a. DO1 ()
				_. a. a. a. a. a. DO2 ()
				_. a. a. a. a. a. DO3 (a)
		A MSVC COMPILER OUTPUTS
				_. DO3  (a)
				_. a. DO2  ()
				_. a. DO1  ()
				_. a. DO3  (a)
				_. a. a. DO2  ()
				_. a. a. DO1  ()
				_. a. a. DO3  (a)
				_. a. a. a. DO2  ()
				_. a. a. a. DO1  ()
				_. a. a. a. DO3  (a)

		IF YOU STUDY THE ABOVE YOU ARRIVE TO THE CONCLUSION THAT THE MSVC COMPILER CONTINUES TO SEE, AND PAINT
		BLUE PREVIOUSLY SEEN MACROS DESPITE "CRXMD__CALL". HOWEVER, THINGS CONTINUE TO ADVANCE WHICH EACH
		REEVALUATION.

		IF TARGETTING ONE SPECIFIC COMPILER, THEN NON CONVERGENT ABNORMAL MACROS COULD BE DEFINED AND USED, BUT
		OTHERWISE, ONE SHOULD STICK TO CONVERGENT COMPILERS.
*/




//CRXMD__EVALUATE AND CRXMD__CALL ARE MEANT TO ALLOW RECURSIVE CALLING. SEE BELOW.
//ENABLE THE FOLLOWG LINE INSTEAD IF YOU WANT EXACT NUMBER OF RE EVALUATIONS. THE REASON THINGS ARE DONE 
//		LIKE IN THE CODE BELOW FOR "CRXMD__EVALUATE_1_TIMES" IS TO AVOID THE MSVC++ __VA_ARGS__ BUG/DIFFERENT
//		BEHAVIOR WHICH WHAT THE 'CRXM__RESOLVE_MACRO_CALL2' IS FOR EXPLICITLY, BUT I DID NOT WANT TO USE IT IN THIS
//		MACRO.
//		#define CRXMD__EVALUATE_1_TIMES(...) __VA_ARGS__
#define CRXMD__EVALUATE(...) __VA_ARGS__
#define CRXMD__EVALUATE_1024_TIMES(...) CRXMD__EVALUATE_512_TIMES(CRXMD__EVALUATE_512_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_512_TIMES(...) CRXMD__EVALUATE_256_TIMES(CRXMD__EVALUATE_256_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_256_TIMES(...) CRXMD__EVALUATE_128_TIMES(CRXMD__EVALUATE_128_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_128_TIMES(...) CRXMD__EVALUATE_64_TIMES(CRXMD__EVALUATE_64_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_64_TIMES(...) CRXMD__EVALUATE_32_TIMES(CRXMD__EVALUATE_32_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_32_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_16_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_16_TIMES(...) CRXMD__EVALUATE_8_TIMES(CRXMD__EVALUATE_8_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_8_TIMES(...) CRXMD__EVALUATE_4_TIMES(CRXMD__EVALUATE_4_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_4_TIMES(...) CRXMD__EVALUATE_2_TIMES(CRXMD__EVALUATE_2_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_2_TIMES(...) CRXMD__EVALUATE_1_TIMES(CRXMD__EVALUATE_1_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_1_TIMES(...) __VA_ARGS__
//#define CRXMD__EVALUATE_1_TIMES(...) CRXMD__EVALUATE_1_TIMES__DO1(CRXMD__EVALUATE_1_TIMES__DO2(__VA_ARGS__))
//#define CRXMD__EVALUATE_1_TIMES__DO1(X) X
//#define CRXMD__EVALUATE_1_TIMES__DO2(...) __VA_ARGS__

#define CRXMD__EVALUATE_729_TIMES(...) CRXMD__EVALUATE_243_TIMES(CRXMD__EVALUATE_243_TIMES(CRXMD__EVALUATE_243_TIMES(__VA_ARGS__)))
#define CRXMD__EVALUATE_243_TIMES(...) CRXMD__EVALUATE_81_TIMES(CRXMD__EVALUATE_81_TIMES(CRXMD__EVALUATE_81_TIMES(__VA_ARGS__)))
#define CRXMD__EVALUATE_81_TIMES(...) CRXMD__EVALUATE_27_TIMES(CRXMD__EVALUATE_27_TIMES(CRXMD__EVALUATE_27_TIMES(__VA_ARGS__)))
#define CRXMD__EVALUATE_27_TIMES(...) CRXMD__EVALUATE_9_TIMES(CRXMD__EVALUATE_9_TIMES(CRXMD__EVALUATE_9_TIMES(__VA_ARGS__)))
#define CRXMD__EVALUATE_9_TIMES(...) CRXMD__EVALUATE_3_TIMES(CRXMD__EVALUATE_3_TIMES(CRXMD__EVALUATE_3_TIMES(__VA_ARGS__)))
#define CRXMD__EVALUATE_3_TIMES(...) CRXMD__EVALUATE_2_TIMES(CRXMD__EVALUATE_1_TIMES(__VA_ARGS__))

#define CRXMD__EVALUATE_5_TIMES(...) CRXMD__EVALUATE_4_TIMES(CRXMD__EVALUATE_1_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_6_TIMES(...) CRXMD__EVALUATE_4_TIMES(CRXMD__EVALUATE_2_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_7_TIMES(...) CRXMD__EVALUATE_4_TIMES(CRXMD__EVALUATE_3_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_10_TIMES(...) CRXMD__EVALUATE_8_TIMES(CRXMD__EVALUATE_2_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_11_TIMES(...) CRXMD__EVALUATE_8_TIMES(CRXMD__EVALUATE_3_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_12_TIMES(...) CRXMD__EVALUATE_8_TIMES(CRXMD__EVALUATE_4_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_13_TIMES(...) CRXMD__EVALUATE_8_TIMES(CRXMD__EVALUATE_5_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_14_TIMES(...) CRXMD__EVALUATE_8_TIMES(CRXMD__EVALUATE_6_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_15_TIMES(...) CRXMD__EVALUATE_8_TIMES(CRXMD__EVALUATE_7_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_17_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_1_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_18_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_2_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_19_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_3_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_20_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_4_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_21_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_5_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_22_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_6_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_23_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_7_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_24_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_8_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_25_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_9_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_26_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_10_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_28_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_12_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_29_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_13_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_30_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_14_TIMES(__VA_ARGS__))
#define CRXMD__EVALUATE_31_TIMES(...) CRXMD__EVALUATE_16_TIMES(CRXMD__EVALUATE_15_TIMES(__VA_ARGS__))

//EVALUATES 1 + pN TIMES ON NON MSVC COMPILERS, AND 2 + pN ON MSVC COMPILERS.
#define CRXMD__REEVALUATE(pN, ...) CRXMD__REEVALUATE__GET_CALL(pN, __VA_ARGS__)
#define CRXMD__REEVALUATE__GET_CALL(pN, ...) CRXMD__REEVALUATE_ ## pN ## _TIMES(__VA_ARGS__)


//THE FOLLOWING DISABLES A MACRO FROM EVALUATING. THIS HOWEVER ONLY WORKS THIS WAY FOR NON MSVC COMPILERS. FOR MSVC
//		COMPILERS HOWEVER, THE NET EFFECT IS STILL TO ALLOW ABNORMAL MACROS. 
//		HOWEVER, THE FOLLOWING DOES NOT HIDE THE MACRO NAME FROM THE PREPROCESSOR SO THAT IT IS NOT PAINTED BLUE. 
//		THE FOLLOWING EXAMPLES ARE FOR A NON MSVC COMPILER. GCC WAS USED.
//
//		TAKE THE EXAMPLE:
//			#define C() f CRXMD__CALL(C)()
//
//			C()								OUTPUT: f C()
//			CRXMD__EVALUATE_1_TIMES(C())	OUTPUT: f C()
//		NOTICE HOW C() WAS STILL SEEN BY THE PREPROCESSOR, AND THUS 'PAINTED BLUE'
//
//		IF WE DO:
//			#define C() f CRXMD__CALL(C2)()
//			#define C2() C()
//
//			C()								OUTPUT: f C2()
//			CRXMD__EVALUATE_1_TIMES(C())	OUTPUT: f f C2()
//			CRXMD__EVALUATE_2_TIMES(C())	OUTPUT: f f C2()
//		THIS TIME C2 GOT PAINTED BLUE AFTER CRXMD__EVALUATE_1_TIMES CALL, IT WOULD SEEM
//
//		TO UNDERSTAND, THE PROCESS FOR THE LINE  "CRXMD__EVALUATE_1_TIMES(C())" WAS
//			[EXPLANATION 1: IN THIS THE MACRO ITSELF IS EITHER "NOT SEEN", "SEEN" OR "BLUE"]
//				CONTEXT OPENED ON "CRXMD__EVALUATE_2_TIMES(C())"
//				{
//					EVALUATING 	"CRXMD__EVALUATE_2_TIMES(C())"
//					CONTEXT OPENED FOR PARAMETER "C()"
//					{
//						EVALUATING "C()"
//						RUNNING "C()"
//						"C()" IS SEEN, 
//						"C2()" IS SEEN
//						OUTPUT: f C2()
//					}CONTEXT CLOSED	=> "C()" UNSEEN, "C2()" UNSEEN
//					RUNNING "CRXMD__EVALUATE_2_TIMES(f C2())"
//					"CRXMD__EVALUATE_2_TIMES()" IS SEEN
//					OUTPUT: "CRXMD__EVALUATE_1_TIMES(CRXMD__EVALUATE_1_TIMES(f C2()))"
//					EVALUATING "CRXMD__EVALUATE_1_TIMES(CRXMD__EVALUATE_1_TIMES(f C2()))"
//					CONTEXT OPENED FOR PARAMETER "CRXMD__EVALUATE_1_TIMES(f C2())"
//					{
//						EVALUATING "CRXMD__EVALUATE_1_TIMES(f C2())"
//						CONTEXT OPENED FOR PARAMETER f C2()
//						{
//							EVALUATING "f C2()"
//							RUNNING "C2()" FROM "f C2()"
//							"C2()" IS SEEN
//							"C()" IS SEEN
//							"C2()" IS BLUED
//							OUTPUT "f f C2()"
//						}CONTEXT CLOSED => "C2()" IS BLUE AND SO REMAINS BLUE, "C()" UNSEEN
//						RUNNING "CRXMD__EVALUATE_1_TIMES(f f C2())"
//						"CRXMD__EVALUATE_1_TIMES" IS SEEN
//						OUTPUT "f f C2()"
//						EVALUATING "f f C2()"
//						OUTPUT "f f C2()"		"C2()" IS BLUE AND SO NOT RUN
//
//
//
//					}CONTEXT CLOSED => "C2()" IS BLUE AND SO REMAINS BLUE, "CRXMD__EVALUATE_1_TIMES" UNSEEN
//					RUNNING "CRXMD__EVALUATE_1_TIMES(f f C2())"
//					"CRXMD__EVALUATE_1_TIMES" IS SEEN
//					OUTPUT "f f C2()"
//					EVALUATING "f f C2()"
//
//
//
//					OUTPUT "f f C2()"	"C2()" IS BLUE AND SO NOT RUN
//				}CONTEXT CLOSED, EVERYTHING UNSEEN NOW THAT WE ARE BACK TO GLOBAL SCOPE.
//
//			[EXPLANATION 2: IN THIS THE MACRO ITSELF IS "NOT SEEN" OR "SEEN". WHEN "SEEN",
//					ANY TOKEN (NOT MACRO, BUT TOKEN. THINK STRING PARSING) THAT HAS THE SAME
//					NAME AS THE SEEN MACRO IS PERMANENTLY MARKED BLUE.]
//				CONTEXT OPENED ON "CRXMD__EVALUATE_2_TIMES(C())"
//				{
//					EVALUATING 	"CRXMD__EVALUATE_2_TIMES(C())"
//					CONTEXT OPENED FOR PARAMETER "C()"
//					{
//						EVALUATING "C()"
//						RUNNING "C()"
//						"C()" IS SEEN, 
//						"C2()" IS SEEN
//						OUTPUT: f C2()
//					}CONTEXT CLOSED	=> "C()" UNSEEN, "C2()" UNSEEN
//					RUNNING "CRXMD__EVALUATE_2_TIMES(f C2())"
//					"CRXMD__EVALUATE_2_TIMES()" IS SEEN
//					OUTPUT: "CRXMD__EVALUATE_1_TIMES(CRXMD__EVALUATE_1_TIMES(f C2()))"
//					EVALUATING "CRXMD__EVALUATE_1_TIMES(CRXMD__EVALUATE_1_TIMES(f C2()))"
//					CONTEXT OPENED FOR PARAMETER "CRXMD__EVALUATE_1_TIMES(f C2())"
//					{
//						EVALUATING "CRXMD__EVALUATE_1_TIMES(f C2())"
//						CONTEXT OPENED FOR PARAMETER f C2()
//						{
//							EVALUATING "f C2()"
//							RUNNING "C2()" FROM "f C2()"
//							"C2()" IS SEEN
//							"C()" IS SEEN
//
//							OUTPUT "f f C2()" WITH TOKEN 'C2' MARKED BLUE
//						}CONTEXT CLOSED => "C2()" UNSEEN, "C()" UNSEEN
//						RUNNING "CRXMD__EVALUATE_1_TIMES(f f C2())" WITH 'C2' BEING BLUE
//						"CRXMD__EVALUATE_1_TIMES" IS SEEN
//						OUTPUT "f f C2()" WITH 'C2' BEING BLUE
//						EVALUATING "f f C2()" WITH 'C2' BEING BLUE
//						OUTPUT "f f C2()" THE TOKEN 'C2' IS BLUE AND LEFT AS IS
//
//
//
//					}CONTEXT CLOSED => "CRXMD__EVALUATE_1_TIMES" UNSEEN
//					RUNNING "CRXMD__EVALUATE_1_TIMES(f f C2())" WITH 'C2' BEING BLUE
//					"CRXMD__EVALUATE_1_TIMES" IS SEEN
//					OUTPUT "f f C2()"  WITH 'C2' BEING BLUE
//					EVALUATING "f f C2()" WITH 'C2' BEING BLUE
//
//
//
//					OUTPUT "f f C2()"	'C2' IS BLUE AND LEFT AS IS
//				}CONTEXT CLOSED, EVERYTHING UNSEEN NOW THAT WE ARE BACK TO GLOBAL SCOPE.
//
//		AND IF WE DO
//			#define C() f CRXMD__CALL(C2)()
//			#define C2() CRXMD__CALL(C)()
//
//			C()								OUTPUT: f C2()
//			CRXMD__EVALUATE_1_TIMES(C())	OUTPUT: f C()
//			CRXMD__EVALUATE_2_TIMES(C())	OUTPUT: f f C()
//			CRXMD__EVALUATE_4_TIMES(C())	OUTPUT: f f f f C()
//		NOW THINGS WORK CORRECTLY.
//		POINT IS, CRXMD__CALL, DISABLES A MACRO CALL, NOT HIDE IT FROM THE PREPROCESSOR, AND THUS THE
//		PREPROCESSOR CAN STILL END UP PAINTING THE MACRO BLUE.
//
//		TO UNDERSTAND, THE PROCESS FOR THE LINE  "CRXMD__EVALUATE_1_TIMES(C())" WAS
//			[EXPLANATION 1: IN THIS THE MACRO ITSELF IS EITHER "NOT SEEN", "SEEN" OR "BLUE"]
//				CONTEXT OPENED ON "CRXMD__EVALUATE_2_TIMES(C())"
//				{
//					EVALUATING 	"CRXMD__EVALUATE_2_TIMES(C())"
//					CONTEXT OPENED FOR PARAMETER "C()"
//					{
//						EVALUATING "C()"
//						RUNNING "C()"
//						"C()" IS SEEN, 
//						"C2()" IS SEEN
//						OUTPUT: f C2()
//					}CONTEXT CLOSED	=> "C()" UNSEEN, "C2()" UNSEEN
//					RUNNING "CRXMD__EVALUATE_2_TIMES(f C2())"
//					"CRXMD__EVALUATE_2_TIMES()" IS SEEN
//					OUTPUT: "CRXMD__EVALUATE_1_TIMES(CRXMD__EVALUATE_1_TIMES(f C2()))"
//					EVALUATING "CRXMD__EVALUATE_1_TIMES(CRXMD__EVALUATE_1_TIMES(f C2()))"
//					CONTEXT OPENED FOR PARAMETER "CRXMD__EVALUATE_1_TIMES(f C2())"
//					{
//						EVALUATING "CRXMD__EVALUATE_1_TIMES(f C2())"
//						CONTEXT OPENED FOR PARAMETER f C2()
//						{
//							EVALUATING "f C2()"
//							RUNNING "C2()" FROM "f C2()"
//							"C2()" IS SEEN
//							"C()" IS SEEN
//		
//							OUTPUT "f C()"
//						}CONTEXT CLOSED => "C2()" UNSEEN, "C()" UNSEEN
//						RUNNING "CRXMD__EVALUATE_1_TIMES(f C())"
//						"CRXMD__EVALUATE_1_TIMES" IS SEEN
//						OUTPUT "f C()"
//						EVALUATING "f C()"
//						RUNNING "C()" FROM "f C()"
//						"C()" IS SEEN
//						"C2()" IS SEEN
//						OUTPUT "f f C2()"
//					}CONTEXT CLOSED => "C()" UNSEEN, "C2()" UNSEEN, "CRXMD__EVALUATE_1_TIMES" UNSEEN
//					RUNNING "CRXMD__EVALUATE_1_TIMES(f f C2())"
//					"CRXMD__EVALUATE_1_TIMES" IS SEEN
//					OUTPUT f f C2()
//					EVALUATING "f f C2()"
//					RUNNING "C2()" FROM "f f C2()"
//					"C2()" IS SEEN
//					"C()" IS SEEN
//					OUTPUT "f f C()"
//				}CONTEXT CLOSED, EVERYTHING UNSEEN NOW THAT WE ARE BACK TO GLOBAL SCOPE.
//
#define CRXMD__CALL(pMacroName) pMacroName CRXMD__CALL__GET_EMPTY()
#define CRXMD__CALL__GET_EMPTY() 


/*
THE FOLLOWING IS LIKE CRXM__REPEAT_MACRO, BUT ALLOWS NESTED LOOPING.
		FOR EXAMPLE:
			#define A(N, ...)   CRXMD__REPEAT_MACRO(3, B, N)
			#define B(N2, N1, ...) [N1, N2]
			CRXMD__EVALUATE_2_TIMES(CRXMD__REPEAT_MACRO(2, A))		OUTPUT: [1, 1] [1, 2] [1, 3] [2, 1] [2, 2] [2, 3]
*/
#define CRXMD__REPEAT_MACRO(pNumber, pMacro, ...) CRXMD__REPEAT_MACRO__GET_DO(pNumber)(pMacro, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__GET_DO(pNumber) CRXMD__REPEAT_MACRO__DO ## pNumber
#define CRXMD__REPEAT_MACRO__DO50(pMacro, ...) CRXMD__REPEAT_MACRO__DO49(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(50, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO49(pMacro, ...) CRXMD__REPEAT_MACRO__DO48(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(49, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO48(pMacro, ...) CRXMD__REPEAT_MACRO__DO47(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(48, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO47(pMacro, ...) CRXMD__REPEAT_MACRO__DO46(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(47, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO46(pMacro, ...) CRXMD__REPEAT_MACRO__DO45(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(46, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO45(pMacro, ...) CRXMD__REPEAT_MACRO__DO44(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(45, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO44(pMacro, ...) CRXMD__REPEAT_MACRO__DO43(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(44, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO43(pMacro, ...) CRXMD__REPEAT_MACRO__DO42(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(43, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO42(pMacro, ...) CRXMD__REPEAT_MACRO__DO41(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(42, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO41(pMacro, ...) CRXMD__REPEAT_MACRO__DO40(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(41, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO40(pMacro, ...) CRXMD__REPEAT_MACRO__DO39(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(40, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO39(pMacro, ...) CRXMD__REPEAT_MACRO__DO38(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(39, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO38(pMacro, ...) CRXMD__REPEAT_MACRO__DO37(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(38, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO37(pMacro, ...) CRXMD__REPEAT_MACRO__DO36(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(37, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO36(pMacro, ...) CRXMD__REPEAT_MACRO__DO35(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(36, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO35(pMacro, ...) CRXMD__REPEAT_MACRO__DO34(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(35, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO34(pMacro, ...) CRXMD__REPEAT_MACRO__DO33(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(34, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO33(pMacro, ...) CRXMD__REPEAT_MACRO__DO32(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(33, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO32(pMacro, ...) CRXMD__REPEAT_MACRO__DO31(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(32, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO31(pMacro, ...) CRXMD__REPEAT_MACRO__DO30(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(31, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO30(pMacro, ...) CRXMD__REPEAT_MACRO__DO29(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(30, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO29(pMacro, ...) CRXMD__REPEAT_MACRO__DO28(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(29, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO28(pMacro, ...) CRXMD__REPEAT_MACRO__DO27(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(28, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO27(pMacro, ...) CRXMD__REPEAT_MACRO__DO26(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(27, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO26(pMacro, ...) CRXMD__REPEAT_MACRO__DO25(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(26, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO25(pMacro, ...) CRXMD__REPEAT_MACRO__DO24(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(25, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO24(pMacro, ...) CRXMD__REPEAT_MACRO__DO23(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(24, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO23(pMacro, ...) CRXMD__REPEAT_MACRO__DO22(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(23, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO22(pMacro, ...) CRXMD__REPEAT_MACRO__DO21(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(22, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO21(pMacro, ...) CRXMD__REPEAT_MACRO__DO20(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(21, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO20(pMacro, ...) CRXMD__REPEAT_MACRO__DO19(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(20, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO19(pMacro, ...) CRXMD__REPEAT_MACRO__DO18(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(19, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO18(pMacro, ...) CRXMD__REPEAT_MACRO__DO17(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(18, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO17(pMacro, ...) CRXMD__REPEAT_MACRO__DO16(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(17, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO16(pMacro, ...) CRXMD__REPEAT_MACRO__DO15(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(16, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO15(pMacro, ...) CRXMD__REPEAT_MACRO__DO14(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(15, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO14(pMacro, ...) CRXMD__REPEAT_MACRO__DO13(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(14, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO13(pMacro, ...) CRXMD__REPEAT_MACRO__DO12(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(13, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO12(pMacro, ...) CRXMD__REPEAT_MACRO__DO11(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(12, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO11(pMacro, ...) CRXMD__REPEAT_MACRO__DO10(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(11, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO10(pMacro, ...) CRXMD__REPEAT_MACRO__DO9(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(10, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO9(pMacro, ...) CRXMD__REPEAT_MACRO__DO8(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(9, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO8(pMacro, ...) CRXMD__REPEAT_MACRO__DO7(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(8, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO7(pMacro, ...) CRXMD__REPEAT_MACRO__DO6(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(7, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO6(pMacro, ...) CRXMD__REPEAT_MACRO__DO5(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(6, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO5(pMacro, ...) CRXMD__REPEAT_MACRO__DO4(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(5, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO4(pMacro, ...) CRXMD__REPEAT_MACRO__DO3(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(4, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO3(pMacro, ...) CRXMD__REPEAT_MACRO__DO2(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(3, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO2(pMacro, ...) CRXMD__REPEAT_MACRO__DO1(pMacro, __VA_ARGS__) CRXMD__CALL(pMacro)(2, __VA_ARGS__)
#define CRXMD__REPEAT_MACRO__DO1(pMacro, ...) CRXMD__CALL(pMacro)(1, __VA_ARGS__)

#pragma endregion //}

#pragma region CRXM__LIST //{
#define CRXM__LIST__GET_CONTENT(pList) CRXM__LIST__GET_CONTENT__DO pList
#define CRXM__LIST__GET_CONTENT__DO(...) __VA_ARGS__

#define CRXM__LIST__GET_LENGTH(pList) CRXM__LIST__GET_LENGTH__DO( \
		CRXM__LIST__GET_CONTENT(pList))
#define CRXM__LIST__GET_LENGTH__DO(pA) CRXM__IFELSE2(CRXM__IS_EMPTY(pA), 0, CRXM__GET_NUMBER_OF_ARGUMENTS(pA))

#define CRXM__LIST__GET_FIRST(pList) CRXM__LIST__GET_FIRST__DO( \
		CRXM__LIST__GET_CONTENT(pList))
#define CRXM__LIST__GET_FIRST__DO(...) CRXM__LIST__GET_FIRST__DO2(__VA_ARGS__)
#define CRXM__LIST__GET_FIRST__DO2(...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		CRXM__LIST__GET_FIRST__DO3(__VA_ARGS__))
#define CRXM__LIST__GET_FIRST__DO3(pA, ...) pA

#define CRXM__LIST__GET_WITHOUT_FIRST(pList) CRXM__LIST__GET_WITHOUT_FIRST__DO( \
		CRXM__LIST__GET_CONTENT(pList))
#define CRXM__LIST__GET_WITHOUT_FIRST__DO(...) CRXM__LIST__GET_WITHOUT_FIRST__DO2(__VA_ARGS__)
#define CRXM__LIST__GET_WITHOUT_FIRST__DO2(...) CRXM__ASSERT_VARIABLE_ARGUMENTS_CALL( \
		CRXM__LIST__GET_WITHOUT_FIRST__DO3(__VA_ARGS__))
#define CRXM__LIST__GET_WITHOUT_FIRST__DO3(pA, ...) __VA_ARGS__
#pragma endregion //}

#pragma region CRXM__LISTCONTENT //{

#define CRXM__LISTCONTENT__GET_FIRST(pA, ...) pA
#define CRXM__LISTCONTENT__GET_WITHOUT_FIRST(pA, ...) __VA_ARGS__

#pragma endregion //}

#pragma region CRX //{

#if(defined(FEATURE_PAL))
	#if(!defined(alloca))
		#if(!defined(_alloca))
			#define CRX__ALLOCA __builtin_alloca
		#else
			#define CRX__ALLOCA _alloca
		#endif
	#else
		#define CRX__ALLOCA alloca
	#endif
#elif(defined(__linux__))
	#define CRX__ALLOCA alloca
#elif defined __GNUC__
	#define CRX__ALLOCA __builtin_alloca
#elif defined _AIX
	#define CRX__ALLOCA __alloca
#elif defined(_MSC_VER)
	#define CRX__ALLOCA _alloca
#else
	#if(defined(BOOST_STATIC_ASSERT)
		#define CRX__ALLOCA(T)	NULL; BOOST_STATIC_ASSERT(false);
	#else
		#define CRX__ALLOCA(T)	<-- ALLOCA WAS NOT FOUND IN THIS ENVIRONMENT -->; 
	#endif
#endif

#if(defined(FEATURE_PAL))
	#if(!defined(alloca))
		#if(!defined(_alloca))
			#define CRX__ALLOCATE_STACK_ARRAY(pTYPE, pVARIABLE_NAME, pCOUNT) \
					pTYPE * pVARIABLE_NAME = __builtin_alloca(sizeof(pTYPE) * pCOUNT)
		#else
			#define CRX__ALLOCATE_STACK_ARRAY(pTYPE, pVARIABLE_NAME, pCOUNT) \
					pTYPE * pVARIABLE_NAME = _alloca(sizeof(pTYPE) * pCOUNT)
		#endif
	#else
		#define CRX__ALLOCATE_STACK_ARRAY(pTYPE, pVARIABLE_NAME, pCOUNT) \
				pTYPE * pVARIABLE_NAME = alloca(sizeof(pTYPE) * pCOUNT)
	#endif
#elif(defined(__linux__))
	#define CRX__ALLOCATE_STACK_ARRAY(pTYPE, pVARIABLE_NAME, pCOUNT) \
			pTYPE * pVARIABLE_NAME = alloca(sizeof(pTYPE) * pCOUNT)
#elif defined __GNUC__
	#define CRX__ALLOCATE_STACK_ARRAY(pTYPE, pVARIABLE_NAME, pCOUNT) \
			pTYPE * pVARIABLE_NAME = __builtin_alloca(sizeof(pTYPE) * pCOUNT)
#elif defined _AIX
	#define CRX__ALLOCATE_STACK_ARRAY(pTYPE, pVARIABLE_NAME, pCOUNT) \
			pTYPE * pVARIABLE_NAME = __alloca(sizeof(pTYPE) * pCOUNT)
#elif defined(_MSC_VER)
	#define CRX__ALLOCATE_STACK_ARRAY(pTYPE, pVARIABLE_NAME, pCOUNT) \
			pTYPE * pVARIABLE_NAME = _alloca(sizeof(pTYPE) * pCOUNT)
#elif(defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))
	/*C99*/
	#define CRX__ALLOCATE_STACK_ARRAY(pTYPE, pVARIABLE_NAME, pCOUNT) \
			pTYPE * pVARIABLE_NAME[pCOUNT]
#else
	#define CRX__ALLOCATE_STACK_ARRAY(pTYPE, pVARIABLE_NAME, pCOUNT) \
			unsigned char _ ## pVARIABLE_NAME[512]; \
			pTYPE * pVARIABLE_NAME = ((pTYPE *) _ ## pVARIABLE_NAME); assert((sizeof(pTYPE) * pCOUNT) <= 512)
#endif

	#pragma region CRX__PREPROCESSOR //{
#if(defined(__cplusplus))
	#define CRX__PREPROCESSOR__HAS_PUSH_MACRO CRXM__TRUE
#else
	#if(defined(__GNUC__))
		#if(!defined(__clang__))
			#if((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)))
				#define CRX__PREPROCESSOR__HAS_PUSH_MACRO CRXM__TRUE
			#else
				#define CRX__PREPROCESSOR__HAS_PUSH_MACRO CRXM__FALSE
			#endif
		#else
			#define CRX__PREPROCESSOR__HAS_PUSH_MACRO CRXM__FALSE
		#endif
	#elif(defined(_MSC_VER))
		#define CRX__PREPROCESSOR__HAS_PUSH_MACRO CRXM__TRUE
	#else
		#define CRX__PREPROCESSOR__HAS_PUSH_MACRO CRXM__FALSE
	#endif
#endif
	#pragma endregion //}

	#pragma region CRX__LIB //{
#define CRX__LIB__PRIVATE__IS_AUTOMATED 0
//THE FOLLOWING IS NOT RELIABLE, AND CURRENTLY ONLY USEFUL ON MSVC. DETECTING MSVC, HOWEVER
//		IS NOT SIMPLE
//https://developercommunity.visualstudio.com/content/problem/300686/static-inline-class-variables-have-their-destructo.html
#if(defined(__cplusplus) && (__cplusplus > 201704L))//(__cplusplus > 201703L)
	#define CRX__LIB__STATIC_INLINE_DATA_MEMBERS_ARE_SUPPORTED
#endif

/* LIB CONFIGS
#define CRX__LIB__CONFIG__FAVOR_STATIC_INLINE
*/

		#pragma region AUTOMATED IMPLEMENTATION //{
		#if(CRX__LIB__PRIVATE__IS_AUTOMATED)

/* LIB: C++ case
CRX LIB IS TO ALLOW ONE TO BUILD A LIBRARY SUCH AS,
	1- 
		A- CLIENT CAN CONFIGURE THE LIBRARY. THIS USES DEFINES. THIS ENDS UP IMPLYING 
			THAT A LIBRARY SHOULD HAVE THE POSSIBILITY OF BEING A HEADER ONLY LIBRARY.
			CLIENT CONFIGURING LIBRARY MEANS CONFIGURATION THAT AFFECT HOW THE LIBRARY
			BEHAVES.
		B- CLIENT DEFINES MADE BY CLIENT CODE CAN BE PROPOGATED INTO THE LIBRARY WITHOUT 
			THE HELP OF THE COMPILER. THIS IS NEEDED TO BECAUSE COMPILER AIDED
			DEFINES ARE HIDDEN, UNLIKE DEFINES MADE EXPLICITLY IN CODE WHICH ARE MORE
			OBVIOUS. FURTHER MORE, DEFINES MADE AT THE COMPILER BREAK MY STANDARD THAT
			REQUIRE DEFINES TO HAVE VALUES, EVEN IF EMPTY. ON THE OTHER HAND
			DEFINES MADE AT THE COMPILER LEVEL HAVE A VALUES THAT IS EQUAL TO THEIR
			EXISTANCE RATHER THAN THEIR VALUE. HENCE THESE WOULD USED THINGS LIKE
			defined() WHEN CHECKED FOR.
	2- THE LIBRARY CAN BE USED AS A STATIC/DYNAMIC, OR HEADER ONLY LIBRARY. REMEMBER,
			FOR EXAMPLE THAT AS A HEADER ONLY LIBRARY IT SHOULD HAVE THE ADVANTAGE OF 
			HEADER ONLY LIBRARY WHICH GENERALY USE TEMPLATES, MAKING CODE FALL
			INTO THE PARADIGM OF OTHER LANGUAGES WHERE YOU DO NOT HAVE TO WORRY
			ABOUT ODR. REMEMBER ODR CAN NOT BE SOLVED WITH INCLUDE GUARDS OR
			pragma once. ODR IS AN ISSUE OF THE SAME SYMBOL DEFINED IN MULTIPLE
			COMPILATION UNITS. BY CRX LIB, THE CODE, EVEN THOUGH IT MIGHT BE
			NOT A TEMPLATE ONLY LIBRARY, WOULD STILL BEHAVE IN THIS PARADIGM
			WHEN USED AS A HEADER ONLY LIBRARY.

POSSIBLE SCENARIOS:
	A- CRXed LIBRARY ITSELF IS A PRE COMPILED STATIC LIBRARY, OR PERHAPS DLL. 
			IN THIE CASE, THE ENTIRE LIBRARY'S CPP FILES ARE THEMSELVES COMPILED. THE 
			LIBRARY MIGHT USE OTHER CRXed LIBRARIES THAT ARE NOT NECESSARY THEMSELVES
			PRE COMPILED. 
			IN THIS CASE, THE CLIENT IS ONLY GIVEN, AND ONLY USES, THE ".h" FILES OF THE
			CRXed LIBRARY.
			IN THIS CASE, THE CRXed LIBRARY CAN NOT BE CONFIGURED BY CLIENT CODE BECAUSE IT 
			IS ALREADY COMPILED. NOTE THAT THIS IS NOT TO BE CONFUSED WITH THE CONFIGURATION
			THAT THE CLIENT STILL NEEDS TO SET WHEN USING THE LIBRARY, WHICH MUST MATCH
			THE CONFIGURATION SET WHEN THE LIBRARY WAS COMPILED. THE CLIENT CONFIGURATION ARE
			SIMPLY ABOUT USING THE LIBRARY CORRECTLY, RATHER THAN DEFINING ITS BEHAVIOR.
			IN THIS CASE, CONFIGURATION IS SET AS CODE, BUT NOT BY CLIENT. THIS IS DONE IN
			THE stafx.h FILE.
	B- CRXed LIBRARY ITSELF IS A PRE COMPILED STATIC LIBRARY, OR PERHAPS DLL, HOWEVER
			IT IS OPEN SOURCE.
			IN THIS CASE, CLIENT CODE COMPILES THE CPP FILES OF THE CRXed LIBRARY HIMSELF.
			IN THIS CASE, THE CLIENT CONTINUES TO USE ONLY ".h" FILES OF THE CRXed LIBRARY.
			IN THIS CASE, THE CRXed LIBRARY CAN BE CONFIGURED BY CLIENT. THIS IS NOT
			TO BE CONFUSED WITH THE CONFIGURATION THAT THE CLIENT STILL NEEDS TO SET WHEN 
			USING THE LIBRARY, WHICH MUST MATCH THE CONFIGURATION SET WHEN THE LIBRARY WAS
			COMPILED, MEANING THE CONFIGURATION IN THE stdafx.h FILE
			IN THIS CASE, CONFIGURATION IS SET AS CODE. THIS IS DONE IN THE stdafx.h FILE.
			<DEPRECATED>IN THIS CASE, THE CLIENT CODE WOULD NOT BE ABLE TO CONFIGURE THE CODE FROM 
			WITHIN HIS CODE BECAUSE THE DEFINES WOULD NOT PROPOGATE TO THE CRXed LIBRARY
			IN QUESTION, BUT UNLIKE SCENARIO 'A' THE CLIENT CAN STILL CONFIGURE THE 
			LIBRARY USING THE DEFINES SET AT THE COMMAND LINE LEVEL.</DEPRECATED>
	C- CRXed LIBRARY ITSELF IS A HEADER ONLY LIBRARY. 
			IN THIS CASE, THE LIBRARY'S CPP FILES ARE NOT COMPILED, AND NEITHER
			DOES CLIENT COMPILES THE CPP FILES OF THIS LIBRARY HIMSELF (THAT WOULD BE SCENARIO
			'B' ABOVE). 
			IN THIS CASE, THE CRXed LIBRARY CODE ACTS UNDER THE NON ODR PARADIGM.
			IN THIS CASE, THE CLIENT USES ".cpp.h" FILES OF THE CRXed LIBRARY AND WOULD HAVE
			HIS OWN CPP FILES THAT INCLUDES THE CRXed LIBRARY CODE TO COMPILE.
			IN THIS CASE, THE CLIENT NEVER USES THE ".h" FILES OF THIS LIBRARY.
			IN THIS CASE, THE CRXed LIBRARY CAN BE CONFIGURED BY CLIENT.
			IN THIS CASE, CONFIGURATION IS SET AS CODE, AND THE CLIENT IS ABLE TO DECIDE
			WHERE TO DO THIS IN HIS CODE.
			IN THIS CASE, THE CLIENT CODE WOULD BE ABLE TO CONFIGURE THE CODE BY HIS CODE.
			<IN PROGRESS>IN THIS CASE, THE CLIENT IS FREE TO HAVE DIFFERENT CONFIGURATIONS TO DIFFERENT
			PARTS OF THE CRXed LIBRARY PROVIDED THAT THE LIBRARY SUPPORTS IT. THIS MEANS 
			THAT THE SAME CONFIGURATION MACRO WOULD BE GIVEN A DIFFERENT VALUE DEPENDING
			ON WHICH ".cpp.h" IS BEING USED.</IN PROGRESS>

	REMEMBER THAT UNDER ALL SCENARIOS ABOVE, YOU ARE WRITING THE CRXed CODE EXACTLY THE SAME.

USAGE:
	- CODE MUST BE BROKEN INTO THREE DIFFERENT FILES, ".h", ".cpp" and ".cpp.h".
	- ".h" INCLUDES THE USUAL HEADER ONLY INFORMATION, BUT NO SOURCE CODE, EVEN FOR TEMPLATES.
			THESE MUST ALSO HAVE INCLUDE GUARDS.
	- ".cpp.h" INCLUDES ALL SOURCE CODE.
			THESE MUST ALSO HAVE INCLUDE GUARDS.
	- ".cpp" SERVES NOTHING BUT INDICATE A COMPILATION UNIT.
	- CODE FOLLOWING THE CRX LIB FORMAT WILL BE CALLED CRXed CODE FOR THE PURPOSE OF THIS
			DOCUMENTATION.
	- CODE FROM THE SAME LIBRARY IS ASSUMED TO BE EITHER ALL CRXed OR ALL NON CRXed.
	- WARNING: INCLUDING ".h" OF NON CRXed CODE CAN BREAK THE EFFECT OF CRX__LIB IF THE HEADER IS
			USING THE ODR PARADIGM. FOR EXAMPLE C++ CODE WHERE CLASSES ARE DEFINED IN THE HEADER 
			AND THEY ARE NOT TEMPLATES. IF A CRXed LIBRARY USING SUCH CODE IS DISTRIBUTED AS A HEADER
			ONLY LIBRARY, IT WILL END UP WORKING WITH THE ODR PARADIGM BECAUSE OF THE INCLUDED C++ 
			HEADER.

".h": {C++}
	#pragma once

	->> SUGGESTED //... INCLUDE THIS FILE (crx.h), OR A FILE THAT INCLUDES THIS FILE ... <<-
	#pragma push_macro("CRX__LIB__IS_CPPH_INCLUDING")
	#pragma push_macro("CRX__LIB__IS_CPP_INCLUDING")
	#undef CRX__LIB__IS_CPP_INCLUDING
	#undef CRX__LIB__IS_CPPH_INCLUDING
	#define CRX__LIB__IS_CPP_INCLUDING CRXM__FALSE
	#define CRX__LIB__IS_CPPH_INCLUDING CRXM__FALSE
	//<<START>>	INCLUDE ".h" OF NON CRXed CODE THAT THIS HEADER NEEDS.
	//			INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE THAT IS NOT PART OF THIS 
	//					LIBRARY THAT YOU ARE NOT USING AS HEADER ONLY LIBRARY, IF YOU WISH.
	//<<END>>
	#undef CRX__LIB__IS_CPPH_INCLUDING
	#define CRX__LIB__IS_CPPH_INCLUDING CRXM__TRUE
	//<<START>>	INCLUDE ".cpp.h" AND ".c.h", NOT ".h", OF C++, AND C, CRXed CODE THAT IS NOT PART OF THIS 
	//					LIBRARY THAT YOU ARE USING AS HEADER ONLY LIBRARY, IF YOU WISH.
	//<<END>>
	#pragma pop_macro("CRX__LIB__IS_CPP_INCLUDING")
	#pragma pop_macro("CRX__LIB__IS_CPPH_INCLUDING")
	#if CRX__LIB__IS_TO_INCLUDE_IN_H()
	//<<START>>	INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE FROM THIS LIBRARY THAT 
	//					THIS HEADER NEEDS.
	//			INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE THAT IS NOT PART OF THIS
	//					LIBRARY, THAT YOU WISH WOULD FOLLOW THE MODE OF THIS LIBRARY ON WHETHER THEY ARE
	//					HEADER ONLY OR NOT.
	->> SECTION X: THE CONTENT HERE RELATED TO C++ CRXed LIBRARIES, SHOULD BE THE SAME AS SECTION X IN THE
	->>			.cpp.h FILE, EXCEPT THAT THE FILES INCLUDED HERE WOULD BE .h.
	->>			THE CONTENT HERE RELATED TO C CRXed LIBRARIES, SHOULD BE THE SAME AS SECTION X IN THE
	->>			.cpp.h FILE, EXCEPT THAT THE FILES INCLUDED HERE WOULD BE .c.h.
	//<<END>>
	#endif
	.
	.
	.

	class MyClass
	{
		.
		.
	#if(CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_H())
		...THIS IS ONLY NEEDED IF "CRX__LIB__CONFIG__FAVOR_STATIC_INLINE" IS DEFINED. THIS ...
		...		ESSENTIALLY FAVORS FEATURES OF C++17 WHEN USING C++17 OR HIGHER. ...
		CRX__LIB__PUBLIC_STATIC_VARS_START(MyClass)
			... THIS IS WHERE YOU CAN DEFINE YOUR PUBLIC STATIC VARIABLES, AND ONLY HERE ...
			CRX__LIB__PUBLIC_STATIC_VAR() int variable1 = ...;
			CRX__LIB__PUBLIC_STATIC_VAR() int variable2 = ...;
			.
			.
		CRX__LIB__PUBLIC_STATIC_VARS_END
		CRX__LIB__PROTECTED_STATIC_VARS_START(MyClass)
			... THIS IS WHERE YOU CAN DEFINE YOUR PROTECTED STATIC VARIABLES, AND ONLY HERE ...
			CRX__LIB__PROTECTED_STATIC_VAR() int variable3 = ...;
			CRX__LIB__PROTECTED_STATIC_VAR() int variable4 = ...;
			.
			.
		CRX__LIB__PROTECTED_STATIC_VARS_END()
		CRX__LIB__PRIVATE_STATIC_VARS_START(MyClass)
			... THIS IS WHERE YOU CAN DEFINE YOUR PRIVATE STATIC VARIABLES, AND ONLY HERE ...
			CRX__LIB__PRIVATE_STATIC_VAR() int variable5 = ...;
			CRX__LIB__PRIVATE_STATIC_VAR() int variable6 = ...;
			.
			.
		CRX__LIB__PRIVATE_STATIC_VARS_END()
	#else
		...THIS IS ONLY NEEDED IF SUPPORT FOR PRE C++17 IS NEEDED, OR ...
		...		"CRX__LIB__CONFIG__FAVOR_STATIC_INLINE" IS NOT DEFINED.  ...
		CRX__LIB__PUBLIC_STATIC_VARS_START(MyClass)
			... THIS IS WHERE YOU CAN DEFINE YOUR PUBLIC STATIC VARIABLES, AND ONLY HERE ...
			CRX__LIB__PUBLIC_STATIC_VAR() int variable1;
			CRX__LIB__PUBLIC_STATIC_VAR() int variable2;
			.
			.
		CRX__LIB__PUBLIC_STATIC_VARS_END()
		CRX__LIB__PROTECTED_STATIC_VARS_START(MyClass)
			... THIS IS WHERE YOU CAN DEFINE YOUR PROTECTED STATIC VARIABLES, AND ONLY HERE ...
			CRX__LIB__PROTECTED_STATIC_VAR() int variable3;
			CRX__LIB__PROTECTED_STATIC_VAR() int variable4;
			.
			.
		CRX__LIB__PROTECTED_STATIC_VARS_END()
		CRX__LIB__PRIVATE_STATIC_VARS_START(MyClass)
			... THIS IS WHERE YOU CAN DEFINE YOUR PRIVATE STATIC VARIABLES, AND ONLY HERE ...
			CRX__LIB__PRIVATE_STATIC_VAR() int variable5;
			CRX__LIB__PRIVATE_STATIC_VAR() int variable6;
			.
			.
		CRX__LIB__PRIVATE_STATIC_VARS_END()
	#endif
	.
	.
	.
	}

	CRX__LIB__PUBLIC_FUNCTION() void myGlobal_doSomthing(void);
	CRX__LIB__PRIVATE_FUNCTION() void myGlobal_doSomthing2(void);

".cpp.h": {C++}
	#pragma once

	->> SUGGESTED //... INCLUDE THIS FILE (crx.h), OR A FILE THAT INCLUDES THIS FILE ... <<-
	#pragma push_macro("CRX__LIB__IS_CPPH_INCLUDING")
	#pragma push_macro("CRX__LIB__IS_CPP_INCLUDING")
	#undef CRX__LIB__IS_CPP_INCLUDING
	#undef CRX__LIB__IS_CPPH_INCLUDING
	#define CRX__LIB__IS_CPP_INCLUDING CRXM__FALSE
	#define CRX__LIB__IS_CPPH_INCLUDING CRXM__FALSE
	//<<START>>	INCLUDE ".h" OF NON CRXed CODE THAT THIS HEADER NEEDS.
	//			INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE THAT IS NOT PART OF THIS
	//					LIBRARY THAT YOU ARE NOT USING AS HEADER ONLY LIBRARY, IF YOU WISH.
	//<<END>>
	#undef CRX__LIB__IS_CPPH_INCLUDING
	#define CRX__LIB__IS_CPPH_INCLUDING CRXM__TRUE
	//<<START>>	INCLUDE ".cpp.h" AND ".c.h", NOT ".h", OF C++, AND C, CRXed CODE THAT IS NOT PART OF THIS 
	//					LIBRARY THAT YOU ARE USING AS HEADER ONLY LIBRARY, IF YOU WISH.
	//<<END>>
	#pragma pop_macro("CRX__LIB__IS_CPP_INCLUDING")
	#if CRX__LIB__IS_TO_INCLUDE_IN_CPPH()
	//<<START>> INCLUDE ".cpp.h" AND ".c.h", NOT ".h", OF C++, AND C, CRXed CODE FROM THIS LIBRARY THAT 
	//					THIS HEADER NEEDS.
	//			INCLUDE ".cpp.h" AND ".c.h", NOT ".h", OF C++, AND C, CRXed CODE THAT IS NOT PART OF THIS
	//					LIBRARY, THAT YOU WISH WOULD FOLLOW THE MODE OF THIS LIBRARY ON WHETHER THEY ARE
	//					HEADER ONLY OR NOT.
	->> SECTION X: THE CONTENT HERE RELATED TO C++ CRXed LIBRARIES, SHOULD BE THE SAME AS SECTION X IN THE
	->>			.h FILE, EXCEPT THAT THE FILES INCLUDED HERE WOULD BE .cpp.h.
	->>			THE CONTENT HERE RELATED TO C CRXed LIBRARIES, SHOULD BE THE SAME AS SECTION X IN THE
	->>			.h FILE, EXCEPT THAT THE FILES INCLUDED HERE WOULD BE .c.h.
	//<<END>>
	#endif
	//<<START>>	INCLUDE THE CORRESPONDING .h FILE FROM THE CRXed CODE. DO NOT INCLUDE OTHER ".h"
	//					FILES OF CRXed CODE.
	//<<END>>
	#pragma pop_macro("CRX__LIB__IS_CPPH_INCLUDING")
	.
	.
	.
	#if(CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_CPPH())
		int MyClass::StaticPublicVars::variable1 = ...;
		int MyClass::StaticPublicVars::variable2 = ...;
		.
		.
		int MyClass::StaticProtectedVars::variable3 = ...;
		int MyClass::StaticProtectedVars::variable4 = ...;
		.
		.
		int MyClass::StaticPrivateVars::variable5 = ...;
		int MyClass::StaticPrivateVars::variable6 = ...;
	#endif
	.
	.
	.
	//CRX__LIB__METHOD() MUST BE USED BEFORE EVERY CLASS FUNCTION DEFINITION
	CRX__LIB__METHOD() void MyClass::do(void)
	{
	}

	// CRX__LIB__PUBLIC_FUNCTION() OR  CRX__LIB__PRIVATE_FUNCTION() MUST BE USED BEFORE EVERY GLOBAL 
	//		FUNCTION DEFINITION.
	CRX__LIB__PUBLIC_FUNCTION() void myGlobal_doSomthing(void)
	{
	}
	CRX__LIB__PRIVATE_FUNCTION() void myGlobal_doSomthing2(void)
	{
	}

".cpp": {C++}
	#include "myLibrary_stdafx.h"
	->> SUGGESTED //... INCLUDE THIS FILE (crx.h), OR A FILE THAT INCLUDES THIS FILE ... <<-
	#pragma push_macro("CRX__LIB__IS_CPP_INCLUDING")
	#undef CRX__LIB__IS_CPP_INCLUDING
	#define CRX__LIB__IS_CPP_INCLUDING CRXM__TRUE
	//<<START>>	INCLUDE CORRESPONDING ".cpp.h" FILE.
	//<<END>>
	#pragma pop_macro("CRX__LIB__IS_CPP_INCLUDING")

	//... INSTANTIATE TEMPLATES DEFINED IN THE CORRESPONDING ".cpp.h" IF DESIRED


CLIENT CODE:
	CLIENT CODE WISHING TO USE A CRXed LIBRARY MUST INCLUDE ONLY ITS ".h" FILES IF IT WANTS TO
	USE IT AS A STATIC OR DYNAMIC LIBRARY, AND MUST INCLUDE ONLY ITS ".cpp.h" FILES IF IT WANTS
	TO USE IT AS A HEADER ONLY LIBRARY.



WARNING: THE LINES IN THE ".cpp" FILES, 
		#pragma push_macro("CRX__LIB__IS_CPP_INCLUDING")
		#undef CRX__LIB__IS_CPP_INCLUDING
		#pragma pop_macro("CRX__LIB__IS_CPP_INCLUDING")
ARE NECESSARY NOT BECAUSE TWO CPP FILES ARE ALLOWED IN ONE COMPILATION UNIT. PER MY STANDARD ONLY ONE
CPP FILE IS ALLOWED IN ONE COMPILATION UNIT BECAUSE THE CPP FILE ITSELF REPRESENTS THE COMPILATION UNIT.
THEY ARE NECESSARY BECAUSE THIS FILE ALSO DEFINES CRX__LIB__IS_CPP_INCLUDING
*/
/* LIB: C++ trivial case
THE TRIVIAL CASE OCCURS WHEN THE FOLLOWING CONDITIONS ARE MET
	- A CRXed LIBRARY USED AS HEADER ONLY, ONLY USES OTHER CRXed LIBRARIES, INCLUDING C CRXed LIBRARIES, 
			AS HEADER ONLY.
	- A CRXed LIBRARY USED AS NON HEADER ONLY, ONLY USES OTHER CRXed LIBRARIES, INCLUDING C CRXed LIBRARIES, 
			AS NON HEADER ONLY
	- A CRXed LIBRARY USING NON CRXed LIBRARIES, ONLY USES NON CRXed LIBRARIES THAT ARE NOT THEMSELVES
			USING CRXed LIBRARIES.

BY IMPLICATIN, IF A CRXed LIBRARY IS NOT USING ANOTHER CRXed LIBRARY, AND POINT THREE IS MET,
		THE FOLLOWING ALSO APPLIES.

".h": {C++, TRIVAL CASE}
	#pragma once

	->> SUGGESTED //... INCLUDE THIS FILE (crx.h), OR A FILE THAT INCLUDES THIS FILE ... <<-
	//<<START>>	INCLUDE ".h" OF NON CRXed CODE THAT THIS HEADER NEEDS.
	//<<END>>
	->>	IF YOU ARE INCLUDING C CRXed CODE .h HERE FROM OTHER LIBRARIES, IT MEANS THAT YOU WANT TO USE IT AS HEADER 
	->>			ONLY, BUT TO WORK YOU HAVE TO GO BACK TO RESETTING THE MACRO "CRX__LIB__IS_CPPH_INCLUDING" AT LEAST
	->>			LIKE IN THE C++ NON TRIVIAL CASE ABOVE.
	#if CRX__LIB__IS_TO_INCLUDE_IN_H()
	//<<START>>	INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE THAT IS NOT PART OF THIS
	//					LIBRARY, IF YOU WISH.
	//			INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE FROM THIS LIBRARY THAT 
	//					THIS HEADER NEEDS.
	->> SECTION X: THE CONTENT HERE RELATED TO C++ CRXed LIBRARIES, SHOULD BE THE SAME AS SECTION X IN THE
	->>			.cpp.h FILE OF THE TRIVIAL CASE, EXCEPT THAT THE FILES INCLUDED HERE WOULD BE .h.
	->>			THE CONTENT HERE RELATED TO C CRXed LIBRARIES, SHOULD BE THE SAME AS SECTION X IN THE
	->>			.cpp.h FILE OF THE TRIVIAL CASE, EXCEPT THAT THE FILES INCLUDED HERE WOULD BE .c.h.
	//<<END>>
	#endif
	.
	THE REST OF THE CODE IS SAME AS ABOVE
	.
	.


".cpp.h": {C++, TRIVAL CASE}
	#pragma once

	->> SUGGESTED //... INCLUDE THIS FILE (crx.h), OR A FILE THAT INCLUDES THIS FILE ... <<-
	#pragma push_macro("CRX__LIB__IS_CPPH_INCLUDING")
	#undef CRX__LIB__IS_CPPH_INCLUDING
	#define CRX__LIB__IS_CPPH_INCLUDING CRXM__TRUE
	//<<START>>	INCLUDE ".h" OF NON CRXed CODE THAT THIS HEADER NEEDS.
	//<<END>>
	#if CRX__LIB__IS_TO_INCLUDE_IN_CPPH()
	//<<START>>	INCLUDE ".cpp.h" AND ".c.h", NOT ".h", OF C++, AND C, CRXed CODE THAT IS NOT PART OF THIS
	//					LIBRARY, IF YOU WISH.
	//			INCLUDE ".cpp.h" AND ".c.h", NOT ".h", OF C++, AND C, CRXed CODE FROM THIS LIBRARY THAT
	//					THIS HEADER NEEDS.
	->> SECTION X: THE CONTENT HERE RELATED TO C++ CRXed LIBRARIES, SHOULD BE THE SAME AS SECTION X IN THE
	->>			.h FILE OF THE TRIVIAL CASE, EXCEPT THAT THE FILES INCLUDED HERE WOULD BE .cpp.h.
	->>			THE CONTENT HERE RELATED TO C CRXed LIBRARIES, SHOULD BE THE SAME AS SECTION X IN THE
	->>			.h FILE OF THE TRIVIAL CASE, EXCEPT THAT THE FILES INCLUDED HERE WOULD BE .c.h.
	//<<END>>
	#endif
	//<<START>>	INCLUDE THE CORRESPONDING .h FILE FROM THE CRXed CODE. DO NOT INCLUDE OTHER ".h"
	//					FILES OF CRXed CODE.
	//<<END>>
	#pragma pop_macro("CRX__LIB__IS_CPPH_INCLUDING")
	.
	THE REST OF THE CODE IS SAME AS ABOVE
	.
	.


".cpp": {C++, TRIVAL CASE}
	NO CHANGES HERE. THE CODE IS THE SAME AS ABOVE.
*/
/* LIB: C trivial case, manual
THE FOLLOWING IS SPECIFIC TO C

IN THE PAST, MEANING NO LONGER VALID, MEANING WHEN THE C CODE RELIED ON THE C++ CODE FROM THE SAME CRXed
LIBRARY TO CONVEY THE INFORMATION ABOUT WHETHER THE CODE IS RUNNING HEADER ONLY OR NOT, POSSIBLE SCENARIOS
WHEN USING WITH A CRXed C++ LIBRARY WERE:
	A- CRXed C++ LIBRARY IS USING CRXed C LIBRARY SUCH AS THE C LIBRARY IS TO BE TREATED AS HEADER ONLY.
			IN THIS CASE, THE ".ccp.h" FILES WOULD INCLUDE THE ".c.h" AND THE C LIBRARY WOULD UNDERSTAND 
			THE INTENTION BASED ON THAT.
	B- CRXed C++ LIBRARY IS USING CRXed C LIBRARY SUCH AS THE C LIBRARY IS TO BE TREATED AS PRECOMPILED ONLY.
			IN THIS CASE, THE C++ ".h" FILES WOULD INCLUDE THE C ".h" FILES AND THE C LIBRARY WOULD UNDERSTAND THE 
			INTENTION BASED ON THAT.
			
FOR MORE INFORMATION SEE THE "LOGIC" SECTION.

NOTE THAT THIS CASE, THE TRIVIAL, MANUAL, CASE IS ASSUMED FOR C IN THE C++ SECTIONS ABOVE.

USAGE:
	- CODE MUST BE BROKEN INTO THREE DIFFERENT FILES, ".h", ".c" and ".c.h".
	- ".h" INCLUDES THE USUAL HEADER ONLY INFORMATION, BUT NO SOURCE CODE.
			THESE MUST ALSO HAVE INCLUDE GUARDS.
	- ".c.h" INCLUDES ALL SOURCE CODE.
			THESE MUST ALSO HAVE INCLUDE GUARDS.
	- ".c" SERVES NOTHING BUT INDICATE A COMPILATION UNIT.
	- CODE FOLLOWING THE CRX LIB FORMAT WILL BE CALLED CRXed CODE FOR THE PURPOSE OF THIS
			DOCUMENTATION.
	- CODE FROM THE SAME LIBRARY IS ASSUMED TO BE EITHER ALL CRXed OR ALL NON CRXed.
	- IT ASSUMED THAT ".c" FILES WILL ALWAYS BE COMPILED AS C CODE, NOT C++.
	- WARNING: INCLUDING ".h" OF NON CRXed CODE CAN BREAK THE EFFECT OF CRX__LIB IF THE HEADER IS
			USING THE ODR PARADIGM. 
	- NOTE THAT THE FOLLOWING IS ASSUMING THE SIMPLIFYING CONVENTION, SAME AS THE SECTION ABOVE FOR C++
			WHICH IS THAT A C CRXed LIBRARY USED AS HEADER ONLY, ONLY USES OTHER CRXed C LIBRARIES AS 
			HEADER ONLY, AND A C CRXed LIBRARY USED AS NON HEADER ONLY, ONLY USES OTHER C CRXed 
			LIBRARIES AS NON HEADER. OR A C CRXed LIBRARY DOES NOT USE OTHER C CRXed LIBRARIES, WHICH
			FOLLOWS BY IMPLICATION.
	- IN THE PAST, THE SIMPLYFING CONVENTION WAS ASSUMED BELOW BECAUSE IT WAS ASSUMED THAT 
			"#pragma push_macro()" AND "#pragma pop_macro()" ARE NOT AVAILABLE IN THE C COMPILER. 
			NOTE THAT GCC COMPILER INTRODUCED THESE IN V4.6, ROUGHLY 2011.
			LATER THE MACRO CRX__PREPROCESSOR__HAS_PUSH_MACRO WAS INTRODUCED AND INSTEAD THE ASSUMPTION
			BECAME THAT SOME C COMPILERS HAVE THOSE MACROS, BUT EVEN THEN WE WOULD STILL EXPECT THE
			CODE TO WORK ON C COMPILERS THAT DO NOT HAVE THESE MACROS. THIS IS ONE REASON WHY THE TRIVIAL
			CASE REMAINS USEFUL. OF COURSE WITH THE INTRODUCTION OF CRX__PREPROCESSOR__HAS_PUSH_MACRO
			WE COULD HAVE INTRODUCED THE NON TRIVIAL CASE FOR THE C CODE, BUT THIS WAS DECIDED AGAINST
			FOR SIMPLICITLY AND TO KEEP COMPATIBILITY HIGH IF THE COMPILERS DO NOT SUPPORT THE SAID
			MACROS.


".h": {C, TRIVIAL CASE, MANUAL}
	#pragma once

	->> SUGGESTED //... INCLUDE THIS FILE (crx.h), OR A FILE THAT INCLUDES THIS FILE ... <<-
	//<<START>>	INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
	//<<END>>
	#if CRX__LIB__IS_TO_INCLUDE_IN_C_H()
	//<<START>>	INCLUDE ".h", NOT ".c.h", OF C CRXed CODE THAT IS NOT PART OF THIS LIBRARY, IF YOU WISH.
	//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE FROM THIS LIBRARY THAT THIS HEADER NEEDS.
	//<<END>>
	#endif
	
	CRX__LIB__C_CODE_BEGIN()
	.
	.
	.
	
	CRX__LIB__PUBLIC_C_FUNCTION() void myGlobal_doSomthing(void);
	CRX__LIB__PRIVATE_C_FUNCTION() void myGlobal_doSomthing2(void);
	
	CRX__LIB__C_CODE_END()

".c.h": {C, TRIVIAL CASE, MANUAL}
	#pragma once

	->> SUGGESTED //... INCLUDE THIS FILE (crx.h), OR A FILE THAT INCLUDES THIS FILE ... <<-
	#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
		#pragma push_macro("CRX__LIB__IS_CPPH_INCLUDING")
		#undef CRX__LIB__IS_CPPH_INCLUDING
		#define CRX__LIB__IS_CPPH_INCLUDING CRXM__TRUE
	#endif
	//<<START>>	INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
	//<<END>>
	#if CRX__LIB__IS_TO_INCLUDE_IN_C_CH()
	//<<START>> INCLUDE ".c.h", NOT ".h", OF C CRXed CODE THAT IS NOT PART OF THIS LIBRARY, IF YOU WISH.
	//			INCLUDE ".c.h", NOT ".h", OF C CRXed CODE FROM THIS LIBRARY THAT THIS HEADER NEEDS.
	//<<END>>
	#endif
	//<<START>>	INCLUDE THE CORRESPONDING .h FILE FROM THE C CRXed CODE. DO NOT INCLUDE OTHER ".h"
	//					FILES OF C CRXed CODE.
	//<<END>>
	#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
		#pragma pop_macro("CRX__LIB__IS_CPPH_INCLUDING")
	#endif
	
	CRX__LIB__C_CODE_BEGIN()
	.
	.
	.
	.

	// CRX__LIB__PUBLIC_C_FUNCTION() OR  CRX__LIB__PRIVATE_C_FUNCTION() MUST BE USED BEFORE EVERY GLOBAL 
	//		FUNCTION DEFINITION.
	// WARNING: CRX__LIB__PUBLIC_C_FUNCTION() FUNCTIONS ARE NOT ALLOWED TO HAVE STATIC LOCAL VARIABLES.
	CRX__LIB__PUBLIC_C_FUNCTION() void myGlobal_doSomthing(void)
	{
	}
	CRX__LIB__PRIVATE_C_FUNCTION() void myGlobal_doSomthing2(void)
	{
	}
	
	CRX__LIB__C_CODE_END()

".c": {C, TRIVIAL CASE, MANUAL}
	#include "myLibrary_stdafx.h"
	->> SUGGESTED //... INCLUDE THIS FILE (crx.h), OR A FILE THAT INCLUDES THIS FILE ... <<-
	//<<START>>	INCLUDE CORRESPONDING ".c.h" FILE.
	//<<END>>


CLIENT CODE:
	CLIENT CODE WISHING TO USE A C CRXed LIBRARY 
		- IF THE C COMPILER DOES NOT SUPPORT push_macro
			- MUST INCLUDE ONLY ITS ".h" FILES IF IT WANTS TO USE IT AS A STATIC OR DYNAMIC LIBRARY. IT MUST ALSO
					DEFINE THE MACRO CRX__LIB__IS_C_HEADER_ONLY AS CRXM__FALSE. THE CLIENT CODE WOULD BE FORCED
					TO USE ALL C CRXed AS HEADER ONLY, OR ALL AS NON HEADER ONLY. IF THE CLIENT WANTS TO USE
					DIFFERNT C CRXed LIBRARIES DIFFERENTLY, THEN THE COMPILER WOULD NEED TO PROVIDE
					#pragma push_macro() AND #pragma pop_macro()
			- MUST INCLUDE ONLY ITS ".c.h" FILES IF IT WANTS TO USE IT AS A HEADER ONLY LIBRARY. IT MUST ALSO
					DEFINE THE MACRO CRX__LIB__IS_C_HEADER_ONLY AS CRXM__TRUE
			- IF THE CLIENT CODE IS A C++ CRXed LIBRARY, THE CLIENT CODE DOES NOT NEED TO DEFINE
					CRX__LIB__IS_C_HEADER_ONLY, BUT IT INSTEAD WOULD INCLUDE c.h FILES INSIDE cpp.h FILES IF IT WANTS
					TO USE THE LIBRARY AS HEADER ONLY, AND WOULD INCLUDE .h FILES INSIDE C++'S .h FILES IF IT WANTS
					TO USE THE LIBRARY AS STATIC OR DYNAMIC LIBRARY.
		- IF THE C COMPILER DOES SUPPORT push_macro
			- MUST INCLUDE ONLY ITS ".h" FILES IF IT WANTS TO USE IT AS A STATIC OR DYNAMIC LIBRARY.
			- MUST INCLUDE ONLY ITS ".c.h" FILES IF IT WANTS TO USE IT AS A HEADER ONLY LIBRARY.
		- FOR MAXIMUM COMPATIBILITY WITH COMPILERS CLIENT CODE SHOULD SIMPLY ASSUME push_macro IS NOT SUPPORTED.



WARNING: THE LINES IN THE ".cpp" FILES, 
		#pragma push_macro("CRX__LIB__IS_CPP_INCLUDING")
		#undef CRX__LIB__IS_CPP_INCLUDING
		#pragma pop_macro("CRX__LIB__IS_CPP_INCLUDING")
ARE NECESSARY NOT BECAUSE TWO CPP FILES ARE ALLOWED IN ONE COMPILATION UNIT. PER MY STANDARD ONLY ONE
CPP FILE IS ALLOWED IN ONE COMPILATION UNIT BECAUSE THE CPP FILE ITSELF REPRESENTS THE COMPILATION UNIT.
THEY ARE NECESSARY BECAUSE THIS FILE ALSO DEFINES CRX__LIB__IS_CPP_INCLUDING
*/
/* LIB: Design notes
LOGIC:
	- LOGIC TABLE:
		-
										CLOSED		OPEN		ODR			NON ODR 	SETTINGS PASSED
										SOURCE		SOURCE		PARADIGM	PARADIGM	THROUGH CODE
					HEADER ONLY				N			Y			Y			Y			Y
					NOT HEADER ONLY			Y			Y			N			Y			Y*
					NOT HEADER ONLY			Y			N			N			Y			N
					(PRECOMPILED)
			
			*IN THIS CASE WE WOULD USE A SHARED HEADER CONVENTION ON WHICH CLIENT CODE COULD PASS ITS SETTINGS,
					WHICH IS SLIGHTLY RESTRICTIVE COMPARED TO THE HEADER ONLY CASE.
		- NON SUPPORTED SCENARIOS
			- THERE IS NO SUPPORT, WHEN HEADER ONLY, FOR THE LIBRARY TO ACT UNDER ODR PARADIGM.
			- THERE IS NO SUPPORT, WHEN NOT HEADER ONLY AND NOT PRECOPMILED, FOR THE LIBRARY TO BE CONFIGURABLE
					THROUGH CODE
	- THE INTRODUCTION OF THE NEW FILES, .c.h AND .cpp.h, IS MADE TO SUPPORT BOTH CASES OF OPEN SOURCE AND CLOSED
			SOURCE. HOWEVER, THESE FILES ALSO HELP IN THE AUTOMATION OF THE MODE OF THE LIBRARY. SEE BELOW.
	- WHEN INCLUDING CRXed CODE FILES, THERE ARE THREE SITUATION TO CONSIDER, ALL TO BE THOUGHT OF FROM
			THE CLIENT CODE PERSPECTIVE:
		(1)- INCLUSION OF HEADER FILES (.h) EXPECTING THE ACTUAL LIBRARY WAS ALREADY COMPILED ELSEWHERE.
		(2)- INCLUSION OF SOURCE HEADER FILES (.cpp.h) BECAUSE WE ARE USING THE LIBRARY AS A HEADER ONLY LIBRARY.
		(3)- INCLUSION OF SOURCE HEADER FILES (.cpp.h) FILES BECAUSE WE ARE THE ONES COMPILING THE LIBRARY.
	- INCLUDING THE .h FILES IN THE .cpp.h OR .c.h FILES AT THE BEGGINING OF SAID FILES MEANT THAT THE HEADERS 
			INCLUDED IN THE .h FILES DID NOT TO BE REINCLUDED IN THE .cpp.h AND .c.h FILES. HOWEVER, 
			"MESSAGES" FROM IN THE .cpp.h OR .c.h FILES COULD NOT BE PASSED TO THE .h FILES. ON THE OTHER HAND, 
			IF THE ".h" FILES ARE INCLUDED IN THE END, MESSAGES COULD BE PASSED. TO UNDESTAND, CONSIDER THE SECTION
			THAT USES "CRX__LIB__IS_TO_INCLUDE_IN_H()" IN THE .h FILES. THIS IS A SITUATION WHERE
			THE CRXed LIBRARY FILES NEEDS OTHER FILES FROM THE SAME CRXed LIBRARY. REMEMBER THAT A CRXed
			LIBRARY CAN ONLY BE USED FULLY AS A HEADER ONLY LIBRARY, OR FULLY AS A NON HEADER ONLY LIBRARY.
			IN THIS SECTION, IN THE .h FILES THE .h FILE INCLUDES THE FILES IT NEEDS. HOWEVER, IF THE
			CRXed LIBRARY IS USED AS A HEADER ONLY LIBRARY, THE INCLUSION WOULD HAVE TO HAPPEN IN THE
			"CRX__LIB__IS_TO_INCLUDE_IN_CPPH()" OF THE ".cpp.h" FILES. IN THOSE FILES, IF THE CORRESPONDING
			".h" FILES IS ADDED AT THE BEGGINING, THE ".h" FILE WILL NOT GET THE INCLUDES IT ITSELF NEEDS,
			EVEN THOUGH THE FINAL AMALGAMATION HAS ALL THE NECESSARY CODE. 
	- C++
		- THE AIM HAS BEEN TO AUTOMATE THE LOGIC BEHIND THE SCENES OF HOW THE LIBRARY IS TO BEHAVE. WE COULD
				REQUIRE THE CLIENT CODE TO ITSELF INDICATE WHETHER IT WANTS TO USE THE CRXed LIBRARY AS A
				HEADER ONLY LIBRARY OR NOT USING SOME CONFIG MACRO. IN THIS CASE, 
			- IN SCENARIO (1) ABOVE, THE CLIENT CODE DOES NOT SPECIFY THAT THE LIBRARY IS TO BE HEADER ONLY,
					AND THE CLIENT CODE ONLY USES THE HEADER FILES (.h) WHICH THEMSELVES UNDERSTAND THE INTENT
					BY NOT DETECTING THE CONFIG MACRO.
			- IN SCENARIO (2) ABOVE, THE CLIENT CODE DOES SPECIFY THAT THE LIBRARY IS TO BE HEADER ONLY,
					AND THE CLIENT CODE ONLY INCLUDES SOURCE HEADER FILES (.cpp.h). THE SOURCE HEADER FILES,
					BASED ON THEIR DETECTION OF THE CONFIG MACRO KNOW THAT THEY ARE BEING USED AS A
					HEADER ONLY LIBRARY. REMEMBER THAT THOSE FILES PROCEED TO INCLUDE THE HEADER FILES (.h).
					THOSE IN TURN ALSO KNOW THAT THEY ARE BEING USED AS HEADER ONLY FROM THE SAME CONFIG MACRO.
			- IN SCENARIO (3) ABOVE, THE CLIENT CODE IS THE CRXed LIBRARY ITSELF. IN PARTICULAR, IT IS THE
					SOURCE FILES (.cpp) OF THE CRXed LIBRARY. THESE FILES, DO NOT SPECIFY THAT THE LIBRARY IS
					TO BE HEADER ONLY, AND ONLY INCLUDE THE SOURCE HEADER FILES (.cpp.h) FILES WHICH UNDERSTAND
					THE INTENT BY NOT DETECTING THE CONFIG MACRO, AND THEY THEMSELVES INCLUDE THE (.h) FILES
					WHICH IN TURN UNDERSTAND THE INTENT BY NOT DETECTING THE CONFIG MACRO.
		- NOTICE HOW IF IT WAS LEFT TO THE CLIENT CODE TO DEFINE A CONFIG MACRO, WE WOULD ONLY NEED ONE CONFIG
				MACRO. IT WAS DESIRED TO AUTOMATICALLY DETECT THE SCENARIO RATHER THAN HAVE THE CLIENT CODE
				HAVING TO DEFINE A MACRO, AND BECAUSE OF THIS THE MACROS "CRX__LIB__IS_CPP_INCLUDING" AND
				"CRX__LIB__IS_CPPH_INCLUDING" WERE INTRODUCED ALONG WITH THE NEED FOR A
				"#pragma push_macro()" AND "#pragma pop_macro()" MECHANISM. NOTE THAT EVEN WITH A CONFIG MACRO
				INSTEAD, THESE TWO PRAGMAS WOULD STILL LIKELY BE REQUIRED. CONSIDER FOR EXAMPLE IF THE
				CLIENT CODE IS INCLUDING A CRXed LIBRARY "LIB_A" AND "LIB_A" HAPPENS TO MAKE USE OF CRXed LIBRARY
				"LIB_B". IF THE CLIENT CODE WANTED TO USE "LIB_A" AS NON HEADER ONLY, AND "LIB_A" WANTED TO USE
				"LIB_B" AS HEADER ONLY, HOW WOULD THE INFORMATION BE RELAYED? (REMEMBER THAT "LIB_A" IS A CLIENT
				CODE TO "LIB_B"). WITHOUT THE AFORE MENTIONED PRAGMAS, EACH LIBRARY WOULD HAVE TO SAVE A COPY OF
				THE CONFIG MACRO, SET THE NEW VALUE BECFORE USING THE LIBRARY IT IS USING AND THEN RESTORE THE
				OLD VALUE AFTER FINISHING. HOWEVER THIS IS NOT POSSIBLE WITH MACROS.
				IN TERMS OF THE MACROS "CRX__LIB__IS_CPP_INCLUDING" AND "CRX__LIB__IS_CPPH_INCLUDING", THE CONFIG
				MACRO WHICH WOULD SET THAT THE LIBRARY IS HEADER ONLY IS EQUAL TO
						!CRX__LIB__IS_CPP_INCLUDING && CRX__LIB__IS_CPPH_INCLUDING
				OR ALTERNATIVELY
						!(CRX__LIB__IS_CPP_INCLUDING || !CRX__LIB__IS_CPPH_INCLUDING)
				THE MACRO
						"CRX__LIB__IS_TO_INCLUDE_IN_H()"
				IS ESSENTIALLY ASKING IF THE LIBRARY IS NOT HEADER ONLY. AND THE MACRO
						"CRX__LIB__IS_TO_INCLUDE_IN_CPPH()"
				IS ESSENTIALLY ASKING IF THE LIBRARY IS HEADER ONLY. NOTE HOWEVER THAT THE MACRO ASSUMES
				THAT "CRX__LIB__IS_CPPH_INCLUDING" IS TRUE BECAUSE THE MACRO IS MEANT TO BE USED INSIDE
				THE .CPP.H FILES.
		- IT IS UNFORTUNATE HOW IN THE SECTIONS GUARDED BY "CRX__LIB__IS_TO_INCLUDE_IN_H()" AND 
				"CRX__LIB__IS_TO_INCLUDE_IN_CPPH()" WE NEED TO HAVE THE SAME FILE PAIRS INCLUDED UNDER BOTH
				.H AND .CCP.H FILES. THIS IS BECAUSE SOMETIMES THERE ARE FILES ONLY NEEDED IN THE .CPP.H FILE,
				MEANING ONLY NEEDED FOR IMPLEMENTATION, AND HENCE NOT NEED IN THE .H FILES. HOWEVER WE STILL 
				NEED TO INCLUDE THEM IN THE HEADER BECAUSE OTHER WISE THE LIBRARY WOULD ONLY WORK
				SUCCESSFULLY UNDER SCENARIOS 1 AND 2. REMEMBER THAT UNDER SCENARIO 3, THE SECTION GUARDED
				BY "CRX__LIB__IS_TO_INCLUDE_IN_CPPH()" WOULD BE OFF, YET THE CONTENT OF THE ".H" FILES THAT
				ARE INCLUDED BY THE INCLUDED ".CPP.H" FILES WOULD STILL BE NEEDED, AND HENCE, THE SECTION
				GUARDED BY "CRX__LIB__IS_TO_INCLUDE_IN_H()" NEEDS TO INCLUDE THOSE ".H" FILES.
				
				REMEMBER THAT IN 
						SCENARIO 1: WE NEED THE ".H" FILES OF OTHER FILE PAIRS, THAT SATIFY THE CURRENT ".H" FILE.
						SCENARIO 2: WE NEED THE IMPLEMENTATION ".CPP.H" FILES, AND THE ".H" FILES OF OTHER FILE 
							PAIRS.
						SCENARIO 3: WE NEED THE ".H' FILES OF OTHER FILE PAIRS, THAT SATIFY THE CURRENT ".CPP.H" 
							FILE AND THE CURRENT ".H" FILE.
						
				IN OTHER WORDS, TO FINE TUNE IT, WITHIN THE SECTION GUARDED BY "CRX__LIB__IS_TO_INCLUDE_IN_H()"
				WE WOULD NEED ANOTHER SECTION GUARDED BY THE VALUE OF "CRX__LIB__IS_CPPH_INCLUDING" WHERE
				WE WOULD INCLUDE THE ".H" FILES THAT ARE NEEDED BY THE CURRENT ".CPP.H" FILE, BUT NOT BY
				THE CURRENT ".H" FILE.
	- IN C
		- IT IS NOT THE AIM TO AUTOMATE THE LOGIC BEHIND THE SCENES ON HOW THE LIBRARY BEHAVES. THIS IS BECAUSE
				IN C COMPILER IT IS NOT ASSUMED THAT THERE IS A "#pragma push_macro()" AND 
				"#pragma pop_macro()" MECHANISM. SEE THE DISCUSSION ABOVE.
				WITH THIS, IN C, INSTEAD OF THE TWO MACROS "CRX__LIB__IS_CPP_INCLUDING" AND
				"CRX__LIB__IS_CPPH_INCLUDING", THERE IS ONLY ONE MACRO, "CRX__LIB__IS_C_HEADER_ONLY"
				WHICH IS ESSENTIALLY THE CONFIG MACRO THAT THE CLIENT CODE HAS TO SET.

				<REMOVED
				HOWEVER, WHEN CRXed C++ CODE IS MAKING USE OF CRXed C CODE, WE INSTEAD AUTOMATE THE PROCESS
				AGAIN USING THE "CRX__LIB__IS_CPPH_INCLUDING" MACRO. THIS IS BECAUSE IN THIS CASE WE WOULD BE IN 
				A C++ COMPILER. ESSENTIALLY, "CRX__LIB__IS_CPPH_INCLUDING" ACTS AS THE CONFIG MACRO INSTEAD.
				NOTE THAT "CRX__LIB__IS_CPP_INCLUDING" IS NOT TAKEN INTO CONSIDERATION AT ALL. IN OTHER WORDS
				WHEN "CRX__LIB__IS_TO_INCLUDE_IN_C_H()" AND "CRX__LIB__IS_TO_INCLUDE_IN_C_CH()" ARE USED, THEY
				ARE NOT USED TO FORCE THE C LIBRARY TO BE HEADER ONLY OR NOT HEADER ONLY BASED ON THE MODE
				OF CRXed LIBRARY USING IT. INSTEAD, THEY ARE ALLOWING THE C LIBRARY TO HAVE ITS OWN INDEPENDENT
				MODE. IN OTHER WORDS, THE INCLUSION IN THE C++ SIDE IS NOT CONDITIONAL, IT IS NOT BASED ON THE 
				MACROS "CRX__LIB__IS_TO_INCLUDE_IN_H()" AND "CRX__LIB__IS_TO_INCLUDE_IN_CPPH()". IN OTHER WORDS, 
				IF YOU WANT TO MAKE THE C CRXed LIBRARY USE THE MODE OF THE C++ CRXed LIBRARY, YOU HAVE TO 
				PLACE THE INCLUSIONS WITHIN THE SECTIONS GUARDED BY "CRX__LIB__IS_TO_INCLUDE_IN_H()" AND 
				"CRX__LIB__IS_TO_INCLUDE_IN_CPPH()" LIKE YOU DO WITH THE C++ CRXed CODE FROM THE SAME C++ LIBRARY.
				IT SHOULD BE NOTED THAT WHEN CRXed C++ CODE IS INCLUDING CRXed C CODE, WE ONLY NEED TO WORRY
				ABOUT SCENARIOS (1) AND (2) ABOVE.
				>

				HOWEVER, WHEN CRXed C++ CODE IS MAKING USE OF CRXed C CODE, WE INSTEAD AUTOMATE THE PROCESS
				AGAIN USING THE "CRX__LIB__IS_CPPH_INCLUDING" AND "CRX__LIB__IS_CPP_INCLUDING" MACROS GIVING THEM
				THE SAME MEANING AS IN THE C++ SIDE TO KEEP THE TRIVIAL CASE OF C++ SIMPLE. NOTE THAT IN THIS 
				CASE WE WOULD BE IN A C++ COMPILER. ESSENTIALLY, 
						!"CRX__LIB__IS_CPP_INCLUDING" && "CRX__LIB__IS_CPPH_INCLUDING"
				ACT AS THE CONFIG MACRO INSTEAD. NOTE HOWEVER THAT THESE TWO ARE BEING SET AND RESET IN A WAY THAT
				THEY ARE NOT USED TO FORCE THE C LIBRARY TO BE HEADER ONLY OR NOT HEADER ONLY BASED ON THE MODE
				OF CRXed LIBRARY USING IT. INSTEAD, THEY ARE ALLOWING THE C LIBRARY TO HAVE ITS OWN INDEPENDENT
				MODE. IN OTHER WORDS, THE INCLUSION IN THE C++ SIDE IS NOT CONDITIONAL, IT IS NOT BASED ON THE 
				MACROS "CRX__LIB__IS_TO_INCLUDE_IN_H()" AND "CRX__LIB__IS_TO_INCLUDE_IN_CPPH()". IN OTHER WORDS, 
				IF YOU WANT TO MAKE THE C CRXed LIBRARY USE THE MODE OF THE C++ CRXed LIBRARY, YOU HAVE TO 
				PLACE THE INCLUSIONS WITHIN THE SECTIONS GUARDED BY "CRX__LIB__IS_TO_INCLUDE_IN_H()" AND 
				"CRX__LIB__IS_TO_INCLUDE_IN_CPPH()" LIKE YOU DO WITH THE C++ CRXed CODE FROM THE SAME C++ LIBRARY.
				IT SHOULD BE NOTED THAT WHEN CRXed C++ CODE IS INCLUDING CRXed C CODE, WE ONLY NEED TO WORRY
				ABOUT SCENARIOS (1) AND (2) ABOVE.

				THE ABOVE SCHEME SUFFERED FROM ONE THING, AND THAT IS WITHIN C++ IF CLIENT CODE IS USING C CODE
				FROM A CRXed LIBRARY, RATHER THAN USING C++ CODE FROM SAID LIBRARY THAT IS ITSELF USING C CODE
				FROM THE SAME LIBRARY, THE C CODE NEVER GETS THE RIGHT INFORMATION ABOUT WHETHER IT IS RUNNING
				IN HEADER ONLY MODE OR NOT. HENCE, UNDER THE ABOVE SCHEME, CLIENT CODE COULD NOT MAKE USE OF
				C CODE IN A CRXed LIBRARY DIRECTLY. TO SOLVE THIS, THE MACRO "CRX__PREPROCESSOR__HAS_PUSH_MACRO"
				WAS FINALLY INTRODUCED. HOWEVER, THE CODE IN THE C SIDE CONTINUED TO MAKE USE OF
						!"CRX__LIB__IS_CPP_INCLUDING" && "CRX__LIB__IS_CPPH_INCLUDING"
				TO MAKE IT ACT AS THE CONFIG MACRO. WITH THIS, THE CODE CHANGES REMAIN MINIMAL.
		- IT IS ASSUMED THAT IF THE CRXed C IS NOT USED AS A HEADER ONLY LIBRARY FROM A CRXed C++ CODE, THE CODE
				IS TREATED AS C CODE, AND NOT C++ CODE.
	- NOTE: A C++ COMPILER IS ALWAYS ASSUMED TO SUPPORT THE "#pragma push_macro()" AND 
			"#pragma pop_macro()" MECHANISM. IF SUCH A COMPILER CAN COMPILE C CODE AS C,
			THAT COMPILER IS ALSO ASSUMED TO SUPPORT THE SAID MECHANISM UNDER ITS C MODE.
	- DLL SUPPORT:
		- DLL SUPPORT IS MEANT FOR C ONLY, NOT C++. THIS IS BECAUSE PER MY STANDARD, THERE IS
				NO USEFUL CASE FOR EXPORTING C++ CODE FROM A DLL. FORMALLY, A DLL THAT EXPORTS
				C++ CODE, AND WAITS UNTIL THE LAST INSTANCE TO LOAD THE DLL, AND FAILS IMMEDIATELY
				IF AN ERROR IN LOADING, IS A DYNAMIC COMPILATION UNIT AS DEFINED IN MY STANDARD.
				HOWEVER, FOR SUCH A THING TO BE PRACTICAL LAST MINUTE LOADING AND IMMEDIATE
				CRASHING SUPPORT NEEDS TO BE COMING FROM THE COMPILER AND LINKER, RATHER THAN CODE
				WRITTEN BY HAND TO BE PRACTICAL. THEREFORE DLL SUPPORT IS FOR C ONLY.
		- DLL SUPPORT REQUIRES THAT THE CODE CAN TELL THE DIFFERENCE BETWEEN THE THREE SCENARIOS 
				ABOVE, AND IT CAN, AND IT IS NO LONGER A SIMPLE MATTER OF THIS LIBRARY IS HEADER 
				ONLY OR NOT IN THE REST OF THE LOGIC. CONSIDER __declspec(dllimport) AND
				__declspec(dllexport) UNDER MICROSOFT COMPILERS. IF LIBRARY IS HEADER ONLY THESE
				WOULD NOT BE USED, BUT IF NOT, THESE WOULD NEED TO BE USED BASED ON WHETHER THE
				SITUATION IS SCENARIO (1) OR SCENARIO (3). UNDER SCENARIO (1), WE HAVE TO USE
				__declspec(dllimport), AND UNDER SCENARIO (2), WE HAVE TO USE __declspec(dllexport).
				NOTICE THE LACK OF CODE SYMMETRY AS DEFINED IN MY STANDARD.

				BECAUSE THE CODE CAN TELL THE DIFFERENCE BETWEEN THE THREE SCENARIOS THIS IS NOT 
				AN ISSUE, HOWEVER UNDER THE CASE WHERE A C ONLY COMPILER IS BEING USED, THE COMPILER
				CAN BE ONE THAT DOES NOT SUPPORT push_macro AND pop_macro. REMEMBER A COMPILER THAT
				CAN SUPPORT BOTH C AND C++ IS ASSUMED TO SUPPORT THESE TWO MACROS UNDER C BECAUSE
				CRX LIB EXPECTS A C++ COMPILER TO SUPPORT THESE. BACK TO THE SITUATION WHERE IT IS
				A C ONLY COMPILER AND DOES NOT SUPPORT THESE TWO MACROS, THE CODE CAN NO LONGER
				DIFFERENTIATE BETWEEN THE THREE SCENARIOS USING THE CONFIG BOOLEAN MACRO
				CRX__LIB__IS_C_HEADER_ONLY. THEREFORE UNDER THIS SCENARIO, THERE CAN BE NO DLL 
				SUPPORT.
				
				ANOTHER ISSUE IS THAT THE CODE IS ABLE TO TAKE ADVANTAGE OF A NUMBER OF LOGICAL
				SIMPLIFICATIONS SUCH AS THE LINE
								#pragma pop_macro("CRX__LIB__IS_CPPH_INCLUDING")
				IN THE ".cpp.h" FILES REMAINS IN THE TOP SECTION OF THOSE. CRX__LIB__METHOD(),
				AND CRX__LIB__PUBLIC_FUNCTION() ARE EXAMPLES. I WAS UNABLE TO FIND
				ANY SIMPLIFICATIONS TO KEEP THIS THE CASE WHEN ADDING SUPPORT FOR DLLS.
*/


#ifndef CRX__LIB__IS_CPP_INCLUDING
	#define CRX__LIB__IS_CPP_INCLUDING 0
#endif
#ifndef CRX__LIB__IS_CPPH_INCLUDING
	#define CRX__LIB__IS_CPPH_INCLUDING 0
#endif
/*
DLL SUPPORT
CODE HAS BEEN ADDED FOR SUPPORT BUT COMMENTED OUT FOR FUTURE REFERENCE
#ifndef CRX__LIB__IS_DLL
	#define CRX__LIB__IS_DLL 0
#endif
*/

/*
REMEMBER, CRX__LIB__METHOD() IS TO MEANT TO BE USED ON THE DEFINITIONS ONLY, MEANING IN THE ".cpp.h" FILE.
HENCE, CRX__LIB__IS_CPPH_INCLUDING IS ASSUMED TRUE. THIS IS UNLIKE CRX__LIB__PUBLIC_FUNCTION() WHICH
RELIES ON DIFFERENT ASSUMPTIONS TO GET ITS SIMPLIFICATION, AND IS TO BE USED IN BOTH ".h" AND ".cpp.h"
FILES, MEANING ON BOTH DECLERATIONS AND DEFINITIONS.
*/
#define CRX__LIB__METHOD() CRXM__IFELSE2(CRXM__NOT(CRX__LIB__IS_CPP_INCLUDING), inline, )
#define CRX__LIB__IS_TO_INCLUDE_IN_H() CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, 1, \
		CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, 0, 1))
//#define CRX__LIB__IS_TO_INCLUDE_IN_CPPH() CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, 0, 1)
#define CRX__LIB__IS_TO_INCLUDE_IN_CPPH() CRXM__IFELSE2(CRXM__AND(CRXM__NOT(CRX__LIB__IS_CPP_INCLUDING), \
		CRX__LIB__IS_CPPH_INCLUDING), 1, 0)
//CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_CPPH()
//CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_H()
//CRX__LIB__PUBLIC_STATIC_VARS_START(pClassName)
//CRX__LIB__PUBLIC_STATIC_VARS_END()
//CRX__LIB__PROTECTED_STATIC_VARS_START(pClassName)
//CRX__LIB__PROTECTED_STATIC_VARS_END()
//CRX__LIB__PRIVATE_STATIC_VARS_START(pClassName)
//CRX__LIB__PRIVATE_STATIC_VARS_END()
//CRX__LIB__PUBLIC_STATIC_VAR()
//CRX__LIB__PROTECTED_STATIC_VAR()
//CRX__LIB__PRIVATE_STATIC_VAR()
#if(!defined(CRX__LIB__CONFIG__FAVOR_STATIC_INLINE) || !defined(CRX__LIB__STATIC_INLINE_DATA_MEMBERS_ARE_SUPPORTED))
	#define CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, pAccess, pTypeDef) \
		CRXM__IFELSE(CRX__LIB__IS_CPP_INCLUDING) \
		( \
			typedef pClassName pTypeDef; \
		) \
		( \
			CRXM__IFELSE(CRX__LIB__IS_CPPH_INCLUDING) \
			( \
				pAccess: template<int L> \
				class Crx__ ## pAccess ## Statics \
				{ \
			) \
			( \
				typedef pClassName pTypeDef; \
			) \
		)
	//#END_DEFINE
	#define CRX__LIB__PRIVATE__STATIC_VARS_END(pParenthesizedClassName, pAccess, pTypeDef) \
		CRXM__IFELSE(CRX__LIB__IS_CPP_INCLUDING) \
		( \
		) \
		( \
			CRXM__IFELSE(CRX__LIB__IS_CPPH_INCLUDING) \
			( \
				}; \
				typedef Crx__ ## pAccess ## Statics <0> pTypeDef; \
			) \
			( \
			) \
		)
	//#END_DEFINE
	#define CRX__LIB__PUBLIC_STATIC_VARS_START(pClassName) \
			CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, public, StaticPublicVars)
	#define CRX__LIB__PUBLIC_STATIC_VARS_END() CRX__LIB__PRIVATE__STATIC_VARS_END(, public, StaticPublicVars)
	#define CRX__LIB__PROTECTED_STATIC_VARS_START(pClassName) \
			CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, protected, StaticProtectedVars)
	#define CRX__LIB__PROTECTED_STATIC_VARS_END() CRX__LIB__PRIVATE__STATIC_VARS_END(, protected, StaticProtectedVars)
	#define CRX__LIB__PRIVATE_STATIC_VARS_START(pClassName) \
			CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, private, StaticPrivateVars)
	#define CRX__LIB__PRIVATE_STATIC_VARS_END() CRX__LIB__PRIVATE__STATIC_VARS_END(, private, StaticPrivateVars)

	#define CRX__LIB__PUBLIC_STATIC_VAR() public: static
	#define CRX__LIB__PROTECTED_STATIC_VAR() public: static
	//NOTE: USING private INSTEAD OF public WORKS IN VISUAL STUDIO 2017 FOR SOME REASON.
	#define CRX__LIB__PRIVATE_STATIC_VAR() public: static

	#define CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_CPPH() 1
	#define CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_H() 0
#else
	#define CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, pAccess, pTypeDef) \
			typedef pClassName pTypeDef;
	#define CRX__LIB__PRIVATE__STATIC_VARS_END(pClassName, pAccess, pTypeDef)


	#define CRX__LIB__PUBLIC_STATIC_VARS_START(pClassName) \
			CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, , StaticPublicVars)
	#define CRX__LIB__PUBLIC_STATIC_VARS_END()
	#define CRX__LIB__PROTECTED_STATIC_VARS_START(pClassName) \
			CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, , StaticProtectedVars)
	#define CRX__LIB__PROTECTED_STATIC_VARS_END()
	#define CRX__LIB__PRIVATE_STATIC_VARS_START(pClassName) \
			CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, , StaticPrivateVars)
	#define CRX__LIB__PRIVATE_STATIC_VARS_END

	#define CRX__LIB__PUBLIC_STATIC_VAR() CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, public: static, \
			CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, public: static inline, public: static))
	#define CRX__LIB__PROTECTED_STATIC_VAR() CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, protected: static, \
			CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, protected: static inline, protected: static))
	#define CRX__LIB__PRIVATE_STATIC_VAR() CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, private: static \
			CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, private: static inline, private: static))

	#define CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_CPPH() \
			CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, 1, 0)
	#define CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_H() \
			CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, 0, CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, 1, 0))
#endif

#define CRX__LIB__PRIVATE_FUNCTION() static
/*
THE FOLLOWING ASSUMES THAT GLOBAL FUNCTIONS ARE AUTOMATICALLY extern. IT ALSO ASSUMES
THAT IF CODE IS COMPILER WITH EFFECTIVE EXTERN, MEANING NOT EXPLICIT "extern", ON BOTH 
THE HEADER, MEANING ON THE DECLERATION, AND SOURCE, MEANING ON THE DEFINITION, IN THE 
TRADITIONAL SENSE, AND THEN HEADERS ARE USED WITH "inline" IN THE DECLERATIONS, TO
MAKE USE OF THE ALREADY COMPILED CODE, THE CODE USING THE HEADERS WOULD CONTINUE TO
COMPILE AND WORK.

THE REASON THE ABOVE ASSUMPTIONS ARE TAKEN IS TO AVOID HAVING TO DEFINE THE MACRO AS
		#define CRX__LIB__PUBLIC_FUNCTION() CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, , \
				CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, inline, ))
THE PROBLEM WITH THE ABOVE DEFINITION IS THAT WOULD THEN REQUIRE THE LINE
				#pragma pop_macro("CRX__LIB__IS_CPPH_INCLUDING")
IN THE ".cpp.h" FILES TO BE MOVED TO THE BOTTOM OF THESE FILES.
*/
#define CRX__LIB__PUBLIC_FUNCTION() CRXM__IFELSE2(CRXM__NOT(CRX__LIB__IS_CPP_INCLUDING), inline, )

/*
WARNING: THE USE OF THE FOLLOWING IS NOT ADOPTED YET. THIS IS BECAUSE OF NEEDING
TO CHANGE THE POSITION OF #pragma pop_macro("CRX__LIB__IS_CPPH_INCLUDING") IN THE
".cpp.h" FILES TO THE BOTTOM OF THESE FILES.
*/
/*#define CRX__LIB__PRIVATE_CONSTANT(pIS_DEFINITION) \
		CRXM__IFELSE2(CRXM__NOT(pIS_DEFINITION), extern, )
#define CRX__LIB__PUBLIC_CONSTANT(pIS_DEFINITION) CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, extern, \
		CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, \
		CRXM__IFELSE2(CRXM__NOT(pIS_DEFINITION), extern, ), extern))*/


/*
- WARNING ABOUT CRX__LIB__PRIVATE_C_CONSTANT() AND CRX__LIB__PUBLIC_C_CONSTANT().
	- REMEMBER THE VISIBILITY HERE IS COMPILATION UNIT VISIBILITY AS DEFINED IN MY STANDARD IF
			CODE IS USED UNDER THE NON ODR PARADIGN, MEANING AS A HEADER ONLY LIBRARY IN THE 
			CRX/LIB ARCHITECTURE, THERE CAN BE MANY OF THE SAME CONSTANT IN FINAL COMPILED
			CODE, ONE IN EACH TRANSLATION UNIT USING THE HEADERS. THESE CONSTANTS ARE
			NOT GUARANTEED TO BE EQUAL. THEREFORE, WHATEVER YOU ASSIGN TO THEM MAKE SURE
			THAT YOU KNOW THE VALUE OF IT AT COMPILER TIME, NOT RUN TIME. FOR EXAMPLE,
			A CONSTANT POINTER RETURNED BY malloc WOULD NOT WORK, BECAUSE EACH PERTAINING
			COMPILATION UNIT WILL HAVE A DIFFERENT POINTER.
	- REMEMBER THAT YOU STILL NEED TO USE THE KEYWORD const WHEN USING THESE MACROS.
- ABOUT CRX__LIB__PRIVATE_C_CONSTANT() AND CRX__LIB__PUBLIC_C_CONSTANT().
	- NOTE THAT IN C++ WE CAN NOT FARWARD DECLARE USING static.
					"It is only possible in C++ to forward declare an object if you use the 
					extern keyword and do not specify an initializer."
			WHILE IN C WE COULD WRITE
					//DECLERATION
					static int gInts[3];		//IN C THIS IS CALLED A TENTATIVE DECLERATION
					//DEFINITION
					static int gInts[3] = {1, 10, 276};
			IN C++ WE HAVE TO WRITE
					//DECLERATION
					namespace{extern int gInts[3];}
					//DEFINITION
					namespace{int bigIntArray[3] = {1, 10, 276};}
			THIS IS OFCOURSE PROBLOMATIC BECAUSE OF THE NEED TO ADD THE END BRACES. 
	- TO SOLVE THIS ISSUE THE LINE 
					#pragma pop_macro("CRX__LIB__IS_CPPH_INCLUDING")
			IN THE ".cpp.h" FILES WOULD NEED TO BE MOVED TO THE BOTTOM OF THESE FILES.
			ANOTHER APPROACH TO FORBID DEFINING C CONSTANTS EXCEPT IN ".h" FILES. THIS
			KILLS CODE SYMMETRY AS DEFINED IN THE STANDARD, AND MAKES BINARIES UNNECESSARILY
			LARGE WHEN NOT IN HEADER ONLY MODE. CONSIDER THE CASE WHEN THE CONSTANT IS
			PRIVATE, AND THE LIBRARY IS NOT IN HEADER ONLY MODE. WITH THE AFORE MENTIONED
			SOLUTION, THE CONSTANT WOULD BE DECLARED AND DEFINED IN THE SAME STATEMENT
			WITH static AND WOULD HAVE COPIES IN EVERY TRANSLATION UINTS REQUIRING IT.
			NOTE THAT ALTHOUGH THE SIZE BECOMES LARGER, THE SEMANTICS OF CONSTANT REMAIN
			CORRECT AS DEFINED FOR CRX LIB.

- NOTE THAT THE FOLLOWING CAN NOT BE USED WITH inline TO INLINE FUNCTIONS. CURRENTLY
		INLINE FUNCTIONS SHOULD NOT BE USED AT ALL. LEAVE IT TO THE COMPILER TO
		DECIDE INLINING. IN THEORY, UNDER
				- C (GNU89): 
					- HEADER ONLY LIBRARY:
						- static FOR PRIVATE FUNCTIONS
						- static FOR PUBLIC FUNCTIONS
					- NOT HEADER ONLY:
						- static FOR PRIVATE FUNCTIONS
						- NOTHING FOR PUBLIC FUNCTIONS 	(RELYING ON DEFAULT extern FOR FUNCTIONS
								IN THIS CASE)
				- C (C99):
					- HEADER ONLY LIBRARY:
						- static FOR PRIVATE FUNCTIONS
						- static FOR PUBLIC FUNCTIONS
					- NOT HEADER ONLY:
						- static FOR PRIVATE FUNCTIONS
						- extern FOR PUBLIC FUNCTIONS
				- C++:
					- HEADER ONLY LIBRARY:
						- static FOR PRIVATE FUNCTIONS
						- static FOR PUBLIC FUNCTIONS
					- NOT HEADER ONLY:
						- static FOR PRIVATE FUNCTIONS
						- extern FOR PUBLIC FUNCTIONS
		AND WITH CRX__LIB__PRIVATE_C_FUNCTION() AND CRX__LIB__PUBLIC_C_FUNCTION()
		DEFINED USING THE ABOVE ONE COULD COMBINE THEM WITH inline. HOWEVER, THERE
		ARE SEVERAL PROBLEMS:
				- static inline IS NOT REALY PART OF C++ EVEN IF COMPILERS TEND TO SUPPORT IT.
				- extern inline IS NOT REALY PART OF C++ EVEN IF COMPILERS TEND TO SUPPORT IT.
				- C89 DOES NOT SUPPORT inline BUT THAT CAN BE SUPPORTED BY NOT USING inline AT
						ALL IN THAT CASE. TRYING TO USE COMPILER SPECIFIC EXTENSIONS, SUCH AS
						__inline IS NOT A GOOD IDEA BECAUSE ONE HAS TO INVESTIGATE THOSE 
						EXTENSION'S BEHAVIOR WHEN COMBINED WITH static AND extern.
				- WHETHER WITH THE ABOVE A FUNCTION'S ADDRESS CAN BE TAKEN OR NOT MIGHT NOT
						BE CONSISTANT. HOWEVER, AS FAR AS I CAN TELL, WITH THE ABOVE,
						ALL FUNCTIONS ALLOW THE ADDRESS TO BE TAKEN
*/
//CRX__LIB__IS_TO_INCLUDE_IN_C_H()
//CRX__LIB__IS_TO_INCLUDE_IN_C_CH()
//CRX__LIB__PUBLIC_C_FUNCTION()
//CRX__LIB__PRIVATE_C_FUNCTION()
//CRX__LIB__PUBLIC_INLINE_C_FUNCTION()
//CRX__LIB__PRIVATE_INLINE_C_FUNCTION()
#if(defined(__cplusplus) || CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	/*
	WITHOUT DLL SUPPORT
	*/
	#define CRX__LIB__PRIVATE_C_FUNCTION() static
	//#define CRX__LIB__PUBLIC_C_FUNCTION() CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, static, extern)
	#define CRX__LIB__PUBLIC_C_FUNCTION() CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, extern, \
			CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, static, extern))
	/*	
	DLL SUPPORT
	THE FOLLOWING WOULD REQUIRE THE LINE
					#pragma pop_macro("CRX__LIB__IS_CPPH_INCLUDING")
			IN THE ".cpp.h" FILES TO BE MOVED TO THE BOTTOM OF THESE FILES.

	#define CRX__LIB__PRIVATE_C_FUNCTION() CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, CRX_DLL_NO_EXPORT_C_FUNCTION, \
			CRXM__IFELSE2(CRXM__NOT(CRX__LIB__IS_CPPH_INCLUDING), \
			CRX_DLL_NO_EXPORT_C_FUNCTION, ) static
	#define CRX__LIB__PUBLIC_C_FUNCTION() CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, \
			CRXM__IFELSE2(CRX__LIB__IS_DLL, CRX_DLL_EXPORT_C_FUNCTION extern, extern), \
			CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, static, \
			CRXM__IFELSE2(CRX__LIB__IS_DLL, CRX_DLL_IMPORT_C_FUNCTION extern, extern)))
	*/

	//#define CRX__LIB__IS_TO_INCLUDE_IN_C_H() CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, 0, 1)
	//#define CRX__LIB__IS_TO_INCLUDE_IN_C_CH() CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, 1, 0)
	#define CRX__LIB__IS_TO_INCLUDE_IN_C_H() CRX__LIB__IS_TO_INCLUDE_IN_H()
	#define CRX__LIB__IS_TO_INCLUDE_IN_C_CH() CRX__LIB__IS_TO_INCLUDE_IN_CPPH()


	//START: INLINE SUPPORT
	//WARNING: THE FOLLOWING IS EXPERIMENTAL, AND LIKELY ILL DEFINED. NOTICE
	//		THE DIFFERENT BEHAVIOR OF C++ VS C FOR EXAMPLE. THINK OF THE SITUATION
	//		WHEN THE CODE IS COMPILED AS C, MEANING NOT HEADER ONLY SITUATION, 
	//		BUT THEN THE C HEADER IS USED IN C++ TO USE IT. ALSO REMEMBER THAT
	//		C CODE WILL BE WRAPPED IN extern C IN C++.

	/*
		IN TIME, THE FOLLOWING NEEDS TO SUPPORT OTHER C++ COMPILERS THAT HAVE 
			THE EXTENSION static inline. AS FOR extern inline, C++ inline
			SHOULD BE WHAT extern online MEANS IN GNU89. REMEMBER:
					CRX__LIB__PRIVATE__STATIC_INLINE: FUNCTION IS INLINE, AS DEFINED IN C++,
							BUT NOT AVAILABLE TO OTHER COMPILATION UNITS. FUNCTION ADDRESS
							CAN BE TAKEN.
					CRX__LIB__PRIVATE__EXTERN_INLINE: FUNCTION IS INLINE, AS DEFINED IN C++,
							AND AVAILABLE TO OTHER COMPILATION UNITS. (SHOULD ALREADY BE
							THE CASE IN C++). FUNCTION ADDRESS CAN BE TAKEN.
							NOTICE HOW THIS IS ONLY USED IF THE LIBRARY IS NOT HEADER ONLY,
							MEANING THE CODE IS COMPILED IN C, IN WHICH IT WOULD HAVE BEEN
							DEFINED USING C'S extern inline (C99 DEFINITION), HENCE WHY
							THE MACRO EXALUATES TO extern, AND NOT extern __inline FOR
							EXAMPLE, EVEN THOUGH MSVC SUPPORTS IT.
	*/
	#if(defined(_MSC_VER))
		#define CRX__LIB__PRIVATE__STATIC_INLINE static __inline
		#define CRX__LIB__PRIVATE__EXTERN_INLINE extern
	#else
		#define CRX__LIB__PRIVATE__STATIC_INLINE static
		#define CRX__LIB__PRIVATE__EXTERN_INLINE extern
	#endif
	
	#if(defined(__cplusplus))
		/*
		WITHOUT DLL SUPPORT
		*/
		#define CRX__LIB__PRIVATE_INLINE_C_FUNCTION() CRX__LIB__PRIVATE__STATIC_INLINE
		#define CRX__LIB__PUBLIC_INLINE_C_FUNCTION() CRXM__IFELSE2( \
				CRX__LIB__IS_CPP_INCLUDING, CRX__LIB__PRIVATE__EXTERN_INLINE, \
				CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, CRX__LIB__PRIVATE__STATIC_INLINE, \
				CRX__LIB__PRIVATE__EXTERN_INLINE))
		/*	
		WITH DLL SUPPORT
		THE FOLLOWING WOULD REQUIRE THE LINE
						#pragma pop_macro("CRX__LIB__IS_CPPH_INCLUDING")
				IN THE ".cpp.h" FILES TO BE MOVED TO THE BOTTOM OF THESE FILES.
				
		#define CRX__LIB__PRIVATE_INLINE_C_FUNCTION() CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, CRX_DLL_NO_EXPORT_C_FUNCTION, \
				CRXM__IFELSE2(CRXM__NOT(CRX__LIB__IS_CPPH_INCLUDING), \
				CRX_DLL_NO_EXPORT_C_FUNCTION, ) CRX__LIB__PRIVATE__STATIC_INLINE
		#define CRX__LIB__PUBLIC_C_FUNCTION() CRXM__IFELSE2( \
				CRX__LIB__IS_CPP_INCLUDING, CRXM__IFELSE2(CRX__LIB__IS_DLL, \
						CRX_DLL_EXPORT_C_FUNCTION CRX__LIB__PRIVATE__EXTERN_INLINE, \
						CRX__LIB__PRIVATE__EXTERN_INLINE), \
				CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, CRX__LIB__PRIVATE__STATIC_INLINE, \
				CRXM__IFELSE2(CRX__LIB__IS_DLL, \
						CRX_DLL_IMPORT_C_FUNCTION CRX__LIB__PRIVATE__EXTERN_INLINE, \
						CRX__LIB__PRIVATE__EXTERN_INLINE)))
		*/
	#else
		/*
		WITHOUT DLL SUPPORT
		*/
		#define CRX__LIB__PRIVATE_INLINE_C_FUNCTION() CRX__C__PRIVATE_INLINE_FUNCTION
		#define CRX__LIB__PUBLIC_INLINE_C_FUNCTION() CRXM__IFELSE2( \
				CRX__LIB__IS_CPP_INCLUDING, CRX__C__EXTERN_INLINE_FUNCTION, \
				CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, CRX__C__PRIVATE_INLINE_FUNCTION, \
				CRX__C__EXTERN_INLINE_FUNCTION))
		/*	
		WITH DLL SUPPORT
		THE FOLLOWING WOULD REQUIRE THE LINE
						#pragma pop_macro("CRX__LIB__IS_CPPH_INCLUDING")
				IN THE ".cpp.h" FILES TO BE MOVED TO THE BOTTOM OF THESE FILES.
				
		#define CRX__LIB__PRIVATE_INLINE_C_FUNCTION() CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, CRX_DLL_NO_EXPORT_C_FUNCTION, \
				CRXM__IFELSE2(CRXM__NOT(CRX__LIB__IS_CPPH_INCLUDING), \
				CRX_DLL_NO_EXPORT_C_FUNCTION, ) CRX__C__PRIVATE_INLINE_FUNCTION
		#define CRX__LIB__PUBLIC_C_FUNCTION() CRXM__IFELSE2( \
				CRX__LIB__IS_CPP_INCLUDING, CRXM__IFELSE2(CRX__LIB__IS_DLL, \
						CRX_DLL_EXPORT_C_FUNCTION CRX__C__EXTERN_INLINE_FUNCTION, \
						CRX__C__EXTERN_INLINE_FUNCTION), \
				CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, CRX__C__PRIVATE_INLINE_FUNCTION, \
				CRXM__IFELSE2(CRX__LIB__IS_DLL, \
						CRX_DLL_IMPORT_C_FUNCTION CRX__C__EXTERN_INLINE_FUNCTION, \
						CRX__C__EXTERN_INLINE_FUNCTION)))
		*/
	#endif
	//END: INLINE SUPPORT


	//WARNING: READ THE WARNING ABOVE BEFORE USING THESE TWO.
	/*#if(defined(__cplusplus))
		#define CRX__LIB__PRIVATE_C_CONSTANT(pIS_DEFINITION) \
				CRXM__IFELSE2(pIS_DEFINITION, static, extern)
		#define CRX__LIB__PUBLIC_C_CONSTANT(pIS_DEFINITION)  CRXM__IFELSE2( \
				CRX__LIB__IS_CPP_INCLUDING, extern, \
				CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, \
						CRXM__IFELSE2(pIS_DEFINITION, static, extern), extern))
	#else
		#define CRX__LIB__PRIVATE_C_CONSTANT(pIS_DEFINITION) static
		#define CRX__LIB__PUBLIC_C_CONSTANT(pIS_DEFINITION) CRXM__IFELSE2( \
				CRX__LIB__IS_CPP_INCLUDING, extern, \
				CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, static, extern))
	#endif*/
#else
	#ifndef CRX__LIB__IS_C_HEADER_ONLY
		#define CRX__LIB__IS_C_HEADER_ONLY 0
	#endif

	/*
	WITHOUT DLL SUPPORT
	*/
	#define CRX__LIB__PRIVATE_C_FUNCTION() static
	#define CRX__LIB__PUBLIC_C_FUNCTION() CRXM__IFELSE2(CRX__LIB__IS_C_HEADER_ONLY, static, extern)
	/*
	DLL SUPPORT
	CAN NOT SUPPORT DLL IN THIS CASE, MEANING IN C COMPILERS THAT DO NOT SUPPORT
	PUSH MACRO. THIS IS BECAUSE WE CAN NOT TELL THE DIFFERENCE IN THIS CASE IF THE C 
	LIBRARY IS NOT USED AS HEADER ONLY WHETHER IT IS USED TO COMPILE SOURCE CODE OR
	AS HEADERS TO USE ALREADY COMPILED SOURCE CODE. TO SOLVE THIS, THE MACRO
	CRX__LIB__IS_C_HEADER_ONLY WOULD HAVE TO REDEFINED TO BE AN ENUMERATION INSTEAD
	OF A BOOLEAN, AND AT THIS TIME WE ALREADY HAVE THE NON AUTOMATED IMPLEMENTATOIN
	OF CRX LIB THAT USES ENUMERATIONS.
	#define CRX__LIB__PRIVATE_C_FUNCTION() TYTRYTRYTYTYTERRRRRRRRRRRRRROR
	#define CRX__LIB__PUBLIC_C_FUNCTION() EHGFHGFHGFHGFHERRRRRRRRRRRRRROR
	*/

	#define CRX__LIB__IS_TO_INCLUDE_IN_C_H() CRXM__IFELSE2(CRX__LIB__IS_C_HEADER_ONLY, 0, 1)
	#define CRX__LIB__IS_TO_INCLUDE_IN_C_CH() CRXM__IFELSE2(CRX__LIB__IS_C_HEADER_ONLY, 1, 0)


	//START: INLINE SUPPORT
	//WARNING: THE FOLLOWING IS EXPERIMENTAL, AND LIKELY ILL DEFINED. NOTICE
	//		THE DIFFERENT BEHAVIOR OF C++ VS C FOR EXAMPLE. (SEE ABOVE)
	#define CRX__LIB__PRIVATE_INLINE_C_FUNCTION() CRX__C__PRIVATE_INLINE_FUNCTION
	#define CRX__LIB__PUBLIC_INLINE_C_FUNCTION() CRXM__IFELSE2( \
			CRXM__NOT(CRX__LIB__IS_C_HEADER_ONLY), CRX__C__EXTERN_INLINE_FUNCTION, \
			CRX__C__PRIVATE_INLINE_FUNCTION)
	//END: INLINE SUPPORT


	//WARNING: READ THE WARNING ABOVE BEFORE USING THESE TWO.
	//#define CRX__LIB__PRIVATE_C_CONSTANT() static
	//#define CRX__LIB__PUBLIC_C_CONSTANT() CRXM__IFELSE2(CRX__LIB__IS_C_HEADER_ONLY, static, extern)
#endif

//CRX__LIB__C_CODE_BEGIN()
//CRX__LIB__C_CODE_END()
#if(defined(__cplusplus))
	//#define CRX__LIB__C_CODE_BEGIN() CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, , extern "C" {)
	//#define CRX__LIB__C_CODE_END() CRXM__IFELSE2(CRX__LIB__IS_CPPH_INCLUDING, , })
	#define CRX__LIB__C_CODE_BEGIN() CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, extern "C" {, \
			CRXM__IFELSE2(CRXM__NOT(CRX__LIB__IS_CPPH_INCLUDING), extern "C" {, ))
	#define CRX__LIB__C_CODE_END() CRXM__IFELSE2(CRX__LIB__IS_CPP_INCLUDING, }, \
			CRXM__IFELSE2(CRXM__NOT(CRX__LIB__IS_CPPH_INCLUDING), }, ))

	#define CRX__LIB__EXTERN_C CRXM__IFELSE2(CRXM__AND(CRXM__NOT(CRX__LIB__IS_CPP_INCLUDING), \
			CRX__LIB__IS_CPPH_INCLUDING), extern "C", )
#else
	#define CRX__LIB__C_CODE_BEGIN()
	#define CRX__LIB__C_CODE_END()

	#define CRX__LIB__EXTERN_C
#endif
		#endif
		#pragma endregion //}

		#pragma region NOT AUTOMATED IMPLEMENTATION //{
		#if(!CRX__LIB__PRIVATE__IS_AUTOMATED)
/* LIB: C++ case
CRX LIB IS TO ALLOW ONE TO BUILD A LIBRARY SUCH AS,
	1- 
		A- CLIENT CAN CONFIGURE THE LIBRARY. THIS USES DEFINES. THIS ENDS UP IMPLYING 
			THAT A LIBRARY SHOULD HAVE THE POSSIBILITY OF BEING A HEADER ONLY LIBRARY.
			CLIENT CONFIGURING LIBRARY MEANS CONFIGURATION THAT AFFECT HOW THE LIBRARY
			BEHAVES.
		B- CLIENT DEFINES MADE BY CLIENT CODE CAN BE PROPOGATED INTO THE LIBRARY WITHOUT 
			THE HELP OF THE COMPILER. THIS IS NEEDED TO BECAUSE COMPILER AIDED
			DEFINES ARE HIDDEN, UNLIKE DEFINES MADE EXPLICITLY IN CODE WHICH ARE MORE
			OBVIOUS. FURTHER MORE, DEFINES MADE AT THE COMPILER BREAK MY STANDARD THAT
			REQUIRE DEFINES TO HAVE VALUES, EVEN IF EMPTY. ON THE OTHER HAND
			DEFINES MADE AT THE COMPILER LEVEL HAVE A VALUES THAT IS EQUAL TO THEIR
			EXISTANCE RATHER THAN THEIR VALUE. HENCE THESE WOULD USED THINGS LIKE
			defined() WHEN CHECKED FOR.
	2- THE LIBRARY CAN BE USED AS A STATIC/DYNAMIC, OR HEADER ONLY LIBRARY. REMEMBER,
			FOR EXAMPLE THAT AS A HEADER ONLY LIBRARY IT SHOULD HAVE THE ADVANTAGE OF 
			HEADER ONLY LIBRARY WHICH GENERALY USE TEMPLATES, MAKING CODE FALL
			INTO THE PARADIGM OF OTHER LANGUAGES WHERE YOU DO NOT HAVE TO WORRY
			ABOUT ODR. REMEMBER ODR CAN NOT BE SOLVED WITH INCLUDE GUARDS OR
			pragma once. ODR IS AN ISSUE OF THE SAME SYMBOL DEFINED IN MULTIPLE
			COMPILATION UNITS. BY CRX LIB, THE CODE, EVEN THOUGH IT MIGHT BE
			NOT A TEMPLATE ONLY LIBRARY, WOULD STILL BEHAVE IN THIS PARADIGM
			WHEN USED AS A HEADER ONLY LIBRARY.

POSSIBLE SCENARIOS:
	A- CRXed LIBRARY ITSELF IS A PRE COMPILED STATIC LIBRARY, OR PERHAPS DLL. 
			IN THIE CASE, THE ENTIRE LIBRARY'S CPP FILES ARE THEMSELVES COMPILED. THE 
			LIBRARY MIGHT USE OTHER CRXed LIBRARIES THAT ARE NOT NECESSARY THEMSELVES
			PRE COMPILED. 
			IN THIS CASE, THE CLIENT IS ONLY GIVEN, AND ONLY USES, THE ".h" FILES OF THE
			CRXed LIBRARY.
			IN THIS CASE, THE CRXed LIBRARY CAN NOT BE CONFIGURED BY CLIENT CODE BECAUSE IT 
			IS ALREADY COMPILED. NOTE THAT THIS IS NOT TO BE CONFUSED WITH THE CONFIGURATION
			THAT THE CLIENT STILL NEEDS TO SET WHEN USING THE LIBRARY, WHICH MUST MATCH
			THE CONFIGURATION SET WHEN THE LIBRARY WAS COMPILED. THE CLIENT CONFIGURATION ARE
			SIMPLY ABOUT USING THE LIBRARY CORRECTLY, RATHER THAN DEFINING ITS BEHAVIOR.
			IN THIS CASE, CONFIGURATION IS SET AS CODE, BUT NOT BY CLIENT. THIS IS DONE IN
			THE stafx.h FILE.
	B- CRXed LIBRARY ITSELF IS A PRE COMPILED STATIC LIBRARY, OR PERHAPS DLL, HOWEVER
			IT IS OPEN SOURCE.
			IN THIS CASE, CLIENT CODE COMPILES THE CPP FILES OF THE CRXed LIBRARY HIMSELF.
			IN THIS CASE, THE CLIENT CONTINUES TO USE ONLY ".h" FILES OF THE CRXed LIBRARY.
			IN THIS CASE, THE CRXed LIBRARY CAN BE CONFIGURED BY CLIENT. THIS IS NOT
			TO BE CONFUSED WITH THE CONFIGURATION THAT THE CLIENT STILL NEEDS TO SET WHEN 
			USING THE LIBRARY, WHICH MUST MATCH THE CONFIGURATION SET WHEN THE LIBRARY WAS
			COMPILED, MEANING THE CONFIGURATION IN THE stdafx.h FILE
			IN THIS CASE, CONFIGURATION IS SET AS CODE. THIS IS DONE IN THE stdafx.h FILE.
			<DEPRECATED>IN THIS CASE, THE CLIENT CODE WOULD NOT BE ABLE TO CONFIGURE THE CODE FROM 
			WITHIN HIS CODE BECAUSE THE DEFINES WOULD NOT PROPOGATE TO THE CRXed LIBRARY
			IN QUESTION, BUT UNLIKE SCENARIO 'A' THE CLIENT CAN STILL CONFIGURE THE 
			LIBRARY USING THE DEFINES SET AT THE COMMAND LINE LEVEL.</DEPRECATED>
	C- CRXed LIBRARY ITSELF IS A HEADER ONLY LIBRARY. 
			IN THIS CASE, THE LIBRARY'S CPP FILES ARE NOT COMPILED, AND NEITHER
			DOES CLIENT COMPILES THE CPP FILES OF THIS LIBRARY HIMSELF (THAT WOULD BE SCENARIO
			'B' ABOVE). 
			IN THIS CASE, THE CRXed LIBRARY CODE ACTS UNDER THE NON ODR PARADIGM.
			IN THIS CASE, THE CLIENT MUST SET THE CONFIGURATION MACRO SPECIFIC TO HIS
			LIBRARY THAT CONTROLS WHETHER THE LIBRARY IS HEADER ONLY OR NOT. THIS IS THE MACRO
			"MY_LIBRARY_NAME__MODE" IN THE TEMPLATE BELOW. THE CLIENT SHOULD SET IT
			TO CRX__LIB__MODE__HEADER_ONLY.
			IN THIS CASE, THE CLIENT USES ".h" FILES OF THE CRXed LIBRARY AND WOULD HAVE
			HIS OWN CPP FILES THAT INCLUDES THE CRXed LIBRARY CODE TO COMPILE.
			IN THIS CASE, THE CLIENT STILL NEVER USES THE ".cpp.h" FILES OF THIS LIBRARY.
			IN THIS CASE, THE CRXed LIBRARY CAN BE CONFIGURED BY CLIENT.
			IN THIS CASE, CONFIGURATION IS SET AS CODE, AND THE CLIENT IS ABLE TO DECIDE
			WHERE TO DO THIS IN HIS CODE.
			IN THIS CASE, THE CLIENT CODE WOULD BE ABLE TO CONFIGURE THE CODE BY HIS CODE.
			<IN PROGRESS>IN THIS CASE, THE CLIENT IS FREE TO HAVE DIFFERENT CONFIGURATIONS TO DIFFERENT
			PARTS OF THE CRXed LIBRARY PROVIDED THAT THE LIBRARY SUPPORTS IT. THIS MEANS 
			THAT THE SAME CONFIGURATION MACRO WOULD BE GIVEN A DIFFERENT VALUE DEPENDING
			ON WHICH ".cpp.h" IS BEING USED.</IN PROGRESS>

	REMEMBER THAT UNDER ALL SCENARIOS ABOVE, YOU ARE WRITING THE CRXed CODE EXACTLY THE SAME.

USAGE:
	- CODE MUST BE BROKEN INTO THREE DIFFERENT FILES, ".h", ".cpp" and ".cpp.h".
	- ".h" INCLUDES THE USUAL HEADER ONLY INFORMATION, BUT NO SOURCE CODE, EVEN FOR TEMPLATES.
			THESE MUST ALSO HAVE INCLUDE GUARDS.
	- ".cpp.h" INCLUDES ALL SOURCE CODE.
			THESE DO NOT HAVE INCLUDE GUARDS BECAUSE THEY ARE ONLY INCLUDED IN THE CORRESPONDING
			".h" FILE WHICH ITSELF HAS INCLUDE GUARDS, OR AN INCLUDED IN THE CORRESPONDING
			".cpp" FILE, AND ".cpp" ARE ENTRY CODE FILES AS DEFINED IN MY STANDARD AND THEREFORE MAY
			NOT BE INCLUDED BY OTHER FILES.
	- ".cpp" SERVES NOTHING BUT INDICATE A COMPILATION UNIT.
	- CODE FOLLOWING THE CRX LIB FORMAT WILL BE CALLED CRXed CODE FOR THE PURPOSE OF THIS
			DOCUMENTATION.
	- CODE FROM THE SAME LIBRARY IS ASSUMED TO BE EITHER ALL CRXed OR ALL NON CRXed.
	- WARNING: INCLUDING ".h" OF NON CRXed CODE CAN BREAK THE EFFECT OF CRX__LIB IF THE HEADER IS
			USING THE ODR PARADIGM. FOR EXAMPLE C++ CODE WHERE CLASSES ARE DEFINED IN THE HEADER 
			AND THEY ARE NOT TEMPLATES. IF A CRXed LIBRARY USING SUCH CODE IS DISTRIBUTED AS A HEADER
			ONLY LIBRARY, IT WILL END UP WORKING WITH THE ODR PARADIGM BECAUSE OF THE INCLUDED C++ 
			HEADER.

".h": {C++}
	#pragma once

	->> SUGGESTED //... INCLUDE THIS FILE (crx.h), OR A FILE THAT INCLUDES THIS FILE ... <<--
	#pragma push_macro("CRX__LIB__MODE")
	#undef CRX__LIB__MODE
	->> REMEMBER TO RENAME "MY_LIBRARY_NAME__MODE" TO YOUR OWN CONFIGURATION MACRO. <<--
	#if(!defined(MY_LIBRARY_NAME__MODE))
		#define MY_LIBRARY_NAME__MODE CRX__LIB__MODE__STAND_ALONE
	#endif
	#define CRX__LIB__MODE MY_LIBRARY_NAME__MODE
	//<<START>>	INCLUDE ".h" OF NON CRXed CODE THAT THIS HEADER NEEDS.
	//			INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE.
	//<<END>>
	->> DO NOT FORGET THE BOTTOM BIT <<--
	.
	.
	.

	class MyClass
	{
		.
		.
	#if(CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_H())
		...THIS IS ONLY NEEDED IF "CRX__LIB__CONFIG__FAVOR_STATIC_INLINE" IS DEFINED. THIS ...
		...		ESSENTIALLY FAVORS FEATURES OF C++17 WHEN USING C++17 OR HIGHER. ...
		CRX__LIB__PUBLIC_STATIC_VARS_START(MyClass)
			... THIS IS WHERE YOU CAN DEFINE YOUR PUBLIC STATIC VARIABLES, AND ONLY HERE ...
			CRX__LIB__PUBLIC_STATIC_VAR() int variable1 = ...;
			CRX__LIB__PUBLIC_STATIC_VAR() int variable2 = ...;
			.
			.
		CRX__LIB__PUBLIC_STATIC_VARS_END
		CRX__LIB__PROTECTED_STATIC_VARS_START(MyClass)
			... THIS IS WHERE YOU CAN DEFINE YOUR PROTECTED STATIC VARIABLES, AND ONLY HERE ...
			CRX__LIB__PROTECTED_STATIC_VAR() int variable3 = ...;
			CRX__LIB__PROTECTED_STATIC_VAR() int variable4 = ...;
			.
			.
		CRX__LIB__PROTECTED_STATIC_VARS_END()
		CRX__LIB__PRIVATE_STATIC_VARS_START(MyClass)
			... THIS IS WHERE YOU CAN DEFINE YOUR PRIVATE STATIC VARIABLES, AND ONLY HERE ...
			CRX__LIB__PRIVATE_STATIC_VAR() int variable5 = ...;
			CRX__LIB__PRIVATE_STATIC_VAR() int variable6 = ...;
			.
			.
		CRX__LIB__PRIVATE_STATIC_VARS_END()
	#else
		...THIS IS ONLY NEEDED IF SUPPORT FOR PRE C++17 IS NEEDED, OR ...
		...		"CRX__LIB__CONFIG__FAVOR_STATIC_INLINE" IS NOT DEFINED.  ...
		CRX__LIB__PUBLIC_STATIC_VARS_START(MyClass)
			... THIS IS WHERE YOU CAN DEFINE YOUR PUBLIC STATIC VARIABLES, AND ONLY HERE ...
			CRX__LIB__PUBLIC_STATIC_VAR() int variable1;
			CRX__LIB__PUBLIC_STATIC_VAR() int variable2;
			.
			.
		CRX__LIB__PUBLIC_STATIC_VARS_END()
		CRX__LIB__PROTECTED_STATIC_VARS_START(MyClass)
			... THIS IS WHERE YOU CAN DEFINE YOUR PROTECTED STATIC VARIABLES, AND ONLY HERE ...
			CRX__LIB__PROTECTED_STATIC_VAR() int variable3;
			CRX__LIB__PROTECTED_STATIC_VAR() int variable4;
			.
			.
		CRX__LIB__PROTECTED_STATIC_VARS_END()
		CRX__LIB__PRIVATE_STATIC_VARS_START(MyClass)
			... THIS IS WHERE YOU CAN DEFINE YOUR PRIVATE STATIC VARIABLES, AND ONLY HERE ...
			CRX__LIB__PRIVATE_STATIC_VAR() int variable5;
			CRX__LIB__PRIVATE_STATIC_VAR() int variable6;
			.
			.
		CRX__LIB__PRIVATE_STATIC_VARS_END()
	#endif
		.
		.
	}
	
	CRX__LIB__PUBLIC_FUNCTION() void myGlobal_doSomthing(void);
	CRX__LIB__PRIVATE_FUNCTION() void myGlobal_doSomthing2(void);
	
	.
	.
	.
	->> THE BOTTOM BIT DO NOT FORGET THIS <<--
	#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
		//INCLUDE THE CORRESPONDING .cpp.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#endif
	#pragma pop_macro("CRX__LIB__MODE")

".cpp.h": {C++}
	//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .cpp FILE.
	//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
	//			INCLUDE ".h" OF NON CRXed CODE THAT THIS HEADER NEEDS.
	//			INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE.
	//<<END>>
	.
	.
	.
	#if(CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_CPPH())
		int MyClass::StaticPublicVars::variable1 = ...;
		int MyClass::StaticPublicVars::variable2 = ...;
		.
		.
		int MyClass::StaticProtectedVars::variable3 = ...;
		int MyClass::StaticProtectedVars::variable4 = ...;
		.
		.
		int MyClass::StaticPrivateVars::variable5 = ...;
		int MyClass::StaticPrivateVars::variable6 = ...;
	#endif
	.
	.
	.
	//CRX__LIB__METHOD() MUST BE USED BEFORE EVERY CLASS FUNCTION DEFINITION
	CRX__LIB__METHOD() void MyClass::do(void)
	{
	}

	// CRX__LIB__PUBLIC_FUNCTION() OR  CRX__LIB__PRIVATE_FUNCTION() MUST BE USED BEFORE EVERY GLOBAL 
	//		FUNCTION DEFINITION.
	CRX__LIB__PUBLIC_FUNCTION() void myGlobal_doSomthing(void)
	{
	}
	CRX__LIB__PRIVATE_FUNCTION() void myGlobal_doSomthing2(void)
	{
	}

".cpp": {C++}
	->> REMEMBER TO RENAME "myLibrary_stdafx.h" TO YOUR OWN CONFIGURATION FILE NAME. DO NOT INCLUDE A PATH. <<--
	#include "myLibrary_stdafx.h"
	->> SUGGESTED //... INCLUDE THIS FILE (crx.h), OR A FILE THAT INCLUDES THIS FILE ... <<--
	->> REMEMBER TO RENAME "MY_LIBRARY_NAME__MODE" TO YOUR OWN CONFIGURATION MACRO. <<--
	#if(!defined(MY_LIBRARY_NAME__MODE))
		#define MY_LIBRARY_NAME__MODE CRX__LIB__MODE__STAND_ALONE
	#elif(!CRXM__IS(MY_LIBRARY_NAME__MODE, CRX__LIB__MODE__STAND_ALONE) && \
			!CRXM__IS(MY_LIBRARY_NAME__MODE, CRX__LIB__MODE__DLL_STAND_ALONE))
		#undef MY_LIBRARY_NAME__MODE
		#define MY_LIBRARY_NAME__MODE CRX__LIB__MODE__STAND_ALONE
	#endif
	//<<START>>	INCLUDE CORRESPONDING ".cpp.h" FILE
	//<<END>>


	//... INSTANTIATE TEMPLATES DEFINED IN THE CORRESPONDING ".cpp.h" IF DESIRED


CLIENT CODE:
	CLIENT CODE WISHING TO USE A CRXed LIBRARY MUST DEFINE MY_LIBRARY_NAME__MODE AS 
			CRX__LIB__MODE__HEADER_ONLY:		TO USE IT AS HEADER ONLY LIBRARY
			CRX__LIB__MODE__STAND_ALONE:		TO USE IT AS STATIC LIBRARY TO BE COMPILED
												BY HIMSELF. THIS IS USUALLY NOT SOMETHING
												THE CLIENT NEEDS TO DO BECAUSE THIS WOULD
												ALREADY BE SET BY THE CPP FILES OF THE LIBRARY
												ITSELF
			CRX__LIB__MODE__INTERFACE:			TO USE IT AS HEADERS FOR ALREADY COMPILED
												STATIC LIRBARY
			CRX__LIB__MODE__DLL_STAND_ALONE:	TO USE IT AS DYNAMIC LIBRARY TO BE COMPILED
												BY HIMSELF.
			CRX__LIB__MODE__DLL_INTERFACE:		TO USE IT AS HEADERS FOR ALREADY COMPILED
												DYNAMIC LIRBARY
	OR NOT DEFINE MY_LIBRARY_NAME__MODE AND IT WOULD BE EQUIVILANT TO DEFINING IT AS
	CRX__LIB__MODE__STAND_ALONE. 
	REMEMBER THAT THE NAME "MY_LIBRARY_NAME__MODE" IS SPECIFIC TO EACH CRXed LIBRARY, AND 
	EACH CRXed LIBRARY HAS ONLY ONE NAME FOR "MY_LIBRARY_NAME__MODE".

*/
/* LIB: C case
NOTE THAT THIS CASE, THE TRIVIAL, MANUAL, CASE IS ASSUMED FOR C IN THE C++ SECTIONS ABOVE.

USAGE:
	- CODE MUST BE BROKEN INTO THREE DIFFERENT FILES, ".h", ".c" and ".c.h".
	- ".h" INCLUDES THE USUAL HEADER ONLY INFORMATION, BUT NO SOURCE CODE.
			THESE MUST ALSO HAVE INCLUDE GUARDS.
	- ".c.h" INCLUDES ALL SOURCE CODE.
			THESE DO NOT HAVE INCLUDE GUARDS BECAUSE THEY ARE ONLY INCLUDED IN THE CORRESPONDING
			".h" FILE WHICH ITSELF HAS INCLUDE GUARDS, OR AN INCLUDED IN THE CORRESPONDING
			".c" FILE, AND ".c" ARE ENTRY CODE FILES AS DEFINED IN MY STANDARD AND THEREFORE MAY
			NOT BE INCLUDED BY OTHER FILES.
	- ".c" SERVES NOTHING BUT INDICATE A COMPILATION UNIT.
	- CODE FOLLOWING THE CRX LIB FORMAT WILL BE CALLED CRXed CODE FOR THE PURPOSE OF THIS
			DOCUMENTATION.
	- CODE FROM THE SAME LIBRARY IS ASSUMED TO BE EITHER ALL CRXed OR ALL NON CRXed.
	- IT ASSUMED THAT ".c" FILES WILL ALWAYS BE COMPILED AS C CODE, NOT C++.
	- WARNING: INCLUDING ".h" OF NON CRXed CODE CAN BREAK THE EFFECT OF CRX__LIB IF THE HEADER IS
			USING THE ODR PARADIGM. 


".h": {C}
	#pragma once

	->> SUGGESTED //... INCLUDE THIS FILE (crx.h), OR A FILE THAT INCLUDES THIS FILE ... <<-
	#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
		#pragma push_macro("CRX__LIB__MODE")
		#undef CRX__LIB__MODE
		->> REMEMBER TO RENAME "MY_LIBRARY_NAME__MODE" TO YOUR OWN CONFIGURATION MACRO. <<--
		#if(!defined(MY_LIBRARY_NAME__MODE))
			#define MY_LIBRARY_NAME__MODE CRX__LIB__MODE__STAND_ALONE
		#endif
		#define CRX__LIB__MODE MY_LIBRARY_NAME__MODE
	#else
		#undef CRX__LIB__MODE
		#if(!defined(CRX__LIB__C_MODE))
			#define CRX__LIB__C_MODE CRX__LIB__MODE__STAND_ALONE
		#endif
		#define CRX__LIB__MODE CRX__LIB__C_MODE
	#endif
	//<<START>>	INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
	//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
	//<<END>>
	
	CRX__LIB__C_CODE_BEGIN()
	->> DO NOT FORGET THE BOTTOM BIT <<--
	.
	.
	.
	
	CRX__LIB__PUBLIC_C_FUNCTION() void myGlobal_doSomthing(void);
	CRX__LIB__PRIVATE_C_FUNCTION() void myGlobal_doSomthing2(void);

	.
	.
	.
	->> THE BOTTOM BIT DO NOT FORGET THIS <<--
	CRX__LIB__C_CODE_END()

	#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
		//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#endif
	#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
		#pragma pop_macro("CRX__LIB__MODE")
	#endif

".c.h": {C}
	//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
	//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
	//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
	//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
	//<<END>>

	CRX__LIB__C_CODE_BEGIN()
	->> DO NOT FORGET THE BOTTOM BIT <<--
	.
	.
	.

	// CRX__LIB__PUBLIC_C_FUNCTION() OR  CRX__LIB__PRIVATE_C_FUNCTION() MUST BE USED BEFORE EVERY GLOBAL 
	//		FUNCTION DEFINITION.
	// WARNING: CRX__LIB__PUBLIC_C_FUNCTION() FUNCTIONS ARE NOT ALLOWED TO HAVE STATIC LOCAL VARIABLES.
	CRX__LIB__PUBLIC_C_FUNCTION() void myGlobal_doSomthing(void)
	{
	}
	CRX__LIB__PRIVATE_C_FUNCTION() void myGlobal_doSomthing2(void)
	{
	}

	.
	.
	.
	->> THE BOTTOM BIT DO NOT FORGET THIS <<--
	CRX__LIB__C_CODE_END()

".c": {C}
	->> REMEMBER TO RENAME "myLibrary_stdafx.h" TO YOUR OWN CONFIGURATION FILE NAME. DO NOT INCLUDE A PATH. <<--
	#include "myLibrary_stdafx.h"
	->> SUGGESTED //... INCLUDE THIS FILE (crx.h), OR A FILE THAT INCLUDES THIS FILE ... <<--
	->> REMEMBER TO RENAME "MY_LIBRARY_NAME__MODE" TO YOUR OWN CONFIGURATION MACRO. <<--
	#if(!defined(MY_LIBRARY_NAME__MODE))
		#define MY_LIBRARY_NAME__MODE CRX__LIB__MODE__STAND_ALONE
	#elif(!CRXM__IS(MY_LIBRARY_NAME__MODE, CRX__LIB__MODE__STAND_ALONE) && \
			!CRXM__IS(MY_LIBRARY_NAME__MODE, CRX__LIB__MODE__DLL_STAND_ALONE))
		#undef MY_LIBRARY_NAME__MODE
		#define MY_LIBRARY_NAME__MODE CRX__LIB__MODE__STAND_ALONE
	#endif
	#if(!defined(CRX__LIB__C_MODE))
		#define CRX__LIB__C_MODE CRX__LIB__MODE__STAND_ALONE
	#elif(!CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__STAND_ALONE) && \
			!CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__DLL_STAND_ALONE))
		#undef CRX__LIB__C_MODE
		#define CRX__LIB__C_MODE CRX__LIB__MODE__STAND_ALONE
	#endif
	//<<START>>	INCLUDE CORRESPONDING ".c.h" FILE
	//<<END>>


CLIENT CODE:
	CLIENT CODE WISHING TO USE A C CRXed LIBRARY 
		- MUST INCLUDE ONLY ITS ".h" FILES
		- IF THE C COMPILER DOES NOT SUPPORT push_macro, MUST DEFINE CRX__LIB__C_MODE (SEE BELOW).
				THE CLIENT CODE WOULD BE FORCED TO USE ALL C CRXed UNDER THE SAME MODE. IF THE 
				CLIENT WANTS TO USE DIFFERNT C CRXed LIBRARIES DIFFERENTLY, THEN THE COMPILER WOULD 
				NEED TO PROVIDE #pragma push_macro() AND #pragma pop_macro()
				
				IF THE CLIENT CODE IS A C++ CRXed LIBRARY, THE CLIENT CODE DOES NOT NEED TO DEFINE
				CRX__LIB__C_MODE. UNDER A C++ COMPILER push_macro IS ASSUMED TO EXIST.
		- IF THE C COMPILER SUPPORTS push_macro, MUST DEFINE "MY_LIBRARY_NAME__MODE" (SEE BELOW).
		- MUST DEFINE EITHER CRX__LIB__C_MODE, OR MY_LIBRARY_NAME__MODE, DEPENDING ON 
				push_macro SUPPORT, AS
						CRX__LIB__MODE__HEADER_ONLY:		TO USE IT AS HEADER ONLY LIBRARY
						CRX__LIB__MODE__STAND_ALONE:		TO USE IT AS STATIC LIBRARY TO BE COMPILED
															BY HIMSELF. THIS IS USUALLY NOT SOMETHING
															THE CLIENT NEEDS TO DO BECAUSE THIS WOULD
															ALREADY BE SET BY THE CPP FILES OF THE LIBRARY
															ITSELF
						CRX__LIB__MODE__INTERFACE:			TO USE IT AS HEADERS FOR ALREADY COMPILED
															STATIC LIRBARY
						CRX__LIB__MODE__DLL_STAND_ALONE:	TO USE IT AS DYNAMIC LIBRARY TO BE COMPILED
															BY HIMSELF.
						CRX__LIB__MODE__DLL_INTERFACE:		TO USE IT AS HEADERS FOR ALREADY COMPILED
															DYNAMIC LIRBARY
				OR NOT DEFINE CRX__LIB__C_MODE, NOR "MY_LIBRARY_NAME__MODE", AND IT WOULD BE 
				EQUIVILANT TO DEFINING THEM AS CRX__LIB__MODE__STAND_ALONE. 
				REMEMBER THAT THE NAME "MY_LIBRARY_NAME__MODE" IS SPECIFIC TO EACH CRXed LIBRARY, 
				AND EACH CRXed LIBRARY HAS ONLY ONE NAME FOR "MY_LIBRARY_NAME__MODE".
		- FOR MAXIMUM COMPATIBILITY WITH COMPILERS CLIENT CODE SHOULD SIMPLY ASSUME push_macro IS
				NOT SUPPORTED, AND DEFINE BOTH CRX__LIB__C_MODE AND THE LIBRARY SPECIFIC
				"MY_LIBRARY_NAME__MODE" WITH APPROPRIATE VALUES

*/
/* LIB: Design notes
LOGIC:
	- LOGIC TABLE:
		-
										CLOSED		OPEN		ODR			NON ODR 	SETTINGS PASSED
										SOURCE		SOURCE		PARADIGM	PARADIGM	THROUGH CODE
					HEADER ONLY				N			Y			Y			Y			Y
					NOT HEADER ONLY			Y			Y			N			Y			Y*
					NOT HEADER ONLY			Y			N			N			Y			N
					(PRECOMPILED)
			
			*IN THIS CASE WE WOULD USE A SHARED HEADER CONVENTION ON WHICH CLIENT CODE COULD PASS ITS SETTINGS,
					WHICH IS SLIGHTLY RESTRICTIVE COMPARED TO THE HEADER ONLY CASE.
		- NON SUPPORTED SCENARIOS
			- THERE IS NO SUPPORT, WHEN HEADER ONLY, FOR THE LIBRARY TO ACT UNDER ODR PARADIGM.
			- THERE IS NO SUPPORT, WHEN NOT HEADER ONLY AND NOT PRECOPMILED, FOR THE LIBRARY TO BE CONFIGURABLE
					THROUGH CODE
	- THE INTRODUCTION OF THE NEW FILES, .c.h AND .cpp.h, IS MADE TO SUPPORT BOTH CASES OF OPEN SOURCE AND CLOSED
			SOURCE.
	- WHEN INCLUDING CRXed CODE FILES, THERE ARE THREE SITUATION TO CONSIDER, ALL TO BE THOUGHT OF FROM
			THE CLIENT CODE PERSPECTIVE:
		(1)- INCLUSION OF HEADER FILES (.h) EXPECTING THE ACTUAL LIBRARY WAS ALREADY COMPILED ELSEWHERE.
		(2)- INCLUSION OF HEADER FILES (.h) BECAUSE WE ARE USING THE LIBRARY AS A HEADER ONLY LIBRARY.
		(3)- INCLUSION OF HEADER FILES (.h) and (.cpp.h) FILES BECAUSE WE ARE THE ONES COMPILING THE LIBRARY.
	- C++
		- THE CLIENT CODE MUST DEFINE A LIBRARY SPECIFIC MACRO, NAMED IN THE TEMPLATE 
				"MY_LIBRARY_NAME__IS_HEADER_ONLY" TO INDICATE WHETHER THE LIBRARY IS USED AS HEADER ONLY OR NOT.
			- IN SCENARIO (1) ABOVE, THE CLIENT CODE SETS THE LIBRARY SPECIFIC MACRO,
					"MY_LIBRARY_NAME__IS_HEADER_ONLY", TO CRXM__FALSE. AND THE CLIENT CODE ONLY USES THE HEADER
					FILES (.h)
			- IN SCENARIO (2) ABOVE, THE CLIENT CODE SETS THE LIBRARY SPECIFIC MACRO,
					"MY_LIBRARY_NAME__IS_HEADER_ONLY", TO CRXM__TRUE. AND THE CLIENT CODE ONLY USES THE HEADER
					FILES (.h).
			- IN SCENARIO (3) ABOVE, THE CLIENT CODE IS THE CRXed LIBRARY ITSELF. IN PARTICULAR, IT IS THE
					SOURCE FILES (.cpp) OF THE CRXed LIBRARY. THESE FILES, DO NOT SPECIFY THAT THE LIBRARY IS
					TO BE HEADER ONLY, AND INCLUDE THE SOURCE HEADER FILES (.cpp.h) FILES.
	- IN C
		- WE CAN NOT ASSUME THAT A C COMPILER SUPPORTS THE "#pragma push_macro()" AND 
				"#pragma pop_macro()" MECHANISM. HOWEVER, WE STILL PROVIDE FULL FUNCTIONALITY IF THE COMPILER
				DOES SUPPORT THESE MACROS.
		- WHEN THE C COMPILER SUPPORTS THE AFORE MENTIONED MACROS, THE MACHANISM WORK THE SAME AS IN THE C++
				CODE, BUT INSTEAD OF (.cpp.h) FILES WE HAVE (.c.h) FILES.
		- IF THE COMPILER DOES NOT SUPPORT THE AFORE MENTIONED MACROS, INSTEAD OF A LIBRARY SPECIFIC MACRO
				LIKE "MY_LIBRARY_NAME__IS_HEADER_ONLY" TO INDICATE WHETHER THE LIBRARY IS HEADER ONLY, WE
				HAVE A UNIVERSAL MACRO, "CRX__LIB__IS_C_HEADER_ONLY" THAT CONTROLS ALL C LIBRARIES IN USE.
		- IT IS ASSUMED THAT IF THE CRXed C CODE IS NOT USED AS A HEADER ONLY LIBRARY FROM A CRXed C++ CODE, THE
				CODE IS TREATED AS C CODE, AND NOT C++ CODE.
	- IT WAS DECIDED TO INCLUDE THE CORRSPONDING (.h) FILES IN THE (.cpp.h) AND (.c.h) FILES FOR CLARITY
			ONLY AND NOT BECAUSE IT IS NEEDED. HOWEVER, THIS DID SIMPLIFY IN THE (.cpp) AND (.c) FILES WHERE
			IT WAS NO LONGER NEEDED TO INCLUDE CORRESPONDING HEADER (.h) FIRST IMMEDIATELY BEFORE INCLUDING
			THE CORRESPONDING (.cpp.h) OR (.c.h) FILE.
			NOTE, HOWEVER, THAT UNDER SCENARIO 1, THE .h FILES DO NOT INCLUDE THE CORRESPONDING 
			(.cpp.h) OR (.c.h) FILE. UNDER SCENARIO 2, THE .h FILE DOES INCLUDE THE CORRESPONDING 
			(.cpp.h) OR (.c.h) FILE. UNDER SCENARIO 3, THE .h FILE WOULD NOT KNOW WHAT TO DO BECAUSE
			WHETHER THE MACRO "MY_LIBRARY_NAME__IS_HEADER_ONLY" OR "CRX__LIB__IS_C_HEADER_ONLY" 
			THERE IS ONLY TWO STATES FOR DETECTION, WHILE THERE IS THREE POSSIBLE SCENARIOS. 
			INCLUDING THE CORRSPONDING (.h) FILES IN THE (.cpp.h) AND (.c.h) WHILE HAVING THOSE
			INCLUDED IN THE CORRSPONDING (.cpp) AND (.c) FILIES SOLVES THIS PROBLEM.
	- NOTE: A C++ COMPILER IS ALWAYS ASSUMED TO SUPPORT THE "#pragma push_macro()" AND 
			"#pragma pop_macro()" MECHANISM. IF SUCH A COMPILER CAN COMPILE C CODE AS C,
			THAT COMPILER IS ALSO ASSUMED TO SUPPORT THE SAID MECHANISM UNDER ITS C MODE.
*/


#define CRX__LIB__MODE__HEADER_ONLY 0
#define CRX__LIB__MODE__STAND_ALONE 1
#define CRX__LIB__MODE__INTERFACE 2
#define CRX__LIB__MODE__DLL_STAND_ALONE 3
#define CRX__LIB__MODE__DLL_INTERFACE 4

#ifndef CRX__LIB__IS_CPPH_INCLUDING
	#define CRX__LIB__IS_CPPH_INCLUDING 0
#endif
#ifndef CRX__LIB__MODE
	#define CRX__LIB__MODE CRX__LIB__MODE__STAND_ALONE
#endif

/*
REMEMBER, CRX__LIB__METHOD() IS TO MEANT TO BE USED ON THE DEFINITIONS ONLY.
*/
#define CRX__LIB__METHOD() CRXM__IFELSE2(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY), inline, )
//CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_CPPH()
//CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_H()
//CRX__LIB__PUBLIC_STATIC_VARS_START(pClassName)
//CRX__LIB__PUBLIC_STATIC_VARS_END()
//CRX__LIB__PROTECTED_STATIC_VARS_START(pClassName)
//CRX__LIB__PROTECTED_STATIC_VARS_END()
//CRX__LIB__PRIVATE_STATIC_VARS_START(pClassName)
//CRX__LIB__PRIVATE_STATIC_VARS_END()
//CRX__LIB__PUBLIC_STATIC_VAR()
//CRX__LIB__PROTECTED_STATIC_VAR()
//CRX__LIB__PRIVATE_STATIC_VAR()
#if(!defined(CRX__LIB__CONFIG__FAVOR_STATIC_INLINE) || !defined(CRX__LIB__STATIC_INLINE_DATA_MEMBERS_ARE_SUPPORTED))
	#define CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, pAccess, pTypeDef) \
		CRXM__IFELSE(CRXM__NOT(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))) \
		( \
			typedef pClassName pTypeDef; \
		) \
		( \
			pAccess: template<int L> \
			class Crx__ ## pAccess ## Statics \
			{ \
		)
	//#END_DEFINE
	#define CRX__LIB__PRIVATE__STATIC_VARS_END(pParenthesizedClassName, pAccess, pTypeDef) \
		CRXM__IFELSE(CRXM__NOT(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))) \
		( \
		) \
		( \
			}; \
			typedef Crx__ ## pAccess ## Statics <0> pTypeDef; \
		)
	//#END_DEFINE
	#define CRX__LIB__PUBLIC_STATIC_VARS_START(pClassName) \
			CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, public, StaticPublicVars)
	#define CRX__LIB__PUBLIC_STATIC_VARS_END() CRX__LIB__PRIVATE__STATIC_VARS_END(, public, StaticPublicVars)
	#define CRX__LIB__PROTECTED_STATIC_VARS_START(pClassName) \
			CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, protected, StaticProtectedVars)
	#define CRX__LIB__PROTECTED_STATIC_VARS_END() CRX__LIB__PRIVATE__STATIC_VARS_END(, protected, StaticProtectedVars)
	#define CRX__LIB__PRIVATE_STATIC_VARS_START(pClassName) \
			CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, private, StaticPrivateVars)
	#define CRX__LIB__PRIVATE_STATIC_VARS_END() CRX__LIB__PRIVATE__STATIC_VARS_END(, private, StaticPrivateVars)

	#define CRX__LIB__PUBLIC_STATIC_VAR() public: static
	#define CRX__LIB__PROTECTED_STATIC_VAR() public: static
	//NOTE: USING private INSTEAD OF public WORKS IN VISUAL STUDIO 2017 FOR SOME REASON.
	#define CRX__LIB__PRIVATE_STATIC_VAR() public: static

	#define CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_CPPH() 1
	#define CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_H() 0
#else
	#define CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, pAccess, pTypeDef) \
			typedef pClassName pTypeDef;
	#define CRX__LIB__PRIVATE__STATIC_VARS_END(pClassName, pAccess, pTypeDef)


	#define CRX__LIB__PUBLIC_STATIC_VARS_START(pClassName) \
			CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, , StaticPublicVars)
	#define CRX__LIB__PUBLIC_STATIC_VARS_END()
	#define CRX__LIB__PROTECTED_STATIC_VARS_START(pClassName) \
			CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, , StaticProtectedVars)
	#define CRX__LIB__PROTECTED_STATIC_VARS_END()
	#define CRX__LIB__PRIVATE_STATIC_VARS_START(pClassName) \
			CRX__LIB__PRIVATE__STATIC_VARS_START(pClassName, , StaticPrivateVars)
	#define CRX__LIB__PRIVATE_STATIC_VARS_END

	#define CRX__LIB__PUBLIC_STATIC_VAR() CRXM__IFELSE2( \
			CRXM__NOT(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY)), \
			public: static, public: static inline)
	#define CRX__LIB__PROTECTED_STATIC_VAR() CRXM__IFELSE2( \
			CRXM__NOT(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY)), \
			protected: static, protected: static inline)
	#define CRX__LIB__PRIVATE_STATIC_VAR() CRXM__IFELSE2( \
			CRXM__NOT(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY)), \
			private: static, private: static inline)

	#define CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_CPPH() \
			CRXM__IFELSE2(CRXM__NOT(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY)), 1, 0)
	#define CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_H() \
			CRXM__IFELSE2(CRXM__NOT(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY)), 0, 1)
#endif

#define CRX__LIB__PRIVATE_FUNCTION() static
/*
THE FOLLOWING ASSUMES THAT GLOBAL FUNCTIONS ARE AUTOMATICALLY extern.
*/
#define CRX__LIB__PUBLIC_FUNCTION() CRXM__IFELSE2( \
		CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY), inline, )

#define CRX__LIB__PRIVATE_CONSTANT(pIS_DEFINITION) \
		CRXM__IFELSE2(CRXM__NOT(pIS_DEFINITION), extern, )
#define CRX__LIB__PUBLIC_CONSTANT(pIS_DEFINITION) CRXM__IFELSE2( \
		CRXM__NOT(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY)), extern, \
		CRXM__IFELSE2(CRXM__NOT(pIS_DEFINITION), extern, ))


/*
- WARNING ABOUT CRX__LIB__PRIVATE_C_CONSTANT() AND CRX__LIB__PUBLIC_C_CONSTANT().
	- REMEMBER THE VISIBILITY HERE IS COMPILATION UNIT VISIBILITY AS DEFINED IN MY STANDARD IF
			CODE IS USED UNDER THE NON ODR PARADIGN, MEANING AS A HEADER ONLY LIBRARY IN THE 
			CRX/LIB ARCHITECTURE, THERE CAN BE MANY OF THE SAME CONSTANT IN FINAL COMPILED
			CODE, ONE IN EACH TRANSLATION UNIT USING THE HEADERS. THESE CONSTANTS ARE
			NOT GUARANTEED TO BE EQUAL. THEREFORE, WHATEVER YOU ASSIGN TO THEM MAKE SURE
			THAT YOU KNOW THE VALUE OF IT AT COMPILER TIME, NOT RUN TIME. FOR EXAMPLE,
			A CONSTANT POINTER RETURNED BY malloc WOULD NOT WORK, BECAUSE EACH PERTAINING
			COMPILATION UNIT WILL HAVE A DIFFERENT POINTER.
	- REMEMBER THAT YOU STILL NEED TO USE THE KEYWORD const WHEN USING THESE MACROS.
- ABOUT CRX__LIB__PRIVATE_C_CONSTANT() AND CRX__LIB__PUBLIC_C_CONSTANT().
	- NOTE THAT IN C++ WE CAN NOT FARWARD DECLARE USING static.
					"It is only possible in C++ to forward declare an object if you use the 
					extern keyword and do not specify an initializer."
			WHILE IN C WE COULD WRITE
					//DECLERATION
					static int gInts[3];		//IN C THIS IS CALLED A TENTATIVE DECLERATION
					//DEFINITION
					static int gInts[3] = {1, 10, 276};
			IN C++ WE HAVE TO WRITE
					//DECLERATION
					namespace{extern int gInts[3];}
					//DEFINITION
					namespace{int bigIntArray[3] = {1, 10, 276};}
			THIS IS OFCOURSE PROBLOMATIC BECAUSE OF THE NEED TO ADD THE END BRACES. 

- NOTE THAT THE FOLLOWING CAN NOT BE USED WITH inline TO INLINE FUNCTIONS. CURRENTLY
		INLINE FUNCTIONS SHOULD NOT BE USED AT ALL. LEAVE IT TO THE COMPILER TO
		DECIDE INLINING. IN THEORY, UNDER
				- C (GNU89): 
					- HEADER ONLY LIBRARY:
						- static FOR PRIVATE FUNCTIONS
						- static FOR PUBLIC FUNCTIONS
					- NOT HEADER ONLY:
						- static FOR PRIVATE FUNCTIONS
						- NOTHING FOR PUBLIC FUNCTIONS 	(RELYING ON DEFAULT extern FOR FUNCTIONS
								IN THIS CASE)
				- C (C99):
					- HEADER ONLY LIBRARY:
						- static FOR PRIVATE FUNCTIONS
						- static FOR PUBLIC FUNCTIONS
					- NOT HEADER ONLY:
						- static FOR PRIVATE FUNCTIONS
						- extern FOR PUBLIC FUNCTIONS
				- C++:
					- HEADER ONLY LIBRARY:
						- static FOR PRIVATE FUNCTIONS
						- static FOR PUBLIC FUNCTIONS
					- NOT HEADER ONLY:
						- static FOR PRIVATE FUNCTIONS
						- extern FOR PUBLIC FUNCTIONS
		AND WITH CRX__LIB__PRIVATE_C_FUNCTION() AND CRX__LIB__PUBLIC_C_FUNCTION()
		DEFINED USING THE ABOVE ONE COULD COMBINE THEM WITH inline. HOWEVER, THERE
		ARE SEVERAL PROBLEMS:
				- static inline IS NOT REALY PART OF C++ EVEN IF COMPILERS TEND TO SUPPORT IT.
				- extern inline IS NOT REALY PART OF C++ EVEN IF COMPILERS TEND TO SUPPORT IT.
				- C89 DOES NOT SUPPORT inline BUT THAT CAN BE SUPPORTED BY NOT USING inline AT
						ALL IN THAT CASE. TRYING TO USE COMPILER SPECIFIC EXTENSIONS, SUCH AS
						__inline IS NOT A GOOD IDEA BECAUSE ONE HAS TO INVESTIGATE THOSE 
						EXTENSION'S BEHAVIOR WHEN COMBINED WITH static AND extern.
				- WHETHER WITH THE ABOVE A FUNCTION'S ADDRESS CAN BE TAKEN OR NOT MIGHT NOT
						BE CONSISTANT. HOWEVER, AS FAR AS I CAN TELL, WITH THE ABOVE,
						ALL FUNCTIONS ALLOW THE ADDRESS TO BE TAKEN
*/
//CRX__LIB__IS_TO_INCLUDE_IN_C_H()
//CRX__LIB__IS_TO_INCLUDE_IN_C_CH()
//CRX__LIB__PUBLIC_C_FUNCTION()
//CRX__LIB__PRIVATE_C_FUNCTION()
//CRX__LIB__PUBLIC_INLINE_C_FUNCTION()
//CRX__LIB__PRIVATE_INLINE_C_FUNCTION()
//CRX__LIB__PRIVATE_C_CONSTANT()
//CRX__LIB__PUBLIC_C_CONSTANT()
#if(defined(__cplusplus) || CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#define CRX__LIB__PRIVATE_C_FUNCTION() \
			CRXM__SWITCH(5) \
			( \
				(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY), ) \
				(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__STAND_ALONE), ) \
				(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__INTERFACE), ) \
				(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__DLL_STAND_ALONE), \
					CRX_DLL_NO_EXPORT_C_FUNCTION \
				) \
				(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__DLL_INTERFACE), \
					CRX_DLL_NO_EXPORT_C_FUNCTION \
				) \
			) static
	#define CRX__LIB__PUBLIC_C_FUNCTION() \
			CRXM__SWITCH(5) \
			( \
				(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY), \
					static \
				) \
				(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__STAND_ALONE), \
					extern \
				) \
				(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__INTERFACE), \
					extern \
				) \
				(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__DLL_STAND_ALONE), \
					CRX_DLL_EXPORT_C_FUNCTION extern \
				) \
				(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__DLL_INTERFACE), \
					CRX_DLL_IMPORT_C_FUNCTION extern \
				) \
			)


	//START: INLINE SUPPORT
	//WARNING: THE FOLLOWING IS EXPERIMENTAL, AND LIKELY ILL DEFINED. NOTICE
	//		THE DIFFERENT BEHAVIOR OF C++ VS C FOR EXAMPLE. THINK OF THE SITUATION
	//		WHEN THE CODE IS COMPILED AS C, MEANING NOT HEADER ONLY SITUATION, 
	//		BUT THEN THE C HEADER IS USED IN C++ TO USE IT. ALSO REMEMBER THAT
	//		C CODE WILL BE WRAPPED IN extern C IN C++.

	/*
		IN TIME, THE FOLLOWING NEEDS TO SUPPORT OTHER C++ COMPILERS THAT HAVE 
			THE EXTENSION static inline. AS FOR extern inline, C++ inline
			SHOULD BE WHAT extern online MEANS IN GNU89. REMEMBER:
					CRX__LIB__PRIVATE__STATIC_INLINE: FUNCTION IS INLINE, AS DEFINED IN C++,
							BUT NOT AVAILABLE TO OTHER COMPILATION UNITS. FUNCTION ADDRESS
							CAN BE TAKEN.
					CRX__LIB__PRIVATE__EXTERN_INLINE: FUNCTION IS INLINE, AS DEFINED IN C++,
							AND AVAILABLE TO OTHER COMPILATION UNITS. (SHOULD ALREADY BE
							THE CASE IN C++). FUNCTION ADDRESS CAN BE TAKEN.
							NOTICE HOW THIS IS ONLY USED IF THE LIBRARY IS NOT HEADER ONLY,
							MEANING THE CODE IS COMPILED IN C, IN WHICH IT WOULD HAVE BEEN
							DEFINED USING C'S extern inline (C99 DEFINITION), HENCE WHY
							THE MACRO EXALUATES TO extern, AND NOT extern __inline FOR
							EXAMPLE, EVEN THOUGH MSVC SUPPORTS IT.
	*/
	#if(defined(_MSC_VER))
		#define CRX__LIB__PRIVATE__STATIC_INLINE static __inline
		#define CRX__LIB__PRIVATE__EXTERN_INLINE extern
	#else
		#define CRX__LIB__PRIVATE__STATIC_INLINE static
		#define CRX__LIB__PRIVATE__EXTERN_INLINE extern
	#endif

	/*
		NOTE THAT IN THE DLL CASE, IN THE C++ CASE, YOU HAVE TO CONSIDER THE CASE 
		WHERE C++ CODE IS CALLING C CODE FROM THE SAME LIBRARY, WHILE UNDER MODE 
		CRX__LIB__MODE__DLL_STAND_ALONE, AND THE CASE WHERE C++ CODE IS CALLING
		C CODE FROM A DIFFERENT LIBRARY THAT WAS COMPILED WITH MODE 
		CRX__LIB__MODE__DLL_STAND_ALONE, AND THE C++ CODE IS NOW USING IT UNDER
		MODE CRX__LIB__MODE__DLL_INTERFACE.
	*/
	#if(defined(__cplusplus))
		#define CRX__LIB__PRIVATE_INLINE_C_FUNCTION() \
				CRXM__SWITCH(5) \
				( \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY), ) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__STAND_ALONE), ) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__INTERFACE), ) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__DLL_STAND_ALONE), \
						CRX_DLL_NO_EXPORT_C_FUNCTION \
					) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__DLL_INTERFACE), \
						CRX_DLL_NO_EXPORT_C_FUNCTION \
					) \
				) CRX__LIB__PRIVATE__STATIC_INLINE
		#define CRX__LIB__PUBLIC_INLINE_C_FUNCTION() \
				CRXM__SWITCH(5) \
				( \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY), \
						CRX__LIB__PRIVATE__STATIC_INLINE \
					) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__STAND_ALONE), \
						CRX__LIB__PRIVATE__EXTERN_INLINE \
					) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__INTERFACE), \
						CRX__LIB__PRIVATE__EXTERN_INLINE \
					) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__DLL_STAND_ALONE), \
						CRX_DLL_EXPORT_C_FUNCTION CRX__LIB__PRIVATE__EXTERN_INLINE \
					) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__DLL_INTERFACE), \
						CRX_DLL_IMPORT_C_FUNCTION CRX__LIB__PRIVATE__EXTERN_INLINE \
					) \
				)
	#else
		#define CRX__LIB__PRIVATE_INLINE_C_FUNCTION() \
				CRXM__SWITCH(5) \
				( \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY), ) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__STAND_ALONE), ) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__INTERFACE), ) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__DLL_STAND_ALONE), \
						CRX_DLL_NO_EXPORT_C_FUNCTION \
					) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__DLL_INTERFACE), \
						CRX_DLL_NO_EXPORT_C_FUNCTION \
					) \
				) CRX__C__PRIVATE_INLINE_FUNCTION
		#define CRX__LIB__PUBLIC_INLINE_C_FUNCTION() \
				CRXM__SWITCH(5) \
				( \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY), \
						CRX__C__PRIVATE_INLINE_FUNCTION \
					) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__STAND_ALONE), \
						CRX__C__EXTERN_INLINE_FUNCTION \
					) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__INTERFACE), \
						CRX__C__EXTERN_INLINE_FUNCTION \
					) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__DLL_STAND_ALONE), \
						CRX_DLL_EXPORT_C_FUNCTION CRX__C__EXTERN_INLINE_FUNCTION \
					) \
					(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__DLL_INTERFACE), \
						CRX_DLL_IMPORT_C_FUNCTION CRX__C__EXTERN_INLINE_FUNCTION \
					) \
				)
	#endif
	//END: INLINE SUPPORT


	//WARNING: READ THE WARNING ABOVE BEFORE USING THESE TWO.
	//USE OF THESE IS DISCOURAGED BECAUSE OF LACK OF CODE SYMMETRY AND THE USE OF extern WHEN NOT
	//		REQUIRED AND ANY SIDE EFFECT IT MIGHT HAVE WHICH LACKS PROOF CURRENTLY THAT IT WOULD
	//		HAVE NO EFFECT REGARDLESS OF THE COMPILER.
	//		FAVORS static VARIABLES IN FUNCTIONS INSTEAD.
	#if(defined(__cplusplus))
		#define CRX__LIB__PRIVATE_C_CONSTANT(pIS_DEFINITION) \
				CRXM__IFELSE2(pIS_DEFINITION, static, extern)
		#define CRX__LIB__PUBLIC_C_CONSTANT(pIS_DEFINITION) CRXM__IFELSE2( \
				CRXM__NOT(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY)), extern, \
				CRXM__IFELSE2(pIS_DEFINITION, static, extern))
	#else
		#define CRX__LIB__PRIVATE_C_CONSTANT(pIS_DEFINITION) static
		#define CRX__LIB__PUBLIC_C_CONSTANT(pIS_DEFINITION) CRXM__IFELSE2( \
				CRXM__NOT(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY)), extern, static)
	#endif
#else
	#ifndef CRX__LIB__C_MODE
		#define CRX__LIB__C_MODE CRX__LIB__MODE__STAND_ALONE
	#endif

	#define CRX__LIB__PRIVATE_C_FUNCTION() \
			CRXM__SWITCH(5) \
			( \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__HEADER_ONLY), ) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__STAND_ALONE), ) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__INTERFACE), ) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__DLL_STAND_ALONE), \
					CRX_DLL_NO_EXPORT_C_FUNCTION \
				) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__DLL_INTERFACE), \
					CRX_DLL_NO_EXPORT_C_FUNCTION \
				) \
			) static
	#define CRX__LIB__PUBLIC_C_FUNCTION() \
			CRXM__SWITCH(5) \
			( \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__HEADER_ONLY), \
					static \
				) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__STAND_ALONE), \
					extern \
				) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__INTERFACE), \
					extern \
				) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__DLL_STAND_ALONE), \
					CRX_DLL_EXPORT_C_FUNCTION extern \
				) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__DLL_INTERFACE), \
					CRX_DLL_IMPORT_C_FUNCTION extern \
				) \
			)


	//START: INLINE SUPPORT
	//WARNING: THE FOLLOWING IS EXPERIMENTAL, AND LIKELY ILL DEFINED. NOTICE
	//		THE DIFFERENT BEHAVIOR OF C++ VS C FOR EXAMPLE. (SEE ABOVE)
	#define CRX__LIB__PRIVATE_INLINE_C_FUNCTION() \
			CRXM__SWITCH(5) \
			( \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__HEADER_ONLY), ) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__STAND_ALONE), ) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__INTERFACE), ) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__DLL_STAND_ALONE), \
					CRX_DLL_NO_EXPORT_C_FUNCTION \
				) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__DLL_INTERFACE), \
					CRX_DLL_NO_EXPORT_C_FUNCTION \
				) \
			) CRX__C__PRIVATE_INLINE_FUNCTION
	#define CRX__LIB__PUBLIC_INLINE_C_FUNCTION() \
			CRXM__SWITCH(5) \
			( \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__HEADER_ONLY), \
					CRX__C__PRIVATE_INLINE_FUNCTION \
				) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__STAND_ALONE), \
					CRX__C__EXTERN_INLINE_FUNCTION \
				) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__INTERFACE), \
					CRX__C__EXTERN_INLINE_FUNCTION \
				) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__DLL_STAND_ALONE), \
					CRX_DLL_EXPORT_C_FUNCTION CRX__C__EXTERN_INLINE_FUNCTION \
				) \
				(CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__DLL_INTERFACE), \
					CRX_DLL_IMPORT_C_FUNCTION CRX__C__EXTERN_INLINE_FUNCTION \
				) \
			)
	//END: INLINE SUPPORT


	//WARNING: READ THE WARNING ABOVE BEFORE USING THESE TWO.
	//USE OF THESE IS DISCOURAGED BECAUSE OF LACK OF CODE SYMMETRY AND THE USE OF extern WHEN NOT
	//		REQUIRED AND ANY SIDE EFFECT IT MIGHT HAVE WHICH LACKS PROOF CURRENTLY THAT IT WOULD
	//		HAVE NO EFFECT REGARDLESS OF THE COMPILER.
	//		FAVORS static VARIABLES IN FUNCTIONS INSTEAD.
	#define CRX__LIB__PRIVATE_C_CONSTANT(pIS_DEFINITION) static
	#define CRX__LIB__PUBLIC_C_CONSTANT(pIS_DEFINITION) CRXM__IFELSE2( \
			CRXM__IS(CRX__LIB__C_MODE, CRX__LIB__MODE__HEADER_ONLY), static, extern)
#endif

//CRX__LIB__C_CODE_BEGIN()
//CRX__LIB__C_CODE_END()
#if(defined(__cplusplus))
	#define CRX__LIB__C_CODE_BEGIN() CRXM__IFELSE2( \
			CRXM__NOT(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY)), extern "C" {, )
	#define CRX__LIB__C_CODE_END() CRXM__IFELSE2( \
			CRXM__NOT(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY)), }, )

	#define CRX__LIB__EXTERN_C CRXM__IFELSE2( \
			CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY), extern "C", )
#else
	#define CRX__LIB__C_CODE_BEGIN()
	#define CRX__LIB__C_CODE_END()

	#define CRX__LIB__EXTERN_C
#endif
		#endif
		#pragma endregion //}
	#pragma endregion //}

	#pragma region CRX__LAN //{
#if(defined(__cplusplus))
	#define CRX__LAN__CPP
#else
	/*
		NOTES:
			- THE FOLLOWING GIVES SUPPORT FOR CLIENTS SUCH AS IT ASSUMES FARWARD COMPATIBILITY OF FEATURES.
					OTHERWISE, IN C/C++ THE BEST WAY TO DETECT FEATURES IS ONE BY ONE, AND NOT BY RELYING ON 
					THE C/C++ VERSIONS ONLY. IN OTHER WORDS YOU WOULD NEED TO DETECT THINGS LIKE COMPILERS AND
					COMPILER VERSIONS TO BE ACCURATE.
	*/
	#ifdef __STDC__
		#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) ||/*continue..
			...on the next line */ (defined(__GNUC__) && !defined(__STRICT_ANSI__))
			#define CRX__LAN__C
			/*NOTE: THE DEFINE OF CRX__LAN__C_89 WAS ADDED LATER IN THIS IF BRANCH*/
			#define CRX__LAN__C_89
			#define CRX__LAN__C_99
			
			#if __STDC_VERSION__ >= 201112L
				#define CRX__LAN__C_2011
			#endif
		#else
			#define CRX__LAN__C

			#if defined(__STDC_VERSION__)
				#if(__STDC_VERSION__ >= 198900L)
					#define CRX__LAN__C_89
				#endif
				#if(__STDC_VERSION__ >= 199000L)
					#define CRX__LAN__C_90
				#endif
				#if(__STDC_VERSION__ >= 199901L)
					#define CRX__LAN__C_99
				#endif
			#else			
				#define CRX__LAN__C_89
				#define CRX__LAN__C_90
			#endif
		#endif
	#else
		#define CRX__LAN__C
		#define CRX__LAN__C_OLD
	#endif
#endif

/*if (sizeof('c') != sizeof(int)) printf("C++ compiler\n");
//else if ((unsigned char)1 < -1)	printf("Pre-ANSI (K&R) C compiler\n");
//else {
//	int i;	i = 1 //* * /
//		+ 1;
//	if (i == 2) printf("ANSI X3.159-1999 / ISO 9899:1999 (C99) compiler\n");
//	else printf("ANSI X3.159-1989 (C89) / ISO/IEC 9899:1990 (C90) C compiler\n");
//}*/
	#pragma endregion //}

#if(defined(CRX__LAN__CPP))
	#if(defined(_MSC_VER) && (_MSC_VER <= 1600))
		#define CRX__INITIALIZATION_POD_ZERO _CRX_ERROR_NOT_SUPPORT

		#define CRX__SET_TO_ZERO(pPOD_STRUCTURE_TYPE, pVARIABLE) memset(& ## (pVARIABLE), 0, sizeof(pPOD_STRUCTURE_TYPE))
	#else
		#define CRX__INITIALIZATION_POD_ZERO {}

		#define CRX__SET_TO_ZERO(pPOD_STRUCTURE_TYPE, pVARIABLE) pVARIABLE = {}
	#endif
#else
	#define CRX__INITIALIZATION_POD_ZERO {0}

	#if(defined(CRX__LAN__C_99))
		#define CRX__SET_TO_ZERO(pPOD_STRUCTURE_TYPE, pVARIABLE) pVARIABLE = (const pPOD_STRUCTURE_TYPE){0}
	#elif(defined(CRX__LAN__C_89))
		#define CRX__SET_TO_ZERO(pPOD_STRUCTURE_TYPE, pVARIABLE) memset(& ## pVARIABLE, 0, sizeof(pPOD_STRUCTURE_TYPE))
	#else
		#define CRX__SET_TO_ZERO(pPOD_STRUCTURE_TYPE, pVARIABLE) memset(& ## pVARIABLE, 0, sizeof(pPOD_STRUCTURE_TYPE))
	#endif
#endif

/*
	I WAS UNABLE IN THE END TO GET A GUARANTEE FOR NEITHER (>= C89) NOR (>= C++98) THAT TWO POINTERS COMPARING
	UNEQUAL DO NOT POINT TO THE SAME OBJECT. THE FOLLOWING IS MEANT TO BE OVERRIDEN ON ARCHITECTURES, SUCH
	AS THE 8086, WHEN MORE WORK NEEDS TO BE DONE TO NORMALIZE THE POITNERS BEFORE COMPARING THEM.
	THE CRX__ARE_POINTERS_TO_SAME_OBJECT MACRO MUST GUARANTEE THAT IF TWO POINTERS POINT TO THE SAME OBJECT THE 
	MACRO RETURNS TRUE. IF FOR WHATEVER REASON THE MACRO CAN NOT GUARANTEE IT FOR A GIVEN ARCHITECTURE, 
	MEANING CRX__ARE_ONLY_POINTERS_TO_SAME_OBJECT_EQUAL_AND_ALWAYS IS SET TO CRXM__FALSE, IT MUST OUTPUT pDEFAULT.
*/
#define CRX__ARE_ONLY_POINTERS_TO_SAME_OBJECT_EQUAL_AND_ALWAYS CRXM__TRUE
#define CRX__ARE_POINTERS_TO_SAME_OBJECT(pPOINTER1, pPOINTER2, pDEFAULT) \
	(pPOINTER1 == pPOINTER2)

#define CRX_ARE_VARIADIC_MACROS_EMULATED CRXM__FALSE

#pragma endregion //}

/*
Defne offsetof if not defined using
				#define offsetof(st, m) ((size_t)&(((st *)0)->m))
		or to account for NULL not necessarily being zero,
				#define offsetof(st, m) ((size_t)((char *)&((st *)0)->m - (char *)0))
		or if a special compiler thing exists, such as __builtin_offsetof(st, m), using instead.


Define alignof for 'C' if not defined using
				#define ALIGNOF(type) offsetof (struct { char c; type member; }, member)
		and for 'C++' using
				template<typename T> struct alignment_trick { char c; T member; };
				#define ALIGNOF(type) offsetof (alignment_trick<type>, member)
		but this will not work with non POD types because offsetof does not work with non POD types.
		One could use the following:
				    template <typename T>
					struct alignof2
					{
						enum { s = sizeof (T), value = s ^ (s & (s - 1)) };
					};
		which can give minimal aligment in certain cases, and would seem to give higher unnecessary
		aligment in other cases.
		One could also use the fact that the size of the following:
					struct S1 { T x; char c1; };
					struct S2 { T x; char c1; char c2; };
					.
					.
					struct SN { T x; char c1; char c2; char c3; ... char cN; };
		will sooner or later have a sizeof bigger than sizeof(T). When that happens the number of 
		extra chars in the structure should equal the aligment, but could end up being a multiple of
		that aligment in the worst case. An implementation would be
					template <typename T> struct alignof;

					template <typename T, int size_diff>
					struct helper
					{
					  enum { value = size_diff };
					};

					template <typename T>
					struct helper<T, 0>
					{
					  enum { value = alignof3<T>::value };
					};

					template <typename T>
					struct alignof3
					{
					  struct Big { T x; char c; };

					  enum { diff = sizeof (Big) - sizeof (T),
							 value = helper<Big, diff>::value };
					};
		or for old compilers that do not support partial speciailization
					 template <typename T> struct alignof;

					template <int size_diff>
					struct helper
					{
					  template <typename T> struct Val { enum { value = size_diff }; };
					};

					template <>
					struct helper<0>
					{
					  template <typename T> struct Val { enum { value = alignof<T>::value }; };
					};

					template <typename T>
					struct alignof
					{
					  struct Big { T x; char c; };

					  enum { diff = sizeof (Big) - sizeof (T),
						 value = helper<diff>::template Val<Big>::value };
					};
		but I am not sure if this works in VC6.
		Or one could combine the last 2 implementation for the optimal aligment arriving to
				    template <typename T>
					struct alignof
					{
					  enum { x = alignof2<T>::value,
						 y = alignof3<T>::value,
						 value = x < y ? x : y };
					};
					#define ALIGNOF(type) alignof<type>::value
		Note that this would not be an alternative to "alignas" in (>= C++11). The above would
		give us the tool to align ourselves, but "alignas" would do the aligment itself, not calculate
		aligment.
		Instead this would be an alternative to the official macro "alignof" (>= C++11) if it does not exist.
		Also remember to check if compiler specific alignof operators exist such as "__alignof"
		
Perhaps we can take advantage of the following, to reserver byte array that is aligned for a type T.
					union
					{
						char buff[sizeof(T)];
						uint64_t dummy;	//here we use a type that has the aligment of T
					};
		In gcc __attribute__ ((aligned (N))) is available since atleast 2.95.3, if not before.
		But remember also that (>= C++11) provides "std::aligned_storage". There is also
		boost::aligned_storage from boost.
		And one could use
					const int align = 32;
					void *p =_alloca(n + align - 1);
					__m256d *pm = (__m256d *)((((intptr_t)p + align - 1) / align) * align); //or (__m256d *)(((UINT_PTR)p + (align - 1)) & ~(align - 1))
		rewritten as
					const int align = 32;
					unsigned char p[sizeof(T) + align - 1];
					T * pm = (T *)((((intptr_t)p + align - 1) / align) * align);
*/
/*
//pAlignment MUST BE 2^N
crx_malloc(size_t pSize, size_t pAlignment)
{
	//NOTE IT MIGHT BE BETTER NOT TO HAVE CHECKS FOR COMPATIBILITY WITH aligned_alloc AND
	//		posix_memalign, BECAUSE CERTAIN HARDWARE MIGHT HAVE OTHER ALIGMENT RULES. BUT
	//		KEEPING THE CHECKS FOR NOW (CHECKS 2 AND 3)
	assert((pSize > 0) && (pAlignment < 266) && 
			((pAlignment == 0) || ((pAlignment & (pAlignment - 1)) == 0))); ALSO FOR COMPATIBILITY WITH aligned_alloc(>= C11) AND posix_memalign
	assert((pSize % pAlignment) == 0); //FOR COMPATIBILITY WITH aligned_alloc(>= C11) AND posix_memalign
	assert((sizeof(void *) % pAlignment) == 0); //FOR COMPATIBILITY WITH posix_memalign

#if(defined(CRX__LAN__C_2011))
	return aligned_alloc(pAlignment, pSize);
#elif(defined(_MSC_VER))
	return _aligned_malloc(pSize, pAlignment);
#elif(defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200112L))
	void * vPointer 

	if(posix_memalign(&vPointer, pAlignment, pSize))
		{vPointer = NULL;}
	
	return vPointer;
#else
	void * vPointer = malloc(pSize + pAlignment);
	void * vReturn = NULL;
	
	if(vPointer != NULL)
    {
		vReturn = (void *)((((uintptr_t) vPointer) + pAlignment - 1) & (~(uintptr_t)(pAlignment - 1)));

		if(vReturn == vPointer)
			{vReturn = ((void *)(((unsigned char *)(vReturn)) + pAlignment));}

		(((unsigned char *)(vReturn)) - 1)* = ((unsigned char)(vReturn + vPointer));
		
		return vReturn;
	}

	return vReturn;
#endif
}
crx_free(void * pPointer)
{	
#if(defined(CRX__LAN__C_2011))
	free(pPointer);
#elif(defined(_MSC_VER))
	_aligned_free(pPointer);
#elif(defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200112L))
	free(vPointer);
#else
	if(pPointer != NULL)
		{free((void *)(((unsigned char *)pPointer) - *(((unsigned char *)(pPointer)) - 1)));}
#endif
}
crx_realloc(void * pPointer, size_t pSize, size_t pAlignment)
{	
	//CONDITIONS ARE VERBATIM FROM crx_malloc
	assert((pSize > 0) && (pAlignment < 266) && 
			((pAlignment == 0) || ((pAlignment & (pAlignment - 1)) == 0)));
	assert((pSize % pAlignment) == 0);
	assert((sizeof(void *) % pAlignment) == 0);
	
	if((pSize == 0) && (pPointer != NULL))
		{return NULL;}

#if(defined(CRX__LAN__C_2011))
	return NULL; //THERE IS SIMPLY NO SUPPORT
#elif(defined(_MSC_VER))
	_aligned_realloc(pPointer, pSize, pAlignment);
#elif(defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200112L))
	return NULL; //THERE IS SIMPLY NO SUPPORT
#else
	return NULL; //CAN NOT GIVE SUPPORT WITHOUT KEEPING TRACK OF THE ORIGINAL SIZE
#endif
}

//ALTERNATIVE IMPLEMENTATION. LIKELY FASTER, BUT USES MORE MEMORY. ALSO, LIKE MINE, CAN NOT HAVE REALLOC
//		SUPPORT.
void *aligned_malloc(int size)
{
    void *mem = malloc(size+ALIGN+sizeof(void*));
    void **ptr = (void**)((uintptr_t)(mem+ALIGN+sizeof(void*)) & ~(ALIGN-1));
    ptr[-1] = mem;
    return ptr;
}
void aligned_free(void *ptr)
	{free(((void**)ptr)[-1]);}
*/
/*
ALIGN MEMBER
__attribute_ ((aligned (4)))	GCC	(C89 AND UP, C++, HAS TO BE DEFINED AT THE END AFTER THE VARIABLE NAME RATHER THAN BEFORE!)
__declspec(align(32))			MICROSOFT (C, C++, VISUAL STUDIO 6 AND UP)
alignas							(C++11 KEYWORD, C11 APPEARS TO BE ALIAS OF _Alignas THEN LATER BECAME KEYWORD)
_Alignas						(C SINCE C11)


Align structure
__attribute_ ((aligned (4)))	GCC	(C89 AND UP, C++)
__declspec(align(32))			MICROSOFT (C, C++, VISUAL STUDIO 6 AND UP)
alignas							(C++11, C11 APPEARS TO BE ALIAS OF _Alignas)
_Alignas						(C SINCE C11)


EXAMPLES:
	struct
	{
		.
		CRX__MEMBER_ALIGNMENT__START(16) int x CRX__MEMBER_ALIGNMENT__END(16);
		.
		CRX__MEMBER_ALIGNMENT2(16,
		int x2);
	}
	
	typedef CRX__ALIGNMENT__START(16) struct myStructure
	{
		.
	} CRX__ALIGNMENT__END(16) myStructure

	CRX__ALIGNMENT2(16, typedef,
	struct myStructure
	{
		.
	})  myStructure
	
PROBLEMS:
	- SYNTAX WITH START AND END IS NOT NATURAL AS A LANGUAGE KEYWORD.
	- ALIGNMENT WORKS FOR THE STACK ONLY, NOT THE HEAP.
	- __attribute_ CAN TAKE MULTIPLE PARAMETERS. IN OTHER WORDS IF USER WISH TO DEFINE OTHER PROPERTIES
			SUCH AS PACKING, THEY MIGHT NOT BE ABLE TO UNLESS THE COMPILER ALLOWS MULTIPLE __attribute_
			FOR THE SAME THING BEING MODIFIED.
*/
/*
#if(defined(CRX__LAN__CPP))
	#if(defined(_MSC_VER))
		#define CRX__MEMBER_ALIGNMENT__START(pALIGNMENT)	__declspec(align(pALIGNMENT))
		#define CRX__MEMBER_ALIGNMENT__END(pALIGNMENT)
	#elif(defined(__GNUC__))
		#define CRX__MEMBER_ALIGNMENT__START(pALIGNMENT)	
		#define CRX__MEMBER_ALIGNMENT__END(pALIGNMENT)		__attribute_((aligned(pALIGNMENT)))
	#elif(defined(__CLANG__))
		#define CRX__MEMBER_ALIGNMENT__START(pALIGNMENT)	
		#define CRX__MEMBER_ALIGNMENT__END(pALIGNMENT)		__attribute_((aligned(pALIGNMENT)))
	#elif(defined(__alignas_is_defined))
		#define CRX__MEMBER_ALIGNMENT__START(pALIGNMENT)	alignas(pALIGNMENT)
		#define CRX__MEMBER_ALIGNMENT__END(pALIGNMENT) 
	#else
		#define CRX__MEMBER_ALIGNMENT__START(pALIGNMENT)	<-- NO ALIGNMENT APPROACH WAS FOUND FOR THIS ENVIRONMENT -->
		#define CRX__MEMBER_ALIGNMENT__END(pALIGNMENT) 
	#endif
#else
	#if(defined(_MSC_VER))
		#define CRX__MEMBER_ALIGNMENT__START(pALIGNMENT)	__declspec(align(pALIGNMENT))
		#define CRX__MEMBER_ALIGNMENT__END(pALIGNMENT)
	#elif(defined(__GNUC__))
		#define CRX__MEMBER_ALIGNMENT__START(pALIGNMENT)	
		#define CRX__MEMBER_ALIGNMENT__END(pALIGNMENT)		__attribute_((aligned(pALIGNMENT)))
	#elif(defined(__CLANG__))
		#define CRX__MEMBER_ALIGNMENT__START(pALIGNMENT)	
		#define CRX__MEMBER_ALIGNMENT__END(pALIGNMENT)		__attribute_((aligned(pALIGNMENT)))
	#elif(defined(__alignas_is_defined))
		#define CRX__MEMBER_ALIGNMENT__START(pALIGNMENT)	_Alignas(pALIGNMENT)
		#define CRX__MEMBER_ALIGNMENT__END(pALIGNMENT) 
	#else
		#define CRX__MEMBER_ALIGNMENT__START(pALIGNMENT)	<-- NO ALIGNMENT APPROACH WAS FOUND FOR THIS ENVIRONMENT -->
		#define CRX__MEMBER_ALIGNMENT__END(pALIGNMENT) 
	#endif
	
	#define CRX__MEMBER_ALIGNMENT2(pALIGNMENT, pCODE) CRX__MEMBER_ALIGNMENT__START(pALIGNMENT) pCODE CRX__MEMBER_ALIGNMENT__END(pALIGNMENT)

#endif

#define CRX__ALIGNMENT__START(pALIGNMENT)	CRX__MEMBER_ALIGNMENT__START(pALIGNMENT)
#define CRX__ALIGNMENT__END(pALIGNMENT)	CRX__MEMBER_ALIGNMENT__END(pALIGNMENT)
#define CRX__ALIGNMENT2(pALIGNMENT, pI_SHOULD_BE_TYPEDEF_OR_NOTHING, pCODE) typedef CRX__ALIGNMENT__START(pALIGNMENT) pCODE CRX__ALIGNMENT__END(pALIGNMENT)
*/

//

#ifndef __cplusplus
	#if(defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))
		#include <stdbool.h>
	#elif(!defined(_BOOL))
typedef unsigned char bool;
		//#define false 0
		//#define true 1
		enum{false = 0};
		enum{true = 1};
	#else
		#include <stdbool.h>
	#endif
#endif

#endif
#endif