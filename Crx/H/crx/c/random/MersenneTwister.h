#if(!defined(CRX__C__RANDOM__MERSENNE_TWISTER__h__))
#define CRX__C__RANDOM__MERSENNE_TWISTER__h__

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
#include <stdlib.h>
#include "Crx/H/crx/nonCrxed/standard/stdint.h"
#include <string.h>
//<<END>>

CRX__LIB__C_CODE_BEGIN()

/* An implementation of the MT19937 Algorithm for the Mersenne Twister
 * by Evan Sultanik.  Based upon the pseudocode in: M. Matsumoto and
 * T. Nishimura, "Mersenne Twister: A 623-dimensionally
 * equidistributed uniform pseudorandom number generator," ACM
 * Transactions on Modeling and Computer Simulation Vol. 8, No. 1,
 * January pp.3-30 1998.
 *
 * http://www.sultanik.com/Mersenne_twister
 */

#define CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_LENGTH 624
/* changes to CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_LENGTH also require changes to this */
#define CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_M      397

#define CRX__C__RANDOM__MERSENNE_TWISTER__UPPER_MASK		0x80000000
#define CRX__C__RANDOM__MERSENNE_TWISTER__LOWER_MASK		0x7fffffff
#define CRX__C__RANDOM__MERSENNE_TWISTER__TEMPERING_MASK_B	0x9d2c5680
#define CRX__C__RANDOM__MERSENNE_TWISTER__TEMPERING_MASK_C	0xefc60000

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
typedef struct Crx_C_Random_MersenneTwister
{
  uint32_t gPrivate_stateBuffer[CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_LENGTH];
  int gPrivate_index;
} Crx_C_Random_MersenneTwister;

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_mersenneTwister_construct(Crx_C_Random_MersenneTwister * pThis,
		uint32_t pSeedNumber);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_MersenneTwister * crx_c_random_mersenneTwister_new(uint32_t pSeed);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_MersenneTwister * crx_c_random_mersenneTwister_moveNew(
		Crx_C_Random_MersenneTwister * pMersenneTwister);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_MersenneTwister * crx_c_random_mersenneTwister_copyNew(
		Crx_C_Random_MersenneTwister const * pMersenneTwister);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_mersenneTwister_destruct(Crx_C_Random_MersenneTwister * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_mersenneTwister_free(Crx_C_Random_MersenneTwister * pThis);

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_random_mersenneTwister_private_doSeedRand(
		Crx_C_Random_MersenneTwister * pThis, uint32_t pSeedNumber);

CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_random_mersenneTwister_getRandomUnsignedInt32(
		Crx_C_Random_MersenneTwister * rand);
CRX__LIB__PUBLIC_C_FUNCTION() double crx_c_random_mersenneTwister_getRandomDouble(
		Crx_C_Random_MersenneTwister * pThis);

CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/random/MersenneTwister.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif
		
#endif
