#if(!defined(CRX__NON_CRXED__BOOST__RANDOM__RANDOM_DEVICE___h__))
#define CRX__NON_CRXED__BOOST__RANDOM__RANDOM_DEVICE___h__

#if(defined(BOOST_VERSION))
	#if(BOOST_VERSION >= 104300)
		#include "boost/random/random_device.hpp"

		#define CRX__NON_CRXED__BOOST__RANDOM__RANDOM_DEVICE__IS_AVAILABLE CRXM__TRUE
	#else
		//THE FOLLOWING CONDITION IS FROM BOOST SOURCE
		//PRE BOOST 1.43 THERE IS NO SUPPORT FOR WINDOWS
		#if(defined(__linux__) && (!defined(__GNUC__) || !defined(_CXXRT_STD_NAME)))
			#include "boost/nondet_random.hpp"

			#define CRX__NON_CRXED__BOOST__RANDOM__RANDOM_DEVICE__IS_AVAILABLE CRXM__TRUE
		#else
			#define CRX__NON_CRXED__BOOST__RANDOM__RANDOM_DEVICE__IS_AVAILABLE CRXM__FALSE
		#endif
	#endif
#else
	#define CRX__NON_CRXED__BOOST__RANDOM__RANDOM_DEVICE__IS_AVAILABLE CRXM__FALSE
#endif

namespace crx
{
	namespace nonCrxed
	{
		namespace boost
		{
			namespace random
			{
#if(CRX__NON_CRXED__BOOST__RANDOM__RANDOM_DEVICE__IS_AVAILABLE)
	#if(BOOST_VERSION > 104601)
				typedef ::boost::random::random_device RandomDevice;
	#else
				typedef ::boost::random_device RandomDevice;
	#endif
#endif
			}
		}
	}
}

#endif