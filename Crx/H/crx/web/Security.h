#if(!defined(CRX__WEB__SECURITY___h__))
#define CRX__WEB__SECURITY___h__
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
#include <vector>
#include "Crx/H/crx/nonCrxed/boost/random/RandomDevice.h"
#include "Crx/H/crx/nonCrxed/boost/random/MersenneTwister.h"
#include "Crx/H/crx/nonCrxed/boost/random/Uniform01.h"
#include "boost/regex.hpp"
#include "Crx/H/crx/c/html.h"
#include "Crx/H/crx/c/crxCss.h"
#include "Crx/H/crx/ClassUnorderedMap.h"
#if(!CRX__NON_CRXED__BOOST__RANDOM__MERSENNE_TWISTER__IS_AVAILABLE)
	#include "Crx/H/crx/c/random/MersenneTwister.h"
#endif
#if(!CRX__NON_CRXED__BOOST__RANDOM__RANDOM_DEVICE__IS_AVAILABLE)
	#include "Crx/H/crx/c/random/SafeRandom.h"
#endif
#include "Crx/H/crx/Var.h"
#include "pugixml/pugixml.hpp"
//<<END>>


namespace crx{namespace web
{
	class SecurityProtocol;
	class Security;
	
	/*
	THE SecurityProtocol.h FILE NEEDS THE Security.h FILE, AND THAT FILE NEEDS THE SecurityDefaultProtocol.h FILE,
	AND INSIDE THAT FILE THE CLASS SecurityDefaultProtocol EXTENDS SecurityProtocol AND HENCE NEEDS
	SecurityProtocol.h. HOWEVER, THE FILE SecurityProtocol.h WOULD NOT BE INCLUDED AGAIN BECUASE OF INCLUDE GUARDS.
	
	THE SOLUTION IS TO AVOID INCLUDING Security.h INSIDE SecurityProtocol.h BUT TO DO THIS I WOULD NEED TO FARWARD
	DECLERARE THE CLASS Security AND ITS INNER CLASSES, BUT INNER CLASSES CAN NOT BE FARWARD DECLERAED IN C++.
	UNFORTUANETLY THIS IS NOT A PROBLEM MY LIB ARCHITECTECTURE RESOLVED. THIE IS WHY THE INNER CLASSES HAVE BEEN
	MOVED OUT OF Security AN INSTEAD NAME NAMESPACING, AS DEFINED IN MY STANDARD, HAS BEEN USED TO MARK THEM.
	
	ANOTHER APPROACH IS TO NOT INCLUDE SecurityProtocol.h IN THE FILE Security.h, AND UNDER THE "TRADITIONAL"
	ARCHITECTURE, WHERE THERE ARE ONLY CPP AND H FILES, ONLY THE CPP FILE THE Security CLASS WOULD NEED
	TO INCLUDE SecurityProtocol.h BECAUSE IT IS NOT NEEDED BY Security.h AND THAT WOULD HAVE SOLVED THE ISSUE.
	UNFORTUANETLY, UNDER THE ARCHITECTURE IMPOSED BY MY LIB LIBRARY, THE SECTION MAKING THESE INCLUDES IN 
	THE H AND CPP.H FILES MUST MIRROR EACH OTHER, OTHER THINGS DO NOT WORK CORRECTLY. SEE Crx.h FOR DISCUSSION
	ABOUT THIS.
	*/

	class Security_ElementData
	{
		public: ::std::string gNameOfParent /*= ""*/;
		public:	::std::string gName /*= ""*/;
		public: bool gIsToProcessBodyOnly /*= false*/;
		public: bool gMayHasChildElements /*= false*/;
		public: bool gMayHasTextContent /*= false*/;
		public: bool gMayHasAttributes /*= false*/;
		public:	::std::string gPrependedTextToBody /*= ""*/;
		public:	::std::string gAppendedTextToBody /*= ""*/;
		public: bool gIsToTreatWrapperAsTextOnly /*= false*/; //NOT WORKING, DISABLED
		public: bool gIsToTreatContentAsTextOnly /*= false*/; //NOT WORKING, DISABLED

		public: Security_ElementData(::std::string const & pNameOfParent = ::std::string(),
				::std::string const & pName = ::std::string(),
				bool pIsToProcessBodyOnly = false,
				bool pMayHasChildElements = false,
				bool pMayHasTextContent = false,
				bool pMayHasAttributes = false,
				::std::string const & pPrependedTextToBody = ::std::string(),
				::std::string const & pAppendTextToBody = ::std::string(),
				bool pIsToTreatWrapperAsTextOnly = false,
				bool pIsToTreatContentAsTextOnly = false): 
						gNameOfParent(pNameOfParent), gName(pName),
						gIsToProcessBodyOnly(pIsToProcessBodyOnly), 
						gMayHasChildElements(pMayHasChildElements),
						gMayHasTextContent(pMayHasTextContent), gMayHasAttributes(pMayHasAttributes),
						gPrependedTextToBody(pPrependedTextToBody),
						gAppendedTextToBody(pAppendTextToBody),
						gIsToTreatWrapperAsTextOnly(pIsToTreatWrapperAsTextOnly),
						gIsToTreatContentAsTextOnly(pIsToTreatContentAsTextOnly)
			{}
	};
	
	class Security_AttributeData
	{
		public: ::std::string gNameOfElement /*= ""*/;
		public: ::std::string gName /*= ""*/;
		public: ::std::string gValue /*= ""*/;
		public: bool gWasValueSet /*= false*/;

		public: Security_AttributeData(::std::string const & pNameOfElement = ::std::string(),
				::std::string const & pName = ::std::string(),
				::std::string const & pValue = ::std::string(),
				bool pWasValueSet = false) : 
						gNameOfElement(pNameOfElement), 
						gName(pName), gValue(pValue), gWasValueSet(pWasValueSet)
			{}
	};

	class Security_CrxCssAtRuleElementData
	{
		public: ::std::string gName;
		public: ::std::string gValue;
		public: bool gIsToProcessBodyOnly;
		public: bool gMayHasChildren;
		public: ::std::string gPrependedTextToBody;
		public: ::std::string gAppendedTextToBody;
		public: Crx_C_CrxCss_AtRuleElement * CRX_NOT_MINE gParserObject;
		
		public: Security_CrxCssAtRuleElementData(::std::string const & pName, ::std::string const & pValue, 
				Crx_C_CrxCss_AtRuleElement * CRX_NOT_NULL pParserObject) : 
						gName(pName), gValue(pValue), gIsToProcessBodyOnly(false),
						gMayHasChildren(true), gPrependedTextToBody(""), gAppendedTextToBody(""),
						gParserObject(pParserObject)
			{}
							
	};

	class Security_CrxCssAtRuleStatementData
	{
		public: ::std::string gName;
		public: ::std::string gValue;
		public: Crx_C_CrxCss_AtRuleStatement * CRX_NOT_MINE gParserObject;

		public: Security_CrxCssAtRuleStatementData(::std::string const & pName, ::std::string const & pValue, 
				Crx_C_CrxCss_AtRuleStatement * CRX_NOT_NULL pParserObject) : 
						gName(pName), gValue(pValue), gParserObject(pParserObject)
			{}
	};

	class Security_CrxCssAtRuleNameValueBlockData
	{
		public: ::std::string gName;
		public: ::std::string gValue;
		public: Crx_C_CrxCss_AtRuleNameValueBlock * CRX_NOT_MINE gParserObject;

		public: Security_CrxCssAtRuleNameValueBlockData(::std::string const & pName, ::std::string const & pValue, 
				Crx_C_CrxCss_AtRuleNameValueBlock * CRX_NOT_NULL pParserObject) : 
						gName(pName), gValue(pValue), gParserObject(pParserObject)
			{}
	};

	class Security_CrxCssNameValuePairData
	{
		public: ::std::string gName;
		public: ::std::string gValue;
		public: Crx_C_CrxCss_NameValuePair * CRX_NOT_MINE gParserObject;

		public: Security_CrxCssNameValuePairData(Crx_C_CrxCss_NameValuePair * CRX_NOT_NULL pParserObject);
	};

	//THIS IS NOT NECESSARY IN THE C++ IMPLEMENTTION, BUT TO KEEP TO THE NORMAL FORM.
	class Security_CrxCssReference
	{
		public: ::std::string gName;
		public: Crx_C_String * CRX_NOT_MINE gParserObject;

		public: Security_CrxCssReference(::std::string const & pName,
				Crx_C_String * CRX_NOT_NULL pParserObject,
				Security * CRX_NOT_NULL pSecurity /*NEEDED IN THE C++ PORT*/);
	};

	class Security_CrxCssReferenceNameValueBlockData 
	{
		public: ::std::vector<Security_CrxCssReference> gReferences;
		public: Crx_C_CrxCss_ReferenceNameValueBlock * CRX_NOT_MINE gParserObject;
		
		public: Security_CrxCssReferenceNameValueBlockData(
				Crx_C_CrxCss_ReferenceNameValueBlock * CRX_NOT_NULL pParserObject, //THIS IS A TEMPORARY SOLUTION, UNTIL I THINK OF SOMETHING BETTER.
				Security * CRX_NOT_NULL pSecurity /*NEEDED IN THE C++ PORT*/);
	};

	typedef ::std::string (* Security_Decode)(::std::string const & pSource);

	class Security
	{
		friend class Security_ElementData;
		friend class Security_AttributeData;
		friend class Security_CrxCssAtRuleElementData;
		friend class Security_CrxCssAtRuleStatementData;
		friend class Security_CrxCssAtRuleNameValueBlockData;
		friend class Security_CrxCssNameValuePairData;
		friend class Security_CrxCssReference;
		friend class Security_CrxCssReferenceNameValueBlockData;
		
#if(CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_H())
		//...THIS IS ONLY NEEDED IF "CRX__LIB__CONFIG__FAVOR_STATIC_INLINE" IS DEFINED. THIS ...
		//...		ESSENTIALLY FAVORS FEATURES OF C++17 WHEN USING C++17 OR HIGHER. ...
#else
		//...THIS IS ONLY NEEDED IF SUPPORT FOR PRE C++17 IS NEEDED, OR ...
		//...		"CRX__LIB__CONFIG__FAVOR_STATIC_INLINE" IS NOT DEFINED.  ...
		CRX__LIB__PRIVATE_STATIC_VARS_START(Security)
	#if(CRX__NON_CRXED__BOOST__RANDOM__RANDOM_DEVICE__IS_AVAILABLE)
			CRX__LIB__PRIVATE_STATIC_VAR() ::crx::nonCrxed::boost::random::RandomDevice gRandomDevice;
	#else
			CRX__LIB__PRIVATE_STATIC_VAR() Crx_C_Random_SafeRandom * gSafeRandom;
	#endif
	#if(!CRX__NON_CRXED__BOOST__RANDOM__MERSENNE_TWISTER__IS_AVAILABLE)
			CRX__LIB__PRIVATE_STATIC_VAR() Crx_C_Random_MersenneTwister * gMersenneTwister;
	#else
			CRX__LIB__PRIVATE_STATIC_VAR() ::crx::nonCrxed::boost::random::Mt19937 gMt19937;
	#endif
	#if(CRX__NON_CRXED__BOOST__RANDOM__MERSENNE_TWISTER__IS_AVAILABLE && \
			CRX__NON_CRXED__BOOST__RANDOM__UNIFORM01__IS_AVAILABLE)
			CRX__LIB__PRIVATE_STATIC_VAR() ::crx::nonCrxed::boost::random::Uniform01<double, double>::t gUniform01;
	#endif
		CRX__LIB__PRIVATE_STATIC_VARS_END()
#endif

		public: class XmlWriter : public ::pugi::xml_writer
		{
			public: ::std::string gString /*= ""*/;

			public: virtual void write(void const * pData, size_t pSize)
				{this->gString.append(static_cast<char const * >(pData), pSize);}
		};

		public: typedef enum ProcessCageCrxCssRuleOrValue_Type
		{
			PROCESS_CAGE_CRX_CSS_RULE_OR_VALUE__TYPE__REFERENCE = 1,
			PROCESS_CAGE_CRX_CSS_RULE_OR_VALUE__TYPE__RULE_GROUP,
			PROCESS_CAGE_CRX_CSS_RULE_OR_VALUE__TYPE__VALUE,
			PROCESS_CAGE_CRX_CSS_RULE_OR_VALUE__TYPE__AT_RULE_VALUE
		} ProcessCageCrxCssRuleOrValue_Type;

		//VC6
		//typedef ::std::string (* Decode)(::std::string const & pSource);
		
		/*
		- pTarget might point to NULL, in which case the function is responsible for creating a buffer, or
				it might not point to NULL, in which case it would be an empty NULL CHAR terminated buffer
		- The decoding process must not need a buffer larger than the size (number of bytes) of pSource.
		*/
		typedef void (* FastDecode)(char const * pSource, char * pTarget);


		private: SecurityProtocol * gSecurityProtocol /*= NULL*/;
		protected: ::std::vector<std::string> * gNonJavaScriptUrlProtocolsRegexParts; /* = NULL*/

		public: Security();
		public: Security(SecurityProtocol * pSecurityProtocol);
		private: void crxConstruct()
			{this->gNonJavaScriptUrlProtocolsRegexParts = NULL;}


		protected: void setSecurityProtocol(SecurityProtocol* pCrxSecurityProtocol);
		protected: SecurityProtocol* getSecurityProtocol();
		
		protected: std::vector<char const *> getNonJavascriptUrlProtocols();
		private: void buildNonJavaScriptUrlProtocolRegexParts();

	//PREPARATION
	//
	//
		public: void setContetSecurityPolicy(crx::AssociativeArray<std::string>::t pRules);
		//THIS SET HEADERS AND HTML DOCTYPE THAT THIS SECURITY CLASS IS DESIGNED FOR, AND ENSURES
		//	THAT NO MORE HEADER CAN BE OUTPUTED.
		public: void preHtml(void);
		public: void preJson(/*$pJsonData*/);

	//FORM SIGNATURE
	//
	//	
		//THIS SHOULD BE CALLED WITHIN A FORM TO SIGN IT AS COMING FROM THE SERVER
		public: void signForm();
		public: virtual ::std::string signForm_string();
		//THIS SHOULD BE CALLED WHEN VERIFYING FORM SUBMISSION AND CHECKS THAT FORM WAS SIGNED BY
		//	SERVER
		public: virtual void verifyFormSignature();

	//UTILITIES: CPP SPECIFIC
	//
	//
		/*
			REMEMBER: THIS FUNCTION IS NOT THE SAME AS THE PHP FUNCTION str_ireplace CALLED WITH
					AN ARRAY OF REPLACEMENTS. THIS ONLY BEHAVES THE SAME WAY IF THE REPLACEMENTS
					DO NOT LEAD TO A NEW STRING SUCH AS THE REPLACEMENTS ARE REPLACED AGAIN. 
					REMEMBER, WHEN CALLED WITH AN ARRAY, PHP'S str_ireplace SIMPLY CALLS ITSELF
					FOR EACH ARRAY ITEM, HENCE WHY REPLACEMENTS COULD BE REPLACED AGAIN.
		*/
		public: static bool isUrlSeperator(char pChar)
			{return (pChar == '/');};
		public: ::std::string cpp_trimString1(::std::string const & pString);
		public: void cpp_trimString2(::std::string * pString);
		public: ::std::string cpp_removeControlCharactersFrom1(::std::string const & pString);
		public: void cpp_removeControlCharactersFrom2(::std::string * pString);
		public: static bool cpp_removeControlCharactersFrom2__iscntrl(char pChar);
		/*
			WARNING: pLowerCasedSearches IS AN ARRAY THAT MUST END WITH AN EMPTY STRING.
		*/
		public: ::std::string cpp_removeSubstringsIgnoringCaseFrom(::std::string const & pString, 
				char const * pLowerCasedSearches[]);
		public: void cpp_appendUnsignedCharAsHexDigitsTo(::std::string * CRX_NOT_NULL pString, 
				unsigned char pChar);
		public:  double cpp_getSafeRandomNumber();
		public:  double cpp_getUnSafeRandomNumber();
		public:  bool cpp_isStringEmpty(::std::string pString);
		public: ::std::vector<::std::string> Security::cpp_splitString(::std::string pString, char pChar);

	//UTILITIES:
	//
	//
		public: bool doesStringBeginsWith(::std::string const & pString, ::std::string const & pSearch);
		public: bool doesStringEndsWith(::std::string const & pString, ::std::string const & pSearch);
		public: ::std::string normalizePath(::std::string const & pPath, bool pIsToBarInPath = false);
		public: ::std::string rootPath(::std::string const & pPath);
		public: ::std::string groundPath(::std::string const & pUrl);
		/*public final function gateUrl($pUrl, $pIsDomainNameAllowed = false, $pDomainNameInformation = null)
		{
			$vUrl = trim(str_replace('\\', '/',
					$this->regexReplace("/[[:cntrl:]]/","", //$this->decodeUrl(
					$pUrl
					//)
					)));
			$vParsedUrl = parse_url($this->doesStringStartsWith("//", $vUrl) ?
					(CrxSecurity::URL_RELATIVE_PROTOCOL.":".$vUrl) : $vUrl);
			$vPath = $this->normalizePath('/'.$vParsedUrl['path'], true);
			$vReturn = "";


			if(!empty($vParsedUrl['scheme']))
			{
				if($pIsDomainNameAllowed)
				{
					$tDomainNameInformation = $pDomainNameInformation;

					if($pHomeUrlInformation === null)
					{
						$tDomainNameInformation['protocol'] = array("http", "https");

						//THE FOLLOWING ARE NOT SAFE DEPENDING ON SERVER CONFIGURATIONS.
						$tDomainNameInformation['port'] = $_SERVER['SERVER_PORT'];
						$tDomainNameInformation['host'] = $_SERVER['SERVER_NAME'];//WARNING might return HTTP_HOST DEPENDING ON SERVER CONFIGURATIONS.
					}
					else
					{
						$tDomainNameInformation['protocol'] = (array_key_exists('protocol', $pDomainNameInformation) ?
								$pDomainNameInformation['protocol'] : null);
						$tDomainNameInformation['port'] =
						$tDomainNameInformation['host']
					}

					if(
				}
			}

			if(!empty($vUrl))
			{
				$tPathTokens = explode('/', $vUrl);

				if((count($tPathTokens) > 1) &&
						$this->doesStringEndsWith($tPathTokens[1], ':'))
					{$vUrl = "/";echo "YES";}

			}
			else
				{$vUrl = "/";}

			return $vUrl;
		}*/
		private: ::std::string utf8Chr(uint32_t pUnsignedInt32);
		
	//OTHER:
	//
	//	
		//ALL FUNCTIONS THAT CAN POTENTIALLY END PHP EXECUTION MUST CALL THIS FUNCTION, AND THUS CAN
		//	NOT BE STATIC
		protected: void exitProgram(::std::string const & pText);

	//REPLACEMENT: THESE FUNCTION ARE GUARANTEED TO FULLY REPLACE INSTANCES IN THE INPUT
	//
	//
		public: ::std::string ireplace(::std::string const & pStringToFind, ::std::string const & pReplacement, 
				std::string const & pString);
		public: ::std::string regexReplace(::boost::regex pRegex /*::std::string const & pRegexPattern*/, 
				::std::string const & pReplacement, ::std::string const & pString);

	//DECODING: THESE FUNCTIONS ARE GUARANTEED TO FULLY DECODE THE INPUT
	//
	//
		public: ::std::string decodeHtml(::std::string const & pHtml);
		//THE FOLLOWING FUNCTION IS NOT SAFE ON AN ENTIRE URL, BUT ONLY ON THE QUERY PART OF A URL,
		//		BECAUSE IT CAN TRANSFORM A URL TO A DIFFERENT ONE.
		//		
		public: ::std::string decodeUrlPart(::std::string const & pUrlPart);
		//THE FOLLOWING FUNCTION ALLOWS SAFE DECODING OF THE ENTIRE URL WITHOUT THE RISTK OF
		//		TRANSFORMING IT INTO A DIFFERENT URL, OR INTRODUCING A VALID URL WHERE NON WAS
		//		PRESENT.
		//HOWEVER NOTE THAT THIS FUNCTION IS NOT SAFE TO USE ON AN HTML ATTRIBUTE WHERE
		//		BROWSERS ALLOW WHITE SPACE. IF WHITE SPACE IS ENCODED IN THE URL AND THIS FUNCTION
		//		IS CALLED IT COULD PRODUCE OUTPUT SUCH AS "j ava script://", WHICH IN A HTML
		//		ATTRIBUTE IS EQUIVILANT TO "javascript://"
		//
		//IMPORTANT: INITIALLY THE FUNCTION DID NOT IGNORE '#' BUT MUCH LATER I UPDATED IT TO DO SO. THE
		//		DECISION MIGHT BE WRONG. CONVERSELY, IN THE FUTURE YOU MIGHT ALSO WANT TO IGNORE '[', ']'
		//		'!', ''', '(', ')', '*'. THESE HAVE ALSO BEEN RESERVED, BUT DO NOT SEEM TO BE USED.
		//		SEE		https://datatracker.ietf.org/doc/html/rfc3986
		//		SEE		https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/encodeURIComponent
		public: ::std::string safeDecodeUrl(::std::string const & pUrl);
		private: ::std::string safeDecodeUrl__do(::std::string const & pUrl);
		public: ::std::string decodeCss(::std::string const & pCss);
		private: ::std::string decodeCssOnce(::std::string const & pString);
		public: ::std::string decodeHtmlAndCss(::std::string const & pHtmlAndCSS);
		public: ::std::string decodeUsing(::std::vector<Security_Decode> pDecodes, 
				::std::string const & pString, bool pIsNotUsingFullDecoders = false);
		//pFastDecodes must be NULL terminated
		public: ::std::string cpp_decodeUsing(Security::FastDecode pFastDecodes[], ::std::string const & pString, 
				bool pIsNotUsingFullDecoders = false);

	//CAGING: THIS IS OFTEN REFERRED TO AS 'Escaping'. CAGING AIMS TO PREVENT CODE FROM EXITITING 
	//		FROM IT'S CONTEXT.
	//	INPUT: A FULLY DECODED STRING.
	//	OUTPUT: CAGED CODE THAT IS NO LONGER GUARANTEED TO BE FULLY DECODED
		public: ::std::string cageRegexText(::std::string const & pText);
		//THE FOLLOWING CAGES COMMUNICATION HEADERS
		public: ::std::string cageHeader(::std::string const & pHeader);
		public: ::std::string cageEmailHeader(::std::string const & pEmailHeader);
		//THE FOLLOWING CAGES HTML ATTRIBUTES, WITH THE ASSUMPTION THAT ATTRIBUTES ARE PROPERLY 
		//	FORMATTED USING QUOTES.
		public: ::std::string cageHtmlAttribute(::std::string const & pAttribute);
		public: ::std::string cageHtmlText(::std::string const & pHtmlText);
		public: ::std::string cageCssIdentifier(::std::string const & pString);
		public: ::std::string cageCssHexValue(::std::string const & pString);
		public: ::std::string cageCssString(::std::string const & pString);
		public: ::std::string cageJsValue(::crx::Var const & pJsValue);
		public: ::std::string cageJsValue(::crx::Var pJsValue);

	//SANITIZERS: THESE FUNCTIONS SANITIZE CODE FROM JAVASCRIPT. 
	//		- NOTE THAT THE CODE CONTEXT MUST BE NOT JAVASCRIPT ITSELF!
	//
		public: ::std::string sanitizeTextForHtmlAttribute(::std::string const & pUrl);
		public: ::std::string sanitizeUrlForHtmlAttribute(::std::string const & pUrl);
		public: ::std::string sanitizeCssValue(::std::string const & pCssValue);

	//ROOTERS: THESE FUNCTION ENSURE GIVEN URLS START FROM THE ROOT URL, MEANING '/'.
		//public final function rootUrlForHtmlAttribute($pUrl)
			/*{return $this->rootPath($this->regexReplace("/[[:cntrl:]]/","", $pUrl));}*/

	//GROUNDERS: THESE FUNCTION ENSURE GIVEN URLS START FROM THE CURRENT SERVER.
		//public final function groundUrlForHtmlAttribute($pUrl)
			/*{return $this->groundPath($this->regexReplace("/[[:cntrl:]]/","", $pUrl));}*/

		//CLEANERS: THESE FUNCTION PERFORM FULL CLEANING OPERATIONS. EACH IS A COMPOUND OF A COMBINATION
		//		OF CAGERS, SANITIZERS AND GROUNDERS. CLEANERS PROVIDE THE FINAL ENCODING NEEDED.
		//		NOTE THAT A CLEANER CAN NOT BE A COMPOUND OF MORE THAN ONE CAGER. IF THIS IS THE CASE
		//			SOMETHING IS WRONG.
		//		NOTE THAT THE FOLLOWING ONLYL PROVIDES CLEANERS FOR COMMON CASES.
		public: ::std::string cleanTextForHtmlAttribute(::std::string const & pUrl);
		public: ::std::string cleanTextForUrlAttribute(::std::string const & pUrl);

	//PROCESSOR: HTML
	//
	//
		protected: ::std::string tryToGetDomNodeInnerRawContent(::pugi::xml_node * pDomElement);
		protected: ::std::string tryToGetDomNodeOuterRawContent(::pugi::xml_node * pDomElement);
		private: void regenerateHtmlElementBecauseOfCpp(::pugi::xml_node * pDomElement,
				::std::string * pProcessedHtml);

		protected: ::pugi::xml_document * getParsedHtml(::std::string const & pString, bool pIsToThrowOnError = true);
		protected: ::std::string processParsedHtml(pugi::xml_document * pDomDocument);
		public: ::std::string processHtml(::std::string const & pString);
		private: void processHtmlElement(::std::string const & pParentElementName, ::pugi::xml_node * pDomElement, 
				::std::string * pProcessedHtml);
		private: void processHtmlAttribute(::std::string const & pElementName, ::pugi::xml_attribute * pAttribute, 
				::std::string * pProcessedHtml, bool pIsBuildingOnly = false);

		protected: virtual void onProcessHTMLStart();
		protected: virtual void onProcessHTMLEnd();
		protected: virtual bool filterHtmlElement(Security_ElementData * CRX_NOT_NULL pElementData, 
				::pugi::xml_node const & $pDomElement);
		protected: virtual bool filterHtmlAttributeAndValue(
				::std::string const & pElementName, Security_AttributeData * CRX_NOT_NULL pAttributeData);
		protected: virtual ::std::string sieveHtmlElementText(::std::string const & pElementName,
				::std::string const & pText, bool pIsCDATA);
		protected: virtual void onElementClose(Security_ElementData * CRX_NOT_NULL pElementData);

		//HELPER FUNCTION MEANT TO BE USED INSIDE filterHtmlElement WHEN NEEDED.
		protected: ::std::string processHtmlDomBranch(Security_ElementData * CRX_NOT_NULL pElementData_Root, 
				::pugi::xml_node * pDomElement_Root);

		//PROCESSOR: CSS
		//
		//
		public: ::std::string processCss(::std::string const & pString);
		public: ::std::string processInlineCss(::std::string const & pString);
		private: void crxCss_processBlockElement(Crx_C_CrxCss_BlockElement * CRX_NOT_NULL pBlockElement, 
				::std::string * CRX_NOT_NULL pProcessedCss, int * CRX_NOT_NULL pLevel);
		private: void crxCss_processAtRuleStatement(
				Crx_C_CrxCss_AtRuleStatement * CRX_NOT_NULL pAtRuleStatement,
				::std::string * CRX_NOT_NULL pProcessedCss, int * CRX_NOT_NULL pLevel);
		private: void crxCss_processAtRuleElement(
				Crx_C_CrxCss_AtRuleElement * CRX_NOT_NULL pAtRuleElement,
				::std::string * CRX_NOT_NULL pProcessedCss, int * CRX_NOT_NULL pLevel);
		private: void crxCss_processAtRuleNameValueBlock(
				Crx_C_CrxCss_AtRuleNameValueBlock * CRX_NOT_NULL pAtRuleNameValueBlock,
				::std::string * CRX_NOT_NULL pProcessedCss, int * CRX_NOT_NULL pLevel);
		private: void crxCss_processReferenceNameValueBlock(
				Crx_C_CrxCss_ReferenceNameValueBlock * CRX_NOT_NULL pReferenceNameValueBlock,
				::std::string * CRX_NOT_NULL pProcessedCss, int * CRX_NOT_NULL pLevel);
		private: void crxCss_processCssNameValuePair(
				Crx_C_CrxCss_NameValuePair * CRX_NOT_NULL pNameValuePair,
				::std::string const & pAtRuleName, ::std::string const & pAtRuleValue,
				::std::string * CRX_NOT_NULL pProcessedCss, int * CRX_NOT_NULL pLevel);
		private: void crxCss_processCssNameValuePair2(
				Crx_C_CrxCss_NameValuePair * CRX_NOT_NULL pNameValuePair,
				::std::vector<Security_CrxCssReference> const & pReferences,
				::std::string * CRX_NOT_NULL pProcessedCss, int * CRX_NOT_NULL pLevel);

		protected: virtual bool filterCrxCssAtRuleElement(
				Security_CrxCssAtRuleElementData * CRX_NOT_NULL pCrxCssAtRuleElementData);
		protected: virtual bool filterCrxCssAtRuleStatement(
				Security_CrxCssAtRuleStatementData * CRX_NOT_NULL pCrxCssAtRuleStatementData);
		protected: virtual bool filterCrxCssAtRuleNameValueBlock(
				Security_CrxCssAtRuleNameValueBlockData * CRX_NOT_NULL pCrxCssAtRuleNameValueBlockData);
		protected: virtual bool filterCrxCssNameValuePair(
				Security_CrxCssNameValuePairData * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::string const & pAtRuleName, ::std::string const & pAtRuleValue);
		protected: virtual bool filterCrxCssNameValuePair2(
				Security_CrxCssNameValuePairData * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::vector<Security_CrxCssReference> const & pReferences);
		protected: virtual bool filterCrxCssReferenceNameValueBlock(
				Security_CrxCssReferenceNameValueBlockData * CRX_NOT_NULL pCrxCssReferenceNameValueBlockData);

		public: ::std::string processCageCrxCssAtRuleName(::std::string const & pString);
		public: ::std::string processCageCrxCssName(::std::string const & pString);
		public: ::std::string processCageCrxCssReference(::std::string const & pString);
		public: ::std::string processCageCrxCssValue(::std::string const & pString);
		public: ::std::string processCageCrxCssAtRuleValue(::std::string const & pString);
		private: ::std::string processCageCrxCssRuleOrValue(
				Security::ProcessCageCrxCssRuleOrValue_Type pType, ::std::string const & pString);

		public: ::std::string procesCageCssValue(::std::string const & pCssValue);
		public: ::std::string processCageCssSelector(::std::string const & pCSSSelector);

		public: ~Security();
	};
}}


#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .cpp.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/CPP.H/crx/web/Security.cpp.h"
#endif
#pragma pop_macro("CRX__LIB__MODE")

#endif