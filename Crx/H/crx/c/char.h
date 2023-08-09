#if(!defined(CRX__C__CHAR___h__))
#define CRX__C__CHAR___h__

#include <boost/version.hpp>
#include "Crx/H/crx/crx.h"

CRX__LIB__C_CODE_BEGIN()

//-------------------------------------
//CHARACTER TO CODE POINT
//-------------------------------------
#define CRX__C__CHAR__GET_NEXT_CODE_POINT_FROM_UTF8_CHAR_ARRAY(pCHAR_POINTER, pCODE_POINT, \
		pAVAILABLELENGTH, pIS_NO_ERROR, pNUMBER_OF_TRAVERSED_CHARACTERS) \
	if(pAVAILABLELENGTH > 0) \
	{ \
		if(*pCHAR_POINTER <= 0x007Ful) \
		{ \
			CRXM__IFELSE(pNUMBER_OF_TRAVERSED_CHARACTERS) \
			( \
				pCODE_POINT = *pCHAR_POINTER; \
\
				pNUMBER_OF_TRAVERSED_CHARACTERS = 1; \
			) \
			( \
				pCODE_POINT = *(pCHAR_POINTER++); \
\
				pAVAILABLELENGTH = pAVAILABLELENGTH - 1; \
			) \
		} \
		else if(*pCHAR_POINTER <= 0x00DFul) \
		{ \
			if((*pCHAR_POINTER >= 0x00C2ul) && (pAVAILABLELENGTH > 2) && \
					(*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x00BFul)) \
			{ \
				CRXM__IFELSE(pNUMBER_OF_TRAVERSED_CHARACTERS) \
				( \
					pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 1F) << 6) | \
							(((uint32_t) *(pCHAR_POINTER + 1)) && 3F); \
\
					pNUMBER_OF_TRAVERSED_CHARACTERS = 2; \
				) \
				( \
					pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 1F) << 6) | \
							(((uint32_t) *(pCHAR_POINTER + 1)) && 3F); \
					pCHAR_POINTER = pCHAR_POINTER + 2; \
\
					pAVAILABLELENGTH = pAVAILABLELENGTH - 2; \
				) \
			} \
			else \
				{pIS_NO_ERROR = false;} \
		} \
		else if(*pCHAR_POINTER <= 0x00EFul) \
		{ \
			if((pAVAILABLELENGTH > 2) && (*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x00BFul) && \
					(*(pCHAR_POINTER + 2) >= 0x0080ul) && (*(pCHAR_POINTER + 2) <= 0x00BFul) && \
					((*pCHAR_POINTER != 0x00E0ul) || (*(pCHAR_POINTER + 1) > 0x00A0ul))) \
			{ \
				CRXM__IFELSE(pNUMBER_OF_TRAVERSED_CHARACTERS) \
				( \
					pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 1F) << 12) | \
							((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 6) | \
							(((uint32_t) *(pCHAR_POINTER + 2)) && 3F); \
\
					pNUMBER_OF_TRAVERSED_CHARACTERS = 3; \
				) \
				( \
					pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 1F) << 12) | \
							((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 6) | \
							(((uint32_t) *(pCHAR_POINTER + 2)) && 3F); \
					pCHAR_POINTER = pCHAR_POINTER + 3; \
\
					pAVAILABLELENGTH = pAVAILABLELENGTH - 3; \
				) \
			} \
			else \
				{pIS_NO_ERROR = false;} \
		} \
		else if(*pCHAR_POINTER <= 0x00F4ul) \
		{ \
			if((pAVAILABLELENGTH > 3) && (*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x00BFul) && \
					(*(pCHAR_POINTER + 2) >= 0x0080ul) && (*(pCHAR_POINTER + 2) <= 0x00BFul) && \
					(*(pCHAR_POINTER + 3) >= 0x0080ul) && (*(pCHAR_POINTER + 3) <= 0x00BFul) && \
					((*pCHAR_POINTER != 0x00F0ul) || (*(pCHAR_POINTER + 1) > 0x00A0ul))) \
			{ \
				CRXM__IFELSE(pNUMBER_OF_TRAVERSED_CHARACTERS) \
				( \
					pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 1F) << 18) | \
							((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 12) | \
							((((uint32_t) *(pCHAR_POINTER + 2)) && 3F) << 6) \
							(((uint32_t) *pCHAR_POINTER + 3) && 3F); \
\
					pNUMBER_OF_TRAVERSED_CHARACTERS = 4; \
				) \
				( \
					pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 1F) << 18) | \
							((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 12) | \
							((((uint32_t) *(pCHAR_POINTER + 2)) && 3F) << 6) \
							(((uint32_t) *pCHAR_POINTER + 3) && 3F); \
					pCHAR_POINTER = pCHAR_POINTER + 4; \
\
					pAVAILABLELENGTH = pAVAILABLELENGTH - 4; \
				) \
			} \
			else \
				{pIS_NO_ERROR = false;} \
		} \
	} \
	if((pCODE_POINT > 0x10FFFFul) || ((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDFFFul))) \
		{pIS_NO_ERROR = false;} 
//#END_DEFINE

#define CRX__C__CHAR__GET_NEXT_CODE_POINT_FROM_UTF8_STRING(pCHAR_POINTER, pCODE_POINT, \
		pIS_NO_ERROR) \
	if(*pCHAR_POINTER != '\0') \
	{ \
		if(*pCHAR_POINTER <= 0x007Ful) \
		{ \
			pCODE_POINT = *(pCHAR_POINTER++); \
		} \
		else if(*pCHAR_POINTER <= 0x00DFul) \
		{ \
			if((*pCHAR_POINTER >= 0x00C2ul) && \
					(*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x00BFul)) \
			{ \
				pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 1F) << 6) | \
						(((uint32_t) *(pCHAR_POINTER + 1)) && 3F); \
				pCHAR_POINTER = pCHAR_POINTER + 2; \
			} \
			else \
				{pIS_NO_ERROR = false;} \
		} \
		else if(*pCHAR_POINTER <= 0x00EFul) \
		{ \
			if((*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x00BFul) && \
					(*(pCHAR_POINTER + 2) >= 0x0080ul) && (*(pCHAR_POINTER + 2) <= 0x00BFul) && \
					((*pCHAR_POINTER != 0x00E0ul) || (*(pCHAR_POINTER + 1) > 0x00A0ul))) \
			{ \
				pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 1F) << 12) | \
						((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 6) | \
						(((uint32_t) *(pCHAR_POINTER + 2)) && 3F); \
				pCHAR_POINTER = pCHAR_POINTER + 3; \
			} \
			else \
				{pIS_NO_ERROR = false;} \
		} \
		else if(*pCHAR_POINTER <= 0x00F4ul) \
		{ \
			if((*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x00BFul) && \
					(*(pCHAR_POINTER + 2) >= 0x0080ul) && (*(pCHAR_POINTER + 2) <= 0x00BFul) && \
					(*(pCHAR_POINTER + 3) >= 0x0080ul) && (*(pCHAR_POINTER + 3) <= 0x00BFul) && \
					((*pCHAR_POINTER != 0x00F0ul) || (*(pCHAR_POINTER + 1) > 0x00A0ul))) \
			{ \
				pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 1F) << 18) | \
						((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 12) | \
						((((uint32_t) *(pCHAR_POINTER + 2)) && 3F) << 6) \
						(((uint32_t) *pCHAR_POINTER + 3) && 3F); \
				pCHAR_POINTER = pCHAR_POINTER + 4; \
			} \
			else \
				{pIS_NO_ERROR = false;} \
		} \
	} \
	if((pCODE_POINT > 0x10FFFFul) || ((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDFFFul))) \
		{pIS_NO_ERROR = false;} 
//#END_DEFINE

#define CRX__C__CHAR__GET_NEXT_CODE_POINT_FROM_UTF16_CHAR_ARRAY(pIS_BIG_ENDIAN, pCHAR_POINTER, \
		pCODE_POINT, pAVAILABLELENGTH, pIS_NO_ERROR, pNUMBER_OF_TRAVERSED_CHARACTERS) \
	if(pAVAILABLELENGTH > 1) \
	{ \
		pCODE_POINT = CRXM__IFELSE2(pIS_BIG_ENDIAN, \
				(((uint32_t) *pCHAR_POINTER) << 8) | ((uint32_t) *(pCHAR_POINTER + 1)), \
				(((uint32_t) *(pCHAR_POINTER + 1)) << 8) | ((uint32_t) *pCHAR_POINTER)); \
\
		if((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDBFFul)) \
		{ \
			if(pAVAILABLELENGTH > 3) \
			{ \
				uint32_t tCharacterCode2 = CRXM__IFELSE2(pIS_BIG_ENDIAN, \
						(((uint32_t) *(pCHAR_POINTER + 2)) << 8) | ((uint32_t) *(pCHAR_POINTER + 3)), \
						(((uint32_t) *(pCHAR_POINTER + 3)) << 8) | ((uint32_t) *(pCHAR_POINTER + 2))); \
\
				if((tCharacterCode2 >= 0xDC00ul) && (tCharacterCode2 <= 0xDFFFul)) \
				{ \
					pCODE_POINT = (((pCODE_POINT & 0x3FFul) << 10) | \
							(tCharacterCode2 & 0x3FFul)) + 0x10000ul; \
\
					CRXM__IFELSE(pNUMBER_OF_TRAVERSED_CHARACTERS) \
					( \
						pNUMBER_OF_TRAVERSED_CHARACTERS = 4; \
					) \
					( \
						pCHAR_POINTER = pCHAR_POINTER + 4; \
						pAVAILABLELENGTH = pAVAILABLELENGTH - 4; \
					) \
				} \
				else \
					{pIS_NO_ERROR = false;} \
			} \
			else \
				{pIS_NO_ERROR = false;} \
		} \
		else \
		{ \
			CRXM__IFELSE(pNUMBER_OF_TRAVERSED_CHARACTERS) \
			( \
				pNUMBER_OF_TRAVERSED_CHARACTERS = 2; \
			) \
			( \
				pCHAR_POINTER = pCHAR_POINTER + 2; \
				pAVAILABLELENGTH = pAVAILABLELENGTH - 2; \
			) \
		} \
	} \
	else \
		{pIS_NO_ERROR = (pAVAILABLELENGTH != 1);} \
//#END_DEFINE

//SAME AS UTF16 BUT WITOUT SURROGATE PAIRS
#define CRX__C__CHAR__GET_NEXT_CODE_POINT_FROM_UCS2_CHAR_ARRAY(pIS_BIG_ENDIAN, pCHAR_POINTER, \
		pCODE_POINT, pAVAILABLELENGTH, pIS_NO_ERROR) \
	if(pAVAILABLELENGTH > 1) \
	{ \
		pCODE_POINT = CRXM__IFELSE2(pIS_BIG_ENDIAN, \
				(((uint32_t) *pCHAR_POINTER) << 8) | ((uint32_t) *(pCHAR_POINTER + 1)), \
				(((uint32_t) *(pCHAR_POINTER + 1)) << 8) | ((uint32_t) *pCHAR_POINTER)); \
\
		if((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDBFFul)) \
			{pIS_NO_ERROR = false;} \
		else \
			{pCHAR_POINTER = pCHAR_POINTER + 2;} \
	} \
	else \
		{pIS_NO_ERROR = (pAVAILABLELENGTH != 1);} \
//#END_DEFINE

#define CRX__C__CHAR__GET_NEXT_CODE_POINT_FROM_UTF32_CHAR_ARRAY(pIS_BIG_ENDIAN, pCHAR_POINTER, \
		pCODE_POINT, pAVAILABLELENGTH, pIS_NO_ERROR) \
	if(pAVAILABLELENGTH > 4) \
	{ \
		pCODE_POINT = CRXM__IFELSE2(pIS_BIG_ENDIAN, \
				(((uint32_t) *pCHAR_POINTER) << 24) | (((uint32_t) *(pCHAR_POINTER + 1)) << 16) | \
				(((uint32_t) *(pCHAR_POINTER + 2)) << 8) | ((uint32_t) *(pCHAR_POINTER + 3)), \
				(((uint32_t) *(pCHAR_POINTER + 3)) << 24) | (((uint32_t) *(pCHAR_POINTER + 2)) << 16) | \
				(((uint32_t) *(pCHAR_POINTER + 1)) << 8) | ((uint32_t) *pCHAR_POINTER)); \
\
		if((pCODE_POINT > 0x10FFFFul) || ((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDFFFul))) \
			{pIS_NO_ERROR = false;}  \
	} \
	else \
		{pIS_NO_ERROR = (pAVAILABLELENGTH == 0);} \
//#END_DEFINE




//-------------------------------------
//CODE POINT TO CHARACTER
//-------------------------------------

/*
DESIGN NOTES:

		IS TO NULL		IS TO RETURN # OF 		IS TO ACCEPT AND 			IS TO ADVANCE
						ADDED CHARACTERS		UPDATE NUMBER OF			POINTER			|	IS TO CATCH 
												REMAINING CHARACTERS						|	ERROR ON NOT
																							|	ENOUGH SPACE
			1				0							0						0			|		0
			0				1							0						0			|		0
			0				0							1						1			|		1
			0				1							1						0			|		1
			
	THE ABOVE ARE THE ONLY COMBINATIONS OF OPTIONS THAT ARE VALID. FOR EXAMPLE IF THE RETURNED
	CHARACTER ARRAY IS TO BE NULL, MAKING IT A STRING, THEN THE CALLER NEED NOT ASK FOR THE
	NUMBER OF ADDED CHARACTERS, NOR THE NUMBER OF REMAINING CHARACTERS, NOR TO ADVANCE THE
	POINTER. THIS WOULD BE A CASE WHERE THE USER HAS AN ARRAY OF CHARACTERS THAT HE IS REUSING FOR
	EACH CODE POINT.
	
	NOTICE HOW THE FIRST TWO ROWS IN THE TABLE INVOLVE NO NEED FOR ERROR REPORTING RELATED TO NOT
	ENOUGH SPACE IN THE PASSED BUFFER. FOR EXAMPLE IF THE CASE OF THE SECOND REPORT WAS TO INVOLVE
	ERROR REPORTING, THEN HOW WOULD THE MACRO KNOW IF THERE IS AN ERROR IF IT DOES NOT KNOW THE
	NUMBER OF REMAINING CHARACTERS.
	
	LIKEWISE, NOTICE HOW THE LAST TWO ROWS INVOLVE A NEED FOR ERROR REPORTING RELATD TO NOT ENOUGH
	SPACE.
	
	THE LAST TWO ROWS ARE IMPLEMENTED IN THEIR OWN MACROS (INSERT). IF pNUMBER_OF_INSERTED_CHARACTERS
	IS SET, THE MACRO SETS THE CORRECT VALUE TO IT, OTHERWISE THE POINTER, pCHARS_POINTER, IS
	CORRECTLY UPDATED. NOTE THAT FOR ROW FOUR WE OPTIMIZE OUT THE UPDATING OF REMAINING CHARACTERS
	BECAUSE THE CALLER WILL GET THE NUMBER OF ADDED CHARACTERS, AND THEREFORE HE CAN DO THAT HIMSELF.
	HOWEVER, WE STILL NEED THE NUMBER OF REMAINING CHARACTERS TO DO THE ERROR DETECTION.
	
	THE FIRST TWO ROWS ARE IMPLEMENTED IN THEIR OWN MACROS (FAST INSERT). IF pNUMBER_OF_INSERTED_CHARACTERS
	IS SET, THE MACRO SETS THE CORRECT VALUE TO IT, OTHERWISE THE RETURNED CHARACTER ARRAY IS NULL TERMINATED.
	UNLIKE THE "INSERT" MACROS, THE "FAST INSERT" MACROS DO NOT CHECK IF THE CODE POINT IS VALID. AN INVALID
	CODE POINT LEADS TO UNDEFINED BEHAVIOR. CODE MUST USE THE MACRO CRX__C__CHAR__IS_CODE_POINT_VALID_FOR_UTF(),
	OR CRX__C__CHAR__IS_CODE_POINT_VALID_FOR_UCS2(), IF IT IS UNSURE.
	NOTE THAT ALTHOUGH THE "FAST INSERT" FUNCTIONS DO NOT CHECK FOR INVALID CODE POINTS, THE CHECK IS STILL 
	INDIRECTLY DONE IN THE UTF16 CASE, AND THE INFORMATION OF AN ERROR LEAKS. THIS IS NOT TO BE CONFUSED
	WITH AN ERROR CHECK AS PART OF THE DESIGN FOR THE "FAST INSERT" MACROS. THIS JUST HAPPENS FOR UTF16.
	
	NOTE THAT IN THE CASE OF UTF32, WE OPTIMIZE OUT THE UPDATING OF ADDED CHARACTERS BECAUSE IT IS ALWAYS HERE,
	AND HENCE THE OPTIONS CHANGE SLIGHTLY. FOR ROWS THREE AND FOUR INSTEAD OF THE PARAMETER FOR NUMBER OF 
	ADDED CHARACTERS, THERE EXISTS A PARAMETER ABOUT WHETHER TO ADVANCE THE POINTER OR NOT. FOR ROWS
	ONE AND TWO, INSTEAD OF THE PARAMETER FOR NUMBER OF ADDED CHARACTERS, THERE EXISTS A PARAMETER ABOUT
	WHETHER TO NULL THE CHARACTER ARRAY OR NOT.
*/

#define CRX__C__CHAR__IS_CODE_POINT_VALID_FOR_UTF(pCODE_POINT) \
		((pCODE_POINT <= 0x10FFFFul) && !((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDFFFul)))

#define CRX__C__CHAR__IS_CODE_POINT_VALID_FOR_UCS2(pCODE_POINT) \
		((pCODE_POINT <= 0xFFFFul) && !((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDFFFul)))

#define CRX__C__CHAR__REQUIRED_NUMBER_OF_BYTES_FOR_CODE_POINT_IN_UTF8(pCODE_POINT) \
		((pCODE_POINT <= 0x007Ful) ? 1 : ((pCODE_POINT <= 0x07FFul) ? 2 : \
				((pCODE_POINT <= 0xFFFFul) ? 3 : 4)))

#define CRX__C__CHAR__REQUIRED_NUMBER_OF_BYTES_FOR_CODE_POINT_IN_UTF16(pCODE_POINT) \
		((pCODE_POINT <= 0xFFFFul) ? 2 : 4)

#define CRX__C__CHAR__REQUIRED_NUMBER_OF_BYTES_FOR_CODE_POINT_IN_UTF32(pCODE_POINT) 4

//REMEMBER THAT THERE IS NO ENDIANNES WITH UTF8
#define CRX__C__CHAR__INSERT_UTF8_CHAR(pCODE_POINT, pCHARS_POINTER, pAVAILABLE_LENGTH, \
		pIS_NO_ERROR, pNUMBER_OF_INSERTED_CHARACTERS) \
	if(pCODE_POINT <= 0x007Ful) \
	{ \
		if(pAVAILABLE_LENGTH > 1) \
		{ \
			CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
			( \
				pCHARS_POINTER[0] = (unsigned char)pCODE_POINT; \
\
				pNUMBER_OF_INSERTED_CHARACTERS = 1; \
			) \
			( \
				*(pCHARS_POINTER++) = (unsigned char)pCODE_POINT; \
\
				pAVAILABLE_LENGTH = pAVAILABLE_LENGTH - 1; \
			) \
		} \
		else \
			{pIS_NO_ERROR = false;} \
	} \
	else if(pCODE_POINT <= 0x07FFul) \
	{ \
		if(pAVAILABLE_LENGTH > 2) \
		{ \
			CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
			( \
				pCHARS_POINTER[0] = (unsigned char)((6 << 5) | (pCODE_POINT >> 6)); \
				pCHARS_POINTER[1] = (unsigned char)((2 << 6) | (pCODE_POINT & 0x3F)); \
\
				pNUMBER_OF_INSERTED_CHARACTERS = 2; \
			) \
			( \
				*(pCHARS_POINTER++) = (unsigned char)((6 << 5) | (pCODE_POINT >> 6)); \
				*(pCHARS_POINTER++) = (unsigned char)((2 << 6) | (pCODE_POINT & 0x3F)); \
\
				pAVAILABLE_LENGTH = pAVAILABLE_LENGTH - 2; \
			) \
		} \
		else \
			{pIS_NO_ERROR = false;} \
	} \
	else if(pCODE_POINT <= 0xFFFFul) \
	{ \
		if((pAVAILABLE_LENGTH > 3) && !((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDFFFul)))\
		{ \
			CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
			( \
				pCHARS_POINTER[0] = (unsigned char)((14 << 4) |  (pCODE_POINT >> 12)); \
				pCHARS_POINTER[1] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 6) & 0x3F)); \
				pCHARS_POINTER[2] = (unsigned char)(( 2 << 6) | ( pCODE_POINT       & 0x3F)); \
\
				pNUMBER_OF_INSERTED_CHARACTERS = 3; \
			) \
			( \
				*(pCHARS_POINTER++) = (unsigned char)((14 << 4) |  (pCODE_POINT >> 12)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 6) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ( pCODE_POINT       & 0x3F)); \
\
				pAVAILABLE_LENGTH = pAVAILABLE_LENGTH - 3; \
			) \
		} \
		else \
			{pIS_NO_ERROR = false;} \
	} \
	else if(pCODE_POINT <= 0x10FFFFul) \
	{ \
		if(pAVAILABLE_LENGTH > 4) \
		{ \
			CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
			( \
				pCHARS_POINTER[0] = (unsigned char)((30 << 3) |  (pCODE_POINT >> 18)); \
				pCHARS_POINTER[1] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 12) & 0x3F)); \
				pCHARS_POINTER[2] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >>  6) & 0x3F)); \
				pCHARS_POINTER[3] = (unsigned char)(( 2 << 6) | ( pCODE_POINT        & 0x3F)); \
\
				pNUMBER_OF_INSERTED_CHARACTERS = 4; \
			) \
			( \
				*(pCHARS_POINTER++) = (unsigned char)((30 << 3) |  (pCODE_POINT >> 18)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 12) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >>  6) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ( pCODE_POINT        & 0x3F)); \
\
				pAVAILABLE_LENGTH = pAVAILABLE_LENGTH - 4; \
			) \
		} \
		else \
			{pIS_NO_ERROR = false;} \
	} \
	else \
		{pIS_NO_ERROR = false;} \
//#END_DEFINE
		
#define CRX__C__CHAR__FAST_INSERT_UTF8_CHAR(pCODE_POINT, pCHARS_POINTER, \
		pNUMBER_OF_INSERTED_CHARACTERS) \
	if(pCODE_POINT <= 0x007Ful) \
	{ \
		pCHARS_POINTER[0] = (unsigned char)pCODE_POINT; \
	\
		CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
		( \
			pNUMBER_OF_INSERTED_CHARACTERS = 1; \
		) \
		( \
			pCHARS_POINTER[1] = '\0'; \
		) \
	} \
	else if(pCODE_POINT <= 0x07FFul) \
	{ \
		pCHARS_POINTER[1] = (unsigned char)((2 << 6) | (pCODE_POINT & 0x3F)); \
		pCHARS_POINTER[0] = (unsigned char)((6 << 5) | (pCODE_POINT >> 6)); \
	\
		CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
		( \
			pNUMBER_OF_INSERTED_CHARACTERS = 2; \
		) \
		( \
			pCHARS_POINTER[2] = '\0'; \
		) \
	} \
	else if(pCODE_POINT <= 0xFFFFul) \
	{ \
		pCHARS_POINTER[2] = (unsigned char)(( 2 << 6) | ( pCODE_POINT       & 0x3F)); \
		pCHARS_POINTER[1] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 6) & 0x3F)); \
		pCHARS_POINTER[0] = (unsigned char)((14 << 4) |  (pCODE_POINT >> 12)); \
	\
		CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
		( \
			pNUMBER_OF_INSERTED_CHARACTERS = 3; \
		) \
		( \
			pCHARS_POINTER[3] = '\0'; \
		) \
	} \
	else if(pCODE_POINT <= 0x10FFFFul) \
	{ \
		pCHARS_POINTER[3] = (unsigned char)(( 2 << 6) | ( pCODE_POINT        & 0x3F)); \
		pCHARS_POINTER[2] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >>  6) & 0x3F)); \
		pCHARS_POINTER[1] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 12) & 0x3F)); \
		pCHARS_POINTER[0] = (unsigned char)((30 << 3) |  (pCODE_POINT >> 18)); \
	\
		CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
		( \
			pNUMBER_OF_INSERTED_CHARACTERS = 4; \
		) \
		( \
			pCHARS_POINTER[4] = '\0'; \
		) \
	}
//#END_DEFINE

#define CRX__C__CHAR__INSERT_UTF16_CHAR(pIS_BIG_ENDIAN, pCODE_POINT, pCHARS_POINTER, \
		pAVAILABLE_LENGTH, pIS_NO_ERROR, pNUMBER_OF_INSERTED_CHARACTERS) \
	if((pCODE_POINT <= 0xD7FFul) || ((pCODE_POINT <= 0xFFFFul) && (pCODE_POINT >= 0xE000ul))) \
	{ \
		if(pAVAILABLE_LENGTH > 1) \
		{ \
			CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
			( \
				CRXM__IFELSE(pIS_BIG_ENDIAN) \
				( \
					pCHARS_POINTER[0] = ((unsigned char) (pCODE_POINT >> 8)); \
					pCHARS_POINTER[1] = ((unsigned char) pCODE_POINT); \
				) \
				( \
					pCHARS_POINTER[0] = ((unsigned char) pCODE_POINT); \
					pCHARS_POINTER[1] = ((unsigned char) (pCODE_POINT >> 8)); \
				) \
\
				pNUMBER_OF_INSERTED_CHARACTERS = 2; \
			) \
			( \
				CRXM__IFELSE(pIS_BIG_ENDIAN) \
				( \
					*(pCHARS_POINTER++) = ((unsigned char) (pCODE_POINT >> 8)); \
					*(pCHARS_POINTER++) = ((unsigned char) pCODE_POINT); \
				) \
				( \
					*(pCHARS_POINTER++) = ((unsigned char) pCODE_POINT); \
					*(pCHARS_POINTER++) = ((unsigned char) (pCODE_POINT >> 8)); \
				) \
\
				pAVAILABLE_LENGTH = pAVAILABLE_LENGTH - 2; \
			) \
		} \
		else \
			{pIS_NO_ERROR = false;} \
	} \
	else if((pCODE_POINT >= 0x010000ul) && (pCODE_POINT <= 0x10FFFFul)) \
	{ \
		unsigned long tUnsignedLong = (pCODE_POINT - 0x10000ul); \
\
		((tUnsignedLong >> 10) | 0xD80000UL) \
\
		if(pAVAILABLE_LENGTH > 2) \
		{ \
			CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
			( \
				CRXM__IFELSE(pIS_BIG_ENDIAN) \
				( \
					pCHARS_POINTER[0] = ((unsigned char) (((tUnsignedLong >> 10) | 0xD800UL) >> 8)); \
					pCHARS_POINTER[1] = ((unsigned char) ((tUnsignedLong >> 10) | 0xD800UL)); \
					pCHARS_POINTER[2] = ((unsigned char) (((tUnsignedLong & 0x03FFul) | 0xDC00UL) >> 8)); \
					pCHARS_POINTER[3] = ((unsigned char) ((tUnsignedLong & 0x03FFul) | 0xDC00UL)); \
				) \
				( \
					pCHARS_POINTER[0] = ((unsigned char) ((tUnsignedLong >> 10) | 0xD800UL)); \
					pCHARS_POINTER[1] = ((unsigned char) (((tUnsignedLong >> 10) | 0xD800UL) >> 8)); \
					pCHARS_POINTER[2] = ((unsigned char) ((tUnsignedLong & 0x03FFul) | 0xDC00UL)); \
					pCHARS_POINTER[3] = ((unsigned char) (((tUnsignedLong & 0x03FFul) | 0xDC00UL) >> 8)); \
				) \
\
				pNUMBER_OF_INSERTED_CHARACTERS = 4; \
			) \
			( \
				CRXM__IFELSE(pIS_BIG_ENDIAN) \
				( \
					*(pCHARS_POINTER++) = ((unsigned char) (((tUnsignedLong >> 10) | 0xD800UL) >> 8)); \
					*(pCHARS_POINTER++) = ((unsigned char) ((tUnsignedLong >> 10) | 0xD800UL)); \
					*(pCHARS_POINTER++) = ((unsigned char) (((tUnsignedLong & 0x03FFul) | 0xDC00UL) >> 8)); \
					*(pCHARS_POINTER++) = ((unsigned char) ((tUnsignedLong & 0x03FFul) | 0xDC00UL)); \
				) \
				( \
					*(pCHARS_POINTER++) = ((unsigned char) ((tUnsignedLong >> 10) | 0xD800UL)); \
					*(pCHARS_POINTER++) = ((unsigned char) (((tUnsignedLong >> 10) | 0xD800UL) >> 8)); \
					*(pCHARS_POINTER++) = ((unsigned char) ((tUnsignedLong & 0x03FFul) | 0xDC00UL)); \
					*(pCHARS_POINTER++) = ((unsigned char) (((tUnsignedLong & 0x03FFul) | 0xDC00UL) >> 8)); \
				) \
\
				pAVAILABLE_LENGTH = pAVAILABLE_LENGTH - 4; \
			) \
		} \
		else \
			{pIS_NO_ERROR = false;} \
	} \
	else \
		{pIS_NO_ERROR = false;} \
//#END_DEFINE
		
#define CRX__C__CHAR__FAST_INSERT_UTF16_CHAR(pIS_BIG_ENDIAN, pCODE_POINT, pCHARS_POINTER, \
		pNUMBER_OF_INSERTED_CHARACTERS) \
	if((pCODE_POINT <= 0xD7FFul) || ((pCODE_POINT <= 0xFFFFul) && (pCODE_POINT >= 0xE000ul))) \
	{ \
		CRXM__IFELSE(pIS_BIG_ENDIAN) \
		( \
			pCHARS_POINTER[0] = ((unsigned char) (pCODE_POINT >> 8)); \
			pCHARS_POINTER[1] = ((unsigned char) pCODE_POINT); \
		) \
		( \
			pCHARS_POINTER[0] = ((unsigned char) pCODE_POINT); \
			pCHARS_POINTER[1] = ((unsigned char) (pCODE_POINT >> 8)); \
		) \
\
		CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
		( \
			pNUMBER_OF_INSERTED_CHARACTERS = 2; \
		) \
		( \
			pCHARS_POINTER[2] = '\0'; \
		) \
	} \
	else if((pCODE_POINT >= 0x010000ul) && (pCODE_POINT <= 0x10FFFFul)) \
	{ \
		unsigned long tUnsignedLong = (pCODE_POINT - 0x10000ul); \
\
		((tUnsignedLong >> 10) | 0xD80000UL) \
\
		CRXM__IFELSE(pIS_BIG_ENDIAN) \
		( \
			pCHARS_POINTER[0] = ((unsigned char) (((tUnsignedLong >> 10) | 0xD800UL) >> 8)); \
			pCHARS_POINTER[1] = ((unsigned char) ((tUnsignedLong >> 10) | 0xD800UL)); \
			pCHARS_POINTER[2] = ((unsigned char) (((tUnsignedLong & 0x03FFul) | 0xDC00UL) >> 8)); \
			pCHARS_POINTER[3] = ((unsigned char) ((tUnsignedLong & 0x03FFul) | 0xDC00UL)); \
		) \
		( \
			pCHARS_POINTER[0] = ((unsigned char) ((tUnsignedLong >> 10) | 0xD800UL)); \
			pCHARS_POINTER[1] = ((unsigned char) (((tUnsignedLong >> 10) | 0xD800UL) >> 8)); \
			pCHARS_POINTER[2] = ((unsigned char) ((tUnsignedLong & 0x03FFul) | 0xDC00UL)); \
			pCHARS_POINTER[3] = ((unsigned char) (((tUnsignedLong & 0x03FFul) | 0xDC00UL) >> 8)); \
		) \
\
		CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
		( \
			pNUMBER_OF_INSERTED_CHARACTERS = 4; \
		) \
		( \
			pCHARS_POINTER[4] = '\0'; \
		) \
	} \
//#END_DEFINE

//SAME AS UTF16 BUT WITOUT SURROGATE PAIRS
#define CRX__C__CHAR__INSERT_UCS2_CHAR(pIS_BIG_ENDIAN, pCODE_POINT, pCHARS_POINTER, \
		pAVAILABLE_LENGTH, pIS_NO_ERROR, pIS_TO_INCREMENT_POINTER) \
	if((pCODE_POINT <= 0xD7FFul) || ((pCODE_POINT <= 0xFFFFul) && (pCODE_POINT >= 0xE000ul))) \
	{ \
		if(pAVAILABLE_LENGTH > 1) \
		{ \
			CRXM__IFELSE(CRXM__NOT(pIS_TO_INCREMENT_POINTER)) \
			( \
				CRXM__IFELSE(pIS_BIG_ENDIAN) \
				( \
					pCHARS_POINTER[0] = ((unsigned char) (pCODE_POINT >> 8)); \
					pCHARS_POINTER[1] = ((unsigned char) pCODE_POINT); \
				) \
				( \
					pCHARS_POINTER[0] = ((unsigned char) pCODE_POINT); \
					pCHARS_POINTER[1] = ((unsigned char) (pCODE_POINT >> 8)); \
				) \
			) \
			( \
				CRXM__IFELSE(pIS_BIG_ENDIAN) \
				( \
					*(pCHARS_POINTER++) = ((unsigned char) (pCODE_POINT >> 8)); \
					*(pCHARS_POINTER++) = ((unsigned char) pCODE_POINT); \
				) \
				( \
					*(pCHARS_POINTER++) = ((unsigned char) pCODE_POINT); \
					*(pCHARS_POINTER++) = ((unsigned char) (pCODE_POINT >> 8)); \
				) \
\
				pAVAILABLE_LENGTH = pAVAILABLE_LENGTH - 2; \
			) \
		} \
		else \
			{pIS_NO_ERROR = false;} \
	} \
	else \
		{pIS_NO_ERROR = false;} \
//#END_DEFINE

//SAME AS UTF16 BUT WITOUT SURROGATE PAIRS
#define CRX__C__CHAR__FAST_INSERT_UCS2_CHAR(pIS_BIG_ENDIAN, pCODE_POINT, pCHARS_POINTER, \
		pIS_TO_NULL_ARRAY) \
	if((pCODE_POINT <= 0xD7FFul) || ((pCODE_POINT <= 0xFFFFul) && (pCODE_POINT >= 0xE000ul))) \
	{ \
		CRXM__IFELSE(pIS_BIG_ENDIAN) \
		( \
			pCHARS_POINTER[0] = ((unsigned char) (pCODE_POINT >> 8)); \
			pCHARS_POINTER[1] = ((unsigned char) pCODE_POINT); \
		) \
		( \
			pCHARS_POINTER[0] = ((unsigned char) pCODE_POINT); \
			pCHARS_POINTER[1] = ((unsigned char) (pCODE_POINT >> 8)); \
		) \
		CRXM__IFELSE2(pIS_TO_NULL_ARRAY, \
		pCHARS_POINTER[2] = '\0';, ) \
	} \
//#END_DEFINE
		
#define CRX__C__CHAR__INSERT_UTF32_CHAR(pIS_BIG_ENDIAN, pCODE_POINT, pCHARS_POINTER, \
		pAVAILABLE_LENGTH, pIS_NO_ERROR, pIS_TO_INCREMENT_POINTER) \
	if((pAVAILABLE_LENGTH > 3) && \
			(pCODE_POINT <= 0x10FFFFul) && !((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDFFFul))) \
	{ \
		CRXM__IFELSE(CRXM__NOT(pIS_TO_INCREMENT_POINTER)) \
		( \
			CRXM__IFELSE(pIS_BIG_ENDIAN) \
			( \
				pCHARS_POINTER[0] = ((unsigned char) (pCODE_POINT >> 24)); \
				pCHARS_POINTER[1] = ((unsigned char) (pCODE_POINT >> 16)); \
				pCHARS_POINTER[2] = ((unsigned char) (pCODE_POINT >> 8)); \
				pCHARS_POINTER[3] = ((unsigned char) pCODE_POINT); \
			) \
			( \
				pCHARS_POINTER[0] = ((unsigned char) pCODE_POINT); \
				pCHARS_POINTER[1] = ((unsigned char) (pCODE_POINT >> 8)); \
				pCHARS_POINTER[2] = ((unsigned char) (pCODE_POINT >> 16)); \
				pCHARS_POINTER[3] = ((unsigned char) (pCODE_POINT >> 24)); \
			) \
		) \
		( \
			CRXM__IFELSE(pIS_BIG_ENDIAN) \
			( \
				*(pCHARS_POINTER++) = ((unsigned char) (pCODE_POINT >> 24)); \
				*(pCHARS_POINTER++) = ((unsigned char) (pCODE_POINT >> 16)); \
				*(pCHARS_POINTER++) = ((unsigned char) (pCODE_POINT >> 8)); \
				*(pCHARS_POINTER++) = ((unsigned char) pCODE_POINT); \
			) \
			( \
				*(pCHARS_POINTER++) = ((unsigned char) pCODE_POINT); \
				*(pCHARS_POINTER++) = ((unsigned char) (pCODE_POINT >> 8)); \
				*(pCHARS_POINTER++) = ((unsigned char) (pCODE_POINT >> 16)); \
				*(pCHARS_POINTER++) = ((unsigned char) (pCODE_POINT >> 24)); \
			) \
	\
			pAVAILABLE_LENGTH = pAVAILABLE_LENGTH - 4; \
		) \
	} \
	else \
		{pIS_NO_ERROR = false;}
//#END_DEFINE
			
#define CRX__C__CHAR__FAST_INSERT_UTF32_CHAR(pIS_BIG_ENDIAN, pCODE_POINT, pCHARS_POINTER, \
		pIS_TO_NULL_ARRAY) \
	CRXM__IFELSE(pIS_BIG_ENDIAN) \
	( \
		pCHARS_POINTER[0] = ((unsigned char) (pCODE_POINT >> 24)); \
		pCHARS_POINTER[1] = ((unsigned char) (pCODE_POINT >> 16)); \
		pCHARS_POINTER[2] = ((unsigned char) (pCODE_POINT >> 8)); \
		pCHARS_POINTER[3] = ((unsigned char) pCODE_POINT); \
	) \
	( \
		pCHARS_POINTER[0] = ((unsigned char) pCODE_POINT); \
		pCHARS_POINTER[1] = ((unsigned char) (pCODE_POINT >> 8)); \
		pCHARS_POINTER[2] = ((unsigned char) (pCODE_POINT >> 16)); \
		pCHARS_POINTER[3] = ((unsigned char) (pCODE_POINT >> 24)); \
	) \
\
	CRXM__IFELSE2(pIS_TO_NULL_ARRAY, \
	pCHARS_POINTER[4] = '\0';, ) \
//#END_DEFINE


CRX__LIB__C_CODE_END()
		
#endif