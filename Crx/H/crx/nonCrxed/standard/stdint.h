#if(!defined(CRX__NON_CRXED__STANDARD__STDINT___h__))
#define CRX__NON_CRXED__STANDARD__STDINT___h__

/*
NOTE: inttypes.h INCLUDES stdint.h, BUT stdint.h DOES NOT INCLUDE inttypes.h
		THIS FILE HOWEVER MIGHT. THEREFORE BE WARNED THAT IF YOU NEED TO SPECIFY
		THE MACRO __STDC_FORMAT_MACROS FOR inttypes.h AND YOU NEED TO INCLUDE 
		THIS FILE, SPECIFY THAT MACRO BEFORE INCLUDING THIS FILE WHICH SHOULD COME
		EARLIER THAN INCLUDING inttype.h

NOTE: stdint.h, AND THIS FILE, SHOULD ALREADY INCLUDE limits.h
IF ON LINUX limits.h IS NOT INCLUDED, CONSIDER THE CODE:
		#if defined(__linux__)
			#include <linux/limits.h>
		#else
			#include <limits.h>
		#endif
TO BE ADDED TO THIS FILE.

NOTE: THE FALLBACK IN THIS FILE, WHEN stdint.h IS NOT AVAILABLE, DOES NOT GUARANTEE
		LIMIT MACROS SUCH AS UINT32_MAX TO BE DEFINED CURRENTLY.

FOR THIRD PARTY CODE THAT SIMPLY INCLUDES stdint.h AND CAN NOT FIND IT, CREATE AN EMPTY 
FILE WITH THAT NAME TO MAKE IT VISIBLE FOR THE THIRD PARTY CODE, THEN SET ITS CONTENT TO
				#define __STDC_LIMIT_MACROS 
				#define __STDC_CONSTANT_MACROS
				#include "Crx/H/crx/nonCrxed/standard/stdint.h"
				#undef __STDC_LIMIT_MACROS 
				#undef __STDC_CONSTANT_MACROS

OTHERWISE, INCLUDE THIS FILE DIRECTLY.
*/

#if(defined(CRX__BOOST_HAS_STDINT_H) && (!defined(__GLIBC__) || defined(__GLIBC_HAVE_LONG_LONG)  ||   \
		(defined(__GLIBC__) && ((__GLIBC__ > 2) || ((__GLIBC__ == 2) && (__GLIBC_MINOR__ >= 17))))))
	#if(defined(__hpux))
		#include <inttypes.h>
	#elif(defined(__FreeBSD__) || defined(__IBMCPP__) || defined(_AIX))
		#include <inttypes.h>
	#else
		#include <stdint.h>
	
		// FROM BOOST
		// There is a bug in Cygwin two _C macros
		#if(defined(INTMAX_C) && defined(__CYGWIN__))
			#undef INTMAX_C
			#undef UINTMAX_C
			#define INTMAX_C(c) c##LL
			#define UINTMAX_C(c) c##ULL
		#endif
	#endif

#elif defined(__FreeBSD__) && (__FreeBSD__ <= 4) || defined(__osf__) || defined(__VMS) || defined(__SOLARIS9__) || defined(__NetBSD__)
	// FreeBSD and Tru64 have an <inttypes.h> that contains much of what we need.
	#include <inttypes.h>

#else
	/*
	REFERENCE CODE:
		- BOOST 1.82.0 cstind.hpp FILE
		- REPLACEMENT stdint.h FILE FROM MICROSOFT FOR VISUAL STUDIO 2010 AND BEFORE. AS SOME POINT
				VISUAL STUDIO 2010 DID GET ITS OWN stdint.h FILE.
		- VISUAL STUDIO 2017 stdint.h FILE
	CURRENTLY AS REPLACEMENT, I DO NOT SUPPORT INT64 UNLESS IT IS VISUAL STUDIO AND I DO NOT
			INTEND TO EVER SUPPORT INT64 TYPES.
			I ALSO DO NOT SUPPORT C'S PERTAINING STANDARD MACROS UNELSS IT IS VISUAL STUDIO.
	*/

	// ISO C9x  compliant stdint.h for Microsoft Visual Studio
	// Based on ISO/IEC 9899:TC2 Committee draft (May 6, 2005) WG14/N1124 
	// 
	//  Copyright (c) 2006-2008 Alexander Chemeris
	// 
	// Redistribution and use in source and binary forms, with or without
	// modification, are permitted provided that the following conditions are met:
	// 
	//   1. Redistributions of source code must retain the above copyright notice,
	//      this list of conditions and the following disclaimer.
	// 
	//   2. Redistributions in binary form must reproduce the above copyright
	//      notice, this list of conditions and the following disclaimer in the
	//      documentation and/or other materials provided with the distribution.
	// 
	//   3. The name of the author may be used to endorse or promote products
	//      derived from this software without specific prior written permission.
	// 
	// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
	// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
	// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
	// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
	// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
	// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
	// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
	// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
	// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
	// 
	///////////////////////////////////////////////////////////////////////////////
	#include <limits.h>

	//#if(defined(_MSC_VER))
	#if(CRX__COMPILER__TYPE == CRX__COMPILER__TYPE__MICROSOFT)
		// FROM MICROSOFT
		// For Visual Studio 6 in C++ mode and for many Visual Studio versions when
		// compiling for ARM we should wrap <wchar.h> include with 'extern "C++" {}'
		// or compiler give many errors like this:
		//   error C2733: second C linkage of overloaded function 'wmemchr' not allowed
		#ifdef __cplusplus
		extern "C" {
		#endif
		//#include <wchar.h>
		#ifdef __cplusplus
		}
		#endif

		//FROM MICROSOFT
		// Define _W64 macros to mark types changing their size, like intptr_t.
		#ifndef _W64
		#if(!defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && defined(_MSC_VER) && (_MSC_VER >= 1300))
		#  define _W64 __w64
		#else
		#  define _W64
		#endif
		#endif
	#endif

	// FROM BOOST:
	// For the following code we get several warnings along the lines of:
	//
	// boost/cstdint.hpp:428:35: error: use of C99 long long integer constant
	//
	// So we declare this a system header to suppress these warnings.
	// See also https://github.com/boostorg/config/issues/190
	//
	#if defined(__GNUC__) && (__GNUC__ >= 4)
		#pragma GCC system_header
	#endif


	//#if(defined(_MSC_VER))
	#if(CRX__COMPILER__TYPE == CRX__COMPILER__TYPE__MICROSOFT)
	// FROM MICROSOFT
	// 7.18.1 Integer types

	// 7.18.1.1 Exact-width integer types

	// Visual Studio 6 and Embedded Visual C++ 4 doesn't
	// realize that, e.g. char has the same size as __int8
	// so we give up on __intX for them.
		#if(_MSC_VER < 1300)
	typedef signed char       int8_t;
	typedef signed short      int16_t;
	typedef signed int        int32_t;
	typedef unsigned char     uint8_t;
	typedef unsigned short    uint16_t;
	typedef unsigned int      uint32_t;
		#else
	typedef signed __int8     int8_t;
	typedef signed __int16    int16_t;
	typedef signed __int32    int32_t;
	typedef unsigned __int8   uint8_t;
	typedef unsigned __int16  uint16_t;
	typedef unsigned __int32  uint32_t;
		#endif
		
	typedef signed __int64       int64_t;
	typedef unsigned __int64     uint64_t;


	// FROM MICROSOFT
	// 7.18.1.2 Minimum-width integer types
	typedef int8_t    int_least8_t;
	typedef int16_t   int_least16_t;
	typedef int32_t   int_least32_t;
	typedef int64_t   int_least64_t;
	typedef uint8_t   uint_least8_t;
	typedef uint16_t  uint_least16_t;
	typedef uint32_t  uint_least32_t;
	typedef uint64_t  uint_least64_t;

	// FROM MICROSOFT
	// 7.18.1.3 Fastest minimum-width integer types
	typedef int8_t    int_fast8_t;
	typedef int16_t   int_fast16_t;
	typedef int32_t   int_fast32_t;
	typedef int64_t   int_fast64_t;
	typedef uint8_t   uint_fast8_t;
	typedef uint16_t  uint_fast16_t;
	typedef uint32_t  uint_fast32_t;
	typedef uint64_t  uint_fast64_t;

	// FROM MICROSOFT
	// 7.18.1.4 Integer types capable of holding object pointers
		#ifdef _WIN64 // [
	typedef signed __int64    intptr_t;
	typedef unsigned __int64  uintptr_t;
		#else // _WIN64 ][
	typedef _W64 signed int   intptr_t;
	typedef _W64 unsigned int uintptr_t;
		#endif // _WIN64 ]
	/* WARNING ABOUT THE ABOVE (FROM BOOST)
	#if defined(BOOST_WINDOWS) && !defined(_WIN32_WCE) && !defined(BOOST_HAS_STDINT_H)
		// Older MSVC don't have stdint.h and have intptr_t/uintptr_t defined in stddef.h
		#include <stddef.h>
	#endif
	*/
	

	// FROM MICROSOFT
	// 7.18.1.5 Greatest-width integer types
	typedef int64_t   intmax_t;
	typedef uint64_t  uintmax_t;

	#else
		#if(UCHAR_MAX == 0xff)
	typedef signed char     int8_t;
	typedef signed char     int_least8_t;
	typedef signed char     int_fast8_t;
	typedef unsigned char   uint8_t;
	typedef unsigned char   uint_least8_t;
	typedef unsigned char   uint_fast8_t;
		#endif

		#if(USHRT_MAX == 0xffff)
	// FROM BOOST
	// The Cray X1 has a 16-bit short, however it is not recommend
	// for use in performance critical code.
	typedef signed short      int16_t;
	typedef signed short    int_least16_t;
			#if(defined(__crayx1))
	typedef int             int_fast16_t;
			#else
	typedef signed short    int_fast16_t;
			#endif
	typedef unsigned short    uint16_t;
	typedef unsigned short  uint_least16_t;
			#if(defined(__crayx1))
	typedef unsigned int    uint_fast16_t;
			#else
	typedef unsigned short  uint_fast16_t;
			#endif
		#elif((USHRT_MAX == 0xffffffff) && defined(__MTA__))
	// FROM BOOST
	// On MTA / XMT short is 32 bits unless the -short16 compiler flag is specified
	// MTA / XMT does support the following non-standard integer types
	typedef __short16           int16_t;
	typedef __short16           int_least16_t;
	typedef __short16           int_fast16_t;
	typedef unsigned __short16  uint16_t;
	typedef unsigned __short16  uint_least16_t;
	typedef unsigned __short16  uint_fast16_t;
		#elif((USHRT_MAX == 0xffffffff) && defined(CRAY))
	// FROM BOOST     
	// no 16-bit types on Cray:
	typedef short           int_least16_t;
	typedef short           int_fast16_t;
	typedef unsigned short  uint_least16_t;
	typedef unsigned short  uint_fast16_t;
		#endif

		#if(UINT_MAX == 0xffffffff)
	typedef int             int32_t;
	typedef int             int_least32_t;
	typedef int             int_fast32_t;
	typedef unsigned int    uint32_t;
	typedef unsigned int    uint_least32_t;
	typedef unsigned int    uint_fast32_t;
		#elif(USHRT_MAX == 0xffffffff)
	typedef short             int32_t;
	typedef short             int_least32_t;
	typedef short             int_fast32_t;
	typedef unsigned short    uint32_t;
	typedef unsigned short    uint_least32_t;
	typedef unsigned short    uint_fast32_t;
		#elif(ULONG_MAX == 0xffffffff)
	typedef long            int32_t;
	typedef long            int_least32_t;
	typedef long            int_fast32_t;
	typedef unsigned long   uint32_t;
	typedef unsigned long   uint_least32_t;
	typedef unsigned long   uint_fast32_t;
		#elif((UINT_MAX == 0xffffffffffffffff) && defined(__MTA__))
	// FROM BOOST
	// Integers are 64 bits on the MTA / XMT
	typedef __int32           int32_t;
	typedef __int32           int_least32_t;
	typedef __int32           int_fast32_t;
	typedef unsigned __int32  uint32_t;
	typedef unsigned __int32  uint_least32_t;
	typedef unsigned __int32  uint_fast32_t;
		#endif

		/*
		EDUCATED GUESS. USING !defined(CRX__FOR_CRX_ONLY__PRIVATE__BOOST_HAS_MS_INT64) INSTEAD
		OF
				!defined(BOOST_MSVC) && !defined(BOOST_BORLANDC)
		#if(defined(CRX__FOR_CRX_ONLY__BOOST_HAS_LONG_LONG) && \
				!defined(BOOST_MSVC) && !defined(BOOST_BORLANDC) && \
				(!defined(__GLIBCPP__) || defined(_GLIBCPP_USE_LONG_LONG)) && \
				(defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX)))*/
		#if(defined(CRX__FOR_CRX_ONLY__BOOST_HAS_LONG_LONG) && \
				!defined(CRX__FOR_CRX_ONLY__PRIVATE__BOOST_HAS_MS_INT64) && \
				(!defined(__GLIBCPP__) || defined(_GLIBCPP_USE_LONG_LONG)) && \
				(defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX)))
		#elif(ULONG_MAX != 0xffffffff)
			#if ULONG_MAX == 18446744073709551615 // 2**64 - 1
	typedef long                 intmax_t;
	typedef unsigned long        uintmax_t;
	typedef long                 int64_t;
	typedef long                 int_least64_t;
	typedef long                 int_fast64_t;
	typedef unsigned long        uint64_t;
	typedef unsigned long        uint_least64_t;
	typedef unsigned long        uint_fast64_t;
			#endif
		#elif(defined(__GNUC__) && defined(CRX__FOR_CRX_ONLY__BOOST_HAS_LONG_LONG))
	 __extension__ typedef long long            intmax_t;
	 __extension__ typedef unsigned long long   uintmax_t;
	 __extension__ typedef long long            int64_t;
	 __extension__ typedef long long            int_least64_t;
	 __extension__ typedef long long            int_fast64_t;
	 __extension__ typedef unsigned long long   uint64_t;
	 __extension__ typedef unsigned long long   uint_least64_t;
	 __extension__ typedef unsigned long long   uint_fast64_t;
		#elif(defined(CRX__FOR_CRX_ONLY__PRIVATE__BOOST_HAS_MS_INT64))
			 //
			 //FROM BOOST: we have Borland/Intel/Microsoft __int64:
			 //
	 typedef __int64             intmax_t;
	 typedef unsigned __int64    uintmax_t;
	 typedef __int64             int64_t;
	 typedef __int64             int_least64_t;
	 typedef __int64             int_fast64_t;
	 typedef unsigned __int64    uint64_t;
	 typedef unsigned __int64    uint_least64_t;
	 typedef unsigned __int64    uint_fast64_t;
		#else
	// I DO NOT SUPPORT INT64 WITH MY REPLACEMENT FOR stdint.h UNLESS IT IS MSVC
	//	UPDATE: I ADDED SOME SUPPORT NOW (crx.h), BUT RELIANCE ON IT IS CURRENTLY DISCOURAGED
	typedef int32_t   intmax_t;
	typedef uint32_t  uintmax_t;
		#endif
	#endif


	//IF YOU GET AN ERROR WITH BORLAND, OR A COMPILER THAT MIGHT BE DEFINING _MSC_VER, YOU MIGHT 
	//		HAVE TO MOVE THE TEST FOR CRX__FOR_CRX_ONLY__PRIVATE__BOOST_HAS_MS_INT64 TO HERE
	//		AS IN DONE IN BOOST. YOU MIGHT ALSO WANT TO MOVE THE LIMITS TO THEIR OWN REGION.
	//LATER ADDED CHECK FOR ABSENT BOOST_BORLANDC TO HOPEFULY AVOID CONFLICT WITH BORLAND AT LEAST.
	//LATER ADDED PROPER CHECK FOR MICROSOFT COMPILER
	//#if(defined(_MSC_VER) && !defined(BOOST_BORLANDC))
	#if(CRX__COMPILER__TYPE == CRX__COMPILER__TYPE__MICROSOFT)
		// FROM MICROSOFT

		// 7.18.2 Limits of specified-width integer types

		/*
		SEE NOTE BELOW ABOUT THE EXTRA (__cplusplus > 199711L) CHECK
		*/
		#if !defined(__cplusplus) || (__cplusplus > 199711L) || defined(__STDC_LIMIT_MACROS) // [   See footnote 220 at page 257 and footnote 221 at page 259

			// 7.18.2.1 Limits of exact-width integer types
			#define INT8_MIN     ((int8_t)_I8_MIN)
			#define INT8_MAX     _I8_MAX
			#define INT16_MIN    ((int16_t)_I16_MIN)
			#define INT16_MAX    _I16_MAX
			#define INT32_MIN    ((int32_t)_I32_MIN)
			#define INT32_MAX    _I32_MAX
			#define INT64_MIN    ((int64_t)_I64_MIN)
			#define INT64_MAX    _I64_MAX
			#define UINT8_MAX    _UI8_MAX
			#define UINT16_MAX   _UI16_MAX
			#define UINT32_MAX   _UI32_MAX
			#define UINT64_MAX   _UI64_MAX

			// 7.18.2.2 Limits of minimum-width integer types
			#define INT_LEAST8_MIN    INT8_MIN
			#define INT_LEAST8_MAX    INT8_MAX
			#define INT_LEAST16_MIN   INT16_MIN
			#define INT_LEAST16_MAX   INT16_MAX
			#define INT_LEAST32_MIN   INT32_MIN
			#define INT_LEAST32_MAX   INT32_MAX
			#define INT_LEAST64_MIN   INT64_MIN
			#define INT_LEAST64_MAX   INT64_MAX
			#define UINT_LEAST8_MAX   UINT8_MAX
			#define UINT_LEAST16_MAX  UINT16_MAX
			#define UINT_LEAST32_MAX  UINT32_MAX
			#define UINT_LEAST64_MAX  UINT64_MAX

			// 7.18.2.3 Limits of fastest minimum-width integer types
			#define INT_FAST8_MIN    INT8_MIN
			#define INT_FAST8_MAX    INT8_MAX
			#define INT_FAST16_MIN   INT16_MIN
			#define INT_FAST16_MAX   INT16_MAX
			#define INT_FAST32_MIN   INT32_MIN
			#define INT_FAST32_MAX   INT32_MAX
			#define INT_FAST64_MIN   INT64_MIN
			#define INT_FAST64_MAX   INT64_MAX
			#define UINT_FAST8_MAX   UINT8_MAX
			#define UINT_FAST16_MAX  UINT16_MAX
			#define UINT_FAST32_MAX  UINT32_MAX
			#define UINT_FAST64_MAX  UINT64_MAX

			// 7.18.2.4 Limits of integer types capable of holding object pointers
			#ifdef _WIN64 // [
				#define INTPTR_MIN   INT64_MIN
				#define INTPTR_MAX   INT64_MAX
				#define UINTPTR_MAX  UINT64_MAX
			#else // _WIN64 ][
				#define INTPTR_MIN   INT32_MIN
				#define INTPTR_MAX   INT32_MAX
				#define UINTPTR_MAX  UINT32_MAX
			#endif // _WIN64 ]

			// 7.18.2.5 Limits of greatest-width integer types
			#define INTMAX_MIN   INT64_MIN
			#define INTMAX_MAX   INT64_MAX
			#define UINTMAX_MAX  UINT64_MAX

			// 7.18.3 Limits of other integer types

			#ifdef _WIN64 // [
				#define PTRDIFF_MIN  _I64_MIN
				#define PTRDIFF_MAX  _I64_MAX
			#else  // _WIN64 ][
				#define PTRDIFF_MIN  _I32_MIN
				#define PTRDIFF_MAX  _I32_MAX
			#endif  // _WIN64 ]

			#define SIG_ATOMIC_MIN  INT_MIN
			#define SIG_ATOMIC_MAX  INT_MAX

			//NOTE: THIS HEADER DOES NOT GUARANTEE SIZE_MAX. IT IS NOT DEFINED FOR OTHER COMPILERS.
			//		THERE IS THE VALUE OF ((size_t)-1), BUT IT CAN NOT WORK IN PREPROCESSOR 
			//		DIRECTIVES
			#ifndef SIZE_MAX // [
				#ifdef _WIN64 // [
					#define SIZE_MAX  _UI64_MAX
				#else // _WIN64 ][
					#define SIZE_MAX  _UI32_MAX
				#endif // _WIN64 ]
			#endif // SIZE_MAX ]

			// WCHAR_MIN and WCHAR_MAX are also defined in <wchar.h>
			#ifndef WCHAR_MIN // [
				#define WCHAR_MIN  0
			#endif  // WCHAR_MIN ]
			#ifndef WCHAR_MAX // [
				#define WCHAR_MAX  _UI16_MAX
			#endif  // WCHAR_MAX ]

			#define WINT_MIN  0
			#define WINT_MAX  _UI16_MAX

		#endif // __STDC_LIMIT_MACROS ]


		// 7.18.4 Limits of other integer types

		/*
		QUOTE: glibc's <stdint.h> follows C99, which says that in C++, certain macros should only be 
				defined if __STDC_LIMIT_MACROS or __STDC_CONSTANT_MACROS is defined. However, the C++ 
				committee decided that they didn't want this behavior, and explicitly overruled this in the
				C++11 standard (the first to provide <stdint.h>). Consequently C11 removed these rules. 
				glibc has not been updated to follow the C11 rules, and still checks for those macros 
				being defined in C++ mode. The ISO C99 standard specifies that in C++ implementations these
				macros should only be defined if explicitly requested. 
						#if !defined __cplusplus || defined __STDC_LIMIT_MACROS
				{https://sourceware.org/bugzilla/show_bug.cgi?id=15366}
				
				I ADDED THE EXTRA (__cplusplus > 199711L) TO CHECK IF C++11. HOWEVER, UNDER VISUAL STUDIO 2010
				THERE IS C++11 BUT __cplusplus IS SET TO 199711L. 
				{https://stackoverflow.com/questions/5047971/how-do-i-check-for-c11-support}
		*/
		#if(!defined(__cplusplus) || (__cplusplus > 199711L) || defined(__STDC_CONSTANT_MACROS)) // [   See footnote 224 at page 260

			// 7.18.4.1 Macros for minimum-width integer constants

			#define INT8_C(val)  val##i8
			#define INT16_C(val) val##i16
			#define INT32_C(val) val##i32
			#define INT64_C(val) val##i64

			#define UINT8_C(val)  val##ui8
			#define UINT16_C(val) val##ui16
			#define UINT32_C(val) val##ui32
			#define UINT64_C(val) val##ui64

			// 7.18.4.2 Macros for greatest-width integer constants
			#define INTMAX_C   INT64_C
			#define UINTMAX_C  UINT64_C

		#endif // __STDC_CONSTANT_MACROS ]
	#else
		/*
		THE FOLLOWING IS FROM BOOST. HOWEVER, UNLIKE BOOST,
			- THE FOLLOWING DOES NOT INCLUDE THE STUFF FOR MICROSOFT, AND IT SEEMS, BORLAND AS WELL.
			- THE FOLLOWING IS CONDITIONAL ON A "NATIVE" stdint.h NOT EXISTING. HOWEVER, IN BOOST,
					THIS IS NOT THE CASE AND THE FOLLOWING IS ALWAYS USED. IN THE BOOST SOURCE
					CODE THERE IS THE NOTE:
							Macro definition section:

							Added 23rd September 2000 (John Maddock).
							Modified 11th September 2001 to be excluded when
							BOOST_HAS_STDINT_H is defined (John Maddock).
							Modified 11th Dec 2009 to always define the
							INT#_C macros if they're not already defined (John Maddock).			
		*/
		#if(!defined(INT8_C) || !defined(INT16_C) || !defined(INT32_C) || !defined(INT64_C))
			//
			// Undef the macros as a precaution, since we may get here if <stdint.h> has failed
			// to define them all, see https://svn.boost.org/trac/boost/ticket/12786
			//
			#undef INT8_C
			#undef INT16_C
			#undef INT32_C
			#undef INT64_C
			#undef INTMAX_C
			#undef UINT8_C
			#undef UINT16_C
			#undef UINT32_C
			#undef UINT64_C
			#undef UINTMAX_C

			//#include <limits.h>  ORIGINALLY IN BOOST. NOT NEEDED IN OUR CASE
			//  do it the old fashioned way:

			//  8-bit types  ------------------------------------------------------------//

			#if defined(CRX__FOR_CRX_ONLY__PRIVATE__BOOST_HAS_MS_INT64) && !defined(INT8_C)
				#define INT8_C(value)     value##i8

				//#ifdef BOOST_BORLANDC
				// NOTE THE DEFINITION FOR BOOST_BORLANDC WAS FROM V1.82 WHICH INCLUDED THE CODE
				//		GEAR COMPILER AND A CHECK THAT __clang__ WAS NOT DEFINED BY THAT COMPILER.
				#if((CRX__COMPILER__TYPE == CRX__COMPILER__TYPE__BORLAND) || \
						((CRX__COMPILER__TYPE == CRX__COMPILER__TYPE__CODE_GEAR) && \
								!defined(__clang__)))
					//FROM BOOST: Borland bug: appending ui8 makes the type a signed char
					#if(CRX__LAN__CPP)
						#define UINT8_C(value)    static_cast<unsigned char>(value##u)
					#else
						#define UINT8_C(value)    ((unsigned char) value##u)
					#endif
				#else
					#define UINT8_C(value)    value##ui8
				#endif
			#elif (UCHAR_MAX == 0xff) && !defined(INT8_C)
				#if(CRX__LAN__CPP)
					#define INT8_C(value) static_cast<int8_t>(value)
					#define UINT8_C(value) static_cast<uint8_t>(value##u)
				#else
					#define INT8_C(value) ((int8_t) value)
					#define UINT8_C(value) ((uint8_t) value##u)
				#endif
			#endif

			//  16-bit types  -----------------------------------------------------------//

			#if defined(CRX__FOR_CRX_ONLY__PRIVATE__BOOST_HAS_MS_INT64) && !defined(INT16_C)
				#define INT16_C(value)    value##i16
				#define UINT16_C(value)   value##ui16
			#elif (USHRT_MAX == 0xffff) && !defined(INT16_C)
				#if(CRX__LAN__CPP)
					#define INT16_C(value) static_cast<int16_t>(value)
					#define UINT16_C(value) static_cast<uint16_t>(value##u)
				#else
					#define INT16_C(value) ((int16_t) value)
					#define UINT16_C(value) ((uint16_t) value##u)
				#endif
			#endif

			//  32-bit types  -----------------------------------------------------------//
			#ifndef INT32_C
				#if defined(CRX__FOR_CRX_ONLY__PRIVATE__BOOST_HAS_MS_INT64)
					#define INT32_C(value)    value##i32
					#define UINT32_C(value)   value##ui32
				#elif(UINT_MAX == 0xffffffff)
					#define INT32_C(value) value
					#define UINT32_C(value) value##u
				#elif ULONG_MAX == 0xffffffff
					#define INT32_C(value) value##L
					#define UINT32_C(value) value##uL
				#endif
			#endif

			//  64-bit types + intmax_t and uintmax_t  ----------------------------------//
			#ifndef INT64_C
				#if defined(CRX__FOR_CRX_ONLY__PRIVATE__BOOST_HAS_MS_INT64)
					#define UINT64_C(value)   value##ui64
					#define INTMAX_C(value)   value##i64
					#define UINTMAX_C(value)  value##ui64
				//BOOST_HAS_LONG_LONG WAS ASSUMED NOT DEFINED ORIGINALLY. I EVENTUALLY
				//		ADDED SUPPORT BUT THE MACRO IS NOT FUNDAMENTAL AND THEREFORE IS KEPT 
				//		ABOVE IN THIS VERY FILE.
				#elif(defined(CRX__FOR_CRX_ONLY__BOOST_HAS_LONG_LONG) && \
						(defined(ULLONG_MAX) || defined(ULONG_LONG_MAX) || defined(ULONGLONG_MAX) || defined(_ULLONG_MAX) || defined(_LLONG_MAX)))

					#if defined(__hpux)
						// HP-UX's value of ULONG_LONG_MAX is unusable in preprocessor expressions
						#define INT64_C(value) value##LL
						#define UINT64_C(value) value##uLL
					#elif (defined(ULLONG_MAX) && ULLONG_MAX == 18446744073709551615ULL) ||  \
							(defined(ULONG_LONG_MAX) && ULONG_LONG_MAX == 18446744073709551615ULL) ||  \
							(defined(ULONGLONG_MAX) && ULONGLONG_MAX == 18446744073709551615ULL) || \
							(defined(_ULLONG_MAX) && _ULLONG_MAX == 18446744073709551615ULL) || \
							(defined(_LLONG_MAX) && _LLONG_MAX == 9223372036854775807LL)
						#define INT64_C(value) value##LL
						#define UINT64_C(value) value##uLL
					#else
						#error defaults not correct; you must hand modify boost/cstdint.hpp
					#endif
				#elif ULONG_MAX != 0xffffffff
					#if ULONG_MAX == 18446744073709551615U // 2**64 - 1
						#define INT64_C(value) value##L
						#define UINT64_C(value) value##uL
					#else
						#error defaults not correct; you must hand modify boost/cstdint.hpp
					#endif
				#elif defined(BOOST_HAS_LONG_LONG)
					// Usual macros not defined, work things out for ourselves:
					#if(~0uLL == 18446744073709551615ULL)
						#define INT64_C(value) value##LL
						#define UINT64_C(value) value##uLL
					#else
						#error defaults not correct; you must hand modify boost/cstdint.hpp
					#endif
				#else
					#error defaults not correct; you must hand modify boost/cstdint.hpp
				#endif

				#ifdef CRX__BOOST_NO_INT64_T
					#define INTMAX_C(value) INT32_C(value)
					#define UINTMAX_C(value) UINT32_C(value)
				#else
					#define INTMAX_C(value) INT64_C(value)
					#define UINTMAX_C(value) UINT64_C(value)
				#endif
			#endif
		#endif // INT#_C macros.
	#endif
#endif



#endif