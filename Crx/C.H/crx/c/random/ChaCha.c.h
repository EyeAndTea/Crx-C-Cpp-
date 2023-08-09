//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/random/ChaCha.h"

#include <string.h>
#include <stdlib.h>
//<<END>>

CRX__LIB__C_CODE_BEGIN()

/*
chacha-ref.c version 20080118
D. J. Bernstein
Public domain.
*/

#define CRX__C__RANDOM__CHA_CHA__U32V(v) ((uint32_t)(v) & 0xFFFFFFFFu)

#define CRX__C__RANDOM__CHA_CHA__ROTATE(v,c) (CRX__C__RANDOM__CHA_CHA__U32V((v) << (c)) | ((v) >> (32 - (c))))
#define CRX__C__RANDOM__CHA_CHA__XOR(v,w) ((v) ^ (w))
#define CRX__C__RANDOM__CHA_CHA__PLUS(v,w) (CRX__C__RANDOM__CHA_CHA__U32V((v) + (w)))
#define CRX__C__RANDOM__CHA_CHA__PLUSONE(v) (CRX__C__RANDOM__CHA_CHA__PLUS((v),1))

#define CRX__C__RANDOM__CHA_CHA__QUARTERROUND(a,b,c,d) \
  x[a] = CRX__C__RANDOM__CHA_CHA__PLUS(x[a],x[b]); x[d] = CRX__C__RANDOM__CHA_CHA__ROTATE(CRX__C__RANDOM__CHA_CHA__XOR(x[d],x[a]),16); \
  x[c] = CRX__C__RANDOM__CHA_CHA__PLUS(x[c],x[d]); x[b] = CRX__C__RANDOM__CHA_CHA__ROTATE(CRX__C__RANDOM__CHA_CHA__XOR(x[b],x[c]),12); \
  x[a] = CRX__C__RANDOM__CHA_CHA__PLUS(x[a],x[b]); x[d] = CRX__C__RANDOM__CHA_CHA__ROTATE(CRX__C__RANDOM__CHA_CHA__XOR(x[d],x[a]), 8); \
  x[c] = CRX__C__RANDOM__CHA_CHA__PLUS(x[c],x[d]); x[b] = CRX__C__RANDOM__CHA_CHA__ROTATE(CRX__C__RANDOM__CHA_CHA__XOR(x[b],x[c]), 7);

#if(defined(_CRX__C__RANDOM__CHA_CHA__BIG__ENDIAN))
	#define CRX__C__RANDOM__CHA_CHA__U32TO32_LITTLE(v) \
		(((CRX__C__RANDOM__CHA_CHA__U32V((v) << (8)) | ((v) >> (32 - (8)))) & 0x00FF00FFu) | \
		((CRX__C__RANDOM__CHA_CHA__U32V((v) << (24)) | ((v) >> (32 - (24)))) & 0xFF00FF00u))
#else
	#define CRX__C__RANDOM__CHA_CHA__U32TO32_LITTLE(v) (v)
#endif

#define CRX__C__RANDOM__CHA_CHA__U32TO8_LITTLE(p, v) (((uint32_t*)(p))[0] = CRX__C__RANDOM__CHA_CHA__U32TO32_LITTLE(v))
#define CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(p) CRX__C__RANDOM__CHA_CHA__U32TO32_LITTLE(((uint32_t*)(p))[0])


CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_chaCha_construct(Crx_C_Random_ChaCha * pThis, uint32_t pSeed)
	{crx_c_random_chaCha_construct2(pThis, pSeed, pSeed, 0, 0, 0, 0, 0, 0, 0, 0);}//CHOICE OF WHICH SEED IS USED IS ATRBITRAY
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_chaCha_construct2(Crx_C_Random_ChaCha * pThis, uint32_t pSeed01, 
		uint32_t pSeed02, uint32_t pSeed03, uint32_t pSeed04, uint32_t pSeed05, uint32_t pSeed06,
		uint32_t pSeed07, uint32_t pSeed08, uint32_t pSeed09, uint32_t pSeed10)
{
	CRX__SET_TO_ZERO(Crx_C_Random_ChaCha, (*pThis));

	//JUST RANDOM NUMBERS
	pThis->gPrivate_sigma[0] = 0x66u;
	pThis->gPrivate_sigma[1] = 0xD9u;
	pThis->gPrivate_sigma[2] = 0x6Au;
	pThis->gPrivate_sigma[3] = 0x2Fu;
	pThis->gPrivate_sigma[4] = 0x6Cu;
	pThis->gPrivate_sigma[5] = 0x5Du;
	pThis->gPrivate_sigma[6] = 0xE0u;
	pThis->gPrivate_sigma[7] = 0xCFu;
	pThis->gPrivate_sigma[8] = 0x14u;
	pThis->gPrivate_sigma[9] = 0xBEu;
	pThis->gPrivate_sigma[10] = 0x76u;
	pThis->gPrivate_sigma[11] = 0x68u;
	pThis->gPrivate_sigma[12] = 0x88u;
	pThis->gPrivate_sigma[13] = 0x88u;
	pThis->gPrivate_sigma[14] = 0x32u;
	pThis->gPrivate_sigma[15] = 0xB7u;

	//JUST RANDOM NUMBERS
	pThis->gPrivate_tau[0] = 0x10u;
	pThis->gPrivate_tau[1] = 0x49u;
	pThis->gPrivate_tau[2] = 0xB4u;
	pThis->gPrivate_tau[3] = 0xAAu;
	pThis->gPrivate_tau[4] = 0x95u;
	pThis->gPrivate_tau[5] = 0x39u;
	pThis->gPrivate_tau[6] = 0x97u;
	pThis->gPrivate_tau[7] = 0x07u;
	pThis->gPrivate_tau[8] = 0x3Au;
	pThis->gPrivate_tau[9] = 0x2Du;
	pThis->gPrivate_tau[10] = 0x44u;
	pThis->gPrivate_tau[11] = 0x24u;
	pThis->gPrivate_tau[12] = 0xD6u;
	pThis->gPrivate_tau[13] = 0x96u;
	pThis->gPrivate_tau[14] = 0x31u;
	pThis->gPrivate_tau[15] = 0x93u;
	
	crx_c_random_chaCha_seed(pThis, pSeed01, pSeed02, pSeed03, pSeed04, pSeed05, pSeed06,
			pSeed07, pSeed08, pSeed09, pSeed10);
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_ChaCha * crx_c_random_chaCha_new(uint32_t pSeed)
{
	Crx_C_Random_ChaCha * vReturn = 
			((Crx_C_Random_ChaCha *)malloc(sizeof(Crx_C_Random_ChaCha)));

	if(vReturn != NULL)
		{crx_c_random_chaCha_construct(vReturn, pSeed);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_ChaCha * crx_c_random_chaCha_new2(uint32_t pSeed01, 
		uint32_t pSeed02, uint32_t pSeed03, uint32_t pSeed04, uint32_t pSeed05, uint32_t pSeed06,
		uint32_t pSeed07, uint32_t pSeed08, uint32_t pSeed09, uint32_t pSeed10)
{
	Crx_C_Random_ChaCha * vReturn = 
			((Crx_C_Random_ChaCha *)malloc(sizeof(Crx_C_Random_ChaCha)));

	if(vReturn != NULL)
	{
		crx_c_random_chaCha_construct2(vReturn, pSeed01, pSeed02, pSeed03, pSeed04, pSeed05, pSeed06,
				pSeed07, pSeed08, pSeed09, pSeed10);
	}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_ChaCha * crx_c_random_chaCha_moveNew(
		Crx_C_Random_ChaCha * pChaCha)
{
	Crx_C_Random_ChaCha * vReturn = (Crx_C_Random_ChaCha *)(calloc(1,
			sizeof(Crx_C_Random_ChaCha)));

	if(vReturn != NULL)
		{memcpy(vReturn, pChaCha, sizeof(Crx_C_Random_ChaCha));}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_ChaCha * crx_c_random_chaCha_copyNew(
		Crx_C_Random_ChaCha const * pChaCha)
{
	Crx_C_Random_ChaCha * vReturn = (Crx_C_Random_ChaCha *)(calloc(1,
			sizeof(Crx_C_Random_ChaCha)));

	if(vReturn != NULL)
		{memcpy(vReturn, pChaCha, sizeof(Crx_C_Random_ChaCha));}

	return vReturn;
}


CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_chaCha_seed(Crx_C_Random_ChaCha * pThis, 
		uint32_t pSeed01, uint32_t pSeed02, uint32_t pSeed03, uint32_t pSeed04, 
		uint32_t pSeed05, uint32_t pSeed06, uint32_t pSeed07, uint32_t pSeed08, 
		uint32_t pSeed09, uint32_t pSeed10)
{
	uint8_t vK[32];
	uint8_t vIv[8];
	
	//NOTE: ENDIANESS IS EXPLICITLY NOT ADDRESSED HERE. REMEMBER, THE ALGORITHM IS BEING USED
	//		FOR RANDOM NUMBER GENERATION, NOT ENCRYPTION.
	*((uint32_t *)(&(vK[0]))) = pSeed01;
	*((uint32_t *)(&(vK[4]))) = pSeed02;
	*((uint32_t *)(&(vK[8]))) = pSeed03;
	*((uint32_t *)(&(vK[12]))) = pSeed04;
	*((uint32_t *)(&(vK[16]))) = pSeed05;
	*((uint32_t *)(&(vK[20]))) = pSeed06;
	*((uint32_t *)(&(vK[24]))) = pSeed07;
	*((uint32_t *)(&(vK[28]))) = pSeed08;
	*((uint32_t *)(&(vIv[0]))) = pSeed09;
	*((uint32_t *)(&(vIv[4]))) = pSeed10;
	
	crx_c_random_chaCha_private_setupKey(pThis, vK, 256, 0);
	crx_c_random_chaCha_private_setupIv(pThis, vIv);
	
	pThis->gPrivate_index = 16;
}

//BEGGINING PART OF _set_chacha_prng_key_iv with kbits set to 256
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_random_chaCha_private_setupKey(Crx_C_Random_ChaCha * pThis, 
		const uint8_t * pK, uint32_t kbits, uint32_t ivbits)
{
  const char *constants;

  pThis->gPrivate_input[4] = CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(pK + 0);
  pThis->gPrivate_input[5] = CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(pK + 4);
  pThis->gPrivate_input[6] = CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(pK + 8);
  pThis->gPrivate_input[7] = CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(pK + 12);
  if (kbits == 256) { /* recommended */
    pK += 16;
    constants = pThis->gPrivate_sigma;
  } else { /* kbits == 128 */
    constants = pThis->gPrivate_tau;
  }
  pThis->gPrivate_input[8] = CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(pK + 0);
  pThis->gPrivate_input[9] = CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(pK + 4);
  pThis->gPrivate_input[10] = CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(pK + 8);
  pThis->gPrivate_input[11] = CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(pK + 12);
  pThis->gPrivate_input[0] = CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(constants + 0);
  pThis->gPrivate_input[1] = CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(constants + 4);
  pThis->gPrivate_input[2] = CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(constants + 8);
  pThis->gPrivate_input[3] = CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(constants + 12);
}
//END PART OF _set_chacha_prng_key_iv
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_random_chaCha_private_setupIv(Crx_C_Random_ChaCha * pThis, 
		const uint8_t *iv)
{
  pThis->gPrivate_input[12] = 0;
  pThis->gPrivate_input[13] = 0;
  pThis->gPrivate_input[14] = CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(iv + 0);
  pThis->gPrivate_input[15] = CRX__C__RANDOM__CHA_CHA__U8TO32_LITTLE(iv + 4);
}

//PART OF get_chacha_prn
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_random_chaCha_private_encryptBytes(
		Crx_C_Random_ChaCha * pThis, const uint8_t *m, uint8_t *c, uint32_t bytes)
{
  uint8_t vOutput[64];
  //int i;

  //if (!bytes) return;
  //for (;;)
  while(true) {
    crx_c_random_chaCha_private_encryptBytes__doWordToByte(vOutput,pThis->gPrivate_input);
    pThis->gPrivate_input[12] = CRX__C__RANDOM__CHA_CHA__PLUSONE(pThis->gPrivate_input[12]);
    if (!pThis->gPrivate_input[12]) {
      pThis->gPrivate_input[13] = CRX__C__RANDOM__CHA_CHA__PLUSONE(pThis->gPrivate_input[13]);
      /* stopping at 2^70 bytes per nonce is user's responsibility */
    }
	break;
	/* ENCRYPTION CODE WHICH IS NOT NEEDED
    if (bytes <= 64) {
      for (i = 0;i < bytes;++i) c[i] = m[i] ^ vOutput[i];
      return;
    }
    for (i = 0;i < 64;++i) c[i] = m[i] ^ vOutput[i];
    bytes -= 64;
    c += 64;
    m += 64;
	*/
  }
  
  pThis->gPrivate_output[0] = *((uint32_t *)(&(vOutput[0])));
  pThis->gPrivate_output[1] = *((uint32_t *)(&(vOutput[4])));
  pThis->gPrivate_output[2] = *((uint32_t *)(&(vOutput[8])));
  pThis->gPrivate_output[3] = *((uint32_t *)(&(vOutput[12])));
  pThis->gPrivate_output[4] = *((uint32_t *)(&(vOutput[16])));
  pThis->gPrivate_output[5] = *((uint32_t *)(&(vOutput[20])));
  pThis->gPrivate_output[6] = *((uint32_t *)(&(vOutput[24])));
  pThis->gPrivate_output[7] = *((uint32_t *)(&(vOutput[28])));
  pThis->gPrivate_output[8] = *((uint32_t *)(&(vOutput[32])));
  pThis->gPrivate_output[9] = *((uint32_t *)(&(vOutput[36])));
  pThis->gPrivate_output[10] = *((uint32_t *)(&(vOutput[40])));
  pThis->gPrivate_output[11] = *((uint32_t *)(&(vOutput[44])));
  pThis->gPrivate_output[12] = *((uint32_t *)(&(vOutput[48])));
  pThis->gPrivate_output[13] = *((uint32_t *)(&(vOutput[52])));
  pThis->gPrivate_output[14] = *((uint32_t *)(&(vOutput[56])));
  pThis->gPrivate_output[15] = *((uint32_t *)(&(vOutput[60])));
}
//_chacha_prng_salsa20
CRX__LIB__PRIVATE_C_FUNCTION()  void crx_c_random_chaCha_private_encryptBytes__doWordToByte(
		uint8_t * pOutput/*pOutput[64]*/, const uint32_t * pInput /*pInput[16]*/)
{
  uint32_t x[16];
  int i;

  for (i = 0;i < 16;++i) x[i] = pInput[i];
  for (i = 8;i > 0;i -= 2) {
    CRX__C__RANDOM__CHA_CHA__QUARTERROUND( 0, 4, 8,12)
    CRX__C__RANDOM__CHA_CHA__QUARTERROUND( 1, 5, 9,13)
    CRX__C__RANDOM__CHA_CHA__QUARTERROUND( 2, 6,10,14)
    CRX__C__RANDOM__CHA_CHA__QUARTERROUND( 3, 7,11,15)
    CRX__C__RANDOM__CHA_CHA__QUARTERROUND( 0, 5,10,15)
    CRX__C__RANDOM__CHA_CHA__QUARTERROUND( 1, 6,11,12)
    CRX__C__RANDOM__CHA_CHA__QUARTERROUND( 2, 7, 8,13)
    CRX__C__RANDOM__CHA_CHA__QUARTERROUND( 3, 4, 9,14)
  }
  for (i = 0;i < 16;++i) x[i] = CRX__C__RANDOM__CHA_CHA__PLUS(x[i],pInput[i]);
  for (i = 0;i < 16;++i) CRX__C__RANDOM__CHA_CHA__U32TO8_LITTLE(pOutput + 4 * i,x[i]);
}

CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_random_chaCha_getRandomUnsignedInt32(Crx_C_Random_ChaCha * pThis)
{
	if(pThis->gPrivate_index >= 16)
	{
		crx_c_random_chaCha_private_encryptBytes(pThis, NULL, NULL, 0);
		pThis->gPrivate_index = 0;
	}
	
	pThis->gPrivate_index = pThis->gPrivate_index + 1;
		
	return pThis->gPrivate_output[pThis->gPrivate_index - 1];
}
CRX__LIB__PUBLIC_C_FUNCTION() double crx_c_random_chaCha_getRandomDouble(Crx_C_Random_ChaCha * pThis)
	{return((double)crx_c_random_chaCha_getRandomUnsignedInt32(pThis) / (uint32_t)0xffffffff);}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_chaCha_free(Crx_C_Random_ChaCha * pThis)
	{free(pThis);}

/*
void ECRYPT_decrypt_bytes(Crx_C_Random_ChaCha * x,const uint8_t *c,uint8_t *m,uint32_t bytes)
{
  crx_c_random_chaCha_private_encryptBytes(x,c,m,bytes);
}

void ECRYPT_keystream_bytes(Crx_C_Random_ChaCha * x,uint8_t *stream,uint32_t bytes)
{
  uint32_t i;
  for (i = 0;i < bytes;++i) stream[i] = 0;
  crx_c_random_chaCha_private_encryptBytes(x,stream,stream,bytes);
}*/


CRX__LIB__C_CODE_END()
