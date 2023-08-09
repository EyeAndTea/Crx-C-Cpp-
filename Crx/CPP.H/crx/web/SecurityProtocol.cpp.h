//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .cpp FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE.
#include "Crx/H/crx/web/SecurityProtocol.h"

#include "Crx/H/crx/web/Security.h"
//<<END>>


namespace crx{namespace web
{
	#pragma region CLASS SecurityProtocol //{

		CRX_PUBLIC SecurityProtocol::SecurityProtocol(bool pIsComplexMode CRX_DEFAULT(false))
			{this->gIsNotComplexMode = !pIsComplexMode;}

		CRX_PUBLIC bool SecurityProtocol::isNotComplexMode()
			{return this->gIsNotComplexMode;}
		CRX_PROTECTED void SecurityProtocol::setComplexMode(bool pIsComplexMode CRX_DEFAULT(false))
			{this->gIsNotComplexMode = !pIsComplexMode;}

		CRX_PUBLIC bool SecurityProtocol::filterHtmlElement(Security * CRX_NOT_NULL const pSecurity, 
				Security_ElementData * CRX_NOT_NULL pElementData, 
				::pugi::xml_node const & pNode)
			{return this->doFilterHtmlElement(true, pSecurity, pElementData, pNode);}
		CRX_PUBLIC bool SecurityProtocol::filterHtmlAttributeAndValue(Security * CRX_NOT_NULL pSecurity, 
				::std::string const & pElementName, Security_AttributeData * CRX_NOT_NULL pAttributeData)
		{
			return this->doFilterHtmlAttributeAndValue(true, pSecurity, pElementName, 
					pAttributeData);
		}
		CRX_PUBLIC ::std::string SecurityProtocol::sieveHtmlElementText(Security * CRX_NOT_NULL pSecurity, 
				::std::string const & pElementName, ::std::string const & pText, bool pIsCDATA)
			{return this->doSieveHtmlElementText(true, pSecurity, pElementName, pText, pIsCDATA);}

		CRX_PUBLIC bool SecurityProtocol::filterCrxCssAtRuleElement(Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleElementData * CRX_NOT_NULL pCrxCssAtRuleElementData)
			{return this->doFilterCrxCssAtRuleElement(true, pSecurity, pCrxCssAtRuleElementData);}
		CRX_PUBLIC bool SecurityProtocol::filterCrxCssAtRuleStatement(Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleStatementData * CRX_NOT_NULL pCrxCssAtRuleStatementData)
			{return this->doFilterCrxCssAtRuleStatement(true, pSecurity, pCrxCssAtRuleStatementData);}
		CRX_PUBLIC bool SecurityProtocol::filterCrxCssAtRuleNameValueBlock(Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleNameValueBlockData * CRX_NOT_NULL pCrxCssAtRuleNameValueBlockData)
		{
			return this->doFilterCrxCssAtRuleNameValueBlock(true, pSecurity, 
					pCrxCssAtRuleNameValueBlockData);
		}
		CRX_PUBLIC bool SecurityProtocol::filterCrxCssNameValuePair(Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssNameValuePairData  * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::string const & pAtRuleName, ::std::string const & pAtRuleValue)
		{
			return this->doFilterCrxCssNameValuePair(true, pSecurity, pCrxCssNameValuePairData, 
					pAtRuleName, pAtRuleValue);
		}
		CRX_PUBLIC bool SecurityProtocol::filterCrxCssNameValuePair2(Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssNameValuePairData  * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::vector<Security_CrxCssReference> const & pReferences)
		{
			return this->doFilterCrxCssNameValuePair2(true, pSecurity, pCrxCssNameValuePairData, 
					pReferences);
		}
		CRX_PUBLIC bool SecurityProtocol::filterCrxCssReferenceNameValueBlock(Security * CRX_NOT_NULL pSecurity,
				Security_CrxCssReferenceNameValueBlockData * CRX_NOT_NULL pCrxCssReferenceNameValueBlockData)
		{
			return this->doFilterCrxCssReferenceNameValueBlock(true, pSecurity, 
					pCrxCssReferenceNameValueBlockData);
		}

	#pragma endregion CLASS SecurityProtocol //}
}}


