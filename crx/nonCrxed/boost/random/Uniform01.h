#if(!defined(CRX__NON_CRXED__BOOST__RANDOM__UNIFORM01___h__))
#define CRX__NON_CRXED__BOOST__RANDOM__UNIFORM01___h__

#if(defined(_MSC_VER) && (_MSC_VER <= 1200))
	#define CRX__NON_CRXED__BOOST__RANDOM__UNIFORM01__IS_AVAILABLE CRM__FALSE
#else
	#include "boost/random/uniform_01.hpp"

	#define CRX__NON_CRXED__BOOST__RANDOM__UNIFORM01__IS_AVAILABLE CRM__TRUE
#endif


namespace crx
{
	namespace nonCrxed
	{
		namespace boost
		{
			namespace random
			{
#if(CRX__NON_CRXED__BOOST__RANDOM__UNIFORM01__IS_AVAILABLE)
				template<class UniformRandomNumberGenerator, class RealType>
				class Uniform01
				{
	#if(defined(BOOST_VERSION) && (BOOST_VERSION > 104601))
					public: typedef ::boost::random::uniform_01<UniformRandomNumberGenerator, RealType> t;
	#else
					public: typedef ::boost::uniform_01<UniformRandomNumberGenerator, RealType> t;
	#endif
				};
#endif
			}
		}
	}
}

#endif