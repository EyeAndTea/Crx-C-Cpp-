#if(!defined(CRX__NON_CRXED__STANDARD__MATH___h__))
#define CRX__NON_CRXED__STANDARD__MATH___h__

#include "math.h"


/*
THE FOLLOWING FOR INFINITY AND NAN ASSUMES IEEE754
STRICTLY SPEAKING, THERE IS NO SAFE WAY OF DEFINING INFINITY AND NAN
*/
#if(!defined(INFINITY))
	//REFERENCE VS2017. NOTE NUMBER 1e+300 IS PICKED TO BE LARGE ENOUGH TO OVERFLOW.
	//		CAUSES WARNINGS (C4056 AND C4756 UNDER VS6)
	#define INFINITY   ((float)(1e+300 * 1e+300))
	//#define INFINITY   (static_cast<float>(1e+300 * 1e+300))
	//
	//#define INFINITY (-logf(0.0));
	//
	//
	//PROBLEM: REQUIRES GLOBAL VARIABLES
	//static int inf = 0x7F800000;
	//static int _crx_noncrxed_standard_math__inf = 0x7F800000;
	//#define INFINITY (*((float *) &_crx_noncrxed_standard_math__inf))
	//
	//
	//PROBLEM: 	CAN NOT BE USED AS CONSTANT. DID NOT WORK IN VS6
	//#define INFINITY strtod("Inf", NULL)
	//
	//
	//PROBLEM: COULD RAISE TRAPS. DID NOT WORK IN VS6
	//#define INFINITY(1.0 /0.0)
#endif
#if(!defined(NAN))
	//PROBLEM: DID NOT WORK IN VS6
	//#define NAN        ((float)(INFINITY * 0.0F))
	//
	//PROBLEM: REQUIRES GLOBAL VARIABLES
	//static int _crx_noncrxed_standard_math__nan = 0x7F800001;  //SIGNALLING NAN IT SEEMS
	static int _crx_noncrxed_standard_math__nan = 0x7fc00000;
	#define NAN (*((float *) &_crx_noncrxed_standard_math__nan))
	//
	//
	//PROBLEM: 	CAN NOT BE USED AS CONSTANT. DID NOT WORK IN VS6
	//#define NAN strtod("NaN(0x7F800001)",0)
	//
	//
	//PROBLEM: COULD RAISE TRAPS. DID NOT WORK IN VS6
	//#define NAN (0.0/0.0)
#endif

#endif