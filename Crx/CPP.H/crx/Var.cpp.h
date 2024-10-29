//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .cpp FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".cpp.h" NOR ".c.h", OF C++, AND C, CRXed CODE.
#include "Crx/H/crx/Var.h"

//#include <boost/cstdint.hpp>
#include <doubleConversion/double-conversion.h>
#include <deque>
//#include <boost/algorithm/searching/boyer_moore.hpp>
#if(defined(BOOST_VERSION) && (BOOST_VERSION >= 105500))
	#include <boost/core/explicit_operator_bool.hpp>
#endif
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/predef.h>
#include <boost/type_traits/remove_cv.hpp>
#include <algorithm>
#include <cctype>
#include <klib/khash.h>
#include <string.h>
#include <stdarg.h>
#include "Crx/H/crx/nonCrxed/standard/math.h"
#include "Crx/H/crx/nonCrxed/standard/stdint.h"
#include "Crx/H/crx/ClassUnorderedMap.h"
#include "Crx/H/crx/c/Ring.h"
#include "Crx/H/crx/c/char.h"
//<<END>>

#if !CRX__ARE_ONLY_POINTERS_TO_SAME_OBJECT_EQUAL_AND_ALWAYS
typedef char CRX__VAR__ERROR__SAME_OBJECT_MEMORY_TESTS_ARE_NOT_RELIABLE[-1];
#endif

#if(defined(_MSC_VER) && (_MSC_VER <= 1600))
	#define CRX__VAR__PRIVATE__POD_ZERO
	#define CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(pPOD_STRUCTURE_TYPE, pVARIABLE) \
			CRX__SET_TO_ZERO(pPOD_STRUCTURE_TYPE, pVARIABLE);
#else
	#define CRX__VAR__PRIVATE__POD_ZERO CRX__INITIALIZATION_POD_ZERO
	#define CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(pPOD_STRUCTURE_TYPE, pVARIABLE)
#endif

namespace crx
{
	#pragma region CLASS Var //{
#if(CRX__LIB__IS_TO_DEFINE_STATIC_VARS_IN_CPPH())
		CRX_PUBLIC_STATIC Var const Var::StaticPublicVars::gVAR_NULL = Var(Var::Nil(), true);
		CRX_PRIVATE_STATIC char const Var::StaticPrivateVars::gINFINITY_SYMBOL[4] = "INF";
		CRX_PRIVATE_STATIC char const Var::StaticPrivateVars::gNAN_SYMBOL[4] = "NAN";
		CRX_PRIVATE_STATIC ::double_conversion::DoubleToStringConverter * 
				Var::StaticPrivateVars::gDoubleToStringConverter =
				new ::double_conversion::DoubleToStringConverter(
				::double_conversion::DoubleToStringConverter::Flags::EMIT_TRAILING_DECIMAL_POINT |
				::double_conversion::DoubleToStringConverter::Flags::EMIT_TRAILING_ZERO_AFTER_POINT |
				::double_conversion::DoubleToStringConverter::Flags::UNIQUE_ZERO,
				Var::StaticPrivateVars::gINFINITY_SYMBOL,
				Var::StaticPrivateVars::gNAN_SYMBOL, 'E', 0, 0, 1, 0);
		CRX_PRIVATE_STATIC ::double_conversion::StringToDoubleConverter * 
				Var::StaticPrivateVars::gStringToDoubleConverter = 
				new ::double_conversion::StringToDoubleConverter(
				::double_conversion::StringToDoubleConverter::Flags::NO_FLAGS,
				CRX__VAR__DOUBLE__ERROR, 
				CRX__VAR__DOUBLE__ERROR, 
				Var::StaticPrivateVars::gINFINITY_SYMBOL,
				Var::StaticPrivateVars::gNAN_SYMBOL);
		CRX_PRIVATE_STATIC ::double_conversion::StringToDoubleConverter * 
				Var::StaticPrivateVars::gStringToDoubleConverter__loose = 
				new ::double_conversion::StringToDoubleConverter(
				::double_conversion::StringToDoubleConverter::Flags::ALLOW_LEADING_SPACES |
				::double_conversion::StringToDoubleConverter::Flags::ALLOW_TRAILING_SPACES |
				::double_conversion::StringToDoubleConverter::Flags::ALLOW_CASE_INSENSIBILITY |
				::double_conversion::StringToDoubleConverter::Flags::ALLOW_TRAILING_JUNK,
				CRX__VAR__DOUBLE__ERROR, 
				CRX__VAR__DOUBLE__ERROR, 
				Var::StaticPrivateVars::gINFINITY_SYMBOL,
				Var::StaticPrivateVars::gNAN_SYMBOL);
		CRX_PRIVATE_STATIC int Var::StaticPrivateVars::gHexCharacterToValueArray[256] = 
		{ 
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,-1,-1,-1,-1,-1,-1,-1,10,11,12,13,
			14,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,10,11,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1
		};
		
		/*
			0-9, a-f, A-F : Hex values
			{: 17
			[: 18
			", ', `: 19 
			\t, \n, , \r: 20
			/: 21
			f, F, i, I, n, N, t, T: 15, 16
			
			88,88,88,88,88,88,88,88,88,20,20,88,88,88,88,20,88,88,88,88,88,88,88,
			88,88,88,88,88,88,88,88,88,20,88,19,88,88,88,88,19,88,88,88,88,88,88,
			88,21, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,88,88,88,88,88,88,88,10,11,12,13,
			14,15,88,88,16,88,88,88,88,16,88,88,88,88,88,16,88,88,88,88,88,88,18,
			88,88,88,88,19,10,11,12,13,14,15,88,88,16,88,88,88,88,16,88,88,88,88,
			88,16,88,88,88,88,88,88,17,88,88,88,88,88,88,88,88,88,88,88,88,88,88,
			88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,
			88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,
			88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,
			88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,
			88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,
			88,88,88
		*/
	#ifdef CRX__BOOST_NO_INT64_T
		/*CRX_PRIVATE_STATIC Var::StaticPrivateVars::gERROR_VALUE_FOR_DOUBLE = var_getBitsOfDouble(
				CRX__VAR__DOUBLE__ERROR_HIGH_BITS_IN_INT32, CRX__VAR__DOUBLE__ERROR_LOW_BITS_IN_INT32);*/
	#endif
#endif
		#pragma region STATIC FUNCTIONS //{
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() bool Var::isNumberStringAnIntegerIfValid(char const * pChars, 
				size_t pLength)
		{
			char const * vCurrentChar = pChars;
			size_t vRemainingCharacters = pLength;

			while((vRemainingCharacters--) && (*vCurrentChar == 127 || 
					((*vCurrentChar >= 0) && (*vCurrentChar <= 32))) ||
					((*vCurrentChar >= '0') && (*vCurrentChar <= '9')) ||
					(*vCurrentChar == '+') || (*vCurrentChar == '-'))
				{vCurrentChar++;}

			if(vRemainingCharacters > 0)
			{
				if(*vCurrentChar == '.')
				{
					vRemainingCharacters--;
					vCurrentChar++;
					
					if((vRemainingCharacters > 0) && (*vCurrentChar >= '0') && (*vCurrentChar <= '9'))
						{return false;}
					else
						{return true;}
				}
				else
					{return true;}
			}
			else
				{return true;}
			

			/* THE FOLLOWING WAS WHEN TRAILING NON WHITE SPACE CHARACTERS WERE NOT ALLOWED
					UNDER LOOSE MORPH.
			while((vRemainingCharacters--) && (*vCurrentChar != '.') &&
					(*vCurrentChar != 'e') && (*vCurrentChar != 'E'))
				{vCurrentChar++;}

			return (vRemainingCharacters == 0);*/
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() int32_t Var::convertToSignedInt32(char const * pString, 
				bool * pIsError)
		{
			bool vIsNegative = false;
			unsigned int vCount = 0;
			int32_t vReturn = 0;

			if(*pString)
			{
				if(*pString == '-')
				{
					vIsNegative = true;
					pString++;
				}
				else if(*pString == '+')
					{pString++;}
			}

			while(*pString)
			{
				if((*pString > '9') || (*pString < '0'))
					{break;}

				vCount++;

				if((vCount == 10) && ((vReturn >= 214748364) || 
						((*(pString) - '0') > (7 + (vIsNegative ? 1 : 0)))))
					{break;}

				vReturn = (vReturn * 10) + (*(pString++) - '0');
			}

			if(pIsError != NULL)
				{*pIsError = !(*pString == '\0');}

			return (vIsNegative ? (vReturn * -1) : vReturn);
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() int32_t Var::convertToSignedInt32(char const * pChars, 
				size_t pLength, bool * pIsError)
		{
			size_t vLength = pLength;
			bool vIsNegative = false;
			unsigned int vCount = 0;
			int32_t vReturn = 0;

			if(vLength > 0)
			{
				if(*pChars == '-')
				{
					vIsNegative = true;
					pChars++;
					vLength--;
				}
				else if(*pChars == '+')
				{
					pChars++;
					vLength--;
				}
			}

			while(vLength > 0)
			{
				if((*pChars > '9') || (*pChars < '0'))
					{break;}

				vCount++;

				if((vCount == 10) && ((vReturn >= 214748364) || 
						((*(pChars) - '0') > (7 + (vIsNegative ? 1 : 0)))))
					{break;}

				vReturn = (vReturn * 10) + (*(pChars++) - '0');
				vLength--;
			}

			if(pIsError != NULL)
				{*pIsError = !!vLength;}

			return (vIsNegative ? (vReturn * -1) : vReturn);
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() int32_t Var::looseConvertToSignedInt32(char const * pString, 
				bool * pIsError)
		{
			bool vIsNegative = false;
			bool vIsError = false;
			unsigned int vCount = 0;
			int32_t vReturn = 0;

			while(*pString && (*pString == 127 || ((*pString >= 0) && (*pString <= 32))))
				{pString++;}

			if(*pString)
			{
				if(*pString == '-')
				{
					vIsNegative = true;
					pString++;
				}
				else if(*pString == '+')
					{pString++;}
			}

			while(*pString)
			{
				if((*pString > '9') || (*pString < '0'))
					{break;}

				vCount++;

				if((vCount == 10) && ((vReturn >= 214748364) || 
						((*(pString) - '0') > (7 + (vIsNegative ? 1 : 0)))))
				{
					vIsError = true;
					break;
				}

				vReturn = (vReturn * 10) + (*(pString++) - '0');
			}

			if(pIsError != NULL)
				{*pIsError = vIsError;}

			return (vIsNegative ? (vReturn * -1) : vReturn);
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() int32_t Var::looseConvertToSignedInt32(char const * pChars, 
				size_t pLength, bool * pIsError)
		{
			size_t vLength = pLength;
			bool vIsNegative = false;
			bool vIsError = false;
			unsigned int vCount = 0;
			int32_t vReturn = 0;

			while(vLength && (*pChars == 127 || ((*pChars >= 0) && (*pChars <= 32))))
			{
				pChars++;
				vLength--;
			}

			if(vLength > 0)
			{
				if(*pChars == '-')
				{
					vIsNegative = true;
					pChars++;
					vLength--;
				}
				else if(*pChars == '+')
				{
					pChars++;
					vLength--;
				}
			}

			while(vLength > 0)
			{
				if((*pChars > '9') || (*pChars < '0'))
					{break;}

				vCount++;

				if((vCount == 10) && ((vReturn >= 214748364) || 
						((*(pChars) - '0') > (7 + (vIsNegative ? 1 : 0)))))
				{
					vIsError = true;
					break;
				}

				vReturn = (vReturn * 10) + (*(pChars++) - '0');
				vLength--;
			}

			if(pIsError != NULL)
				{*pIsError = vIsError;}

			return (vIsNegative ? (vReturn * -1) : vReturn);
		}
#ifndef CRX__BOOST_NO_INT64_T		
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() int64_t Var::convertToSignedInt64(char const * pString, 
				bool * pIsError)
		{
			int64_t vReturn = 0;
			bool vIsNegative = false;
			unsigned int vCount = 0;

			if(*pString)
			{
				if(*pString == '-')
				{
					vIsNegative = true;
					pString++;
				}
				else if(*pString == '+')
					{pString++;}
			}

			while(*pString)
			{
				if((*pString > '9') || (*pString < '0'))
					{break;}

				vCount++;

				if((vCount == 19) && ((vReturn >= 922337203685477580) || 
						((*(pString) - '0') > (7 + (vIsNegative ? 1 : 0)))))
					{break;}

				vReturn = (vReturn * 10) + (*(pString++) - '0');
			}

			if(pIsError != NULL)
				{*pIsError = !(*pString == '\0');}

			return (vIsNegative ? (vReturn * -1) : vReturn);
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() int64_t Var::convertToSignedInt64(char const * pChars,
				size_t pLength, bool * pIsError)
		{
			size_t vLength = pLength;
			bool vIsNegative = false;
			unsigned int vCount = 0;
			int64_t vReturn = 0;
			
			if(vLength > 0)
			{
				if(*pChars == '-')
				{
					vIsNegative = true;
					pChars++;
					vLength--;
				}
				else if(*pChars == '+')
				{
					pChars++;
					vLength--;
				}
			}

			while(vLength > 0)
			{
				if((*pChars > '9') || (*pChars < '0'))
					{break;}

				vCount++;

				if((vCount == 19) && ((vReturn >= 922337203685477580) || 
						((*(pChars) - '0') > (7 + (vIsNegative ? 1 : 0)))))
					{break;}

				vReturn = (vReturn * 10) + (*(pChars++) - '0');
				vLength--;
			}

			if(pIsError != NULL)
				{*pIsError = !!vLength;}

			return (vIsNegative ? (vReturn * -1) : vReturn);
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() int64_t Var::looseConvertToSignedInt64(char const * pString, 
				bool * pIsError)
		{
			bool vIsNegative = false;
			bool vIsError = false;
			unsigned int vCount = 0;
			int64_t vReturn = 0;

			while(*pString && (*pString == 127 || ((*pString >= 0) && (*pString <= 32))))
				{pString++;}

			if(*pString)
			{
				if(*pString == '-')
				{
					vIsNegative = true;
					pString++;
				}
				else if(*pString == '+')
					{pString++;}
			}

			while(*pString)
			{
				if((*pString > '9') || (*pString < '0'))
					{break;}

				vCount++;

				if((vCount == 19) && ((vReturn >= 922337203685477580) || 
						((*(pString) - '0') > (7 + (vIsNegative ? 1 : 0)))))
				{
					vIsError = true;
					break;
				}

				vReturn = (vReturn * 10) + (*(pString++) - '0');
			}

			if(pIsError != NULL)
				{*pIsError = vIsError;}

			return (vIsNegative ? (vReturn * -1) : vReturn);
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() int64_t Var::looseConvertToSignedInt64(char const * pChars,
				size_t pLength, bool * pIsError)
		{
			size_t vLength = pLength;
			bool vIsNegative = false;
			bool vIsError = false;
			unsigned int vCount = 0;
			int64_t vReturn = 0;

			while(vLength && (*pChars == 127 || ((*pChars >= 0) && (*pChars <= 32))))
			{
				pChars++;
				vLength--;
			}

			if(vLength > 0)
			{
				if(*pChars == '-')
				{
					vIsNegative = true;
					pChars++;
					vLength--;
				}
				else if(*pChars == '+')
				{
					pChars++;
					vLength--;
				}
			}

			while(vLength > 0)
			{
				if((*pChars > '9') || (*pChars < '0'))
					{break;}

				vCount++;

				if((vCount == 19) && ((vReturn >= 922337203685477580) || 
						((*(pChars) - '0') > (7 + (vIsNegative ? 1 : 0)))))
				{
					vIsError = true;
					break;
				}

				vReturn = (vReturn * 10) + (*(pChars++) - '0');
				vLength--;
			}

			if(pIsError != NULL)
				{*pIsError = vIsError;}

			return (vIsNegative ? (vReturn * -1) : vReturn);
		}
#endif
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() bool Var::stringifyInt32(int32_t pInt32, char * pChars, size_t pAvailableLength)
		{
			if(pInt32 == 0)
			{
				if(pAvailableLength > 1)
				{
					*pChars = '0';
					*(pChars + 1) = '\0';

					return true;
				}
				else
					{return false;}
			}
			else
			{
				int32_t tSignValue = -(pInt32 < 0);
				uint32_t tAbsoluteValue = (pInt32 ^ tSignValue) - tSignValue;
				uint32_t tRequiredNumberOfCharacters = 0;

				if(tAbsoluteValue >= 10000)//5
				{
					if(tAbsoluteValue >= 1000000)//8
					{
						if(tAbsoluteValue >= 1000000000)
							{tRequiredNumberOfCharacters = 10;}
						else if(tAbsoluteValue >= 100000000)
							{tRequiredNumberOfCharacters = 9;}
						else
							{tRequiredNumberOfCharacters = 8;}
					}
					else
					{
						if(tAbsoluteValue >= 1000000)
							{tRequiredNumberOfCharacters = 7;}
						else if(tAbsoluteValue >= 100000)
							{tRequiredNumberOfCharacters = 6;}
						else
							{tRequiredNumberOfCharacters = 5;}
					}
				}
				else
				{
					if(tAbsoluteValue >= 1000)//4
					{
						if(tAbsoluteValue >= 10000)
							{tRequiredNumberOfCharacters = 5;}
						else
							{tRequiredNumberOfCharacters = 4;}
					}
					else
					{
						if(tAbsoluteValue >= 100)
							{tRequiredNumberOfCharacters = 3;}
						else if(tAbsoluteValue >= 10)
							{tRequiredNumberOfCharacters = 2;}
						else
							{tRequiredNumberOfCharacters = 1;}
					}
				}

				if(tSignValue)
					{tRequiredNumberOfCharacters++;}

				if(tRequiredNumberOfCharacters < (pAvailableLength - 1))
				{
					char * tChar = pChars + tRequiredNumberOfCharacters - 1;

					if(tSignValue)
						{*pChars = '-';}

					while(tAbsoluteValue > 0)
					{
						*tChar-- = '0' + (tAbsoluteValue % 10);
						tAbsoluteValue /= 10;
					}

					*(pChars + tRequiredNumberOfCharacters) = '\0';

					return true;
				}
				else
					{return false;}
			}
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() size_t Var::stringifyInt32AndGetSize(int32_t pInt32, char * pChars, size_t pAvailableLength)
		{
			CRX__BOOST_ASSERT(pAvailableLength > 11);

			if(pInt32 == 0)
			{
				*pChars = '0';
				*(pChars + 1) = '\0';
				
				return 1;
			}
			else
			{
				int32_t tSignValue = -(pInt32 < 0);
				uint32_t tAbsoluteValue = (pInt32 ^ tSignValue) - tSignValue;
				int tRequiredNumberOfCharacters = 0;
				char * tChar = NULL;

				if(tAbsoluteValue >= 10000)//5
				{
					if(tAbsoluteValue >= 1000000)//8
					{
						if(tAbsoluteValue >= 1000000000)
							{tRequiredNumberOfCharacters = 10;}
						else if(tAbsoluteValue >= 100000000)
							{tRequiredNumberOfCharacters = 9;}
						else
							{tRequiredNumberOfCharacters = 8;}
					}
					else
					{
						if(tAbsoluteValue >= 1000000)
							{tRequiredNumberOfCharacters = 7;}
						else if(tAbsoluteValue >= 100000)
							{tRequiredNumberOfCharacters = 6;}
						else
							{tRequiredNumberOfCharacters = 5;}
					}
				}
				else
				{
					if(tAbsoluteValue >= 1000)//4
					{
						if(tAbsoluteValue >= 10000)
							{tRequiredNumberOfCharacters = 5;}
						else
							{tRequiredNumberOfCharacters = 4;}
					}
					else
					{
						if(tAbsoluteValue >= 100)
							{tRequiredNumberOfCharacters = 3;}
						else if(tAbsoluteValue >= 10)
							{tRequiredNumberOfCharacters = 2;}
						else
							{tRequiredNumberOfCharacters = 1;}
					}
				}

				if(tSignValue)
				{
					tRequiredNumberOfCharacters++;
					*pChars = '-';
				}

				tChar = pChars + tRequiredNumberOfCharacters - 1;

				while(tAbsoluteValue > 0)
				{
					*tChar-- = '0' + (tAbsoluteValue % 10);
					tAbsoluteValue /= 10;
				}

				*(pChars + tRequiredNumberOfCharacters) = '\0';

				return tRequiredNumberOfCharacters;
			}
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() bool Var::stringifyUnsignedInt32(uint32_t pUnsignedInt32, char * pChars, size_t pAvailableLength)
		{
			if(pUnsignedInt32 == 0)
			{
				if(pAvailableLength > 1)
				{
					*pChars = '0';
					*(pChars + 1) = '\0';

					return true;
				}
				else
					{return false;}
			}
			else
			{
				uint32_t tRequiredNumberOfCharacters = 0;

				if(pUnsignedInt32 >= 10000)//5
				{
					if(pUnsignedInt32 >= 1000000)//8
					{
						if(pUnsignedInt32 >= 1000000000)
							{tRequiredNumberOfCharacters = 10;}
						else if(pUnsignedInt32 >= 100000000)
							{tRequiredNumberOfCharacters = 9;}
						else
							{tRequiredNumberOfCharacters = 8;}
					}
					else
					{
						if(pUnsignedInt32 >= 1000000)
							{tRequiredNumberOfCharacters = 7;}
						else if(pUnsignedInt32 >= 100000)
							{tRequiredNumberOfCharacters = 6;}
						else
							{tRequiredNumberOfCharacters = 5;}
					}
				}
				else
				{
					if(pUnsignedInt32 >= 1000)//4
					{
						if(pUnsignedInt32 >= 10000)
							{tRequiredNumberOfCharacters = 5;}
						else
							{tRequiredNumberOfCharacters = 4;}
					}
					else
					{
						if(pUnsignedInt32 >= 100)
							{tRequiredNumberOfCharacters = 3;}
						else if(pUnsignedInt32 >= 10)
							{tRequiredNumberOfCharacters = 2;}
						else
							{tRequiredNumberOfCharacters = 1;}
					}
				}

				if(tRequiredNumberOfCharacters < (pAvailableLength - 1))
				{
					uint32_t tUnsignedInt32 = pUnsignedInt32;
					char * tChar = pChars + tRequiredNumberOfCharacters - 1;

					while(tUnsignedInt32 > 0)
					{
						*tChar-- = '0' + (tUnsignedInt32 % 10);
						tUnsignedInt32 /= 10;
					}

					*(pChars + tRequiredNumberOfCharacters) = '\0';

					return true;
				}
				else
					{return false;}
			}
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() size_t Var::stringifyUnsignedInt32AndGetSize(uint32_t pUnsignedInt32, char * pChars, 
				size_t pAvailableLength)
		{
			CRX__BOOST_ASSERT(pAvailableLength > 10);

			if(pUnsignedInt32 == 0)
			{
				*pChars = '0';
				*(pChars + 1) = '\0';

				return 1;
			}
			else
			{
				int tRequiredNumberOfCharacters = 0;
				uint32_t tUnsignedInt32 = pUnsignedInt32;
				char * d = 0;

				if(pUnsignedInt32 >= 10000)//5
				{
					if(pUnsignedInt32 >= 1000000)//8
					{
						if(pUnsignedInt32 >= 1000000000)
							{tRequiredNumberOfCharacters = 10;}
						else if(pUnsignedInt32 >= 100000000)
							{tRequiredNumberOfCharacters = 9;}
						else
							{tRequiredNumberOfCharacters = 8;}
					}
					else
					{
						if(pUnsignedInt32 >= 1000000)
							{tRequiredNumberOfCharacters = 7;}
						else if(pUnsignedInt32 >= 100000)
							{tRequiredNumberOfCharacters = 6;}
						else
							{tRequiredNumberOfCharacters = 5;}
					}
				}
				else
				{
					if(pUnsignedInt32 >= 1000)//4
					{
						if(pUnsignedInt32 >= 10000)
							{tRequiredNumberOfCharacters = 5;}
						else
							{tRequiredNumberOfCharacters = 4;}
					}
					else
					{
						if(pUnsignedInt32 >= 100)
							{tRequiredNumberOfCharacters = 3;}
						else if(pUnsignedInt32 >= 10)
							{tRequiredNumberOfCharacters = 2;}
						else
							{tRequiredNumberOfCharacters = 1;}
					}
				}

				d = pChars + tRequiredNumberOfCharacters - 1;

				while(tUnsignedInt32 > 0)
				{
					*d-- = '0' + (tUnsignedInt32 % 10);
					tUnsignedInt32 /= 10;
				}

				*(pChars + tRequiredNumberOfCharacters) = '\0';

				return tRequiredNumberOfCharacters;
			}
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() bool Var::stringifyEmulatedInt(double pDouble, char * pChars, size_t pAvailableLength)
		{
			if(pDouble == 0)
			{
				if(pAvailableLength > 1)
				{
					*pChars = '0';
					*(pChars + 1) = '\0';

					return true;
				}
				else
					{return false;}
			}
			else
			{
				bool tIsNegative = (pDouble < 0.0);
				double tDouble = (tIsNegative ? (pDouble * -1) : pDouble);
				uint32_t tRequiredNumberOfCharacters = 0;

				if(tDouble >= 100000000.0)//9
				{
					if(tDouble >= 100000000000.0)//13
					{
						if(tDouble >= 10000000000000.0)//15
						{
							if(tDouble >= 100000000000000.0)
								{tRequiredNumberOfCharacters = 16;}
							else
								{tRequiredNumberOfCharacters = 15;}
						}
						else
						{
							if(tDouble >= 10000000000000.0)
								{tRequiredNumberOfCharacters = 14;}
							else
								{tRequiredNumberOfCharacters = 13;}
						}
					}
					else
					{
						if(tDouble >= 10000000000.0)//11
						{
							if(tDouble >= 100000000000.0)
								{tRequiredNumberOfCharacters = 12;}
							else
								{tRequiredNumberOfCharacters = 11;}
						}
						else
						{
							if(tDouble >= 1000000000.0)
								{tRequiredNumberOfCharacters = 10;}
							else
								{tRequiredNumberOfCharacters = 9;}
						}
					}
				}
				else
				{
					if(tDouble >= 10000.0)//5
					{
						if(tDouble >= 1000000.0)//7
						{
							if(tDouble >= 10000000.0)
								{tRequiredNumberOfCharacters = 8;}
							else
								{tRequiredNumberOfCharacters = 7;}
						}
						else
						{
							if(tDouble >= 100000.0)
								{tRequiredNumberOfCharacters = 6;}
							else
								{tRequiredNumberOfCharacters = 5;}
						}
					}
					else
					{
						if(tDouble >= 100.0)//3
						{
							if(tDouble >= 1000.0)
								{tRequiredNumberOfCharacters = 4;}
							else
								{tRequiredNumberOfCharacters = 3;}
						}
						else
						{
							if(tDouble >= 10.0)
								{tRequiredNumberOfCharacters = 2;}
							else
								{tRequiredNumberOfCharacters = 1;}
						}
					}
				}

				if(tIsNegative)
					{tRequiredNumberOfCharacters++;}

				if(tRequiredNumberOfCharacters < (pAvailableLength - 1))
				{
					char * tChar = pChars + tRequiredNumberOfCharacters - 1;

					if(tIsNegative)
						{*pChars = '-';}

					while(tDouble > 0.95)
					{
						*tChar-- = '0' + ((int)::fmod(tDouble, 10.0));
						tDouble /= 10.0;
					}

					*(pChars + tRequiredNumberOfCharacters) = '\0';

					return true;
				}
				else
					{return false;}
			}
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() size_t Var::stringifyEmulatedIntAndGetSize(double pDouble, char * pChars, size_t pAvailableLength)
		{
			CRX__BOOST_ASSERT(pAvailableLength > 17);

			if(pDouble == 0)
			{
				*pChars = '0';
				*(pChars + 1) = '\0';

				return 1;
			}
			else
			{
				bool tIsNegative = (pDouble < 0.0);
				double tDouble = (tIsNegative ? (pDouble * -1) : pDouble);
				int tRequiredNumberOfCharacters = 0;
				char * tChar = NULL;

				if(pDouble >= 100000000.0)//9
				{
					if(pDouble >= 100000000000.0)//13
					{
						if(pDouble >= 10000000000000.0)//15
						{
							if(pDouble >= 100000000000000.0)
								{tRequiredNumberOfCharacters = 16;}
							else
								{tRequiredNumberOfCharacters = 15;}
						}
						else
						{
							if(pDouble >= 10000000000000.0)
								{tRequiredNumberOfCharacters = 14;}
							else
								{tRequiredNumberOfCharacters = 13;}
						}
					}
					else
					{
						if(pDouble >= 10000000000.0)//11
						{
							if(pDouble >= 100000000000.0)
								{tRequiredNumberOfCharacters = 12;}
							else
								{tRequiredNumberOfCharacters = 11;}
						}
						else
						{
							if(pDouble >= 1000000000.0)
								{tRequiredNumberOfCharacters = 10;}
							else
								{tRequiredNumberOfCharacters = 9;}
						}
					}
				}
				else
				{
					if(pDouble >= 10000.0)//5
					{
						if(pDouble >= 1000000.0)//7
						{
							if(pDouble >= 10000000.0)
								{tRequiredNumberOfCharacters = 8;}
							else
								{tRequiredNumberOfCharacters = 7;}
						}
						else
						{
							if(pDouble >= 100000.0)
								{tRequiredNumberOfCharacters = 6;}
							else
								{tRequiredNumberOfCharacters = 5;}
						}
					}
					else
					{
						if(pDouble >= 100.0)//3
						{
							if(pDouble >= 1000.0)
								{tRequiredNumberOfCharacters = 4;}
							else
								{tRequiredNumberOfCharacters = 3;}
						}
						else
						{
							if(pDouble >= 10.0)
								{tRequiredNumberOfCharacters = 2;}
							else
								{tRequiredNumberOfCharacters = 1;}
						}
					}
				}

				if(tIsNegative)
				{
					tRequiredNumberOfCharacters++;
					*(pChars) = '-';
				}

				tChar = pChars + tRequiredNumberOfCharacters - 1;

				while(tDouble > 0.95)
				{
					*tChar-- = '0' + ((int)::fmod(tDouble, 10.0));
					tDouble /= 10.0;
				}

				*(pChars + tRequiredNumberOfCharacters) = '\0';
				
				return tRequiredNumberOfCharacters;
			}
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() bool Var::stringifyInt64(int64_t pInt64, char * pChars, size_t pAvailableLength)
		{
			if(pInt64 == 0)
			{
				if(pAvailableLength > 1)
				{
					*pChars = '0';
					*(pChars + 1) = '\0';

					return true;
				}
				else
					{return false;}
			}
			else
			{
				int64_t tSignValue = -(pInt64 < 0);
				uint64_t val = (pInt64 ^ tSignValue) - tSignValue;
				uint32_t tRequiredNumberOfCharacters = 0;

				if(val >= 0x3B9ACA00/*VC6 1000000000ll*/)//10
				{
					if(val >= 0x5AF3107A4000/*VC6 100000000000000ll*/)//15
					{
						if(val >= 0x16345785D8A0000/*VC6 100000000000000000ll*/)//18
						{
							if(val >= 0x8AC7230489E80000/*VC6 10000000000000000000ll*/)
								{tRequiredNumberOfCharacters = 20;}
							else if(val >= 0xDE0B6B3A7640000/*VC6 1000000000000000000ll*/)
								{tRequiredNumberOfCharacters = 19;}
							else
								{tRequiredNumberOfCharacters = 18;}
						}
						else
						{
							if(val >= 0x2386F26FC10000/*VC6 10000000000000000ll*/)
								{tRequiredNumberOfCharacters = 17;}
							else if(val >= 0x38D7EA4C68000/*VC6 1000000000000000ll*/)
								{tRequiredNumberOfCharacters = 16;}
							else
								{tRequiredNumberOfCharacters = 15;}
						}
					}
					else
					{
						if(val >= 0xE8D4A51000/*VC6 1000000000000ll*/)//13
						{
							if(val >= 0x9184E72A000/*VC6 10000000000000ll*/)
								{tRequiredNumberOfCharacters = 14;}
							else
								{tRequiredNumberOfCharacters = 13;}
						}
						else
						{
							if(val >= 0x174876E800/*VC6 100000000000ll*/)
								{tRequiredNumberOfCharacters = 12;}
							else if (val >= 0x2540BE400/*VC6 10000000000ll*/)
								{tRequiredNumberOfCharacters = 11;}
							else
								{tRequiredNumberOfCharacters = 10;}
						}
					}
				}
				else
				{
					if(val >= 0x2710/*VC6 10000ll*/)//5
					{
						if(val >= 0x989680/*VC6 10000000ll*/)
						{
							if(val >= 0x5F5E100/*VC6 100000000ll*/)
								{tRequiredNumberOfCharacters = 9;}
							else
								{tRequiredNumberOfCharacters = 8;}
						}
						else
						{
							if(val >= 0xF4240/*VC6 1000000ll*/)
								{tRequiredNumberOfCharacters = 7;}
							else if(val >= 0x186A0/*VC6 100000ll*/)
								{tRequiredNumberOfCharacters = 6;}
							else
								{tRequiredNumberOfCharacters = 5;}
						}
					}
					else
					{
						if(val >= 0x64/*VC6 100ll*/)
						{
							if(val >= 0x3E8/*VC6 1000ll*/)
								{tRequiredNumberOfCharacters = 4;}
							else
								{tRequiredNumberOfCharacters = 3;}
						}
						else
						{
							if(val >= 0xA/*VC6 10ll*/)
								{tRequiredNumberOfCharacters = 2;}
							else
								{tRequiredNumberOfCharacters = 1;}
						}
					}
				}

				if(tSignValue)
					{tRequiredNumberOfCharacters++;}

				if(tRequiredNumberOfCharacters < (pAvailableLength - 1))
				{
					char * d = pChars + tRequiredNumberOfCharacters - 1;

					if(tSignValue)
						{*pChars = '-';}

					while(val > 0)
					{
						*d-- = '0' + static_cast<char>(val % 10);
						val /= 10;
					}

					*(pChars + tRequiredNumberOfCharacters) = '\0';

					return true;
				}
				else
					{return false;}
			}
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() size_t Var::stringifyInt64AndGetSize(int64_t pInt64, char * pChars, size_t pAvailableLength)
		{
			CRX__BOOST_ASSERT(pAvailableLength > 22);

			if(pInt64 == 0)
			{
				*pChars = '0';
				*(pChars + 1) = '\0';

				return 1;
			}
			else
			{
				int64_t tSignValue = -(pInt64 < 0);
				uint64_t val = (pInt64 ^ tSignValue) - tSignValue;
				int tRequiredNumberOfCharacters = 0;
				char * c = pChars;
				char * d = NULL;

				if(val >= 0x3B9ACA00/*VC6 1000000000ll*/)//10
				{
					if(val >= 0x5AF3107A4000/*VC6 100000000000000ll*/)//15
					{
						if(val >= 0x16345785D8A0000/*VC6 100000000000000000ll*/)//18
						{
							if(val >= 0x8AC7230489E80000/*VC6 10000000000000000000ll*/)
								{tRequiredNumberOfCharacters = 20;}
							else if(val >= 0xDE0B6B3A7640000/*VC6 1000000000000000000ll*/)
								{tRequiredNumberOfCharacters = 19;}
							else
								{tRequiredNumberOfCharacters = 18;}
						}
						else
						{
							if(val >= 0x2386F26FC10000/*VC6 10000000000000000ll*/)
								{tRequiredNumberOfCharacters = 17;}
							else if(val >= 0x38D7EA4C68000/*VC6 1000000000000000ll*/)
								{tRequiredNumberOfCharacters = 16;}
							else
								{tRequiredNumberOfCharacters = 15;}
						}
					}
					else
					{
						if(val >= 0xE8D4A51000/*VC6 1000000000000ll*/)//13
						{
							if(val >= 0x9184E72A000/*VC6 10000000000000ll*/)
								{tRequiredNumberOfCharacters = 14;}
							else
								{tRequiredNumberOfCharacters = 13;}
						}
						else
						{
							if(val >= 0x174876E800/*VC6 100000000000ll*/)
								{tRequiredNumberOfCharacters = 12;}
							else if (val >= 0x2540BE400/*VC6 10000000000ll*/)
								{tRequiredNumberOfCharacters = 11;}
							else
								{tRequiredNumberOfCharacters = 10;}
						}
					}
				}
				else
				{
					if(val >= 2710/*VC6 10000ll*/)//5
					{
						if(val >= 0x989680/*VC6 10000000ll*/)
						{
							if(val >= 0x5F5E100/*VC6 100000000ll*/)
								{tRequiredNumberOfCharacters = 9;}
							else
								{tRequiredNumberOfCharacters = 8;}
						}
						else
						{
							if(val >= 0xF4240/*VC6 1000000ll*/)
								{tRequiredNumberOfCharacters = 7;}
							else if(val >= 0x186A0/*VC6 100000ll*/)
								{tRequiredNumberOfCharacters = 6;}
							else
								{tRequiredNumberOfCharacters = 5;}
						}
					}
					else
					{
						if(val >= 0x64/*VC6 100ll*/)
						{
							if(val >= 0x3E8/*VC6 1000ll*/)
								{tRequiredNumberOfCharacters = 4;}
							else
								{tRequiredNumberOfCharacters = 3;}
						}
						else
						{
							if(val >= 0xA/*VC6 10ll*/)
								{tRequiredNumberOfCharacters = 2;}
							else
								{tRequiredNumberOfCharacters = 1;}
						}
					}
				}

				if(tSignValue)
				{
					tRequiredNumberOfCharacters++;
					*pChars = '-';
				}

				d = pChars + tRequiredNumberOfCharacters - 1;

				while(val > 0)
				{
					*d-- = '0' + static_cast<char>(val % 10);
					val /= 10;
				}

				*(pChars + tRequiredNumberOfCharacters) = '\0';

				return tRequiredNumberOfCharacters;
			}
		}
#endif
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() bool Var::convertStringToBool(char const * pString, bool * pIsError)
		{
			char const * vChars = pString;
			bool vIsFound = false;
			bool vReturn = false;

			if(*vChars == 'T')
			{
				vChars++;

				if(*vChars == 'R')
				{
					vChars++;

					if(*vChars == 'U')
					{
						vChars++;

						if(*vChars == 'E')
						{
							vIsFound = true;
							vReturn = true;
						}
					}
				}
			}
			else if(*vChars == 'F')
			{
				vChars++;

				if(*vChars == 'A')
				{
					vChars++;

					if(*vChars == 'L')
					{
						vChars++;

						if(*vChars == 'S')
						{
							vChars++;

							if(*vChars == 'E')
							{
								vIsFound = true;
								vReturn = false;
							}
						}
					}
				}
			}
		
			if(vIsFound)
			{
				vChars++;

				if(*vChars != '\0')
					{vIsFound = false;}
			}
			else
				{vIsFound = false;}

			if(pIsError != NULL)
				{*pIsError = !vIsFound;}

			return vReturn;
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() bool Var::convertStringToBool(char const * pChars, size_t pLength, bool * pIsError)
		{
			char const * vChars = pChars;
			size_t vLength = pLength;
			bool vIsFound = false;
			bool vReturn = false;

			while(vLength &&  (*vChars == 127 || ((*vChars >= 0) && (*vChars <= 32))))
			{
				vChars++;
				vLength--;
			}


			if(vLength && (*vChars == 'T'))
			{
				vChars++;
				vLength--;

				if(vLength && (*vChars == 'R'))
				{
					vChars++;
					vLength--;

					if(vLength && (*vChars == 'U'))
					{
						vChars++;
						vLength--;

						if(vLength && (*vChars == 'E'))
						{
							vIsFound = true;
							vReturn = true;
						}
					}
				}
			}
			else if(vLength && (*vChars == 'F'))
			{
				vChars++;
				vLength--;

				if(vLength && (*vChars == 'A'))
				{
					vChars++;
					vLength--;

					if(vLength && (*vChars == 'L'))
					{
						vChars++;
						vLength--;

						if(vLength && (*vChars == 'S'))
						{
							vChars++;
							vLength--;

							if(vLength && (*vChars == 'E'))
							{
								vIsFound = true;
								vReturn = false;
							}
						}
					}
				}
			}
		
			if(vIsFound)
			{
				vChars++;
				vLength--;

				//if((vLength != 0) && ((vLength != 1) || (*vChars != '\0')))
				if(vLength != 0)
					{vIsFound = false;}
			}
			else
				{vIsFound = false;}

			if(pIsError != NULL)
				{*pIsError = !vIsFound;}

			return vReturn;
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() bool Var::looseConvertStringToBool(char const * pString, bool * pIsError)
		{
			char const * vChars = pString;
			bool vIsFound = false;
			bool vReturn = false;

			while(*vChars &&  (*vChars == 127 || ((*vChars >= 0) && (*vChars <= 32))))
				{vChars++;}


			if((*vChars == 't') || (*vChars == 'T'))
			{
				vChars++;

				if((*vChars == 'r') || (*vChars == 'R'))
				{
					vChars++;

					if((*vChars == 'u') || (*vChars == 'U'))
					{
						vChars++;

						if((*vChars == 'e') || (*vChars == 'E'))
						{
							vIsFound = true;
							vReturn = true;
						}
					}
				}
			}
			else if((*vChars == 'f') || (*vChars == 'F'))
			{
				vChars++;

				if((*vChars == 'a') || (*vChars == 'A'))
				{
					vChars++;

					if((*vChars == 'l') || (*vChars == 'L'))
					{
						vChars++;

						if((*vChars == 's') || (*vChars == 'S'))
						{
							vChars++;

							if((*vChars == 'e') || (*vChars == 'E'))
							{
								vIsFound = true;
								vReturn = false;
							}
						}
					}
				}
			}
		
			if(vIsFound)
			{
				vChars++;

				while(*vChars &&  (*vChars == 127 || (*vChars >= 0) && (*vChars <= 32)))
					{vChars++;}

				if(*vChars != '\0')
					{vIsFound = false;}
			}
			else
				{vIsFound = false;}

			if(pIsError != NULL)
				{*pIsError = !vIsFound;}

			return vReturn;
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() bool Var::looseConvertStringToBool(char const * pChars, size_t pLength, bool * pIsError)
		{
			char const * vChars = pChars;
			size_t vLength = pLength;
			bool vIsFound = false;
			bool vReturn = false;

			while(vLength &&  (*vChars == 127 || ((*vChars >= 0) && (*vChars <= 32))))
			{
				vChars++;
				vLength--;
			}


			if(vLength && ((*vChars == 't') || (*vChars == 'T')))
			{
				vChars++;
				vLength--;

				if(vLength && ((*vChars == 'r') || (*vChars == 'R')))
				{
					vChars++;
					vLength--;

					if(vLength && ((*vChars == 'u') || (*vChars == 'U')))
					{
						vChars++;
						vLength--;

						if(vLength && ((*vChars == 'e') || (*vChars == 'E')))
						{
							vIsFound = true;
							vReturn = true;
						}
					}
				}
			}
			else if(vLength && ((*vChars == 'f') || (*vChars == 'F')))
			{
				vChars++;
				vLength--;

				if(vLength && ((*vChars == 'a') || (*vChars == 'A')))
				{
					vChars++;
					vLength--;

					if(vLength && ((*vChars == 'l') || (*vChars == 'L')))
					{
						vChars++;
						vLength--;

						if(vLength && ((*vChars == 's') || (*vChars == 'S')))
						{
							vChars++;
							vLength--;

							if(vLength && ((*vChars == 'e') || (*vChars == 'E')))
							{
								vIsFound = true;
								vReturn = false;
							}
						}
					}
				}
			}
		
			if(vIsFound)
			{
				vChars++;
				vLength--;

				while(vLength &&  (*vChars == 127 || ((*vChars >= 0) && (*vChars <= 32))))
				{
					vChars++;
					vLength--;
				}

				//if((vLength != 0) && ((vLength != 1) || (*vChars != '\0')))
				if(vLength != 0)
					{vIsFound = false;}
			}
			else
				{vIsFound = false;}

			if(pIsError != NULL)
				{*pIsError = !vIsFound;}

			return vReturn;
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() bool Var::isNan(double pDouble)
		{
#ifndef isnan
	#if(__cplusplus < 201103L)	//C++11		//<= 199711L  // c++98 or older
		#if(defined(_MSC_VER) || defined(__BORLANDC__))
			return (::_isnan(pDouble) != 0);
		#elif(defined(__APPLE__) && defined(__GNUC__) && (__GNUC__ < 4))
			return (__isnand(pDouble));
		#else
			return (::isnan(pDouble)); //NOT SURE
		#endif
	#else
			return (::std::isnan(pDouble));
	#endif
#else
			return (isnan(pDouble));
#endif
		}
		#pragma endregion STATIC FUNCTIONS //}

		#pragma region BASIC CONSTRUCTOR //{
		/*The following created the 'Null' type, with the Var being not thread possible*/
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var() : gData(CRX__VAR__PRIVATE__POD_ZERO)
			{CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)}

		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(Var::Nil pNil, 
				bool pIsToBeThreadPossible CRX_DEFAULT(false)) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_NULL;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_NULL;}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(Var::Undefined pUndefined, 
				bool pIsToBeThreadPossible CRX_DEFAULT(false)) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_UNDEFINED;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_UNDEFINED;}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(bool pIsToBeThreadPossible, Var::Type pType) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			CRX__VAR__GUARD(pType != Var::TYPE__ERROR);
#endif

			unsigned char vType = CRX__VAR__TYPE_NULL;

			switch(pType)
			{
				case Var::TYPE__STRING:
					vType = CRX__VAR__TYPE_STRING;
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					new(&(this->gData.uString.uStd.gString)) ::std::string /*= ::std::string()*/;
#else
					this->gData.uString.uData.uSmallString.gLength = 1;
					this->gData.uString.uData.uSmallString.gBytes[0] = '\0';
#endif
					break;
				case Var::TYPE__HASH_TABLE:
					vType = CRX__VAR__TYPE_HASH_TABLE;
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					this->gData.uHashTable.gUnorderedMap = 
							new ::crx::ClassUnorderedMap<::std::string, Var>::t();
#else
					CRX__VAR__KHash_new(this->gData.uHashTable.gKHash);
#endif
					break;
				case Var::TYPE__ARRAY:
					vType = CRX__VAR__TYPE_ARRAY;
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					this->gData.uArray.gDeque = new ::std::deque<Var>();
#else
					CRX__VAR__CONSTRUCT_VARRING(this->gData.uArray.gVarRing, 0);
#endif
					break;
				case Var::TYPE__BYTE:
					vType = CRX__VAR__TYPE_UNSIGNED_CHAR;
					break;
				case Var::TYPE__NUMBER:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
					vType = CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32;
#else
					vType = CRX__VAR__TYPE_EMULATED_INT;
#endif
					break;
				case Var::TYPE__BOOL:
					vType = CRX__VAR__TYPE_BOOL;
					break;
				case Var::TYPE__POINTER:
					//vType = CRX__VAR__TYPE_POINTER;
					//this->gData.uPointer.gPointer = new Var_Pointer();
					vType = CRX__VAR__TYPE_NULL; //THIS IS NOT AN ERROR
					break;
				case Var::TYPE__NIL:
					vType = CRX__VAR__TYPE_NULL;
					break;
				case Var::TYPE__UNDEFINED:
					vType = CRX__VAR__TYPE_UNDEFINED;
					break;
			}

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						vType;
			}
			else
				{this->gData.uInfo.gInfo = vType;}
		}
		#pragma endregion BASIC CONSTRUCTOR //}

		#pragma region COPY CONSTRUCTOR //{
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(Var const & pVar) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

			if(CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
				{this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE;}

			this->unsafeCopyInitializeFromVar(pVar);
		};
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(Var const & pVar, bool pIsToBeThreadPossible) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

			if(pIsToBeThreadPossible)
				{this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE;}

			this->unsafeCopyInitializeFromVar(pVar);
		};
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || !CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(::std::string const & pString, bool pIsToBeThreadPossible CRX_DEFAULT(false)) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_STRING;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_STRING;}
	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			new(&(this->gData.uString.uStd.gString)) ::std::string(pString);
	#else
			this->addStringEndIntoIndex(0, pString.c_str(), pString.size() + 1, true);
	#endif
		}
#endif
//#if(defined(_MSC_VER) && (_MSC_VER <= 1200))
		//DID NOT WORK. SEE THE TEMPLATED VAR CONSTRUCTOR FOR DETAIL.
		//CRX_PRIVATE CRX__LIB__METHOD() void Var::doVar(char const * pString, bool pIsToBeThreadPossible CRX_DEFAULT(false))
//#else
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(char const * pString, bool pIsToBeThreadPossible CRX_DEFAULT(false)) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_STRING;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_STRING;}

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			new(&(this->gData.uString.uStd.gString)) ::std::string(pString);
#else
			this->addStringEndIntoIndex(0, pString, strlen(pString) + 1, true);
#endif
		}
//#endif
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap, 
				bool pIsToBeThreadPossible CRX_DEFAULT(false)) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			if(pIsToBeThreadPossible)
			{
				crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator tIterator = 
						pUnorderedMap.begin();
						
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_HASH_TABLE;
						
				this->gData.uHashTable.gUnorderedMap = new ::crx::ClassUnorderedMap<::std::string, Var>::t();

				while(tIterator != pUnorderedMap.end())
				{
					Var tVar(Var::TYPE__UNDEFINED, true);

					(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = tVar;
					(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = (*tIterator).second;

					tIterator++;
				}
			}
			else
			{
				this->gData.uInfo.gInfo = CRX__VAR__TYPE_HASH_TABLE;

				this->gData.uHashTable.gUnorderedMap = 
						new ::crx::ClassUnorderedMap<::std::string, Var>::t(pUnorderedMap);
			}
	#else
			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_HASH_TABLE;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_HASH_TABLE;}

			CRX__VAR__KHash_new(this->gData.uHashTable.gKHash);
			CRX__VAR__KHash_copyFromVarHashTable2(this->gData.uHashTable.gKHash, 
					pUnorderedMap, pIsToBeThreadPossible);
	#endif
		}
#endif
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(::std::deque<Var> const & pDeque, bool pIsToBeThreadPossible CRX_DEFAULT(false)) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

	#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_ARRAY;
			
				this->gData.uArray.gDeque = new ::std::deque<Var>();

				for(size_t tI = 0; tI < pDeque.size(); tI++)
				{
					Var tVar(Var::TYPE__UNDEFINED, true);

					this->gData.uArray.gDeque->push_back(tVar);
					(*(this->gData.uArray.gDeque))[tI] = pDeque[tI];
				}
			}
			else
			{
				this->gData.uInfo.gInfo = CRX__VAR__TYPE_ARRAY;

				this->gData.uArray.gDeque = new ::std::deque<Var>(pDeque);
			}
	#else
			CRX__VAR__CONSTRUCT_VARRING(this->gData.uArray.gVarRing, 0);

			CRX__VAR__GUARD(crx_varRing_ensureCapacity(CRX__VAR__GET_VARRING(this), pDeque.size()));

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_ARRAY;

				for(size_t tI = 0; tI < pDeque.size(); tI++)
				{
					Var tVar(Var::TYPE__UNDEFINED, true);

					crx_varRing_push(CRX__VAR__GET_VARRING(this), &tVar);
					*(crx_varRing_get(CRX__VAR__GET_VARRING(this), tI)) = pDeque[tI];
				}
			}
			else
			{
				this->gData.uInfo.gInfo = CRX__VAR__TYPE_ARRAY;
				
				for(size_t tI = 0; tI < pDeque.size(); tI++)
					{crx_varRing_push(CRX__VAR__GET_VARRING(this), &(pDeque[tI]));}
			}
	#endif
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(unsigned char const & pUnsignedChar, bool pIsToBeThreadPossible CRX_DEFAULT(false)) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_UNSIGNED_CHAR;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_UNSIGNED_CHAR;}

			this->gData.uIntegral.uUnsignedChar = pUnsignedChar;
		}
#if((!CRX__VAR__IS_EMULATED_INT_USED && CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64) || CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(uint32_t pUnsignedInt32, bool pIsToBeThreadPossible CRX_DEFAULT(false)) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

	#if(!CRX__VAR__IS_EMULATED_INT_USED)
			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_SIGNED_INT64;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_SIGNED_INT64;}

			this->gData.uIntegral.uSignedInt64 = static_cast<int64_t>(pUnsignedInt32);
	#else
			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_EMULATED_INT;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_EMULATED_INT;}

			this->gData.uIntegral.uDouble = static_cast<double>(pUnsignedInt32);
	#endif

			/*if(pUnsignedInt32 > INT32_MAX)
			{
				if(pIsToBeThreadPossible)
				{
					this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
							CRX__VAR__TYPE_DOUBLE;
				}
				else
					{this->gData.uInfo.gInfo = CRX__VAR__TYPE_DOUBLE;}

				this->gData.uIntegral.uDouble = NAN;
			}
			else
			{
				if(pIsToBeThreadPossible)
				{
					this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
							CRX__VAR__TYPE_SIGNED_INT32;
				}
				else
					{this->gData.uInfo.gInfo = CRX__VAR__TYPE_SIGNED_INT32;}

				this->gData.uIntegral.uSignedInt32 = static_cast<int32_t>(pUnsignedInt32);
			}*/
		}
#else
		CRX_DISABLED_METHOD(Var::Var(uint32_t pUnsignedInt32))
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(int32_t const & pSignedInt, bool pIsToBeThreadPossible CRX_DEFAULT(false)) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

#if(!CRX__VAR__IS_EMULATED_INT_USED)
			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32;}

			CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) = 
					static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt);
#else	
			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_EMULATED_INT;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_EMULATED_INT;}

			this->gData.uIntegral.uDouble = static_cast<double>(pSignedInt);
#endif
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var::Var(uint64_t pUnsignedInt64))
	#if(CRX__VAR__IS_EMULATED_INT_USED || CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(int64_t pSignedInt64, bool pIsToBeThreadPossible CRX_DEFAULT(false)) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

		#if(!CRX__VAR__IS_EMULATED_INT_USED)
			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_SIGNED_INT64;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_SIGNED_INT64;}
	
			this->gData.uIntegral.uSignedInt64 = static_cast<int64_t>(pSignedInt64);

			/*
			if((pSignedInt64 > INT32_MAX) || (pSignedInt64 < INT32_MIN))
			{
				if(pIsToBeThreadPossible)
				{
					this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
							CRX__VAR__TYPE_SIGNED_INT32;
				}
				else
					{this->gData.uInfo.gInfo = CRX__VAR__TYPE_SIGNED_INT32;}
	
				this->gData.uIntegral.uSignedInt32 = static_cast<int32_t>(pSignedInt64);
			}
			else
			{
				if(pIsToBeThreadPossible)
				{
					this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
							CRX__VAR__TYPE_DOUBLE;
				}
				else
					{this->gData.uInfo.gInfo = CRX__VAR__TYPE_DOUBLE;}
	
				this->gData.uIntegral.uDouble = NAN;
			}
			*/
		#else
			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_EMULATED_INT;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_EMULATED_INT;}

			if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
					(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
				{this->gData.uIntegral.uDouble = NAN;}
			else
				{this->gData.uIntegral.uDouble = static_cast<double>(pSignedInt64);}
		#endif
		}
	#else
		CRX_DISABLED_METHOD(Var::Var(int64_t pSignedInt64))
	#endif
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(float const & pFloat, bool pIsToBeThreadPossible CRX_DEFAULT(false)) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_DOUBLE;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_DOUBLE;}

			this->gData.uIntegral.uDouble = static_cast<double>(pFloat);
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(double const & pDouble, bool pIsToBeThreadPossible CRX_DEFAULT(false)) : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_DOUBLE;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_DOUBLE;}
			
			this->gData.uIntegral.uDouble = pDouble;
		}
#if(CRX__VAR__IS_ERROR_TYPE_AVAILABLE_FOR_PUBLIC_USE)
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(uint32_t gCode, ::std::string const pMessage, bool pIsToBeThreadPossible CRX_DEFAULT(false))
		{
			CRX__VAR__GUARD(gCode > CRX__VAR__LARGEST_RESERVED_ERROR_CODE);

			size_t vSizeOfString /*= ?*/;

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_ERROR;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_ERROR;}

			this->gData.uError.gCode = gCode;
			//this->gData.uError.gString = new(::std::nothrow) ::std::string(pMessage);

			if(pMessage.size() < UINT16_MAX)
				{vSizeOfString = pMessage.size();}
			else
				{vSizeOfString = UINT16_MAX - 1;}
			
			this->gData.uError.gString = ((char *) ::malloc(vSizeOfString + 1));

			if(this->gData.uError.gString != NULL)
			{
				this->gData.uError.gLength = static_cast<uint16_t>(vSizeOfString + 1);

				::memcpy(this->gData.uError.gString, pMessage.c_str(), vSizeOfString);
				*(this->gData.uError.gString + vSizeOfString) = '\0';
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(uint32_t gCode, char const * pMessage, bool pIsToBeThreadPossible CRX_DEFAULT(false))
		{
			CRX__VAR__GUARD(gCode > CRX__VAR__LARGEST_RESERVED_ERROR_CODE);
			size_t vSizeOfString = ::strlen(pMessage);

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_ERROR;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_ERROR;}

			this->gData.uError.gCode = gCode;
			//this->gData.uError.gString = new(::std::nothrow) ::std::string(pMessage);

			if(vSizeOfString >= UINT16_MAX)
				{vSizeOfString = UINT16_MAX - 1;}
			
			this->gData.uError.gString = ((char *) ::malloc(vSizeOfString + 1));

			if(this->gData.uError.gString != NULL)
			{
				this->gData.uError.gLength = static_cast<uint16_t>(vSizeOfString + 1);

				::memcpy(this->gData.uError.gString, pMessage, vSizeOfString);
				*(this->gData.uError.gString + vSizeOfString) = '\0';
			}
		}
#endif
		// /* //UNSAFE PRE C++11, BUT SAFE AFTERWARDS
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(bool pBool, bool pIsToBeThreadPossible CRX_DEFAULT(false))
		{
			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_BOOL;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_BOOL;}

			this->gData.uIntegral.uBool = pBool;
		} // */
		/*CRX_PUBLIC CRX__LIB__METHOD() Var::Var(Var::VarBoolean pVarBoolean, bool pIsToBeThreadPossible CRX_DEFAULT(false))
		{
			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_BOOL;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_BOOL;}

			this->gData.uIntegral.uBool = pVarBoolean.gBool;
		}*/
		#pragma endregion COPY CONSTRUCTOR //}

		#pragma region LIST INITIALIZATION CONSTRUCTOR //{
#ifndef CRX__BOOST_NO_CXX11_HDR_INITIALIZER_LIST
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(
				::std::initializer_list<::std::pair<::std::string const, Var>> pInitializerList)
		{
			/*::std::initializer_list<::std::pair<::std::string const, Var>>::iterator vIterator = 
					pInitializerList.begin();*/

	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			if(true)
			{
				::std::initializer_list<::std::pair<::std::string const, Var>>::iterator tIterator = 
						pInitializerList.begin();

				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_HASH_TABLE;
						
				this->gData.uHashTable.gUnorderedMap = new ::crx::ClassUnorderedMap<::std::string, Var>::t();

				while(tIterator != pInitializerList.end())
				{
					Var tVar(Var::TYPE__UNDEFINED, true);

					(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = tVar;
					(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = (*tIterator).second;

					tIterator++;
				}
			}
			else
			{
				this->gData.uInfo.gInfo = CRX__VAR__TYPE_HASH_TABLE;
				
				this->gData.uHashTable.gUnorderedMap = 
						new ::crx::ClassUnorderedMap<::std::string, Var>::t(pInitializerList);
			}
	#else
			::std::initializer_list<::std::pair<::std::string const, Var>>::iterator vIterator = 
					pInitializerList.begin();

			CRX__VAR__KHash_new(this->gData.uHashTable.gKHash);

			if(true)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_HASH_TABLE;

				while(vIterator != pInitializerList.end())
				{
					CRX__VAR__KHash_set(this->gData.uHashTable.gKHash, 
							(*vIterator).first.c_str(), &((*vIterator).second), true);

					vIterator++;
				}
			}
			else
			{
				this->gData.uInfo.gInfo = CRX__VAR__TYPE_HASH_TABLE;
				
				while(vIterator != pInitializerList.end())
				{
					CRX__VAR__KHash_set(this->gData.uHashTable.gKHash, 
							(*vIterator).first.c_str(), &((*vIterator).second), false);

					vIterator++;
				}
			}
	#endif

			/*while(vIterator != pInitializerList.end())
			{
				

				vIterator++;
			}*/
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(
				::std::initializer_list<::std::pair<::std::string const, Var>> pInitializerList, 
				bool pIsToBeThreadPossible)
		{
			/*::std::initializer_list<::std::pair<::std::string const, Var>>::iterator vIterator = 
					pInitializerList.begin();*/

	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			if(pIsToBeThreadPossible)
			{
				::std::initializer_list<::std::pair<::std::string const, Var>>::iterator tIterator = 
						pInitializerList.begin();

				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_HASH_TABLE;
						
				this->gData.uHashTable.gUnorderedMap = new ::crx::ClassUnorderedMap<::std::string, Var>::t();

				while(tIterator != pInitializerList.end())
				{
					Var tVar(Var::TYPE__UNDEFINED, true);

					(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = tVar;
					(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = (*tIterator).second;
				}
			}
			else
			{
				this->gData.uInfo.gInfo = CRX__VAR__TYPE_HASH_TABLE;
				
				this->gData.uHashTable.gUnorderedMap = 
						new ::crx::ClassUnorderedMap<::std::string, Var>::t(pInitializerList);
			}
	#else
			::std::initializer_list<::std::pair<::std::string const, Var>>::iterator vIterator = 
					pInitializerList.begin();

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_HASH_TABLE;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_HASH_TABLE;}

			CRX__VAR__KHash_new(this->gData.uHashTable.gKHash);

			while(vIterator != pInitializerList.end())
			{
				CRX__VAR__KHash_set(this->gData.uHashTable.gKHash, 
						(*vIterator).first.c_str(), &((*vIterator).second), pIsToBeThreadPossible);

				vIterator++;
			}
	#endif

			/*while(vIterator != pInitializerList.end())
			{
				

				vIterator++;
			}*/
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(Var::ARRAY_DEFINITION _s,
				::std::initializer_list<Var> pInitializerList)
		{
	#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
			if(true)
			{
				::std::initializer_list<Var>::iterator vIterator = pInitializerList.begin();

				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_ARRAY;

				while(vIterator != pInitializerList.end())
				{
					Var tVar(Var::TYPE__UNDEFINED, true);

					this->gData.uArray.gDeque->push_back(tVar);
					this->gData.uArray.gDeque[this->gData.uArray.gDeque->size() - 1] = *vIterator;

					vIterator++;
				}
			}
			else
			{
				this->gData.uInfo.gInfo = CRX__VAR__TYPE_ARRAY;

				this->gData.uArray.gDeque = new ::std::deque<Var>(pInitializerList);
			}
	#else
			::std::initializer_list<Var>::iterator vIterator = pInitializerList.begin();

			CRX__VAR__CONSTRUCT_VARRING(this->gData.uArray.gVarRing, 0);
			CRX__VAR__GUARD(crx_varRing_ensureCapacity(CRX__VAR__GET_VARRING(this), 
					pInitializerList.size()));

			if(true)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_ARRAY;

				while(vIterator != pInitializerList.end())
				{
					Var tVar(Var::TYPE__UNDEFINED, true);

					crx_varRing_push(CRX__VAR__GET_VARRING(this), &tVar);
					*(crx_varRing_get(CRX__VAR__GET_VARRING(this), 
							crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) - 1)) = *vIterator;

					vIterator++;
				}
			}
			else
			{
				this->gData.uInfo.gInfo = CRX__VAR__TYPE_ARRAY;

				while(vIterator != pInitializerList.end())
				{
					crx_varRing_push(CRX__VAR__GET_VARRING(this), &(*vIterator));

					vIterator++;
				}
			}
	#endif
		}		
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(Var::ARRAY_DEFINITION _s,
				::std::initializer_list<Var> pInitializerList, bool pIsToBeThreadPossible)
		{
	#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
			if(pIsToBeThreadPossible)
			{
				::std::initializer_list<Var>::iterator vIterator = pInitializerList.begin();

				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_ARRAY;

				while(vIterator != pInitializerList.end())
				{
					Var tVar(Var::TYPE__UNDEFINED, true);

					this->gData.uArray.gDeque->push_back(tVar);
					this->gData.uArray.gDeque[this->gData.uArray.gDeque->size() - 1] = *vIterator;

					vIterator++;
				}
			}
			else
			{
				this->gData.uInfo.gInfo = CRX__VAR__TYPE_ARRAY;

				this->gData.uArray.gDeque = new ::std::deque<Var>(pInitializerList);
			}
	#else
			::std::initializer_list<Var>::iterator vIterator = pInitializerList.begin();

			CRX__VAR__CONSTRUCT_VARRING(this->gData.uArray.gVarRing, 0);
			CRX__VAR__GUARD(crx_varRing_ensureCapacity(CRX__VAR__GET_VARRING(this), 
					pInitializerList.size()));

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_ARRAY;

				while(vIterator != pInitializerList.end())
				{
					Var tVar(Var::TYPE__UNDEFINED, true);

					crx_varRing_push(CRX__VAR__GET_VARRING(this), &tVar);
					*(crx_varRing_get(CRX__VAR__GET_VARRING(this), 
							crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) - 1)) = *vIterator;

					vIterator++;
				}
			}
			else
			{
				this->gData.uInfo.gInfo = CRX__VAR__TYPE_ARRAY;

				while(vIterator != pInitializerList.end())
				{
					crx_varRing_push(CRX__VAR__GET_VARRING(this), &(*vIterator));

					vIterator++;
				}
			}
	#endif
		}
#endif
		#pragma endregion LIST INITIALIZATION CONSTRUCTOR //}

		#pragma region MOVE CONSTRUCTOR //{
#ifndef CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(Var && pVar) CRX__VAR__PRIVATE__NOEXCEPT : gData(CRX__VAR__PRIVATE__POD_ZERO) 
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

			if(CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
				{this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE;}

			this->unsafeMoveInitializeFromVar(pVar);
		};
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(Var && pVar, bool pIsToBeThreadPossible) CRX__VAR__PRIVATE__NOEXCEPT : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

			if(pIsToBeThreadPossible)
				{this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE;}

			this->unsafeMoveInitializeFromVar(pVar);
		};
#endif
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		//IF NO MOVE SEMANTICS:	Var::Var(::std::string pString, bool pIsToBeThreadPossible = false)
		//IF MOVE SEMANTICS:	Var::Var(::std::string && pString, bool pIsToBeThreadPossible = false)
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(CRX__VAR__TYPE_FOR_MOVE(::std::string) pString, 
				bool pIsToBeThreadPossible CRX_DEFAULT(false)) CRX__VAR__PRIVATE__NOEXCEPT : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

			if(pIsToBeThreadPossible)
			{
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_STRING;
			}
			else
				{this->gData.uInfo.gInfo = CRX__VAR__TYPE_STRING;}

			new(&(this->gData.uString.uStd.gString)) ::std::string /*= ::std::string()*/;
			this->gData.uString.uStd.gString.swap(pString);
		}
#endif
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		//IF NO MOVE SEMANTICS:	Var::Var(::crx::ClassUnorderedMap<::std::string, Var>::t pUnorderedMap, 
		//		bool pIsToBeThreadPossible = true)
		//IF MOVE SEMANTICS:	Var::Var(::crx::ClassUnorderedMap<::std::string, Var>::t && pUnorderedMap, 
		//		bool pIsToBeThreadPossible = true)
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(CRX__VAR__TYPE_FOR_MOVE(Var::VarUnorderedMap) pUnorderedMap, 
				bool pIsToBeThreadPossible CRX_DEFAULT(true)) CRX__VAR__PRIVATE__NOEXCEPT : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

			if(pIsToBeThreadPossible)
			{
				crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator tIterator = 
						pUnorderedMap.begin();
				bool tIsMoveSafe;
				
				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_HASH_TABLE;

#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES))
				tIsMoveSafe = true;
			
				while(tIterator != pUnorderedMap.end())
				{
					if(!CRX__VAR__GET_IS_THREAD_POSSIBLE2((*tIterator).second))
					{
						tIsMoveSafe = false;
						break;
					}

					tIterator++;
				}
#else
				tIsMoveSafe = false;
#endif

				if(tIsMoveSafe)
				{
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES))
					this->gData.uHashTable.gUnorderedMap = 
							new ::crx::ClassUnorderedMap<::std::string, Var>::t(
							::std::move(pUnorderedMap));
#endif
				}
				else
				{
					this->gData.uHashTable.gUnorderedMap = 
							new ::crx::ClassUnorderedMap<::std::string, Var>::t();

					tIterator = pUnorderedMap.begin();

					while(tIterator != pUnorderedMap.end())
					{
						Var tVar(Var::TYPE__UNDEFINED, true);

						(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = tVar;
						(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = (*tIterator).second;

						tIterator++;
					}
				}
			}
			else
			{
				this->gData.uInfo.gInfo = CRX__VAR__TYPE_HASH_TABLE;
	#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES))
				this->gData.uHashTable.gUnorderedMap = 
						new ::crx::ClassUnorderedMap<::std::string, Var>::t(
						::std::move(pUnorderedMap));
	#else
				crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator tIterator = 
						pUnorderedMap.begin();

				this->gData.uHashTable.gUnorderedMap = 
						new ::crx::ClassUnorderedMap<::std::string, Var>::t();

				while(tIterator != pUnorderedMap.end())
				{
					Var tVar(Var::TYPE__UNDEFINED, true);

					(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = tVar;
					(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = (*tIterator).second;

					tIterator++;
				}
	#endif
			}
		}
#endif
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		//IF NO MOVE SEMANTICS:	Var::Var(::std::deque<Var> pDeque, bool pIsToBeThreadPossible CRX_DEFAULT(true))
		//IF MOVE SEMANTICS:	Var::Var(::std::deque<Var> && pDeque, bool pIsToBeThreadPossible CRX_DEFAULT(true))
		CRX_PUBLIC CRX__LIB__METHOD() Var::Var(CRX__VAR__TYPE_FOR_MOVE(::std::deque<Var>) pDeque, 
				bool pIsToBeThreadPossible CRX_DEFAULT(true)) CRX__VAR__PRIVATE__NOEXCEPT : gData(CRX__VAR__PRIVATE__POD_ZERO)
		{
			CRX__VAR__PRIVATE__SET_TO_ZERO_IF_NECESSARY(Var::Data, this->gData)

			if(pIsToBeThreadPossible)
			{
				bool tIsMoveSafe = true;

				this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_ARRAY;

#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES))
				tIsMoveSafe = true;
	
				for(size_t tI = 0; tI < pDeque.size(); tI++)
				{
					if(!CRX__VAR__GET_IS_THREAD_POSSIBLE2(pDeque[tI]))
					{
						tIsMoveSafe = false;
						break;
					}
				}
#else
				tIsMoveSafe = false;
#endif

				if(tIsMoveSafe)
				{
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES))
					this->gData.uArray.gDeque = new ::std::deque<Var>(::std::move(pDeque));
#endif
				}
				else
				{
					this->gData.uArray.gDeque = new ::std::deque<Var>();

					for(size_t tI = 0; tI < pDeque.size(); tI++)
					{
						Var tVar(Var::TYPE__UNDEFINED, true);

						this->gData.uArray.gDeque->push_back(tVar);
						(*(this->gData.uArray.gDeque))[tI] = pDeque[tI];
					}
				}
			}
			else
			{
				this->gData.uInfo.gInfo = CRX__VAR__TYPE_ARRAY;
	#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES))
				this->gData.uArray.gDeque = new ::std::deque<Var>(::std::move(pDeque));
	#else
				this->gData.uArray.gDeque = new ::std::deque<Var>();

				for(size_t tI = 0; tI < pDeque.size(); tI++)
				{
					Var tVar(Var::TYPE__UNDEFINED, true);

					this->gData.uArray.gDeque->push_back(tVar);
					(*(this->gData.uArray.gDeque))[tI] = pDeque[tI];
				}
	#endif
			}
		}
#endif
		#pragma endregion MOVE CONSTRUCTOR //}

		#pragma region UTILITIES //{
		CRX_PRIVATE CRX__LIB__METHOD() void Var::unsafeCopyInitializeFromVar(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_STRING);
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					new(&(this->gData.uString.uStd.gString)) ::std::string(pVar.gData.uString.uStd.gString);
#else
					if(!CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) && !CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar) &&
							((CRX__VAR__STRING__GET_MODE2(pVar) == CRX__VAR__STRING__MODE__LARGE_BUFFER) || 
							(CRX__VAR__STRING__GET_MODE2(pVar) == CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT)))
					{
						CRX__VAR__STRING__SET_MODE(this, CRX__VAR__STRING__GET_MODE2(pVar));

						this->gData.uString.uData.uLargeString.gString = 
								pVar.gData.uString.uData.uLargeString.gString;

						if(CRX__VAR__STRING__GET_MODE2(pVar) ==
								CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT)
						{
							this->gData.uString.uData.uLargeString.gSegmentLength = 
									pVar.gData.uString.uData.uLargeString.gSegmentLength;
							this->gData.uString.uData.uLargeString.gOffset = 
									pVar.gData.uString.uData.uLargeString.gOffset;
						}

						this->gData.uString.uData.uLargeString.gString->gCount++;
					}
					else
						{this->addStringEndFromVarIntoIndex(0, pVar);}
#endif
					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_HASH_TABLE);
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) != CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
					{
						bool tIS_THREAD_POSSIBLE = CRX__VAR__GET_IS_THREAD_POSSIBLE1(this);

						crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator tIterator = 
								pVar.gData.uHashTable.gUnorderedMap->begin();

						this->gData.uHashTable.gUnorderedMap = 
								new ::crx::ClassUnorderedMap<::std::string, Var>::t();

						while(tIterator != pVar.gData.uHashTable.gUnorderedMap->end())
						{
							Var tVar(Var::TYPE__UNDEFINED, tIS_THREAD_POSSIBLE);

							(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = tVar;
							(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = (*tIterator).second;

							tIterator++;
						}
					}
					else
					{
						this->gData.uHashTable.gUnorderedMap = 
								new ::crx::ClassUnorderedMap<::std::string, Var>::t(
								*(pVar.gData.uHashTable.gUnorderedMap));
					}
#else
					CRX__VAR__KHash_new(this->gData.uHashTable.gKHash);

					CRX__VAR__KHash_copyAddDifferenceFromKHash(this->gData.uHashTable.gKHash, 
							pVar.gData.uHashTable.gKHash, 
							CRX__VAR__GET_IS_THREAD_POSSIBLE1(this));
#endif
					break;
				}
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_ARRAY);
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) != CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
					{
						bool tIS_THREAD_POSSIBLE = CRX__VAR__GET_IS_THREAD_POSSIBLE1(this);

						this->gData.uArray.gDeque = new ::std::deque<Var>();

						for(size_t tI = 0; tI < pVar.gData.uArray.gDeque->size(); tI++)
						{
							Var tVar(Var::TYPE__UNDEFINED, tIS_THREAD_POSSIBLE);

							this->gData.uArray.gDeque->push_back(tVar);
							(*(this->gData.uArray.gDeque))[tI] = (*(pVar.gData.uArray.gDeque))[tI];
						}
					}
					else
					{
						this->gData.uArray.gDeque = new ::std::deque<Var>(*(pVar.gData.uArray.gDeque));
						//this->gData.uArray.gDeque = pVar.gData.uArray.gDeque;
					}
#else
					CRX__VAR__CONSTRUCT_VARRING(this->gData.uArray.gVarRing, 0);

					if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) != CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
					{
						bool tIS_THREAD_POSSIBLE = CRX__VAR__GET_IS_THREAD_POSSIBLE1(this);

						CRX__VAR__GUARD(crx_varRing_ensureCapacity(CRX__VAR__GET_VARRING(this),
								crx_varRing_getLength(CRX__VAR__GET_VARRING2(pVar))));

						for(size_t tI = 0; tI < crx_varRing_getLength(CRX__VAR__GET_VARRING2(pVar)); tI++)
						{
							Var tVar(Var::TYPE__UNDEFINED, tIS_THREAD_POSSIBLE);

							crx_varRing_push(CRX__VAR__GET_VARRING(this), &tVar);
							*(crx_varRing_get(CRX__VAR__GET_VARRING(this), tI)) = 
									*(crx_varRing_constantGet(CRX__VAR__GET_VARRING2(pVar), tI));
						}
					}
					else
					{
						CRX__VAR__GUARD(crx_varRing_insertElementsAt(CRX__VAR__GET_VARRING(this), 
								0, CRX__VAR__GET_VARRING2(pVar), 0, 
								crx_varRing_getLength(CRX__VAR__GET_VARRING2(pVar))));
					}
#endif
					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_UNSIGNED_CHAR);
					this->gData.uIntegral.uUnsignedChar = pVar.gData.uIntegral.uUnsignedChar;
					
					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32);
					CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) = CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar);

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_EMULATED_INT);
					this->gData.uIntegral.uDouble = pVar.gData.uIntegral.uDouble;

					break;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
					this->gData.uIntegral.uDouble = pVar.gData.uIntegral.uDouble;

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_BOOL);
					this->gData.uIntegral.uBool = pVar.gData.uIntegral.uBool;

					break;
				}
				case CRX__VAR__TYPE_POINTER:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_POINTER);
					this->gData.uPointer.gPointer = pVar.gData.uPointer.gPointer->clone();
					
					break;
				}
				case CRX__VAR__TYPE_NULL:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_NULL);
					
					break;
				}
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_UNDEFINED);
					
					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_ERROR);
					this->copyInitializeErrorFrom(pVar);

					break;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}
		}
#ifndef CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
		CRX_PRIVATE CRX__LIB__METHOD() void Var::unsafeMoveInitializeFromVar(Var & pVar) CRX__VAR__PRIVATE__NOEXCEPT
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_STRING);
	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					/*
						FOR CONSISTENCY WITH THE MOVE CONSTRUCTOR THAT ACCEPTS ::std::string, THE 
								FOLLOWING APPROACH IS NOT USED.
					*/
					//new(this->gData.uString.uStd.gString) ::std::string(::std::move(pVar));

					new(&(this->gData.uString.uStd.gString)) ::std::string /*= ::std::string()*/;
					this->gData.uString.uStd.gString.swap(pVar.gData.uString.uStd.gString);
	#else
					if(((CRX__VAR__STRING__GET_MODE2(pVar) == CRX__VAR__STRING__MODE__LARGE_BUFFER) ||
									(CRX__VAR__STRING__GET_MODE2(pVar) == 
											CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT)) &&
							((pVar.gData.uString.uData.uLargeString.gString->gCount < 2) ||
									!CRX__VAR__GET_IS_THREAD_POSSIBLE1(this)))
					{
						CRX__VAR__STRING__SET_MODE(this, CRX__VAR__STRING__GET_MODE2(pVar));

						this->gData.uString.uData.uLargeString.gString = 
								pVar.gData.uString.uData.uLargeString.gString;
								
						if(CRX__VAR__STRING__GET_MODE2(pVar) == CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT)
						{
							this->gData.uString.uData.uLargeString.gSegmentLength = 
									pVar.gData.uString.uData.uLargeString.gSegmentLength;
							this->gData.uString.uData.uLargeString.gOffset = 
									pVar.gData.uString.uData.uLargeString.gOffset;
						}

						CRX__VAR__STRING__SET_MODE2(pVar, CRX__VAR__STRING__MODE__SMALL_BUFFER);
						pVar.gData.uString.uData.uSmallString.gLength = 0;
					}
					else
						{this->addStringEndFromVarIntoIndex(0, pVar);}
	#endif
					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_HASH_TABLE);
	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) != CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
					{
						bool tIS_THREAD_POSSIBLE = CRX__VAR__GET_IS_THREAD_POSSIBLE1(this);

						crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator tIterator = 
								pVar.gData.uHashTable.gUnorderedMap->begin();

						this->gData.uHashTable.gUnorderedMap = 
								new ::crx::ClassUnorderedMap<::std::string, Var>::t();

						while(tIterator != pVar.gData.uHashTable.gUnorderedMap->end())
						{
							Var tVar(Var::TYPE__UNDEFINED, tIS_THREAD_POSSIBLE);

							(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = tVar;
							(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = (*tIterator).second;

							tIterator++;
						}
					}
					else
					{
						//this->gData.uHashTable.gUnorderedMap->swap(*(pVar.gData.uHashTable.gUnorderedMap));

						this->gData.uHashTable.gUnorderedMap = pVar.gData.uHashTable.gUnorderedMap;
						pVar.gData.uHashTable.gUnorderedMap = NULL;
						CRX__VAR__SET_TYPE2(pVar, CRX__VAR__TYPE_NULL);
					}
	#else
					if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) != CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
					{
						CRX__VAR__KHash_new(this->gData.uHashTable.gKHash);

						CRX__VAR__KHash_copyAddDifferenceFromKHash(this->gData.uHashTable.gKHash, 
								pVar.gData.uHashTable.gKHash, CRX__VAR__GET_IS_THREAD_POSSIBLE1(this));
					}
					else
					{
						this->gData.uHashTable.gKHash = pVar.gData.uHashTable.gKHash;
						pVar.gData.uHashTable.gKHash = NULL;
						CRX__VAR__SET_TYPE2(pVar, CRX__VAR__TYPE_NULL);
					}
	#endif
					break;
				}
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_ARRAY);
	#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) != CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
					{
						bool tIS_THREAD_POSSIBLE = CRX__VAR__GET_IS_THREAD_POSSIBLE1(this);

						this->gData.uArray.gDeque = new ::std::deque<Var>();

						for(size_t tI = 0; tI < pVar.gData.uArray.gDeque->size(); tI++)
						{
							Var tVar(Var::TYPE__UNDEFINED, tIS_THREAD_POSSIBLE);

							this->gData.uArray.gDeque->push_back(tVar);
							(*(this->gData.uArray.gDeque))[tI] = (*(pVar.gData.uArray.gDeque))[tI];
						}
					}
					else
					{
						this->gData.uArray.gDeque = pVar.gData.uArray.gDeque;
						pVar.gData.uArray.gDeque = NULL;

						CRX__VAR__SET_TYPE2(pVar, CRX__VAR__TYPE_NULL);
					}
	#else
					if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) != CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
					{
						bool tIS_THREAD_POSSIBLE = CRX__VAR__GET_IS_THREAD_POSSIBLE1(this);

						CRX__VAR__CONSTRUCT_VARRING(this->gData.uArray.gVarRing, 0);
						CRX__VAR__GUARD(crx_varRing_ensureCapacity(CRX__VAR__GET_VARRING(this),
								crx_varRing_getLength(CRX__VAR__GET_VARRING2(pVar))));

						for(size_t tI = 0; tI < crx_varRing_getLength(CRX__VAR__GET_VARRING2(pVar)); tI++)
						{
							Var tVar(Var::TYPE__UNDEFINED, tIS_THREAD_POSSIBLE);

							crx_varRing_push(CRX__VAR__GET_VARRING(this), &tVar);
							*(crx_varRing_get(CRX__VAR__GET_VARRING(this), tI)) = 
									*(crx_varRing_get(CRX__VAR__GET_VARRING2(pVar), tI));
						}
					}
					else
					{
						CRX__VAR__CONSTRUCT_VARRING(this->gData.uArray.gVarRing, 0); 	
						crx_varRing_pilferSwapContentWith(CRX__VAR__GET_VARRING(this),
								CRX__VAR__GET_VARRING2(pVar));
					}
	#endif
					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_UNSIGNED_CHAR);
					this->gData.uIntegral.uUnsignedChar = pVar.gData.uIntegral.uUnsignedChar;

					break;
				}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32);
					CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) = CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar);
					
					break;
				}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_EMULATED_INT);
					this->gData.uIntegral.uDouble = pVar.gData.uIntegral.uDouble;

					break;
				}
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
					this->gData.uIntegral.uDouble = pVar.gData.uIntegral.uDouble;

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_BOOL);
					this->gData.uIntegral.uBool = pVar.gData.uIntegral.uBool;

					break;
				}
				case CRX__VAR__TYPE_POINTER:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_POINTER);

					this->gData.uPointer.gPointer = pVar.gData.uPointer.gPointer;
					pVar.gData.uPointer.gPointer = NULL;
					CRX__VAR__SET_TYPE2(pVar, CRX__VAR__TYPE_NULL);

					break;
				}
				case CRX__VAR__TYPE_NULL:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_NULL);

					break;
				}
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_UNDEFINED);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_ERROR);
					this->copyInitializeErrorFrom(pVar);
					
					break;
				}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}
		}		
#endif
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
		CRX_PRIVATE CRX__LIB__METHOD() void Var::copyInitializeErrorFrom(Var const & pVar) CRX__VAR__PRIVATE__NOEXCEPT
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR);

			//::std::string * tString =  new(::std::nothrow) ::std::string(pVar.gData.uError.gString);
			
			this->gData.uError.gCode = pVar.gData.uError.gCode;

			/*if(tString !== NULL)
				{this->gData.uError.gString = tString;}*/
			
			this->gData.uError.gString = ((char *) ::malloc(pVar.gData.uError.gLength));

			if(this->gData.uError.gString != NULL)
			{
				this->gData.uError.gLength = pVar.gData.uError.gLength;

				::memcpy(this->gData.uError.gString, pVar.gData.uError.gString, pVar.gData.uError.gLength);
			}
		}
		CRX_PRIVATE CRX__LIB__METHOD() void Var::pilferErrorFrom(Var & pVar) CRX__VAR__PRIVATE__NOEXCEPT
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR);

			char * vString = this->gData.uError.gString;

			this->gData.uError.gCode = pVar.gData.uError.gCode;
			this->gData.uError.gString = pVar.gData.uError.gString;

			pVar.gData.uError.gString = vString;
		}
		
		CRX_PRIVATE CRX__LIB__METHOD() bool Var::assignPropogateErrorFrom(Var const & pVar) 
				CRX__VAR__PRIVATE__NOEXCEPT
		{
			if((CRX__VAR__GET_TYPE1(this) != CRX__VAR__TYPE_ERROR) &&
					(CRX__VAR__GET_TYPE2(pVar) == CRX__VAR__TYPE_ERROR))
			{
				//::std::string * tString =  new(::std::nothrow) ::std::string(pVar.gData.uError.gString);

				this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_ERROR);

				this->gData.uError.gCode = pVar.gData.uError.gCode;
				
				/*if(tString !== NULL)
				{
					if(this->gData.uError.gString != NULL)
						{delete this->gData.uError.gString;}

					this->gData.uError.gString = tString;
				}*/
				
				this->gData.uError.gString = ((char *) ::malloc(pVar.gData.uError.gLength));

				if(this->gData.uError.gString != NULL)
				{
					this->gData.uError.gLength = pVar.gData.uError.gLength;

					::memcpy(this->gData.uError.gString, pVar.gData.uError.gString, pVar.gData.uError.gLength);
				}
				else
					{this->gData.uError.gLength = 0;}
				
				return true;
			}
			else
				{return false;}
		}
#endif
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE void Var::emptyDynamicResourcesIfNecessaryForAssigment(
				unsigned char pType)
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING)
			{
				if(pType != CRX__VAR__TYPE_STRING)
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString.~basic_string();
#else
					switch(CRX__VAR__STRING__GET_MODE1(this))
					{
						case CRX__VAR__STRING__MODE__SMALL_BUFFER:
							{break;}
						case CRX__VAR__STRING__MODE__LARGE_BUFFER:
						case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
						{
							this->gData.uString.uData.uLargeString.gString->gCount--;

							if(this->gData.uString.uData.uLargeString.gString->gCount == 0)
							{
								Var::String::deleteString(
										this->gData.uString.uData.uLargeString.gString);
								this->gData.uString.uData.uLargeString.gString = NULL;
								/*CRX__VAR__STRING__SET_MODE(this, 
										CRX__VAR__STRING__MODE__SMALL_BUFFER);*/
							}

							break;
						}
					}
#endif
				}
			}
			else if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE)
			{
				if(pType != CRX__VAR__TYPE_HASH_TABLE)
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					if(this->gData.uHashTable.gUnorderedMap != NULL)
					{
						delete this->gData.uHashTable.gUnorderedMap;
						this->gData.uHashTable.gUnorderedMap = NULL;
					}
#else
					if(this->gData.uHashTable.gKHash != NULL)
					{
						CRX__VAR__KHash_delete(this->gData.uHashTable.gKHash);

						//delete this->gData.uHashTable.gKHash;
						this->gData.uHashTable.gKHash = NULL;
					}
#endif
				}
			}
			else if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY)
			{
				if(pType != CRX__VAR__TYPE_ARRAY)
				{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					if(this->gData.uArray.gDeque != NULL)
					{
						delete this->gData.uArray.gDeque;
						this->gData.uArray.gDeque = NULL;
					}
#else
					if(!CRX__VAR__IS_VARRING_NULL(this->gData.uArray.gVarRing))
					{
						//WARNING: SOMETHING WRONG HERE WHEN THE VarRing IS NOT A POINTER
						//		THIS IS BECAUSE UNLIKE THE Deque CASE, THERE IS IMMEDIATE
						//		ASSUMPTION THAT THE VarRing IS VALID WHEN THE TYPE IS
						//		CRX__VAR__TYPE_ARRAY (TODO), WHILE IN THE Deque CASE THIS
						//		IS NOT ASSUMED
						CRX__VAR__DELETE_VARRING(this->gData.uArray.gVarRing);
					}
#endif
				}
			}
			else if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_POINTER)
			{
				if(pType != CRX__VAR__TYPE_POINTER)
				{
					if(this->gData.uPointer.gPointer != NULL)
					{
						delete this->gData.uPointer.gPointer;
						this->gData.uPointer.gPointer = NULL;
					}
				}
			}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			else if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR)
			{
				if(pType != CRX__VAR__TYPE_ERROR)
				{
					if(this->gData.uError.gString != NULL)
					{
						::free(this->gData.uError.gString);
						this->gData.uError.gString = NULL;
					}
				}
			}
#endif

			if(CRX__VAR__GET_TYPE1(this) != pType)
			{
				if(pType == CRX__VAR__TYPE_STRING)
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					new(&(this->gData.uString.uStd.gString)) ::std::string /*= ::std::string()*/;
#else
					CRX__VAR__STRING__SET_MODE(this, CRX__VAR__STRING__MODE__SMALL_BUFFER);
					this->gData.uString.uData.uSmallString.gLength = 1;
					this->gData.uString.uData.uSmallString.gBytes[0] = '\0';
#endif
				}
				else if(pType == CRX__VAR__TYPE_HASH_TABLE)
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					this->gData.uHashTable.gUnorderedMap = new 
								crx::ClassUnorderedMap<::std::string, Var>::t();
#else
					CRX__VAR__KHash_new(this->gData.uHashTable.gKHash);
#endif
				}
				else if(pType == CRX__VAR__TYPE_ARRAY)
				{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					this->gData.uArray.gDeque = new ::std::deque<Var>();
#else
					CRX__VAR__ZERO_VARRING_BLOCK(this->gData.uArray.gVarRing);
					CRX__VAR__CONSTRUCT_VARRING(this->gData.uArray.gVarRing, 0);
#endif
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				else if(pType == CRX__VAR__TYPE_ERROR)
				{
					/*this->gData.uError.gString = new(::std::nothrow) ::std::string();*/
					this->gData.uError.gString = NULL;
				}
#endif
				
				if(pType != CRX__VAR__TYPE_POINTER)
					{CRX__VAR__SET_TYPE(this, pType);}
				else
				{
					this->gData.uPointer.gPointer = NULL;
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_NULL);
				}
			}
		}
		CRX_PRIVATE CRX__LIB__METHOD() void Var::template_emptyDynamicResourcesIfNecessaryForAssigment(
				unsigned char pType)
			{this->emptyDynamicResourcesIfNecessaryForAssigment(pType);}
		
		CRX_PRIVATE CRX__LIB__METHOD() void Var::unsafeMoveAssignFromVar(Var & pVar)
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__GET_TYPE2(pVar));

			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString.swap(pVar.gData.uString.uStd.gString);
#else
					if(((CRX__VAR__STRING__GET_MODE2(pVar) == CRX__VAR__STRING__MODE__LARGE_BUFFER) ||
									(CRX__VAR__STRING__GET_MODE2(pVar) == 
											CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT)) &&
							((pVar.gData.uString.uData.uLargeString.gString->gCount < 2) ||
									!CRX__VAR__GET_IS_THREAD_POSSIBLE1(this)))
					{
						switch(CRX__VAR__STRING__GET_MODE1(this))
						{
							case CRX__VAR__STRING__MODE__SMALL_BUFFER:
								{break;}
							case CRX__VAR__STRING__MODE__LARGE_BUFFER:
							case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
							{
								this->gData.uString.uData.uLargeString.gString->gCount--;

								if(this->gData.uString.uData.uLargeString.gString->gCount == 0)
									{Var::String::deleteString(this->gData.uString.uData.uLargeString.gString);}

								break;
							}
						}

						CRX__VAR__STRING__SET_MODE(this, CRX__VAR__STRING__GET_MODE2(pVar));

						this->gData.uString.uData.uLargeString.gString = 
									pVar.gData.uString.uData.uLargeString.gString;

						if(CRX__VAR__STRING__GET_MODE2(pVar) == CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT)
						{
							this->gData.uString.uData.uLargeString.gSegmentLength = 
									pVar.gData.uString.uData.uLargeString.gSegmentLength;
							this->gData.uString.uData.uLargeString.gOffset = 
									pVar.gData.uString.uData.uLargeString.gOffset;
						}

						CRX__VAR__STRING__SET_MODE2(pVar, CRX__VAR__STRING__MODE__SMALL_BUFFER);
						pVar.gData.uString.uData.uSmallString.gLength = 0;
					}
					else
						{this->addStringEndFromVarIntoIndex(0, pVar);}
#endif
					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) != CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
					{
						bool tIS_THREAD_POSSIBLE = CRX__VAR__GET_IS_THREAD_POSSIBLE1(this);

						crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator tIterator = 
								pVar.gData.uHashTable.gUnorderedMap->begin();

						this->gData.uHashTable.gUnorderedMap->clear();

						while(tIterator != pVar.gData.uHashTable.gUnorderedMap->end())
						{
							Var tVar(Var::TYPE__UNDEFINED, tIS_THREAD_POSSIBLE);

							(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = tVar;
							(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = (*tIterator).second;

							tIterator++;
						}
					}
					else
					{
						::crx::ClassUnorderedMap<::std::string, Var>::t * tUnorderedMap = 
								this->gData.uHashTable.gUnorderedMap;

						this->gData.uHashTable.gUnorderedMap = pVar.gData.uHashTable.gUnorderedMap;
						pVar.gData.uHashTable.gUnorderedMap = tUnorderedMap;
					}
#else
					if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) != CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
					{
						CRX__VAR__KHash_empty(this->gData.uHashTable.gKHash);

						CRX__VAR__KHash_copyAddDifferenceFromKHash(this->gData.uHashTable.gKHash, 
								pVar.gData.uHashTable.gKHash, CRX__VAR__GET_IS_THREAD_POSSIBLE1(this));
					}
					else
					{
						CRX__VAR__KHash * tKHash = this->gData.uHashTable.gKHash;

						this->gData.uHashTable.gKHash = pVar.gData.uHashTable.gKHash;
						pVar.gData.uHashTable.gKHash = tKHash;
					}
#endif
					break;
				}
				case CRX__VAR__TYPE_ARRAY:
				{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) != CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
					{
						bool tIS_THREAD_POSSIBLE = CRX__VAR__GET_IS_THREAD_POSSIBLE1(this);

						this->gData.uArray.gDeque->clear();

						for(size_t tI = 0; tI < pVar.gData.uArray.gDeque->size(); tI++)
						{
							Var tVar(Var::TYPE__UNDEFINED, tIS_THREAD_POSSIBLE);

							this->gData.uArray.gDeque->push_back(tVar);
							(*(this->gData.uArray.gDeque))[tI] = (*(pVar.gData.uArray.gDeque))[tI];
						}
					}
					else
					{
						::std::deque<Var> * tDeque = this->gData.uArray.gDeque;

						this->gData.uArray.gDeque = pVar.gData.uArray.gDeque;
						pVar.gData.uArray.gDeque = tDeque;
					}
#else
					if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) != CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
					{
						bool tIS_THREAD_POSSIBLE = CRX__VAR__GET_IS_THREAD_POSSIBLE1(this);

						crx_varRing_empty(CRX__VAR__GET_VARRING(this));
						CRX__VAR__GUARD(crx_varRing_ensureCapacity(CRX__VAR__GET_VARRING(this), 
								crx_varRing_getLength(CRX__VAR__GET_VARRING2(pVar))));

						for(size_t tI = 0; tI < crx_varRing_getLength(CRX__VAR__GET_VARRING2(pVar)); tI++)
						{
							Var tVar(Var::TYPE__UNDEFINED, tIS_THREAD_POSSIBLE);

							crx_varRing_push(CRX__VAR__GET_VARRING(this), &tVar);
							*(crx_varRing_get(CRX__VAR__GET_VARRING(this), tI)) = 
									*(crx_varRing_get(CRX__VAR__GET_VARRING2(pVar), tI));
						}
					}
					else
					{
						crx_varRing_pilferSwapContentWith(CRX__VAR__GET_VARRING(this),
								CRX__VAR__GET_VARRING2(pVar));
					}
#endif
					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					this->gData.uIntegral.uUnsignedChar = pVar.gData.uIntegral.uUnsignedChar;

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) = CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar);
					
					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					this->gData.uIntegral.uDouble = pVar.gData.uIntegral.uDouble;

					break;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					this->gData.uIntegral.uDouble = pVar.gData.uIntegral.uDouble;

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				{
					this->gData.uIntegral.uBool = pVar.gData.uIntegral.uBool;

					break;
				}
				case CRX__VAR__TYPE_POINTER:
				{
					Var_Pointer * tPointer = this->gData.uPointer.gPointer;

					this->gData.uPointer.gPointer = pVar.gData.uPointer.gPointer;
					pVar.gData.uPointer.gPointer = tPointer;
				}
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{break;}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_ERROR);
					this->pilferErrorFrom(pVar);
					
					break;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}
		}
		#pragma endregion UTILITIES //}

		#pragma region UTILITIES: STRING FUNCTIONS //{
		//WARNING: 
		//	- MAY ONLY BE CALLED IF INSTANCE CURRENTLY HOLDS A STRING
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE char * Var::getCharPointerAndInfo(
				size_t * CRX_NOT_NULL pLength, bool * CRX_NOT_NULL pIsNullTerminated)
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
				{
					(*pIsNullTerminated) = true;
					(*pLength) = this->gData.uString.uData.uSmallString.gLength;

					return this->gData.uString.uData.uSmallString.gBytes;
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
				{
					(*pIsNullTerminated) = true;
					(*pLength) = this->gData.uString.uData.uLargeString.gString->gLength;

					return this->gData.uString.uData.uLargeString.gString->gChars;
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
				{
					(*pIsNullTerminated) = false;
					(*pLength) = this->gData.uString.uData.uLargeString.gSegmentLength;

					return this->gData.uString.uData.uLargeString.gString->gChars + 
						this->gData.uString.uData.uLargeString.gOffset;
				}
				default:
					{CRX__BOOST_ASSERT(false); return NULL;}
			}
		}
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE char const * Var::getCharPointerAndInfo(
				size_t * CRX_NOT_NULL pLength, bool * CRX_NOT_NULL pIsNullTerminated) const
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
				{
					(*pIsNullTerminated) = true;
					(*pLength) = this->gData.uString.uData.uSmallString.gLength;

					return this->gData.uString.uData.uSmallString.gBytes;
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
				{
					(*pIsNullTerminated) = true;
					(*pLength) = this->gData.uString.uData.uLargeString.gString->gLength;

					return this->gData.uString.uData.uLargeString.gString->gChars;
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
				{
					(*pIsNullTerminated) = false;
					(*pLength) = this->gData.uString.uData.uLargeString.gSegmentLength;

					return this->gData.uString.uData.uLargeString.gString->gChars + 
						this->gData.uString.uData.uLargeString.gOffset;
				}
				default:
					{CRX__BOOST_ASSERT(false); return NULL;}
			}
		}
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE size_t Var::getStringSize() const
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
					{return this->gData.uString.uData.uSmallString.gLength - 1;}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
					{return this->gData.uString.uData.uLargeString.gString->gLength - 1;}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
					{return this->gData.uString.uData.uLargeString.gSegmentLength;}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
		}
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE size_t Var::getStringCapacity()
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
					{return CRX__VAR__SIZE_OF_STRING_STRING_BUFFER;}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
					{return this->gData.uString.uData.uLargeString.gString->gCapacity;}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
					{return CRX__VAR__SIZE_OF_STRING_STRING_BUFFER;}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
		}
		/*
		WARNING: pIndex MUST BE SMALLER THAN THE LENGTH OF THE INTERNAL STRING
		WARNING: pChars MUST BE NOT PART OF THE SAME INTERNAL STRING.

		THIS FUNCTION COPIES pChars INTO THE STRING STARTING AT pIndex. A NEW STRING IS MADE FROM 
		THE OLD STRING UP TO, AND EXCLUDING, pIndex, PLUS THE NEW STRING IN pChars. IF THE SIZE OF THE 
		NEW STRING IS SMALLER THAN THE ORIGINAL STRING, THEN THE EXTRA BYTES FROM THE ORIGINAL
		STRING ARE ALSO ADDED TO IT MAKING THE FINAL STRING. OTHERWISE, THE NEW STRING IS THE FINAL
		STRING.
		*/
		CRX_PRIVATE CRX__LIB__METHOD() void Var::addStringIntoIndex(size_t pIndex, 
				char const * CRX_NOT_NULL pChars, size_t pLength /*INCLUDES '\0'*/, 
				bool pIsNullTerminated)
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			size_t vNewLengthUpToNewSegmentEndWithNullChar = pIndex + pLength + (pIsNullTerminated ? 0 : 1);

			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
				{
					if(vNewLengthUpToNewSegmentEndWithNullChar <= CRX__VAR__SIZE_OF_STRING_STRING_BUFFER)
					{
						if(pIsNullTerminated)
						{
							::memcpy(this->gData.uString.uData.uSmallString.gBytes + pIndex,
									pChars,
									((vNewLengthUpToNewSegmentEndWithNullChar < this->gData.uString.uData.uSmallString.gLength) ? 
											pLength - 1 : pLength));

							if(vNewLengthUpToNewSegmentEndWithNullChar > this->gData.uString.uData.uSmallString.gLength)
								{this->gData.uString.uData.uSmallString.gLength = static_cast<unsigned char>(pIndex + pLength);}
						}
						else
						{
							::memcpy(this->gData.uString.uData.uSmallString.gBytes + pIndex,
									pChars, pLength);

							if(vNewLengthUpToNewSegmentEndWithNullChar > this->gData.uString.uData.uSmallString.gLength)
							{
								*(this->gData.uString.uData.uSmallString.gBytes + pIndex + pLength) = '\0';
								this->gData.uString.uData.uSmallString.gLength = static_cast<unsigned char>(pIndex + pLength + 1);
							}
						}
					}
					else
					{
						Var::String * tString /*= ?*/;
						size_t tNewCapacity = 32 * 2;

						CRX__VAR__STRING__CORRECT_CAPACITY(tNewCapacity, vNewLengthUpToNewSegmentEndWithNullChar);
						tString = Var::String::newString(tNewCapacity);
						
						::memcpy(tString->gChars, this->gData.uString.uData.uSmallString.gBytes, 
								pIndex);
						::memcpy(tString->gChars + pIndex, pChars, pLength);

						if(!pIsNullTerminated)
							{*(tString->gChars + pIndex + pLength) = '\0';}

						tString->gLength = vNewLengthUpToNewSegmentEndWithNullChar;

						CRX__VAR__STRING__SET_MODE(this, CRX__VAR__STRING__MODE__LARGE_BUFFER);
						this->gData.uString.uData.uLargeString.gString = tString;
					}	

					break;
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
				{
					if(vNewLengthUpToNewSegmentEndWithNullChar <= this->gData.uString.uData.uLargeString.gString->gCapacity)
					{
						if(this->gData.uString.uData.uLargeString.gString->gCount == 1)
						{
							if(pIsNullTerminated)
							{
								::memcpy(this->gData.uString.uData.uLargeString.gString->gChars + pIndex,
										pChars, ((vNewLengthUpToNewSegmentEndWithNullChar <
												this->gData.uString.uData.uLargeString.gString->gLength) ? 
												pLength - 1 : pLength));

								if(vNewLengthUpToNewSegmentEndWithNullChar > 
										this->gData.uString.uData.uLargeString.gString->gLength)
								{
									this->gData.uString.uData.uLargeString.gString->gLength = 
											vNewLengthUpToNewSegmentEndWithNullChar;
								}
							}
							else
							{
								::memcpy(this->gData.uString.uData.uLargeString.gString->gChars + pIndex,
										pChars, pLength);

								if(vNewLengthUpToNewSegmentEndWithNullChar >
												this->gData.uString.uData.uLargeString.gString->gLength)
								{
									*(this->gData.uString.uData.uLargeString.gString->gChars + pIndex +
											pLength) = '\0';
									this->gData.uString.uData.uLargeString.gString->gLength = 
											vNewLengthUpToNewSegmentEndWithNullChar;
								}
							}
						}
						else
						{
							//NOTE: CURRENTLY WE DO NOT SEE IF WE CAN SHRINK ALL THE WAY TO THE SMALL BUFFER
							Var::String * tString /*= ?*/;
							size_t tNewSize = CRX__VAR__PRIVATE__MAX(vNewLengthUpToNewSegmentEndWithNullChar,
									this->gData.uString.uData.uLargeString.gString->gLength);
							size_t tNewCapacity = 32 * 2;

							CRX__VAR__STRING__CORRECT_CAPACITY(tNewCapacity, tNewSize);
							tString = Var::String::newString(tNewCapacity);

							::memcpy(tString->gChars, 
									this->gData.uString.uData.uLargeString.gString->gChars, 
									pIndex);

							if(vNewLengthUpToNewSegmentEndWithNullChar < this->gData.uString.uData.uLargeString.gString->gLength)
							{
								if(pIsNullTerminated)
								{
									::memcpy(tString->gChars + pIndex, pChars, pLength - 1);
									::memcpy(tString->gChars + pIndex + pLength - 1, 
											this->gData.uString.uData.uLargeString.gString->gChars + 
											pIndex + pLength - 1, 
											this->gData.uString.uData.uLargeString.gString->gLength - 
											vNewLengthUpToNewSegmentEndWithNullChar + 1);
								}
								else
								{
									::memcpy(tString->gChars + pIndex, pChars, pLength);
									::memcpy(tString->gChars + pIndex + pLength, 
											this->gData.uString.uData.uLargeString.gString->gChars + 
											pIndex + pLength, 
											this->gData.uString.uData.uLargeString.gString->gLength - 
											vNewLengthUpToNewSegmentEndWithNullChar + 1);
								}

								tString->gLength = 
										this->gData.uString.uData.uLargeString.gString->gLength;
							}
							else
							{
								::memcpy(tString->gChars + pIndex, pChars, pLength);

								if(!pIsNullTerminated)
									{*(tString->gChars + pIndex + pLength) = '\0';}

								tString->gLength = vNewLengthUpToNewSegmentEndWithNullChar;
							}

							this->gData.uString.uData.uLargeString.gString->gCount--;
							this->gData.uString.uData.uLargeString.gString = tString;
						}
					}
					else
					{
						Var::String * tString /*= ?*/;
						size_t tNewCapacity = 32 * 2;

						CRX__VAR__STRING__CORRECT_CAPACITY(tNewCapacity, vNewLengthUpToNewSegmentEndWithNullChar);
						tString = Var::String::newString(tNewCapacity);

						::memcpy(tString->gChars, 
								this->gData.uString.uData.uLargeString.gString->gChars, 
								pIndex);
						::memcpy(tString->gChars + pIndex, pChars, pLength);

						if(!pIsNullTerminated)
							{*(tString->gChars + pIndex + pLength) = '\0';}

						this->gData.uString.uData.uLargeString.gString->gCount--;

						if(this->gData.uString.uData.uLargeString.gString->gCount == 0)
							{Var::String::deleteString(this->gData.uString.uData.uLargeString.gString);}

						tString->gLength = vNewLengthUpToNewSegmentEndWithNullChar;

						this->gData.uString.uData.uLargeString.gString = tString;
					}

					break;
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
				{
					size_t tNewLength = CRX__VAR__PRIVATE__MAX(vNewLengthUpToNewSegmentEndWithNullChar,
							this->gData.uString.uData.uLargeString.gSegmentLength + 1);

					if(tNewLength <= CRX__VAR__SIZE_OF_STRING_STRING_BUFFER)
					{
						Var::String * tString = this->gData.uString.uData.uLargeString.gString;
						size_t tSegmentLength = this->gData.uString.uData.uLargeString.gSegmentLength;
						size_t tOffset = this->gData.uString.uData.uLargeString.gOffset;

						CRX__VAR__STRING__SET_MODE(this, CRX__VAR__STRING__MODE__SMALL_BUFFER);
						::memcpy(this->gData.uString.uData.uSmallString.gBytes, tString->gChars + tOffset,
								pIndex);

						if(vNewLengthUpToNewSegmentEndWithNullChar <= tSegmentLength)
						{
							if(pIsNullTerminated)
							{
								::memcpy(this->gData.uString.uData.uSmallString.gBytes + pIndex, pChars, 
										pLength - 1);
								::memcpy(this->gData.uString.uData.uSmallString.gBytes + pIndex + pLength - 1,
										tString->gChars + tOffset + pIndex + pLength - 1, 
										tSegmentLength - vNewLengthUpToNewSegmentEndWithNullChar + 1);
								*(this->gData.uString.uData.uSmallString.gBytes + tSegmentLength) = '\0';
							}
							else
							{
								::memcpy(this->gData.uString.uData.uSmallString.gBytes + pIndex, pChars, 
										pLength);
								::memcpy(this->gData.uString.uData.uSmallString.gBytes + pIndex + pLength,
										tString->gChars + tOffset + pIndex + pLength, 
										tSegmentLength - vNewLengthUpToNewSegmentEndWithNullChar + 1);
								*(this->gData.uString.uData.uSmallString.gBytes + tSegmentLength) = '\0';
							}
						}
						else
						{	
							::memcpy(this->gData.uString.uData.uSmallString.gBytes + pIndex, pChars, 
									pLength);

							if(!pIsNullTerminated)
								{*(this->gData.uString.uData.uSmallString.gBytes + pIndex + pLength) = '\0';}
						}

						this->gData.uString.uData.uSmallString.gLength = static_cast<unsigned char>(tNewLength);

						tString->gCount--;

						if(tString->gCount == 0)
							{Var::String::deleteString(tString);}
					}
					else
					{
						if((this->gData.uString.uData.uLargeString.gString->gCount == 1) &&
								(tNewLength < this->gData.uString.uData.uLargeString.gString->gCapacity))
						{
							::memmove(this->gData.uString.uData.uLargeString.gString->gChars,
									this->gData.uString.uData.uLargeString.gString->gChars + 
											this->gData.uString.uData.uLargeString.gOffset,
									pIndex);

							if(vNewLengthUpToNewSegmentEndWithNullChar <= this->gData.uString.uData.uLargeString.gSegmentLength)
							{
								if(pIsNullTerminated)
								{
									::memcpy(this->gData.uString.uData.uLargeString.gString->gChars +
													pIndex, 
											pChars, pLength - 1);
									::memmove(gData.uString.uData.uLargeString.gString->gChars +
													pIndex + pLength - 1,
											gData.uString.uData.uLargeString.gString->gChars + 
													this->gData.uString.uData.uLargeString.gOffset +
													pIndex + pLength - 1,
											this->gData.uString.uData.uLargeString.gSegmentLength - 
													vNewLengthUpToNewSegmentEndWithNullChar + 1);

									*(this->gData.uString.uData.uLargeString.gString->gChars + 
										this->gData.uString.uData.uLargeString.gSegmentLength) = '\0';
								}
								else
								{
									::memcpy(this->gData.uString.uData.uLargeString.gString->gChars +
													pIndex, 
											pChars, pLength);
									::memmove(gData.uString.uData.uLargeString.gString->gChars +
													pIndex + pLength,
											gData.uString.uData.uLargeString.gString->gChars + 
													this->gData.uString.uData.uLargeString.gOffset +
													pIndex + pLength,
											this->gData.uString.uData.uLargeString.gSegmentLength - 
													vNewLengthUpToNewSegmentEndWithNullChar + 1);

									*(this->gData.uString.uData.uLargeString.gString->gChars + 
										this->gData.uString.uData.uLargeString.gSegmentLength) = '\0';
								}
							}
							else
							{
								::memcpy(this->gData.uString.uData.uLargeString.gString->gChars +
										pIndex, pChars, pLength);

								if(!pIsNullTerminated)
								{
									*(this->gData.uString.uData.uLargeString.gString->gChars +
											pIndex + pLength) = '\0';
								}
							}

							CRX__VAR__STRING__SET_MODE(this, 
									CRX__VAR__STRING__MODE__LARGE_BUFFER);
							this->gData.uString.uData.uLargeString.gString->gLength = tNewLength;
						}
						else
						{
							Var::String * tString /*= ?*/;
							size_t tNewCapacity = 32 * 2;

							CRX__VAR__STRING__CORRECT_CAPACITY(tNewCapacity, tNewLength);
							tString = Var::String::newString(tNewCapacity);

							::memcpy(tString->gChars, 
										this->gData.uString.uData.uLargeString.gString->gChars +
												this->gData.uString.uData.uLargeString.gOffset, 
										pIndex);

							if(vNewLengthUpToNewSegmentEndWithNullChar <= this->gData.uString.uData.uLargeString.gSegmentLength)
							{
								if(pIsNullTerminated)
								{
									::memcpy(tString->gChars + pIndex, pChars, pLength - 1);
									::memcpy(tString->gChars + pIndex + pLength - 1,
											gData.uString.uData.uLargeString.gString->gChars + 
													this->gData.uString.uData.uLargeString.gOffset +
													pIndex + pLength - 1,
											this->gData.uString.uData.uLargeString.gSegmentLength - 
													vNewLengthUpToNewSegmentEndWithNullChar + 1);
									*(tString->gChars + 
											this->gData.uString.uData.uLargeString.gSegmentLength) = '\0';
								}
								else
								{
									::memcpy(tString->gChars + pIndex, pChars, pLength);
									::memcpy(tString->gChars + pIndex + pLength,
											gData.uString.uData.uLargeString.gString->gChars + 
													this->gData.uString.uData.uLargeString.gOffset +
													pIndex + pLength,
											this->gData.uString.uData.uLargeString.gSegmentLength - 
													vNewLengthUpToNewSegmentEndWithNullChar + 1);
									*(tString->gChars + 
											this->gData.uString.uData.uLargeString.gSegmentLength) = '\0';
								}
							}
							else
							{
								::memcpy(tString->gChars + pIndex, pChars, pLength);

								if(!pIsNullTerminated)
									{*(tString->gChars + pIndex + pLength) = '\0';}
							}

							tString->gLength = tNewLength;

							this->gData.uString.uData.uLargeString.gString->gCount--;

							if(this->gData.uString.uData.uLargeString.gString->gCount == 0)
								{Var::String::deleteString(this->gData.uString.uData.uLargeString.gString);}

							CRX__VAR__STRING__SET_MODE(this, 
									CRX__VAR__STRING__MODE__LARGE_BUFFER);

							this->gData.uString.uData.uLargeString.gString = tString;
						}
					}

					break;
				}
			}
		}

		/*
		WARNING: pIndex MUST BE SMALLER THAN THE LENGTH OF THE INTERNAL STRING. THE FUNCTION
				AVOIDS USING THE LENGTH PROPERTIES FROM THE INTERNAL STRING ASSUMING IT UNDEFINED.
		WARNING: pChars MUST BE NOT PART OF THE SAME INTERNAL STRING.
				
		THIS FUNCTION COPIES pChars INTO THE STRING STARTING AT pIndex. THE FINAL STRING IS THE OLD
		STRING UP TO, AND EXCLUDING, pIndex, PLUS THE NEW STRING IN pChars.
		*/
		CRX_PRIVATE CRX__LIB__METHOD() void Var::addStringEndIntoIndex(size_t pIndex, 
				char const * CRX_NOT_NULL pChars, size_t pLength /*INCLUDES '\0'*/, 
				bool pIsNullTerminated)
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			size_t vNewCapacity = this->getStringCapacity();
			size_t vNewLengthUpToNewSegmentEndWithNullChar = pIndex + pLength + (pIsNullTerminated ? 0 : 1);

			if(vNewCapacity < vNewLengthUpToNewSegmentEndWithNullChar)
			{
				vNewCapacity = 32 * 2;

				CRX__VAR__STRING__CORRECT_CAPACITY(vNewCapacity, 
						vNewLengthUpToNewSegmentEndWithNullChar);
			}

			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
				{
					if(vNewLengthUpToNewSegmentEndWithNullChar <= CRX__VAR__SIZE_OF_STRING_STRING_BUFFER)
					{
						::memcpy(this->gData.uString.uData.uSmallString.gBytes + pIndex,
								pChars, pLength);

						if(!pIsNullTerminated)
							{*(this->gData.uString.uData.uSmallString.gBytes + pIndex + pLength) = '\0';}
						
						this->gData.uString.uData.uSmallString.gLength = 
								static_cast<unsigned char>(vNewLengthUpToNewSegmentEndWithNullChar);
					}
					else
					{
						Var::String * tString = Var::String::newString(vNewCapacity);

						//CRX__VAR__STRING__CORRECT_CAPACITY(vNewCapacity, vNewLengthUpToNewSegmentEndWithNullChar);
						//tString = Var::String::newString(vNewCapacity);
						
						::memcpy(tString->gChars, this->gData.uString.uData.uSmallString.gBytes, 
								pIndex);
						::memcpy(tString->gChars + pIndex, pChars, pLength);

						if(!pIsNullTerminated)
							{*(tString->gChars + pIndex + pLength) = '\0';}

						tString->gLength = vNewLengthUpToNewSegmentEndWithNullChar;

						CRX__VAR__STRING__SET_MODE(this, CRX__VAR__STRING__MODE__LARGE_BUFFER);
						this->gData.uString.uData.uLargeString.gString = tString;
					}	

					break;
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
				{
					if(vNewCapacity <= this->gData.uString.uData.uLargeString.gString->gCapacity)
					{
						if(this->gData.uString.uData.uLargeString.gString->gCount == 1)
						{
							::memcpy(this->gData.uString.uData.uLargeString.gString->gChars + pIndex,
									pChars, pLength);

							if(!pIsNullTerminated)
							{
								*(this->gData.uString.uData.uLargeString.gString->gChars + 
										pIndex + pLength) = '\0';
							}
							
							this->gData.uString.uData.uLargeString.gString->gLength = 
									vNewLengthUpToNewSegmentEndWithNullChar;
						}
						else
						{
							Var::String * tString = Var::String::newString(vNewCapacity);

							//CRX__VAR__STRING__CORRECT_CAPACITY(vNewCapacity, vNewLengthUpToNewSegmentEndWithNullChar);
							//tString = Var::String::newString(vNewCapacity);

							::memcpy(tString->gChars, 
									this->gData.uString.uData.uLargeString.gString->gChars, 
									pIndex);

							::memcpy(tString->gChars + pIndex, pChars, pLength);

							if(!pIsNullTerminated)
								{*(tString->gChars + pIndex + pLength) = '\0';}

							this->gData.uString.uData.uLargeString.gString->gCount--;
							this->gData.uString.uData.uLargeString.gString = tString;
							this->gData.uString.uData.uLargeString.gString->gLength = 
									vNewLengthUpToNewSegmentEndWithNullChar;
						}
					}
					else
					{
						Var::String * tString = Var::String::newString(vNewCapacity);

						//CRX__VAR__STRING__CORRECT_CAPACITY(vNewCapacity, vNewLengthUpToNewSegmentEndWithNullChar);
						//tString = Var::String::newString(vNewCapacity);

						::memcpy(tString->gChars, 
									this->gData.uString.uData.uLargeString.gString->gChars, 
									pIndex);
						::memcpy(tString->gChars + pIndex, pChars, pLength);

						if(!pIsNullTerminated)
								{*(tString->gChars + pIndex + pLength) = '\0';}

						this->gData.uString.uData.uLargeString.gString->gCount--;

						if(this->gData.uString.uData.uLargeString.gString->gCount == 0)
							{Var::String::deleteString(this->gData.uString.uData.uLargeString.gString);}

						this->gData.uString.uData.uLargeString.gString = tString;
						this->gData.uString.uData.uLargeString.gString->gLength = 
								vNewLengthUpToNewSegmentEndWithNullChar;
					}

					break;
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
				{
					if(vNewLengthUpToNewSegmentEndWithNullChar <= CRX__VAR__SIZE_OF_STRING_STRING_BUFFER)
					{
						Var::String * tString = this->gData.uString.uData.uLargeString.gString;
						size_t tOffset = this->gData.uString.uData.uLargeString.gOffset;

						CRX__VAR__STRING__SET_MODE(this, CRX__VAR__STRING__MODE__SMALL_BUFFER);
						::memcpy(this->gData.uString.uData.uSmallString.gBytes, tString->gChars + tOffset,
								pIndex);
						::memcpy(this->gData.uString.uData.uSmallString.gBytes + pIndex, pChars, 
								pLength);

						if(!pIsNullTerminated)
							{*(this->gData.uString.uData.uSmallString.gBytes + pIndex + pLength) = '\0';}

						this->gData.uString.uData.uSmallString.gLength = static_cast<unsigned char>(
								vNewLengthUpToNewSegmentEndWithNullChar);

						tString->gCount--;

						if(tString->gCount == 0)
							{Var::String::deleteString(tString);}
					}
					else
					{
						if((CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) || 
								(this->gData.uString.uData.uLargeString.gString->gCount == 1)) &&
								(vNewLengthUpToNewSegmentEndWithNullChar < 
										this->gData.uString.uData.uLargeString.gString->gCapacity))
						{
							::memmove(this->gData.uString.uData.uLargeString.gString->gChars,
									this->gData.uString.uData.uLargeString.gString->gChars + 
											this->gData.uString.uData.uLargeString.gOffset,
									pIndex);
							::memcpy(this->gData.uString.uData.uLargeString.gString->gChars +
									pIndex, pChars, pLength);

							CRX__VAR__STRING__SET_MODE(this, 
									CRX__VAR__STRING__MODE__LARGE_BUFFER);

							this->gData.uString.uData.uLargeString.gString->gLength = 
									vNewLengthUpToNewSegmentEndWithNullChar;
						}
						else
						{
							Var::String * tString = Var::String::newString(vNewCapacity);

							//CRX__VAR__STRING__CORRECT_CAPACITY(vNewCapacity, vNewLengthUpToNewSegmentEndWithNullChar);
							//tString = Var::String::newString(vNewCapacity);

							::memcpy(tString->gChars, 
									this->gData.uString.uData.uLargeString.gString->gChars +
											this->gData.uString.uData.uLargeString.gOffset, 
									pIndex);

							::memcpy(tString->gChars + pIndex, pChars, pLength);

							if(!pIsNullTerminated)
								{*(tString->gChars + pIndex + pLength) = '\0';}

							tString->gLength = vNewLengthUpToNewSegmentEndWithNullChar;

							this->gData.uString.uData.uLargeString.gString->gCount--;

							if(this->gData.uString.uData.uLargeString.gString->gCount == 0)
								{Var::String::deleteString(this->gData.uString.uData.uLargeString.gString);}

							CRX__VAR__STRING__SET_MODE(this, 
									CRX__VAR__STRING__MODE__LARGE_BUFFER);

							this->gData.uString.uData.uLargeString.gString = tString;
						}
					}

					break;
				}
			}
		}
		
		/*WARNING: pVar MUST BE CONTAINING A STRING*/
		CRX_PRIVATE CRX__LIB__METHOD() void Var::addStringFromVarIntoIndex(size_t pIndex, Var const & pVar)
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			bool vIsNullTerminated /*= ?*/;
			size_t vLength /*= ?*/;
			char const * vChars = pVar.getCharPointerAndInfo(&vLength, &vIsNullTerminated);

			this->addStringIntoIndex(pIndex, vChars, vLength, vIsNullTerminated);
		}

		/*WARNING: pVar MUST BE CONTAINING A STRING*/
		CRX_PRIVATE CRX__LIB__METHOD() void Var::addStringEndFromVarIntoIndex(size_t pIndex, Var const & pVar)
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			bool vIsNullTerminated;
			size_t vLength;
			char const * vChars = pVar.getCharPointerAndInfo(&vLength, &vIsNullTerminated);

			this->addStringEndIntoIndex(pIndex, vChars, vLength, vIsNullTerminated);
		}

		/*WARNING: INSTANCE MUST BE CONTAINING A STRING*/
		CRX_PRIVATE CRX__LIB__METHOD() void Var::ensureStringIsNotInLargeBufferSegmentMode()
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			if(CRX__VAR__STRING__GET_MODE1(this) != 
					CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT)
				{return;}

			if(this->gData.uString.uData.uLargeString.gSegmentLength < CRX__VAR__SIZE_OF_STRING_STRING_BUFFER)
			{
				Var::String * tString = this->gData.uString.uData.uLargeString.gString;
				size_t tSegmentLength = this->gData.uString.uData.uLargeString.gSegmentLength;
				size_t tOffset = this->gData.uString.uData.uLargeString.gOffset;

				CRX__VAR__STRING__SET_MODE(this, CRX__VAR__STRING__MODE__SMALL_BUFFER);
				
				::memcpy(this->gData.uString.uData.uSmallString.gBytes, tString->gChars + tOffset, 
						tSegmentLength);
				this->gData.uString.uData.uSmallString.gLength = static_cast<unsigned char>(tSegmentLength + 1);
				this->gData.uString.uData.uSmallString.gBytes[tSegmentLength] = '\0';
				

				tString->gCount--;

				if(tString->gCount == 0)
					{Var::String::deleteString(tString);}
			}
			else
			{
				if((CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) || 
						(this->gData.uString.uData.uLargeString.gString->gCount == 1)))
				{
					::memmove(this->gData.uString.uData.uLargeString.gString->gChars,
							this->gData.uString.uData.uLargeString.gString->gChars + 
							this->gData.uString.uData.uLargeString.gOffset,
							this->gData.uString.uData.uLargeString.gSegmentLength);
					this->gData.uString.uData.uLargeString.gString->gChars[
							this->gData.uString.uData.uLargeString.gSegmentLength] = '\0';
					this->gData.uString.uData.uLargeString.gString->gLength = 
							this->gData.uString.uData.uLargeString.gSegmentLength + 1;

					CRX__VAR__STRING__SET_MODE(this, CRX__VAR__STRING__MODE__LARGE_BUFFER);
				}
				else
				{
					size_t tCapacity = 32 * 2;
					Var::String * tString = NULL;

					CRX__VAR__STRING__CORRECT_CAPACITY(tCapacity, 
							(this->gData.uString.uData.uLargeString.gSegmentLength + 1))
					tString = Var::String::newString(tCapacity);

					CRX__VAR__STRING__SET_MODE(this, CRX__VAR__STRING__MODE__LARGE_BUFFER);
				
					::memcpy(tString->gChars, 
							this->gData.uString.uData.uLargeString.gString->gChars + 
							this->gData.uString.uData.uLargeString.gOffset, 
							this->gData.uString.uData.uLargeString.gSegmentLength);
					tString->gChars[this->gData.uString.uData.uLargeString.gSegmentLength + 1] = '\0';
					tString->gLength = this->gData.uString.uData.uLargeString.gSegmentLength + 1;

					this->gData.uString.uData.uLargeString.gString->gCount--;

					if(this->gData.uString.uData.uLargeString.gString->gCount == 0)
					{//REDUNDANT. SHOULD NOT HAPPEN, BUT KEEPING FOR NOW
						Var::String::deleteString(
								this->gData.uString.uData.uLargeString.gString);
					}

					this->gData.uString.uData.uLargeString.gString = tString;
				}
			}
		}

		/*WARNING: INSTANCE MUST BE CONTAINING A STRING*/
		CRX_PRIVATE CRX__LIB__METHOD() void Var::ensureStringIsOwned()
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
				{
					if(this->gData.uString.uData.uLargeString.gString->gCount > 1)
					{
						Var::String * tString = 
								Var::String::newString(this->gData.uString.uData.uLargeString.gString->gCapacity);
					
						::memcpy(tString->gChars, this->gData.uString.uData.uLargeString.gString->gChars,
								this->gData.uString.uData.uLargeString.gString->gLength);

						tString->gLength = this->gData.uString.uData.uLargeString.gString->gLength;

						this->gData.uString.uData.uLargeString.gString->gCount--;
						this->gData.uString.uData.uLargeString.gString = tString;
					}

					break;
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
				{
					this->ensureStringIsNotInLargeBufferSegmentMode();

					break;
				}
			}
		}

		CRX_PRIVATE CRX__LIB__METHOD() size_t Var::removeCharactersAt(size_t pIndex, size_t pWidth)
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			if(pWidth == 0)
				{return 0;}
			
			size_t vReturn = 0;
			
			this->ensureStringIsOwned();

			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
				{
					if(pIndex < static_cast<size_t>(this->gData.uString.uData.uSmallString.gLength - 1))
					{
						if((pIndex + pWidth) >= static_cast<size_t>(this->gData.uString.uData.uSmallString.gLength - 1))
						{
							vReturn = this->gData.uString.uData.uSmallString.gLength - 1 - pIndex;

							this->gData.uString.uData.uSmallString.gLength = static_cast<unsigned char>(pIndex + 1);
							this->gData.uString.uData.uSmallString.gBytes[pIndex + 1] = '\0';
						}
						else
						{
							vReturn = pWidth;

							::memmove(this->gData.uString.uData.uSmallString.gBytes + pIndex,
									this->gData.uString.uData.uSmallString.gBytes + pIndex + pWidth,
									this->gData.uString.uData.uSmallString.gLength - pIndex - pWidth);

							this->gData.uString.uData.uSmallString.gLength = 
									static_cast<unsigned char>(this->gData.uString.uData.uSmallString.gLength - pWidth);
						}
					}
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
				{
					if(pIndex < this->gData.uString.uData.uLargeString.gString->gLength - 1)
					{
						if((pIndex + pWidth) >= 
								(this->gData.uString.uData.uLargeString.gString->gLength - 1))
						{
							vReturn = this->gData.uString.uData.uLargeString.gString->gLength - 1 - pIndex;

							this->gData.uString.uData.uLargeString.gString->gLength = pIndex + 1;
							*(this->gData.uString.uData.uLargeString.gString->gChars + pIndex + 1) = '\0';
						}
						else
						{
							vReturn = pWidth;

							::memmove(this->gData.uString.uData.uLargeString.gString->gChars + pIndex,
									this->gData.uString.uData.uLargeString.gString->gChars + pIndex + 
											pWidth,
									this->gData.uString.uData.uLargeString.gString->gLength - pIndex - 
											pWidth);

							this->gData.uString.uData.uLargeString.gString->gLength = 
									this->gData.uString.uData.uLargeString.gString->gLength - pWidth;
						}
					}
				}
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return vReturn;
		}
		#pragma endregion UTILITIES: STRING FUNCTIONS //}

		#pragma region UTILITIES: STRING DEVELOPMENT //{
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE ::std::string Var::development_getStdString() const
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			return this->gData.uString.uStd.gString;
#else
			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
				{
					return ::std::string(this->gData.uString.uData.uSmallString.gBytes,
							this->gData.uString.uData.uSmallString.gLength - 1);
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
				{
					return ::std::string(this->gData.uString.uData.uLargeString.gString->gChars,
							this->gData.uString.uData.uLargeString.gString->gLength - 1);
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
				{
					return ::std::string(this->gData.uString.uData.uLargeString.gString->gChars +
							this->gData.uString.uData.uLargeString.gOffset, 
							this->gData.uString.uData.uLargeString.gSegmentLength);
				}
				default:
					{CRX__BOOST_ASSERT(false); return ::std::string();}
			}
#endif
		}
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE bool Var::development_isInternalNumberStringAnIntegerIfValid() const
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			return Var::isNumberStringAnIntegerIfValid(this->gData.uString.uStd.gString.c_str(), this->gData.uString.uStd.gString.size());
#else
			bool vIsNullTerminated /*= ?*/;
			size_t vLength /*= ?*/;
			char const * vChar = this->getCharPointerAndInfo(&vLength, &vIsNullTerminated);

			return Var::isNumberStringAnIntegerIfValid(vChar, vLength);
#endif	
		}
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE double Var::development_looseConvertInternalStringToDouble() const
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			int _f;

			return Var::StaticPrivateVars::gStringToDoubleConverter__loose->
					StringToDouble(this->gData.uString.uStd.gString.c_str(), 
					CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(this->gData.uString.uStd.gString.size()), &_f);
#else
			int _f;
			bool vIsNullTerminated;
			size_t vLength;
			char const * vChar = this->getCharPointerAndInfo(&vLength, &vIsNullTerminated);
			
			return Var::StaticPrivateVars::gStringToDoubleConverter__loose->
					StringToDouble(vChar, CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(vLength), 
					&_f);
#endif
		}
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE double Var::development_convertInternalStringToDouble(bool * pIsError) const
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			int _f;
			double vReturn = Var::StaticPrivateVars::gStringToDoubleConverter->
					StringToDouble(this->gData.uString.uStd.gString.c_str(), 
					CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(this->gData.uString.uStd.gString.size()), &_f);
#else
			int _f;
			bool vIsNullTerminated /*= ?*/;
			size_t vLength /*= ?*/;
			char const * vChar = this->getCharPointerAndInfo(&vLength, &vIsNullTerminated);
			double vReturn = Var::StaticPrivateVars::gStringToDoubleConverter->
					StringToDouble(vChar, 
					CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(vLength), &_f);
#endif
			char vChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE] /*= ?*/;
			::double_conversion::StringBuilder vStringBuilder(vChars,
					CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE) /*= ...*/;

			Var::StaticPrivateVars::gDoubleToStringConverter->ToShortest(
					this->gData.uIntegral.uDouble, &vStringBuilder);
			vStringBuilder.Finalize();

			
			if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(vReturn) &&
					(this->development_doStrcmpOnInternalStringAnd(vChars, 
					vStringBuilder.position())) == 0)
			{
				if(pIsError != NULL)
					{*pIsError = false;}
			}
			else
			{
				vReturn = NAN;
				
				if(pIsError != NULL)
					{*pIsError = true;}
			}

			return vReturn;
		}
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE bool Var::development_convertInternalStringToBool(bool * pIsError) const
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			return Var::convertStringToBool(this->gData.uString.uStd.gString.c_str(), pIsError);
#else
			bool tIsNullTerminated;
			size_t tLength;
			char const * tChar = this->getCharPointerAndInfo(&tLength, &tIsNullTerminated);

			return Var::convertStringToBool(tChar, tLength, pIsError);
#endif
		}
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE bool Var::development_looseConvertInternalStringToBool(bool * pIsError) const
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			return Var::looseConvertStringToBool(this->gData.uString.uStd.gString.c_str(), pIsError);
#else
			bool tIsNullTerminated;
			size_t tLength;
			char const * tChar = this->getCharPointerAndInfo(&tLength, &tIsNullTerminated);

			return Var::looseConvertStringToBool(tChar, tLength, pIsError);
#endif
		}
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE int Var::development_doStrcmpOnInternalStringAnd(
				char const * pChars, size_t pSize) const
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)

			return ::strncmp(this->gData.uString.uStd.gString.c_str(), pChars,
					((pSize <= this->gData.uString.uStd.gString.size()) ? pSize :
					this->gData.uString.uStd.gString.size()));
#else
			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
				{
					return ::strncmp(this->gData.uString.uData.uSmallString.gBytes, pChars,
							((pSize <= static_cast<size_t>(
							this->gData.uString.uData.uSmallString.gLength - 1)) ? pSize :
							(this->gData.uString.uData.uSmallString.gLength - 1)));
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
				{
					return ::strncmp(this->gData.uString.uData.uLargeString.gString->gChars, pChars, 
							((pSize <= (this->gData.uString.uData.uLargeString.gString->gLength - 1)) ? pSize :
							(this->gData.uString.uData.uLargeString.gString->gLength - 1)));
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
				{
					return ::strncmp(this->gData.uString.uData.uLargeString.gString->gChars + 
							this->gData.uString.uData.uLargeString.gOffset, pChars, 
							((pSize <= this->gData.uString.uData.uLargeString.gSegmentLength) ? 
							pSize : this->gData.uString.uData.uLargeString.gSegmentLength));
				}
				default:
					{CRX__BOOST_ASSERT(false); return -1;}
			}
#endif
		}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE CRX__VAR__UNIFIED_SIGNED_INT 
				Var::development_convertInternalStringToUnifiedSignedInt(bool * pIsError) const
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			return CRX__VAR__CONVERT_TO_UNIFIED_INT(this->gData.uString.uStd.gString.c_str(), this->gData.uString.uStd.gString.size(),
					pIsError);
#else
			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
				{
					return CRX__VAR__CONVERT_TO_UNIFIED_INT(
							this->gData.uString.uData.uSmallString.gBytes, 
							this->gData.uString.uData.uSmallString.gLength,
							pIsError);
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
				{
					return CRX__VAR__CONVERT_TO_UNIFIED_INT(
							this->gData.uString.uData.uLargeString.gString->gChars, 
							this->gData.uString.uData.uLargeString.gString->gLength,
							pIsError);
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
				{
					return CRX__VAR__CONVERT_TO_UNIFIED_INT(
							this->gData.uString.uData.uLargeString.gString->gChars +
							this->gData.uString.uData.uLargeString.gOffset,
							this->gData.uString.uData.uLargeString.gSegmentLength, pIsError);
				}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
#endif
		}
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE CRX__VAR__UNIFIED_SIGNED_INT 
				Var::development_looseConvertInternalStringToUnifiedSignedInt(bool * pIsError) const
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			return CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT(this->gData.uString.uStd.gString.c_str(), this->gData.uString.uStd.gString.size(),
					pIsError);
	#else
			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
				{
					return CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT(
							this->gData.uString.uData.uSmallString.gBytes, 
							this->gData.uString.uData.uSmallString.gLength,
							pIsError);
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
				{
					return CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT(
							this->gData.uString.uData.uLargeString.gString->gChars, 
							this->gData.uString.uData.uLargeString.gString->gLength,
							pIsError);
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
				{
					return CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT(
							this->gData.uString.uData.uLargeString.gString->gChars +
							this->gData.uString.uData.uLargeString.gOffset,
							this->gData.uString.uData.uLargeString.gSegmentLength, pIsError);
				}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
	#endif
		}
#endif
		CRX_PRIVATE CRX__LIB__METHOD() char * Var::development_unsafeGetStringAsChars(
				bool * CRX_NOT_NULL pIsPassing) const
		{
			CRX__BOOST_ASSERT(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			size_t tLength = this->gData.uString.uStd.gString.size() + 1;
			char * vReturn = ((char *) malloc(sizeof(char) * tLength));

			*pIsPassing = true;

			if(vReturn != NULL)
				{memcpy(vReturn, this->gData.uString.uStd.gString.c_str(), tLength);}

			return vReturn;
#else
			*pIsPassing = false;

			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
					{return const_cast<char *>(this->gData.uString.uData.uSmallString.gBytes);}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
					{return const_cast<char *>(this->gData.uString.uData.uLargeString.gString->gChars);}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
				{
					char * tReturn = ((char *) malloc(sizeof(char) * 
							this->gData.uString.uData.uLargeString.gSegmentLength + 1));

					*pIsPassing = true;

					if(tReturn != NULL)
					{
						memcpy(tReturn, this->gData.uString.uData.uLargeString.gString->gChars +
								this->gData.uString.uData.uLargeString.gOffset,
								this->gData.uString.uData.uLargeString.gSegmentLength);

						*(tReturn + this->gData.uString.uData.uLargeString.gSegmentLength) = '\0';
					}

					return tReturn;
				}
				default:
					{CRX__BOOST_ASSERT(false); return NULL;}
			}
#endif
		}
		
		#pragma endregion UTILITIES: STRING DEVELOPMENT //}

		#pragma region operator = //{
//#ifndef CRX__BOOST_NO_CXX11_RVALUE_REFERENCES
		/*SEE NOTES IN THE HEADER AS TO WHY THIS WAS COMMENTED OUT*/
		/*CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(Var && pVar)
		{
			if(CRX__ARE_POINTERS_TO_SAME_OBJECT(this, &pVar, CRX__BOOST_ASSERT(false)))
				{return *this;}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			else if(this->assignPropogateErrorFrom(pVar))
				{return *this;}
	#endif
	

			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__GET_TYPE2(pVar));
			this->unsafeMoveAssignFromVar(pVar);

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(Var const & pVar)
		{
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			if(this->assignPropogateErrorFrom(pVar);)
				{return *this;}
	#endif

			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__GET_TYPE2(pVar));
			
			if(CRX__VAR__GET_TYPE2(pVar) == CRX__VAR__TYPE_STRING)
			{
	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
				this->gData.uString.uStd.gString = pVar.gData.uString.uStd.gString;
	#else
				if(!CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) &&
						!CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar) &&
						((CRX__VAR__STRING__GET_MODE2(pVar) == 
								CRX__VAR__STRING__MODE__LARGE_BUFFER) ||
						(CRX__VAR__STRING__GET_MODE2(pVar) == 
								CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT)))
				{
					switch(CRX__VAR__STRING__GET_MODE1(this))
					{
						case CRX__VAR__STRING__MODE__SMALL_BUFFER:
							{break;}
						case CRX__VAR__STRING__MODE__LARGE_BUFFER:
						case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
						{
							this->gData.uString.uData.uLargeString.gString->gCount--;

							if(this->gData.uString.uData.uLargeString.gString->gCount == 0)
							{
								Var::String::deleteString(this->gData.uString.uData.uLargeString.gString);
								//this->gData.uString.uData.uLargeString.gString = NULL;
							}

							break;
						}
					}

					CRX__VAR__STRING__SET_MODE(this, CRX__VAR__STRING__GET_MODE2(pVar));
					
					this->gData.uString.uData.uLargeString.gString = 
							pVar.gData.uString.uData.uLargeString.gString;
					
					if(CRX__VAR__STRING__GET_MODE2(pVar) ==
							CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT)
					{
						this->gData.uString.uData.uLargeString.gSegmentLength = 
								pVar.gData.uString.uData.uLargeString.gSegmentLength;
						this->gData.uString.uData.uLargeString.gOffset = 
								pVar.gData.uString.uData.uLargeString.gOffset;
					}

					this->gData.uString.uData.uLargeString.gString->gCount++;
				}
				else
					{this->addStringEndFromVarIntoIndex(0, pVar);}
	#endif
			}
			else if(CRX__VAR__GET_TYPE2(pVar) == CRX__VAR__TYPE_HASH_TABLE)
			{
	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
				if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) != CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
				{
					bool tIS_THREAD_POSSIBLE = CRX__VAR__GET_IS_THREAD_POSSIBLE1(this);

					crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator tIterator = 
							pVar.gData.uHashTable.gUnorderedMap->begin();

					this->gData.uHashTable.gUnorderedMap->clear();

					while(tIterator != pVar.gData.uHashTable.gUnorderedMap->end())
					{
						Var tVar(Var::TYPE__UNDEFINED, tIS_THREAD_POSSIBLE);

						(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = tVar;
						(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = (*tIterator).second;

						tIterator++;
					}
				}
				else
					{*(this->gData.uHashTable.gUnorderedMap) = *(pVar.gData.uHashTable.gUnorderedMap);}
	#else
				CRX__VAR__KHash_empty(this->gData.uHashTable.gKHash);
				CRX__VAR__KHash_copyAddDifferenceFromKHash(this->gData.uHashTable.gKHash, 
						pVar.gData.uHashTable.gKHash, 
						CRX__VAR__GET_IS_THREAD_POSSIBLE1(this));
	#endif
			}
			else if(CRX__VAR__GET_TYPE2(pVar) == CRX__VAR__TYPE_ARRAY)
			{
	#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) != CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
					{
						bool tIS_THREAD_POSSIBLE = CRX__VAR__GET_IS_THREAD_POSSIBLE1(this);

						this->gData.uArray.gDeque->clear();

						for(size_t tI = 0; tI < pVar.gData.uArray.gDeque->size(); tI++)
						{
							Var tVar(Var::TYPE__UNDEFINED, tIS_THREAD_POSSIBLE);

							this->gData.uArray.gDeque->push_back(tVar);
							(*(this->gData.uArray.gDeque))[tI] = (*(pVar.gData.uArray.gDeque))[tI];
						}
					}
					else
						{*(this->gData.uArray.gDeque) = *(pVar.gData.uArray.gDeque);}
	#else
					if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this) || CRX__VAR__GET_IS_THREAD_POSSIBLE2(pVar))
					{
						bool tIS_THREAD_POSSIBLE = CRX__VAR__GET_IS_THREAD_POSSIBLE1(this);

						crx_varRing_empty(CRX__VAR__GET_VARRING(this));
						CRX__VAR__GUARD(crx_varRing_ensureCapacity(CRX__VAR__GET_VARRING(this), 
								crx_varRing_getLength(CRX__VAR__GET_VARRING2(pVar))));

						for(size_t tI = 0; tI < crx_varRing_getLength(CRX__VAR__GET_VARRING2(pVar)); tI++)
						{
							Var tVar(Var::TYPE__UNDEFINED, tIS_THREAD_POSSIBLE);

							crx_varRing_push(CRX__VAR__GET_VARRING(this), &tVar);
							*(crx_varRing_get(CRX__VAR__GET_VARRING(this), tI)) = 
									*(crx_varRing_get(CRX__VAR__GET_VARRING2(pVar), tI));
						}
					}
					else
					{
						crx_varRing_empty(CRX__VAR__GET_VARRING(this));

						CRX__VAR__GUARD(crx_varRing_insertElementsAt(CRX__VAR__GET_VARRING(this), 
								0, CRX__VAR__GET_VARRING2(pVar), 0, 
								crx_varRing_getLength(CRX__VAR__GET_VARRING2(pVar))));
					}
	#endif
			}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
			else if(CRX__VAR__GET_TYPE2(pVar) == CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32)
				{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) = CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar);}
	#else
			else if(CRX__VAR__GET_TYPE2(pVar) == CRX__VAR__TYPE_EMULATED_INT)
				{this->gData.uIntegral.uDouble = pVar.gData.uIntegral.uDouble;}
	#endif
			else if(CRX__VAR__GET_TYPE2(pVar) == CRX__VAR__TYPE_DOUBLE)
				{this->gData.uIntegral.uDouble = pVar.gData.uIntegral.uDouble;}
			else if(CRX__VAR__GET_TYPE2(pVar) == CRX__VAR__TYPE_BOOL)
				{this->gData.uIntegral.uBool = pVar.gData.uIntegral.uBool;}
			else
				{CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_NULL);}

			return *this;
		}*/
//#else
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(Var pVar)
		{
			/*if(CRX__ARE_POINTERS_TO_SAME_OBJECT(this, &pVar, CRX__BOOST_ASSERT(false)))
				{return *this;}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			else if(this->assignPropogateErrorFrom(pVar))
				{return *this;}
	#endif*/

			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__GET_TYPE2(pVar));
			/*NOTE: THE FOLLOWING ASSUMES THAT THE COMPILER DOES RETURN VALUE OPTIMIZATION*/
			this->unsafeMoveAssignFromVar(pVar);

			return *this;
		}
//#endif
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		//IF NO MOVE SEMANTICS:	Var & Var::operator=(::std::string pString)
		//IF MOVE SEMANTICS:	Var & Var::operator=(::std::string && pString)
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(CRX__VAR__TYPE_FOR_MOVE(::std::string) pString)
		{
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_STRING);
			this->gData.uString.uStd.gString.swap(pString);

			return *this;
		}
#endif
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || !CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(::std::string const & pString)
		{
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_STRING);
	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			this->gData.uString.uStd.gString = pString;
	#else
			this->addStringEndIntoIndex(0, pString.c_str(), pString.size() + 1, true);
	#endif

			return *this;
		}
#endif
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		//IF NO MOVE SEMANTICS:	Var & Var::operator=(::crx::ClassUnorderedMap<::std::string, Var>::t pUnorderedMap)
		//IF MOVE SEMANTICS:	Var & Var::operator=(::crx::ClassUnorderedMap<::std::string, Var>::t && pUnorderedMap)
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(CRX__VAR__TYPE_FOR_MOVE(Var::VarUnorderedMap) pUnorderedMap)
		{
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_HASH_TABLE);

			if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this))
			{
				crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator tIterator = 
						pUnorderedMap.begin();
				bool tIsMoveSafe = true;

				while(tIterator != pUnorderedMap.end())
				{
					if(!CRX__VAR__GET_IS_THREAD_POSSIBLE2((*tIterator).second))
					{
						tIsMoveSafe = false;
						break;
					}

					tIterator++;
				}

				if(tIsMoveSafe)
					{this->gData.uHashTable.gUnorderedMap->swap(pUnorderedMap);}
				else
				{
					this->gData.uHashTable.gUnorderedMap->clear();

					tIterator = pUnorderedMap.begin();

					while(tIterator != pUnorderedMap.end())
					{
						Var tVar(Var::TYPE__UNDEFINED, true);

						(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = tVar;
						(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = (*tIterator).second;

						tIterator++;
					}
				}
			}
			else
				{this->gData.uHashTable.gUnorderedMap->swap(pUnorderedMap);}

			return *this;
		}
#endif
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap)
		{
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_HASH_TABLE);
	
	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this))
			{
				crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator tIterator = 
						pUnorderedMap.begin();
						
				this->gData.uHashTable.gUnorderedMap->clear();

				while(tIterator != pUnorderedMap.end())
				{
					Var tVar(Var::TYPE__UNDEFINED, true);

					(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = tVar;
					(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = (*tIterator).second;

					tIterator++;
				}
			}
			else
				{*(this->gData.uHashTable.gUnorderedMap) = pUnorderedMap;}
	#else
			CRX__VAR__KHash_empty(this->gData.uHashTable.gKHash);
			CRX__VAR__KHash_copyFromVarHashTable2(this->gData.uHashTable.gKHash, 
					pUnorderedMap, CRX__VAR__GET_IS_THREAD_POSSIBLE1(this));
	#endif

			return *this;
		}
#endif
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		//IF NO MOVE SEMANTICS:	Var & Var::operator=(::std::deque<Var> pDeque)
		//IF MOVE SEMANTICS:	Var & Var::operator=(::std::deque<Var> && pDeque)
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(CRX__VAR__TYPE_FOR_MOVE(::std::deque<Var>) pDeque)
		{
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_ARRAY);

			if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this))
			{
				bool tIsMoveSafe = true;

				for(size_t tI = 0; tI < pDeque.size(); tI++)
				{
					if(!CRX__VAR__GET_IS_THREAD_POSSIBLE2(pDeque[tI]))
					{
						tIsMoveSafe = false;
						break;
					}
				}

				if(tIsMoveSafe)
					{this->gData.uArray.gDeque->swap(pDeque);}
				else
				{
					this->gData.uArray.gDeque->clear();

					for(size_t tI = 0; tI < pDeque.size(); tI++)
					{
						Var tVar(Var::TYPE__UNDEFINED, true);

						this->gData.uArray.gDeque->push_back(tVar);
						(*(this->gData.uArray.gDeque))[tI] = pDeque[tI];
					}
				}
			}
			else
				{this->gData.uArray.gDeque->swap(pDeque);}

			return *this;
		}
#endif
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(::std::deque<Var> const & pDeque)
		{
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_ARRAY);

	#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
			if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this))
			{
				this->gData.uArray.gDeque->clear();

				for(size_t tI = 0; tI < pDeque.size(); tI++)
				{
					Var tVar(Var::TYPE__UNDEFINED, true);

					this->gData.uArray.gDeque->push_back(tVar);
					(*(this->gData.uArray.gDeque))[tI] = pDeque[tI];
				}
			}
			else
				{*(this->gData.uArray.gDeque) = pDeque;}
	#else
			crx_varRing_empty(CRX__VAR__GET_VARRING(this));
			CRX__VAR__GUARD(crx_varRing_ensureCapacity(CRX__VAR__GET_VARRING(this), pDeque.size()));

			if(CRX__VAR__GET_IS_THREAD_POSSIBLE1(this))
			{
				for(size_t tI = 0; tI < pDeque.size(); tI++)
				{
					Var tVar(Var::TYPE__UNDEFINED, true);

					crx_varRing_push(CRX__VAR__GET_VARRING(this), &tVar);
					*(crx_varRing_get(CRX__VAR__GET_VARRING(this), tI)) = pDeque[tI];
				}
			}
			else
			{
				for(size_t tI = 0; tI < pDeque.size(); tI++)
					{crx_varRing_push(CRX__VAR__GET_VARRING(this), &(pDeque[tI]));}
			}
	#endif

			return *this;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(char const * pString)
		{
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_STRING);
	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			this->gData.uString.uStd.gString = pString;
	#else
			this->addStringEndIntoIndex(0, pString, ::strlen(pString) + 1, true);
	#endif

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(unsigned char const & pUnsignedChar)
		{
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_UNSIGNED_CHAR);

			this->gData.uIntegral.uUnsignedChar = pUnsignedChar;

			return *this;
		}
#if((!CRX__VAR__IS_EMULATED_INT_USED && CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64) || CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(uint32_t const pUnsignedInt32)
		{
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_SIGNED_INT64);
			this->gData.uIntegral.uSignedInt64 = static_cast<int64_t>(pUnsignedInt32);
	#else
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_EMULATED_INT);
			this->gData.uIntegral.uDouble = static_cast<double>(pUnsignedInt32);
	#endif

			return *this;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(int32_t const & pSignedInt)
		{
#if(!CRX__VAR__IS_EMULATED_INT_USED)
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32);
			CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) = static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt);
#else
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_EMULATED_INT);
			this->gData.uIntegral.uDouble = static_cast<double>(pSignedInt);
#endif

			return *this;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var & Var::operator=(uint64_t pUnsignedInt64))
	#if(CRX__VAR__IS_EMULATED_INT_USED || CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(int64_t const pSignedInt64)
		{
		#if(!CRX__VAR__IS_EMULATED_INT_USED)
			#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_SIGNED_INT64);
			this->gData.uIntegral.uSignedInt64 = static_cast<int64_t>(pSignedInt64);
			#else
			/*if((pSignedInt64 > INT32_MAX) || (pSignedInt64 < INT32_MIN))
			{
				this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_DOUBLE);
				this->gData.uIntegral.uDouble = static_cast<double>(pSignedInt64);
			}
			else
			{
				this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_SIGNED_INT32);
				this->gData.uIntegral.uSignedInt32 = static_cast<int32_t>(pSignedInt64);
			}*/
			#endif
		#else
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_EMULATED_INT);

			if((pSignedInt64 > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) || 
					(pSignedInt64 < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
				{this->gData.uIntegral.uDouble = NAN;}
			else
				{this->gData.uIntegral.uDouble = static_cast<double>(pSignedInt64);}
		#endif

			return *this;
		}
	#else
		CRX_DISABLED_METHOD(Var & Var::operator=(int64_t pSignedInt64))
	#endif
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(float const & pFloat)
		{
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_DOUBLE);
			this->gData.uIntegral.uDouble = static_cast<double>(pFloat);

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(double const & pDouble)
		{
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_DOUBLE);
			this->gData.uIntegral.uDouble = pDouble;

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator=(bool const & pBool)
		{
			this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_BOOL);
			this->gData.uIntegral.uBool = pBool;

			return *this;
		}
		#pragma endregion operator = //}

		#pragma region LOOSE MORPH //{
			#pragma region Loose Morph //{
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::looseMorphToString()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
					{return true;}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR] /*= ?*/;

					Var::stringifyInt32(this->gData.uIntegral.uUnsignedChar, tChars, 
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR);

					this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_STRING);
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString = tChars;
#else
					this->addStringEndIntoIndex(0, tChars, ::strlen(tChars) + 1, true);
#endif

					return true;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT] /*= ?*/;

					CRX__VAR__STRINGIFY_UNIFIED_INT(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this), 
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT);

					this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_STRING);

	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString = tChars;
	#else
					this->addStringEndIntoIndex(0, tChars, ::strlen(tChars) + 1, true);
	#endif

					return true;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT] /*= ?*/;

					Var::stringifyEmulatedInt(this->gData.uIntegral.uDouble,
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT);

					this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_STRING);

	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString = tChars;
	#else
					this->addStringEndIntoIndex(0, tChars, ::strlen(tChars) + 1, true);
	#endif

					return true;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE] /*= ?*/;
					size_t tLength /* = ?*/;
					::double_conversion::StringBuilder tStringBuilder(tChars, 
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE) /*= ...*/;

					Var::StaticPrivateVars::gDoubleToStringConverter->ToShortest(
							this->gData.uIntegral.uDouble, &tStringBuilder);
					tLength = tStringBuilder.position() + 1;
					tStringBuilder.Finalize();
					
					this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_STRING);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString = tChars;
#else
					this->addStringEndIntoIndex(0, tChars, tLength, true);
#endif

					return true;
				}
				case CRX__VAR__TYPE_BOOL:
				{
					bool tBool = this->gData.uIntegral.uBool;

					this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_STRING);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString = (tBool ? "TRUE" : "FALSE");
#else
					if(tBool)
						{this->addStringEndIntoIndex(0, "TRUE", 5, true);}
					else
						{this->addStringEndIntoIndex(0, "FALSE", 6, true);}
#endif

					return true;
				}
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::looseMorphToByte()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
					{
						this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_UNSIGNED_CHAR);
					
						this->gData.uIntegral.uUnsignedChar = static_cast<unsigned char>(tResult);

						return true;
					}
					else
						{return false;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return true;}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= UINT8_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						unsigned char tValue = 
								static_cast<unsigned char>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));

						this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_UNSIGNED_CHAR);
						
						this->gData.uIntegral.uUnsignedChar = tValue;

						return true;
					}
					else
						{return false;}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((this->gData.uIntegral.uDouble <= UINT8_MAX) &&
							(this->gData.uIntegral.uDouble >= 0))
					{
						unsigned char tValue = 
								static_cast<unsigned char>(this->gData.uIntegral.uDouble);

						this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_UNSIGNED_CHAR);
						
						this->gData.uIntegral.uUnsignedChar = tValue;

						return true;
					}
					else
						{return false;}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 
							0, UINT8_MAX))
					{
						unsigned char tValue = 
								static_cast<unsigned char>(this->gData.uIntegral.uDouble);

						this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_UNSIGNED_CHAR);
						
						this->gData.uIntegral.uUnsignedChar = tValue;

						return true;
					}
					else
						{return false;}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::looseMorphToNumber()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					if(this->development_isInternalNumberStringAnIntegerIfValid())
					{
#if(!CRX__VAR__IS_EMULATED_INT_USED)
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								this->development_looseConvertInternalStringToUnifiedSignedInt(&tIsError);

						if(!tIsError)
						{
							this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32);
						
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) = tResult;

							return true;
						}
						else
							{return false;}
#else
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								(tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_EMULATED_INT);
					
							this->gData.uIntegral.uDouble = tResult;

							return true;
						}
						else
							{return false;}
#endif
					}
					else
					{
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
						{
							this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_DOUBLE);

							this->gData.uIntegral.uDouble = tResult;

							return true;
						}
						else
							{return false;}
					}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int32_t tValue = static_cast<int32_t>(this->gData.uIntegral.uUnsignedChar);

#if(!CRX__VAR__IS_EMULATED_INT_USED)
					this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32);

					CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) = tValue;
#else
					this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_EMULATED_INT);

					this->gData.uIntegral.uDouble = tValue;
#endif

					return true;
				}	
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return true;}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::looseMorphToBool()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					bool tIsError = false;
					bool tResult = this->development_looseConvertInternalStringToBool(&tIsError);

					if(!tIsError)
					{
						this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_BOOL);

						this->gData.uIntegral.uBool = tResult;

						return true;
					}
					else
						{return false;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return false;}
				case CRX__VAR__TYPE_BOOL:
					{return true;}
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
			#pragma endregion Loose Morph //}
			
			#pragma region "CAST" (LOOSE MORPH) //{

		CRX_PUBLIC CRX__LIB__METHOD() Var::operator ::std::string() const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
					{return this->development_getStdString();}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return ::std::string());}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR] /*= ?*/;

					Var::stringifyInt32(this->gData.uIntegral.uUnsignedChar, tChars, 
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR);

					return ::std::string(tChars);
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT] /*= ?*/;

					CRX__VAR__STRINGIFY_UNIFIED_INT(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT);

					return ::std::string(tChars);
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT] /*= ?*/;

					Var::stringifyEmulatedInt(this->gData.uIntegral.uDouble,
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT);

					return ::std::string(tChars);
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					/*::double_conversion::StringBuilder vStringBuilder(this->gData.uIntegral.uStringBuffer,
							CRX__VAR__SIZE_OF_TEMPORARY_STRING_BUFFER);

					Var::StaticPrivateVars::gDoubleToStringConverter->ToShortest(this->gData.uIntegral.uDouble, 
							&vStringBuilder);

					return ::std::string(vStringBuilder.Finalize());*/

					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE] /*= ?*/;
					::double_conversion::StringBuilder tStringBuilder(tChars, 
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE) /*= ...*/;

					Var::StaticPrivateVars::gDoubleToStringConverter->ToShortest(
							this->gData.uIntegral.uDouble, &tStringBuilder);

					return ::std::string(tStringBuilder.Finalize());
				}
				case CRX__VAR__TYPE_BOOL:
					{return (this->gData.uIntegral.uBool ? ::std::string("TRUE") : ::std::string("FALSE"));}
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return ::std::string());}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{CRX__VAR__GUARD(false);}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return ::std::string();}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::operator ::crx::ClassUnorderedMap<::std::string, Var>::t() const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, 
							return Var::VarUnorderedMap());
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					return *(this->gData.uHashTable.gUnorderedMap);
#else
					::crx::ClassUnorderedMap<::std::string, Var>::t tReturn /*= 
							::crx::ClassUnorderedMap<::std::string, Var>::t()*/;
					CRX__VAR__KHASH__ITERATOR vKhiter /*= ?*/;
					CRX__VAR__KHASH__ITERATOR vKhiter_end /*= ?*/;
					
					CRX__VAR__KHash_getIteratorStart(this->gData.uHashTable.gKHash, vKhiter);
					CRX__VAR__KHash_getIteratorEnd(this->gData.uHashTable.gKHash, vKhiter_end);

					while(vKhiter != vKhiter_end)
					{
						tReturn.insert(::std::make_pair(
								CRX__VAR__KHASH__GET_KEY_FROM_ITERATOR(this->gData.uHashTable.gKHash,
										vKhiter),
								*(CRX__VAR__KHASH__GET_VALUE_FROM_ITERATOR(this->gData.uHashTable.gKHash, 
										vKhiter))));

						CRX__VAR__KHASH__INCREMENT_ITERATOR(this->gData.uHashTable.gKHash, vKhiter);
					}

					return tReturn;
#endif
				}
				case CRX__VAR__TYPE_ARRAY:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, 
							return Var::VarUnorderedMap());
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{CRX__VAR__GUARD(false);}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return ::crx::ClassUnorderedMap<::std::string, Var>::t();}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::operator ::std::deque<Var>() const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return ::std::deque<Var>());}
				case CRX__VAR__TYPE_ARRAY:
				{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					return *(this->gData.uArray.gDeque);
#else
					::std::deque<Var> tReturn /*= ::std::deque<Var>()*/;

					for(size_t tI = 0; tI < crx_varRing_getLength(CRX__VAR__GET_VARRING(this)); tI++)
						{tReturn.push_back(*(crx_varRing_constantGet(CRX__VAR__GET_VARRING(this), tI)));}
					
					return tReturn;
#endif
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, 
							return ::std::deque<Var>());
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{CRX__VAR__GUARD(false);}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return ::std::deque<Var>();}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::operator unsigned char() const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{return static_cast<unsigned char>(tResult);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return this->gData.uIntegral.uUnsignedChar;}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= UINT8_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
						{return static_cast<unsigned char>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((this->gData.uIntegral.uDouble <= UINT8_MAX) &&
							(this->gData.uIntegral.uDouble >= 0))
						{return static_cast<unsigned char>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 
							0, UINT8_MAX))
						{return static_cast<unsigned char>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{CRX__VAR__GUARD(false);}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::operator signed char() const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					/*
					THE FOLLOWING CODE WORKS IN ALL CASES, WITHOUT HAVING TO CHECK IF A NUMBER
					STRING IS AN INTEGER (NOT A DOUBLE) OR NOT. THIS IS BECAUSE EVEN IF IT HAPPENS
					TO BE AN INTEGER, NO MATTER WHAT THE MODE OF INTEGER REPRESENTATION IS FOR
					THE INTERNAL TYPE, THE INTEGER INTERNAL TYPE IS LARGE ENOUGH TO HOLD INT8, WHICH
					IS WHAT WE ARE CASTING TO. THIS IS UNLIKE THE CASTING TO INT64 CASE. FOR EXAMPLE, 
					THE INTERNAL INTEGER MODE COULD BE INT32, WHICH MEANS STRINGS THAT REPRESENT 
					INTEGERS LARGERS THAN WHAT AN INT32 CAN HOLD CAN NOT BE CAST TO INT64 
					BECAUSE IT WOULD BREAK MORPHING RULES. FURTHER MORE FOR THAT EXAMPLE, A DOUBLE
					WOULD NOT BE ABLE TO HOLD ALL NUMBER STRINGS THAT ARE INTEGERS FOR AN INT64.
					*/
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, INT8_MIN, INT8_MAX))
						{return static_cast<signed char>(tResult);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(this->gData.uIntegral.uUnsignedChar <= INT8_MAX)
						{return static_cast<signed char>(this->gData.uIntegral.uUnsignedChar);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT8_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= INT8_MIN))
						{return static_cast<signed char>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((this->gData.uIntegral.uDouble <= INT8_MAX) &&
							(this->gData.uIntegral.uDouble >= INT8_MIN))
						{return static_cast<signed char>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 
							INT8_MIN, INT8_MAX))
						{return static_cast<unsigned char>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{CRX__VAR__GUARD(false);}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::operator uint16_t() const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					/*
					THE FOLLOWING CODE WORKS IN ALL CASES, WITHOUT HAVING TO CHECK IF A NUMBER
					STRING IS AN INTEGER (NOT A DOUBLE) OR NOT. THIS IS BECAUSE EVEN IF IT HAPPENS
					TO BE AN INTEGER, NO MATTER WHAT THE MODE OF INTEGER REPRESENTATION IS FOR
					THE INTERNAL TYPE, THE INTEGER INTERNAL TYPE IS LARGE ENOUGH TO HOLD UINT16, WHICH
					IS WHAT WE ARE CASTING TO. THIS IS UNLIKE THE CASTING TO INT64 CASE. FOR EXAMPLE, 
					THE INTERNAL INTEGER MODE COULD BE INT32, WHICH MEANS STRINGS THAT REPRESENT 
					INTEGERS LARGERS THAN WHAT AN INT32 CAN HOLD CAN NOT BE CAST TO INT64 
					BECAUSE IT WOULD BREAK MORPHING RULES. FURTHER MORE FOR THAT EXAMPLE, A DOUBLE
					WOULD NOT BE ABLE TO HOLD ALL NUMBER STRINGS THAT ARE INTEGERS FOR AN INT64.
					*/
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT16_MAX))
						{return static_cast<uint16_t>(tResult);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<uint16_t>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= UINT16_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
						{return static_cast<uint16_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((this->gData.uIntegral.uDouble <= UINT16_MAX) &&
							(this->gData.uIntegral.uDouble >= 0))
						{return static_cast<uint16_t>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 
							0, UINT16_MAX))
						{return static_cast<uint16_t>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{CRX__VAR__GUARD(false);}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::operator int16_t() const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					/*
					THE FOLLOWING CODE WORKS IN ALL CASES, WITHOUT HAVING TO CHECK IF A NUMBER
					STRING IS AN INTEGER (NOT A DOUBLE) OR NOT. THIS IS BECAUSE EVEN IF IT HAPPENS
					TO BE AN INTEGER, NO MATTER WHAT THE MODE OF INTEGER REPRESENTATION IS FOR
					THE INTERNAL TYPE, THE INTEGER INTERNAL TYPE IS LARGE ENOUGH TO HOLD INT16, WHICH
					IS WHAT WE ARE CASTING TO. THIS IS UNLIKE THE CASTING TO INT64 CASE. FOR EXAMPLE, 
					THE INTERNAL INTEGER MODE COULD BE INT32, WHICH MEANS STRINGS THAT REPRESENT 
					INTEGERS LARGERS THAN WHAT AN INT32 CAN HOLD CAN NOT BE CAST TO INT64 
					BECAUSE IT WOULD BREAK MORPHING RULES. FURTHER MORE FOR THAT EXAMPLE, A DOUBLE
					WOULD NOT BE ABLE TO HOLD ALL NUMBER STRINGS THAT ARE INTEGERS FOR AN INT64.
					*/
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, INT16_MIN, INT16_MAX))
						{return static_cast<int16_t>(tResult);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<int16_t>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT16_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= INT16_MIN))
						{return static_cast<int16_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((this->gData.uIntegral.uDouble <= INT16_MAX) &&
							(this->gData.uIntegral.uDouble >= INT16_MIN))
						{return static_cast<int16_t>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble,
							INT16_MIN, INT16_MAX))
						{return static_cast<int16_t>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{CRX__VAR__GUARD(false);}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::operator uint32_t() const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
/*
//THE FOLLOWING CODE IS EQUIVILANT TO THE CODE BELOW IT, BUT KEEPING THE CODE BELOW IT TO KEEP
//CODE SUMMETRY WITH THE REST OF THE CODE. SEE THE LOOSE MORPH FUNCTIONS.

					double tResult = this->development_looseConvertInternalStringToDouble();

#if(CRX__VAR__IS_EMULATED_INT_USED || CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT32_MAX))
						{return static_cast<uint32_t>(tResult);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
#else
					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(this->development_isInternalNumberStringAnIntegerIfValid())
						{
							if((tResult <= INT32_MAX) && (tResult >= 0))
								{return static_cast<uint32_t>(tResult);}
							else
								{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
						}
						else
						{
							if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT32_MAX))
								{return static_cast<uint32_t>(tResult);}
							else
								{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
						}
					}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
#endif
*/
					if(this->development_isInternalNumberStringAnIntegerIfValid())
					{
#if(!CRX__VAR__IS_EMULATED_INT_USED)
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								this->development_looseConvertInternalStringToUnifiedSignedInt(&tIsError);

						/*
							NOTE THAT IF CRX__VAR__UNIFIED_SIGNED_INT IS int32_t THE CHECK FOR
							UINT32_MAX IS REDUNDANT BECAUSE 
							development_looseConvertInternalStringToUnifiedSignedInt() WOULD TAKE
							CARE OF IT ENFORCING A CHECK THAT IS EQUIVILANT TO 
									(tResult <= INT32_MAX)
							AND INT32_MAX IS SMALLER THAN UINT32_MAX, BUT IT IS FINE.
						*/
						if(!tIsError && (tResult >= 0) && (tResult <= UINT32_MAX))
							{return static_cast<uint32_t>(tResult);}
						else
							{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
#else
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								(tResult <= UINT32_MAX) && (tResult >= 0))
							{return static_cast<uint32_t>(tResult);}
						else
							{return false;}
#endif
					}
					else
					{
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, 
								::std::min<CRX__VAR__MACHINE_UNSIGNED_INT>(
								CRX__VAR__INT_STRING_MAX, UINT32_MAX)))//HOPING COMPILER WILL OPTIMIZE THIS OUT.
							{return static_cast<uint32_t>(tResult);}
						else
							{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
					}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<uint32_t>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= UINT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
						{return static_cast<uint32_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((this->gData.uIntegral.uDouble <= UINT32_MAX) &&
							(this->gData.uIntegral.uDouble >= 0))
						{return static_cast<uint32_t>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble,
							0, ::std::min<CRX__VAR__MACHINE_UNSIGNED_INT>(
							CRX__VAR__INTERNAL_INT_MAX, UINT32_MAX)))//HOPING COMPILER WILL OPTIMIZE THIS OUT.
						{return static_cast<uint32_t>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{CRX__VAR__GUARD(false);}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::operator int32_t() const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					/*
					THE FOLLOWING CODE WORKS IN ALL CASES, WITHOUT HAVING TO CHECK IF A NUMBER
					STRING IS AN INTEGER (NOT A DOUBLE) OR NOT. THIS IS BECAUSE EVEN IF IT HAPPENS
					TO BE AN INTEGER, NO MATTER WHAT THE MODE OF INTEGER REPRESENTATION IS FOR
					THE INTERNAL TYPE, THE INTEGER INTERNAL TYPE IS LARGE ENOUGH TO HOLD INT32, WHICH
					IS WHAT WE ARE CASTING TO. THIS IS UNLIKE THE CASTING TO INT64 CASE. FOR EXAMPLE, 
					THE INTERNAL INTEGER MODE COULD BE INT32, WHICH MEANS STRINGS THAT REPRESENT 
					INTEGERS LARGERS THAN WHAT AN INT32 CAN HOLD CAN NOT BE CAST TO INT64 
					BECAUSE IT WOULD BREAK MORPHING RULES. FURTHER MORE FOR THAT EXAMPLE, A DOUBLE
					WOULD NOT BE ABLE TO HOLD ALL NUMBER STRINGS THAT ARE INTEGERS FOR AN INT64.
					*/
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, INT32_MIN, INT32_MAX))
						{return static_cast<int32_t>(tResult);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<int32_t>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= INT32_MIN))
						{return static_cast<int32_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((this->gData.uIntegral.uDouble <= INT32_MAX) &&
							(this->gData.uIntegral.uDouble >= INT32_MIN))
						{return static_cast<int32_t>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble,
							INT32_MIN, INT32_MAX))
						{return static_cast<int32_t>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{CRX__VAR__GUARD(false);}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var::operator uint64_t() const)
		CRX_PUBLIC CRX__LIB__METHOD() Var::operator int64_t() const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					if(this->development_isInternalNumberStringAnIntegerIfValid())
					{
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								development_looseConvertInternalStringToUnifiedSignedInt(&tIsError);

						if(!tIsError)
							{return static_cast<int64_t>(tResult);}
						else
							{return false;}
	#else
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								(tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{return static_cast<int64_t>(tResult);}
						else
							{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
	#endif
					}
					else
					{
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, CRX__VAR__INT_STRING_MIN,
								CRX__VAR__INT_STRING_MAX))
							{return static_cast<int64_t>(tResult);}
						else
							{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
					}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<int64_t>(this->gData.uIntegral.uUnsignedChar);}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return static_cast<int64_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return static_cast<int64_t>(this->gData.uIntegral.uDouble);}
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble,
							CRX__VAR__PRIVATE__MAX(static_cast<int64_t>(CRX__VAR__INTERNAL_INT_MIN), CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE),
							CRX__VAR__PRIVATE__MIN(static_cast<int64_t>(CRX__VAR__INTERNAL_INT_MAX), CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE)))//HOPING COMPILER WILL OPTIMIZE THIS OUT.
						{return static_cast<int64_t>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{CRX__VAR__GUARD(false);}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var::operator float() const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					/*<REMOVED>CASTS BELOW FROM DOUBLE TO FLOAT ARE LEFT TO COMPILER IMPLEMENTATION; 
							THIS HANDLES OVERFLOW CORRECTLY, BUT THERE IS A ROUNDING OF EFFECT.
							UNSURE HOWEVER IF MANUAL CHECK OF LIMITS WOULD
							YIELD DIFFERENT RESULTS.</REMOVED>*/
					if(this->development_isInternalNumberStringAnIntegerIfValid())
					{
#if(!CRX__VAR__IS_EMULATED_INT_USED)
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								this->development_looseConvertInternalStringToUnifiedSignedInt(&tIsError);

						/*
							NOTE THAT WE CAN NOT RELY ON THE INTEGER STRING RANGE CHECK DONE IN 
							development_looseConvertInternalStringToUnifiedSignedInt() BECAUSE
							WHETHER THE INTEGER MODE IS INT32 OR INT64, THE FLOAT CAN NOT HANDLE
							THE ENTIRE INTEGER RANGE TO ENSURE WPG AND THE MORPH RULES
						*/
						if(!tIsError && (tResult <= 16777214) /*2^24 - 1*/ && 
								(tResult >= -16777214))
							{return static_cast<float>(tResult);}
						else
							{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
#else
						double tResult = this->development_looseConvertInternalStringToDouble();

						/*
							NOTE THAT THE FOLLOWING RANGE CHECKS TAKES CARE OF BOTH INTEGER
							STRING BEING VALID, AND VALID RANGE OF INTEGER TO FLOAT CONVERSION
							UNDER WPG AND MORPH RULES BEING VALID. NOTE THAT 16777214 IS SMALLER THAN
							CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE
						*/
						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								(tResult <= 16777214) /*2^24 - 1*/ && 
								(tResult >= -16777214))
							{return static_cast<float>(tResult);}
						else
							{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
#endif
					}
					else
					{
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
						{
							float tFloat = static_cast<float>(tResult);
							
							if(static_cast<double>(tFloat) == tResult)
								{return tFloat;}
							else
								{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
						}
						else
							{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
					}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<float>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= 16777214 /*2^24 - 1*/) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= -16777214))
						{return static_cast<float>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((this->gData.uIntegral.uDouble <= 16777214) /*2^24 - 1*/ &&
							(this->gData.uIntegral.uDouble >= -16777214))
						{return static_cast<float>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					float tFloat = static_cast<float>(this->gData.uIntegral.uDouble);
					
					if(static_cast<double>(tFloat) == this->gData.uIntegral.uDouble)
						{return static_cast<float>(this->gData.uIntegral.uDouble);}// <DEPTECATED>LEFT TO COMPILER IMPLEMENTATION.</DEPRECATED>
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{CRX__VAR__GUARD(false);}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::operator double() const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					if(this->development_isInternalNumberStringAnIntegerIfValid())
					{
#if(!CRX__VAR__IS_EMULATED_INT_USED)
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								this->development_looseConvertInternalStringToUnifiedSignedInt(&tIsError);

						/*
							NOTE THAT WE CAN NOT RELY ON THE INTEGER STRING RANGE CHECK DONE IN 
							development_looseConvertInternalStringToUnifiedSignedInt() BECAUSE
							IF THE INTEGER MODE IS INT64, THE DOUBLE CAN NOT HANDLE
							THE ENTIRE INTEGER RANGE TO ENSURE WPG AND THE MORPH RULES
						*/
						if(!tIsError && (tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{return static_cast<double>(tResult);}
						else
							{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
#else
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								(tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{return tResult;}
						else
							{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
#endif
					}
					else
					{
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
							{return tResult;}
						else
							{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
					}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<double>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{return static_cast<double>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
	#else
					{return static_cast<double>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
	#endif
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return this->gData.uIntegral.uDouble;}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return NAN);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{CRX__VAR__GUARD(false);}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
/*#if(BOOST_VERSION >= 105500)
		/*CRX_PUBLIC CRX__LIB__METHOD() BOOST_EXPLICIT_OPERATOR_BOOL()* /
#endif*/
		/*CRX_PUBLIC CRX__LIB__METHOD() CRX__BOOST_EXPLICIT_OPERATOR_BOOL()*/
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator!() const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					bool tIsError = false;
					bool tResult = this->development_looseConvertInternalStringToBool(&tIsError);

					if(!tIsError)
						{return !tResult;}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return false);}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return false);}
				case CRX__VAR__TYPE_BOOL:
					{return !this->gData.uIntegral.uBool;}
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return false);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{CRX__VAR__GUARD(false);}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
			#pragma endregion "CAST" (LOOSE MORPH) //}

			#pragma region CastTo functions (LOOSE MORPH) //{

		CRX_PUBLIC CRX__LIB__METHOD() ::std::string Var::castToString(bool * pIsError) const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
					{return this->development_getStdString();}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{break;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR] /*= ?*/;

					Var::stringifyInt32(this->gData.uIntegral.uUnsignedChar, tChars, 
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR);

					return ::std::string(tChars);
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT] /*= ?*/;

					CRX__VAR__STRINGIFY_UNIFIED_INT(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT);

					return ::std::string(tChars);
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT] /*= ?*/;

					Var::stringifyEmulatedInt(this->gData.uIntegral.uDouble,
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT);

					return ::std::string(tChars);
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					/*::double_conversion::StringBuilder vStringBuilder(this->gData.uIntegral.uStringBuffer,
							CRX__VAR__SIZE_OF_TEMPORARY_STRING_BUFFER);

					Var::StaticPrivateVars::gDoubleToStringConverter->ToShortest(this->gData.uIntegral.uDouble, 
							&vStringBuilder);

					return ::std::string(vStringBuilder.Finalize());*/

					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE] /*= ?*/;
					::double_conversion::StringBuilder tStringBuilder(tChars, 
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE) /*= ...*/;

					Var::StaticPrivateVars::gDoubleToStringConverter->ToShortest(
							this->gData.uIntegral.uDouble, &tStringBuilder);

					return ::std::string(tStringBuilder.Finalize());
				}
				case CRX__VAR__TYPE_BOOL:
					{return (this->gData.uIntegral.uBool ? ::std::string("TRUE") : ::std::string("FALSE"));}
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{break;}
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			if(pIsError != NULL)
				{*pIsError = true;}

			return "";
		}
		CRX_PUBLIC CRX__LIB__METHOD() ::crx::ClassUnorderedMap<::std::string, Var>::t 
				Var::castToUnorderedMap(bool * pIsError) const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
					{break;}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					return *(this->gData.uHashTable.gUnorderedMap);
#else
					::crx::ClassUnorderedMap<::std::string, Var>::t tReturn /*= 
							::crx::ClassUnorderedMap<::std::string, Var>::t()*/;
					CRX__VAR__KHASH__ITERATOR vKhiter /*= ?*/;
					CRX__VAR__KHASH__ITERATOR vKhiter_end /*= ?*/;
					
					CRX__VAR__KHash_getIteratorStart(this->gData.uHashTable.gKHash, vKhiter);
					CRX__VAR__KHash_getIteratorEnd(this->gData.uHashTable.gKHash, vKhiter_end);

					while(vKhiter != vKhiter_end)
					{
						tReturn.insert(::std::make_pair(
								CRX__VAR__KHASH__GET_KEY_FROM_ITERATOR(this->gData.uHashTable.gKHash,
										vKhiter),
								*(CRX__VAR__KHASH__GET_VALUE_FROM_ITERATOR(this->gData.uHashTable.gKHash, 
										vKhiter))));

						CRX__VAR__KHASH__INCREMENT_ITERATOR(this->gData.uHashTable.gKHash, vKhiter);
					}

					return tReturn;
#endif
				}
				case CRX__VAR__TYPE_ARRAY:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{break;}
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			if(pIsError != NULL)
				{*pIsError = true;}

			return ::crx::ClassUnorderedMap<::std::string, Var>::t();
		}
		CRX_PUBLIC CRX__LIB__METHOD() ::std::deque<Var> Var::castToDeque(bool * pIsError) const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
					{break;}
				case CRX__VAR__TYPE_ARRAY:
				{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					return *(this->gData.uArray.gDeque);
#else
					::std::deque<Var> tReturn /*= ::std::deque<Var>()*/;

					for(size_t tI = 0; tI < crx_varRing_getLength(CRX__VAR__GET_VARRING(this)); tI++)
						{tReturn.push_back(*(crx_varRing_constantGet(CRX__VAR__GET_VARRING(this), tI)));}
					
					return tReturn;
#endif
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{break;}
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			if(pIsError != NULL)
				{*pIsError = true;}

			return ::std::deque<Var>();
		}
		CRX_PUBLIC CRX__LIB__METHOD() unsigned char Var::castToUnsignedChar(bool * pIsError) const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{return static_cast<unsigned char>(tResult);}
					else
						{break;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{break;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return this->gData.uIntegral.uUnsignedChar;}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= UINT8_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
						{return static_cast<unsigned char>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
					else
						{break;}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((this->gData.uIntegral.uDouble <= UINT8_MAX) &&
							(this->gData.uIntegral.uDouble >= 0))
						{return static_cast<unsigned char>(this->gData.uIntegral.uDouble);}
					else
						{break;}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 
							0, UINT8_MAX))
						{return static_cast<unsigned char>(this->gData.uIntegral.uDouble);}
					else
						{break;}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{break;}
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			if(pIsError != NULL)
				{*pIsError = true;}

			return 0;
		}
		CRX_PUBLIC CRX__LIB__METHOD() uint32_t Var::castToUnsignedInt32(bool * pIsError) const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
/*
//THE FOLLOWING CODE IS EQUIVILANT TO THE CODE BELOW IT, BUT KEEPING THE CODE BELOW IT TO KEEP
//CODE SUMMETRY WITH THE REST OF THE CODE. SEE THE LOOSE MORPH FUNCTIONS.

					double tResult = this->development_looseConvertInternalStringToDouble();

#if(CRX__VAR__IS_EMULATED_INT_USED || CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT32_MAX))
						{return static_cast<uint32_t>(tResult);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
#else
					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(this->development_isInternalNumberStringAnIntegerIfValid())
						{
							if((tResult <= INT32_MAX) && (tResult >= 0))
								{return static_cast<uint32_t>(tResult);}
							else
								{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
						}
						else
						{
							if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT32_MAX))
								{return static_cast<uint32_t>(tResult);}
							else
								{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
						}
					}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
#endif
*/
					if(this->development_isInternalNumberStringAnIntegerIfValid())
					{
#if(!CRX__VAR__IS_EMULATED_INT_USED)
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								this->development_looseConvertInternalStringToUnifiedSignedInt(&tIsError);

						/*
							NOTE THAT IF CRX__VAR__UNIFIED_SIGNED_INT IS int32_t THE CHECK FOR
							UINT32_MAX IS REDUNDANT BECAUSE 
							development_looseConvertInternalStringToUnifiedSignedInt() WOULD TAKE
							CARE OF IT ENFORCING A CHECK THAT IS EQUIVILANT TO 
									(tResult <= INT32_MAX)
							AND INT32_MAX IS SMALLER THAN UINT32_MAX, BUT IT IS FINE.
						*/
						if(!tIsError && (tResult >= 0) && (tResult <= UINT32_MAX))
							{return static_cast<uint32_t>(tResult);}
						else
							{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
#else
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								(tResult <= UINT32_MAX) && (tResult >= 0))
							{return static_cast<uint32_t>(tResult);}
						else
							{return false;}
#endif
					}
					else
					{
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, 
								::std::min<CRX__VAR__MACHINE_UNSIGNED_INT>(
								CRX__VAR__INT_STRING_MAX, UINT32_MAX)))//HOPING COMPILER WILL OPTIMIZE THIS OUT.
							{return static_cast<uint32_t>(tResult);}
						else
							{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
					}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<uint32_t>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= UINT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
						{return static_cast<uint32_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((this->gData.uIntegral.uDouble <= UINT32_MAX) &&
							(this->gData.uIntegral.uDouble >= 0))
						{return static_cast<uint32_t>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble,
							0, 
							::std::min<CRX__VAR__MACHINE_UNSIGNED_INT>(
							CRX__VAR__INTERNAL_INT_MAX, UINT32_MAX)))//HOPING COMPILER WILL OPTIMIZE THIS OUT.
						{return static_cast<uint32_t>(this->gData.uIntegral.uDouble);}
					else
						{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR_FROM_CAST2(CRX__VAR__ERROR__ILLEGAL_CAST, return 0);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{CRX__VAR__GUARD(false);}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			if(pIsError != NULL)
				{*pIsError = true;}

			return 0;
		}
		CRX_PUBLIC CRX__LIB__METHOD() int32_t Var::castToSignedInt32(bool * pIsError) const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					/*
					THE FOLLOWING CODE WORKS IN ALL CASES, WITHOUT HAVING TO CHECK IF A NUMBER
					STRING IS AN INTEGER (NOT A DOUBLE) OR NOT. THIS IS BECAUSE EVEN IF IT HAPPENS
					TO BE AN INTEGER, NO MATTER WHAT THE MODE OF INTEGER REPRESENTATION IS FOR
					THE INTERNAL TYPE, THE INTEGER INTERNAL TYPE IS LARGE ENOUGH TO HOLD INT32, WHICH
					IS WHAT WE ARE CASTING TO. THIS IS UNLIKE THE CASTING TO INT64 CASE. FOR EXAMPLE, 
					THE INTERNAL INTEGER MODE COULD BE INT32, WHICH MEANS STRINGS THAT REPRESENT 
					INTEGERS LARGERS THAN WHAT AN INT32 CAN HOLD CAN NOT BE CAST TO INT64 
					BECAUSE IT WOULD BREAK MORPHING RULES. FURTHER MORE FOR THAT EXAMPLE, A DOUBLE
					WOULD NOT BE ABLE TO HOLD ALL NUMBER STRINGS THAT ARE INTEGERS FOR AN INT64.
					*/
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, INT32_MIN, INT32_MAX))
						{return static_cast<int32_t>(tResult);}
					else
						{break;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{break;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<int32_t>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= INT32_MIN))
						{return static_cast<int32_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
					else
						{break;}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((this->gData.uIntegral.uDouble <= INT32_MAX) &&
							(this->gData.uIntegral.uDouble >= INT32_MIN))
						{return static_cast<int32_t>(this->gData.uIntegral.uDouble);}
					else
						{break;}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble,
							INT32_MIN, INT32_MAX))
						{return static_cast<int32_t>(this->gData.uIntegral.uDouble);}
					else
						{break;}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{break;}
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			if(pIsError != NULL)
				{*pIsError = true;}

			return 0;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_PUBLIC CRX__LIB__METHOD() int64_t Var::castToSignedInt64 (bool * pIsError) const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					if(this->development_isInternalNumberStringAnIntegerIfValid())
					{
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								development_looseConvertInternalStringToUnifiedSignedInt(&tIsError);

						if(!tIsError)
							{return static_cast<int64_t>(tResult);}
						else
							{return false;}
	#else
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								(tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{return static_cast<int64_t>(tResult);}
						else
							{break;}
	#endif
					}
					else
					{
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, CRX__VAR__INT_STRING_MIN,
								CRX__VAR__INT_STRING_MAX))
							{return static_cast<int64_t>(tResult);}
						else
							{break;}
					}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{break;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<int64_t>(this->gData.uIntegral.uUnsignedChar);}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return static_cast<int64_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return static_cast<int64_t>(this->gData.uIntegral.uDouble);}
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble,
							CRX__VAR__PRIVATE__MAX(static_cast<int64_t>(CRX__VAR__INTERNAL_INT_MIN), CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE),
							CRX__VAR__PRIVATE__MIN(static_cast<int64_t>(CRX__VAR__INTERNAL_INT_MAX), CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE)))//HOPING COMPILER WILL OPTIMIZE THIS OUT.
						{return static_cast<int64_t>(this->gData.uIntegral.uDouble);}
					else
						{break;}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{break;}
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			if(pIsError != NULL)
				{*pIsError = true;}

			return 0;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() double Var::castToDouble(bool * pIsError) const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					if(this->development_isInternalNumberStringAnIntegerIfValid())
					{
#if(!CRX__VAR__IS_EMULATED_INT_USED)
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								this->development_looseConvertInternalStringToUnifiedSignedInt(&tIsError);

						/*
							NOTE THAT WE CAN NOT RELY ON THE INTEGER STRING RANGE CHECK DONE IN 
							development_looseConvertInternalStringToUnifiedSignedInt() BECAUSE
							IF THE INTEGER MODE IS INT64, THE DOUBLE CAN NOT HANDLE
							THE ENTIRE INTEGER RANGE TO ENSURE WPG AND THE MORPH RULES
						*/
						if(!tIsError && (tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{return static_cast<double>(tResult);}
						else
							{break;}
#else
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								(tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{return tResult;}
						else
							{break;}
#endif
					}
					else
					{
						double tResult = this->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
							{return tResult;}
						else
							{break;}
					}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{break;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<double>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{return static_cast<double>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
					else
						{break;}
	#else
					{return static_cast<double>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
	#endif
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return this->gData.uIntegral.uDouble;}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{break;}
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			if(pIsError != NULL)
				{*pIsError = true;}

			return NAN;
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::castToBool(bool * pIsError) const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					bool tIsError = false;
					bool tResult = this->development_looseConvertInternalStringToBool(&tIsError);

					if(!tIsError)
						{return tResult;}
					else
						{break;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{break;}
				case CRX__VAR__TYPE_BOOL:
					{return this->gData.uIntegral.uBool;}
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{break;}
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			if(pIsError != NULL)
				{*pIsError = true;}

			return false;
		}
			#pragma endregion CastTo functions (LOOSE MORPH) //}
		#pragma endregion LOOSE MORPH //}

		#pragma region FORCED CONVERSIONS //{
		CRX_PUBLIC CRX__LIB__METHOD() ::std::string Var::forceGetAsStdString()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
					{return this->development_getStdString();}
				case CRX__VAR__TYPE_HASH_TABLE:
					{return ::std::string("[[HASH TABLE]]");}
				case CRX__VAR__TYPE_ARRAY:
					{return ::std::string("[[ARRAY]]");}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR] /*= ?*/;

					Var::stringifyInt32(this->gData.uIntegral.uUnsignedChar, tChars, 
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR);

					return ::std::string(tChars);
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT] /*= ?*/;

					CRX__VAR__STRINGIFY_UNIFIED_INT(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT);

					return ::std::string(tChars);
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT] /*= ?*/;

					Var::stringifyEmulatedInt(this->gData.uIntegral.uDouble,
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT);

					return ::std::string(tChars);
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					/*::double_conversion::StringBuilder vStringBuilder(this->gData.uIntegral.uStringBuffer,
							CRX__VAR__SIZE_OF_TEMPORARY_STRING_BUFFER);

					Var::StaticPrivateVars::gDoubleToStringConverter->ToShortest(this->gData.uIntegral.uDouble, 
							&vStringBuilder);

					return ::std::string(vStringBuilder.Finalize());*/

					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE] /*= ?*/;
					::double_conversion::StringBuilder tStringBuilder(tChars,
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE) /*= ...*/;

					Var::StaticPrivateVars::gDoubleToStringConverter->ToShortest(
							this->gData.uIntegral.uDouble, &tStringBuilder);

					return ::std::string(tStringBuilder.Finalize());
				}
				case CRX__VAR__TYPE_BOOL:
					{return (this->gData.uIntegral.uBool ? ::std::string("TRUE") : ::std::string("FALSE"));}
				case CRX__VAR__TYPE_POINTER:
					{return this->gData.uPointer.gPointer->getAsString();}
				case CRX__VAR__TYPE_NULL:
					{return ::std::string("[[NULL]]");}
				case CRX__VAR__TYPE_UNDEFINED:
					{return ::std::string("[[UNDEFINED]]");}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return ::std::string("[[ERROR]]");}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return ::std::string();}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() ::crx::ClassUnorderedMap<::std::string, Var>::t 
				Var::forceGetAsVarHashTable()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					::crx::ClassUnorderedMap<::std::string, Var>::t tReturn /*= 
							::crx::ClassUnorderedMap<::std::string, Var>::t()*/;

					tReturn.insert(::std::make_pair(::std::string("0"), *this));

					return tReturn;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					return *(this->gData.uHashTable.gUnorderedMap);
#else
					crx::ClassUnorderedMap<::std::string, Var>::t tReturn /*= 
							crx::ClassUnorderedMap<::std::string, Var>::t()*/;
					CRX__VAR__KHASH__ITERATOR vKhiter /*= ?*/;
					CRX__VAR__KHASH__ITERATOR vKhiter_end /*= ?*/;
					
					CRX__VAR__KHash_getIteratorStart(this->gData.uHashTable.gKHash, vKhiter);
					CRX__VAR__KHash_getIteratorEnd(this->gData.uHashTable.gKHash, vKhiter_end);

					while(vKhiter != vKhiter_end)
					{
						tReturn.insert(::std::make_pair(
								CRX__VAR__KHASH__GET_KEY_FROM_ITERATOR(this->gData.uHashTable.gKHash,
										vKhiter),
								*(CRX__VAR__KHASH__GET_VALUE_FROM_ITERATOR(this->gData.uHashTable.gKHash, 
										vKhiter))));

						CRX__VAR__KHASH__INCREMENT_ITERATOR(this->gData.uHashTable.gKHash, vKhiter);
					}

					return tReturn;
#endif
				}
				case CRX__VAR__TYPE_ARRAY:
				{
					crx::ClassUnorderedMap<::std::string, Var>::t tReturn /*= 
							crx::ClassUnorderedMap<::std::string, Var>::t()*/;

					/*
						FOR EASE OF DEVELOPMENT WE USE THE FOLLOWING LIMIT. OTHERWISE,
								WE MIGHT HAVE TO FOLLOW THE MORPHING RULES (WORK IN PROGRESS)
					*/
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					if(this->gData.uArray.gDeque->size() <= INT32_MAX)
					{
						char tChars[11];

						for(size_t tI = 0; tI < this->gData.uArray.gDeque->size(); tI++)
						{
							Var::stringifyUnsignedInt32(static_cast<uint32_t>(tI), tChars, 11);

							tReturn.insert(::std::make_pair(::std::string(tChars), 
									this->gData.uArray.gDeque[tI]));
						}
					}
					else
						{tReturn.insert(::std::make_pair(::std::string("0"), "{{VERY_LARGE_ARRAY}}"));}
#else					
					if(crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) <= INT32_MAX)
					{
						char tChars[11];

						for(size_t tI = 0; tI < crx_varRing_getLength(CRX__VAR__GET_VARRING(this)); tI++)
						{
							Var::stringifyUnsignedInt32(static_cast<uint32_t>(tI), tChars, 11);

							tReturn.insert(::std::make_pair(::std::string(tChars), *(crx_varRing_get(CRX__VAR__GET_VARRING(this), tI))));
						}
					}
					else
						{tReturn.insert(::std::make_pair(::std::string("0"), "{{VERY_LARGE_ARRAY}}"));}
#endif
					return tReturn;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
				{
					::crx::ClassUnorderedMap<::std::string, Var>::t tReturn /*= 
							::crx::ClassUnorderedMap<::std::string, Var>::t()*/;

					tReturn.insert(::std::make_pair(::std::string("0"), *this));

					return tReturn;
				}

				default:
					{CRX__BOOST_ASSERT(false); return ::crx::ClassUnorderedMap<::std::string, Var>::t();}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() ::std::deque<Var> Var::forceGetAsArray()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				{
					::std::deque<Var> tReturn /*= ::std::deque<Var>()*/;

					tReturn.push_back(*this);

					return tReturn;
				}
				case CRX__VAR__TYPE_ARRAY:
				{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					return *(this->gData.uArray.gDeque);
#else
					::std::deque<Var> tReturn /*= ::std::deque<Var>()*/;

					for(size_t tI = 0; tI < crx_varRing_getLength(CRX__VAR__GET_VARRING(this)); tI++)
						{tReturn.push_back(*(crx_varRing_get(CRX__VAR__GET_VARRING(this), tI)));}
					
					return tReturn;
#endif
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
				{
					::std::deque<Var> tReturn /*= ::std::deque<Var>()*/;

					tReturn.push_back(*this);

					return tReturn;
				}
				default:
					{CRX__BOOST_ASSERT(false); return ::std::deque<Var>();}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() unsigned char Var::forceGetAsUnsignedChar()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNan(tResult))
							{return 0;}
						else if(tResult > UINT8_MAX)
							{return UINT8_MAX;}
						else if(tResult < 0)
							{return 0;}
						else
							{return static_cast<uint8_t>(tResult);}
					}
					else
						{return 0;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return 0;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return this->gData.uIntegral.uUnsignedChar;}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) > UINT8_MAX)
						{return UINT8_MAX;}
					else if(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) < 0)
						{return 0;}
					else
						{return static_cast<uint8_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(Var::isNan(this->gData.uIntegral.uDouble))
						{return 0;}
					else if(this->gData.uIntegral.uDouble > UINT8_MAX)
						{return UINT8_MAX;}
					else if(this->gData.uIntegral.uDouble < 0)
						{return 0;}
					else
						{return static_cast<uint8_t>(this->gData.uIntegral.uDouble);}
				}
				case CRX__VAR__TYPE_BOOL:
					{return (this->gData.uIntegral.uBool ? 1 : 0);}
				case CRX__VAR__TYPE_POINTER:
					{return 1;}
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return 0;}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() signed char Var::forceGetAsSignedChar()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNan(tResult))
							{return 0;}
						else if(tResult > INT8_MAX)
							{return INT8_MAX;}
						else if(tResult < INT8_MIN)
							{return INT8_MIN;}
						else
							{return static_cast<int8_t>(tResult);}
					}
					else
						{return 0;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return 0;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(this->gData.uIntegral.uUnsignedChar > INT8_MAX)
						{return INT8_MAX;}
					else
						{return static_cast<signed char>(this->gData.uIntegral.uUnsignedChar);}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) > INT8_MAX)
						{return INT8_MAX;}
					else if(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) < INT8_MIN)
						{return INT8_MIN;}
					else
						{return static_cast<int8_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif;
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(Var::isNan(this->gData.uIntegral.uDouble))
						{return 0;}
					else if(this->gData.uIntegral.uDouble > INT8_MAX)
						{return INT8_MAX;}
					else if(this->gData.uIntegral.uDouble < INT8_MIN)
						{return INT8_MIN;}
					else
						{return static_cast<int8_t>(this->gData.uIntegral.uDouble);}
				}
				case CRX__VAR__TYPE_BOOL:
					{return (this->gData.uIntegral.uBool ? 1 : 0);}
				case CRX__VAR__TYPE_POINTER:
					{return 1;}
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return 0;}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() uint16_t Var::forceGetAsUnsignedInt16()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNan(tResult))
							{return 0;}
						else if(tResult > UINT16_MAX)
							{return UINT16_MAX;}
						else if(tResult < 0)
							{return 0;}
						else
							{return static_cast<uint16_t>(tResult);}
					}
					else
						{return 0;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return 0;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<uint16_t>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) > UINT16_MAX)
						{return UINT16_MAX;}
					else if(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) < 0)
						{return 0;}
					else
						{return static_cast<uint16_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(Var::isNan(this->gData.uIntegral.uDouble))
						{return 0;}
					else if(this->gData.uIntegral.uDouble > UINT16_MAX)
						{return UINT16_MAX;}
					else if(this->gData.uIntegral.uDouble < 0)
						{return 0;}
					else
						{return static_cast<uint16_t>(this->gData.uIntegral.uDouble);}
				}
				case CRX__VAR__TYPE_BOOL:
					{return (this->gData.uIntegral.uBool ? 1 : 0);}
				case CRX__VAR__TYPE_POINTER:
					{return 1;}
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return 0;}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() int16_t Var::forceGetAsSignedInt16()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNan(tResult))
							{return 0;}
						else if(tResult > INT16_MAX)
							{return INT16_MAX;}
						else if(tResult < INT16_MIN)
							{return INT16_MIN;}
						else
							{return static_cast<int16_t>(tResult);}
					}
					else
						{return 0;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return 0;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<int16_t>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) > INT16_MAX)
						{return INT16_MAX;}
					else if(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) < INT16_MIN)
						{return INT16_MIN;}
					else
						{return static_cast<int16_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(Var::isNan(this->gData.uIntegral.uDouble))
						{return 0;}
					else if(this->gData.uIntegral.uDouble > INT16_MAX)
						{return INT16_MAX;}
					else if(this->gData.uIntegral.uDouble < INT16_MIN)
						{return INT16_MIN;}
					else
						{return static_cast<int16_t>(this->gData.uIntegral.uDouble);}
				}
				case CRX__VAR__TYPE_BOOL:
					{return (this->gData.uIntegral.uBool ? 1 : 0);}
				case CRX__VAR__TYPE_POINTER:
					{return 1;}
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return 0;}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() uint32_t Var::forceGetAsUnsignedInt32()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNan(tResult))
							{return 0;}
						else if(tResult > UINT32_MAX)
							{return UINT32_MAX;}
						else if(tResult < 0)
							{return 0;}
						else
							{return static_cast<uint32_t>(tResult);}
					}
					else
						{return 0;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return 0;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<uint32_t>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) > UINT32_MAX)
						{return UINT32_MAX;}
					else if(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) < 0)
						{return 0;}
					else
						{return static_cast<uint32_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(Var::isNan(this->gData.uIntegral.uDouble))
						{return 0;}
					else if(this->gData.uIntegral.uDouble > UINT32_MAX)
						{return UINT32_MAX;}
					else if(this->gData.uIntegral.uDouble < 0)
						{return 0;}
					else
						{return static_cast<uint32_t>(this->gData.uIntegral.uDouble);}
				}
				case CRX__VAR__TYPE_BOOL:
					{return (this->gData.uIntegral.uBool ? 1 : 0);}
				case CRX__VAR__TYPE_POINTER:
				{
					if(sizeof(void *) <= sizeof(uint32_t))
						{return static_cast<uint32_t>(reinterpret_cast<CRX__VAR__MACHINE_UNSIGNED_INT>(this->gData.uPointer.gPointer->getPointer()));}
					else
						{return 1;}
				}
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return 0;}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() int32_t Var::forceGetAsSignedInt32()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNan(tResult))
							{return 0;}
						else if(tResult > INT32_MAX)
							{return INT32_MAX;}
						else if(tResult < INT32_MIN)
							{return INT32_MIN;}
						else
							{return static_cast<int32_t>(tResult);}
					}
					else
						{return 0;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return 0;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<int32_t>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) > INT32_MAX)
						{return INT32_MAX;}
					else if(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) < INT32_MIN)
						{return INT32_MIN;}
					else
						{return static_cast<int32_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(Var::isNan(this->gData.uIntegral.uDouble))
						{return 0;}
					else if(this->gData.uIntegral.uDouble > INT32_MAX)
						{return INT32_MAX;}
					else if(this->gData.uIntegral.uDouble < INT32_MIN)
						{return INT32_MIN;}
					else
						{return static_cast<int32_t>(this->gData.uIntegral.uDouble);}
				}
				case CRX__VAR__TYPE_BOOL:
					{return (this->gData.uIntegral.uBool ? 1 : 0);}
				case CRX__VAR__TYPE_POINTER:
					{return 1;}
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return 0;}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_PUBLIC CRX__LIB__METHOD() int64_t Var::forceGetAsSignedInt64()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					if(Var::isNumberStringAnIntegerIfValid(this->gData.uString.uStd.gString.c_str(), this->gData.uString.uStd.gString.size()))
					{
						bool tIsError = false;
						int64_t tResult = Var::looseConvertToSignedInt64(this->gData.uString.uStd.gString.c_str(), &tIsError);

						if(!tIsError)
							{return tResult;}
						else
						{
							int _f;
							double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
									StringToDouble(this->gData.uString.uStd.gString.c_str(), 
									CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(
											this->gData.uString.uStd.gString.size()), 
									&_f);

							if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
							{
								if(Var::isNan(tResult))
									{return 0;}
								if(tResult > INT64_MAX)
									{return INT64_MAX;}
								else if(tResult < INT64_MIN)
									{return INT64_MIN;}
								else
									{return static_cast<int64_t>(tResult);}
							}
							else
								{return 0;}
						}
					}
					else
					{
						int _f;
						double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
								StringToDouble(this->gData.uString.uStd.gString.c_str(), 
								CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(
										this->gData.uString.uStd.gString.size()), 
								&_f);

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
						{
							if(Var::isNan(tResult))
								{return 0;}
							if(tResult > INT64_MAX)
								{return INT64_MAX;}
							else if(tResult < INT64_MIN)
								{return INT64_MIN;}
							else
								{return static_cast<int64_t>(tResult);}
						}
						else
							{return 0;}
					}
	#else
					bool tIsNullTerminated;
					size_t tSize;
					char * tChar = this->getCharPointerAndInfo(&tSize, &tIsNullTerminated);

					if(Var::isNumberStringAnIntegerIfValid(tChar, tSize))
					{
						bool tIsError = false;
						int64_t tResult = Var::looseConvertToSignedInt64(tChar, tSize, &tIsError);

						if(!tIsError)
							{return tResult;}
						else
						{
							int _f;
							double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
									StringToDouble(tChar, 
									CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(tSize), &_f);

							if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
							{
								if(Var::isNan(tResult))
									{return 0;}
								if(tResult > INT64_MAX)
									{return INT64_MAX;}
								else if(tResult < INT64_MIN)
									{return INT64_MIN;}
								else
									{return static_cast<int64_t>(tResult);}
							}
							else
								{return 0;}
						}
					}
					else
					{
						int _f;
						double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
								StringToDouble(tChar, 
								CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(tSize), &_f);

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
						{
							if(Var::isNan(tResult))
								{return 0;}
							if(tResult > INT64_MAX)
								{return INT64_MAX;}
							else if(tResult < INT64_MIN)
								{return INT64_MIN;}
							else
								{return static_cast<int64_t>(tResult);}
						}
						else
							{return 0;}
					}
	#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return 0;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<int64_t>(this->gData.uIntegral.uUnsignedChar);}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return static_cast<int64_t>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return static_cast<int64_t>(this->gData.uIntegral.uDouble);}
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(Var::isNan(this->gData.uIntegral.uDouble))
						{return 0;}
					else if(this->gData.uIntegral.uDouble > INT64_MAX)
						{return INT64_MAX;}
					else if(this->gData.uIntegral.uDouble < INT64_MIN)
						{return INT64_MIN;}
					else
						{return static_cast<int64_t>(this->gData.uIntegral.uDouble);}
				}
				case CRX__VAR__TYPE_BOOL:
					{return (this->gData.uIntegral.uBool ? 1 : 0);}
				case CRX__VAR__TYPE_POINTER:
					{return 1;}
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return 0;}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() float Var::forceGetAsFloat()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
						{return static_cast<float>(tResult);}
					else
						{return NAN;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return NAN;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<float>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return static_cast<float>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return static_cast<float>(this->gData.uIntegral.uDouble);}/*LEFT TO COMPILER IMPLEMENTATION.*/
				case CRX__VAR__TYPE_BOOL:
					{return (this->gData.uIntegral.uBool ? 1.0f : 0.0f);}
				case CRX__VAR__TYPE_POINTER:
				{
#ifndef CRX__BOOST_NO_INT64_T
					return ((float)((int64_t)this->gData.uPointer.gPointer->getPointer()));
#else
					return 1.0f;
#endif
				}
				case CRX__VAR__TYPE_NULL:
					{return 0.0f;}
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return NAN;}
				default:
					{CRX__BOOST_ASSERT(false); return NAN;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() double Var::forceGetAsDouble()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					double tResult = this->development_looseConvertInternalStringToDouble();

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
						{return tResult;}
					else
						{return NAN;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return NAN;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return static_cast<double>(this->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return static_cast<double>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return this->gData.uIntegral.uDouble;}
				case CRX__VAR__TYPE_BOOL:
					{return (this->gData.uIntegral.uBool ? 1.0 : 0.0);}
				case CRX__VAR__TYPE_POINTER:
				{
#ifndef CRX__BOOST_NO_INT64_T
					return ((double)((int64_t)this->gData.uPointer.gPointer->getPointer()));
#else
					return 1.0;
#endif
				}
				case CRX__VAR__TYPE_NULL:
					{return 0.0;}
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return NAN;}
				default:
					{CRX__BOOST_ASSERT(false); return NAN;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::forceGetAsBool()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					bool tIsError = false;
					bool tResult = Var::looseConvertStringToBool(this->gData.uString.uStd.gString.c_str(), &tIsError);

					if(!tIsError)
						{return tResult;}
					else if(!::std::empty(this->gData.uString.uStd.gString))
						{return true;}
					else
						{return false;}
#else
					bool tIsNullTerminated;
					size_t tSize;
					char * tChar = this->getCharPointerAndInfo(&tSize, &tIsNullTerminated);
					bool tIsError = false;
					bool tResult = Var::looseConvertStringToBool(tChar, tSize, &tIsError);

					if(!tIsError)
						{return tResult;}
					else if(tSize > 0)
						{return true;}
					else
						{return false;}
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					return (this->gData.uHashTable.gUnorderedMap->size() > 0);
#else
					return (CRX__VAR__KHASH__SIZE(this->gData.uHashTable.gKHash) > 0);
#endif
				}
				case CRX__VAR__TYPE_ARRAY:
				{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					return (this->gData.uArray.gDeque->size() > 0);
#else
					return (crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) > 0);
#endif
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					/*{return static_cast<bool>(this->gData.uIntegral.uUnsignedChar);}*/
					{return (this->gData.uIntegral.uUnsignedChar != 0);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) != 0);}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					/*{return static_cast<bool>(this->gData.uIntegral.uDouble);}*/
					{return (this->gData.uIntegral.uDouble != 0);}
				case CRX__VAR__TYPE_BOOL:
					{return this->gData.uIntegral.uBool;}
				case CRX__VAR__TYPE_POINTER:
					{return true;}
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		#pragma endregion FORCED CONVERSIONS //}

		#pragma region operator += //{
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator+=(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return (*this += pVar.gData.uString.uStd.gString);
#else
					bool tIsNullTerminated;
					size_t tLength;
					char const * tChar = pVar.getCharPointerAndInfo(&tLength, &tIsNullTerminated);

					return this->doOperatorPlusEqual(tChar, (tIsNullTerminated ? (tLength - 1) : tLength));
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					return (*this += *(pVar.gData.uHashTable.gUnorderedMap));
#else
					return this->doOperatorPlusEqual(pVar.gData.uHashTable.gKHash);
#endif
				}
				case CRX__VAR__TYPE_ARRAY:
				{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					return (*this += *(pVar.gData.uArray.gDeque));
#else
					return this->doOperatorPlusEqual(CRX__VAR__GET_VARRING2(pVar));
#endif
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (*this += pVar.gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (*this += CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return this->doOperatorPlusEqualForEmulatedInt(pVar.gData.uIntegral.uDouble);}
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (*this += pVar.gData.uIntegral.uDouble);}
				case CRX__VAR__TYPE_BOOL:
					{return (*this += pVar.gData.uIntegral.uBool);}
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					this->assignPropogateErrorFrom(pVar);

					return *this;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator+=(::std::string const & pString)
			{return this->doOperatorPlusEqual(pString.c_str(), pString.size());}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator+=(char const * pString)
			{return this->doOperatorPlusEqual(pString, strlen(pString));}
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorPlusEqual(char const * pChars, size_t pSize)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString.append(pChars, pSize);
#else
					this->addStringEndIntoIndex(this->getStringSize(), pChars, pSize, false);
#endif
					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar += static_cast<unsigned char>(tResult);}//LEFT TO C++ STANDARD
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
					{
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT(pChars, pSize, &tIsError);

						if(!tIsError)
						{
							if(CRX__VAR__WILL_ADD_ON_UNIFIED_INT_OVERFLOW(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
									tResult))
							{
								CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
								this->gData.uIntegral.uDouble = NAN;
							}
							else
								{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) += tResult;}
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							int _f;
							double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
									StringToDouble(pChars, 
									CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

							if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
							{
								CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
								this->gData.uIntegral.uDouble = static_cast<double>(
										CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this)) + tResult;
							}
							else
							{
								CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							if((tResult <= CRX__VAR__INT_STRING_MAX) &&
									(tResult >= CRX__VAR__INT_STRING_MIN))
							{
								this->gData.uIntegral.uDouble += tResult;

								if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
										(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{
									CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
									this->gData.uIntegral.uDouble = NAN;
								}
							}
							else
							{
								CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
						else
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble += tResult;
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							if((tResult <= CRX__VAR__INT_STRING_MAX) &&
									(tResult >= CRX__VAR__INT_STRING_MIN) &&
									(tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
									(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{
								if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
										(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{
									this->gData.uIntegral.uDouble += tResult;

									if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
											(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
										{this->gData.uIntegral.uDouble = NAN;}
								}
								else
									{this->gData.uIntegral.uDouble = NAN;}
							}
							else
							{
								CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
						else
							{this->gData.uIntegral.uDouble += tResult;}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator+=(char const & pChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString += pChar;
#else
					this->addStringEndIntoIndex(this->getStringSize(), &pChar, 1, false);
#endif

					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					//this->gData.uIntegral.uUnsignedChar += pChar;
					if((pChar >= '0') && (pChar <= '9'))
						{this->gData.uIntegral.uUnsignedChar += (pChar - '0');}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((pChar >= '0') && (pChar <= '9'))
					{
						CRX__VAR__UNIFIED_SIGNED_INT tResult = (pChar - '0');

						if(CRX__VAR__WILL_ADD_ON_UNIFIED_INT_OVERFLOW(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
									tResult))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = NAN;
						}
						else
							{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) += tResult;}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pChar >= '0') && (pChar <= '9'))
					{
						if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
									(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							this->gData.uIntegral.uDouble += static_cast<double>(pChar - '0');

							if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE)  ||
									(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
						}
						else
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator+=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator vIterator = 
							pUnorderedMap.begin();

					while(vIterator != pUnorderedMap.end())
					{
						if(this->gData.uHashTable.gUnorderedMap->count((*vIterator).first) == 1)
							{continue;}

						this->gData.uHashTable.gUnorderedMap->insert(::std::make_pair(
								(*vIterator).first,
								Var((*vIterator).second, CRX__VAR__GET_IS_THREAD_POSSIBLE1(this))));

						vIterator++;
					}
#else
					CRX__VAR__KHash_copyFromVarHashTable2(this->gData.uHashTable.gKHash,
							pUnorderedMap, CRX__VAR__GET_IS_THREAD_POSSIBLE1(this));
#endif
					break;
				}
				case CRX__VAR__TYPE_ARRAY:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#if(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorPlusEqual(CRX__VAR__KHash const * pKHash)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
					CRX__VAR__KHash_copyAddDifferenceFromKHash(this->gData.uHashTable.gKHash,
							pKHash, CRX__VAR__GET_IS_THREAD_POSSIBLE1(this));

					break;
				}
				case CRX__VAR__TYPE_ARRAY:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator+=(::std::deque<Var> & pDeque)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_ARRAY:
				{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					this->gData.uArray.gDeque->insert(this->gData.uArray.gDeque->end(), pDeque.begin(), pDeque.end());
#else
					if(crx_varRing_ensureCapacity(CRX__VAR__GET_VARRING(this),
							crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) + pDeque.size()))
					{
						for(size_t tI = 0; tI < pDeque.size(); tI++)
							{crx_varRing_fastPush(CRX__VAR__GET_VARRING(this), &(pDeque[tI]));}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__OUT_OF_MEMORY, 
								CRX__VAR__GUARD(false));
					}
#endif
					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#if(CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorPlusEqual(Crx_VarRing const * pVarRing)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_ARRAY:
				{
					if(!crx_varRing_insertElementsAt(CRX__VAR__GET_VARRING(this),
							crx_varRing_getLength(CRX__VAR__GET_VARRING(this)),
							pVarRing, 0, crx_varRing_getLength(pVarRing)))
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__OUT_OF_MEMORY, 
								CRX__VAR__GUARD(false));
					}
					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator+=(unsigned char const & pUnsignedChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR] /*= ?*/;

					Var::stringifyUnsignedInt32(pUnsignedChar,
							tChars,
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR);

					this->gData.uString.uStd.gString += tChars;
#else
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR] /*= ?*/;

					this->addStringEndIntoIndex(this->getStringSize(), 
							tChars, 
							Var::stringifyUnsignedInt32AndGetSize(pUnsignedChar,
									tChars, 
									CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR) + 1, 
							true);
#endif
					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					this->gData.uIntegral.uUnsignedChar += pUnsignedChar;

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(CRX__VAR__WILL_ADD_ON_UNIFIED_INT_OVERFLOW(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
								static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedChar)))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = NAN;
					}
					else
						{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) += static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedChar);}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						this->gData.uIntegral.uDouble += static_cast<double>(pUnsignedChar);

						if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
								(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator+=(uint32_t const & pUnsignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					if(pUnsignedInt32 <= CRX__VAR__INTERNAL_INT_MAX)
					{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
						char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_INT32];

						Var::stringifyUnsignedInt32(pUnsignedInt32, tChars,
								CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_INT32);

						this->gData.uString.uStd.gString += tChars;
#else
						char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_INT32];

						this->addStringEndIntoIndex(this->getStringSize(), tChars, 
								Var::stringifyUnsignedInt32AndGetSize(pUnsignedInt32, tChars, 
										CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_INT32) + 1, 
								true);
#endif
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(pUnsignedInt32 <= UINT8_MAX)
						{this->gData.uIntegral.uUnsignedChar += static_cast<unsigned char>(pUnsignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					int64_t tResult = static_cast<int64_t>(pUnsignedInt32);

					if(CRX__VAR__WILL_ADD_ON_INT64_OVERFLOW(this->gData.uIntegral.uSignedInt64,
							tResult))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = NAN;
					}
					else
						{this->gData.uIntegral.uSignedInt64 += tResult;}
	#else
					if((pUnsignedInt32 <= INT32_MAX) && (pUnsignedInt32 >= INT32_MIN))
					{
						int32_t tResult = static_cast<int32_t>(pUnsignedInt32);

						if(CRX__VAR__WILL_ADD_ON_INT32_OVERFLOW(this->gData.uIntegral.uSignedInt32,
								tResult))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = NAN;
						}
						else
							{this->gData.uIntegral.uSignedInt32 += tResult;}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
	#endif
					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pUnsignedInt32 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pUnsignedInt32 >= CRX__VAR__INTERNAL_INT_MIN))
					{
						if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							this->gData.uIntegral.uDouble += pUnsignedInt32;

							if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
									(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
						}
						else
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator+=(int32_t const & pSignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT32];

					Var::stringifyInt32(pSignedInt32, tChars,
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT32);

					this->gData.uString.uStd.gString += tChars;
#else
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT32];

					this->addStringEndIntoIndex(this->getStringSize(), tChars, 
							Var::stringifyInt32AndGetSize(pSignedInt32, tChars, 
									CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT32) + 1,
							true);
#endif
					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt32 <= UINT8_MAX) && (pSignedInt32 >= 0) /*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar += static_cast<unsigned char>(pSignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					CRX__VAR__UNIFIED_SIGNED_INT tResult = static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt32);

					if(CRX__VAR__WILL_ADD_ON_UNIFIED_INT_OVERFLOW(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
							tResult))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = NAN;
					}
					else
						{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) += tResult;}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						this->gData.uIntegral.uDouble += pSignedInt32;

						if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
								(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var & Var::operator+=(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator+=(int64_t const & pSignedInt64)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) &&
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN))
					{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
						char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT64];

						Var::stringifyInt64(pSignedInt64, tChars, 
								CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT64);

						this->gData.uString.uStd.gString += tChars;
#else
						char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT64];

						this->addStringEndIntoIndex(this->getStringSize(), tChars, 
								Var::stringifyInt64AndGetSize(pSignedInt64, tChars, 
										CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT64) + 1, 
								true);
#endif
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt64 <= UINT8_MAX) && (pSignedInt64 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar += static_cast<unsigned char>(pSignedInt64);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
		#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					int64_t tResult = pSignedInt64;

					if(CRX__VAR__WILL_ADD_ON_INT64_OVERFLOW(this->gData.uIntegral.uSignedInt64,
							tResult))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = NAN;
					}
					else
						{this->gData.uIntegral.uSignedInt64 += tResult;}
		#else
					if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= INT32_MIN))
					{
						int32_t tResult = static_cast<int32_t>(pSignedInt64);

						if(CRX__VAR__WILL_ADD_ON_INT32_OVERFLOW(this->gData.uIntegral.uSignedInt32,
								tResult))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = NAN;
						}
						else
							{this->gData.uIntegral.uSignedInt32 += tResult;}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
		#endif
					break;
				}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN))
					{
						this->gData.uIntegral.uDouble += pSignedInt64;

						if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
								(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = NAN;
						}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN) &&
							(pSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(pSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							this->gData.uIntegral.uDouble += pSignedInt64;

							if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
									(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{this->gData.uIntegral.uDouble = NAN;}
						}
						else
							{this->gData.uIntegral.uDouble = NAN;}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif
#if(CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorPlusEqualForEmulatedInt(double const & pDouble)
		{
			CRX__BOOST_ASSERT((pDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
					(pDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE));

			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT];

					Var::stringifyEmulatedInt(pDouble, tChars, 
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT);

					this->gData.uString.uStd.gString += tChars;
#else
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT];

					this->addStringEndIntoIndex(this->getStringSize(), tChars, 
							Var::stringifyEmulatedIntAndGetSize(pDouble, tChars, 
									CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT) + 1,
							true);
#endif
					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar += static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_EMULATED_INT:
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						this->gData.uIntegral.uDouble += pDouble;

						if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
								(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator+=(double const & pDouble)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE] /*= ?*/;
					::double_conversion::StringBuilder tStringBuilder(tChars,
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE) /*= ...*/;

					Var::StaticPrivateVars::gDoubleToStringConverter->ToShortest(pDouble, 
							&tStringBuilder);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)							
					this->gData.uString.uStd.gString += tStringBuilder.Finalize();
#else
					size_t tLength = tStringBuilder.position() + 1;

					this->addStringEndIntoIndex(this->getStringSize(),
							tStringBuilder.Finalize(), tLength, true);
#endif
					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar += static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					if((this->gData.uIntegral.uSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = 
								static_cast<double>(this->gData.uIntegral.uSignedInt64) + pDouble;
					}
					else //WE ARE NOT SETTING TO NAN BECAUSE THIS IS A VIOLATION OF MORPH RULES, NOT WPG.
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
	#else
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
					this->gData.uIntegral.uDouble = 
							static_cast<double>(this->gData.uIntegral.uSignedInt32) + pDouble;
	#endif
					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
					this->gData.uIntegral.uDouble += pDouble;

					break;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					this->gData.uIntegral.uDouble += pDouble;

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator+=(bool const & pBool)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString += (pBool ? "TRUE" : "FALSE");
#else
					if(pBool)
						{this->addStringEndIntoIndex(this->getStringSize(), "TRUE", 5, true);}
					else
						{this->addStringEndIntoIndex(this->getStringSize(), "FALSE", 6, true);}
#endif

					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		#pragma endregion operator += //}

		//-----------------------------------

		#pragma region operator -= //{
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator-=(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return (*this -= pVar.gData.uString.uStd.gString);
#else
					bool tIsNullTerminated;
					size_t tLength;
					char const * tChar = pVar.getCharPointerAndInfo(&tLength, &tIsNullTerminated);

					return this->doOperatorMinusEqual(tChar, (tIsNullTerminated ? (tLength - 1) : tLength));
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (*this -= pVar.gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (*this -= CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return this->doOperatorMinusEqualForEmulatedInt(pVar.gData.uIntegral.uDouble);}
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (*this -= pVar.gData.uIntegral.uDouble);}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					this->assignPropogateErrorFrom(pVar);

					return *this;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator-=(::std::string const & pString)
			{return this->doOperatorMinusEqual(pString.c_str(), pString.size());}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator-=(char const * pString)
			{return this->doOperatorMinusEqual(pString, strlen(pString));}
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorMinusEqual(char const * pChars, size_t pSize)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar -= static_cast<unsigned char>(tResult);}//LEFT TO C++ STANDARD
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
					{
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT(pChars, pSize, &tIsError);

						if(!tIsError)
						{
							if(CRX__VAR__WILL_SUBTRACT_ON_UNIFIED_INT_OVERFLOW(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
									tResult))
							{
								CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
								this->gData.uIntegral.uDouble = NAN;
							}
							else
								{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) -= tResult;}
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							int _f;
							double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
									StringToDouble(pChars, 
									CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

							if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
							{
								CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
								this->gData.uIntegral.uDouble = static_cast<double>(
										CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this)) - tResult;
							}
							else
							{
								CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							if((tResult <= CRX__VAR__INT_STRING_MAX) &&
									(tResult >= CRX__VAR__INT_STRING_MIN))
							{
								this->gData.uIntegral.uDouble -= tResult;

								if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
										(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{
									CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
									this->gData.uIntegral.uDouble = NAN;
								}
							}
							else
							{
								CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
						else
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble -= tResult;
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							if((tResult <= CRX__VAR__INT_STRING_MAX) &&
									(tResult >= CRX__VAR__INT_STRING_MIN) &&
									(tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
									(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{
								if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
										(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{
									this->gData.uIntegral.uDouble -= tResult;

									if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
											(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
										{this->gData.uIntegral.uDouble = NAN;}
								}
								else
									{this->gData.uIntegral.uDouble = NAN;}
							}
							else
							{
								CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
						else
							{this->gData.uIntegral.uDouble -= tResult;}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator-=(char const & pChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					//this->gData.uIntegral.uUnsignedChar -= pChar;
					if((pChar >= '0') && (pChar <= '9'))
						{this->gData.uIntegral.uUnsignedChar -= (pChar - '0');}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((pChar >= '0') && (pChar <= '9'))
					{
						CRX__VAR__UNIFIED_SIGNED_INT tResult = (pChar - '0');

						if(CRX__VAR__WILL_SUBTRACT_ON_UNIFIED_INT_OVERFLOW(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
									tResult))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = NAN;
						}
						else
							{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) -= tResult;}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pChar >= '0') && (pChar <= '9'))
					{
						if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
									(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							this->gData.uIntegral.uDouble -= static_cast<double>(pChar - '0');

							if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE)  ||
									(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
						}
						else
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator-=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var & Var::operator-=(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator-=(unsigned char const & pUnsignedChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					this->gData.uIntegral.uUnsignedChar -= pUnsignedChar;

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(CRX__VAR__WILL_SUBTRACT_ON_UNIFIED_INT_OVERFLOW(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
								static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedChar)))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = NAN;
					}
					else
						{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) -= static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedChar);}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						this->gData.uIntegral.uDouble -= static_cast<double>(pUnsignedChar);

						if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
								(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator-=(uint32_t const & pUnsignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(pUnsignedInt32 <= UINT8_MAX)
						{this->gData.uIntegral.uUnsignedChar -= static_cast<unsigned char>(pUnsignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					int64_t tResult = static_cast<int64_t>(pUnsignedInt32);

					if(CRX__VAR__WILL_SUBTRACT_ON_INT64_OVERFLOW(this->gData.uIntegral.uSignedInt64,
							tResult))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = NAN;
					}
					else
						{this->gData.uIntegral.uSignedInt64 -= tResult;}
	#else
					if((pUnsignedInt32 <= INT32_MAX) && (pUnsignedInt32 >= INT32_MIN))
					{
						int32_t tResult = static_cast<int32_t>(pUnsignedInt32);

						if(CRX__VAR__WILL_SUBTRACT_ON_INT32_OVERFLOW(this->gData.uIntegral.uSignedInt32,
								tResult))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = NAN;
						}
						else
							{this->gData.uIntegral.uSignedInt32 -= tResult;}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
	#endif
					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pUnsignedInt32 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pUnsignedInt32 >= CRX__VAR__INTERNAL_INT_MIN))
					{
						if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							this->gData.uIntegral.uDouble -= pUnsignedInt32;

							if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
									(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
						}
						else
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator-=(int32_t const & pSignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt32 <= UINT8_MAX) && (pSignedInt32 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar -= static_cast<unsigned char>(pSignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					CRX__VAR__UNIFIED_SIGNED_INT tResult = static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt32);

					if(CRX__VAR__WILL_SUBTRACT_ON_INT64_OVERFLOW(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
							tResult))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = NAN;
					}
					else
						{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) -= tResult;}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						this->gData.uIntegral.uDouble -= pSignedInt32;

						if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
								(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var & Var::operator-=(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator-=(int64_t const & pSignedInt64)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt64 <= UINT8_MAX) && (pSignedInt64 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar -= static_cast<unsigned char>(pSignedInt64);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
		#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					int64_t tResult = pSignedInt64;

					if(CRX__VAR__WILL_SUBTRACT_ON_INT64_OVERFLOW(this->gData.uIntegral.uSignedInt64,
							tResult))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = NAN;
					}
					else
						{this->gData.uIntegral.uSignedInt64 -= tResult;}
		#else
					if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= INT32_MIN))
					{
						int32_t tResult = static_cast<int32_t>(pSignedInt64);

						if(CRX__VAR__WILL_SUBTRACT_ON_INT64_OVERFLOW(this->gData.uIntegral.uSignedInt32,
								tResult))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = NAN;
						}
						else
							{this->gData.uIntegral.uSignedInt32 -= tResult;}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
		#endif
					break;
				}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN))
					{
						this->gData.uIntegral.uDouble -= pSignedInt64;

						if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
								(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = NAN;
						}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN) &&
							(pSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(pSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							this->gData.uIntegral.uDouble -= pSignedInt64;

							if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
									(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{this->gData.uIntegral.uDouble = NAN;}
						}
						else
							{this->gData.uIntegral.uDouble = NAN;}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::doOperatorMinusEqualForEmulatedInt(double const & pDouble)
		{
			CRX__BOOST_ASSERT((pDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
					(pDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE));

			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar -= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_EMULATED_INT:
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						this->gData.uIntegral.uDouble -= pDouble;

						if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
								(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator-=(double const & pDouble)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar -= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					if((this->gData.uIntegral.uSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = 
								static_cast<double>(this->gData.uIntegral.uSignedInt64) - pDouble;
					}
					else //WE ARE NOT SETTING TO NAN BECAUSE THIS IS A VIOLATION OF MORPH RULES, NOT WPG.
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
	#else
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
					this->gData.uIntegral.uDouble = 
							static_cast<double>(this->gData.uIntegral.uSignedInt32) - pDouble;
	#endif
					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
					this->gData.uIntegral.uDouble -= pDouble;

					break;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					this->gData.uIntegral.uDouble -= pDouble;

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator-=(bool const & pBool))
		#pragma endregion operator -= //}
	
		//-----------------------------------

		#pragma region operator *= //{
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator*=(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return (*this *= pVar.gData.uString.uStd.gString);
#else
					bool tIsNullTerminated;
					size_t tLength;
					char const * tChar = pVar.getCharPointerAndInfo(&tLength, &tIsNullTerminated);

					return this->doOperatorMultiplyEqual(tChar, (tIsNullTerminated ? (tLength - 1) : tLength));
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (*this *= pVar.gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (*this *= CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return this->doOperatorMultiplyEqualForEmulatedInt(pVar.gData.uIntegral.uDouble);}
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (*this *= pVar.gData.uIntegral.uDouble);}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					this->assignPropogateErrorFrom(pVar);

					return *this;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator*=(::std::string const & pString)
			{return this->doOperatorMultiplyEqual(pString.c_str(), pString.size());}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator*=(char const * pString)
			{return this->doOperatorMultiplyEqual(pString, strlen(pString));}
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorMultiplyEqual(char const * pChars, size_t pSize)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar *= static_cast<unsigned char>(tResult);}//LEFT TO C++ STANDARD
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
					{
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT(pChars, pSize, &tIsError);

						if(!tIsError)
						{
							if(CRX__VAR__WILL_MULTIPLY_ON_UNIFIED_INT_OVERFLOW(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
									tResult))
							{
								CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
								this->gData.uIntegral.uDouble = NAN;
							}
							else
								{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) *= tResult;}
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							int _f;
							double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
									StringToDouble(pChars, 
									CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

							if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
							{
								CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
								this->gData.uIntegral.uDouble = static_cast<double>(
										CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this)) * tResult;
							}
							else
							{
								CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							if((tResult <= CRX__VAR__INT_STRING_MAX) &&
									(tResult >= CRX__VAR__INT_STRING_MIN))
							{
								this->gData.uIntegral.uDouble *= tResult;

								if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
										(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{
									CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
									this->gData.uIntegral.uDouble = NAN;
								}
							}
							else
							{
								CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
						else
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble *= tResult;
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							if((tResult <= CRX__VAR__INT_STRING_MAX) &&
									(tResult >= CRX__VAR__INT_STRING_MIN) &&
									(tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
									(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{
								if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
										(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{
									this->gData.uIntegral.uDouble *= tResult;

									if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
											(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
										{this->gData.uIntegral.uDouble = NAN;}
								}
								else
									{this->gData.uIntegral.uDouble = NAN;}
							}
							else
							{
								CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
						else
							{this->gData.uIntegral.uDouble *= tResult;}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator*=(char const & pChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					//this->gData.uIntegral.uUnsignedChar *= pChar;
					if((pChar >= '0') && (pChar <= '9'))
						{this->gData.uIntegral.uUnsignedChar *= (pChar - '0');}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((pChar >= '0') && (pChar <= '9'))
					{
						CRX__VAR__UNIFIED_SIGNED_INT tResult = (pChar - '0');

						if(CRX__VAR__WILL_MULTIPLY_ON_UNIFIED_INT_OVERFLOW(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
									tResult))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = NAN;
						}
						else
							{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) *= tResult;}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pChar >= '0') && (pChar <= '9'))
					{
						if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
									(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							this->gData.uIntegral.uDouble *= static_cast<double>(pChar - '0');

							if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE)  ||
									(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
						}
						else
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator*=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var & Var::operator*=(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator*=(unsigned char const & pUnsignedChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					this->gData.uIntegral.uUnsignedChar *= pUnsignedChar;

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(CRX__VAR__WILL_MULTIPLY_ON_UNIFIED_INT_OVERFLOW(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
								static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedChar)))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = NAN;
					}
					else
						{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) *= static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedChar);}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						this->gData.uIntegral.uDouble *= static_cast<double>(pUnsignedChar);

						if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
								(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator*=(uint32_t const & pUnsignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(pUnsignedInt32 <= UINT8_MAX)
						{this->gData.uIntegral.uUnsignedChar *= static_cast<unsigned char>(pUnsignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					int64_t tResult = static_cast<int64_t>(pUnsignedInt32);

					if(CRX__VAR__WILL_MULTIPLY_ON_INT64_OVERFLOW(this->gData.uIntegral.uSignedInt64,
							tResult))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = NAN;
					}
					else
						{this->gData.uIntegral.uSignedInt64 *= tResult;}
	#else
					if((pUnsignedInt32 <= INT32_MAX) && (pUnsignedInt32 >= INT32_MIN))
					{
						int32_t tResult = static_cast<int32_t>(pUnsignedInt32);

						if(CRX__VAR__WILL_MULTIPLY_ON_INT64_OVERFLOW(this->gData.uIntegral.uSignedInt32,
								tResult))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = NAN;
						}
						else
							{this->gData.uIntegral.uSignedInt32 *= tResult;}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
	#endif
					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pUnsignedInt32 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pUnsignedInt32 >= CRX__VAR__INTERNAL_INT_MIN))
					{
						if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							this->gData.uIntegral.uDouble *= pUnsignedInt32;

							if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
									(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
						}
						else
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator*=(int32_t const & pSignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt32 <= UINT8_MAX) && (pSignedInt32 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar *= static_cast<unsigned char>(pSignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					CRX__VAR__UNIFIED_SIGNED_INT tResult = static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt32);

					if(CRX__VAR__WILL_MULTIPLY_ON_INT64_OVERFLOW(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
							tResult))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = NAN;
					}
					else
						{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) *= tResult;}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						this->gData.uIntegral.uDouble *= pSignedInt32;

						if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
								(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var & Var::operator*=(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator*=(int64_t const & pSignedInt64)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt64 <= UINT8_MAX) && (pSignedInt64 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar *= static_cast<unsigned char>(pSignedInt64);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
		#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					int64_t tResult = pSignedInt64;

					if(CRX__VAR__WILL_MULTIPLY_ON_INT64_OVERFLOW(this->gData.uIntegral.uSignedInt64,
							tResult))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = NAN;
					}
					else
						{this->gData.uIntegral.uSignedInt64 *= tResult;}
		#else
					if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= INT32_MIN))
					{
						int32_t tResult = static_cast<int32_t>(pSignedInt64);

						if(CRX__VAR__WILL_MULTIPLY_ON_INT32_OVERFLOW(this->gData.uIntegral.uSignedInt32,
								tResult))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = NAN;
						}
						else
							{this->gData.uIntegral.uSignedInt32 *= tResult;}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
		#endif
					break;
				}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN))
					{
						this->gData.uIntegral.uDouble *= pSignedInt64;

						if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
								(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = NAN;
						}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN) &&
							(pSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(pSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							this->gData.uIntegral.uDouble *= pSignedInt64;

							if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
									(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{this->gData.uIntegral.uDouble = NAN;}
						}
						else
							{this->gData.uIntegral.uDouble = NAN;}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorMultiplyEqualForEmulatedInt(double const & pDouble)
		{
			CRX__BOOST_ASSERT((pDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
					(pDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE));

			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar *= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_EMULATED_INT:
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((this->gData.uIntegral.uDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						this->gData.uIntegral.uDouble *= pDouble;

						if((this->gData.uIntegral.uDouble > CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) ||
								(this->gData.uIntegral.uDouble < CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}
					}
					else
						{CRX__VAR__SET_DOUBLE_TO_NAN_CONSIDERING_EMULATED_INT(this);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator*=(double const & pDouble)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar *= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					if((this->gData.uIntegral.uSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = 
								static_cast<double>(this->gData.uIntegral.uSignedInt64) * pDouble;
					}
					else //WE ARE NOT SETTING TO NAN BECAUSE THIS IS A VIOLATION OF MORPH RULES, NOT WPG.
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
	#else
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
					this->gData.uIntegral.uDouble = 
							static_cast<double>(this->gData.uIntegral.uSignedInt32) * pDouble;
	#endif
					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
					this->gData.uIntegral.uDouble *= pDouble;

					break;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					this->gData.uIntegral.uDouble *= pDouble;

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator*=(bool const & pBool))
		#pragma endregion operator *= //}
			
		//-----------------------------------

		#pragma region operator /= //{
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator/=(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return (*this /= pVar.gData.uString.uStd.gString);
#else
					bool tIsNullTerminated;
					size_t tLength;
					char const * tChar = pVar.getCharPointerAndInfo(&tLength, &tIsNullTerminated);

					return this->doOperatorDivideEqual(tChar, (tIsNullTerminated ? (tLength - 1) : tLength));
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (*this /= pVar.gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (*this /= CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return this->doOperatorDivideEqualForEmulatedInt(pVar.gData.uIntegral.uDouble);}
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (*this /= pVar.gData.uIntegral.uDouble);}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					this->assignPropogateErrorFrom(pVar);

					return *this;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator/=(::std::string const & pString)
			{return this->doOperatorDivideEqual(pString.c_str(), pString.size());}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator/=(char const * pString)
			{return this->doOperatorDivideEqual(pString, strlen(pString));}
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorDivideEqual(char const * pChars, size_t pSize)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar /= static_cast<unsigned char>(tResult);}//LEFT TO C++ STANDARD
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					/*HOPING COMPILER WILL OPTIMIZE THIS OUT WHEN THE INTERNAL INTEGER IS INT32*/
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							bool tIsError = false;
							CRX__VAR__UNIFIED_SIGNED_INT tResult = 
									CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT(pChars, pSize, &tIsError);

							/*
							HOPING COMPILER WILL OPTIMIZE THE EXTRA CHECKS OUT WHEN THE INTERNAL INTEGER IS INT32
							NOTE: THE CHECKS HERE ARE FOR MORPH RULES, NOT FOR WPG.
							*/
							if(!tIsError && (tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
									(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{
								CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
								this->gData.uIntegral.uDouble = static_cast<double>(
										CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this)) / static_cast<double>(tResult);
							}
							else
							{
								CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
						else
						{
							int _f;
							double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
									StringToDouble(pChars, 
									CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

							if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
							{
								CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
								this->gData.uIntegral.uDouble = static_cast<double>(
										CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this)) / tResult;
							}
							else
							{
								CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						/*NOTE: ALL THE CHECKS HERE ARE FOR MORPH RULES, NOT FOR WPG.*/
						if(!Var::isNumberStringAnIntegerIfValid(pChars, pSize) ||
								((tResult <= CRX__VAR__INT_STRING_MAX) &&
								(tResult >= CRX__VAR__INT_STRING_MIN) &&
								((CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE >= CRX__VAR__INT_STRING_MAX) ||
								((tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE)))))
						{
							CRX__VAR_SET_TYPE_TO_DOUBLE_FROM_EMULATED_INT(this);
							this->gData.uIntegral.uDouble /= tResult;
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator/=(char const & pChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					//this->gData.uIntegral.uUnsignedChar /= pChar;
					if((pChar >= '0') && (pChar <= '9'))
						{this->gData.uIntegral.uUnsignedChar /= (pChar - '0');}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					/*HOPING COMPILER WILL OPTIMIZE THIS OUT WHEN THE INTERNAL INTEGER IS INT32*/
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						if((pChar >= '0') && (pChar <= '9'))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = static_cast<double>(
									CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this)) / static_cast<double>(pChar - '0');
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pChar >= '0') && (pChar <= '9'))
					{
						CRX__VAR_SET_TYPE_TO_DOUBLE_FROM_EMULATED_INT(this);
						this->gData.uIntegral.uDouble /= static_cast<double>(pChar - '0');
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator/=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var & Var::operator/=(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator/=(unsigned char const & pUnsignedChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					this->gData.uIntegral.uUnsignedChar /= pUnsignedChar;

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					/*HOPING COMPILER WILL OPTIMIZE THIS OUT WHEN THE INTERNAL INTEGER IS INT32*/
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = static_cast<double>(
								CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this)) / static_cast<double>(pUnsignedChar);
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					CRX__VAR_SET_TYPE_TO_DOUBLE_FROM_EMULATED_INT(this);
					this->gData.uIntegral.uDouble /= static_cast<double>(pUnsignedChar);

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator/=(uint32_t const & pUnsignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(pUnsignedInt32 <= UINT8_MAX)
						{this->gData.uIntegral.uUnsignedChar /= static_cast<unsigned char>(pUnsignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					if((this->gData.uIntegral.uSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = static_cast<double>(
								this->gData.uIntegral.uSignedInt64) / static_cast<double>(pUnsignedInt32);
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);}
	#else
					if((pUnsignedInt32 <= INT32_MAX) && (pUnsignedInt32 >= INT32_MIN))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = static_cast<double>(
								this->gData.uIntegral.uSignedInt32) / static_cast<double>(pUnsignedInt32);
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
	#endif
					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pUnsignedInt32 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pUnsignedInt32 >= CRX__VAR__INTERNAL_INT_MIN))
					{
						CRX__VAR_SET_TYPE_TO_DOUBLE_FROM_EMULATED_INT(this);
						this->gData.uIntegral.uDouble /= static_cast<double>(pUnsignedInt32);
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator/=(int32_t const & pSignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt32 <= UINT8_MAX) && (pSignedInt32 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar /= static_cast<unsigned char>(pSignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					/*HOPING COMPILER WILL OPTIMIZE THIS OUT WHEN THE INTERNAL INTEGER IS INT32*/
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = static_cast<double>(
								CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this)) / static_cast<double>(pSignedInt32);
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					CRX__VAR_SET_TYPE_TO_DOUBLE_FROM_EMULATED_INT(this);
					this->gData.uIntegral.uDouble /= static_cast<double>(pSignedInt32);

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var & Var::operator/=(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator/=(int64_t const & pSignedInt64)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt64 <= UINT8_MAX) && (pSignedInt64 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar /= static_cast<unsigned char>(pSignedInt64);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
		#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					if((this->gData.uIntegral.uSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						if((pSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(pSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = static_cast<double>(
									this->gData.uIntegral.uSignedInt64) / static_cast<double>(pSignedInt64);
						}
						else
							{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);}
		#else
					if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= INT32_MIN))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = static_cast<double>(
								this->gData.uIntegral.uSignedInt32) / static_cast<double>(pSignedInt64);
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
		#endif
					break;
				}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					/*NOTE: ALL THE CHECKS HERE ARE FOR MORPH RULES, NOT FOR WPG.*/
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN) &&
							((CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE >= CRX__VAR__INTERNAL_INT_MAX) ||
							((pSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(pSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))))
					{
						CRX__VAR_SET_TYPE_TO_DOUBLE_FROM_EMULATED_INT(this);
						this->gData.uIntegral.uDouble /= static_cast<double>(pSignedInt64);
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorDivideEqualForEmulatedInt(double const & pDouble)
		{
			CRX__BOOST_ASSERT((pDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
					(pDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE));

			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar /= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_EMULATED_INT:
				case CRX__VAR__TYPE_DOUBLE:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
					this->gData.uIntegral.uDouble /= pDouble;

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator/=(double const & pDouble)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar /= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					if((this->gData.uIntegral.uSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = static_cast<double>(
								this->gData.uIntegral.uSignedInt64) / pDouble;
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
	#else
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
					this->gData.uIntegral.uDouble = static_cast<double>(
							this->gData.uIntegral.uSignedInt32) / pDouble;
	#endif
					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
					this->gData.uIntegral.uDouble /= pDouble;

					break;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					this->gData.uIntegral.uDouble /= pDouble;

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator/=(bool const & pBool))
		#pragma endregion operator /= //}
	
		//-----------------------------------

		#pragma region operator %= //{
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator%=(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return (*this %= pVar.gData.uString.uStd.gString);
#else
					bool tIsNullTerminated;
					size_t tLength;
					char const * tChar = pVar.getCharPointerAndInfo(&tLength, &tIsNullTerminated);

					return this->doOperatorModulusEqual(tChar, (tIsNullTerminated ? (tLength - 1) : tLength));
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					return (*this %= *(pVar.gData.uHashTable.gUnorderedMap));
#else
					return this->doOperatorModulusEqual(pVar.gData.uHashTable.gKHash);
#endif
				}
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (*this %= pVar.gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (*this %= CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return this->doOperatorModulusEqualForEmulatedInt(pVar.gData.uIntegral.uDouble);}
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (*this %= pVar.gData.uIntegral.uDouble);}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					this->assignPropogateErrorFrom(pVar);

					return *this;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator%=(::std::string const & pString)
			{return this->doOperatorModulusEqual(pString.c_str(), pString.size());}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator%=(char const * pString)
			{return this->doOperatorModulusEqual(pString, strlen(pString));}
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorModulusEqual(char const * pChars, size_t pSize)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar %= static_cast<unsigned char>(tResult);}//LEFT TO C++ STANDARD
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
					{
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT(pChars, pSize, &tIsError);

						if(!tIsError)
							{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) %= tResult;}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							int _f;
							double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
									StringToDouble(pChars, 
									CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

							if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
							{
								CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
								this->gData.uIntegral.uDouble = ::fmod(static_cast<double>(
										CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this)), tResult);
							}
							else
							{
								CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							if((tResult <= CRX__VAR__INT_STRING_MAX) &&
									(tResult >= CRX__VAR__INT_STRING_MIN))
							{
								this->gData.uIntegral.uDouble = ::fmod(this->gData.uIntegral.uDouble, 
										tResult);
							}
							else
							{
								CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
						else
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = ::fmod(this->gData.uIntegral.uDouble, 
									tResult);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							if((tResult <= CRX__VAR__INT_STRING_MAX) &&
									(tResult >= CRX__VAR__INT_STRING_MIN) &&
									(tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
									(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
							{
								this->gData.uIntegral.uDouble = ::fmod(this->gData.uIntegral.uDouble, 
										tResult);
							}
							else
							{
								CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
						else
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
							this->gData.uIntegral.uDouble = ::fmod(this->gData.uIntegral.uDouble, 
									tResult);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator%=(char const & pChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					//this->gData.uIntegral.uUnsignedChar %= pChar;
					if((pChar >= '0') && (pChar <= '9'))
						{this->gData.uIntegral.uUnsignedChar %= (pChar - '0');}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((pChar >= '0') && (pChar <= '9'))
					{
						CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) %= 
								static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pChar - '0');
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pChar >= '0') && (pChar <= '9'))
					{
						this->gData.uIntegral.uDouble = ::fmod(this->gData.uIntegral.uDouble, 
								static_cast<double>(pChar - '0'));
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator%=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
/*					
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator tIterator = 
							this->gData.uHashTable.gUnorderedMap->begin();

					while(tIterator != this->gData.uHashTable.gUnorderedMap->end())
					{
						if(pUnorderedMap.count((*tIterator).first) == 1)
							{continue;}

						this->gData.uHashTable.gUnorderedMap->erase((*tIterator).first);

						tIterator++;
					}

					tIterator = pUnorderedMap.begin();
					while(tIterator != pUnorderedMap.end())
					{
						if(this->gData.uHashTable.gUnorderedMap->count((*tIterator).first) == 1)
							{continue;}

						this->gData.uHashTable.gUnorderedMap->insert(::std::make_pair((*tIterator).first, (*tIterator).second));

						tIterator++;
					}
#else
					CRX__VAR__KHash_copyImpressFromVarHashTable(this->gData.uHashTable.gKHash, 
							pUnorderedMap);
#endif
*/
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator tIterator = 
							this->gData.uHashTable.gUnorderedMap->begin();

					while(tIterator != this->gData.uHashTable.gUnorderedMap->end())
					{
						if(pUnorderedMap.count((*tIterator).first) == 0)
							{continue;}

						(*(this->gData.uHashTable.gUnorderedMap))[(*tIterator).first] = (*tIterator).second;

						tIterator++;
					}
#else
					CRX__VAR__KHash_copyUpdateFromVarHashTable(this->gData.uHashTable.gKHash, 
							pUnorderedMap);
#endif
					break;
				}
				case CRX__VAR__TYPE_ARRAY:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#if(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorModulusEqual(CRX__VAR__KHash const * pKHash)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
					/*CRX__VAR__KHash_copyImpressFromKHash(this->gData.uHashTable.gKHash, pKHash);*/
					CRX__VAR__KHash_copyUpdateFromKHash(this->gData.uHashTable.gKHash, pKHash);

					break;
				}
				case CRX__VAR__TYPE_ARRAY:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif
		CRX_DISABLED_METHOD(Var & Var::operator%=(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator%=(unsigned char const & pUnsignedChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					this->gData.uIntegral.uUnsignedChar %= pUnsignedChar;

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) %= 
							static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedChar);

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					this->gData.uIntegral.uDouble = ::fmod(this->gData.uIntegral.uDouble, 
							static_cast<double>(pUnsignedChar));

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator%=(uint32_t const & pUnsignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(pUnsignedInt32 <= UINT8_MAX)
						{this->gData.uIntegral.uUnsignedChar %= static_cast<unsigned char>(pUnsignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					this->gData.uIntegral.uSignedInt64 %= static_cast<int64_t>(pUnsignedInt32);
	#else
					if((pUnsignedInt32 <= INT32_MAX) && (pUnsignedInt32 >= INT32_MIN))
						{this->gData.uIntegral.uSignedInt32 %= static_cast<int32_t>(pUnsignedInt32);}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
	#endif
					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pUnsignedInt32 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pUnsignedInt32 >= CRX__VAR__INTERNAL_INT_MIN))
					{
						this->gData.uIntegral.uDouble = ::fmod(this->gData.uIntegral.uDouble, 
								static_cast<double>(pUnsignedInt32));
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator%=(int32_t const & pSignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt32 <= UINT8_MAX) && (pSignedInt32 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar %= static_cast<unsigned char>(pSignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) %= static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt32);

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					this->gData.uIntegral.uDouble = ::fmod(this->gData.uIntegral.uDouble, 
							static_cast<double>(pSignedInt32));

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var & Var::operator%=(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator%=(int64_t const & pSignedInt64)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt64 <= UINT8_MAX) && (pSignedInt64 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar %= static_cast<unsigned char>(pSignedInt64);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
		#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					this->gData.uIntegral.uSignedInt64 %= pSignedInt64;
		#else
					if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= INT32_MIN))
						{this->gData.uIntegral.uSignedInt32 %= static_cast<int32_t>(pSignedInt64);}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
		#endif
					break;
				}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN))
					{
						this->gData.uIntegral.uDouble = ::fmod(this->gData.uIntegral.uDouble, 
								static_cast<double>(pSignedInt64));
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN) &&
							(pSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(pSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						this->gData.uIntegral.uDouble = ::fmod(this->gData.uIntegral.uDouble, 
								static_cast<double>(pSignedInt64));
					}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorModulusEqualForEmulatedInt(double const & pDouble)
		{
			CRX__BOOST_ASSERT((pDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
					(pDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE));

			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar %= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_EMULATED_INT:
				case CRX__VAR__TYPE_DOUBLE:
				{
					this->gData.uIntegral.uDouble = ::fmod(this->gData.uIntegral.uDouble, 
							static_cast<double>(pDouble));

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator%=(double const & pDouble)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar %= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					if((this->gData.uIntegral.uSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
					{
						CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
						this->gData.uIntegral.uDouble = 
								::fmod(static_cast<double>(this->gData.uIntegral.uSignedInt64), pDouble);
					}
					else //WE ARE NOT SETTING TO NAN BECAUSE THIS IS A VIOLATION OF MORPH RULES, NOT WPG.
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
	#else
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
					this->gData.uIntegral.uDouble = 
							::fmod(static_cast<double>(this->gData.uIntegral.uSignedInt32), pDouble);
	#endif
					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_DOUBLE);
					this->gData.uIntegral.uDouble = ::fmod(this->gData.uIntegral.uDouble, pDouble);

					break;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					this->gData.uIntegral.uDouble = ::fmod(this->gData.uIntegral.uDouble, pDouble);

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator%=(bool const & pBool))
		#pragma endregion operator %= //}
		
		//-----------------------------------

		#pragma region operator < //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return (*this < pVar.gData.uString.uStd.gString);
#else
					bool tIsNullTerminated;
					size_t tLength;
					char const * tChar = pVar.getCharPointerAndInfo(&tLength, &tIsNullTerminated);

					return this->doOperatorLessThan(tChar, (tIsNullTerminated ? (tLength - 1) : tLength));
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (*this < pVar.gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (*this < CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return this->doOperatorLessThanForEmulatedInt(pVar.gData.uIntegral.uDouble);}
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (*this < pVar.gData.uIntegral.uDouble);}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					Var vReturn /*= ?*/;

					vReturn.assignPropogateErrorFrom(pVar);

					return vReturn;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<(::std::string const & pString)
			{return this->doOperatorLessThan(pString.c_str(), pString.size());}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<(char const * pString)
			{return this->doOperatorLessThan(pString, strlen(pString));}
		CRX_PRIVATE CRX__LIB__METHOD() Var Var::doOperatorLessThan(char const * pChars, size_t pSize)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
					{return (this->development_doStrcmpOnInternalStringAnd(pChars, pSize) < 0);}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{return (this->gData.uIntegral.uUnsignedChar < static_cast<unsigned char>(tResult));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND,
								return tReturn);
					}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
					{
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT(pChars, pSize, &tIsError);

						if(!tIsError)
							{return (CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) < tResult);}
						else
						{
							Var tReturn = false;

							CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND,
									return tReturn);
						}
					}
					else
					{
						if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							int _f;
							double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
									StringToDouble(pChars,
									CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

							if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
							{
								return (static_cast<double>(
										CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this)) < tResult);
							}
							else
							{
								Var tReturn = false;

								CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND,
										return tReturn);
							}
						}
						else
						{
							Var tReturn = false;

							CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION,
									return tReturn);
						}
					}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							if((tResult <= CRX__VAR__INT_STRING_MAX) &&
									(tResult >= CRX__VAR__INT_STRING_MIN))
								{return (this->gData.uIntegral.uDouble < tResult);}
							else
							{
								Var tReturn = false;

								CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, 
										return tReturn);
							}
						}
						else
							{return (this->gData.uIntegral.uDouble < tResult);}
					}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND,
								return tReturn);
					}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							if((tResult <= CRX__VAR__INT_STRING_MAX) &&
									(tResult >= CRX__VAR__INT_STRING_MIN) &&
									(tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
									(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{return (this->gData.uIntegral.uDouble < tResult);}
							else
							{
								Var tReturn = false;

								CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, 
										return tReturn);
							}
						}
						else
							{return (this->gData.uIntegral.uDouble < tResult);}
					}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND,
								return tReturn);
					}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<(char const & pChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					char tString[2];

					tString[0] = pChar;
					tString[1] = '\0';

					return (this->development_doStrcmpOnInternalStringAnd(tString, 1) < 0);
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					//this->gData.uIntegral.uUnsignedChar < pChar;
					if((pChar >= '0') && (pChar <= '9'))
						{return (this->gData.uIntegral.uUnsignedChar < (pChar - '0'));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((pChar >= '0') && (pChar <= '9'))
					{
						return (CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) < 
								static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pChar - '0'));
					}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pChar >= '0') && (pChar <= '9'))
						{return (this->gData.uIntegral.uDouble < static_cast<double>(pChar - '0'));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_DISABLED_METHOD(Var Var::operator<(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var Var::operator<(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<(unsigned char const & pUnsignedChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (this->gData.uIntegral.uUnsignedChar < pUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					return (CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) < 
							static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedChar));
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (this->gData.uIntegral.uDouble < static_cast<double>(pUnsignedChar));}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<(uint32_t const & pUnsignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(pUnsignedInt32 <= UINT8_MAX)
						{return (this->gData.uIntegral.uUnsignedChar < static_cast<unsigned char>(pUnsignedInt32));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					return (this->gData.uIntegral.uSignedInt64 < static_cast<int64_t>(pUnsignedInt32));
	#else
					if((pUnsignedInt32 <= INT32_MAX) && (pUnsignedInt32 >= INT32_MIN))
						{return (this->gData.uIntegral.uSignedInt32 < static_cast<int32_t>(pUnsignedInt32));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}	
	#endif
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pUnsignedInt32 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pUnsignedInt32 >= CRX__VAR__INTERNAL_INT_MIN))
						{return (this->gData.uIntegral.uDouble < static_cast<double>(pUnsignedInt32));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<(int32_t const & pSignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt32 <= UINT8_MAX) && (pSignedInt32 >= 0)/*UINT8_MIN*/)
						{return (this->gData.uIntegral.uUnsignedChar < static_cast<unsigned char>(pSignedInt32));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) < static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt32));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (this->gData.uIntegral.uDouble < static_cast<double>(pSignedInt32));}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var Var::operator<(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<(int64_t const & pSignedInt64)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt64 <= UINT8_MAX) && (pSignedInt64 >= 0)/*UINT8_MIN*/)
						{return (this->gData.uIntegral.uUnsignedChar < static_cast<unsigned char>(pSignedInt64));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
		#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					return (this->gData.uIntegral.uSignedInt64 < pSignedInt64);
		#else
					if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= INT32_MIN))
						{return (this->gData.uIntegral.uSignedInt32 < static_cast<int32_t>(pSignedInt64));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
		#endif
				}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN))
						{return (this->gData.uIntegral.uDouble < static_cast<double>(pSignedInt64));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN) &&
							(pSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(pSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{return (this->gData.uIntegral.uDouble < static_cast<double>(pSignedInt64));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PRIVATE CRX__LIB__METHOD() Var Var::doOperatorLessThanForEmulatedInt(double const & pDouble)
		{
			CRX__BOOST_ASSERT((pDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
					(pDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE));

			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{return (this->gData.uIntegral.uUnsignedChar < static_cast<unsigned char>(pDouble));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
				case CRX__VAR__TYPE_EMULATED_INT:
				case CRX__VAR__TYPE_DOUBLE:
					{return (this->gData.uIntegral.uDouble < pDouble);}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<(double const & pDouble)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, UINT8_MAX))
						{return (this->gData.uIntegral.uUnsignedChar < static_cast<unsigned char>(pDouble));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					if((this->gData.uIntegral.uSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{return (static_cast<double>(this->gData.uIntegral.uSignedInt64) < pDouble);}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
	#else
					return (static_cast<double>(this->gData.uIntegral.uSignedInt32) < pDouble);
	#endif
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (this->gData.uIntegral.uDouble < pDouble);}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_DISABLED_METHOD(Var Var::operator<(bool const & pBool))
		#pragma endregion operator < //}
	
		//-----------------------------------

		#pragma region operator > //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return (*this > pVar.gData.uString.uStd.gString);
#else
					bool tIsNullTerminated;
					size_t tLength;
					char const * tChar = pVar.getCharPointerAndInfo(&tLength, &tIsNullTerminated);

					return this->doOperatorGreaterThan(tChar, (tIsNullTerminated ? (tLength - 1) : tLength));
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (*this > pVar.gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (*this > CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return this->doOperatorGreaterThanForEmulatedInt(pVar.gData.uIntegral.uDouble);}
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (*this > pVar.gData.uIntegral.uDouble);}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					Var vReturn /*= ?*/;

					vReturn.assignPropogateErrorFrom(pVar);

					return vReturn;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>(::std::string const & pString)
			{return this->doOperatorGreaterThan(pString.c_str(), pString.size());}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>(char const * pString)
			{return this->doOperatorGreaterThan(pString, strlen(pString));}
		CRX_PRIVATE CRX__LIB__METHOD() Var Var::doOperatorGreaterThan(char const * pChars, size_t pSize)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
					{return (this->development_doStrcmpOnInternalStringAnd(pChars, pSize) > 0);}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{return (this->gData.uIntegral.uUnsignedChar > static_cast<unsigned char>(tResult));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND,
								return tReturn);
					}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
					{
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT(pChars, pSize, &tIsError);

						if(!tIsError)
							{return (CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) > tResult);}
						else
						{
							Var tReturn = false;

							CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND,
									return tReturn);
						}
					}
					else
					{
						if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							int _f;
							double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
									StringToDouble(pChars, 
									CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

							if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
							{
								return (static_cast<double>(
										CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this)) > tResult);
							}
							else
							{
								Var tReturn = false;

								CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND,
										return tReturn);
							}
						}
						else
						{
							Var tReturn = false;

							CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION,
									return tReturn);
						}
					}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							if((tResult <= CRX__VAR__INT_STRING_MAX) &&
									(tResult >= CRX__VAR__INT_STRING_MIN))
								{return (this->gData.uIntegral.uDouble > tResult);}
							else
							{
								Var tReturn = false;

								CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, 
										return tReturn);
							}
						}
						else
							{return (this->gData.uIntegral.uDouble > tResult);}
					}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND,
								return tReturn);
					}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							if((tResult <= CRX__VAR__INT_STRING_MAX) &&
									(tResult >= CRX__VAR__INT_STRING_MIN) &&
									(tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
									(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{return (this->gData.uIntegral.uDouble > tResult);}
							else
							{
								Var tReturn = false;

								CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, 
										return tReturn);
							}
						}
						else
							{return (this->gData.uIntegral.uDouble > tResult);}
					}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND,
								return tReturn);
					}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>(char const & pChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					char tString[2];

					tString[0] = pChar;
					tString[1] = '\0';

					return (this->development_doStrcmpOnInternalStringAnd(tString, 1) > 0);
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					//this->gData.uIntegral.uUnsignedChar > pChar;
					if((pChar >= '0') && (pChar <= '9'))
						{return (this->gData.uIntegral.uUnsignedChar > (pChar - '0'));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((pChar >= '0') && (pChar <= '9'))
					{
						return (CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) > 
								static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pChar - '0'));
					}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pChar >= '0') && (pChar <= '9'))
						{return (this->gData.uIntegral.uDouble > static_cast<double>(pChar - '0'));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_DISABLED_METHOD(Var Var::operator>(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var Var::operator>(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>(unsigned char const & pUnsignedChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (this->gData.uIntegral.uUnsignedChar > pUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					return (CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) > 
							static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedChar));
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (this->gData.uIntegral.uDouble > static_cast<double>(pUnsignedChar));}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>(uint32_t const & pUnsignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(pUnsignedInt32 <= UINT8_MAX)
						{return (this->gData.uIntegral.uUnsignedChar > static_cast<unsigned char>(pUnsignedInt32));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					return (this->gData.uIntegral.uSignedInt64 > static_cast<int64_t>(pUnsignedInt32));
	#else
					if((pUnsignedInt32 <= INT32_MAX) && (pUnsignedInt32 >= INT32_MIN))
						{return (this->gData.uIntegral.uSignedInt32 > static_cast<int32_t>(pUnsignedInt32));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}	
	#endif
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pUnsignedInt32 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pUnsignedInt32 >= CRX__VAR__INTERNAL_INT_MIN))
						{return (this->gData.uIntegral.uDouble > static_cast<double>(pUnsignedInt32));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>(int32_t const & pSignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt32 <= UINT8_MAX) && (pSignedInt32 >= 0)/*UINT8_MIN*/)
						{return (this->gData.uIntegral.uUnsignedChar > static_cast<unsigned char>(pSignedInt32));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) > static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt32));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (this->gData.uIntegral.uDouble > static_cast<double>(pSignedInt32));}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var Var::operator>(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>(int64_t const & pSignedInt64)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt64 <= UINT8_MAX) && (pSignedInt64 >= 0)/*UINT8_MIN*/)
						{return (this->gData.uIntegral.uUnsignedChar > static_cast<unsigned char>(pSignedInt64));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
		#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					return (this->gData.uIntegral.uSignedInt64 > pSignedInt64);
		#else
					if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= INT32_MIN))
						{return (this->gData.uIntegral.uSignedInt32 > static_cast<int32_t>(pSignedInt64));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
		#endif
				}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN))
						{return (this->gData.uIntegral.uDouble > static_cast<double>(pSignedInt64));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN) &&
							(pSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(pSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{return (this->gData.uIntegral.uDouble > static_cast<double>(pSignedInt64));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PRIVATE CRX__LIB__METHOD() Var Var::doOperatorGreaterThanForEmulatedInt(double const & pDouble)
		{
			CRX__BOOST_ASSERT((pDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
					(pDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE));

			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{return (this->gData.uIntegral.uUnsignedChar > static_cast<unsigned char>(pDouble));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
				case CRX__VAR__TYPE_EMULATED_INT:
				case CRX__VAR__TYPE_DOUBLE:
					{return (this->gData.uIntegral.uDouble > pDouble);}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>(double const & pDouble)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, UINT8_MAX))
						{return (this->gData.uIntegral.uUnsignedChar > static_cast<unsigned char>(pDouble));}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					if((this->gData.uIntegral.uSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{return (static_cast<double>(this->gData.uIntegral.uSignedInt64) > pDouble);}
					else
					{
						Var tReturn = false;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND, return tReturn);
					}
	#else
					return (static_cast<double>(this->gData.uIntegral.uSignedInt32) > pDouble);
	#endif
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (this->gData.uIntegral.uDouble > pDouble);}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn = false;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION, return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_DISABLED_METHOD(Var Var::operator>(bool const & pBool))
		#pragma endregion operator > //}
	
		//-----------------------------------
		
		#pragma region operator &= //{
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator&=(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return (*this &= pVar.gData.uString.uStd.gString);
#else
					bool tIsNullTerminated;
					size_t tLength;
					char const * tChar = pVar.getCharPointerAndInfo(&tLength, &tIsNullTerminated);

					return this->doOperatorLogicAndEqual(tChar, (tIsNullTerminated ? (tLength - 1) : tLength));
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (*this &= pVar.gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (*this &= CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return this->doOperatorLogicAndEqualForEmulatedInt(pVar.gData.uIntegral.uDouble);}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					this->assignPropogateErrorFrom(pVar);

					return *this;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator&=(::std::string const & pString)
			{return this->doOperatorLogicAndEqual(pString.c_str(), pString.size());}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator&=(char const * pString)
			{return this->doOperatorLogicAndEqual(pString, strlen(pString));}
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorLogicAndEqual(char const * pChars, size_t pSize)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar &= static_cast<unsigned char>(tResult);}//LEFT TO C++ STANDARD
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						int _f;
						double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
								StringToDouble(pChars, 
								CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, INT32_MAX))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) &= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(tResult);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						int _f;
						double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
								StringToDouble(pChars, 
								CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, INT32_MAX))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) &
									static_cast<int32_t>(tResult));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator&=(char const & pChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					//this->gData.uIntegral.uUnsignedChar &= pChar;
					if((pChar >= '0') && (pChar <= '9'))
						{this->gData.uIntegral.uUnsignedChar &= (pChar - '0');}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if((pChar >= '0') && (pChar <= '9'))
							{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) &= (pChar - '0');}
						else
							{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0, INT32_MAX))
					{
						if((pChar >= '0') && (pChar <= '9'))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) &
									static_cast<int32_t>(pChar - '0'));
						}
						else
							{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator&=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var & Var::operator&=(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator&=(unsigned char const & pUnsignedChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					this->gData.uIntegral.uUnsignedChar &= pUnsignedChar;

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
						{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) &= pUnsignedChar;}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0, INT32_MAX))
					{
						CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
						CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
								static_cast<int32_t>(this->gData.uIntegral.uDouble) &
								static_cast<int32_t>(pUnsignedChar));
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator&=(uint32_t const & pUnsignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(pUnsignedInt32 <= UINT8_MAX)
						{this->gData.uIntegral.uUnsignedChar &= static_cast<unsigned char>(pUnsignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(pUnsignedInt32 <= INT32_MAX)
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) &= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(pUnsignedInt32 <= INT32_MAX)
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) &
									static_cast<int32_t>(pUnsignedInt32));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator&=(int32_t const & pSignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt32 <= UINT8_MAX) && (pSignedInt32 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar &= static_cast<unsigned char>(pSignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(pSignedInt32 >= 0)
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) &= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(pSignedInt32 >= 0)
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) & pSignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var & operator&=(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator&=(int64_t const & pSignedInt64)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt64 <= UINT8_MAX) && (pSignedInt64 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar &= static_cast<unsigned char>(pSignedInt64);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= 0))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) &= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt64);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= 0))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) & pSignedInt64);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorLogicAndEqualForEmulatedInt(double const & pDouble)
		{
			CRX__BOOST_ASSERT((pDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
					(pDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE));

			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar &= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_EMULATED_INT:
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if((pDouble <= INT32_MAX) && (pDouble >= 0))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_EMULATED_INT);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<double>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) &
									static_cast<int32_t>(pDouble));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator&=(double const & pDouble)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar &= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, INT32_MAX))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) &= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pDouble);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, INT32_MAX))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_EMULATED_INT);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) &
									static_cast<int32_t>(pDouble));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator&=(bool const & pBool))
		#pragma endregion operator &= //}
	
		//-----------------------------------

		#pragma region operator |= //{
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator|=(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return (*this |= pVar.gData.uString.uStd.gString);
#else
					bool tIsNullTerminated;
					size_t tLength;
					char const * tChar = pVar.getCharPointerAndInfo(&tLength, &tIsNullTerminated);

					return this->doOperatorLogicOrEqual(tChar, (tIsNullTerminated ? (tLength - 1) : tLength));
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (*this |= pVar.gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (*this |= CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return this->doOperatorLogicOrEqualForEmulatedInt(pVar.gData.uIntegral.uDouble);}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					this->assignPropogateErrorFrom(pVar);

					return *this;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator|=(::std::string const & pString)
			{return this->doOperatorLogicOrEqual(pString.c_str(), pString.size());}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator|=(char const * pString)
			{return this->doOperatorLogicOrEqual(pString, strlen(pString));}
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorLogicOrEqual(char const * pChars, size_t pSize)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar |= static_cast<unsigned char>(tResult);}//LEFT TO C++ STANDARD
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						int _f;
						double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
								StringToDouble(pChars, 
								CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, INT32_MAX))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) |= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(tResult);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						int _f;
						double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
								StringToDouble(pChars, 
								CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, INT32_MAX))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) <<
									static_cast<int32_t>(tResult));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator|=(char const & pChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					//this->gData.uIntegral.uUnsignedChar &= pChar;
					if((pChar >= '0') && (pChar <= '9'))
						{this->gData.uIntegral.uUnsignedChar |= (pChar - '0');}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if((pChar >= '0') && (pChar <= '9'))
							{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) |= (pChar - '0');}
						else
							{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0, INT32_MAX))
					{
						if((pChar >= '0') && (pChar <= '9'))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) |
									static_cast<int32_t>(pChar - '0'));
						}
						else
							{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator|=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var & Var::operator|=(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator|=(unsigned char const & pUnsignedChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					this->gData.uIntegral.uUnsignedChar |= pUnsignedChar;

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
						{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) |= pUnsignedChar;}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0, INT32_MAX))
					{
						CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
						CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
								static_cast<int32_t>(this->gData.uIntegral.uDouble) |
								static_cast<int32_t>(pUnsignedChar));
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif				
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator|=(uint32_t const & pUnsignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(pUnsignedInt32 <= UINT8_MAX)
						{this->gData.uIntegral.uUnsignedChar |= static_cast<unsigned char>(pUnsignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(pUnsignedInt32 <= INT32_MAX)
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) |= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(pUnsignedInt32 <= INT32_MAX)
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) |
									static_cast<int32_t>(pUnsignedInt32));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator|=(int32_t const & pSignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt32 <= UINT8_MAX) && (pSignedInt32 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar |= static_cast<unsigned char>(pSignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(pSignedInt32 >= 0)
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) |= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(pSignedInt32 >= 0)
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) | pSignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var & operator|=(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator|=(int64_t const & pSignedInt64)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt64 <= UINT8_MAX) && (pSignedInt64 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar |= static_cast<unsigned char>(pSignedInt64);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= 0))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) |= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt64);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= 0))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) | pSignedInt64);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorLogicOrEqualForEmulatedInt(double const & pDouble)
		{
			CRX__BOOST_ASSERT((pDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
					(pDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE));

			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar |= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_EMULATED_INT:
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if((pDouble <= INT32_MAX) && (pDouble >= 0))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_EMULATED_INT);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<double>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) |
									static_cast<int32_t>(pDouble));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator|=(double const & pDouble)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar |= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, INT32_MAX))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) |= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pDouble);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, INT32_MAX))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_EMULATED_INT);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) |
									static_cast<int32_t>(pDouble));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator|=(bool const & pBool))
		#pragma endregion operator |= //}
	
		//-----------------------------------

		#pragma region operator ^= //{
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator^=(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return (*this ^= pVar.gData.uString.uStd.gString);
#else
					bool tIsNullTerminated;
					size_t tLength;
					char const * tChar = pVar.getCharPointerAndInfo(&tLength, &tIsNullTerminated);

					return this->doOperatorLogicXOrEqual(tChar, (tIsNullTerminated ? (tLength - 1) : tLength));
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (*this ^= pVar.gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (*this ^= CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return this->doOperatorLogicXOrEqualForEmulatedInt(pVar.gData.uIntegral.uDouble);}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					this->assignPropogateErrorFrom(pVar);

					return *this;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator^=(::std::string const & pString)
			{return this->doOperatorLogicXOrEqual(pString.c_str(), pString.size());}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator^=(char const * pString)
			{return this->doOperatorLogicXOrEqual(pString, strlen(pString));}
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorLogicXOrEqual(char const * pChars, size_t pSize)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar ^= static_cast<unsigned char>(tResult);}//LEFT TO C++ STANDARD
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						int _f;
						double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
								StringToDouble(pChars, 
								CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, INT32_MAX))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) ^= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(tResult);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						int _f;
						double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
								StringToDouble(pChars, 
								CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, INT32_MAX))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) ^
									static_cast<int32_t>(tResult));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator^=(char const & pChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					//this->gData.uIntegral.uUnsignedChar &= pChar;
					if((pChar >= '0') && (pChar <= '9'))
						{this->gData.uIntegral.uUnsignedChar ^= (pChar - '0');}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if((pChar >= '0') && (pChar <= '9'))
							{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) ^= (pChar - '0');}
						else
							{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0, INT32_MAX))
					{
						if((pChar >= '0') && (pChar <= '9'))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) ^
									static_cast<int32_t>(pChar - '0'));
						}
						else
							{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator^=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var & Var::operator^=(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator^=(unsigned char const & pUnsignedChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					this->gData.uIntegral.uUnsignedChar ^= pUnsignedChar;

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
						{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) ^= pUnsignedChar;}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0, INT32_MAX))
					{
						CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
						CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
								static_cast<int32_t>(this->gData.uIntegral.uDouble) ^
								static_cast<int32_t>(pUnsignedChar));
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif				
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator^=(uint32_t const & pUnsignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(pUnsignedInt32 <= UINT8_MAX)
						{this->gData.uIntegral.uUnsignedChar ^= static_cast<unsigned char>(pUnsignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(pUnsignedInt32 <= INT32_MAX)
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) ^= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(pUnsignedInt32 <= INT32_MAX)
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) ^
									static_cast<int32_t>(pUnsignedInt32));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator^=(int32_t const & pSignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt32 <= UINT8_MAX) && (pSignedInt32 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar ^= static_cast<unsigned char>(pSignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(pSignedInt32 >= 0)
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) ^= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(pSignedInt32 >= 0)
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) & pSignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var & operator^=(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator^=(int64_t const & pSignedInt64)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt64 <= UINT8_MAX) && (pSignedInt64 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar ^= static_cast<unsigned char>(pSignedInt64);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= 0))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) ^= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt64);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= 0))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) ^ pSignedInt64);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorLogicXOrEqualForEmulatedInt(double const & pDouble)
		{
			CRX__BOOST_ASSERT((pDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
					(pDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE));

			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar ^= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_EMULATED_INT:
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if((pDouble <= INT32_MAX) && (pDouble >= 0))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_EMULATED_INT);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<double>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) ^
									static_cast<int32_t>(pDouble));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator^=(double const & pDouble)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar ^= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, INT32_MAX))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) ^= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pDouble);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, INT32_MAX))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_EMULATED_INT);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) ^
									static_cast<int32_t>(pDouble));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator^=(bool const & pBool))
		#pragma endregion operator ^= //}
	
		//-----------------------------------

		#pragma region operator >>= //{
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator>>=(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return (*this >>= pVar.gData.uString.uStd.gString);
#else
					bool tIsNullTerminated;
					size_t tLength;
					char const * tChar = pVar.getCharPointerAndInfo(&tLength, &tIsNullTerminated);

					return this->doOperatorLogicBitShiftRightEqual(tChar, (tIsNullTerminated ? (tLength - 1) : tLength));
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (*this >>= pVar.gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (*this >>= CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return this->doOperatorLogicBitShiftRightEqualForEmulatedInt(pVar.gData.uIntegral.uDouble);}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					this->assignPropogateErrorFrom(pVar);

					return *this;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator>>=(::std::string const & pString)
			{return this->doOperatorLogicBitShiftRightEqual(pString.c_str(), pString.size());}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator>>=(char const * pString)
			{return this->doOperatorLogicBitShiftRightEqual(pString, strlen(pString));}
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorLogicBitShiftRightEqual(char const * pChars, size_t pSize)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar >>= static_cast<unsigned char>(tResult);}//LEFT TO C++ STANDARD
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						int _f;
						double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
								StringToDouble(pChars, 
								CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, INT32_MAX))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >>= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(tResult);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						int _f;
						double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
								StringToDouble(pChars, 
								CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, INT32_MAX))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) >>
									static_cast<int32_t>(tResult));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator>>=(char const & pChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					//this->gData.uIntegral.uUnsignedChar &= pChar;
					if((pChar >= '0') && (pChar <= '9'))
						{this->gData.uIntegral.uUnsignedChar >>= (pChar - '0');}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if((pChar >= '0') && (pChar <= '9'))
							{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >>= (pChar - '0');}
						else
							{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0, INT32_MAX))
					{
						if((pChar >= '0') && (pChar <= '9'))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) >>
									static_cast<int32_t>(pChar - '0'));
						}
						else
							{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator>>=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var & Var::operator>>=(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator>>=(unsigned char const & pUnsignedChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					this->gData.uIntegral.uUnsignedChar >>= pUnsignedChar;

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
						{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >>= pUnsignedChar;}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0, INT32_MAX))
					{
						CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
						CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
								static_cast<int32_t>(this->gData.uIntegral.uDouble) >>
								static_cast<int32_t>(pUnsignedChar));
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif				
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator>>=(uint32_t const & pUnsignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(pUnsignedInt32 <= UINT8_MAX)
						{this->gData.uIntegral.uUnsignedChar >>= static_cast<unsigned char>(pUnsignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(pUnsignedInt32 <= INT32_MAX)
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >>= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(pUnsignedInt32 <= INT32_MAX)
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) >>
									static_cast<int32_t>(pUnsignedInt32));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator>>=(int32_t const & pSignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt32 <= UINT8_MAX) && (pSignedInt32 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar >>= static_cast<unsigned char>(pSignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(pSignedInt32 >= 0)
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >>= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(pSignedInt32 >= 0)
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) >> pSignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var & operator>>=(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator>>=(int64_t const & pSignedInt64)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt64 <= UINT8_MAX) && (pSignedInt64 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar >>= static_cast<unsigned char>(pSignedInt64);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= 0))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >>= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt64);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= 0))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) >> pSignedInt64);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorLogicBitShiftRightEqualForEmulatedInt(double const & pDouble)
		{
			CRX__BOOST_ASSERT((pDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
					(pDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE));

			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar >>= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_EMULATED_INT:
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if((pDouble <= INT32_MAX) && (pDouble >= 0))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_EMULATED_INT);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<double>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) >>
									static_cast<int32_t>(pDouble));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator>>=(double const & pDouble)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar >>= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, INT32_MAX))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >>= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pDouble);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, INT32_MAX))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_EMULATED_INT);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) >>
									static_cast<int32_t>(pDouble));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator>>=(bool const & pBool))
		#pragma endregion operator >>= //}
	
		//-----------------------------------

		#pragma region operator <<= //{
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator<<=(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return (*this <<= pVar.gData.uString.uStd.gString);
#else
					bool tIsNullTerminated;
					size_t tLength;
					char const * tChar = pVar.getCharPointerAndInfo(&tLength, &tIsNullTerminated);

					return this->doOperatorLogicBitShiftLeftEqual(tChar, (tIsNullTerminated ? (tLength - 1) : tLength));
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (*this <<= pVar.gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (*this <<= CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return this->doOperatorLogicBitShiftLeftEqualForEmulatedInt(pVar.gData.uIntegral.uDouble);}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
					{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return *this);}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					this->assignPropogateErrorFrom(pVar);

					return *this;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator<<=(::std::string const & pString)
			{return this->doOperatorLogicBitShiftLeftEqual(pString.c_str(), pString.size());}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator<<=(char const * pString)
			{return this->doOperatorLogicBitShiftLeftEqual(pString, strlen(pString));}
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorLogicBitShiftLeftEqual(char const * pChars, size_t pSize)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{this->gData.uIntegral.uUnsignedChar <<= static_cast<unsigned char>(tResult);}//LEFT TO C++ STANDARD
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						int _f;
						double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
								StringToDouble(pChars, 
								CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, INT32_MAX))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <<= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(tResult);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						int _f;
						double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
								StringToDouble(pChars, 
								CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, INT32_MAX))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) |
									static_cast<int32_t>(tResult));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator<<=(char const & pChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					//this->gData.uIntegral.uUnsignedChar &= pChar;
					if((pChar >= '0') && (pChar <= '9'))
						{this->gData.uIntegral.uUnsignedChar <<= (pChar - '0');}
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if((pChar >= '0') && (pChar <= '9'))
							{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <<= (pChar - '0');}
						else
							{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0, INT32_MAX))
					{
						if((pChar >= '0') && (pChar <= '9'))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) <<
									static_cast<int32_t>(pChar - '0'));
						}
						else
							{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator<<=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var & Var::operator<<=(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator<<=(unsigned char const & pUnsignedChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					this->gData.uIntegral.uUnsignedChar <<= pUnsignedChar;

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
						{CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <<= pUnsignedChar;}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0, INT32_MAX))
					{
						CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
						CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
								static_cast<int32_t>(this->gData.uIntegral.uDouble) <<
								static_cast<int32_t>(pUnsignedChar));
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif				
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator<<=(uint32_t const & pUnsignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(pUnsignedInt32 <= UINT8_MAX)
						{this->gData.uIntegral.uUnsignedChar <<= static_cast<unsigned char>(pUnsignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(pUnsignedInt32 <= INT32_MAX)
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <<= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(pUnsignedInt32 <= INT32_MAX)
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) <<
									static_cast<int32_t>(pUnsignedInt32));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator<<=(int32_t const & pSignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt32 <= UINT8_MAX) && (pSignedInt32 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar <<= static_cast<unsigned char>(pSignedInt32);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(pSignedInt32 >= 0)
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <<= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(pSignedInt32 >= 0)
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) << pSignedInt32);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var & operator<<=(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator<<=(int64_t const & pSignedInt64)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt64 <= UINT8_MAX) && (pSignedInt64 >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar <<= static_cast<unsigned char>(pSignedInt64);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= 0))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <<= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt64);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= 0))
						{
							CRX__VAR__SET_TYPE_TO_INTERNAL_INT_TYPE_FROM_DOUBLE(this);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) << pSignedInt64);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PRIVATE CRX__LIB__METHOD() Var & Var::doOperatorLogicBitShiftLeftEqualForEmulatedInt(double const & pDouble)
		{
			CRX__BOOST_ASSERT((pDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
					(pDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE));

			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar <<= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
				case CRX__VAR__TYPE_EMULATED_INT:
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if((pDouble <= INT32_MAX) && (pDouble >= 0))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_EMULATED_INT);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<double>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) <<
									static_cast<int32_t>(pDouble));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
	#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator<<=(double const & pDouble)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{this->gData.uIntegral.uUnsignedChar <<= static_cast<unsigned char>(pDouble);}//LEFT TO C++ STANDARD
					else
						{CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, CRX__VAR__NO_OP_FOR_ERROR);}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, INT32_MAX))
						{
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <<= 
									static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pDouble);
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
					{
						if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, INT32_MAX))
						{
							CRX__VAR__SET_TYPE(this, CRX__VAR__TYPE_EMULATED_INT);
							CRX__VAR__GET_INTERNAL_INT_VARIABLE1(this) = static_cast<CRX__VAR__INTERNAL_INT>(
									static_cast<int32_t>(this->gData.uIntegral.uDouble) <<
									static_cast<int32_t>(pDouble));
						}
						else
						{
							CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
									CRX__VAR__NO_OP_FOR_ERROR);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND, 
								CRX__VAR__NO_OP_FOR_ERROR);
					}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, CRX__VAR__NO_OP_FOR_ERROR);

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			return *this;
		}
		CRX_DISABLED_METHOD(Var & Var::operator<<=(bool const & pBool))
		#pragma endregion operator <<= //}
	
		//-----------------------------------

		#pragma region weakCompareTo //{
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::weakCompareTo(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return this->weakCompareTo(pVar.gData.uString.uStd.gString);
#else
					bool tIsNullTerminated;
					size_t tLength;
					char const * tChar = pVar.getCharPointerAndInfo(&tLength, &tIsNullTerminated);

					return this->weakCompareTo(tChar, (tIsNullTerminated ? (tLength - 1) : tLength));
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return this->weakCompareTo(pVar.gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return this->weakCompareTo(CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
					{return this->weakCompareToEmulatedInt(pVar.gData.uIntegral.uDouble);}
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return this->weakCompareTo(pVar.gData.uIntegral.uDouble);}
				case CRX__VAR__TYPE_BOOL:
					{return this->weakCompareTo(pVar.gData.uIntegral.uBool);}
				case CRX__VAR__TYPE_POINTER:
				{
					return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_POINTER) &&
							this->gData.uPointer.gPointer->isEqualTo(pVar.gData.uPointer.gPointer));
				}
				case CRX__VAR__TYPE_NULL:
					{return CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_NULL;}
				case CRX__VAR__TYPE_UNDEFINED:
					{return CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_UNDEFINED;}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR) &&
							(this->gData.uError.gCode == pVar.gData.uError.gCode));
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::weakCompareTo(::std::string const & pString)
			{return this->weakCompareTo(pString.c_str(), pString.size());}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::weakCompareTo(char const * pString)
			{return this->weakCompareTo(pString, strlen(pString));}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::weakCompareTo(char const * pChars, size_t pSize)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					return (this->development_doStrcmpOnInternalStringAnd(pChars, pSize) == 
							0);
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
							CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
						{return (this->gData.uIntegral.uUnsignedChar == static_cast<unsigned char>(tResult));}
					else
						{return false;}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
					{
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT(pChars, pSize, &tIsError);

						if(!tIsError)
							{return (CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) == tResult);}
						else
							{return false;}
					}
					else
					{
						if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							int _f;
							double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
									StringToDouble(pChars, 
									CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

							if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
							{
								return (static_cast<double>(
										CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this)) == tResult);
							}
							else
								{return false;}
						}
						else
							{return false;}
					}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							if((tResult <= CRX__VAR__INT_STRING_MAX) &&
									(tResult >= CRX__VAR__INT_STRING_MIN))
								{return this->gData.uIntegral.uDouble == tResult;}
							else
								{return false;}
						}
						else
							{return (this->gData.uIntegral.uDouble == tResult);}
					}
					else
						{return false;}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					int _f;
					double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
							StringToDouble(pChars, 
							CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(pSize), &_f);

					if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
					{
						if(Var::isNumberStringAnIntegerIfValid(pChars, pSize))
						{
							if((tResult <= CRX__VAR__INT_STRING_MAX) &&
									(tResult >= CRX__VAR__INT_STRING_MIN) &&
									(tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
									(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
								{return (this->gData.uIntegral.uDouble == tResult);}
							else
								{return false;}
						}
						else
							{return (this->gData.uIntegral.uDouble == tResult);}
					}
					else
						{return false;}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				{
					bool tIsError = false;
					bool tResult = Var::looseConvertStringToBool(pChars, pSize, &tIsError);
					
					return (!tIsError && tResult);
				}
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::weakCompareTo(char const & pChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					char tString[2];

					tString[0] = pChar;
					tString[1] = '\0';

					return (this->development_doStrcmpOnInternalStringAnd(tString, 1) == 0);
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					//LEFT TO C++ STANDARD
					//this->gData.uIntegral.uUnsignedChar < pChar;
					if((pChar >= '0') && (pChar <= '9'))
						{return (this->gData.uIntegral.uUnsignedChar == (pChar - '0'));}
					else
						{return false;}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((pChar >= '0') && (pChar <= '9'))
					{
						return (CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) == 
								static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pChar - '0'));
					}
					else
						{return false;}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pChar >= '0') && (pChar <= '9'))
						{return (this->gData.uIntegral.uDouble == static_cast<double>(pChar - '0'));}
					else
						{return false;}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::weakCompareTo(unsigned char const & pUnsignedChar)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR] /*= ?*/;

					return (this->development_doStrcmpOnInternalStringAnd(tChars, 
							Var::stringifyUnsignedInt32AndGetSize(pUnsignedChar, tChars, 
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR)) == 0);
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (this->gData.uIntegral.uUnsignedChar == pUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					return (CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) == 
							static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pUnsignedChar));
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (this->gData.uIntegral.uDouble == static_cast<double>(pUnsignedChar));}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::weakCompareTo(uint32_t const & pUnsignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					if(pUnsignedInt32 <= CRX__VAR__INTERNAL_INT_MAX)
					{
						char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_INT32];

						return (this->development_doStrcmpOnInternalStringAnd(tChars, 
								Var::stringifyUnsignedInt32AndGetSize(pUnsignedInt32, tChars, 
										CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_INT32)) == 0);
					}
					else
						{return false;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(pUnsignedInt32 <= UINT8_MAX)
						{return (this->gData.uIntegral.uUnsignedChar == static_cast<unsigned char>(pUnsignedInt32));}
					else
						{return false;}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					return (this->gData.uIntegral.uSignedInt64 == static_cast<int64_t>(pUnsignedInt32));
	#else
					if((pUnsignedInt32 <= INT32_MAX) && (pUnsignedInt32 >= INT32_MIN))
						{return (this->gData.uIntegral.uSignedInt32 == static_cast<int32_t>(pUnsignedInt32));}
					else
						{return false;}
	#endif
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pUnsignedInt32 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pUnsignedInt32 >= CRX__VAR__INTERNAL_INT_MIN))
						{return (this->gData.uIntegral.uDouble == static_cast<double>(pUnsignedInt32));}
					else
						{return false;}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::weakCompareTo(int32_t const & pSignedInt32)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT32];

					return (this->development_doStrcmpOnInternalStringAnd(tChars, 
							Var::stringifyInt32AndGetSize(pSignedInt32, tChars, 
									CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT32)) == 0);
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt32 <= UINT8_MAX) && (pSignedInt32 >= 0)/*UINT8_MIN*/)
						{return (this->gData.uIntegral.uUnsignedChar == static_cast<unsigned char>(pSignedInt32));}
					else
						{return false;}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) == static_cast<CRX__VAR__UNIFIED_SIGNED_INT>(pSignedInt32));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (this->gData.uIntegral.uDouble == static_cast<double>(pSignedInt32));}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::weakCompareTo(int64_t const & pSignedInt64)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) &&
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN))
					{
						char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT64];

						return (this->development_doStrcmpOnInternalStringAnd(tChars, 
								Var::stringifyInt64AndGetSize(pSignedInt64, tChars, 
										CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT64)) == 0);
					}
					else
						{return false;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pSignedInt64 <= UINT8_MAX) && (pSignedInt64 >= 0)/*UINT8_MIN*/)
						{return (this->gData.uIntegral.uUnsignedChar == static_cast<unsigned char>(pSignedInt64));}
					else
						{return false;}
				}
	#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
		#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					return (this->gData.uIntegral.uSignedInt64 == pSignedInt64);
		#else
					if((pSignedInt64 <= INT32_MAX) && (pSignedInt64 >= INT32_MIN))
						{return (this->gData.uIntegral.uSignedInt32 == static_cast<int32_t>(pSignedInt64));}
					else
						{return false;}
		#endif
				}
	#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN))
						{return (this->gData.uIntegral.uDouble == static_cast<double>(pSignedInt64));}
					else
						{return false;}
				}
	#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if((pSignedInt64 <= CRX__VAR__INTERNAL_INT_MAX) && 
							(pSignedInt64 >= CRX__VAR__INTERNAL_INT_MIN) &&
							(pSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(pSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{return (this->gData.uIntegral.uDouble == static_cast<double>(pSignedInt64));}
					else
						{return false;}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
	#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
#endif;
#if(CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PRIVATE CRX__LIB__METHOD() bool Var::weakCompareToEmulatedInt(double const & pDouble)
		{
			CRX__BOOST_ASSERT((pDouble <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
					(pDouble >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE));

			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT];

					return (this->development_doStrcmpOnInternalStringAnd(tChars, 
							Var::stringifyEmulatedIntAndGetSize(pDouble, tChars, 
									CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT)) == 0);
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if((pDouble <= UINT8_MAX) && (pDouble >= 0)/*UINT8_MIN*/)
						{return (this->gData.uIntegral.uUnsignedChar == static_cast<unsigned char>(pDouble));}
					else
						{return false;}
				}
				case CRX__VAR__TYPE_EMULATED_INT:
				case CRX__VAR__TYPE_DOUBLE:
					{return (this->gData.uIntegral.uDouble == pDouble);}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
	#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::weakCompareTo(double const & pDouble)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE] /*= ?*/;
					::double_conversion::StringBuilder tStringBuilder(tChars,
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE) /*= ...*/;
					size_t tLength /*= ?*/;

					Var::StaticPrivateVars::gDoubleToStringConverter->ToShortest(pDouble, 
							&tStringBuilder);

					tLength = tStringBuilder.position();
					
					return (this->development_doStrcmpOnInternalStringAnd(tStringBuilder.Finalize(), 
							tLength) == 0);
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pDouble, 0, UINT8_MAX))
						{return (this->gData.uIntegral.uUnsignedChar == static_cast<unsigned char>(pDouble));}
					else
						{return false;}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
	#if(CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
					if((this->gData.uIntegral.uSignedInt64 <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
							(this->gData.uIntegral.uSignedInt64 >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{return (static_cast<double>(this->gData.uIntegral.uSignedInt64) == pDouble);}
					else
						{return false;}
	#else
					return (static_cast<double>(this->gData.uIntegral.uSignedInt32) == pDouble);
	#endif
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (this->gData.uIntegral.uDouble == pDouble);}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::weakCompareTo(bool const & pBool)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					if(pBool)
						{return (this->development_doStrcmpOnInternalStringAnd("TRUE", 4) == 0);}
					else
						{return (this->development_doStrcmpOnInternalStringAnd("FALSE", 5) == 0);}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return false;}
				case CRX__VAR__TYPE_BOOL:
					{return (this->gData.uIntegral.uBool == pBool);}
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		#pragma endregion weakCompareTo //}

		//-----------------------------------

		#pragma region operator + //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator+(Var const & pVar)
		{
			Var vReturn(*this);

			vReturn += pVar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator+(::std::string const & pString)	
		{
			Var vReturn(*this);

			vReturn += pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator+(char const * pString)
		{
			Var vReturn(*this);

			vReturn += pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator+(char const & pChar)
		{
			Var vReturn(*this);

			vReturn += vReturn;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator+(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap)
		{
			Var vReturn(*this);

			vReturn += pUnorderedMap;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator+(::std::deque<Var> & pDeque)
		{
			Var vReturn(*this);

			vReturn += pDeque;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator+(unsigned char const & pUnsignedChar)
		{
			Var vReturn(*this);

			vReturn += pUnsignedChar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator+(uint32_t const & pUnsignedInt32)
		{
			Var vReturn(*this);

			vReturn += pUnsignedInt32;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator+(int32_t const & pSignedInt32)
		{
			Var vReturn(*this);

			vReturn += pSignedInt32;

			return vReturn;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var Var::operator+(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator+(int64_t const & pSignedInt64)
		{
			Var vReturn(*this);

			vReturn += pSignedInt64;

			return vReturn;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator+(double const & pDouble)
		{
			Var vReturn(*this);

			vReturn += pDouble;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator+(bool const & pBool)
		{
			Var vReturn(*this);

			vReturn += pBool;

			return vReturn;
		}
		#pragma endregion operator + //}
			
		//-----------------------------------

		#pragma region operator - //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator-(Var const & pVar)
		{
			Var vReturn(*this);

			vReturn -= pVar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator-(::std::string const & pString)	
		{
			Var vReturn(*this);

			vReturn -= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator-(char const * pString)
		{
			Var vReturn(*this);

			vReturn -= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator-(char const & pChar)
		{
			Var vReturn(*this);

			vReturn -= pChar;

			return vReturn;
		}
		CRX_DISABLED_METHOD(Var operator-(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var operator-(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator-(unsigned char const & pUnsignedChar)
		{
			Var vReturn(*this);

			vReturn -= pUnsignedChar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator-(uint32_t const & pUnsignedInt32)
		{
			Var vReturn(*this);

			vReturn -= pUnsignedInt32;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator-(int32_t const & pSignedInt32)
		{
			Var vReturn(*this);

			vReturn -= pSignedInt32;

			return vReturn;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var Var::operator-(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator-(int64_t const & pSignedInt64)
		{
			Var vReturn(*this);

			vReturn -= pSignedInt64;

			return vReturn;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator-(double const & pDouble)
		{
			Var vReturn(*this);

			vReturn -= pDouble;

			return vReturn;
		}
		CRX_DISABLED_METHOD(Var Var::operator-(bool const & pBool))
		#pragma endregion operator - //}

		//-----------------------------------

		#pragma region operator * //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator*(Var const & pVar)
		{
			Var vReturn(*this);

			vReturn *= pVar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator*(::std::string const & pString)	
		{
			Var vReturn(*this);

			vReturn *= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator*(char const * pString)
		{
			Var vReturn(*this);

			vReturn *= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator*(char const & pChar)
		{
			Var vReturn(*this);

			vReturn *= pChar;

			return vReturn;
		}
		CRX_DISABLED_METHOD(Var operator*(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var operator*(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator*(unsigned char const & pUnsignedChar)
		{
			Var vReturn(*this);

			vReturn *= pUnsignedChar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator*(uint32_t const & pUnsignedInt32)
		{
			Var vReturn(*this);

			vReturn *= pUnsignedInt32;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator*(int32_t const & pSignedInt32)
		{
			Var vReturn(*this);

			vReturn *= pSignedInt32;

			return vReturn;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var Var::operator*(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator*(int64_t const & pSignedInt64)
		{
			Var vReturn(*this);

			vReturn *= pSignedInt64;

			return vReturn;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator*(double const & pDouble)
		{
			Var vReturn(*this);

			vReturn *= pDouble;

			return vReturn;
		}
		CRX_DISABLED_METHOD(Var Var::operator*(bool const & pBool))
		#pragma endregion operator * //}

		//-----------------------------------

		#pragma region operator / //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator/(Var const & pVar)
		{
			Var vReturn(*this);

			vReturn /= pVar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator/(::std::string const & pString)	
		{
			Var vReturn(*this);

			vReturn /= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator/(char const * pString)
		{
			Var vReturn(*this);

			vReturn /= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator/(char const & pChar)
		{
			Var vReturn(*this);

			vReturn /= pChar;

			return vReturn;
		}
		CRX_DISABLED_METHOD(Var Var::operator/(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var Var::operator/(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator/(unsigned char const & pUnsignedChar)
		{
			Var vReturn(*this);

			vReturn /= pUnsignedChar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator/(uint32_t const & pUnsignedInt32)
		{
			Var vReturn(*this);

			vReturn /= pUnsignedInt32;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator/(int32_t const & pSignedInt32)
		{
			Var vReturn(*this);

			vReturn /= pSignedInt32;

			return vReturn;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var Var::operator/(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator/(int64_t const & pSignedInt64)
		{
			Var vReturn(*this);

			vReturn /= pSignedInt64;

			return vReturn;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator/(double const & pDouble)
		{
			Var vReturn(*this);

			vReturn /= pDouble;

			return vReturn;
		}
		CRX_DISABLED_METHOD(Var Var::operator/(bool const & pBool))
		#pragma endregion operator - //}

		//-----------------------------------

		#pragma region operator % //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator%(Var const & pVar)
		{
			Var vReturn(*this);

			vReturn %= pVar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator%(::std::string const & pString)	
		{
			Var vReturn(*this);

			vReturn %= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator%(char const * pString)
		{
			Var vReturn(*this);

			vReturn %= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator%(char const & pChar)
		{
			Var vReturn(*this);

			vReturn %= pChar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator%(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap)
		{
			Var vReturn(*this);

			vReturn %= pUnorderedMap;

			return vReturn;
		}
		CRX_DISABLED_METHOD(Var Var::operator%(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator%(unsigned char const & pUnsignedChar)
		{
			Var vReturn(*this);

			vReturn %= pUnsignedChar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator%(uint32_t const & pUnsignedInt32)
		{
			Var vReturn(*this);

			vReturn %= pUnsignedInt32;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator%(int32_t const & pSignedInt32)
		{
			Var vReturn(*this);

			vReturn %= pSignedInt32;

			return vReturn;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var Var::operator%(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator%(int64_t const & pSignedInt64)
		{
			Var vReturn(*this);

			vReturn %= pSignedInt64;

			return vReturn;
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator%(double const & pDouble)
		{
			Var vReturn(*this);

			vReturn %= pDouble;

			return vReturn;
		}
		CRX_DISABLED_METHOD(Var Var::operator%(bool const & pBool))
		#pragma endregion operator % //}

		//-----------------------------------

		#pragma region operator <= //{
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator<=(Var const & pVar)
			{return !(*this > pVar);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator<=(::std::string const & pString)
			{return !(*this > pString);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator<=(char const * pString)
			{return !(*this > pString);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator<=(char const & pChar)
			{return !(*this > pChar);}
		CRX_DISABLED_METHOD(bool Var::operator<=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(bool Var::operator<=(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator<=(unsigned char const & pUnsignedChar)
			{return !(*this > pUnsignedChar);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator<=(uint32_t const & pUnsignedInt32)
			{return !(*this > pUnsignedInt32);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator<=(int32_t const & pSignedInt32)
			{return !(*this > pSignedInt32);}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(bool Var::operator<=(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator<=(int64_t const & pSignedInt64)
			{return !(*this > pSignedInt64);}
#endif;
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator<=(double const & pDouble)
			{return !(*this > pDouble);}
		CRX_DISABLED_METHOD(bool Var::operator<=(bool const & pBool))
		#pragma endregion operator <= //}
		
		//-----------------------------------

		#pragma region operator >= //{
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator>=(Var const & pVar)
			{return !(*this < pVar);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator>=(::std::string const & pString)
			{return !(*this < pString);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator>=(char const * pString)
			{return !(*this < pString);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator>=(char const & pChar)
			{return !(*this < pChar);}
		CRX_DISABLED_METHOD(bool Var::operator>=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(bool Var::operator>=(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator>=(unsigned char const & pUnsignedChar)
			{return !(*this < pUnsignedChar);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator>=(uint32_t const & pUnsignedInt32)
			{return !(*this < pUnsignedInt32);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator>=(int32_t const & pSignedInt32)
			{return !(*this < pSignedInt32);}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(bool Var::operator>=(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator>=(int64_t const & pSignedInt64)
			{return !(*this < pSignedInt64);}
#endif;
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator>=(double const & pDouble)
			{return !(*this < pDouble);}
		CRX_DISABLED_METHOD(bool Var::operator>=(bool const & pBool))
		#pragma endregion operator >= //}
	
		//-----------------------------------

		#pragma region operator & //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator&(Var const & pVar)
		{
			Var vReturn(*this);

			vReturn &= pVar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator&(::std::string const & pString)	
		{
			Var vReturn(*this);

			vReturn &= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator&(char const * pString)
		{
			Var vReturn(*this);

			vReturn &= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator&(char const & pChar)
		{
			Var vReturn(*this);

			vReturn &= pChar;

			return vReturn;
		}
		CRX_DISABLED_METHOD(Var Var::operator&(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var Var::operator&(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator&(unsigned char const & pUnsignedChar)
		{
			Var vReturn(*this);

			vReturn &= pUnsignedChar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator&(uint32_t const & pUnsignedInt32)
		{
			Var vReturn(*this);

			vReturn &= pUnsignedInt32;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator&(int32_t const & pSignedInt32)
		{
			Var vReturn(*this);

			vReturn &= pSignedInt32;

			return vReturn;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var Var::operator&(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator&(int64_t const & pSignedInt64)
		{
			Var vReturn(*this);

			vReturn &= pSignedInt64;

			return vReturn;
		}
#endif
		CRX_DISABLED_METHOD(Var Var::operator&(float const & pFloat))
		CRX_DISABLED_METHOD(Var Var::operator&(double const & pDouble))
		CRX_DISABLED_METHOD(Var Var::operator&(bool const & pBool))
		#pragma endregion operator & //}

		//-----------------------------------

		#pragma region operator | //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator|(Var const & pVar)
		{
			Var vReturn(*this);

			vReturn |= pVar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator|(::std::string const & pString)	
		{
			Var vReturn(*this);

			vReturn |= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator|(char const * pString)
		{
			Var vReturn(*this);

			vReturn |= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator|(char const & pChar)
		{
			Var vReturn(*this);

			vReturn |= pChar;

			return vReturn;
		}
		CRX_DISABLED_METHOD(Var Var::operator|(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var Var::operator|(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator|(unsigned char const & pUnsignedChar)
		{
			Var vReturn(*this);

			vReturn |= pUnsignedChar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator|(uint32_t const & pUnsignedInt32)
		{
			Var vReturn(*this);

			vReturn |= pUnsignedInt32;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator|(int32_t const & pSignedInt32)
		{
			Var vReturn(*this);

			vReturn |= pSignedInt32;

			return vReturn;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var Var::operator|(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator|(int64_t const & pSignedInt64)
		{
			Var vReturn(*this);

			vReturn |= pSignedInt64;

			return vReturn;
		}
#endif
		CRX_DISABLED_METHOD(Var Var::operator|(float const & pFloat))
		CRX_DISABLED_METHOD(Var Var::operator|(double const & pDouble))
		CRX_DISABLED_METHOD(Var Var::operator|(bool const & pBool))
		#pragma endregion operator | //}

		//-----------------------------------

		#pragma region operator ^ //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator^(Var const & pVar)
		{
			Var vReturn(*this);

			vReturn ^= pVar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator^(::std::string const & pString)	
		{
			Var vReturn(*this);

			vReturn ^= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator^(char const * pString)
		{
			Var vReturn(*this);

			vReturn ^= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator^(char const & pChar)
		{
			Var vReturn(*this);

			vReturn ^= pChar;

			return vReturn;
		}
		CRX_DISABLED_METHOD(Var Var::operator^(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var Var::operator^(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator^(unsigned char const & pUnsignedChar)
		{
			Var vReturn(*this);

			vReturn ^= pUnsignedChar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator^(uint32_t const & pUnsignedInt32)
		{
			Var vReturn(*this);

			vReturn ^= pUnsignedInt32;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator^(int32_t const & pSignedInt32)
		{
			Var vReturn(*this);

			vReturn ^= pSignedInt32;

			return vReturn;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var operator^(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator^(int64_t const & pSignedInt64)
		{
			Var vReturn(*this);

			vReturn ^= pSignedInt64;

			return vReturn;
		}
#endif
		CRX_DISABLED_METHOD(Var Var::operator^(float const & pFloat))
		CRX_DISABLED_METHOD(Var Var::operator^(double const & pDouble))
		CRX_DISABLED_METHOD(Var Var::operator^(bool const & pBool))
		#pragma endregion operator ^ //}

		//-----------------------------------

		#pragma region operator >> //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>>(Var const & pVar)
		{
			Var vReturn(*this);

			vReturn >>= pVar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>>(::std::string const & pString)	
		{
			Var vReturn(*this);

			vReturn >>= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>>(char const * pString)
		{
			Var vReturn(*this);

			vReturn >>= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>>(char const & pChar)
		{
			Var vReturn(*this);

			vReturn >>= pChar;

			return vReturn;
		}
		CRX_DISABLED_METHOD(Var Var::operator>>(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var Var::operator>>(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>>(unsigned char const & pUnsignedChar)
		{
			Var vReturn(*this);

			vReturn >>= pUnsignedChar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>>(uint32_t const & pUnsignedInt32)
		{
			Var vReturn(*this);

			vReturn >>= pUnsignedInt32;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>>(int32_t const & pSignedInt32)
		{
			Var vReturn(*this);

			vReturn >>= pSignedInt32;

			return vReturn;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var operator>>(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator>>(int64_t const & pSignedInt64)
		{
			Var vReturn(*this);

			vReturn >>= pSignedInt64;

			return vReturn;
		}
#endif
		CRX_DISABLED_METHOD(Var Var::operator>>(float const & pFloat))
		CRX_DISABLED_METHOD(Var Var::operator>>(double const & pDouble))
		CRX_DISABLED_METHOD(Var Var::operator>>(bool const & pBool))
		#pragma endregion operator >> //}

		//-----------------------------------

		#pragma region operator << //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<<(Var const & pVar)
		{
			Var vReturn(*this);

			vReturn <<= pVar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<<(::std::string const & pString)	
		{
			Var vReturn(*this);

			vReturn <<= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<<(char const * pString)
		{
			Var vReturn(*this);

			vReturn <<= pString;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<<(char const & pChar)
		{
			Var vReturn(*this);

			vReturn <<= pChar;

			return vReturn;
		}
		CRX_DISABLED_METHOD(Var Var::operator<<(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var Var::operator<<(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<<(unsigned char const & pUnsignedChar)
		{
			Var vReturn(*this);

			vReturn <<= pUnsignedChar;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<<(uint32_t const & pUnsignedInt32)
		{
			Var vReturn(*this);

			vReturn <<= pUnsignedInt32;

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<<(int32_t const & pSignedInt32)
		{
			Var vReturn(*this);

			vReturn <<= pSignedInt32;

			return vReturn;
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var Var::operator<<(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator<<(int64_t const & pSignedInt64)
		{
			Var vReturn(*this);

			vReturn <<= pSignedInt64;

			return vReturn;
		}
#endif
		CRX_DISABLED_METHOD(Var Var::operator<<(float const & pFloat))
		CRX_DISABLED_METHOD(Var Var::operator<<(double const & pDouble))
		CRX_DISABLED_METHOD(Var Var::operator<<(bool const & pBool))
		#pragma endregion operator << //}

		//-----------------------------------

		#pragma region operator == //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator==(Var const & pVar)
		{
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__GET_TYPE2(pVar)) &&
					this->weakCompareTo(pVar));
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator==(::std::string const & pString)
		{
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING) &&
					this->weakCompareTo(pString));
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator==(char const * pString)
		{
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING) &&
					this->weakCompareTo(pString));
		}
		CRX_PRIVATE CRX__LIB__METHOD() Var Var::doOperatorEqual(char const * pChars, size_t pSize)
		{
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING) &&
					this->weakCompareTo(pChars, pSize));
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator==(char const & pChar)
		{
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING) &&
					this->weakCompareTo(pChar));
		}
		CRX_DISABLED_METHOD(Var Var::operator==(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(Var Var::operator==(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator==(unsigned char const & pUnsignedChar)
		{
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_UNSIGNED_CHAR) &&
					this->weakCompareTo(pUnsignedChar));
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator==(uint32_t const & pUnsignedInt32)
		{
			unsigned char vType = CRX__VAR__GET_TYPE1(this);

#if(!CRX__VAR__IS_EMULATED_INT_USED)
			return (((vType == CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32) ||
					(vType == CRX__VAR__TYPE_DOUBLE)) && this->weakCompareTo(pUnsignedInt32));
#else
			return (((vType == CRX__VAR__TYPE_EMULATED_INT) ||
					(vType == CRX__VAR__TYPE_DOUBLE)) && this->weakCompareTo(pUnsignedInt32));
#endif
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator==(int32_t const & pSignedInt32)
		{
			unsigned char vType = CRX__VAR__GET_TYPE1(this);

#if(!CRX__VAR__IS_EMULATED_INT_USED)
			return (((vType == CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32) ||
					(vType == CRX__VAR__TYPE_DOUBLE)) && this->weakCompareTo(pSignedInt32));
#else
			return (((vType == CRX__VAR__TYPE_EMULATED_INT) ||
					(vType == CRX__VAR__TYPE_DOUBLE)) && this->weakCompareTo(pSignedInt32));
#endif
		}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var Var::operator==(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator==(int64_t const & pSignedInt64)
		{
			unsigned char vType = CRX__VAR__GET_TYPE1(this);

	#if(!CRX__VAR__IS_EMULATED_INT_USED)
			return (((vType == CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32) ||
					(vType == CRX__VAR__TYPE_DOUBLE)) && this->weakCompareTo(pSignedInt64));
	#else
			return (((vType == CRX__VAR__TYPE_EMULATED_INT) ||
					(vType == CRX__VAR__TYPE_DOUBLE)) && this->weakCompareTo(pSignedInt64));
	#endif
		}
#endif;
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator==(double const & pDouble)
		{
			unsigned char vType = CRX__VAR__GET_TYPE1(this);

#if(!CRX__VAR__IS_EMULATED_INT_USED)
			return (((vType == CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32) ||
					(vType == CRX__VAR__TYPE_DOUBLE)) && this->weakCompareTo(pDouble));
#else
			return (((vType == CRX__VAR__TYPE_EMULATED_INT) ||
					(vType == CRX__VAR__TYPE_DOUBLE)) && this->weakCompareTo(pDouble));
#endif
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator==(bool const & pBool)
		{
			unsigned char vType = CRX__VAR__GET_TYPE1(this);

#if(!CRX__VAR__IS_EMULATED_INT_USED)
			return (((vType == CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32) ||
					(vType == CRX__VAR__TYPE_DOUBLE)) && this->weakCompareTo(pBool));
#else
			return (((vType == CRX__VAR__TYPE_EMULATED_INT) ||
					(vType == CRX__VAR__TYPE_DOUBLE)) && this->weakCompareTo(pBool));
#endif
		}
		#pragma endregion operator == //}

		//-----------------------------------

		#pragma region operator != //{
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator!=(Var const & pVar)
		{
			switch(CRX__VAR__GET_TYPE2(pVar))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return (*this !=(pVar.gData.uString.uStd.gString));
#else
					bool tIsNullTerminated;
					size_t tLength;
					char const * tChar = pVar.getCharPointerAndInfo(&tLength, &tIsNullTerminated);

					return !this->doOperatorEqual(tChar, (tIsNullTerminated ? (tLength - 1) : tLength));
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION, return false);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return (*this != pVar.gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return (*this != CRX__VAR__GET_UNIFIED_INT_VARIABLE2(pVar));}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return (*this != pVar.gData.uIntegral.uDouble);}
				case CRX__VAR__TYPE_BOOL:
					{return (*this != pVar.gData.uIntegral.uBool);}
				case CRX__VAR__TYPE_NULL:
					{return CRX__VAR__GET_TYPE2(pVar) != CRX__VAR__TYPE_NULL;}
				default:
					return false;
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator!=(::std::string const & pString)
			{return !(*this == pString);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator!=(char const * pString)
			{return !(*this == pString);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator!=(char const & pChar)
			{return !(*this == pChar);}
		CRX_DISABLED_METHOD(bool Var::operator!=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap))
		CRX_DISABLED_METHOD(bool Var::operator!=(::std::deque<Var> & pDeque))
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator!=(unsigned char const & pUnsignedChar)
			{return !(*this == pUnsignedChar);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator!=(uint32_t const & pUnsignedInt32)
			{return !(*this == pUnsignedInt32);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator!=(int32_t const & pSignedInt32)
			{return !(*this == pSignedInt32);}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(bool Var::operator!=(uint64_t const & pUnsignedInt64))
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator!=(int64_t const & pSignedInt64)
			{return !(*this == pSignedInt64);}
#endif;
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator!=(double const & pDouble)
			{return !(*this == pDouble);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator!=(bool const & pBool)
			{return !(*this == pBool);}
		#pragma endregion operator != //}

		//-----------------------------------

		#pragma region operator ++ //{
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator++()
	    {
			this->operator+=(1);

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator++(int)
		{
			Var vVar(*this);

			this->operator+=(1);

			return vVar;   // return old value
		}
		#pragma endregion operator ++ //}

		//-----------------------------------

		#pragma region operator -- //{
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator--()
	    {
			this->operator-=(1);

			return *this;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator--(int)
		{
			Var vVar(*this);

			this->operator-=(1);

			return vVar;   // return old value
		}
		#pragma endregion operator -- //}

		//-----------------------------------

		#pragma region operator ~ //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator~()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION,
							return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return ~this->gData.uIntegral.uUnsignedChar;}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= INT32_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
						{return ~CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this);}
					else
					{
						Var tReturn;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND,
								return tReturn);
					}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					Var tReturn /*= ?*/;

					if((this->gData.uIntegral.uDouble >= 0) && (this->gData.uIntegral.uDouble <= INT32_MAX))
					{
						CRX__VAR__SET_TYPE2(tReturn, CRX__VAR__TYPE_EMULATED_INT);

						tReturn.gData.uIntegral.uDouble = static_cast<double>(
								~(static_cast<int32_t>(this->gData.uIntegral.uDouble)));

						return tReturn;
					}
					else
					{
						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND,
								return tReturn);
					}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 0,
							INT32_MAX))
						{return ~(static_cast<int32_t>(this->gData.uIntegral.uDouble));}
					else
					{
						Var tReturn;

						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__INVALID_OPERAND,
								return tReturn);
					}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION,
							return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		#pragma endregion operator ~ //}
	
		//-----------------------------------

		#pragma region operator + (unary) //{
		/*THIS OPERATOR WILL NOT BE DEFINED*/
		#pragma endregion operator + (unary) //}

		//-----------------------------------

		#pragma region operator - (unary) //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::operator-()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION,
							return tReturn);
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return -this->gData.uIntegral.uUnsignedChar;}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
					{return -CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this);}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					Var tReturn /*= ?*/;

					CRX__VAR__SET_TYPE2(tReturn, CRX__VAR__TYPE_EMULATED_INT);

					tReturn.gData.uIntegral.uDouble = -this->gData.uIntegral.uDouble;

					return tReturn;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return -this->gData.uIntegral.uDouble;}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn;

					CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__ILLEGAL_OPERATION,
							return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return *this;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return *this;}
			}
		}
		#pragma endregion operator - (unary) //}
	
		//-----------------------------------

		#pragma region operator && //{
		/*ORIGINALLY: "THIS OPERATOR WILL NOT BE EXPLICITLY DEFINED, HOWEVER SHOULD SILL WORK"
				HOWEVER, DECIDED TO DEFINE THESE FOR THE BENEFIT OF VC6 AND POSSIBLY OTHER COMPILERS.
		*/
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator&&(Var const & pVar)
			/*VC6 {return (static_cast<bool>(*this) && static_cast<bool>(pVar));}*/
			{return !!(*this) && !!pVar;}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator&&(bool const & pBool)
			/*VC6 {return (static_cast<bool>(*this) && pBool);}*/
			{return !!(*this) && pBool;}
		#pragma endregion operator && //}

		//-----------------------------------

		#pragma region operator || //{
		/*ORIGINALLY: "THIS OPERATOR WILL NOT BE EXPLICITLY DEFINED, HOWEVER SHOULD SILL WORK"
				HOWEVER, DECIDED TO DEFINE THESE FOR THE BENEFIT OF VC6 AND POSSIBLY OTHER COMPILERS.
		*/
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator||(Var const & pVar)
			/*VC6 {return (static_cast<bool>(*this) || static_cast<bool>(pVar));}*/
			{return !!(*this) || !!pVar;}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::operator||(bool const & pBool)
			/*VC6 {return (static_cast<bool>(*this) || pBool);}*/
			{return !!(*this) || pBool;}
		#pragma endregion operator || //}

		//-----------------------------------

		#pragma region operator [] //{
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator[](::std::size_t pIndex)
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY)
			{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
				if(pIndex < this->gData.uArray.gDeque->size())
					{return this->gData.uArray.gDeque->operator[](pIndex);}
				else
				{
	#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__SWALLOW)
					if(this->gData.uArray.gDeque->size() > 0)
						{return this->gData.uArray.gDeque->operator[](this->gData.uArray.gDeque->size() - 1);}
					else
					{
						this->gData.uArray.gDeque->push(Var::Nil());

						return this->gData.uArray.gDeque->operator[](0);
					}
	#else
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INDEX_OUT_OF_BOUNDS,
							CRX__VAR__NO_OP_FOR_ERROR);

					return *this;
	#endif
				}
#else
				if(pIndex < crx_varRing_getLength(CRX__VAR__GET_VARRING(this)))
					{return *(crx_varRing_get(CRX__VAR__GET_VARRING(this), pIndex));}
				else
				{
	#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__SWALLOW)
					if(crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) > 0)
						{return *(crx_varRing_get(CRX__VAR__GET_VARRING(this), crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) - 1));}
					else
					{
						Var tVar = Var::Nil();

						crx_varRing_push(CRX__VAR__GET_VARRING(this), &tVar);

						return *(crx_varRing_get(CRX__VAR__GET_VARRING(this), 0));
					}
	#else
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INDEX_OUT_OF_BOUNDS,
							CRX__VAR__NO_OP_FOR_ERROR);

					return *this;
	#endif
				}
#endif
			}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			else if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR)
				{return *this;}
#endif
			else
			{
				CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
						CRX__VAR__NO_OP_FOR_ERROR);

				return *this;
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var const & Var::operator[](::std::size_t pIndex) const
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY)
			{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
				if(pIndex < this->gData.uArray.gDeque->size())
					{return this->gData.uArray.gDeque->operator[](pIndex);}
				else
				{
	#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__SWALLOW)
					if(this->gData.uArray.gDeque->size() > 0)
						{return this->gData.uArray.gDeque->operator[](this->gData.uArray.gDeque->size() - 1);}
					else
						{CRX__VAR__GUARD(false); return *this;}
	#elif(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
					CRX__VAR__GUARD(false); return *this;
	#else
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INDEX_OUT_OF_BOUNDS,
							CRX__VAR__NO_OP_FOR_ERROR);

					return *this;
	#endif
				}
#else
				if(pIndex < crx_varRing_getLength(CRX__VAR__GET_VARRING(this)))
					{return *(crx_varRing_constantGet(CRX__VAR__GET_VARRING(this), pIndex));}
				else
				{
	#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__SWALLOW)
					if(crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) > 0)
						{return *(crx_varRing_constantGet(CRX__VAR__GET_VARRING(this), crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) - 1));}
					else
						{CRX__VAR__GUARD(false); return *this;}
	#elif(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
					CRX__VAR__GUARD(false); return *this;
	#else
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INDEX_OUT_OF_BOUNDS,
							CRX__VAR__NO_OP_FOR_ERROR);

					return *this;
	#endif
				}
#endif
			}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			else if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR)
				{return *this;}
#endif
			else
			{
#if(CRX__VAR__ERROR_MODE != CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
				CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
						CRX__VAR__NO_OP_FOR_ERROR);

				return *this;
#else
				CRX__VAR__GUARD(false); return *this;
#endif
			}
		}

#if(CRX__VAR__IS_MACHINE_64BIT)
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator[](unsigned int pIndex)
			{return this->operator[](static_cast<size_t>(pIndex));}
		CRX_PUBLIC CRX__LIB__METHOD() Var const & Var::operator[](unsigned int pIndex) const
			{return this->operator[](static_cast<size_t>(pIndex));}
#endif

		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator[](::std::string const & pKey)
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE)
			{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
				return this->gData.uHashTable.gUnorderedMap->operator[](pKey);
#else
				Var * vVar = NULL;
					
				CRX__VAR__KHash_forceGet(this->gData.uHashTable.gKHash, vVar, pKey.c_str(),
						CRX__VAR__GET_IS_THREAD_POSSIBLE1(this));

				return (*vVar);
#endif
			}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			else if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR)
				{return *this;}
#endif
			else
			{
				CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
						CRX__VAR__NO_OP_FOR_ERROR);

				return *this;
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var const & Var::operator[](::std::string const & pKey) const
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE)
			{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
				if(this->gData.uHashTable.gUnorderedMap->count(pKey) == 1)
					{return this->gData.uHashTable.gUnorderedMap->operator[](pKey);}
				else
				{
	#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__SWALLOW)
					CRX__VAR__GUARD(false); return *this;
	#elif(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
					CRX__VAR__GUARD(false); return *this;
	#else
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INDEX_OUT_OF_BOUNDS,
							CRX__VAR__NO_OP_FOR_ERROR);

					return *this;
	#endif
				}
#else
				if(CRX__VAR__KHASH__HAS_KEY(this->gData.uHashTable.gKHash, pKey.c_str()))
				{
					Var * vVar = NULL;
					
					CRX__VAR__KHash_forceGet(this->gData.uHashTable.gKHash, vVar, pKey.c_str(),
							CRX__VAR__GET_IS_THREAD_POSSIBLE1(this));

					return (*vVar);
				}
				else
				{
	#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__SWALLOW)
					CRX__VAR__GUARD(false); return *this;
	#elif(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
					CRX__VAR__GUARD(false); return *this;
	#else
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INDEX_OUT_OF_BOUNDS,
							CRX__VAR__NO_OP_FOR_ERROR);

					return *this;
	#endif
				}
#endif
			}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			else if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR)
				{return *this;}
#endif
			else
			{
#if(CRX__VAR__ERROR_MODE != CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
				CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
						CRX__VAR__NO_OP_FOR_ERROR);

				return *this;
#else
				CRX__VAR__GUARD(false); return *this;
#endif
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator[](char const * pKey)
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE)
			{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
				return this->gData.uHashTable.gUnorderedMap->operator[](pKey);
#else
				Var * vVar = NULL;

				CRX__VAR__KHash_forceGet(this->gData.uHashTable.gKHash, vVar, pKey,
						CRX__VAR__GET_IS_THREAD_POSSIBLE1(this));

				return (*vVar);
#endif
			}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			else if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR)
				{return *this;}
#endif
			else
			{
				CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
						CRX__VAR__NO_OP_FOR_ERROR);

				return *this;
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var const & Var::operator[](char const * pKey) const
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE)
			{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
				if(this->gData.uHashTable.gUnorderedMap->count(pKey) == 1)
					{return this->gData.uHashTable.gUnorderedMap->operator[](pKey);}
				else
				{
	#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__SWALLOW)
					CRX__VAR__GUARD(false); return *this;
	#elif(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
					CRX__VAR__GUARD(false); return *this;
	#else
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INDEX_OUT_OF_BOUNDS,
							CRX__VAR__NO_OP_FOR_ERROR);

					return *this;
	#endif
				}
#else
				if(CRX__VAR__KHASH__HAS_KEY(this->gData.uHashTable.gKHash, pKey))
				{
					Var * vVar = NULL;

					CRX__VAR__KHash_forceGet(this->gData.uHashTable.gKHash, vVar, pKey,
							CRX__VAR__GET_IS_THREAD_POSSIBLE1(this));

					return (*vVar);
				}
				else
				{
	#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__SWALLOW)
					CRX__VAR__GUARD(false); return *this;
	#elif(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
					CRX__VAR__GUARD(false); return *this;
	#else
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INDEX_OUT_OF_BOUNDS,
							CRX__VAR__NO_OP_FOR_ERROR);

					return *this;
	#endif
				}
#endif
			}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			else if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR)
				{return *this;}
#endif
			else
			{
#if(CRX__VAR__ERROR_MODE != CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
				CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
						CRX__VAR__NO_OP_FOR_ERROR);

				return *this;
#else
				CRX__VAR__GUARD(false); return *this;
#endif
			}
		}

		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator[](bool pIndex)
		{
			if(!pIndex || (CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE) ||
					(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY))
			{
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR)
					{return *this;}
				else
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INDEX_OUT_OF_BOUNDS,
							CRX__VAR__NO_OP_FOR_ERROR);

					return *this;
				}
#else
				CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INDEX_OUT_OF_BOUNDS,
						CRX__VAR__NO_OP_FOR_ERROR);

				return *this;
#endif
			}
			else
				{return *this;}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var const & Var::operator[](bool pIndex) const
		{
			if(!pIndex || (CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE) ||
					(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY))
			{
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR)
					{return *this;}
				else
				{
	#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
					CRX__VAR__GUARD2(false, *this);
	#else
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INDEX_OUT_OF_BOUNDS,
							CRX__VAR__NO_OP_FOR_ERROR);

					return *this;
	#endif
				}
#else
				CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INDEX_OUT_OF_BOUNDS,
						CRX__VAR__NO_OP_FOR_ERROR);

				return *this;
#endif
			}
			else
				{return *this;}
		}
		
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator[](Var & pVar)
			{return this->doOperatorSquareBrackets(false, &pVar, false);}
		CRX_PUBLIC CRX__LIB__METHOD() Var const & Var::operator[](Var & pVar) const
			{return const_cast<Var *>(this)->doOperatorSquareBrackets(true, &pVar, false);}
		CRX_PUBLIC CRX__LIB__METHOD() Var & Var::operator[](Var const & pVar)
			{return this->doOperatorSquareBrackets(false, &(const_cast<Var &>(pVar)), true);}
		CRX_PUBLIC CRX__LIB__METHOD() Var const & Var::operator[](Var const & pVar) const
			{return const_cast<Var *>(this)->doOperatorSquareBrackets(true, &(const_cast<Var &>(pVar)), true);}
		CRX_PRIVATE CRX__LIB__METHOD() CRX__BOOST_FORCEINLINE Var & Var::doOperatorSquareBrackets(
				bool pIsThisConstant, Var * CRX_NOT_NULL pVar, bool pIsConstant)
		{
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_ERROR)
			{
				if(!pIsThisConstant)
					{this->assignPropogateErrorFrom(*pVar); return *this;}
				else
					{CRX__VAR__GUARD2(false, *this);}
			}
#endif

			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY)
			{
				/*THE FOLLOWING IS ILL DEFINED, BUT I DO NOT KNOW HOW TO SOLVE IT IN A SATISFACTORY
						AND CORRECT MANNER. THE OPERATOR[] COULD BE MADE TO ACCEPT A SIGNED INTEGER, 
						BUT THAT CAN CUT THE ACCEPTABLE SIZE OF THE ARRAY IN HALF, OR IT CAN REMOVE 
						COMPILE TIME CHECK FOR WHEN CRX__VAR__MACHINE_SIGNED_INT CAN BE LARGER 
						THAN size_t. HOWEVER, BECUASE THE VAR CAN NOT BE SMALLER THAN 16 BYTES, ON 
						A 32 BIT MACHINE THE CALLER WOULD HAVE TO USE 64GB OF RAM TO FILL THE ARRAY, 
						WHICH CAN NOT HAPPEN. ON 64BIT MACHINES 64GB WOULD BE FAR TOO MUCH EVEN 
						THOUGH POSSIBLE
				*/
				CRX__VAR__MACHINE_SIGNED_INT tIndex = CRX__VAR__MACHINE_SIGNED_INT_MAX; //-1;
				bool tIsError = false;

				if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_STRING)
				{
					if(pVar->development_isInternalNumberStringAnIntegerIfValid())
					{
						/*ORIGINAL CODE FOR COMMENT ABOVE, AND THERE WERE NO CHECKS ON INTERNAL INT MODE*/
						/*CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								pVar->development_looseConvertInternalStringToUnifiedSignedInt(&tIsError);

						if(!tIsError)
							{tIndex = tResult;}*/
#if(!CRX__VAR__IS_EMULATED_INT_USED)
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								pVar->development_looseConvertInternalStringToUnifiedSignedInt(&tIsError);

						if((!tIsError) && (tResult >= 0) && (tResult <= SIZE_MAX) && 
								(tResult <= CRX__VAR__INTERNAL_INT_MAX))
							{tIndex = tResult;}
#else
						double tResult = pVar->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, SIZE_MAX) &&
								(tResult <= CRX__VAR__INTERNAL_INT_MAX))
							{tIndex = static_cast<CRX__VAR__MACHINE_SIGNED_INT>(tResult);}
#endif
					}
					else
					{
						double tResult = pVar->development_looseConvertInternalStringToDouble();

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) && 
								CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, SIZE_MAX) &&
								(tResult <= CRX__VAR__INTERNAL_INT_MAX))
								/*CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, CRX__VAR__INTERNAL_INT_MAX))*/
							{tIndex = static_cast<CRX__VAR__MACHINE_SIGNED_INT>(tResult);}
					}
				}
				else if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_UNSIGNED_CHAR)
					{tIndex = static_cast<CRX__VAR__MACHINE_SIGNED_INT>(pVar->gData.uIntegral.uUnsignedChar);}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				else if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32)
					{tIndex = static_cast<CRX__VAR__MACHINE_SIGNED_INT>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(pVar));}
#else
				else if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_EMULATED_INT)
					{tIndex = static_cast<CRX__VAR__MACHINE_SIGNED_INT>(pVar->gData.uIntegral.uDouble);}
#endif
				else if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_DOUBLE)
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(pVar->gData.uIntegral.uDouble, 0, 
							CRX__VAR__INTERNAL_INT_MAX))
						{tIndex = static_cast<CRX__VAR__MACHINE_SIGNED_INT>(pVar->gData.uIntegral.uDouble);}
				}

				if(!tIsError)
				{
					if(!pIsThisConstant)
						{return (*this)[static_cast<size_t>(tIndex)];}
					else
						{return const_cast<Var &>(const_cast<Var const &>(*this)[static_cast<size_t>(tIndex)]);}
				}
				else
				{
#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__SWALLOW)
					if(!pIsThisConstant)
						{return (*this)[static_cast<size_t>(tIndex)];}
					else
						{return const_cast<Var &>(const_cast<Var const &>(*this)[static_cast<size_t>(tIndex)]);}
#elif(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
					if(!pIsThisConstant)
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
							
						return *this;
					}
					else
						{CRX__VAR__GUARD2(false, *this);}
#else
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
							CRX__VAR__NO_OP_FOR_ERROR);
							
					return *this;
#endif
				}
			}
			else if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE)
			{
				if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_STRING)
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					if(!pIsThisConstant)
						{return this->operator[](pVar->gData.uString.uStd.gString);}
					else
						{return const_cast<Var &>(const_cast<Var const *>(this)->operator[](pVar->gData.uString.uStd.gString));}
#else
					if(!pIsConstant)
					{
						char * tString = NULL;

						pVar->ensureStringIsNotInLargeBufferSegmentMode();

						switch(CRX__VAR__STRING__GET_MODE1(pVar))
						{
							case CRX__VAR__STRING__MODE__SMALL_BUFFER:
							{
								tString = pVar->gData.uString.uData.uSmallString.gBytes;

								break;
							}
							case CRX__VAR__STRING__MODE__LARGE_BUFFER:
							{
								tString = pVar->gData.uString.uData.uLargeString.gString->gChars;

								break;
							}
						}
						
						if(tString != NULL)
						{
							if(!pIsThisConstant)
								{return this->operator[](tString);}
							else
								{return const_cast<Var &>(const_cast<Var const *>(this)->operator[](tString));}
						}
						else
							{return *this;}
					}
					else
					{
						switch(CRX__VAR__STRING__GET_MODE1(pVar))
						{
							case CRX__VAR__STRING__MODE__SMALL_BUFFER:
							{
								if(!pIsThisConstant)
								{
									return this->operator[](
											pVar->gData.uString.uData.uSmallString.gBytes);
								}
								else
								{
									return const_cast<Var &>(const_cast<Var const *>(this)->operator[](
											pVar->gData.uString.uData.uSmallString.gBytes));
								}
							}
							case CRX__VAR__STRING__MODE__LARGE_BUFFER:
							{
								if(!pIsThisConstant)
								{
									return this->operator[](
											pVar->gData.uString.uData.uLargeString.gString->gChars);
								}
								else
								{
									return const_cast<Var &>(const_cast<Var const *>(this)->operator[](
											pVar->gData.uString.uData.uLargeString.gString->gChars));
								}
							}
							case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
							{
								if(!pIsThisConstant)
								{
									return this->operator[](::std::string(
											pVar->gData.uString.uData.uLargeString.gString->gChars +
											pVar->gData.uString.uData.uLargeString.gOffset,
											pVar->gData.uString.uData.uLargeString.gSegmentLength));
								}
								else
								{
									return const_cast<Var &>(const_cast<Var const *>(this)->operator[](::std::string(
											pVar->gData.uString.uData.uLargeString.gString->gChars +
											pVar->gData.uString.uData.uLargeString.gOffset,
											pVar->gData.uString.uData.uLargeString.gSegmentLength)));
								}
							}
							default:
								{CRX__BOOST_ASSERT(false); return *this;}
						}
					}
#endif
				}
				else if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_UNSIGNED_CHAR)
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR] /*= ?*/;

					Var::stringifyInt32(pVar->gData.uIntegral.uUnsignedChar, tChars, 
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR);

					if(!pIsThisConstant)
						{return this->operator[](tChars);}
					else
						{return const_cast<Var &>(const_cast<Var const *>(this)->operator[](tChars));}
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				else if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32)
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT] /*= ?*/;

					CRX__VAR__STRINGIFY_UNIFIED_INT(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(pVar),
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT);

					if(!pIsThisConstant)
						{return this->operator[](tChars);}
					else
						{return const_cast<Var &>(const_cast<Var const *>(this)->operator[](tChars));}
				}
#else
				else if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_EMULATED_INT)
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT] /*= ?*/;

					Var::stringifyEmulatedInt(pVar->gData.uIntegral.uDouble,
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT);

					if(!pIsThisConstant)
						{return this->operator[](tChars);}
					else
						{return const_cast<Var &>(const_cast<Var const *>(this)->operator[](tChars));}
				}
#endif
				else if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_DOUBLE)
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE] /*= ?*/;
					::double_conversion::StringBuilder tStringBuilder(tChars, 
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE) /*= ...*/;

					Var::StaticPrivateVars::gDoubleToStringConverter->ToShortest(
							this->gData.uIntegral.uDouble, &tStringBuilder);

					if(!pIsThisConstant)
						{return this->operator[](tStringBuilder.Finalize());}
					else
						{return const_cast<Var &>(const_cast<Var const *>(this)->operator[](tStringBuilder.Finalize()));}
				}
				else if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_BOOL)
				{
					if(!pIsThisConstant)
					{
						return (pVar->gData.uIntegral.uBool ? 
								this->operator[]("TRUE") : 
								this->operator[]("FALSE"));
					}
					else
					{
						return (this->gData.uIntegral.uBool ? 
								const_cast<Var &>(const_cast<Var const *>(this)->operator[]("TRUE")) : 
								const_cast<Var &>(const_cast<Var const *>(this)->operator[]("FALSE")));
					}
				}
				else
				{
#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__SWALLOW)
					if(!pIsThisConstant)
						{return this->operator[](pVar->forceGetAsStdString());}
					else
						{return const_cast<Var &>(const_cast<Var const *>(this)->operator[](pVar->forceGetAsStdString()));}
#elif(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
					if(!pIsThisConstant)
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
							
						return *this;
					}
					else
						{CRX__VAR__GUARD2(false, *this);}
#else
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
							CRX__VAR__NO_OP_FOR_ERROR);
							
					return *this;
#endif
				}
			}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			else if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR)
				{return *this;}
#endif
			else
			{
				bool tIndex = false;
				bool tIsError = false;

				if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_STRING)
					{tIndex = this->development_looseConvertInternalStringToBool(&tIsError);}
				else if(CRX__VAR__GET_TYPE1(pVar) == CRX__VAR__TYPE_BOOL)
					{tIndex = this->gData.uIntegral.uBool;}
				
				if(!tIsError)
				{
					if(!pIsThisConstant)
						{return this->operator[](tIndex);}
					else
						{return const_cast<Var &>(const_cast<Var const *>(this)->operator[](tIndex));}
				}
				else
				{
#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__SWALLOW)
					if(!pIsThisConstant)
						{return this->operator[](pVar->forceGetAsBool());}
					else
						{return const_cast<Var &>(const_cast<Var const *>(this)->operator[](pVar->forceGetAsBool()));}
#elif(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
					if(!pIsThisConstant)
					{
						CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
								CRX__VAR__NO_OP_FOR_ERROR);
							
						return *this;
					}
					else
						{CRX__VAR__GUARD2(false, *this);}
#else
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__INVALID_OPERAND,
							CRX__VAR__NO_OP_FOR_ERROR);
							
					return *this;
#endif
					
				}
					
					
#if(CRX__VAR__ERROR_MODE != CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
				CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
						CRX__VAR__NO_OP_FOR_ERROR);

				return *this;
#else
				if(!pIsThisConstant)
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__ILLEGAL_OPERATION,
							CRX__VAR__NO_OP_FOR_ERROR);

					return *this;
				}
				else
					{CRX__VAR__GUARD2(false, *this);}
#endif
			}
		}
		#pragma endregion operator [] //}
		
		//-----------------------------------

		#pragma region Morph //{
		/*
		MORPH OPERATIONS MUST BE REVERSIBLE. THIS MEANS IF AN INSTANCE OF
				Var IS CURRENTLY OF TYPE A AND MORPTH_TO_TYPE_B(X) IS VALID, THEN
						X = MORPTH_TO_TYPE_A(MORPTH_TO_TYPE_B(X))
				THIS IS NOT LIMITED TO ONE MORPH STEPS.
		*/
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::morphToString()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
					{return true;}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR] /*= ?*/;

					Var::stringifyInt32(this->gData.uIntegral.uUnsignedChar, tChars, 
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR);

					this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_STRING);
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString = tChars;
#else
					this->addStringEndIntoIndex(0, tChars, ::strlen(tChars) + 1, true);
#endif

					return true;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT] /*= ?*/;

					CRX__VAR__STRINGIFY_UNIFIED_INT(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this), 
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT);

					this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_STRING);

	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString = tChars;
	#else
					this->addStringEndIntoIndex(0, tChars, ::strlen(tChars) + 1, true);
	#endif

					return true;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT] /*= ?*/;

					Var::stringifyEmulatedInt(this->gData.uIntegral.uDouble,
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT);

					this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_STRING);

	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString = tChars;
	#else
					this->addStringEndIntoIndex(0, tChars, ::strlen(tChars) + 1, true);
	#endif

					return true;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE] /*= ?*/;
					size_t tLength /* = ?*/;
					::double_conversion::StringBuilder tStringBuilder(tChars, 
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE) /*= ...*/;

					Var::StaticPrivateVars::gDoubleToStringConverter->ToShortest(
							this->gData.uIntegral.uDouble, &tStringBuilder);
					tLength = tStringBuilder.position() + 1;
					tStringBuilder.Finalize();
					
					this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_STRING);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString = tChars;
#else
					this->addStringEndIntoIndex(0, tChars, tLength, true);
#endif

					return true;
				}
				case CRX__VAR__TYPE_BOOL:
				{
					bool tBool = this->gData.uIntegral.uBool;

					this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_STRING);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					this->gData.uString.uStd.gString = (tBool ? "TRUE" : "FALSE");
#else
					if(tBool)
						{this->addStringEndIntoIndex(0, "TRUE", 5, true);}
					else
						{this->addStringEndIntoIndex(0, "FALSE", 6, true);}
#endif

					return true;
				}
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::morphToByte()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					bool tIsError /*= ?*/;
					double tResult = this->development_convertInternalStringToDouble(&tIsError);

					if(!tIsError && CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(tResult, 0, UINT8_MAX))
					{
						this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_UNSIGNED_CHAR);
					
						this->gData.uIntegral.uUnsignedChar = static_cast<unsigned char>(tResult);

						return true;
					}
					else
						{return false;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return true;}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					if((CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) <= UINT8_MAX) &&
							(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) >= 0))
					{
						unsigned char tValue = 
								static_cast<unsigned char>(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this));

						this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_UNSIGNED_CHAR);
						
						this->gData.uIntegral.uUnsignedChar = tValue;

						return true;
					}
					else
						{return false;}
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					if((this->gData.uIntegral.uDouble <= UINT8_MAX) &&
							(this->gData.uIntegral.uDouble >= 0))
					{
						unsigned char tValue = 
								static_cast<unsigned char>(this->gData.uIntegral.uDouble);

						this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_UNSIGNED_CHAR);
						
						this->gData.uIntegral.uUnsignedChar = tValue;

						return true;
					}
					else
						{return false;}
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(CRX__VAR__IS_DOUBLE_IN_RANGE_AND_WHOLE(this->gData.uIntegral.uDouble, 
							0, UINT8_MAX))
					{
						unsigned char tValue = 
								static_cast<unsigned char>(this->gData.uIntegral.uDouble);

						this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_UNSIGNED_CHAR);
						
						this->gData.uIntegral.uUnsignedChar = tValue;

						return true;
					}
					else
						{return false;}
				}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::morphToNumber()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					if(this->development_isInternalNumberStringAnIntegerIfValid())
					{	
#if(!CRX__VAR__IS_EMULATED_INT_USED)
						bool tIsError = false;
						CRX__VAR__UNIFIED_SIGNED_INT tResult = 
								this->development_convertInternalStringToUnifiedSignedInt(&tIsError);

						if(!tIsError)
						{
							this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32);
						
							CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) = tResult;

							return true;
						}
						else
							{return false;}
#else
						bool tIsError /*= ?*/;
						double tResult = this->development_convertInternalStringToDouble(&tIsError);

						if(!tIsError && (tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_EMULATED_INT);
						
							this->gData.uIntegral.uDouble = tResult;

							return true;
						}
						else
							{return false;}
#endif
					}
					else
					{
						bool tIsError /*= ?*/;
						double tResult = this->development_convertInternalStringToDouble(&tIsError);

						if(!tIsError)
						{
							this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_DOUBLE);

							this->gData.uIntegral.uDouble = tResult;

							return true;
						}
						else
							{return false;}
					}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{return false;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					int32_t tValue = static_cast<int32_t>(this->gData.uIntegral.uUnsignedChar);

#if(!CRX__VAR__IS_EMULATED_INT_USED)
					this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32);

					CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this) = tValue;
#else
					this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_EMULATED_INT);

					this->gData.uIntegral.uDouble = tValue;
#endif

					return true;
				}	
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return true;}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::morphToBool()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					bool tIsError = false;
					bool tResult = this->development_convertInternalStringToBool(&tIsError);

					if(!tIsError)
					{
						this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_BOOL);

						this->gData.uIntegral.uBool = tResult;

						return true;
					}
					else
						{return false;}
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return false;}
				case CRX__VAR__TYPE_BOOL:
					{return true;}
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return false;}
				default:
					{CRX__BOOST_ASSERT(false); return false;}
			}
		}
		#pragma endregion Morph //}
		
		//-----------------------------------

		#pragma region Public Utilities //{
			#pragma region Types //{
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isString() const
			{return (CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isHashTable() const
			{return (CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isArray() const
			{return (CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isUnsignedChar() const
			{return (CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_UNSIGNED_CHAR);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isNumber() const
		{
#if(!CRX__VAR__IS_EMULATED_INT_USED)
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32) ||
					(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_DOUBLE));
#else
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_EMULATED_INT) ||
					(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_DOUBLE));
#endif
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isBool() const
			{return (CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_BOOL);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isPointer() const
			{return (CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_POINTER);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isPointerOrNull() const
		{
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_POINTER) ||
					(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_NULL));
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isNull() const
			{return (CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_NULL);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isUndefined() const
			{return (CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_UNDEFINED);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isError() const
		{
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			return (CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR);
#else
			return false;
#endif
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isError(uint32_t pErrorCode) const
		{
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR) &&
				(this->gData.uError.gCode == pErrorCode));
#else
			return false;
#endif
		}
		
		CRX_PUBLIC CRX__LIB__METHOD() Var::Type Var::getType()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
					{return Var::TYPE__STRING;}
				case CRX__VAR__TYPE_HASH_TABLE:
					{return Var::TYPE__HASH_TABLE;}
				case CRX__VAR__TYPE_ARRAY:
					{return Var::TYPE__ARRAY;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{return Var::TYPE__BYTE;}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{return Var::TYPE__NUMBER;}
				case CRX__VAR__TYPE_BOOL:
					{return Var::TYPE__BOOL;}
				case CRX__VAR__TYPE_POINTER:
					{return Var::TYPE__POINTER;}
				case CRX__VAR__TYPE_NULL:
					{return Var::TYPE__NIL;}
				case CRX__VAR__TYPE_UNDEFINED:
					{return Var::TYPE__UNDEFINED;}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return Var::TYPE__ERROR;}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return Var::TYPE__UNDEFINED;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::setType(Var::Type pType)
		{
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			if((pType == Var::TYPE__ERROR) || (pType == Var::TYPE__POINTER))
				{return false;}
#else
			if(pType == Var::TYPE__POINTER)
				{return false;}
#endif

			unsigned char vType = CRX__VAR__TYPE_NULL;

			switch(pType)
			{
				case Var::TYPE__STRING:
					vType = CRX__VAR__TYPE_STRING;
					break;
				case Var::TYPE__HASH_TABLE:
					vType = CRX__VAR__TYPE_HASH_TABLE;
					break;
				case Var::TYPE__ARRAY:
					vType = CRX__VAR__TYPE_ARRAY;
					break;
				case Var::TYPE__BYTE:
					vType = CRX__VAR__TYPE_UNSIGNED_CHAR;
					break;
				case Var::TYPE__NUMBER:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
					vType = CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32;
#else
					vType = CRX__VAR__TYPE_EMULATED_INT;
#endif
					break;
				case Var::TYPE__BOOL:
					vType = CRX__VAR__TYPE_BOOL;
					break;
				//case Var::TYPE__POINTER:
					//CAN NOT DO ANYTHING HERE
					//break;
				case Var::TYPE__NIL:
					vType = CRX__VAR__TYPE_NULL;
					break;
				case Var::TYPE__UNDEFINED:
					vType = CRX__VAR__TYPE_UNDEFINED;
					break;
			}
			
			this->emptyDynamicResourcesIfNecessaryForAssigment(vType);
			
			if(pType == Var::TYPE__STRING)
			{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
				this->gData.uString.uStd.gString.clear();
#else
				bool tIsToReduceCapacity = false;

				switch(CRX__VAR__STRING__GET_MODE1(this))
				{
					case CRX__VAR__STRING__MODE__SMALL_BUFFER:
						{break;}
					case CRX__VAR__STRING__MODE__LARGE_BUFFER:
					{
						if(this->gData.uString.uData.uLargeString.gString->gCapacity > 256)
							{tIsToReduceCapacity = true;}
						else
							{this->gData.uString.uData.uLargeString.gString->gLength = 0;}

						break;
					}
					case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
					{
						tIsToReduceCapacity = true;

						break;
					}
				}

				if(tIsToReduceCapacity)
				{
					this->gData.uString.uData.uLargeString.gString->gCount--;

					if(this->gData.uString.uData.uLargeString.gString->gCount == 0)
					{
						Var::String::deleteString(this->gData.uString.uData.uLargeString.gString);
						this->gData.uString.uData.uLargeString.gString = NULL;
					}

					CRX__VAR__STRING__SET_MODE(this, CRX__VAR__STRING__MODE__SMALL_BUFFER);
					this->gData.uString.uData.uSmallString.gLength = 0;
				}
#endif
			}
			else if(pType == Var::TYPE__HASH_TABLE)
			{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
				this->gData.uHashTable.gUnorderedMap->clear();
#else
				CRX__VAR__KHash_empty(this->gData.uHashTable.gKHash);
#endif
			}
			else if(pType == Var::TYPE__ARRAY)
			{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
				this->gData.uArray.gDeque->clear();
#else
				crx_varRing_empty(CRX__VAR__GET_VARRING(this));
#endif
			}

			//return (pType != Var::TYPE__POINTER);
			return true;
		}
			#pragma endregion Types //}

		//-----------------------------------
			#pragma region Number //{
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isNan() const
		{
			return (CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_DOUBLE) && 
					Var::isNan(this->gData.uIntegral.uDouble);
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isInf() const
		{
#ifndef isinf
	#if(__cplusplus < 201103L)	//C++11		//<= 199711L  // c++98 or older
		#if(defined(_MSC_VER))
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_DOUBLE) &&
					!::_isnan(this->gData.uIntegral.uDouble) &&
					!::_finite(this->gData.uIntegral.uDouble));
		#elif(defined(__APPLE__) && defined(__GNUC__) && (__GNUC__ < 4))
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_DOUBLE) &&
					__isinfd(this->gData.uIntegral.uDouble)); //NOT SURE
		#else
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_DOUBLE) &&
					::isinf(this->gData.uIntegral.uDouble)); //NOT SURE
		#endif
	#else
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_DOUBLE) &&
					::std::isinf(this->gData.uIntegral.uDouble));
	#endif	
#else
			return ((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_DOUBLE) &&
					isinf(this->gData.uIntegral.uDouble));
#endif
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::isFinite() const
			{return (this->isNumber() && !this->isNan() && !this->isInf());}
			#pragma endregion Number //}
		
		//-----------------------------------

			#pragma region Error //{
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
		CRX_PRIVATE CRX__LIB__METHOD() void Var::setPrivateError(uint32_t pCode, 
				::std::string const & pMessage CRX_DEFAULT(""))
		{
			if(CRX__VAR__GET_TYPE1(this) != CRX__VAR__TYPE_ERROR)
			{
				//::std::string * tString =  new(::std::nothrow) ::std::string(pMessage);
				size_t tSizeOfString /*= ?*/;

				this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_ERROR);

				this->gData.uError.gCode = pCode;
				
				/*if(tString !== NULL)
				{
					if(this->gData.uError.gString != NULL)
						{delete this->gData.uError.gString;}

					this->gData.uError.gString = tString;
				}*/
				if(pMessage.size() < UINT16_MAX)
					{tSizeOfString = pMessage.size();}
				else
					{tSizeOfString = UINT16_MAX - 1;}
				
				this->gData.uError.gString = ((char *) ::malloc(tSizeOfString + 1));

				if(this->gData.uError.gString != NULL)
				{
					this->gData.uError.gLength = static_cast<uint16_t>(tSizeOfString + 1);

					::memcpy(this->gData.uError.gString, pMessage.c_str(), tSizeOfString);
					*(this->gData.uError.gString + tSizeOfString) = '\0';
				}
			}
		}
		CRX_PRIVATE CRX__LIB__METHOD() void Var::safeSetPrivateError(uint32_t pCode, 
				::std::string const & pMessage CRX_DEFAULT(""))
		{
			CRX__VAR__GUARD(CRX__VAR__GET_TYPE1(this) != CRX__VAR__TYPE_POINTER);

			this->setPrivateError(pCode, pMessage);
		}
#endif
#if(CRX__VAR__IS_ERROR_TYPE_AVAILABLE_FOR_PUBLIC_USE)
		CRX_PRIVATE CRX__LIB__METHOD() void Var::setError(uint32_t pCode, 
				::std::string pMessage CRX_DEFAULT(""))
		{
	#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			CRX__VAR__GUARD(pCode > CRX__VAR__LARGEST_RESERVED_ERROR_CODE);

			if(CRX__VAR__GET_TYPE1(this) != CRX__VAR__TYPE_ERROR)
			{
				//::std::string * tString =  new(::std::nothrow) ::std::string(pMessage);
				size_t tSizeOfString /*= ?*/;

				this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_ERROR);

				this->gData.uError.gCode = pCode;
				
				/*if(tString !== NULL)
				{
					if(this->gData.uError.gString != NULL)
						{delete this->gData.uError.gString;}

					this->gData.uError.gString = tString;
				}*/
				if(pMessage.size() < UINT16_MAX)
					{tSizeOfString = pMessage.size();}
				else
					{tSizeOfString = UINT16_MAX - 1;}
				
				this->gData.uError.gString = ((char *) ::malloc(tSizeOfString + 1));

				if(this->gData.uError.gString != NULL)
				{
					this->gData.uError.gLength = static_cast<uint16_t>(tSizeOfString + 1);

					::memcpy(this->gData.uError.gString, pMessage.c_str(), tSizeOfString);
					*(this->gData.uError.gString + tSizeOfString) = '\0';
				}
			}
	#else
			throw Var(gCode, pMessage, CRX__VAR__GET_IS_THREAD_POSSIBLE1(this));
	#endif
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() void Var::clearError()
		{
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR)
				{this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_NULL);}
#endif
		}
		CRX_PUBLIC CRX__LIB__METHOD() uint32_t Var::getErrorCode()
		{
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR)
				{return this->gData.uError.gCode;}
			else
				{return 0;}
#else
			return 0;
#endif
		}
		CRX_PUBLIC CRX__LIB__METHOD() ::std::string Var::getErrorMessage()
		{
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
			if((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ERROR) &&
					(this->gData.uError.gString != NULL))
				{return ::std::string(this->gData.uError.gString, this->gData.uError.gLength - 1);}
			else
				{return "";}
#else
			return "";
#endif
		}
			#pragma endregion Error //}
		
		//-----------------------------------

			#pragma region Generic //{
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::append(char const * pChars, size_t pSize)
		{
			bool vReturn = true;

			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
					{break;}
				case CRX__VAR__TYPE_HASH_TABLE:
				case CRX__VAR__TYPE_ARRAY:
					{vReturn = false; break;}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
					{break;}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
					{break;}
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{vReturn = false; break;}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}

			if(vReturn)
				{this->doOperatorPlusEqual(pChars, pSize);}

			return vReturn;
		}

		CRX_PUBLIC CRX__LIB__METHOD() Var Var::getSub(size_t pStartIndex, size_t pMaxSize) const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					Var tVar("");

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					if(pStartIndex < this->gData.uString.uStd.gString.size())
						{tVar = this->gData.uString.uStd.gString.substr(pStartIndex, pMaxSize);}
					else
					{
						CRX__VAR__REPORT_ERROR(&tVar, CRX__VAR__ERROR__OUT_OF_RANGE,
								CRX__VAR__NO_OP_FOR_ERROR);
					}
#else
					switch(CRX__VAR__STRING__GET_MODE1(this))
					{
						case CRX__VAR__STRING__MODE__SMALL_BUFFER:
						{
							if(pStartIndex < static_cast<size_t>(this->gData.uString.uData.uSmallString.gLength - 1))
							{
								if(pStartIndex + pMaxSize < this->gData.uString.uData.uSmallString.gLength)
								{
									tVar.addStringEndIntoIndex(0,
											this->gData.uString.uData.uSmallString.gBytes + pStartIndex,
											pMaxSize, false);
								}
								else
								{
									tVar.addStringEndIntoIndex(0, 
											this->gData.uString.uData.uSmallString.gBytes + pStartIndex,
											this->gData.uString.uData.uSmallString.gLength - pStartIndex, true);
								}
							}
							else
							{
								CRX__VAR__REPORT_ERROR(&tVar, CRX__VAR__ERROR__OUT_OF_RANGE,
										CRX__VAR__NO_OP_FOR_ERROR);
							}

							break;
						}
						case CRX__VAR__STRING__MODE__LARGE_BUFFER:
						{
							if(pStartIndex < 
									(this->gData.uString.uData.uLargeString.gString->gLength - 1))
							{
								if(!CRX__VAR__GET_IS_THREAD_POSSIBLE1(this))
								{
									CRX__VAR__STRING__SET_MODE2(tVar, 
											CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT);

									tVar.gData.uString.uData.uLargeString.gString = 
											this->gData.uString.uData.uLargeString.gString;

									tVar.gData.uString.uData.uLargeString.gString->gCount++;
									tVar.gData.uString.uData.uLargeString.gOffset = pStartIndex;

									if(pStartIndex + pMaxSize <
											this->gData.uString.uData.uLargeString.gString->gLength)
										{tVar.gData.uString.uData.uLargeString.gSegmentLength = pMaxSize;}
									else
									{
										tVar.gData.uString.uData.uLargeString.gSegmentLength = 
												this->gData.uString.uData.uLargeString.gString->gLength -
												pStartIndex - 1;
									}
								}
								else
								{
									if(pStartIndex + pMaxSize <
											this->gData.uString.uData.uLargeString.gString->gLength)
									{
										tVar.addStringEndIntoIndex(0, 
												this->gData.uString.uData.uLargeString.gString->gChars + 
												pStartIndex, pMaxSize, false);
									}
									else
									{
										tVar.addStringEndIntoIndex(0, 
												this->gData.uString.uData.uLargeString.gString->gChars + 
												pStartIndex, 
												this->gData.uString.uData.uLargeString.gString->gLength -
												pStartIndex - 1, false);
									}
								}
							}
							else
							{
								CRX__VAR__REPORT_ERROR(&tVar, CRX__VAR__ERROR__OUT_OF_RANGE,
										CRX__VAR__NO_OP_FOR_ERROR);
							}

							break;
						}
						case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
						{
							CRX__BOOST_ASSERT(!CRX__VAR__GET_IS_THREAD_POSSIBLE1(this));

							if(pStartIndex < this->gData.uString.uData.uLargeString.gSegmentLength)
							{
								CRX__VAR__STRING__SET_MODE2(tVar, 
										CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT);

								tVar.gData.uString.uData.uLargeString.gString = 
										this->gData.uString.uData.uLargeString.gString;

								tVar.gData.uString.uData.uLargeString.gString->gCount++;
								tVar.gData.uString.uData.uLargeString.gOffset = 
										this->gData.uString.uData.uLargeString.gOffset +
										pStartIndex;

								if(pStartIndex + pMaxSize <=
										this->gData.uString.uData.uLargeString.gSegmentLength)
									{tVar.gData.uString.uData.uLargeString.gSegmentLength = pMaxSize;}
								else
								{
									tVar.gData.uString.uData.uLargeString.gSegmentLength = 
											this->gData.uString.uData.uLargeString.gSegmentLength -
											pStartIndex;
								}
							}
							else
							{
								CRX__VAR__REPORT_ERROR(&tVar, CRX__VAR__ERROR__OUT_OF_RANGE,
										CRX__VAR__NO_OP_FOR_ERROR);
							}
						}
					}
#endif
					return tVar;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
					Var tReturn((Var::Nil())) /*= Var(Var::Nil())*/;

					CRX__VAR__REPORT_ERROR((&tReturn), CRX__VAR__ERROR__OUT_OF_RANGE,
							return tReturn);
				}
				case CRX__VAR__TYPE_ARRAY:
				{
					Var tReturn(Var::TYPE__ARRAY, CRX__VAR__GET_IS_THREAD_POSSIBLE1(this)) /*= []*/;

#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					if(pStartIndex < this->gData.uArray.gDeque->size())
					{
						if(pStartIndex + pMaxSize <= this->gData.uArray.gDeque->size())
						{
							for(size_t tI = pStartIndex; tI < pMaxSize; tI++)
								{tReturn.gData.uArray.gDeque->push_back((*(tReturn.gData.uArray.gDeque))[tI]);}
						}
						else
						{
							for(size_t tI = pStartIndex; tI < this->gData.uArray.gDeque->size(); tI++)
								{tReturn.gData.uArray.gDeque->push_back((*(tReturn.gData.uArray.gDeque))[tI]);}
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__OUT_OF_RANGE,
								CRX__VAR__NO_OP_FOR_ERROR);
					}
#else
					if(pStartIndex < crx_varRing_getLength(CRX__VAR__GET_VARRING(this)))
					{
						if(pStartIndex + pMaxSize <= crx_varRing_getLength(CRX__VAR__GET_VARRING(this)))
						{
							CRX__VAR__GUARD(crx_varRing_ensureCapacity(CRX__VAR__GET_VARRING2(tReturn),
									pMaxSize));

							crx_varRing_fastInsertElementsAt(CRX__VAR__GET_VARRING2(tReturn), 0, 
									CRX__VAR__GET_VARRING(this), pStartIndex, pMaxSize);
						}
						else
						{
							CRX__VAR__GUARD(crx_varRing_ensureCapacity(CRX__VAR__GET_VARRING2(tReturn),
									crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) - pStartIndex));

							crx_varRing_insertElementsAt(CRX__VAR__GET_VARRING2(tReturn), 0, 
									CRX__VAR__GET_VARRING(this), pStartIndex, 
									crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) - pStartIndex);
						}
					}
					else
					{
						CRX__VAR__REPORT_ERROR(&tReturn, CRX__VAR__ERROR__OUT_OF_RANGE,
								CRX__VAR__NO_OP_FOR_ERROR);
					}
#endif
					return tReturn;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
				{
					Var tReturn((Var::Nil())) /*= Var(Var::Nil())*/;

					CRX__VAR__REPORT_ERROR((&tReturn), CRX__VAR__ERROR__OUT_OF_RANGE,
							return tReturn);
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
					{return Var(*this);}
#endif
				default:
					{CRX__BOOST_ASSERT(false); return Var(Var::Nil());}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() size_t Var::getSize() const
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return this->gData.uString.uStd.gString.size();
#else
					return this->getStringSize();
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					return this->gData.uHashTable.gUnorderedMap->size();
#else
					return CRX__VAR__KHASH__SIZE(this->gData.uHashTable.gKHash);
#endif
				}
				case CRX__VAR__TYPE_ARRAY:
				{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					return this->gData.uArray.gDeque->size();
#else
					return crx_varRing_getLength(CRX__VAR__GET_VARRING(this));
#endif
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
					{return 1;}
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return 0;}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() size_t Var::getCapacity()
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					return this->gData.uString.uStd.gString.capacity();
#else
					return this->getStringCapacity();
#endif
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					return this->gData.uHashTable.gUnorderedMap->size();
#else
					return CRX__VAR__KHASH__SIZE(this->gData.uHashTable.gKHash);
#endif
				}
				case CRX__VAR__TYPE_ARRAY:
				{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					return this->gData.uArray.gDeque->size();
#else
					return crx_varRing_getCapacity(CRX__VAR__GET_VARRING(this));
#endif
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
#else
				case CRX__VAR__TYPE_EMULATED_INT:
#endif
				case CRX__VAR__TYPE_DOUBLE:
				case CRX__VAR__TYPE_BOOL:
				case CRX__VAR__TYPE_POINTER:
					{return 1;}
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED:
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
					{return 0;}
				default:
					{CRX__BOOST_ASSERT(false); return 0;}
			}
		}
			
		CRX_PRIVATE CRX__LIB__METHOD() size_t Var::removeElementsAt(size_t pIndex, 
				size_t pNumberOfElements CRX_DEFAULT(1))
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY)
			{
				size_t tNumberOfElements = 0;

#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
				if(pIndex < this->gData.uArray.gDeque->size())
				{
					if(pIndex + pNumberOfElements <= this->gData.uArray.gDeque->size()) 
						{tNumberOfElements = pNumberOfElements;}
					else
						{tNumberOfElements = this->gData.uArray.gDeque->size() - pIndex;}

					this->gData.uArray.gDeque->erase(this->gData.uArray.gDeque->begin() + pIndex, 
							this->gData.uArray.gDeque->begin() + pIndex + tNumberOfElements);
				}
#else
				if(pIndex < crx_varRing_getLength(CRX__VAR__GET_VARRING(this)))
				{
					if(pIndex + pNumberOfElements <= crx_varRing_getLength(CRX__VAR__GET_VARRING(this)))
						{tNumberOfElements = pNumberOfElements;}
					else
						{tNumberOfElements = crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) - pIndex;}

					crx_varRing_removeElements(CRX__VAR__GET_VARRING(this), pIndex, tNumberOfElements);
				}
#endif
				return tNumberOfElements;
			}
			else
				{return 0;}
		}
#if(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_HASH_TABLE_SORTED)
		CRX_PRIVATE CRX__LIB__METHOD() size_t Var::removeElementsAt(::std::string const & pKey,
				size_t pNumberOfElements CRX_DEFAULT(1))
			{return this->removeElementsAt(pKey.c_str(), pNumberOfElements);}
		CRX_PRIVATE CRX__LIB__METHOD() size_t Var::removeElementsAt(char const * pKey,
				size_t pNumberOfElements CRX_DEFAULT(1))
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE)
			{
				size_t tNumberOfElements /*= ?*/;

	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
				CRX__BOOST_ASSERT(false);
	#else
				CRX__VAR__KHash_removeElementsAt(this->gData.uHashTable.gKHash, tNumberOfElements, pKey, 
						pNumberOfElements);
	#endif
	
				return tNumberOfElements;
			}
			else
				{return 0;}
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() size_t Var::removeElementsAt(size_t pIndex,
				Var const & pVar__numberOfElements)
		{
			bool vIsError = false;
			size_t vNumberOfElements;

#ifndef CRX__BOOST_NO_INT64_T
			vNumberOfElements = ((size_t) pVar__numberOfElements.castToSignedInt64(&vIsError));
#else
			vNumberOfElements = ((size_t) pVar__numberOfElements.castToUnsignedInt32(&vIsError));
#endif

			if(!vIsError)
			{
				if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY)
				{
					if(!vIsError)
						{return this->removeElementsAt(pIndex, vNumberOfElements);}
					else
						{return 0;}
				}
				else
					{return 0;}
			}
			else
				{return 0;}
		}
#if(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_HASH_TABLE_SORTED)
		CRX_PUBLIC CRX__LIB__METHOD() size_t Var::removeElementsAt(::std::string const & pKey,
				Var const & pVar__numberOfElements)
			{return this->removeElementsAt(pKey.c_str(), pVar__numberOfElements);}
		CRX_PUBLIC CRX__LIB__METHOD() size_t Var::removeElementsAt(char const * pKey,
				Var const & pVar__numberOfElements)
		{
			bool vIsError = false;
			size_t vNumberOfElements;

	#ifndef CRX__BOOST_NO_INT64_T
			vNumberOfElements = ((size_t) pVar__numberOfElements.castToSignedInt64(&vIsError));
	#else
			vNumberOfElements = ((size_t) pVar__numberOfElements.castToUnsignedInt32(&vIsError));
	#endif

			if(!vIsError)
			{
				if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE)
				{
					::std::string tString = this->castToString(&vIsError);

					if(!vIsError)
						{return this->removeElementsAt(tString, vNumberOfElements);}
					else
						{return 0;}
				}
				else
					{return 0;}
			}
			else
				{return 0;}
		}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() size_t Var::removeElementsAt(Var const & pVar,
				Var const & pVar__numberOfElements CRX_DEFAULT(1))
		{
			bool vIsError = false;
			size_t vNumberOfElements;

#ifndef CRX__BOOST_NO_INT64_T
			vNumberOfElements = ((size_t) pVar__numberOfElements.castToSignedInt64(&vIsError));
#else
			vNumberOfElements = ((size_t) pVar__numberOfElements.castToUnsignedInt32(&vIsError));
#endif

			if(!vIsError)
			{
				if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY)
				{
					size_t tSize;

#ifndef CRX__BOOST_NO_INT64_T
					tSize = ((size_t) pVar.castToSignedInt64(&vIsError));
#else
					tSize = ((size_t) pVar.castToUnsignedInt32(&vIsError));
#endif

					if(!vIsError)
						{return this->removeElementsAt(tSize, vNumberOfElements);}
					else
						{return 0;}
				}
#if(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_HASH_TABLE_SORTED)
				else if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE)
				{
					::std::string tString = this->castToString(&vIsError);

					if(!vIsError)
						{return this->removeElementsAt(tString, vNumberOfElements);}
					else
						{return 0;}
				}
#endif
				else
					{return 0;}
			}
			else
				{return 0;}
		}

		CRX_PUBLIC CRX__LIB__METHOD() void Var::removeElementAt(size_t pIndex)
			{this->removeElementsAt(pIndex, 1);}
		CRX_PUBLIC CRX__LIB__METHOD() void Var::removeElementAt(::std::string const & pKey)
			{this->removeElementAt(pKey.c_str());}
		CRX_PUBLIC CRX__LIB__METHOD() void Var::removeElementAt(char const * pKey)
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE)
			{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
				this->gData.uHashTable.gUnorderedMap->erase(pKey);
#else
				CRX__VAR__KHash_removeElementAt(this->gData.uHashTable.gKHash, pKey);
#endif
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() void Var::removeElementAt(Var const & pVar)
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY)
			{
				bool tIsError = false;
				size_t tSize;

#ifndef CRX__BOOST_NO_INT64_T
				tSize = ((size_t) pVar.castToSignedInt64(&tIsError));
#else
				tSize = ((size_t) pVar.castToUnsignedInt32(&tIsError));
#endif

				if(!tIsError)
					{this->removeElementAt(tSize);}
			}
#if(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_HASH_TABLE_SORTED)
			else if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE)
			{
				bool tIsError = false;
				::std::string tString = pVar.castToString(&tIsError);

				if(!tIsError)
					{this->removeElementAt(tString);}
			}
#endif
		}

		CRX_PRIVATE CRX__LIB__METHOD() Var::ArrayStlIterator Var::unsafeRemoveElementsAtRange(
				Var::ArrayStlIterator pStartIterator, Var::ArrayStlIterator pEndIterator)
		{
			CRX__VAR__GUARD(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY);

#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
			return this->gData.uArray.gDeque->erase(pStartIterator, pEndIterator);
#else
			//STRICTLY, pStartIterator CAN NOT BE NULL WITHOUT pEndIterator BEING NULL, BUT
			//		WE ARE TRYING TO BE AS FORGIVING AS POSSIBLE.
			if((pStartIterator != NULL) && 
					(pEndIterator != NULL))
			{
				size_t tStartIndex = pStartIterator - crx_varRing_getElementsPointer(CRX__VAR__GET_VARRING(this));
				size_t tNumberOfElements = pEndIterator - pStartIterator;

				crx_varRing_removeElements(CRX__VAR__GET_VARRING(this), tStartIndex, tNumberOfElements);

				return crx_varRing_getElementsPointer(CRX__VAR__GET_VARRING(this)) + 
						tStartIndex + tNumberOfElements;
			}
			else
				{return NULL;}
#endif
		}
		CRX_PRIVATE CRX__LIB__METHOD() Var::StringStlIterator Var::unsafeRemoveElementsAtRange(
				Var::StringStlIterator pStartIterator, Var::StringStlIterator pEndIterator)
		{
			CRX__VAR__GUARD(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			return this->gData.uString.uStd.gString.erase(pStartIterator, pEndIterator);
#else
			//STRICTLY, pStartIterator CAN NOT BE NULL WITHOUT pEndIterator BEING NULL, BUT
			//		WE ARE TRYING TO BE AS FORGIVING AS POSSIBLE.
			if((pStartIterator != NULL) && (pEndIterator != NULL))
			{
				bool tIsNullTerminated /*= ?*/;
				size_t tLength /*= ?*/;
				char * tChars = this->getCharPointerAndInfo(&tLength, &tIsNullTerminated);
				size_t tNumberOfChars = this->removeCharactersAt(pStartIterator - tChars, 
						pEndIterator - pStartIterator);

				tChars = this->getCharPointerAndInfo(&tLength, &tIsNullTerminated);

				return tChars + tNumberOfChars;
			}
			else
				{return NULL;}
#endif
		}
			#pragma endregion Generic //}

		//-----------------------------------

			#pragma region String //{
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::getLowerCased() const
		{
			Var vReturn(*this) /* = *this*/;

			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING)
			{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
				for(size_t tI = 0; tI < vReturn.gData.uString.uStd.gString.size(); tI++)
				{
					vReturn.gData.uString.uStd.gString[tI] = 
							::std::tolower(vReturn.gData.uString.uStd.gString[tI],
							/*VC6*/::std::locale(""));
				}
#else
				bool vIsNullTerminated /*= ?*/;
				size_t vNumberOfRemainingCharacters /*= ?*/;
				char * vChar /*= ?*/;

				vReturn.ensureStringIsOwned();
				vChar = vReturn.getCharPointerAndInfo(&vNumberOfRemainingCharacters, 
						&vIsNullTerminated);

				if(vIsNullTerminated)
				{
					while(*vChar != '\0')
					{
						*vChar = ::std::tolower(*vChar, /*VC6*/::std::locale(""));
						vChar = vChar + 1;
					}
				}
				else
				{
					while(vNumberOfRemainingCharacters > 0)
					{
						*vChar = ::std::tolower(*vChar, /*VC6*/::std::locale(""));
						vChar = vChar + 1;
						vNumberOfRemainingCharacters = vNumberOfRemainingCharacters - 1;
					}
				}
#endif
			}
			else
			{
				CRX__VAR__REPORT_ERROR((&vReturn),
							CRX__VAR__ERROR__VAR_FUNCTION_CALL_ON_INVALID_INTERNAL_TYPE,
							CRX__VAR__NO_OP_FOR_ERROR);
			}

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::getLowerCased(::std::locale const & pLocale) const
		{
			Var vReturn(*this) /* = *this*/;

			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING)
			{
				if(::std::has_facet<::std::ctype<char> >(pLocale))
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					//VC6 ::std::ctype<char> const & tCtype = ::std::use_facet<::std::ctype<char> >(pLocale);

					for(size_t tI = 0; tI < vReturn.gData.uString.uStd.gString.size(); tI++)
					{
						vReturn.gData.uString.uStd.gString[tI] = 
								//VC6 tCtype.tolower(vReturn.gData.uString.uStd.gString[tI]);
								::std::tolower(vReturn.gData.uString.uStd.gString[tI], pLocale);
					}
#else
					//VC6 ::std::ctype<char> const & tCtype = ::std::use_facet<::std::ctype<char> >(pLocale);
					bool tIsNullTerminated /*= ?*/;
					size_t tNumberOfRemainingCharacters /*= ?*/;
					char * vChar /*= ?*/;

					vReturn.ensureStringIsOwned();
					vChar = vReturn.getCharPointerAndInfo(&tNumberOfRemainingCharacters, &tIsNullTerminated);

					if(tIsNullTerminated)
					{
						while(*vChar != '\0')
						{
							//VC6 *vChar = tCtype.tolower(*vChar);
							*vChar = ::std::tolower(*vChar, pLocale);
							vChar = vChar + 1;
						}
					}
					else
					{
						while(tNumberOfRemainingCharacters > 0)
						{
							//VC6 *vChar = tCtype.tolower(*vChar);
							*vChar = ::std::tolower(*vChar, pLocale);
							vChar = vChar + 1;
							tNumberOfRemainingCharacters = tNumberOfRemainingCharacters - 1;
						}
					}
#endif
				}
			}
			else
			{
				CRX__VAR__REPORT_ERROR((&vReturn),
							CRX__VAR__ERROR__VAR_FUNCTION_CALL_ON_INVALID_INTERNAL_TYPE,
							CRX__VAR__NO_OP_FOR_ERROR);
			}

			return vReturn;
		}

		CRX_PUBLIC CRX__LIB__METHOD() Var Var::getUpperCased() const
		{
			Var vReturn((*this)) /* = *this*/;

			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING)
			{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
				for(size_t tI = 0; tI < vReturn.gData.uString.uStd.gString.size(); tI++)
				{
					vReturn.gData.uString.uStd.gString[tI] = 
							::std::toupper(vReturn.gData.uString.uStd.gString[tI],
							/*VC6*/::std::locale(""));
				}
#else
				bool vIsNullTerminated /*= ?*/;
				size_t vNumberOfRemainingCharacters /*= ?*/;
				char * vChar /*= ?*/;

				vReturn.ensureStringIsOwned();
				vChar = vReturn.getCharPointerAndInfo(&vNumberOfRemainingCharacters, 
						&vIsNullTerminated);

				if(vIsNullTerminated)
				{
					while(vChar != '\0')
					{
						*vChar = ::std::toupper(*vChar, /*VC6*/::std::locale(""));
						vChar = vChar + 1;
					}
				}
				else
				{
					while(vNumberOfRemainingCharacters > 0)
					{
						*vChar = ::std::toupper(*vChar, /*VC6*/::std::locale(""));
						vChar = vChar + 1;
						vNumberOfRemainingCharacters = vNumberOfRemainingCharacters - 1;
					}
				}
#endif
			}
			else
			{
				CRX__VAR__REPORT_ERROR((&vReturn),
							CRX__VAR__ERROR__VAR_FUNCTION_CALL_ON_INVALID_INTERNAL_TYPE,
							CRX__VAR__NO_OP_FOR_ERROR);
			}

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::getUpperCased(::std::locale const & pLocale) const
		{
			Var vReturn((*this)) /* = *this*/;

			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING)
			{
				if(::std::has_facet<::std::ctype<char> >(pLocale))
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					//VC6 ::std::ctype<char> const & tCtype = ::std::use_facet<::std::ctype<char> >(pLocale);

					for(size_t tI = 0; tI < vReturn.gData.uString.uStd.gString.size(); tI++)
					{
						vReturn.gData.uString.uStd.gString[tI] = 
								//tCtype.toupper(vReturn.gData.uString.uStd.gString[tI]);
								::std::toupper(vReturn.gData.uString.uStd.gString[tI], pLocale);
					}
#else
					//VC6 ::std::ctype<char> const & tCtype = ::std::use_facet<::std::ctype<char> >(pLocale);
					bool tIsNullTerminated /*= ?*/;
					size_t tNumberOfRemainingCharacters /*= ?*/;
					char * vChar /*= ?*/;

					vReturn.ensureStringIsOwned();
					vChar = vReturn.getCharPointerAndInfo(&tNumberOfRemainingCharacters, &tIsNullTerminated);

					if(tIsNullTerminated)
					{
						while(vChar != '\0')
						{
							//VC6 *vChar = tCtype.toupper(*vChar);
							*vChar = ::std::toupper(*vChar, pLocale);
							vChar = vChar + 1;
						}
					}
					else
					{
						while(tNumberOfRemainingCharacters > 0)
						{
							//VC6 *vChar = tCtype.toupper(*vChar);
							*vChar = ::std::toupper(*vChar, pLocale);
							vChar = vChar + 1;
							tNumberOfRemainingCharacters = tNumberOfRemainingCharacters - 1;
						}
					}
#endif
				}
			}
			else
			{
				CRX__VAR__REPORT_ERROR((&vReturn),
							CRX__VAR__ERROR__VAR_FUNCTION_CALL_ON_INVALID_INTERNAL_TYPE,
							CRX__VAR__NO_OP_FOR_ERROR);
			}

			return vReturn;
		}

		CRX_PUBLIC CRX__LIB__METHOD() Var Var::getTrimmed() const
		{
			Var vReturn("") /* = ""*/;

			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING)
			{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
				if(vReturn.gData.uString.uStd.gString.size() > 0)
				{
					size_t tStartIndex = 0;

					while((tStartIndex < vReturn.gData.uString.uStd.gString.size()) &&
							/*VC6 !::std::isspace(static_cast<unsigned char>(
									vReturn.gData.uString.uStd.gString[tStartIndex]))*/
							!::std::isspace(vReturn.gData.uString.uStd.gString[tStartIndex],
									::std::locale("")))
						{tStartIndex++;}

					if(tStartIndex < vReturn.gData.uString.uStd.gString.size())
					{
						size_t tEndIndex = vReturn.gData.uString.uStd.gString.size();

						while((tEndIndex > 0) &&
								/*VC6 !::std::isspace(static_cast<unsigned char>(
										vReturn.gData.uString.uStd.gString[tEndIndex - 1]))*/
								!::std::isspace(vReturn.gData.uString.uStd.gString[tEndIndex - 1],
										::std::locale("")))
							{tEndIndex--;}

						vReturn.gData.uString.uStd.gString = 
								this->gData.uString.uStd.gString.substr(tStartIndex, tEndIndex - tStartIndex);
					}
				}
#else
				if(this->getStringSize() > 0)
				{
					size_t tStartIndex = 0;
					size_t tEndIndex = 0;
					bool tIsNullTerminated /*= ?*/;
					size_t tLength /*= ?*/;
					char * tChar = vReturn.getCharPointerAndInfo(&tLength, &tIsNullTerminated);
					
					while((tStartIndex < tLength) &&
							//VC6 !::std::isspace(static_cast<unsigned char>(*(tChar + tStartIndex))), 
							!::std::isspace(*(tChar + tStartIndex), ::std::locale("")))
						{tStartIndex++;}

					if(tStartIndex < tLength)
					{
						size_t tEndIndex = tLength;

						while((tEndIndex > 0) &&
								//VC6 !::std::isspace(static_cast<unsigned char>(*(tChar + tEndIndex - 1)))
								!::std::isspace(*(tChar + tEndIndex - 1), ::std::locale("")))
							{tEndIndex--;}

						vReturn = this->getSub(tStartIndex, tEndIndex - tStartIndex);
					}
				}
#endif
			}
			else
			{
				CRX__VAR__REPORT_ERROR((&vReturn),
							CRX__VAR__ERROR__VAR_FUNCTION_CALL_ON_INVALID_INTERNAL_TYPE,
							CRX__VAR__NO_OP_FOR_ERROR);
			}

			return vReturn;
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::getTrimmed(::std::locale const & pLocale) const
		{
			Var vReturn("") /* = ""*/;

			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING)
			{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
				if(vReturn.gData.uString.uStd.gString.size() > 0)
				{
					size_t tStartIndex = 0;

					while((tStartIndex < vReturn.gData.uString.uStd.gString.size()) &&
							!::std::isspace(vReturn.gData.uString.uStd.gString[tStartIndex], pLocale))
						{tStartIndex++;}

					if(tStartIndex < vReturn.gData.uString.uStd.gString.size())
					{
						size_t tEndIndex = vReturn.gData.uString.uStd.gString.size();

						while((tEndIndex > 0) &&
								!::std::isspace(vReturn.gData.uString.uStd.gString[tEndIndex - 1], pLocale))
							{tEndIndex--;}

						vReturn.gData.uString.uStd.gString = 
								this->gData.uString.uStd.gString.substr(tStartIndex, tEndIndex - tStartIndex);
					}
				}
#else
				if(this->getStringSize() > 0)
				{
					size_t tStartIndex = 0;
					size_t tEndIndex = 0;
					bool tIsNullTerminated /*= ?*/;
					size_t tLength /*= ?*/;
					char * tChar = vReturn.getCharPointerAndInfo(&tLength, &tIsNullTerminated);
					
					while((tStartIndex < tLength) &&
							!::std::isspace(*(tChar + tStartIndex), pLocale))
						{tStartIndex++;}

					if(tStartIndex < tLength)
					{
						size_t tEndIndex = tLength;

						while((tEndIndex > 0) &&
								!::std::isspace(*(tChar + tEndIndex - 1), pLocale))
							{tEndIndex--;}

						vReturn = this->getSub(tStartIndex, tEndIndex - tStartIndex);
					}
				}
#endif
			}
			else
			{
				CRX__VAR__REPORT_ERROR((&vReturn),
							CRX__VAR__ERROR__VAR_FUNCTION_CALL_ON_INVALID_INTERNAL_TYPE,
							CRX__VAR__NO_OP_FOR_ERROR);
			}

			return vReturn;
		}

		CRX_PUBLIC CRX__LIB__METHOD() char Var::getCharAt(size_t pIndex) const
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING)
			{
				bool tIsNullTerminated /*= ?*/;
				size_t tLength /*= ?*/;
				char const * tChars = this->getCharPointerAndInfo(&tLength, &tIsNullTerminated);

				if(pIndex < tLength)
					{return *(tChars + pIndex);}
				else
					{return '\0';}
			}
			else
				{return '\0';}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::setCharAt(char pChar, size_t pIndex)
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING)
			{
				bool tIsNullTerminated /*= ?*/;
				size_t tLength /*= ?*/;
				char * tChars = this->getCharPointerAndInfo(&tLength, &tIsNullTerminated);

				if(pIndex < tLength)
				{
					*(tChars + pIndex) = pChar;

					return true;
				}
				else
					{return false;}
			}
			else
				{return false;}
		}
		CRX_PUBLIC CRX__LIB__METHOD() size_t Var::removeCharAt(size_t pIndex)
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING)
			{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
				if(this->gData.uString.uStd.gString.size() > 0)
				{
					if(this->gData.uString.uStd.gString.size() > pIndex)
					{
						this->gData.uString.uStd.gString.erase(pIndex, 1);

						return 1;
					}
					else
						{return 0;}
				}
				else
					{return 0;}
#else
				return this->removeCharactersAt(pIndex, 1);
#endif
			}
			else
				{return 0;}
		}
		CRX_PUBLIC CRX__LIB__METHOD() size_t Var::removeCharsAt(size_t pIndex, size_t pWidth)
		{
			if((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING) && (pWidth > 0))
			{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
				if(this->gData.uString.uStd.gString.size() > pIndex)
				{
					if(this->gData.uString.uStd.gString.size() >= (pWidth + pIndex))
					{
						this->gData.uString.uStd.gString.erase(pIndex, pWidth);

						return pWidth;
					}
					else
					{
						size_t tReturn = this->gData.uString.uStd.gString.size() - pIndex;

						this->gData.uString.uStd.gString.erase(pIndex, tReturn);

						return tReturn;
					}
				}
				else
					{return 0;}
#else
				return this->removeCharactersAt(pIndex, pWidth);
#endif
			}
			else
				{return 0;}
		}
			
			#pragma endregion String //}

		//-----------------------------------

			#pragma region HashTable //{
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::hasKey(Var const & pVar)
		{
			if(CRX__VAR__GET_TYPE2(pVar) == CRX__VAR__TYPE_STRING)
			{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
				return this->hasKey(pVar.gData.uString.uStd.gString);
#else
				switch(CRX__VAR__STRING__GET_MODE2(pVar))
				{
					case CRX__VAR__STRING__MODE__SMALL_BUFFER:
						{return this->hasKey(pVar.gData.uString.uData.uSmallString.gBytes);}
					case CRX__VAR__STRING__MODE__LARGE_BUFFER:
						{return this->hasKey(pVar.gData.uString.uData.uLargeString.gString->gChars);}
					case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
					{
						bool tIsError = false;
						::std::string tString = pVar.castToString(&tIsError);

						return this->hasKey(tString);
					}
					default:
						{CRX__BOOST_ASSERT(false); return false;}
				}
#endif
			}
			else
			{
				bool tIsError = false;
				::std::string tString = pVar.castToString(&tIsError);

				if(!tIsError)
					{return this->hasKey(tString);}
				else
					{return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::hasKey(::std::string const & pString)
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE)
			{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
				return (this->gData.uHashTable.gUnorderedMap->count(pString) == 1);
#else
				return CRX__VAR__KHASH__HAS_KEY(this->gData.uHashTable.gKHash, pString.c_str());
#endif
			}
			else
				{return false;}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::hasKey(char const * pString)
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_HASH_TABLE)
			{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
				return (this->gData.uHashTable.gUnorderedMap->count(pString) == 1);
#else
				return CRX__VAR__KHASH__HAS_KEY(this->gData.uHashTable.gKHash, pString);
#endif
			}
			else
				{return false;}
		}

#if(CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_HASH_TABLE_SORTED)
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::insertElementAfterKey(Var const & pVar__key,
				Var const & pVar__key2, Var const & pVar__value)
		{
			if(CRX__VAR__GET_TYPE2(pVar__key) == CRX__VAR__TYPE_STRING)
			{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
				if(CRX__VAR__GET_TYPE2(pVar__key2) == CRX__VAR__TYPE_STRING)
				{
					return this->insertElementAfterKey(pVar__key.gData.uString.uStd.gString,
							pVar__key2.gData.uString.uStd.gString, pVar__value);
				}
				else
				{
					bool tIsError = false;
					::std::string tString = pVar__key2.castToString(&tIsError);

					if(!tIsError)
					{
						return this->insertElementAfterKey(pVar__key.gData.uString.uStd.gString,
								tString, pVar__value);
					}
					else
						{return false;}
				}
#else
				bool tIsPassing = false;
				char * tString = pVar__key.development_unsafeGetStringAsChars(&tIsPassing);
				bool tReturn = false;

				if(tString != NULL)
				{
					if(CRX__VAR__GET_TYPE2(pVar__key2) == CRX__VAR__TYPE_STRING)
					{
						bool tIsPassing2 = false;
						char * tString2 = pVar__key2.development_unsafeGetStringAsChars(&tIsPassing2);

						if(tString2 != NULL)
						{
							tReturn = this->insertElementAfterKey(tString, tString2, pVar__value);

							if(tIsPassing2)
								{::free(tString2);}
						}
					}
					else
					{
						bool tIsError = false;
						::std::string tString = pVar__key2.castToString(&tIsError);

						if(!tIsError)
							{tReturn = this->insertElementAfterKey(tString, tString, pVar__value);}
					}
				}
				
				if(tIsPassing)
					{::free(tString);}

				return tReturn;
#endif
			}
			else
			{
				bool tIsError = false;
				::std::string tString = pVar__key.castToString(&tIsError);

				if(!tIsError)
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					if(CRX__VAR__GET_TYPE2(pVar__key2) == CRX__VAR__TYPE_STRING)
					{
						return this->insertElementAfterKey(tString,
								pVar__key2.gData.uString.uStd.gString, pVar__value);
					}
					else
					{
						bool tIsError = false;
						::std::string tString2 = pVar__key2.castToString(&tIsError);

						if(!tIsError)
							{return this->insertElementAfterKey(tString, tString2, pVar__value);}
						else
							{return false;}
					}
#else
					if(CRX__VAR__GET_TYPE2(pVar__key2) == CRX__VAR__TYPE_STRING)
					{
						bool tIsPassing = false;
						char * tString2 = pVar__key2.development_unsafeGetStringAsChars(&tIsPassing);
						bool tReturn = false;

						if(tString2 != NULL)
						{
							tReturn = this->insertElementAfterKey(tString, tString2, pVar__value);

							if(tIsPassing)
								{::free(tString2);}
						}
						
						return tReturn;
					}
					else
					{
						bool tIsError = false;
						::std::string tString2 = pVar__key2.castToString(&tIsError);

						if(!tIsError)
							{return this->insertElementAfterKey(tString, tString2, pVar__value);}
						else
							{return false;}
					}
#endif
				}
				else
					{return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::insertElementAfterKey(::std::string const & pKey1,
				::std::string const & pKey2, Var const & pVar__value)
			{return this->insertElementAfterKey(pKey1.c_str(), pKey2.c_str(), pVar__value);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::insertElementAfterKey(char const * pKey1,
				::std::string const & pKey2, Var const & pVar__value)
			{return this->insertElementAfterKey(pKey1, pKey2.c_str(), pVar__value);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::insertElementAfterKey(::std::string const & pKey1,
				char const * pKey2, Var const & pVar__value)
			{return this->insertElementAfterKey(pKey1.c_str(), pKey2, pVar__value);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::insertElementAfterKey(char const * pKey1,
				char const * pKey2, Var const & pVar__value)
		{
			if(pKey2 == NULL)
				{return false;}
			
			bool vReturn /*= ?*/;

			CRX__VAR__KHash_insertElementAfterKey(this->gData.uHashTable.gKHash, vReturn, pKey1, pKey2, &pVar__value);

			return vReturn;
		}


		CRX_PUBLIC CRX__LIB__METHOD() bool Var::insertElementBeforeKey(Var const & pVar__key,
				Var const & pVar__key2, Var const & pVar__value)
		{
			if(CRX__VAR__GET_TYPE2(pVar__key) == CRX__VAR__TYPE_STRING)
			{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
				if(CRX__VAR__GET_TYPE2(pVar__key2) == CRX__VAR__TYPE_STRING)
				{
					return this->insertElementBeforeKey(pVar__key.gData.uString.uStd.gString,
							pVar__key2.gData.uString.uStd.gString, pVar__value);
				}
				else
				{
					bool tIsError = false;
					::std::string tString = pVar__key2.castToString(&tIsError);

					if(!tIsError)
					{
						return this->insertElementBeforeKey(pVar__key.gData.uString.uStd.gString,
								tString, pVar__value);
					}
					else
						{return false;}
				}
#else
				bool tIsPassing = false;
				char * tString = pVar__key.development_unsafeGetStringAsChars(&tIsPassing);
				bool tReturn = false;

				if(tString != NULL)
				{
					if(CRX__VAR__GET_TYPE2(pVar__key2) == CRX__VAR__TYPE_STRING)
					{
						bool tIsPassing2 = false;
						char * tString2 = pVar__key2.development_unsafeGetStringAsChars(&tIsPassing2);

						if(tString2 != NULL)
						{
							tReturn = this->insertElementBeforeKey(tString, tString2, pVar__value);

							if(tIsPassing2)
								{::free(tString2);}
						}
					}
					else
					{
						bool tIsError = false;
						::std::string tString = pVar__key2.castToString(&tIsError);

						if(!tIsError)
							{tReturn = this->insertElementBeforeKey(tString, tString, pVar__value);}
					}
				}
				
				if(tIsPassing)
					{::free(tString);}

				return tReturn;
#endif
			}
			else
			{
				bool tIsError = false;
				::std::string tString = pVar__key.castToString(&tIsError);

				if(!tIsError)
				{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					if(CRX__VAR__GET_TYPE2(pVar__key2) == CRX__VAR__TYPE_STRING)
					{
						return this->insertElementBeforeKey(tString,
								pVar__key2.gData.uString.uStd.gString, pVar__value);
					}
					else
					{
						bool tIsError = false;
						::std::string tString2 = pVar__key2.castToString(&tIsError);

						if(!tIsError)
							{return this->insertElementBeforeKey(tString, tString2, pVar__value);}
						else
							{return false;}
					}
#else
					if(CRX__VAR__GET_TYPE2(pVar__key2) == CRX__VAR__TYPE_STRING)
					{
						bool tIsPassing = false;
						char * tString2 = pVar__key2.development_unsafeGetStringAsChars(&tIsPassing);
						bool tReturn = false;

						if(tString2 != NULL)
						{
							tReturn = this->insertElementBeforeKey(tString, tString2, pVar__value);

							if(tIsPassing)
								{::free(tString2);}
						}
						
						return tReturn;
					}
					else
					{
						bool tIsError = false;
						::std::string tString2 = pVar__key2.castToString(&tIsError);

						if(!tIsError)
							{return this->insertElementBeforeKey(tString, tString2, pVar__value);}
						else
							{return false;}
					}
#endif
				}
				else
					{return false;}
			}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::insertElementBeforeKey(::std::string const & pKey1,
				::std::string const & pKey2, Var const & pVar__value)
			{return this->insertElementBeforeKey(pKey1.c_str(), pKey2.c_str(), pVar__value);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::insertElementBeforeKey(char const * pKey1,
				::std::string const & pKey2, Var const & pVar__value)
			{return this->insertElementBeforeKey(pKey1, pKey2.c_str(), pVar__value);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::insertElementBeforeKey(::std::string const & pKey1,
				char const * pKey2, Var const & pVar__value)
			{return this->insertElementBeforeKey(pKey1.c_str(), pKey2, pVar__value);}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::insertElementBeforeKey(char const * pKey1,
				char const * pKey2, Var const & pVar__value)
		{
			if(pKey2 == NULL)
				{return false;}
			
			bool vReturn /*= ?*/;

			CRX__VAR__KHash_insertElementBeforeKey(this->gData.uHashTable.gKHash, vReturn, pKey1, pKey2, &pVar__value);

			return vReturn;
		}
#endif
			#pragma endregion HashTable //}

		//-----------------------------------

			#pragma region Array //{
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::push(Var const & pVar)
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY)
			{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
				CRX__VAR__TRY
					this->gData.uArray.gDeque->push_back(pVar);

					return true;
				CRX__VAR__END_TRY
				CRX__VAR__CATCH
					return false;
				CRX__VAR__END_CATCH
#else
				return crx_varRing_push(CRX__VAR__GET_VARRING(this), &pVar);
#endif
			}
			else
				{return false;}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::popAndGet()
		{
			Var vReturn((Var::Undefined())) /*= Var::Undefined()*/;

			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY)
			{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
				if(this->gData.uArray.gDeque->size() > 0)
				{
					vReturn = this->gData.uArray.gDeque->back();

					this->gData.uArray.gDeque->pop_back();
				}
#else
				if(crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) > 0)
				{
					vReturn = *(crx_varRing_get(CRX__VAR__GET_VARRING(this), 
							crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) - 1));

					crx_varRing_pop(CRX__VAR__GET_VARRING(this));
				}
#endif
			}

			return vReturn;
		}
		
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::pushToFront(Var const & pVar)
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY)
			{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
				CRX__VAR__TRY
					this->gData.uArray.gDeque->push_front(pVar);

					return true;
				CRX__VAR__END_TRY
				CRX__VAR__CATCH
					return false;
				CRX__VAR__END_CATCH
#else
				return crx_varRing_pushToFront(CRX__VAR__GET_VARRING(this), &pVar);
#endif
			}
			else
				{return false;}
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var Var::popFromFrontAndGet()
		{
			Var vReturn((Var::Undefined())) /*= Var::Undefined()*/;

			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY)
			{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
				if(this->gData.uArray.gDeque->size() > 0)
				{
					vReturn = this->gData.uArray.gDeque->front();

					this->gData.uArray.gDeque->pop_front();
				}
#else
				if(crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) > 0)
				{
					vReturn = *(crx_varRing_get(CRX__VAR__GET_VARRING(this), 0));

					crx_varRing_popFromFront(CRX__VAR__GET_VARRING(this));
				}
#endif
			}

			return vReturn;
		}

		CRX_PUBLIC CRX__LIB__METHOD() bool Var::insertElementAt(size_t pIndex,
				Var const & pVar)
		{
			if(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY)
			{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
				if(pIndex < this->gData.uArray.gDeque->size())
				{
					CRX__VAR__TRY
						this->gData.uArray.gDeque->insert(this->gData.uArray.gDeque->begin() + pIndex,
								pVar);

						return true;
					CRX__VAR__END_TRY
					CRX__VAR__CATCH
						return false;
					CRX__VAR__END_CATCH
				}
				else
					{return false;}
#else
				if(pIndex < crx_varRing_getLength(CRX__VAR__GET_VARRING(this)))
					{return crx_varRing_insertElementAt(CRX__VAR__GET_VARRING(this), pIndex, &pVar);}
				else
					{return false;}
#endif
			}
			else
				{return false;}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::insertElementAt(Var pVar__index,
				Var const & pVar)
		{
			bool vIsError = false;
			size_t vIndex /*= ?*/;

#ifndef CRX__BOOST_NO_INT64_T
			vIndex = ((size_t) pVar__index.castToSignedInt64(&vIsError));
#else
			vIndex = ((size_t) pVar__index.castToUnsignedInt32(&vIsError));
#endif
			if(!vIsError)
				{return this->insertElementAt(vIndex, pVar);}
			else
				{return false;}
		}
		
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::insertElementsAt(size_t pIndex,
				Var const & pVar__array, size_t pStartIndex, size_t pWidth)
		{
			if((CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_ARRAY) &&
					(CRX__VAR__GET_TYPE2(pVar__array) == CRX__VAR__TYPE_ARRAY))
			{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
				if((pIndex < this->gData.uArray.gDeque->size()) &&
					(pStartIndex < pVar__array.gData.uArray.gDeque->size()))
				{
					CRX__VAR__TRY
						if((pStartIndex + pWidth) < pVar__array.gData.uArray.gDeque->size())
						{
							this->gData.uArray.gDeque->insert(this->gData.uArray.gDeque->begin() + pIndex,
									pVar__array.gData.uArray.gDeque->begin() + pStartIndex,
									pVar__array.gData.uArray.gDeque->begin() + pStartIndex + pWidth);
						}
						else
						{
							this->gData.uArray.gDeque->insert(this->gData.uArray.gDeque->begin() + pIndex,
									pVar__array.gData.uArray.gDeque->begin() + pStartIndex,
									pVar__array.gData.uArray.gDeque->end());
						}

						return true;
					CRX__VAR__END_TRY
					CRX__VAR__CATCH
						return false;
					CRX__VAR__END_CATCH
				}
				else
					{return false;}
#else
				if((pIndex < crx_varRing_getLength(CRX__VAR__GET_VARRING(this))) &&
						(pStartIndex < crx_varRing_getLength(CRX__VAR__GET_VARRING2(pVar__array))))
				{
					if((pStartIndex + pWidth) < crx_varRing_getLength(CRX__VAR__GET_VARRING2(pVar__array)))
					{
						return crx_varRing_insertElementsAt(CRX__VAR__GET_VARRING(this), pIndex, 
								CRX__VAR__GET_VARRING2(pVar__array), pStartIndex, pWidth);
					}
					else
					{
						return crx_varRing_insertElementsAt(CRX__VAR__GET_VARRING(this), pIndex, 
								CRX__VAR__GET_VARRING2(pVar__array), pStartIndex, 
								crx_varRing_getLength(CRX__VAR__GET_VARRING2(pVar__array)) - pStartIndex);
					}
				}
				else
					{return false;}
#endif
			}
			else
				{return false;}
		}
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::insertElementsAt(Var const & pVar__index,
				Var const & pVar__array, Var const & pVar__startIndex, Var const &  pVar__width)
		{
			bool vIsError = false;
			size_t vIndex /*= ?*/;
			size_t vStartIndex /*= ?*/;
			size_t vWidth /*= ?*/;

#ifndef CRX__BOOST_NO_INT64_T
			vIndex = ((size_t) pVar__index.castToSignedInt64(&vIsError));
			vStartIndex = ((size_t) pVar__startIndex.castToSignedInt64(&vIsError));
			vWidth = ((size_t) pVar__width.castToSignedInt64(&vIsError));
#else
			vIndex = ((size_t) pVar__index.castToUnsignedInt32(&vIsError));
			vStartIndex = ((size_t) pVar__startIndex.castToSignedInt32(&vIsError));
			vWidth = ((size_t) pVar__width.castToSignedInt32(&vIsError));
#endif
			if(!vIsError)
				{return this->insertElementsAt(vIndex, pVar__array, vStartIndex, vWidth);}
			else
				{return false;}
		}
			#pragma endregion Array //}
		#pragma endregion Public Utilities //}
		
		//-----------------------------------

		#pragma region ITERATOR SUPPORT //{			
			#pragma region STL ITERATORS //{
				#pragma region STRING //{
		/*
		FOR THE FOLLOWING FUNCTIONS, NOTE THE FOLLOWING
			- REMEMBER THAT LENGTH INCLUDES THE NULL CHARACTER.
			- WHEN IN LARGE BUFFER SEGMENT MODE, THERE IS NO NULL CHARACTER.
			- THE LENGTH CAN NOT BE ZERO.
			- THE FOLLOWING IS NOT MEANT TO BE USED WITH C FUNCTIONS, MEANING
					THOSE EXPECTING A char *. REMEMBER, A ::std::string ITERATOR
					IS NOT NECESSARILY A CHARACTER POINTER.
		*/
		

		CRX_PUBLIC CRX__LIB__METHOD() Var::StringStlIterator Var::getStringStartStlIterator()
		{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			CRX__VAR__GUARD(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			return this->gData.uString.uStd.gString.begin();
#else
			CRX__VAR__GUARD(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);
			/*if(CRX__VAR__GET_TYPE1(this) != CRX__VAR__TYPE_STRING)
				{return NULL;}*/

			this->ensureStringIsOwned();

			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
					{return this->gData.uString.uData.uSmallString.gBytes;}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
					{return this->gData.uString.uData.uLargeString.gString->gChars;}
				default:
					{CRX__BOOST_ASSERT(false); return NULL;}
			}
#endif
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::StringConstantStlIterator Var::getStringStartConstantStlIterator() const
		{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			CRX__VAR__GUARD(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			return this->gData.uString.uStd.gString.cbegin();
#else
			CRX__VAR__GUARD(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);
			/*if(CRX__VAR__GET_TYPE1(this) != CRX__VAR__TYPE_STRING)
				{return NULL;}*/

			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
					{return this->gData.uString.uData.uSmallString.gBytes;}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
					{return this->gData.uString.uData.uLargeString.gString->gChars;}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
				{
					return this->gData.uString.uData.uLargeString.gString->gChars + 
							this->gData.uString.uData.uLargeString.gOffset;
				}
				default:
					{CRX__BOOST_ASSERT(false); return NULL;}
			}
#endif
		}
		
		CRX_PUBLIC CRX__LIB__METHOD() bool Var::hasStringStlIteratorEnded(
				Var::StringConstantStlIterator pChar) const
		{
			/*
			NOTE: CURRENTLY CODE IS WRITTEN DEFENSIVELY, ASSUMING THAT THE LENGTH OF THE STRING (NOT SIZE)
			CAN BE ZERO. ORIGINALLY THIS CAN ONLY HAPPEN WHEN THE STRING IS IN SMALL BUFFER MODE. HOWEVER,
			EVEN THAT SHOULD NO LONGER BE POSSIBLE. THE CODE IS WRITTEN THIS WAY AS NOT TO AFFECT CLIENT
			CODE SHOULD THE INTERNAL IMPLEMENTATION OF THINGS CHANGE.
			
			COMPARISON OF POINTER USING '>' AND '<' AND '<=' AND '>=' IS ASSUMED UNSAFE WHEN TWO POINTERS
			DO NOT POINT TO AREAS ON THE SAME OBJECT. THEREFORE CHECKS FIRST MAKE USE OF '=='. THE CHECKS
			WITH THE OTHER OPERATORS MIGHT BE REMOVED IN THE FUTURE IF THEY GIVE WRONG RESULTS. REMEMBER
			THIS IS A STL COMPATIBLE ITERATOR, AND STL COMPATIBLE ITERATORS ARE NOT EXPECTED TO BE SAFE
			PER THE VAR SPECIFICATION.
			*/

			if(CRX__VAR__GET_TYPE1(this) != CRX__VAR__TYPE_STRING)
				{return true;}

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			return (this->gData.uString.uStd.gString.size() == 0) ||
					(pChar == this->gData.uString.uStd.gString.end());
#else
			if(pChar != NULL)
			{
				switch(CRX__VAR__STRING__GET_MODE1(this))
				{
					case CRX__VAR__STRING__MODE__SMALL_BUFFER:
					{
						return (this->gData.uString.uData.uSmallString.gLength == 0) ||
								((this->gData.uString.uData.uSmallString.gBytes + 
										this->gData.uString.uData.uSmallString.gLength - 1) == pChar) ||
								(this->gData.uString.uData.uSmallString.gBytes > pChar) ||
								((this->gData.uString.uData.uSmallString.gBytes + 
										this->gData.uString.uData.uSmallString.gLength - 1) <= pChar);
					}
					case CRX__VAR__STRING__MODE__LARGE_BUFFER:
					{
						return (this->gData.uString.uData.uLargeString.gString->gLength == 0) ||
								((this->gData.uString.uData.uLargeString.gString->gChars + 
										this->gData.uString.uData.uLargeString.gString->gLength - 1) == pChar) ||
								(this->gData.uString.uData.uLargeString.gString->gChars > pChar) ||
								((this->gData.uString.uData.uLargeString.gString->gChars + 
										this->gData.uString.uData.uLargeString.gString->gLength - 1) <= pChar);
					}
					case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
					{
						return (this->gData.uString.uData.uLargeString.gSegmentLength == 0) ||
								((this->gData.uString.uData.uLargeString.gString->gChars + 
										this->gData.uString.uData.uLargeString.gOffset + 
										this->gData.uString.uData.uLargeString.gSegmentLength) == pChar) ||
								((this->gData.uString.uData.uLargeString.gString->gChars + 
										this->gData.uString.uData.uLargeString.gOffset) > pChar) ||
								((this->gData.uString.uData.uLargeString.gString->gChars + 
										this->gData.uString.uData.uLargeString.gOffset + 
										this->gData.uString.uData.uLargeString.gSegmentLength) <= pChar);
					}
					default:
						{CRX__BOOST_ASSERT(false); return true;}
				}
			}
			else
				{return true;}
#endif
		}

		CRX_PUBLIC CRX__LIB__METHOD() Var::StringStlIterator Var::getStringEndStlIterator()
		{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			CRX__VAR__GUARD(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			return this->gData.uString.uStd.gString.end();
#else
			CRX__VAR__GUARD(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);
			/*if(CRX__VAR__GET_TYPE1(this) != CRX__VAR__TYPE_STRING)
				{return NULL;}*/

			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
				{
					return this->gData.uString.uData.uSmallString.gBytes + 
							this->gData.uString.uData.uSmallString.gLength - 1;
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
				{
					return this->gData.uString.uData.uLargeString.gString->gChars + 
							this->gData.uString.uData.uLargeString.gString->gLength - 1;
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
				{
					return this->gData.uString.uData.uLargeString.gString->gChars + 
							this->gData.uString.uData.uLargeString.gOffset + 
							this->gData.uString.uData.uLargeString.gSegmentLength;
				}
				default:
					{CRX__BOOST_ASSERT(false); return NULL;}
			}
#endif
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::StringConstantStlIterator Var::getStringEndConstantStlIterator() const
		{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
			CRX__VAR__GUARD(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);

			return this->gData.uString.uStd.gString.cend();
#else
			CRX__VAR__GUARD(CRX__VAR__GET_TYPE1(this) == CRX__VAR__TYPE_STRING);
			/*if(CRX__VAR__GET_TYPE1(this) != CRX__VAR__TYPE_STRING)
				{return NULL;}*/

			switch(CRX__VAR__STRING__GET_MODE1(this))
			{
				case CRX__VAR__STRING__MODE__SMALL_BUFFER:
				{
					return this->gData.uString.uData.uSmallString.gBytes + 
							this->gData.uString.uData.uSmallString.gLength - 1;
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER:
				{
					return this->gData.uString.uData.uLargeString.gString->gChars + 
							this->gData.uString.uData.uLargeString.gString->gLength - 1;
				}
				case CRX__VAR__STRING__MODE__LARGE_BUFFER_SEGMENT:
				{
					return this->gData.uString.uData.uLargeString.gString->gChars + 
							this->gData.uString.uData.uLargeString.gOffset + 
							this->gData.uString.uData.uLargeString.gSegmentLength;
				}
				default:
					{CRX__BOOST_ASSERT(false); return NULL;}
			}
#endif
		}

				#pragma endregion STRING //}

		//-----------------------------------

				#pragma region ARRAY //{
		CRX_PUBLIC CRX__LIB__METHOD() Var::ArrayStlIterator Var::getArrayStartStlIterator()
		{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
			return this->gData.uArray.gDeque->begin();
#else
			if(crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) == 0)
				{return NULL;}
			else
				{return crx_varRing_getElementsPointer(CRX__VAR__GET_VARRING(this));}
#endif
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::ArrayConstantStlIterator Var::getArrayStartConstantStlIterator() const
		{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
			//VC6
			//return this->gData.uArray.gDeque->cbegin();
			return this->gData.uArray.gDeque->begin();
#else
			if(crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) == 0)
				{return NULL;}
			else
				{return crx_varRing_constantGetElementsPointer(CRX__VAR__GET_VARRING(this));}
#endif
		}

		CRX_PUBLIC CRX__LIB__METHOD() bool Var::hasArrayStlIteratorEnded(
				Var::ArrayConstantStlIterator pArrayConstantStlIterator) const
		{
			/*
			NOTE: CURRENTLY CODE IS WRITTEN DEFENSIVELY, ASSUMING THAT THE LENGTH OF THE STRING (NOT SIZE)
			CAN BE ZERO. ORIGINALLY THIS CAN ONLY HAPPEN WHEN THE STRING IS IN SMALL BUFFER MODE. HOWEVER,
			EVEN THAT SHOULD NO LONGER BE POSSIBLE. THE CODE IS WRITTEN THIS WAY AS NOT TO AFFECT CLIENT
			CODE SHOULD THE INTERNAL IMPLEMENTATION OF THINGS CHANGE.
			
			COMPARISON OF POINTER USING '>' AND '<' AND '<=' AND '>=' IS ASSUMED UNSAFE WHEN TWO POINTERS
			DO NOT POINT TO AREAS ON THE SAME OBJECT. THEREFORE CHECKS FIRST MAKE USE OF '=='. THE CHECKS
			WITH THE OTHER OPERATORS MIGHT BE REMOVED IN THE FUTURE IF THEY GIVE WRONG RESULTS. REMEMBER
			THIS IS A STL COMPATIBLE ITERATOR, AND STL COMPATIBLE ITERATORS ARE NOT EXPECTED TO BE SAFE
			PER THE VAR SPECIFICATION.
			*/

			if(CRX__VAR__GET_TYPE1(this) != CRX__VAR__TYPE_ARRAY)
				{return true;}

#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
			return (this->gData.uArray.gDeque->size() == 0) ||
					(((Var_ArrayConstantStlIterator)pArrayConstantStlIterator) == 
					/*VC6 this->gData.uArray.gDeque->cend()*/this->gData.uArray.gDeque->end());
#else
			size_t tLength = crx_varRing_getLength(CRX__VAR__GET_VARRING(this));

			if(tLength == 0)
				{return true;}
			else
			{
				Var const * tVar = crx_varRing_constantGetElementsPointer(CRX__VAR__GET_VARRING(this));
				Var::ArrayConstantStlIterator tArrayConstantStlIterator = pArrayConstantStlIterator;

				return ((tArrayConstantStlIterator == tVar) ||
						(tArrayConstantStlIterator == (tVar + tLength)) ||
						(tArrayConstantStlIterator < tVar) ||
						(tArrayConstantStlIterator >= (tVar + tLength)));
			}	
#endif
		}

		CRX_PUBLIC CRX__LIB__METHOD() Var::ArrayStlIterator Var::getArrayEndStlIterator()
		{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
			return this->gData.uArray.gDeque->end();
#else
			if(crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) == 0)
				{return NULL;}
			else
			{
				return crx_varRing_getElementsPointer(CRX__VAR__GET_VARRING(this)) + 
						crx_varRing_getLength(CRX__VAR__GET_VARRING(this));
			}
#endif
		}
		CRX_PUBLIC CRX__LIB__METHOD() Var::ArrayConstantStlIterator Var::getArrayEndStlIterator() const
		{
#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
			//return this->gData.uArray.gDeque->cend();
			return this->gData.uArray.gDeque->end();
#else
			if(crx_varRing_getLength(CRX__VAR__GET_VARRING(this)) == 0)
				{return NULL;}
			else
			{
				return crx_varRing_constantGetElementsPointer(CRX__VAR__GET_VARRING(this)) + 
						crx_varRing_getLength(CRX__VAR__GET_VARRING(this));
			}
#endif
		}
				#pragma endregion ARRAY //}
			#pragma endregion STL ITERATORS //}

		//-----------------------------------
	
			#pragma region GENERIC ITERATOR AND ALTERNATIVES //{
		
				#pragma region MAIN ITERATOR //{
		CRX_PUBLIC CRX__LIB__METHOD() Var::iterator Var::begin()
			{return Var::iterator(this);}
		CRX_PUBLIC CRX__LIB__METHOD() Var::iterator Var::end()
			{return Var::iterator(this, true);}

		CRX_PUBLIC CRX__LIB__METHOD() Var::const_iterator Var::cbegin() const
			{return Var::const_iterator(this);}
		CRX_PUBLIC CRX__LIB__METHOD() Var::const_iterator Var::cend() const
			{return Var::const_iterator(this, true);}
				#pragma endregion MAIN ITERATOR //}

		//-----------------------------------

				#pragma region ALTERNATIVE ITERATOR: STRING //{
		CRX_PUBLIC CRX__LIB__METHOD() Var::StringIterator Var::getStringStartIterator()
			{return Var::StringIterator(this);}
		CRX_PUBLIC CRX__LIB__METHOD() Var::StringIterator Var::getStringEndIterator()
			{return Var::StringIterator(this, true);}

		CRX_PUBLIC CRX__LIB__METHOD() Var::StringConstantIterator Var::getStringStartConstantIterator() const
			{return Var::StringConstantIterator(this);}
		CRX_PUBLIC CRX__LIB__METHOD() Var::StringConstantIterator Var::getStringEndConstantIterator() const
			{return Var::StringConstantIterator(this, true);}
				#pragma endregion ALTERNATIVE ITERATOR: STRING //}
			
			#pragma endregion GENERIC ITERATOR AND ALTERNATIVES //}

		//-----------------------------------

			#pragma region OTHERS //{
		CRX_PUBLIC CRX__LIB__METHOD() ::std::vector<::std::string> Var::getHashTableKeys()
		{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			::std::vector<::std::string> vReturn(this->gData.uHashTable.gUnorderedMap->size());
			::crx::ClassUnorderedMap<::std::string, Var>::t::const_iterator vIterator = 
					this->gData.uHashTable.gUnorderedMap->begin();

			while(vIterator != this->gData.uHashTable.gUnorderedMap->end())
			{
				vReturn.push_back((*vIterator).first);

				vIterator++;
			}
#else
			::std::vector<::std::string> vReturn;
			CRX__VAR__KHash_getKeys(this->gData.uHashTable.gKHash, vReturn);
#endif
			return vReturn;
		}
			#pragma endregion OTHERS //}
		#pragma endregion ITERATOR SUPPORT //}

		//-----------------------------------
		
		#pragma region VARJSON //{
		CRX_PUBLIC_STATIC CRX__LIB__METHOD() Var Var::parseVarJson(Var const & pVar__string)
		{
			if(CRX__VAR__GET_TYPE2(pVar__string) == CRX__VAR__TYPE_STRING)
			{
#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
				return Var::parseVarJson(pVar__string.gData.uString.uStd.gString.c_str(), 
						pVar__string.gData.uString.uStd.gString.size());
#else
				size_t tRemainingCharacters /*= ?*/;
				bool tIsNullTerminated /*= ?*/;
				char const * tChar = pVar__string.getCharPointerAndInfo(&tRemainingCharacters, &tIsNullTerminated);

				return Var::parseVarJson(tChar, 
						(tIsNullTerminated ? (tRemainingCharacters - 1) : tRemainingCharacters));
#endif
			}
			else
				{return pVar__string;}
		}
		CRX_PUBLIC_STATIC CRX__LIB__METHOD() Var Var::parseVarJson(::std::string const & pString)
			{return Var::parseVarJson(pString.c_str(), pString.size());}
		CRX_PUBLIC_STATIC CRX__LIB__METHOD() Var Var::parseVarJson(char const * pString)
			{return Var::parseVarJson(pString, ::strlen(pString));}
		CRX_PUBLIC_STATIC CRX__LIB__METHOD() Var Var::parseVarJson(char const * pChars, 
				size_t pSize)
		{
			if(pChars == NULL)
				{return Var(Var::Undefined());}
			
			size_t vRemainingSize = pSize;
			Var::VarJsonData vVarJsonData /*=?*/;
			Var vReturn;
			
			vVarJsonData.gCurrentChar = pChars;
			vVarJsonData.gRemainingSize = pSize;
			vVarJsonData.gChars = pChars;
			
			
			Var::parseVarJsonValue__skipWhiteSpacesAndComments(&vVarJsonData);
			
			if(vRemainingSize > 0)
				{Var::parseVarJsonValue(&vVarJsonData, &vReturn);}
			else
				{vReturn.setType(Var::TYPE__UNDEFINED);}

			return vReturn;
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() bool Var::parseVarJsonValue(
				Var::VarJsonData * CRX_NOT_NULL const pVarJsonData, Var * CRX_NOT_NULL pVar)
		{
			bool vIsError = false;

			Var::parseVarJsonValue__skipWhiteSpacesAndComments(pVarJsonData);

			if(pVarJsonData->gRemainingSize > 0)
			{
				if(*(pVarJsonData->gCurrentChar) == '{')
				{
					(pVarJsonData->gCurrentChar)++;
					(pVarJsonData->gRemainingSize)--;
					
					pVar->setType(Var::TYPE__HASH_TABLE);

					Var::parseVarJsonValue__skipWhiteSpacesAndComments(pVarJsonData);

					if(pVarJsonData->gRemainingSize > 0)
					{
						while(pVarJsonData->gRemainingSize > 0)
						{
							Var tKey /*= Var()*/;

							if((*(pVarJsonData->gCurrentChar) == '"') || 
									(*(pVarJsonData->gCurrentChar) == '\'') || 
									(*(pVarJsonData->gCurrentChar) == '`'))
							{
								vIsError = Var::parseVarJsonValue(pVarJsonData, &tKey);

								if(!vIsError)
								{
									Var::parseVarJsonValue__skipWhiteSpacesAndComments(pVarJsonData);

									if((pVarJsonData->gRemainingSize > 0) && 
											(*(pVarJsonData->gCurrentChar) == ':'))
									{
										(pVarJsonData->gCurrentChar)++;
										(pVarJsonData->gRemainingSize)--;

										vIsError = Var::parseVarJsonValue(pVarJsonData, &((*pVar)[tKey]));

										if(!vIsError)
										{
											Var::parseVarJsonValue__skipWhiteSpacesAndComments(pVarJsonData);

											if(pVarJsonData->gRemainingSize > 0)
											{
												if(*(pVarJsonData->gCurrentChar) == ',')
												{
													(pVarJsonData->gCurrentChar)++;
													(pVarJsonData->gRemainingSize)--;

													Var::parseVarJsonValue__skipWhiteSpacesAndComments(
															pVarJsonData);

													if(pVarJsonData->gRemainingSize == 0)
													{
														vIsError = true;
														
														Var::reportVarJsonError(pVarJsonData, 
																"Expected Value or '}'", &((*pVar)[tKey]));
													}
									
												}
												else if(*(pVarJsonData->gCurrentChar) == '}')
												{
													(pVarJsonData->gCurrentChar)++;
													(pVarJsonData->gRemainingSize)--;

													break;
												}
												else
												{
													vIsError = true;

													Var::reportVarJsonError(pVarJsonData, 
															"Expected hash table delimiter. ',' or '}'", 
															&((*pVar)[tKey]));
												}
											}
											else
											{
												vIsError = true;

												Var::reportVarJsonError(pVarJsonData, 
														"Expected hash table delimiter. ',' or '}'",
														&((*pVar)[tKey]));
											}
										}
									}
									else
									{
										vIsError = true;

										Var::reportVarJsonError(pVarJsonData, 
												"Expected key value pair delimiter. ':'", &((*pVar)[tKey]));
									}

									
#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
									if(vIsError)
									{
										*pVar = (*pVar)[tKey];
										/*TODO: REMOVE ELEMENT*/
									}
#endif
								}
#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
								else
								{
									*pVar = tKey;
									/*TODO: REMOVE ELEMENT*/
								}
#endif
							}
							else if(*(pVarJsonData->gCurrentChar) == '}')
							{
								(pVarJsonData->gCurrentChar)++;
								(pVarJsonData->gRemainingSize)--;

								break;
							}
							else
							{
								vIsError = true;

								Var::reportVarJsonError(pVarJsonData, 
										"Expected string opening character. \" or ' or `", pVar);
							}

							if(vIsError)
								{break;}
						}
					}
					else
					{
						vIsError = true;

						Var::reportVarJsonError(pVarJsonData, "Expected '}'", pVar);
					}
				}
				else if(*(pVarJsonData->gCurrentChar) == '[')
				{
					(pVarJsonData->gCurrentChar)++;
					(pVarJsonData->gRemainingSize)--;

					pVar->setType(Var::TYPE__ARRAY);

					Var::parseVarJsonValue__skipWhiteSpacesAndComments(pVarJsonData);

					if(pVarJsonData->gRemainingSize > 0)
					{
						if(*(pVarJsonData->gCurrentChar) != ']')
						{
							while(pVarJsonData->gRemainingSize > 0)
							{
								pVar->push(Var(Var::Undefined()));

								vIsError = Var::parseVarJsonValue(pVarJsonData, 
										&((*pVar)[pVar->getSize() - 1]));

								if(!vIsError)
								{
									if(*(pVarJsonData->gCurrentChar) == ',')
									{
										(pVarJsonData->gCurrentChar)++;
										(pVarJsonData->gRemainingSize)--;
										
										Var::parseVarJsonValue__skipWhiteSpacesAndComments(pVarJsonData);

										if(pVarJsonData->gRemainingSize == 0)
										{
											vIsError = true;

											Var::reportVarJsonError(pVarJsonData, 
													"Expected value or ']'", pVar);
										}
									}
									else if(*(pVarJsonData->gCurrentChar) == ']')
									{
										(pVarJsonData->gCurrentChar)++;
										(pVarJsonData->gRemainingSize)--;

										break;
									}
									else
									{
										vIsError = true;

										Var::reportVarJsonError(pVarJsonData, 
												"Expected ',' or ']'", pVar);
									}
								}
#if(CRX__VAR__ERROR_MODE == CRX__VAR__OPTION__ERROR_MODE__PROPOGATER)
								else
									{*pVar = (*pVar)[pVar->getSize() - 1];}							
#endif
								if(vIsError)
									{break;}
							}
						}
						else
						{
							(pVarJsonData->gCurrentChar)++;
							(pVarJsonData->gRemainingSize)--;
						}
					}
					else
					{
						vIsError = true;

						Var::reportVarJsonError(pVarJsonData, "Expected ']'", pVar);
					}
				}
				else if((*(pVarJsonData->gCurrentChar) == '"') ||
						(*(pVarJsonData->gCurrentChar) == '\'') || 
						(*(pVarJsonData->gCurrentChar) == '`'))
				{
					char tChar = *(pVarJsonData->gCurrentChar);

					pVar->setType(Var::TYPE__STRING);
					//pVar->append(pVarJsonData->gCurrentChar, 1);

					(pVarJsonData->gCurrentChar)++;
					(pVarJsonData->gRemainingSize)--;

					if(*(pVarJsonData->gCurrentChar) != tChar)
					{
						while(pVarJsonData->gRemainingSize > 0)
						{
							if(*(pVarJsonData->gCurrentChar) == '\\')
							{
								char tChars[5] /*= ?*/;
								bool tIsCodePoint = false;
								uint32_t tCodePoint = 0;

								(pVarJsonData->gCurrentChar)++;
								(pVarJsonData->gRemainingSize)--;
								
								if((pVarJsonData->gRemainingSize > 4) && 
										((*(pVarJsonData->gCurrentChar) == 'u') ||
										(*(pVarJsonData->gCurrentChar) == 'U')))
								{
									if((Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar) + 1)] > -1)&& 
										(Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar) + 2)] > -1) &&
										(Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar) + 3)] > -1) &&
										(Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar) + 4)] > -1))
									{
										tIsCodePoint = true;

										(pVarJsonData->gCurrentChar)++;

										tCodePoint = Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];
										tCodePoint = (tCodePoint << 4) | 
												Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];
										tCodePoint = (tCodePoint << 4) | 
												Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];
										tCodePoint = (tCodePoint << 4) | 
												Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];

										(pVarJsonData->gRemainingSize) = (pVarJsonData->gRemainingSize) - 5;
										
										if((tCodePoint >= 0xD800ul) || (tCodePoint <= 0xD800ul))
										{//WE EXPECT HERE UTF16 ENCODING, BIG ENDIAN
											if((pVarJsonData->gRemainingSize > 5) && 
													(*(pVarJsonData->gCurrentChar) == '\\') &&
													(*(pVarJsonData->gCurrentChar + 1) == 'u') &&
													(Var::StaticPrivateVars::gHexCharacterToValueArray[
															*((pVarJsonData->gCurrentChar) + 2)] > -1)&& 
													(Var::StaticPrivateVars::gHexCharacterToValueArray[
															*((pVarJsonData->gCurrentChar) + 3)] > -1) &&
													(Var::StaticPrivateVars::gHexCharacterToValueArray[
															*((pVarJsonData->gCurrentChar) + 4)] > -1) &&
													(Var::StaticPrivateVars::gHexCharacterToValueArray[
															*((pVarJsonData->gCurrentChar) + 5)] > -1))
											{
												uint32_t tCodePoint2 = 0;

												tCodePoint2 = Var::StaticPrivateVars::gHexCharacterToValueArray[
														*((pVarJsonData->gCurrentChar)++)];
												tCodePoint2 = (tCodePoint2 << 4) | 
														Var::StaticPrivateVars::gHexCharacterToValueArray[
														*((pVarJsonData->gCurrentChar)++)];
												tCodePoint2 = (tCodePoint2 << 4) | 
														Var::StaticPrivateVars::gHexCharacterToValueArray[
														*((pVarJsonData->gCurrentChar)++)];
												tCodePoint2 = (tCodePoint2 << 4) | 
														Var::StaticPrivateVars::gHexCharacterToValueArray[
														*((pVarJsonData->gCurrentChar)++)];
														
												if((tCodePoint2 >= 0xDC00ul) && (tCodePoint2 <= 0xDFFFul))
												{
													tCodePoint = (((tCodePoint & 0x3FFul) << 10) |
															(tCodePoint2 & 0x3FFul)) + 0x10000ul;
												}
												else
													{tCodePoint = 65533;}

												(pVarJsonData->gRemainingSize) = (pVarJsonData->gRemainingSize) - 6;
											}
											else
												{tCodePoint = 65533;}
										}
										else
										{
											if(!CRX__C__CHAR__IS_CODE_POINT_VALID_FOR_UTF(tCodePoint))
												{tCodePoint = 65533;}
										}

										//CRX__C__CHAR__FAST_INSERT_UTF8_CHAR(tCodePoint, tChars, CRXM__FALSE)
										
										//pVarJsonData->gRemainingSize = pVarJsonData->gRemainingSize - 4;

										//(*pVar) += tChars;
									}
									else if((tChar == '`') &&
											(pVarJsonData->gRemainingSize > 7) && 
											(*(pVarJsonData->gCurrentChar + 1) == ':') &&
											((*(pVarJsonData->gCurrentChar + 2) == 'x') ||
													(*(pVarJsonData->gCurrentChar + 2) == 'X')) &&
											(Var::StaticPrivateVars::gHexCharacterToValueArray[
													*((pVarJsonData->gCurrentChar) + 3)] > -1)&& 
											(Var::StaticPrivateVars::gHexCharacterToValueArray[
													*((pVarJsonData->gCurrentChar) + 4)] > -1) &&
											(Var::StaticPrivateVars::gHexCharacterToValueArray[
													*((pVarJsonData->gCurrentChar) + 5)] > -1) &&
											(Var::StaticPrivateVars::gHexCharacterToValueArray[
													*((pVarJsonData->gCurrentChar) + 6)] > -1) &&
											(Var::StaticPrivateVars::gHexCharacterToValueArray[
													*((pVarJsonData->gCurrentChar) + 7)] > -1))
									{
										tIsCodePoint = true;

										pVarJsonData->gCurrentChar = pVarJsonData->gCurrentChar + 3;

										tCodePoint = Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];
										tCodePoint = (tCodePoint << 4) | 
												Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];
										tCodePoint = (tCodePoint << 4) | 
												Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];
										tCodePoint = (tCodePoint << 4) | 
												Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];
										tCodePoint = (tCodePoint << 4) | 
												Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];

										pVarJsonData->gRemainingSize = pVarJsonData->gRemainingSize - 8;
									}
									else if((tChar == '`') &&
											(pVarJsonData->gRemainingSize > 8) && 
											(*(pVarJsonData->gCurrentChar + 1) == ':') &&
											(*(pVarJsonData->gCurrentChar + 2) <= '9') &&
											(*(pVarJsonData->gCurrentChar + 2) >= '0') &&
											(*(pVarJsonData->gCurrentChar + 3) <= '9') &&
											(*(pVarJsonData->gCurrentChar + 3) >= '0') &&
											(*(pVarJsonData->gCurrentChar + 4) <= '9') &&
											(*(pVarJsonData->gCurrentChar + 4) >= '0') &&
											(*(pVarJsonData->gCurrentChar + 5) <= '9') &&
											(*(pVarJsonData->gCurrentChar + 5) >= '0') &&
											(*(pVarJsonData->gCurrentChar + 6) <= '9') &&
											(*(pVarJsonData->gCurrentChar + 6) >= '0') &&
											(*(pVarJsonData->gCurrentChar + 7) <= '9') &&
											(*(pVarJsonData->gCurrentChar + 7) >= '0') &&
											(*(pVarJsonData->gCurrentChar + 8) <= '9') &&
											(*(pVarJsonData->gCurrentChar + 8) >= '0'))
									{
										tIsCodePoint = true;

										pVarJsonData->gCurrentChar = pVarJsonData->gCurrentChar + 2;

										tCodePoint = Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];
										tCodePoint = (tCodePoint << 4) | 
												Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];
										tCodePoint = (tCodePoint << 4) | 
												Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];
										tCodePoint = (tCodePoint << 4) | 
												Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];
										tCodePoint = (tCodePoint << 4) | 
												Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];
										tCodePoint = (tCodePoint << 4) | 
												Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];
										tCodePoint = (tCodePoint << 4) | 
												Var::StaticPrivateVars::gHexCharacterToValueArray[
												*((pVarJsonData->gCurrentChar)++)];

										pVarJsonData->gRemainingSize = pVarJsonData->gRemainingSize - 9;
									}
								}
								
								if(tIsCodePoint)
								{
									CRX__C__CHAR__FAST_INSERT_UTF8_CHAR(tCodePoint, tChars, CRXM__FALSE)
								}
								else if(pVarJsonData->gRemainingSize > 1)
								{
									(pVarJsonData->gCurrentChar)++;
									(pVarJsonData->gRemainingSize)--;

									if(*(pVarJsonData->gCurrentChar) == '"')
									{
										tChars[0] = '"';
										tChars[1] = '\0';

										(*pVar) += tChars;
										(pVarJsonData->gCurrentChar)++;
										(pVarJsonData->gRemainingSize)--;
									}
									else if(*(pVarJsonData->gCurrentChar) == '\'')
									{
										tChars[0] = '\'';
										tChars[1] = '\0';

										(*pVar) += *tChars;
										(pVarJsonData->gCurrentChar)++;
										(pVarJsonData->gRemainingSize)--;
									}
									else if(*(pVarJsonData->gCurrentChar) == '`')
									{
										tChars[0] = '`';
										tChars[1] = '\0';

										(*pVar) += tChars;
										(pVarJsonData->gCurrentChar)++;
										(pVarJsonData->gRemainingSize)--;
									}
									else if(*(pVarJsonData->gCurrentChar) == '\\')
									{
										tChars[0] = '\\';
										tChars[1] = '\0';

										(*pVar) += tChars;
										(pVarJsonData->gCurrentChar)++;
										(pVarJsonData->gRemainingSize)--;
									}
									else if(*(pVarJsonData->gCurrentChar) == '/')
									{
										tChars[0] = '/';
										tChars[1] = '\0';

										(*pVar) += tChars;
										(pVarJsonData->gCurrentChar)++;
										(pVarJsonData->gRemainingSize)--;
									}
									else if(*(pVarJsonData->gCurrentChar) == 'b')
									{
										tChars[0] = '\b';
										tChars[1] = '\0';

										(*pVar) += tChars;
										(pVarJsonData->gCurrentChar)++;
										(pVarJsonData->gRemainingSize)--;
									}
									else if(*(pVarJsonData->gCurrentChar) == 'f')
									{
										tChars[0] = '\f';
										tChars[1] = '\0';

										(*pVar) += tChars;
										(pVarJsonData->gCurrentChar)++;
										(pVarJsonData->gRemainingSize)--;
									}
									else if(*(pVarJsonData->gCurrentChar) == 'n')
									{
										tChars[0] = '\n';
										tChars[1] = '\0';

										(*pVar) += tChars;
										(pVarJsonData->gCurrentChar)++;
										(pVarJsonData->gRemainingSize)--;
									}
									else if(*(pVarJsonData->gCurrentChar) == 'r')
									{
										tChars[0] = '\r';
										tChars[1] = '\0';

										(*pVar) += tChars;
										(pVarJsonData->gCurrentChar)++;
										(pVarJsonData->gRemainingSize)--;
									}
									else if(*(pVarJsonData->gCurrentChar) == 't')
									{
										tChars[0] = '\t';
										tChars[1] = '\0';

										(*pVar) += tChars;
										(pVarJsonData->gCurrentChar)++;
										(pVarJsonData->gRemainingSize)--;
									}
									else
									{
										char tChars2[30] = "Invalid escaped character '";
										
										tChars2[27] = *(pVarJsonData->gCurrentChar);
										tChars2[28] = '\'';
										tChars2[29] = '\0';

										vIsError = true;

										Var::reportVarJsonError(pVarJsonData, tChars2, pVar);
									}
								}
							}
							else
							{
								char tChars[2] /*= ?*/;

								tChars[0] = *(pVarJsonData->gCurrentChar);
								tChars[1] = '\0';

								(pVarJsonData->gCurrentChar)++;
								(pVarJsonData->gRemainingSize)--;

								if(tChars[0] != tChar)
									{(*pVar) += tChars;}
								else
									{break;}
							}
						}
					}
					else
					{
						//vIsError = true;

						//Var::reportVarJsonError(pVarJsonData, "Expected end of string", pVar);
					}
				}
				else if(((*(pVarJsonData->gCurrentChar) >= '0') && 
						(*(pVarJsonData->gCurrentChar) <= '9')) || 
						(*(pVarJsonData->gCurrentChar) == '+') || 
						((*(pVarJsonData->gCurrentChar) == '-') &&
						(pVarJsonData->gRemainingSize > 1) &&
						(*(pVarJsonData->gCurrentChar + 1) >= '0') &&
						(*(pVarJsonData->gCurrentChar + 1) <= '9')))
				{
					pVar->setType(Var::TYPE__NUMBER);

					if(Var::isNumberStringAnIntegerIfValid((pVarJsonData->gCurrentChar), 
							(pVarJsonData->gRemainingSize)))
					{
#if(!CRX__VAR__IS_EMULATED_INT_USED)
						size_t tLength = 0;
						char const * vChar = (pVarJsonData->gCurrentChar);
						CRX__VAR__UNIFIED_SIGNED_INT tResult =
								CRX__VAR__LOOSE_CONVERT_TO_UNIFIED_INT((pVarJsonData->gCurrentChar), 
								&vIsError);
						
								
						while((*vChar >= '0') && (*(vChar++) <= '9'))
							{tLength++;}

						pVarJsonData->gCurrentChar = (pVarJsonData->gCurrentChar) + tLength;
						pVarJsonData->gRemainingSize = pVarJsonData->gRemainingSize - tLength;

						if(!vIsError)
							{*pVar = tResult;}
						else
						{
							vIsError = true;

							Var::reportVarJsonError(pVarJsonData, "Error parsing integer", pVar);
						}
#else
						int _f;
						size_t tLength = 0;
						char const * vChar = (pVarJsonData->gCurrentChar);
						double tResult = 0.0;

						while((*vChar >= '0') && (*(vChar++) <= '9'))
							{tLength++;}
						
						tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
								StringToDouble(pVarJsonData->gCurrentChar,
								CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(tLength), &_f);

						pVarJsonData->gCurrentChar = pVarJsonData->gCurrentChar + tLength;
						pVarJsonData->gRemainingSize = pVarJsonData->gRemainingSize - tLength;

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult) &&
								(tResult <= CRX__VAR__MAX_SAFE_INTEGER_TO_DOUBLE) &&
								(tResult >= CRX__VAR__MIN_SAFE_INTEGER_TO_DOUBLE))
						{
							CRX__VAR__SET_TYPE(pVar, CRX__VAR__TYPE_EMULATED_INT);
							pVar->gData.uIntegral.uDouble = tResult;
						}
						else
						{
							vIsError = true;

							Var::reportVarJsonError(pVarJsonData, "Error parsing integer", pVar);
						}
#endif
					}
					else
					{
						int _f;
						size_t tLength = 0;
						double tResult = Var::StaticPrivateVars::gStringToDoubleConverter__loose->
								StringToDouble(pVarJsonData->gCurrentChar,
								CRX__VAR__GET_LENGTH_FROM_SIZET_FOR_STRINGTODOUBLE(tLength), &_f);

						if(!CRX__VAR__IS_DOUBLE_A_PARSE_ERROR(tResult))
							{pVar->gData.uIntegral.uDouble = tResult;}
						else
						{
							vIsError = true;

							Var::reportVarJsonError(pVarJsonData, "Error parsing integer", pVar);
						}
					}
				}
				else if((*(pVarJsonData->gCurrentChar) == 'b') || 
						(*(pVarJsonData->gCurrentChar) == 'B'))
				{
					unsigned char tUnsignedChar = 0;

					(pVarJsonData->gCurrentChar)++;
					(pVarJsonData->gRemainingSize)--;

					for(size_t tI = 0; tI < 8; tI++)
					{
						if(*(pVarJsonData->gCurrentChar) == '1')
							{tUnsignedChar = (tUnsignedChar << 1) + 1;}
						else if(*(pVarJsonData->gCurrentChar) == '0')
							{tUnsignedChar = (tUnsignedChar << 1);}
						else
						{
							vIsError = true;

							Var::reportVarJsonError(pVarJsonData, "Expected 0 or 1", pVar);
						}
						
						(pVarJsonData->gCurrentChar)++;
					}
					
					if(!vIsError)
						{*pVar = tUnsignedChar;}
				}
				else if((*(pVarJsonData->gCurrentChar) == 'f') || 
						(*(pVarJsonData->gCurrentChar) == 't') || 
						(*(pVarJsonData->gCurrentChar) == 'n') ||
						(*(pVarJsonData->gCurrentChar) == 'i') || 
						(*(pVarJsonData->gCurrentChar) == 'F') || 
						(*(pVarJsonData->gCurrentChar) == 'T') || 
						(*(pVarJsonData->gCurrentChar) == 'N') || 
						(*(pVarJsonData->gCurrentChar) == 'I') ||
						(*(pVarJsonData->gCurrentChar) == '-'))
				{
					bool tIsFound = false;

					while((pVarJsonData->gRemainingSize > 0) && 
							((*(pVarJsonData->gCurrentChar) == ' ') || 
							(*(pVarJsonData->gCurrentChar) == '\n') || 
							(*(pVarJsonData->gCurrentChar) == '\r') ||
							(*(pVarJsonData->gCurrentChar) == '\t')))
					{
						(pVarJsonData->gCurrentChar)++;
						(pVarJsonData->gRemainingSize)--;
					}

					if((pVarJsonData->gRemainingSize > 0) && 
							((*(pVarJsonData->gCurrentChar) == 't') || 
							(*(pVarJsonData->gCurrentChar) == 'T')))
					{
						(pVarJsonData->gCurrentChar)++;
						(pVarJsonData->gRemainingSize)--;

						if((pVarJsonData->gRemainingSize > 0) && 
								((*(pVarJsonData->gCurrentChar) == 'r') || 
								(*(pVarJsonData->gCurrentChar) == 'R')))
						{
							(pVarJsonData->gCurrentChar)++;
							(pVarJsonData->gRemainingSize)--;

							if((pVarJsonData->gRemainingSize > 0) && 
									((*(pVarJsonData->gCurrentChar) == 'u') || 
									(*(pVarJsonData->gCurrentChar) == 'U')))
							{
								(pVarJsonData->gCurrentChar)++;
								(pVarJsonData->gRemainingSize)--;

								if((pVarJsonData->gRemainingSize > 0) && 
										((*(pVarJsonData->gCurrentChar) == 'e') || 
										(*(pVarJsonData->gCurrentChar) == 'E')))
								{
									*pVar = true;
									tIsFound = true;
								}
							}
						}
					}
					else if((pVarJsonData->gRemainingSize > 0) && 
							((*(pVarJsonData->gCurrentChar) == 'f') || 
							(*(pVarJsonData->gCurrentChar) == 'F')))
					{
						(pVarJsonData->gCurrentChar)++;
						(pVarJsonData->gRemainingSize)--;

						if((pVarJsonData->gRemainingSize > 0) && 
								((*(pVarJsonData->gCurrentChar) == 'a') || 
								(*(pVarJsonData->gCurrentChar) == 'A')))
						{
							(pVarJsonData->gCurrentChar)++;
							(pVarJsonData->gRemainingSize)--;

							if((pVarJsonData->gRemainingSize > 0) && 
									((*(pVarJsonData->gCurrentChar) == 'l') || 
									(*(pVarJsonData->gCurrentChar) == 'L')))
							{
								(pVarJsonData->gCurrentChar)++;
								(pVarJsonData->gRemainingSize)--;

								if((pVarJsonData->gRemainingSize > 0) && 
										((*(pVarJsonData->gCurrentChar) == 's') || 
										(*(pVarJsonData->gCurrentChar) == 'S')))
								{
									(pVarJsonData->gCurrentChar)++;
									(pVarJsonData->gRemainingSize)--;

									if((pVarJsonData->gRemainingSize > 0) && 
											((*(pVarJsonData->gCurrentChar) == 'e') || 
											(*(pVarJsonData->gCurrentChar) == 'E')))
									{
										*pVar = true;
										tIsFound = true;
									}
								}
							}
						}
					}
					else if((pVarJsonData->gRemainingSize > 0) && 
							((*(pVarJsonData->gCurrentChar) == 'n') || 
							(*(pVarJsonData->gCurrentChar) == 'N')))
					{
						(pVarJsonData->gCurrentChar)++;
						(pVarJsonData->gRemainingSize)--;

						if((pVarJsonData->gRemainingSize > 0) && 
								((*(pVarJsonData->gCurrentChar) == 'u') || 
								(*(pVarJsonData->gCurrentChar) == 'U')))
						{
							(pVarJsonData->gCurrentChar)++;
							(pVarJsonData->gRemainingSize)--;

							if((pVarJsonData->gRemainingSize > 0) && 
									((*(pVarJsonData->gCurrentChar) == 'l') || 
									(*(pVarJsonData->gCurrentChar) == 'L')))
							{
								(pVarJsonData->gCurrentChar)++;
								(pVarJsonData->gRemainingSize)--;

								if((pVarJsonData->gRemainingSize > 0) && 
										((*(pVarJsonData->gCurrentChar) == 'l') || 
										(*(pVarJsonData->gCurrentChar) == 'L')))
								{
									pVar->setType(Var::TYPE__NIL);
									tIsFound = true;
								}
							}
						}
						else if((pVarJsonData->gRemainingSize > 0) && ((*(pVarJsonData->gCurrentChar) == 'a') || 
								(*(pVarJsonData->gCurrentChar) == 'A')))
						{
							(pVarJsonData->gCurrentChar)++;
							(pVarJsonData->gRemainingSize)--;

							if((pVarJsonData->gRemainingSize > 0) && ((*(pVarJsonData->gCurrentChar) == 'n') || 
									(*(pVarJsonData->gCurrentChar) == 'N')))
							{
								*pVar = NAN;
								tIsFound = true;
							}
						}
					}
					else if((pVarJsonData->gRemainingSize > 0) && 
							((*(pVarJsonData->gCurrentChar) == 'i') || 
							(*(pVarJsonData->gCurrentChar) == 'I')))
					{
						(pVarJsonData->gCurrentChar)++;
						(pVarJsonData->gRemainingSize)--;

						if((pVarJsonData->gRemainingSize > 0) && ((*(pVarJsonData->gCurrentChar) == 'n') || 
								(*(pVarJsonData->gCurrentChar) == 'N')))
						{
							(pVarJsonData->gCurrentChar)++;
							(pVarJsonData->gRemainingSize)--;

							if((pVarJsonData->gRemainingSize > 0) && ((*(pVarJsonData->gCurrentChar) == 'f') || 
									(*(pVarJsonData->gCurrentChar) == 'F')))
							{
								//pVar = INFINITY;
								//tIsFound = true;

								if((pVarJsonData->gRemainingSize > 1) && 
										((*(pVarJsonData->gCurrentChar + 1) == 'i') || 
										(*(pVarJsonData->gCurrentChar + 1) == 'I')))
								{
									pVarJsonData->gCurrentChar = pVarJsonData->gCurrentChar + 2;
									pVarJsonData->gRemainingSize = pVarJsonData->gRemainingSize + 2;

									if((pVarJsonData->gRemainingSize > 0) && 
											((*(pVarJsonData->gCurrentChar) == 'n') || 
											(*(pVarJsonData->gCurrentChar) == 'N')))
									{
										(pVarJsonData->gCurrentChar)++;
										(pVarJsonData->gRemainingSize)--;

										if((pVarJsonData->gRemainingSize > 0) && 
												((*(pVarJsonData->gCurrentChar) == 'i') || 
												(*(pVarJsonData->gCurrentChar) == 'I')))
										{
											(pVarJsonData->gCurrentChar)++;
											(pVarJsonData->gRemainingSize)--;

											if((pVarJsonData->gRemainingSize > 0) && 
													((*(pVarJsonData->gCurrentChar) == 't') || 
													(*(pVarJsonData->gCurrentChar) == 'T')))
											{
												(pVarJsonData->gCurrentChar)++;
												(pVarJsonData->gRemainingSize)--;

												if((pVarJsonData->gRemainingSize > 0) && 
														((*(pVarJsonData->gCurrentChar) == 'y') || 
														(*(pVarJsonData->gCurrentChar) == 'Y')))
												{
													*pVar = -INFINITY;
													tIsFound = true;
												}
											}
										}
									}
								}
								else
								{
									*pVar = -INFINITY;
									tIsFound = true;
								}
							}
						}
					}
					else if((pVarJsonData->gRemainingSize > 0) && 
							(*(pVarJsonData->gCurrentChar) == '-'))
					{
						(pVarJsonData->gCurrentChar)++;
						(pVarJsonData->gRemainingSize)--;

						if((pVarJsonData->gRemainingSize > 0) && 
								((*(pVarJsonData->gCurrentChar) == 'i') || 
								(*(pVarJsonData->gCurrentChar) == 'I')))
						{
							(pVarJsonData->gCurrentChar)++;
							(pVarJsonData->gRemainingSize)--;

							if((pVarJsonData->gRemainingSize > 0) && 
									((*(pVarJsonData->gCurrentChar) == 'n') || 
									(*(pVarJsonData->gCurrentChar) == 'N')))
							{
								(pVarJsonData->gCurrentChar)++;
								(pVarJsonData->gRemainingSize)--;

								if((pVarJsonData->gRemainingSize > 0) && 
										((*(pVarJsonData->gCurrentChar) == 'f') || 
										(*(pVarJsonData->gCurrentChar) == 'F')))
								{
									//pVar = -INFINITY;
									//tIsFound = true;

									if((pVarJsonData->gRemainingSize > 1) && 
											((*(pVarJsonData->gCurrentChar + 1) == 'i') || 
											(*(pVarJsonData->gCurrentChar + 1) == 'I')))
									{
										pVarJsonData->gCurrentChar = pVarJsonData->gCurrentChar + 2;
										pVarJsonData->gRemainingSize = pVarJsonData->gRemainingSize + 2;

										if((pVarJsonData->gRemainingSize > 0) && 
												((*(pVarJsonData->gCurrentChar) == 'n') || 
												(*(pVarJsonData->gCurrentChar) == 'N')))
										{
											(pVarJsonData->gCurrentChar)++;
											(pVarJsonData->gRemainingSize)--;

											if((pVarJsonData->gRemainingSize > 0) && 
													((*(pVarJsonData->gCurrentChar) == 'i') || 
													(*(pVarJsonData->gCurrentChar) == 'I')))
											{
												(pVarJsonData->gCurrentChar)++;
												(pVarJsonData->gRemainingSize)--;

												if((pVarJsonData->gRemainingSize > 0) && 
														((*(pVarJsonData->gCurrentChar) == 't') || 
														(*(pVarJsonData->gCurrentChar) == 'T')))
												{
													(pVarJsonData->gCurrentChar)++;
													(pVarJsonData->gRemainingSize)--;

													if((pVarJsonData->gRemainingSize > 0) && 
															((*(pVarJsonData->gCurrentChar) == 'y') || 
															(*(pVarJsonData->gCurrentChar) == 'Y')))
													{
														*pVar = -INFINITY;
														tIsFound = true;
													}
												}
											}
										}
									}
									else
									{
										*pVar = -INFINITY;
										tIsFound = true;
									}
								}
							}
						}
					}
		
					if(!tIsFound)
					{
						vIsError = true;

						Var::reportVarJsonError(pVarJsonData, "Unexpected Character", pVar);
					}
					else
					{
						(pVarJsonData->gCurrentChar)++;
						(pVarJsonData->gRemainingSize)--;
					}
				}
				else
				{
					vIsError = true;

					Var::reportVarJsonError(pVarJsonData, "Unexpected Character", pVar);
				}
			}
			else
			{
				vIsError = true;

				Var::reportVarJsonError(pVarJsonData, "No Character Found Parsing Value", pVar);
			}
			

			return vIsError;
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() void Var::parseVarJsonValue__skipWhiteSpacesAndComments(
				Var::VarJsonData * CRX_NOT_NULL const pVarJsonData)
		{
			while(pVarJsonData->gRemainingSize > 0)
			{
				while((pVarJsonData->gRemainingSize > 0) && ((*(pVarJsonData->gCurrentChar) == ' ') || 
						(*(pVarJsonData->gCurrentChar) == '\n') || (*(pVarJsonData->gCurrentChar) == '\r') || 
						(*(pVarJsonData->gCurrentChar) == '\t')))
				{
					(pVarJsonData->gCurrentChar)++;
					(pVarJsonData->gRemainingSize)--;
				}
				
				if((pVarJsonData->gRemainingSize > 1) && (*(pVarJsonData->gCurrentChar) == '/') && 
						(*(pVarJsonData->gCurrentChar + 1) == '*'))
				{
					pVarJsonData->gCurrentChar = pVarJsonData->gCurrentChar + 2;
					pVarJsonData->gRemainingSize = pVarJsonData->gRemainingSize - 2;

					while(pVarJsonData->gRemainingSize > 0)
					{
						if((*(pVarJsonData->gCurrentChar) != '*') || (pVarJsonData->gRemainingSize == 1) || 
								(*(pVarJsonData->gCurrentChar + 1) != '/'))
						{
							(pVarJsonData->gCurrentChar)++;
							(pVarJsonData->gRemainingSize)--;
						}
						else
						{
							pVarJsonData->gCurrentChar = pVarJsonData->gCurrentChar + 2;
							pVarJsonData->gRemainingSize = pVarJsonData->gRemainingSize - 2;
							
							break;
						}
					}
					
					if(!((pVarJsonData->gRemainingSize > 0) && ((*(pVarJsonData->gCurrentChar) == ' ') || 
							(*(pVarJsonData->gCurrentChar) == '\n') || (*(pVarJsonData->gCurrentChar) == '\r') || 
							(*(pVarJsonData->gCurrentChar) == '\t'))))
						{break;}
				}
				else
					{break;}
			}
		}
		CRX_PRIVATE_STATIC CRX__LIB__METHOD() void Var::reportVarJsonError(
				Var::VarJsonData * const pVarJsonData, char const * CRX_NOT_NULL pMessage, 
				Var * CRX_NOT_NULL pVar)
		{
			::std::string vMessage;
			char const * vChar = pVarJsonData->gChars;
			char const * vChars__errorChars = pVarJsonData->gChars;
			int vLineNumber = 1;
			int vCharacterNumber = 0;
			int tCount = 0;
			
			
			while(vChar != pVarJsonData->gCurrentChar)
			{
				if(*vChar == '\n')
				{
					vLineNumber = vLineNumber + 1;
					vCharacterNumber = 0;
				}
				else
					{vCharacterNumber = vCharacterNumber + 1;}

				if(tCount == 200)
					{vChars__errorChars++;}
				else
					{tCount = tCount + 1;}
				
				vChar++;
			}
			

			char tLineNumberString[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT32] /*= ?*/;
			char tCharacterNumberString[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT32] /*= ?*/;

			Var::stringifyInt32(vLineNumber, tLineNumberString, 
					CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT32);
			Var::stringifyInt32(vCharacterNumber, tCharacterNumberString, 
					CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_SIGNED_INT32);

			CRX__VAR__REPORT_ERROR2(pVar, CRX__VAR__ERROR__MALFORMED_VARJSON, 
					(::std::string("VAR JSON ERROR AT LINE ") + tLineNumberString + 
					::std::string(", AT CHARACTER ") + tCharacterNumberString + 
					::std::string(", AFTER TEXT: \n\n") + ::std::string(vChars__errorChars, tCount)),
					CRX__VAR__NO_OP_FOR_ERROR);
		}

		CRX_PUBLIC CRX__LIB__METHOD() Var Var::convertToVarJsonUtf8String()
		{
			Var vReturn = "";
			
			Var::_convertToVarJsonUtf8String(&vReturn);

			return vReturn;
		}
		CRX_PRIVATE CRX__LIB__METHOD() void Var::_convertToVarJsonUtf8String(Var * CRX_NOT_NULL pString)
		{
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					size_t tRemainingCharacters /*= ?*/;
					char const * tChar /*= ?*/;
#if(!CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					bool tIsNullTerminated /*= ?*/;
#endif

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					tRemainingCharacters = this->gData.uString.uStd.gString.size();
					tChar = this->gData.uString.uStd.gString.c_str();
#else				
					tChar = this->getCharPointerAndInfo(&tRemainingCharacters, &tIsNullTerminated);
					
					if(tIsNullTerminated)
						{tRemainingCharacters = tRemainingCharacters - 1;}
#endif

					*pString += '"';

					while(tRemainingCharacters > 0)
					{
						if(*tChar == '"')
							{*pString += "\\\"";}
						else if(*tChar == '\\')
							{*pString += "\\\\";}
						else if(*tChar == '/')
							{*pString += "/";}
						else if(*tChar == '\t')
							{*pString += "\\t";}
						else if(*tChar == '\n')
							{*pString += "\\n";}
						else if(*tChar == '\r')
							{*pString += "\\r";}
						else if(*tChar == '\b')
							{*pString += "\\b";}
						else if(*tChar == '\f')
							{*pString += "\\f";}
						else if((*tChar == 'u') && (tRemainingCharacters > 4) &&
								(*(tChar + 1) <= '9') && (*(tChar + 1) >= '0') &&
								(*(tChar + 2) <= '9') && (*(tChar + 2) >= '0') &&
								(*(tChar + 3) <= '9') && (*(tChar + 3) >= '0') &&
								(*(tChar + 4) <= '9') && (*(tChar + 4) >= '0'))
							{*pString += "\\u";}
						else if((*tChar <= 0x1f) || (*tChar == 0x7f)/*THIS SECOND IS NOT REQUIRED BUT SAFER*/)
						{
							char const tDigits[17] = "0123456789ABCDEF";
							char tOutput[7] /*= ?*/;

							tOutput[0] = '\\';
							tOutput[1] = 'u';
							tOutput[2] = tDigits[((*tChar) >> 12) & 0x0f];
							tOutput[3] = tDigits[((*tChar) >> 8) & 0x0f];
							tOutput[4] = tDigits[((*tChar) >> 4) & 0x0f];
							tOutput[5] = tDigits[(*tChar) & 0x0f];
							tOutput[6] = '\0';

							*pString += tOutput;
						}
						else						
							{*pString += *tChar;}

						tChar = tChar + 1;
						tRemainingCharacters = tRemainingCharacters - 1;
					}

					*pString += '"';

					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					crx::ClassUnorderedMap<::std::string, Var>::t::iterator tIterator = 
							this->gData.uHashTable.gUnorderedMap->begin();
					bool tIsNotFirst = false;

					*pString += "{";

					while(tIterator != this->gData.uHashTable.gUnorderedMap->end())
					{
						if(tIsNotFirst)
							{*pString += ", ";}
						else
							{tIsNotFirst = true;}

						//*pString += '\"';
						*pString += (Var((*tIterator).first)).convertToVarJsonUtf8String();
						//*pString += "\": ";
						*pString += ": ";
						*pString += (*tIterator).second.convertToVarJsonUtf8String();

						tIterator++;
					}

					*pString += "}";
#else
					CRX__VAR__KHASH__ITERATOR tKhiter /*= ?*/;
					CRX__VAR__KHASH__ITERATOR tKhiter_end /*= ?*/;
					bool tIsNotFirst = false;
					
					CRX__VAR__KHash_getIteratorStart(this->gData.uHashTable.gKHash, tKhiter);
					CRX__VAR__KHash_getIteratorEnd(this->gData.uHashTable.gKHash, tKhiter_end);
					
					*pString += "{";

					while(tKhiter != tKhiter_end)
					{
						if(tIsNotFirst)
							{*pString += ", ";}
						else
							{tIsNotFirst = true;}

						*pString += '\"';
						*pString += CRX__VAR__KHASH__GET_KEY_FROM_ITERATOR(
								this->gData.uHashTable.gKHash, tKhiter);
						*pString += "\": ";
						*pString += (CRX__VAR__KHASH__GET_VALUE_FROM_ITERATOR(
								this->gData.uHashTable.gKHash, 
								tKhiter))->convertToVarJsonUtf8String();

						CRX__VAR__KHASH__INCREMENT_ITERATOR(this->gData.uHashTable.gKHash, tKhiter);
					}

					*pString += "}";
#endif
					break;
				}
				case CRX__VAR__TYPE_ARRAY:
				{
					*pString += "[";

#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					for(size_t tI = 0; tI < this->gData.uArray.gDeque->size(); tI++)
					{
						if(tI != 0)
							{*pString += ", ";}

						*pString += ((*(this->gData.uArray.gDeque))[tI]).
									convertToVarJsonUtf8String();
					}
#else
					for(size_t tI = 0; tI < crx_varRing_getLength(CRX__VAR__GET_VARRING(this)); tI++)
					{
						if(tI != 0)
							{*pString += ", ";}

						*pString += crx_varRing_get(CRX__VAR__GET_VARRING(this), tI)->
								convertToVarJsonUtf8String();
					}
#endif

					*pString += "]";

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{
					unsigned char tUnsignedChar = this->gData.uIntegral.uUnsignedChar;

					*pString += 'b';

					for(size_t tI = 0; tI < 8; tI++)
					{
						*pString += ((((unsigned char)1) & tUnsignedChar) ? "1" : "0");
						tUnsignedChar = tUnsignedChar << 1;
					}

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT] /*= ?*/;

					CRX__VAR__STRINGIFY_UNIFIED_INT(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT);

					*pString += tChars;

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT] /*= ?*/;

					Var::stringifyEmulatedInt(this->gData.uIntegral.uDouble,
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT);

					*pString += tChars;

					break;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE] /*= ?*/;
					::double_conversion::StringBuilder tStringBuilder(tChars, 
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE) /*= ...*/;

					Var::StaticPrivateVars::gDoubleToStringConverter->ToShortest(
							this->gData.uIntegral.uDouble, &tStringBuilder);

					*pString += tStringBuilder.Finalize();

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				{
					if(this->gData.uIntegral.uBool)
						{*pString += "true";}
					else
						{*pString += "false";}

					break;
				}
				case CRX__VAR__TYPE_POINTER:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__VARJSON_FORMATION_ENCOUNTERED_POINTER,
							*pString += "\"[|ERROR: POINTER|]\"");

					break;
				}
				case CRX__VAR__TYPE_NULL:
				{
					*pString += "null";
					break;
				}
				case CRX__VAR__TYPE_UNDEFINED:
				{
					CRX__VAR__REPORT_ERROR(this, CRX__VAR__ERROR__VARJSON_FORMATION_ENCOUNTERED_UNDEFINED,
							*pString += "\"[|ERROR: UNDEFINED|]\"");

					break;
				}
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
				{
					CRX__VAR__GUARD(false);

					break;
				}
#endif
				default:
					{CRX__BOOST_ASSERT(false);}
			}
		}

		CRX_PUBLIC CRX__LIB__METHOD() Var Var::convertToJsonUtf8String() const
		{
			Var vReturn = "";
			
			Var::_convertToJsonUtf8String(&vReturn);

			return vReturn;
		}
		CRX_PRIVATE CRX__LIB__METHOD() void Var::_convertToJsonUtf8String(Var * CRX_NOT_NULL pString) const
		{//ALMOST VERBATIM FROM Var::_convertToVarJsonUtf8String()
			switch(CRX__VAR__GET_TYPE1(this))
			{
				case CRX__VAR__TYPE_STRING:
				{
					size_t tRemainingCharacters /*= ?*/;
					char const * tChar /*= ?*/;
#if(!CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					bool tIsNullTerminated /*= ?*/;
#endif

#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
					tRemainingCharacters = this->gData.uString.uStd.gString.size();
					tChar = this->gData.uString.uStd.gString.c_str();
#else				
					tChar = this->getCharPointerAndInfo(&tRemainingCharacters, &tIsNullTerminated);

					if(tIsNullTerminated)
						{tRemainingCharacters = tRemainingCharacters - 1;}
#endif

					*pString += '"';

					while(tRemainingCharacters > 0)
					{
						if(*tChar == '"')
							{*pString += "\\\"";}
						else if(*tChar == '\\')
							{*pString += "\\\\";}
						else if(*tChar == '/')
							{*pString += "/";}
						else if(*tChar == '\t')
							{*pString += "\\t";}
						else if(*tChar == '\n')
							{*pString += "\\n";}
						else if(*tChar == '\r')
							{*pString += "\\r";}
						else if(*tChar == '\b')
							{*pString += "\\b";}
						else if(*tChar == '\f')
							{*pString += "\\f";}
						else if((*tChar == 'u') && (tRemainingCharacters > 4) &&
								(*(tChar + 1) <= '9') && (*(tChar + 1) >= '0') &&
								(*(tChar + 2) <= '9') && (*(tChar + 2) >= '0') &&
								(*(tChar + 3) <= '9') && (*(tChar + 3) >= '0') &&
								(*(tChar + 4) <= '9') && (*(tChar + 4) >= '0'))
							{*pString += "\\u";}
						else if((*tChar <= 0x1f) || (*tChar == 0x7f)/*THIS SECOND IS NOT REQUIRED BUT SAFER*/)
						{
							char const tDigits[17] = "0123456789ABCDEF";
							char tOutput[7] /*= ?*/;

							tOutput[0] = '\\';
							tOutput[1] = 'u';
							tOutput[2] = tDigits[((*tChar) >> 12) & 0x0f];
							tOutput[3] = tDigits[((*tChar) >> 8) & 0x0f];
							tOutput[4] = tDigits[((*tChar) >> 4) & 0x0f];
							tOutput[5] = tDigits[(*tChar) & 0x0f];
							tOutput[6] = '\0';

							*pString += tOutput;
						}
						else						
							{*pString += *tChar;}

						tChar = tChar + 1;
						tRemainingCharacters = tRemainingCharacters - 1;
					}

					*pString += '"';

					break;
				}
				case CRX__VAR__TYPE_HASH_TABLE:
				{
#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
					crx::ClassUnorderedMap<::std::string, Var>::t::iterator tIterator = 
							this->gData.uHashTable.gUnorderedMap->begin();
					bool tIsNotFirst = false;

					*pString += "{";

					while(tIterator != this->gData.uHashTable.gUnorderedMap->end())
					{
						if(tIsNotFirst)
							{*pString += ", ";}
						else
							{tIsNotFirst = true;}

						//*pString += '\"';
						*pString += (Var((*tIterator).first)).convertToJsonUtf8String();
						//*pString += "\": ";
						*pString += ": ";
						*pString += (*tIterator).second.convertToJsonUtf8String();

						tIterator++;
					}

					*pString += "}";
#else
					CRX__VAR__KHASH__ITERATOR tKhiter /*= ?*/;
					CRX__VAR__KHASH__ITERATOR tKhiter_end /*= ?*/;
					bool tIsNotFirst = false;
					
					CRX__VAR__KHash_getIteratorStart(this->gData.uHashTable.gKHash, tKhiter);
					CRX__VAR__KHash_getIteratorEnd(this->gData.uHashTable.gKHash, tKhiter_end);
					
					*pString += "{";

					while(tKhiter != tKhiter_end)
					{
						if(tIsNotFirst)
							{*pString += ", ";}
						else
							{tIsNotFirst = true;}

						*pString += '\"';
						*pString += CRX__VAR__KHASH__GET_KEY_FROM_ITERATOR(
								this->gData.uHashTable.gKHash, tKhiter);
						*pString += "\": ";
						*pString += (CRX__VAR__KHASH__GET_VALUE_FROM_ITERATOR(
								this->gData.uHashTable.gKHash, 
								tKhiter))->convertToJsonUtf8String();

						CRX__VAR__KHASH__INCREMENT_ITERATOR(this->gData.uHashTable.gKHash, tKhiter);
					}

					*pString += "}";
#endif
					break;
				}
				case CRX__VAR__TYPE_ARRAY:
				{
					*pString += "[";

#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
					for(size_t tI = 0; tI < this->gData.uArray.gDeque->size(); tI++)
					{
						if(tI != 0)
							{*pString += ", ";}

						*pString += ((*(this->gData.uArray.gDeque))[tI]).
								convertToJsonUtf8String();
					}
#else
					for(size_t tI = 0; tI < crx_varRing_getLength(CRX__VAR__GET_VARRING(this)); tI++)
					{
						if(tI != 0)
							{*pString += ", ";}

						*pString += crx_varRing_constantGet(CRX__VAR__GET_VARRING(this), tI)->
								convertToJsonUtf8String();
					}
#endif

					*pString += "]";

					break;
				}
				case CRX__VAR__TYPE_UNSIGNED_CHAR:
				{//THIS DIFFERS FROM Var::_convertToVarJsonUtf8String()
					unsigned char tUnsignedChar = this->gData.uIntegral.uUnsignedChar;

					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR] /*= ?*/;

					Var::stringifyUnsignedInt32(tUnsignedChar, tChars,
							CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNSIGNED_CHAR);

					*pString += tChars;

					break;
				}
#if(!CRX__VAR__IS_EMULATED_INT_USED)
				case CRX__VAR__TYPE_SIGNED_INT64_OR_SIGNED_INT32:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT] /*= ?*/;

					CRX__VAR__STRINGIFY_UNIFIED_INT(CRX__VAR__GET_UNIFIED_INT_VARIABLE1(this),
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_UNIFIED_INT);

					*pString += tChars;

					break;
				}
#else
				case CRX__VAR__TYPE_EMULATED_INT:
				{
					char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT] /*= ?*/;

					Var::stringifyEmulatedInt(this->gData.uIntegral.uDouble,
							tChars, CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_EMULATED_INT);

					*pString += tChars;

					break;
				}
#endif
				case CRX__VAR__TYPE_DOUBLE:
				{
					if(this->isFinite())
					{
						char tChars[CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE] /*= ?*/;
						::double_conversion::StringBuilder tStringBuilder(tChars, 
								CRX__VAR__LENGTH_OF_NUMBER_STRING_FROM_DOUBLE) /*= ...*/;

						Var::StaticPrivateVars::gDoubleToStringConverter->ToShortest(
								this->gData.uIntegral.uDouble, &tStringBuilder);

						*pString += tStringBuilder.Finalize();
					}
					else
						{*pString += "null";}

					break;
				}
				case CRX__VAR__TYPE_BOOL:
				{
					if(this->gData.uIntegral.uBool)
						{*pString += "true";}
					else
						{*pString += "false";}

					break;
				}
				case CRX__VAR__TYPE_POINTER:
				case CRX__VAR__TYPE_NULL:
				case CRX__VAR__TYPE_UNDEFINED: //THIS DIFFERS FROM Var::_convertToVarJsonUtf8String()
#if(CRX__VAR__DOES_ERROR_TYPE_EXISTS)
				case CRX__VAR__TYPE_ERROR:
#endif
				{//THIS DIFFERS FROM Var::_convertToVarJsonUtf8String()
					*pString += "null";

					break;
				}
				default:
					{CRX__BOOST_ASSERT(false);}
			}
		}
		#pragma endregion VARJSON //}
		
		//-----------------------------------

		CRX_PUBLIC CRX__LIB__METHOD() Var::~Var()
			{this->emptyDynamicResourcesIfNecessaryForAssigment(CRX__VAR__TYPE_NULL);}
	
	#pragma endregion CLASS Var //}

	#pragma region CLASS VarThreadPossible //{
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible() : Var()
		{
			this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
					CRX__VAR__TYPE_NULL;
		}
		
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(Var::Nil pNil) : Var(pNil, true)
			{}
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(Var::Undefined pUndefined) :
				Var(pUndefined, true)
			{}
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(Var::Type pType) : Var(pType, true)
			{}

		#pragma region operator = //{
#if(defined(CRX__BOOST_NO_CXX11_DELETED_FUNCTIONS))
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(Var pVar)
			{return Var::operator=(pVar);}
	#if(CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		//IF NO MOVE SEMANTICS:	Var & Var::operator=(::std::string pString)
		//IF MOVE SEMANTICS:	Var & Var::operator=(::std::string && pString)
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(CRX__VAR__TYPE_FOR_MOVE(::std::string) pString)
			{return Var::operator=(pString);}
	#endif
	#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || !CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(::std::string const & pString)
			{return Var::operator=(pString);}
	#endif
	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		//IF NO MOVE SEMANTICS:	Var & VarThreadPossible::operator=(::crx::ClassUnorderedMap<::std::string, Var>::t pUnorderedMap)
		//IF MOVE SEMANTICS:	Var & VarThreadPossible::operator=(::crx::ClassUnorderedMap<::std::string, Var>::t && pUnorderedMap)
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(CRX__VAR__TYPE_FOR_MOVE(Var::VarUnorderedMap) pUnorderedMap)
			{return Var::operator=(pUnorderedMap);}
	#endif
	#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap)
			{return Var::operator=(pUnorderedMap);}
	#endif
	#if(!CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		//IF NO MOVE SEMANTICS:	Var & VarThreadPossible::operator=(::std::deque<Var> pDeque)
		//IF MOVE SEMANTICS:	Var & VarThreadPossible::operator=(::std::deque<Var> && pDeque)
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(CRX__VAR__TYPE_FOR_MOVE(::std::deque<Var>) pDeque)
			{return Var::operator=(pDeque);}
	#endif
	#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(::std::deque<Var> const & pDeque)
			{return Var::operator=(pDeque);}
	#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(char const * pString)
			{return Var::operator=(pString);}
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(unsigned char const & pUnsignedChar)
			{return Var::operator=(pUnsignedChar);}
	#if((!CRX__VAR__IS_EMULATED_INT_USED && CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64) || CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(uint32_t const pUnsignedInt32)
			{return Var::operator=(pUnsignedInt32);}
	#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(int32_t const & pSignedInt)
			{return Var::operator=(pSignedInt);}
	#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(Var & VarThreadPossible::operator=(uint64_t pUnsignedInt64))
		#if(CRX__VAR__IS_EMULATED_INT_USED || CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(int64_t const pSignedInt64)
			{return Var::operator=(pSignedInt64);}
		#else
		CRX_DISABLED_METHOD(Var & VarThreadPossible::operator=(int64_t pSignedInt64))
		#endif
	#endif
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(float const & pFloat)
			{return Var::operator=(pFloat);}
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(double const & pDouble)
			{return Var::operator=(pDouble);}
		CRX_PUBLIC CRX__LIB__METHOD() Var & VarThreadPossible::operator=(bool const & pBool)
			{return Var::operator=(pBool);}
#endif
		#pragma endregion operator = //}

		#pragma region COPY CONSTRUCTOR //{
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(Var const & pVar) : Var(pVar, true)
			{}
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || !CRX__VAR__DEVELOPMENT__IS_USING_STD_STRING)
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(::std::string const & pString) : 
				Var(pString, true)
			{}
#endif
//#if(defined(_MSC_VER) && (_MSC_VER <= 1200))
		//DID NOT WORK. SEE THE TEMPLATED VAR CONSTRUCTOR FOR DETAIL.
		//		AND HENCE WE ARE DISABLING THIS CONSTRUCTOR INSTEAD.
//#else
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(char const * pString) : 
				Var(pString, true)
			{}
//#endif
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(
				::crx::ClassUnorderedMap<::std::string, Var>::t const & pUnorderedMap) : Var(pUnorderedMap, true)
			{}
#endif
#if(!defined(CRX__BOOST_NO_CXX11_RVALUE_REFERENCES) || CRX__VAR__ARRAY_IMPLEMENTATION__IS_USING_VARRING)
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(::std::deque<Var> const & pDeque) : 
				Var(pDeque, true)
			{}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(unsigned char const & pUnsignedChar) :
				Var(pUnsignedChar, true)
			{}
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(signed char const & pChar) : 
				Var(pChar, true)
			{}
#if((!CRX__VAR__IS_EMULATED_INT_USED && CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64) || CRX__VAR__IS_EMULATED_INT_USED)
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(uint32_t pUnsignedInt32) : 
				Var(pUnsignedInt32, true)
			{}
#else
		CRX_DISABLED_METHOD(VarThreadPossible::VarThreadPossible(uint32_t pUnsignedInt32))
#endif
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(int32_t const & pSignedInt) : 
				Var(pSignedInt, true)
			{}
#ifndef CRX__BOOST_NO_INT64_T
		CRX_DISABLED_METHOD(VarThreadPossible::VarThreadPossible(uint64_t pUnsignedInt64))
	#if(CRX__VAR__IS_EMULATED_INT_USED || CRX__VAR__IS_UNIFIED_SIGNED_INT_AN_INT64)
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(int64_t pSignedInt64) : 
				Var(pSignedInt64, true)
			{}
	#else
		CRX_DISABLED_METHOD(VarThreadPossible::VarThreadPossible(int64_t pSignedInt64))
	#endif
#endif
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(float const & pFloat) : 
				Var(pFloat, true)
			{}
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(double const & pDouble) : 
				Var(pDouble, true)
			{}
#if(CRX__VAR__IS_ERROR_TYPE_AVAILABLE_FOR_PUBLIC_USE)
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(uint32_t gCode, 
				::std::string const pMessage) : Var(gCode, pMessage, true)
			{}
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(uint32_t gCode, 
				char const * pMessage) : Var(gCode, pMessage, true)
			{}
#endif
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(bool pBool) : 
				Var(pBool, true)
			{}
		/*CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(
					Var::VarBoolean pVarBoolean) : Var(pVarBoolean, true)
			{}*/
		#pragma endregion COPY CONSTRUCTOR //}

#ifndef CRX__BOOST_NO_CXX11_HDR_INITIALIZER_LIST
		/*CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(::std::initializer_list<::std::pair<::std::string const, VarThreadPossible>> pInitializerList) :
				Var()
		{
			this->gData.uInfo.gInfo = CRX__VAR__THREAD_MODE_POSSIBLE |
						CRX__VAR__TYPE_HASH_TABLE;

	#if(!CRX__VAR__HASH_TABLE_IMPLEMENTATION__IS_USING_KHASH)
			this->gData.uHashTable.gUnorderedMap = new ::crx::ClassUnorderedMap<::std::string, Var>::t();
			::std::initializer_list<::std::pair<::std::string const, VarThreadPossible>>::iterator vIterator = 
					pInitializerList.begin();

			while(vIterator)
			{
				VarThreadPossible * tVar = new VarThreadPossible((*vIterator).second);

				this->gData.uHashTable.gUnorderedMap->operator[]((*vIterator).first) = (*vIterator).second;

				vIterator++;
			}
	#else
			::std::initializer_list<::std::pair<::std::string const, VarThreadPossible>>::iterator vIterator = 
					pInitializerList.begin();

			CRX__VAR__KHash_new(this->gData.uHashTable.gKHash);

			while(vIterator)
			{
				CRX__VAR__KHash_set(this->gData.uHashTable.gKHash, 
						(*vIterator).first.c_str(), &((*vIterator).second), true);

				vIterator++;
			}
	#endif

		}*/
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(
				::std::initializer_list<::std::pair<::std::string const, Var>> pInitializerList) :
				Var(pInitializerList, true)
			{}
		CRX_PUBLIC CRX__LIB__METHOD() VarThreadPossible::VarThreadPossible(Var::ARRAY_DEFINITION _s,
				::std::initializer_list<Var> pInitializerList) : Var(_s, pInitializerList, true)
			{}
#endif

		/*using Var::operator=;*/
	#pragma endregion CLASS VarThreadPossible //}

	CRX__LIB__PRIVATE_FUNCTION() void var_private_destruct(Var * pVar)
		{pVar->~Var();}
	CRX__LIB__PRIVATE_FUNCTION() void var_private_copyConstruct(Var * pVar, Var const * pVar2)
		{pVar = new(pVar) Var(*pVar2);}

	CRX__C__Ring__DEFINE(Crx_VarRing, 
			crx_varRing_, Var, uint32_t, ((uint32_t)(-1)), 0, CRXM__FALSE, 4, CRXM__FALSE,
			var_private_destruct, var_private_copyConstruct, CRXM__FALSE, CRXM__FALSE)
	CRX__LIB__PUBLIC_FUNCTION() void crx_varRing_constructFromDeque(Crx_VarRing * pThis, 
			::std::deque<Var> * pDeque)
	{
		crx_varRing_construct(pThis, pDeque->size());

		if(crx_varRing_getCapacity(pThis) >= pDeque->size())
		{
			for(size_t tI = 0; tI < pDeque->size(); tI++)
				{crx_varRing_push(pThis, &(pDeque->at(tI)));}

			/*return true;*/
		}
		else
			{/*return false;*/}
	}
	CRX__LIB__PUBLIC_FUNCTION() void crx_varRing_constructFromDeque2(Crx_VarRing * pThis, 
			::std::deque<Var> * pDeque, bool pArePossiblyCreatedVarsThreadPossible)
	{
		crx_varRing_construct(pThis, pDeque->size());

		if(crx_varRing_getCapacity(pThis) >= pDeque->size())
		{
			for(size_t tI = 0; tI < pDeque->size(); tI++)
			{
				Var tVar(Var::TYPE__UNDEFINED, true);

				crx_varRing_push(pThis, &tVar);
				*(crx_varRing_get(pThis, tI)) = pDeque->at(tI);
			}

			/*return true;*/
		}
		else
			{/*return false;*/}
	}

#ifdef CRX__BOOST_NO_INT64_T
	//WARNING: THIS IS FOR BIG ENDIAN BY BYTE, NOT WORD
	CRX__LIB__PRIVATE_FUNCTION() bool var_isMachineUsingBigEndian()
	{
		union
		{
			uint32_t i;
			char c[4];
		} vBits = {0x01020304};

		return (vBits.c[0] == 1);
	}
	CRX__LIB__PRIVATE_FUNCTION() CRX__BOOST_FORCEINLINE Var_BitsOfDouble var_getBitsOfDouble(
			uint32_t pHighBits, uint32_t pLowBits)
	{
		//VC6 Var_BitsOfDouble vBitsOfDouble = {};
		Var_BitsOfDouble vBitsOfDouble; CRX__SET_TO_ZERO(Var_BitsOfDouble, vBitsOfDouble);
		
		if(var_isMachineUsingBigEndian()) //big endian
		{
			vBitsOfDouble.uBytes[0] = (pHighBits >> 24) & 0xFF;
			vBitsOfDouble.uBytes[1] = (pHighBits >> 16) & 0xFF;
			vBitsOfDouble.uBytes[2] = (pHighBits >> 8) & 0xFF;
			vBitsOfDouble.uBytes[3] = pHighBits & 0xFF;
			vBitsOfDouble.uBytes[4] = (pLowBits >> 24) & 0xFF;
			vBitsOfDouble.uBytes[5] = (pLowBits >> 16) & 0xFF;
			vBitsOfDouble.uBytes[6] = (pLowBits >> 8) & 0xFF;
			vBitsOfDouble.uBytes[7] = pLowBits & 0xFF;
		}
		else	//little endian
		{
			vBitsOfDouble.uBytes[7] = (pHighBits >> 24) & 0xFF;
			vBitsOfDouble.uBytes[6] = (pHighBits >> 16) & 0xFF;
			vBitsOfDouble.uBytes[5] = (pHighBits >> 8) & 0xFF;
			vBitsOfDouble.uBytes[4] = pHighBits & 0xFF;
			vBitsOfDouble.uBytes[3] = (pLowBits >> 24) & 0xFF;
			vBitsOfDouble.uBytes[2] = (pLowBits >> 16) & 0xFF;
			vBitsOfDouble.uBytes[1] = (pLowBits >> 8) & 0xFF;
			vBitsOfDouble.uBytes[0] = pLowBits & 0xFF;
		}

		return vBitsOfDouble;
	}
	CRX__LIB__PRIVATE_FUNCTION() CRX__BOOST_FORCEINLINE bool var_isDoubleEqualTo(double pDouble, 
			uint32_t pHighBits, uint32_t pLowBits)
	{
		//VC6 Var_BitsOfDouble vBitsOfDouble = {};
		Var_BitsOfDouble vBitsOfDouble; CRX__SET_TO_ZERO(Var_BitsOfDouble, vBitsOfDouble);


		vBitsOfDouble.uDouble = pDouble;

		if(var_isMachineUsingBigEndian())
		{
			return ((vBitsOfDouble.uBytes[0] == ((pHighBits >> 24) & 0xFF)) &&
					(vBitsOfDouble.uBytes[1] == ((pHighBits >> 16) & 0xFF)) &&
					(vBitsOfDouble.uBytes[2] == ((pHighBits >> 8) & 0xFF)) &&
					(vBitsOfDouble.uBytes[3] == (pHighBits & 0xFF)) &&
					(vBitsOfDouble.uBytes[4] == ((pLowBits >> 24) & 0xFF)) &&
					(vBitsOfDouble.uBytes[5] == ((pLowBits >> 16) & 0xFF)) &&
					(vBitsOfDouble.uBytes[6] == ((pLowBits >> 8) & 0xFF)) &&
					(vBitsOfDouble.uBytes[7] == (pLowBits & 0xFF)));
		}
		else
		{
			return ((vBitsOfDouble.uBytes[7] == ((pHighBits >> 24) & 0xFF)) &&
					(vBitsOfDouble.uBytes[6] == ((pHighBits >> 16) & 0xFF)) &&
					(vBitsOfDouble.uBytes[5] == ((pHighBits >> 8) & 0xFF)) &&
					(vBitsOfDouble.uBytes[4] == (pHighBits & 0xFF)) &&
					(vBitsOfDouble.uBytes[3] == ((pLowBits >> 24) & 0xFF)) &&
					(vBitsOfDouble.uBytes[2] == ((pLowBits >> 16) & 0xFF)) &&
					(vBitsOfDouble.uBytes[1] == ((pLowBits >> 8) & 0xFF)) &&
					(vBitsOfDouble.uBytes[0] == (pLowBits  & 0xFF)));
		}
	}
#endif
	
	CRX__LIB__PUBLIC_FUNCTION() Var::iterator begin(Var & pVar)
		{return Var::iterator(&pVar);}
	CRX__LIB__PUBLIC_FUNCTION() Var::iterator end(Var & pVar)
		{return Var::iterator(&pVar, true);}
	CRX__LIB__PUBLIC_FUNCTION() Var::const_iterator cbegin(Var & pVar)
		{return Var::const_iterator(&pVar);}
	CRX__LIB__PUBLIC_FUNCTION() Var::const_iterator cend(Var & pVar)
		{return Var::const_iterator(&pVar, true);}

	/*SUPPORT FOR JSON LIKE SYNTAX FOR PRE C++11 COMPILERS*/
	CRX__LIB__PUBLIC_FUNCTION() VarVarArgsKeyValue var_varArgsKeyValue(char const * pString, Var const pVar)
	{
		//VC6 VarVarArgsKeyValue vReturn = CRX__INITIALIZATION_POD_ZERO;
		VarVarArgsKeyValue vReturn; //CRX__SET_TO_ZERO(VarVarArgsKeyValue, vReturn);

		vReturn.gString = pString;
		vReturn.gVar = pVar;

		return vReturn;
	}
	CRX__LIB__PUBLIC_FUNCTION() VarVarArgsKeyValue var_varArgsKeyValue()
	{
		//VC6 VarVarArgsKeyValue vReturn = CRX__INITIALIZATION_POD_ZERO;
		VarVarArgsKeyValue vReturn; //CRX__SET_TO_ZERO(VarVarArgsKeyValue, vReturn);
		vReturn.gString = NULL;

		return vReturn;
	}
	CRX__LIB__PUBLIC_FUNCTION() Var var_varArgs(VarVarArgsKeyValue pVarVarArgsKeyValue__1, ...)
	{
		va_list vArguments;
		VarVarArgsKeyValue vVarVarArgsKeyValue = pVarVarArgsKeyValue__1;
		Var vReturn = Var(true, Var::TYPE__HASH_TABLE);

		va_start(vArguments, pVarVarArgsKeyValue__1);

		while(vVarVarArgsKeyValue.gString != NULL)
		{
			vReturn[vVarVarArgsKeyValue.gString] = vVarVarArgsKeyValue.gVar;

			vVarVarArgsKeyValue = va_arg(vArguments, VarVarArgsKeyValue);
		}

		va_end(vArguments);

		return vReturn;
	}
	CRX__LIB__PUBLIC_FUNCTION() Var var_varArgs(Var pVar__1, ...)
	{
		va_list vArguments;
		Var vVar = pVar__1;
		Var vReturn = Var(true, Var::TYPE__ARRAY);

		va_start(vArguments, pVar__1);

		while(!vVar.isUndefined())
		{
			vReturn.push(vVar);

			vVar = va_arg(vArguments, Var);
		}

		va_end(vArguments);

		return vReturn;
	}
	CRX__LIB__PUBLIC_FUNCTION() Var var_varArgs(bool pIsToBeThreadPossible, VarVarArgsKeyValue pVarVarArgsKeyValue__1, ...)
	{
		va_list vArguments;
		VarVarArgsKeyValue vVarVarArgsKeyValue = pVarVarArgsKeyValue__1;
		Var vReturn = Var(pIsToBeThreadPossible, Var::TYPE__HASH_TABLE);

		va_start(vArguments, pVarVarArgsKeyValue__1);

		while(vVarVarArgsKeyValue.gString != NULL)
		{
			vReturn[vVarVarArgsKeyValue.gString] = vVarVarArgsKeyValue.gVar;

			vVarVarArgsKeyValue = va_arg(vArguments, VarVarArgsKeyValue);
		}

		va_end(vArguments);

		return vReturn;
	}
	CRX__LIB__PUBLIC_FUNCTION() Var var_varArgs(bool pIsToBeThreadPossible, Var pVar__1, ...)
	{
		va_list vArguments;
		Var vVar = pVar__1;
		Var vReturn = Var(pIsToBeThreadPossible, Var::TYPE__ARRAY);

		va_start(vArguments, pVar__1);

		while(!vVar.isUndefined())
		{
			vReturn.push(vVar);

			vVar = va_arg(vArguments, Var);
		}

		va_end(vArguments);

		return vReturn;
	}
}

