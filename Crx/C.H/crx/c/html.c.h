//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/html.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "Crx/H/crx/c/char.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()

//#define CRX__UNICODE_MAX 0x10FFFFul

/*	WARNING: HTML ENTITIES ARE CASE SENSITIVE, BUT WEB BROWSERS MIGHT ACCEPT THEM AS CASE 
			INSENSITIVE AS A MATTER OF FORGIVENESS
	THE USE OF CRX__LIB__PRIVATE_C_CONSTANT() IS KEPT FOR TESTING PURPOSES FOR THE TIME BEING. IN 
			THE FUTURE THIS SHOULD BE MOVED TO A static VARIABLE INSIDE A FUNCTION.
*/
CRX__LIB__PRIVATE_C_CONSTANT(1) char const * const gCRX__C__HTML__NAMED_ENTITIES_TO_UTF8[253 /*HAD TO USE SIZE FOR SUPPORTING VISUAL STUDIO*/][2] = 
{
	{"AElig;", "\xc3\x86"},
	{"Aacute;", "\xc3\x81"},
	{"Acirc;", "\xc3\x82"},
	{"Agrave;", "\xc3\x80"},
	{"Alpha;", "\xce\x91"},
	{"Aring;", "\xc3\x85"},
	{"Atilde;", "\xc3\x83"},
	{"Auml;", "\xc3\x84"},
	{"Beta;", "\xce\x92"},
	{"Ccedil;", "\xc3\x87"},
	{"Chi;", "\xce\xa7"},
	{"Dagger;", "\xe2\x80\xa1"},
	{"Delta;", "\xce\x94"},
	{"ETH;", "\xc3\x90"},
	{"Eacute;", "\xc3\x89"},
	{"Ecirc;", "\xc3\x8a"},
	{"Egrave;", "\xc3\x88"},
	{"Epsilon;", "\xce\x95"},
	{"Eta;", "\xce\x97"},
	{"Euml;", "\xc3\x8b"},
	{"Gamma;", "\xce\x93"},
	{"Iacute;", "\xc3\x8d"},
	{"Icirc;", "\xc3\x8e"},
	{"Igrave;", "\xc3\x8c"},
	{"Iota;", "\xce\x99"},
	{"Iuml;", "\xc3\x8f"},
	{"Kappa;", "\xce\x9a"},
	{"Lambda;", "\xce\x9b"},
	{"Mu;", "\xce\x9c"},
	{"Ntilde;", "\xc3\x91"},
	{"Nu;", "\xce\x9d"},
	{"OElig;", "\xc5\x9"},
	{"Oacute;", "\xc3\x93"},
	{"Ocirc;", "\xc3\x94"},
	{"Ograve;", "\xc3\x92"},
	{"Omega;", "\xce\xa9"},
	{"Omicron;", "\xce\x9f"},
	{"Oslash;", "\xc3\x98"},
	{"Otilde;", "\xc3\x95"},
	{"Ouml;", "\xc3\x96"},
	{"Phi;", "\xce\xa6"},
	{"Pi;", "\xce\xa0"},
	{"Prime;", "\xe2\x80\xb3"},
	{"Psi;", "\xce\xa8"},
	{"Rho;", "\xce\xa1"},
	{"Scaron;", "\xc5\xa0"},
	{"Sigma;", "\xce\xa3"},
	{"THORN;", "\xc3\x9e"},
	{"Tau;", "\xce\xa4"},
	{"Theta;", "\xce\x98"},
	{"Uacute;", "\xc3\x9a"},
	{"Ucirc;", "\xc3\x9b"},
	{"Ugrave;", "\xc3\x99"},
	{"Upsilon;", "\xce\xa5"},
	{"Uuml;", "\xc3\x9c"},
	{"Xi;", "\xce\x9e"},
	{"Yacute;", "\xc3\x9d"},
	{"Yuml;", "\xc5\xb8"},
	{"Zeta;", "\xce\x96"},
	{"aacute;", "\xc3\xa1"},
	{"acirc;", "\xc3\xa2"},
	{"acute;", "\xc2\xb4"},
	{"aelig;", "\xc3\xa6"},
	{"agrave;", "\xc3\xa0"},
	{"alefsym;", "\xe2\x84\xb5"},
	{"alpha;", "\xce\xb1"},
	{"amp;", "\x26"},
	{"and;", "\xe2\x88\xa7"},
	{"ang;", "\xe2\x88\xa0"},
	{"apos;", "\x27"},
	{"aring;", "\xc3\xa5"},
	{"asymp;", "\xe2\x89\x88"},
	{"atilde;", "\xc3\xa3"},
	{"auml;", "\xc3\xa4"},
	{"bdquo;", "\xe2\x80\x9e"},
	{"beta;", "\xce\xb2"},
	{"brvbar;", "\xc2\xa6"},
	{"bull;", "\xe2\x80\xa2"},
	{"cap;", "\xe2\x88\xa9"},
	{"ccedil;", "\xc3\xa7"},
	{"cedil;", "\xc2\xb8"},
	{"cent;", "\xc2\xa2"},
	{"chi;", "\xcf\x87"},
	{"circ;", "\xcb\x86"},
	{"clubs;", "\xe2\x99\xa3"},
	{"cong;", "\xe2\x89\x85"},
	{"copy;", "\xc2\xa9"},
	{"crarr;", "\xe2\x86\xb5"},
	{"cup;", "\xe2\x88\xaa"},
	{"curren;", "\xc2\xa4"},
	{"dArr;", "\xe2\x87\x93"},
	{"dagger;", "\xe2\x80\xa0"},
	{"darr;", "\xe2\x86\x93"},
	{"deg;", "\xc2\xb0"},
	{"delta;", "\xce\xb4"},
	{"diams;", "\xe2\x99\xa6"},
	{"divide;", "\xc3\xb7"},
	{"eacute;", "\xc3\xa9"},
	{"ecirc;", "\xc3\xaa"},
	{"egrave;", "\xc3\xa8"},
	{"empty;", "\xe2\x88\x85"},
	{"emsp;", "\xE2\x80\x83"},
	{"ensp;", "\xE2\x80\x82"},
	{"epsilon;", "\xce\xb5"},
	{"equiv;", "\xe2\x89\xa1"},
	{"eta;", "\xce\xb7"},
	{"eth;", "\xc3\xb0"},
	{"euml;", "\xc3\xab"},
	{"euro;", "\xe2\x82\xac"},
	{"exist;", "\xe2\x88\x83"},
	{"fnof;", "\xc6\x92"},
	{"forall;", "\xe2\x88\x80"},
	{"frac12;", "\xc2\xbd"},
	{"frac14;", "\xc2\xbc"},
	{"frac34;", "\xc2\xbe"},
	{"frasl;", "\xe2\x81\x84"},
	{"gamma;", "\xce\xb3"},
	{"ge;", "\xe2\x89\xa5"},
	{"gt;", "\x3e"},
	{"hArr;", "\xe2\x87\x94"},
	{"harr;", "\xe2\x86\x94"},
	{"hearts;", "\xe2\x99\xa5"},
	{"hellip;", "\xe2\x80\xa6"},
	{"iacute;", "\xc3\xad"},
	{"icirc;", "\xc3\xae"},
	{"iexcl;", "\xc2\xa1"},
	{"igrave;", "\xc3\xac"},
	{"image;", "\xe2\x84\x91"},
	{"infin;", "\xe2\x88\x9e"},
	{"int;", "\xe2\x88\xab"},
	{"iota;", "\xce\xb9"},
	{"iquest;", "\xc2\xbf"},
	{"isin;", "\xe2\x88\x88"},
	{"iuml;", "\xc3\xaf"},
	{"kappa;", "\xce\xba"},
	{"lArr;", "\xe2\x87\x90"},
	{"lambda;", "\xce\xbb"},
	{"lang;", "\xe3\x80\x88"},
	{"laquo;", "\xc2\xab"},
	{"larr;", "\xe2\x86\x90"},
	{"lceil;", "\xe2\x8c\x88"},
	{"ldquo;", "\xe2\x80\x9c"},
	{"le;", "\xe2\x89\xa4"},
	{"lfloor;", "\xe2\x8c\x8a"},
	{"lowast;", "\xe2\x88\x97"},
	{"loz;", "\xe2\x97\x8a"},
	{"lrm;", "\xE2\x80\x8E"},
	{"lsaquo;", "\xe2\x80\xb9"},
	{"lsquo;", "\xe2\x80\x98"},
	{"lt;", "\x3c"},
	{"macr;", "\xc2\xaf"},
	{"mdash;", "\xe2\x80\x94"},
	{"micro;", "\xc2\xb5"},
	{"middot;", "\xc2\xb7"},
	{"minus;", "\xe2\x88\x92"},
	{"mu;", "\xce\xbc"},
	{"nabla;", "\xe2\x88\x87"},
	{"nbsp;", "\xC2\xA0"},
	{"ndash;", "\xe2\x80\x93"},
	{"ne;", "\xe2\x89\xa0"},
	{"ni;", "\xe2\x88\x8b"},
	{"not;", "\xc2\xac"},
	{"notin;", "\xe2\x88\x89"},
	{"nsub;", "\xe2\x8a\x84"},
	{"ntilde;", "\xc3\xb1"},
	{"nu;", "\xce\xbd"},
	{"oacute;", "\xc3\xb3"},
	{"ocirc;", "\xc3\xb4"},
	{"oelig;", "\xc5\x93"},
	{"ograve;", "\xc3\xb2"},
	{"oline;", "\xe2\x80\xbe"},
	{"omega;", "\xcf\x89"},
	{"omicron;", "\xce\xbf"},
	{"oplus;", "\xe2\x8a\x95"},
	{"or;", "\xe2\x88\xa8"},
	{"ordf;", "\xc2\xaa"},
	{"ordm;", "\xc2\xba"},
	{"oslash;", "\xc3\xb8"},
	{"otilde;", "\xc3\xb5"},
	{"otimes;", "\xe2\x8a\x97"},
	{"ouml;", "\xc3\xb6"},
	{"para;", "\xc2\xb6"},
	{"part;", "\xe2\x88\x82"},
	{"permil;", "\xe2\x80\xb0"},
	{"perp;", "\xe2\x8a\xa5"},
	{"phi;", "\xcf\x86"},
	{"pi;", "\xcf\x80"},
	{"piv;", "\xcf\x96"},
	{"plusmn;", "\xc2\xb1"},
	{"pound;", "\xc2\xa3"},
	{"prime;", "\xe2\x80\xb2"},
	{"prod;", "\xe2\x88\x8f"},
	{"prop;", "\xe2\x88\x9d"},
	{"psi;", "\xcf\x88"},
	{"quot;", "\x22"},
	{"rArr;", "\xe2\x87\x92"},
	{"radic;", "\xe2\x88\x9a"},
	{"rang;", "\xe3\x80\x89"},
	{"raquo;", "\xc2\xbb"},
	{"rarr;", "\xe2\x86\x92"},
	{"rceil;", "\xe2\x8c\x89"},
	{"rdquo;", "\xe2\x80\x9d"},
	{"real;", "\xe2\x84\x9c"},
	{"reg;", "\xc2\xae"},
	{"rfloor;", "\xe2\x8c\x8b"},
	{"rho;", "\xcf\x81"},
	{"rlm;", "\xE2\x80\x8F"},
	{"rsaquo;", "\xe2\x80\xba"},
	{"rsquo;", "\xe2\x80\x99"},
	{"sbquo;", "\xe2\x80\x9a"},
	{"scaron;", "\xc5\xa1"},
	{"sdot;", "\xe2\x8b\x85"},
	{"sect;", "\xc2\xa7"},
	{"shy;", "\xC2\xAD"},
	{"sigma;", "\xcf\x83"},
	{"sigmaf;", "\xcf\x82"},
	{"sim;", "\xe2\x88\xbc"},
	{"spades;", "\xe2\x99\xa0"},
	{"sub;", "\xe2\x8a\x82"},
	{"sube;", "\xe2\x8a\x86"},
	{"sum;", "\xe2\x88\x91"},
	{"sup1;", "\xc2\xb9"},
	{"sup2;", "\xc2\xb2"},
	{"sup3;", "\xc2\xb3"},
	{"sup;", "\xe2\x8a\x83"},
	{"supe;", "\xe2\x8a\x87"},
	{"szlig;", "\xc3\x9f"},
	{"tau;", "\xcf\x84"},
	{"there4;", "\xe2\x88\xb4"},
	{"theta;", "\xce\xb8"},
	{"thetasym;", "\xcf\x91"},
	{"thinsp;", "\xE2\x80\x89"},
	{"thorn;", "\xc3\xbe"},
	{"tilde;", "\xcb\x9c"},
	{"times;", "\xc3\x97"},
	{"trade;", "\xe2\x84\xa2"},
	{"uArr;", "\xe2\x87\x91"},
	{"uacute;", "\xc3\xba"},
	{"uarr;", "\xe2\x86\x91"},
	{"ucirc;", "\xc3\xbb"},
	{"ugrave;", "\xc3\xb9"},
	{"uml;", "\xc2\xa8"},
	{"upsih;", "\xcf\x92"},
	{"upsilon;", "\xcf\x85"},
	{"uuml;", "\xc3\xbc"},
	{"weierp;", "\xe2\x84\x98"},
	{"xi;", "\xce\xbe"},
	{"yacute;", "\xc3\xbd"},
	{"yen;", "\xc2\xa5"},
	{"yuml;", "\xc3\xbf"},
	{"zeta;", "\xce\xb6"},
	{"zwj;", "\xE2\x80\x8D"},
	{"zwnj;", "\xE2\x80\x8C"}
};


CRX__LIB__PRIVATE_C_FUNCTION() int crx_c_html_getUtf8CharFromHtmlNamedEntity__doCompare(void const * pKey, void const * pValue)
{
	return strncmp((char const *) pKey, *((char const * const *) pValue),
			strlen(*((char const * const *) pValue)));
}
CRX__LIB__PRIVATE_C_FUNCTION() char const * crx_c_html_getUtf8CharFromHtmlNamedEntity(char const * pName)
{
	char const * const * vEntity = (char const * const *) bsearch(pName,
			gCRX__C__HTML__NAMED_ENTITIES_TO_UTF8,
			sizeof(gCRX__C__HTML__NAMED_ENTITIES_TO_UTF8) / sizeof(*gCRX__C__HTML__NAMED_ENTITIES_TO_UTF8),
			sizeof(*gCRX__C__HTML__NAMED_ENTITIES_TO_UTF8), crx_c_html_getUtf8CharFromHtmlNamedEntity__doCompare);

	return vEntity ? vEntity[1] : NULL;
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_html_insertUtf8Character(unsigned long pCodePoint, 
		char * pTarget, size_t pAvailableLength, bool * pIsNoError)
{
	unsigned char * vBytes = (unsigned char *)pTarget;
	bool vIsNoError = true;
	size_t vReturn = 0;

	if((vBytes != NULL) && (pAvailableLength != 0))
	{
		CRX__C__CHAR__INSERT_UTF8_CHAR(pCodePoint, vBytes, pAvailableLength, vIsNoError, vReturn)
	}
	
	if(pIsNoError != NULL)
		{*pIsNoError = vIsNoError;}

	return vReturn;
}
/*
static bool crx_c_html_decodeHtmlEntitiesToUtf8__processEntity(char const * pStartPosition, char ** pOutputPosition,
		char const ** pFromPosition, size_t * pAvailableLength, bool * pIsNoError)
{
	char const * vEnd = strchr(pStartPosition, ';');

	if(!vEnd)
	{
		*pFromPosition = NULL;
		return false;
	}
	else if(pStartPosition[1] == '#')
	{
		char * tTail = NULL;
		int tOldErrno = errno;
		bool tIsHex = ((pStartPosition[2] == 'x') || (pStartPosition[2] == 'X'));
		unsigned long tCodePoint = 0;
		bool tIsError = false;

		errno = 0;

		tCodePoint = strtoul(pStartPosition + (tIsHex ? 3 : 2), &tTail, tIsHex ? 16 : 10);
		tIsError = errno || (tTail != vEnd) || (tCodePoint > CRX__UNICODE_MAX);

		errno = tOldErrno;
		
		if(tIsError)
			{return false;}
		else
		{
			size_t tNumberOfBytes = crx_c_html_insertUtf8Character(tCodePoint, *pOutputPosition,
					pAvailableLength, pIsNoError);

			if(*pIsNoError)
			{
				*pOutputPosition += tNumberOfBytes;
				*pFromPosition = vEnd + 1;

				return true;
			}
			else
				{return false;}
		}
	}
	else
	{
		char const * tUtf8Char = getUtf8CharFromHtmlNamedEntity(&pStartPosition[1]);

		if(!tUtf8Char)
			{return false;}
		else
		{
			size_t tEntityByteLength = strlen(tUtf8Char);
			
			if(tEntityByteLength > *pAvailableLength)
			{
				memcpy(*pOutputPosition, tUtf8Char, tEntityByteLength);

				*pOutputPosition += tEntityByteLength;
				*pFromPosition = vEnd + 1;
				
				*pAvailableLength -= tEntityByteLength;

				return true;
			}
		}
	}
}*/
/*
WARNING: THIS FUNCTION CURRENTLY WOULD DETECT WHITE SPACE AS PART OF HTML ENTITY, AND THEREFORE
		CAN REMOVE LARGE CHUNKS OF TEXT. I FORGET IF THIS WAS VALID, SECURITY WISE, OR NOT.
*/
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_html_decodeHtmlEntitiesUsingUtf8(char const * pChars, 
		size_t pLength, char * pTarget, size_t pAvailableLength, bool * pWasSpaceSufficient)
{
	CRX_SCOPE_META
	if((pChars == NULL) || (pTarget == NULL))
	{
		if(pWasSpaceSufficient != NULL)
			{*pWasSpaceSufficient = true;}

		return 0;
	}

	CRX_SCOPE
	char const * vCurrentChar = pChars;
	char * vStartChar__outputBuffer = pTarget;
	size_t vRemainingLength = pLength;
	size_t vAvailableLength = pAvailableLength;
	size_t vNumberOfCharactersRemaining = 0;
	bool vIsNoError = true;

	while(true)
	{
		char const * tCurrentChar = (char const *)memchr(vCurrentChar, '&', vRemainingLength);  //strchr(vCurrentChar, '&');

		if(tCurrentChar && vCurrentChar && (vRemainingLength > 0))
		{
			char const * vEnd = (char const *)memchr(tCurrentChar, ';', vRemainingLength - 
					(tCurrentChar - vCurrentChar)); //strchr(tCurrentChar, ';');

			memmove(vStartChar__outputBuffer, vCurrentChar, (size_t)(tCurrentChar - vCurrentChar));
			vStartChar__outputBuffer += tCurrentChar - vCurrentChar;
			vAvailableLength = vAvailableLength - (size_t)(tCurrentChar - vCurrentChar);
			vRemainingLength = vRemainingLength - (size_t)(tCurrentChar - vCurrentChar);
			
			if(!vEnd)
				{break;}
			else
			{
				if(tCurrentChar[1] == '#')
				{
					char * tTail = NULL;
					int tOldErrno = errno;
					bool tIsHex = ((tCurrentChar[2] == 'x') || (tCurrentChar[2] == 'X'));
					unsigned long tCodePoint = 0;
					bool tIsError = false;

					errno = 0;

					tCodePoint = strtoul(tCurrentChar + (tIsHex ? 3 : 2), &tTail, tIsHex ? 16 : 10);
					tIsError = errno || (tTail != vEnd);

					errno = tOldErrno;
					
					if(tIsError) //ERROR IS ASSUMED TO HAPPEN BECAUSE OF WHAT IS THOUGHT TO BE AN ENCODING, IS NOT.
					{
						vCurrentChar = tCurrentChar;
						//*vStartChar__outputBuffer++ = *vCurrentChar++;

						*vStartChar__outputBuffer = *vCurrentChar;

						vStartChar__outputBuffer = vStartChar__outputBuffer + 1;
						vCurrentChar = vCurrentChar + 1;
						vAvailableLength = vAvailableLength - 1;
						vRemainingLength = vRemainingLength - 1;
					}
					else
					{
						size_t tNumberOfBytes /*= ?*/;
						
						if(!CRX__C__CHAR__IS_CODE_POINT_VALID_FOR_UTF(tCodePoint))
							{tCodePoint = 0xFFFDul;}
						
						tNumberOfBytes = crx_c_html_insertUtf8Character(tCodePoint, vStartChar__outputBuffer,
								vAvailableLength, &vIsNoError);

						if(vIsNoError) //ERROR IS ASSUMED FROM NOT ENOUGH SPACE.
						{
							vStartChar__outputBuffer += tNumberOfBytes;
							vCurrentChar = vEnd + 1;
							vAvailableLength = vAvailableLength - tNumberOfBytes;
							vRemainingLength = vRemainingLength - (vEnd - tCurrentChar);
						}
					}
				}
				else
				{
					char const * tUtf8CharString = NULL; //crx_c_html_getUtf8CharFromHtmlNamedEntity(&tCurrentChar[1]);
					
					if(((vEnd - tCurrentChar) < 15) && ((vEnd - tCurrentChar) > 1))
					{
						char tChars[15];//15 SAFE VALUE
						size_t tLength = vEnd - tCurrentChar;

						memcpy(&tChars, &tCurrentChar[1], tLength);
						tChars[tLength + 1] = '\0';
						
						tUtf8CharString = crx_c_html_getUtf8CharFromHtmlNamedEntity(
								&tChars[0]);
					}

					if(!tUtf8CharString)
					{
						size_t tNumberOfBytes = crx_c_html_insertUtf8Character(0xFFFDul, 
								vStartChar__outputBuffer, vAvailableLength, &vIsNoError);

						if(vIsNoError) //ERROR IS ASSUMED FROM NOT ENOUGH SPACE.
						{
							vStartChar__outputBuffer += tNumberOfBytes;
							vCurrentChar = vEnd + 1;
							vAvailableLength = vAvailableLength - tNumberOfBytes;
							vRemainingLength = vRemainingLength - (vEnd - tCurrentChar);
						}
					}
					else
					{
						size_t tEntityByteLength = strlen(tUtf8CharString);
						
						if(tEntityByteLength < vAvailableLength)
						{
							memcpy(vStartChar__outputBuffer, tUtf8CharString, tEntityByteLength);

							vStartChar__outputBuffer += tEntityByteLength;
							vCurrentChar = vEnd + 1;
							vAvailableLength = vAvailableLength - tEntityByteLength;
							vRemainingLength = vRemainingLength - (vEnd - tCurrentChar);
						}
						else
							{vIsNoError = false;}
					}
				}
			}
			
			if(!vIsNoError)
				{break;}
		}
		else
			{break;}
	}

	if(vIsNoError)
	{
		vNumberOfCharactersRemaining = (vAvailableLength > vRemainingLength ? 
				vRemainingLength : (vAvailableLength - 1));

		memmove(vStartChar__outputBuffer, vCurrentChar, vNumberOfCharactersRemaining);
		vStartChar__outputBuffer += vNumberOfCharactersRemaining;
		*vStartChar__outputBuffer++ = '\0';
		vAvailableLength = vAvailableLength - vNumberOfCharactersRemaining - 1;
	}
	
	if(pWasSpaceSufficient != NULL)
		{*pWasSpaceSufficient = vIsNoError;}

	return (size_t)(vStartChar__outputBuffer - pTarget);
	CRX_SCOPE_END
}

//WARNING: THIS FUNCTION WILL REMOVE EACH OCCURANCE OF % AND THE NEXT TWO CHARACTERS, WHETHER
//		THEY REPRESENT A VALID ENCODING OR NOT.
/*CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_html_decodeUrl(char const * pSource, char * pTarget, 
		size_t pAvailableLength, bool * pWasSpaceSufficient)
{
    static const char gDIGIT_CHAR_TO_BYTE[256] =
	{
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
         0, 1, 2, 3, 4, 5, 6, 7,  8, 9,-1,-1,-1,-1,-1,-1,
        -1,10,11,12,13,14,15,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,10,11,12,13,14,15,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1
    };
	size_t vAvailableLength = pAvailableLength - 1; //RESERVING FOR NULL CHARACTER
	char * vCurrentChar = pSource;
	char * vCurrentChar__target = pTarget;
	char * vTarget = pTarget;
	bool vWasSpaceSufficient = true;

    if(vCurrentChar != NULL)
	{
		char c = '\0';
		char tDigit1 = '\0';
		char tDigit2 = '\0';

        while((c = *(vCurrentChar++)) != '\0')
		{
            if(c == '%')
			{
                if(!(tDigit1 = *(vCurrentChar++)) ||
						((tDigit1 = gDIGIT_CHAR_TO_BYTE[(unsigned char)tDigit1]) < 0))
					{vCurrentChar++;}
				else if(!(!(tDigit2 = *(vCurrentChar++)) || 
						((tDigit2 = gDIGIT_CHAR_TO_BYTE[(unsigned char)tDigit2]) < 0)))
				{
					if(vAvailableLength > 0)
					{
						*(vCurrentChar__target++) = (tDigit1 << 4) | tDigit2;
						vAvailableLength--;
					}
					else
					{
						vWasSpaceSufficient = false;
						break;
					}
				}
            }
			else if(c == '+')
			{
				if(vAvailableLength > 0)
				{
					*(vCurrentChar__target++) = ' ';
					vAvailableLength--;
				}
				else
				{
					vWasSpaceSufficient = false;
					break;
				}
			}
			else
			{
				if(vAvailableLength > 0)
				{
					*(vCurrentChar__target++) = c;
					vAvailableLength--;
				}
				else
				{
					vWasSpaceSufficient = false;
					break;
				}
			}
        }
    }

    *(vCurrentChar__target++) = '\0';
	
	if(pWasSpaceSufficient != NULL)
		{*pWasSpaceSufficient = vWasSpaceSufficient;}

    return vCurrentChar__target - pTarget;
}*/

/*THIS FUNCTION USED TO REMOVE BAD ENCODING, BUT THEN, FOLLOWING SIMILAR LOGIC FROM MY SECURITY
		PROJECT ABOUT CAGERS, I DECIDED NOT TO. HOWEVER, UNLIKE THE CAGERS, THERE IS NO PROVEN
		REASON WHY REMOVING CHARACTERS WOULD BE UNSAFE WHEN PROCESSING, AS DEFINED IN THE SECURITY
		PROJECT, IS DONE AFTER THE DECODING. THEREFORE IN PRJECT TERE ARE, OR WERE, DECODERS THAT SIMPLY
		DELETED CHARACTERS. HOWEVER, BECAUSE THIS IS A GENERIC FUNCTION, NOT TIED TO THE PREMISES
		OF THE SECURITY PROJECT, IT MIGH BE BENEFICIAL TO FOLLOW A SIMILAR PATTERN AS WITH THE CAGERS
		THERE AND GENERALY AVOID REMOVING CHARACTERS, AND INSTEAD ONLY EVER REPLACE THEM WITH NON
		EMPTY SEGMENTS.
		I SRUVEYED PHP, PYTHON, AND JAVA, AND ONLY JAVA'S STANDARD FUNCTIONS FOR DECODING URLS 
		THROW AN EXCEPTION INSTEAD OF LEAVING THE WRONG ENCODINGS INTACT.
*/
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_html_decodeUrl(char const * pSource, 
		size_t pLength, char * pTarget, size_t pAvailableLength, bool * pWasSpaceSufficient)
{
    static const char gDIGIT_CHAR_TO_BYTE[256] =
	{
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
         0, 1, 2, 3, 4, 5, 6, 7,  8, 9,-1,-1,-1,-1,-1,-1,
        -1,10,11,12,13,14,15,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,10,11,12,13,14,15,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1
    };
	size_t vRemainingLength = pLength;
	size_t vAvailableLength = pAvailableLength - 1; //RESERVING FOR NULL CHARACTER
	char const * vCurrentChar = pSource;
	char * vCurrentChar__target = pTarget;
	char * vTarget = pTarget;
	bool vWasSpaceSufficient = true;

    //if(vCurrentChar != NULL)
	if(vRemainingLength > 0)
	{
		char c = '\0';
		char tDigit1 = '\0';
		char tDigit2 = '\0';

        //while((c = *(vCurrentChar++)) != '\0')
		while(vRemainingLength > 2)
		{
            if((c = *(vCurrentChar++)) == '%')
			{
                if(!(tDigit1 = *(vCurrentChar++)) ||
						(gDIGIT_CHAR_TO_BYTE[(unsigned char)tDigit1] < 0))
				{
					//vCurrentChar++; //THIS PART WAS INSTEAD OF THAT BELOW WHEN THE FUNCTION REMOVED BAD ENCODING
					vRemainingLength = vRemainingLength - 2;
					*(vCurrentChar__target++) = c;
					*(vCurrentChar__target++) = tDigit1;
				}
				else if(!(tDigit2 = *(vCurrentChar++)) || 
						(gDIGIT_CHAR_TO_BYTE[(unsigned char)tDigit2] < 0))
				{
					//THIS PART DID NOT EXIST WHEN THE FUNCTION REMOVED BAD ENCODING
					vRemainingLength = vRemainingLength - 3;
					*(vCurrentChar__target++) = c;
					*(vCurrentChar__target++) = tDigit1;
					*(vCurrentChar__target++) = tDigit2;					
				}
				else
				{
					vRemainingLength = vRemainingLength - 3;

					if(vAvailableLength > 0)
					{
						*(vCurrentChar__target++) = (gDIGIT_CHAR_TO_BYTE[(unsigned char)tDigit1] << 4) | 
								gDIGIT_CHAR_TO_BYTE[(unsigned char)tDigit2];
						vAvailableLength--;
					}
					else
					{
						vWasSpaceSufficient = false;
						break;
					}
				}
            }
			else if(c == '+')
			{
				vRemainingLength--;

				if(vAvailableLength > 0)
				{
					*(vCurrentChar__target++) = ' ';
					vAvailableLength--;
				}
				else
				{
					vWasSpaceSufficient = false;
					break;
				}
			}
			else
			{
				vRemainingLength--;

				if(vAvailableLength > 0)
				{
					*(vCurrentChar__target++) = c;
					vAvailableLength--;
				}
				else
				{
					vWasSpaceSufficient = false;
					break;
				}
			}
        }
		if(vWasSpaceSufficient)
		{
			if(vRemainingLength == 2)
			{
				*(vCurrentChar__target++) = *(vCurrentChar++);
				*(vCurrentChar__target++) = *(vCurrentChar++);
			}
			else if(vRemainingLength == 1)
				{*(vCurrentChar__target++) = *(vCurrentChar++);}
		}
    }

    *(vCurrentChar__target++) = '\0';
	
	if(pWasSpaceSufficient != NULL)
		{*pWasSpaceSufficient = vWasSpaceSufficient;}

    return vCurrentChar__target - pTarget;
}

#if 0
size_t crx_c_html_getNextUt8Character(char * pChars, uint32_t * pCodePoint, size_t pAvailableLength, 
		bool * pIsNoError)
{
	char * vChar = pChars;

	if(pAvailableLength > 0)
	{
		if(*vChar <= 0x007Ful)
		{
			if(pAvailableLength > 0)
			{
				*pCodePoint = *vChar;
				vChar++;
			}

			return vChar;
		}
		else if(*vChar >= 0x00C0ul)
		{
			if((*vChar <= 0x00DFul) && (pAvailableLength > 2) && 
					(*(vChar + 1) >= 0x0080ul) && (*(vChar + 1) <= 0x00BFul))
			{
				*pCodePoint = ((((uint32_t) *(vChar)) && 1F) << 6) | 
						(((uint32_t) *(vChar + 1)) && 3F);
				vChar = vChar + 2;
			}
			
			return vChar;
		}
		else if(*vChar <= 0x00EFul)
		{
			if((pAvailableLength > 2) && (*(vChar + 1) >= 0x0080ul) && (*(vChar + 1) <= 0x00BFul) &&
					(*(vChar + 2) >= 0x0080ul) && (*(vChar + 2) <= 0x00BFul))
			{
				*pCodePoint = ((((uint32_t) *(vChar)) && 1F) << 12) | 
						((((uint32_t) *(vChar + 1)) && 3F) << 6) | 
						(((uint32_t) *(vChar + 2)) && 3F);
				vChar = vChar + 3;
			}
			
			return vChar;
		}
		else
		{
			if((pAvailableLength > 3) && (*(vChar + 1) >= 0x0080ul) && (*(vChar + 1) <= 0x00BFul) &&
					(*(vChar + 2) >= 0x0080ul) && (*(vChar + 2) <= 0x00BFul) && 
					(*(vChar + 3) >= 0x0080ul) && (*(vChar + 3) <= 0x00BFul))
			{
				*pCodePoint = ((((uint32_t) *(vChar)) && 1F) << 18) | 
						((((uint32_t) *(vChar + 1)) && 3F) << 12) | 
						((((uint32_t) *(vChar + 2)) && 3F) << 6)
						(((uint32_t) *vChar + 3) && 3F);
				vChar = vChar + 4;
			}
			
			return vChar;
		}
	}
}


size_t crx_c_insertUtf16Character(unsigned long cp, char * pTarget, size_t pAvailableLength, 
		bool * pIsNoError)
{
	unsigned char * vBytes = (unsigned char *)pTarget;
	bool vIsNoError = true;
	size_t vReturn = 0;
	

	if((vBytes != NULL) && (pAvailableLength != 0))
	{
		if((cp <= 0xD7FFul) || ((cp <= 0xFFFFul) && (cp >= 0xE000ul)))
		{
			if(pAvailableLength > 1)
			{
				vBytes[1] = ((unsigned char) cp);
				vBytes[0] = ((unsigned char) (cp >> 8));

				vReturn = 2;
			}
			else
				{vIsNoError = false;}
		}
		else if((cp >= 0x010000ul) && (cp <= 0x10FFFFul))
		{
			unsigned long tUnsignedLong = (cp - 0x10000ul);
			
			((tUnsignedLong >> 10) | 0xD80000UL)

			if(pAvailableLength > 2)
			{
				vBytes[3] = ((unsigned char) ((tUnsignedLong & 0x03FFul) | 0xDC00UL));
				vBytes[2] = ((unsigned char) (((tUnsignedLong & 0x03FFul) | 0xDC00UL) >> 8));

				vBytes[1] = ((unsigned char) ((tUnsignedLong >> 10) | 0xD800UL));
				vBytes[0] = ((unsigned char) (((tUnsignedLong >> 10) | 0xD800UL) >> 8));

				vReturn = 4;
			}
			else
				{vIsNoError = false;}
		}
		else
			{vIsNoError = false;}
	}
	
	if(pIsNoError != NULL)
		{*pIsNoError = false;}

	return vReturn;
}

#endif

CRX__LIB__C_CODE_END()

