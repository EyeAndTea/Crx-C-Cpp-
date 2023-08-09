#if(!defined(CRX__CLASS_UNORDERED_MAP___h__))
#define CRX__CLASS_UNORDERED_MAP___h__
#pragma once

#include <boost/version.hpp>
#include "Crx/H/crx/crx.h"
#if(defined(CRX__BOOST_NO_CXX11_HDR_UNORDERED_MAP) && (BOOST_VERSION >= 103600))
	#define CRX__CLASS_UNORDERED_MAP__IS_AVAILABLE CRXM__TRUE
	//#include CRX__TO_STRING2(CRX__CONFIG__BOOST_PATH/unordered_map.hpp)	WORKS BUT LIKELY UNSTABLE.
	#include "boost/unordered_map.hpp"
#else
	#define CRX__CLASS_UNORDERED_MAP__IS_AVAILABLE CRXM__TRUE

	#include <unordered_map>
#endif


#if(defined(CRX__BOOST_NO_CXX11_HDR_UNORDERED_MAP) && (BOOST_VERSION >= 103600))
	#define CRX__CLASS_UNORDERED_MAP(pKeyType, pValueType) boost::unordered_map<pKeyType, pValueType>
	//#define CRX__CLASS_UNORDERED_MAP_ITERATOR(pKeyType, pValueType) CRX__CLASS_UNORDERED_MAP(pKeyType, pValueType)::iterator
#else
	#if(defined(_STLP_UNORDERED_MAP))
		#define CRX__CLASS_UNORDERED_MAP(pKeyType, pValueType) stlport::tr1::unordered_map<pKeyType, pValueType>
	#else
		#define CRX__CLASS_UNORDERED_MAP(pKeyType, pValueType) std::unordered_map<pKeyType, pValueType>
		//#define CRX__CLASS_UNORDERED_MAP(pKeyType, pValueType) std::unordered_map<pKeyType, pValueType>::iterator
	#endif
#endif



namespace crx
{
#if(CRX__CLASS_UNORDERED_MAP__IS_AVAILABLE)
	template<typename T1, typename T2>
			struct ClassUnorderedMap
	{
		typedef CRX__CLASS_UNORDERED_MAP(T1, T2) t;
	};

	//C++11
	//template<typename T1, typename T2>
	//using HashTable2 = CRX__CLASS_UNORDERED_MAP(T1, T2);

	template<typename T1 = std::string>
			struct AssociativeArray
	{
		typedef CRX__CLASS_UNORDERED_MAP(std::string, T1) t;
	};
#endif
}

#endif