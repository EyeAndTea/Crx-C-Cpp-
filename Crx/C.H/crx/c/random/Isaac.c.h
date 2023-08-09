//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/random/Isaac.h"

#include <string.h>
#include <stdlib.h>
//<<END>>

CRX__LIB__C_CODE_BEGIN()

/*
------------------------------------------------------------------------------
rand.c: By Bob Jenkins.  My random number generator, ISAAC.  Public Domain
MODIFIED:
  960327: Creation (addition of randinit, really)
  970719: use context, not global variables, for internal state
  980324: make a portable version
  010626: Note this is public domain
  100725: Mask on use of >32 bits, not on assignment: from Paul Eggert
------------------------------------------------------------------------------
*/

#define CRX_C_RANDOM_ISAAC_IND(mm,x)  ((mm)[(x>>2)&(CRX_C_RANDOM_ISAAC_RANDSIZ-1)])
#define CRX_C_RANDOM_ISAAC_RNGSTEP(mix,a,b,mm,m,m2,r,x) \
{ \
  x = *m;  \
  a = ((a^(mix)) + *(m2++)); \
  *(m++) = y = (CRX_C_RANDOM_ISAAC_IND(mm,x) + a + b); \
  *(r++) = b = (CRX_C_RANDOM_ISAAC_IND(mm,y>>CRX_C_RANDOM_ISAAC_RANDSIZL) + x) & 0xffffffff; \
}
#define CRX_C_RANDOM_ISAAC_MIX(a,b,c,d,e,f,g,h) \
{ \
   a^=b<<11;              d+=a; b+=c; \
   b^=(c&0xffffffff)>>2;  e+=b; c+=d; \
   c^=d<<8;               f+=c; d+=e; \
   d^=(e&0xffffffff)>>16; g+=d; e+=f; \
   e^=f<<10;              h+=e; f+=g; \
   f^=(g&0xffffffff)>>4;  a+=f; g+=h; \
   g^=h<<8;               b+=g; h+=a; \
   h^=(a&0xffffffff)>>9;  c+=h; a+=b; \
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_isaac_construct(Crx_C_Random_Isaac * pThis, 
		uint32_t pSeed)
{
	crx_c_random_isaac_construct2(pThis, pSeed, pSeed, pSeed, pSeed, pSeed,
			pSeed, pSeed, pSeed);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_isaac_construct2(Crx_C_Random_Isaac * pThis, 
		uint32_t pSeed1, uint32_t pSeed2, uint32_t pSeed3, uint32_t pSeed4, uint32_t pSeed5,
		uint32_t pSeed6, uint32_t pSeed7, uint32_t pSeed8)
{
   size_t tI;
   //uint32_t a,b,c,d,e,f,g,h;
   uint32_t * m,*r;

   m=pThis->gPrivate_randmem;
   r=pThis->gPrivate_randrsl;
   
   CRX__SET_TO_ZERO(Crx_C_Random_Isaac, (*pThis));

   //a=b=c=d=e=f=g=h=0x9e3779b9;  /* the golden ratio */

   for(tI=0; tI<4; ++tI)          /* scramble it */
   {
     CRX_C_RANDOM_ISAAC_MIX(pSeed1,pSeed2,pSeed3,pSeed4,pSeed5,pSeed6,pSeed7,pSeed8);
   }

   for(tI=0; tI<CRX_C_RANDOM_ISAAC_RANDSIZ; tI+=8)
   {
     /* fill in mm[] with messy stuff */
     CRX_C_RANDOM_ISAAC_MIX(pSeed1,pSeed2,pSeed3,pSeed4,pSeed5,pSeed6,pSeed7,pSeed8);
     m[tI  ]=pSeed1; m[tI+1]=pSeed2; m[tI+2]=pSeed3; m[tI+3]=pSeed4;
     m[tI+4]=pSeed5; m[tI+5]=pSeed6; m[tI+6]=pSeed7; m[tI+7]=pSeed8;
   }

   crx_c_random_isaac_computeNext(pThis);         /* fill in the first set of results */
   //pThis->gPrivaye_count=CRX_C_RANDOM_ISAAC_RANDSIZ;  				/* prepare to use the first set of results */
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_Isaac * crx_c_random_isaac_new(uint32_t pSeed)
{
	Crx_C_Random_Isaac * vReturn = 
			((Crx_C_Random_Isaac *)malloc(sizeof(Crx_C_Random_Isaac)));

	if(vReturn != NULL)
		{crx_c_random_isaac_construct(vReturn, pSeed);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_Isaac * crx_c_random_isaac_new2(uint32_t pSeed1,
		uint32_t pSeed2, uint32_t pSeed3, uint32_t pSeed4, uint32_t pSeed5,
		uint32_t pSeed6, uint32_t pSeed7, uint32_t pSeed8)
{
	Crx_C_Random_Isaac * vReturn = 
			((Crx_C_Random_Isaac *)malloc(sizeof(Crx_C_Random_Isaac)));

	if(vReturn != NULL)
	{
		crx_c_random_isaac_construct2(vReturn, pSeed1, pSeed2, pSeed3, pSeed4, pSeed5,
				pSeed6, pSeed7, pSeed8);
	}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_Isaac * crx_c_random_isaac_moveNew(
		Crx_C_Random_Isaac * pIsaac)
{
	Crx_C_Random_Isaac * vReturn = (Crx_C_Random_Isaac *)(calloc(1,
			sizeof(Crx_C_Random_Isaac)));

	if(vReturn != NULL)
		{memcpy(vReturn, pIsaac, sizeof(Crx_C_Random_Isaac));}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Random_Isaac * crx_c_random_isaac_copyNew(
		Crx_C_Random_Isaac const * pIsaac)
{
	Crx_C_Random_Isaac * vReturn = (Crx_C_Random_Isaac *)(calloc(1,
			sizeof(Crx_C_Random_Isaac)));

	if(vReturn != NULL)
		{memcpy(vReturn, pIsaac, sizeof(Crx_C_Random_Isaac));}

	return vReturn;
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_random_isaac_computeNext(Crx_C_Random_Isaac * pThis)
{
   uint32_t a,b,x,y,*m,*mm,*m2,*r,*mend;
   mm=pThis->gPrivate_randmem; r=pThis->gPrivate_randrsl;
   a = pThis->gPrivate_randa; b = pThis->gPrivate_randb + (++pThis->gPrivate_randc);
   for (m = mm, mend = m2 = m+(CRX_C_RANDOM_ISAAC_RANDSIZ/2); m<mend; )
   {
      CRX_C_RANDOM_ISAAC_RNGSTEP( a<<13, a, b, mm, m, m2, r, x);
      CRX_C_RANDOM_ISAAC_RNGSTEP( (a & 0xffffffff) >>6 , a, b, mm, m, m2, r, x);
      CRX_C_RANDOM_ISAAC_RNGSTEP( a<<2 , a, b, mm, m, m2, r, x);
      CRX_C_RANDOM_ISAAC_RNGSTEP( (a & 0xffffffff) >>16, a, b, mm, m, m2, r, x);
   }
   for (m2 = mm; m2<mend; )
   {
      CRX_C_RANDOM_ISAAC_RNGSTEP( a<<13, a, b, mm, m, m2, r, x);
      CRX_C_RANDOM_ISAAC_RNGSTEP( (a & 0xffffffff) >>6 , a, b, mm, m, m2, r, x);
      CRX_C_RANDOM_ISAAC_RNGSTEP( a<<2 , a, b, mm, m, m2, r, x);
      CRX_C_RANDOM_ISAAC_RNGSTEP( (a & 0xffffffff) >>16, a, b, mm, m, m2, r, x);
   }
   pThis->gPrivate_randb = b; pThis->gPrivate_randa = a;
   pThis->gPrivaye_count = CRX_C_RANDOM_ISAAC_RANDSIZ;
}

CRX__LIB__PUBLIC_C_FUNCTION() uint32_t crx_c_random_isaac_getRandomUnsignedInt32(
		Crx_C_Random_Isaac * pThis)
{
	//SEE CRX_C_RANDOM_ISAAC_GET_RANDOM_UINT32()
	pThis->gPrivaye_count = pThis->gPrivaye_count - 1;

	if(pThis->gPrivaye_count == 0)
	{
		crx_c_random_isaac_computeNext(pThis);
		pThis->gPrivaye_count = CRX_C_RANDOM_ISAAC_RANDSIZ;
	}

	return pThis->gPrivate_randrsl[pThis->gPrivaye_count - 1];
}
CRX__LIB__PUBLIC_C_FUNCTION() double crx_c_random_isaac_getRandomDouble(Crx_C_Random_Isaac * pThis)
	{return((double)crx_c_random_isaac_getRandomUnsignedInt32(pThis) / (uint32_t)0xffffffff);}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_random_isaac_free(Crx_C_Random_Isaac * pThis)
	{free(pThis);}

#ifdef NEVER
int main()
{
  uint32_t i,j;
  Crx_C_Random_Isaac ctx;
  ctx.gPrivate_randa=ctx.gPrivate_randb=ctx.gPrivate_randc=(uint32_t)0;
  for (i=0; i<256; ++i) ctx.gPrivate_randrsl[i]=(uint32_t)0;
  randinit(&ctx, true);
  for (i=0; i<2; ++i)
  {
    isaac(&ctx);
    for (j=0; j<256; ++j)
    {
      printf("%.8lx",ctx.gPrivate_randrsl[j]);
      if ((j&7)==7) printf("\n");
    }
  }
}
#endif


CRX__LIB__C_CODE_END()

