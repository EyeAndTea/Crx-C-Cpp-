#if(!defined(CRX__C__RANDOM__SAFE___h__))
#define CRX__C__RANDOM__SAFE___h__

/*
	(TODO)
	REMEMBER, THIS CLASS NEEDS TO BE CHANGED TO BE INLINE WITH THE CRX RT PROJECT, AND THE MORE
			COMPLETE MAPPING TO THE ABSTRACT LANGUAGE THERE AFTER. WHEN THE TIME COMES, NOTE THE
			FOLLOWING,
		- MANY COMPILE TIME CHECKS MUST CHANGE TO RUN TIME CHECKS.
		- arc4random() WAS INTRODUCED INTO GLIBC IN V2.36. IT EXISTS ON FREEBSD 2.2.6 AND UP.
				IT EXISTS ON MACOS 10.4 AT LEAST IF NOT FURTHER BACK, AND UP.
		- arc4random_buf() WAS INTRODUCED INTO GLIBC IN V2.36. IT EXISTS ON FREEBSD 8.0 AND UP.
				IT EXISTS ON MACOS 10.8 AND UP.
		- getrandom()  WAS INTRODUCED INTO GLIBC IN V2.25, LINUX 3.17
		- PERHAPS IMPLEMENT A RESEED FUNCTION. THE FUNCTION MUST NOT RESEED IF TIME IS USED.
				THIS NEEDS REVIEW HOWEVER.
*/

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
#if(!(defined(__OpenBSD__) || defined(__CloudABI__) || defined(__wasi__)) && defined(_WIN32))
	#include "Crx/H/crx/c/random/Isaac.h"
#endif
#ifdef _WIN32
	#if((NTDDI_VERSION < NTDDI_WINXPSP3) || \
			!(defined(WIN32_LEAN_AND_MEAN) && defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0400)))
		#include "Crx/H/crx/c/random/MersenneTwister.h"
	#endif
#endif
//<<END>>

CRX__LIB__C_CODE_BEGIN()

#if(defined(__OpenBSD__) || defined(__CloudABI__) || defined(__wasi__))
	#define CRX__C__RANDOM__SAFE__PRIVATE__HAS_NATIVE_ARC4RANDOM CRXM__TRUE
#else
	#define CRX__C__RANDOM__SAFE__PRIVATE__HAS_NATIVE_ARC4RANDOM CRXM__FALSE
#endif

//REFERENCE: https://github.com/jedisct1/libsodium/blob/master/src/libsodium/randombytes/sysrandom/randombytes_sysrandom.c

/*
CONTRACT:
	IS FIXED SIZE:			1
	HAS CONSTRUCT:		 	1
	HAS DESTRUCT:		 	1
	IS COPYABLE:			0
	HAS COPY CONSTRUCT:		1
	HAS MOVE CONSTRUCT:		0
	HAS MOVE DESTRUCT:		0
*/
typedef struct Crx_C_Random_SafeRandom
{
	#if(!CRX__C__RANDOM__SAFE__PRIVATE__HAS_NATIVE_ARC4RANDOM)
	int gPrivate_randomDataSourceFileDescriptorBits;
	bool gPrivate_isInitialized;
	bool gPrivate_isLinuxGetRandomAvailable;
		#if(!(defined(__OpenBSD__) || defined(__CloudABI__) || defined(__wasi__)) && defined(_WIN32))
	Crx_C_Random_Isaac gPrivate_isaac;
		#endif
		#ifdef _WIN32
			#if((NTDDI_VERSION < NTDDI_WINXPSP3) || \
					!(defined(WIN32_LEAN_AND_MEAN) && defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0400)))
	Crx_C_Random_MersenneTwister gPrivate_mersenneTwister;
			#endif
		#endif
	#else
	unsigned char _fgf;
	#endif
}Crx_C_Random_SafeRandom;

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_safeRandom_construct(
		Crx_C_Random_SafeRandom * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_safeRandom_copyConstruct(
		Crx_C_Random_SafeRandom * pThis, Crx_C_Random_SafeRandom const * pSafeRandom);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_SafeRandom * crx_c_random_safeRandom_new();
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_SafeRandom * crx_c_random_safeRandom_moveNew(
		Crx_C_Random_SafeRandom * pSafeRandom);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_SafeRandom * crx_c_random_safeRandom_copyNew(
		Crx_C_Random_SafeRandom const * pSafeRandom);

#if(!CRX__C__RANDOM__SAFE__PRIVATE__HAS_NATIVE_ARC4RANDOM)
	#ifndef _WIN32
CRX__LIB__PRIVATE_C_FUNCTION() int crx_c_random_safeRandom_private_openLinuxRandomSource(
		Crx_C_Random_SafeRandom * pThis);
CRX__LIB__PRIVATE_C_FUNCTION() int crx_c_random_safeRandom_private_callLinuxGetRandom(
		Crx_C_Random_SafeRandom * pThis, void * const pBuffer, size_t pLength);
	#else
		#if 0
	/* `RtlGenRandom` is used over `CryptGenRandom` on Microsoft Windows based systems:
	 *  - `CryptGenRandom` requires pulling in `CryptoAPI` which causes unnecessary
	 *     memory overhead if this API is not being used for other purposes
	 *  - `RtlGenRandom` is thus called directly instead. A detailed explanation
	 *     can be found here: https://blogs.msdn.microsoft.com/michael_howard/2005/01/14/cryptographically-secure-random-number-on-windows-without-using-cryptoapi/
	 *
	 * In spite of the disclaimer on the `RtlGenRandom` documentation page that was
	 * written back in the Windows XP days, this function is here to stay. The CRT
	 * function `rand_s()` directly depends on it, so touching it would break many
	 * applications released since Windows XP.
	 *
	 * Also note that Rust, Firefox and BoringSSL (thus, Google Chrome and everything
	 * based on Chromium) also depend on it, and that libsodium allows the RNG to be
	 * replaced without patching nor recompiling the library.
	 */
	 /*
		CryptGenRandom usage is described in
		http://msdn.microsoft.com/library/en-us/security/security/cryptgenrandom.asp
		and many associated pages on Windows Cryptographic Service
		Providers, which say:

			With Microsoft CSPs, CryptGenRandom uses the same
			random number generator used by other security
			components. This allows numerous processes to
			contribute to a system-wide seed. CryptoAPI stores
			an intermediate random seed with every user. To form
			the seed for the random number generator, a calling
			application supplies bits it might havefor instance,
			mouse or keyboard timing inputthat are then added to
			both the stored seed and various system data and
			user data such as the process ID and thread ID, the
			system clock, the system time, the system counter,
			memory status, free disk clusters, the hashed user
			environment block. This result is SHA-1 hashed, and
			the output is used to seed an RC4 stream, which is
			then used as the random stream and used to update
			the stored seed.

		The only other detailed description I've found of the
		sources of randomness for CryptGenRandom is this excerpt
		from a posting
		http://www.der-keiler.de/Newsgroups/comp.security.ssh/2002-06/0169.html

		From: Jon McClelland (dowot69@hotmail.com) 
		Date: 06/12/02 
		... 
		 
		Windows, call a function such as CryptGenRandom, which has two of 
		the properties of a good random number generator, unpredictability and 
		even value distribution. This function, declared in Wincrypt.h, is 
		available on just about every Windows platform, including Windows 95 
		with Internet Explorer 3.02 or later, Windows 98, Windows Me, Windows 
		CE v3, Windows NT 4, Windows 2000, and Windows XP. 
		 
		CryptGenRandom gets its randomness, also known as entropy, from many 
		sources in Windows 2000, including the following: 
		The current process ID (GetCurrentProcessID). 
		The current thread ID (GetCurrentThreadID). 
		The ticks since boot (GetTickCount). 
		The current time (GetLocalTime). 
		Various high-precision performance counters (QueryPerformanceCounter). 
		A Message Digest 4 (MD4) hash of the user's environment block, which 
		includes username, computer name, and search path. 
		 
		High-precision internal CPU counters, such as RDTSC, RDMSR, RDPMC (x86 
		only-more information about these counters is at 
		developer.intel.com/software/idap/resources/technical_collateral/pentiumii/RDTSCPM1.HTM 
		<http://developer.intel.com>). 
		 
		Low-level system information, such as idle time, kernel time, 
		interrupt times, commit limit, page read count, cache read count, 
		nonpaged pool allocations, alignment fixup count, operating system 
		lookaside information. 
		 
		Such information is added to a buffer, which is hashed using MD4 and 
		used as the key to modify a buffer, using RC4, provided by the user. 
		(Refer to the CryptGenRandom documentation in the Platform SDK for 
		more information about the user-provided buffer.) Hence, if the user 
		provides additional data in the buffer, this is used as an element in 
		the witches brew to generate the random data. The result is a 
		cryptographically random number generator. 
		Also, note that if you plan to sell your software to the United States 
		federal government, you'll need to use FIPS 140-1-approved algorithms. 
		The default versions of CryptGenRandom in Microsoft Windows CE v3, 
		Windows 95, Windows 98, Windows Me, Windows 2000, and Windows XP are 
		FIPS-approved. Obviously FIPS-140 compliance is necessary but not 
		sufficient to provide a properly secure source of random data. 
	*/
	//#define RtlGenRandom SystemFunction036
	
//CRX__LIB__EXTERN_C BOOLEAN NTAPI RtlGenRandom(PVOID RandomBuffer, ULONG RandomBufferLength);
CRX__LIB__EXTERN_C BOOLEAN NTAPI SystemFunction036(PVOID RandomBuffer, ULONG RandomBufferLength);
		#endif
CRX__LIB__PRIVATE_C_FUNCTION() unsigned int crx_c_random_safeRandom_private_callWindowsRtlGenRandom(
		Crx_C_Random_SafeRandom * pThis, void * pReturn, size_t pLength);
	#endif

CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_random_safeRandom_private_setup(Crx_C_Random_SafeRandom * pThis);
CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_random_safeRandom_private_closeRandomSource(
		Crx_C_Random_SafeRandom * pThis);
#endif

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_random_safeRandom_getRandomBytes(Crx_C_Random_SafeRandom * pThis,
		void * const pBuffer, const size_t pLength);
CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_random_safeRandom_getRandomUnsignedInt32(
		Crx_C_Random_SafeRandom * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() double crx_c_random_safeRandom_getRandomDouble(Crx_C_Random_SafeRandom * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_safeRandom_destruct(Crx_C_Random_SafeRandom * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_safeRandom_free(Crx_C_Random_SafeRandom * pThis);

CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/random/SafeRandom.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif