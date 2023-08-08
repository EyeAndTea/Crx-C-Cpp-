#if(!defined(CRX__C__RANDOM__CHA_CHA___h__))
#define CRX__C__RANDOM__CHA_CHA___h__

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

//REFERENCE: https://cr.yp.to/chacha.html
//REFERENCE: https://github.com/vnmakarov/mum-hash/blob/master/src/chacha-prng.h

/*
 * Specify which key and IV sizes are supported by your cipher. A user
 * should be able to enumerate the supported sizes by running the
 * following code:
 *
 * for (i = 0; ECRYPT_KEYSIZE(i) <= ECRYPT_MAXKEYSIZE; ++i)
 *   {
 *     keysize = ECRYPT_KEYSIZE(i);
 *
 *     ...
 *   }
 *
 * All sizes are in bits.
 */

/*#define ECRYPT_MAXKEYSIZE 256                 /* [edit] * /
#define ECRYPT_KEYSIZE(i) (128 + (i)*128)     /* [edit] * /

#define ECRYPT_MAXIVSIZE 64                   /* [edit] * /
#define ECRYPT_IVSIZE(i) (64 + (i)*64)        /* [edit] * / */

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
typedef struct Crx_C_Random_ChaCha
{
  uint32_t gPrivate_input[16]; /* could be compressed */
  uint32_t gPrivate_output[16];
  char gPrivate_sigma[32];
  char gPrivate_tau[32];
  int gPrivate_index;
} Crx_C_Random_ChaCha;

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_chaCha_construct(Crx_C_Random_ChaCha * pThis, 
		uint32_t pSeed);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_chaCha_construct2(Crx_C_Random_ChaCha * pThis, 
		uint32_t pSeed01, uint32_t pSeed02, uint32_t pSeed03, uint32_t pSeed04, uint32_t pSeed05, 
		uint32_t pSeed06, uint32_t pSeed07, uint32_t pSeed08, uint32_t pSeed09, uint32_t pSeed10);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_ChaCha * crx_c_random_chaCha_new(uint32_t pSeed);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_ChaCha * crx_c_random_chaCha_new2(uint32_t pSeed01, 
		uint32_t pSeed02, uint32_t pSeed03, uint32_t pSeed04, uint32_t pSeed05, uint32_t pSeed06,
		uint32_t pSeed07, uint32_t pSeed08, uint32_t pSeed09, uint32_t pSeed10);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_ChaCha * crx_c_random_chaCha_moveNew(
		Crx_C_Random_ChaCha * pChaCha);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_ChaCha * crx_c_random_chaCha_copyNew(
		Crx_C_Random_ChaCha const * pChaCha);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_chaCha_seed(Crx_C_Random_ChaCha * pThis, 
		uint32_t pSeed01, uint32_t pSeed02, uint32_t pSeed03, uint32_t pSeed04, 
		uint32_t pSeed05, uint32_t pSeed06, uint32_t pSeed07, uint32_t pSeed08, 
		uint32_t pSeed09, uint32_t pSeed10);

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_random_chaCha_private_setupKey(Crx_C_Random_ChaCha * pThis, 
		const uint8_t * pKey, uint32_t pKeyBitSize, uint32_t pIvBitSize);
/*
 * "IV setup. After having called crx_c_random_chaCha_private_setupKey(), the user is
 * allowed to call crx_c_random_chaCha_private_setupIv() different times in order to
 * encrypt/decrypt different messages with the same key but different
 * IV's."
 */
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_random_chaCha_private_setupIv(Crx_C_Random_ChaCha * pThis, 
		const uint8_t * pIv);

/*
 * Encryption/decryption of arbitrary length messages.
 *
 * For efficiency reasons, the API provides two types of
 * encrypt/decrypt functions. The crx_c_random_chaCha_private_encryptBytes() function
 * (declared here) encrypts byte strings of arbitrary length, while
 * the ECRYPT_encrypt_blocks() function (defined later) only accepts
 * lengths which are multiples of ECRYPT_BLOCKLENGTH.
 * 
 * The user is allowed to make multiple calls to
 * ECRYPT_encrypt_blocks() to incrementally encrypt a long message,
 * but he is NOT allowed to make additional encryption calls once he
 * has called crx_c_random_chaCha_private_encryptBytes() (unless he starts a new message
 * of course). For example, this sequence of calls is acceptable:
 *
 * crx_c_random_chaCha_private_setupKey();
 *
 * crx_c_random_chaCha_private_setupIv();
 * ECRYPT_encrypt_blocks();
 * ECRYPT_encrypt_blocks();
 * crx_c_random_chaCha_private_encryptBytes();
 *
 * crx_c_random_chaCha_private_setupIv();
 * ECRYPT_encrypt_blocks();
 * ECRYPT_encrypt_blocks();
 *
 * crx_c_random_chaCha_private_setupIv();
 * crx_c_random_chaCha_private_encryptBytes();
 * 
 * The following sequence is not:
 *
 * crx_c_random_chaCha_private_setupKey();
 * crx_c_random_chaCha_private_setupIv();
 * ECRYPT_encrypt_blocks();
 * crx_c_random_chaCha_private_encryptBytes();
 * ECRYPT_encrypt_blocks();
 */

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_random_chaCha_private_encryptBytes(
		Crx_C_Random_ChaCha * ctx, const uint8_t* plaintext, uint8_t* ciphertext, 
		uint32_t msglen); /* Message length in bytes. */ 
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_random_chaCha_private_encryptBytes__doWordToByte(
		uint8_t * pOutput/*pOutput[64]*/, const uint32_t * pInput /*pInput[16]*/);
		
CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_random_chaCha_getRandomUnsignedInt32(
		Crx_C_Random_ChaCha * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() double crx_c_random_chaCha_getRandomDouble(
		Crx_C_Random_ChaCha * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_chaCha_free(Crx_C_Random_ChaCha * pThis);

/*void ECRYPT_decrypt_bytes(Crx_C_Random_ChaCha * ctx, const uint8_t* ciphertext, 
  uint8_t* plaintext, uint32_t msglen);                /* Message length in bytes. */ 

/* 
 * For testing purposes it can sometimes be useful to have a function
 * which immediately generates keystream without having to provide it
 * with a zero plaintext. If your cipher cannot provide this function
 * (e.g., because it is not strictly a synchronous cipher), please
 * reset the ECRYPT_GENERATES_KEYSTREAM flag.
 * /
#define ECRYPT_GENERATES_KEYSTREAM
#ifdef ECRYPT_GENERATES_KEYSTREAM
void ECRYPT_keystream_bytes(Crx_C_Random_ChaCha * ctx, uint8_t* keystream, uint32_t length); /* Length of keystream in bytes. * /
#endif */

/*
 * Encryption/decryption of blocks.
 * 
 * By default, these functions are defined as macros. If you want to
 * provide a different implementation, please undef the
 * ECRYPT_USES_DEFAULT_BLOCK_MACROS flag and implement the functions
 * declared below.
 */
/*
#define ECRYPT_BLOCKLENGTH 64                  /* [edit] * /


#define ECRYPT_encrypt_blocks(ctx, plaintext, ciphertext, blocks)  \
  crx_c_random_chaCha_private_encryptBytes(ctx, plaintext, ciphertext,                 \
    (blocks) * ECRYPT_BLOCKLENGTH)

#define ECRYPT_decrypt_blocks(ctx, ciphertext, plaintext, blocks)  \
  ECRYPT_decrypt_bytes(ctx, ciphertext, plaintext,                 \
    (blocks) * ECRYPT_BLOCKLENGTH)

#ifdef ECRYPT_GENERATES_KEYSTREAM

#define ECRYPT_keystream_blocks(ctx, keystream, blocks)            \
  ECRYPT_keystream_bytes(ctx, keystream,                        \
    (blocks) * ECRYPT_BLOCKLENGTH)

#endif
*/

CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/random/ChaCha.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif
