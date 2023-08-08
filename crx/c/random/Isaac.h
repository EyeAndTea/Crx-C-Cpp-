#if(!defined(CRX__C__RANDOM__ISAAC___h__))
#define CRX__C__RANDOM__ISAAC___h__

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
//<<END>>

CRX__LIB__C_CODE_BEGIN()

/*
------------------------------------------------------------------------------
rand.h: definitions for a random number generator
By Bob Jenkins, 1996, Public Domain
MODIFIED:
  960327: Creation (addition of randinit, really)
  970719: use context, not global variables, for internal state
  980324: renamed seed to flag
  980605: recommend CRX_C_RANDOM_ISAAC_RANDSIZL=4 for noncryptography.
  010626: note this is public domain
------------------------------------------------------------------------------
*/
#define CRX_C_RANDOM_ISAAC_RANDSIZL   (8)
#define CRX_C_RANDOM_ISAAC_RANDSIZ    (1<<CRX_C_RANDOM_ISAAC_RANDSIZL)

/* context of random number generator */
typedef struct Crx_C_Random_Isaac
{
  uint32_t gPrivaye_count;
  uint32_t gPrivate_randrsl[CRX_C_RANDOM_ISAAC_RANDSIZ];
  uint32_t gPrivate_randmem[CRX_C_RANDOM_ISAAC_RANDSIZ];
  uint32_t gPrivate_randa;
  uint32_t gPrivate_randb;
  uint32_t gPrivate_randc;
} Crx_C_Random_Isaac;

/*
------------------------------------------------------------------------------
 If (flag==TRUE), then use the contents of gPrivate_randrsl[0..CRX_C_RANDOM_ISAAC_RANDSIZ-1] as the seed.
------------------------------------------------------------------------------
*/
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_isaac_construct(Crx_C_Random_Isaac *ctx, uint32_t flag);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_isaac_construct2(Crx_C_Random_Isaac * pThis, uint32_t pSeed1,
		uint32_t pSeed2, uint32_t pSeed3, uint32_t pSeed4, uint32_t pSeed5,
		uint32_t pSeed6, uint32_t pSeed7, uint32_t pSeed8);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_Isaac * crx_c_random_isaac_new(uint32_t flag);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_Isaac * crx_c_random_isaac_new2(uint32_t pSeed1,
		uint32_t pSeed2, uint32_t pSeed3, uint32_t pSeed4, uint32_t pSeed5,
		uint32_t pSeed6, uint32_t pSeed7, uint32_t pSeed8);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_Isaac * crx_c_random_isaac_moveNew(
		Crx_C_Random_Isaac * pIsaac);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_Isaac * crx_c_random_isaac_copyNew(
		Crx_C_Random_Isaac const * pIsaac);
		
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_random_isaac_computeNext(Crx_C_Random_Isaac * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_random_isaac_getRandomUnsignedInt32(Crx_C_Random_Isaac * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() double crx_c_random_isaac_getRandomDouble(Crx_C_Random_Isaac * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_isaac_free(Crx_C_Random_Isaac * pThis);


/*
------------------------------------------------------------------------------
 Call CRX_C_RANDOM_ISAAC_GET_RANDOM_UINT32(/o_ randctx *r _o/) to retrieve a single 32-bit random value
------------------------------------------------------------------------------
*/
/*#define CRX_C_RANDOM_ISAAC_GET_RANDOM_UINT32(r) \
   (!(r)->gPrivaye_count-- ? \
     (isaac(r), (r)->gPrivaye_count=CRX_C_RANDOM_ISAAC_RANDSIZ-1, (r)->gPrivate_randrsl[(r)->gPrivaye_count]) : \
     (r)->gPrivate_randrsl[(r)->gPrivaye_count])*/

CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/random/Isaac.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif