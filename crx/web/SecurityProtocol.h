#if(!defined(CRX__WEB__SECURITY_PROTOCOL___h__))
#define CRX__WEB__SECURITY_PROTOCOL___h__
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
#include "pugixml/pugixml.hpp"
#include <list>
#include <vector>
//#include "Crx/H/crx/web/Security.h"
//<<END>>


namespace crx{namespace web
{
	class Security;
	class Security_ElementData;
	class Security_AttributeData;
	class Security_CrxCssAtRuleElementData;
	class Security_CrxCssAtRuleStatementData;
	class Security_CrxCssAtRuleNameValueBlockData;
	class Security_CrxCssNameValuePairData;
	class Security_CrxCssReference;
	class Security_CrxCssReferenceNameValueBlockData;

	class SecurityProtocol
	{
		private: bool gIsNotComplexMode /*= false*/;

		public: SecurityProtocol(bool pIsComplexMode = false);

		public: bool isNotComplexMode();
		protected: void setComplexMode(bool pIsComplexMode = false);
		protected: void pushComplexMode(bool pIsComplexMode = false);
		protected: bool popComplexMode();
		
		public: bool filterHtmlElement(Security * CRX_NOT_NULL const pSecurity, 
				Security_ElementData * CRX_NOT_NULL pElementData, 
				::pugi::xml_node const & pNode);
		public: bool filterHtmlAttributeAndValue(Security * CRX_NOT_NULL pSecurity, 
				::std::string const & pElementName, Security_AttributeData * CRX_NOT_NULL pAttributeData);
		public: std::string sieveHtmlElementText(Security * CRX_NOT_NULL pSecurity, 
				::std::string const & pElementName, ::std::string const & pText, bool pIsCDATA);

		/*public: virtual bool filterCSSCharset(Security * CRX_NOT_NULL pSecurity, ::std::string const & pCharset) = 0;
		public: virtual bool filterCSSImport(Security * CRX_NOT_NULL pSecurity, ::std::string * $pImport) = 0;
		public: virtual bool filterCssRule(Security * CRX_NOT_NULL pSecurity, ::std::string * $pRule) = 0;
		public: virtual bool filterCssSelector(Security * CRX_NOT_NULL pSecurity, ::std::string * pSelector) = 0;*/
		public: bool filterCrxCssAtRuleElement(Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleElementData * CRX_NOT_NULL pCrxCssAtRuleElementData);
		public: bool filterCrxCssAtRuleStatement(Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleStatementData * CRX_NOT_NULL pCrxCssAtRuleStatementData);
		public: bool filterCrxCssAtRuleNameValueBlock(Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleNameValueBlockData * CRX_NOT_NULL pCrxCssAtRuleNameValueBlockData);
		public: bool filterCrxCssNameValuePair(Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssNameValuePairData * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::string const & pAtRuleName, ::std::string const & pAtRuleValue);
		public: bool filterCrxCssNameValuePair2(Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssNameValuePairData * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::vector<Security_CrxCssReference> const & pReferences);
		public: bool filterCrxCssReferenceNameValueBlock(Security * CRX_NOT_NULL pSecurity,
				Security_CrxCssReferenceNameValueBlockData * CRX_NOT_NULL pCrxCssReferenceNameValueBlockData);

		protected: virtual bool doFilterHtmlElement(bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				Security_ElementData * CRX_NOT_NULL pElementData, 
				::pugi::xml_node const & pNode) = 0;
		protected: virtual bool doFilterHtmlAttributeAndValue(bool pIsNotComplexMode, 
				Security * CRX_NOT_NULL pSecurity, ::std::string const & pElementName,
				Security_AttributeData * CRX_NOT_NULL pAttributeData) = 0;
		protected: virtual std::string doSieveHtmlElementText(bool pIsNotComplexMode, 
				Security * CRX_NOT_NULL pSecurity, ::std::string const & pElementName,
				::std::string const & pText, bool pIsCDATA) = 0;

		protected: virtual bool doFilterCrxCssAtRuleElement(bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleElementData * CRX_NOT_NULL pCrxCssAtRuleElementData) = 0;
		protected: virtual bool doFilterCrxCssAtRuleStatement(bool pIsNotComplexMode, 
				Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleStatementData * CRX_NOT_NULL pCrxCssAtRuleStatementData) = 0;
		protected: virtual bool doFilterCrxCssAtRuleNameValueBlock(bool pIsNotComplexMode, 
				Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleNameValueBlockData * CRX_NOT_NULL pCrxCssAtRuleNameValueBlockData) = 0;
		protected: virtual bool doFilterCrxCssNameValuePair(bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssNameValuePairData * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::string const & pAtRuleName, ::std::string const & pAtRuleValue) = 0;
		protected: virtual bool doFilterCrxCssNameValuePair2(bool pIsNotComplexMode,
				Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssNameValuePairData * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::vector<Security_CrxCssReference> const & pReferences) = 0;
		protected: virtual bool doFilterCrxCssReferenceNameValueBlock(bool pIsNotComplexMode, 
				Security * CRX_NOT_NULL pSecurity,
				Security_CrxCssReferenceNameValueBlockData * CRX_NOT_NULL pCrxCssReferenceNameValueBlockData) = 0;
	};
}}


#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .cpp.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/CPP.H/crx/web/SecurityProtocol.cpp.h"
#endif
#pragma pop_macro("CRX__LIB__MODE")

#endif