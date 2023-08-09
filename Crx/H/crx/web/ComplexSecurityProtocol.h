#if(!defined(CRX__WEB__COMPLEX_SECURITY_PROTOCOL___h__))
#define CRX__WEB__COMPLEX_SECURITY_PROTOCOL___h__
#pragma once

#include <boost/version.hpp>
#include "Crx/H/crx/crx.h"
#pragma push_macro("CRX__LIB__MODE")
#undef CRX__LIB__MODE
#if(!defined(CRX__CONFIG__MODE))
	#define CRX__CONFIG__MODE CRX__LIB__MODE__STAND_ALONE
#endif
#define CRX__LIB__MODE CRX__CONFIG__MODE
//<<START>>	INCLUDE ".h" OF NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE.
#include <string>
#include "Crx/H/crx/web/Security.h"
#include "Crx/H/crx/web/SecurityProtocol.h"
//<<END>>


namespace crx{namespace web
{
	class ComplexSecurityProtocol : public SecurityProtocol
	{
		private: ::std::vector<SecurityProtocol> gSecurityProtocols /*= ::std::vector<SecurityProtocol>()*/;
		private: bool gWasBaseSecurityProtocolAdded; /*= false*/;
		private: bool gIsToAllowRemovingProtocols /*= false*/;
		private: ::crx::Var gLockKey /*= ?*/;
		
		
		public function ComplexSecurityProtocol::ComplexSecurityProtocol(int = -1);
		public function ComplexSecurityProtocol::ComplexSecurityProtocol(
				SecurityProtocol * pSecurityProtocol, bool pIsToAllowRemovingProtocols = false,
				::crx::Var pLockKey = -1);

		public function crxConstruct(int pMode, SecurityProtocol * pSecurityProtocol = NULL, 
				bool pIsToAllowRemovingProtocols = false, ::crx::Var pLockKey = -1);

		public final ComplexSecurityProtocol::pushSecurityProtocol(SecurityProtocol * CRX_NOT_NULL pSecurityProtocol);
		public final ComplexSecurityProtocol::popSecurityProtocol(::crx::Var pLockKey = -1);

		protected: virtual bool doFilterHtmlElement(bool pIsNotComplexMode, Security * CRX_NOT_NULL const pSecurity, 
				Security_ElementData * CRX_NOT_NULL pElementData, 
				::pugi::xml_node const & pNode);
		protected: virtual bool doFilterHtmlAttributeAndValue(bool pIsNotComplexMode, 
				Security * CRX_NOT_NULL pSecurity, ::std::string const & pElementName,
				Security_AttributeData * CRX_NOT_NULL pAttributeData);
		protected: virtual std::string doSieveHtmlElementText(bool pIsNotComplexMode, 
				Security * CRX_NOT_NULL pSecurity, ::std::string const & pElementName,
				::std::string const & pText, bool pIsCDATA);

		protected: virtual bool doFilterCrxCssAtRuleElement(bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleElementData * CRX_NOT_NULL pCrxCssAtRuleElementData);
		protected: virtual bool doFilterCrxCssAtRuleStatement(bool pIsNotComplexMode, 
				Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleStatementData * CRX_NOT_NULL pCrxCssAtRuleStatementData);
		protected: virtual bool doFilterCrxCssAtRuleNameValueBlock(bool pIsNotComplexMode, 
				Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleNameValueBlockData * CRX_NOT_NULL pCrxCssAtRuleNameValueBlockData);
		protected: virtual bool doFilterCrxCssNameValuePair(bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssNameValuePairData * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::string const & pAtRuleName, ::std::string const & pAtRuleValue);
		protected: virtual bool doFilterCrxCssNameValuePair2(bool pIsNotComplexMode,
				Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssNameValuePairData * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::vector<Security_CrxCssReference> const & pReferences);
		protected: virtual bool doFilterCrxCssReferenceNameValueBlock(bool pIsNotComplexMode, 
				Security * CRX_NOT_NULL pSecurity,
				Security_CrxCssReferenceNameValueBlockData * CRX_NOT_NULL pCrxCssReferenceNameValueBlockData);
	}
}}
	

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .cpp.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/CPP.H/crx/web/ComplexSecurityProtocol.cpp.h"
#endif
#pragma pop_macro("CRX__LIB__MODE")	

#endif