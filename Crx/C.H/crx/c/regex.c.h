#include "../../../H/crx/c/regex.h"


size_t crx_c_regex_escapeRegularExpressionTokens(char * const pSource, char * pTarget, size_t pAvailableLength,
		size_t * pWasSpaceSufficient)
{
	if((pSource == NULL) || (pTarget == NULL))
		{return 0;}

	char * vCurrentChar = pSource;
	char * vCurrentChar__target = pTarget;
	char * vTarget = pTarget;
	size_t vAvailableLength = pAvailableLength;
	bool vWasSpaceSufficient = true;

	while(((*vCurrentChar) != '\0') && (vAvailableLength > 1))
	{
		char tChar = *vCurrentChar++;

		if((tChar == '\\') ||  (tChar == '*') ||  (tChar == '+') ||  (tChar == '?') ||  
				(tChar == '|') ||  (tChar == '{') ||  (tChar == '[') ||  (tChar == '(') ||  
				(tChar == ')') ||  (tChar == '^') ||  (tChar == '$') ||  (tChar == '.') ||
				(tChar == '#') || (tChar == ']'))
		{
			if(vAvailableLength > 2)
			{
				*(vCurrentChar__target++) = '\\';
				*(vCurrentChar__target++) = tChar;
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
			if(vAvailableLength > 1)
			{
				*(vCurrentChar__target++) = tChar;
				vAvailableLength--;
			}
			else
			{
				vWasSpaceSufficient = false;
				break;
			}
		}
	}
	
	*vCurrentChar__target = '/0';
	
	if(pWasSpaceSufficient != NULL)
		{*pWasSpaceSufficient = vWasSpaceSufficient;}

	return pAvailableLength - vAvailableLength - 1;
}