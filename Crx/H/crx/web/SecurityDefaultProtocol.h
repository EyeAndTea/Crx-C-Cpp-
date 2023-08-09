#if(!defined(CRX__WEB__SECURITY_DEFAULT_PROTOCOL___h__))
#define CRX__WEB__SECURITY_DEFAULT_PROTOCOL___h__
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
#include "Crx/H/crx/ClassUnorderedMap.h"
#include "Crx/H/crx/Var.h"
#include "Crx/H/crx/web/SecurityProtocol.h"
//<<END>>

class ::crx::web::Security;
class ::crx::web::Security_ElementData;
class ::crx::web::Security_AttributeData;
class ::crx::web::Security_CrxCssAtRuleElementData;
class ::crx::web::Security_CrxCssAtRuleStatementData;
class ::crx::web::Security_CrxCssAtRuleNameValueBlockData;
class ::crx::web::Security_CrxCssNameValuePairData;
class ::crx::web::Security_CrxCssReferenceNameValueBlockData;

namespace crx{namespace web
{
	class SecurityDefaultProtocol : public SecurityProtocol
	{
		protected: ::crx::VarThreadPossible gDefaultImplementation_htmlFilterData /*= ::crx::VarThreadPossible()*/;
		protected: ::crx::VarThreadPossible gDefaultImplementation_cssFilterData /*= ::crx::VarThreadPossible()*/;

		public: SecurityDefaultProtocol(bool pIsComplexMode = false);

		protected: virtual bool doFilterHtmlElement(bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				Security_ElementData * CRX_NOT_NULL pElementData, 
				::pugi::xml_node const & pNode);
		protected: virtual bool doFilterHtmlAttributeAndValue(bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				::std::string const & pElementName, Security_AttributeData * CRX_NOT_NULL pAttributeData);
		protected: virtual std::string doSieveHtmlElementText(bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				::std::string const & pElementName, ::std::string const & pText, bool pIsCDATA);

		protected: virtual bool doFilterCrxCssAtRuleElement(bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleElementData * CRX_NOT_NULL pCrxCssAtRuleElementData);
		protected: virtual bool doFilterCrxCssAtRuleStatement(bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleStatementData * CRX_NOT_NULL pCrxCssAtRuleStatementData);
		protected: virtual bool doFilterCrxCssAtRuleNameValueBlock(bool pIsNotComplexMode, 
				Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleNameValueBlockData * CRX_NOT_NULL pCrxCssAtRuleNameValueBlockData);
		protected: virtual bool doFilterCrxCssNameValuePair(bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssNameValuePairData * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::string const & pAtRuleName, ::std::string const & pAtRuleValue);
		protected: virtual bool doFilterCrxCssNameValuePair2(bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssNameValuePairData * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::vector<Security_CrxCssReference> const & pReferences);
		protected: virtual bool doFilterCrxCssReferenceNameValueBlock(bool pIsNotComplexMode, 
				Security * CRX_NOT_NULL pSecurity,
				Security_CrxCssReferenceNameValueBlockData * CRX_NOT_NULL pCrxCssReferenceNameValueBlockData);
	};
}}

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .cpp.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/CPP.H/crx/web/SecurityDefaultProtocol.cpp.h"
#endif
#pragma pop_macro("CRX__LIB__MODE")

#endif