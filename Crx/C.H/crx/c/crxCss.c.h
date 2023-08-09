//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/crxCss.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "Crx/H/crx/c/String.h"
#include "Crx/H/crx/c/Array.h"
#include "Crx/H/crx/c/error.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()


#define CRX__C__CRXSS__IS_WHITE_SPACE(pCHAR) \
		((*(pCHAR) > 0) && (*(pCHAR) == 127 || (*(pCHAR) >= 0) && (*(pCHAR) <= 32)))
#define CRX__C__CRXSS__IS_WHITE_SPACE2(pCHAR) \
		(((pCHAR) > 0) && ((pCHAR) == 127 || ((pCHAR) >= 0) && ((pCHAR) <= 32)))


//--- CLASS: AtRuleStatement ----------------------------//
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleStatement_construct(
		Crx_C_CrxCss_AtRuleStatement * pThis)
{
	crx_c_string_construct(&(pThis->gName), 0);
	crx_c_string_construct(&(pThis->gValue), 0);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleStatement_copyConstruct(
		Crx_C_CrxCss_AtRuleStatement * pThis, Crx_C_CrxCss_AtRuleStatement const * pAtRuleStatement)
{
	crx_c_string_copyConstruct(&(pThis->gName), &(pAtRuleStatement->gName));
	crx_c_string_copyConstruct(&(pThis->gValue), &(pAtRuleStatement->gName));
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleStatement * crx_c_crxCss_atRuleStatement_new()
{
	Crx_C_CrxCss_AtRuleStatement * vReturn = 
			((Crx_C_CrxCss_AtRuleStatement *)malloc(sizeof(Crx_C_CrxCss_AtRuleStatement)));

	if(vReturn != NULL)
		{crx_c_crxCss_atRuleStatement_construct(vReturn);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleStatement * crx_c_crxCss_atRuleStatement_copyNew(
		Crx_C_CrxCss_AtRuleStatement const * pAtRuleStatement)
{
	Crx_C_CrxCss_AtRuleStatement * vReturn = 
			((Crx_C_CrxCss_AtRuleStatement *)malloc(sizeof(Crx_C_CrxCss_AtRuleStatement)));

	if(vReturn != NULL)
		{crx_c_crxCss_atRuleStatement_copyConstruct(vReturn, pAtRuleStatement);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleStatement * crx_c_crxCss_atRuleStatement_moveNew(
		Crx_C_CrxCss_AtRuleStatement * pAtRuleStatement)
{
	Crx_C_CrxCss_AtRuleStatement * vReturn = 
			((Crx_C_CrxCss_AtRuleStatement *)malloc(sizeof(Crx_C_CrxCss_AtRuleStatement)));

	if(vReturn != NULL)
		{memcpy(vReturn, pAtRuleStatement, sizeof(Crx_C_CrxCss_AtRuleStatement));}

	return vReturn;
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleStatement_destruct(
		Crx_C_CrxCss_AtRuleStatement * pThis)
{
	crx_c_string_destruct(&(pThis->gName));
	crx_c_string_destruct(&(pThis->gValue));
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleStatement_free(
		Crx_C_CrxCss_AtRuleStatement * pThis)
	{free(pThis);}

//--- CLASS: AtRuleElement ---------------------//
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleElement_construct(
		Crx_C_CrxCss_AtRuleElement * pThis)
{
	crx_c_string_construct(&(pThis->gName), 0);
	crx_c_string_construct(&(pThis->gValue), 0);
	pThis->gBlock = crx_c_crxCss_block_new(0);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleElement_copyConstruct(
		Crx_C_CrxCss_AtRuleElement * pThis, Crx_C_CrxCss_AtRuleElement const * pAtRuleElement)
{
	crx_c_string_copyConstruct(&(pThis->gName), &(pAtRuleElement->gName));
	crx_c_string_copyConstruct(&(pThis->gValue), &(pAtRuleElement->gValue));
	pThis->gBlock = crx_c_crxCss_block_copyNew(pAtRuleElement->gBlock);
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleElement * crx_c_crxCss_atRuleElement_new()
{
	Crx_C_CrxCss_AtRuleElement * vReturn = 
			((Crx_C_CrxCss_AtRuleElement *)malloc(sizeof(Crx_C_CrxCss_AtRuleElement)));

	if(vReturn != NULL)
		{crx_c_crxCss_atRuleElement_construct(vReturn);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleElement * crx_c_crxCss_atRuleElement_copyNew(
		Crx_C_CrxCss_AtRuleElement const * pAtRuleElement)
{
	Crx_C_CrxCss_AtRuleElement * vReturn = 
			((Crx_C_CrxCss_AtRuleElement *)malloc(sizeof(Crx_C_CrxCss_AtRuleElement)));

	if(vReturn != NULL)
		{crx_c_crxCss_atRuleElement_copyConstruct(vReturn, pAtRuleElement);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleElement * crx_c_crxCss_atRuleElement_moveNew(
		Crx_C_CrxCss_AtRuleElement * pAtRuleElement)
{
	Crx_C_CrxCss_AtRuleElement * vReturn = 
			((Crx_C_CrxCss_AtRuleElement *)malloc(sizeof(Crx_C_CrxCss_AtRuleElement)));

	if(vReturn != NULL)
		{memcpy(vReturn, pAtRuleElement, sizeof(Crx_C_CrxCss_AtRuleElement));}

	return vReturn;
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleElement_destruct(
		Crx_C_CrxCss_AtRuleElement * pThis)
{
	crx_c_string_destruct(&(pThis->gName));
	crx_c_string_destruct(&(pThis->gValue));
	crx_c_crxCss_block_destruct(pThis->gBlock);
	crx_c_crxCss_block_free(pThis->gBlock);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleElement_free(
		Crx_C_CrxCss_AtRuleElement * pThis)
	{free(pThis);}

//--- CLASS: NameValuePair --------------------//
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_nameValuePair_construct(
		Crx_C_CrxCss_NameValuePair * pThis)
{
	crx_c_string_construct(&(pThis->gName), 0);
	crx_c_string_construct(&(pThis->gValue), 0);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_nameValuePair_copyConstruct(
		Crx_C_CrxCss_NameValuePair * pThis, Crx_C_CrxCss_NameValuePair const * pNameValuePair)
{
	crx_c_string_copyConstruct(&(pThis->gName), &(pNameValuePair->gName));
	crx_c_string_copyConstruct(&(pThis->gValue), &(pNameValuePair->gValue));
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_NameValuePair * crx_c_crxCss_nameValuePair_new()
{
	Crx_C_CrxCss_NameValuePair * vReturn = 
			((Crx_C_CrxCss_NameValuePair *)malloc(sizeof(Crx_C_CrxCss_NameValuePair)));

	if(vReturn != NULL)
		{crx_c_crxCss_nameValuePair_construct(vReturn);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_NameValuePair * crx_c_crxCss_nameValuePair_copyNew(
		Crx_C_CrxCss_NameValuePair const * pNameValuePair)
{
	Crx_C_CrxCss_NameValuePair * vReturn = 
			((Crx_C_CrxCss_NameValuePair *)malloc(sizeof(Crx_C_CrxCss_NameValuePair)));

	if(vReturn != NULL)
		{crx_c_crxCss_nameValuePair_copyConstruct(vReturn, pNameValuePair);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_NameValuePair * crx_c_crxCss_nameValuePair_moveNew(
		Crx_C_CrxCss_NameValuePair * pNameValuePair)
{
	Crx_C_CrxCss_NameValuePair * vReturn = 
			((Crx_C_CrxCss_NameValuePair *)malloc(sizeof(Crx_C_CrxCss_NameValuePair)));

	if(vReturn != NULL)
		{memcpy(vReturn, pNameValuePair, sizeof(Crx_C_CrxCss_NameValuePair));}

	return vReturn;
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_nameValuePair_destruct(
		Crx_C_CrxCss_NameValuePair * pThis)
{
	crx_c_string_destruct(&(pThis->gName));
	crx_c_string_destruct(&(pThis->gValue));
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_nameValuePair_free(
		Crx_C_CrxCss_NameValuePair * pThis)
	{free(pThis);}

//--- CLASS: NameValueBlock --------------------//
CRX__C__Array__DEFINE(Crx_C_CrxCss_NameValueBlock, crx_c_crxCss_nameValueBlock_, 
		Crx_C_CrxCss_NameValuePair,
		CRX__C__CRX_CSS__PRIVATE__SIZE08_T, CRX__C__CRX_CSS__PRIVATE__SIZE08_MAX, 
		0, CRXM__FALSE, 
		crx_c_crxCss_nameValuePair_destruct, crx_c_crxCss_nameValuePair_copyConstruct, 
		CRXM__FALSE, CRXM__FALSE)

//--- CLASS: AtRuleNameValueBlock --------------//
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleNameValueBlock_construct(
		Crx_C_CrxCss_AtRuleNameValueBlock * pThis)
{
	crx_c_string_construct(&(pThis->gName), 0);
	crx_c_string_construct(&(pThis->gValue), 0);
	crx_c_crxCss_nameValueBlock_construct(&(pThis->gNameValueBlock), 0);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleNameValueBlock_copyConstruct(
		Crx_C_CrxCss_AtRuleNameValueBlock * pThis, 
		Crx_C_CrxCss_AtRuleNameValueBlock const * pAtRuleNameValueBlock)
{
	crx_c_string_copyConstruct(&(pThis->gName), &(pAtRuleNameValueBlock->gName));
	crx_c_string_copyConstruct(&(pThis->gValue), &(pAtRuleNameValueBlock->gValue));
	crx_c_crxCss_nameValueBlock_copyConstruct(&(pThis->gNameValueBlock), &(pAtRuleNameValueBlock->gNameValueBlock));
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleNameValueBlock * crx_c_crxCss_atRuleNameValueBlock_new()
{
	Crx_C_CrxCss_AtRuleNameValueBlock * vReturn = 
			((Crx_C_CrxCss_AtRuleNameValueBlock *)malloc(sizeof(Crx_C_CrxCss_AtRuleNameValueBlock)));

	if(vReturn != NULL)
		{crx_c_crxCss_atRuleNameValueBlock_construct(vReturn);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleNameValueBlock * crx_c_crxCss_atRuleNameValueBlock_copyNew(
		Crx_C_CrxCss_AtRuleNameValueBlock const * pAtRuleNameValueBlock)
{
	Crx_C_CrxCss_AtRuleNameValueBlock * vReturn = 
			((Crx_C_CrxCss_AtRuleNameValueBlock *)malloc(sizeof(Crx_C_CrxCss_AtRuleNameValueBlock)));

	if(vReturn != NULL)
		{crx_c_crxCss_atRuleNameValueBlock_copyConstruct(vReturn, pAtRuleNameValueBlock);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleNameValueBlock * crx_c_crxCss_atRuleNameValueBlock_moveNew(
		Crx_C_CrxCss_AtRuleNameValueBlock * pAtRuleNameValueBlock)
{
	Crx_C_CrxCss_AtRuleNameValueBlock * vReturn = 
			((Crx_C_CrxCss_AtRuleNameValueBlock *)malloc(sizeof(Crx_C_CrxCss_AtRuleNameValueBlock)));

	if(vReturn != NULL)
		{memcpy(vReturn, pAtRuleNameValueBlock, sizeof(Crx_C_CrxCss_AtRuleNameValueBlock));}

	return vReturn;
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleNameValueBlock_destruct(
		Crx_C_CrxCss_AtRuleNameValueBlock * pThis)
{
	crx_c_string_destruct(&(pThis->gName));
	crx_c_string_destruct(&(pThis->gValue));
	crx_c_crxCss_nameValueBlock_destruct(&(pThis->gNameValueBlock));
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_atRuleNameValueBlock_free(
		Crx_C_CrxCss_AtRuleNameValueBlock * pThis)
	{free(pThis);}

//--- CLASS: ReferenceNameValueBlock -----------//
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_referenceNameValueBlock_construct(
		Crx_C_CrxCss_ReferenceNameValueBlock * pThis)
{
	crx_c_arrays_stringSmall_construct(&(pThis->gReferences), 0);
	crx_c_crxCss_nameValueBlock_construct(&(pThis->gNameValueBlock), 0);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_referenceNameValueBlock_copyConstruct(
		Crx_C_CrxCss_ReferenceNameValueBlock * pThis, 
		Crx_C_CrxCss_ReferenceNameValueBlock const * pReferenceNameValueBlock)
{
	crx_c_arrays_stringSmall_copyConstruct(&(pThis->gReferences), 
			&(pReferenceNameValueBlock->gReferences));
	crx_c_crxCss_nameValueBlock_copyConstruct(&(pThis->gNameValueBlock), 
			&(pReferenceNameValueBlock->gNameValueBlock));
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_ReferenceNameValueBlock * crx_c_crxCss_referenceNameValueBlock_new()
{
	Crx_C_CrxCss_ReferenceNameValueBlock * vReturn = 
			((Crx_C_CrxCss_ReferenceNameValueBlock *)malloc(
			sizeof(Crx_C_CrxCss_ReferenceNameValueBlock)));

	if(vReturn != NULL)
		{crx_c_crxCss_referenceNameValueBlock_construct(vReturn);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_ReferenceNameValueBlock * crx_c_crxCss_referenceNameValueBlock_copyNew(
		Crx_C_CrxCss_ReferenceNameValueBlock const * pReferenceNameValueBlock)
{
	Crx_C_CrxCss_ReferenceNameValueBlock * vReturn = 
			((Crx_C_CrxCss_ReferenceNameValueBlock *)malloc(
			sizeof(Crx_C_CrxCss_ReferenceNameValueBlock)));

	if(vReturn != NULL)
		{crx_c_crxCss_referenceNameValueBlock_copyConstruct(vReturn, pReferenceNameValueBlock);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_ReferenceNameValueBlock * crx_c_crxCss_referenceNameValueBlock_moveNew(
		Crx_C_CrxCss_ReferenceNameValueBlock * pReferenceNameValueBlock)
{
	Crx_C_CrxCss_ReferenceNameValueBlock * vReturn = 
			((Crx_C_CrxCss_ReferenceNameValueBlock *)malloc(
			sizeof(Crx_C_CrxCss_ReferenceNameValueBlock)));

	if(vReturn != NULL)
		{memcpy(vReturn, pReferenceNameValueBlock, sizeof(Crx_C_CrxCss_ReferenceNameValueBlock));}

	return vReturn;
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_referenceNameValueBlock_destruct(
		Crx_C_CrxCss_ReferenceNameValueBlock * pThis)
{
	crx_c_arrays_stringSmall_destruct(&(pThis->gReferences));
	crx_c_crxCss_nameValueBlock_destruct(&(pThis->gNameValueBlock));
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_referenceNameValueBlock_free(
		Crx_C_CrxCss_ReferenceNameValueBlock * pThis)
	{free(pThis);}

//--- CLASS: BlockElement ----------------------//
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_construct(
		Crx_C_CrxCss_BlockElement * pThis)
{
	CRX__SET_TO_ZERO(Crx_C_CrxCss_BlockElement, *pThis);
	pThis->gPrivate_type = CRX__C__CRX_CSS__TYPE__NULL;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_copyConstruct(
		Crx_C_CrxCss_BlockElement * pThis, Crx_C_CrxCss_BlockElement const * pBlockElement)
{
	CRX__SET_TO_ZERO(Crx_C_CrxCss_BlockElement, *pThis);

	switch(pBlockElement->gPrivate_type)
	{
		case CRX__C__CRX_CSS__TYPE__AT_RULE_STATEMENT:
		{
			crx_c_crxCss_atRuleStatement_copyConstruct(&(pThis->gPrivate_data.uAtRuleStatement),
					&(pBlockElement->gPrivate_data.uAtRuleStatement));

			break;
		}
		case CRX__C__CRX_CSS__TYPE__AT_RULE_ELEMENT:
		{
			crx_c_crxCss_atRuleElement_copyConstruct(&(pThis->gPrivate_data.uAtRuleElement),
					&(pBlockElement->gPrivate_data.uAtRuleElement));

			break;
		}
		case CRX__C__CRX_CSS__TYPE__AT_RULE_NAME_VALUE_BLOCK:
		{
			crx_c_crxCss_atRuleNameValueBlock_copyConstruct(&(pThis->gPrivate_data.uAtRuleNameValueBlock),
					&(pBlockElement->gPrivate_data.uAtRuleNameValueBlock));

			break;
		}
		case CRX__C__CRX_CSS__TYPE__REFERENCE_NAME_VALUE_BLOCK:
		{
			crx_c_crxCss_referenceNameValueBlock_copyConstruct(&(pThis->gPrivate_data.uReferenceNameValueBlock),
					&(pBlockElement->gPrivate_data.uReferenceNameValueBlock));

			break;
		}
	}

	pThis->gPrivate_type = pBlockElement->gPrivate_type;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_moveConstruct(
		Crx_C_CrxCss_BlockElement * pThis, Crx_C_CrxCss_BlockElement * pBlockElement)
{
	CRX__SET_TO_ZERO(Crx_C_CrxCss_BlockElement, *pThis);

	switch(pBlockElement->gPrivate_type)
	{
		case CRX__C__CRX_CSS__TYPE__AT_RULE_STATEMENT:
		{
			memcpy(&(pThis->gPrivate_data.uAtRuleStatement),
					&(pBlockElement->gPrivate_data.uAtRuleStatement),
					sizeof(Crx_C_CrxCss_AtRuleStatement));

			break;
		}
		case CRX__C__CRX_CSS__TYPE__AT_RULE_ELEMENT:
		{
			memcpy(&(pThis->gPrivate_data.uAtRuleElement),
					&(pBlockElement->gPrivate_data.uAtRuleElement), 
					sizeof(Crx_C_CrxCss_AtRuleElement));

			break;
		}
		case CRX__C__CRX_CSS__TYPE__AT_RULE_NAME_VALUE_BLOCK:
		{
			memcpy(&(pThis->gPrivate_data.uAtRuleNameValueBlock),
					&(pBlockElement->gPrivate_data.uAtRuleNameValueBlock),
					sizeof(Crx_C_CrxCss_AtRuleNameValueBlock));

			break;
		}
		case CRX__C__CRX_CSS__TYPE__REFERENCE_NAME_VALUE_BLOCK:
		{
			memcpy(&(pThis->gPrivate_data.uReferenceNameValueBlock),
					&(pBlockElement->gPrivate_data.uReferenceNameValueBlock),
					sizeof(Crx_C_CrxCss_ReferenceNameValueBlock));

			break;
		}
	}

	pThis->gPrivate_type = pBlockElement->gPrivate_type;
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_BlockElement * crx_c_crxCss_blockElement_new()
{
	Crx_C_CrxCss_BlockElement * vReturn = 
			((Crx_C_CrxCss_BlockElement *)malloc(sizeof(Crx_C_CrxCss_BlockElement)));

	if(vReturn != NULL)
		{crx_c_crxCss_blockElement_construct(vReturn);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_BlockElement * crx_c_crxCss_blockElement_copyNew(
		Crx_C_CrxCss_BlockElement const * pBlockElement)
{
	Crx_C_CrxCss_BlockElement * vReturn = 
			((Crx_C_CrxCss_BlockElement *)malloc(sizeof(Crx_C_CrxCss_BlockElement)));

	if(vReturn != NULL)
		{crx_c_crxCss_blockElement_copyConstruct(vReturn, pBlockElement);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_BlockElement * crx_c_crxCss_blockElement_moveNew(
		Crx_C_CrxCss_BlockElement * pBlockElement)
{
	Crx_C_CrxCss_BlockElement * vReturn = 
			((Crx_C_CrxCss_BlockElement *)malloc(sizeof(Crx_C_CrxCss_BlockElement)));

	if(vReturn != NULL)
		{crx_c_crxCss_blockElement_moveConstruct(vReturn, pBlockElement);}

	return vReturn;
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_crxCss_blockElement_private_empty(
		Crx_C_CrxCss_BlockElement * pThis)
{
	if(pThis->gPrivate_type == CRX__C__CRX_CSS__TYPE__NULL)
		{return;}

	switch(pThis->gPrivate_type)
	{
		case CRX__C__CRX_CSS__TYPE__AT_RULE_STATEMENT:
		{
			crx_c_crxCss_atRuleStatement_destruct(&(pThis->gPrivate_data.uAtRuleStatement));

			break;
		}
		case CRX__C__CRX_CSS__TYPE__AT_RULE_ELEMENT:
		{
			crx_c_crxCss_atRuleElement_destruct(&(pThis->gPrivate_data.uAtRuleElement));

			break;
		}
		case CRX__C__CRX_CSS__TYPE__AT_RULE_NAME_VALUE_BLOCK:
		{
			crx_c_crxCss_atRuleNameValueBlock_destruct(&(pThis->gPrivate_data.uAtRuleNameValueBlock));

			break;
		}
		case CRX__C__CRX_CSS__TYPE__REFERENCE_NAME_VALUE_BLOCK:
		{
			crx_c_crxCss_referenceNameValueBlock_destruct(&(pThis->gPrivate_data.uReferenceNameValueBlock));

			break;
		}
	}

	pThis->gPrivate_type = CRX__C__CRX_CSS__TYPE__NULL;
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_moveAndSetAtRuleStatement(
		Crx_C_CrxCss_BlockElement * pThis, Crx_C_CrxCss_AtRuleStatement * pAtRuleStatement)
{
	crx_c_crxCss_blockElement_private_empty(pThis);
	memcpy(&(pThis->gPrivate_data.uAtRuleStatement), 
			pAtRuleStatement, sizeof(Crx_C_CrxCss_AtRuleStatement));
	pThis->gPrivate_type = CRX__C__CRX_CSS__TYPE__AT_RULE_STATEMENT;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_moveAndSetAtRuleElement(
		Crx_C_CrxCss_BlockElement * pThis, Crx_C_CrxCss_AtRuleElement * pAtRuleElement)
{
	crx_c_crxCss_blockElement_private_empty(pThis);
	memcpy(&(pThis->gPrivate_data.uAtRuleElement), 
			pAtRuleElement, sizeof(Crx_C_CrxCss_AtRuleElement));
	pThis->gPrivate_type = CRX__C__CRX_CSS__TYPE__AT_RULE_ELEMENT;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_moveAndSetAtRuleNameValueBlock(
		Crx_C_CrxCss_BlockElement * pThis, 
		Crx_C_CrxCss_AtRuleNameValueBlock * pAtRuleNameValueBlock)
{
	crx_c_crxCss_blockElement_private_empty(pThis);
	memcpy(&(pThis->gPrivate_data.uAtRuleNameValueBlock), 
			pAtRuleNameValueBlock, sizeof(Crx_C_CrxCss_AtRuleNameValueBlock));
	pThis->gPrivate_type = CRX__C__CRX_CSS__TYPE__AT_RULE_NAME_VALUE_BLOCK;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_moveAndSetReferenceNameValueBlock(
		Crx_C_CrxCss_BlockElement * pThis, 
		Crx_C_CrxCss_ReferenceNameValueBlock * pReferenceNameValueBlock)
{
	crx_c_crxCss_blockElement_private_empty(pThis);
	memcpy(&(pThis->gPrivate_data.uReferenceNameValueBlock), 
			pReferenceNameValueBlock, sizeof(Crx_C_CrxCss_ReferenceNameValueBlock));
	pThis->gPrivate_type = CRX__C__CRX_CSS__TYPE__REFERENCE_NAME_VALUE_BLOCK;
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_Type crx_c_crxCss_blockElement_getType(
		Crx_C_CrxCss_BlockElement * pThis)
	{return pThis->gPrivate_type;}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleStatement * crx_c_crxCss_blockElement_getAtRuleStatement(
		Crx_C_CrxCss_BlockElement * pThis)
{
	if(pThis->gPrivate_type != CRX__C__CRX_CSS__TYPE__AT_RULE_STATEMENT)
		{return NULL;}

	return &(pThis->gPrivate_data.uAtRuleStatement);
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleElement * crx_c_crxCss_blockElement_getAtRuleElement(
		Crx_C_CrxCss_BlockElement * pThis)
{
	if(pThis->gPrivate_type != CRX__C__CRX_CSS__TYPE__AT_RULE_ELEMENT)
		{return NULL;}

	return &(pThis->gPrivate_data.uAtRuleElement);
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_AtRuleNameValueBlock * crx_c_crxCss_blockElement_getAtRuleNameValueBlock(
		Crx_C_CrxCss_BlockElement * pThis)
{
	if(pThis->gPrivate_type != CRX__C__CRX_CSS__TYPE__AT_RULE_NAME_VALUE_BLOCK)
		{return NULL;}

	return &(pThis->gPrivate_data.uAtRuleNameValueBlock);
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_ReferenceNameValueBlock * crx_c_crxCss_blockElement_getReferenceNameValueBlock(
		Crx_C_CrxCss_BlockElement * pThis)
{
	if(pThis->gPrivate_type != CRX__C__CRX_CSS__TYPE__REFERENCE_NAME_VALUE_BLOCK)
		{return NULL;}

	return &(pThis->gPrivate_data.uReferenceNameValueBlock);
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_destruct(
		Crx_C_CrxCss_BlockElement * pThis)
{
	crx_c_crxCss_blockElement_private_empty(pThis);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_crxCss_blockElement_free(Crx_C_CrxCss_BlockElement * pThis)
	{free(pThis);}



//--- CLASS: Block -----------------------------//
CRX__C__Array__DEFINE(Crx_C_CrxCss_Block, crx_c_crxCss_block_, Crx_C_CrxCss_BlockElement,
		CRX__C__CRX_CSS__PRIVATE__SIZE32_T, CRX__C__CRX_CSS__PRIVATE__SIZE32_MAX, 0, 
		CRXM__FALSE, crx_c_crxCss_blockElement_destruct, crx_c_crxCss_blockElement_copyConstruct, 
		crx_c_crxCss_blockElement_moveConstruct, CRXM__FALSE)

//--- GLOBALS ----------------------------------//

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_BlockElement * CRX_PASSING crx_c_crxCss_parseCrxCss(
		Crx_C_String * pSource, Crx_C_Error_Error * pError__out)
{
	if(pSource == NULL)
		{return crx_c_crxCss_blockElement_new();}
	else
	{
		return crx_c_crxCss_parseCrxCss3(crx_c_string_getElementsPointer(pSource), crx_c_string_getLength(pSource),
				pError__out);
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_BlockElement * CRX_PASSING crx_c_crxCss_parseCrxCss2(
		char const * pSource, Crx_C_Error_Error * pError__out)
{
	if(pSource == NULL)
		{return crx_c_crxCss_blockElement_new();}
	else
		{return crx_c_crxCss_parseCrxCss3(pSource, strlen(pSource), pError__out);}
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_CrxCss_BlockElement * CRX_PASSING crx_c_crxCss_parseCrxCss3(
		char const * pSource, size_t pSourceLength, Crx_C_Error_Error * pError__out)
{
	CRX_SCOPE_META
	if(pSource == NULL)
		{return crx_c_crxCss_blockElement_new();}

	CRX_SCOPE
	Crx_C_CrxCss_ParserData vParserData /*= ?*/;
	Crx_C_CrxCss_BlockElement * vReturn = crx_c_crxCss_blockElement_new();
	
	vParserData.gChars = pSource;
	vParserData.gCurrentCharacter = pSource;
	vParserData.gError = pError__out;
	vParserData.gIsError = false;
	vParserData.gLength = pSourceLength;
	vParserData.gRemainingLength = pSourceLength;
	
	crx_c_crxCss_skipWhiteSpaceAndComment(&vParserData);

	if(!vParserData.gIsError)
	{
		if(crx_c_crxCss_isInKeyValueBlock(&vParserData))
		{
			Crx_C_CrxCss_AtRuleNameValueBlock tAtRuleNameValueBlock /*= ?*/;

			crx_c_crxCss_atRuleNameValueBlock_construct(&tAtRuleNameValueBlock);

			crx_c_crxCss_parseNameValueBlock(&vParserData, &(tAtRuleNameValueBlock.gNameValueBlock));

			crx_c_crxCss_blockElement_moveAndSetAtRuleNameValueBlock(vReturn,
					&tAtRuleNameValueBlock);
		}
		else
		{
			Crx_C_CrxCss_AtRuleElement tAtRuleElement /*= ?*/;

			crx_c_crxCss_atRuleElement_construct(&tAtRuleElement);
			//crx_c_string_appendString2(&(tAtRuleElement.gName), "crx_root");

			crx_c_crxCss_parseBlock(&vParserData, tAtRuleElement.gBlock);

			crx_c_crxCss_blockElement_moveAndSetAtRuleElement(vReturn, &tAtRuleElement);
		}
	}

	if(!vParserData.gIsError)
		{crx_c_crxCss_skipWhiteSpaceAndComment(&vParserData);}
	

	if(vParserData.gRemainingLength != 0)
	{
		crx_c_crxCss_pushErrorTraceToParserData(&vParserData, 1, 
				"ERROR: Unexpected character after root block");
	}
	
	if(!vParserData.gIsError)
		{return vReturn;}
	else
	{
		crx_c_crxCss_blockElement_destruct(vReturn);
		crx_c_crxCss_blockElement_free(vReturn);
		
		return NULL;
	}
	CRX_SCOPE_END
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_crxCss_pushErrorTraceToParserData(
		Crx_C_CrxCss_ParserData * pParserData, unsigned int pCode, 
		char const * CRX_NOT_NULL pString)
{
	pParserData->gIsError = true;

	if(pParserData->gError == NULL)
		{return;}
	else
	{
		Crx_C_String tString /*= ?*/;
		char const * tCurrentChar = pParserData->gChars;
		char const * tCurrentChar__error = pParserData->gChars;
		int tLineNumber = 1;
		int tCharacterNumber = 0;
		int tCount = 0;
		
		crx_c_string_construct(&tString, 0);

		while(tCurrentChar != pParserData->gCurrentCharacter)
		{
			if(*tCurrentChar == '\n')
			{
				tLineNumber = tLineNumber + 1;
				tCharacterNumber = 0;
			}
			else
				{tCharacterNumber = tCharacterNumber + 1;}

			if(tCount == 200)
				{tCurrentChar__error++;}
			else
				{tCount = tCount + 1;}

			tCurrentChar++;
		}

		crx_c_string_appendString2(&tString, "Error at [line: ");
		crx_c_string_appendInt(&tString, tLineNumber);
		crx_c_string_appendString2(&tString, ", Byte: ");
		crx_c_string_appendInt(&tString, tCharacterNumber);
		crx_c_string_appendString2(&tString, "] After:\n");
		crx_c_string_appendChars(&tString, tCurrentChar__error, tCount);
		crx_c_string_appendString2(&tString, "\n With Message \n");
		crx_c_string_appendString2(&tString, pString);

		crx_c_error_error_pushTrace2(pParserData->gError, pCode, &tString);
		
		crx_c_string_destruct(&tString);
	}
}
CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_crxCss_isInKeyValueBlock(
		Crx_C_CrxCss_ParserData * CRX_NOT_NULL pParserData)
{
	CRX_SCOPE_META
	if(pParserData->gRemainingLength == 0)
		{return false;}

	CRX_SCOPE
	size_t vRemainingLength = pParserData->gRemainingLength;
	char const * vCurrentChar = pParserData->gCurrentCharacter;

	while((vRemainingLength--) > 0)
	{
		if(*vCurrentChar == ':')
		{
			vCurrentChar++;

			while((vRemainingLength--) > 0)
			{
				if(*vCurrentChar == '{')
					{return false;}
				else if(*vCurrentChar == ';')
					{return true;}
				else
					{vCurrentChar = vCurrentChar + 1;}
			}
		}
		else if(*vCurrentChar == '{')
			{return false;}
		else
			{vCurrentChar = vCurrentChar + 1;}
	}

	return false;
	CRX_SCOPE_END
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_crxCss_skipWhiteSpaceAndComment(
		Crx_C_CrxCss_ParserData * CRX_NOT_NULL pParserData)
{
	while(pParserData->gRemainingLength > 0)
	{
		while((pParserData->gRemainingLength > 0) && (*(pParserData->gCurrentCharacter) == 127 || 
				(*(pParserData->gCurrentCharacter) >= 0) && (*(pParserData->gCurrentCharacter) <= 32)))
		{
			(pParserData->gCurrentCharacter)++; 
			(pParserData->gRemainingLength)--;
		}

		if((pParserData->gRemainingLength > 1) && (*(pParserData->gCurrentCharacter) == '/') && 
				(*(pParserData->gCurrentCharacter + 1) == '*'))
		{
			pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 2;
			pParserData->gRemainingLength = pParserData->gRemainingLength - 2;
			
			while(pParserData->gRemainingLength > 0)
			{
				if((*(pParserData->gCurrentCharacter) != '*') || (pParserData->gRemainingLength == 1) || 
						(*(pParserData->gCurrentCharacter + 1) != '/'))
				{
					pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;
					pParserData->gRemainingLength = pParserData->gRemainingLength - 1;
				}
				else
				{
					pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 2;
					pParserData->gRemainingLength = pParserData->gRemainingLength - 2;

					break;
				}
			}
			
			if(!((pParserData->gRemainingLength > 0) || (*(pParserData->gCurrentCharacter) == 127 || 
					(*(pParserData->gCurrentCharacter) >= 0) && (*(pParserData->gCurrentCharacter) <= 32))))
				{break;}
		}
		else
			{break;}
	}
	
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_crxCss_skipComment(
		Crx_C_CrxCss_ParserData * CRX_NOT_NULL pParserData)
{
	if((pParserData->gRemainingLength > 1) && (*(pParserData->gCurrentCharacter) == '/') && 
			(*(pParserData->gCurrentCharacter + 1) == '*'))
	{
		pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 2;
		pParserData->gRemainingLength = pParserData->gRemainingLength - 2;
		
		while(pParserData->gRemainingLength > 0)
		{
			if((*(pParserData->gCurrentCharacter) != '*') || (pParserData->gRemainingLength == 1) || 
					(*(pParserData->gCurrentCharacter + 1) != '/'))
			{
				pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;
				pParserData->gRemainingLength = pParserData->gRemainingLength - 1;
			}
			else
			{
				pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 2;
				pParserData->gRemainingLength = pParserData->gRemainingLength - 2;

				break;
			}
		}
	}
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_crxCss_parseBlock(
		Crx_C_CrxCss_ParserData * CRX_NOT_NULL pParserData, 
		Crx_C_CrxCss_Block * CRX_NOT_NULL pBlock)
{
	if(pParserData->gRemainingLength > 0)
	{
		while((pParserData->gRemainingLength > 0) && !pParserData->gIsError)
		{
			if(*(pParserData->gCurrentCharacter) == '@')
			{
				Crx_C_String tString /*= ?*/;
				Crx_C_String tString2 /*= ?*/;
				unsigned int tType = 0; /*	0: Not found, 1: AtRuleStatement, 2: AtRuleElement, 
											3: AtRuleKeyValueBlock*/

				pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;
				pParserData->gRemainingLength = pParserData->gRemainingLength - 1;

				crx_c_string_construct(&tString, 0);
				crx_c_string_construct(&tString2, 0);

				while(pParserData->gRemainingLength > 0)
				{
					if(CRX__C__CRXSS__IS_WHITE_SPACE(pParserData->gCurrentCharacter))
						{break;}
					else if((*(pParserData->gCurrentCharacter) == '/') && 
							(pParserData->gRemainingLength > 1) && 
							(*(pParserData->gCurrentCharacter + 1) == '*'))
						{crx_c_crxCss_skipComment(pParserData);}
					else if((*(pParserData->gCurrentCharacter) == '{') ||
							(*(pParserData->gCurrentCharacter) == ';'))
						{break;}
					else if((*(pParserData->gCurrentCharacter) != '}') &&
							(*(pParserData->gCurrentCharacter) != ':') &&
							(*(pParserData->gCurrentCharacter) != ','))
					{
						crx_c_string_appendChars(&tString, pParserData->gCurrentCharacter, 1);
						
						pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;
						pParserData->gRemainingLength = pParserData->gRemainingLength - 1;
					}
					else
					{
						crx_c_crxCss_pushErrorTraceToParserData(pParserData, 1, 
								"Error: Unexpected character while parsing @ruleName");

						break;
					}
				}
				
				if(crx_c_string_getLength(&tString) == 0)
				{
					crx_c_crxCss_pushErrorTraceToParserData(pParserData, 1, 
							"Error: ruleName can not be empty");
				}

				if(!pParserData->gIsError)
				{
					crx_c_crxCss_skipWhiteSpaceAndComment(pParserData);

					while(pParserData->gRemainingLength > 0)
					{
						if((*(pParserData->gCurrentCharacter) == '/') && 
								(pParserData->gRemainingLength > 1) && 
								(*(pParserData->gCurrentCharacter + 1) == '*'))
							{crx_c_crxCss_skipComment(pParserData);}
						else if(*(pParserData->gCurrentCharacter) == '{')
						{
							pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;
							pParserData->gRemainingLength = pParserData->gRemainingLength - 1;

							if(crx_c_crxCss_isInKeyValueBlock(pParserData))
								{tType = 3;}
							else
								{tType = 2;}

							break;
						}
						else if(*(pParserData->gCurrentCharacter) == ';')
						{
							tType = 1;
							
							pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;
							pParserData->gRemainingLength = pParserData->gRemainingLength - 1;
							
							break;
						}
						else if(*(pParserData->gCurrentCharacter) != '}')
						{
							crx_c_string_appendChars(&tString2, pParserData->gCurrentCharacter, 1);
							
							pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;
							pParserData->gRemainingLength = pParserData->gRemainingLength - 1;
						}
					}
				}

				if(tType != 0)
				{
					Crx_C_CrxCss_BlockElement tBlockElement /*= ?*/;

					crx_c_crxCss_blockElement_construct(&tBlockElement);
					
					if(tType == 1)
					{
						Crx_C_CrxCss_AtRuleStatement tAtRuleStatement /*= ?*/;

						crx_c_crxCss_atRuleStatement_construct(&tAtRuleStatement);

						crx_c_string_appendString(&(tAtRuleStatement.gName), &tString);
						crx_c_string_appendString(&(tAtRuleStatement.gValue), &tString2);

						crx_c_crxCss_blockElement_moveAndSetAtRuleStatement(&tBlockElement,
								&tAtRuleStatement);
					}
					else if(tType == 2)
					{
						Crx_C_CrxCss_AtRuleElement tAtRuleElement /*= ?*/;

						crx_c_crxCss_atRuleElement_construct(&tAtRuleElement);

						crx_c_string_appendString(&(tAtRuleElement.gName), &tString);
						crx_c_string_appendString(&(tAtRuleElement.gValue), &tString2);

						crx_c_crxCss_parseBlock(pParserData, tAtRuleElement.gBlock);

						crx_c_crxCss_blockElement_moveAndSetAtRuleElement(&tBlockElement,
								&tAtRuleElement);
					}
					else
					{
						CRX_SCOPE_META
						assert(tType == 3);

						CRX_SCOPE
						Crx_C_CrxCss_AtRuleNameValueBlock tAtRuleNameValueBlock /*= ?*/;

						crx_c_crxCss_atRuleNameValueBlock_construct(&tAtRuleNameValueBlock);

						crx_c_string_appendString(&(tAtRuleNameValueBlock.gName), &tString);
						crx_c_string_appendString(&(tAtRuleNameValueBlock.gValue), &tString2);

						crx_c_crxCss_parseNameValueBlock(pParserData, &(tAtRuleNameValueBlock.gNameValueBlock));

						crx_c_crxCss_blockElement_moveAndSetAtRuleNameValueBlock(&tBlockElement,
								&tAtRuleNameValueBlock);
						CRX_SCOPE_END
					}

					if(!crx_c_crxCss_block_tryMoveAndPush(pBlock, &tBlockElement))
						{crx_c_crxCss_blockElement_destruct(&tBlockElement);}
				}
				else
					{crx_c_crxCss_pushErrorTraceToParserData(pParserData, 1, "Error: Unexpected end of input");}
			}
			else if(*(pParserData->gCurrentCharacter) != '}')
			{
				Crx_C_Arrays_StringSmall tStrings /*= ?*/;
				Crx_C_String tString /*= ?*/;
				Crx_C_CrxCss_BlockElement tBlockElement /*= ?*/;
				Crx_C_CrxCss_ReferenceNameValueBlock tReferenceNameValueBlock /*= ?*/;

				
				crx_c_arrays_stringSmall_construct(&tStrings, 0);
				crx_c_string_construct(&tString, 0);
				crx_c_crxCss_blockElement_construct(&tBlockElement);
				crx_c_crxCss_referenceNameValueBlock_construct(&tReferenceNameValueBlock);

				while(pParserData->gRemainingLength > 0)
				{
					if((*(pParserData->gCurrentCharacter) == '/') && 
							(pParserData->gRemainingLength > 1) && 
							(*(pParserData->gCurrentCharacter + 1) == '*'))
						{crx_c_crxCss_skipComment(pParserData);}
					else if((*(pParserData->gCurrentCharacter) == ',') ||
							(*(pParserData->gCurrentCharacter) == '{'))
					{
						bool tIsToBreak = (*(pParserData->gCurrentCharacter) == '{');

						if(!crx_c_arrays_stringSmall_tryMoveAndPush(&tStrings, &tString))
							{crx_c_string_destruct(&tString);}

						crx_c_string_construct(&tString, 0);
						
						pParserData->gRemainingLength = pParserData->gRemainingLength - 1;
						pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;
						
						if(tIsToBreak)
							{break;}
					}
					else if((*(pParserData->gCurrentCharacter) != '}') &&
							(*(pParserData->gCurrentCharacter) != ';'))
					{
						crx_c_string_appendChar(&tString, *(pParserData->gCurrentCharacter));

						pParserData->gRemainingLength = pParserData->gRemainingLength - 1;
						pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;
					}
					else
					{	
						crx_c_crxCss_pushErrorTraceToParserData(pParserData, 1, 
								"Error: Unexpected character while parsing reference");

						break;
					}
				}

				crx_c_crxCss_parseNameValueBlock(pParserData, &(tReferenceNameValueBlock.gNameValueBlock));
				crx_c_arrays_stringSmall_destruct(&(tReferenceNameValueBlock.gReferences));
				memcpy(&(tReferenceNameValueBlock.gReferences), &tStrings, 
						sizeof(Crx_C_Arrays_StringSmall));

				crx_c_crxCss_blockElement_moveAndSetReferenceNameValueBlock(&tBlockElement,
						&tReferenceNameValueBlock);
				if(!crx_c_crxCss_block_tryMoveAndPush(pBlock, &tBlockElement))
					{crx_c_crxCss_blockElement_destruct(&tBlockElement);}
				crx_c_arrays_stringSmall_destruct(&tStrings);
				crx_c_string_destruct(&tString);
			}
			else if(*(pParserData->gCurrentCharacter) == '}')
			{
				pParserData->gRemainingLength = pParserData->gRemainingLength - 1;
				pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;
						
				break;
			}
		}
	}
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_crxCss_parseNameValueBlock(
		Crx_C_CrxCss_ParserData * CRX_NOT_NULL pParserData, 
		Crx_C_CrxCss_NameValueBlock * CRX_NOT_NULL pNameValueBlock)
{
	if(pParserData->gRemainingLength > 0)
	{
		while(pParserData->gRemainingLength > 0)
		{
			if(*(pParserData->gCurrentCharacter) != '}')
			{
				Crx_C_CrxCss_NameValuePair tNameValuePair /*= ?*/;
				char tWasValueEncountred = false;

				crx_c_crxCss_nameValuePair_construct(&tNameValuePair);
				
				while(pParserData->gRemainingLength > 0)
				{
					if(CRX__C__CRXSS__IS_WHITE_SPACE(pParserData->gCurrentCharacter))
						{break;}
					else if((*(pParserData->gCurrentCharacter) == '/') && 
							(pParserData->gRemainingLength > 1) && 
							(*(pParserData->gCurrentCharacter + 1) == '*'))
						{crx_c_crxCss_skipComment(pParserData);}
					else if((*(pParserData->gCurrentCharacter) == ':') ||
							(*(pParserData->gCurrentCharacter) == ';'))
						{break;}
					else if((*(pParserData->gCurrentCharacter) != '{') &&
							(*(pParserData->gCurrentCharacter) != '}') &&
							(*(pParserData->gCurrentCharacter) != ',') &&
							(*(pParserData->gCurrentCharacter) != '@'))
					{
						crx_c_string_appendChar(&(tNameValuePair.gName), *(pParserData->gCurrentCharacter));

						pParserData->gRemainingLength = pParserData->gRemainingLength - 1;
						pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;
					}
					else
					{	
						crx_c_crxCss_pushErrorTraceToParserData(pParserData, 1, 
								"Error: Unexpected character while parsing name of nameValuePair");

						break;
					}
				}

				if(!pParserData->gIsError)
				{
					crx_c_crxCss_skipWhiteSpaceAndComment(pParserData);

					if(*(pParserData->gCurrentCharacter) == ':')
					{
						if(crx_c_string_getLength(&(tNameValuePair.gName)) > 0)
						{
							pParserData->gRemainingLength = pParserData->gRemainingLength - 1;
							pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;
							
							crx_c_crxCss_skipWhiteSpaceAndComment(pParserData);

							while(pParserData->gRemainingLength > 0)
							{
								if((*(pParserData->gCurrentCharacter) == '/') && 
										(pParserData->gRemainingLength > 1) && 
										(*(pParserData->gCurrentCharacter + 1) == '*'))
									{crx_c_crxCss_skipComment(pParserData);}
								else if(*(pParserData->gCurrentCharacter) == ';')
								{
									pParserData->gRemainingLength = pParserData->gRemainingLength - 1;
									pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;

									break;
								}
								else if((*(pParserData->gCurrentCharacter) != ':') &&
										(*(pParserData->gCurrentCharacter) != '{') &&
										(*(pParserData->gCurrentCharacter) != '}') &&
										(*(pParserData->gCurrentCharacter) != ':'))
								{
									crx_c_string_appendChar(&(tNameValuePair.gValue), *(pParserData->gCurrentCharacter));

									pParserData->gRemainingLength = pParserData->gRemainingLength - 1;
									pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;
								}
								else
								{
									crx_c_crxCss_pushErrorTraceToParserData(pParserData, 1, 
											"Error: Unexpected character while parsing value of nameValuePair");

									break;
								}
							}
						}
						else
						{
							crx_c_crxCss_pushErrorTraceToParserData(pParserData, 1, 
									"Error: Expected name from nameValuePair");
						}
					}
					else if(*(pParserData->gCurrentCharacter) == ';')
					{
						if(crx_c_string_getLength(&(tNameValuePair.gName)) == 0)
						{
							pParserData->gRemainingLength = pParserData->gRemainingLength - 1;
							pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;
						}
						else
						{
							crx_c_crxCss_pushErrorTraceToParserData(pParserData, 1, 
									"Error: Unexpected character while parsing name of nameValuePair");
						}
					}
					else
					{
						crx_c_crxCss_pushErrorTraceToParserData(pParserData, 1, 
								"Error: Expected ':' while parsing name of nameValuePair");
					}
				}

				if((!pParserData->gIsError) &&
						(crx_c_string_getLength(&(tNameValuePair.gName)) > 0))
				{
					if(!crx_c_crxCss_nameValueBlock_tryMoveAndPush(pNameValueBlock, &tNameValuePair))
						{crx_c_crxCss_nameValuePair_destruct(&tNameValuePair);}
				}
				else
				{
					crx_c_crxCss_nameValuePair_destruct(&tNameValuePair);
					
					break;
				}
			}
			else
			{
				pParserData->gRemainingLength = pParserData->gRemainingLength - 1;
				pParserData->gCurrentCharacter = pParserData->gCurrentCharacter + 1;

				break;
			}
		}
	}
}



//

#undef CRX__C__CRX_CSS__PRIVATE__SIZE08_T
#undef CRX__C__CRX_CSS__PRIVATE__SIZE08_MAX
#undef CRX__C__CRX_CSS__PRIVATE__SIZE16_T
#undef CRX__C__CRX_CSS__PRIVATE__SIZE16_MAX
#undef CRX__C__CRX_CSS__PRIVATE__SIZE32_T
#undef CRX__C__CRX_CSS__PRIVATE__SIZE32_MAX



CRX__LIB__C_CODE_END()

