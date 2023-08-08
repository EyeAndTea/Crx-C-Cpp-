#if(!defined(CRX__NON_CRXED__BOOST__RANDOM__MERSENNE_TWISTER___h__))
#define CRX__NON_CRXED__BOOST__RANDOM__MERSENNE_TWISTER___h__

#if(defined(_MSC_VER) && (_MSC_VER <= 1200))
	#define CRX__NON_CRXED__BOOST__RANDOM__MERSENNE_TWISTER__IS_AVAILABLE CRM__FALSE
#else
	#include "boost/random/mersenne_twister.hpp"
	#include "Crx/H/crx/nonCrxed/boost/random/Mt19937.h"
	#include "Crx/H/crx/nonCrxed/boost/random/Mt11213b.h"

	#define CRX__NON_CRXED__BOOST__RANDOM__MERSENNE_TWISTER__IS_AVAILABLE CRM__TRUE
#endif


namespace crx
{
	namespace nonCrxed
	{
		namespace boost
		{
			namespace random
			{
#if(CRX__NON_CRXED__BOOST__RANDOM__MERSENNE_TWISTER__IS_AVAILABLE)
				template<class UIntType, int w, int n, int m, int r, UIntType a, int u,
						int s, UIntType b, int t, UIntType c, int l, UIntType val>
				class MersenneTwister
				{				
					public: typedef ::boost::random::mersenne_twister<UIntType, w, n, m, r, 
							a, u, s, b, t, c, l, val> t;
				};
#endif
			}
		}
	}
}

#endif