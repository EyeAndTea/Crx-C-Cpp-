#if(!defined(CRX__NON_CRXED__BOOST__RANDOM__MT19937___h__))
#define CRX__NON_CRXED__BOOST__RANDOM__MT19937___h__

#if(defined(_MSC_VER) && (_MSC_VER <= 1200))
	#define CRX__NON_CRXED__BOOST__RANDOM__MT19937__IS_AVAILABLE CRM__FALSE
#else
	#include "boost/random/mersenne_twister.hpp"

	#define CRX__NON_CRXED__BOOST__RANDOM__MT19937__IS_AVAILABLE CRM__TRUE
#endif

namespace crx
{
	namespace nonCrxed
	{
		namespace boost
		{
			namespace random
			{
#if(CRX__NON_CRXED__BOOST__RANDOM__MT19937__IS_AVAILABLE)
	#if(defined(BOOST_VERSION) && (BOOST_VERSION > 104601))
				typedef ::boost::random::mt19937 Mt19937;
	#else
				typedef ::boost::mt19937 Mt19937;
	#endif
#endif
			}
		}
	}
}

#endif