#if(!defined(CRX__C__CRX_CSS___h__))
#define CRX__C__CRX_CSS___h__

#include <boost/version.hpp>
#include "Crx/H/crx/crx.h"
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma push_macro("CRX__LIB__MODE")
	#undef CRX__LIB__MODE
	#if(!defined(CRX__CONFIG__MODE))
		#define CRX__CONFIG__MODE CRX__LIB__MODE__STAND_ALONE
	#endif
	#define CRX__LIB__MODE CRX__CONFIG__MODE
#else
	#undef CRX__LIB__MODE
	#if(!defined(CRX__LIB__C_MODE))
		#define CRX__LIB__C_MODE CRX__LIB__MODE__STAND_ALONE
	#endif
	#define CRX__LIB__MODE CRX__LIB__C_MODE
#endif
//<<START>>	INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/String.h"
#include "Crx/H/crx/c/Array.h"
#include "Crx/H/crx/c/error.h"
#include "Crx/H/crx/c/arrays/StringSmall.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()

#if(defined(CRX__LAN__C_99) || defined(UINT32_MAX))
	#define CRX__C__CRX_CSS__PRIVATE__SIZE08_T uint8_t
	#define CRX__C__CRX_CSS__PRIVATE__SIZE08_MAX UINT8_MAX
	#define CRX__C__CRX_CSS__PRIVATE__SIZE16_T uint16_t
	#define CRX__C__CRX_CSS__PRIVATE__SIZE16_MAX UINT16_MAX
	#define CRX__C__CRX_CSS__PRIVATE__SIZE32_T uint32_t
	#define CRX__C__CRX_CSS__PRIVATE__SIZE32_MAX UINT32_MAX
#else
	#define CRX__C__CRX_CSS__PRIVATE__SIZE08_T size_t
	#define CRX__C__CRX_CSS__PRIVATE__SIZE16_T size_t
	#define CRX__C__CRX_CSS__PRIVATE__SIZE32_T size_t
	#ifdef SIZE_MAX
		#define CRX__C__CRX_CSS__PRIVATE__SIZE08_MAX SIZE_MAX
		#define CRX__C__CRX_CSS__PRIVATE__SIZE16_MAX SIZE_MAX
		#define CRX__C__CRX_CSS__PRIVATE__SIZE32_MAX SIZE_MAX
	#else
		#define CRX__C__CRX_CSS__PRIVATE__SIZE08_MAX ((size_t)(-1))
		#define CRX__C__CRX_CSS__PRIVATE__SIZE16_MAX ((size_t)(-1))
		#define CRX__C__CRX_CSS__PRIVATE__SIZE32_MAX ((size_t)(-1))
	#endif
#endif

typedef struct Crx_C_CrxCss_Block Crx_C_CrxCss_Block;


//--- ENUM: Type ------------------//
CRX_ENUM(Crx_C_CrxCss_Type,
(
	CRX__C__CRX_CSS__TYPE__NULL = 0,
	CRX__C__CRX_CSS__TYPE__AT_RULE_STATEMENT,
	CRX__C__CRX_CSS__TYPE__AT_RULE_ELEMENT,
	CRX__C__CRX_CSS__TYPE__AT_RULE_NAME_VALUE_BLOCK,
	CRX__C__CRX_CSS__TYPE__REFERENCE_NAME_VALUE_BLOCK
));

//--- CLASS: AtRuleStatement ----------------------------//
typedef struct Crx_C_CrxCss_AtRuleStatement
{
	Crx_C_String gName;
	Crx_C_String gValue;
}Crx_C_CrxCss_AtRuleStatement;

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleStatement_construct(
		Crx_C_CrxCss_AtRuleStatement * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleStatement_copyConstruct(
		Crx_C_CrxCss_AtRuleStatement * pThis,
		Crx_C_CrxCss_AtRuleStatement const * pAtRuleStatement);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleStatement * crx_c_crxCss_atRuleStatement_new();
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleStatement * crx_c_crxCss_atRuleStatement_copyNew(
		Crx_C_CrxCss_AtRuleStatement const * pAtRuleStatement);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleStatement * crx_c_crxCss_atRuleStatement_moveNew(
		Crx_C_CrxCss_AtRuleStatement * pAtRuleStatement);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleStatement_destruct(
		Crx_C_CrxCss_AtRuleStatement * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleStatement_free(
		Crx_C_CrxCss_AtRuleStatement * pThis);

//--- CLASS: AtRuleElement ---------------------//
struct Crx_C_CrxCss_Block;
typedef struct Crx_C_CrxCss_AtRuleElement
{
	Crx_C_String gName;
	Crx_C_String gValue;
	Crx_C_CrxCss_Block * gBlock;
}Crx_C_CrxCss_AtRuleElement;

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleElement_construct(
		Crx_C_CrxCss_AtRuleElement * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleElement_copyConstruct(
		Crx_C_CrxCss_AtRuleElement * pThis, Crx_C_CrxCss_AtRuleElement const * pAtRuleElement);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleElement * crx_c_crxCss_atRuleElement_new();
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleElement * crx_c_crxCss_atRuleElement_copyNew(
		Crx_C_CrxCss_AtRuleElement const * pAtRuleElement);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleElement * crx_c_crxCss_atRuleElement_moveNew(
		Crx_C_CrxCss_AtRuleElement * pAtRuleElement);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleElement_destruct(
		Crx_C_CrxCss_AtRuleElement * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleElement_free(
		Crx_C_CrxCss_AtRuleElement * pThis);

//--- CLASS: NameValuePair --------------------//
typedef struct Crx_C_CrxCss_NameValuePair
{
	Crx_C_String gName;
	Crx_C_String gValue;
}Crx_C_CrxCss_NameValuePair;

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_nameValuePair_construct(
		Crx_C_CrxCss_NameValuePair * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_nameValuePair_copyConstruct(
		Crx_C_CrxCss_NameValuePair * pThis, Crx_C_CrxCss_NameValuePair const * pNameValuePair);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_NameValuePair * crx_c_crxCss_nameValuePair_new();
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_NameValuePair * crx_c_crxCss_nameValuePair_copyNew(
		Crx_C_CrxCss_NameValuePair const * pNameValuePair);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_NameValuePair * crx_c_crxCss_nameValuePair_moveNew(
		Crx_C_CrxCss_NameValuePair * pNameValuePair);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_nameValuePair_destruct(
		Crx_C_CrxCss_NameValuePair * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_nameValuePair_free(
		Crx_C_CrxCss_NameValuePair * pThis);

//--- CLASS: NameValueBlock --------------------//
CRX__C__Array__DECLARE(Crx_C_CrxCss_NameValueBlock, crx_c_crxCss_nameValueBlock_, 
		Crx_C_CrxCss_NameValuePair,
		CRX__C__CRX_CSS__PRIVATE__SIZE08_T, CRX__C__CRX_CSS__PRIVATE__SIZE08_MAX, 
		0, CRXM__FALSE, 
		crx_c_crxCss_nameValuePair_destruct, crx_c_crxCss_nameValuePair_copyConstruct, 
		CRXM__FALSE, CRXM__FALSE)

//--- CLASS: AtRuleNameValueBlock --------------//
typedef struct Crx_C_CrxCss_AtRuleNameValueBlock
{
	Crx_C_String gName;
	Crx_C_String gValue;
	Crx_C_CrxCss_NameValueBlock gNameValueBlock;
}Crx_C_CrxCss_AtRuleNameValueBlock;

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleNameValueBlock_construct(
		Crx_C_CrxCss_AtRuleNameValueBlock * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleNameValueBlock_copyConstruct(
		Crx_C_CrxCss_AtRuleNameValueBlock * pThis, 
		Crx_C_CrxCss_AtRuleNameValueBlock const * pAtRuleNameValueBlock);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleNameValueBlock * crx_c_crxCss_atRuleNameValueBlock_new();
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleNameValueBlock * crx_c_crxCss_atRuleNameValueBlock_copyNew(
		Crx_C_CrxCss_AtRuleNameValueBlock const * pAtRuleNameValueBlock);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleNameValueBlock * crx_c_crxCss_atRuleNameValueBlock_moveNew(
		Crx_C_CrxCss_AtRuleNameValueBlock * pAtRuleNameValueBlock);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleNameValueBlock_destruct(
		Crx_C_CrxCss_AtRuleNameValueBlock * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleNameValueBlock_free(
		Crx_C_CrxCss_AtRuleNameValueBlock * pThis);

//--- CLASS: ReferenceNameValueBlock -----------//
typedef struct Crx_C_CrxCss_ReferenceNameValueBlock
{
	Crx_C_Arrays_StringSmall gReferences;
	Crx_C_CrxCss_NameValueBlock gNameValueBlock;
}Crx_C_CrxCss_ReferenceNameValueBlock;

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_referenceNameValueBlock_construct(
		Crx_C_CrxCss_ReferenceNameValueBlock * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_referenceNameValueBlock_copyConstruct(
		Crx_C_CrxCss_ReferenceNameValueBlock * pThis, 
		Crx_C_CrxCss_ReferenceNameValueBlock const * pReferenceNameValueBlock);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_ReferenceNameValueBlock * crx_c_crxCss_referenceNameValueBlock_new();
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_ReferenceNameValueBlock * crx_c_crxCss_referenceNameValueBlock_copyNew(
		Crx_C_CrxCss_ReferenceNameValueBlock const * pReferenceNameValueBlock);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_ReferenceNameValueBlock * crx_c_crxCss_referenceNameValueBlock_moveNew(
		Crx_C_CrxCss_ReferenceNameValueBlock * pReferenceNameValueBlock);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_referenceNameValueBlock_destruct(
		Crx_C_CrxCss_ReferenceNameValueBlock * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_referenceNameValueBlock_free(
		Crx_C_CrxCss_ReferenceNameValueBlock * pThis);

//--- CLASS: BlockElement ----------------------//
typedef struct Crx_C_CrxCss_BlockElement
{
	Crx_C_CrxCss_Type gPrivate_type;
	union
	{
		Crx_C_CrxCss_AtRuleStatement uAtRuleStatement;
		Crx_C_CrxCss_AtRuleElement uAtRuleElement;
		Crx_C_CrxCss_AtRuleNameValueBlock uAtRuleNameValueBlock;
		Crx_C_CrxCss_ReferenceNameValueBlock uReferenceNameValueBlock;
		/*Crx_C_CrxCss_Comment uComment;*/
	}gPrivate_data;
}Crx_C_CrxCss_BlockElement;

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_construct(
		Crx_C_CrxCss_BlockElement * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_copyConstruct(
		Crx_C_CrxCss_BlockElement * pThis, Crx_C_CrxCss_BlockElement const * pBlockElement);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_moveConstruct(
		Crx_C_CrxCss_BlockElement * pThis, Crx_C_CrxCss_BlockElement * pBlockElement);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_BlockElement * crx_c_crxCss_blockElement_new();
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_BlockElement * crx_c_crxCss_blockElement_copyNew(
		Crx_C_CrxCss_BlockElement const * pBlockElement);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_BlockElement * crx_c_crxCss_blockElement_moveNew(
		Crx_C_CrxCss_BlockElement * pBlockElement);

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_crxCss_blockElement_private_empty(
		Crx_C_CrxCss_BlockElement * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_moveAndSetAtRuleStatement(
		Crx_C_CrxCss_BlockElement * pThis, Crx_C_CrxCss_AtRuleStatement * pAtRuleStatement);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_moveAndSetAtRuleElement(
		Crx_C_CrxCss_BlockElement * pThis, Crx_C_CrxCss_AtRuleElement * pAtRuleElement);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_moveAndSetAtRuleNameValueBlock(
		Crx_C_CrxCss_BlockElement * pThis, 
		Crx_C_CrxCss_AtRuleNameValueBlock * pAtRuleNameValueBlock);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_moveAndSetReferenceNameValueBlock(
		Crx_C_CrxCss_BlockElement * pThis, 
		Crx_C_CrxCss_ReferenceNameValueBlock * pReferenceNameValueBlock);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_Type crx_c_crxCss_blockElement_getType(
		Crx_C_CrxCss_BlockElement * pThis);

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleStatement * crx_c_crxCss_blockElement_getAtRuleStatement(
		Crx_C_CrxCss_BlockElement * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleElement * crx_c_crxCss_blockElement_getAtRuleElement(
		Crx_C_CrxCss_BlockElement * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleNameValueBlock * crx_c_crxCss_blockElement_getAtRuleNameValueBlock(
		Crx_C_CrxCss_BlockElement * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_ReferenceNameValueBlock * crx_c_crxCss_blockElement_getReferenceNameValueBlock(
		Crx_C_CrxCss_BlockElement * pThis);
		
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_destruct(
		Crx_C_CrxCss_BlockElement * pThis);
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_free(Crx_C_CrxCss_BlockElement * pThis);


//--- CLASS: Block -----------------------------//
CRX__C__Array__DECLARE(Crx_C_CrxCss_Block, crx_c_crxCss_block_, Crx_C_CrxCss_BlockElement,
		CRX__C__CRX_CSS__PRIVATE__SIZE32_T, CRX__C__CRX_CSS__PRIVATE__SIZE32_MAX, 0, 
		CRXM__FALSE, crx_c_crxCss_blockElement_destruct, crx_c_crxCss_blockElement_copyConstruct, 
		crx_c_crxCss_blockElement_moveConstruct, CRXM__FALSE)

//--- CLASS: ParserData---------------------------//
typedef struct Crx_C_CrxCss_ParserData
{
	char const * CRX_NOT_MINE gChars;
	char const * CRX_NOT_MINE gCurrentCharacter;
	Crx_C_Error_Error * CRX_NOT_MINE gError;
	bool gIsError;
	size_t gLength;
	size_t gRemainingLength;
}Crx_C_CrxCss_ParserData;


//--- GLOBALS ----------------------------------//

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_BlockElement * CRX_PASSING crx_c_crxCss_parseCrxCss(
		Crx_C_String * pSource, Crx_C_Error_Error * pError__out);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_BlockElement * CRX_PASSING crx_c_crxCss_parseCrxCss2(
		char const * pSource, Crx_C_Error_Error * pError__out);
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_BlockElement * CRX_PASSING crx_c_crxCss_parseCrxCss3(
		char const * pSource, size_t pSourceLength, Crx_C_Error_Error * pError__out);

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_crxCss_pushErrorTraceToParserData(
		Crx_C_CrxCss_ParserData * pParserData, unsigned int pCode, 
		char const * CRX_NOT_NULL pString);
CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_crxCss_isInKeyValueBlock(
		Crx_C_CrxCss_ParserData * CRX_NOT_NULL pParserData);
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_crxCss_skipWhiteSpaceAndComment(
		Crx_C_CrxCss_ParserData * CRX_NOT_NULL pParserData);
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_crxCss_skipComment(
		Crx_C_CrxCss_ParserData * CRX_NOT_NULL pParserData);
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_crxCss_parseBlock(
		Crx_C_CrxCss_ParserData * CRX_NOT_NULL pParserData, 
		Crx_C_CrxCss_Block * CRX_NOT_NULL pBlock);
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_crxCss_parseNameValueBlock(
		Crx_C_CrxCss_ParserData * CRX_NOT_NULL pParserData, 
		Crx_C_CrxCss_NameValueBlock * CRX_NOT_NULL pNameValueBlock);


CRX__LIB__C_CODE_END()

#if(CRXM__IS(CRX__LIB__MODE, CRX__LIB__MODE__HEADER_ONLY))
	//INCLUDE THE CORRESPONDING .c.h FILE FROM THE CRXed CODE. DO NOT INCLUDE ANY OTHER FILE
	#include "Crx/C.H/crx/c/crxCss.c.h"
#endif
#if(CRX__PREPROCESSOR__HAS_PUSH_MACRO)
	#pragma pop_macro("CRX__LIB__MODE")
#endif

#endif