//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/random/SafeRandom.h"

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include "Crx/H/crx/nonCrxed/standard/stdint.h"
#include <string.h>
#if(defined(__OpenBSD__) || defined(__CloudABI__) || defined(__wasi__))
	#define CRX__C__RANDOM__SAFE__PRIVATE__HAS_LINUX_COMPATIBLE_GETRANDOM CRXM__FALSE

	#define CRX__C__RANDOM__SAFE__GET_RANDOM(B, S, F)  __ERROR__NOT__SUPPORTED
#else
	#ifndef _WIN32
		#include <unistd.h>
		#include <sys/stat.h>
		#include <sys/time.h>
		
		#ifdef HAVE_SYS_RANDOM_H
			#include <sys/random.h>
		#endif
		
		#ifdef __linux__
			#ifdef HAVE_GETRANDOM
				#define CRX__C__RANDOM__SAFE__PRIVATE__HAS_LINUX_COMPATIBLE_GETRANDOM CRXM__TRUE
				
				#define CRX__C__RANDOM__SAFE__GET_RANDOM(B, S, F) getrandom(B, S, F)
			#else
				#include <sys/syscall.h>

				#if(defined(SYS_getrandom) && defined(__NR_getrandom))
					#define CRX__C__RANDOM__SAFE__PRIVATE__HAS_LINUX_COMPATIBLE_GETRANDOM CRXM__TRUE
					
					#define CRX__C__RANDOM__SAFE__GET_RANDOM(B, S, F) \
							syscall(SYS_getrandom, (B), (int) (S), (F))
				#else
					#define CRX__C__RANDOM__SAFE__PRIVATE__HAS_LINUX_COMPATIBLE_GETRANDOM CRXM__FALSE
				#endif
			#endif
		#elif defined(__FreeBSD__) || defined(__DragonFly__)
			#include <sys/param.h>

			#if(defined(__FreeBSD_version) && __FreeBSD_version >= 1200000) || \
					(defined(__DragonFly_version) && __DragonFly_version >= 500700)
				#define CRX__C__RANDOM__SAFE__PRIVATE__HAS_LINUX_COMPATIBLE_GETRANDOM CRXM__TRUE

				#define CRX__C__RANDOM__SAFE__GET_RANDOM(B, S, F) getrandom(B, S, F)
			#else
				#define CRX__C__RANDOM__SAFE__PRIVATE__HAS_LINUX_COMPATIBLE_GETRANDOM CRXM__FALSE
			#endif
		#else
			#define CRX__C__RANDOM__SAFE__PRIVATE__HAS_LINUX_COMPATIBLE_GETRANDOM CRXM__FALSE
		#endif

		#if(!defined(NO_BLOCKING_RANDOM_POLL) && defined(__linux__))
			#define CRX_RANDOM_SAFE__BLOCK_ON_DEV_RANDOM

			#include <poll.h>
		#endif
		
		#ifndef SSIZE_MAX
			#define SSIZE_MAX (SIZE_MAX / 2 - 1)
		#endif
	#else
		//#define WIN32_LEAN_AND_MEAN
		#include <windows.h>
		/*
			"The wincrypt.h file is guarded with the following statement:
			#if(_WIN32_WINNT >= 0x0400)

			Here is the explanation of the use of that pre-processor logic from MSDN:

			There are functions in Windows 95 OEM Service Release 2 that are guarded by 
			(_WIN32_WINNT >= 0x0400), such as the Crypto API. If you are writing an application 
			specifically for Windows 95 OEM Service Release 2, and you want the header files 
			to provide compile time access to these functions, it is necessary to define _WIN32_WINNT 
			as 0x0400. Note that an application that uses these functions will not run correctly on 
			the retail release of Windows 95. In general, applications expected to run on 
			Windows 95 should be built without defining _WIN32_WINNT." [SOUCE: 
					https://www.tek-tips.com/viewthread.cfm?qid=20694]
			
			NOTE THAT THIS WOULD ALSO NEED DEFINING WIN32_LEAN_AND_MEAN ABOVE
		*/
		//#if(!defined(_WIN32_WINNT))
			//#define _WIN32_WINNT 0x0400
		//#endif
		//#include <Wincrypt.h>
		//#include "isaac/rand.h"
		#if(defined(WIN32_LEAN_AND_MEAN) && defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0400))
			#include <Wincrypt.h>
		#endif
		
		//NOT USING THE lib, BUT USING THE DLL INSTEAD TO SUPPORT OLD WINDOWS.
		#if 0
			#pragma comment(lib, "advapi32.lib")

			#define RtlGenRandom SystemFunction036
		#endif
		
		#define CRX__C__RANDOM__SAFE__PRIVATE__HAS_LINUX_COMPATIBLE_GETRANDOM CRXM__FALSE
	#endif

	#if(!CRX__C__RANDOM__SAFE__PRIVATE__HAS_LINUX_COMPATIBLE_GETRANDOM)
		#define CRX__C__RANDOM__SAFE__GET_RANDOM(B, S, F)  __ERROR__NOT__SUPPORTED
	#endif
#endif
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#if(!(defined(__OpenBSD__) || defined(__CloudABI__) || defined(__wasi__)) && defined(_WIN32))
	#include "Crx/H/crx/c/random/Isaac.h"
#endif
#ifdef _WIN32
	#if((NTDDI_VERSION < NTDDI_WINXPSP3) || \
			!(defined(WIN32_LEAN_AND_MEAN) && defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0400)))
		#include "Crx/H/crx/c/random/MersenneTwister.h"
	#endif
#endif
#if(!CRX__C__RANDOM__SAFE__PRIVATE__HAS_NATIVE_ARC4RANDOM && !defined(_WIN32))
	//CRX__C__RANDOM__SAFE__PRIVATE__DO_ISNAM_AND_ISCHR()
	#if(defined(__COMPCERT__))
		#define CRX__C__RANDOM__SAFE__PRIVATE__DO_ISNAM_AND_ISCHR(pSTAT) true
	#elif(defined(S_ISNAM))
		#define CRX__C__RANDOM__SAFE__PRIVATE__DO_ISNAM_AND_ISCHR(pSTAT) \
				(S_ISNAM(pSTAT.st_mode) || S_ISCHR(pSTAT.st_mode))
	#else
		#define CRX__C__RANDOM__SAFE__PRIVATE__DO_ISNAM_AND_ISCHR(pSTAT) \
				S_ISCHR(pSTAT.st_mode)
	#endif
#endif
//<<END>>

CRX__LIB__C_CODE_BEGIN()

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_safeRandom_construct(
		Crx_C_Random_SafeRandom * pThis)
{
#if(!CRX__C__RANDOM__SAFE__PRIVATE__HAS_NATIVE_ARC4RANDOM)
	pThis->gPrivate_randomDataSourceFileDescriptorBits = -1;
	pThis->gPrivate_isInitialized = false;
	pThis->gPrivate_isLinuxGetRandomAvailable = false;
	#if(!(defined(__OpenBSD__) || defined(__CloudABI__) || defined(__wasi__)) && defined(_WIN32))
	crx_c_random_isaac_construct(&(pThis->gPrivate_isaac), (uint32_t)(time(NULL)));
	#endif
	#ifdef _WIN32
		#if((NTDDI_VERSION < NTDDI_WINXPSP3) || \
				!(defined(WIN32_LEAN_AND_MEAN) && defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0400)))
	crx_c_random_mersenneTwister_construct(&(pThis->gPrivate_mersenneTwister), 
			crx_c_random_isaac_getRandomUnsignedInt32(&(pThis->gPrivate_isaac)));
		#endif
	#endif

	crx_c_random_safeRandom_private_setup(pThis);
#endif
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_safeRandom_copyConstruct(
		Crx_C_Random_SafeRandom * pThis, Crx_C_Random_SafeRandom const * pSafeRandom)
	{abort();}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_SafeRandom * crx_c_random_safeRandom_new()
{
	Crx_C_Random_SafeRandom * vReturn = 
			((Crx_C_Random_SafeRandom *)malloc(sizeof(Crx_C_Random_SafeRandom)));

	if(vReturn != NULL)
		{crx_c_random_safeRandom_construct(vReturn);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_SafeRandom * crx_c_random_safeRandom_moveNew(
		Crx_C_Random_SafeRandom * pSafeRandom)
{
	Crx_C_Random_SafeRandom * vReturn = (Crx_C_Random_SafeRandom *)(calloc(1,
			sizeof(Crx_C_Random_SafeRandom)));

	if(vReturn != NULL)
		{memcpy(vReturn, pSafeRandom, sizeof(Crx_C_Random_SafeRandom));}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_SafeRandom * crx_c_random_safeRandom_copyNew(
		Crx_C_Random_SafeRandom const * pSafeRandom)
	{abort(); return NULL;}

#if(!CRX__C__RANDOM__SAFE__PRIVATE__HAS_NATIVE_ARC4RANDOM)
	#ifndef _WIN32
CRX__LIB__PRIVATE_C_FUNCTION() int crx_c_random_safeRandom_private_openLinuxRandomSource(
		Crx_C_Random_SafeRandom * pThis)
{
		#ifdef CRX_RANDOM_SAFE__BLOCK_ON_DEV_RANDOM
    struct pollfd vPollfd;
		#endif
	int vFileDescripterBits;
	int vErrorNumber;

		#ifdef CRX_RANDOM_SAFE__BLOCK_ON_DEV_RANDOM
    vFileDescripterBits = open("/dev/random", O_RDONLY);
	
    if(vFileDescripterBits == -1)
		{vErrorNumber = 0;}
	else
	{
		int tReturnOfPoll = -1;

		vPollfd.fd = vFileDescripterBits;
		vPollfd.events = POLLIN;
		vPollfd.revents = 0;
		
		tReturnOfPoll = poll(&vPollfd, 1, -1);
		
		while(tReturnOfPoll < 0 && (errno == EINTR || errno == EAGAIN))
			{tReturnOfPoll = poll(&vPollfd, 1, -1);}

		if(tReturnOfPoll != 1)
		{
			(void) close(vFileDescripterBits);
			errno = EIO;

			vErrorNumber = -1;
		}
		else
			{vErrorNumber = close(vFileDescripterBits);}
	}
		#else
	vErrorNumber = 0;
		#endif

	
	if(vErrorNumber != 0)
		{return -1;}
	else
	{
		/* LCOV_EXCL_START */
		struct stat tStat;
		const char * vDevices[] = {"/dev/urandom", "/dev/random", NULL};
		const char * * tDevice = vDevices;

		while (*tDevice != NULL)
		{
			vFileDescripterBits = open(*tDevice, O_RDONLY);

			if(vFileDescripterBits != -1)
			{
				if(fstat(vFileDescripterBits, &tStat) == 0 &&
						CRX__C__RANDOM__SAFE__PRIVATE__DO_ISNAM_AND_ISCHR(tStat))
				{
		#if defined(F_SETFD) && defined(FD_CLOEXEC)
					(void) fcntl(vFileDescripterBits, F_SETFD, fcntl(vFileDescripterBits, F_GETFD) | FD_CLOEXEC);
		#endif
					return vFileDescripterBits;
				}
				else
					{(void) close(vFileDescripterBits);}
			}
			else if(errno == EINTR)
				{}
			else
				{tDevice++;}
		}

		errno = EIO;

		return -1;
	}
}
CRX__LIB__PRIVATE_C_FUNCTION() int crx_c_random_safeRandom_private_callLinuxGetRandom(
		Crx_C_Random_SafeRandom * pThis, void * pBuffer, size_t pLength)
{
		#if(CRX__C__RANDOM__SAFE__PRIVATE__HAS_LINUX_COMPATIBLE_GETRANDOM)
    unsigned char * buf = (unsigned char *) pBuffer;
    size_t chunk_size = 256U;

    do
	{
		int readnb;

        if (pLength < chunk_size)
		{
            chunk_size = pLength;
            assert(chunk_size > (size_t) 0U);
        }
		
		assert(pLength <= 256U);

		do
		{
			readnb = CRX__C__RANDOM__SAFE__GET_RANDOM(buf, pLength, 0);
		} while (readnb < 0 && (errno == EINTR || errno == EAGAIN));

        if(((readnb == (int) pLength) - 1) != 0)
			{return -1;}
		else
		{
			pLength -= chunk_size;
			buf += chunk_size;
		}
    } while (pLength > (size_t) 0U);

    return 0;
		#else
	return -1;
		#endif
}
	#else
CRX__LIB__PRIVATE_C_FUNCTION() unsigned int crx_c_random_safeRandom_private_callWindowsRtlGenRandom(
		Crx_C_Random_SafeRandom * pThis, void * pBuffer, size_t pLength)
{
	//REFERENCE: https://cpp.hotexamples.com/examples/-/-/RtlGenRandom/cpp-rtlgenrandom-function-examples.html
	HMODULE vHandle = GetModuleHandle(TEXT("advapi32.dll"));
	bool vIsDone = false;

	if(vHandle != NULL)
	{
		BOOLEAN (APIENTRY *tRtlGenRandom)(void *, ULONG) =
				(BOOLEAN (APIENTRY *)(void *, ULONG))GetProcAddress(vHandle, TEXT("SystemFunction036"));

		if(tRtlGenRandom != NULL)
		{
			if(tRtlGenRandom(pBuffer, pLength))
			{
				//PRE WINXP SP3 THIS FUNCTION HAD A VULNERABILITY. THE FOLLOWING IS IN HOPE TO 
				//		MAKE IT SAFER.
		#if(NTDDI_VERSION < NTDDI_WINXPSP3)
				size_t tLength = 0;

				while((tLength + 4) <= pLength)
				{
					*(pBuffer + tLength) = crx_c_random_mersenneTwister_getRandomUnsignedInt32(
							&(pThis->gPrivate_mersenneTwister)) ^ (*(pBuffer + tLength));

					tLength = tLength + sizeof(unsigned int);
				}
		#endif
				vIsDone = true;
			}
		}
	}

	//PRE WINDOWS XP SP3 WE USE THE SLOWER API BECAUSE SystemFunction036 DID NOT EXIST. NOTE
	//		THAT IT IS ASSUMED THAT THIS API DOES NOT HAVE A VULNERABILITY
	if(!vIsDone)
	{
		/*FOR BETTER COMPATIBILITY WITH WINDOWS 95.*/
		#if(defined(WIN32_LEAN_AND_MEAN) && defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0400))
		HCRYPTPROV tHCryptProv;

		if(CryptAcquireContext(&tHCryptProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
		{
			if(CryptGenRandom(tHCryptProv, pLength, (BYTE *)pBuffer))
				{vIsDone = true;}
			
			CryptReleaseContext(tHCryptProv, 0);
		}

		#else

		size_t tLength = 0;
		uint32_t tUnsignedInt32;
		unsigned char * tUnsignedChars = (unsigned char *)pBuffer;

		while((tLength + 4) <= pLength)
		{
			tUnsignedInt32 = crx_c_random_isaac_getRandomUnsignedInt32(&(pThis->gPrivate_isaac)) ^
					crx_c_random_mersenneTwister_getRandomUnsignedInt32(
					&(pThis->gPrivate_mersenneTwister));

			*(tUnsignedChars + tLength) = *(((unsigned char *)(&tUnsignedInt32)));
			*(tUnsignedChars + tLength + 1) = *(((unsigned char *)(&tUnsignedInt32)) + 1);
			*(tUnsignedChars + tLength + 2) = *(((unsigned char *)(&tUnsignedInt32)) + 2);
			*(tUnsignedChars + tLength + 3) = *(((unsigned char *)(&tUnsignedInt32)) + 3);

			tLength = tLength + 4;
		}
		
		if(tLength < pLength)
		{
			size_t tI = 0;

			tUnsignedInt32 = crx_c_random_isaac_getRandomUnsignedInt32(&(pThis->gPrivate_isaac)) ^
					crx_c_random_mersenneTwister_getRandomUnsignedInt32(
					&(pThis->gPrivate_mersenneTwister));

			for(tI = 0; tI < pLength - tLength; tI++)
				{*(tUnsignedChars + tLength + tI) = *(((unsigned char *)(&tUnsignedInt32)) + tI);}
			
			/*WARNING: POTENTIAL WASTE OF RANDOM BYTES HERE COULD BE A SECURITY THREAT*/
		}
		#endif
	}

	return vIsDone;
}
	#endif

CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_random_safeRandom_private_setup(
		Crx_C_Random_SafeRandom * pThis)
{
	#ifndef _WIN32
    const int errno_save = errno;
	unsigned char fodder[16];
	bool vReturn = true;

	if(crx_c_random_safeRandom_private_callLinuxGetRandom(pThis, fodder, sizeof fodder) == 0)
	{
		pThis->gPrivate_isLinuxGetRandomAvailable = true;

		errno = errno_save;
	}
	else
	{
		pThis->gPrivate_isLinuxGetRandomAvailable = false;
		pThis->gPrivate_randomDataSourceFileDescriptorBits = 
				crx_c_random_safeRandom_private_openLinuxRandomSource(pThis);

		if(pThis->gPrivate_randomDataSourceFileDescriptorBits == -1)
			{vReturn = false;}

		errno = errno_save;
	}

	return vReturn;
	#else
	return true;
	#endif
}
CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_random_safeRandom_private_closeRandomSource(
		Crx_C_Random_SafeRandom * pThis)
{
    bool vReturn = false;

	#ifndef _WIN32
    if((pThis->gPrivate_randomDataSourceFileDescriptorBits != -1) &&
			(close(pThis->gPrivate_randomDataSourceFileDescriptorBits) == 0))
	{
        pThis->gPrivate_randomDataSourceFileDescriptorBits = -1;
        pThis->gPrivate_isInitialized = false;
        vReturn = true;
    }

    if(pThis->gPrivate_isLinuxGetRandomAvailable)
		{vReturn = true;}

	#else
    if(pThis->gPrivate_isInitialized)
	{
        pThis->gPrivate_isInitialized = false;
        vReturn = true;
    }
	#endif

    return vReturn;
}
#endif

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_random_safeRandom_getRandomBytes(
		Crx_C_Random_SafeRandom * pThis, void * const pBuffer, const size_t pLength)
{
#if(CRX__C__RANDOM__SAFE__PRIVATE__HAS_NATIVE_ARC4RANDOM)
	arc4random_buf(buf, size); 

	return true;
#else
	bool vReturn = true;

	#if defined(ULLONG_MAX) && defined(SIZE_MAX)
		#if SIZE_MAX > ULLONG_MAX
    /* coverity[result_independent_of_operands] */
    assert(pLength <= ULLONG_MAX);
		#endif
	#endif
	
    if(!pThis->gPrivate_isInitialized)
	{
		if(crx_c_random_safeRandom_private_setup(pThis))
			{pThis->gPrivate_isInitialized = true;}
	}

	if(pThis->gPrivate_isInitialized)
	{
	#ifndef _WIN32
		if(pThis->gPrivate_isLinuxGetRandomAvailable)
		{
			if(crx_c_random_safeRandom_private_callLinuxGetRandom(pThis, pBuffer, pLength) != 0)
				{vReturn = false;}
		}
		else
		{
			if(pThis->gPrivate_randomDataSourceFileDescriptorBits == -1)
				{vReturn = false;}
			else
			{
				CRX_SCOPE_META
				assert(pLength > ((size_t)0u));
				assert(pLength <= SSIZE_MAX);

				CRX_SCOPE
				unsigned char * tBuffer = (unsigned char *) pBuffer;
				ssize_t tNumberOfBytesRead = -1;
				ssize_t tLength = (ssize_t)pLength;

				while(true)
				{
					tNumberOfBytesRead = read(pThis->gPrivate_randomDataSourceFileDescriptorBits, 
							tBuffer, (size_t)tLength);

					while((tNumberOfBytesRead < ((ssize_t)0)) && 
							(errno == EINTR || errno == EAGAIN)) /* LCOV_EXCL_LINE */
					{
						tNumberOfBytesRead = read(pThis->gPrivate_randomDataSourceFileDescriptorBits, 
								tBuffer, (size_t)tLength);
					}

					if(tNumberOfBytesRead < (ssize_t) 0)
						{}
					else if(tNumberOfBytesRead == (ssize_t) 0)
						{break; /* LCOV_EXCL_LINE */}

					tLength -= (size_t) tNumberOfBytesRead;
					tBuffer += tNumberOfBytesRead;
					
					if(tLength < (ssize_t) 0)
						{break;}
				}
				
				tNumberOfBytesRead = ((ssize_t) (tBuffer - (unsigned char *) pBuffer));
							
				if(tNumberOfBytesRead != (ssize_t) tLength)
					{vReturn = false;}
				CRX_SCOPE_END
			}
		}
	#else
		if(pLength > (size_t) 0xffffffffUL)
			{vReturn = false;}
		else if(!crx_c_random_safeRandom_private_callWindowsRtlGenRandom(pThis, (PVOID) pBuffer, 
				(ULONG) pLength))
			{vReturn = false;}
	#endif
	}

	crx_c_random_safeRandom_private_closeRandomSource(pThis);
	
	return vReturn;
#endif
}
CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_random_safeRandom_getRandomUnsignedInt32(
		Crx_C_Random_SafeRandom * pThis)
{
#if(CRX__C__RANDOM__SAFE__PRIVATE__HAS_NATIVE_ARC4RANDOM)
	return arc4random();
#else
    uint32_t r;

    crx_c_random_safeRandom_getRandomBytes(pThis, &r, sizeof r);

    return r;
#endif
}
CRX__LIB__PUBLIC_C_FUNCTION() double crx_c_random_safeRandom_getRandomDouble(
		Crx_C_Random_SafeRandom * pThis)
	{return((double)crx_c_random_safeRandom_getRandomUnsignedInt32(pThis) / (uint32_t)0xffffffff);}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_safeRandom_destruct(Crx_C_Random_SafeRandom * pThis)
{
#if(!CRX__C__RANDOM__SAFE__PRIVATE__HAS_NATIVE_ARC4RANDOM)
	crx_c_random_safeRandom_private_closeRandomSource(pThis);
#endif
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_safeRandom_free(Crx_C_Random_SafeRandom * pThis)
	{free(pThis);}

#undef CRX__C__RANDOM__SAFE__PRIVATE__HAS_LINUX_COMPATIBLE_GETRANDOM
#undef CRX__C__RANDOM__SAFE__GET_RANDOM


CRX__LIB__C_CODE_END()

