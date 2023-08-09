//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .cpp FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE.
#include "Crx/H/crx/web/ComplexSecurityProtocol.h"

#include "Crx/H/crx/web/Security.h"
#include "Crx/H/crx/web/SecurityProtocol.h"
//<<END>>

namespace crx{namespace web
{
	#pragma region CLASS SecurityProtocol //{
		/*
		ONE OF THE FUNDAMENTAL ISSUES THAT THE VAR TYPE WAS SUPPOSED TO FIX IS THE FOLLOWING
		AND UNFORTUANETLY IT FAILED. IT WAS PROVEN THAT IF THE VAR TYPE WAS TO HAVE A 'NULL'
		INTERNAL TYPE, IT MUST HAVE AN 'UNDEFINED' INTERNAL TYPE. THIS IS NEEDED FOR LANGUAGES
		THAT DO NOT SUPPORT FUNCTION OVERLOADING, BUT ALSO DO NOT SUPPORT SELECTIVELY PASSING
		N PARAMETERS, LIKE PHP, BUT DO ALLOW EXPLICIT SETTING OF A DEFAULT. (THIS IS UNLIKE
		JAVASCRIPT WHERE IT DOES SUPPORT SELECTIVELY PASSING PARAMETERS, BUT NOT UNTILL RECENTLY,
		DID NOT SUPPORT PARAMETER DEFAULTS YET THERE WAS A DEFAULT, THE 'undefined'.) IN SUCH
		A CASE A DEFAULT VALUE WOULD BE NEEDED TO DETECT IF NO PARAMETER WAS ACTUALLY PASSED BY 
		THE CALLER. HOWEVER IF THIS DEFAULT VALUE IS ALSO A VALID VALUE TO PASS, THEN THERE
		ANOTHER 'VALUE' WOULD BE REQUIRED OUTSIDE THE SPACE OF THE TYPE. THEREFOR, IF NULL
		IS VALID, THEN NULL CAN NOT BE USED, AND UNDEFINED, AS DEFINED IN MY STANDARD, CAN BE
		USED. HENCE, IN THE PHP SIDE '-1' WAS USED TO MEAN undefined, BECAUSE PER MY STANDARD
		IT WAS NOT ALLOWED TO BE PASSED BY CALLING CODE BECAUSE THE TYPE THERE IS 
		"CrxSecurityProtocol" WHICH IS FORMALLY A SMART POINTER IN MY STANDARD TO THAT TYPE. IN THE
		JAVASCRIPT SIDE, JAVASCRIPT'S undefined WAS USED.

		HOWEVER, COMING BACK TO THIS, WHICH IN THE PAST I AVOIDED BY SIMPLY NOT IMPLEMENTING THIS CLASS
		AT ALL, I FIND THAT CONDITION ABOUT NULL AND UNDEFINED IS NOT SUFFICIENT. FOR POINTER TYPES
		IN PARTICULAR, IF NULL IS ALLOWED AS A PARAMETER FOR A SPECIFIC FUNCTION, THERE REMAINS
		THE REQUIREMENT THAT THE VAR TYPE CAN GIVE CODE THE TYPE IT NEEDS FROM THE POINTER THE VAR
		IS HOLDING. UNFORTUANETLY, THE VAR TYPE CAN NOT, BECAUSE IT CAN ONLY GIVE THE POINTER
		UNDER THE TYPE IT IS REGISTERED UNDER, AND DOES NOT SUPPORT TRACING THE CLASS CHAIN. INCIDENTALLY,
		DO NOT CONFUSE NULL WITH POINTER. NULL HERE IS AS DEFINED IN MY STANDARD. REMEMBER VAR DID NOT
		HAVE THE INTERNAL 'POINTER' TYPE INITIALLY. HOWEVER, IT IS NOW APPARANT THAT THIS INTERNAL TYPE
		WAS ALSO NEEDED TO SOLVE THIS SPECIFIC PROBLEM IN THIS CLASS, BUT, AGAIN, STILL NOT SUFFICIENT 
		BECAUSE THE MECHANISM CAN NOT TRACE THE CLASS CHAIN.
		*/
		CRX_PUBLIC ComplexSecurityProtocol::ComplexSecurityProtocol(int CRX_DEFAULT(-1)) : gLockKey(-1)
			{this->crxConstruct(0);}
		CRX_PUBLIC ComplexSecurityProtocol::ComplexSecurityProtocol(
				SecurityProtocol * pSecurityProtocol, bool pIsToAllowRemovingProtocols = false,
				::crx::Var pLockKey CRX_DEFAULT(-1)) : gLockKey(-1)
			{this->crxConstruct(1, pSecurityProtocol, pIsToAllowRemovingProtocols, pLockKey);}

		CRX_PUBLIC void crxConstruct(int pMode, SecurityProtocol * pSecurityProtocol = NULL, 
				bool pIsToAllowRemovingProtocols = false, ::crx::Var pLockKey CRX_DEFAULT(-1))
		{
			if(pMode == 0)
			{
				this->gSecurityProtocols.push_back(new CrxSecurityDefaultProtocol());
				this->gWasBaseSecurityProtocolAdded = true;
			}
			else if(pSecurityProtocol !== NULL)
			{
				this->gSecurityProtocols.push_back(*pSecurityProtocol);
				this->gWasBaseSecurityProtocolAdded = true;
			}

			this->gIsToAllowRemovingProtocols = pIsToAllowRemovingProtocols;

			if(this->gIsToAllowRemovingProtocols)
				{this->gLockKey = pLockKey;}
		}

		CRX_PUBLIC ComplexSecurityProtocol::pushSecurityProtocol(
				SecurityProtocol * CRX_NOT_NULL pSecurityProtocol)
			{this->gSecurityProtocols.push_back(*pSecurityProtocol);}
		CRX_PUBLIC ComplexSecurityProtocol::popSecurityProtocol(::crx::Var pLockKey CRX_DEFAULT(-1))
		{
			if(this->gIsToAllowRemovingProtocols)
			{
				if(this->gSecurityProtocols.size() > (this->gWasBaseSecurityProtocolAdded ? 1 : 0))
				{
					if((this->gLockKey == -1) || (this->gLockKey == pLockKey))
						{this->gSecurityProtocols.pop_back();}
				}
			}
		}

		CRX_PROTECTED_VIRTUAL bool ComplexSecurityProtocol::doFilterHtmlElement(bool pIsNotComplexMode,
				Security * CRX_NOT_NULL const pSecurity, 
				Security_ElementData * CRX_NOT_NULL pElementData, 
				::pugi::xml_node const & pNode)
		{
			bool vReturn = true;

			for(size_t tI = this->gSecurityProtocols.size() - 1; tI > -1; tI--)
			{
				if(tI === 0)
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterHtmlElement(pIsNotComplexMode, pSecurity, pElementData, 
							pNode);
				}
				else
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterHtmlElement(false, pSecurity, pElementData, pNode);
				}

				if(!vReturn)
					{break;}
			}

			return vReturn;
		}
		CRX_PROTECTED_VIRTUAL bool ComplexSecurityProtocol::doFilterHtmlAttributeAndValue(
				bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				::std::string const & pElementName, Security_AttributeData * CRX_NOT_NULL pAttributeData)
		{
			bool vReturn = true;

			for(size_t tI = this->gSecurityProtocols.size() - 1; tI > -1; tI--)
			{
				if(tI === 0)
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterHtmlAttributeAndValue(pIsNotComplexMode, pSecurity, 
							pElementName, pAttributeData);
				}
				else
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterHtmlAttributeAndValue(false, pSecurity,
							pElementName, pAttributeData);
				}

				if(!vReturn)
					{break;}
			}

			return vReturn;
		}
		CRX_PROTECTED_VIRTUAL ::std::string ComplexSecurityProtocol::doSieveHtmlElementText(
				bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, ::std::string const & pElementName,
				::std::string const & pText, bool pIsCDATA)
		{
			::std::string vReturn = pText;

			for(size_t tI = this->gSecurityProtocols.size() - 1; tI > -1; tI--)
			{
				if(tI === 0)
				{
					vReturn = this->gSecurityProtocols[tI].
							doSieveHtmlElementText(pIsNotComplexMode, pSecurity,
							pElementName, vReturn, pIsCDATA);
				}
				else
				{
					vReturn = this->gSecurityProtocols[tI].
							doSieveHtmlElementText(false, pSecurity, 
							pElementName, vReturn, pIsCDATA);
				}
			}

			return vReturn;
		}

		CRX_PROTECTED_VIRTUAL bool ComplexSecurityProtocol::doFilterCrxCssAtRuleElement(bool pIsNotComplexMode,
				Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleElementData * CRX_NOT_NULL pCrxCssAtRuleElementData)
		{
			bool vReturn = true;

			for(size_t tI = this->gSecurityProtocols.size() - 1; tI > -1; tI--)
			{
				if(tI === 0)
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterCrxCssAtRuleElement(pIsNotComplexMode, pSecurity, 
							pCrxCssAtRuleElementData);
				}
				else
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterCrxCssAtRuleElement(false, pSecurity, 
							pCrxCssAtRuleElementData);
				}

				if(!vReturn)
					{break;}
			}

			return vReturn;
		}
		CRX_PROTECTED_VIRTUAL bool ComplexSecurityProtocol::doFilterCrxCssAtRuleStatement(
				bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleStatementData * CRX_NOT_NULL pCrxCssAtRuleStatementData)
		{
			bool vReturn = true;

			for(size_t tI = this->gSecurityProtocols.size() - 1; tI > -1; tI--)
			{
				if(tI === 0)
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterCrxCssAtRuleStatement(pIsNotComplexMode, pSecurity,
							pCrxCssAtRuleStatementData);
				}
				else
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterCrxCssAtRuleStatement(false, pSecurity,
							pCrxCssAtRuleStatementData);
				}

				if(!vReturn)
					{break;}
			}

			return vReturn;
		}
		CRX_PROTECTED_VIRTUAL bool ComplexSecurityProtocol::doFilterCrxCssAtRuleNameValueBlock(
				bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssAtRuleNameValueBlockData * CRX_NOT_NULL pCrxCssAtRuleNameValueBlockData)
		{
			bool vReturn = true;

			for(size_t tI = this->gSecurityProtocols.size() - 1; tI > -1; tI--)
			{
				if(tI === 0)
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterCrxCssAtRuleNameValueBlock(pIsNotComplexMode, pSecurity, 
							pCrxCssAtRuleNameValueBlockData);
				}
				else
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterCrxCssAtRuleNameValueBlock(false, pSecurity, 
							pCrxCssAtRuleNameValueBlockData);
				}

				if(!vReturn)
					{break;}
			}

			return vReturn;
		}
		CRX_PROTECTED_VIRTUAL bool ComplexSecurityProtocol::doFilterCrxCssNameValuePair(
				bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssNameValuePairData  * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::string const & pAtRuleName, ::std::string const & pAtRuleValue)
		{
			bool vReturn = true;

			for(size_t tI = this->gSecurityProtocols.size() - 1; tI > -1; tI--)
			{
				if(tI === 0)
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterCrxCssNameValuePair(pIsNotComplexMode, pSecurity, 
							pCrxCssNameValuePairData, pAtRuleName, pAtRuleValue);
				}
				else
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterCrxCssNameValuePair(false, pSecurity, 
							pCrxCssNameValuePairData, pAtRuleName, pAtRuleValue);
				}

				if(!vReturn)
					{break;}
			}

			return vReturn;
		}
		CRX_PROTECTED_VIRTUAL bool ComplexSecurityProtocol::doFilterCrxCssNameValuePair2(
				bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity, 
				Security_CrxCssNameValuePairData  * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::vector<Security_CrxCssReference> const & pReferences)
		{
			bool vReturn = true;

			for(size_t tI = this->gSecurityProtocols.size() - 1; tI > -1; tI--)
			{
				if(tI === 0)
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterCrxCssNameValuePair2(pIsNotComplexMode, pSecurity, 
							pCrxCssNameValuePairData, pReferences);
				}
				else
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterCrxCssNameValuePair2(false, pSecurity, 
							pCrxCssNameValuePairData, pReferences);
				}

				if(!vReturn)
					{break;}
			}

			return vReturn;
		}
		CRX_PROTECTED_VIRTUAL bool ComplexSecurityProtocol::doFilterCrxCssReferenceNameValueBlock(
				bool pIsNotComplexMode, Security * CRX_NOT_NULL pSecurity,
				Security_CrxCssReferenceNameValueBlockData * CRX_NOT_NULL pCrxCssReferenceNameValueBlockData)
		{
			bool vReturn = true;

			for(size_t tI = this->gSecurityProtocols.size() - 1; tI > -1; tI--)
			{
				if(tI === 0)
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterCrxCssReferenceNameValueBlock(pIsNotComplexMode, pSecurity, 
							pCrxCssReferenceNameValueBlockData);
				}
				else
				{
					vReturn = this->gSecurityProtocols[tI].
							doFilterCrxCssReferenceNameValueBlock(false, pSecurity, 
							pCrxCssReferenceNameValueBlockData);
				}

				if(!vReturn)
					{break;}
			}

			return vReturn;
		}
	#pragma endregion //}
}}

