//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .cpp FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE.
#include "Crx/H/crx/web/Security.h"

#include <cctype>
#include <list>
#include <vector>
#include <time.h>
//#include "boost/algorithm/string/trim.hpp"
//#include "boost/algorithm/string/split.hpp"
//#include "boost/algorithm/string/join.hpp"
#include "Crx/H/crx/nonCrxed/boost/random/RandomDevice.h"
#include "Crx/H/crx/nonCrxed/boost/random/MersenneTwister.h"
#include "Crx/H/crx/nonCrxed/boost/random/Uniform01.h"
#include "pugixml/pugixml.hpp"
//#include "boost/range/algorithm/remove_if.hpp"
#include "boost/regex.hpp"
#include <iostream>

#include "Crx/H/crx/c/html.h"
#include "Crx/H/crx/c/crxCss.h"
#include "Crx/H/crx/ClassUnorderedMap.h"
#if(!CRX__NON_CRXED__BOOST__RANDOM__MERSENNE_TWISTER__IS_AVAILABLE)
	#include "Crx/H/crx/c/random/MersenneTwister.h"
#endif
#if(!CRX__NON_CRXED__BOOST__RANDOM__RANDOM_DEVICE__IS_AVAILABLE)
	#include "Crx/H/crx/c/random/SafeRandom.h"
#endif
#include "Crx/H/crx/web/SecurityDefaultProtocol.h"
//<<END>>


namespace crx{namespace web
{
	#pragma region CLASS CrxCssNameValuePairData //{
		CRX_PUBLIC Security_CrxCssNameValuePairData::Security_CrxCssNameValuePairData(
				Crx_C_CrxCss_NameValuePair * CRX_NOT_NULL pParserObject) : 
						gName(""), gValue(""), gParserObject(pParserObject)
		{
			::std::string vString(crx_c_string_constantGetCharsPointer(&(pParserObject->gName)), 
						crx_c_string_getSize(&(pParserObject->gName)));

			std::transform(vString.begin(), vString.end(), this->gName.begin(), ::tolower);

			this->gValue.append(crx_c_string_constantGetCharsPointer(&(pParserObject->gValue)), 
						crx_c_string_getSize(&(pParserObject->gValue)));
		}
	#pragma endregion //}

	#pragma region CLASS CrxCssReference //{
		CRX_PUBLIC Security_CrxCssReference::Security_CrxCssReference(::std::string const & pName,
				Crx_C_String * CRX_NOT_NULL pParserObject,
				Security * CRX_NOT_NULL pSecurity /*NEEDED IN THE C++ PORT*/) : 
						gName(""), gParserObject(pParserObject)
		{
			/*
			NOTE: THE UNDERLYING CSS, NOT CRX CSS, PARSER IN THE JS IMPLEMENTATION, DECODES THE TEXT, 
					HENCE THE CALL TO decodeCssOnce(). NOTE THAT SIMILAR THING IS DONE IN THE PHP
					IMPLEMENTATION.
			*/
			this->gName = pSecurity->decodeCssOnce(pName);
		}
	#pragma endregion //}

	#pragma region CLASS CrxCssReferenceNameValueBlockData //{
		CRX_PUBLIC Security_CrxCssReferenceNameValueBlockData::Security_CrxCssReferenceNameValueBlockData(
				Crx_C_CrxCss_ReferenceNameValueBlock * CRX_NOT_NULL pParserObject, 
				Security * CRX_NOT_NULL pSecurity /*NEEDED IN THE C++ PORT*/) : 
						gParserObject(pParserObject) //THIS IS A TEMPORARY SOLUTION, UNTIL I THINK OF SOMETHING BETTER.
		{
			for(size_t tI = 0; tI < crx_c_arrays_stringSmall_getLength(&(pParserObject->gReferences)); tI++)
			{
				Crx_C_String * tString = crx_c_arrays_stringSmall_get(&(pParserObject->gReferences), tI);

				this->gReferences.push_back(Security_CrxCssReference(::std::string(
						crx_c_string_constantGetCharsPointer(tString), 
						crx_c_string_getSize(tString)), tString, pSecurity));
			}
		}
	#pragma endregion //}

	#pragma region CLASS Security //{
#if(CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_CPPH())
	#if(CRX__NON_CRXED__BOOST__RANDOM__RANDOM_DEVICE__IS_AVAILABLE)
		CRX_PRIVATE_STATIC ::crx::nonCrxed::boost::random::RandomDevice Security::StaticPrivateVars::gRandomDevice;
	#else
		CRX_PRIVATE_STATIC Crx_C_Random_SafeRandom * Security::StaticPrivateVars::gSafeRandom = 
				::crx_c_random_safeRandom_new();
	#endif
	#if(!CRX__NON_CRXED__BOOST__RANDOM__MERSENNE_TWISTER__IS_AVAILABLE)
		CRX_PRIVATE_STATIC ::Crx_C_Random_MersenneTwister * Security::StaticPrivateVars::gMersenneTwister = 
				::crx_c_random_mersenneTwister_new(static_cast<uint32_t>(::time(NULL)));
	#else
		CRX_PRIVATE_STATIC ::crx::nonCrxed::boost::random::Mt19937 Security::StaticPrivateVars::gMt19937;
	#endif
	#if(CRX__NON_CRXED__BOOST__RANDOM__MERSENNE_TWISTER__IS_AVAILABLE && \
			CRX__NON_CRXED__BOOST__RANDOM__UNIFORM01__IS_AVAILABLE)
		CRX_PRIVATE_STATIC ::crx::nonCrxed::boost::random::Uniform01<double, double>::t Security::StaticPrivateVars::gUniform01;
	#endif
#endif
			
		CRX_PUBLIC Security::Security()
		{
			this->crxConstruct();
			this->gSecurityProtocol = new SecurityDefaultProtocol();
		};
		CRX_PUBLIC Security::Security(SecurityProtocol* pCrxSecurityProtocol) : 
				gSecurityProtocol(pCrxSecurityProtocol)
			{this->crxConstruct();};

		CRX_PROTECTED void Security::setSecurityProtocol(SecurityProtocol* pCrxSecurityProtocol)
			{this->gSecurityProtocol = pCrxSecurityProtocol;};
		CRX_PROTECTED SecurityProtocol* Security::getSecurityProtocol()
			{return this->gSecurityProtocol;};

		CRX_PROTECTED ::std::vector<char const *> Security::getNonJavascriptUrlProtocols()
		{
			::std::vector<char const *> vVector;

			vVector.push_back("http");
			vVector.push_back("https");
			vVector.push_back("ftp");
			vVector.push_back("ftps");
			vVector.push_back("sftp");
			vVector.push_back("feed");
			vVector.push_back("mailto");

			return vVector;
		}
		CRX_PRIVATE void Security::buildNonJavaScriptUrlProtocolRegexParts()
		{
			std::vector<char const *> vNonJavaScriptUrlProtocols =
						this->getNonJavascriptUrlProtocols();
			std::size_t vIndex = 0;

			this->gNonJavaScriptUrlProtocolsRegexParts = 
						new std::vector<std::string>();

			for(std::size_t tI = 0; tI < vNonJavaScriptUrlProtocols.size(); tI++)
			{
				std::string tRegex; /*= "";*/
				std::size_t tLength = strlen(vNonJavaScriptUrlProtocols[tI]);

				for(std::size_t tI2 = 0; tI2 < tLength; tI2++)
					{tRegex += vNonJavaScriptUrlProtocols[tI][tI2] + "\\s*";}
			
				this->gNonJavaScriptUrlProtocolsRegexParts->push_back(tRegex);
			}
		}

	//PREPARATION
	//
	//
		CRX_PUBLIC void Security::setContetSecurityPolicy(::crx::AssociativeArray<std::string>::t pRules)
		{
			//$vHeader = "Content-Security-Policy: default-src: 'self'; script-src: 'self' static.domain.tld";
			std::string vHeader = "Content-Security-Policy:";
			crx::AssociativeArray<std::string>::t::iterator vIterator = pRules.begin();

			while(vIterator != pRules.end())
			{
				if(vIterator->first == "default-src")
					{}
				else if(vIterator->first == "default-src")
					{}
				else if(vIterator->first == "script-src")
					{}
				else if(vIterator->first == "object-src")
					{}
				else if(vIterator->first == "style-src")
					{}
				else if(vIterator->first == "img-src")
					{}
				else if(vIterator->first == "media-src")
					{}
				else if(vIterator->first == "frame-src")
					{}
				else if(vIterator->first == "font-src")
					{}
				else if(vIterator->first == "connect-src")
					{}
				else if(vIterator->first == "form-action")
					{}
				else if(vIterator->first == "sandbox")
					{}
				else if(vIterator->first == "script-nonce")
					{}
				else if(vIterator->first == "plugin-types")
					{}
				else if(vIterator->first == "reflected-xss")
					{}
				else if(vIterator->first == "report-uri")
					{}
				else
					{}

				vIterator++;
			}
			/*header($vHeader);*/
			
			this->exitProgram("NOT IMPLEMENTED");
		};
		CRX_PUBLIC void Security::preHtml(void)
		{
			//header('Content-Type: text/html; charset=utf-8');
			//echo("<!DOCTYPE html>");
			
			this->exitProgram("NOT IMPLEMENTED");
		};
		CRX_PUBLIC void Security::preJson(/*$pJsonData*/)
		{
			//header('Content-Type: application/json; charset=utf-8');

			this->exitProgram("NOT IMPLEMENTED");
		};
	
	//FORM SIGNATURE
	//
	//	
		CRX_PUBLIC void Security::signForm()
			{/*echo $this->signForm_string();*/ this->exitProgram("NOT IMPLEMENTED");}
		CRX_PUBLIC_VIRTUAL ::std::string Security::signForm_string()
			{this->exitProgram("CrxSecurity::singForm_string() IS USED WITHOUT IMPLEMENTATION"); return "";}
		CRX_PUBLIC_VIRTUAL void Security::verifyFormSignature()
			{this->exitProgram("CrxSecurity::verifyFormSignature() IS USED WITHOUT IMPLEMENTATION");}
			
	//UTILITIES: CPP SPECIFIC
	//
	//
		CRX_PUBLIC ::std::string Security::cpp_trimString1(::std::string const & pString)
		{
			std::string vString = pString;

			//VC6
			//boost::trim(vString);
			
			Security::cpp_trimString2(&vString);

			return vString;
		}
		CRX_PUBLIC void Security::cpp_trimString2(::std::string * pString)
		{
			if(pString != NULL)
			{
				//VC6
				//boost::trim(*pString);
				
				if(pString->size() > 0)
				{
					size_t tStartIndex = 0;

					while((tStartIndex < pString->size()) &&
							/*VC6 !::std::isspace(static_cast<unsigned char>(
									(*pString)[tStartIndex]))*/
							!::std::isspace((*pString)[tStartIndex], ::std::locale("")))
						{tStartIndex++;}

					if(tStartIndex < pString->size())
					{
						size_t tEndIndex = pString->size();

						while((tEndIndex > 0) &&
								/*VC6 !::std::isspace(static_cast<unsigned char>(
										(*pString)[tEndIndex - 1]))*/
								!::std::isspace((*pString)[tEndIndex - 1], ::std::locale("")))
							{tEndIndex--;}

						*pString = pString->substr(tStartIndex, tEndIndex - tStartIndex);
					}
					else
						{*pString = "";}
				}
			}
		};
		CRX_PUBLIC ::std::string crx::web::Security::cpp_removeControlCharactersFrom1(::std::string const & pString)
		{
			::std::string vReturn /*= ::std::string()*/;
			::std::string::const_iterator vIterator = pString.begin();

			while(vIterator != pString.end())
			{
				if(::std::iscntrl(*vIterator, ::std::locale("")))
					{continue;}

				vReturn += *vIterator;
			}

			return vReturn;
		}
		CRX_PUBLIC void Security::cpp_removeControlCharactersFrom2(::std::string * pString)
		{
			if(pString == NULL)
				{return;}

			//pString->erase(boost::remove_if(*pString, __iscntrl), pString->end());
			pString->erase(::std::remove_if(pString->begin(), pString->end(), 
					Security::cpp_removeControlCharactersFrom2__iscntrl), pString->end());
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() bool Security::cpp_removeControlCharactersFrom2__iscntrl(char pChar)
			{return static_cast<bool>(::std::iscntrl(pChar, ::std::locale("")));}
		CRX_PUBLIC ::std::string Security::cpp_removeSubstringsIgnoringCaseFrom(::std::string const & pString, 
				char const * pLowerCasedSearches[])
		{
			std::string vTemp = pString;
			std::string vTemp__lowerCase = ::std::string();
			std::string vReturn = ::std::string();
			int vNumberOfTries = 10;
			char * tLastChar = NULL;

			std::transform(vTemp.begin(), vTemp.end(), vTemp__lowerCase.begin(), ::tolower);

			do
			{
				int tI = 0;
				
				vReturn = vTemp;

				while(pLowerCasedSearches[tI][0] != '\0')
				{
					size_t tIndex = ::std::string::npos;
					char * tChar__original = &(vTemp[0]);
					char * tChar__normalized = &(vTemp__lowerCase[1]);
					char * tChar__original__output = tChar__original;
					char * tChar__normalized__output = tChar__normalized;

					if((*tChar__normalized) == pLowerCasedSearches[tI][0])
					{
						char * tChar__normalized2 = tChar__normalized + 1;
						char const * tChar_search = &(pLowerCasedSearches[tI][1]);
						bool tIsFound = false;

						while(*tChar__normalized2 != '\0')
						{
							if(*tChar_search == '\0')
							{
								tIsFound = true;
								break;
							}
							else if(*tChar__normalized2 != *tChar_search)
							{
								tIsFound = false;
								break;
							}
							else
							{
								tChar__normalized2++;
								tChar_search++;
							}
						}

						if(tIsFound)
						{
							while(tChar__normalized != tChar__normalized2)
							{
								*tChar__original__output = *tChar__original;
								*tChar__normalized__output = *tChar__normalized;

								tChar__original__output++;
								tChar__normalized__output++;

								tChar__original++;
								tChar__normalized++;
							}
						}
						else
						{
							while(tChar__normalized != tChar__normalized2)
							{
								tChar__original++;
								tChar__normalized++;
							}
						}
					}
					else
					{
						*tChar__original__output = *tChar__original;
						*tChar__normalized__output = *tChar__normalized;

						tChar__original__output++;
						tChar__normalized__output++;

						tChar__original++;
						tChar__normalized++;
					}

					tLastChar = tChar__original__output + 1;

					(*(tChar__original__output + 1)) = '\0';
					(*(tChar__normalized__output + 1)) = '\0';

					tI++;
				}

				vNumberOfTries--;
			}
			while((vTemp != vReturn) && (vNumberOfTries > 0));

			if(tLastChar != NULL)
				{vReturn.erase(tLastChar - (&vReturn[0]));}

			return vReturn;
		}
		CRX_PUBLIC void Security::cpp_appendUnsignedCharAsHexDigitsTo(::std::string * CRX_NOT_NULL pString,
				unsigned char pUnsignedChar)
		{
			char vDIGITS[17] = "0123456789ABCDEF";
			char vOutput[5] /*= ?*/;

			vOutput[0] = 0; //vDIGITS[(pUnsignedChar >> 12) & 0x0f];
			vOutput[1] = 0; //vDIGITS[(pUnsignedChar >> 8) & 0x0f];
			vOutput[2] = vDIGITS[(pUnsignedChar >> 4) & 0x0f];
			vOutput[3] = vDIGITS[pUnsignedChar & 0x0f];
			vOutput[4] = '\0';

			pString->append(vOutput);
		}
		CRX_PUBLIC double Security::cpp_getSafeRandomNumber()
		{
#if(CRX__NON_CRXED__BOOST__RANDOM__RANDOM_DEVICE__IS_AVAILABLE)
	#if(!(CRX__NON_CRXED__BOOST__RANDOM__MERSENNE_TWISTER__IS_AVAILABLE && \
			CRX__NON_CRXED__BOOST__RANDOM__UNIFORM01__IS_AVAILABLE))
			//return crx_c_random_mersenneTwister_getRandomDouble(::crx::web::Security::gMersenneTwister);
			return (((double)(Security::StaticPrivateVars::gRandomDevice.operator()() - 
					Security::StaticPrivateVars::gRandomDevice.min BOOST_PREVENT_MACRO_SUBSTITUTION ())) / 
					((double)(Security::StaticPrivateVars::gRandomDevice.max BOOST_PREVENT_MACRO_SUBSTITUTION () - 
							Security::StaticPrivateVars::gRandomDevice.min BOOST_PREVENT_MACRO_SUBSTITUTION ())));
	#else
			return Security::StaticPrivateVars::gUniform01(Security::StaticPrivateVars::gRandomDevice);
	#endif
#else
			//return Security::cpp_getUnSafeRandomNumber();
			return crx_c_random_safeRandom_getRandomDouble(Security::StaticPrivateVars::gSafeRandom);
#endif
		}
		CRX_PUBLIC double Security::cpp_getUnSafeRandomNumber()
		{
#if(!CRX__NON_CRXED__BOOST__RANDOM__MERSENNE_TWISTER__IS_AVAILABLE)
			return ::crx_c_random_mersenneTwister_getRandomDouble(Security::StaticPrivateVars::gMersenneTwister);
#else
			return Security::StaticPrivateVars::gUniform01(::crx::web::Security::StaticPrivateVars::gMt19937);
#endif
		}
		CRX_PUBLIC bool Security::cpp_isStringEmpty(::std::string pString)
			{return (pString.size() == 0);}
		CRX_PUBLIC ::std::vector<::std::string> Security::cpp_splitString(::std::string pString, char pChar)
		{
			::std::vector<::std::string> vReturn /*= ::std::vector<::std::string>()*/;
			::std::string::const_iterator vIterator = pString.begin();
			::std::string::const_iterator vIterator__first = vIterator;
			::std::string::const_iterator vIterator__end = pString.end();

			while(vIterator != vIterator__end)
			{
				if(*vIterator == pChar)
				{
					vReturn.push_back(::std::string(vIterator__first, vIterator));

					vIterator__first = vIterator + 1;
				}

				 ++vIterator;
			}

			vReturn.push_back(::std::string(vIterator__first, vIterator));

			return vReturn;
		}
		
	//UTILITIES:
	//
	//
		CRX_PUBLIC bool Security::doesStringBeginsWith(::std::string const & pString, 
				std::string const & pSearch)
			{return (pString.compare(0, pSearch.length(), pSearch) == 0);}
		CRX_PUBLIC bool Security::doesStringEndsWith(::std::string const & pString,
				std::string const & pSearch)
		{
			if(pString.length() >= pSearch.length())
			{
				return (pString.compare(pString.length() - pSearch.length(), pSearch.length(), 
						pSearch) == 0);
			}
			else
				{return false;}
		}
		CRX_PUBLIC ::std::string Security::normalizePath(::std::string const & pPath, bool pIsToBarInPath CRX_DEFAULT(false))
		{
			::std::string vPath = this->cpp_trimString1(pPath);
			::std::vector<std::string> vPathTokens /*= std::vector<std::string>()*/;
			::std::list<std::string> vNormalizedPathTokens = std::list<std::string>();
			::std::string vReturn = "";
			//echo "SS:<pre>"; print_r($vPathTokens); echo "</pre><br/>";

			std::replace(vPath.begin(), vPath.end(), '\\', '/');
			//VC6 boost::split(vPathTokens, vPath, Security::isUrlSeperator);
			vPathTokens = this->cpp_splitString(vPath, '/');

			if(this->cpp_isStringEmpty(vPath))
				{return "";}

			for(size_t tI = 0; tI < vPathTokens.size(); tI++)
			{
				std::string tPathToken = this->cpp_trimString1(vPathTokens[tI]);


				if(tPathToken == "")
				{
					if(tI == 0)
						{vNormalizedPathTokens.push_back("");}
				}
				else if(tPathToken == ".")
					{}
				else if(tPathToken == "..")
				{
					if(vNormalizedPathTokens.size() == 0)
					{
						if(pIsToBarInPath)
							{return "";}
						else
							{vNormalizedPathTokens.push_back("..");}
					}
					//elseif((count($vNormalizedPathTokens) === 1) && empty($vNormalizedPathTokens[0]))
					//	{$vNormalizedPathTokens[0] = "..";}
					else if(vNormalizedPathTokens.back() == "..")
						{vNormalizedPathTokens.push_front("..");}
					else
						{vNormalizedPathTokens.pop_back();}
				}
				else
					{vNormalizedPathTokens.push_back(tPathToken);}
			
				//echo "II:<pre>"; print_r($vNormalizedPathTokens); echo "</pre><br/>";
			}

			if((vNormalizedPathTokens.size() == 1) && vNormalizedPathTokens.front() == "")
				{vReturn = "/";}
			else if(vNormalizedPathTokens.empty())
				{vReturn = "";}
			else
			{
				bool tIsNotFirst = false;

				for(::std::list<std::string>::iterator tI = vNormalizedPathTokens.begin();
						tI != vNormalizedPathTokens.end(); tI++)
				{
					if(tIsNotFirst)
						{vReturn.append("/");}
					else
						{tIsNotFirst = false;}

					vReturn.append(*tI);
				}

				//VC6 vReturn  = boost::algorithm::join(vNormalizedPathTokens, "/");
				vReturn += (this->doesStringEndsWith(vPath, "/") ? "/" : "");			
			}

			if(vReturn == "//")
				{vReturn = "/";}

			return vReturn;
		};
		CRX_PUBLIC ::std::string Security::rootPath(::std::string const & pPath)
		{
			std::string vPath = this->normalizePath("/" + this->cpp_removeControlCharactersFrom1(vPath), true);

			if(!this->cpp_isStringEmpty(vPath))
			{
				std::vector<std::string> tPathTokens /*= std::vector<std::string>()*/;

				//VC6 boost::split(tPathTokens, vPath, Security::isUrlSeperator);
				tPathTokens = this->cpp_splitString(vPath, '/');

				if((tPathTokens.size() > 1) && 
						this->doesStringEndsWith(tPathTokens[1], ":"))
					{vPath = "/";}

			}
			else
				{vPath = "/";}

			return vPath;
		}
		CRX_PUBLIC ::std::string Security::groundPath(::std::string const & pUrl)
		{
			std::string vPath = this->normalizePath(this->cpp_removeControlCharactersFrom1(pUrl), true);

			if(!this->cpp_isStringEmpty(vPath))
			{
				std::vector<std::string> tPathTokens = std::vector<std::string>();

				//VC6 boost::split(tPathTokens, vPath, Security::isUrlSeperator);
				tPathTokens = this->cpp_splitString(vPath, '/');

				if((tPathTokens.size() > 0) && 
						this->doesStringEndsWith(tPathTokens[0], ":"))
					{vPath = "";}

			}		

			return vPath;
		}
		CRX_PRIVATE ::std::string Security::utf8Chr(uint32_t pUnsignedInt32)
		{
			char vChars[5] /*= ?*/;

			CRX__C__CHAR__FAST_INSERT_UTF8_CHAR(pUnsignedInt32, vChars, CRXM__FALSE);

			return ::std::string(vChars);
		}
		
	//OTHER:
	//
	//	
		CRX_PROTECTED void Security::exitProgram(::std::string const & pText)
		{
			::std::cerr << pText;
			::exit(EXIT_FAILURE);
		}


	//REPLACEMENT: THESE FUNCTION ARE GUARANTEED TO FULLY REPLACE INSTANCES IN THE INPUT
	//
	//
		CRX_PUBLIC ::std::string Security::ireplace(::std::string const & pStringToFind,
				std::string const & pReplacement, ::std::string const & pString)
		{
			if(pStringToFind.size() == 0)
				{return pString;}

			std::string vString = pString;
			std::string tString = ::std::string();
			std::string vStringToFind__lowerCase = ::std::string();
			std::string vReplacement__lowerCase = ::std::string();
			std::string vString__lowerCase = ::std::string();

			std::transform(pStringToFind.begin(), pStringToFind.end(), vStringToFind__lowerCase.begin(),
					::tolower);
			std::transform(pReplacement.begin(), pReplacement.end(), vReplacement__lowerCase.begin(), 
					::tolower);
			std::transform(pString.begin(), pString.end(), vString__lowerCase.begin(), ::tolower);

			while(tString != vString)
			{
				size_t tIndex = ::std::string::npos;

				tString = vString;

				tIndex = vString__lowerCase.find(vStringToFind__lowerCase);
				while(tIndex != ::std::string::npos)
				{
					vString.replace(tIndex, pStringToFind.size(), pReplacement);
					vString__lowerCase.replace(tIndex, vStringToFind__lowerCase.size(), vReplacement__lowerCase);

					tIndex = vStringToFind__lowerCase.find(vStringToFind__lowerCase, tIndex + 
							vReplacement__lowerCase.size());
				}
			}

			return vString;
		}
		CRX_PUBLIC ::std::string Security::regexReplace(::boost::regex pRegex /*::std::string const & pRegexPattern*/, 
				::std::string const & pReplacement, ::std::string const & pString)
		{
			//NOTE THAT THE FLAG normal IS ASSUMED TO GIVE JAVASCRIPT LIKE BEHAVIOR.
			//NOTE THAT THE DEFAULT IS ASSUMED TO GIVE normal AND char_classes FLAGS
			//::boost::regex vRegex = boost::regex(pRegexPattern);
			::std::string vString = pString;
			::std::string tString = ::std::string();

			while(tString != vString)
			{
				tString = vString;
				vString = ::boost::regex_replace(vString, pRegex, pReplacement);
			}

			return vString;
		}

	//DECODING: THESE FUNCTIONS ARE GUARANTEED TO FULLY DECODE THE INPUT
	//
	//
		CRX_PUBLIC ::std::string Security::decodeHtml(::std::string const & pHtml)
		{
			if(pHtml.size() == 0)
				{return ::std::string();}

			std::string vHtml = pHtml;				//ASSUMING A CHARACTER ENCODING NOT
													//	EXCEEDIND FOUR BYTES PER CHACRATER
			std::string tHtml(pHtml.size(), '1');

			while(tHtml != vHtml)
			{
				tHtml = vHtml;
				crx_c_html_decodeHtmlEntitiesUsingUtf8(vHtml.c_str(), vHtml.size(), &vHtml[0],
							vHtml.capacity(), NULL);
			}

			return vHtml;
		}
		CRX_PUBLIC ::std::string Security::decodeUrlPart(::std::string const & pUrlPart)
		{//return $pUrlPart;
			if(pUrlPart.size() == 0)
				{return ::std::string();}

			std::string vUrlPart = pUrlPart;
			std::string tUrlPart(vUrlPart.size(), '1');

			while(tUrlPart != vUrlPart)
			{
				tUrlPart = vUrlPart;
				crx_c_html_decodeUrl(vUrlPart.c_str(), vUrlPart.size(), &vUrlPart[0], vUrlPart.capacity(), NULL);
			}

			return vUrlPart;
		}
		CRX_PUBLIC ::std::string Security::safeDecodeUrl(::std::string const & pUrl)
		{
			::std::string vUrl = pUrl;
			::std::string tUrl /*= ""*/;

			while(tUrl != vUrl)
			{
				tUrl = vUrl;
				vUrl = this->safeDecodeUrl__do(vUrl);
			}

			return vUrl;
		}
		CRX_PRIVATE ::std::string Security::safeDecodeUrl__do(::std::string const & pUrl)
		{
			static char const * vRESERVED_URL_CHARACTERS[] = {"%3b", "%2f", "%3f", "%3a", "%40", "%26", 
					"%3d", "%2b", "%24", "%2c", "%23"};	// `;`, `/`, `?`, `:`, `@`, `&`, `=`, `+`, `$`, `,`, `#`;
			static ::std::string vRANDOM /*= ?*/;	//NOT  ; / ? : @ & = + $ , % #
			static ::std::vector<::std::string> vREPLACEMENTS /*= ::std::vector<::std::string>()*/;
			::std::string vUrl = pUrl;
					
			if(vREPLACEMENTS.size() == 0)
			{
				char tChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!~`*-{}[]^()',.";
				size_t tLastIndex = sizeof(tChars) - 1;

				for(size_t tI = 0; tI < 64; tI++)
					{vRANDOM.push_back(tChars[static_cast<size_t>(::floor(this->cpp_getUnSafeRandomNumber() * (tLastIndex + 1)))]);}

				vREPLACEMENTS.push_back(::std::string("_3b") + vRANDOM);
				vREPLACEMENTS.push_back(::std::string("_2f") + vRANDOM);
				vREPLACEMENTS.push_back(::std::string("_3f") + vRANDOM);
				vREPLACEMENTS.push_back(::std::string("_3a") + vRANDOM);
				vREPLACEMENTS.push_back(::std::string("_40") + vRANDOM);
				vREPLACEMENTS.push_back(::std::string("_26") + vRANDOM);
				vREPLACEMENTS.push_back(::std::string("_3d") + vRANDOM);
				vREPLACEMENTS.push_back(::std::string("_2b") + vRANDOM);
				vREPLACEMENTS.push_back(::std::string("_24") + vRANDOM);
				vREPLACEMENTS.push_back(::std::string("_2c") + vRANDOM);
				vREPLACEMENTS.push_back(::std::string("_23") + vRANDOM);
			}

			CRX_FOR(size_t tI = 0, tI < vREPLACEMENTS.size(), tI++)
				{vUrl = this->ireplace(vRESERVED_URL_CHARACTERS[tI], vREPLACEMENTS[tI] , vUrl);}
			CRX_ENDFOR
			crx_c_html_decodeUrl(vUrl.c_str(), vUrl.size(), &vUrl[0], vUrl.capacity(), NULL);
			CRX_FOR(size_t tI = 0, tI < vREPLACEMENTS.size(), tI++)
				{vUrl = this->ireplace(vREPLACEMENTS[tI], vRESERVED_URL_CHARACTERS[tI] , vUrl);}
			CRX_ENDFOR

			return vUrl;
		}
		CRX_PUBLIC ::std::string Security::decodeCss(::std::string const & pCss)
		{
			//NOTE: THE FOLLOWING (COMMENTED OUT CODE) SIMPLY KILLS ANY ENCODING
			/*std::string vCss = pCss;

			vCss.erase(std::remove_if(vCss.begin(), vCss.end(), "\\"), vCss.end());*/
			
			std::string vCss = pCss;
			std::string tCss /*= ""*/;

			while(tCss != vCss)
			{
				tCss = vCss;
				vCss = this->decodeCssOnce(vCss);
			}

			return vCss;
		}
		CRX_PRIVATE ::std::string Security::decodeCssOnce(::std::string const & pString)
		{
			bool vIsInsideString = false;
			::std::string vEncodingString = "";
			unsigned char vStringCharacterCode = 0;
			unsigned char vCurrentCharacterCode = 0;
			unsigned char vPreviousCharacterCode = 0;
			bool vIsEscaping = false;
			::std::string vReturn = "";
			size_t tI = 0;
			
			while(tI < pString.size())
			{
				vPreviousCharacterCode = vCurrentCharacterCode;
				vCurrentCharacterCode = static_cast<unsigned char>(pString[tI]);

				if(vIsEscaping)
				{
					if(((vCurrentCharacterCode >= 0x0030) && (vCurrentCharacterCode <= 0x0039) /*0-9*/) ||
							((vCurrentCharacterCode >= 0x0041) && (vCurrentCharacterCode <= 0x0046) /*A-F*/) ||
							((vCurrentCharacterCode >= 0x0061) && (vCurrentCharacterCode <= 0x0066) /*a-f*/))
					{
						if(vEncodingString.size() < 6)
						{
							vEncodingString.push_back(pString[tI]);

							if((vEncodingString.size() == 6) || (tI == (pString.size() - 1)))
								{vReturn.append(this->utf8Chr(::strtoul(vEncodingString.c_str(), NULL, 16)));}
						}
						else
						{
							vReturn.push_back(pString[tI]);
							vEncodingString = "";
							vIsEscaping = false;
						}
					}
					else if(vCurrentCharacterCode == 0x0020)
					{
						if(vEncodingString.size() == 0)
							{vReturn.append(" ");}
						else if(vEncodingString.size() < 6)
							{vReturn.append(this->utf8Chr(strtoul(vEncodingString.c_str(), NULL, 16)));}

						vEncodingString = "";
						vIsEscaping = false;
					}
					else
					{
						if((vEncodingString.size() > 0) && (vEncodingString.size() < 6))
						{
							vReturn.append(this->utf8Chr(strtoul(vEncodingString.c_str(), NULL, 16)));
							vReturn.push_back(pString[tI]);
						}
						else
						{
							if((vCurrentCharacterCode == 0x0022 /*"*/) || (vCurrentCharacterCode == 0x0060 /*'*/))
							{
								vReturn.push_back(pString[tI]);
								vStringCharacterCode = vCurrentCharacterCode;
								vIsInsideString = true;
							}
							else
								{vReturn.push_back(pString[tI]);}
						}

						vEncodingString = "";
						vIsEscaping = false;
					}
				}
				else if(!vIsInsideString && (vCurrentCharacterCode == 0x005C /*\*/))
					{vIsEscaping = true;}
				else
				{
					if(vIsInsideString)
					{
						if(vCurrentCharacterCode == vStringCharacterCode)
						{
							vReturn.push_back(pString[tI]);
							vIsInsideString = false;
							vStringCharacterCode = 0;
						}
						else
							{vReturn.push_back(pString[tI]);}
					}
					else
					{
						if((vCurrentCharacterCode == 0x0022 /*"*/) || (vCurrentCharacterCode == 0x0060 /*'*/))
						{
							vReturn.push_back(pString[tI]);
							vStringCharacterCode = vCurrentCharacterCode;
							vIsInsideString = true;
						}
						else
							{vReturn.push_back(pString[tI]);}
					}
				}

				tI++;
			}

			return vReturn;
		}
		CRX_PUBLIC ::std::string Security::decodeHtmlAndCss(::std::string const & pHtmlAndCSS)
		{
			if(pHtmlAndCSS.size() == 0)
				{return ::std::string();}

			std::string vHtmlAndCSS = pHtmlAndCSS;
			std::string tHtmlAndCSS(vHtmlAndCSS.size(), '1');

			while(tHtmlAndCSS != vHtmlAndCSS)
			{
				tHtmlAndCSS = vHtmlAndCSS;
				vHtmlAndCSS = this->decodeCss(this->decodeHtml(vHtmlAndCSS));
			}

			return vHtmlAndCSS;
		}
		CRX_PUBLIC ::std::string Security::decodeUsing(::std::vector<Security_Decode> pDecodes, 
				::std::string const & pString, bool pIsNotUsingFullDecoders CRX_DEFAULT(false))
		{
			std::string vString = pString;
			std::string tString(vString.size(), '1');

			if(pIsNotUsingFullDecoders)
			{
				while(tString != vString)
				{
					for(size_t tI = 0; tI < pDecodes.size(); tI++)
					{
						do
						{
							tString = vString;
							vString = pDecodes[tI](vString);
						}
						while(tString != vString);
					}
				}
			}
			else
			{
				while(tString != vString)
				{
					tString = vString;

					for(size_t tI = 0; tI < pDecodes.size(); tI++)
						{vString = pDecodes[tI](vString);}
				}
			}

			return tString;
		}
		CRX_PUBLIC ::std::string Security::cpp_decodeUsing(Security::FastDecode pFastDecodes[], 
				::std::string const & pString, bool pIsNotUsingFullDecoders CRX_DEFAULT(false))
		{
			std::string vString = pString;
			std::string tString(vString.size(), '1');

			if(pIsNotUsingFullDecoders)
			{
				while(tString != vString)
				{
					int tI = 0;
					char * tCharPtrPtr;

					tCharPtrPtr = &(vString[0]);

					while(pFastDecodes[tI] != NULL)
					{
						do
						{
							tString = vString;
							tCharPtrPtr = &(vString[0]);
							pFastDecodes[tI](vString.c_str(), tCharPtrPtr);
						}
						while(tString != vString);

						tI++;
					}
				}
			}
			else
			{
				while(tString != vString)
				{
					int tI = 0;
					char * tCharPtrPtr;

					tString = vString;

					while(pFastDecodes[tI] != NULL)
					{
						tCharPtrPtr = &(vString[0]);
						pFastDecodes[tI](vString.c_str(), tCharPtrPtr);
						tI++;
					}
				}
			}

			return tString;
		}

	//CAGING: THIS IS OFTEN REFERRED TO AS 'Escaping'. CAGING AIMS TO PREVENT CODE FROM EXITITING 
	//		FROM IT'S CONTEXT.
	//	INPUT: A FULLY DECODED STRING.
	//	OUTPUT: CAGED CODE THAT IS NO LONGER GUARANTEED TO BE FULLY DECODED
		CRX_PUBLIC ::std::string Security::cageRegexText(::std::string const & pText)
		{
			std::string vReturn; /*= "";*/
			char const * vCurrentChar = pText.c_str();

			while(vCurrentChar != '\0')
			{
				char const tChar = *vCurrentChar;

				if((tChar == '\\') ||  (tChar == '*') ||  (tChar == '+') ||  (tChar == '?') ||  
						(tChar == '|') ||  (tChar == '{') ||  (tChar == '[') ||  (tChar == '(') ||  
						(tChar == ')') ||  (tChar == '^') ||  (tChar == '$') ||  (tChar == '.') ||
						(tChar == '#') || (tChar == ']') || (tChar == '/')/*ESCAPING '/' JUST IN CASE.*/)
					{vReturn.push_back('\\');}

				vReturn.push_back(tChar);
				vCurrentChar++;
			}

			return vReturn;
		}
		CRX_PUBLIC ::std::string Security::cageHeader(::std::string const & pHeader)
		{
			static char const * vSEARCHES[] = {"\\", "\r", "\n", "%0a", "%0d", "<cr>", "<lf>", ""};

			return this->cpp_removeSubstringsIgnoringCaseFrom(pHeader, vSEARCHES);
		}
		CRX_PUBLIC ::std::string Security::cageEmailHeader(::std::string const & pEmailHeader)
			{return this->cageHeader(pEmailHeader);}
		//THE FOLLOWING CAGES HTML ATTRIBUTES, WITH THE ASSUMPTION THAT ATTRIBUTES ARE PROPERLY 
		//	FORMATTED USING QUOTES.
		CRX_PUBLIC ::std::string Security::cageHtmlAttribute(::std::string const & pAttribute)
		{
			//ON TOP OF THE PHP IMPLEMENTAION THE FOLLOWING ENCODES \ BUT I DO NOT REMEMBER WHY. KEEP, HOWEVER,
			//		UNTILL ITS PURPOSE IS REMEMBERED.
			static const unsigned char vSIZE_OF_ENCODING[] = 
			{
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   6,   1,   1,   1,   5,   6,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   4,   1,   4,   5,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   6,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1
			};
			std::string vReturn;

			if(pAttribute.size() > 48)
			{
				vReturn.reserve(pAttribute.size());

				for(size_t tI = 0; tI < pAttribute.size(); tI++)
				{
					switch(pAttribute[tI])
					{
						case '&': 
							vReturn.append("&#x26;"); //vReturn.append("&amp;");
							break;
						case '\"':
							vReturn.append("&#x22;"); //vReturn.append("&quot;");
							break;
						case '\'':
							vReturn.append("&#x27;"); //vReturn.append("&apos;"); &apos; IS NOT SUPPORTED IN HTML4
							break;
						case '>':
							vReturn.append("&#x3E;"); //vReturn.append("&gt;");
							break;
						case '<':
							vReturn.append("&#x3C;"); //vReturn.append("&lt;");
							break;
						case '`':
							vReturn.append("&#x60;"); //NEEDED FOR OLD IE BROWSERS
							break;
						case '\\':
							vReturn.append("&#x2F;");
							break;
						default:
							vReturn.append(&pAttribute[tI], 1);
							break;
					}
				}
			}
			else
			{
				char const * tCharPtr = &(pAttribute[0]);
				size_t tSize = pAttribute.size();
				char * tCharPtr__out = NULL;
				size_t tSize__output = 0;


				for(size_t tI = 0; tI < tSize; tI++)
					{tSize__output += vSIZE_OF_ENCODING[*(tCharPtr++)];}

				vReturn.resize(tSize__output);

				tCharPtr = &pAttribute[0];
				tCharPtr__out = &vReturn[0];

				for(size_t i = 0; i < tSize; i++)
				{
					char current_char = *(tCharPtr++);

					switch (current_char)
					{
						case '&':
						{
							*(tCharPtr__out++) = '&';
							*(tCharPtr__out++) = 'a';
							*(tCharPtr__out++) = 'm';
							*(tCharPtr__out++) = 'p';
							*(tCharPtr__out++) = ';';
							break;
						}
						case '"':
						{
							*(tCharPtr__out++) = '&';
							*(tCharPtr__out++) = 'q';
							*(tCharPtr__out++) = 'u';
							*(tCharPtr__out++) = 'o';
							*(tCharPtr__out++) = 't';
							*(tCharPtr__out++) = ';';
							break;
						}
						case '\'':
						{
							*(tCharPtr__out++) = '&';
							*(tCharPtr__out++) = 'a';
							*(tCharPtr__out++) = 'p';
							*(tCharPtr__out++) = 'o';
							*(tCharPtr__out++) = 's';
							*(tCharPtr__out++) = ';';
							break;
						}
						case '>':
						{
							*(tCharPtr__out++) = '&';
							*(tCharPtr__out++) = 'g';
							*(tCharPtr__out++) = 't';
							*(tCharPtr__out++) = ';';
							break;
						}
						case '<':
						{
							*(tCharPtr__out++) = '&';
							*(tCharPtr__out++) = 'l';
							*(tCharPtr__out++) = 't';
							*(tCharPtr__out++) = ';';
							break;
						}
						case '`':
						{
							*(tCharPtr__out++) = '&';
							*(tCharPtr__out++) = '#';
							*(tCharPtr__out++) = 'x';
							*(tCharPtr__out++) = '6';
							*(tCharPtr__out++) = '0';
							*(tCharPtr__out++) = ';';
							break;
						}
						case '\\':
						{
							*(tCharPtr__out++) = '&';
							*(tCharPtr__out++) = '#';
							*(tCharPtr__out++) = 'x';
							*(tCharPtr__out++) = '2';
							*(tCharPtr__out++) = 'F';
							*(tCharPtr__out++) = ';';
							break;
						}
						default:
						{
							*(tCharPtr__out++) = current_char;
						}
					}
				}
			}

			return vReturn;
		}
		CRX_PUBLIC ::std::string Security::cageHtmlText(::std::string const & pHtmlText)
		{
			//ON TOP OF THE PHP IMPLEMENTAION THE FOLLOWING ENCODES \ BUT I DO NOT REMEMBER WHY. KEEP, HOWEVER,
			//		UNTILL ITS PURPOSE IS REMEMBERED.
			const unsigned char vSIZE_OF_ENCODING[] = 
			{
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   5,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   4,   1,   4,   5,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
			   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1
			};
			std::string vReturn;

			if(pHtmlText.size() > 48)
			{
				vReturn.reserve(pHtmlText.size());

				for(size_t tI = 0; tI < pHtmlText.size(); tI++)
				{
					switch(pHtmlText[tI])
					{
						case '&': 
							vReturn.append("&#x26;"); //vReturn.append("&amp;");
							break;
						case '>':
							vReturn.append("&#x3E;"); //vReturn.append("&gt;");
							break;
						case '<':
							vReturn.append("&#x3C;"); //vReturn.append("&lt;");
							break;
						case '\\':
							vReturn.append("&#x2F;");
							break;
						default:
							vReturn.append(&pHtmlText[tI], 1);
							break;
					}
				}
			}
			else
			{
				char const * tCharPtr = &(pHtmlText[0]);
				size_t tSize = pHtmlText.size();
				char * tCharPtr__out = NULL;
				size_t tSize__output = 0;


				for(size_t tI = 0; tI < tSize; tI++)
					{tSize__output += vSIZE_OF_ENCODING[*(tCharPtr++)];}

				vReturn.resize(tSize__output);

				tCharPtr = &pHtmlText[0];
				tCharPtr__out = &vReturn[0];

				for(size_t i = 0; i < tSize; i++)
				{
					char current_char = *(tCharPtr++);

					switch (current_char)
					{
						case '&':
						{
							*(tCharPtr__out++) = '&';
							*(tCharPtr__out++) = 'a';
							*(tCharPtr__out++) = 'm';
							*(tCharPtr__out++) = 'p';
							*(tCharPtr__out++) = ';';
							break;
						}
						case '<':
						{
							*(tCharPtr__out++) = '&';
							*(tCharPtr__out++) = 'l';
							*(tCharPtr__out++) = 't';
							*(tCharPtr__out++) = ';';
							break;
						}
						case '>':
						{
							*(tCharPtr__out++) = '&';
							*(tCharPtr__out++) = 'g';
							*(tCharPtr__out++) = 't';
							*(tCharPtr__out++) = ';';
							break;
						}
						case '\\':
						{
							*(tCharPtr__out++) = '&';
							*(tCharPtr__out++) = '#';
							*(tCharPtr__out++) = 'x';
							*(tCharPtr__out++) = '2';
							*(tCharPtr__out++) = 'F';
							*(tCharPtr__out++) = ';';
							break;
						}
						default:
						{
							*(tCharPtr__out++) = current_char;
						}
					}
				}
			}

			return vReturn;
		}
		CRX_PUBLIC ::std::string Security::cageCssIdentifier(::std::string const & pString)
		{
			//https://github.com/mathiasbynens/CSS.escape/blob/master/css.escape.js
			// https://drafts.csswg.org/cssom/#serialize-an-identifier
			/* ORIGINAL NOTES FROM REFERENCE CODE. COMMENTED OUT CODE IMPLEMENTS THE ORIGINAL
						ALGORITHM. MY OWN CODE IS SAFER AND ACCOUNTS FOR OLD BROWSERS.
								// Note: there’s no need to special-case astral symbols, surrogate
								// pairs, or lone surrogates.
								// If the character is NULL (U+0000), then the REPLACEMENT CHARACTER
								// 		(U+FFFD).
								// elseif 
								//		1 - If the character is in the range [\1-\1F] (U+0001 to U+001F) or is
								//		 		U+007F, […]
								//		2- If the character is the first character and is in the range [0-9]
								//				(U+0030 to U+0039), […]
								// 		3- If the character is the second character and is in the range [0-9]
								//				(U+0030 to U+0039) and the first character is a `-` (U+002D), […]
								// 		https://drafts.csswg.org/cssom/#escape-a-character-as-code-point
								// else if 
								//		the character is the first character and is a `-` (U+002D), and
								// 				there is no second character, […]
								// else if
								//		the character is not handled by one of the above rules and is
								//				greater than or equal to U+0080, is `-` (U+002D) or `_` (U+005F), or
								//				is in one of the ranges [0-9] (U+0030 to U+0039), [A-Z] (U+0041 to
								//				U+005A), or [a-z] (U+0061 to U+007A), […]
								//		the character itself
								//	else
								//		Otherwise, the escaped character.
								https://drafts.csswg.org/cssom/#escape-a-character
			*/
			size_t vLength = pString.size();
			::std::string vReturn /*= ""*/;
			unsigned char vFirstCharacterCode = ((vLength > 0) ? static_cast<unsigned char>(pString[0]) : 0);
			size_t tI = 0;
			

			if((vLength == 1) && (vFirstCharacterCode == 0x002D))
			{
				vReturn.push_back('\\');
				this->cpp_appendUnsignedCharAsHexDigitsTo(&vReturn, vFirstCharacterCode);
				vReturn.push_back(' ');
			}
			else
			{
				while(tI < vLength)
				{
					unsigned char tCharacterCode = static_cast<unsigned char>(pString[tI]);
					
					if(tCharacterCode == 0x0000) 
						{vReturn.append(this->utf8Chr(0xFFFD));}
					/*else if(((tCharacterCode >= 0x0001) && (tCharacterCode <= 0x001F)) || (tCharacterCode == 0x007F) ||
							((tI == 0) && (tCharacterCode >= 0x0030) && (tCharacterCode <= 0x0039)) ||				
							((tI == 1) && (tCharacterCode >= 0x0030) && (tCharacterCode <= 0x0039) &&
									(vFirstCharacterCode == 0x002D)))*/
					else if(((tCharacterCode >= 0x0001) && (tCharacterCode <= 0x001F) /*[:CNTRL]*/) || 
							(tCharacterCode == 0x007F /*[:CNTRL]*/) || (tCharacterCode == 0x003A /*:*/) ||
							((tI == 0) && (((tCharacterCode >= 0x0030) && (tCharacterCode <= 0x0039) /*[0-9]*/) ||
									(tCharacterCode == 0x005F) /*_*/)) ||
							((tI == 1) && ((tCharacterCode >= 0x0030) && (tCharacterCode <= 0x0039) /*[0-9]*/) &&
									(vFirstCharacterCode == 0x002D /*-*/)))
					{
						vReturn.push_back('\\');
						this->cpp_appendUnsignedCharAsHexDigitsTo(&vReturn, tCharacterCode);
						vReturn.push_back(' ');
					}
					/*else if((tI == 0) && (vLength == 1) && (tCharacterCode == 0x002D))
						{vReturn += '\\' + pString.charAt(tI);}*/
					else if((tCharacterCode >= 0x0080 /*NON ASCII*/) || (tCharacterCode == 0x002D /*-*/) ||
							((tCharacterCode >= 0x0030) && (tCharacterCode <= 0x0039) /*[0-9]*/) ||
							((tCharacterCode >= 0x0041) && (tCharacterCode <= 0x005A) /*[A-Z]*/) ||
							(tCharacterCode == 0x005F /*_*/) ||
							((tCharacterCode >= 0x0061) && (tCharacterCode <= 0x007A) /*[a-z]*/))
						{vReturn.push_back(pString[tI]);}
					else
					{
						vReturn.push_back('\\');
						vReturn.push_back(pString[tI]);
					}

					tI = tI + 1;
				}
			}

			return vReturn;
		}
		CRX_PUBLIC ::std::string Security::cageCssHexValue(::std::string const & pString)
		{
			if((pString.size() == 3) || (pString.size() == 6))
			{
				for(size_t tI = 0; tI < pString.size(); tI++)
				{
					unsigned char tCharacterCode = static_cast<unsigned char>(pString[tI]);

					if(!(((tCharacterCode >= 0x0030) && (tCharacterCode <= 0x0039) /*[0-9]*/) ||
							((tCharacterCode >= 0x0041) && (tCharacterCode <= 0x0046) /*[a-f]*/) ||
							((tCharacterCode >= 0x0061) && (tCharacterCode <= 0x0066) /*[A-F]*/)))
						{return this->cageCssIdentifier(pString);}
				}
				
				return pString;
			}
			else
				{return this->cageCssIdentifier(pString);}
		}
		CRX_PUBLIC ::std::string Security::cageCssString(::std::string const & pString)
			{return this->cageCssIdentifier(pString);/*CAN BE FASTER. SEE THE JS PORT*/}
		CRX_PUBLIC ::std::string Security::cageJsValue(::crx::Var const & pJsValue)
			{return pJsValue.convertToJsonUtf8String();}
		CRX_PUBLIC ::std::string Security::cageJsValue(::crx::Var pJsValue)
			{return pJsValue.convertToJsonUtf8String();}
		
	//SANITIZERS: THESE FUNCTIONS SANITIZE CODE FROM JAVASCRIPT. 
	//		- NOTE THAT THE CODE CONTEXT MUST BE NOT JAVASCRIPT ITSELF!
	//
		CRX_PUBLIC ::std::string Security::sanitizeTextForHtmlAttribute(::std::string const & pUrl)
		{
			std::string vUrl = this->cpp_removeControlCharactersFrom1(pUrl);
			std::string tUrl = "";
			boost::match_results<std::string::const_iterator> vMatchResults; /*= boost::match_results<std::string::const_iterator>()*/
			boost::regex vRegex("^([^:]+:).+");
			
			if(this->gNonJavaScriptUrlProtocolsRegexParts == NULL)
				{this->buildNonJavaScriptUrlProtocolRegexParts();}

			while(tUrl != vUrl)
			{
				tUrl = vUrl;			

				if(boost::regex_match(vUrl, vMatchResults, vRegex))
				{
					std::string tProtocol = this->cpp_trimString1(vMatchResults[1]);
					bool tIsMatchNotFound = true;

					std::transform(tProtocol.begin(), tProtocol.end(), 
								tProtocol.begin(), ::tolower);

					for(std::size_t tI = 0; tI < this->gNonJavaScriptUrlProtocolsRegexParts->size(); tI++)
					{
						//vMatchResults = NULL;

						if(boost::regex_match(tProtocol, vMatchResults, ::boost::regex(::std::string("^\\s*") + 
								((*(this->gNonJavaScriptUrlProtocolsRegexParts))[tI]) + ":", ::boost::regex::icase)))
						{
							tIsMatchNotFound = false;						
							break;
						}
					}
					if(tIsMatchNotFound)
						{vUrl = this->regexReplace(::boost::regex(this->cageRegexText(tProtocol), ::boost::regex::icase), "", vUrl);}
				}
				vUrl = this->regexReplace(::boost::regex("^\\s*&\\s*{", ::boost::regex::icase), "", vUrl);
			}

			return vUrl;
		}
		CRX_PUBLIC ::std::string Security::sanitizeUrlForHtmlAttribute(::std::string const & pUrl)
			{return this->sanitizeTextForHtmlAttribute(pUrl);}
		CRX_PUBLIC ::std::string Security::sanitizeCssValue(::std::string const & pCssValue)
		{
			::std::string vCSSValue = this->cpp_removeControlCharactersFrom1(pCssValue);
			::std::string tCSSValue /*= ""*/; 
		
			while(tCSSValue != vCSSValue)
			{
				tCSSValue = vCSSValue;
				vCSSValue = this->regexReplace(
						::boost::regex("^\\s*e\\s*x\\s*p\\s*r\\s*e\\s*s\\s*s\\s*i\\s*o\\s*n\\s*\\(", 
						::boost::regex::icase), "", vCSSValue);
				vCSSValue = this->regexReplace(
						::boost::regex("\\s*j\\s*a\\s*v\\s*a\\s*s\\s*c\\s*r\\s*i\\s*p\\s*t\\s*:", 
						::boost::regex::icase), "", vCSSValue);
				vCSSValue = this->regexReplace(
						::boost::regex("\\s*v\\s*b\\s*s\\s*c\\s*r\\s*i\\s*p\\s*t\\s*:",
						::boost::regex::icase), "", vCSSValue);
				vCSSValue = this->regexReplace(
						::boost::regex("\\s*l\\s*i\\s*v\\s*e\\s*s\\s*c\\s*r\\s*i\\s*p\\s*t\\s*:", 
						::boost::regex::icase), "", vCSSValue);
				vCSSValue = this->regexReplace(::boost::regex("\\s*&\\s*{", ::boost::regex::icase), "", vCSSValue);
			}

			return vCSSValue;
		}

	//ROOTERS: THESE FUNCTION ENSURE GIVEN URLS START FROM THE ROOT URL, MEANING '/'.
		/*public final function rootUrlForHtmlAttribute($pUrl)
			{return $this->rootPath($this->regexReplace("/[[:cntrl:]]/","", $pUrl));}*/

	//GROUNDERS: THESE FUNCTION ENSURE GIVEN URLS START FROM THE CURRENT SERVER.
		/*public final function groundUrlForHtmlAttribute($pUrl)
			{return $this->groundPath($this->regexReplace("/[[:cntrl:]]/","", $pUrl));}*/

	//CLEANERS: THESE FUNCTION PERFORM FULL CLEANING OPERATIONS. EACH IS A COMPOUND OF A COMBINATION
	//		OF CAGERS, SANITIZERS AND GROUNDERS. CLEANERS PROVIDE THE FINAL ENCODING NEEDED.
	//		NOTE THAT A CLEANER CAN NOT BE A COMPOUND OF MORE THAN ONE CAGER. IF THIS IS THE CASE
	//			SOMETHING IS WRONG.
	//		NOTE THAT THE FOLLOWING ONLYL PROVIDES CLEANERS FOR COMMON CASES.
		CRX_PUBLIC ::std::string Security::cleanTextForHtmlAttribute(::std::string const & pUrl)
		{
			//NOTE THAT IN THE FOLLOWING LINE, DECODING IS HAPPENING, AND THEN ENCODING WHICH HAPPENS
			//	IN cageHtmlAttribute. THIS IS USEFULL AS IT KILLS ENCODING THAT USE ZERO PADDING AND
			//	NO SEMICOLONS. EXAMPLE '&#0000106'. THE ENCODING ADDS SEMICOLON TO THE ENCODING OF
			//	'&', AND THEN THE BROWSER TREATS THE WHOLE STRING AS IF REQUIRING ENCODING WITH
			//	SEMICOLON
			return this->cageHtmlAttribute(this->sanitizeTextForHtmlAttribute(
					this->cpp_trimString1(this->decodeHtml(pUrl))));//trim($this->decodeHtmlAndUrl($pUrl))));
		}
		CRX_PUBLIC ::std::string Security::cleanTextForUrlAttribute(::std::string const & pUrl)
		{
			return this->cageHtmlAttribute(this->sanitizeTextForHtmlAttribute(
					this->cpp_trimString1(this->decodeHtml(pUrl))));//trim($this->decodeHtmlAndUrl($pUrl)))));
		}

	//PROCESSOR: HTML
	//
	//
		CRX_PROTECTED ::std::string Security::tryToGetDomNodeInnerRawContent(::pugi::xml_node * pDomElement)
		{
			::std::string vReturn /*= ""*/; 

			/*foreach($pDomElement->childNodes as $tChild) 
				//{$vReturn .= $pDomElement->ownerDocument->saveXML($tChild);}
				{$vReturn .= $pDomElement->ownerDocument->saveHTML($tChild);}
				//{$vReturn .= $tChild->C14N();}*/
			
			for(::pugi::xml_node tNode = pDomElement->first_child(); !!tNode; tNode = tNode.next_sibling())
				{this->regenerateHtmlElementBecauseOfCpp(&tNode, &vReturn);}

			return vReturn; 
		}
		CRX_PROTECTED ::std::string Security::tryToGetDomNodeOuterRawContent(::pugi::xml_node * pDomElement)
		{
			::std::string vReturn /*= ""*/;

			this->regenerateHtmlElementBecauseOfCpp(pDomElement, &vReturn);

			return vReturn;
		}
		CRX_PRIVATE void Security::regenerateHtmlElementBecauseOfCpp(::pugi::xml_node * pDomElement, 
				::std::string * pProcessedHtml)
		{
			Security::XmlWriter vXmlWriter /*= ?*/;

			//WARNING: THE FOLLOWING IS ILL DEFINED. print() BELOW EXPECTS THE FIRST PARAMETER
			//		TO BE &::pugi::xml_writer. PER MY STANDARD, POLYMORPHISM MAY NOT BE ASSUMED
			//		FOR REFERENCES. UNFORTUANETLY pugixml ASSUMES POLYMORPHISM
			pDomElement->print(vXmlWriter, PUGIXML_TEXT("\t"), ::pugi::format_raw);

			pProcessedHtml->append(vXmlWriter.gString);
		}

		CRX_PROTECTED ::pugi::xml_document * CRX_PASSING Security::getParsedHtml(::std::string const & pString, 
				bool pIsToThrowOnError CRX_DEFAULT(true))
		{
			unsigned int vOPTIONS = ::pugi::parse_default & ~pugi::parse_declaration &
					~pugi::parse_doctype & ~pugi::parse_pi & ~pugi::parse_comments &
					pugi::parse_cdata & ~pugi::parse_trim_pcdata &
					~pugi::parse_ws_pcdata & ~pugi::parse_ws_pcdata_single &
					~pugi::parse_embed_pcdata & ::pugi::parse_embed_pcdata &
					~pugi::parse_escapes & ~pugi::parse_eol &
					pugi::parse_wconv_attribute;
			pugi::xml_document * vReturn = NULL; 	//TO STICK TO THE NORMAL FORM, A POINTER IS USED 
													//UNFORTUANETLY. SEE OTHER PORTS.

			try
			{
				pugi::xml_parse_result tParseResult;

				vReturn = new ::pugi::xml_document();
				tParseResult = vReturn->load_buffer(pString.c_str(), pString.size(),
						vOPTIONS, ::pugi::encoding_utf8);

				if(!tParseResult)
				{
					delete vReturn;
					vReturn = NULL;

					if(pIsToThrowOnError)//UNSURE IF load_buffer WILL ALWAYS THROW
						{throw tParseResult;}
				}
			}
			catch(...)
			{
				if(vReturn != NULL)
				{
					delete vReturn;
					vReturn = NULL;
				}
				
				if(pIsToThrowOnError)
					{throw;}
			}

			return vReturn;
		}
		CRX_PROTECTED ::std::string Security::processParsedHtml(::pugi::xml_document * pDomDocument)
		{
			std::string vProcessedHtml = "";

			this->onProcessHTMLStart();

			try
			{
				if(pDomDocument == NULL)
					{}
				else
				{
					for(pugi::xml_node tNode = pDomDocument->first_child(); !!(tNode); 
								tNode = tNode.next_sibling())
					{
						//echo "processHtml:".$tChild->nodeName."<br/>";
						this->processHtmlElement("", &tNode, &vProcessedHtml);
					}
				}
			}
			catch(...)
			{
				this->onProcessHTMLEnd();

				throw;
			}

			this->onProcessHTMLEnd();

			return vProcessedHtml;
		}
		CRX_PUBLIC ::std::string Security::processHtml(::std::string const & pString)
		{
			::std::string vProcessedHtml /*= ""*/;
			::pugi::xml_document * vDocument = NULL;

			this->onProcessHTMLStart();

			try
			{
				::pugi::xml_document * tDocument = this->getParsedHtml(pString, true);

				for(::pugi::xml_node tNode = vDocument->first_child(); !!(tNode); 
						tNode = tNode.next_sibling())
				{
					//echo "processHtml:".$tChild->nodeName."<br/>";
					this->processHtmlElement("", &tNode, &vProcessedHtml);			
				}

				delete vDocument;
				vDocument = NULL;
			}
			catch(...)
			{
				this->onProcessHTMLEnd();

				if(vDocument != NULL)
				{
					delete vDocument;
					vDocument = NULL;
				}

				throw;
			}

			this->onProcessHTMLEnd();

			return vProcessedHtml;
		}
		CRX_PRIVATE void Security::processHtmlElement(::std::string const & pParentElementName, ::pugi::xml_node * pDomElement, ::std::string * pProcessedHtml)
		{
			//echo "processHtmlElement:".$pDomElement->nodeName."<br/>";		

			::std::string vElementName = pDomElement->name();
			bool vIsToIgnoreCurrentElementButProcessChildren = false;
			::std::string vTempString = "";
			Security_ElementData vElementData /*= ?*/;
			
			std::transform(vElementName.begin(), vElementName.end(), 
					vElementName.begin(), ::tolower);
			pDomElement->set_name(vElementName.c_str());

			vIsToIgnoreCurrentElementButProcessChildren = ((vElementName == "html") || 
					(vElementName == "body") || 
					(vElementName == "head"));
			/*
			* nameOfParent: THE NAME OF THE PARENT HTML ELEMENT. THIS IS READ ONLY.
			* name: THE NAME OF THE HTML ELEMENT. THE VALUE MAY NOT BE EMPTY.
			* isToProcessBodyOnly: THIS INDICATED WHETHER THE ELEMENT SIGNATURE (NAME AND ATTRTIBUTES)
			*		IS TO BE PROCESSED.
			* mayHasChildElements: THIS INDICATES WHETHER THE ELEMENT MAY HAS CHILD HTML ELEMENTS.
			* mayHasTextContent: THIS INDICATES WHETHER THE ELEMENT MAY HAS CHILD TEXT OR CDDATA 
			*		NODES.
			* mayHasAttributes: THIS INDICATES WHETHER THE ELEMENT MAY HAS ATTRIBUTES
			* prependedTextToBody: TEXT TO BE PREPENDED TO THE ELEMENT'S BODY.
			* appendedTextToBody: TEXT TO APPEND TO THE ELEMENT'S BODY.
			*/
			vElementData = Security_ElementData(pParentElementName, 
					vElementName, false, true, true, true, "", "", false, false);		

			if(vIsToIgnoreCurrentElementButProcessChildren || 
					this->filterHtmlElement(&vElementData, *pDomElement))
			{
				if(vIsToIgnoreCurrentElementButProcessChildren)
				{
					vElementData.gIsToProcessBodyOnly = true;
					vElementData.gPrependedTextToBody = "";
					vElementData.gAppendedTextToBody = "";			
				}

				vElementData.gIsToTreatWrapperAsTextOnly = false; //BECAUSE NOT WORKING, DISABLING.
				vElementData.gIsToTreatContentAsTextOnly = false; //BECAUSE NOT WORKING, DISABLING.

				if(!vElementData.gIsToProcessBodyOnly)
				{
					pugi::xml_attribute tAttribute = pDomElement->first_attribute();

					if(!vElementData.gIsToTreatWrapperAsTextOnly)
						{*pProcessedHtml += ::std::string("<") + vElementData.gName;}
					else
						{vTempString += ::std::string("<") + vElementData.gName;}

					if(vElementData.gMayHasAttributes && !!tAttribute)
					{
						for(; !!tAttribute; tAttribute = tAttribute.next_attribute())
						{
							/*switch(tAttribute nodeType)
							{
								case XML_ATTRIBUTE_NODE:
									//echo("processHtmlElement:XML_ATTRIBUTE_NODE<br/>");*/
							if(!vElementData.gIsToTreatWrapperAsTextOnly)
							{
								this->processHtmlAttribute(vElementData.gName, &tAttribute,
										pProcessedHtml, false);
							}
							else
							{
								this->processHtmlAttribute(vElementData.gName, &tAttribute,
										&vTempString, true);
							}

								/*break;
							}*/
						}
					}
				}

				if(vElementData.gMayHasTextContent || 
						(!vElementData.gIsToTreatContentAsTextOnly && vElementData.gMayHasChildElements))
				{
					::pugi::xml_node tNode = pDomElement->first_child();

					if(!vElementData.gIsToProcessBodyOnly)
					{
						if(!vElementData.gIsToTreatWrapperAsTextOnly)
							{*pProcessedHtml += ">";}
						else
							{vTempString += ">";}
					}

					if(!this->cpp_isStringEmpty(vElementData.gPrependedTextToBody))
					{
						if(vElementData.gIsToTreatWrapperAsTextOnly)
						{
							*pProcessedHtml += this->sieveHtmlElementText(vElementData.gName, 
									vTempString, false);
							vTempString = "";
						}

						*pProcessedHtml += vElementData.gPrependedTextToBody;
					}

					if(!!tNode)
					{
						if(vElementData.gIsToTreatContentAsTextOnly)
							{vTempString += this->tryToGetDomNodeInnerRawContent(pDomElement);}
						else
						{
							for(; !!tNode; tNode = tNode.next_sibling())
							{
								switch(tNode.type())
								{
									//VC6 case ::pugi::xml_node_type::node_element:
									case ::pugi::node_element:
										if(!vElementData.gMayHasChildElements)
											{continue;}
										//echo("processHtmlElement:XML_ELEMENT_NODE<br/>");
										this->processHtmlElement(vElementData.gName, &tNode, 
												pProcessedHtml);
										break;						
									case ::pugi::node_pcdata:
									case ::pugi::node_cdata:
										if(!vElementData.gMayHasTextContent)
											{continue;}
									
										//echo("processHtmlElement:XML_TEXT_NODE<br/>");
										*pProcessedHtml += this->sieveHtmlElementText(vElementData.gName, 
												tNode.text().as_string(), 
												(tNode.type() == ::pugi::node_cdata));
										break;
									default:
										//echo("processHtmlElement:default ({$tChild->nodeType})<br/>");
										//unset($tChild);
										break;
								}
							}
						}
					}

					if(!vElementData.gIsToProcessBodyOnly)
					{
						if(!vElementData.gIsToTreatWrapperAsTextOnly)
						{
							*pProcessedHtml += vElementData.gAppendedTextToBody +
									"</" + vElementData.gName + ">";
						}
						else
						{
							vTempString += vElementData.gAppendedTextToBody +
								"</" + vElementData.gName + ">";
						}
					}

					if(!this->cpp_isStringEmpty(vTempString))
					{
						*pProcessedHtml += this->sieveHtmlElementText(vElementData.gName, 
								vTempString, false);
						vTempString = "";
					}
				}
				else
				{
					if((vElementData.gAppendedTextToBody != "") || 
							(vElementData.gPrependedTextToBody != ""))
					{
						if(!vElementData.gIsToProcessBodyOnly)
						{
							if(!vElementData.gIsToTreatWrapperAsTextOnly)
								{*pProcessedHtml += ">";}
							else
							{
								vTempString += ">";
								*pProcessedHtml += this->sieveHtmlElementText(vElementData.gName, 
										vTempString, false);
								vTempString = "";
							}
						}

						*pProcessedHtml += vElementData.gPrependedTextToBody +
								vElementData.gAppendedTextToBody;

						if(!vElementData.gIsToProcessBodyOnly)
						{
							if(!vElementData.gIsToTreatWrapperAsTextOnly)
								{*pProcessedHtml += ::std::string("</") + vElementData.gName + ">";}
							else
							{
								vTempString += ::std::string("</") + vElementData.gName + ">";
								*pProcessedHtml += this->sieveHtmlElementText(vElementData.gName, 
										vTempString, false);
								vTempString = "";
							}
						}
					}
					else if(!vElementData.gIsToProcessBodyOnly)
					{
						if(!vElementData.gIsToTreatWrapperAsTextOnly)
							{*pProcessedHtml += " />";}
						else
						{
							vTempString += " />";
							*pProcessedHtml += this->sieveHtmlElementText(vElementData.gName, 
									vTempString, false);
							vTempString = "";
						}
					}
				}

				if(!vIsToIgnoreCurrentElementButProcessChildren)
					{this->onElementClose(&vElementData);}
			}
		}
		CRX_PRIVATE void Security::processHtmlAttribute(::std::string const & pElementName,
				::pugi::xml_attribute * pAttribute, ::std::string * pProcessedHtml, 
				bool pIsBuildingOnly CRX_DEFAULT(false))
		{		
			//echo "processHtmlAttribute:".$pDomElement->nodeName."<br/>";

			::std::string vAttributeName = pAttribute->name();
			Security_AttributeData vAttributeData(pElementName, 
					""/*pAttribute->name*/, "", false);

			::std::transform(vAttributeName.begin(), vAttributeName.end(), 
					vAttributeName.begin(), ::tolower);
			pAttribute->set_name(vAttributeName.c_str());
			vAttributeData.gName = vAttributeName;

			if(!!(*pAttribute))
			{
				vAttributeData.gValue = pAttribute->as_string();
				vAttributeData.gWasValueSet = true; //REQUIRES TESTING. TRY AN ATTRIBUTE WITHOUT VALUE TO SEE WHAT HAPPENS

				if(pIsBuildingOnly || this->filterHtmlAttributeAndValue(pElementName, &vAttributeData))
				{
					*pProcessedHtml += " " + vAttributeData.gName + "=\"" + 
							this->cageHtmlAttribute(vAttributeData.gValue) + "\"";
				}
			}
			else
			{
				vAttributeData.gValue = (pIsBuildingOnly ? "" : vAttributeData.gName);

				if(pIsBuildingOnly || this->filterHtmlAttributeAndValue(pElementName, &vAttributeData))
				{
					*pProcessedHtml += " " + vAttributeData.gName + "=\"" +
							this->cageHtmlAttribute(vAttributeData.gValue) + "\"";
				}
			}
		}

		CRX_PROTECTED_VIRTUAL void Security::onProcessHTMLStart()
			{}
		CRX_PROTECTED_VIRTUAL void Security::onProcessHTMLEnd()
			{}
		CRX_PROTECTED_VIRTUAL bool Security::filterHtmlElement(Security_ElementData * CRX_NOT_NULL pElementData, 
				::pugi::xml_node const & pNode)
			{return this->gSecurityProtocol->filterHtmlElement(this, pElementData, pNode);}
		CRX_PROTECTED_VIRTUAL bool Security::filterHtmlAttributeAndValue(::std::string const & pElementName,
				Security_AttributeData * CRX_NOT_NULL pAttributeData)
		{
			return this->gSecurityProtocol->
					filterHtmlAttributeAndValue(this, pElementName, pAttributeData);
		}
		CRX_PROTECTED_VIRTUAL ::std::string Security::sieveHtmlElementText(::std::string const & pElementName,
				::std::string const & pText, bool pIsCDATA)
		{
			return this->gSecurityProtocol->
					sieveHtmlElementText(this, pElementName, pText, pIsCDATA);
		}
		CRX_PROTECTED_VIRTUAL void Security::onElementClose(Security_ElementData * CRX_NOT_NULL pElementData)
			{}
	
		CRX_PROTECTED ::std::string Security::processHtmlDomBranch(Security_ElementData * CRX_NOT_NULL pElementData_Root, 
				::pugi::xml_node * pDomElement_Root)
		{
			::std::string vProcessedHtml /*= ""*/;

			for(::pugi::xml_node tNode = pDomElement_Root->first_child(); !!(tNode); 
					tNode = tNode.next_sibling())
			{
				//echo "processHTMLDomBranch:".$tChild->nodeName."<br/>";
				//$vProcessedHtml .= "processHtmlDomBranch:".$tChild->nodeName."<br/>";
			
				switch(tNode.type())
				{
					case ::pugi::node_element:
						//echo("processHTMLDomBranch:XML_ELEMENT_NODE<br/>");
						this->processHtmlElement(pElementData_Root->gName, &tNode,
								&vProcessedHtml);
						break;						
					case ::pugi::node_pcdata:
					case ::pugi::node_cdata:
						if(!pElementData_Root->gMayHasTextContent)
							{continue;}
					
						//echo("processHTMLDomBranch:XML_TEXT_NODE<br/>");
						vProcessedHtml += this->sieveHtmlElementText(pElementData_Root->gName,
								tNode.text().as_string(), 
								(tNode.type() == ::pugi::node_cdata));
						break;
					default:
						//echo("processHtmlElement:default ({$tChild->nodeType})<br/>");
						//unset($tChild);
						break;
				}		
			}

			return vProcessedHtml;
		}

	//PROCESSOR: CSS
	//
	//
		CRX_PUBLIC ::std::string Security::processCss(::std::string const & pString)
		{
			//echo "processInlineCss: ".$this->cageHtmlText($pString)."<br/>";
			Crx_C_Error_Error vError /*= ?*/;
			Crx_C_CrxCss_BlockElement * vBlockElement = NULL;
			::std::string vProcessedCss = "";
			
			crx_c_error_error_construct(&vError, 0);

			vBlockElement = crx_c_crxCss_parseCrxCss3(pString.c_str(), pString.size(), &vError);

			if(crx_c_error_error_isError(&vError))
			{
				::std::string tString = "";
				
				tString.append("\nERROR: processCSS\n");

				for(size_t tI = 0; tI < crx_c_error_error_getLength(&vError); tI++)
				{
					Crx_C_Error_ErrorElement * tErrorElement = crx_c_error_error_get(&vError, tI);

					if(tErrorElement->gMessage != NULL)
					{
						tString.append(
								crx_c_string_constantGetCharsPointer(tErrorElement->gMessage),
								crx_c_string_getSize(tErrorElement->gMessage));
						tString.push_back('\n');
					}
				}


				crx_c_error_error_destruct(&vError);

				if(vBlockElement != NULL)
				{
					crx_c_crxCss_blockElement_destruct(vBlockElement);
					::free(vBlockElement);
				}
				
				throw tString; return "";
			}

			if(crx_c_crxCss_blockElement_getType(vBlockElement) == 
					CRX__C__CRX_CSS__TYPE__AT_RULE_ELEMENT)
			{
				Crx_C_CrxCss_AtRuleElement * tAtRuleElement = 
						crx_c_crxCss_blockElement_getAtRuleElement(vBlockElement);
				
				for(size_t tI = 0; tI < crx_c_crxCss_block_getLength(tAtRuleElement->gBlock); tI++)
				{
					this->crxCss_processBlockElement(crx_c_crxCss_block_get(
							tAtRuleElement->gBlock, tI), &vProcessedCss, 0);
				}
			}
			else if(crx_c_crxCss_blockElement_getType(vBlockElement) == 
					CRX__C__CRX_CSS__TYPE__AT_RULE_NAME_VALUE_BLOCK)
			{
				Crx_C_CrxCss_AtRuleNameValueBlock * tAtRuleNameValueBlock = 
						crx_c_crxCss_blockElement_getAtRuleNameValueBlock(vBlockElement);

				for(size_t tI = 0; 
						tI < crx_c_crxCss_nameValueBlock_getLength(&(tAtRuleNameValueBlock->gNameValueBlock));
						tI++)
				{
					this->crxCss_processCssNameValuePair(
							crx_c_crxCss_nameValueBlock_get(&(tAtRuleNameValueBlock->gNameValueBlock), tI),
							"crx_root", "", &vProcessedCss, 0);
				}
			}

			crx_c_error_error_destruct(&vError);

			if(vBlockElement != NULL)
			{
				crx_c_crxCss_blockElement_destruct(vBlockElement);
				::free(vBlockElement);
			}

			return vProcessedCss;
		}
		CRX_PUBLIC ::std::string Security::processInlineCss(::std::string const & pString)
		{
			Crx_C_Error_Error vError /*= ?*/;
			Crx_C_CrxCss_BlockElement * vBlockElement = NULL;
			::std::string vProcessedCss = "";
			
			crx_c_error_error_construct(&vError, 0);

			vBlockElement = crx_c_crxCss_parseCrxCss3(pString.c_str(), pString.size(), &vError);

			if(crx_c_error_error_isError(&vError))
			{
				::std::string tString = "";
				
				tString.append("\nERROR: processInlineCss\n");

				for(size_t tI = 0; tI < crx_c_error_error_getLength(&vError); tI++)
				{
					Crx_C_Error_ErrorElement * tErrorElement = crx_c_error_error_get(&vError, tI);

					if(tErrorElement->gMessage != NULL)
					{
						tString.append( 
								crx_c_string_constantGetCharsPointer(tErrorElement->gMessage),
								crx_c_string_getSize(tErrorElement->gMessage));
						tString.push_back('\n');
					}
				}


				crx_c_error_error_destruct(&vError);

				if(vBlockElement != NULL)
				{
					crx_c_crxCss_blockElement_destruct(vBlockElement);
					::free(vBlockElement);
				}
				
				throw tString; return "";
			}

			if(crx_c_crxCss_blockElement_getType(vBlockElement) == 
					CRX__C__CRX_CSS__TYPE__AT_RULE_NAME_VALUE_BLOCK)
			{
				Crx_C_CrxCss_AtRuleNameValueBlock * tAtRuleNameValueBlock = 
						crx_c_crxCss_blockElement_getAtRuleNameValueBlock(vBlockElement);

				for(size_t tI = 0; 
						tI < crx_c_crxCss_nameValueBlock_getLength(&(tAtRuleNameValueBlock->gNameValueBlock));
						tI++)
				{
					this->crxCss_processCssNameValuePair(
							crx_c_crxCss_nameValueBlock_get(&(tAtRuleNameValueBlock->gNameValueBlock), tI),
							"crx_root", "", &vProcessedCss, 0);
				}
			}

			crx_c_error_error_destruct(&vError);

			if(vBlockElement != NULL)
			{
				crx_c_crxCss_blockElement_destruct(vBlockElement);
				::free(vBlockElement);
			}

			return vProcessedCss;
		}
		CRX_PRIVATE void Security::crxCss_processBlockElement(
				Crx_C_CrxCss_BlockElement * CRX_NOT_NULL pBlockElement, 
				::std::string * CRX_NOT_NULL pProcessedCss, int * CRX_NOT_NULL pLevel)
		{
			Crx_C_CrxCss_Type vType = crx_c_crxCss_blockElement_getType(pBlockElement);

			if(vType == CRX__C__CRX_CSS__TYPE__AT_RULE_ELEMENT)
			{
				this->crxCss_processAtRuleElement(crx_c_crxCss_blockElement_getAtRuleElement(pBlockElement),
						pProcessedCss, pLevel);
			}
			else if(vType == CRX__C__CRX_CSS__TYPE__REFERENCE_NAME_VALUE_BLOCK)
			{
				this->crxCss_processReferenceNameValueBlock(
						crx_c_crxCss_blockElement_getReferenceNameValueBlock(pBlockElement),
						pProcessedCss, pLevel);
			}
			else if(vType == CRX__C__CRX_CSS__TYPE__AT_RULE_STATEMENT)
			{
				this->crxCss_processAtRuleStatement(crx_c_crxCss_blockElement_getAtRuleStatement(pBlockElement),
						pProcessedCss, pLevel);
			}
			else if(vType == CRX__C__CRX_CSS__TYPE__AT_RULE_NAME_VALUE_BLOCK)
			{
				this->crxCss_processAtRuleNameValueBlock(
						crx_c_crxCss_blockElement_getAtRuleNameValueBlock(pBlockElement),
						pProcessedCss, pLevel);
			}
		}
		CRX_PRIVATE void Security::crxCss_processAtRuleStatement(
				Crx_C_CrxCss_AtRuleStatement * CRX_NOT_NULL pAtRuleStatement,
				::std::string * CRX_NOT_NULL pProcessedCss, int * CRX_NOT_NULL pLevel)
		{
			//echo "sabberworm_processCrxCssAtRule__processAtRule: AtRuleStatement<br/>";
			Security_CrxCssAtRuleStatementData vCrxCssAtRuleStatementData(
					::std::string(crx_c_string_constantGetCharsPointer(&(pAtRuleStatement->gName)), 
							crx_c_string_getSize(&(pAtRuleStatement->gName))),
					::std::string(crx_c_string_constantGetCharsPointer(&(pAtRuleStatement->gValue)), 
							crx_c_string_getSize(&(pAtRuleStatement->gValue))),
					pAtRuleStatement);
					
			if(this->filterCrxCssAtRuleStatement(&vCrxCssAtRuleStatementData) &&
					(vCrxCssAtRuleStatementData.gName != ""))
			{
				pProcessedCss->append("@");
				pProcessedCss->append(this->processCageCrxCssAtRuleName(vCrxCssAtRuleStatementData.gName));
				pProcessedCss->append(" ");
				pProcessedCss->append(processCageCrxCssAtRuleValue(vCrxCssAtRuleStatementData.gValue));
				pProcessedCss->append(";");
			}
		}
		CRX_PRIVATE void Security::crxCss_processAtRuleElement(
				Crx_C_CrxCss_AtRuleElement * CRX_NOT_NULL pAtRuleElement,
				::std::string * CRX_NOT_NULL pProcessedCss, int * CRX_NOT_NULL pLevel)
		{
			//echo "sabberworm_processCrxCssAtRule__processAtRuleBlockList: AtRule Element<br/>";
			Security_CrxCssAtRuleElementData vCrxCssAtRuleElementData(::std::string(
							crx_c_string_constantGetCharsPointer(&(pAtRuleElement->gName)), 
							crx_c_string_getSize(&(pAtRuleElement->gName))), 
					::std::string(crx_c_string_constantGetCharsPointer(&(pAtRuleElement->gValue)), 
							crx_c_string_getSize(&(pAtRuleElement->gValue))),
					pAtRuleElement);

			if(this->filterCrxCssAtRuleElement(&vCrxCssAtRuleElementData) &&
					(vCrxCssAtRuleElementData.gName != ""))
			{
				if(!vCrxCssAtRuleElementData.gIsToProcessBodyOnly)
				{
					pProcessedCss->append("@");
					pProcessedCss->append(this->processCageCrxCssAtRuleName(vCrxCssAtRuleElementData.gName));
					pProcessedCss->append(" ");
					pProcessedCss->append(this->processCageCrxCssAtRuleValue(vCrxCssAtRuleElementData.gValue));
					pProcessedCss->append("{");
				}
				
				if(vCrxCssAtRuleElementData.gPrependedTextToBody != "")
					{pProcessedCss->append(vCrxCssAtRuleElementData.gPrependedTextToBody);}

				if(vCrxCssAtRuleElementData.gMayHasChildren)
				{
					*pLevel = *pLevel + 1;

					for(size_t tI = 0; tI < crx_c_crxCss_block_getLength(pAtRuleElement->gBlock); tI++)
					{
						this->crxCss_processBlockElement(crx_c_crxCss_block_get(
								pAtRuleElement->gBlock, tI), pProcessedCss, pLevel);
					}

					*pLevel = *pLevel - 1;
				}

				if(vCrxCssAtRuleElementData.gAppendedTextToBody != "")
					{pProcessedCss->append(vCrxCssAtRuleElementData.gAppendedTextToBody);}

				if(!vCrxCssAtRuleElementData.gIsToProcessBodyOnly)
					{pProcessedCss->append("}");}
			}
		}
		CRX_PRIVATE void Security::crxCss_processAtRuleNameValueBlock(
				Crx_C_CrxCss_AtRuleNameValueBlock * CRX_NOT_NULL pAtRuleNameValueBlock,
				::std::string * CRX_NOT_NULL pProcessedCss, int * CRX_NOT_NULL pLevel)
		{
			//echo "sabberworm_processCrxCssAtRule__processAtRuleSet: ".$pAtRuleSet->atRuleName()."<br/>";
			
			Security_CrxCssAtRuleNameValueBlockData vCrxCssAtRuleNameValueBlockData(
					::std::string(crx_c_string_constantGetCharsPointer(&(pAtRuleNameValueBlock->gName)), 
							crx_c_string_getSize(&(pAtRuleNameValueBlock->gName))),
					::std::string(crx_c_string_constantGetCharsPointer(&(pAtRuleNameValueBlock->gValue)), 
							crx_c_string_getSize(&(pAtRuleNameValueBlock->gValue))),
					pAtRuleNameValueBlock);

			if(this->filterCrxCssAtRuleNameValueBlock(&vCrxCssAtRuleNameValueBlockData) &&
					(vCrxCssAtRuleNameValueBlockData.gName != ""))
			{
				pProcessedCss->append("@");
				pProcessedCss->append(this->processCageCrxCssAtRuleName(vCrxCssAtRuleNameValueBlockData.gName));
				pProcessedCss->append(" ");
				pProcessedCss->append(this->processCageCrxCssAtRuleValue(vCrxCssAtRuleNameValueBlockData.gValue));
				pProcessedCss->append("{");
				
				*pLevel = *pLevel + 1;
				
				//testCrxCss__processNameValueBlock(pString, pLevel, &(pAtRuleNameValueBlock->gNameValueBlock));
				for(size_t tI = 0; tI < crx_c_crxCss_nameValueBlock_getLength(&(pAtRuleNameValueBlock->gNameValueBlock)); 
						tI++)
				{
					this->crxCss_processCssNameValuePair(
							crx_c_crxCss_nameValueBlock_get(&(pAtRuleNameValueBlock->gNameValueBlock), tI),
							vCrxCssAtRuleNameValueBlockData.gName, vCrxCssAtRuleNameValueBlockData.gValue,
							pProcessedCss, pLevel);
				}
				
				*pLevel = *pLevel - 1;

				pProcessedCss->append("}");
			}
		}
		CRX_PRIVATE void Security::crxCss_processReferenceNameValueBlock(
				Crx_C_CrxCss_ReferenceNameValueBlock * CRX_NOT_NULL pReferenceNameValueBlock,
				::std::string * CRX_NOT_NULL pProcessedCss, int * CRX_NOT_NULL pLevel)
		{
			//echo "sabberworm_processCrxCssReferenceBlock"."<br/>";
			
			Security_CrxCssReferenceNameValueBlockData vCrxCssReferenceNameValueBlockData(
					pReferenceNameValueBlock, this);
					
			if(this->filterCrxCssReferenceNameValueBlock(&vCrxCssReferenceNameValueBlockData))
			{
				bool tIsFirst = true;
				bool tWereSelectorsFound = false;

				for(size_t tI = 0; tI < vCrxCssReferenceNameValueBlockData.gReferences.size(); tI++)
				{
					::std::string tSelectorText = this->cpp_trimString1(this->processCageCrxCssReference(
							vCrxCssReferenceNameValueBlockData.gReferences[tI].gName));
						
					if(!this->cpp_isStringEmpty(tSelectorText))
					{
						tWereSelectorsFound = true;

						if(!tIsFirst)
							{*pProcessedCss += ", ";}
						else
							{tIsFirst = false;}

						pProcessedCss->append(tSelectorText);
					}
				}
				
				if(tWereSelectorsFound)
				{
					tIsFirst = true;
					pProcessedCss->append("{");
					
					*pLevel = *pLevel + 1;

					//testCrxCss__processNameValueBlock(pString, pLevel, &(pReferenceNameValueBlock->gNameValueBlock));

					for(size_t tI = 0; tI < crx_c_crxCss_nameValueBlock_getLength(
							&(pReferenceNameValueBlock->gNameValueBlock)); tI++)
					{
						//echo get_class($tRule)."<br/>";

						this->crxCss_processCssNameValuePair2(
								crx_c_crxCss_nameValueBlock_get(&(pReferenceNameValueBlock->gNameValueBlock), tI),
								vCrxCssReferenceNameValueBlockData.gReferences, pProcessedCss, pLevel);
					}
					
					*pLevel = *pLevel - 1;
					
					pProcessedCss->append("}");
				}
			}
		}
		CRX_PRIVATE void Security::crxCss_processCssNameValuePair(
				Crx_C_CrxCss_NameValuePair * CRX_NOT_NULL pNameValuePair,
				::std::string const & pAtRuleName, ::std::string const & pAtRuleValue,
				::std::string * CRX_NOT_NULL pProcessedCss, int * CRX_NOT_NULL pLevel)
		{
			Security_CrxCssNameValuePairData vCrxCssNameValuePairData(pNameValuePair);

			if(!this->filterCrxCssNameValuePair(&vCrxCssNameValuePairData, pAtRuleName, pAtRuleValue))
			{
				/*APPEARS TO BE A RELIC OF THE PHP IMPLEMENTATION THAT MADE IT TO THE JAVASCRIPT IMPLEMENTATION
						BUT DOES NOTHING RELATED TO THE OLD APPRACH OF USING THE CSS PARSER IN PHP TO GENERATE
						THE CSS. KEEPING THIS FOR NOW UNTIL IT IS REMOVED FROM THE JS SIDE.
				*/
			}
			else
			{
				if(!crx_c_string_isEmpty(&(pNameValuePair->gName)))
				{
					pProcessedCss->append(this->processCageCrxCssName(vCrxCssNameValuePairData.gName));
					pProcessedCss->append(": ");
					pProcessedCss->append(this->processCageCrxCssValue(vCrxCssNameValuePairData.gValue));
					pProcessedCss->append(";");
				}
			}
		}
		CRX_PRIVATE void Security::crxCss_processCssNameValuePair2(
				Crx_C_CrxCss_NameValuePair * CRX_NOT_NULL pNameValuePair,
				::std::vector<Security_CrxCssReference> const & pReferences,
				::std::string * CRX_NOT_NULL pProcessedCss, int * CRX_NOT_NULL pLevel)
		{
			Security_CrxCssNameValuePairData vCrxCssNameValuePairData(pNameValuePair);

			if(!this->filterCrxCssNameValuePair2(&vCrxCssNameValuePairData, pReferences))
			{
				/*APPEARS TO BE A RELIC OF THE PHP IMPLEMENTATION THAT MADE IT TO THE JAVASCRIPT IMPLEMENTATION
						BUT DOES NOTHING RELATED TO THE OLD APPRACH OF USING THE CSS PARSER IN PHP TO GENERATE
						THE CSS. KEEPING THIS FOR NOW UNTIL IT IS REMOVED FROM THE JS SIDE.
				*/
			}
			else
			{
				if(!crx_c_string_isEmpty(&(pNameValuePair->gName)))
				{
					pProcessedCss->append(this->processCageCrxCssName(vCrxCssNameValuePairData.gName));
					pProcessedCss->append(": ");
					pProcessedCss->append(this->processCageCrxCssValue(vCrxCssNameValuePairData.gValue));
					pProcessedCss->append(";");
				}
			}
		}


		/*protected function filterCssCharset($pCharset)
			{return $this->gCrxSecurityProtocol->filterCssCharset($this, $pCharset);}
		protected function filterCssImport($pImport)
			{return $this->gCrxSecurityProtocol->filterCssImport($this, $pImport);}*/
		CRX_PROTECTED_VIRTUAL bool Security::filterCrxCssAtRuleElement(
				Security_CrxCssAtRuleElementData * CRX_NOT_NULL pCrxCssAtRuleElementData)
			{return this->gSecurityProtocol->filterCrxCssAtRuleElement(this, pCrxCssAtRuleElementData);}
		CRX_PROTECTED_VIRTUAL bool Security::filterCrxCssAtRuleStatement(
				Security_CrxCssAtRuleStatementData * CRX_NOT_NULL pCrxCssAtRuleStatementData)
			{return this->gSecurityProtocol->filterCrxCssAtRuleStatement(this, pCrxCssAtRuleStatementData);}
		CRX_PROTECTED_VIRTUAL bool Security::filterCrxCssAtRuleNameValueBlock(
				Security_CrxCssAtRuleNameValueBlockData * CRX_NOT_NULL pCrxCssAtRuleNameValueBlockData)
			{return this->gSecurityProtocol->filterCrxCssAtRuleNameValueBlock(this, pCrxCssAtRuleNameValueBlockData);}
		CRX_PROTECTED_VIRTUAL bool Security::filterCrxCssNameValuePair(
				Security_CrxCssNameValuePairData * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::string const & pAtRuleName, ::std::string const & pAtRuleValue)
			{return this->gSecurityProtocol->filterCrxCssNameValuePair(this, pCrxCssNameValuePairData, pAtRuleName, pAtRuleValue);}
		CRX_PROTECTED_VIRTUAL bool Security::filterCrxCssNameValuePair2(
				Security_CrxCssNameValuePairData * CRX_NOT_NULL pCrxCssNameValuePairData,
				::std::vector<Security_CrxCssReference> const & pReferences)
			{return this->gSecurityProtocol->filterCrxCssNameValuePair2(this, pCrxCssNameValuePairData, pReferences);}
		CRX_PROTECTED_VIRTUAL bool Security::filterCrxCssReferenceNameValueBlock(
				Security_CrxCssReferenceNameValueBlockData * CRX_NOT_NULL pCrxCssReferenceNameValueBlockData)
			{return this->gSecurityProtocol->filterCrxCssReferenceNameValueBlock(this, pCrxCssReferenceNameValueBlockData);}
			
		//
		CRX_PUBLIC ::std::string Security::processCageCrxCssAtRuleName(::std::string const & pString)
			{return this->cageCssIdentifier(pString);}
		CRX_PUBLIC ::std::string Security::processCageCrxCssName(::std::string const & pString)
			{return this->cageCssIdentifier(pString);}
		CRX_PUBLIC ::std::string Security::processCageCrxCssReference(::std::string const & pString)
		{
			return this->processCageCrxCssRuleOrValue(
					Security::PROCESS_CAGE_CRX_CSS_RULE_OR_VALUE__TYPE__REFERENCE, pString);
		}
		CRX_PUBLIC ::std::string Security::processCageCrxCssValue(::std::string const & pString)
		{
			return this->processCageCrxCssRuleOrValue(
					Security::PROCESS_CAGE_CRX_CSS_RULE_OR_VALUE__TYPE__VALUE, pString);
		}
		CRX_PUBLIC ::std::string Security::processCageCrxCssAtRuleValue(::std::string const & pString)
		{
			return this->processCageCrxCssRuleOrValue(
					Security::PROCESS_CAGE_CRX_CSS_RULE_OR_VALUE__TYPE__AT_RULE_VALUE, pString);
		}
		CRX_PRIVATE ::std::string Security::processCageCrxCssRuleOrValue(
				Security::ProcessCageCrxCssRuleOrValue_Type pType, ::std::string const & pString)
		{
			bool vIsInsideString = false;
			unsigned char vStringCharacterCode = 0;
			unsigned char vCurrentCharacterCode = 0;
			unsigned char vPreviousCharacterCode = 0;
			bool vIsEscaping = false;
			::std::string vReturn /*= ""*/;
			size_t tI = 0;
			
			while(tI < pString.size())
			{
				vPreviousCharacterCode = vCurrentCharacterCode;
				vCurrentCharacterCode = static_cast<unsigned char>(pString[tI]);

				if(vIsEscaping)
				{
					vReturn.push_back('\\');
					vReturn.push_back(pString[tI]);
					vIsEscaping = false;
				}
				else if(vCurrentCharacterCode == 0x005C /*\*/)
					{vIsEscaping = true;}
				else if(vCurrentCharacterCode == 0x0000) 
					{vReturn.append("\\00FFFD");}
				else if(((vCurrentCharacterCode >= 0x0001) && (vCurrentCharacterCode <= 0x001F) &&
						(vCurrentCharacterCode != 0x0009 /*TAB*/) && 
						(vCurrentCharacterCode != 0x000A /*LINE FEED*/) && 
						(vCurrentCharacterCode != 0x000D /*CARRIAGE RETURN*/)) ||
						(vCurrentCharacterCode == 0x007F /*[:CNTRL]*/))
				{
					vReturn.push_back('\\');
					this->cpp_appendUnsignedCharAsHexDigitsTo(&vReturn, vCurrentCharacterCode);
					vReturn.push_back(' ');
				}
				else
				{
					if(vIsInsideString)
					{
						if(vCurrentCharacterCode == vStringCharacterCode)
						{
							vReturn.push_back(pString[tI]);
							vIsInsideString = false;
							vStringCharacterCode = 0;
						}
						else
							{vReturn.push_back(pString[tI]);}
					}
					else
					{
						if((vCurrentCharacterCode == 0x0022 /*"*/) || (vCurrentCharacterCode == 0x0060 /*'*/))
						{
							vReturn.push_back(pString[tI]);
							vStringCharacterCode = vCurrentCharacterCode;
							vIsInsideString = true;
						}
						else if(((pType == Security::PROCESS_CAGE_CRX_CSS_RULE_OR_VALUE__TYPE__VALUE) && 
										(vCurrentCharacterCode == 0x003A /*:*/)) || 
								((pType == Security::PROCESS_CAGE_CRX_CSS_RULE_OR_VALUE__TYPE__REFERENCE) && 
										(vCurrentCharacterCode == 0x002C /*,*/)) ||
								(vCurrentCharacterCode == 0x003B /*;*/) ||
								(vCurrentCharacterCode == 0x007B /*{*/) || (vCurrentCharacterCode == 0x007D /*}*/))
						{
							vReturn.push_back('\\');
							vReturn.push_back(pString[tI]);
						}
						else if((vCurrentCharacterCode == 0x002F /*/*/) &&
								(tI != pString.size() - 1) && (static_cast<unsigned char>(pString[tI + 1]) == 0x002A /***/))
						{
							vReturn.append("/*");

							tI = tI + 2;

							while(tI < pString.size())
							{
								if(static_cast<unsigned char>(pString[tI]) == 0x002A /***/)
								{
									tI = tI + 1;

									if((tI == pString.size()) || (static_cast<unsigned char>(pString[tI]) == 0x002F /*/*/))
										{break;}
									else
									{
										vReturn.push_back('*');
										vReturn.push_back(pString[tI]);
									}
								}
								else
									{vReturn.push_back(pString[tI]);}

								tI = tI + 1;
							}

							vReturn.append("*/ ");
						}
						else
							{vReturn.push_back(pString[tI]);}
					}
				}

				tI = tI + 1;
			}

			if(vIsInsideString)
				{vReturn.push_back(static_cast<char>(vStringCharacterCode));}
		
			return vReturn;
		}

		CRX_PUBLIC ::std::string Security::procesCageCssValue(::std::string const & pCssValue)
		{
			//THE FOLLWING (COMMENTED OUT CODE) CAGES CSS VALUES, BUT IT WILL DAMAGE URLS
			/*static char const * vSEARCHES[] = {";", ":", "}", "{", ""};

			return this->cpp_removeSubstringsIgnoringCaseFrom(pCssValue, vSEARCHES);*/

			return this->processCageCrxCssValue(pCssValue);
		}
		CRX_PUBLIC ::std::string Security::processCageCssSelector(::std::string const & pCssSelector)
		{
			/*static char const * vSEARCHES[] = {";", "}", "{", ""};

			return this->cpp_removeSubstringsIgnoringCaseFrom(pCssSelector, vSEARCHES);*/

			return this->processCageCrxCssReference(pCssSelector);
		}

		CRX_PUBLIC Security::~Security()
		{
			delete this->gNonJavaScriptUrlProtocolsRegexParts;
			this->gNonJavaScriptUrlProtocolsRegexParts = NULL;
		}
	#pragma endregion CLASS Security //}
}}

