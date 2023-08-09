//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/random/MersenneTwister.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()



/**
* Creates a new random number generator from a given seed.
*/
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_mersenneTwister_construct(
		Crx_C_Random_MersenneTwister * pThis, uint32_t pSeedNumber)
{
	CRX__SET_TO_ZERO(Crx_C_Random_MersenneTwister, *pThis);
	crx_c_random_mersenneTwister_private_doSeedRand(pThis, pSeedNumber);
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_MersenneTwister * crx_c_random_mersenneTwister_new(
		uint32_t pSeedNumber)
{
	Crx_C_Random_MersenneTwister * vReturn = 
			((Crx_C_Random_MersenneTwister *)malloc(sizeof(Crx_C_Random_MersenneTwister)));

	if(vReturn != NULL)
		{crx_c_random_mersenneTwister_construct(vReturn, pSeedNumber);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_MersenneTwister * crx_c_random_mersenneTwister_moveNew(
		Crx_C_Random_MersenneTwister * pMersenneTwister)
{
	Crx_C_Random_MersenneTwister * vReturn = (Crx_C_Random_MersenneTwister *)(calloc(1,
			sizeof(Crx_C_Random_MersenneTwister)));

	if(vReturn != NULL)
		{memcpy(vReturn, pMersenneTwister, sizeof(Crx_C_Random_MersenneTwister));}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_MersenneTwister * crx_c_random_mersenneTwister_copyNew(
		Crx_C_Random_MersenneTwister const * pMersenneTwister)
{
	Crx_C_Random_MersenneTwister * vReturn = (Crx_C_Random_MersenneTwister *)(calloc(1,
			sizeof(Crx_C_Random_MersenneTwister)));

	if(vReturn != NULL)
		{memcpy(vReturn, pMersenneTwister, sizeof(Crx_C_Random_MersenneTwister));}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_mersenneTwister_destruct(Crx_C_Random_MersenneTwister * pThis)
	{}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_mersenneTwister_free(Crx_C_Random_MersenneTwister * pThis)
	{free(pThis);}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_random_mersenneTwister_private_doSeedRand(
		Crx_C_Random_MersenneTwister * pThis, uint32_t pSeedNumber)
{
  /* set initial seeds to gPrivate_stateBuffer[CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_LENGTH] using the generator
   * from Line 25 of Table 1 in: Donald Knuth, "The Art of Computer
   * Programming," Vol. 2 (2nd Ed.) pp.102.
   */
  pThis->gPrivate_stateBuffer[0] = pSeedNumber & 0xffffffff;
  for(pThis->gPrivate_index=1; pThis->gPrivate_index<CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_LENGTH; pThis->gPrivate_index++) {
    pThis->gPrivate_stateBuffer[pThis->gPrivate_index] = (6069 * pThis->gPrivate_stateBuffer[pThis->gPrivate_index-1]) & 0xffffffff;
  }
}
	
/**
 * Generates a pseudo-randomly generated long.
 */
uint32_t crx_c_random_mersenneTwister_getRandomUnsignedInt32(Crx_C_Random_MersenneTwister * pThis) {

  uint32_t y;
  static uint32_t mag[2] = {0x0, 0x9908b0df}; /* mag[x] = x * 0x9908b0df for x = 0,1 */
  if(pThis->gPrivate_index >= CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_LENGTH || pThis->gPrivate_index < 0) {
    /* generate CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_LENGTH words at a time */
    int kk;
    if(pThis->gPrivate_index >= CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_LENGTH+1 || pThis->gPrivate_index < 0) {
      crx_c_random_mersenneTwister_private_doSeedRand(pThis, 4357);
    }
    for(kk=0; kk<CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_LENGTH-CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_M; kk++) {
      y = (pThis->gPrivate_stateBuffer[kk] & CRX__C__RANDOM__MERSENNE_TWISTER__UPPER_MASK) | (pThis->gPrivate_stateBuffer[kk+1] & CRX__C__RANDOM__MERSENNE_TWISTER__LOWER_MASK);
      pThis->gPrivate_stateBuffer[kk] = pThis->gPrivate_stateBuffer[kk+CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_M] ^ (y >> 1) ^ mag[y & 0x1];
    }
    for(; kk<CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_LENGTH-1; kk++) {
      y = (pThis->gPrivate_stateBuffer[kk] & CRX__C__RANDOM__MERSENNE_TWISTER__UPPER_MASK) | (pThis->gPrivate_stateBuffer[kk+1] & CRX__C__RANDOM__MERSENNE_TWISTER__LOWER_MASK);
      pThis->gPrivate_stateBuffer[kk] = pThis->gPrivate_stateBuffer[kk+(CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_M-CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_LENGTH)] ^ (y >> 1) ^ mag[y & 0x1];
    }
    y = (pThis->gPrivate_stateBuffer[CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_LENGTH-1] & CRX__C__RANDOM__MERSENNE_TWISTER__UPPER_MASK) | (pThis->gPrivate_stateBuffer[0] & CRX__C__RANDOM__MERSENNE_TWISTER__LOWER_MASK);
    pThis->gPrivate_stateBuffer[CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_LENGTH-1] = pThis->gPrivate_stateBuffer[CRX__C__RANDOM__MERSENNE_TWISTER__STATE_VECTOR_M-1] ^ (y >> 1) ^ mag[y & 0x1];
    pThis->gPrivate_index = 0;
  }
  y = pThis->gPrivate_stateBuffer[pThis->gPrivate_index++];
  y ^= (y >> 11);
  y ^= (y << 7) & CRX__C__RANDOM__MERSENNE_TWISTER__TEMPERING_MASK_B;
  y ^= (y << 15) & CRX__C__RANDOM__MERSENNE_TWISTER__TEMPERING_MASK_C;
  y ^= (y >> 18);
  return y;
}

/**
 * Generates a pseudo-randomly generated double in the range [0..1].
 */
CRX__LIB__PUBLIC_C_FUNCTION() double crx_c_random_mersenneTwister_getRandomDouble(
		Crx_C_Random_MersenneTwister * pThis)
	{return((double)crx_c_random_mersenneTwister_getRandomUnsignedInt32(pThis) / (uint32_t)0xffffffff);}

CRX__LIB__C_CODE_END()

