#if(!defined(CRX__C__CHAR___h__))
#define CRX__C__CHAR___h__

#include <boost/version.hpp>
#include "Crx/H/crx/crx.h"

CRX__LIB__C_CODE_BEGIN()

//-------------------------------------
//CHARACTER TO CODE POINT
//-------------------------------------
#define CRX__C__CHAR__GET_NEXT_CODE_POINT_FROM_UTF8_CHAR_ARRAY(pCHAR_POINTER, pCODE_POINT, \
		pAVAILABLELENGTH, pIS_NO_ERROR, pNUMBER_OF_TRAVERSED_CHARACTERS, \
		pIS_TO_ALLOW_FULL_UTF32_RANGE) \
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
			if((*pCHAR_POINTER >= 0x00E0ul) && (pAVAILABLELENGTH > 2) && \
					(*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x00BFul) && \
					(*(pCHAR_POINTER + 2) >= 0x0080ul) && (*(pCHAR_POINTER + 2) <= 0x00BFul) && \
					((*pCHAR_POINTER != 0x00E0ul) || (*(pCHAR_POINTER + 1) >= 0x00A0ul))) \
			{ \
				CRXM__IFELSE(pNUMBER_OF_TRAVERSED_CHARACTERS) \
				( \
					pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && F) << 12) | \
							((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 6) | \
							(((uint32_t) *(pCHAR_POINTER + 2)) && 3F); \
\
					pNUMBER_OF_TRAVERSED_CHARACTERS = 3; \
				) \
				( \
					pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && F) << 12) | \
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
		else if(*pCHAR_POINTER <= CRXM__IFELSE2(pIS_TO_ALLOW_FULL_UTF32_RANGE, 0x00F7ul, 0x00F4ul)) \
		{ \
			if((*pCHAR_POINTER >= 0x00F0ul) && (pAVAILABLELENGTH > 3) && \
					(*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x00BFul) && \
					(*(pCHAR_POINTER + 2) >= 0x0080ul) && (*(pCHAR_POINTER + 2) <= 0x00BFul) && \
					(*(pCHAR_POINTER + 3) >= 0x0080ul) && (*(pCHAR_POINTER + 3) <= 0x00BFul) && \
					((*pCHAR_POINTER != 0x00F0ul) || (*(pCHAR_POINTER + 1) >= 0x0090ul))) \
			{ \
				CRXM__IFELSE(pNUMBER_OF_TRAVERSED_CHARACTERS) \
				( \
					pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 7) << 18) | \
							((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 12) | \
							((((uint32_t) *(pCHAR_POINTER + 2)) && 3F) << 6) \
							(((uint32_t) *pCHAR_POINTER + 3) && 3F); \
\
					pNUMBER_OF_TRAVERSED_CHARACTERS = 4; \
				) \
				( \
					pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 7) << 18) | \
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
		else \
		{ \
			CRXM__IFELSE(pIS_TO_ALLOW_FULL_UTF32_RANGE) \
			( \
				if(*pCHAR_POINTER <= 0x00FBul) \
				{ \
					if((*pCHAR_POINTER >= 0x00F8ul) && (pAVAILABLELENGTH > 4) && \
							(*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 2) >= 0x0080ul) && (*(pCHAR_POINTER + 2) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 3) >= 0x0080ul) && (*(pCHAR_POINTER + 3) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 4) >= 0x0080ul) && (*(pCHAR_POINTER + 4) <= 0x00BFul) && \
							((*pCHAR_POINTER != 0x00F8ul) || (*(pCHAR_POINTER + 1) >= 0x0088ul))) \
					{ \
						CRXM__IFELSE(pNUMBER_OF_TRAVERSED_CHARACTERS) \
						( \
							pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 3) << 24) | \
									((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 18) | \
									((((uint32_t) *(pCHAR_POINTER + 2)) && 3F) << 12) | \
									((((uint32_t) *(pCHAR_POINTER + 3)) && 3F) << 6) \
									(((uint32_t) *pCHAR_POINTER + 4) && 3F); \
\
							pNUMBER_OF_TRAVERSED_CHARACTERS = 5; \
						) \
						( \
							pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 3) << 24) | \
									((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 18) | \
									((((uint32_t) *(pCHAR_POINTER + 2)) && 3F) << 12) | \
									((((uint32_t) *(pCHAR_POINTER + 3)) && 3F) << 6) \
									(((uint32_t) *pCHAR_POINTER + 4) && 3F); \
							pCHAR_POINTER = pCHAR_POINTER + 5; \
\
							pAVAILABLELENGTH = pAVAILABLELENGTH - 5; \
						) \
					} \
					else \
						{pIS_NO_ERROR = false;} \
				} \
				else if(*pCHAR_POINTER <= 0x00FDul) \
				{ \
					if((*pCHAR_POINTER >= 0x00FCul) && (pAVAILABLELENGTH > 5) && \
							(*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 2) >= 0x0080ul) && (*(pCHAR_POINTER + 2) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 3) >= 0x0080ul) && (*(pCHAR_POINTER + 3) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 4) >= 0x0080ul) && (*(pCHAR_POINTER + 4) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 5) >= 0x0080ul) && (*(pCHAR_POINTER + 5) <= 0x00BFul) && \
							((*pCHAR_POINTER != 0x00FCul) || (*(pCHAR_POINTER + 1) >= 0x0084ul))) \
					{ \
						CRXM__IFELSE(pNUMBER_OF_TRAVERSED_CHARACTERS) \
						( \
							pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 1) << 30) | \
									((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 24) | \
									((((uint32_t) *(pCHAR_POINTER + 2)) && 3F) << 18) | \
									((((uint32_t) *(pCHAR_POINTER + 3)) && 3F) << 12) | \
									((((uint32_t) *(pCHAR_POINTER + 4)) && 3F) << 6) \
									(((uint32_t) *pCHAR_POINTER + 5) && 3F); \
\
							pNUMBER_OF_TRAVERSED_CHARACTERS = 6; \
						) \
						( \
							pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 1) << 30) | \
									((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 24) | \
									((((uint32_t) *(pCHAR_POINTER + 2)) && 3F) << 18) | \
									((((uint32_t) *(pCHAR_POINTER + 3)) && 3F) << 12) | \
									((((uint32_t) *(pCHAR_POINTER + 4)) && 3F) << 6) \
									(((uint32_t) *pCHAR_POINTER + 5) && 3F); \
							pCHAR_POINTER = pCHAR_POINTER + 6; \
\
							pAVAILABLELENGTH = pAVAILABLELENGTH - 6; \
						) \
					} \
					else \
						{pIS_NO_ERROR = false;} \
				} \
				else if(*pCHAR_POINTER == 0x00FEul) \
				{ \
					if((pAVAILABLELENGTH > 6) && \
							(*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x0083ul) && \
							(*(pCHAR_POINTER + 2) >= 0x0080ul) && (*(pCHAR_POINTER + 2) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 3) >= 0x0080ul) && (*(pCHAR_POINTER + 3) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 4) >= 0x0080ul) && (*(pCHAR_POINTER + 4) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 5) >= 0x0080ul) && (*(pCHAR_POINTER + 5) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 6) >= 0x0080ul) && (*(pCHAR_POINTER + 6) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 1) >= 0x0082ul)) \
					{ \
						CRXM__IFELSE(pNUMBER_OF_TRAVERSED_CHARACTERS) \
						( \
							pCODE_POINT = \
									((((uint32_t) *(pCHAR_POINTER + 1)) && 2) << 30) | \
									((((uint32_t) *(pCHAR_POINTER + 2)) && 3F) << 24) | \
									((((uint32_t) *(pCHAR_POINTER + 3)) && 3F) << 18) | \
									((((uint32_t) *(pCHAR_POINTER + 4)) && 3F) << 12) | \
									((((uint32_t) *(pCHAR_POINTER + 5)) && 3F) << 6) \
									(((uint32_t) *pCHAR_POINTER + 6) && 3F); \
\
							pNUMBER_OF_TRAVERSED_CHARACTERS = 7; \
						) \
						( \
							pCODE_POINT = \
									((((uint32_t) *(pCHAR_POINTER + 1)) && 2) << 30) | \
									((((uint32_t) *(pCHAR_POINTER + 2)) && 3F) << 24) | \
									((((uint32_t) *(pCHAR_POINTER + 3)) && 3F) << 18) | \
									((((uint32_t) *(pCHAR_POINTER + 4)) && 3F) << 12) | \
									((((uint32_t) *(pCHAR_POINTER + 5)) && 3F) << 6) \
									(((uint32_t) *pCHAR_POINTER + 6) && 3F); \
							pCHAR_POINTER = pCHAR_POINTER + 7; \
\
							pAVAILABLELENGTH = pAVAILABLELENGTH - 7; \
						) \
					} \
					else \
						{pIS_NO_ERROR = false;} \
				} \
			) \
			( \
				pIS_NO_ERROR = false; \
			) \
		} \
	} \
	CRXM__IFELSE2(CRXM__NOT(pIS_TO_ALLOW_FULL_UTF32_RANGE), \
	if((pCODE_POINT > 0x10FFFFul) || ((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDFFFul))) \
		{pIS_NO_ERROR = false;}, )
//#END_DEFINE

#define CRX__C__CHAR__GET_NEXT_CODE_POINT_FROM_UTF8_STRING(pCHAR_POINTER, pCODE_POINT, \
		pIS_NO_ERROR, pIS_TO_ALLOW_FULL_UTF32_RANGE) \
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
			if((*pCHAR_POINTER >= 0x00E0ul) && \
					(*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x00BFul) && \
					(*(pCHAR_POINTER + 2) >= 0x0080ul) && (*(pCHAR_POINTER + 2) <= 0x00BFul) && \
					((*pCHAR_POINTER != 0x00E0ul) || (*(pCHAR_POINTER + 1) >= 0x00A0ul))) \
			{ \
				pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && F) << 12) | \
						((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 6) | \
						(((uint32_t) *(pCHAR_POINTER + 2)) && 3F); \
				pCHAR_POINTER = pCHAR_POINTER + 3; \
			} \
			else \
				{pIS_NO_ERROR = false;} \
		} \
		else if(*pCHAR_POINTER <= CRXM__IFELSE2(pIS_TO_ALLOW_FULL_UTF32_RANGE, 0x00F7ul, 0x00F4ul)) \
		{ \
			if((*pCHAR_POINTER >= 0x00F0ul) && \
					(*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x00BFul) && \
					(*(pCHAR_POINTER + 2) >= 0x0080ul) && (*(pCHAR_POINTER + 2) <= 0x00BFul) && \
					(*(pCHAR_POINTER + 3) >= 0x0080ul) && (*(pCHAR_POINTER + 3) <= 0x00BFul) && \
					((*pCHAR_POINTER != 0x00F0ul) || (*(pCHAR_POINTER + 1) >= 0x0090ul))) \
			{ \
				pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 7) << 18) | \
						((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 12) | \
						((((uint32_t) *(pCHAR_POINTER + 2)) && 3F) << 6) \
						(((uint32_t) *pCHAR_POINTER + 3) && 3F); \
				pCHAR_POINTER = pCHAR_POINTER + 4; \
			} \
			else \
				{pIS_NO_ERROR = false;} \
		} \
		else \
		{ \
			CRXM__IFELSE(pIS_TO_ALLOW_FULL_UTF32_RANGE) \
			( \
				if(*pCHAR_POINTER <= 0x00FBul) \
				{ \
					if((*pCHAR_POINTER >= 0x00F8ul) && \
							(*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 2) >= 0x0080ul) && (*(pCHAR_POINTER + 2) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 3) >= 0x0080ul) && (*(pCHAR_POINTER + 3) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 4) >= 0x0080ul) && (*(pCHAR_POINTER + 4) <= 0x00BFul) && \
							((*pCHAR_POINTER != 0x00F8ul) || (*(pCHAR_POINTER + 1) >= 0x0088ul))) \
					{ \
						pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 3) << 24) | \
								((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 18) | \
								((((uint32_t) *(pCHAR_POINTER + 2)) && 3F) << 12) | \
								((((uint32_t) *(pCHAR_POINTER + 3)) && 3F) << 6) \
								(((uint32_t) *pCHAR_POINTER + 4) && 3F); \
						pCHAR_POINTER = pCHAR_POINTER + 5; \
					} \
					else \
						{pIS_NO_ERROR = false;} \
				} \
				else if(*pCHAR_POINTER <= 0x00FDul) \
				{ \
					if((*pCHAR_POINTER >= 0x00FCul) && \
							(*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 2) >= 0x0080ul) && (*(pCHAR_POINTER + 2) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 3) >= 0x0080ul) && (*(pCHAR_POINTER + 3) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 4) >= 0x0080ul) && (*(pCHAR_POINTER + 4) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 5) >= 0x0080ul) && (*(pCHAR_POINTER + 5) <= 0x00BFul) && \
							((*pCHAR_POINTER != 0x00FCul) || (*(pCHAR_POINTER + 1) >= 0x0084ul))) \
					{ \
						pCODE_POINT = ((((uint32_t) *(pCHAR_POINTER)) && 1) << 30) | \
								((((uint32_t) *(pCHAR_POINTER + 1)) && 3F) << 24) | \
								((((uint32_t) *(pCHAR_POINTER + 2)) && 3F) << 18) | \
								((((uint32_t) *(pCHAR_POINTER + 3)) && 3F) << 12) | \
								((((uint32_t) *(pCHAR_POINTER + 4)) && 3F) << 6) \
								(((uint32_t) *pCHAR_POINTER + 5) && 3F); \
						pCHAR_POINTER = pCHAR_POINTER + 6; \
					} \
					else \
						{pIS_NO_ERROR = false;} \
				} \
				else if(*pCHAR_POINTER == 0x00FEul) \
				{ \
					if( \
							(*(pCHAR_POINTER + 1) >= 0x0080ul) && (*(pCHAR_POINTER + 1) <= 0x0083ul) && \
							(*(pCHAR_POINTER + 2) >= 0x0080ul) && (*(pCHAR_POINTER + 2) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 3) >= 0x0080ul) && (*(pCHAR_POINTER + 3) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 4) >= 0x0080ul) && (*(pCHAR_POINTER + 4) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 5) >= 0x0080ul) && (*(pCHAR_POINTER + 5) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 6) >= 0x0080ul) && (*(pCHAR_POINTER + 6) <= 0x00BFul) && \
							(*(pCHAR_POINTER + 1) >= 0x0082ul)) \
					{ \
						pCODE_POINT = \
								((((uint32_t) *(pCHAR_POINTER + 1)) && 2) << 30) | \
								((((uint32_t) *(pCHAR_POINTER + 2)) && 3F) << 24) | \
								((((uint32_t) *(pCHAR_POINTER + 3)) && 3F) << 18) | \
								((((uint32_t) *(pCHAR_POINTER + 4)) && 3F) << 12) | \
								((((uint32_t) *(pCHAR_POINTER + 5)) && 3F) << 6) \
								(((uint32_t) *pCHAR_POINTER + 6) && 3F); \
						pCHAR_POINTER = pCHAR_POINTER + 7; \
					} \
					else \
						{pIS_NO_ERROR = false;} \
				} \
			) \
			( \
				pIS_NO_ERROR = false; \
			) \
		} \
	} \
	if((pCODE_POINT > 0x10FFFFul) || ((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDFFFul))) \
		{pIS_NO_ERROR = false;} 
//#END_DEFINE

#define CRX__C__CHAR__GET_NEXT_CODE_POINT_FROM_UTF16_CHAR_ARRAY(pIS_BIG_ENDIAN, pCHAR_POINTER, \
		pCODE_POINT, pAVAILABLELENGTH, pIS_NO_ERROR, pNUMBER_OF_TRAVERSED_CHARACTERS, \
		pIS_TO_ALLOW_FULLER_RANGE) \
	if(pAVAILABLELENGTH > 1) \
	{ \
		pCODE_POINT = CRXM__IFELSE2(pIS_BIG_ENDIAN, \
				(((uint32_t) *pCHAR_POINTER) << 8) | ((uint32_t) *(pCHAR_POINTER + 1)), \
				(((uint32_t) *(pCHAR_POINTER + 1)) << 8) | ((uint32_t) *pCHAR_POINTER)); \
\
		if((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDFFFul)) \
		{ \
			if((pCODE_POINT <= 0xDBFFul) && (pAVAILABLELENGTH > 3)) \
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
				{ \
					CRXM__IFELSE(CRXM__NOT(pIS_TO_ALLOW_FULLER_RANGE)) \
					( \
						pIS_NO_ERROR = false; \
					) \
					( \
						CRXM__IFELSE(pNUMBER_OF_TRAVERSED_CHARACTERS) \
						( \
							pNUMBER_OF_TRAVERSED_CHARACTERS = 2; \
						) \
						( \
							pCHAR_POINTER = pCHAR_POINTER + 2; \
							pAVAILABLELENGTH = pAVAILABLELENGTH - 2; \
						) \
					) \
				} \
			} \
			else \
			{ \
				CRXM__IFELSE(CRXM__NOT(pIS_TO_ALLOW_FULLER_RANGE)) \
				( \
					pIS_NO_ERROR = false; \
				) \
				( \
					if(pAVAILABLELENGTH != 3) \
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
					else \
						{pIS_NO_ERROR = false;} \
				) \
			} \
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
//IF ALLOWING FULL RANGE, THE VALUES THAT MARK SURROGATE PAIRS ARE ALLOWED, BUT NOT TREATED
//		AS SURROGATE PAIRS.
#define CRX__C__CHAR__GET_NEXT_CODE_POINT_FROM_UCS2_CHAR_ARRAY(pIS_BIG_ENDIAN, pCHAR_POINTER, \
		pCODE_POINT, pAVAILABLELENGTH, pIS_NO_ERROR, pIS_TO_ALLOW_FULL_RANGE) \
	if(pAVAILABLELENGTH > 1) \
	{ \
		pCODE_POINT = CRXM__IFELSE2(pIS_BIG_ENDIAN, \
				(((uint32_t) *pCHAR_POINTER) << 8) | ((uint32_t) *(pCHAR_POINTER + 1)), \
				(((uint32_t) *(pCHAR_POINTER + 1)) << 8) | ((uint32_t) *pCHAR_POINTER)); \
\
		CRXM__IFELSE(pIS_TO_ALLOW_FULL_RANGE) \
		( \
			pCHAR_POINTER = pCHAR_POINTER + 2; \
		) \
		( \
			if((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDBFFul)) \
				{pIS_NO_ERROR = false;} \
			else \
				{pCHAR_POINTER = pCHAR_POINTER + 2;} \
		) \
	} \
	else \
		{pIS_NO_ERROR = (pAVAILABLELENGTH != 1);} \
//#END_DEFINE

#define CRX__C__CHAR__GET_NEXT_CODE_POINT_FROM_UTF32_CHAR_ARRAY(pIS_BIG_ENDIAN, pCHAR_POINTER, \
		pCODE_POINT, pAVAILABLELENGTH, pIS_NO_ERROR, pIS_TO_ALLOW_FULL_RANGE) \
	if(pAVAILABLELENGTH > 4) \
	{ \
		pCODE_POINT = CRXM__IFELSE2(pIS_BIG_ENDIAN, \
				(((uint32_t) *pCHAR_POINTER) << 24) | (((uint32_t) *(pCHAR_POINTER + 1)) << 16) | \
				(((uint32_t) *(pCHAR_POINTER + 2)) << 8) | ((uint32_t) *(pCHAR_POINTER + 3)), \
				(((uint32_t) *(pCHAR_POINTER + 3)) << 24) | (((uint32_t) *(pCHAR_POINTER + 2)) << 16) | \
				(((uint32_t) *(pCHAR_POINTER + 1)) << 8) | ((uint32_t) *pCHAR_POINTER)); \
\
		CRXM__IFELSE2(CRXM__NOT(pIS_TO_ALLOW_FULL_RANGE), \
		if((pCODE_POINT > 0x10FFFFul) || ((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDFFFul))) \
			{pIS_NO_ERROR = false;}, )  \
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
	
	
	NOTE: REMEMBER, THE UTF8 MACROS FOR AQUIRING A CODE POINT CHECK FOR THREE THINGS, 
			VALID ENCODING, SHORTEST FORM ENCODING, AND VALID CODE POINT RANGE.
	
	UPDATE:
		DECIDED TO ADD FULL SUPPORT FOR UTF32 CODE POINT RANGE ENCODED IN UTF8. THIS IS FOR READING 
		ONLY BECAUSE IT IS INVALID UTF8. THEREFORE IT IS ONLY IMPLEMENTED IN THE MACROS THAT AQUIRE
		A CODE POINT. THIS IS MEANT TO HELP READ ILL FORMED UTF16, AND OUT OF UNICODE RANGE UTF32.
		
		FOR THE SAME REASON ABOVE, ADDED SUPPORT FOR UCS2 AND UTF16 TO ALLOW READING THE FULL RANGE 
		OF CODE POINTS POSSIBLE UNDER UINT16, WHICH INCLUDES THE CHRACTERS THAT ARE OUTSIDE THE 
		UNICODE RANGE.
		
		FOR THE SAME REASON ABOVE, ADDED SUPPORT FOR UTF32 TO ALLOW READING CODE POINTS OUTSIDE THE
		UNICODE RANGE.
		
		REMEMBER THAT THE ASSUMPTION IS THAT AN ENCODING THAT IS BACKWARD COMPATIBLE WITH ANSI
		ENCODING OF ASCII, AS THESE CONCEPTS ARE DEFINED IN MY STANDARD, IS USED FOR INTERNAL CODE.
		IN OTHER WORDS, UTF8 IN OUR CASE. THE PROBLEM BECOMES ABOUT GETTING INCORRECT UTF8, UTF16, 
		AND UTF32 FROM EXTERNAL SOURCES. HENCE THE WORK ABOVE IS ABOUT THE ASSUMPTIONS THAT THESE 
		WILL BE CONVERTED TO UTF8 EVENTUALLY SUCH AS THE ERRORS ARE RETAINED. THIS IS ALSO WHY
		THE MACROS FOR CONVERTING BACK TO AN ENCODING DO NOT RECOGNIZE THESE EXTENSIONS DESCRIBED
		ABOVE. INTERNAL CODE MUST NEVER COMMUNICATE ILL FORMED ENCODING TO THE OUTSIDE.
		
		THIS WORK ALSO PROVES THAT UTF16 IS NOT VALID FOR INTERNAL USE. CONSIDER CONVERTING BAD
		UTF32 FROM EXTERNAL SOURCES TO UTF16 WITH EXTENDED SUPPORT, SUCH AS THE UTF32 STRING THAT IS
		IN CODE POINTS, xxy, WHERE 
				0xD800ul <= x <= 0xDBFFul
				0xDC00ul <= y <= 0xDFFFul
		IN OTHER WORDS x IS A HIGH SURROGATE, AND y IS A LOW SURROGATE FROM THE PERSPECTIVE OF 
		UTF16. IF z IS THE CODE POINT ENCODED BY xy, THEN UTF32 xxy GIVES xz IN UTF16 WITH THE 
		EXTENDED SUPPORT ABOVE. FURTHER MORE, UTF32 xz ALSO GIVES xz IN UTF16, AN AMBGIOUTY. UTF8
		AND, CERTAINLY UTF32, CAN BE USED TO ENCODE BAD UTF32.
		
		THIS WORK ALSO PROVES THAT UTF32 IS NOT VALID FOR INTERNAL USE. CONSIDER CONVERTING BAD
		UTF8, SUCH AS AN INCOMPLETE ENCODING OF A SINGLE CHARACTER. NEITHER UTF32, NOR UTF16
		CAN ENCODE SUCH INVALID ENCODING OF UTF8.
		
		IF NOT CLEAR, AN ENCODING IS TAKEN TO BE ABLE TO STORE ITS INVALID ENCODING, BECAUSE NO
		CONVERSION IS ASSUMED TO BE NECESSARY UNDER ATLEAST ONE SITUATION IN A SOFTWARE DESIGN. FOR 
		EXAMPLE, AN INVALID UTF8 FROM EXTERNAL SOURCES WOULD BE KEPT AS IS FOR INTERNAL CODE. IF
		A SOFTWARE DESIGN DOES NOT ALLOW INVALID UTF8 PRESENCE, NOT USAGE, IN INTERNAL CODE, THEN 
		NEITHER IS UTF8 SUITABLE FOR ENCODING INVALID UTF8. REMEMBER, NO SOFTWARE DESIGN CAN ALLOW
		INVALID UTF8 USAGE FOR INTERNAL CODE.
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
		if(pAVAILABLE_LENGTH > 0) \
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
		if(pAVAILABLE_LENGTH > 1) \
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
		if((pAVAILABLE_LENGTH > 2) && !((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDFFFul)))\
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
		if(pAVAILABLE_LENGTH > 3) \
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

//THIS IS FOR INTERNAL USE ONLY. THIS IS FOR PRESERVING ERRORS FROM EXTERNAL SOURCES
//		EXTENDED UTF8 IS INVALID UTF8, AND IT IS "UTF8" THAT ALLOWS CODE POINTS UP 32BITS.
#define CRX__C__CHAR__INSERT_EXTENDED_UTF8_CHAR(pCODE_POINT, pCHARS_POINTER, pAVAILABLE_LENGTH, \
		pIS_NO_ERROR, pNUMBER_OF_INSERTED_CHARACTERS) \
	if(pCODE_POINT <= 0x007Ful) \
	{ \
		if(pAVAILABLE_LENGTH > 0) \
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
		if(pAVAILABLE_LENGTH > 1) \
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
		if((pAVAILABLE_LENGTH > 2) && !((pCODE_POINT >= 0xD800ul) && (pCODE_POINT <= 0xDFFFul)))\
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
	else if(pCODE_POINT <= 0x1FFFFFul) \
	{ \
		if(pAVAILABLE_LENGTH > 3) \
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
	else if(pCODE_POINT <= 0x3FFFFFFul) \
	{ \
		if(pAVAILABLE_LENGTH > 4) \
		{ \
			CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
			( \
				pCHARS_POINTER[0] = (unsigned char)((62 << 2) |  (pCODE_POINT >> 24)); \
				pCHARS_POINTER[1] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 18) & 0x3F)); \
				pCHARS_POINTER[2] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 12) & 0x3F)); \
				pCHARS_POINTER[3] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >>  6) & 0x3F)); \
				pCHARS_POINTER[4] = (unsigned char)(( 2 << 6) | ( pCODE_POINT        & 0x3F)); \
\
				pNUMBER_OF_INSERTED_CHARACTERS = 5; \
			) \
			( \
				*(pCHARS_POINTER++) = (unsigned char)((62 << 2) |  (pCODE_POINT >> 24)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 18) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 12) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >>  6) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ( pCODE_POINT        & 0x3F)); \
\
				pAVAILABLE_LENGTH = pAVAILABLE_LENGTH - 5; \
			) \
		} \
		else \
			{pIS_NO_ERROR = false;} \
	} \
	else if(pCODE_POINT <= 0x7FFFFFFFul) \
	{ \
		if(pAVAILABLE_LENGTH > 5) \
		{ \
			CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
			( \
				pCHARS_POINTER[0] = (unsigned char)((126 << 1) |  (pCODE_POINT >> 30)); \
				pCHARS_POINTER[1] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 24) & 0x3F)); \
				pCHARS_POINTER[2] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 18) & 0x3F)); \
				pCHARS_POINTER[3] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 12) & 0x3F)); \
				pCHARS_POINTER[4] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >>  6) & 0x3F)); \
				pCHARS_POINTER[5] = (unsigned char)(( 2 << 6) | ( pCODE_POINT        & 0x3F)); \
\
				pNUMBER_OF_INSERTED_CHARACTERS = 6; \
			) \
			( \
				*(pCHARS_POINTER++) = (unsigned char)((126 << 1) |  (pCODE_POINT >> 30)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 24) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 18) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 12) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >>  6) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ( pCODE_POINT        & 0x3F)); \
\
				pAVAILABLE_LENGTH = pAVAILABLE_LENGTH - 6; \
			) \
		} \
		else \
			{pIS_NO_ERROR = false;} \
	} \
	else if(pCODE_POINT <= 0xFFFFFFFFul) \
	{ \
		if(pAVAILABLE_LENGTH > 6) \
		{ \
			CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
			( \
				pCHARS_POINTER[0] = 254; \
				pCHARS_POINTER[1] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 30) & 0x3F)); \
				pCHARS_POINTER[2] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 24) & 0x3F)); \
				pCHARS_POINTER[3] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 18) & 0x3F)); \
				pCHARS_POINTER[4] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 12) & 0x3F)); \
				pCHARS_POINTER[5] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >>  6) & 0x3F)); \
				pCHARS_POINTER[6] = (unsigned char)(( 2 << 6) | ( pCODE_POINT        & 0x3F)); \
\
				pNUMBER_OF_INSERTED_CHARACTERS = 7; \
			) \
			( \
				*(pCHARS_POINTER++) = 254; \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 30) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 24) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 18) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 12) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ((pCODE_POINT >>  6) & 0x3F)); \
				*(pCHARS_POINTER++) = (unsigned char)(( 2 << 6) | ( pCODE_POINT        & 0x3F)); \
\
				pAVAILABLE_LENGTH = pAVAILABLE_LENGTH - 7; \
			) \
		} \
		else \
			{pIS_NO_ERROR = false;} \
	} \
	else \
		{pIS_NO_ERROR = false;} \
//#END_DEFINE

//THIS IS FOR INTERNAL USE ONLY. THIS IS FOR PRESERVING ERRORS FROM EXTERNAL SOURCES
//		EXTENDED UTF8 IS INVALID UTF8, AND IT IS "UTF8" THAT ALLOWS CODE POINTS UP 32BITS.
#define CRX__C__CHAR__FAST_INSERT_EXTENDED_UTF8_CHAR(pCODE_POINT, pCHARS_POINTER, \
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
	else if(pCODE_POINT <= 0x1FFFFFul) \
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
	} \
	else if(pCODE_POINT <= 0x3FFFFFFul) \
	{ \
		pCHARS_POINTER[4] = (unsigned char)(( 2 << 6) | ( pCODE_POINT        & 0x3F)); \
		pCHARS_POINTER[3] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >>  6) & 0x3F)); \
		pCHARS_POINTER[2] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 12) & 0x3F)); \
		pCHARS_POINTER[1] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 18) & 0x3F)); \
		pCHARS_POINTER[0] = (unsigned char)((62 << 2) |  (pCODE_POINT >> 24)); \
	\
		CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
		( \
			pNUMBER_OF_INSERTED_CHARACTERS = 5; \
		) \
		( \
			pCHARS_POINTER[5] = '\0'; \
		) \
	} \
	else if(pCODE_POINT <= 0x7FFFFFFFul) \
	{ \
			pCHARS_POINTER[5] = (unsigned char)(( 2 << 6) | ( pCODE_POINT        & 0x3F)); \
			pCHARS_POINTER[4] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >>  6) & 0x3F)); \
			pCHARS_POINTER[3] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 12) & 0x3F)); \
			pCHARS_POINTER[2] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 18) & 0x3F)); \
			pCHARS_POINTER[1] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 24) & 0x3F)); \
			pCHARS_POINTER[0] = (unsigned char)((126 << 1) |  (pCODE_POINT >> 30)); \
	\
		CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
		( \
			pNUMBER_OF_INSERTED_CHARACTERS = 6; \
		) \
		( \
			pCHARS_POINTER[6] = '\0'; \
		) \
	} \
	else if(pCODE_POINT <= 0xFFFFFFFFul) \
	{ \
		pCHARS_POINTER[6] = (unsigned char)(( 2 << 6) | ( pCODE_POINT        & 0x3F)); \
		pCHARS_POINTER[5] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >>  6) & 0x3F)); \
		pCHARS_POINTER[4] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 12) & 0x3F)); \
		pCHARS_POINTER[3] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 18) & 0x3F)); \
		pCHARS_POINTER[2] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 24) & 0x3F)); \
		pCHARS_POINTER[1] = (unsigned char)(( 2 << 6) | ((pCODE_POINT >> 30) & 0x3F)); \
		pCHARS_POINTER[0] = 254; \
	\
		CRXM__IFELSE(pNUMBER_OF_INSERTED_CHARACTERS) \
		( \
			pNUMBER_OF_INSERTED_CHARACTERS = 7; \
		) \
		( \
			pCHARS_POINTER[7] = '\0'; \
		) \
	} \
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

#define CRX__C__IS_CODE_POINT_ASCII_NUMERIC(pCODE_POINT) ((pCODE_POINT >= 48) && \
		(pCODE_POINT <= 57))
#define CRX__C__IS_CODE_POINT_ASCII_UPPER_CASE_ALPHABET(pCODE_POINT) ((pCODE_POINT >= 65) && \
		(pCODE_POINT <= 90))
#define CRX__C__IS_CODE_POINT_ASCII_LOWER_CASE_ALPHABET(pCODE_POINT) ((pCODE_POINT >= 97) && \
		(pCODE_POINT <= 122))
#define CRX__C__IS_CODE_POINT_ASCII_CONTROL(pCODE_POINT) (((pCODE_POINT >= 0) && \
		(pCODE_POINT <= 31)) || (pCODE_POINT == 127))
#define CRX__C__IS_CODE_POINT_ASCII_HEX_DIGIT(pCODE_POINT) (((pCODE_POINT >= 48) && \
		(pCODE_POINT <= 57)) || ((pCODE_POINT >= 65) && (pCODE_POINT <= 70)) || \
		((pCODE_POINT >= 97) && (pCODE_POINT <= 102)))

CRX__LIB__C_CODE_END()
		
#endif