//WARNING: NEVER INCLUDE THIS FILE DIRECTLY EXCEPT IN THE CORRESPONDING .c FILE.
//<<START>>	IMPORTANT: FIRST INCLUDE THE CORRESPONDING ".h" FILE
//			INCLUDE ".h" OF C NON CRXed CODE THAT THIS HEADER NEEDS.
//			INCLUDE ".h", NOT ".c.h", OF C CRXed CODE.
#include "Crx/H/crx/c/Tree.h"
//<<END>>

CRX__LIB__C_CODE_BEGIN()


/*WITHOUT INDEX, PRIMARY ENTRIES EVERYWHERE*/
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		size_t pCountOfMidElementInNode)
{
	crx_c_tree_private_construct(pThis, pTypeBluePrint__element, NULL, 
			pOptions & (CRX__C__TREE__FLAG__PERSISTANT |
					CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
					CRX__C__TREE__FLAG__PREEMPTIVE |
					CRX__C__TREE__FLAG__USES_RINGS), 
			pFunc_getOrderOfElements, NULL, NULL, pCountOfMidElementInNode);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct2(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		size_t pDesiredNumberOfElementsPerNode)
{
	crx_c_tree_private_construct2(pThis, pTypeBluePrint__element, NULL, 
			pOptions & (CRX__C__TREE__FLAG__PERSISTANT |
					CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
					CRX__C__TREE__FLAG__PREEMPTIVE |
					CRX__C__TREE__FLAG__USES_RINGS), 
			pFunc_getOrderOfElements, NULL, NULL, pDesiredNumberOfElementsPerNode);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct3(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		size_t pDesiredByteSizeOfNode, bool pIsToBaseOnLeafNode)
{
	crx_c_tree_private_construct3(pThis, pTypeBluePrint__element, NULL, 
			pOptions & (CRX__C__TREE__FLAG__PERSISTANT |
					CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
					CRX__C__TREE__FLAG__PREEMPTIVE |
					CRX__C__TREE__FLAG__USES_RINGS), 
			pFunc_getOrderOfElements, NULL, NULL, pDesiredByteSizeOfNode, pIsToBaseOnLeafNode);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct4(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		size_t pDesiredByteSizeOfHotRegionInNode)
{
	crx_c_tree_private_construct4(pThis, pTypeBluePrint__element, NULL, 
			pOptions & (CRX__C__TREE__FLAG__PERSISTANT |
					CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
					CRX__C__TREE__FLAG__PREEMPTIVE |
					CRX__C__TREE__FLAG__USES_RINGS), 
			pFunc_getOrderOfElements, NULL, NULL, pDesiredByteSizeOfHotRegionInNode);
}

/*WITHOUT INDEX, PRIMARY ENTRIES IN LEAVES ONLY. ELEMENT MUST BE COPYABLE*/
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct5(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		size_t pCountOfMidElementInNode)
{
	assert(pTypeBluePrint__element->gIS_COPYABLE);

	crx_c_tree_private_construct(pThis, pTypeBluePrint__element, NULL, 
			pOptions & (CRX__C__TREE__FLAG__USES_DELEGATION |
					CRX__C__TREE__FLAG__PERSISTANT |
					CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
					CRX__C__TREE__FLAG__PREEMPTIVE |
					CRX__C__TREE__FLAG__USES_RINGS), 
			pFunc_getOrderOfElements, NULL, NULL, pCountOfMidElementInNode);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct6(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		size_t pDesiredNumberOfElementsPerNode)
{
	assert(pTypeBluePrint__element->gIS_COPYABLE);

	crx_c_tree_private_construct2(pThis, pTypeBluePrint__element, NULL, 
			pOptions & (CRX__C__TREE__FLAG__USES_DELEGATION |
					CRX__C__TREE__FLAG__PERSISTANT |
					CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
					CRX__C__TREE__FLAG__PREEMPTIVE |
					CRX__C__TREE__FLAG__USES_RINGS), 
			pFunc_getOrderOfElements, NULL, NULL, pDesiredNumberOfElementsPerNode);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct7(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		size_t pDesiredByteSizeOfNode, bool pIsToBaseOnLeafNode)
{
	assert(pTypeBluePrint__element->gIS_COPYABLE);

	crx_c_tree_private_construct3(pThis, pTypeBluePrint__element, NULL, 
			pOptions & (CRX__C__TREE__FLAG__USES_DELEGATION |
					CRX__C__TREE__FLAG__PERSISTANT |
					CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
					CRX__C__TREE__FLAG__PREEMPTIVE |
					CRX__C__TREE__FLAG__USES_RINGS), 
			pFunc_getOrderOfElements, NULL, NULL, pDesiredByteSizeOfNode, pIsToBaseOnLeafNode);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct8(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		size_t pDesiredByteSizeOfHotRegionInNode)
{
	assert(pTypeBluePrint__element->gIS_COPYABLE);

	crx_c_tree_private_construct4(pThis, pTypeBluePrint__element, NULL, 
			pOptions & (CRX__C__TREE__FLAG__USES_DELEGATION |
					CRX__C__TREE__FLAG__PERSISTANT |
					CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
					CRX__C__TREE__FLAG__PREEMPTIVE |
					CRX__C__TREE__FLAG__USES_RINGS), 
			pFunc_getOrderOfElements, NULL, NULL, pDesiredByteSizeOfHotRegionInNode);
}

/*WITHOUT INDEX, PRIMARY ENTRIES IN LEAVES ONLY. ELEMENT MUST BE NON COPYABLE*/
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct9(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		size_t pCountOfMidElementInNode)
{
	assert(!(pTypeBluePrint__element->gIS_COPYABLE));

	crx_c_tree_private_construct(pThis, pTypeBluePrint__element, NULL, 
			(pOptions & (CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
							CRX__C__TREE__FLAG__PREEMPTIVE | 
							CRX__C__TREE__FLAG__USES_RINGS)) | 
					(CRX__C__TREE__FLAG__USES_DELEGATION | CRX__C__TREE__FLAG__PERSISTANT), 
			pFunc_getOrderOfElements, NULL, NULL, pCountOfMidElementInNode);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct10(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		size_t pDesiredNumberOfElementsPerNode)
{
	assert(!(pTypeBluePrint__element->gIS_COPYABLE));

	crx_c_tree_private_construct2(pThis, pTypeBluePrint__element, NULL, 
			(pOptions & (CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
							CRX__C__TREE__FLAG__PREEMPTIVE | 
							CRX__C__TREE__FLAG__USES_RINGS)) | 
					(CRX__C__TREE__FLAG__USES_DELEGATION | CRX__C__TREE__FLAG__PERSISTANT), 
			pFunc_getOrderOfElements, NULL, NULL, pDesiredNumberOfElementsPerNode);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct11(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		size_t pDesiredByteSizeOfNode, bool pIsToBaseOnLeafNode)
{
	assert(!(pTypeBluePrint__element->gIS_COPYABLE));

	crx_c_tree_private_construct3(pThis, pTypeBluePrint__element, NULL, 
			(pOptions & (CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
							CRX__C__TREE__FLAG__PREEMPTIVE | 
							CRX__C__TREE__FLAG__USES_RINGS)) | 
					(CRX__C__TREE__FLAG__USES_DELEGATION | CRX__C__TREE__FLAG__PERSISTANT), 
			pFunc_getOrderOfElements, NULL, NULL, pDesiredByteSizeOfNode, pIsToBaseOnLeafNode);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct12(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		size_t pDesiredByteSizeOfHotRegionInNode)
{
	assert(!(pTypeBluePrint__element->gIS_COPYABLE));

	crx_c_tree_private_construct4(pThis, pTypeBluePrint__element, NULL, 
			(pOptions & (CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
							CRX__C__TREE__FLAG__PREEMPTIVE | 
							CRX__C__TREE__FLAG__USES_RINGS)) | 
					(CRX__C__TREE__FLAG__USES_DELEGATION | CRX__C__TREE__FLAG__PERSISTANT), 
			pFunc_getOrderOfElements, NULL, NULL, pDesiredByteSizeOfHotRegionInNode);
}

/*WITH INDEX*/
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct13(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__index, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfIndices, 
		Crx_C_Tree_ConstructIndexFrom CRX_NOT_NULL pFunc_constructIndexFrom,
		size_t pCountOfMidElementInNode)
{
	crx_c_tree_private_construct(pThis, pTypeBluePrint__element, pTypeBluePrint__index, 
			pOptions & (CRX__C__TREE__FLAG__INDICES_IN_INTERNAL_NODES_ONLY |
					CRX__C__TREE__FLAG__ELEMENT_DATA_IN_LEAVES_ONLY |
					CRX__C__TREE__FLAG__USES_DELEGATION |
					CRX__C__TREE__FLAG__PERSISTANT |
					CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
					CRX__C__TREE__FLAG__PREEMPTIVE |
					CRX__C__TREE__FLAG__USES_RINGS), 
			pFunc_getOrderOfElements, pFunc_getOrderOfIndices, pFunc_constructIndexFrom,
			pCountOfMidElementInNode);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct14(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__index, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfIndices, 
		Crx_C_Tree_ConstructIndexFrom CRX_NOT_NULL pFunc_constructIndexFrom,
		size_t pDesiredNumberOfElementsPerNode)
{
	crx_c_tree_private_construct2(pThis, pTypeBluePrint__element, pTypeBluePrint__index, 
			pOptions & (CRX__C__TREE__FLAG__INDICES_IN_INTERNAL_NODES_ONLY |
					CRX__C__TREE__FLAG__ELEMENT_DATA_IN_LEAVES_ONLY |
					CRX__C__TREE__FLAG__USES_DELEGATION |
					CRX__C__TREE__FLAG__PERSISTANT |
					CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
					CRX__C__TREE__FLAG__PREEMPTIVE |
					CRX__C__TREE__FLAG__USES_RINGS), 
			pFunc_getOrderOfElements, pFunc_getOrderOfIndices, pFunc_constructIndexFrom,
			pDesiredNumberOfElementsPerNode);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct15(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__index, uint32_t 
		pOptions, Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfIndices, 
		Crx_C_Tree_ConstructIndexFrom CRX_NOT_NULL pFunc_constructIndexFrom,
		size_t pDesiredByteSizeOfNode, bool pIsToBaseOnLeafNode)
{
	crx_c_tree_private_construct3(pThis, pTypeBluePrint__element, pTypeBluePrint__index, 
			pOptions & (CRX__C__TREE__FLAG__INDICES_IN_INTERNAL_NODES_ONLY |
					CRX__C__TREE__FLAG__ELEMENT_DATA_IN_LEAVES_ONLY |
					CRX__C__TREE__FLAG__USES_DELEGATION |
					CRX__C__TREE__FLAG__PERSISTANT |
					CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
					CRX__C__TREE__FLAG__PREEMPTIVE |
					CRX__C__TREE__FLAG__USES_RINGS), 
			pFunc_getOrderOfElements, pFunc_getOrderOfIndices, pFunc_constructIndexFrom,
			pDesiredByteSizeOfNode, pIsToBaseOnLeafNode);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_construct16(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__index, uint32_t pOptions, 
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfIndices, 
		Crx_C_Tree_ConstructIndexFrom CRX_NOT_NULL pFunc_constructIndexFrom,
		size_t pDesiredByteSizeOfHotRegionInNode)
{
	crx_c_tree_private_construct4(pThis, pTypeBluePrint__element, pTypeBluePrint__index, 
			pOptions & (CRX__C__TREE__FLAG__INDICES_IN_INTERNAL_NODES_ONLY |
					CRX__C__TREE__FLAG__ELEMENT_DATA_IN_LEAVES_ONLY |
					CRX__C__TREE__FLAG__USES_DELEGATION |
					CRX__C__TREE__FLAG__PERSISTANT |
					CRX__C__TREE__FLAG__CONSERVATIVE_IN_GROWTH |
					CRX__C__TREE__FLAG__PREEMPTIVE |
					CRX__C__TREE__FLAG__USES_RINGS), 
			pFunc_getOrderOfElements, pFunc_getOrderOfIndices, pFunc_constructIndexFrom,
			pDesiredByteSizeOfHotRegionInNode);
}


CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_private_construct(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element,
		Crx_C_TypeBluePrint const * pTypeBluePrint__index,
		uint32_t pOptions,
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		Crx_C_TypeBluePrint_GetOrderOfObjects pFunc_getOrderOfIndices,
		Crx_C_Tree_ConstructIndexFrom pFunc_constructIndexFrom,
		size_t pCountOfMidElementInNode)
{
	CRX_SCOPE_META
	assert((pTypeBluePrint__index == NULL) || (pFunc_getOrderOfIndices != NULL));
	assert((pTypeBluePrint__index == NULL) || (pTypeBluePrint__index->gIS_COPYABLE && !(
			(pTypeBluePrint__index->gFUNC__DESTRUCT != NULL) || 
			(pTypeBluePrint__index->gFUNC__COPY_CONSTRUCT != NULL))));
	assert(!(CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY3(pOptions) && 
					(pTypeBluePrint__index == NULL) &&
			!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT3(pOptions) && 
			(!(pTypeBluePrint__element->gIS_COPYABLE))));
	assert(!(CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY3(pOptions) && 
			(pTypeBluePrint__index == NULL) &&
			CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT3(pOptions) &&
			!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION3(pOptions) &&
			(!(pTypeBluePrint__element->gIS_COPYABLE))));

	CRX_SCOPE
	size_t vCountOfMidElementInNode = pCountOfMidElementInNode;
	size_t vNumberOfElementsPerNode = 0;
	Crx_C_Tree_Private_InternalNode vInternalNode /*= ?*/;
	Crx_C_Tree_Private_LeafNode vLeafNode /*= ?*/;
	Crx_C_Tree_Private_LeafNode * vLeafNode__2 = NULL;

	pThis->gPrivate_typeBluePrint__element = pTypeBluePrint__element;
	pThis->gPrivate_typeBluePrint__index = pTypeBluePrint__index;
	pThis->gPrivate_info = pOptions;
	pThis->gPrivate_getOrderOfElements = pFunc_getOrderOfElements;
	pThis->gPrivate_getOrderOfIndices = pFunc_getOrderOfIndices;
	pThis->gPrivate_constructIndexFrom = pFunc_constructIndexFrom;

	/*SEE THE ELEMENT REMOVING FUNCTIONS*/
	if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY || CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE ||
			!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
	{
		if(vCountOfMidElementInNode < 2)
			{vCountOfMidElementInNode = 2;}
	}
	else
	{
		if(vCountOfMidElementInNode < 3)
			{vCountOfMidElementInNode = 3;}
	}

	/*NUMBER OF CHILD NODES PER NODE IS vNumberOfElementsPerNode + 1. IF USING RINGS, AN
			EMPTY SPACE IS ADDED AT THE END FOR THE INDICES AND ELEMENTS, BUT THE EFFECTIVE
			CAPACITY REMAINS THE SAME, MEANING THE LAST SPACE IS NEVER USED.*/
	if(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS)
	{
		size_t tCountOfMidKeyInNode = 2;

		while(tCountOfMidKeyInNode < vCountOfMidElementInNode)
			{tCountOfMidKeyInNode = (tCountOfMidKeyInNode << 1);}

		vCountOfMidElementInNode = tCountOfMidKeyInNode;

		/*THE CAPACITY LIMIT IS 1/3 OF MAXIMUM(UINT32_MAX/2) BECAUSE OF ONE OF THE RING 
				ALGORITHMS EMPLOYED, BUT USING 1/4 TO KEEP THE CALCULATION SIMPLE */
		if(vCountOfMidElementInNode > (UINT32_MAX >> 4))
			{vCountOfMidElementInNode = (UINT32_MAX >> 4);}
	}
	else
	{
		if(vCountOfMidElementInNode > (UINT32_MAX >> 2))
			{vCountOfMidElementInNode = (UINT32_MAX >> 2);}
	}

	vNumberOfElementsPerNode = (2 * vCountOfMidElementInNode) - 1;

	pThis->gPrviate_countOfMidElementInNode = vCountOfMidElementInNode;

	if(!CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
	{
		pThis->gPrivate_internalNode_byteOffsetToChildNodes =
				CRX__TREE__PRIVATE__ROUND_TO_POINTER_ALIGNMENT(
				(((volatile void const *)&(vInternalNode.gPrivate_buffer)) -
				((volatile void const *)&vInternalNode)) +
				((vNumberOfElementsPerNode + (CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? 1 : 0)) *
				(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) :
						pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE)));
				
		pThis->gPrivate_internalNode_byteLength =
				pThis->gPrivate_internalNode_byteOffsetToChildNodes +
				((vNumberOfElementsPerNode + 1) *
				sizeof(volatile void const *));

		pThis->gPrivate_leafNode_byteLength =
				(((volatile void const *)&(vLeafNode.gPrivate_buffer)) -
				((volatile void const *)&vLeafNode)) +
				((vNumberOfElementsPerNode + (CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? 1 : 0)) *
				(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
				pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
	}
	else
	{
		pThis->gPrivate_internalNode_byteOffsetToChildNodes =
				CRX__TREE__PRIVATE__ROUND_TO_POINTER_ALIGNMENT(
				(((volatile void const *)&(vInternalNode.gPrivate_buffer)) -
				((volatile void const *)&vInternalNode)) +
				((vNumberOfElementsPerNode + (CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? 1 : 0)) *
				pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE));

		if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
		{
			pThis->gPrivate_internalNode_byteOffsetToElementData = 
					pThis->gPrivate_internalNode_byteOffsetToChildNodes +
					((vNumberOfElementsPerNode + 1) *
					sizeof(volatile void const *));

			if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				pThis->gPrivate_internalNode_byteOffsetToElementData =
						CRX__TREE__PRIVATE__ROUND_TO_POINTER_ALIGNMENT(
						pThis->gPrivate_internalNode_byteOffsetToElementData);
			}
			else
			{
				pThis->gPrivate_internalNode_byteOffsetToElementData =
						CRX__TREE__PRIVATE__ROUND_TO_GENERAL_ALIGNMENT(
						pThis->gPrivate_internalNode_byteOffsetToElementData);
			}

			pThis->gPrivate_internalNode_byteLength =
					pThis->gPrivate_internalNode_byteOffsetToElementData +
					((vNumberOfElementsPerNode + (CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? 1 : 0)) *
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
		}
		else
		{
			pThis->gPrivate_internalNode_byteLength =
					pThis->gPrivate_internalNode_byteOffsetToChildNodes +
					((vNumberOfElementsPerNode + 1) *
					sizeof(volatile void const *));
		}

		if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
		{
			pThis->gPrivate_leafNode_byteOffsetToElementData =
					(((volatile void const *)&(vLeafNode.gPrivate_buffer)) -
					((volatile void const *)&vLeafNode)) +
					((vNumberOfElementsPerNode + (CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? 1 : 0)) *
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);

			if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				pThis->gPrivate_leafNode_byteOffsetToElementData =
						CRX__TREE__PRIVATE__ROUND_TO_POINTER_ALIGNMENT(
						pThis->gPrivate_leafNode_byteOffsetToElementData);
			}
			else
			{
				pThis->gPrivate_leafNode_byteOffsetToElementData =
						CRX__TREE__PRIVATE__ROUND_TO_GENERAL_ALIGNMENT(
						pThis->gPrivate_leafNode_byteOffsetToElementData);
			}

			pThis->gPrivate_leafNode_byteLength =
					pThis->gPrivate_leafNode_byteOffsetToElementData +
					((vNumberOfElementsPerNode + (CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? 1 : 0)) *
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
		}
		else
		{
			pThis->gPrivate_leafNode_byteLength =
					(((volatile void const *)&(vLeafNode.gPrivate_buffer)) -
					((volatile void const *)&vLeafNode)) +
					((vNumberOfElementsPerNode + (CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? 1 : 0)) *
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
		}
	}

	vLeafNode__2 = (Crx_C_Tree_Private_LeafNode *)calloc(1,
			pThis->gPrivate_leafNode_byteLength);

	if(vLeafNode__2 != NULL)
	{
		pThis->gPrivate_node__root = &(vLeafNode__2->gPrivate_node);
		pThis->gPrivate_numberOfNodes = 1;
	}
	else
	{
		pThis->gPrivate_node__root = NULL;
		pThis->gPrivate_numberOfNodes = 0;
	}

	pThis->gPrivate_numberOfElements = 0;

	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_private_construct2(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element,
		Crx_C_TypeBluePrint const * pTypeBluePrint__index,
		uint32_t pOptions,
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		Crx_C_TypeBluePrint_GetOrderOfObjects pFunc_getOrderOfIndices,
		Crx_C_Tree_ConstructIndexFrom pFunc_constructIndexFrom,
		size_t pDesiredNumberOfElementsPerNode)
{
	if(pDesiredNumberOfElementsPerNode >= (UINT32_MAX >> 1))
	{
		crx_c_tree_private_construct(pThis, 
				pTypeBluePrint__element, pTypeBluePrint__index, pOptions, 
				pFunc_getOrderOfElements, pFunc_getOrderOfIndices, pFunc_constructIndexFrom,
				(UINT32_MAX >> 2));
	}
	else
	{
		crx_c_tree_private_construct(pThis,
				pTypeBluePrint__element, pTypeBluePrint__index, pOptions, 
				pFunc_getOrderOfElements, pFunc_getOrderOfIndices, pFunc_constructIndexFrom,
				((pDesiredNumberOfElementsPerNode + 2) >> 1));
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_private_construct3(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element,
		Crx_C_TypeBluePrint const * pTypeBluePrint__index,
		uint32_t pOptions,
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		Crx_C_TypeBluePrint_GetOrderOfObjects pFunc_getOrderOfIndices,
		Crx_C_Tree_ConstructIndexFrom pFunc_constructIndexFrom,
		size_t pDesiredByteSizeOfNode, bool pIsToBaseOnLeafNode)
{
	double vNumberOfElementsPerNode = 0;
	
	pThis->gPrivate_info = pOptions;

	if(!pIsToBaseOnLeafNode)
	{
		Crx_C_Tree_Private_InternalNode tInternalNode /*= ?*/;

		if(pTypeBluePrint__index != NULL)
		{
			vNumberOfElementsPerNode = ((pDesiredByteSizeOfNode -
							(((volatile void const *)&(tInternalNode.gPrivate_buffer)) + 1 -
									((volatile void const *)&tInternalNode)) -
							(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ?
									(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE) : 0) -
							CRX__TREE__PRIVATE__MAXIMUM_PADDING_BECAUSE_OF_POINTER -
							sizeof(volatile void const *)) /
					((CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE) +
							sizeof(volatile void const *)));
		}
		else
		{
			if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
			{
				vNumberOfElementsPerNode = (pDesiredByteSizeOfNode -
								(((volatile void const *)&(tInternalNode.gPrivate_buffer)) + 1 -
										((volatile void const *)&tInternalNode)) - 
								(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? 
										pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE : 0) -
								CRX__TREE__PRIVATE__MAXIMUM_PADDING_BECAUSE_OF_POINTER -
								sizeof(volatile void const *) -
								(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ?
										CRX__TREE__PRIVATE__MAXIMUM_PADDING_BECAUSE_OF_POINTER :
										CRX__TREE__PRIVATE__MAXIMUM_PADDING_BECAUSE_OF_GENERAL_ALIGNMENT) -
								(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ?
										(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(
										volatile void const *) : 
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE) : 0)) /
						(pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE +
								sizeof(volatile void const *) +
								(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
			}
			else
			{
				vNumberOfElementsPerNode = ((pDesiredByteSizeOfNode -
								(((volatile void const *)&(tInternalNode.gPrivate_buffer)) + 1 -
										((volatile void const *)&tInternalNode)) -
								(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? 
										pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE : 0) -
								CRX__TREE__PRIVATE__MAXIMUM_PADDING_BECAUSE_OF_POINTER -
								sizeof(volatile void const *)) /
						(pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE + 
								sizeof(volatile void const *)));
			}
		}
	}
	else
	{
		Crx_C_Tree_Private_LeafNode tLeafNode /*= ?*/;

		if((pTypeBluePrint__index == NULL) || 
				!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
		{
			vNumberOfElementsPerNode = ((pDesiredByteSizeOfNode -
							(((volatile void const *)&(tLeafNode.gPrivate_buffer)) + 1 -
									((volatile void const *)&tLeafNode)) -
							(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ?
									(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? 
									sizeof(volatile void const *) : 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE) : 0)) /
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
		}
		else
		{
			vNumberOfElementsPerNode = ((pDesiredByteSizeOfNode -
							(((volatile void const *)&(tLeafNode.gPrivate_buffer)) + 1 -
									((volatile void const *)&tLeafNode)) -
							(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ?
									pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE : 0) -
							(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ?
									CRX__TREE__PRIVATE__MAXIMUM_PADDING_BECAUSE_OF_POINTER :
									CRX__TREE__PRIVATE__MAXIMUM_PADDING_BECAUSE_OF_GENERAL_ALIGNMENT) -
							(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ?
									(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? 
									sizeof(volatile void const *) : 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE) : 0)) /
					(pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE +
							(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE)));
		}
	}

	if(vNumberOfElementsPerNode < 3.0)
	{
		crx_c_tree_private_construct(pThis, 
				pTypeBluePrint__element, pTypeBluePrint__index, pOptions, 
				pFunc_getOrderOfElements, pFunc_getOrderOfIndices, pFunc_constructIndexFrom,
				2);
	}
	else
	{
		if(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS)
		{
			size_t tCountOfMidKeyInNode = 2;

			while(((tCountOfMidKeyInNode * 2) - 1) <= vNumberOfElementsPerNode)
				{tCountOfMidKeyInNode = (tCountOfMidKeyInNode << 1);}

			if((tCountOfMidKeyInNode > 2) &&
					((tCountOfMidKeyInNode * 2 - 1) != vNumberOfElementsPerNode))
				{tCountOfMidKeyInNode = tCountOfMidKeyInNode - 1;}

			crx_c_tree_private_construct(pThis, 
					pTypeBluePrint__element, pTypeBluePrint__index, pOptions, 
					pFunc_getOrderOfElements, pFunc_getOrderOfIndices, pFunc_constructIndexFrom,
					tCountOfMidKeyInNode);
		}
		else
		{
			crx_c_tree_private_construct(pThis,
					pTypeBluePrint__element, pTypeBluePrint__index, pOptions, 
					pFunc_getOrderOfElements, pFunc_getOrderOfIndices, pFunc_constructIndexFrom,
					(((uint32_t)vNumberOfElementsPerNode + 1) >> 1));
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_private_construct4(Crx_C_Tree * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint__element,
		Crx_C_TypeBluePrint const * pTypeBluePrint__index,
		uint32_t pOptions,
		Crx_C_TypeBluePrint_GetOrderOfObjects CRX_NOT_NULL pFunc_getOrderOfElements,
		Crx_C_TypeBluePrint_GetOrderOfObjects pFunc_getOrderOfIndices,
		Crx_C_Tree_ConstructIndexFrom pFunc_constructIndexFrom,
		size_t pDesiredByteSizeOfHotRegionInNode)
{
	double vNumberOfElementsPerNode = 0;

	pThis->gPrivate_info = pOptions;

	if(((pTypeBluePrint__index == NULL) || 
					!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY) ?
			!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY :
			(pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE >= 
					((CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
					pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE) + 
					(CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY ?
					2 * sizeof(volatile void const *) : 0))))
	{
		Crx_C_Tree_Private_InternalNode tInternalNode /*= ?*/;
		Crx_C_Tree_Private_LeafNode tLeafNode /*= ?*/;

		if(pTypeBluePrint__index == NULL)
		{
			vNumberOfElementsPerNode = ((pDesiredByteSizeOfHotRegionInNode -
							(((volatile void const *)&(tInternalNode.gPrivate_buffer)) + 1 -
									((volatile void const *)&tInternalNode)) -
							(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ?
									(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? 
									sizeof(volatile void const *) : 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE) : 0)) /
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
		}
		else
		{
			vNumberOfElementsPerNode = ((pDesiredByteSizeOfHotRegionInNode -
							(((volatile void const *)&(tInternalNode.gPrivate_buffer)) + 1 -
									((volatile void const *)&tInternalNode)) -
							(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? 
									pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE : 0)) /
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
		}

		if(vNumberOfElementsPerNode > 0)
		{
			double tNumberOfElementsPerNode = 0;

			if((pTypeBluePrint__index == NULL) || 
					!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
			{
				tNumberOfElementsPerNode = ((pDesiredByteSizeOfHotRegionInNode -
								(((volatile void const *)&(tLeafNode.gPrivate_buffer)) + 1 -
										((volatile void const *)&tLeafNode)) -
								(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ?
										(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? 
										sizeof(volatile void const *) : 
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE) : 0)) /
						(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
								pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
			}
			else
			{
				tNumberOfElementsPerNode = ((pDesiredByteSizeOfHotRegionInNode -
								(((volatile void const *)&(tLeafNode.gPrivate_buffer)) + 1 -
										((volatile void const *)&tLeafNode)) -
								(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? 
										pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE : 0)) /
						pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
			}

			if(vNumberOfElementsPerNode > tNumberOfElementsPerNode)
				{vNumberOfElementsPerNode = tNumberOfElementsPerNode;}
		}
	}
	else
	{
		Crx_C_Tree_Private_LeafNode tLeafNode /*= ?*/;

		if((pTypeBluePrint__index == NULL) || 
				!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
		{
			vNumberOfElementsPerNode = ((pDesiredByteSizeOfHotRegionInNode -
							(((volatile void const *)&(tLeafNode.gPrivate_buffer)) + 1 -
									((volatile void const *)&tLeafNode)) -
							(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ?
									(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? 
									sizeof(volatile void const *) : 
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE) : 0)) /
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
		}
		else
		{
			vNumberOfElementsPerNode = ((pDesiredByteSizeOfHotRegionInNode -
							(((volatile void const *)&(tLeafNode.gPrivate_buffer)) + 1 -
									((volatile void const *)&tLeafNode)) -
							(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? 
									pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE : 0)) /
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
		}
	}

	if(vNumberOfElementsPerNode < 3.0)
	{
		crx_c_tree_private_construct(pThis, 
				pTypeBluePrint__element, pTypeBluePrint__index, pOptions, 
				pFunc_getOrderOfElements, pFunc_getOrderOfIndices, pFunc_constructIndexFrom,
				2);
	}
	else
	{
		crx_c_tree_private_construct(pThis,
				pTypeBluePrint__element, pTypeBluePrint__index, pOptions, 
				pFunc_getOrderOfElements, pFunc_getOrderOfIndices, pFunc_constructIndexFrom,
				(((uint32_t)vNumberOfElementsPerNode) >> 1));
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_copyConstruct(Crx_C_Tree * pThis,
		Crx_C_Tree const * CRX_NOT_NULL pTree)
{
	CRX_SCOPE_META
	if(!pTree->gPrivate_typeBluePrint__element->gIS_COPYABLE)
		{abort();}

	CRX_SCOPE
	uint32_t vTypeOfRootNode = ((pTree->gPrivate_node__root != NULL) ?
			pTree->gPrivate_node__root->gPrivate_type : 0);

	
	pThis->gPrivate_typeBluePrint__element = pTree->gPrivate_typeBluePrint__element;
	pThis->gPrivate_typeBluePrint__index = pTree->gPrivate_typeBluePrint__index;
	pThis->gPrivate_info = pTree->gPrivate_info;
	pThis->gPrivate_getOrderOfElements = pTree->gPrivate_getOrderOfElements;
	pThis->gPrivate_getOrderOfIndices = pTree->gPrivate_getOrderOfIndices;
	pThis->gPrivate_constructIndexFrom = pTree->gPrivate_constructIndexFrom;

	pThis->gPrivate_node__root = (Crx_C_Tree_Private_Node *)calloc(1,
			((vTypeOfRootNode != 0) ? pTree->gPrivate_internalNode_byteLength :
			pTree->gPrivate_leafNode_byteLength));
	pThis->gPrivate_internalNode_byteOffsetToChildNodes =
			pTree->gPrivate_internalNode_byteOffsetToChildNodes;

	pThis->gPrivate_internalNode_byteOffsetToElementData =
			pTree->gPrivate_internalNode_byteOffsetToElementData;
	pThis->gPrivate_leafNode_byteOffsetToElementData =
			pTree->gPrivate_leafNode_byteOffsetToElementData;

	pThis->gPrivate_internalNode_byteLength = pTree->gPrivate_internalNode_byteLength;
	pThis->gPrivate_leafNode_byteLength = pTree->gPrivate_leafNode_byteLength;
	pThis->gPrviate_countOfMidElementInNode = pTree->gPrviate_countOfMidElementInNode;
	pThis->gPrivate_numberOfElements = 0;
	pThis->gPrivate_numberOfNodes = 0;

	if(pThis->gPrivate_node__root != NULL)
	{
		pThis->gPrivate_node__root->gPrivate_type = ((vTypeOfRootNode == 0) ? 0 : 1);
		pThis->gPrivate_node__root->gPrivate_numberOfEntries =
				pTree->gPrivate_node__root->gPrivate_numberOfEntries;
		pThis->gPrivate_node__root->gPrivate_node__parent = NULL;
		pThis->gPrivate_node__root->gPrivate_startIndex = 0;

		if(vTypeOfRootNode == 0)
		{
			((Crx_C_Tree_Private_LeafNode *)(pThis->gPrivate_node__root))->
					gPrivate_leafNode__prev = NULL;
			((Crx_C_Tree_Private_LeafNode *)(pThis->gPrivate_node__root))->
					gPrivate_leafNode__next = NULL;
		}

		if((CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT && !CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX &&
						CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY) ?
				crx_c_tree_private_copyConstruct__finishBuildingNode(
						pThis, pTree, pThis->gPrivate_node__root,
						pTree->gPrivate_node__root, NULL) :
				crx_c_tree_private_copyConstruct__finishBuildingNode(
						pThis, pTree, pThis->gPrivate_node__root,
						pTree->gPrivate_node__root, NULL))
		{
			pThis->gPrivate_numberOfElements = pTree->gPrivate_numberOfElements;
			pThis->gPrivate_numberOfNodes = pTree->gPrivate_numberOfNodes;
		}
		else
		{
			if(vTypeOfRootNode != 0)
			{
				free(pThis->gPrivate_node__root);
				pThis->gPrivate_node__root = (Crx_C_Tree_Private_Node *)calloc(1,
						pThis->gPrivate_leafNode_byteLength);
			}

			if(pThis->gPrivate_node__root != NULL)
			{
				pThis->gPrivate_node__root->gPrivate_type = 0;
				pThis->gPrivate_node__root->gPrivate_numberOfEntries = 0;
				pThis->gPrivate_node__root->gPrivate_node__parent = NULL;
				pThis->gPrivate_node__root->gPrivate_startIndex = 0;

				((Crx_C_Tree_Private_LeafNode *)(pThis->gPrivate_node__root))->
						gPrivate_leafNode__prev = NULL;
				((Crx_C_Tree_Private_LeafNode *)(pThis->gPrivate_node__root))->
						gPrivate_leafNode__next = NULL;

				pThis->gPrivate_numberOfNodes = 1;
			}
		}
	}
	CRX_SCOPE_END
}
CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_tree_private_copyConstruct__finishBuildingNode(
		Crx_C_Tree * pThis, Crx_C_Tree const * CRX_NOT_NULL pTree,
		Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode__target,
		Crx_C_Tree_Private_Node const * pNode__source,
		unsigned char * pElement__lastSeenNonFirstChildInTarget /*unsigned char * * */)
{
	CRX_SCOPE_META
	assert(pTree->gPrivate_typeBluePrint__element->gIS_COPYABLE);
	assert(!(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT && !CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX &&
			CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY && 
			CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION) ? 
			(pElement__lastSeenNonFirstChildInTarget == NULL) : true);

	CRX_SCOPE
	bool vIsNoError = true;

	if(pNode__source->gPrivate_type == 1)
	{
		/*WE ALWAYS NEED TO CLEANUP THE ELEMENTS IF THEY EXIST IN THE INTERNAL NODES AND THERE
				IS AN ERROR, BUT THERE IS NO DANGER OF FAILING WHILE CREATING THE ELEMENTS
				WHEN THE TREE IS NOT PERSISTANT. tIndexInElements IS ONLY REQUIRED WHEN THE
				DANGER EXISTS AND WE NEED TO DO THE CLEANUP AFTER AN ERROR. REMEMBER THAT WHEN
				THE TREE IS PERSISTANT AND DATA IS IN THE LEAVES ONLY, IF ELEMENTS ENTRIES
				EXIST IN THE INTERNAL NODES, WE DO NOT NEED TO CLEAN THEM UP. THE INTERNAL
				NODES WOULD BE HOLDING COPIES OF POINTERS TO ELEMENTS THEN, AND HENCE CLEANING
				IS INSTEAD LEFT FOR THE LEAVES TO DO.*/
		size_t tIndexInElements = 0;
		bool tAreChildNodesInternal = ((*(crx_c_tree_private_getChildNode(pTree, pNode__source,
				0)))->gPrivate_type == 1);

		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			crx_c_tree_private_copy(pThis,
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
					pThis->gPrivate_typeBluePrint__index->gFUNC__COPY_CONSTRUCT,
					crx_c_tree_private_getIndexFrom(pThis, pNode__target, 0),
					pNode__target, 0,
					crx_c_tree_private_getIndexFrom(pTree, pNode__source, 0),
					pNode__source, 0, pNode__source->gPrivate_numberOfEntries);
		}

		if(!CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX || !CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
		{
			if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				crx_c_tree_private_copy(pThis,
						pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE,
						pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT,
						crx_c_tree_private_getElementEntry(pThis, pNode__target, 0),
						pNode__target, 0,
						crx_c_tree_private_getElementEntry(pTree, pNode__source, 0),
						pNode__source, 0, pNode__source->gPrivate_numberOfEntries);
			}
			else
			{
				if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY ||
						!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
				{
					CRX_FOR(tIndexInElements = 0,
							tIndexInElements < pNode__source->gPrivate_numberOfEntries,
							tIndexInElements++)
					{
						unsigned char * tElement = ((unsigned char *)calloc(1, 
								pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));

						if(tElement != NULL)
						{
							if(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != 
									NULL)
							{
								(*(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT))(
										tElement, crx_c_tree_private_getElement(pTree,
										pNode__source, tIndexInElements));
							}
							else
							{
								memcpy(tElement, crx_c_tree_private_getElement(pTree,
										pNode__source, tIndexInElements),
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
							}

							*((unsigned char * *)crx_c_tree_private_getElementEntry(pThis,
									pNode__target, tIndexInElements)) = tElement;
						}
						else
						{
							vIsNoError = false;

							break;
						}
					}
					CRX_ENDFOR
				}
				else
				{
					/*THE FOLLOWING IS NOT REQUIRED. THE CODE CAN BE USEFUL FOR DEBUGGING IN THE
					FUTURE* /
					crx_c_tree_private_copy(pThis,
							sizeof(volatile void const *),
							NULL,
							crx_c_tree_private_getElementEntry(pThis,
									pNode__target, 0),
							pNode__target, 0,
							crx_c_tree_private_getElementEntry(pThis,
									pNode__source, 0),
							pNode__source, 0, pNode__source->gPrivate_numberOfEntries);
					*/
				}
			}
		}

		if(vIsNoError)
		{
			CRX_FOR(size_t tI = 0, tI <= pNode__source->gPrivate_numberOfEntries, tI++)
			{
				Crx_C_Tree_Private_Node * tNode /*= ?*/;

				if(tAreChildNodesInternal)
				{
					tNode = (Crx_C_Tree_Private_Node *)calloc(1,
							pThis->gPrivate_internalNode_byteLength);
				}
				else
				{
					tNode = (Crx_C_Tree_Private_Node *)calloc(1,
							pThis->gPrivate_leafNode_byteLength);

					if(tNode != NULL)
					{
						if(CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
						{
							if(tI != 0)
							{
								((Crx_C_Tree_Private_LeafNode *)tNode)->
										gPrivate_leafNode__prev =
										((Crx_C_Tree_Private_LeafNode *)
										(*(crx_c_tree_private_getChildNode(
										pThis, pNode__target, tI - 1))));
								((Crx_C_Tree_Private_LeafNode *)tNode)->
										gPrivate_leafNode__prev-> gPrivate_leafNode__next =
										((Crx_C_Tree_Private_LeafNode *)tNode);
							}
							else
							{
								((Crx_C_Tree_Private_LeafNode *)tNode)->
										gPrivate_leafNode__prev = NULL;
							}

							((Crx_C_Tree_Private_LeafNode *)tNode)->
									gPrivate_leafNode__next = NULL;
						}
					}
				}

				if(tNode != NULL)
				{
					tNode->gPrivate_type = 1;
					tNode->gPrivate_numberOfEntries = (*(crx_c_tree_private_getChildNode(
							pTree, pNode__source, tI)))->gPrivate_numberOfEntries;
					
					if(!CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
						{tNode->gPrivate_node__parent = pNode__target;}

					tNode->gPrivate_startIndex = 0;

					if((CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT && !CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX &&
									CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY &&
									CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION) ?
							crx_c_tree_private_copyConstruct__finishBuildingNode(
									pThis, pTree, tNode, *(crx_c_tree_private_getChildNode(
									pTree, pNode__source, tI)),
									((tI == 0) ? pElement__lastSeenNonFirstChildInTarget :
									crx_c_tree_private_getElementEntry(pThis,
									pNode__target, tI - 1))) :
							crx_c_tree_private_copyConstruct__finishBuildingNode(
									pThis, pTree, tNode, *(crx_c_tree_private_getChildNode(
									pTree, pNode__source, tI)), NULL))
					{
						*(crx_c_tree_private_getChildNode(pThis, pNode__target, tI)) =
								tNode;
					}
					else
					{
						free(tNode);
						tNode = NULL;
					}
				}

				if(tNode == NULL)
				{
					vIsNoError = false;

					CRX_FOR(size_t tI2 = 0, tI2 < tI, tI2++)
					{
						crx_c_tree_private_deleteNode(pThis,
								*(crx_c_tree_private_getChildNode(pThis, pNode__target, tI2)));
						/* *(crx_c_tree_private_getChildNode(pThis, pNode__target, tI2)) =
								NULL;*/
					}
					CRX_ENDFOR

					break;
				}
			}
			CRX_ENDFOR
		}

		if(!vIsNoError)
		{
			if(!CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX ||
					!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
			{
				if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
				{
					if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
					{
						CRX_FOR(size_t tI = 0,
								tI < pNode__target->gPrivate_numberOfEntries, tI++)
						{
							(*(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(
									crx_c_tree_private_getElement(pThis, pNode__target, tI));
						}
						CRX_ENDFOR
					}
				}
				else
				{
					if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY ||
							!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
					{
						CRX_FOR(size_t tI = 0, tI < tIndexInElements, tI++)
						{
							if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
							{
								(*(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(
										crx_c_tree_private_getElement(pThis, pNode__target, tI));
							}

							free(crx_c_tree_private_getElement(pThis, pNode__target, tI));
							/* *(crx_c_tree_private_getElementEntry(pThis,
									pNode__target, tI)) = NULL;*/
						}
						CRX_ENDFOR
					}
				}
			}

			pNode__target->gPrivate_numberOfEntries = 0;
		}
	}
	else
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX && 
				!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
		{
			crx_c_tree_private_copy(pThis,
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
					pThis->gPrivate_typeBluePrint__index->gFUNC__COPY_CONSTRUCT,
					crx_c_tree_private_getIndexFrom(pThis, pNode__target, 0),
					pNode__target, 0,
					crx_c_tree_private_getIndexFrom(pThis, pNode__source, 0),
					pNode__source, 0, pNode__source->gPrivate_numberOfEntries);
		}

		if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
		{
			crx_c_tree_private_copy(pThis,
					pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE,
					pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT,
					crx_c_tree_private_getElementEntry(pThis, pNode__target, 0),
					pNode__target, 0,
					crx_c_tree_private_getElementEntry(pTree, pNode__source, 0),
					pNode__source, 0, pNode__source->gPrivate_numberOfEntries);
		}
		else
		{
			CRX_FOR(size_t tI = 0,
					tI < pNode__source->gPrivate_numberOfEntries, tI++)
			{
				unsigned char * tElement = ((unsigned char *)calloc(1, 
						pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));

				if(tElement != NULL)
				{
					if(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != 
							NULL)
					{
						(*(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT))(tElement,
								crx_c_tree_private_getElement(pTree, pNode__source, tI));
					}
					else
					{
						memcpy(tElement, crx_c_tree_private_getElement(
								pTree, pNode__source, tI), 
								pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
					}

					*((unsigned char * *)crx_c_tree_private_getElementEntry(pThis, pNode__target, 
							tI)) = tElement;

					if(!CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX &&
							CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY &&
							CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
					{
						if(tI == 0)
						{
							if(pElement__lastSeenNonFirstChildInTarget != NULL)
							{
								*((unsigned char * *)pElement__lastSeenNonFirstChildInTarget) = 
										tElement;
							}
						}
					}
				}
				else
				{
					vIsNoError = false;

					CRX_FOR(size_t tI2 = 0, tI2 < tI, tI2++)
					{
						if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
						{
							(*(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(
									crx_c_tree_private_getElement(pThis, pNode__target, tI2));
						}

						free(crx_c_tree_private_getElement(pThis, pNode__target, tI2));
					}
					CRX_ENDFOR

					break;
				}
			}
			CRX_ENDFOR
		}
	}

	return vIsNoError;

	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_destruct(Crx_C_Tree * pThis)
{
	if(pThis->gPrivate_node__root != NULL)
		{crx_c_tree_private_deleteNode(pThis, pThis->gPrivate_node__root);}

	CRX__C__TYPE_BLUE_PRINT__GENERIC__FINALIZE(pThis->gPrivate_typeBluePrint__element);
	CRX__C__TYPE_BLUE_PRINT__GENERIC__FINALIZE(pThis->gPrivate_typeBluePrint__index);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_free(Crx_C_Tree * pThis)
	{free(pThis);}

CRX__C__TYPE_BLUE_PRINT__GENERIC__DEFINE_GET_BLUE_PRINT(
		Crx_C_Tree, crx_c_tree_,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__FALSE, CRXM__FALSE,
		true, true,
		pThis->gPrivate_typeBluePrint__element->gIS_COPYABLE, true,
		false, false);

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_deleteNode(
		Crx_C_Tree * pThis, Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode)
{
	if(pNode->gPrivate_type)
	{
		CRX_FOR(size_t tI = 0, tI <= pNode->gPrivate_numberOfEntries, tI++)
		{
			crx_c_tree_private_deleteNode(pThis,
					*(crx_c_tree_private_getChildNode(pThis, pNode, tI)));
		}
		CRX_ENDFOR

		if(!CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX ||
				!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
		{
			if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
				{
					CRX_FOR(size_t tI = 0, tI < pNode->gPrivate_numberOfEntries, tI++)
					{
						(*(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(
								crx_c_tree_private_getElement(pThis, pNode, tI));
					}
					CRX_ENDFOR
				}
			}
			else
			{
				if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY ||
						!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
				{
					CRX_FOR(size_t tI = 0, tI < pNode->gPrivate_numberOfEntries, tI++)
					{
						if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
						{
							(*(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(
									crx_c_tree_private_getElement(pThis, pNode, tI));
						}

						free(crx_c_tree_private_getElement(pThis, pNode, tI));
						/* *((unsigned char * *)crx_c_tree_private_getElementEntry(pThis,
								pNode, tI)) = NULL;*/
					}
					CRX_ENDFOR
				}
			}
		}
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
		{
			CRX_FOR(size_t tI = 0, tI < pNode->gPrivate_numberOfEntries, tI++)
			{
				(*(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(
						crx_c_tree_private_getElement(pThis, pNode, tI));

				if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
					{free(crx_c_tree_private_getElement(pThis, pNode, tI));}
			}
			CRX_ENDFOR
		}
		else
		{
			if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				CRX_FOR(size_t tI = 0, tI < pNode->gPrivate_numberOfEntries, tI++)
					{free(crx_c_tree_private_getElement(pThis, pNode, tI));}
				CRX_ENDFOR
			}
		}
	}

	free(pNode);
}

CRX__LIB__PRIVATE_C_FUNCTION() size_t crx_c_tree_private_getSuitableImagineryIndexFor(
		Crx_C_Tree * pThis, Crx_C_Tree_Private_Node const * CRX_NOT_NULL pNode,
		void const * pElement,
		void const * pIndex__guide,
		int32_t * pZeroIfFoundOrResultOfComparisonWithLargestKeyInNode)
{
	CRX_SCOPE_META
	assert(((pElement != NULL) || (pIndex__guide != NULL)) && (pElement != pIndex__guide));

	if(pNode->gPrivate_numberOfEntries == 0)
	{
		if(pZeroIfFoundOrResultOfComparisonWithLargestKeyInNode != NULL)
			{*pZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 1;}

		return 0 /*-1*/;
	}

	CRX_SCOPE
	size_t vBeginingIndex = 0;
	size_t vEndingIndex = pNode->gPrivate_numberOfEntries;

	if(pNode->gPrivate_type)
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			while(vBeginingIndex < vEndingIndex)
			{
				size_t tMiddleIndex = (vBeginingIndex + vEndingIndex) >> 1;

				if((*(pThis->gPrivate_getOrderOfIndices))(crx_c_tree_private_getIndexFrom(pThis, 
						pNode, tMiddleIndex), pIndex__guide) < 0)
					{vBeginingIndex = tMiddleIndex + 1;}
				else
					{vEndingIndex = tMiddleIndex;}
			}
		}
		else
		{
			while(vBeginingIndex < vEndingIndex)
			{
				size_t tMiddleIndex = (vBeginingIndex + vEndingIndex) >> 1;

				if((*(pThis->gPrivate_getOrderOfElements))(crx_c_tree_private_getElement(pThis,
						pNode, tMiddleIndex), pElement) < 0)
					{vBeginingIndex = tMiddleIndex + 1;}
				else
					{vEndingIndex = tMiddleIndex;}
			}
		}
	}
	else
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
			{
				while(vBeginingIndex < vEndingIndex)
				{
					size_t tMiddleIndex = (vBeginingIndex + vEndingIndex) >> 1;

					if((*(pThis->gPrivate_getOrderOfIndices))(crx_c_tree_private_getIndexFrom(pThis, 
							pNode, tMiddleIndex), pIndex__guide) < 0)
						{vBeginingIndex = tMiddleIndex + 1;}
					else
						{vEndingIndex = tMiddleIndex;}
				}
			}
			else
			{
				unsigned char * tIndex__guide = ((unsigned char *)CRX__ALLOCA(
						pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE));

				while(vBeginingIndex < vEndingIndex)
				{
					size_t tMiddleIndex = (vBeginingIndex + vEndingIndex) >> 1;

					(*(pThis->gPrivate_constructIndexFrom))(tIndex__guide,
							crx_c_tree_private_getElement(pThis, pNode, tMiddleIndex));

					if((*(pThis->gPrivate_getOrderOfIndices))(tIndex__guide, 
							pIndex__guide) < 0)
						{vBeginingIndex = tMiddleIndex + 1;}
					else
						{vEndingIndex = tMiddleIndex;}
				}
			}
		}
		else
		{
			while(vBeginingIndex < vEndingIndex)
			{
				size_t tMiddleIndex = (vBeginingIndex + vEndingIndex) >> 1;

				if((*(pThis->gPrivate_getOrderOfElements))(crx_c_tree_private_getElement(pThis,
						pNode, tMiddleIndex), pElement) < 0)
					{vBeginingIndex = tMiddleIndex + 1;}
				else
					{vEndingIndex = tMiddleIndex;}
			}
		}
	}

	if(vBeginingIndex == pNode->gPrivate_numberOfEntries)
	{
		if(pZeroIfFoundOrResultOfComparisonWithLargestKeyInNode != NULL)
			{*pZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 1;}

		return pNode->gPrivate_numberOfEntries /*- 1*/;
	}
	else
	{
		int32_t tResult /*= ?*/;

		if(pNode->gPrivate_type)
		{
			if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
			{
				tResult = (*(pThis->gPrivate_getOrderOfIndices))(pIndex__guide, 
						crx_c_tree_private_getIndexFrom(pThis, pNode, vBeginingIndex));
			}
			else
			{
				tResult = (*(pThis->gPrivate_getOrderOfElements))(pElement, 
						crx_c_tree_private_getElement(pThis, pNode, vBeginingIndex));
			}
		}
		else
		{
			if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
			{
				if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
				{
					tResult = (*(pThis->gPrivate_getOrderOfIndices))(pIndex__guide, 
							crx_c_tree_private_getIndexFrom(
							pThis, pNode, vBeginingIndex));
				}
				else
				{
					unsigned char * tIndex__guide = ((unsigned char *)CRX__ALLOCA(
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE));

					(*(pThis->gPrivate_constructIndexFrom))(tIndex__guide,
							crx_c_tree_private_getElement(pThis, pNode, vBeginingIndex));

					tResult = (*(pThis->gPrivate_getOrderOfIndices))(pIndex__guide, 
							tIndex__guide);
				}
			}
			else
			{
				tResult = (*(pThis->gPrivate_getOrderOfElements))(pElement, 
						crx_c_tree_private_getElement(pThis, pNode, vBeginingIndex));
			}
		}

		if(pZeroIfFoundOrResultOfComparisonWithLargestKeyInNode != NULL)
			{*pZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = tResult;}

		if(tResult < 0)
			{return vBeginingIndex; /*--vBeginingIndex;*/}
		else
			{return (vBeginingIndex + 1);}

		/*return ((size_t)(vBeginingIndex + 1)) /*vBeginingIndex*/;
	}
	CRX_SCOPE_END
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_transferPushFromNodeToNode(
		Crx_C_Tree * pThis, Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode,
		Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode__target,
		bool pIsToIncludeBegginingChildNode, size_t pStartingIndex)
{
	assert(pNode->gPrivate_type == pNode__target->gPrivate_type);

	if(pNode->gPrivate_type)
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			crx_c_tree_private_transfer(pThis, 
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
					pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
					pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
					crx_c_tree_private_getIndexFrom(pThis, pNode__target, 0),
					pNode__target, pNode__target->gPrivate_numberOfEntries,
					crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
					pNode, pStartingIndex,
					pNode->gPrivate_numberOfEntries - pStartingIndex);
		}
		else
		{
			crx_c_tree_private_transfer(pThis, 
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) :
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
					crx_c_tree_private_getElementEntry(pThis, pNode__target, 0),
					pNode__target, pNode__target->gPrivate_numberOfEntries,
					crx_c_tree_private_getElementEntry(pThis, pNode, 0),
					pNode, pStartingIndex,
					pNode->gPrivate_numberOfEntries - pStartingIndex);
		}

		if(!CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
		{
			CRX_FOR(size_t tI = pStartingIndex + (pIsToIncludeBegginingChildNode ? 0 : 1),
					tI <= pNode->gPrivate_numberOfEntries, tI++)
			{
				(*(crx_c_tree_private_getChildNode(pThis, pNode, tI)))->
						gPrivate_node__parent = pNode__target;
			}
			CRX_ENDFOR
		}

		crx_c_tree_private_transfer(pThis, sizeof(Crx_C_Tree_Private_Node *),
				NULL,
				NULL,
				((unsigned char *)crx_c_tree_private_getChildNode(pThis, pNode__target, 0)),
				pNode__target, pNode__target->gPrivate_numberOfEntries +
				(pIsToIncludeBegginingChildNode ? 0 : 1),
				((unsigned char *)crx_c_tree_private_getChildNode(pThis, pNode, 0)),
				pNode, pStartingIndex + (pIsToIncludeBegginingChildNode ? 0 : 1),
				pNode->gPrivate_numberOfEntries - pStartingIndex +
						(pIsToIncludeBegginingChildNode ? 1 : 0));

		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX && !CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
		{
			crx_c_tree_private_transfer(pThis, 
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) :
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
					crx_c_tree_private_getElementEntry(pThis, pNode__target, 0),
					pNode__target, pNode__target->gPrivate_numberOfEntries,
					crx_c_tree_private_getElementEntry(pThis, pNode, 0),
					pNode, pStartingIndex,
					pNode->gPrivate_numberOfEntries - pStartingIndex);
		}
	}
	else
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX && !CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
		{
			crx_c_tree_private_transfer(pThis, 
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
					pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
					pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
					crx_c_tree_private_getIndexFrom(pThis, pNode__target, 0),
					pNode__target, pNode__target->gPrivate_numberOfEntries,
					crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
					pNode, pStartingIndex,
					pNode->gPrivate_numberOfEntries - pStartingIndex);
		}

		crx_c_tree_private_transfer(pThis, 
				(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) :
						pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
				(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL : 
						pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
				(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL : 
						pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
				crx_c_tree_private_getElementEntry(pThis, pNode__target, 0),
				pNode__target, pNode__target->gPrivate_numberOfEntries,
				crx_c_tree_private_getElementEntry(pThis, pNode, 0),
				pNode, pStartingIndex,
				pNode->gPrivate_numberOfEntries - pStartingIndex);
	}
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_transferAllIntoNode(
		Crx_C_Tree * pThis, void * pIndex__guide,
		Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode__child,
		void * pElement,
		Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode,
		size_t pIndex, bool pIsToIncludeBegginingChildNode)
{
	CRX_SCOPE_META
	assert(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX || (pIndex__guide == NULL));

	CRX_SCOPE
	bool vIsToRotateRight = (CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ?
			((pNode->gPrivate_numberOfEntries >> 1) < pIndex) : false);

	if(pNode->gPrivate_type)
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			crx_c_tree_private_insertSpaceAt(pThis,
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE, 
					pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
					pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
					vIsToRotateRight, pNode,
					crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
					pNode->gPrivate_numberOfEntries, pIndex, 1);
		}
		else
		{
			crx_c_tree_private_insertSpaceAt(pThis,
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) :
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL : pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL : pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
					vIsToRotateRight, pNode,
					crx_c_tree_private_getElementEntry(pThis, pNode, 0),
					pNode->gPrivate_numberOfEntries, pIndex, 1);
		}

		crx_c_tree_private_insertSpaceAt(pThis,
				sizeof(Crx_C_Tree_Private_Node *),
				NULL, NULL,
				vIsToRotateRight, pNode,
				((unsigned char *)crx_c_tree_private_getChildNode(pThis, pNode, 0)),
				pNode->gPrivate_numberOfEntries + 1,
				(pIsToIncludeBegginingChildNode ? pIndex : pIndex + 1), 1);

		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX && !CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
		{
			crx_c_tree_private_insertSpaceAt(pThis,
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) :
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL : pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL : pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
					vIsToRotateRight, pNode,
					crx_c_tree_private_getElementEntry(pThis, pNode, 0),
					pNode->gPrivate_numberOfEntries, pIndex, 1);
		}

		crx_c_tree_private_updateStartIndexAfterInsertionOfSpace(pThis,
				vIsToRotateRight, pNode, pIndex, 1);

		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			if(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				(*(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT))(
						crx_c_tree_private_getIndexFrom(pThis, pNode, pIndex),
						pIndex__guide);
			}
			else
			{
				memmove(crx_c_tree_private_getIndexFrom(pThis, pNode,
						pIndex), pIndex__guide, pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
			}

			if(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT != NULL)
				{(*(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT))(pIndex__guide);}
		}
		else
		{
			if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)
				{
					(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT))(
							crx_c_tree_private_getElement(pThis, pNode, pIndex), pElement);
				}
				else
				{
					memmove(crx_c_tree_private_getElement(pThis, pNode, pIndex), pElement, 
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
				}

				if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL)
					{(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT))(pElement);}
			}
			else
			{
				*((unsigned char * *)crx_c_tree_private_getElementEntry(pThis, pNode, pIndex)) = 
						((unsigned char *)pElement);
			}
		}

		*(crx_c_tree_private_getChildNode(pThis, pNode, (pIsToIncludeBegginingChildNode ?
				pIndex : pIndex + 1))) = pNode__child;

		if(!CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
			{pNode__child->gPrivate_node__parent = pNode;}

		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX && !CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
		{
			if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)
				{
					(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT))(
							crx_c_tree_private_getElement(pThis, pNode, pIndex), pElement);
				}
				else
				{
					memmove(crx_c_tree_private_getElement(pThis,
							pNode, pIndex), pElement, pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
				}

				if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL)
					{(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT))(pElement);}
			}
			else
			{
				*((unsigned char * *)crx_c_tree_private_getElementEntry(pThis, pNode, pIndex)) = 
						((unsigned char *)pElement);
			}
		}
	}
	else
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX && !CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
		{
			crx_c_tree_private_insertSpaceAt(pThis,
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE, 
					pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
					pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
					vIsToRotateRight, pNode,
					crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
					pNode->gPrivate_numberOfEntries, pIndex, 1);
		}

		crx_c_tree_private_insertSpaceAt(pThis,
				(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) :
						pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
				(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL : 
						pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
				(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL : 
						pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
				vIsToRotateRight, pNode,
				crx_c_tree_private_getElementEntry(pThis, pNode, 0),
				pNode->gPrivate_numberOfEntries, pIndex, 1);

		crx_c_tree_private_updateStartIndexAfterInsertionOfSpace(pThis,
				vIsToRotateRight, pNode, pIndex, 1);

		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX && !CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
		{
			if(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				(*(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT))(
						crx_c_tree_private_getIndexFrom(pThis, pNode, pIndex),
						pIndex__guide);
			}
			else
			{
				memmove(crx_c_tree_private_getIndexFrom(pThis, pNode, pIndex),
						pIndex__guide, pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
			}

			if(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT != NULL)
				{(*(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT))(pIndex__guide);}
		}

		if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
		{
			if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT))(
						crx_c_tree_private_getElement(pThis, pNode, pIndex), pElement);
			}
			else
			{
				memmove(crx_c_tree_private_getElement(pThis, pNode, pIndex), pElement, 
						pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
			}

			if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL)
				{(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT))(pElement);}
		}
		else
		{
			*((unsigned char * *)crx_c_tree_private_getElementEntry(pThis, pNode, pIndex)) = 
					((unsigned char *)pElement);
		}

	}

	(pNode->gPrivate_numberOfEntries)++;
	
	CRX_SCOPE_END
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_removeFirstNEntriesFrom(
		Crx_C_Tree * pThis, Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode,
		size_t pWidth)
{
	if(!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS)
	{
		if(pNode->gPrivate_type)
		{
			if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
			{
				if((pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT != NULL) || 
						(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT != NULL))
				{
					if(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT != NULL)
					{
						CRX_FOR(size_t tI = pWidth,
								tI < pNode->gPrivate_numberOfEntries, tI++)
						{
							(*(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT))(
									crx_c_tree_private_getIndexFrom(pThis, pNode, tI - pWidth),
									crx_c_tree_private_getIndexFrom(pThis, pNode, tI));

							if(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT != NULL)
							{
								(*(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT))(
										crx_c_tree_private_getIndexFrom(pThis, pNode, tI));
							}
						}
						CRX_ENDFOR
					}
					else
					{
						CRX_FOR(size_t tI = pWidth,
								tI < pNode->gPrivate_numberOfEntries, tI++)
						{
							memmove(crx_c_tree_private_getIndexFrom(pThis,
									pNode, tI - pWidth),
									crx_c_tree_private_getIndexFrom(pThis, pNode, tI),
									pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);

							(*(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT))(
									crx_c_tree_private_getIndexFrom(pThis, pNode, tI));
						}
						CRX_ENDFOR
					}
				}
				else
				{
					memmove(crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
							crx_c_tree_private_getIndexFrom(pThis, pNode, pWidth),
							(pNode->gPrivate_numberOfEntries - pWidth) *
									pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
				}
			}
			else
			{
				if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
				{
					if((pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL) ||
							(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL))
					{
						if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)
						{
							CRX_FOR(size_t tI = pWidth,
									tI < pNode->gPrivate_numberOfEntries, tI++)
							{
								(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT))(
										crx_c_tree_private_getElement(pThis, pNode, tI - pWidth),
										crx_c_tree_private_getElement(pThis, pNode, tI));

								if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != 
										NULL)
								{
									(*(pThis->gPrivate_typeBluePrint__element->
											gFUNC__MOVE_DESTRUCT))(crx_c_tree_private_getElement(
											pThis, pNode, tI));
								}
							}
							CRX_ENDFOR
						}
						else
						{
							CRX_FOR(size_t tI = pWidth,
									tI < pNode->gPrivate_numberOfEntries, tI++)
							{
								memmove(crx_c_tree_private_getElementEntry(pThis,
												pNode, tI - pWidth),
										crx_c_tree_private_getElementEntry(pThis,
												pNode, tI),
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

								(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT))(
										crx_c_tree_private_getElement(pThis, pNode, tI));
							}
							CRX_ENDFOR
						}
					}
					else
					{
						memmove(crx_c_tree_private_getElementEntry(pThis, pNode, 0),
								crx_c_tree_private_getElementEntry(pThis, pNode, pWidth),
								(pNode->gPrivate_numberOfEntries - pWidth) *
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
					}
				}
				else
				{
					memmove(crx_c_tree_private_getElementEntry(pThis, pNode, 0),
							crx_c_tree_private_getElementEntry(pThis, pNode, pWidth),
							(pNode->gPrivate_numberOfEntries - pWidth) *
									sizeof(volatile void const *));
				}
			}

			memmove(crx_c_tree_private_getChildNode(pThis, pNode, 0),
					crx_c_tree_private_getChildNode(pThis, pNode, pWidth),
					(pNode->gPrivate_numberOfEntries + 1 - pWidth) *
					sizeof(volatile void const *));

			if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX && !CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
			{
				if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
				{
					if((pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL) ||
							(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL))
					{
						if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)
						{
							CRX_FOR(size_t tI = pWidth,
									tI < pNode->gPrivate_numberOfEntries, tI++)
							{
								(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT))(
										crx_c_tree_private_getElement(pThis, pNode, tI - pWidth),
										crx_c_tree_private_getElement(pThis, pNode, tI));

								if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != 
										NULL)
								{
									(*(pThis->gPrivate_typeBluePrint__element->
											gFUNC__MOVE_DESTRUCT))(crx_c_tree_private_getElement(
											pThis, pNode, tI));
								}
							}
							CRX_ENDFOR
						}
						else
						{
							CRX_FOR(size_t tI = pWidth,
									tI < pNode->gPrivate_numberOfEntries, tI++)
							{
								memmove(crx_c_tree_private_getElementEntry(pThis,
												pNode, tI - pWidth),
										crx_c_tree_private_getElementEntry(pThis,
												pNode, tI),
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

								(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT))(
										crx_c_tree_private_getElement(pThis, pNode, tI));
							}
							CRX_ENDFOR
						}
					}
					else
					{
						memmove(crx_c_tree_private_getElementEntry(pThis, pNode, 0),
								crx_c_tree_private_getElementEntry(pThis, pNode, pWidth),
								(pNode->gPrivate_numberOfEntries - pWidth) *
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
					}
				}
				else
				{
					memmove(crx_c_tree_private_getElementEntry(pThis, pNode, 0),
							crx_c_tree_private_getElementEntry(pThis, pNode, pWidth),
							(pNode->gPrivate_numberOfEntries - pWidth) *
									sizeof(volatile void const *));
				}
			}
		}
		else
		{
			if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX && 
					!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
			{
				if((pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT != NULL) || 
						(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT != NULL))
				{
					if(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT != NULL)
					{
						CRX_FOR(size_t tI = pWidth,
								tI < pNode->gPrivate_numberOfEntries, tI++)
						{
							(*(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT))(
									crx_c_tree_private_getIndexFrom(pThis, pNode, tI - pWidth),
									crx_c_tree_private_getIndexFrom(pThis, pNode, tI));

							if(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT != NULL)
							{
								(*(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT))(
										crx_c_tree_private_getIndexFrom(pThis, pNode, tI));
							}
						}
						CRX_ENDFOR
					}
					else
					{
						CRX_FOR(size_t tI = pWidth,
								tI < pNode->gPrivate_numberOfEntries, tI++)
						{
							memmove(crx_c_tree_private_getIndexFrom(pThis,
									pNode, tI - pWidth),
									crx_c_tree_private_getIndexFrom(pThis, pNode, tI),
									pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);

							(*(pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT))(
									crx_c_tree_private_getIndexFrom(pThis, pNode, tI));
						}
						CRX_ENDFOR
					}
				}
				else
				{
					memmove(crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
							crx_c_tree_private_getIndexFrom(pThis, pNode, pWidth),
							(pNode->gPrivate_numberOfEntries - pWidth) * 
									pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
				}
			}

			if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				if((pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL) ||
						(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL))
				{
					if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)
					{
						CRX_FOR(size_t tI = pWidth,
								tI < pNode->gPrivate_numberOfEntries, tI++)
						{
							(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT))(
									crx_c_tree_private_getElement(pThis, pNode, tI - pWidth),
									crx_c_tree_private_getElement(pThis, pNode, tI));

							if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL)
							{
								(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT))(
										crx_c_tree_private_getElement(pThis, pNode, tI));
							}
						}
						CRX_ENDFOR
					}
					else
					{
						CRX_FOR(size_t tI = pWidth,
								tI < pNode->gPrivate_numberOfEntries, tI++)
						{
							memmove(crx_c_tree_private_getElementEntry(pThis, pNode, tI - pWidth),
									crx_c_tree_private_getElementEntry(pThis, pNode, tI),
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

							(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT))(
									crx_c_tree_private_getElement(pThis, pNode, tI));
						}
						CRX_ENDFOR
					}
				}
				else
				{
					memmove(crx_c_tree_private_getElementEntry(pThis, pNode, 0),
							crx_c_tree_private_getElementEntry(pThis, pNode, pWidth),
							(pNode->gPrivate_numberOfEntries - pWidth) *
									pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
				}
			}
			else
			{
				memmove(crx_c_tree_private_getElementEntry(pThis, pNode, 0),
						crx_c_tree_private_getElementEntry(pThis, pNode, pWidth),
						(pNode->gPrivate_numberOfEntries - pWidth) *
								sizeof(volatile void const *));
			}
		}
	}
	else
	{
		pNode->gPrivate_startIndex = ((pNode->gPrivate_startIndex + pWidth) &
				((pThis->gPrviate_countOfMidElementInNode * 2) - 1));
	}
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_rotateRight(Crx_C_Tree * pThis,
		Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode, size_t pIndexOfNodeInParent,
		Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode__parent,
		Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode__rightSibling)
{
	if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		if(pNode->gPrivate_type)
		{
			if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
			{
				crx_c_tree_private_transferAllIntoNode(pThis,
						crx_c_tree_private_getIndexFrom(pThis, pNode__parent, pIndexOfNodeInParent),
						*(crx_c_tree_private_getChildNode(pThis, pNode,
								pNode->gPrivate_numberOfEntries)),
						crx_c_tree_private_getElement(pThis, pNode__parent, pIndexOfNodeInParent),
						pNode__rightSibling, 0, true);

				crx_c_tree_private_transferConstruct(pThis, 
						pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
						pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
						pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
						crx_c_tree_private_getIndexFrom(pThis, pNode__parent, pIndexOfNodeInParent),
						crx_c_tree_private_getIndexFrom(pThis, pNode,
								pNode->gPrivate_numberOfEntries - 1));
			}
			else
			{
				crx_c_tree_private_transferAllIntoNode(pThis, NULL,
						*(crx_c_tree_private_getChildNode(pThis, pNode,
								pNode->gPrivate_numberOfEntries)),
						crx_c_tree_private_getElement(pThis, pNode__parent, pIndexOfNodeInParent),
						pNode__rightSibling, 0, true);
			}

			crx_c_tree_private_transferConstruct(pThis,
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
					crx_c_tree_private_getElementEntry(pThis, pNode__parent, pIndexOfNodeInParent),
					crx_c_tree_private_getElementEntry(pThis, pNode, 
							pNode->gPrivate_numberOfEntries - 1));
		}
		else
		{
			if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
			{
				if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
				{
					crx_c_tree_private_transferAllIntoNode(pThis,
							crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
									pIndexOfNodeInParent),
							NULL,
							crx_c_tree_private_getElement(pThis, pNode__parent, 
									pIndexOfNodeInParent),
							pNode__rightSibling, 0, true);

					crx_c_tree_private_transferConstruct(pThis, 
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
							pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
							pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
							crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
									pIndexOfNodeInParent),
							crx_c_tree_private_getIndexFrom(pThis, pNode,
									pNode->gPrivate_numberOfEntries - 1));
				}
				else
				{
					unsigned char * tIndex__guide = ((unsigned char *)CRX__ALLOCA(
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE));

					(*(pThis->gPrivate_constructIndexFrom))(tIndex__guide,
							crx_c_tree_private_getElement(pThis, pNode,
							pNode->gPrivate_numberOfEntries - 1));

					crx_c_tree_private_transferAllIntoNode(
							pThis,
							NULL,
							NULL,
							crx_c_tree_private_getElement(pThis, pNode__parent, 
									pIndexOfNodeInParent),
							pNode__rightSibling, 0, true);

					memcpy(crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
									pIndexOfNodeInParent),
							tIndex__guide,
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
				}
			}
			else
			{
				crx_c_tree_private_transferAllIntoNode(pThis, NULL,
						NULL,
						crx_c_tree_private_getElement(pThis, pNode__parent, pIndexOfNodeInParent),
						pNode__rightSibling, 0, true);
			}

			crx_c_tree_private_transferConstruct(pThis,
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
					crx_c_tree_private_getElementEntry(pThis, pNode__parent, pIndexOfNodeInParent),
					crx_c_tree_private_getElementEntry(pThis,
							pNode, pNode->gPrivate_numberOfEntries - 1));
		}
	}
	else
	{
		if(pNode->gPrivate_type)
		{
			if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
			{
				crx_c_tree_private_transferAllIntoNode(pThis,
						crx_c_tree_private_getIndexFrom(pThis, pNode__parent, pIndexOfNodeInParent),
						*(crx_c_tree_private_getChildNode(pThis, pNode,
								pNode->gPrivate_numberOfEntries)),
						NULL,
						pNode__rightSibling, 0, true);

				crx_c_tree_private_transferConstruct(pThis,
						pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
						pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
						pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
						crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
								pIndexOfNodeInParent),
						crx_c_tree_private_getIndexFrom(pThis, pNode, 
								pNode->gPrivate_numberOfEntries - 1));
			}
			else
			{
				crx_c_tree_private_transferAllIntoNode(pThis, NULL,
						*(crx_c_tree_private_getChildNode(pThis, pNode,
								pNode->gPrivate_numberOfEntries)),
						crx_c_tree_private_getElement(pThis, pNode__parent, pIndexOfNodeInParent),
						pNode__rightSibling, 0, true);

				crx_c_tree_private_transferConstruct(pThis,
						(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
								pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
						(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
								pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
						(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
								pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
						crx_c_tree_private_getElementEntry(pThis, 
								pNode__parent, pIndexOfNodeInParent),
						crx_c_tree_private_getElementEntry(pThis,
								pNode, pNode->gPrivate_numberOfEntries - 1));
			}
		}
		else
		{
			if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
			{
				if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
				{
					crx_c_tree_private_transferAllIntoNode(pThis,
							crx_c_tree_private_getIndexFrom(pThis, pNode,
									pNode->gPrivate_numberOfEntries - 1),
							NULL,
							crx_c_tree_private_getElement(pThis, pNode,
									pNode->gPrivate_numberOfEntries - 1),
							pNode__rightSibling, 0, true);

					memcpy(crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
									pIndexOfNodeInParent),
							crx_c_tree_private_getIndexFrom(pThis, pNode__rightSibling, 0),
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
				}
				else
				{
					unsigned char * tIndex__guide = ((unsigned char *)CRX__ALLOCA(
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE));

					(*(pThis->gPrivate_constructIndexFrom))(tIndex__guide,
							crx_c_tree_private_getElement(pThis, pNode,
							pNode->gPrivate_numberOfEntries - 1));

					crx_c_tree_private_transferAllIntoNode(pThis, NULL,
							NULL,
							crx_c_tree_private_getElement(pThis, pNode,
									pNode->gPrivate_numberOfEntries - 1),
							pNode__rightSibling, 0, true);

					memcpy(crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
									pIndexOfNodeInParent),
							tIndex__guide,
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
				}
			}
			else
			{
				crx_c_tree_private_transferAllIntoNode(pThis, NULL,
						NULL,
						crx_c_tree_private_getElement(pThis, pNode,
								pNode->gPrivate_numberOfEntries - 1),
						pNode__rightSibling, 0, true);

				if((pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL) && 
						(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT || 
						!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION))
				{
					(*(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(
							crx_c_tree_private_getElement(pThis,
							pNode__parent, pIndexOfNodeInParent));
				}

				if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT && CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
				{
					*((unsigned char * *)crx_c_tree_private_getElementEntry(pThis,
							pNode__parent, pIndexOfNodeInParent)) =
							crx_c_tree_private_getElement(pThis, pNode__rightSibling, 0);
				}
				else
				{
					if(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != NULL)
					{
						(*(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT))(
								crx_c_tree_private_getElement(pThis, 
										pNode__parent, pIndexOfNodeInParent),
								crx_c_tree_private_getElement(pThis, pNode__rightSibling, 0));
					}
					else
					{
						memcpy(crx_c_tree_private_getElement(pThis, 
										pNode__parent, pIndexOfNodeInParent),
								crx_c_tree_private_getElement(pThis, pNode__rightSibling, 0),
								pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
					}
				}
			}
		}
	}

	(pNode->gPrivate_numberOfEntries)--;
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_rotateLeft(Crx_C_Tree * pThis,
		Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode, size_t pIndexOfNodeInParent,
		Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode__parent,
		Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode__leftSibling)
{
	if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		if(pNode->gPrivate_type)
		{
			if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
			{
				crx_c_tree_private_transferAllIntoNode(pThis,
						crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
								pIndexOfNodeInParent - 1),
						*(crx_c_tree_private_getChildNode(pThis, pNode, 0)),
						crx_c_tree_private_getElement(pThis, pNode__parent, 
								pIndexOfNodeInParent - 1),
						pNode__leftSibling,
						pNode__leftSibling->gPrivate_numberOfEntries, false);

				crx_c_tree_private_transferConstruct(pThis,
						pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
						pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
						pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
						crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
								pIndexOfNodeInParent - 1),
						crx_c_tree_private_getIndexFrom(pThis, pNode, 0));
			}
			else
			{
				crx_c_tree_private_transferAllIntoNode(
						pThis, NULL,
						*(crx_c_tree_private_getChildNode(pThis, pNode, 0)),
						crx_c_tree_private_getElement(pThis, pNode__parent,
								pIndexOfNodeInParent - 1),
						pNode__leftSibling,
						pNode__leftSibling->gPrivate_numberOfEntries, false);
			}

			crx_c_tree_private_transferConstruct(pThis,
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
					crx_c_tree_private_getElementEntry(pThis,
							pNode__parent, pIndexOfNodeInParent - 1),
					crx_c_tree_private_getElementEntry(pThis,
							pNode, 0));
		}
		else
		{
			if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
			{
				if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
				{
					crx_c_tree_private_transferAllIntoNode(pThis,
							crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
									pIndexOfNodeInParent - 1),
							NULL,
							crx_c_tree_private_getElement(pThis,
									pNode__parent, pIndexOfNodeInParent - 1),
							pNode__leftSibling,
							pNode__leftSibling->gPrivate_numberOfEntries, false);

					crx_c_tree_private_transferConstruct(pThis,
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
							pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
							pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
							crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
									pIndexOfNodeInParent - 1),
							crx_c_tree_private_getIndexFrom(pThis, pNode, 0));
				}
				else
				{
					unsigned char * tIndex__guide = ((unsigned char *)CRX__ALLOCA(
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE));

					(*(pThis->gPrivate_constructIndexFrom))(tIndex__guide,
							crx_c_tree_private_getElement(pThis, pNode, 0));

					crx_c_tree_private_transferAllIntoNode(pThis, NULL,
							NULL,
							crx_c_tree_private_getElement(pThis,
									pNode__parent, pIndexOfNodeInParent - 1),
							pNode__leftSibling,
							pNode__leftSibling->gPrivate_numberOfEntries, false);

					memcpy(crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
									pIndexOfNodeInParent - 1),
							tIndex__guide,
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
				}
			}
			else
			{
				crx_c_tree_private_transferAllIntoNode(
						pThis, NULL,
						NULL,
						crx_c_tree_private_getElement(pThis,
								pNode__parent, pIndexOfNodeInParent - 1),
						pNode__leftSibling,
						pNode__leftSibling->gPrivate_numberOfEntries, false);
			}

			crx_c_tree_private_transferConstruct(pThis,
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
					crx_c_tree_private_getElementEntry(pThis,
							pNode__parent, pIndexOfNodeInParent - 1),
					crx_c_tree_private_getElementEntry(pThis, pNode, 0));
		}
	}
	else
	{
		if(pNode->gPrivate_type)
		{
			if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
			{
				crx_c_tree_private_transferAllIntoNode(pThis,
						crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
								pIndexOfNodeInParent - 1),
						*(crx_c_tree_private_getChildNode(pThis, pNode, 0)),
						NULL,
						pNode__leftSibling,
						pNode__leftSibling->gPrivate_numberOfEntries, false);

				crx_c_tree_private_transferConstruct(pThis,
						pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
						pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
						pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
						crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
								pIndexOfNodeInParent - 1),
						crx_c_tree_private_getIndexFrom(pThis, pNode, 0));
			}
			else
			{
				crx_c_tree_private_transferAllIntoNode(pThis, NULL,
						*(crx_c_tree_private_getChildNode(pThis, pNode, 0)),
						crx_c_tree_private_getElement(pThis, pNode__parent,
								pIndexOfNodeInParent - 1),
						pNode__leftSibling,
						pNode__leftSibling->gPrivate_numberOfEntries, false);

				crx_c_tree_private_transferConstruct(pThis,
						(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
								pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
						(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
								pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
						(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
								pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
						crx_c_tree_private_getElementEntry(pThis,
								pNode__parent, pIndexOfNodeInParent - 1),
						crx_c_tree_private_getElementEntry(pThis,
								pNode, 0));
			}
		}
		else
		{
			if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
			{
				if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
				{
					crx_c_tree_private_transferAllIntoNode(pThis,
							crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
							NULL,
							crx_c_tree_private_getElement(pThis, pNode, 0),
							pNode__leftSibling,
							pNode__leftSibling->gPrivate_numberOfEntries, false);

					memcpy(crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
									pIndexOfNodeInParent - 1),
							crx_c_tree_private_getIndexFrom(pThis, pNode, 1),
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
				}
				else
				{
					unsigned char * tIndex__guide = ((unsigned char *)CRX__ALLOCA(
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE));

					(*(pThis->gPrivate_constructIndexFrom))(tIndex__guide,
							crx_c_tree_private_getElement(pThis, pNode, 1));

					crx_c_tree_private_transferAllIntoNode(pThis, NULL,
							NULL,
							crx_c_tree_private_getElement(pThis, pNode, 0),
							pNode__leftSibling,
							pNode__leftSibling->gPrivate_numberOfEntries, false);

					memcpy(crx_c_tree_private_getIndexFrom(pThis, pNode__parent,
									pIndexOfNodeInParent - 1),
							tIndex__guide,
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
				}
			}
			else
			{
				crx_c_tree_private_transferAllIntoNode(pThis, NULL,
						NULL,
						crx_c_tree_private_getElement(pThis, pNode, 0),
						pNode__leftSibling,
						pNode__leftSibling->gPrivate_numberOfEntries, false);

				if((pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL) && 
						(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ||
						!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION))
				{
					(*(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(
							crx_c_tree_private_getElement(pThis,
							pNode__parent, pIndexOfNodeInParent - 1));
				}

				if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT && CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
				{
					*((unsigned char * *)crx_c_tree_private_getElementEntry(pThis,
							pNode__parent, pIndexOfNodeInParent - 1)) =
							crx_c_tree_private_getElement(pThis, pNode, 1);
				}
				else
				{
					if(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != NULL)
					{
						(*(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT))(
								crx_c_tree_private_getElement(pThis,
										pNode__parent, pIndexOfNodeInParent - 1),
								crx_c_tree_private_getElement(pThis, pNode, 1));
					}
					else
					{
						memcpy(crx_c_tree_private_getElement(pThis,
										pNode__parent, pIndexOfNodeInParent - 1),
								crx_c_tree_private_getElement(pThis, pNode, 1),
								pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
					}
				}
			}
		}
	}

	crx_c_tree_private_removeFirstNEntriesFrom(pThis, pNode, 1);
	(pNode->gPrivate_numberOfEntries)--;
}

/*REMEMBER: IN THE PRE EMPTIVE CASE, THIS MUST NOT MODIFY *pIndicesOfNodesInParents, MEANING
		pIndexOfNodeInParent*/
CRX__LIB__PRIVATE_C_FUNCTION() uint32_t crx_c_tree_private_resolveFullNode(Crx_C_Tree * pThis,
		Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode,
		Crx_C_Tree_Private_Node * pNode__parent,
		size_t * CRX_NOT_NULL pIndicesOfNodesInParents /*pIndexOfNodeInParent*/)
{
	CRX_SCOPE_META
	assert(pNode->gPrivate_numberOfEntries ==
			(2 * pThis->gPrviate_countOfMidElementInNode) - 1);

	CRX_SCOPE
	Crx_C_Tree_Private_Node * vNode__parent = (CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE ?
			pNode__parent : pNode->gPrivate_node__parent);
	size_t vIndexOfNodeInParent = *pIndicesOfNodesInParents;
	uint32_t vReturn = 1;

	if(vNode__parent == NULL)
	{
		Crx_C_Tree_Private_InternalNode * tInternalNode =
				((Crx_C_Tree_Private_InternalNode *)calloc(1,
				pThis->gPrivate_internalNode_byteLength));

		if(tInternalNode != NULL)
		{
			pThis->gPrivate_node__root = &(tInternalNode->gPrivate_node);
			pThis->gPrivate_node__root->gPrivate_type = 1;
			pThis->gPrivate_node__root->gPrivate_numberOfEntries = 0;

			*(crx_c_tree_private_getChildNode(pThis, pThis->gPrivate_node__root, 0)) =
					pNode;
			/*REMEMBER: THIS IS NECESSARY FOR THE CODE LATER*/
			*(crx_c_tree_private_getChildNode(pThis, pThis->gPrivate_node__root, 1)) =
					NULL;

			if(!CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
				{pNode->gPrivate_node__parent = pThis->gPrivate_node__root;}

			++(pThis->gPrivate_numberOfNodes);

			vNode__parent = pThis->gPrivate_node__root;
		}
		else
			{vReturn = 0;}
	}

	if(!CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
	{
		if(vReturn != 0)
		{
			if((vNode__parent->gPrivate_numberOfEntries ==
					(2 * pThis->gPrviate_countOfMidElementInNode) - 1))
			{
				/*WARNING: FORMAL VIOLATION. SEMANTIC OF vReturn IS CHANGED TEMPORARILY HERE*/
				vReturn = crx_c_tree_private_resolveFullNode(pThis,
						vNode__parent, NULL, pIndicesOfNodesInParents - 1);

				if(vReturn == 1)
				{
					if(vIndexOfNodeInParent >= pThis->gPrviate_countOfMidElementInNode)
					{
						vNode__parent = pNode->gPrivate_node__parent;

						*(pIndicesOfNodesInParents - 1) =
								*(pIndicesOfNodesInParents - 1) + 1;
						*pIndicesOfNodesInParents = *pIndicesOfNodesInParents -
								pThis->gPrviate_countOfMidElementInNode;
						vIndexOfNodeInParent = *pIndicesOfNodesInParents;
					}
				}
				else if(CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH)
				{
					if(vReturn == 2)
					{
						if(vIndexOfNodeInParent == 0)
						{
							vNode__parent = pNode->gPrivate_node__parent;

							*(pIndicesOfNodesInParents - 1) =
									*(pIndicesOfNodesInParents - 1) - 1;
							*pIndicesOfNodesInParents =
									vNode__parent->gPrivate_numberOfEntries;
							vIndexOfNodeInParent = *pIndicesOfNodesInParents;
						}
					}
					else if(vReturn == 3)
					{
						if(vIndexOfNodeInParent > vNode__parent->gPrivate_numberOfEntries)
						{
							vNode__parent = pNode->gPrivate_node__parent;

							*(pIndicesOfNodesInParents - 1) =
									*(pIndicesOfNodesInParents - 1) + 1;
							*pIndicesOfNodesInParents = 0;
							vIndexOfNodeInParent = *pIndicesOfNodesInParents;
						}
					}
				}
				else
					{assert(vReturn == 0);}
			}
		}
	}

	if(vReturn != 0)
	{
		bool tIsToSplit = (CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH ? false : true);

		if(CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH)
		{
			Crx_C_Tree_Private_Node * tNode__sibling = (
					(vIndexOfNodeInParent < (2 * pThis->gPrviate_countOfMidElementInNode)) ?
					*(crx_c_tree_private_getChildNode(pThis, vNode__parent,
					vIndexOfNodeInParent + 1)) : NULL);

			if((tNode__sibling != NULL) && (tNode__sibling->gPrivate_numberOfEntries <
					((2 * pThis->gPrviate_countOfMidElementInNode) - 2)))
			{
				crx_c_tree_private_rotateRight(pThis,
						pNode, vIndexOfNodeInParent, vNode__parent, tNode__sibling);
				vReturn = 3;
			}
			else
			{
				tNode__sibling = ((vIndexOfNodeInParent > 0) ?
						*(crx_c_tree_private_getChildNode(pThis, vNode__parent,
						vIndexOfNodeInParent - 1)) : NULL);

				if((tNode__sibling != NULL) && (tNode__sibling->gPrivate_numberOfEntries <
						((2 * pThis->gPrviate_countOfMidElementInNode) - 2)))
				{
					crx_c_tree_private_rotateLeft(pThis,
							pNode, vIndexOfNodeInParent, vNode__parent, tNode__sibling);
					vReturn = 2;
				}
				else
					{tIsToSplit = true;}
			}
		}

		if(tIsToSplit)
		{
			Crx_C_Tree_Private_Node * tNode = NULL;
			unsigned char * tElement = NULL;

			if(pNode->gPrivate_type)
			{
				Crx_C_Tree_Private_InternalNode * tInternalNode =
						(Crx_C_Tree_Private_InternalNode *)calloc(1,
						pThis->gPrivate_internalNode_byteLength);

				if(tInternalNode != NULL)
					{tNode = &(tInternalNode->gPrivate_node);}
			}
			else
			{
				Crx_C_Tree_Private_LeafNode * tLeafNode =
						(Crx_C_Tree_Private_LeafNode *)calloc(1,
						pThis->gPrivate_leafNode_byteLength);

				if(tLeafNode != NULL)
					{tNode = &(tLeafNode->gPrivate_node);}
			}

			if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT && !CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX &&
					CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY &&
					!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
			{
				if((tNode != NULL) && (pNode->gPrivate_type == 0))
				{
					tElement = ((unsigned char *)calloc(1, 
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));

					if(tElement == NULL)
					{
						free(tNode);
						tNode = NULL;
					}
				}
			}

			if(tNode != NULL)
			{
				(pThis->gPrivate_numberOfNodes)++;

				tNode->gPrivate_type = pNode->gPrivate_type;
				tNode->gPrivate_numberOfEntries = 0;
				if(!CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
					{tNode->gPrivate_node__parent = pNode->gPrivate_node__parent;}

				crx_c_tree_private_transferPushFromNodeToNode(pThis, pNode,
						tNode, true, pThis->gPrviate_countOfMidElementInNode);

				tNode->gPrivate_numberOfEntries =
						pThis->gPrviate_countOfMidElementInNode - 1;

				if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
				{
					if(pNode->gPrivate_type)
					{
						if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
						{
							crx_c_tree_private_transferAllIntoNode(pThis,
									crx_c_tree_private_getIndexFrom(pThis, pNode,
											pThis->gPrviate_countOfMidElementInNode - 1),
									tNode,
									crx_c_tree_private_getElement(pThis, pNode,
											pThis->gPrviate_countOfMidElementInNode - 1),
									vNode__parent, vIndexOfNodeInParent, false);
						}
						else
						{
							crx_c_tree_private_transferAllIntoNode(pThis, NULL,
									tNode,
									crx_c_tree_private_getElement(pThis, pNode,
											pThis->gPrviate_countOfMidElementInNode - 1),
									vNode__parent, vIndexOfNodeInParent, false);
						}
					}
					else
					{
						if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
						{
							if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
							{
								crx_c_tree_private_transferAllIntoNode(pThis,
										crx_c_tree_private_getIndexFrom(pThis, pNode,
												pThis->gPrviate_countOfMidElementInNode - 1),
										tNode,
										crx_c_tree_private_getElement(pThis, pNode, 
												pThis->gPrviate_countOfMidElementInNode - 1),
										vNode__parent, vIndexOfNodeInParent, false);
							}
							else
							{
								unsigned char * tIndex__guide = (unsigned char *) CRX__ALLOCA(
										pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);

								(*(pThis->gPrivate_constructIndexFrom))(
										tIndex__guide,
										crx_c_tree_private_getElement(pThis, pNode,
										pThis->gPrviate_countOfMidElementInNode - 1));

								crx_c_tree_private_transferAllIntoNode(pThis,
										tIndex__guide,
										tNode,
										crx_c_tree_private_getElement(pThis, pNode, 
												pThis->gPrviate_countOfMidElementInNode - 1),
										vNode__parent, vIndexOfNodeInParent, false);
							}
						}
						else
						{
							crx_c_tree_private_transferAllIntoNode(pThis, NULL,
									tNode,
									crx_c_tree_private_getElement(pThis, pNode,
											pThis->gPrviate_countOfMidElementInNode - 1),
									vNode__parent, vIndexOfNodeInParent, false);
						}
					}

					pNode->gPrivate_numberOfEntries =
							pThis->gPrviate_countOfMidElementInNode - 1;
				}
				else
				{
					if(pNode->gPrivate_type)
					{
						if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
						{
							crx_c_tree_private_transferAllIntoNode(pThis,
									crx_c_tree_private_getIndexFrom(pThis, pNode,
											pThis->gPrviate_countOfMidElementInNode - 1),
									tNode,
									NULL,
									vNode__parent, vIndexOfNodeInParent, false);
						}
						else
						{
							crx_c_tree_private_transferAllIntoNode(pThis, NULL,
									tNode,
									crx_c_tree_private_getElement(pThis,
											pNode, pThis->gPrviate_countOfMidElementInNode - 1),
									vNode__parent, vIndexOfNodeInParent, false);
						}

						pNode->gPrivate_numberOfEntries =
								pThis->gPrviate_countOfMidElementInNode - 1;
					}
					else
					{
						if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
						{
							unsigned char * tIndex__guide = (unsigned char *) CRX__ALLOCA(
									pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);

							if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
							{
								memcpy(tIndex__guide, crx_c_tree_private_getIndexFrom(pThis,
										tNode, 0), pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
							}
							else
							{
								(*(pThis->gPrivate_constructIndexFrom))(tIndex__guide,
										crx_c_tree_private_getElement(pThis, tNode, 0));
							}

							crx_c_tree_private_transferAllIntoNode(pThis,
									tIndex__guide,
									tNode,
									NULL,
									vNode__parent, vIndexOfNodeInParent, false);
						}
						else
						{
							if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ||
									!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
							{
								if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
								{
									tElement = (unsigned char *) CRX__ALLOCA(
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
								}

								if(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != 
										NULL)
								{
									(*(pThis->gPrivate_typeBluePrint__element->
											gFUNC__COPY_CONSTRUCT))(tElement,
											crx_c_tree_private_getElement(pThis, tNode, 0));
								}
								else
								{
									memcpy(tElement, crx_c_tree_private_getElement(
											pThis, tNode, 0),
											pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
								}

								crx_c_tree_private_transferAllIntoNode(pThis, NULL,
										tNode,
										tElement,
										vNode__parent, vIndexOfNodeInParent, false);
							}
							else
							{
								crx_c_tree_private_transferAllIntoNode(pThis, NULL,
										tNode,
										crx_c_tree_private_getElement(pThis, tNode, 0),
										vNode__parent, vIndexOfNodeInParent, false);
							}
						}

						pNode->gPrivate_numberOfEntries =
								pThis->gPrviate_countOfMidElementInNode;

						((Crx_C_Tree_Private_LeafNode *)tNode)->gPrivate_leafNode__prev =
								((Crx_C_Tree_Private_LeafNode *)pNode);
						((Crx_C_Tree_Private_LeafNode *)tNode)->gPrivate_leafNode__next =
								((Crx_C_Tree_Private_LeafNode *)pNode)->
										gPrivate_leafNode__next;

						if(((Crx_C_Tree_Private_LeafNode *)pNode)->
								gPrivate_leafNode__next != NULL)
						{
							((Crx_C_Tree_Private_LeafNode *)pNode)->
									gPrivate_leafNode__next->gPrivate_leafNode__prev =
									((Crx_C_Tree_Private_LeafNode *)tNode);
						}

						((Crx_C_Tree_Private_LeafNode *)pNode)->
								gPrivate_leafNode__next =
								((Crx_C_Tree_Private_LeafNode *)tNode);
					}
				}

				/*(vNode__parent->gPrivate_numberOfEntries)++;*/
			}
			else
				{vReturn = 0;}
		}
	}
	else
		{vReturn = 0;}

	return vReturn;

	CRX_SCOPE_END
}

CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_tree_private_transferAndInsertElementEntry(
		Crx_C_Tree * pThis, void * CRX_NOT_NULL pElement)
{
	CRX_SCOPE_META
	if(pThis->gPrivate_node__root == NULL)
		{return false;}

	CRX_SCOPE
	bool vIsNoError = true;
	size_t * vIndices /*= ?*/;

	if(!CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
	{
		vIndices = ((size_t *) CRX__ALLOCA(sizeof(size_t) * 65));
	
		vIndices[0] = 0;
		vIndices[1] = 0;
	}

	if(CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
	{
		if(pThis->gPrivate_node__root->gPrivate_numberOfEntries ==
				2 * pThis->gPrviate_countOfMidElementInNode - 1)
		{
			size_t tIndex = 0;

			vIsNoError = (crx_c_tree_private_resolveFullNode(pThis,
					pThis->gPrivate_node__root, NULL, &tIndex) != 0);
		}
	}

	if(vIsNoError)
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			unsigned char * tIndex__guide = (unsigned char *) CRX__ALLOCA(
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);

			(*(pThis->gPrivate_constructIndexFrom))(tIndex__guide, pElement);

			if(CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
			{
				vIsNoError = crx_c_tree_private_transferAndInsertElementEntry__do(
						pThis, pThis->gPrivate_node__root, NULL,
						tIndex__guide, pElement);
			}
			else
			{
				vIsNoError = crx_c_tree_private_transferAndInsertElementEntry__do(
						pThis, pThis->gPrivate_node__root, &(vIndices[1]),
						tIndex__guide, pElement);
			}
		}
		else
		{
			if(CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
			{
				vIsNoError = crx_c_tree_private_transferAndInsertElementEntry__do(
						pThis, pThis->gPrivate_node__root, NULL, NULL, pElement);
			}
			else
			{
				vIsNoError = crx_c_tree_private_transferAndInsertElementEntry__do(
						pThis, pThis->gPrivate_node__root, &(vIndices[1]), NULL, pElement);
			}
		}

		if(vIsNoError)
		{
			++(pThis->gPrivate_numberOfElements);

			return true;
		}
		else
			{return false;}
	}
	else
		{return false;}
	CRX_SCOPE_END
}
CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_tree_private_transferAndInsertElementEntry__do(
		Crx_C_Tree * pThis, Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode,
		size_t * pIndexOfNodeInParent,
		void * pIndex__guide,
		void * CRX_NOT_NULL pElement)
{
	assert(!CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX || (pIndex__guide != NULL));
	assert(CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE || (pIndexOfNodeInParent != NULL));
	/*pGUIDE_TYPE * vReturn = NULL;*/

	if(pNode->gPrivate_type)
	{
		bool tIsNoError = true;

		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			size_t tIndex = crx_c_tree_private_getSuitableImagineryIndexFor(
					pThis, pNode, NULL, pIndex__guide, NULL) /*+ 1*/;
			Crx_C_Tree_Private_Node * tNode = *(crx_c_tree_private_getChildNode(pThis,
					pNode, tIndex));

			if(CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
			{
				if(tNode->gPrivate_numberOfEntries ==
						((2 * pThis->gPrviate_countOfMidElementInNode) - 1))
				{
					uint32_t tResult = crx_c_tree_private_resolveFullNode(
							pThis, tNode, pNode, &tIndex);

					/*NOTE: IN THIS CASE WE ARE DELIBRATELY DECIDING ON THE INSERTION WITH
							">" AND "<" INSTEAD OF ">=" AND "<" THAT WOULD BE PER THE
							ALGORITHM OF Tree::getSuitableImagineryIndexFor(). THIS IS TO
							AVOID RE ASSIGNING TO tNode.
					*/
					if(tResult != 0)
					{
						if(((tResult == 1) || (CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH ?
										(tResult == 3) : false)) &&
								((*(pThis->gPrivate_getOrderOfIndices))(pIndex__guide, crx_c_tree_private_getIndexFrom(
										pThis, pNode, tIndex)) > 0))
						{
							tNode = *(crx_c_tree_private_getChildNode(pThis, pNode, tIndex + 1));
						}
						else if((tResult == 2) && (CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH ?
								((*(pThis->gPrivate_getOrderOfIndices))(pIndex__guide, crx_c_tree_private_getIndexFrom(
										pThis, pNode, tIndex - 1)) < 0) :
								false))
						{
							if(CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH)
							{
								tNode = *(crx_c_tree_private_getChildNode(pThis, pNode, 
										tIndex - 1));
							}
						}
					}
					else
						{tIsNoError = false;}
				}

				if(tIsNoError)
				{
					tIsNoError =
							crx_c_tree_private_transferAndInsertElementEntry__do(
							pThis, tNode, NULL, pIndex__guide, pElement);
				}
			}
			else
			{
				*(pIndexOfNodeInParent + 1) = tIndex;

				tIsNoError = crx_c_tree_private_transferAndInsertElementEntry__do(
						pThis, tNode, pIndexOfNodeInParent + 1, pIndex__guide, pElement);
			}
		}
		else
		{
			size_t tIndex = crx_c_tree_private_getSuitableImagineryIndexFor(
					pThis, pNode, pElement, NULL, NULL) /*+ 1*/;
			Crx_C_Tree_Private_Node * tNode = *(crx_c_tree_private_getChildNode(pThis,
					pNode, tIndex));

			if(CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
			{
				if(tNode->gPrivate_numberOfEntries ==
						((2 * pThis->gPrviate_countOfMidElementInNode) - 1))
				{
					uint32_t tResult = crx_c_tree_private_resolveFullNode(
							pThis, tNode, pNode, &tIndex);

					/*NOTE: IN THIS CASE WE ARE DELIBRATELY DECIDING ON THE INSERTION WITH
							">" AND "<" INSTEAD OF ">=" AND "<" THAT WOULD BE PER THE
							ALGORITHM OF Tree::getSuitableImagineryIndexFor(). THIS IS TO
							AVOID RE ASSIGNING TO tNode.
					*/
					if(tResult != 0)
					{
						if(((tResult == 1) || (CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH ?
										(tResult == 3) : false)) &&
								((*(pThis->gPrivate_getOrderOfElements))(pElement, crx_c_tree_private_getElement(
										pThis, pNode, tIndex)) > 0))
						{
							tNode = *(crx_c_tree_private_getChildNode(pThis, pNode, tIndex + 1));
						}
						else if((tResult == 2) && (CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH ?
								((*(pThis->gPrivate_getOrderOfElements))(pElement, crx_c_tree_private_getElement(
										pThis, pNode, tIndex - 1)) < 0) : false))
						{
							if(CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH)
							{
								tNode = *(crx_c_tree_private_getChildNode(pThis, pNode, 
										tIndex - 1));
							}
						}
					}
					else
						{tIsNoError = false;}
				}

				if(tIsNoError)
				{
					tIsNoError =
							crx_c_tree_private_transferAndInsertElementEntry__do(
							pThis, tNode, NULL, NULL, pElement);
				}
			}
			else
			{
				*(pIndexOfNodeInParent + 1) = tIndex;

				tIsNoError = crx_c_tree_private_transferAndInsertElementEntry__do(
						pThis, tNode, pIndexOfNodeInParent + 1, NULL, pElement);
			}
		}

		return tIsNoError;
	}
	else
	{
		bool tIsNoError = true;
		Crx_C_Tree_Private_Node * tNode = pNode;

		if(!CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
		{
			if(tNode->gPrivate_numberOfEntries ==
					((2 * pThis->gPrviate_countOfMidElementInNode) - 1))
			{
				uint32_t tResult = crx_c_tree_private_resolveFullNode(pThis,
						tNode, NULL, pIndexOfNodeInParent);

				if(tResult != 0)
				{
					/*NOTE: IN THIS CASE WE ARE DELIBRATELY DECIDING ON THE INSERTION WITH
							">" AND "<" INSTEAD OF ">=" AND "<" THAT WOULD BE PER THE
							ALGORITHM OF Tree::getSuitableImagineryIndexFor(). THIS IS TO
							AVOID RE ASSIGNING TO tNode.
					*/
					if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
					{
						if(((tResult == 1) || (CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH ?
										(tResult == 3) : false)) &&
								((*(pThis->gPrivate_getOrderOfIndices))(pIndex__guide, crx_c_tree_private_getIndexFrom(
										pThis, tNode->gPrivate_node__parent,
										*pIndexOfNodeInParent)) > 0))
						{
							tNode = *(crx_c_tree_private_getChildNode(pThis,
									tNode->gPrivate_node__parent, (*pIndexOfNodeInParent) + 1));
						}
						else if((tResult == 2) && (CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH ?
								((*(pThis->gPrivate_getOrderOfIndices))(pIndex__guide, crx_c_tree_private_getIndexFrom(
										pThis, tNode->gPrivate_node__parent,
										(*pIndexOfNodeInParent) - 1)) < 0) :
								false))
						{
							if(CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH)
							{
								tNode = *(crx_c_tree_private_getChildNode(pThis,
										tNode->gPrivate_node__parent, (*pIndexOfNodeInParent) - 1));
							}
						}
					}
					else
					{
						if(((tResult == 1) || (CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH ?
										(tResult == 3) : false)) &&
								((*(pThis->gPrivate_getOrderOfElements))(pElement, crx_c_tree_private_getElement(
										pThis, tNode->gPrivate_node__parent,
										*pIndexOfNodeInParent)) > 0))
						{
							tNode = *(crx_c_tree_private_getChildNode(pThis,
									tNode->gPrivate_node__parent, (*pIndexOfNodeInParent) + 1));
						}
						else if((tResult == 2) && (CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH ?
								((*(pThis->gPrivate_getOrderOfElements))(pElement, crx_c_tree_private_getElement(
										pThis, tNode->gPrivate_node__parent,
										(*pIndexOfNodeInParent) - 1)) < 0) :
								false))
						{
							tNode = *(crx_c_tree_private_getChildNode(pThis,
									tNode->gPrivate_node__parent, (*pIndexOfNodeInParent) - 1));
						}
					}
				}
				else
					{tIsNoError = false;}
			}
		}

		if(tIsNoError)
		{
			if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
			{
				size_t tImaginaryIndex =
						crx_c_tree_private_getSuitableImagineryIndexFor(
						pThis, tNode, NULL, pIndex__guide, NULL);

				if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
				{
					crx_c_tree_private_transferAllIntoNode(pThis,
							pIndex__guide, NULL, pElement, tNode, tImaginaryIndex, false);
				}
				else
				{
					crx_c_tree_private_transferAllIntoNode(pThis,
							NULL, NULL, pElement, tNode, tImaginaryIndex, false);
				}
			}
			else
			{
				size_t tImaginaryIndex =
						crx_c_tree_private_getSuitableImagineryIndexFor(
						pThis, tNode, pElement, NULL, NULL);

				crx_c_tree_private_transferAllIntoNode(pThis, NULL, NULL,
						pElement, tNode, tImaginaryIndex, false);
			}

			/*vReturn = crx_c_tree_private_getElement(pThis, tNode, tImaginaryIndex);*/
			return true;
		}
		else
			{return false;}
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_tree_tryMoveAndInsertElement(Crx_C_Tree * pThis,
		void * CRX_NOT_NULL pElement)
{
	if((pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL) || 
			CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
	{
		unsigned char * tElement = (CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ?
				((unsigned char *)calloc(1, pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE)) :
				((unsigned char *)CRX__ALLOCA(pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE)));

		if(tElement != NULL)
		{
			if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT))(tElement, 
						pElement);
			}
			else
			{
				memcpy(tElement, pElement, pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
			}

			if(crx_c_tree_private_transferAndInsertElementEntry(pThis, tElement))
				{return true;}
			else
			{
				if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL)
					{(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT))(pElement);}

				if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)
				{
					(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT))(pElement, 
							tElement);
				}
				else
				{
					memcpy(pElement, tElement, pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);
				}

				if(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL)
				{
					(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT))(
							tElement);
				}

				if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
					{free(tElement);}

				return false;
			}
		}
		else
			{return false;}
	}
	else
		{return crx_c_tree_private_transferAndInsertElementEntry(pThis, pElement);}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_tree_insertElement(Crx_C_Tree * pThis,
		void * CRX_NOT_NULL pElement)
{
	CRX_SCOPE_META
	assert(pThis->gPrivate_typeBluePrint__element->gIS_COPYABLE);

	CRX_SCOPE
	unsigned char * vElement = (CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ?
				((unsigned char *) calloc(1, pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE)) :
				(((pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != NULL) ||
						(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL) || 
						(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL)) ?
						((unsigned char *) CRX__ALLOCA(pThis->gPrivate_typeBluePrint__element->
								gBYTE_SIZE)) :
						NULL));
	bool vReturn /*= ?*/;

	if(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(*(pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT))(vElement, pElement);

		vReturn = crx_c_tree_private_transferAndInsertElementEntry(pThis, vElement);
	}
	else
	{
		if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ||
				(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL) || 
				(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL))
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE);

			vReturn = crx_c_tree_private_transferAndInsertElementEntry(pThis, vElement);
		}
		else
		{
			return crx_c_tree_private_transferAndInsertElementEntry(pThis,
					pElement);
		}
	}

	if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT || 
			((pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL) && 
					((pThis->gPrivate_typeBluePrint__element->gFUNC__COPY_CONSTRUCT != NULL) || 
					(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT != NULL) ||
					(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT != NULL))))
	{
		if(!vReturn)
		{
			if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
				{(*(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(vElement);}

			if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
				{free(vElement);}
		}
	}

	return vReturn;
	CRX_SCOPE_END
}

CRX__LIB__PRIVATE_C_FUNCTION() Crx_C_Tree_Private_Node * 
		crx_c_tree_mergeTwoNodesAndGetRemainingNode(Crx_C_Tree * pThis, 
		Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode, size_t pIndex)
{
	CRX_SCOPE_META
	assert(pNode->gPrivate_type);

	CRX_SCOPE
	Crx_C_Tree_Private_Node * tNode__left = *(crx_c_tree_private_getChildNode(pThis,
			pNode, pIndex));
	Crx_C_Tree_Private_Node * tNode__right = *(crx_c_tree_private_getChildNode(pThis,
			pNode, pIndex + 1));
	bool vIsToRotateRight = (CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ?
			((pNode->gPrivate_numberOfEntries >> 1) > pIndex) : false);

	/*WE HAVE TO CONSIDER THE NON PR EMPTIVE CASE, HENCE NO STRICT '==' WITH
			"gPrivate_numberOfEntries - 1", AND INSTEAD WHEN USES '<' WITH
			"gPrivate_numberOfEntries"*/
	assert((tNode__left->gPrivate_numberOfEntries <
					pThis->gPrviate_countOfMidElementInNode) &&
			(tNode__right->gPrivate_numberOfEntries <
					pThis->gPrviate_countOfMidElementInNode));

	if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			/*NOTES:
				- NULL IS ACTUALLY INSERTED FOR THE NODE IN THIS CASE UNLIKE ELSEWHERE IN THE
						CODE.
				- STRICTLY, WE WOULD NEED TO CHECK FOR CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY BUT
						THERE IS UNLIKELY A PERFORMANCE COST SAVING OF CHECKING WHETHER THE
						CHILD NODE IS A LEAF AND THEN PASSING NULL OR THE INDEX, OR JUST
						IMMEDIATELY PASSING AN INDEX AND RELYING ON transferAllIntoNode() TO
						SIMPLY IGNORE IT.
			*/
			crx_c_tree_private_transferAllIntoNode(
					pThis,
					crx_c_tree_private_getIndexFrom(pThis, pNode, pIndex),
					NULL,
					crx_c_tree_private_getElement(pThis, pNode, pIndex),
					tNode__left,
					tNode__left->gPrivate_numberOfEntries, false);

			crx_c_tree_private_removeSpaceFrom(pThis, 
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
					pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
					pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
					pNode,
					crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
					pNode->gPrivate_numberOfEntries, pIndex, 1, vIsToRotateRight);
		}
		else
		{
			/*NOTE: NULL IS ACTUALLY INSERTED FOR THE NODE IN THIS
					CASE UNLIKE ELSEWHERE IN THE CODE.*/
			crx_c_tree_private_transferAllIntoNode(pThis, NULL,
					NULL,
					crx_c_tree_private_getElement(pThis, pNode, pIndex),
					tNode__left,
					tNode__left->gPrivate_numberOfEntries, false);

			crx_c_tree_private_removeSpaceFrom(pThis,
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) :
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
					pNode,
					crx_c_tree_private_getElementEntry(pThis, pNode, 0),
					pNode->gPrivate_numberOfEntries, pIndex, 1, vIsToRotateRight);
		}

		/*(tNode__left->gPrivate_numberOfEntries)++;*/

		crx_c_tree_private_removeSpaceFrom(pThis,
				sizeof(Crx_C_Tree_Private_Node *),
				CRXM__FALSE, CRXM__FALSE,
				pNode,
				((unsigned char *)crx_c_tree_private_getChildNode(pThis, pNode, 0)),
				pNode->gPrivate_numberOfEntries + 1, pIndex + 1, 1, vIsToRotateRight);

		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			crx_c_tree_private_removeSpaceFrom(pThis,
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) :
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
					pNode,
					crx_c_tree_private_getElementEntry(pThis, pNode, 0),
					pNode->gPrivate_numberOfEntries, pIndex, 1, vIsToRotateRight);
		}

		crx_c_tree_private_updateStartIndexAfterRemovalOfSpace(pThis, pNode, 1, vIsToRotateRight);

		crx_c_tree_private_transferPushFromNodeToNode(
				pThis, tNode__right, tNode__left, true, 0);
	}
	else
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			if(tNode__left->gPrivate_type)
			{
				crx_c_tree_private_transferAllIntoNode(pThis,
						crx_c_tree_private_getIndexFrom(pThis, pNode, pIndex),
						NULL,
						NULL,
						tNode__left,
						tNode__left->gPrivate_numberOfEntries, true);
			}

			crx_c_tree_private_removeSpaceFrom(pThis,
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
					pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
					pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
					pNode,
					crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
					pNode->gPrivate_numberOfEntries, pIndex, 1, vIsToRotateRight);
		}
		else
		{
			if(tNode__left->gPrivate_type)
			{
				/*NOTE: NULL IS ACTUALLY INSERTED FOR THE NODE IN THIS
						CASE UNLIKE ELSEWHERE IN THE CODE.*/
				crx_c_tree_private_transferAllIntoNode(pThis, NULL,
						NULL,
						crx_c_tree_private_getElement(pThis, pNode, pIndex),
						tNode__left,
						tNode__left->gPrivate_numberOfEntries, true);
			}
			else
			{
				if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ||
						!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
				{
					if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
					{
						(*(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(
								crx_c_tree_private_getElement(pThis, pNode, pIndex));
					}

					if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
						{free(crx_c_tree_private_getElement(pThis, pNode, pIndex));}
				}
			}

			crx_c_tree_private_removeSpaceFrom(pThis,
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) :
							pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_CONSTRUCT),
					(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT),
					pNode,
					crx_c_tree_private_getElementEntry(pThis, pNode, 0),
					pNode->gPrivate_numberOfEntries, pIndex, 1, vIsToRotateRight);
		}

		/*(tNode__left->gPrivate_numberOfEntries)++;*/

		crx_c_tree_private_removeSpaceFrom(pThis,
				sizeof(Crx_C_Tree_Private_Node *),
				CRXM__FALSE, CRXM__FALSE,
				pNode,
				((unsigned char *)crx_c_tree_private_getChildNode(pThis, pNode, 0)),
				pNode->gPrivate_numberOfEntries + 1, pIndex + 1, 1, vIsToRotateRight);

		crx_c_tree_private_updateStartIndexAfterRemovalOfSpace(pThis, pNode, 1, vIsToRotateRight);

		crx_c_tree_private_transferPushFromNodeToNode(
				pThis, tNode__right, tNode__left, true, 0);

		if(tNode__left->gPrivate_type == 0)
		{
			((Crx_C_Tree_Private_LeafNode *)tNode__left)->gPrivate_leafNode__next =
					((Crx_C_Tree_Private_LeafNode *)tNode__right)->
							gPrivate_leafNode__next;

			if(((Crx_C_Tree_Private_LeafNode *)tNode__right)->
					gPrivate_leafNode__next != NULL)
			{
				((Crx_C_Tree_Private_LeafNode *)tNode__right)->
						gPrivate_leafNode__next->gPrivate_leafNode__prev =
						((Crx_C_Tree_Private_LeafNode *)tNode__left);
			}
		}
	}

	tNode__left->gPrivate_numberOfEntries +=
			tNode__right->gPrivate_numberOfEntries;

	--(pNode->gPrivate_numberOfEntries);

	free(tNode__right);
	tNode__right = NULL;

	--(pThis->gPrivate_numberOfNodes);

	return tNode__left;

	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_tree_removeElement(Crx_C_Tree * pThis,
		void const * CRX_NOT_NULL pElement)
{
	unsigned char * vIndex__guide = (CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX ? 
			((unsigned char *)CRX__ALLOCA(pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE)) :
			NULL);
	Crx_C_Tree_Iterator vIterator /*= ?*/;
	Crx_C_Tree_Iterator_Private_Position * vPositions = 
			((!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY && CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX) ?
			((Crx_C_Tree_Iterator_Private_Position *)CRX__ALLOCA(
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE * 64)) :
			NULL);
	bool vReturn /*= ?*/;

	if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{(*(pThis->gPrivate_constructIndexFrom))(vIndex__guide, pElement);}
	if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY && CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{crx_c_tree_iterator_private_construct3(&vIterator, &(vPositions[0]), pThis);}

	if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				vReturn = crx_c_tree_private_removeElement__do(pThis, 0,
						pThis->gPrivate_node__root, vIndex__guide,
						((unsigned char *)pElement), &vIterator, NULL, NULL);
			}
			else
			{
				vReturn = crx_c_tree_private_removeElement__do(pThis, 0,
						pThis->gPrivate_node__root, vIndex__guide,
						((unsigned char *)&pElement), &vIterator, NULL, NULL);
			}
		}
		else
		{
			if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				vReturn = crx_c_tree_private_removeElement__do(pThis, 0,
						pThis->gPrivate_node__root, NULL, 
						((unsigned char *)pElement), NULL, NULL, NULL);
			}
			else
			{
				vReturn = crx_c_tree_private_removeElement__do(pThis, 0,
						pThis->gPrivate_node__root, NULL, 
						((unsigned char *)&pElement), NULL, NULL, NULL);
			}
		}
	}
	else
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				vReturn = crx_c_tree_private_removeElement__do(pThis, 0,
						pThis->gPrivate_node__root, vIndex__guide, 
						((unsigned char *)pElement), NULL, NULL, NULL);
			}
			else
			{
				vReturn = crx_c_tree_private_removeElement__do(pThis, 0,
						pThis->gPrivate_node__root, vIndex__guide, 
						((unsigned char *)pElement), NULL, NULL, NULL);
			}
		}
		else
		{
			if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				vReturn = crx_c_tree_private_removeElement__do(pThis, 0,
						pThis->gPrivate_node__root, NULL, 
						((unsigned char *)pElement), NULL, NULL, NULL);
			}
			else
			{
				vReturn = crx_c_tree_private_removeElement__do(pThis, 0,
						pThis->gPrivate_node__root, NULL, 
						((unsigned char *)pElement), NULL, NULL, NULL);
			}
		}
	}

	if(vReturn)
	{
		--pThis->gPrivate_numberOfElements;

		/*HAPPENS WHEN WE HAVE ONE LEAF NODE ATTACHED TO THE ROOT, AN INTERNAL NODE.*/
		if((pThis->gPrivate_node__root->gPrivate_numberOfEntries == 0) &&
				(pThis->gPrivate_node__root->gPrivate_type))
		{
			Crx_C_Tree_Private_Node * tNode = pThis->gPrivate_node__root;

			pThis->gPrivate_node__root = *(crx_c_tree_private_getChildNode(pThis,
					tNode, 0));
			if(!CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
				{pThis->gPrivate_node__root->gPrivate_node__parent = NULL;}

			(pThis->gPrivate_numberOfNodes)--;

			free(tNode);
		}
	}

	return vReturn;
}
CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_tree_private_removeElement__do(
		Crx_C_Tree * pThis, uint32_t pMode, Crx_C_Tree_Private_Node * pNode,
		void * pIndex__guide, void * pElement,
		Crx_C_Tree_Iterator * pIterator,
		void * pIndex__out, void * pElement__out)
{
	assert(CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY || !CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX ||
			((pIndex__out == NULL) && (pElement__out == NULL)));
	assert(CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY || CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX ||
			((pIndex__guide == NULL) && (pIterator == NULL) && (pIndex__out == NULL) && 
			(pElement__out == NULL)));
	assert(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY || !CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX ||
			((pIterator == NULL) && (pElement__out == NULL)));
	assert(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY || CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX ||
			((pIndex__guide == NULL) && (pIterator == NULL) && (pIndex__out == NULL)));

	/*if(pNode == NULL)
		{return *pKey;}
	else*/

	if(pNode != NULL)
	{
		size_t tImaginaryIndex;
		int32_t tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 0;

		/*if(pMode)
		{ /* pMode can only be 0, 1 or 2 * /
			tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode =
					((pNode->gPrivate_type == 0) ? 0 : ((pMode == 1) ? 1 : -1));
			tImaginaryIndex = ((pMode == 1) ? (pNode->gPrivate_numberOfEntries /*- 1* /) : 0/*-1* /);
		}*/
		if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
		{
			if(pMode == 1)
			{
				if(pNode->gPrivate_type)
					{tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 1;}

				tImaginaryIndex = pNode->gPrivate_numberOfEntries /*- 1*/;
			}
			else if(pMode == 2)
			{
				if(pNode->gPrivate_type)
				{
					tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = -1;
					tImaginaryIndex = 0 /*-1*/;
				}
				else
					{tImaginaryIndex = 1 /*0*/;}
			}
			else /*pMode == 0*/
			{
				if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
				{
					tImaginaryIndex =
							crx_c_tree_private_getSuitableImagineryIndexFor(
							pThis, pNode, NULL, pIndex__guide,
							&tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode);
				}
				else
				{
					tImaginaryIndex =
							crx_c_tree_private_getSuitableImagineryIndexFor(pThis, pNode, 
							(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? *((unsigned char * *)(pElement)) : 
							pElement), NULL, &tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode);
				}
			}
		}
		else
		{
			/* if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
			{
				tImaginaryIndex =
						crx_c_tree_private_getSuitableImagineryIndexFor(
						pThis, pNode, NULL, pIndex__guide,
						&tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode);
			}
			else
			{
				tImaginaryIndex =
						crx_c_tree_private_getSuitableImagineryIndexFor(pThis, pNode,
						pElement, NULL, &tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode);
			} */

			/*UNLIKE THE ABOVE CODE, THE FOLLOWING ASSUMES THAT THE ELEMENT FROM THE LEAVES
					THAT WAS COPIED TO THE INTERNAL NODES REMAINS AT THE RIGHT MOST EDGE OF
					THE LEAF THAT IT IS IN NO MATTER HOW MUCH SPLITTING HAPPENS OR THE COPY
					MOVES THE TREE RELATIVE TO THE LEAVES.*/
			if(pMode == 1)
			{
				/*SHOULD NOT HAPPEN*/
				assert(false);
				if(pNode->gPrivate_type)
					{tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 1;}

				tImaginaryIndex = pNode->gPrivate_numberOfEntries /*- 1*/;
			}
			if(pMode == 2)
			{
				if(pNode->gPrivate_type)
				{
					tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = -1;
					tImaginaryIndex = 0 /*-1*/;
				}
				else
					{tImaginaryIndex = 1 /*0*/;}
			}
			else
			{
				if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
				{
					tImaginaryIndex =
							crx_c_tree_private_getSuitableImagineryIndexFor(
							pThis, pNode, NULL, pIndex__guide,
							&tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode);
				}
				else
				{
					tImaginaryIndex =
							crx_c_tree_private_getSuitableImagineryIndexFor(pThis, pNode, 
							pElement, NULL, &tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode);
				}
			}
		}

		if(pNode->gPrivate_type)
		{
			bool tIsDone = false;
			bool tReturn = false;

			if((tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0) &&
					(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY || (pMode == 0)))
			{
				/*EVEN WHEN ELEMENT DATA IS NOT IN LEAVES ONLY, pMode MUST ALSO BE 0 IF WE ARE
						HERE. THIS IS BECAUSE WE ARE STICKING TO THE FIRST FOUND ENTRY IN THE
						INTERNAL NODES IN THAT CASE.
						NOTE THAT THIS WAS NECESSARY WHEN THE ALGORITHM CONTINUED TO DO A
						BINARY SEARCH IN THE CASE WHEN MODE WAS NOT ZERO AND ELEMENT DATA WAS
						IN LEAVES. LATER I CHANED THAT, BUT KEEPING THE CODE ABOVE IN THE IF
						CONDITION, AND THE ASSERTION BELOW, FOR THE TIME BEING.
				*/
				CRX_SCOPE_META
				assert(pMode == 0);

				CRX_SCOPE
				size_t tNumberOfKeysInLeftNode = 0;
				size_t tNumberOfKeysInRightNode = (*(crx_c_tree_private_getChildNode(pThis,
						pNode, tImaginaryIndex /*+ 1*/)))->gPrivate_numberOfEntries;
				int32_t tBranchToTake = -2;	/*-2: non,  -1: left,  0: merge and try again,
											1: right*/
				bool tIsFound = false;

				if(CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY && 
						CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
				{
					if(tNumberOfKeysInRightNode < pThis->gPrviate_countOfMidElementInNode)
					{
						tNumberOfKeysInLeftNode = (*(crx_c_tree_private_getChildNode(pThis,
								pNode, tImaginaryIndex - 1)))->gPrivate_numberOfEntries;

						if(tNumberOfKeysInLeftNode >= pThis->gPrviate_countOfMidElementInNode)
						{
							crx_c_tree_private_rotateRight(pThis,
									*(crx_c_tree_private_getChildNode(pThis, pNode,
											tImaginaryIndex - 1)),
									tImaginaryIndex - 1, pNode,
									*(crx_c_tree_private_getChildNode(pThis, pNode,
											tImaginaryIndex /*+ 1*/)));

							if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
							{
								tReturn =
										crx_c_tree_private_removeElement__do(pThis, 
										0, pNode, pIndex__guide, pElement, NULL, NULL, NULL);
							}
							else
							{
								tReturn =
										crx_c_tree_private_removeElement__do(pThis, 
										0, pNode, NULL, pElement, NULL, NULL, NULL);
							}

							tIsDone = true;
						}
					}
				}

				/*THE FOLLOWING CHECK FOR tIsDone IS ONLY REQUIRED WHEN DATA IS IN THE 
						LEAVES ONLY, BUT TO KEEP THINGS SIMPLE THE CHECK IS ALWAYS DONE.
				*/
				if(!tIsDone)
				{
					if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY &&
							CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
					{
						crx_c_tree_iterator_private_depthPush(pIterator,
								pNode, tImaginaryIndex - 1);
					}

					if(tNumberOfKeysInRightNode >= pThis->gPrviate_countOfMidElementInNode)
						{tBranchToTake = 1;}
					else
					{
						if(CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
						{
							if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
							{
								tNumberOfKeysInLeftNode = (*(crx_c_tree_private_getChildNode(
										pThis, pNode, 
										tImaginaryIndex - 1)))->gPrivate_numberOfEntries;

								if(tNumberOfKeysInLeftNode >=
										pThis->gPrviate_countOfMidElementInNode)
									{tBranchToTake = -1;}
								else
									{tBranchToTake = 0;}
							}
							else
							{
								assert((tNumberOfKeysInLeftNode > 0) &&
										(tNumberOfKeysInLeftNode <
												pThis->gPrviate_countOfMidElementInNode));

								tBranchToTake = 0;
							}
						}
						else
						{
							if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
							{
								tBranchToTake = -1;
							}
							else
							{
								tBranchToTake = 1;
							}
						}
					}

					if(tBranchToTake != 0)
					{
						if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
						{
							if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
							{
								Crx_C_Tree_Iterator tIterator /*= ?*/;
								unsigned char * tPositions /*= ?*/;
								uint32_t tResult /*= ?*/;

								/*THIS IS FORMAL VIOLATION. THIS IS DONE BECAUSE WE CAN NOT
								GUARANTEE WHEN THE ALLOCATION OF THE LARGE BUFFER HAPPENS
								ON THE STACK, AND IT MIGHT END UP HAPPENING IN EVERY
								ITERATION*/
								tPositions = ((unsigned char *) CRX__ALLOCA(sizeof(
										Crx_C_Tree_Iterator_Private_Position) * 64));
								crx_c_tree_iterator_private_construct3(&tIterator,
										((Crx_C_Tree_Iterator_Private_Position *)tPositions), 
										pThis);

								tResult =
										crx_c_tree_private_removeElement__do__findExactEntry(
										pThis, pIndex__guide, pElement, pIterator, &tIterator);

								if(tResult != 0)
								{
									if(tResult == 1)
									{
										if(pThis->gPrivate_typeBluePrint__element->
												gFUNC__DESTRUCT != NULL)
										{
											(*(pThis->gPrivate_typeBluePrint__element->
													gFUNC__DESTRUCT))(
													crx_c_tree_private_getElement(
													pThis, pNode, tImaginaryIndex - 1));
										}

										if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
										{
											free(crx_c_tree_private_getElement(pThis,
													pNode, tImaginaryIndex - 1));
										}
									}
									else
									{
										assert(tResult == 2);

										if(pThis->gPrivate_typeBluePrint__element->
												gFUNC__DESTRUCT != NULL)
										{
											(*(pThis->gPrivate_typeBluePrint__element->
													gFUNC__DESTRUCT))(crx_c_tree_iterator_get(
													&tIterator));
										}

										if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
											{free(crx_c_tree_iterator_get(&tIterator));}

										if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY ||
												crx_c_tree_iterator_private_isInInternalNode(
												&tIterator))
										{
											crx_c_tree_private_transferConstruct(pThis,
													pThis->gPrivate_typeBluePrint__index->
															gBYTE_SIZE,
													pThis->gPrivate_typeBluePrint__index->
															gFUNC__MOVE_CONSTRUCT,
													pThis->gPrivate_typeBluePrint__index->
															gFUNC__MOVE_DESTRUCT,
													crx_c_tree_iterator_private_getIndex(
															&tIterator),
													crx_c_tree_private_getIndexFrom(pThis,
															pNode, tImaginaryIndex - 1));
										}

										crx_c_tree_private_transferConstruct(pThis,
												(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? 
														sizeof(volatile void const *) : 
														pThis->gPrivate_typeBluePrint__element->
														gBYTE_SIZE),
												(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
														pThis->gPrivate_typeBluePrint__element->
														gFUNC__MOVE_CONSTRUCT),
												(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
														pThis->gPrivate_typeBluePrint__element->
														gFUNC__MOVE_DESTRUCT),
												crx_c_tree_iterator_private_getEntry(
														&tIterator),
												crx_c_tree_private_getElementEntry(pThis,
														pNode, tImaginaryIndex - 1));
									}

									tIsFound = true;
								}

								crx_c_tree_iterator_destruct(&tIterator);
							}
							else
							{
								if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
								{
										(*(pThis->gPrivate_typeBluePrint__element->
												gFUNC__DESTRUCT))(crx_c_tree_private_getElement(
												pThis, pNode, tImaginaryIndex - 1));
								}

								if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
								{
									free(crx_c_tree_private_getElement(pThis,
											pNode, tImaginaryIndex - 1));
								}

								tIsFound = true;
							}
						}
						else
						{
							/*NOTICE: EFFECTIVELY WE ARE TREATING TWO EQUAL INDICES AS IF THEY
									ARE BYTE WISE EQUAL. THIS IS CONTRARY TO ALMOST EVERY
									WHERE, IF NOT EVERY WHERE, ELSE IN THE CODE. IF OTHER
									WORDS, WHEN THE TREE HAS AN INDEX WE DO NOT ATTEMPT TO
									CHECK IF IT IS EXACTLY THE INDEX THAT IS CREATED FROM THE
									ELEMENT THAT WE SHALL EVENTUALLY REMOVE FROM A LEAF.
									INSTEAD, WE REASON THAT WHATEVER THAT INDEX IS IT MUST BE
									EQUAL UNDER THE INDEX ORDERING TO THE ONE FOUND HERE, BUT
									THIS EFFECTIVELY ASSUMES BYTE WISE EQUALITY ALSO.*/

							if(!CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
							{
								if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
								{
									if((pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != 
											NULL) && CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
									{
										(*(pThis->gPrivate_typeBluePrint__element->
												gFUNC__DESTRUCT))(crx_c_tree_private_getElement(
												pThis, pNode, tImaginaryIndex - 1));
									}
								}
								else
								{
									if(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
									{
										*((unsigned char * *)crx_c_tree_private_getElementEntry(
												pThis, pNode, tImaginaryIndex - 1)) = NULL;
									}
								}
							}

							tIsFound = true;
						}
					}

					if(tBranchToTake == 1)
					{
						if(tIsFound)
						{
							if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
							{
								/*vKey = __KB_KEY(pGUIDE_TYPE, pNode)[tImaginaryIndex - 1];*/
								if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
								{
									/*NOTE THAT THE NEXT NODE WE GO INTO IS tImaginaryIndex,
											NOT tImaginaryIndex - 1. BUT BECAUSE
											name__findExactEntry() WILL EXPECT THE
											CURRENT CHILD NODE INDEX IN pIterator TO BE THE
											KEY INDEX OF THE FOUND INDEX(GUIDE), WE PUSHED
											tImaginaryIndex - 1 EARLIER INSTEAD.
									*/
									crx_c_tree_iterator_private_depthPop(pIterator);

									crx_c_tree_iterator_private_depthPush(
											pIterator, pNode, tImaginaryIndex /*+ 1*/);

									tReturn =
											crx_c_tree_private_removeElement__do(
											pThis, 2,
											*(crx_c_tree_private_getChildNode(pThis, pNode,
													tImaginaryIndex /*+ 1*/)),
											crx_c_tree_private_getIndexFrom(pThis, pNode,
													tImaginaryIndex - 1),
											crx_c_tree_private_getElementEntry(pThis,
													pNode, tImaginaryIndex - 1),
											pIterator, NULL, NULL);
								}
								else
								{
									tReturn = crx_c_tree_private_removeElement__do(
											pThis, 2,
											*(crx_c_tree_private_getChildNode(pThis, pNode,
													tImaginaryIndex /*+ 1*/)),
											NULL,
											crx_c_tree_private_getElementEntry(pThis,
													pNode, tImaginaryIndex - 1),
											NULL, NULL, NULL);
								}

								/*return vKey;*/
							}
							else
							{
								/*IT IS NOT IMPORTANT THAT THE VERY SAME ELEMENT THAT WE THE 
										INDEX FROM TO STORE IN THE INTERNAL NODE BE THE ONE
										FOUND. HENCE, WHEN CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX, NO SEARCHING FOR THE 
										EXACT ENTRY IS DONE.*/

								if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
								{
									crx_c_tree_private_removeElement__do(
											pThis, 2,
											*(crx_c_tree_private_getChildNode(pThis, pNode,
													tImaginaryIndex /*+ 1*/)),
											pIndex__guide, pElement, NULL,
											(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION ?
													crx_c_tree_private_getIndexFrom(pThis,
													pNode, tImaginaryIndex - 1) : NULL),
											NULL);
								}
								else
								{
									crx_c_tree_private_removeElement__do(
											pThis, 2,
											*(crx_c_tree_private_getChildNode(pThis, pNode,
													tImaginaryIndex /*+ 1*/)),
											NULL, pElement, NULL, 
											NULL,
											(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION ?
													crx_c_tree_private_getElementEntry(pThis,
													pNode, tImaginaryIndex - 1) : NULL));
								}
							}
							/*vKey = __KB_KEY(pGUIDE_TYPE, pNode)[tImaginaryIndex - 1];*/

							/*return vKey;*/
							if(CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
								{tIsDone = true;}
						}
						else
							{tIsDone = true;}
					}
					else if(tBranchToTake == -1)
					{
						if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
						{
							if(tIsFound)
							{
								if(tNumberOfKeysInLeftNode == 0)
								{
									tNumberOfKeysInLeftNode = (*(crx_c_tree_private_getChildNode(
											pThis, pNode, tImaginaryIndex - 1)))->
											gPrivate_numberOfEntries;
								}

								if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
								{
									tReturn = crx_c_tree_private_removeElement__do(
											pThis, 1,
											*(crx_c_tree_private_getChildNode(pThis, pNode,
													tImaginaryIndex - 1)),
											crx_c_tree_private_getIndexFrom(pThis, pNode,
													tImaginaryIndex - 1),
											crx_c_tree_private_getElementEntry(pThis,
													pNode, tImaginaryIndex - 1),
											pIterator, NULL, NULL);
								}
								else
								{
									tReturn = crx_c_tree_private_removeElement__do(
											pThis, 1,
											*(crx_c_tree_private_getChildNode(pThis, pNode,
													tImaginaryIndex - 1)),
											NULL,
											crx_c_tree_private_getElementEntry(pThis,
													pNode, tImaginaryIndex - 1),
											NULL, NULL, NULL);
								}

								if(CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
									{tIsDone = true;}
								else
								{
									/*WARNING: tImaginaryIndex HERE CHANGES ITS SEMANTICS*/
									tImaginaryIndex = tImaginaryIndex - 1;
								}
							}
							else
								{tIsDone = true;}
						}
						else
							{assert(false);}
					}
					else
					{
						if(CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
						{
							assert(tBranchToTake == 0);

							/*THE FOLLOWING SHOULD ALWAYS BE TRUE IF I AM NOT WRONG, BUT
									STICKING TO REFERENCE FOR NOW*/
							if((tNumberOfKeysInLeftNode ==
											pThis->gPrviate_countOfMidElementInNode - 1) &&
									(tNumberOfKeysInRightNode ==
											pThis->gPrviate_countOfMidElementInNode - 1))
							{
								Crx_C_Tree_Private_Node * tNode__left =
										crx_c_tree_mergeTwoNodesAndGetRemainingNode(
										pThis, pNode, tImaginaryIndex - 1);

								/*return crx_c_tree_private_removeElement__do(
										pMode, pThis, tNode__left, pKey)*/
								if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
								{
									if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
									{
										tReturn =
												crx_c_tree_private_removeElement__do(
												pThis, 0 /*pMode*/, tNode__left, pIndex__guide,
												pElement, pIterator, NULL, NULL);
									}
									else
									{
										tReturn =
												crx_c_tree_private_removeElement__do(
												pThis, 0 /*pMode*/, tNode__left, NULL, 
												pElement, NULL, NULL, NULL);
									}
								}
								else
								{
									if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
									{
										tReturn =
												crx_c_tree_private_removeElement__do(
												pThis, 0 /*pMode*/, tNode__left, pIndex__guide,
												pElement, NULL, pIndex__out, NULL);
									}
									else
									{
										tReturn =
												crx_c_tree_private_removeElement__do(
												pThis, 0 /*pMode*/, tNode__left, NULL, 
												pElement, NULL, NULL, pElement__out);
									}
								}

								tIsDone = true;
							}
							else
								{assert(false);}
						}
					}

					if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY &&
							CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
						{crx_c_tree_iterator_private_depthPop(pIterator);}
				}
				CRX_SCOPE_END
			}
			else
			{
				if(!CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
				{
					if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
					{
						if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
						{
							crx_c_tree_iterator_private_depthPush(pIterator,
									pNode, tImaginaryIndex /*+ 1*/);

							tReturn = crx_c_tree_private_removeElement__do(
									pThis, pMode,
									*(crx_c_tree_private_getChildNode(pThis, pNode,
											tImaginaryIndex /*+ 1*/)),
									pIndex__guide, pElement, pIterator, NULL, NULL);

							crx_c_tree_iterator_private_depthPop(pIterator);
						}
						else
						{
							tReturn = crx_c_tree_private_removeElement__do(
									pThis, pMode,
									*(crx_c_tree_private_getChildNode(pThis, pNode,
											tImaginaryIndex /*+ 1*/)),
									NULL, pElement, NULL, NULL, NULL);
						}
					}
					else
					{
						if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
						{
							tReturn = crx_c_tree_private_removeElement__do(
									pThis, pMode,
									*(crx_c_tree_private_getChildNode(pThis, pNode,
											tImaginaryIndex /*+ 1*/)),
									pIndex__guide, pElement, NULL, pIndex__out, NULL);
						}
						else
						{
							tReturn = crx_c_tree_private_removeElement__do(
									pThis, pMode,
									*(crx_c_tree_private_getChildNode(pThis, pNode,
											tImaginaryIndex /*+ 1*/)),
									NULL, pElement, NULL, NULL, pElement__out);
						}
					}
				}
			}

			if(!tIsDone)
			{
				/*TO EASE ANALYSIS, 
					- REMEMBER THAT tNode BELOW IS ALWAYS THE NODE TO THE RIGHT
							OF THE 'FOUND' ENTRY POSITION. THE ONLY EXCEPTION IS WHEN THE
							ALGORITHM IS NOT PRE EMPTIVE, AND THE ELEMENT HAS ALREADY BEEN
							FOUND ABOVE, AND ENTRIES ARE NOT STORED IN THE LEAVES ONLY AND THE
							ALGORITHM ABOVE CHOOSE TO TAKE THE LEFT BRANCH TO HOIST AN ELEMENT
							BACK UP.
					- IF CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE AND (pMode == 0) AND
							(tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0)
							WE SHOULD NOT BE HERE AT ALL.
					- IF PRIMARY ENTRIES ARE NOT IN THE LEAVES ONLY, AND
							(tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0)
							IT IS GUARANTEED THAT WE ARE AT THE END OF THE TRACE THAT IS IN
							THE ITERATOR. IN OTHER WORDS, THE INDEX IN THE TRACE AT THAT
							POINT, MEANING Iterator::Position::gIndex, IS THE INDEX OF THE
							ELEMENT, AND NOT THE INDEX OF THE NEXT CHILD NODE AS IT IS
							OTHERWISE. IF PRIMARY ENTRIES ARE IN THE LEAVES ONLY, THEN
							REGARDLESS OF THE VALUE OF
							tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode THE INDEX IN
							THE TRACE THAT IS IN THE ITERATOR AT THAT POINT, MEANING
							Iterator::Position::gIndex, IS THE INDEX OF THE NEXT NODE.
				*/

				Crx_C_Tree_Private_Node * tNode;

				/*WARNING: tImaginaryIndex CHANGES ITS SEMANTICS HERE. IN THE NON PREMTIVE
						CASE, tImaginaryIndex WOULD HAVE ALREADY BEEN DECREMENTED ONCE IF THE
						CODE ABOVE WENT DOWN THE LEFT NODE RELATIVE TO THE FOUND RECORD.
						AFTER THE FOLLOWING, tImaginaryIndex IS GUARANTEED TO BE THE INDEX OF
						THE NODE THAT WILL BE TAKEN NEXT, IN THE PRE EMPTIVE CASE, OR
						HAS BEEN TAKEN IN THE NON PRE EMPTIVE CASE.
				*/
				/*i++;*/

				tNode = *(crx_c_tree_private_getChildNode(pThis, pNode, tImaginaryIndex));

				/*WE HAVE TO USE '<=' INSTEAD OF '==' BECAUSE WE COULD BE FIXING UNDER FILLED 
						NODES AFTER THE FACT, MEANING THE ALGORITHM IS NOT PRE EMPTIVE.*/
				if(tNode->gPrivate_numberOfEntries <=
						pThis->gPrviate_countOfMidElementInNode - 1)
				{
					assert(tNode->gPrivate_numberOfEntries >=
							pThis->gPrviate_countOfMidElementInNode - 2);

					/*NOTE THAT 'PREVIOUS' AND 'NEXT' AND SIMILAR ARE RELATIVE TO THE
							KEY "FOUND" BY private_getSuitableImagineryIndexFor(), WHICH, AFTER
							tImaginaryIndex CHANGED ITS SEMANTICS ABOVE, IS AT INDEX
							tImaginaryIndex - 1 IN THE PREEMPTIVE CASE.
							IN THE NON PREEMPTIVE CASE, tImaginaryIndex, BEFORE THE CHANGE OF
							SEMANTICS ABOVE, IS EITHER THE INDEX OF THE KEY "FOUND" + 1, OR
							THE INDEX OF THE KEY BEFORE THE BRANCH THAT IS TAKEN TO HOIST AN
							ELEMENT BACK  UP TO WHERE THE KEY WAS ALREADY FOUND + 1, AND HENCE, 
							'PREVIOUS' AND 'NEXT' ARE SIMPLY RELATIVE TO THE KEY AT
							tImaginaryIndex - 1 WHICH IS NOT NECESSARILY THE INDEX OF THE KEY
							FOUND OR "FOUND"
					*/
					if((tImaginaryIndex > 0) &&
							((*(crx_c_tree_private_getChildNode(pThis, pNode,
									tImaginaryIndex - 1)))->gPrivate_numberOfEntries >=
									pThis->gPrviate_countOfMidElementInNode))
					{
						/*ROTATE PREVIOUS CHILD NODE'S LAST KEY AND KEY AND NEXT
								CHILD NODE'S FIRST KEY RIGHT */
						crx_c_tree_private_rotateRight(pThis,
								(*(crx_c_tree_private_getChildNode(pThis, pNode,
										tImaginaryIndex - 1))),
								tImaginaryIndex - 1, pNode, tNode);
					}
					else if((tImaginaryIndex < pNode->gPrivate_numberOfEntries) &&
							((*(crx_c_tree_private_getChildNode(pThis, pNode,
									tImaginaryIndex + 1)))->gPrivate_numberOfEntries >=
									pThis->gPrviate_countOfMidElementInNode))
					{
						/*ROTATE NEXT CHILD NODE'S LAST KEY AND PARENT NODE'S NEXT KEY AND 
								NEXT NEXT CHILD NODE'S FIRST KEY LEFT*/
						crx_c_tree_private_rotateLeft(pThis,
								(*(crx_c_tree_private_getChildNode(pThis, pNode,
										tImaginaryIndex + 1))),
								tImaginaryIndex + 1, pNode, tNode);
					}
					else if((tImaginaryIndex > 0) &&
							((*(crx_c_tree_private_getChildNode(pThis, pNode,
									tImaginaryIndex - 1)))->gPrivate_numberOfEntries ==
							pThis->gPrviate_countOfMidElementInNode - 1))
					{
						/*MERGE PREVIOUS CHILD NODE, KEY, AND NEXT CHILD NODE*/
						tNode = crx_c_tree_mergeTwoNodesAndGetRemainingNode(
								pThis, pNode, tImaginaryIndex - 1);

						tImaginaryIndex = tImaginaryIndex - 1;
					}
					else if((tImaginaryIndex < pNode->gPrivate_numberOfEntries) &&
							((*(crx_c_tree_private_getChildNode(pThis, pNode,
									tImaginaryIndex + 1)))->gPrivate_numberOfEntries ==
							pThis->gPrviate_countOfMidElementInNode - 1))
					{
						/*MERGE NEXT CHILD NODE, NEXT KEY, AND NEXT NEXT CHILD NODE*/
						tNode = crx_c_tree_mergeTwoNodesAndGetRemainingNode(
								pThis, pNode, tImaginaryIndex);
					}
				}

				/*
					NOTE THAT THE CODE ABOVE TAKES CARE OF THE IREGULAR SITUATION OF A NODE
					HAVING NO KEYS, MAKING gPrivate_numberOfEntries == 0, WHILE STILL
					HAVING ONE NODE. IN THE PREEMPTIVE CASE, THIS HAPPENS WHEN THERE IS ONE
					LEAF REMAINIG, AND THAT WOULD MEAN ONE INTERNAL NODE REMAINING, AND THAT
					WOULD BE THE ROOT NODE. THAT INTERNAL NODE WOULD HAVE A SINGLE CHILD NODE,
					THE LEAF, AND NO KEYS. IN THE NON PRE EMPTIVE CASE, THIS HAPPENS BECAUSE
					WE ONLY CHECK THE NODES ON THE WAY BACK UP TO MAKE SURE THAT THEY ARE NOT
					TOO EMPTY, AND 'N', SEE NOTES ABOVE, COULD BE 2, WHICH MEANS N - 1, THE
					MINIMAL ALLOWED LENGTH OF A NODE COULD BE 1, WHICH MEANS THAT IF A MERGER 
					HAPPENS ON THE WAY DOWN THE LENGTH COULD BECOME 0, AND THE CODE ABOVE
					WOULD OBSERVE '0' THAT ON THE WAY UP.
				*/
				/*return crx_c_tree_private_removeElement__do(pMode, pThis,
						tNode, pKey); */
				if(CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
				{
					if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
					{
						if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
						{
							crx_c_tree_iterator_private_depthPush(
									pIterator, pNode, tImaginaryIndex);

							tReturn = crx_c_tree_private_removeElement__do(pThis, pMode, tNode, 
									pIndex__guide, pElement, pIterator, NULL, NULL);

							crx_c_tree_iterator_private_depthPop(pIterator);
						}
						else
						{
							tReturn = crx_c_tree_private_removeElement__do(pThis, pMode, tNode, 
									NULL, pElement, NULL, NULL, NULL);
						}
					}
					else
					{
						if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
						{
							tReturn = crx_c_tree_private_removeElement__do(pThis, pMode, tNode, 
									pIndex__guide, pElement, NULL, pIndex__out, NULL);
						}
						else
						{
							tReturn = crx_c_tree_private_removeElement__do(pThis, pMode, tNode, 
									NULL, pElement, NULL, NULL, pElement__out);
						}
					}
				}
			}

			return tReturn;
		}
		else
		{
			bool tIsFound = false;

			/*vKey = __KB_KEY(pGUIDE_TYPE, pNode)[tImaginaryIndex - 1];*/
			if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
			{
				if((tImaginaryIndex > 0 /*>=*/) &&
						(tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0))
				{
					if(pMode != 0)
					{
						if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
						{
							if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
							{
								crx_c_tree_private_transferConstruct(pThis,
										pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
										pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
										pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
										pIndex__guide,
										crx_c_tree_private_getIndexFrom(pThis, pNode,
												tImaginaryIndex - 1));
							}
							else
							{
								(*(pThis->gPrivate_constructIndexFrom))(pIndex__guide,
										crx_c_tree_private_getElement(pThis,
										pNode, tImaginaryIndex - 1));
							}
						}

						crx_c_tree_private_transferConstruct(pThis,
								(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
								(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
										pThis->gPrivate_typeBluePrint__element->
										gFUNC__MOVE_CONSTRUCT),
								(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
										pThis->gPrivate_typeBluePrint__element->
										gFUNC__MOVE_DESTRUCT),
								pElement,
								crx_c_tree_private_getElementEntry(pThis,
										pNode, tImaginaryIndex - 1));

						tIsFound = true;
					}
					else
					{
						if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
						{
							Crx_C_Tree_Iterator tIterator /*= ?*/;
							unsigned char * tPositions /*= ?*/;
							uint32_t tResult = 0;

							/*THIS IS FORMAL VIOLATION. THIS IS DONE BECAUSE WE CAN NOT
							GUARANTEE WHEN THE ALLOCATION OF THE LARGE BUFFER HAPPENS
							ON THE STACK, AND IT MIGHT END UP HAPPENING IN EVERY
							ITERATION*/
							tPositions = ((unsigned char *) CRX__ALLOCA(sizeof(
									Crx_C_Tree_Iterator_Private_Position) * 64));
							crx_c_tree_iterator_private_construct3(
									&tIterator,
									((Crx_C_Tree_Iterator_Private_Position *)
											tPositions),
									pThis);

							if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
							{
								crx_c_tree_iterator_private_depthPush(pIterator, pNode, 
										tImaginaryIndex - 1);
							}
							tResult =
									crx_c_tree_private_removeElement__do__findExactEntry(
									pThis, pIndex__guide, pElement, pIterator, &tIterator);
							if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
								{crx_c_tree_iterator_private_depthPop(pIterator);}

							if(tResult != 0)
							{
								if(tResult == 1)
								{
									if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != 
											NULL)
									{
										(*(pThis->gPrivate_typeBluePrint__element->
												gFUNC__DESTRUCT))(crx_c_tree_private_getElement(
												pThis, pNode, tImaginaryIndex - 1));
									}

									if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
									{
										free(crx_c_tree_private_getElement(pThis, pNode, 
												tImaginaryIndex - 1));
									}
								}
								else
								{
									if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != 
											NULL)
									{
										(*(pThis->gPrivate_typeBluePrint__element->
												gFUNC__DESTRUCT))(crx_c_tree_iterator_get(
												&tIterator));
									}

									if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
										{free(crx_c_tree_iterator_get(&tIterator));}

									if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
									{
										crx_c_tree_private_transferConstruct(pThis,
												pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
												pThis->gPrivate_typeBluePrint__index->
														gFUNC__MOVE_CONSTRUCT,
												pThis->gPrivate_typeBluePrint__index->
														gFUNC__MOVE_DESTRUCT,
												crx_c_tree_iterator_private_getIndex(
														&tIterator),
												crx_c_tree_private_getIndexFrom(pThis, pNode,
														tImaginaryIndex - 1));
									}
														

									crx_c_tree_private_transferConstruct(pThis,
											(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? 
													sizeof(volatile void const *) : 
													pThis->gPrivate_typeBluePrint__element->
													gBYTE_SIZE),
											(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
													pThis->gPrivate_typeBluePrint__element->
													gFUNC__MOVE_CONSTRUCT),
											(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
													pThis->gPrivate_typeBluePrint__element->
													gFUNC__MOVE_DESTRUCT),
											crx_c_tree_iterator_private_getEntry(
													&tIterator),
											crx_c_tree_private_getElementEntry(pThis,
													pNode, tImaginaryIndex - 1));
								}

								tIsFound = true;
							}

							crx_c_tree_iterator_destruct(&tIterator);
						}
						else
						{
							if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
							{
								(*(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(
										crx_c_tree_private_getElement(pThis,
										pNode, tImaginaryIndex - 1));
							}

							if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
							{
								free(crx_c_tree_private_getElement(pThis, pNode,
										tImaginaryIndex - 1));
							}

							tIsFound = true;
						}
					}

					if(tIsFound)
					{
						bool tIsToRotateRight = (CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ?
								((pNode->gPrivate_numberOfEntries >> 1) > (tImaginaryIndex - 1)) :
								false);

						if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX &&
								!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
						{
							crx_c_tree_private_removeSpaceFrom(pThis,
									pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
									pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
									pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
									pNode,
									crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
									pNode->gPrivate_numberOfEntries,
									tImaginaryIndex - 1, 1, tIsToRotateRight);
						}

						crx_c_tree_private_removeSpaceFrom(pThis,
								(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) :
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
								(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
										pThis->gPrivate_typeBluePrint__element->
										gFUNC__MOVE_CONSTRUCT),
								(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
										pThis->gPrivate_typeBluePrint__element->
										gFUNC__MOVE_DESTRUCT),
								pNode,
								crx_c_tree_private_getElementEntry(pThis, pNode, 0),
								pNode->gPrivate_numberOfEntries,
								tImaginaryIndex - 1, 1, tIsToRotateRight);

						crx_c_tree_private_updateStartIndexAfterRemovalOfSpace(pThis, 
								pNode, 1, tIsToRotateRight);
					}
				}
			}
			else
			{
				if((tImaginaryIndex > 0 /*>=*/) &&
						(tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0))
				{
					if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
					{
						Crx_C_Tree_Private_Node * tNode = pNode;
						size_t tIndex = tImaginaryIndex - 1;
						/*REMEMBER: THE FOLLOWING IS FORMALLY INCORRECT. ALLOCA MUST APPEAR
								AT THE TOP LEVEL SCOPE OF THE FUNCTION. BUT THINGS KEPT THIS
								WAY FOR PERFORMANCE FOR THE TIME BEING.*/
						unsigned char * tIndex__guide = 
								(CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY ?
								((unsigned char *)CRX__ALLOCA(
								pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE)) : NULL);
						bool tIsToSwap = false;

						if((*(pThis->gPrivate_getOrderOfElements))(crx_c_tree_private_getElement(
								pThis, pNode, tImaginaryIndex - 1),
								pElement) == 0)
							{tIsFound = true;}

						if(!tIsFound)
						{
							Crx_C_Tree_Private_Node * tNode2 = tNode;
							size_t tIndex2 = tIndex;
							int32_t tOrderOfIndices = 0;

							if(tIndex2 < (tNode2->gPrivate_numberOfEntries - 1))
								{tIndex2 = tIndex2 + 1;}
							else
							{
								tNode2 = &(((Crx_C_Tree_Private_LeafNode *)
										tNode)->gPrivate_leafNode__next->gPrivate_node);

								tIndex2 = 0;
							}

							if(tNode2 != NULL)
							{
								if(CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
								{
									(*(pThis->gPrivate_constructIndexFrom))(tIndex__guide,
											crx_c_tree_private_getElement(pThis,
											tNode2, tIndex2));

									tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(
											pIndex__guide, tIndex__guide);
								}
								else
								{
									tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(
											pIndex__guide, crx_c_tree_private_getIndexFrom(pThis, 
											tNode2, tIndex2));
								}
							}

							while(tOrderOfIndices == 0)
							{
								if((*(pThis->gPrivate_getOrderOfElements))(
										crx_c_tree_private_getElement(pThis, tNode2, tIndex2),
										pElement) == 0)
								{
									tIsFound = true;
									tIsToSwap = true;
									break;
								}
								else
								{
									tNode = tNode2;
									tIndex = tIndex2;

									if(tIndex2 < (tNode2->gPrivate_numberOfEntries - 1))
										{tIndex2 = tIndex2 + 1;}
									else
									{
										tNode2 = &(((Crx_C_Tree_Private_LeafNode *)
												tNode)->gPrivate_leafNode__next->gPrivate_node);
										tIndex2 = 0;
									}

									if(tNode2 != NULL) /*&& (tIndex2 <
											tNode2->gPrivate_numberOfEntries)*/
									{
										if(CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
										{
											(*(pThis->gPrivate_constructIndexFrom))(
													tIndex__guide,
													crx_c_tree_private_getElement(pThis,
													tNode2, tIndex2));

											tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(
													pIndex__guide, tIndex__guide);
										}
										else
										{
											tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(
													pIndex__guide, crx_c_tree_private_getIndexFrom(
													pThis, tNode2, tIndex2));
										}
									}
									else
										{break;}
								}
							}
						}

						if(!tIsFound)
						{
							Crx_C_Tree_Private_Node * tNode2 = pNode;
							size_t tIndex2 = tImaginaryIndex - 1;
							int32_t tOrderOfIndices = -1;

							tNode = pNode;
							tIndex = tImaginaryIndex - 1;

							if(tIndex2 > 0)
								{tIndex2 = tIndex2 - 1;}
							else
							{
								tNode2 = &(((Crx_C_Tree_Private_LeafNode *)
										tNode)->gPrivate_leafNode__prev->gPrivate_node);

								tIndex2 = ((tNode2 != NULL) ?
										(tNode2->gPrivate_numberOfEntries - 1) : 0);
							}

							if(tNode2 != NULL)
							{
								if(CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
								{
									(*(pThis->gPrivate_constructIndexFrom))(tIndex__guide,
											crx_c_tree_private_getElement(pThis,
											tNode2, tIndex2));

									tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(
											pIndex__guide, tIndex__guide);
								}
								else
								{
									tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(
											pIndex__guide, crx_c_tree_private_getIndexFrom(pThis, 
											tNode2, tIndex2));
								}
							}

							while(tOrderOfIndices == 0)
							{
								if((*(pThis->gPrivate_getOrderOfElements))(
										crx_c_tree_private_getElement(pThis, tNode2, tIndex2),
										pElement) == 0)
								{
									tIsFound = true;
									tIsToSwap = true;
									break;
								}
								else
								{
									tNode = tNode2;
									tIndex = tIndex2;

									if(tIndex2 > 0)
										{tIndex2 = tIndex2 - 1;}
									else
									{
										tNode2 = &(((Crx_C_Tree_Private_LeafNode *)
												tNode)->gPrivate_leafNode__prev->gPrivate_node);
										tIndex2 = ((tNode2 != NULL) ?
												(tNode2->gPrivate_numberOfEntries - 1) : 0);
									}

									if(tNode2 != NULL /*&& (tIndex2 >= 0)*/)
									{
										if(CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
										{
											(*(pThis->gPrivate_constructIndexFrom))(
													tIndex__guide,
													crx_c_tree_private_getElement(pThis,
													tNode2, tIndex2));

											tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(
													pIndex__guide, tIndex__guide);
										}
										else
										{
											tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(
													pIndex__guide, crx_c_tree_private_getIndexFrom(
													pThis, tNode2, tIndex2));
										}
									}
									else
										{break;}
								}
							}
						}

						if(tIsFound)
						{
							if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
							{
								(*(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(
										crx_c_tree_private_getElement(pThis, tNode, tIndex));
							}

							if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
								{free(crx_c_tree_private_getElement(pThis, tNode, tIndex));}

							if(tIsToSwap)
							{
								if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
								{
									crx_c_tree_private_transferConstruct(pThis,
											pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
											pThis->gPrivate_typeBluePrint__index->
													gFUNC__MOVE_CONSTRUCT,
											pThis->gPrivate_typeBluePrint__index->
													gFUNC__MOVE_DESTRUCT,
											crx_c_tree_private_getIndexFrom(pThis, tNode, tIndex),
											crx_c_tree_private_getIndexFrom(pThis, pNode,
													tImaginaryIndex - 1));
								}

								crx_c_tree_private_transferConstruct(pThis,
										(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? 
												sizeof(volatile void const *) : 
												pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
										(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
												pThis->gPrivate_typeBluePrint__element->
												gFUNC__MOVE_CONSTRUCT),
										(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
												pThis->gPrivate_typeBluePrint__element->
												gFUNC__MOVE_DESTRUCT),
										crx_c_tree_private_getElementEntry(pThis,
												pNode, tIndex),
										crx_c_tree_private_getElementEntry(pThis,
												pNode, tImaginaryIndex - 1));
							}
						}
					}
					else
					{
						if(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
						{
							(*(pThis->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(
									crx_c_tree_private_getElement(pThis, pNode, 
									tImaginaryIndex - 1));
						}

						if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
						{
							free(crx_c_tree_private_getElement(pThis, pNode,
									tImaginaryIndex - 1));
						}

						tIsFound = true;
					}

					if(tIsFound)
					{
						bool tIsToRotateRight = (CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ?
								((pNode->gPrivate_numberOfEntries >> 1) > (tImaginaryIndex - 1)) : 
								false);

						if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX &&
								!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
						{
							crx_c_tree_private_removeSpaceFrom(pThis,
									pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE,
									pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT, 
									pThis->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
									pNode,
									crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
									pNode->gPrivate_numberOfEntries,
									tImaginaryIndex - 1, 1, tIsToRotateRight);
						}

						crx_c_tree_private_removeSpaceFrom(pThis,
								(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) :
										pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE),
								(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
										pThis->gPrivate_typeBluePrint__element->
										gFUNC__MOVE_CONSTRUCT),
								(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
										pThis->gPrivate_typeBluePrint__element->
										gFUNC__MOVE_DESTRUCT),
								pNode,
								crx_c_tree_private_getElementEntry(pThis, pNode, 0),
								pNode->gPrivate_numberOfEntries,
								tImaginaryIndex - 1, 1, tIsToRotateRight);

						crx_c_tree_private_updateStartIndexAfterRemovalOfSpace(pThis, pNode, 1,
								tIsToRotateRight);

						if(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
						{
							if(pMode != 0)
							{
								/*WHEN USING DELEGATION, HOISTING IS REUIQRED, AND THEREFORE
										SUCH TREES MUST HAVE N >= 3 AS TO KEEP THE FOLLOWING
										ASSERTION TRUE. REMEMBER THAT IF N IS 2, AND THE
										ALGORITHM IS NOT PRE EMPTIVE, pNode COULD NOW BE EMPTY
										AFTER THE REMOVAL ABOVE, AND HENCE IT WOULD HAVE
										NOTHING LEFT FOR HOISTING.
								*/
								assert(pNode->gPrivate_numberOfEntries > 1);
								/*WARNING: REMEMBER, THE LENGTH IS NOT YET UPDATED AT THIS POINT,
										HENCE THE '- 1'.*/
								if(pMode == 1)
									{tImaginaryIndex = pNode->gPrivate_numberOfEntries - 1 /*2*/;}
								else /*pMode == 2*/
									{tImaginaryIndex = 1 /*0*/;}

								if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
								{
									if(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
									{
										memcpy(pIndex__out,
												crx_c_tree_private_getIndexFrom(pThis, pNode,
														tImaginaryIndex - 1),
												pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
									}
									else
									{
										(*(pThis->gPrivate_constructIndexFrom))(pIndex__out,
												crx_c_tree_private_getElement(pThis,
														pNode, tImaginaryIndex - 1));
									}
								}
								else
								{
									if(!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
									{
										if(pThis->gPrivate_typeBluePrint__element->
												gFUNC__COPY_CONSTRUCT != NULL)
										{
											(*(pThis->gPrivate_typeBluePrint__element->
													gFUNC__COPY_CONSTRUCT))(pElement__out,
													crx_c_tree_private_getElement(pThis, pNode, 
													tImaginaryIndex - 1));
										}
										else
										{
											memcpy(pElement__out,
													crx_c_tree_private_getElement(pThis,
															pNode, tImaginaryIndex - 1),
													pThis->gPrivate_typeBluePrint__element->
													gBYTE_SIZE);
										}
									}
									else
									{
										*((unsigned char * *)pElement__out) = crx_c_tree_private_getElement(pThis,
												pNode, tImaginaryIndex - 1);
									}
								}
							}
						}
					}
					else
						/*REMEMBER: WHEN ELEMENTS ARE ONLY IN LEAVES, INTERNAL NODES WOULD ONLY
								HOLD INDICES OF ELEMENTS THAT EXIST IN THE LEAVES, OR COPIES OF
								ELEMENT ENTRIES THAT EXIST IN THE LEAVES DEPENDING ON WHETHER AN
								INDEX IS USED OR NOT. IN OTHER WORDS, IF pMode IS NOT 0, AN ENTRY
								MUST BE FOUND IN THE LEAVES.
								NOTE THAT THIS WAS NECESSARY WHEN THE ALGORITHM CONTINUED TO DO A
								BINARY SEARCH IN THAT CASE WHEN MODE WAS NOT ZERO. LATER I CHANED
								THAT, BUT KEEPING THE CODE BELOW FOR THE TIME BEING.
						*/
						{assert(pMode == 0);}
				}
				else
					/*REMEMBER: WHEN ELEMENTS ARE ONLY IN LEAVES, INTERNAL NODES WOULD ONLY
							HOLD INDICES OF ELEMENTS THAT EXIST IN THE LEAVES, OR COPIES OF
							ELEMENT ENTRIES THAT EXIST IN THE LEAVES DEPENDING ON WHETHER AN
							INDEX IS USED OR NOT. IN OTHER WORDS, IF pMode IS NOT 0, AN ENTRY
							MUST BE FOUND IN THE LEAVES.
							NOTE THAT THIS WAS NECESSARY WHEN THE ALGORITHM CONTINUED TO DO A
							BINARY SEARCH IN THAT CASE WHEN MODE WAS NOT ZERO. LATER I CHANED
							THAT, BUT KEEPING THE CODE BELOW FOR THE TIME BEING.
					*/
					{assert(pMode == 0);}
			}

			if(tIsFound)
				{--(pNode->gPrivate_numberOfEntries);}

			/*return vKey;*/
			return tIsFound;
		}
	}
	else
		{return false;}
}
CRX__LIB__PRIVATE_C_FUNCTION() uint32_t crx_c_tree_private_removeElement__do__findExactEntry(
		Crx_C_Tree * pThis, void * pIndex__guide, void const * pElement,
		Crx_C_Tree_Iterator const * pIterator,
		Crx_C_Tree_Iterator * pIterator__return)
{
	CRX_SCOPE_META
	assert(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX && !CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY);

	CRX_SCOPE
	unsigned char const * vElement = (!CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT ? 
			((unsigned char *)pElement) : *((unsigned char * *)pElement));
	unsigned char * vIndex__guide = (CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY ?
			((unsigned char *)CRX__ALLOCA(pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE)) : 
			NULL);
	bool tIsFound = false;
	bool tIsToSwap = false;

	if((*(pThis->gPrivate_getOrderOfElements))(crx_c_tree_iterator_get(pIterator), vElement) == 0)
		{tIsFound = true;}

	if(!tIsFound)
	{
		crx_c_tree_iterator_copyAssignFrom(pIterator__return,
				pIterator);

		while(true)
		{
			if(crx_c_tree_iterator_next(pIterator__return))
			{
				int32_t tOrderOfIndices /*= ?*/;

				if(CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
				{
					if((CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE ?
							pIterator__return->gPrivate_position__current->gNode :
							pIterator__return->gPrivate_node)->gPrivate_type)
					{
						memcpy(vIndex__guide,
								crx_c_tree_iterator_private_getIndex(pIterator__return), 
								pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
					}
					else
					{
						(*(pThis->gPrivate_constructIndexFrom))(
								vIndex__guide,
								crx_c_tree_iterator_get(
								pIterator__return));
					}

					tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(pIndex__guide,
							vIndex__guide);
				}
				else
				{
					tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(pIndex__guide,
							crx_c_tree_iterator_private_getIndex(
							pIterator__return));
				}

				if(tOrderOfIndices == 0)
				{
					if((*(pThis->gPrivate_getOrderOfElements))(
							crx_c_tree_iterator_get(
							pIterator__return), vElement) == 0)
					{
						tIsFound = true;
						tIsToSwap = true;
						break;
					}
				}
				else
					{break;}
			}
			else
				{break;}
		}
	}

	if(!tIsFound)
	{
		crx_c_tree_iterator_copyAssignFrom(pIterator__return, pIterator);

		while(true)
		{
			if(crx_c_tree_iterator_prev(pIterator__return))
			{
				int32_t tOrderOfIndices /*= ?*/;

				if(CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
				{
					if((CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE ? 
							pIterator__return->gPrivate_position__current->gNode :
							pIterator__return->gPrivate_node)->gPrivate_type)
					{
						memcpy(vIndex__guide,
								crx_c_tree_iterator_private_getIndex(pIterator__return), 
								pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE);
					}
					else
					{
						(*(pThis->gPrivate_constructIndexFrom))(
								vIndex__guide, crx_c_tree_iterator_get(pIterator__return));
					}

					tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(pIndex__guide,
							vIndex__guide);
				}
				else
				{
					tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(pIndex__guide,
							crx_c_tree_iterator_private_getIndex(pIterator__return));
				}

				if(tOrderOfIndices == 0)
				{
					if((*(pThis->gPrivate_getOrderOfElements))(
							crx_c_tree_iterator_get(pIterator__return), vElement) == 0)
					{
						tIsFound = true;
						tIsToSwap = true;
						break;
					}
				}
				else
					{break;}
			}
			else
				{break;}
		}
	}

	if(tIsFound)
	{
		if(tIsToSwap)
			{return 2;}
		else
			{return 1;}
	}
	else
		{return 0;}

	CRX_SCOPE_END
}

CRX__LIB__PRIVATE_C_FUNCTION() size_t crx_c_tree_private_findChildNodeIndexInParent(
		Crx_C_Tree * pThis, Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode)
{
	CRX_SCOPE_META
	assert(CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY && !CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE);

	if(pNode->gPrivate_node__parent == NULL)
		{return ((size_t)(-1));}

	CRX_SCOPE
	size_t vIndex = ((size_t)(-1));
	bool vIsFound = false;

	if(pNode->gPrivate_type)
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			int32_t tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 0;
			Crx_C_Tree_Private_Node * tNode = NULL;

			vIndex = crx_c_tree_private_getSuitableImagineryIndexFor(
					pThis, pNode->gPrivate_node__parent,
					NULL, crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
					&tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode) /*+ 1*/;

			/*if((vIndex > 0) &&
					(tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0))
				{vIndex++;}*/

			tNode = *(crx_c_tree_private_getChildNode(
					pThis, pNode->gPrivate_node__parent, vIndex));

			if(CRX__ARE_POINTERS_TO_SAME_OBJECT(tNode, pNode, false))
				{vIsFound = true;}

			if(!vIsFound)
			{
				/*NEED TO REWIND TO FIND FIRST*/
				Crx_C_Tree_Private_Node * tNode2 =
						&(((Crx_C_Tree_Private_LeafNode *)tNode)->
						gPrivate_leafNode__prev->gPrivate_node);
				size_t tIndex = vIndex;

				while(tNode2 != NULL)
				{
					if(!CRX__ARE_POINTERS_TO_SAME_OBJECT(
							pNode->gPrivate_node__parent,
							tNode2->gPrivate_node__parent, false) ||
							(tIndex == 0))
						{break;}

					tIndex = tIndex - 1;

					if(((*(pThis->gPrivate_getOrderOfIndices))(
							crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
							crx_c_tree_private_getIndexFrom(pThis, tNode2, 0)) == 0) &&
							CRX__ARE_POINTERS_TO_SAME_OBJECT(pNode, tNode2, false))
					{
						vIndex = tIndex;
						vIsFound = true;

						break;
					}
					else
					{
						tNode2 = &(((Crx_C_Tree_Private_LeafNode *)tNode2)->
								gPrivate_leafNode__prev->gPrivate_node);
					}
				}
			}

			if(!vIsFound)
			{
				/*NEED TO FARWARD TO FIND LAST*/
				Crx_C_Tree_Private_Node * tNode2 =
						&(((Crx_C_Tree_Private_LeafNode *)tNode)->
						gPrivate_leafNode__next->gPrivate_node);
				size_t tIndex = vIndex;
				int32_t tOrderOfIndices = -1;

				while(tNode2 != NULL)
				{
					if(!CRX__ARE_POINTERS_TO_SAME_OBJECT(
							pNode->gPrivate_node__parent,
							tNode2->gPrivate_node__parent, false) ||
							(tIndex == (pNode->gPrivate_node__parent->
									gPrivate_numberOfEntries + 1)))
						{break;}

					tIndex = tIndex + 1;

					if(((*(pThis->gPrivate_getOrderOfIndices))(
							crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
							crx_c_tree_private_getIndexFrom(pThis, tNode2, 0)) == 0) &&
							CRX__ARE_POINTERS_TO_SAME_OBJECT(pNode, tNode2, false))
					{
						vIndex = tIndex;
						vIsFound = true;

						break;
					}
					else
					{
						tNode2 = &(((Crx_C_Tree_Private_LeafNode *)tNode2)->
								gPrivate_leafNode__next->gPrivate_node);
					}
				}
			}
		}
		else
		{
			int32_t tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 0;
			Crx_C_Tree_Private_Node * tNode = NULL;

			vIndex = crx_c_tree_private_getSuitableImagineryIndexFor(
					pThis, pNode->gPrivate_node__parent,
					crx_c_tree_private_getElement(pThis, pNode, 0), NULL,
					&tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode) /*+ 1*/;

			/*if((vIndex > 0) &&
					(tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0))
				{vIndex++;}*/

			tNode = *(crx_c_tree_private_getChildNode(
					pThis, pNode->gPrivate_node__parent, vIndex));

			if(CRX__ARE_POINTERS_TO_SAME_OBJECT(tNode, pNode, false))
				{vIsFound = true;}

			if(!vIsFound)
			{
				/*NEED TO REWIND TO FIND FIRST*/
				Crx_C_Tree_Private_Node * tNode2 =
						&(((Crx_C_Tree_Private_LeafNode *)tNode)->
						gPrivate_leafNode__prev->gPrivate_node);
				size_t tIndex = vIndex;

				while(tNode2 != NULL)
				{
					if(!CRX__ARE_POINTERS_TO_SAME_OBJECT(
							pNode->gPrivate_node__parent,
							tNode2->gPrivate_node__parent, false) ||
							(tIndex == 0))
						{break;}

					tIndex = tIndex - 1;

					if(((*(pThis->gPrivate_getOrderOfElements))(
							crx_c_tree_private_getElement(pThis, pNode, 0),
							crx_c_tree_private_getElement(pThis, tNode2, 0)) == 0) &&
							CRX__ARE_POINTERS_TO_SAME_OBJECT(pNode, tNode2, false))
					{
						vIndex = tIndex;
						vIsFound = true;

						break;
					}
					else
					{
						tNode2 = &(((Crx_C_Tree_Private_LeafNode *)tNode2)->
								gPrivate_leafNode__prev->gPrivate_node);
					}
				}
			}

			if(!vIsFound)
			{
				/*NEED TO FARWARD TO FIND LAST*/
				Crx_C_Tree_Private_Node * tNode2 =
						&(((Crx_C_Tree_Private_LeafNode *)tNode)->
						gPrivate_leafNode__next->gPrivate_node);
				size_t tIndex = vIndex;

				while(tNode2 != NULL)
				{
					if(!CRX__ARE_POINTERS_TO_SAME_OBJECT(
							pNode->gPrivate_node__parent,
							tNode2->gPrivate_node__parent, false) ||
							(tIndex == (pNode->gPrivate_node__parent->
									gPrivate_numberOfEntries + 1)))
						{break;}

					tIndex = tIndex + 1;

					if(((*(pThis->gPrivate_getOrderOfElements))(crx_c_tree_private_getElement(pThis, pNode, 0),
							crx_c_tree_private_getElement(pThis, tNode2, 0)) == 0) &&
							CRX__ARE_POINTERS_TO_SAME_OBJECT(pNode, tNode2, false))
					{
						vIndex = tIndex;
						vIsFound = true;

						break;
					}
					else
					{
						tNode2 = &(((Crx_C_Tree_Private_LeafNode *)tNode2)->
								gPrivate_leafNode__next->gPrivate_node);
					}
				}
			}
		}
	}
	else
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			int32_t tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 0;
			unsigned char * tIndex__guide = 
					(CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY ?
					((unsigned char *)CRX__ALLOCA(
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE)) : NULL);
			unsigned char * tIndex__guide2 = 
					(CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY ?
					((unsigned char *)CRX__ALLOCA(
					pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE)) : NULL);
			Crx_C_Tree_Private_Node * tNode = NULL;

			if(CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
			{
				(*(pThis->gPrivate_constructIndexFrom))(tIndex__guide,
						crx_c_tree_private_getElement(pThis, pNode, 0));

				vIndex = crx_c_tree_private_getSuitableImagineryIndexFor(
						pThis, pNode->gPrivate_node__parent, NULL, tIndex__guide,
						&tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode) /*+ 1*/;
			}
			else
			{
				vIndex = crx_c_tree_private_getSuitableImagineryIndexFor(
						pThis, pNode->gPrivate_node__parent,
						NULL, crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
						&tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode) /*+ 1*/;
			}

			/*if((vIndex > 0) &&
					(tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0))
				{vIndex++;}*/

			tNode = *(crx_c_tree_private_getChildNode(
					pThis, pNode->gPrivate_node__parent, vIndex));

			if(CRX__ARE_POINTERS_TO_SAME_OBJECT(tNode, pNode, false))
				{vIsFound = true;}

			if(!vIsFound)
			{
				/*NEED TO REWIND TO FIND FIRST*/
				Crx_C_Tree_Private_Node * tNode2 =
						&(((Crx_C_Tree_Private_LeafNode *)tNode)->
						gPrivate_leafNode__prev->gPrivate_node);
				size_t tIndex = vIndex;
				int32_t tOrderOfIndices = -1;

				while(tNode2 != NULL)
				{
					if(!CRX__ARE_POINTERS_TO_SAME_OBJECT(
							pNode->gPrivate_node__parent,
							tNode2->gPrivate_node__parent, false) ||
							(tIndex == 0))
						{break;}

					tIndex = tIndex - 1;

					if(CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
					{
						(*(pThis->gPrivate_constructIndexFrom))(tIndex__guide2,
								crx_c_tree_private_getElement(pThis, tNode2, 0));

						tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(
								tIndex__guide,
								tIndex__guide2);
					}
					else
					{
						tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(
								crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
								crx_c_tree_private_getIndexFrom(pThis, tNode2, 0));
					}

					if((tOrderOfIndices == 0) &&
							CRX__ARE_POINTERS_TO_SAME_OBJECT(pNode, tNode2, false))
					{
						vIndex = tIndex;
						vIsFound = true;

						break;
					}
					else
					{
						tNode2 = &(((Crx_C_Tree_Private_LeafNode *)tNode2)->
								gPrivate_leafNode__prev->gPrivate_node);
					}
				}
			}

			if(!vIsFound)
			{
				/*NEED TO FARWARD TO FIND LAST*/
				Crx_C_Tree_Private_Node * tNode2 =
						&(((Crx_C_Tree_Private_LeafNode *)tNode)->
						gPrivate_leafNode__next->gPrivate_node);
				size_t tIndex = vIndex;
				int32_t tOrderOfIndices = -1;

				while(tNode2 != NULL)
				{
					if(!CRX__ARE_POINTERS_TO_SAME_OBJECT(
							pNode->gPrivate_node__parent,
							tNode2->gPrivate_node__parent, false) ||
							(tIndex == (pNode->gPrivate_node__parent->
									gPrivate_numberOfEntries + 1)))
						{break;}

					tIndex = tIndex + 1;

					if(CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
					{
						(*(pThis->gPrivate_constructIndexFrom))(tIndex__guide2,
								crx_c_tree_private_getElement(pThis, tNode2, 0));

						tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(
								tIndex__guide, tIndex__guide2);
					}
					else
					{
						tOrderOfIndices = (*(pThis->gPrivate_getOrderOfIndices))(
								crx_c_tree_private_getIndexFrom(pThis, pNode, 0),
								crx_c_tree_private_getIndexFrom(pThis, tNode2, 0));
					}

					if((tOrderOfIndices == 0) &&
							CRX__ARE_POINTERS_TO_SAME_OBJECT(pNode, tNode2, false))
					{
						vIndex = tIndex;
						vIsFound = true;

						break;
					}
					else
					{
						tNode2 = &(((Crx_C_Tree_Private_LeafNode *)tNode2)->
								gPrivate_leafNode__next->gPrivate_node);
					}
				}
			}
		}
		else
		{
			int32_t tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 0;
			Crx_C_Tree_Private_Node * tNode = NULL;

			vIndex = crx_c_tree_private_getSuitableImagineryIndexFor(
					pThis, pNode->gPrivate_node__parent,
					crx_c_tree_private_getElement(pThis, pNode, 0), NULL,
					&tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode) /*+ 1*/;

			/*if((vIndex > 0) &&
					(tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0))
				{vIndex++;}*/

			tNode = *(crx_c_tree_private_getChildNode(
					pThis, pNode->gPrivate_node__parent, vIndex));

			if(CRX__ARE_POINTERS_TO_SAME_OBJECT(tNode, pNode, false))
				{vIsFound = true;}

			if(!vIsFound)
			{
				/*NEED TO REWIND TO FIND FIRST*/
				Crx_C_Tree_Private_Node * tNode2 =
						&(((Crx_C_Tree_Private_LeafNode *)tNode)->
						gPrivate_leafNode__prev->gPrivate_node);
				size_t tIndex = vIndex;

				while(tNode2 != NULL)
				{
					if(!CRX__ARE_POINTERS_TO_SAME_OBJECT(
							pNode->gPrivate_node__parent,
							tNode2->gPrivate_node__parent, false) ||
							(tIndex == 0))
						{break;}

					tIndex = tIndex - 1;

					if(((*(pThis->gPrivate_getOrderOfElements))(crx_c_tree_private_getElement(pThis, 
							pNode, 0), crx_c_tree_private_getElement(pThis, tNode2, 0)) == 0) &&
							CRX__ARE_POINTERS_TO_SAME_OBJECT(pNode, tNode2, false))
					{
						vIndex = tIndex;
						vIsFound = true;

						break;
					}
					else
					{
						tNode2 = &(((Crx_C_Tree_Private_LeafNode *)tNode2)->
								gPrivate_leafNode__prev->gPrivate_node);
					}
				}
			}

			if(!vIsFound)
			{
				/*NEED TO FARWARD TO FIND LAST*/
				Crx_C_Tree_Private_Node * tNode2 =
						&(((Crx_C_Tree_Private_LeafNode *)tNode)->
						gPrivate_leafNode__next->gPrivate_node);
				size_t tIndex = vIndex;

				while(tNode2 != NULL)
				{
					if(!CRX__ARE_POINTERS_TO_SAME_OBJECT(
							pNode->gPrivate_node__parent,
							tNode2->gPrivate_node__parent, false) ||
							(tIndex == (pNode->gPrivate_node__parent->
									gPrivate_numberOfEntries + 1)))
						{break;}

					tIndex = tIndex + 1;

					if(((*(pThis->gPrivate_getOrderOfElements))(crx_c_tree_private_getElement(pThis, 
							pNode, 0), crx_c_tree_private_getElement(pThis, tNode2, 0)) == 0) &&
							CRX__ARE_POINTERS_TO_SAME_OBJECT(pNode, tNode2, false))
					{
						vIndex = tIndex;
						vIsFound = true;

						break;
					}
					else
					{
						tNode2 = &(((Crx_C_Tree_Private_LeafNode *)tNode2)->
								gPrivate_leafNode__next->gPrivate_node);
					}
				}
			}
		}
	}

	if(vIsFound)
		{return vIndex;}
	else
		{return ((size_t)(-1));}
	CRX_SCOPE_END
}

CRX__LIB__PRIVATE_C_FUNCTION() size_t crx_c_tree_private_getTraceOfLeafNode(
		Crx_C_Tree * pThis, Crx_C_Tree_Private_Node * CRX_NOT_NULL pNode,
		Crx_C_Tree_Private_Node * * CRX_NOT_NULL pNodes,
		size_t * CRX_NOT_NULL pIndices)
{
	assert(CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY && CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE);
	assert(pNode->gPrivate_type == 0);

	pNodes[0] = NULL;
	pIndices[0] = 0;

	if(pThis->gPrivate_node__root->gPrivate_type == 0)
	{
		if(CRX__ARE_POINTERS_TO_SAME_OBJECT(pNode, pThis->gPrivate_node__root, false))
		{
			pNodes[1] = pThis->gPrivate_node__root;
			pIndices[1] = 0;

			return 2;
		}
		else
			{return 0;}
	}
	else
	{
		Crx_C_Tree_Private_Node * tNode = pThis->gPrivate_node__root;
		size_t tIndex = 0;
		unsigned char * tIndex__guide = ((CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX && 
				CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY) ?
				((unsigned char *)CRX__ALLOCA(pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE)) : 
				NULL);
		unsigned char * tIndex__guide2 = ((CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX && 
				CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY) ?
				((unsigned char *)CRX__ALLOCA(pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE)) :
				NULL);
		unsigned char const * tElement = (!CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX ? 
				crx_c_tree_private_getElement(pThis, pNode, 0) : NULL);
		bool tIsFound = false;

		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			if(CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
			{
				(*(pThis->gPrivate_constructIndexFrom))(tIndex__guide,
						crx_c_tree_private_getElement(pThis, pNode, 0));
			}
			else
			{
				tIndex__guide = ((unsigned char *)crx_c_tree_private_getIndexFrom(pThis, pNode, 0));
			}
		}

		while(tNode != NULL)
		{
			int32_t tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 0;
			size_t tImaginaryIndex = (CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX ?
					crx_c_tree_private_getSuitableImagineryIndexFor(
							pThis, tNode, NULL, tIndex__guide,
							&tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode) :
					crx_c_tree_private_getSuitableImagineryIndexFor(
							pThis, tNode, tElement, NULL,
							&tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode));

			if(tImaginaryIndex > 0 /*>=*/ &&
					tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0)
			{
				if(tNode->gPrivate_type)
				{
					tIndex++;
					pNodes[tIndex] = tNode;
					pIndices[tIndex] = tImaginaryIndex /*+ 1*/;

					tNode = *(crx_c_tree_private_getChildNode(pThis, tNode,
							tImaginaryIndex /*+ 1*/));
				}
				else
				{
					/*tIndexInLeaf = tImaginaryIndex - 1;*/

					break;
				}
			}
			else
			{
				if(tNode->gPrivate_type)
				{
					tIndex++;
					pNodes[tIndex] = tNode;
					pIndices[tIndex] = tImaginaryIndex /*+ 1*/;

					tNode = *(crx_c_tree_private_getChildNode(pThis, tNode,
							tImaginaryIndex /*+ 1*/));
				}
				else
				{
					/*tIndexInLeaf = ((size_t)(-1));*/

					break;
				}
			}
		}

		if(CRX__ARE_POINTERS_TO_SAME_OBJECT(pNode,
				*(crx_c_tree_private_getChildNode(pThis, pNodes[tIndex],
						pIndices[tIndex])), false))
			{tIsFound = true;}

		if(!tIsFound)
		{
			size_t tIndex2 = tIndex;
			bool tIsToSkipUp = false;
			Crx_C_Tree_Private_Node * tNodes[64];
			size_t tIndices[64];

			memcpy(&(tNodes[0]), &(pNodes[0]),
					(tIndex + 1) * sizeof(volatile void const *));
			memcpy(&(tIndices[0]), &(pIndices[0]), (tIndex + 1) * sizeof(size_t));

			while(!tIsFound)
			{
				assert(tNodes[tIndex2]->gPrivate_type);

				while(tNodes[tIndex2])
				{
					if(tIsToSkipUp || (tNodes[tIndex2]->gPrivate_type == 0))
					{
						tIsToSkipUp = false;

						break;
					}

					tNodes[tIndex2 + 1] = *(crx_c_tree_private_getChildNode(pThis,
							tNodes[tIndex2], tIndices[tIndex2]));
					tIndices[tIndex2 + 1] = tNodes[tIndex2 + 1]->
							gPrivate_numberOfEntries;

					tIndex2++;
				}
				tIndex2--;

				/*THIS IS THE REASON 64 PER THE REFERENCE IMPLEMENTATION BECAME 65 HERE*/
				if(tIndex2 == 0)
					{break;}
				else if(tNodes[tIndex2])
				{
					if((*(crx_c_tree_private_getChildNode(pThis, tNodes[tIndex2],
							tIndices[tIndex2])))->gPrivate_type == 0)
					{
						tIsFound = CRX__ARE_POINTERS_TO_SAME_OBJECT(pNode,
								*(crx_c_tree_private_getChildNode(pThis, tNodes[tIndex2],
								tIndices[tIndex2])), false);
					}

					if(tIndices[tIndex2] > 0)
						{(tIndices[tIndex2])--;}
					else
						{tIsToSkipUp = true;}
				}
			}

			if(tIsFound)
			{
				tIndex = tIndex2;

				memcpy(&(pNodes[0]), &(tNodes[0]),
						(tIndex + 1) * sizeof(volatile void const *));
				memcpy(&(pIndices[0]), &(tIndices[0]), (tIndex + 1) * sizeof(size_t));
			}
		}

		if(!tIsFound)
		{
			size_t tIndex2 = tIndex;
			bool tIsToSkipUp = false;
			Crx_C_Tree_Private_Node * tNodes[64];
			size_t tIndices[64];

			memcpy(&(tNodes[0]), &(pNodes[0]),
					(tIndex + 1) * sizeof(volatile void const *));
			memcpy(&(tIndices[0]), &(pIndices[0]), (tIndex + 1) * sizeof(size_t));

			while(true)
			{
				assert(tNodes[tIndex2]->gPrivate_type != 0);

				tIndices[tIndex2]++;

				while(tNodes[tIndex2] &&
						(tIndices[tIndex2] <= tNodes[tIndex2]->gPrivate_numberOfEntries))
				{
					if(tNodes[tIndex2]->gPrivate_type == 0)
						{break;}

					tIndices[tIndex2 + 1] = 0;
					tNodes[tIndex2 + 1] = *(crx_c_tree_private_getChildNode(pThis,
							tNodes[tIndex2], tIndices[tIndex2]));
					tIndex2++;
				}
				tIndex2--;

				/*THIS IS THE REASON 64 PER THE REFERENCE IMPLEMENTATION BECAME 65 HERE*/
				if(tIndex2 == 0)
					{break;}
				else if(tNodes[tIndex2] &&
						(tIndices[tIndex2] <= tNodes[tIndex2]->gPrivate_numberOfEntries))
				{
					if((*(crx_c_tree_private_getChildNode(pThis, tNodes[tIndex2],
							tIndices[tIndex2])))->gPrivate_type == 0)
					{
						tIsFound = CRX__ARE_POINTERS_TO_SAME_OBJECT(pNode,
								*(crx_c_tree_private_getChildNode(pThis, tNodes[tIndex2],
								pIndices[tIndex2])), false);
					}
				}
			}

			if(tIsFound)
			{
				tIndex = tIndex2;

				memcpy(&(pNodes[0]), &(tNodes[0]),
						(tIndex + 1) * sizeof(volatile void const *));
				memcpy(&(pIndices[0]), &(tIndices[0]), (tIndex + 1) * sizeof(size_t));
			}
		}

		return tIndex + 1;
	}
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_decrementNumberOfElements(
		Crx_C_Tree * pThis)
	{(pThis->gPrivate_numberOfElements)--;}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_decrementNumberOfNodes(
		Crx_C_Tree * pThis)
	{(pThis->gPrivate_numberOfNodes)--;}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_unsafePopRootNode(
		Crx_C_Tree * pThis)
{
	Crx_C_Tree_Private_Node * vNode = pThis->gPrivate_node__root;

	pThis->gPrivate_node__root = *crx_c_tree_private_getChildNode(pThis, vNode, 0);
	if(!CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE)
		{pThis->gPrivate_node__root->gPrivate_node__parent = NULL;}

	free(vNode);
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_transfer(Crx_C_Tree * pThis, 
		size_t pByteSizeOfType, Crx_C_TypeBluePrint_MoveConstruct pFunc_moveConstruct,
		Crx_C_TypeBluePrint_MoveDestruct pFunc_moveDestruct,
		unsigned char * pTarget, Crx_C_Tree_Private_Node * pTarget_node, size_t pTarget_index, 
		unsigned char * pSrc, Crx_C_Tree_Private_Node * pSrc_node, size_t pSrc_index, 
		size_t pCount)
{
	if(!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS)
	{
		if((pFunc_moveConstruct != NULL) || (pFunc_moveDestruct != NULL))
		{
			if(pFunc_moveConstruct != NULL)
			{
				CRX_FOR(size_t tI = 0, tI < pCount, tI++)
				{
					(*(pFunc_moveConstruct))(pTarget + ((pTarget_index + tI) * pByteSizeOfType),
							pSrc + ((pSrc_index + tI) * pByteSizeOfType));

					if(pFunc_moveDestruct != NULL)
						{(*(pFunc_moveDestruct))(pSrc + ((pSrc_index + tI) * pByteSizeOfType));}
				}
				CRX_ENDFOR
			}
			else
			{
				CRX_FOR(size_t tI = 0, tI < pCount, tI++)
				{
					memcpy(pTarget + ((pTarget_index + tI) * pByteSizeOfType),
							pSrc + ((pSrc_index + tI) * pByteSizeOfType), pByteSizeOfType);

					if(pFunc_moveDestruct != NULL)
						{(*(pFunc_moveDestruct))(pSrc + ((pSrc_index + tI) * pByteSizeOfType));}
				}
				CRX_ENDFOR
			}
		}
		else
		{
			memcpy(pTarget + (pTarget_index * pByteSizeOfType), 
					pSrc + (pSrc_index * pByteSizeOfType),
					pByteSizeOfType * pCount);
		}
	}
	else
	{
		unsigned char * tTarget = pTarget - (pTarget_node->gPrivate_startIndex * pByteSizeOfType);
		unsigned char * tSrc = pSrc - (pSrc_node->gPrivate_startIndex * pByteSizeOfType);

		if((pFunc_moveConstruct != NULL) || (pFunc_moveDestruct != NULL))
		{
			if(pFunc_moveConstruct != NULL)
			{
				CRX_FOR(size_t tI = 0, tI < pCount, tI++)
				{
					(*(pFunc_moveConstruct))(tTarget + (((pTarget_node->gPrivate_startIndex + tI +
									pTarget_index) & 
									((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
									pByteSizeOfType),
							tSrc + (((pSrc_node->gPrivate_startIndex + tI + pSrc_index) &
									((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
									pByteSizeOfType));

					if(pFunc_moveDestruct != NULL)
					{
						(*(pFunc_moveDestruct))(tSrc + (((pSrc_node->gPrivate_startIndex + 
								tI + pSrc_index) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 
								1)) * pByteSizeOfType));
					}
				}
				CRX_ENDFOR
			}
			else
			{
				CRX_FOR(size_t tI = 0, tI < pCount, tI++)
				{
					memcpy(tTarget + (((pTarget_node->gPrivate_startIndex + tI + pTarget_index) & 
									((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
									pByteSizeOfType),
							tSrc + (((pSrc_node->gPrivate_startIndex + tI + pSrc_index) &
									((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
									pByteSizeOfType), 
							pByteSizeOfType);

					if(pFunc_moveDestruct != NULL)
					{
						(*(pFunc_moveDestruct))(tSrc + (((pSrc_node->gPrivate_startIndex + 
								tI + pSrc_index) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 
								1)) * pByteSizeOfType));
					}
				}
				CRX_ENDFOR
			}
		}
		else
		{
			size_t tTargetStartIndex = ((pTarget_node->gPrivate_startIndex +
					pTarget_index) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1));
			size_t tTargetSegmentLength = ((tTargetStartIndex >=
							pTarget_node->gPrivate_startIndex) ?
					((((pTarget_node->gPrivate_startIndex + pTarget_index + pCount - 1) &
							((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) >= tTargetStartIndex) ? pCount :
							((2 * pThis->gPrviate_countOfMidElementInNode) - tTargetStartIndex)) :
					pCount);
			size_t tSourceStartIndex = ((pSrc_node->gPrivate_startIndex + pSrc_index) &
					((2 * pThis->gPrviate_countOfMidElementInNode) - 1));
			size_t tSourceSegmentLength = ((tSourceStartIndex >= pSrc_node->gPrivate_startIndex) ?
					((((pSrc_node->gPrivate_startIndex + pSrc_index + pCount - 1) &
							((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) >= tSourceStartIndex) ? pCount :
							((2 * pThis->gPrviate_countOfMidElementInNode) - tSourceStartIndex)) :
					pCount);

			if(tTargetSegmentLength <= tSourceSegmentLength)
			{
				memcpy(tTarget + (tTargetStartIndex * pByteSizeOfType), 
						tSrc + (tSourceStartIndex * pByteSizeOfType),
						tTargetSegmentLength * pByteSizeOfType);

				if(tTargetSegmentLength < pCount)
				{
					assert(((pTarget_node->gPrivate_startIndex + pTarget_index +
							tTargetSegmentLength) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) == 0);

					memcpy(tTarget, 
							tSrc + ((tSourceStartIndex + tTargetSegmentLength) * pByteSizeOfType),
							(tSourceSegmentLength - tTargetSegmentLength) * pByteSizeOfType);

					if(tSourceSegmentLength < pCount)
					{
						assert(((pSrc_node->gPrivate_startIndex + tSourceStartIndex +
								tSourceSegmentLength) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) == 0);

						memcpy(tTarget + ((tSourceSegmentLength - tTargetSegmentLength) * 
										pByteSizeOfType), tSrc, 
								(pCount - tSourceSegmentLength) * pByteSizeOfType);
					}
				}
			}
			else
			{
				memcpy(tTarget + (tTargetStartIndex * pByteSizeOfType), 
						tSrc + (tSourceStartIndex * pByteSizeOfType),
						tSourceSegmentLength * pByteSizeOfType);

				assert(((pSrc_node->gPrivate_startIndex + pSrc_index + tSourceSegmentLength) &
						((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) == 0);

				memcpy(tTarget + ((tTargetStartIndex + tSourceSegmentLength) * pByteSizeOfType), 
						tSrc, (tTargetSegmentLength - tSourceSegmentLength) * pByteSizeOfType);

				if(tTargetSegmentLength < pCount)
				{ 
					assert(((pTarget_node->gPrivate_startIndex + pTarget_index + tTargetSegmentLength) &
							((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) == 0);

					memcpy(tTarget, 
							tSrc + ((tTargetSegmentLength - tSourceSegmentLength) * 
									pByteSizeOfType),
							(pCount - tTargetSegmentLength) * pByteSizeOfType);
				}
			}
		}
	}
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_copy(Crx_C_Tree * pThis,
		size_t pByteSizeOfType, Crx_C_TypeBluePrint_CopyConstruct pFunc_copyConstruct,
		unsigned char * pTarget, Crx_C_Tree_Private_Node * pTarget_node, size_t pTarget_index, 
		unsigned char * pSrc, Crx_C_Tree_Private_Node const * pSrc_node, size_t pSrc_index, 
		size_t pCount)
{
	if(!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS)
	{
		if(pFunc_copyConstruct != NULL)
		{
			CRX_FOR(size_t tI = 0, tI < pCount, tI++)
			{
				(*pFunc_copyConstruct)(pTarget + ((pTarget_index + tI) * pByteSizeOfType),
						pSrc + ((pSrc_index + tI) * pByteSizeOfType));
			}
			CRX_ENDFOR
		}
		else
		{
			memcpy(pTarget + (pTarget_index * pByteSizeOfType), 
					pSrc + (pSrc_index * pByteSizeOfType), pByteSizeOfType * pCount);
		}
	}
	else
	{
		unsigned char * tTarget = pTarget - (pTarget_node->gPrivate_startIndex * pByteSizeOfType);
		unsigned char * tSrc = pSrc - (pSrc_node->gPrivate_startIndex * pByteSizeOfType);

		if(pFunc_copyConstruct != NULL)
		{
			CRX_FOR(size_t tI = 0, tI < pCount, tI++)
			{
				(*pFunc_copyConstruct)(tTarget + (((pTarget_node->gPrivate_startIndex + tI +
								pTarget_index) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 
								1)) * pByteSizeOfType),
						tSrc + (((pSrc_node->gPrivate_startIndex + tI + pSrc_index) &
								((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
								pByteSizeOfType));
			}
			CRX_ENDFOR
		}
		else
		{
			size_t tTargetStartIndex = ((pTarget_node->gPrivate_startIndex +
					pTarget_index) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1));
			size_t tTargetSegmentLength = ((tTargetStartIndex >=
							pTarget_node->gPrivate_startIndex) ?
					((((pTarget_node->gPrivate_startIndex + pTarget_index + pCount - 1) &
							((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) >= 
							tTargetStartIndex) ? pCount :
							((2 * pThis->gPrviate_countOfMidElementInNode) - tTargetStartIndex)) :
					pCount);
			size_t tSourceStartIndex = ((pSrc_node->gPrivate_startIndex + pSrc_index) &
					((2 * pThis->gPrviate_countOfMidElementInNode) - 1));
			size_t tSourceSegmentLength = ((tSourceStartIndex >= pSrc_node->gPrivate_startIndex) ?
					((((pSrc_node->gPrivate_startIndex + pSrc_index + pCount - 1) &
							((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) >= 
							tSourceStartIndex) ? pCount :
							((2 * pThis->gPrviate_countOfMidElementInNode) - tSourceStartIndex)) :
					pCount);

			if(tTargetSegmentLength <= tSourceSegmentLength)
			{
				memcpy(tTarget + (tTargetStartIndex * pByteSizeOfType), 
						tSrc + (tSourceStartIndex * pByteSizeOfType),
						tTargetSegmentLength * pByteSizeOfType);

				if(tTargetSegmentLength < pCount)
				{
					assert(((pTarget_node->gPrivate_startIndex + pTarget_index +
							tTargetSegmentLength) & 
							((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) == 0);

					memcpy(tTarget, 
							tSrc + ((tSourceStartIndex + tTargetSegmentLength) * pByteSizeOfType),
							(tSourceSegmentLength - tTargetSegmentLength) * pByteSizeOfType);

					if(tSourceSegmentLength < pCount)
					{
						assert(((pSrc_node->gPrivate_startIndex + tSourceStartIndex +
								tSourceSegmentLength) & 
								((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) == 0);

						memcpy(tTarget + ((tSourceSegmentLength - tTargetSegmentLength) * 
								pByteSizeOfType), tSrc, 
								(pCount - tSourceSegmentLength) * pByteSizeOfType);
					}
				}
			}
			else
			{
				memcpy(tTarget + (tTargetStartIndex * pByteSizeOfType), 
						tSrc + (tSourceStartIndex * pByteSizeOfType),
						tSourceSegmentLength * pByteSizeOfType);

				assert(((pSrc_node->gPrivate_startIndex + pSrc_index + tSourceSegmentLength) &
						((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) == 0);

				memcpy(tTarget + ((tTargetStartIndex + tSourceSegmentLength) * pByteSizeOfType), 
						tSrc, (tTargetSegmentLength - tSourceSegmentLength) * pByteSizeOfType);

				if(tTargetSegmentLength < pCount)
				{
					assert(((pTarget_node->gPrivate_startIndex + pTarget_index + 
							tTargetSegmentLength) &
							((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) == 0);

					memcpy(tTarget, 
							tSrc + ((tTargetSegmentLength - tSourceSegmentLength) * pByteSizeOfType),
							(pCount - tTargetSegmentLength) * pByteSizeOfType);
				}
			}
		}
	}
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_insertSpaceAt(Crx_C_Tree * pThis,
		size_t pByteSizeOfType, Crx_C_TypeBluePrint_MoveConstruct pFunc_moveConstruct,
		Crx_C_TypeBluePrint_MoveDestruct pFunc_moveDestruct, bool pIsToRotateRightIfRing,
		Crx_C_Tree_Private_Node * pNode, unsigned char * pBuffer, size_t pLength, size_t pIndex,
		size_t pWidth)
{
	if(!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS)
	{
		if((pFunc_moveConstruct != NULL) || (pFunc_moveDestruct != NULL))
		{
			if(pFunc_moveConstruct != NULL)
			{
				CRX_FOR(size_t tI = pLength - 1, tI >= pIndex, tI--)
				{
					pFunc_moveConstruct(pBuffer + ((pIndex + tI + pWidth) * pByteSizeOfType),
							pBuffer + ((pIndex + tI) * pByteSizeOfType));

					if(pFunc_moveDestruct != NULL)
						{(*(pFunc_moveDestruct))(pBuffer + ((pIndex + tI) * pByteSizeOfType));}
				}
				CRX_ENDFOR
			}
			else
			{
				CRX_FOR(size_t tI = pLength - 1, tI >= pIndex, tI--)
				{
					memcpy(pBuffer + ((pIndex + tI + pWidth) * pByteSizeOfType),
							pBuffer + ((pIndex + tI) * pByteSizeOfType), pByteSizeOfType);

					if(pFunc_moveDestruct != NULL)
						{(*(pFunc_moveDestruct))(pBuffer + ((pIndex + tI) * pByteSizeOfType));}
				}
				CRX_ENDFOR
			}
		}
		else
		{
			memmove(pBuffer + ((pIndex + pWidth) * pByteSizeOfType), 
					pBuffer + (pIndex * pByteSizeOfType),
					(pLength - pIndex) * pByteSizeOfType);
		}
	}
	else
	{
		unsigned char * tBuffer = pBuffer - (pNode->gPrivate_startIndex * pByteSizeOfType);
		size_t tLength = pLength;

		if(pIndex == 0)
		{
			assert(!pIsToRotateRightIfRing);

			/*if(pNode->gPrivate_startIndex > pWidth)
				{pNode->gPrivate_startIndex = ((pSIZE_T)(pNode->gPrivate_startIndex - pWidth));}
			else
				{pNode->gPrivate_startIndex = ((pSIZE_T)((2 * pThis->gPrviate_countOfMidElementInNode) - (pWidth - pNode->gPrivate_startIndex)));}*/
		}
		else if((pIndex == tLength) && pIsToRotateRightIfRing)
			{}
		else
		{
			size_t tInsertIndex = (pNode->gPrivate_startIndex + pIndex) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1);

			assert(tInsertIndex != pNode->gPrivate_startIndex);

			if((pFunc_moveConstruct != NULL) || (pFunc_moveDestruct != NULL))
			{
				if(pFunc_moveConstruct != NULL)
				{
					/*if((tLength >> 1) < pIndex)*/
					if(pIsToRotateRightIfRing)
					{
						CRX_FOR(size_t tI = tLength - 1, tI >= pIndex, tI--)
						{
							(*(pFunc_moveConstruct))(
									tBuffer + (((pNode->gPrivate_startIndex + tI + pWidth) & 
											((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
											pByteSizeOfType),
									tBuffer + (((pNode->gPrivate_startIndex + tI) & 
											((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
											pByteSizeOfType));

							if(pFunc_moveDestruct != NULL)
							{
								(*(pFunc_moveDestruct))(tBuffer +
										(((pNode->gPrivate_startIndex + tI) & 
										((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
										pByteSizeOfType));
							}
						}
						CRX_ENDFOR
					}
					else
					{
						CRX_FOR(size_t tI = 0, tI < pIndex, tI++)
						{
							(*(pFunc_moveConstruct))(
									tBuffer + (((pNode->gPrivate_startIndex + tI +
											(2 * pThis->gPrviate_countOfMidElementInNode) - pWidth) &
											((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
											pByteSizeOfType),
									tBuffer + (((pNode->gPrivate_startIndex + tI) &
											((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
											pByteSizeOfType));

							if(pFunc_moveDestruct != NULL)
							{
								(*(pFunc_moveDestruct))(tBuffer +
										(((pNode->gPrivate_startIndex + tI) &
										((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
										pByteSizeOfType));
							}
						}
						CRX_ENDFOR

						/*pNode->gPrivate_startIndex = (pNode->gPrivate_startIndex + (2 * pThis->gPrviate_countOfMidElementInNode) -
								pWidth) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1);*/
					}
				}
				else
				{
					/*THIS CODE IS NOT OPTIMAL.*/
					/*if((tLength >> 1) < pIndex)*/
					if(pIsToRotateRightIfRing)
					{
						CRX_FOR(size_t tI = tLength - 1, tI >= pIndex, tI--)
						{
							memmove(tBuffer + (((pNode->gPrivate_startIndex + tI + pWidth) &
											((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
											pByteSizeOfType),
									tBuffer + (((pNode->gPrivate_startIndex + tI) &
											((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) *
											pByteSizeOfType),
									pByteSizeOfType);

							(*(pFunc_moveDestruct))(tBuffer +
									(((pNode->gPrivate_startIndex + tI) & 
									((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
									pByteSizeOfType));
						}
						CRX_ENDFOR
					}
					else
					{
						CRX_FOR(size_t tI = 0, tI < pIndex, tI++)
						{
							memmove(tBuffer + (((pNode->gPrivate_startIndex + tI +
											(2 * pThis->gPrviate_countOfMidElementInNode) - pWidth) &
											((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
											pByteSizeOfType),
									tBuffer + (((pNode->gPrivate_startIndex + tI) &
											((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
											pByteSizeOfType),
									pByteSizeOfType);

							(*(pThis->gPrivate_typeBluePrint__element->gFUNC__MOVE_DESTRUCT))(tBuffer +
									(((pNode->gPrivate_startIndex + tI) &
									((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
									pByteSizeOfType));
						}
						CRX_ENDFOR

						/*pNode->gPrivate_startIndex = (pNode->gPrivate_startIndex + (2 * pThis->gPrviate_countOfMidElementInNode) -
								pWidth) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1);*/
					}
				}
			}
			else
			{
				/*if((tLength >> 1) >= pIndex)*/
				if(!pIsToRotateRightIfRing)
				{
					if(pNode->gPrivate_startIndex >= pWidth)
					{
						if(pNode->gPrivate_startIndex + 1 <= tInsertIndex)
						{
							memmove(tBuffer + ((pNode->gPrivate_startIndex - pWidth) * 
											pByteSizeOfType),
									tBuffer + (pNode->gPrivate_startIndex * pByteSizeOfType),
									(tInsertIndex - pNode->gPrivate_startIndex) *
											pByteSizeOfType);
						}
						else
						{
							memmove(tBuffer + ((pNode->gPrivate_startIndex - pWidth) * 
											pByteSizeOfType),
									tBuffer + (pNode->gPrivate_startIndex * pByteSizeOfType),
									((2 * pThis->gPrviate_countOfMidElementInNode) - 
											pNode->gPrivate_startIndex) * pByteSizeOfType);

							if(tInsertIndex <= pWidth)
							{
								memmove(tBuffer + (((2 * pThis->gPrviate_countOfMidElementInNode) - 
												pWidth) * pByteSizeOfType), 
										tBuffer, tInsertIndex * pByteSizeOfType);
							}
							else
							{
								memmove(tBuffer + (((2 * pThis->gPrviate_countOfMidElementInNode) - 
												pWidth) * pByteSizeOfType), 
										tBuffer, pWidth * pByteSizeOfType);
								memmove(tBuffer,
										tBuffer + (pWidth * pByteSizeOfType),
										(tInsertIndex - pWidth) * pByteSizeOfType);
							}
						}

						/*pNode->gPrivate_startIndex =
								((pSIZE_T)(pNode->gPrivate_startIndex - pWidth));*/
					}
					else
					{
						if(pWidth < tInsertIndex)
						{
							memmove(tBuffer + (((2 * pThis->gPrviate_countOfMidElementInNode) - 
											(pWidth - pNode->gPrivate_startIndex)) * 
											pByteSizeOfType),
									tBuffer + (pNode->gPrivate_startIndex * pByteSizeOfType),
									(pWidth - pNode->gPrivate_startIndex) * pByteSizeOfType);
							memmove(tBuffer, tBuffer + (pWidth * pByteSizeOfType),
									(tInsertIndex - pWidth) * pByteSizeOfType);
						}
						else
						{
							memmove(tBuffer + (((2 * pThis->gPrviate_countOfMidElementInNode) -
											(pWidth - pNode->gPrivate_startIndex)) * 
											pByteSizeOfType),
									tBuffer + (pNode->gPrivate_startIndex * pByteSizeOfType),
									(tInsertIndex - pNode->gPrivate_startIndex) *
											pByteSizeOfType);
						}
						/*pNode->gPrivate_startIndex = ((pSIZE_T)((2 * pThis->gPrviate_countOfMidElementInNode) - (pWidth - pNode->gPrivate_startIndex)));*/
					}
				}
				else
				{
					size_t tEndIndex = (pNode->gPrivate_startIndex + tLength - 1) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1);

					if((2 * pThis->gPrviate_countOfMidElementInNode) - 1 - tEndIndex >= pWidth)
					{
						if(tEndIndex + 1 >= tInsertIndex)
						{
							memmove(tBuffer + ((tInsertIndex + pWidth) * pByteSizeOfType),
									tBuffer + (tInsertIndex * pByteSizeOfType),
									(tEndIndex  + 1 - tInsertIndex) * pByteSizeOfType);
						}
						else
						{
							memmove(tBuffer + (pWidth * pByteSizeOfType), tBuffer, 
									(tEndIndex + 1) * pByteSizeOfType);

							if((2 * pThis->gPrviate_countOfMidElementInNode) - tInsertIndex <= pWidth)
							{
								memmove(tBuffer + ((pWidth - 
												((2 * pThis->gPrviate_countOfMidElementInNode) - 
												tInsertIndex)) * pByteSizeOfType),
										tBuffer + (tInsertIndex * pByteSizeOfType),
										((2 * pThis->gPrviate_countOfMidElementInNode) - tInsertIndex) * pByteSizeOfType);
							}
							else
							{
								memmove(tBuffer, tBuffer + (((2 * 
												pThis->gPrviate_countOfMidElementInNode) - pWidth) * 
												pByteSizeOfType),
										pWidth * pByteSizeOfType);
								memmove(tBuffer + ((tInsertIndex + pWidth) * pByteSizeOfType),
										tBuffer + (tInsertIndex * pByteSizeOfType),
										((2 * pThis->gPrviate_countOfMidElementInNode) - pWidth - tInsertIndex) * pByteSizeOfType);
							}
						}
					}
					else
					{
						if((2 * pThis->gPrviate_countOfMidElementInNode) - pWidth > tInsertIndex)
						{
							memmove(tBuffer, 
									tBuffer + (((2 * pThis->gPrviate_countOfMidElementInNode) - 
											pWidth) * pByteSizeOfType),
									(tEndIndex + pWidth + 1 - (2 * pThis->gPrviate_countOfMidElementInNode)) * pByteSizeOfType);
							memmove(tBuffer + ((tInsertIndex + pWidth) * pByteSizeOfType), 
									tBuffer + (tInsertIndex * pByteSizeOfType),
									((2 * pThis->gPrviate_countOfMidElementInNode) - pWidth - 
											tInsertIndex) * pByteSizeOfType);
						}
						else
						{
							memmove(tBuffer, tBuffer + (tInsertIndex * pByteSizeOfType),
									(tEndIndex + 1 - tInsertIndex) * pByteSizeOfType);
						}
					}
				}
			}
		}
	}
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_updateStartIndexAfterInsertionOfSpace(
		Crx_C_Tree * pThis, bool pIsToRotateRightIfRing, Crx_C_Tree_Private_Node * pNode,
		size_t pIndex, size_t pWidth)
{
	if(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS)
	{
		if(pIndex == 0)
		{
			assert(!pIsToRotateRightIfRing);

			if(pNode->gPrivate_startIndex >= pWidth)
				{pNode->gPrivate_startIndex = pNode->gPrivate_startIndex - pWidth;}
			else
				{pNode->gPrivate_startIndex = (2 * pThis->gPrviate_countOfMidElementInNode) - (pWidth - pNode->gPrivate_startIndex);}
		}
		else
		{
			/*if((tLength >> 1) >= pIndex)*/
			if(!pIsToRotateRightIfRing)
			{
				/*SEE NOTES OF CRX__C__TREE__PRIVATE__INSERT_SPACE_AT()*/
				pNode->gPrivate_startIndex = (pNode->gPrivate_startIndex + (2 * pThis->gPrviate_countOfMidElementInNode) -
						pWidth) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1);
			}
		}
	}
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_removeSpaceFrom(
		Crx_C_Tree * pThis, size_t pByteSizeOfType, 
		Crx_C_TypeBluePrint_MoveConstruct pFunc_moveConstruct,
		Crx_C_TypeBluePrint_MoveDestruct pFunc_moveDestruct, 
		Crx_C_Tree_Private_Node * pNode, unsigned char * pBuffer,
		size_t pLength, size_t pIndex, size_t pWidth,
		bool pIsToRotateRightIfRing)
{
	if(!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS)
	{
		memmove(pBuffer + (pIndex * pByteSizeOfType), 
				pBuffer + ((pIndex + pWidth) * pByteSizeOfType),
				(pLength - (pIndex) - (pWidth)) * pByteSizeOfType);
	}
	else
	{
		unsigned char * tBuffer = pBuffer - (pNode->gPrivate_startIndex * pByteSizeOfType);

		if((pFunc_moveConstruct != NULL) || (pFunc_moveDestruct != NULL))
		{
			if(pFunc_moveConstruct != NULL)
			{
				if(pIsToRotateRightIfRing)
				{
					CRX_FOR(size_t tI = 0, tI < pIndex, tI++)
					{
						(*(pFunc_moveConstruct))(tBuffer +
										(((pNode->gPrivate_startIndex + pIndex + pWidth - 1 - tI) &
										((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
										pByteSizeOfType),
								tBuffer + (((pNode->gPrivate_startIndex + pIndex - 1 - tI) &
										((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
										pByteSizeOfType));

						if(pFunc_moveDestruct != NULL)
						{
							(*(pFunc_moveDestruct))(tBuffer +
									(((pNode->gPrivate_startIndex + pIndex - 1 - tI) & 
									((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
									pByteSizeOfType));
						}
					}
					CRX_ENDFOR

					/*pNode->gPrivate_startIndex = ((pSIZE_T)((pNode->gPrivate_startIndex + pWidth) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1)));*/
				}
				else
				{
					CRX_FOR(size_t tI = 0, tI < pLength - (pWidth) - (pIndex), tI++)
					{
						(*(pFunc_moveConstruct))(tBuffer +
										(((pNode->gPrivate_startIndex + tI + pIndex) & 
										((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
										pByteSizeOfType),
								tBuffer + (((pNode->gPrivate_startIndex + tI + pIndex + pWidth) &
										((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
										pByteSizeOfType));

						if(pFunc_moveDestruct != NULL)
						{
							(*(pFunc_moveDestruct))(tBuffer +
									(((pNode->gPrivate_startIndex + tI + pIndex + pWidth) & 
									((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
									pByteSizeOfType));
						}
					}
					CRX_ENDFOR
				}
			}
			else
			{
				if(pIsToRotateRightIfRing)
				{
					CRX_FOR(size_t tI = 0, tI < pIndex, tI++)
					{
						memmove(tBuffer + (((pNode->gPrivate_startIndex + pIndex + pWidth - 1 - 
										tI) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) *
										pByteSizeOfType),
								tBuffer + (((pNode->gPrivate_startIndex + pIndex - 1 - tI) &
										((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
										pByteSizeOfType),
								pByteSizeOfType);

						(*(pFunc_moveDestruct))(tBuffer +
								(((pNode->gPrivate_startIndex + pIndex - 1 - tI) & 
								((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
								pByteSizeOfType));
					}
					CRX_ENDFOR

					/*pNode->gPrivate_startIndex = ((pSIZE_T)((pNode->gPrivate_startIndex + pWidth) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1)));*/
				}
				else
				{
					CRX_FOR(size_t tI = 0, tI < pLength - (pWidth) - (pIndex), tI++)
					{
						memmove(tBuffer + (((pNode->gPrivate_startIndex + tI + pIndex) & 
										((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
										pByteSizeOfType),
								tBuffer + (((pNode->gPrivate_startIndex + tI + pIndex + pWidth) & 
										((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
										pByteSizeOfType),
								pByteSizeOfType);

						(*(pFunc_moveDestruct))(tBuffer +
								(((pNode->gPrivate_startIndex + tI + pIndex + pWidth) & 
								((2 * pThis->gPrviate_countOfMidElementInNode) - 1)) * 
								pByteSizeOfType));
					}
					CRX_ENDFOR
				}
			}
		}
		else
		{
			if(pIsToRotateRightIfRing)
			{
				if(pIndex > 0)
				{
					crx_c_tree_private_rawRotateRight(pThis, pByteSizeOfType, tBuffer,
							pNode->gPrivate_startIndex, ((pNode->gPrivate_startIndex + pIndex - 1) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1)),
							pWidth);
				}

				/*pNode->gPrivate_startIndex = ((pSIZE_T)((pNode->gPrivate_startIndex + pWidth) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1)));*/
			}
			else
			{
				if(pIndex + pWidth < pLength)
				{
					crx_c_tree_private_rawRotateLeft(pThis, pByteSizeOfType, tBuffer,
							((pNode->gPrivate_startIndex + pIndex + pWidth) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1)),
							((pNode->gPrivate_startIndex + pLength - 1) & ((2 * pThis->gPrviate_countOfMidElementInNode) - 1)),
							pWidth);
				}
			}
		}
	}

	/*pThis->gPrivate_length = ((pSIZE_T)(pThis->gPrivate_length - (pWidth)));*/
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_updateStartIndexAfterRemovalOfSpace(
		Crx_C_Tree * pThis, Crx_C_Tree_Private_Node * pNode, size_t pWidth,
		bool pIsToRotateRightIfRing)
{
	if(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS)
	{
		if(pIsToRotateRightIfRing)
		{
			pNode->gPrivate_startIndex = ((pNode->gPrivate_startIndex + pWidth) &
					((2 * pThis->gPrviate_countOfMidElementInNode) - 1));
		}
	}
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_rawRotateRight(Crx_C_Tree * pThis,
		size_t pByteSizeOfType, unsigned char * pElements, size_t pRawStartIndex, 
		size_t pRawEndIndex, size_t pWidth)
{
	assert(pWidth > 0);

	size_t tEmptySpaceBeforeEnd;

	if(pRawEndIndex < pRawStartIndex)
		{tEmptySpaceBeforeEnd = 0;}
	else
		{tEmptySpaceBeforeEnd = (2 * pThis->gPrviate_countOfMidElementInNode) - pRawEndIndex - 1;}

	if(pRawEndIndex < pRawStartIndex)
	{
		memmove(pElements + (pWidth * pByteSizeOfType), pElements,
				/*pRawEndIndex * pByteSizeOfType*/
				(pRawEndIndex + 1) * pByteSizeOfType);
	}

	if(pWidth <= tEmptySpaceBeforeEnd)
	{
		memmove(pElements + ((pRawStartIndex + pWidth) * pByteSizeOfType), 
				pElements + (pRawStartIndex * pByteSizeOfType),
				(pRawEndIndex + 1 - pRawStartIndex) * pByteSizeOfType);
	}
	else
	{
		if(pWidth < (2 * pThis->gPrviate_countOfMidElementInNode) - pRawStartIndex)
		{
			memcpy(pElements, 
					pElements + (((2 * pThis->gPrviate_countOfMidElementInNode) - 
							(pWidth - tEmptySpaceBeforeEnd)) * pByteSizeOfType), 
					(pWidth - tEmptySpaceBeforeEnd) * pByteSizeOfType);

			memmove(pElements + ((pRawStartIndex + pWidth) * pByteSizeOfType), 
					pElements + (pRawStartIndex * pByteSizeOfType),
					((2 * pThis->gPrviate_countOfMidElementInNode) - pRawStartIndex  - pWidth) * 
							pByteSizeOfType);
		}
		else
		{
			memcpy(pElements + ((pWidth - ((2 * pThis->gPrviate_countOfMidElementInNode) - pRawStartIndex)) * pByteSizeOfType), 
					pElements + (pRawStartIndex * pByteSizeOfType),
					((2 * pThis->gPrviate_countOfMidElementInNode) - tEmptySpaceBeforeEnd - pRawStartIndex) * pByteSizeOfType);
		}
	}
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_rawRotateLeft(Crx_C_Tree * pThis,
		size_t pByteSizeOfType, unsigned char * pElements, size_t pRawStartIndex, 
		size_t pRawEndIndex, size_t pWidth)
{
	assert(pWidth > 0);

	size_t tIndexOfFirstElementFromLeftSide;

	if(pRawStartIndex > pRawEndIndex)
		{tIndexOfFirstElementFromLeftSide = 0;}
	else
		{tIndexOfFirstElementFromLeftSide = pRawStartIndex;}

	if(pRawStartIndex > pRawEndIndex)
	{ 
		memmove(pElements + ((pRawStartIndex - pWidth) * pByteSizeOfType), 
				pElements + (pRawStartIndex * pByteSizeOfType),
				((2 * pThis->gPrviate_countOfMidElementInNode) - pRawStartIndex) * pByteSizeOfType);
	}

	if(pWidth <= tIndexOfFirstElementFromLeftSide)
	{
		memcpy(pElements + ((pRawStartIndex - pWidth) * pByteSizeOfType), 
				pElements + (pRawStartIndex * pByteSizeOfType),
				/*(pRawStartIndex + 1 - pRawStartIndex) * pByteSizeOfType*/
				(pRawEndIndex + 1 - pRawStartIndex) * pByteSizeOfType);
	}
	else
	{
		if(pWidth <= pRawEndIndex)
		{
			memcpy(pElements + (((2 * pThis->gPrviate_countOfMidElementInNode) + tIndexOfFirstElementFromLeftSide - pWidth) * 
					pByteSizeOfType),
					pElements + (tIndexOfFirstElementFromLeftSide * pByteSizeOfType),
					(pWidth - tIndexOfFirstElementFromLeftSide) * pByteSizeOfType);

			memcpy(pElements, pElements + (pWidth * pByteSizeOfType),
					(pRawEndIndex + 1 - pWidth) * pByteSizeOfType);
		}
		else
		{
			memcpy(pElements + (((2 * pThis->gPrviate_countOfMidElementInNode) + tIndexOfFirstElementFromLeftSide - pWidth) * 
					pByteSizeOfType),
					pElements + (tIndexOfFirstElementFromLeftSide * pByteSizeOfType),
					(pRawEndIndex + 1 - tIndexOfFirstElementFromLeftSide) * pByteSizeOfType);
		}
	}
}

CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_private_transferConstruct(Crx_C_Tree * pThis,
		size_t pByteSizeOfType, Crx_C_TypeBluePrint_MoveConstruct pFunc_moveConstruct,
		Crx_C_TypeBluePrint_MoveDestruct pFunc_moveDestruct, 
		void * pObject, void * pObject__2)
{
	if((pFunc_moveConstruct != NULL) || (pFunc_moveDestruct != NULL))
	{
		if(pFunc_moveConstruct = NULL)
			{(*(pFunc_moveConstruct))(pObject, pObject__2);}
		else
			{memcpy(pObject, pObject__2, pByteSizeOfType);}

		if(pFunc_moveDestruct)
			{(*(pFunc_moveDestruct))(pObject__2);}
	}
	else
		{memcpy(pObject, pObject__2, pByteSizeOfType);}
}

CRX__LIB__PRIVATE_C_FUNCTION() unsigned char * crx_c_tree_private_getElementEntry(
		Crx_C_Tree const * pThis, Crx_C_Tree_Private_Node const * CRX_NOT_NULL pNode, size_t pIndex)
{
	size_t vIndex = (!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? pIndex :
			(((pNode)->gPrivate_startIndex + pIndex) & 
			(2 * pThis->gPrviate_countOfMidElementInNode - 1)));

	if(pNode->gPrivate_type)
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			assert(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY);

			if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				return ((unsigned char *)(((unsigned char * *)(((unsigned char *)pNode) + 
								pThis->gPrivate_internalNode_byteOffsetToElementData)) + 
						(vIndex * sizeof(volatile void const *))));
			}
			else
			{
				return (((unsigned char *)(((unsigned char *)(pNode)) + 
								pThis->gPrivate_internalNode_byteOffsetToElementData)) + 
						(vIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
			}
		}
		else
		{
			if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				return ((unsigned char *)((unsigned char * *)(
						((Crx_C_Tree_Private_InternalNode *)pNode)->gPrivate_buffer.uElements + 
						(vIndex * sizeof(volatile void const *)))));
			}
			else
			{
				return ((unsigned char *)(
						((Crx_C_Tree_Private_InternalNode *)pNode)->gPrivate_buffer.uElements + 
						(vIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE)));
			}
		}
	}
	else
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX && !CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
		{
			if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				return ((unsigned char *)(((unsigned char * *)(((unsigned char *)pNode) + 
								pThis->gPrivate_leafNode_byteOffsetToElementData)) + 
						(vIndex * sizeof(volatile void const *))));
			}
			else
			{
				return (((unsigned char *)(((unsigned char *)pNode) + 
								pThis->gPrivate_leafNode_byteOffsetToElementData)) + 
						(vIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
			}
		}
		else
		{
			if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				return ((unsigned char *)((unsigned char * *)(
						((Crx_C_Tree_Private_LeafNode *)pNode)->gPrivate_buffer.uElements + 
						(vIndex * sizeof(volatile void const *)))));
			}
			else
			{
				return ((unsigned char * )(
						((Crx_C_Tree_Private_LeafNode *)pNode)->gPrivate_buffer.uElements + 
						(vIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE)));
			}
		}
	}
}
CRX__LIB__PRIVATE_C_FUNCTION() unsigned char * crx_c_tree_private_getElement(
		Crx_C_Tree const * pThis, Crx_C_Tree_Private_Node const * CRX_NOT_NULL pNode, size_t pIndex)
{
	size_t vIndex = (!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? pIndex :
			(((pNode)->gPrivate_startIndex + pIndex) & 
			(2 * pThis->gPrviate_countOfMidElementInNode - 1)));

	if(pNode->gPrivate_type)
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX)
		{
			assert(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY);

			if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				return *(((unsigned char * *)(((unsigned char *)pNode) + 
								pThis->gPrivate_internalNode_byteOffsetToElementData)) + 
						(vIndex * sizeof(volatile void const *)));
			}
			else
			{
				return (((unsigned char *)(((unsigned char *)(pNode)) + 
								pThis->gPrivate_internalNode_byteOffsetToElementData)) + 
						(vIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
			}
		}
		else
		{
			if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				return *((unsigned char * *)(
						((Crx_C_Tree_Private_InternalNode *)pNode)->gPrivate_buffer.uElements + 
						(vIndex * sizeof(volatile void const *))));
			}
			else
			{
				return ((unsigned char *)(
						((Crx_C_Tree_Private_InternalNode *)pNode)->gPrivate_buffer.uElements + 
						(vIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE)));
			}
		}
	}
	else
	{
		if(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX && !CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
		{
			if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				return *(((unsigned char * *)(((unsigned char *)pNode) + 
								pThis->gPrivate_leafNode_byteOffsetToElementData)) + 
						(vIndex * sizeof(volatile void const *)));
			}
			else
			{
				return (((unsigned char *)(((unsigned char *)pNode) + 
								pThis->gPrivate_leafNode_byteOffsetToElementData)) + 
						(vIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE));
			}
		}
		else
		{
			if(CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT)
			{
				return *((unsigned char * *)(
						((Crx_C_Tree_Private_LeafNode *)pNode)->gPrivate_buffer.uElements + 
						(vIndex * sizeof(volatile void const *))));
			}
			else
			{
				return ((unsigned char * )(
						((Crx_C_Tree_Private_LeafNode *)pNode)->gPrivate_buffer.uElements + 
						(vIndex * pThis->gPrivate_typeBluePrint__element->gBYTE_SIZE)));
			}
		}
	}
}
CRX__LIB__PRIVATE_C_FUNCTION() Crx_C_Tree_Private_Node * * crx_c_tree_private_getChildNode(
		Crx_C_Tree const * pThis, Crx_C_Tree_Private_Node const * CRX_NOT_NULL pNode, size_t pIndex)
{
	assert(pNode->gPrivate_type);

	if(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS)
	{
		return (((Crx_C_Tree_Private_Node * *)(((unsigned char *)pNode) +
				pThis->gPrivate_internalNode_byteOffsetToChildNodes)) +
				(((pNode)->gPrivate_startIndex + pIndex) &
				(2 * pThis->gPrviate_countOfMidElementInNode - 1)));
	}
	else		
	{
		return (((Crx_C_Tree_Private_Node * *)(((unsigned char *)pNode) +
				pThis->gPrivate_internalNode_byteOffsetToChildNodes)) + pIndex);
	}
}
CRX__LIB__PRIVATE_C_FUNCTION() unsigned char * crx_c_tree_private_getIndexFrom(
		Crx_C_Tree const * pThis, Crx_C_Tree_Private_Node const * CRX_NOT_NULL pNode, size_t pIndex)
{
	assert(CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX);

	size_t vIndex = (!CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS ? pIndex :
			(((pNode)->gPrivate_startIndex + pIndex) & 
			(2 * pThis->gPrviate_countOfMidElementInNode - 1)));

	if(pNode->gPrivate_type)
	{
		if(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS)
		{
			return ((unsigned char *)(
					((Crx_C_Tree_Private_InternalNode *)pNode)->gPrivate_buffer.uIndices + 
					((((pNode)->gPrivate_startIndex + pIndex) & 
							(2 * pThis->gPrviate_countOfMidElementInNode - 1)) * 
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE)));
		}
		else
		{
			return ((unsigned char *)(
					((Crx_C_Tree_Private_InternalNode *)pNode)->gPrivate_buffer.uIndices + 
					(pIndex * pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE)));
		}
	}
	else
	{
		assert(!CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY);

		if(CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS)
		{
			return ((unsigned char *)(
					((Crx_C_Tree_Private_LeafNode *)pNode)->gPrivate_buffer.uIndices + 
					((((pNode)->gPrivate_startIndex + pIndex) & 
							(2 * pThis->gPrviate_countOfMidElementInNode - 1)) * 
							pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE)));
		}
		else
		{
			return ((unsigned char *)(
					((Crx_C_Tree_Private_LeafNode *)pNode)->gPrivate_buffer.uIndices + 
					(pIndex * pThis->gPrivate_typeBluePrint__index->gBYTE_SIZE)));
		}
	}
}


CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_iterator_construct(
		Crx_C_Tree_Iterator * pThis, Crx_C_Tree * pTree)
{
	if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY2(pTree))
	{
		_crx_c_tree_iterator_construct(pThis, NULL, false,
				(Crx_C_Tree *)pTree);
	}
	else
	{
		_crx_c_tree_iterator_construct(pThis, NULL, false,
				(Crx_C_Tree *)pTree);
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_iterator_construct2(
		Crx_C_Tree_Iterator * pThis, Crx_C_Tree const * pTree)
{
	if(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY2(pTree))
	{
		_crx_c_tree_iterator_construct(pThis, NULL, true,
				(Crx_C_Tree *)pTree);
	}
	else
	{
		_crx_c_tree_iterator_construct(pThis, NULL, true,
				(Crx_C_Tree *)pTree);
	}
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_iterator_private_construct3(
		Crx_C_Tree_Iterator * pThis,
		Crx_C_Tree_Iterator_Private_Position * pPositions,
		Crx_C_Tree const * pTree)
{
	assert(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY2(pTree));

	_crx_c_tree_iterator_construct(pThis, pPositions, false,
			(Crx_C_Tree *)pTree);
}
CRX__LIB__PRIVATE_C_FUNCTION() void _crx_c_tree_iterator_construct(
		Crx_C_Tree_Iterator * pThis,
		Crx_C_Tree_Iterator_Private_Position * pPositions,
		bool pIsConstant, Crx_C_Tree * pTree)
{
	assert(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY2(pTree) || (pPositions == NULL));

	pThis->gPrivate_isConstant = pIsConstant;
	pThis->gPrivate_tree = pTree;

	if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		pThis->gPrivate_isPositionsMine = (pPositions == NULL);
		pThis->gPrivate_node = NULL;

		if(pPositions != NULL)
		{
			pThis->gPrivate_positions = pPositions;
			memset(pThis->gPrivate_positions, 0, 64 * sizeof(
					Crx_C_Tree_Iterator_Private_Position));
		}
		else
		{
			/*IT SHOULD BE 65 WITH THE FIXED ALGORITHM(ASSUMING 64BIT MACHINES) BUT THIS IS 
					ASSUMING 1 BYTE PER NODE*/
			pThis->gPrivate_positions = (Crx_C_Tree_Iterator_Private_Position *)calloc(1, 
					64 * sizeof(Crx_C_Tree_Iterator_Private_Position));
		}

		pThis->gPrivate_position__current = pThis->gPrivate_positions;

		if(pThis->gPrivate_positions != NULL)
		{
			(pThis->gPrivate_positions + 0)->gNode = NULL;
			(pThis->gPrivate_positions + 0)->gIndex = 0;

			/*crx_c_tree_iterator_reset(pThis, pTree); */
		}
	}
	else
	{
		pThis->gPrivate_node = NULL;
		pThis->gPrivate_elementIndex = 0;

		/*crx_c_tree_iterator_reset(pThis, pTree);*/
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_iterator_copyConstruct(
		Crx_C_Tree_Iterator * pThis,
		Crx_C_Tree_Iterator const * CRX_NOT_NULL pIterator)
{
	/* AN ASSERT HERE WOULD BE A FORMAL VIOLATION; THE EXISTANCE OF THE FUNDAMENTAL MEMORY
			FUNCTION IS THE CONTRACT, AND THIS FUNCTION HERE IS PUBLIC.
	assert(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY2(pIterator));*/

	if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY2(pIterator))
		{memcpy(pThis, pIterator, sizeof(Crx_C_Tree_Iterator));}
	else
		{crx_c_tree_iterator_private_copyConstructUsing(pThis, NULL, pIterator);}
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_iterator_private_copyConstructFrom(
		Crx_C_Tree_Iterator * pThis,
		Crx_C_Tree_Iterator_Private_Position * pPositions,
		Crx_C_Tree_Iterator const * CRX_NOT_NULL pIterator)
{
	assert(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY2(pIterator));
	crx_c_tree_iterator_private_copyConstructUsing(pThis, pPositions, pIterator);
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_iterator_private_copyConstructUsing(
		Crx_C_Tree_Iterator * pThis,
		Crx_C_Tree_Iterator_Private_Position * pPositions,
		Crx_C_Tree_Iterator const * CRX_NOT_NULL pIterator)
{
	assert(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY2(pIterator));

	pThis->gPrivate_isConstant = pIterator->gPrivate_isConstant;
	pThis->gPrivate_tree = pIterator->gPrivate_tree;
	pThis->gPrivate_node = pIterator->gPrivate_node;

	if(pIterator->gPrivate_positions != NULL)
	{
		pThis->gPrivate_isPositionsMine = (pPositions == NULL);

		if(pPositions != NULL)
		{
			pThis->gPrivate_positions = pPositions;
			memset(pThis->gPrivate_positions, 0, 64 * sizeof(
					Crx_C_Tree_Iterator_Private_Position));
		}
		else
		{
			pThis->gPrivate_positions = (Crx_C_Tree_Iterator_Private_Position *)calloc(1, 
					64 * sizeof(Crx_C_Tree_Iterator_Private_Position));
		}

		if(pThis->gPrivate_positions != NULL)
		{
			memcpy(pThis->gPrivate_positions, pIterator->gPrivate_positions,
					(pIterator->gPrivate_position__current - pIterator->gPrivate_positions +
					1) * sizeof(Crx_C_Tree_Iterator_Private_Position));

			pThis->gPrivate_position__current = pThis->gPrivate_positions +
					(pIterator->gPrivate_position__current - pIterator->gPrivate_positions);
		}
		else
			{pThis->gPrivate_position__current = NULL;}
	}
	else
	{
		pThis->gPrivate_isPositionsMine = false;
		pThis->gPrivate_positions = NULL;
		pThis->gPrivate_position__current = NULL;
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Tree_Iterator * crx_c_tree_iterator_new(
		Crx_C_Tree * pTree)
{
	Crx_C_Tree_Iterator * vReturn = (Crx_C_Tree_Iterator *)(calloc(1,
			sizeof(Crx_C_Tree_Iterator)));

	if(vReturn != NULL)
		{crx_c_tree_iterator_construct(vReturn, pTree);}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Tree_Iterator * crx_c_tree_iterator_new2(
		Crx_C_Tree const * pTree)
{
	Crx_C_Tree_Iterator * vReturn = (Crx_C_Tree_Iterator *)(calloc(1,
			sizeof(Crx_C_Tree_Iterator)));

	if(vReturn != NULL)
		{crx_c_tree_iterator_construct2(vReturn, pTree);}

	return vReturn;
}
CRX__LIB__PRIVATE_C_FUNCTION() Crx_C_Tree_Iterator * crx_c_tree_iterator_private_new3(
		Crx_C_Tree_Iterator_Private_Position * pPositions,
		Crx_C_Tree const * pTree)
{
	CRX_SCOPE_META
	assert(!CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY2(pTree));

	CRX_SCOPE
	Crx_C_Tree_Iterator * vReturn = (Crx_C_Tree_Iterator *)(calloc(1,
			sizeof(Crx_C_Tree_Iterator)));

	if(vReturn != NULL)
		{crx_c_tree_iterator_private_construct3(vReturn, pPositions, pTree);}

	return vReturn;
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Tree_Iterator * crx_c_tree_iterator_moveNew(
		Crx_C_Tree_Iterator * CRX_NOT_NULL pIterator)
{
	Crx_C_Tree_Iterator * vReturn = (Crx_C_Tree_Iterator *)(calloc(1,
			sizeof(Crx_C_Tree_Iterator)));

	if(vReturn != NULL)
		{memcpy(vReturn, pIterator, sizeof(Crx_C_Tree_Iterator));}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Tree_Iterator * crx_c_tree_iterator_copyNew(
		Crx_C_Tree_Iterator const * CRX_NOT_NULL pIterator)
{
	Crx_C_Tree_Iterator * vReturn = (Crx_C_Tree_Iterator *)(calloc(1,
			sizeof(Crx_C_Tree_Iterator)));

	if(vReturn != NULL)
	{
		if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY2(pIterator))
			{memcpy(vReturn, pIterator, sizeof(Crx_C_Tree_Iterator));}
		else
			{crx_c_tree_iterator_copyConstruct(vReturn, pIterator);}
	}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Tree_Iterator * crx_c_tree_iterator_private_copyNewUsing(
		Crx_C_Tree_Iterator_Private_Position * pPositions,
		Crx_C_Tree_Iterator const * CRX_NOT_NULL pIterator)
{
	CRX_SCOPE_META
	assert(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY2(pIterator));

	CRX_SCOPE
	Crx_C_Tree_Iterator * vReturn = (Crx_C_Tree_Iterator *)(calloc(1,
			sizeof(Crx_C_Tree_Iterator)));

	if(vReturn != NULL)
	{
		if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY2(pIterator))
			{memcpy(vReturn, pIterator, sizeof(Crx_C_Tree_Iterator));}
		else
			{crx_c_tree_iterator_private_copyConstructUsing(vReturn, pPositions, pIterator);}
	}

	return vReturn;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_iterator_destruct(
		Crx_C_Tree_Iterator * pThis)
{
	/* AN ASSERT HERE WOULD BE A FORMAL VIOLATION; THE EXISTANCE OF THE FUNDAMENTAL MEMORY
			FUNCTION IS THE CONTRACT, AND THIS FUNCTION HERE IS PUBLIC.
	assert(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY);*/
	if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
		{return;}

	if(pThis->gPrivate_isPositionsMine && (pThis->gPrivate_positions != NULL))
	{
		free(pThis->gPrivate_positions);
		pThis->gPrivate_positions = NULL;
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_iterator_free(Crx_C_Tree_Iterator * pThis)
	{free(pThis);}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_tree_iterator_copyAssignFrom(
		Crx_C_Tree_Iterator * pThis,
		Crx_C_Tree_Iterator const * CRX_NOT_NULL pIterator)
{
	assert(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY &&
			(pThis->gPrivate_tree->gPrivate_info == pIterator->gPrivate_tree->gPrivate_info));

	pThis->gPrivate_tree = pIterator->gPrivate_tree;
	pThis->gPrivate_node = pIterator->gPrivate_node;

	if(pThis->gPrivate_positions != NULL)
	{
		if(pIterator->gPrivate_positions != NULL)
		{
			memcpy(pThis->gPrivate_positions, pIterator->gPrivate_positions,
					64 * sizeof(Crx_C_Tree_Iterator_Private_Position));

			pThis->gPrivate_position__current = pThis->gPrivate_positions +
					(pIterator->gPrivate_position__current -
					pIterator->gPrivate_positions);
		}
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_iterator_associateWith(
		Crx_C_Tree_Iterator * pThis, Crx_C_Tree const * pTree)
	{crx_c_tree_iterator_private_doAssociateWith(pThis, false, pTree);}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_iterator_constantAssociateWith(
		Crx_C_Tree_Iterator * pThis, Crx_C_Tree const * pTree)
	{crx_c_tree_iterator_private_doAssociateWith(pThis, true, pTree);}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_iterator_private_doAssociateWith(
		Crx_C_Tree_Iterator * pThis, bool pIsConstant, Crx_C_Tree const * pTree)
{
	assert(pThis->gPrivate_isPositionsMine);
	
	pThis->gPrivate_tree = ((Crx_C_Tree *)pTree);
	
	if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		pThis->gPrivate_node = NULL;

		pThis->gPrivate_position__current = pThis->gPrivate_positions;
	}
	else
	{
		pThis->gPrivate_node = NULL;
		pThis->gPrivate_elementIndex = 0;
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_iterator_reset(Crx_C_Tree_Iterator * pThis)
{
	if((pThis->gPrivate_tree == NULL) || 
			(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY && 
			(pThis->gPrivate_positions == NULL)))
		{return;}

	if(pThis->gPrivate_tree->gPrivate_numberOfElements != 0)
	{
		if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
		{
			Crx_C_Tree_Private_Node * tNode =
					pThis->gPrivate_tree->gPrivate_node__root;

			/*THIS IS THE REASON 64 PER THE REFERENCE IMPLEMENTATION BECAME 65 HERE*/
			pThis->gPrivate_position__current = pThis->gPrivate_positions + 1;

			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
				{pThis->gPrivate_position__current->gNode = tNode;}
			else
				{pThis->gPrivate_node = tNode;}
			pThis->gPrivate_position__current->gIndex = 0;

			while(tNode->gPrivate_type)
			{
				tNode = *(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, tNode, 0));

				/*ASSERTION: NODES ARE NEVER EMPTY IF
								pThis->gPrivate_tree->gPrivate_numberOfElements != 0
						BUT STICKING TO REFERENCE */
				if(tNode != NULL)
				{
					(pThis->gPrivate_position__current)++;

					if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
						{pThis->gPrivate_position__current->gNode = tNode;}
					else
						{pThis->gPrivate_node = tNode;}

					pThis->gPrivate_position__current->gIndex = 0;
				}
				else
					{break;}
			}
		}
		else
		{
			pThis->gPrivate_node = pThis->gPrivate_tree->gPrivate_node__root;
			pThis->gPrivate_elementIndex = 0;

			while(pThis->gPrivate_node->gPrivate_type)
			{
				pThis->gPrivate_node = *(crx_c_tree_private_getChildNode(pThis->gPrivate_tree,
						pThis->gPrivate_node, 0));

				/*ASSERTION: NODES ARE NEVER EMPTY IF
								pThis->gPrivate_tree->gPrivate_numberOfElements != 0
						BUT STICKING TO REFERENCE */
				if(pThis->gPrivate_node != NULL)
					{}
				else
					{assert(false); break;}
			}
		}
	}
	else
	{
		if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
		{
			pThis->gPrivate_node = NULL;
			pThis->gPrivate_position__current = pThis->gPrivate_positions;
		}
		else
		{
			pThis->gPrivate_node = NULL;
			pThis->gPrivate_elementIndex = 0;
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_tree_iterator_resetToBack(
		Crx_C_Tree_Iterator * pThis)
{
	if((pThis->gPrivate_tree == NULL) || 
			(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY && 
			(pThis->gPrivate_positions == NULL)))
		{return;}

	if(pThis->gPrivate_tree->gPrivate_numberOfElements != 0)
	{
		if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
		{
			Crx_C_Tree_Private_Node * tNode =
					pThis->gPrivate_tree->gPrivate_node__root;

			/*THIS IS THE REASON 64 PER THE REFERENCE IMPLEMENTATION BECAME 65 HERE*/
			pThis->gPrivate_position__current = pThis->gPrivate_positions + 1;

			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
				{pThis->gPrivate_position__current->gNode = tNode;}
			else
				{pThis->gPrivate_node = tNode;}
			pThis->gPrivate_position__current->gIndex = pThis->gPrivate_tree->
					gPrivate_node__root->gPrivate_numberOfEntries;

			while(tNode->gPrivate_type)
			{
				tNode = *(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, tNode, 
						tNode->gPrivate_numberOfEntries));

				/*ASSERTION: NODES ARE NEVER EMPTY IF
								pThis->gPrivate_tree->gPrivate_numberOfElements != 0
						BUT STICKING TO REFERENCE */
				if(tNode != NULL)
				{
					(pThis->gPrivate_position__current)++;

					if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
						{pThis->gPrivate_position__current->gNode = tNode;}
					else
						{pThis->gPrivate_node = tNode;}

					pThis->gPrivate_position__current->gIndex =
							tNode->gPrivate_numberOfEntries;
				}
				else
					{break;}
			}

			if(pThis->gPrivate_position__current->gIndex > 0)
				{pThis->gPrivate_position__current->gIndex--;}
		}
		else
		{
			pThis->gPrivate_node = pThis->gPrivate_tree->gPrivate_node__root;

			while(pThis->gPrivate_node->gPrivate_type != 0)
			{
				pThis->gPrivate_node = *(crx_c_tree_private_getChildNode(
						pThis->gPrivate_tree, pThis->gPrivate_node,
						pThis->gPrivate_node->gPrivate_numberOfEntries));

				/*ASSERTION: NODES ARE NEVER EMPTY IF
								pThis->gPrivate_tree->gPrivate_numberOfElements != 0
						BUT STICKING TO REFERENCE
						ALSO NOTE THAT THIS NOT FULLY RELIABLE BECAUSE THE CODE DOES NOT
						NECESSARY ENFORCE NULL ON EMPTY POINTERS AS FORMALLY REQUIRED IN THE 
						SSTANDARD.*/
				if(pThis->gPrivate_node != NULL)
					{}
				else
					{assert(false); break;}
			}

			assert(pThis->gPrivate_node->gPrivate_numberOfEntries > 0);

			pThis->gPrivate_elementIndex =
					pThis->gPrivate_node->gPrivate_numberOfEntries - 1;
		}
	}
	else
	{
		if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
		{
			pThis->gPrivate_node = NULL;
			pThis->gPrivate_position__current = pThis->gPrivate_positions;
		}
		else
		{
			pThis->gPrivate_node = NULL;
			pThis->gPrivate_elementIndex = 0;
		}
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_tree_iterator_isEqualTo(
		Crx_C_Tree_Iterator * pThis, Crx_C_Tree_Iterator const * pIterator)
{
	if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		return ((pThis->gPrivate_tree != NULL) && 
				CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis->gPrivate_tree,
						pIterator->gPrivate_tree, false) &&
				CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis->gPrivate_node,
				pIterator->gPrivate_node, false) &&
				(pThis->gPrivate_elementIndex == pIterator->gPrivate_elementIndex));
	}
	else
	{
		/*
			REMEMBER, 
					pThis->gPrivate_position__current == pThis->gPrivate_positions 
			ALSO ACCOUNTS FOR 
					pThis->gPrivate_positions == NULL				
		*/
		return ((pThis->gPrivate_tree != NULL) && 
				CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis->gPrivate_tree,
						pIterator->gPrivate_tree, false) &&
				(((pThis->gPrivate_position__current == pThis->gPrivate_positions) &&
						(pIterator->gPrivate_position__current ==
								pIterator->gPrivate_positions) &&
						(pThis->gPrivate_positions->gIndex ==
								pIterator->gPrivate_positions->gIndex)) ||
						((pThis->gPrivate_position__current != pThis->gPrivate_positions) &&
						(pIterator->gPrivate_position__current !=
								pIterator->gPrivate_positions) &&
						(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ?
								CRX__ARE_POINTERS_TO_SAME_OBJECT(
								pThis->gPrivate_position__current->gNode,
								pIterator->gPrivate_position__current->gNode, false) :
								CRX__ARE_POINTERS_TO_SAME_OBJECT(pThis->gPrivate_node,
								pIterator->gPrivate_node, false)) &&
						(pThis->gPrivate_position__current->gIndex == 
								pIterator->gPrivate_position__current->gIndex))));
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_tree_iterator_next(Crx_C_Tree_Iterator * pThis)
{
	if(pThis->gPrivate_tree == NULL)
		{return false;}

	if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		/*THIS IS THE REASON 64 PER THE REFERENCE IMPLEMENTATION BECAME 65 HERE*/
		if(pThis->gPrivate_position__current == pThis->gPrivate_positions)
			{return false;}
		else
		{
			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
			{
				while(true)
				{
					(pThis->gPrivate_position__current->gIndex)++;

					while(pThis->gPrivate_position__current->gNode &&
							(pThis->gPrivate_position__current->gIndex <=
							pThis->gPrivate_position__current->gNode->
									gPrivate_numberOfEntries))
					{
						(pThis->gPrivate_position__current + 1)->gIndex = 0;
						(pThis->gPrivate_position__current + 1)->gNode =
								(pThis->gPrivate_position__current->
										gNode->gPrivate_type ?
								*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree,
										pThis->gPrivate_position__current->gNode,
										pThis->gPrivate_position__current->gIndex)) : NULL);
						(pThis->gPrivate_position__current)++;
					}
					(pThis->gPrivate_position__current)--;

					/*THIS IS THE REASON 64 PER THE REFERENCE IMPLEMENTATION BECAME 65 HERE*/
					if(pThis->gPrivate_position__current == pThis->gPrivate_positions)
					{
						pThis->gPrivate_positions->gIndex = 1;

						return false;
					}
					else if(pThis->gPrivate_position__current->gNode &&
							(pThis->gPrivate_position__current->gIndex <
							pThis->gPrivate_position__current->gNode->gPrivate_numberOfEntries))
						{return true;}
				}
			}
			else
			{
				Crx_C_Tree_Private_Node * tNode = pThis->gPrivate_node;

				while(true)
				{
					(pThis->gPrivate_position__current->gIndex)++;

					while(tNode &&
							(pThis->gPrivate_position__current->gIndex <=
							tNode->gPrivate_numberOfEntries))
					{
						pThis->gPrivate_node = tNode;
						(pThis->gPrivate_position__current + 1)->gIndex = 0;
						tNode = (tNode->gPrivate_type ? *(crx_c_tree_private_getChildNode(
								pThis->gPrivate_tree, tNode,
								pThis->gPrivate_position__current->gIndex)) : NULL);
						(pThis->gPrivate_position__current)++;
					}
					(pThis->gPrivate_position__current)--;

					if(tNode != NULL)
					{
						tNode = tNode->gPrivate_node__parent;
						pThis->gPrivate_node = tNode;
					}

					/*THIS IS THE REASON 64 PER THE REFERENCE IMPLEMENTATION BECAME 65 HERE*/
					if(pThis->gPrivate_position__current == pThis->gPrivate_positions)
					{
						pThis->gPrivate_positions->gIndex = 1;
						pThis->gPrivate_node = NULL;

						return false;
					}
					else if(pThis->gPrivate_node &&
							(pThis->gPrivate_position__current->gIndex <
							pThis->gPrivate_node->gPrivate_numberOfEntries))
						{return true;}
					else
						{tNode = pThis->gPrivate_node;}
				}
			}
		}
	}
	else
	{
		if(pThis->gPrivate_node == NULL)
			{return false;}
		else
		{
			if(pThis->gPrivate_elementIndex <
					(pThis->gPrivate_node->gPrivate_numberOfEntries - 1))
				{pThis->gPrivate_elementIndex = pThis->gPrivate_elementIndex + 1;}
			else
			{
				pThis->gPrivate_node = &(((Crx_C_Tree_Private_LeafNode *)
						(pThis->gPrivate_node))->gPrivate_leafNode__next->gPrivate_node);
				pThis->gPrivate_elementIndex = ((pThis->gPrivate_node != NULL) ? 0 : 1);
			}

			return true;
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_tree_iterator_prev(Crx_C_Tree_Iterator * pThis)
{
	if(pThis->gPrivate_tree == NULL)
		{return false;}

	if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		/*THIS IS THE REASON 64 PER THE REFERENCE IMPLEMENTATION BECAME 65 HERE*/
		if(pThis->gPrivate_position__current == pThis->gPrivate_positions)
		{
			if(pThis->gPrivate_positions->gIndex == 1)
			{
				pThis->gPrivate_positions->gIndex = 0;

				crx_c_tree_iterator_resetToBack(pThis);

				return (pThis->gPrivate_position__current != pThis->gPrivate_positions);
			}
			else
				{return false;}
		}
		else
		{
			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
			{
				bool tIsToSkipUp = false;

				while(true)
				{
					while(pThis->gPrivate_position__current->gNode /*&&
							(pThis->gPrivate_position__current->gIndex >= 0)*/)
					{
						/*if((pThis->gPrivate_position__current->gNode->
										gPrivate_type == 0) &&
								(pThis->gPrivate_position__current->gIndex == 0))*/
						if(!tIsToSkipUp)
						{
							(pThis->gPrivate_position__current + 1)->gNode =
											(pThis->gPrivate_position__current->gNode->
											gPrivate_type ?
									*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree,
											pThis->gPrivate_position__current->gNode,
											pThis->gPrivate_position__current->gIndex)) : NULL);
							(pThis->gPrivate_position__current + 1)->gIndex =
									(pThis->gPrivate_position__current->gNode->
											gPrivate_type ?
									(pThis->gPrivate_position__current + 1)->gNode->
											gPrivate_numberOfEntries : 0);

							(pThis->gPrivate_position__current)++;
						}
						else
						{
							tIsToSkipUp = false;

							break;
						}
					}
					--pThis->gPrivate_position__current;

					/*THIS IS THE REASON 64 PER THE REFERENCE IMPLEMENTATION BECAME 65 HERE*/
					if(pThis->gPrivate_position__current == pThis->gPrivate_positions)
					{
						pThis->gPrivate_positions->gIndex = 0;

						return false;
					}
					else if(pThis->gPrivate_position__current->gNode)
					{
						if(pThis->gPrivate_position__current->gIndex > 0)
						{
							(pThis->gPrivate_position__current->gIndex)--;

							return true;
						}
						else
							{tIsToSkipUp = true;}
					}
				}
			 }
			 else
			 {
				Crx_C_Tree_Private_Node * tNode = pThis->gPrivate_node;
				bool tIsToSkipUp = false;

				while(true)
				{
					while(tNode)
					{
						if(!tIsToSkipUp)
						{
							pThis->gPrivate_node = tNode;
							tNode = (pThis->gPrivate_node->gPrivate_type ?
									*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree,
											tNode, pThis->gPrivate_position__current->gIndex)) :
									NULL);
							(pThis->gPrivate_position__current + 1)->gIndex =
									(pThis->gPrivate_node->gPrivate_type ?
									tNode->gPrivate_numberOfEntries : 0);

							(pThis->gPrivate_position__current)++;
						}
						else
						{
							tIsToSkipUp = false;

							if(tNode == NULL)
								{tNode = pThis->gPrivate_node;}
							else
							{
								tNode = tNode->gPrivate_node__parent;
								pThis->gPrivate_node = tNode;
							}

							break;
						}
					}
					--pThis->gPrivate_position__current;

					/*if(tNode != NULL)
					{
						tNode = tNode->gPrivate_node__parent;
						pThis->gPrivate_node = tNode;
					}*/

					/*THIS IS THE REASON 64 PER THE REFERENCE IMPLEMENTATION BECAME 65 HERE*/
					if(pThis->gPrivate_position__current == pThis->gPrivate_positions)
					{
						pThis->gPrivate_positions->gIndex = 0;

						return false;
					}
					else if(pThis->gPrivate_node)
					{
						if(pThis->gPrivate_position__current->gIndex > 0)
						{
							(pThis->gPrivate_position__current->gIndex)--;

							return true;
						}
						else
						{
							tIsToSkipUp = true;
							tNode = pThis->gPrivate_node;
						}
					}
				}
			}
		}
	}
	else
	{
		if(pThis->gPrivate_node == NULL)
		{
			if(pThis->gPrivate_elementIndex == 1)
			{
				pThis->gPrivate_elementIndex = 0;

				crx_c_tree_iterator_resetToBack(pThis);

				return (pThis->gPrivate_node != NULL);
			}
			else
				{return false;}
		}
		else
		{
			if(pThis->gPrivate_elementIndex > 0)
				{pThis->gPrivate_elementIndex = pThis->gPrivate_elementIndex - 1;}
			else
			{
				pThis->gPrivate_node = &(((Crx_C_Tree_Private_LeafNode *)
						(pThis->gPrivate_node))->gPrivate_leafNode__prev->gPrivate_node);
				pThis->gPrivate_elementIndex = ((pThis->gPrivate_node != NULL) ?
						(pThis->gPrivate_node->gPrivate_numberOfEntries - 1) : 0);
			}

			return true;
		}
	}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_tree_iterator_isValid(
		Crx_C_Tree_Iterator * pThis)
{
	if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		return (pThis->gPrivate_position__current != pThis->gPrivate_positions);
	}
	else
	{
		return (pThis->gPrivate_node != NULL);
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_tree_iterator_setToPositionOf(
		Crx_C_Tree_Iterator * pThis, void const * pElement,
		Crx_C_Tree_Edge pEdge)
{
	if(pThis->gPrivate_tree == NULL)
		{return false;}

	if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
	{
		unsigned char * tIndex__guide = 
				((unsigned char *)CRX__ALLOCA(pThis->gPrivate_tree->gPrivate_typeBluePrint__index->
						gBYTE_SIZE));

		(*(pThis->gPrivate_tree->gPrivate_constructIndexFrom))(tIndex__guide, pElement);

		return crx_c_tree_iterator_setToPositionOf__do(pThis,
				tIndex__guide, NULL, pEdge);
	}
	else
	{
		return crx_c_tree_iterator_setToPositionOf__do(pThis,
				NULL, pElement, pEdge);
	}
}
CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_tree_iterator_setToPositionOf__do(
		Crx_C_Tree_Iterator * pThis, void const * pIndex__guide,
		void const * pElement, Crx_C_Tree_Edge pEdge)
{
	bool vReturn = false;

	if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		Crx_C_Tree_Iterator_Private_Position * tLastSeenLower_position =
				pThis->gPrivate_positions;
		Crx_C_Tree_Private_Node * tLastSeenLower_node = NULL;
		unsigned char * tIndex__guide = ((CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX && 
				CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY) ?
				((unsigned char *)CRX__ALLOCA(
				pThis->gPrivate_tree->gPrivate_typeBluePrint__index->gBYTE_SIZE)) : NULL);

		pThis->gPrivate_positions->gIndex = 0;

		pThis->gPrivate_position__current = pThis->gPrivate_positions + 1;
		if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
		{
			pThis->gPrivate_position__current->gNode =
					pThis->gPrivate_tree->gPrivate_node__root;
		}
		else
			{pThis->gPrivate_node = pThis->gPrivate_tree->gPrivate_node__root;}
		pThis->gPrivate_position__current->gIndex = 0;

		while((CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ? 
				pThis->gPrivate_position__current->gNode : pThis->gPrivate_node))
		{
			int32_t tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 0;
			size_t tImaginaryIndex = (CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX ?
					crx_c_tree_private_getSuitableImagineryIndexFor(
							pThis->gPrivate_tree,
							(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ?
									pThis->gPrivate_position__current->gNode :
									pThis->gPrivate_node),
							NULL, pIndex__guide,
							&tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode) :
					crx_c_tree_private_getSuitableImagineryIndexFor(
							pThis->gPrivate_tree,
							(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ? 
									pThis->gPrivate_position__current->gNode :
									pThis->gPrivate_node),
							pElement, NULL,
							&tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode));

			if(tImaginaryIndex > 0 /*>=*/ &&
					tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0)
			{
				pThis->gPrivate_position__current->gIndex = tImaginaryIndex - 1;

				tLastSeenLower_position = pThis->gPrivate_position__current;
				
				if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
					{tLastSeenLower_node = pThis->gPrivate_node;}

				if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
				{
					switch(pEdge)
					{
						case CRX__C__TREE__EDGE__LEFT:
						{
							/*NEED TO REWIND TO FIND FIRST*/

							while(true)
							{
								if(crx_c_tree_iterator_prev(pThis))
								{
									Crx_C_Tree_Private_Node * tNode =
											(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ?
											pThis->gPrivate_position__current->gNode :
											pThis->gPrivate_node);
									int32_t tOrderOfIndices = -1;

									tLastSeenLower_position =
											pThis->gPrivate_position__current;
									
									if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
										{tLastSeenLower_node = pThis->gPrivate_node;}

									if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
									{
										if(tNode->gPrivate_type)
										{
											memcpy(tIndex__guide,
													crx_c_tree_private_getIndexFrom(
															pThis->gPrivate_tree, tNode,
															pThis->
															gPrivate_position__current->
															gIndex),
													pThis->gPrivate_tree->
															gPrivate_typeBluePrint__index->
															gBYTE_SIZE);
										}
										else
										{
											(*(pThis->gPrivate_tree->gPrivate_constructIndexFrom))(
													tIndex__guide,
													crx_c_tree_private_getElement(
															pThis->gPrivate_tree, tNode, 
															pThis->
															gPrivate_position__current->
															gIndex));
										}

										tOrderOfIndices = (*(pThis->gPrivate_tree->
												gPrivate_getOrderOfIndices))(pIndex__guide, 
												tIndex__guide);
									}
									else
									{
										tOrderOfIndices = (*(pThis->gPrivate_tree->
												gPrivate_getOrderOfIndices))(pIndex__guide,
												((tNode->gPrivate_type) ?
												crx_c_tree_private_getIndexFrom(
												pThis->gPrivate_tree, tNode,
												pThis->gPrivate_position__current->gIndex) :
												crx_c_tree_private_getIndexFrom(
												pThis->gPrivate_tree, tNode,
												pThis->gPrivate_position__current->gIndex)));
									}

									if(tOrderOfIndices != 0)
									{
										crx_c_tree_iterator_next(pThis);

										break;
									}
								}
								else
								{
									pThis->gPrivate_position__current =
											tLastSeenLower_position;

									if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
										{pThis->gPrivate_node = tLastSeenLower_node;}

									break;
								}
							}

							break;
						}
						case CRX__C__TREE__EDGE__RIGHT:
						{
							/*NEED TO FARWARD TO FIND LAST*/

							while(true)
							{
								if(crx_c_tree_iterator_next(pThis))
								{
									Crx_C_Tree_Private_Node * tNode = 
											(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ?
											pThis->gPrivate_position__current->gNode :
											pThis->gPrivate_node);
									int32_t tOrderOfIndices = -1;

									tLastSeenLower_position =
											pThis->gPrivate_position__current;

									if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
										{tLastSeenLower_node = pThis->gPrivate_node;}

									if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
									{
										if(tNode->gPrivate_type)
										{
											memcpy(tIndex__guide,
													crx_c_tree_private_getIndexFrom(
															pThis->gPrivate_tree, tNode,
															pThis->
															gPrivate_position__current->
															gIndex),
													pThis->gPrivate_tree->
															gPrivate_typeBluePrint__index->
															gBYTE_SIZE);
										}
										else
										{
											(*(pThis->gPrivate_tree->gPrivate_constructIndexFrom))(
													tIndex__guide,
													crx_c_tree_private_getElement(
															pThis->gPrivate_tree, tNode,
															pThis->
															gPrivate_position__current->
															gIndex));
										}

										tOrderOfIndices = (*(pThis->gPrivate_tree->
												gPrivate_getOrderOfIndices))(pIndex__guide, 
												tIndex__guide);
									}
									else
									{
										tOrderOfIndices = (*(pThis->gPrivate_tree->
												gPrivate_getOrderOfIndices))(pIndex__guide,
												(tNode->gPrivate_type ?
														crx_c_tree_private_getIndexFrom(
																pThis->gPrivate_tree, tNode,
																pThis->
																gPrivate_position__current->
																gIndex) :
														crx_c_tree_private_getIndexFrom(
																pThis->gPrivate_tree, tNode,
																pThis->
																gPrivate_position__current->
																gIndex)));
									}

									if(tOrderOfIndices != 0)
									{
										crx_c_tree_iterator_prev(pThis);

										break;
									}
								}
								else
								{
									pThis->gPrivate_position__current =
											tLastSeenLower_position;

									if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
										{pThis->gPrivate_node = tLastSeenLower_node;}

									break;
								}
							}

							break;
						}
						case CRX__C__TREE__EDGE__UNSPECIFIC:
							{break;}
						default:
						{
							assert(false);
							break;
						}
					}
				}
				else
				{
					switch(pEdge)
					{
						case CRX__C__TREE__EDGE__LEFT:
						{
							/*NEED TO REWIND TO FIND FIRST*/

							while(true)
							{
								if(crx_c_tree_iterator_prev(pThis))
								{
									Crx_C_Tree_Private_Node * tNode =
											(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ?
											pThis->gPrivate_position__current->gNode :
											pThis->gPrivate_node);
									unsigned char * tElement = NULL;

									tLastSeenLower_position =
											pThis->gPrivate_position__current;

									if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
										{tLastSeenLower_node = pThis->gPrivate_node;}

									if(tNode->gPrivate_type)
									{
										tElement = crx_c_tree_private_getElement(
												pThis->gPrivate_tree, tNode, 
												pThis->gPrivate_position__current->gIndex);
									}
									else
									{
										tElement = crx_c_tree_private_getElement(
												pThis->gPrivate_tree, tNode,
												pThis->gPrivate_position__current->gIndex);
									}

									if((*(pThis->gPrivate_tree->gPrivate_getOrderOfElements))(
											pElement, tElement) != 0)
									{
										crx_c_tree_iterator_next(pThis);

										break;
									}
								}
								else
								{
									pThis->gPrivate_position__current =
											tLastSeenLower_position;

									if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
										{pThis->gPrivate_node = tLastSeenLower_node;}

									break;
								}
							}

							break;
						}
						case CRX__C__TREE__EDGE__RIGHT:
						{
							/*NEED TO FARWARD TO FIND LAST*/

							while(true)
							{
								if(crx_c_tree_iterator_next(pThis))
								{
									Crx_C_Tree_Private_Node * tNode =
											(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ?
											pThis->gPrivate_position__current->gNode :
											pThis->gPrivate_node);
									unsigned char * tElement;

									tLastSeenLower_position =
											pThis->gPrivate_position__current;
									
									if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
										{tLastSeenLower_node = pThis->gPrivate_node;}

									if(tNode->gPrivate_type)
									{
										tElement = crx_c_tree_private_getElement(
												pThis->gPrivate_tree, tNode,
												pThis->gPrivate_position__current->gIndex);
									}
									else
									{
										tElement = crx_c_tree_private_getElement(
												pThis->gPrivate_tree, tNode,
												pThis->gPrivate_position__current->gIndex);
									}

									if((*(pThis->gPrivate_tree->gPrivate_getOrderOfElements))(
											pElement, tElement) != 0)
									{
										crx_c_tree_iterator_prev(pThis);

										break;
									}
								}
								else
								{
									pThis->gPrivate_position__current =
											tLastSeenLower_position;

									if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
										{pThis->gPrivate_node = tLastSeenLower_node;}

									break;
								}
							}

							break;
						}
						case CRX__C__TREE__EDGE__UNSPECIFIC:
							{break;}
						default:
						{
							assert(false);
							break;
						}
					}
				}

				vReturn = true;

				break;
			}
			else
			{
				if(tImaginaryIndex > 0 /*>=*/)
				{
					tLastSeenLower_position = pThis->gPrivate_position__current;
					
					if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
						{tLastSeenLower_node = pThis->gPrivate_node;}
				}

				if((CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ? 
						pThis->gPrivate_position__current->gNode :
						pThis->gPrivate_node)->gPrivate_type)
				{
					pThis->gPrivate_position__current->gIndex = tImaginaryIndex /*+ 1*/;

					if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
					{
						(pThis->gPrivate_position__current + 1)->gNode =
								*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree,
								pThis->gPrivate_position__current->gNode,
								tImaginaryIndex /*+ 1*/));
					}
					else
					{
						pThis->gPrivate_node =
								*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree,
								pThis->gPrivate_node, tImaginaryIndex /*+ 1*/));
					}

					(pThis->gPrivate_position__current)++;
				}
				else
				{
					if(tImaginaryIndex == 0 /*<*/)
					{
						pThis->gPrivate_position__current = tLastSeenLower_position;
						
						if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
							{pThis->gPrivate_node = tLastSeenLower_node;}

						if(pThis->gPrivate_position__current != pThis->gPrivate_positions)
							{(pThis->gPrivate_position__current->gIndex)--;}
					}
					else
						{pThis->gPrivate_position__current->gIndex = tImaginaryIndex - 1;}

					break;
				}
			}
		}
	}
	else
	{
		Crx_C_Tree_Private_Node * tNode = pThis->gPrivate_tree->gPrivate_node__root;
		size_t tIndex = 0;
		unsigned char * tIndex__guide = ((CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX && 
				CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY) ?
				((unsigned char *)CRX__ALLOCA(
				pThis->gPrivate_tree->gPrivate_typeBluePrint__index->gBYTE_SIZE)) : NULL);

		while(tNode != NULL)
		{
			int32_t tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 0;
			size_t tImaginaryIndex = (CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX ?
					crx_c_tree_private_getSuitableImagineryIndexFor(
							pThis->gPrivate_tree, tNode, NULL, pIndex__guide,
							&tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode) :
					crx_c_tree_private_getSuitableImagineryIndexFor(
							pThis->gPrivate_tree, tNode, pElement, NULL,
							&tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode));

			if((tImaginaryIndex > 0 /*>=*/) &&
					(tZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0))
			{
				if(tNode->gPrivate_type)
				{
					tNode = *(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, tNode,
							tImaginaryIndex /*+ 1*/));
				}
				else
				{
					tIndex = tImaginaryIndex - 1;

					if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
					{
						switch(pEdge)
						{
							case CRX__C__TREE__EDGE__LEFT:
							{
								/*NEED TO REWIND TO FIND FIRST*/
								Crx_C_Tree_Private_Node * tNode2 = tNode;
								size_t tIndex2 = tIndex;
								int32_t tOrderOfIndices = -1;

								if(tIndex2 > 0)
									{tIndex2 = tIndex2 - 1;}
								else
								{
									tNode2 = &(((Crx_C_Tree_Private_LeafNode *)
											tNode)->gPrivate_leafNode__prev->gPrivate_node);

									tIndex2 = ((tNode2 != NULL) ?
											(tNode2->gPrivate_numberOfEntries - 1) : 0);
								}

								if(tNode2 != NULL)
								{
									if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
									{
										(*(pThis->gPrivate_tree->gPrivate_constructIndexFrom))(
												tIndex__guide,
												crx_c_tree_private_getElement(pThis->gPrivate_tree,
												tNode2, tIndex2));

										tOrderOfIndices = (*(pThis->gPrivate_tree->
												gPrivate_getOrderOfIndices))(pIndex__guide, 
												tIndex__guide);
									}
									else
									{
										tOrderOfIndices = (*(pThis->gPrivate_tree->
												gPrivate_getOrderOfIndices))(pIndex__guide, 
												crx_c_tree_private_getIndexFrom(
														pThis->gPrivate_tree, tNode2, tIndex2));
									}
								}

								while(tOrderOfIndices == 0)
								{
									tNode = tNode2;
									tIndex = tIndex2;

									if(tIndex2 > 0)
										{tIndex2 = tIndex2 - 1;}
									else
									{
										tNode2 = &(((Crx_C_Tree_Private_LeafNode *)
												tNode)->gPrivate_leafNode__prev->gPrivate_node);
										tIndex2 = ((tNode2 != NULL) ?
												(tNode2->gPrivate_numberOfEntries -
												1) : 0);
									}

									if(tNode2 != NULL /*&& (tIndex2 >= 0)*/)
									{
										if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
										{
											(*(pThis->gPrivate_tree->gPrivate_constructIndexFrom))(
													tIndex__guide,
													crx_c_tree_private_getElement(
													pThis->gPrivate_tree, tNode2, tIndex2));

											tOrderOfIndices = (*(pThis->gPrivate_tree->
													gPrivate_getOrderOfIndices))(pIndex__guide, 
													tIndex__guide);
										}
										else
										{
											tOrderOfIndices = (*(pThis->gPrivate_tree->
													gPrivate_getOrderOfIndices))(pIndex__guide,
													crx_c_tree_private_getIndexFrom(
															pThis->gPrivate_tree, tNode2, tIndex2));
										}
									}
									else
										{break;}
								}

								break;
							}
							case CRX__C__TREE__EDGE__RIGHT:
							{
								/*NEED TO FARWARD TO FIND LAST*/
								Crx_C_Tree_Private_Node * tNode2 = tNode;
								size_t tIndex2 = tIndex;
								int32_t tOrderOfIndices = 0;

								if(tIndex2 < (tNode2->gPrivate_numberOfEntries - 1))
									{tIndex2 = tIndex2 + 1;}
								else
								{
									tNode2 = &(((Crx_C_Tree_Private_LeafNode *)
											tNode)->gPrivate_leafNode__next->gPrivate_node);

									tIndex2 = 0;
								}

								if(tNode2 != NULL)
								{
									if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
									{
										(*(pThis->gPrivate_tree->gPrivate_constructIndexFrom))(
												tIndex__guide,
												crx_c_tree_private_getElement(pThis->gPrivate_tree,
												tNode2, tIndex2));

										tOrderOfIndices = (*(pThis->gPrivate_tree->
												gPrivate_getOrderOfIndices))(pIndex__guide, 
												tIndex__guide);
									}
									else
									{
										tOrderOfIndices = (*(pThis->gPrivate_tree->
												gPrivate_getOrderOfIndices))(pIndex__guide,
												crx_c_tree_private_getIndexFrom(
												pThis->gPrivate_tree, tNode2, tIndex2));
									}
								}

								while(tOrderOfIndices == 0)
								{
									tNode = tNode2;
									tIndex = tIndex2;

									if(tIndex2 < (tNode2->gPrivate_numberOfEntries - 1))
										{tIndex2 = tIndex2 + 1;}
									else
									{
										tNode2 = &(((Crx_C_Tree_Private_LeafNode *)
												tNode)->gPrivate_leafNode__next->gPrivate_node);
										tIndex2 = 0;
									}

									if(tNode2 != NULL) /*&& (tIndex2 < tNode2->gPrivate_numberOfEntries)*/
									{
										if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
										{
											(*(pThis->gPrivate_tree->gPrivate_constructIndexFrom))(
													tIndex__guide,
													crx_c_tree_private_getElement(
													pThis->gPrivate_tree, tNode2, tIndex2));

											tOrderOfIndices = (*(pThis->gPrivate_tree->
													gPrivate_getOrderOfIndices))(
													pIndex__guide, tIndex__guide);
										}
										else
										{
											tOrderOfIndices = (*(pThis->gPrivate_tree->
													gPrivate_getOrderOfIndices))(
													pIndex__guide, crx_c_tree_private_getIndexFrom(
													pThis->gPrivate_tree, tNode2, tIndex2));
										}
									}
									else
										{break;}
								}

								break;
							}
							case CRX__C__TREE__EDGE__UNSPECIFIC:
								{break;}
							default:
							{
								assert(false);
								break;
							}
						}
					}
					else
					{
						switch(pEdge)
						{
							case CRX__C__TREE__EDGE__LEFT:
							{
								/*NEED TO REWIND TO FIND FIRST*/
								Crx_C_Tree_Private_Node * tNode2 = tNode;
								size_t tIndex2 = tIndex;

								if(tIndex2 > 0)
									{tIndex2 = tIndex2 - 1;}
								else
								{
									tNode2 = &(((Crx_C_Tree_Private_LeafNode *)
											tNode)->gPrivate_leafNode__prev->gPrivate_node);

									tIndex2 = ((tNode2 != NULL) ?
											(tNode2->gPrivate_numberOfEntries - 1) :
											0);
								}

								while((tNode2 != NULL) &&
										((*(pThis->gPrivate_tree->gPrivate_getOrderOfElements))(
										pElement, crx_c_tree_private_getElement(
										pThis->gPrivate_tree, tNode2, tIndex2)) == 0))
								{
									tNode = tNode2;
									tIndex = tIndex2;

									if(tIndex2 > 0)
										{tIndex2 = tIndex2 - 1;}
									else
									{
										tNode2 = &(((Crx_C_Tree_Private_LeafNode *)
												tNode)->gPrivate_leafNode__prev->gPrivate_node);
										tIndex2 = ((tNode2 != NULL) ?
												(tNode2->gPrivate_numberOfEntries -
												1) : 0);
									}
								}

								break;
							}
							case CRX__C__TREE__EDGE__RIGHT:
							{
								/*NEED TO FARWARD TO FIND LAST*/
								Crx_C_Tree_Private_Node * tNode2 = tNode;
								size_t tIndex2 = tIndex;

								if(tIndex2 < (tNode2->gPrivate_numberOfEntries - 1))
									{tIndex2 = tIndex2 + 1;}
								else
								{
									tNode2 = &(((Crx_C_Tree_Private_LeafNode *)
											tNode)->gPrivate_leafNode__next->gPrivate_node);

									tIndex2 = 0;
								}

								while((tNode2 != NULL) &&
										((*(pThis->gPrivate_tree->gPrivate_getOrderOfElements))(
										pElement, crx_c_tree_private_getElement(
										pThis->gPrivate_tree, tNode2, tIndex2)) == 0))
								{
									tNode = tNode2;
									tIndex = tIndex2;

									if(tIndex2 < (tNode2->gPrivate_numberOfEntries -
											1))
										{tIndex2 = tIndex2 + 1;}
									else
									{
										tNode2 = &(((Crx_C_Tree_Private_LeafNode *)
												tNode)->gPrivate_leafNode__next->gPrivate_node);
										tIndex2 = 0;
									}
								}

								break;
							}
							case CRX__C__TREE__EDGE__UNSPECIFIC:
								{break;}
							default:
							{
								assert(false);
								break;
							}
						}
					}

					break;
					vReturn = true;
				}
			}
			else
			{
				if(tNode->gPrivate_type)
				{
					tNode = *(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, tNode,
							tImaginaryIndex /*+ 1*/));
				}
				else
				{
					if(tImaginaryIndex > 0 /*>=*/)
						{tIndex = tImaginaryIndex - 1;}
					else
					{
						tNode = &(((Crx_C_Tree_Private_LeafNode *)tNode)->
								gPrivate_leafNode__prev->gPrivate_node);
						tIndex = ((tNode != NULL) ? (tNode->gPrivate_numberOfEntries -
								1) : 0);
					}

					break;
				}
			}
		}

		pThis->gPrivate_node = tNode;
		pThis->gPrivate_elementIndex = tIndex;
	}

	return vReturn;
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_tree_iterator_remove(Crx_C_Tree_Iterator * pThis)
{
	CRX_SCOPE_META
	if((pThis->gPrivate_tree == NULL) || 
			(pThis->gPrivate_isConstant) ||
			(pThis->gPrivate_tree->gPrivate_node__root == NULL) ||
			(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY ? 
					(pThis->gPrivate_node == NULL) :
					(pThis->gPrivate_position__current == pThis->gPrivate_positions)))
		{return false;}

	CRX_SCOPE
	if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		Crx_C_Tree_Iterator_Private_Position * tPosition =
				pThis->gPrivate_position__current;
		Crx_C_Tree_Private_Node * tNode = (CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ?
				NULL : pThis->gPrivate_node);
		bool tIsToAdvance = false;

		if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
		{
			while((tPosition != pThis->gPrivate_positions) &&
					(tPosition->gNode->gPrivate_numberOfEntries <
							pThis->gPrivate_tree->gPrviate_countOfMidElementInNode))
				{tPosition--;}

			tNode = tPosition->gNode;
		}
		else
		{
			while((tPosition != pThis->gPrivate_positions) &&
					(tNode->gPrivate_numberOfEntries <
							pThis->gPrivate_tree->gPrviate_countOfMidElementInNode))
			{
				tPosition--;

				tNode = tNode->gPrivate_node__parent;
			}
		}

		if(tNode == NULL)
		{
			tNode = pThis->gPrivate_tree->gPrivate_node__root;
			tPosition = pThis->gPrivate_positions + 1;
		}

		if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
		{
			crx_c_tree_iterator_private_remove__do(pThis, 0, tNode,
					tPosition, NULL, ((size_t)(-1)), NULL, NULL, &tIsToAdvance, NULL, NULL);
		}
		else
		{
			crx_c_tree_iterator_private_remove__do(pThis, 0, tNode,
					tPosition, NULL, ((size_t)(-1)), NULL, NULL, &tIsToAdvance, NULL, NULL);
		}

		if(tIsToAdvance)
			{crx_c_tree_iterator_next(pThis);}
		else
		{
			if(pThis->gPrivate_position__current == pThis->gPrivate_positions)
				{pThis->gPrivate_positions->gIndex = 1;}
		}
	}
	else
	{
		/*
			WARNING: THESE HAVE DIFFERENT SEMANTICS DEPENDING ON WHETHER THE ALGORITHM IS
					PRE EMTPIVE. A FORMAL VIOLATION. IF PRE EMPTIVE, THE FOLLOWING ARRAYS
					CARRY A FULL TRACE, OTHERWISE THEY CARRY A TRACE STARTING THE FIRST
					IMPORTANT NODE FOR THE ALGORITHM TO ADDRESS. IN BOTH CASES, THE
					ARRAYS BEGIN WITH A NODE NULL, AND INDEX 0 TO MATCH
					this->gPrivate_positions BEHAVIOR.
		*/
		Crx_C_Tree_Private_Node * tNodes[64];
		size_t tIndices[64];
		unsigned char * tIndex__guide = (CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX ?
				((unsigned char *)CRX__ALLOCA(
				pThis->gPrivate_tree->gPrivate_typeBluePrint__index->gBYTE_SIZE)) : NULL);

		if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
		{
			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
			{
				(*(pThis->gPrivate_tree->gPrivate_constructIndexFrom))(tIndex__guide,
						crx_c_tree_private_getElement(pThis->gPrivate_tree, pThis->gPrivate_node,
								pThis->gPrivate_elementIndex));
			}
			else
			{
				memcpy(tIndex__guide, ((unsigned char *)crx_c_tree_private_getIndexFrom(
						pThis->gPrivate_tree, pThis->gPrivate_node,
						pThis->gPrivate_elementIndex)), 
						pThis->gPrivate_tree->gPrivate_typeBluePrint__index->gBYTE_SIZE);
			}
		}

		if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
		{
			size_t tLength = 1;
			size_t tIndex = tLength;

			/*THE SECOND PART OF THE CHECK BELOW, WHICH IS TO DETERMINE WHETHER THE ENTRY
					HAS A COPY, OR A RELATED ENTRY, ELSEWHERE, IS BASED ON THE ASSUMPTION 
					DISCUSSED BELOW.*/
			if((pThis->gPrivate_node->gPrivate_numberOfEntries <
					pThis->gPrivate_tree->gPrviate_countOfMidElementInNode) ||
					(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_TO_USE_DELEGATION ?
					((pThis->gPrivate_elementIndex == 0) &&
					(((Crx_C_Tree_Private_LeafNode *)(pThis->gPrivate_node))->
							gPrivate_leafNode__prev != NULL)) : false))
			{
				tLength = crx_c_tree_private_getTraceOfLeafNode(
						pThis->gPrivate_tree, pThis->gPrivate_node,
						&(tNodes[0]), &(tIndices[0]));
				tIndex = tLength;
			}
			else
			{
				tNodes[0] = NULL;
				tIndices[0] = 0;
			}

			assert(tLength > 0);

			tNodes[tIndex] = pThis->gPrivate_node;
			tIndices[tIndex] = pThis->gPrivate_elementIndex;

			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
			{
				/*
					IF AN ELEMENT HAS A COPY ELSEWHERE, IT WOULD BE, WHEN TRAVERSING UP, IN
					THE NODE WHERE THE INDEX OF THE CHILD NODE THAT IS PART OF THE PATH IS
					NOT ZERO. AT THAT NODE, THE COPY WOULD BE AT THAT NON ZERO INDEX MINUS
					ONE. AND IF WE ARE THE LEFT MOST NODE, THE FIRST ELEMENT THERE COULD NOT
					POSSIBLY HAVE A COPY ELSEWHERE.
					IF THE ABOVE IS INCORRECT, THE FOLLOWING IS INCORRECT.
				*/
				if((pThis->gPrivate_elementIndex == 0) &&
						(((Crx_C_Tree_Private_LeafNode *)(pThis->gPrivate_node))->
								gPrivate_leafNode__prev != NULL))
				{
					while((tIndex > 0) && (tIndices[tIndex - 1] == 0))
						{tIndex--;}

					assert(tIndex != 1);

					if(tIndex > 0)
						{tIndex--;}
				}
			}

			while((tIndex > 0) && (tNodes[tIndex]->gPrivate_numberOfEntries <
					pThis->gPrivate_tree->gPrviate_countOfMidElementInNode))
				{tIndex--;}

			if(tIndex == 0)
				{tIndex = 1;}

			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
			{
				crx_c_tree_iterator_private_remove__do(
						pThis, 0, tNodes[tIndex], NULL, &(tIndices[0]), tIndex,
						tIndex__guide,
						crx_c_tree_private_getElement(pThis->gPrivate_tree,
								pThis->gPrivate_node, pThis->gPrivate_elementIndex),
						NULL, NULL, NULL);
			}
			else
			{
				crx_c_tree_iterator_private_remove__do(
						pThis, 0, tNodes[tIndex], NULL, &(tIndices[0]), tIndex,
						NULL,
						crx_c_tree_private_getElement(pThis->gPrivate_tree,
								pThis->gPrivate_node, pThis->gPrivate_elementIndex),
						NULL, NULL, NULL);
			}
		}
		else
		{
			Crx_C_Tree_Private_Node * tNodes2[64] /*= ?*/;
			size_t tIndices2[64] /*= ?*/;
			size_t tIndex = 0;

			tNodes2[0] = pThis->gPrivate_node;
			tIndices2[0] = pThis->gPrivate_elementIndex;

			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
			{
				/*
					IF AN ELEMENT HAS A COPY ELSEWHERE, IT WOULD BE, WHEN TRAVERSING UP, IN
					THE NODE WHERE THE INDEX OF THE CHILD NODE THAT IS PART OF THE PATH IS
					NOT ZERO. AT THAT NODE, THE COPY WOULD BE AT THAT NON ZERO INDEX MINUS
					ONE. AND IF WE ARE THE LEFT MOST NODE, THE FIRST ELEMENT THERE COULD NOT
					POSSIBLY HAVE A COPY ELSEWHERE.
					IF THE ABOVE IS INCORRECT, THE FOLLOWING IS INCORRECT.
				*/
				if((pThis->gPrivate_elementIndex == 0) &&
						(((Crx_C_Tree_Private_LeafNode *)(pThis->gPrivate_node))->
								gPrivate_leafNode__prev != NULL))
				{
					while(tNodes2[tIndex]->gPrivate_node__parent != NULL)
					{
						size_t tChildNodeIndex =
								crx_c_tree_private_findChildNodeIndexInParent(
								pThis->gPrivate_tree, tNodes2[tIndex]);

						assert(tChildNodeIndex != ((size_t)(-1)));

						tNodes2[tIndex + 1] = tNodes2[tIndex]->gPrivate_node__parent;
						tIndices2[tIndex + 1] = tChildNodeIndex;
						tIndex++;

						if(tChildNodeIndex != 0)
							{break;}
					}

					/*TO MATCH THE ASSERT ABOVE, NO MORE*/
					assert(tNodes2[tIndex] != NULL);
				}
			}

			if(tNodes2[tIndex]->gPrivate_node__parent != NULL)
			{
				while(tNodes2[tIndex]->gPrivate_numberOfEntries <
						pThis->gPrivate_tree->gPrviate_countOfMidElementInNode)
				{
					size_t tChildNodeIndex = crx_c_tree_private_findChildNodeIndexInParent(
							pThis->gPrivate_tree, tNodes2[tIndex]);

					assert(tChildNodeIndex != ((size_t)(-1)));

					tNodes2[tIndex + 1] = tNodes2[tIndex]->gPrivate_node__parent;
					tIndices2[tIndex + 1] = tChildNodeIndex;
					tIndex++;

					if(tNodes2[tIndex]->gPrivate_node__parent == NULL)
						{break;}
				}
			}

			/*TO BE CONSISTANT. HOWEVER, tNodes[1] STILL DOES NOT NECESSARILY POINT TO ROOT*/
			tNodes[0] = NULL;
			tIndices[0] = 0;

			CRX_FOR(size_t tI = 0, tI <= tIndex, tI++)
			{
				tNodes[tI + 1] = tNodes2[tIndex - tI];
				tIndices[tI + 1] = tIndices2[tIndex - tI];
			}
			CRX_ENDFOR

			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
			{
				crx_c_tree_iterator_private_remove__do(pThis, 0,
						tNodes[1], NULL, &(tIndices[0]), 1, tIndex__guide,
						crx_c_tree_private_getElement(pThis->gPrivate_tree,
								pThis->gPrivate_node, pThis->gPrivate_elementIndex), 
						NULL, NULL, NULL);
			}
			else
			{
				crx_c_tree_iterator_private_remove__do(pThis, 0,
						tNodes[1], NULL, &(tIndices[0]), 1, NULL,
						crx_c_tree_private_getElement(pThis->gPrivate_tree,
								pThis->gPrivate_node, pThis->gPrivate_elementIndex), 
						NULL, NULL, NULL);
			}
		}

		if(pThis->gPrivate_elementIndex ==
				pThis->gPrivate_node->gPrivate_numberOfEntries)
		{
			pThis->gPrivate_node = &(((Crx_C_Tree_Private_LeafNode *)
					(pThis->gPrivate_node))->gPrivate_leafNode__next->gPrivate_node);
			pThis->gPrivate_elementIndex = ((pThis->gPrivate_node != NULL) ? 0 : 1);
		}
	}

	crx_c_tree_private_decrementNumberOfElements(pThis->gPrivate_tree);

	if((pThis->gPrivate_tree->gPrivate_node__root->gPrivate_numberOfEntries == 0) &&
			(pThis->gPrivate_tree->gPrivate_node__root->gPrivate_type))
	{
		crx_c_tree_private_unsafePopRootNode(pThis->gPrivate_tree);
		crx_c_tree_private_decrementNumberOfNodes(pThis->gPrivate_tree);
	}

	return true;

	CRX_SCOPE_END
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_iterator_private_remove__do(
		Crx_C_Tree_Iterator * pThis, uint32_t pMode,
		Crx_C_Tree_Private_Node * pNode,
		Crx_C_Tree_Iterator_Private_Position * pPosition__current,
		size_t * pIndices, size_t pIndexInIndices,
		void * pIndex__guide, void * pElement,
		bool * CRX_NOT_NULL pIsToAdvance,
		void * pIndex__out, void * pElement__out)
{
	/*if(pNode == NULL)
		{return *pKey;}
	else*/

	size_t vImaginaryIndex;
	int32_t vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 0;

	/*if(pMode)
	{ /* pMode can only be 0, 1 or 2 * /
		vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode =
				((pNode->gPrivate_type == 0) ? 0 : ((pMode == 1) ? 1 : -1));
		vImaginaryIndex = ((pMode == 1) ? (pNode->gPrivate_numberOfEntries /*- 1* /) : 0/*-1* /);
	}*/
	if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		if(pMode == 1)
		{
			if(pNode->gPrivate_type)
				{vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 1;}

			vImaginaryIndex = pNode->gPrivate_numberOfEntries /*- 1*/;
		}
		else if(pMode == 2)
		{
			if(pNode->gPrivate_type)
			{
				vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = -1;
				vImaginaryIndex = 0 /*-1*/;
			}
			else
				{vImaginaryIndex = 1 /*0*/;}
		}
		else /*pMode == 0*/
		{
			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
				{assert(pNode == pPosition__current->gNode);}

			if(CRX__ARE_POINTERS_TO_SAME_OBJECT(pPosition__current,
					pThis->gPrivate_position__current, false))
			{
				vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 0;
				vImaginaryIndex = pPosition__current->gIndex + 1;
			}
			else
			{
				assert(pNode->gPrivate_type != 0);

				/*NOTE THAT THE FOLLOWING EVALUATION OF
						vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode IS NOT
						NECESSARILY CORRECT WHEN
						(pPosition__current->gIndex !=
								pNode->gPrivate_numberOfEntries),
						BUT IT SHOULD NOT BE A PROBLEM.
				*/
				vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode =
						((pPosition__current->gIndex ==
						pNode->gPrivate_numberOfEntries) ? 1 : -1);
				vImaginaryIndex = pPosition__current->gIndex /*- 1*/;
			}
		}
	}
	else
	{
		/* if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
		{
			vImaginaryIndex =
					crx_c_tree_private_getSuitableImagineryIndexFor(
					pThis->gPrivate_tree, pNode,
					NULL, pIndex__guide,
					&vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode);
		}
		else
		{
			vImaginaryIndex =
					crx_c_tree_private_getSuitableImagineryIndexFor(
					pThis->gPrivate_tree, pNode,
					(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT ? ((unsigned char *)(*pElement)) : pElement), 
					NULL, &vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode);
		} */

		/*UNLIKE THE ABOVE CODE, THE FOLLOWING ASSUMES THAT THE ELEMENT FROM THE LEAVES
				THAT WAS COPIED TO THE INTERNAL NODES REMAINS AT THE RIGHT MOST EDGE OF
				THE LEAF THAT IT IS IN NO MATTER HOW MUCH SPLITTING HAPPENS OR THE COPY
				MOVES THE TREE RELATIVE TO THE LEAVES.*/
		if(pMode == 1)
		{
			/*SHOULD NOT HAPPEN*/
			assert(false);
			if(pNode->gPrivate_type)
				{vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 1;}

			vImaginaryIndex = pNode->gPrivate_numberOfEntries /*- 1*/;
		}
		else if(pMode == 2)
		{
			if(pNode->gPrivate_type)
			{
				vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = -1;
				vImaginaryIndex = 0 /*-1*/;
			}
			else
				{vImaginaryIndex = 1 /*0*/;}
		}
		else
		{
			if(CRX__ARE_POINTERS_TO_SAME_OBJECT(pNode,
					pThis->gPrivate_node, false))
			{
				vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 0;
				vImaginaryIndex = pIndices[pIndexInIndices] + 1;
			}
			else
			{
				CRX_SCOPE_META
				assert(pNode->gPrivate_type != 0);

				CRX_SCOPE
				int32_t tResult = 1; /*ARBITRARY. WE ONLY CARE IF RESULT IS 0.*/

				if(pIndices[pIndexInIndices] > 0)
				{
					if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
					{
						tResult = (*(pThis->gPrivate_tree->gPrivate_getOrderOfIndices))(
								pIndex__guide,
								crx_c_tree_private_getIndexFrom(pThis->gPrivate_tree, pNode,
										pIndices[pIndexInIndices] - 1));
					}
					else
					{
						tResult = (*(pThis->gPrivate_tree->gPrivate_getOrderOfElements))(pElement,
								crx_c_tree_private_getElement(pThis->gPrivate_tree,
										pNode, pIndices[pIndexInIndices] - 1));
					}
				}

				if(tResult == 0)
					{vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode = 0;}
				else
				{
					/*NOTE THAT THE FOLLOWING EVALUATION OF 
							vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode IS NOT
							NECESSARILY CORRECT WHEN
							(pIndices[pIndexInIndices] !=
									pNode->gPrivate_numberOfEntries),
							BUT IT SHOULD NOT BE A PROBLEM.
					*/
					vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode =
							((pIndices[pIndexInIndices] ==
							pNode->gPrivate_numberOfEntries) ?
							1 : -1);
				}

				vImaginaryIndex = pIndices[pIndexInIndices] /*- 1*/;
				CRX_SCOPE_END
			}
		}
	}

	if(pNode->gPrivate_type)
	{
		bool tIsDone = false;
		size_t tIndexOfNextNode = 0;

		if((vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0) &&
				(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY || (pMode == 0)))
		{
			/*EVEN WHEN ELEMENT DATA IS NOT IN LEAVES ONLY, pMode MUST ALSO BE 0 IF WE ARE
					HERE. THIS IS BECAUSE WE ARE STICKING TO THE FIRST FOUND ENTRY IN THE
					INTERNAL NODES IN THAT CASE.
					NOTE THAT THIS WAS NECESSARY WHEN THE ALGORITHM CONTINUED TO DO A
					BINARY SEARCH IN THE CASE WHEN MODE WAS NOT ZERO AND ELEMENT DATA WAS
					IN LEAVES. LATER I CHANED THAT, BUT KEEPING THE CODE ABOVE IN THE IF
					CONDITION, AND THE ASSERTION BELOW, FOR THE TIME BEING.
			*/
			CRX_SCOPE_META
			assert(pMode == 0);

			CRX_SCOPE
			size_t tNumberOfKeysInLeftNode = 0;
			size_t tNumberOfKeysInRightNode = (*(crx_c_tree_private_getChildNode(
					pThis->gPrivate_tree, pNode,
					vImaginaryIndex /*+ 1*/)))->gPrivate_numberOfEntries;
			int32_t tBranchToTake = -2; /*-2: non,  -1: left,  0: merge and try again, 
										1: right*/

			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY && 
					CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
			{
				if(tNumberOfKeysInRightNode <
						pThis->gPrivate_tree->gPrviate_countOfMidElementInNode)
				{
					tNumberOfKeysInLeftNode = (*(crx_c_tree_private_getChildNode(
							pThis->gPrivate_tree, pNode,
							vImaginaryIndex - 1)))->gPrivate_numberOfEntries;

					if(tNumberOfKeysInLeftNode >=
							pThis->gPrivate_tree->gPrviate_countOfMidElementInNode)
					{
						crx_c_tree_private_rotateRight(
								pThis->gPrivate_tree,
								*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
										vImaginaryIndex - 1)),
								vImaginaryIndex - 1, pNode,
								*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
										vImaginaryIndex /*+ 1*/)));

						pIndices[pIndexInIndices + 1] = pIndices[pIndexInIndices + 1] + 1;

						if((*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree,
								pNode, vImaginaryIndex /*+ 1*/)))->gPrivate_type == 0)
						{
							assert(CRX__ARE_POINTERS_TO_SAME_OBJECT(
									*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree,
									pNode, vImaginaryIndex /*+ 1*/)), pThis->gPrivate_node,
									false));

							(pThis->gPrivate_elementIndex)++;
						}

						if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
						{
							crx_c_tree_iterator_private_remove__do(
									pThis, 0, pNode, NULL, pIndices, pIndexInIndices,
									pIndex__guide, pElement, NULL, NULL, NULL);
						}
						else
						{
							crx_c_tree_iterator_private_remove__do(
									pThis, 0, pNode, NULL, pIndices, pIndexInIndices,
									NULL, pElement, NULL, NULL, NULL);
						}

						tIsDone = true;
					}
				}
			}

			/*THE FOLLOWING CHECK FOR tIsDone IS ONLY REQUIRED WHEN DATA IS IN THE 
					LEAVES ONLY, BUT TO KEEP THINGS SIMPLE THE CHECK IS ALWAYS DONE.
			*/
			if(!tIsDone)
			{
				if(tNumberOfKeysInRightNode >=
						pThis->gPrivate_tree->gPrviate_countOfMidElementInNode)
					{tBranchToTake = 1;}
				else
				{
					if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
					{
						if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
						{
							tNumberOfKeysInLeftNode = (*(crx_c_tree_private_getChildNode(
									pThis->gPrivate_tree, pNode, 
									vImaginaryIndex - 1)))->gPrivate_numberOfEntries;

							if(tNumberOfKeysInLeftNode >=
									pThis->gPrivate_tree->gPrviate_countOfMidElementInNode)
								{tBranchToTake = -1;}
							else
								{tBranchToTake = 0;}
						}
						else
						{
							assert((tNumberOfKeysInLeftNode > 0) &&
									(tNumberOfKeysInLeftNode <
											pThis->gPrivate_tree->
											gPrviate_countOfMidElementInNode));

							tBranchToTake = 0;
						}
					}
					else
					{
						if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
						{
							tBranchToTake = -1;
						}
						else
						{
							tBranchToTake = 1;
						}
					}
				}

				if(tBranchToTake != 0)
				{
					if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
					{
						if(pThis->gPrivate_tree->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != 
								NULL)
						{
							(*(pThis->gPrivate_tree->gPrivate_typeBluePrint__element->
									gFUNC__DESTRUCT))(crx_c_tree_private_getElement(
									pThis->gPrivate_tree, pNode, vImaginaryIndex - 1));
						}

						if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT)
						{
							free(crx_c_tree_private_getElement(pThis->gPrivate_tree,
									pNode, vImaginaryIndex - 1));
						}
					}
					else
					{
						/*NOTICE: EFFECTIVELY WE ARE TREATING TWO EQUAL INDICES AS IF THEY
								ARE BYTE WISE EQUAL. THIS IS CONTRARY TO ALMOST EVERY
								WHERE, IF NOT EVERY WHERE, ELSE IN THE CODE. IF OTHER
								WORDS, WHEN THE TREE HAS AN INDEX WE DO NOT ATTEMPT TO
								CHECK IF IT IS EXACTLY THE INDEX THAT IS CREATED FROM THE
								ELEMENT THAT WE SHALL EVENTUALLY REMOVE FROM A LEAF.
								INSTEAD, WE REASON THAT WHATEVER THAT INDEX IS IT MUST BE
								EQUAL UNDER THE INDEX ORDERING TO THE ONE FOUND HERE, BUT
								THIS EFFECTIVELY ASSUMES BYTE WISE EQUALITY ALSO.*/

						if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
						{
							if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT)
							{
								if((pThis->gPrivate_tree->gPrivate_typeBluePrint__element->
										gFUNC__DESTRUCT != NULL) && 
										CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
								{
									(*(pThis->gPrivate_tree->gPrivate_typeBluePrint__element->
											gFUNC__DESTRUCT))(crx_c_tree_private_getElement(
											pThis->gPrivate_tree, pNode, vImaginaryIndex - 1));
								}
							}
							else
							{
								if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
								{
									*((unsigned char * *)crx_c_tree_private_getElementEntry(
											pThis->gPrivate_tree, pNode, 
											vImaginaryIndex - 1)) = NULL;
								}
							}
						}
					}
				}

				if(tBranchToTake == 1)
				{
					if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
					{
						/*vKey = __KB_KEY(pGUIDE_TYPE, pNode)[vImaginaryIndex - 1];*/
						if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
						{
							crx_c_tree_iterator_private_remove__do(
									pThis, 2,
									*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
											vImaginaryIndex /*+ 1*/)),
									NULL, NULL, ((size_t)(-1)),
									crx_c_tree_private_getIndexFrom(pThis->gPrivate_tree, pNode,
											vImaginaryIndex - 1),
									crx_c_tree_private_getElementEntry(pThis->gPrivate_tree,
											pNode, vImaginaryIndex - 1),
									pIsToAdvance, NULL, NULL);
						}
						else
						{
							crx_c_tree_iterator_private_remove__do(
									pThis, 2,
									*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
											vImaginaryIndex /*+ 1*/)),
									NULL, NULL, ((size_t)(-1)),
									NULL,
									crx_c_tree_private_getElementEntry(pThis->gPrivate_tree,
											pNode, vImaginaryIndex - 1),
									pIsToAdvance, NULL, NULL);
						}

						/*return vKey;*/
					}
					else
					{
						/*IT IS NOT IMPORTANT THAT THE VERY SAME ELEMENT THAT WE THE 
								INDEX FROM TO STORE IN THE INTERNAL NODE BE THE ONE
								FOUND. HENCE, WHEN CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX, NO SEARCHING FOR THE 
								EXACT ENTRY IS DONE.*/

						if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
						{
							crx_c_tree_iterator_private_remove__do(
									pThis, 2,
									*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
											vImaginaryIndex /*+ 1*/)),
									NULL, pIndices, pIndexInIndices + 1,
									pIndex__guide, pElement, NULL,
									(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_TO_USE_DELEGATION ?
											crx_c_tree_private_getIndexFrom(pThis->gPrivate_tree,
											pNode, vImaginaryIndex - 1) : NULL),
									NULL);
						}
						else
						{
							crx_c_tree_iterator_private_remove__do(
									pThis, 2,
									*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
											vImaginaryIndex /*+ 1*/)),
									NULL, pIndices, pIndexInIndices + 1,
									NULL, pElement, NULL,
									NULL,
									(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_TO_USE_DELEGATION ?
											crx_c_tree_private_getElementEntry(pThis->gPrivate_tree,
											pNode, vImaginaryIndex - 1) : NULL));
						}
					}
					/*vKey = __KB_KEY(pGUIDE_TYPE, pNode)[vImaginaryIndex - 1];*/

					/*return vKey;*/
					if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
					{
						tIsDone = true;
					}
					else
					{
						tIndexOfNextNode = vImaginaryIndex /*+ 1*/;
					}
				}
				else if(tBranchToTake == -1)
				{
					if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
					{
						if(tNumberOfKeysInLeftNode == 0)
						{
							tNumberOfKeysInLeftNode = (*(crx_c_tree_private_getChildNode(
									pThis->gPrivate_tree, pNode,
									vImaginaryIndex - 1)))->gPrivate_numberOfEntries;
						}

						if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
						{
							crx_c_tree_iterator_private_remove__do(
									pThis, 1,
									*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
											vImaginaryIndex - 1)),
									NULL, NULL, ((size_t)(-1)),
									crx_c_tree_private_getIndexFrom(pThis->gPrivate_tree, pNode,
											vImaginaryIndex - 1),
									crx_c_tree_private_getElementEntry(pThis->gPrivate_tree,
											pNode, vImaginaryIndex - 1),
									pIsToAdvance, NULL, NULL);
						}
						else
						{
							crx_c_tree_iterator_private_remove__do(
									pThis, 1,
									*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
											vImaginaryIndex - 1)),
									NULL, NULL, ((size_t)(-1)),
									NULL,
									crx_c_tree_private_getElementEntry(pThis->gPrivate_tree,
											pNode, vImaginaryIndex - 1),
									pIsToAdvance, NULL, NULL);
						}

						if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
						{
							tIsDone = true;
						}
						else
						{
							tIndexOfNextNode = vImaginaryIndex - 1;
						}

						assert(*pIsToAdvance == false);
						*pIsToAdvance = true;
					}
					else
					{
						assert(false);
					}
				}
				else
				{
					if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
					{
						assert(tBranchToTake == 0);

						/*THE FOLLOWING SHOULD ALWAYS BE TRUE IF I AM NOT WRONG, BUT
								STICKING TO REFERENCE FOR NOW*/
						if((tNumberOfKeysInLeftNode ==
										pThis->gPrivate_tree->
										gPrviate_countOfMidElementInNode - 1) &&
								(tNumberOfKeysInRightNode ==
										pThis->gPrivate_tree->
										gPrviate_countOfMidElementInNode - 1))
						{
							Crx_C_Tree_Private_Node * tNode__left =
									crx_c_tree_mergeTwoNodesAndGetRemainingNode(
									pThis->gPrivate_tree, pNode, vImaginaryIndex - 1);

							/*return crx_c_tree_iterator_private_remove__do(
									pMode, pTree, tNode__left, pKey)*/
							if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
							{
								/*THE FOLLOWING WOULD BE TRUE HERE:
										pPosition__current ==
												pThis->gPrivate_position__current
								*/
								(pPosition__current + 1)->gNode = tNode__left;
								(pPosition__current + 1)->gIndex =
										pThis->gPrivate_tree->
												gPrviate_countOfMidElementInNode - 1;

								(pThis->gPrivate_position__current)++;

								if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
								{
									crx_c_tree_iterator_private_remove__do(
											pThis, 0 /*pMode*/, tNode__left,
											pPosition__current + 1, NULL, ((size_t)(-1)),
											pIndex__guide,
											pElement, pIsToAdvance, NULL, NULL);
								}
								else
								{
									crx_c_tree_iterator_private_remove__do(
											pThis, 0 /*pMode*/, tNode__left,
											pPosition__current + 1, NULL, ((size_t)(-1)), 
											NULL, 
											pElement, pIsToAdvance, NULL, NULL);
								}
							}
							else
							{
								pIndices[pIndexInIndices] = pIndices[pIndexInIndices] - 1;

								if(tNode__left->gPrivate_type)
								{
									pIndices[pIndexInIndices + 1] =
											pIndices[pIndexInIndices + 1] +
											pThis->gPrivate_tree->
													gPrviate_countOfMidElementInNode;
								}
								else
								{
									pIndices[pIndexInIndices + 1] =
											pIndices[pIndexInIndices + 1] +
											pThis->gPrivate_tree->
													gPrviate_countOfMidElementInNode - 1;

									pThis->gPrivate_node = tNode__left;
									pThis->gPrivate_elementIndex =
											pThis->gPrivate_elementIndex +
											pThis->gPrivate_tree->
													gPrviate_countOfMidElementInNode - 1;
								}

								if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
								{
									crx_c_tree_iterator_private_remove__do(
											pThis, 0 /*pMode*/, tNode__left, NULL,
											pIndices, pIndexInIndices + 1,
											pIndex__guide, pElement, NULL, pIndex__out, NULL);
								}
								else
								{
									crx_c_tree_iterator_private_remove__do(
											pThis, 0 /*pMode*/, tNode__left, NULL,
											pIndices, pIndexInIndices + 1,
											NULL, pElement, NULL, NULL, pElement__out);
								}
							}

							tIsDone = true;
						}
						else
							{assert(false);}
					}
				}
			}
			CRX_SCOPE_END
		}
		else
		{
			if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
			{
				if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
				{
					if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
					{
						crx_c_tree_iterator_private_remove__do(
								pThis, pMode,
								*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
										vImaginaryIndex /*+ 1*/)),
								((pMode == 0) ? (pPosition__current + 1) : NULL),
								NULL, ((size_t)(-1)),
								pIndex__guide, pElement, pIsToAdvance, NULL, NULL);
					}
					else
					{
						crx_c_tree_iterator_private_remove__do(
								pThis, pMode,
								*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
										vImaginaryIndex /*+ 1*/)),
								((pMode == 0) ? (pPosition__current + 1) : NULL),
								NULL, ((size_t)(-1)), 
								NULL, pElement, pIsToAdvance, NULL, NULL);
					}
				}
				else
				{
					if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
					{
						crx_c_tree_iterator_private_remove__do(
								pThis, pMode,
								*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
										vImaginaryIndex /*+ 1*/)),
								NULL, 
								pIndices, pIndexInIndices + 1,
								pIndex__guide, pElement, NULL, pIndex__out, NULL);
					}
					else
					{
						crx_c_tree_iterator_private_remove__do(
								pThis, pMode,
								*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
										vImaginaryIndex /*+ 1*/)), 
								NULL,
								pIndices, pIndexInIndices + 1, 
								NULL, pElement, NULL, NULL, pElement__out);
					}
				}
			}

			tIndexOfNextNode = vImaginaryIndex /*+ 1*/;
		}

		if(!tIsDone)
		{
			/*TO EASE ANALYSIS, 
				- REMEMBER THAT tNode BELOW IS ALWAYS THE NODE TO THE RIGHT
						OF THE 'FOUND' ENTRY POSITION. THE ONLY EXCEPTION IS WHEN THE
						ALGORITHM IS NOT PRE EMPTIVE, AND THE ELEMENT HAS ALREADY BEEN
						FOUND ABOVE, AND ENTRIES ARE NOT STORED IN THE LEAVES ONLY AND THE
						ALGORITHM ABOVE CHOOSE TO TAKE THE LEFT BRANCH TO HOIST AN ELEMENT
						BACK UP.
				- IF CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE AND (pMode == 0) AND
						(vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0)
						WE SHOULD NOT BE HERE AT ALL.
				- IF PRIMARY ENTRIES ARE NOT IN THE LEAVES ONLY, AND
						(vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode == 0)
						IT IS GUARANTEED THAT WE ARE AT THE END OF THE TRACE THAT IS IN
						THE ITERATOR. IN OTHER WORDS, THE INDEX IN THE TRACE AT THAT
						POINT, MEANING Iterator::Position::gIndex, IS THE INDEX OF THE
						ELEMENT, AND NOT THE INDEX OF THE NEXT CHILD NODE AS IT IS
						OTHERWISE. IF PRIMARY ENTRIES ARE IN THE LEAVES ONLY, THEN
						REGARDLESS OF THE VALUE OF
						vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode THE INDEX IN
						THE TRACE THAT IS IN THE ITERATOR AT THAT POINT, MEANING
						Iterator::Position::gIndex, IS THE INDEX OF THE NEXT NODE.
			*/

			Crx_C_Tree_Private_Node * tNode;

			tNode = *(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
					tIndexOfNextNode));

			/*WE HAVE TO USE '<=' INSTEAD OF '==' BECAUSE WE COULD BE FIXING UNDER FILLED 
					NODES AFTER THE FACT, MEANING THE ALGORITHM IS NOT PRE EMPTIVE.*/
			if(tNode->gPrivate_numberOfEntries <=
					pThis->gPrivate_tree->gPrviate_countOfMidElementInNode - 1)
			{
				assert(tNode->gPrivate_numberOfEntries >=
						pThis->gPrivate_tree->gPrviate_countOfMidElementInNode - 2);

				/*NOTE THAT 'PREVIOUS' AND 'NEXT' AND SIMILAR ARE RELATIVE TO THE
						KEY AT "tIndexOfNextNode - 1" WHICH IS THE KEY "FOUND" BY 
						private_getSuitableImagineryIndexFor() IN THE PREEMPTIVE CASE.
						IN THE NON PREEMPTIVE CASE, tIndexOfNextNode IS EITHER THE
						INDEX OF THE BRANCH ALREADY TAKEN TO CONTINUE THE SEARCH, OR
						THE INDEX OF THE BRANCH TAKEN TO HOIST AN ELEMENT BACK UP TO WHERE 
						THE KEY WAS ALREADY FOUND. WHERE THE KEY WAS FOUND OR "FOUND"
						MIGHT BE TO THE RIGHT OR LEFT OF tIndexOfNextNode.
				*/
				if((tIndexOfNextNode > 0) &&
						((*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
								tIndexOfNextNode - 1)))->
										gPrivate_numberOfEntries >=
								pThis->gPrivate_tree->gPrviate_countOfMidElementInNode))
				{
					/*ROTATE PREVIOUS CHILD NODE'S LAST KEY AND KEY AND NEXT
							CHILD NODE'S FIRST KEY RIGHT */
					crx_c_tree_private_rotateRight(pThis->gPrivate_tree,
							(*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
									tIndexOfNextNode - 1))),
							tIndexOfNextNode - 1, pNode, tNode);

					if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
					{
						/* THE FOLLOWING CHECK IS TO AVOID READING AND WRITING PAST
								THE FURTHEST POSITION IN THE ITERATOR CURRENTLY. */
						if(pMode == 0)
						{
							/* CHECKING WHICH BRANCH, RIGHT OR LEFT, WAS TAKEN WHEN NOT
									CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE AND (pMode == 0) AND
									(vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode
											== 0)
									MEANING WHEN HOISTING HAPPENED AND THE ALGORITHM IS
									NOT PREEMPTIVE. REMEMBER, ONLY WITH HOISTING DO WE
									CONSIDER TAKING THE 'LEFT' SIDE. OTHERWISE WE ARE
									ALWAYS TAKING THE 'RIGHT' SIDE.
							*/
							if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
							{
								((pPosition__current + 1)->gIndex)++;
							}
							else
							{
								if(vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode !=
										0)
									{((pPosition__current + 1)->gIndex)++;}
								else
								{
									if(tIndexOfNextNode == vImaginaryIndex)
									{
										(pPosition__current->gIndex)++;
										(pPosition__current + 1)->gIndex = 0;

										(pThis->gPrivate_position__current)++;
										pThis->gPrivate_node = tNode;
									}
								}
							}
						}
					}
					else
					{
						pIndices[pIndexInIndices + 1] = pIndices[pIndexInIndices + 1] + 1;

						if(tNode->gPrivate_type == 0)
						{
							pThis->gPrivate_elementIndex =
									pThis->gPrivate_elementIndex + 1;
						}
					}
				}
				else if((tIndexOfNextNode < pNode->gPrivate_numberOfEntries) &&
						((*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
								tIndexOfNextNode + 1)))->gPrivate_numberOfEntries >=
								pThis->gPrivate_tree->gPrviate_countOfMidElementInNode))
				{
					/*ROTATE NEXT CHILD NODE'S LAST KEY AND PARENT NODE'S NEXT KEY AND
							NEXT NEXT CHILD NODE'S FIRST KEY LEFT*/
					crx_c_tree_private_rotateLeft(pThis->gPrivate_tree,
							(*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
									tIndexOfNextNode + 1))),
							tIndexOfNextNode + 1, pNode, tNode);

					if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
					{
						/*
						THE FOLLOWING CHECK IS TO AVOID READING AND WRITING PAST
						THE FURTHEST POSITION IN THE ITERATOR CURRENTLY.

						THE FOLLOWING SHOULD NOT HAPPEN. IN OTHER WORDS WE SHOULD NOT
						END UP HAVING WENT THROUGH THE LEFT NODE, BECAUSE IF THE ENTRY
						WAS FOUND, AND BECAUSE THE ALGORITHM IS NOT PREEMPTIVE, THEN IF WE
						ALREADY FINISHED HOISTING AND THROUGH THE LEFT NODE, THEN WE CAN
						BE SURE THAT THE RIGHT NODE CAN NOT HAVE ENOUGH ENTRIES TO PASS
						TO THE LEFT NODE BECAUSE THE ALGORITHM ABOVE THAT DECIDED TO HOIST
						THROUGH THE LEFT NODE CHECKS THE RIGHT NODE FIRST. */
						if(pMode == 0)
						{
							if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
							{
								if(vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode ==
										0)
								{
									if(tIndexOfNextNode == (vImaginaryIndex - 1))
									{
										(pPosition__current + 1)->gIndex = tNode->
												gPrivate_numberOfEntries - 1;

										(pThis->gPrivate_position__current)++;
										pThis->gPrivate_node = tNode;
									}
								}
								else
								{
									/*REMEMBER: IF WE DID NOT END IN THIS ELSE BRANCH THEN
											ZeroIfFoundOrResultOfComparisonWithLargestKeyInNode
											IS 0, AND THEREFORE pMode COULD NOT POSSIBLY
											BE 0 WHEN WE GET TO THE LEAF, AND HENCE
											*pIsToAdvance COULD NOT HAVE BEEN SET.*/
									if((tNode->gPrivate_type == 0) &&
											*pIsToAdvance)
										{*pIsToAdvance = false;}
								}
							}
						}
					}
				}
				else if((tIndexOfNextNode > 0) &&
						((*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
								tIndexOfNextNode - 1)))->gPrivate_numberOfEntries ==
						pThis->gPrivate_tree->gPrviate_countOfMidElementInNode - 1))
				{
					bool tWasNextNodeTheCurrentIteratorNode =
							((!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY &&
											!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE) ?
									CRX__ARE_POINTERS_TO_SAME_OBJECT(tNode, pThis->gPrivate_node,
											false) : false);

					/*MERGE PREVIOUS CHILD NODE, KEY, AND NEXT CHILD NODE*/
					tNode = crx_c_tree_mergeTwoNodesAndGetRemainingNode(
							pThis->gPrivate_tree, pNode, tIndexOfNextNode - 1);

					if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
					{
						if(pMode == 0)
						{
							if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
							{
								assert(pPosition__current->gIndex > 0);

								(pPosition__current->gIndex)--;
								(pPosition__current + 1)->gNode = tNode;
								(pPosition__current + 1)->gIndex =
										(pPosition__current + 1)->gIndex +
										pThis->gPrivate_tree->
										gPrviate_countOfMidElementInNode;
							}
							else
							{
								if(vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode != 0)
								{
									assert(pPosition__current->gIndex > 0);

									(pPosition__current->gIndex)--;
									(pPosition__current + 1)->gIndex =
											(pPosition__current + 1)->gIndex +
											pThis->gPrivate_tree->
											gPrviate_countOfMidElementInNode;

									if(tWasNextNodeTheCurrentIteratorNode)
										{pThis->gPrivate_node = tNode;}
								}
								else
								{
									if(tIndexOfNextNode == vImaginaryIndex)
									{
										(pPosition__current + 1)->gIndex =
												pThis->gPrivate_tree->
												gPrviate_countOfMidElementInNode;
										(pThis->gPrivate_position__current)++;
										pThis->gPrivate_node = tNode;
									}
								}
							}
						}
					}
					else
					{
						(pIndices[pIndexInIndices])--;

						if(tNode->gPrivate_type)
						{
							pIndices[pIndexInIndices + 1] =
									pIndices[pIndexInIndices + 1] +
									pThis->gPrivate_tree->gPrviate_countOfMidElementInNode;
						}
						else
						{
							pIndices[pIndexInIndices + 1] =
									pIndices[pIndexInIndices + 1] + pThis->
									gPrivate_tree->gPrviate_countOfMidElementInNode - 1;

							pThis->gPrivate_node = tNode;
							pThis->gPrivate_elementIndex =
									pThis->gPrivate_elementIndex +
									pThis->gPrivate_tree->
											gPrviate_countOfMidElementInNode - 1;
						}
					}

					tIndexOfNextNode = tIndexOfNextNode - 1;
				}
				else if((tIndexOfNextNode < pNode->gPrivate_numberOfEntries) &&
						((*(crx_c_tree_private_getChildNode(pThis->gPrivate_tree, pNode,
								tIndexOfNextNode + 1)))->gPrivate_numberOfEntries ==
								pThis->gPrivate_tree->gPrviate_countOfMidElementInNode - 1))
				{
					size_t tOldNumberOfEntries = 
							((!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY &&
											!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE) ?
									tNode->gPrivate_numberOfEntries : 0);

					/*MERGE NEXT CHILD NODE, NEXT KEY, AND NEXT NEXT CHILD NODE*/
					tNode = crx_c_tree_mergeTwoNodesAndGetRemainingNode(
							pThis->gPrivate_tree, pNode, tIndexOfNextNode);

					if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
					{
						if(pMode == 0)
						{
							if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
							{
								if(vZeroIfFoundOrResultOfComparisonWithLargestKeyInNode ==
										0)
								{
									if(tIndexOfNextNode == (vImaginaryIndex - 1))
									{
										/*REMEMBER THAT THE FOLLOWING IS NOT NECESSARILY
												TRUE IN THE NON PREMPTIVE CASE.
												(tNode->gPrivate_numberOfEntries ==
														pThis->gPrivate_tree->
														gPrviate_countOfMidElementInNode -
														1)
										*/
										(pPosition__current + 1)->gIndex =
												tOldNumberOfEntries;
										(pThis->gPrivate_position__current)++;
										pThis->gPrivate_node = tNode;

										/*BECAUSE HOISTING HAPPENED FROM THE LEFT SIDE.*/
										*pIsToAdvance = true;
									}
								}
								else
								{
									/*REMEMBER: IF WE DID NOT END IN THIS ELSE BRANCH THEN
											ZeroIfFoundOrResultOfComparisonWithLargestKeyInNode
											IS 0, AND THEREFORE pMode COULD NOT POSSIBLY
											BE 0 WHEN WE GET TO THE LEAF, AND HENCE
											*pIsToAdvance COULD NOT HAVE BEEN SET.*/
									if((tNode->gPrivate_type == 0) &&
											*pIsToAdvance)
										{*pIsToAdvance = false;}
								}
							}
						}
					}
				}
			}

			/*
				NOTE THAT THE CODE ABOVE TAKES CARE OF THE IREGULAR SITUATION OF A NODE
				HAVING NO KEYS, MAKING gPrivate_numberOfEntries == 0, WHILE STILL
				HAVING ONE NODE. IN THE PREEMPTIVE CASE, THIS HAPPENS WHEN THERE IS ONE
				LEAF REMAINIG, AND THAT WOULD MEAN ONE INTERNAL NODE REMAINING, AND THAT
				WOULD BE THE ROOT NODE. THAT INTERNAL NODE WOULD HAVE A SINGLE CHILD NODE,
				THE LEAF, AND NO KEYS. IN THE NON PRE EMPTIVE CASE, THIS HAPPENS BECAUSE
				WE ONLY CHECK THE NODES ON THE WAY BACK UP TO MAKE SURE THAT THEY ARE NOT
				TOO EMPTY, AND 'N', SEE NOTES ABOVE, COULD BE 2, WHICH MEANS N - 1, THE
				MINIMAL ALLOWED LENGTH OF A NODE COULD BE 1, WHICH MEANS THAT IF A MERGER 
				HAPPENS ON THE WAY DOWN THE LENGTH COULD BECOME 0, AND THE CODE ABOVE
				WOULD OBSERVE '0' THAT ON THE WAY UP.
			*/
			/*return crx_c_tree_iterator_private_remove__do(pMode, pTree,
					tNode, pKey); */
			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
			{
				if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
				{
					if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
					{
						crx_c_tree_iterator_private_remove__do(
								pThis, pMode, tNode, pPosition__current + 1, NULL, ((size_t)(-1)),
								pIndex__guide, pElement, pIsToAdvance, NULL, NULL);
					}
					else
					{
						crx_c_tree_iterator_private_remove__do(
								pThis, pMode, tNode, pPosition__current + 1, NULL, ((size_t)(-1)), 
								NULL, pElement, pIsToAdvance, NULL, NULL);
					}
				}
				else
				{
					if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
					{
						crx_c_tree_iterator_private_remove__do(
								pThis, pMode, tNode, NULL, pIndices, pIndexInIndices + 1,
								pIndex__guide, pElement, NULL, pIndex__out, NULL);
					}
					else
					{
						crx_c_tree_iterator_private_remove__do(
								pThis, pMode, tNode, NULL, pIndices, pIndexInIndices + 1,
								NULL, pElement, NULL, NULL, pElement__out);
					}
				}
			}
		}
	}
	else
	{
		/*REMEMBER: IF WE ARE HERE, WE DEFINATELY 'FOUND' WHAT WE ARE SEARCHING FOR.*/
		bool tIsToRotateRight = (CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_TO_USE_RINGS ? 
				((pNode->gPrivate_numberOfEntries >> 1) > (vImaginaryIndex - 1)) :
				false);

		/*vKey = __KB_KEY(pGUIDE_TYPE, pNode)[vImaginaryIndex - 1];*/
		if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
		{
			if(pMode != 0)
			{
				if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
				{
					if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
					{
						crx_c_tree_private_transferConstruct(pThis->gPrivate_tree,
								pThis->gPrivate_tree->gPrivate_typeBluePrint__index->gBYTE_SIZE,
								pThis->gPrivate_tree->gPrivate_typeBluePrint__index->
										gFUNC__MOVE_CONSTRUCT,
								pThis->gPrivate_tree->gPrivate_typeBluePrint__index->
										gFUNC__MOVE_DESTRUCT, 
								pIndex__guide,
								crx_c_tree_private_getIndexFrom(pThis->gPrivate_tree, pNode,
										vImaginaryIndex - 1));
					}
					else
					{
						(*(pThis->gPrivate_tree->gPrivate_constructIndexFrom))(pIndex__guide,
								crx_c_tree_private_getElement(pThis->gPrivate_tree,
								pNode, vImaginaryIndex - 1));
					}
				}

				crx_c_tree_private_transferConstruct(pThis->gPrivate_tree,
						(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) : 
								pThis->gPrivate_tree->gPrivate_typeBluePrint__element->gBYTE_SIZE),
						(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
								pThis->gPrivate_tree->gPrivate_typeBluePrint__element->
								gFUNC__MOVE_CONSTRUCT),
						(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
								pThis->gPrivate_tree->gPrivate_typeBluePrint__element->
								gFUNC__MOVE_DESTRUCT),
						pElement,
						crx_c_tree_private_getElementEntry(pThis->gPrivate_tree,
								pNode, vImaginaryIndex - 1));
			}
			else
			{
				if(pThis->gPrivate_tree->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
				{
					(*(pThis->gPrivate_tree->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(
							crx_c_tree_private_getElement(pThis->gPrivate_tree,
							pNode, vImaginaryIndex - 1));
				}

				if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT)
				{
					free(crx_c_tree_private_getElement(pThis->gPrivate_tree, pNode,
							vImaginaryIndex - 1));
				}
			}

			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX &&
					!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
			{
				crx_c_tree_private_removeSpaceFrom(pThis->gPrivate_tree,
						pThis->gPrivate_tree->gPrivate_typeBluePrint__index->gBYTE_SIZE,
						pThis->gPrivate_tree->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT,
						pThis->gPrivate_tree->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
						pNode,
						crx_c_tree_private_getIndexFrom(pThis->gPrivate_tree, pNode, 0),
						pNode->gPrivate_numberOfEntries,
						vImaginaryIndex - 1, 1, tIsToRotateRight);
			}

			crx_c_tree_private_removeSpaceFrom(pThis->gPrivate_tree,
					(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) :
							pThis->gPrivate_tree->gPrivate_typeBluePrint__element->gBYTE_SIZE),
					(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_tree->gPrivate_typeBluePrint__element->
							gFUNC__MOVE_CONSTRUCT),
					(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_tree->gPrivate_typeBluePrint__element->
							gFUNC__MOVE_DESTRUCT),
					pNode,
					crx_c_tree_private_getElementEntry(pThis->gPrivate_tree, pNode, 0),
					pNode->gPrivate_numberOfEntries,
					vImaginaryIndex - 1, 1, tIsToRotateRight);

			crx_c_tree_private_updateStartIndexAfterRemovalOfSpace(pThis->gPrivate_tree, pNode, 1,
					tIsToRotateRight);

			if(pMode == 0)
			{
				if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
				{
					if(vImaginaryIndex ==
							(pNode->gPrivate_numberOfEntries /*- 1*/))
						{*pIsToAdvance = true;}
				}
				else
				{
					if((pNode->gPrivate_numberOfEntries == 0) ||
							(vImaginaryIndex ==
									(pNode->gPrivate_numberOfEntries /*- 1*/)))
						{*pIsToAdvance = true;}
				}
			}
		}
		else
		{
			if(pThis->gPrivate_tree->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT != NULL)
			{
				(*(pThis->gPrivate_tree->gPrivate_typeBluePrint__element->gFUNC__DESTRUCT))(
						crx_c_tree_private_getElement(pThis->gPrivate_tree,
						pNode, vImaginaryIndex - 1));
			}

			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT)
			{
				free(crx_c_tree_private_getElement(pThis->gPrivate_tree, pNode,
						vImaginaryIndex - 1));
			}

			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX &&
					!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
			{
				crx_c_tree_private_removeSpaceFrom(pThis->gPrivate_tree,
						pThis->gPrivate_tree->gPrivate_typeBluePrint__index->gBYTE_SIZE,
						pThis->gPrivate_tree->gPrivate_typeBluePrint__index->gFUNC__MOVE_CONSTRUCT, 
						pThis->gPrivate_tree->gPrivate_typeBluePrint__index->gFUNC__MOVE_DESTRUCT,
						pNode,
						crx_c_tree_private_getIndexFrom(pThis->gPrivate_tree, pNode, 0),
						pNode->gPrivate_numberOfEntries,
						vImaginaryIndex - 1, 1, tIsToRotateRight);
			}

			crx_c_tree_private_removeSpaceFrom(pThis->gPrivate_tree,
					(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT ? sizeof(volatile void const *) :
							pThis->gPrivate_tree->gPrivate_typeBluePrint__element->gBYTE_SIZE),
					(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_tree->gPrivate_typeBluePrint__element->
							gFUNC__MOVE_CONSTRUCT),
					(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT ? NULL :
							pThis->gPrivate_tree->gPrivate_typeBluePrint__element->
							gFUNC__MOVE_DESTRUCT),
					pNode,
					crx_c_tree_private_getElementEntry(pThis->gPrivate_tree, pNode, 0),
					pNode->gPrivate_numberOfEntries,
					vImaginaryIndex - 1, 1, tIsToRotateRight);

			crx_c_tree_private_updateStartIndexAfterRemovalOfSpace(pThis->gPrivate_tree,
					pNode, 1, tIsToRotateRight);

			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_TO_USE_DELEGATION)
			{
				if(pMode != 0)
				{
					/*WHEN USING DELEGATION, HOISTING IS REUIQRED, AND THEREFORE
							SUCH TREES MUST HAVE N >= 3 AS TO KEEP THE FOLLOWING
							ASSERTION TRUE. REMEMBER THAT IF N IS 2, AND THE
							ALGORITHM IS NOT PRE EMPTIVE, pNode COULD NOW BE EMPTY
							AFTER THE REMOVAL ABOVE, AND HENCE IT WOULD HAVE
							NOTHING LEFT FOR HOISTING.
					*/
					assert(pNode->gPrivate_numberOfEntries > 1);
					/*WARNING: REMEMBER, THE LENGTH IS NOT YET UPDATED AT THIS POINT,
							HENCE THE '- 1'.*/
					if(pMode == 1)
						{vImaginaryIndex = pNode->gPrivate_numberOfEntries - 1 /*2*/;}
					else /*pMode == 2*/
						{vImaginaryIndex = 1 /*0*/;}

					if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX)
					{
						if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
						{
							memcpy(pIndex__out,
									crx_c_tree_private_getIndexFrom(pThis->gPrivate_tree, pNode,
											vImaginaryIndex - 1),
									pThis->gPrivate_tree->gPrivate_typeBluePrint__index->
											gBYTE_SIZE);
						}
						else
						{
							(*(pThis->gPrivate_tree->gPrivate_constructIndexFrom))(pIndex__out,
									crx_c_tree_private_getElement(pThis->gPrivate_tree,
											pNode, vImaginaryIndex - 1));
						}
					}
					else
					{
						if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT)
						{
							if(pThis->gPrivate_tree->gPrivate_typeBluePrint__element->
									gFUNC__COPY_CONSTRUCT != NULL)
							{
								(*(pThis->gPrivate_tree->gPrivate_typeBluePrint__element->
										gFUNC__COPY_CONSTRUCT))(pElement__out,
										crx_c_tree_private_getElement(pThis->gPrivate_tree,
												pNode, vImaginaryIndex - 1));
							}
							else
							{
								memcpy(pElement__out,
										crx_c_tree_private_getElement(pThis->gPrivate_tree,
												pNode, vImaginaryIndex - 1),
										pThis->gPrivate_tree->gPrivate_typeBluePrint__element->
												gBYTE_SIZE);
							}
						}
						else
						{
							*((unsigned char * *)pElement__out) = crx_c_tree_private_getElement(
									pThis->gPrivate_tree, pNode, vImaginaryIndex - 1);
						}
					}
				}
			}
		}

		--(pNode->gPrivate_numberOfEntries);

		/*return vKey;*/
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() unsigned char * crx_c_tree_iterator_get(
		Crx_C_Tree_Iterator const * pThis)
{
	if(pThis->gPrivate_isConstant)
		{return NULL;}

	return crx_c_tree_iterator_private_doGet(pThis);
}
CRX__LIB__PUBLIC_C_FUNCTION() unsigned char const * crx_c_tree_iterator_constantGet(
		Crx_C_Tree_Iterator const * pThis)
	{return crx_c_tree_iterator_private_doGet(pThis);}
CRX__LIB__PRIVATE_C_FUNCTION() unsigned char * crx_c_tree_iterator_private_doGet(
		Crx_C_Tree_Iterator const * pThis)
{
	if(pThis->gPrivate_tree == NULL)
		{return NULL;}

	if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		if(pThis->gPrivate_position__current == pThis->gPrivate_positions)
			{return NULL;}
		else
		{
			if((CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ? 
					pThis->gPrivate_position__current->gNode : pThis->gPrivate_node)->gPrivate_type)
			{
				return crx_c_tree_private_getElement(pThis->gPrivate_tree,
						(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ? 
						pThis->gPrivate_position__current->gNode : pThis->gPrivate_node), 
						pThis->gPrivate_position__current->gIndex);
			}
			else
			{
				return crx_c_tree_private_getElement(pThis->gPrivate_tree,
						(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ? 
						pThis->gPrivate_position__current->gNode : pThis->gPrivate_node), 
						pThis->gPrivate_position__current->gIndex);
			}
		}
	}
	else
	{
		if(pThis->gPrivate_node == NULL)
			{return NULL;}
		else
		{
			return crx_c_tree_private_getElement(pThis->gPrivate_tree, pThis->gPrivate_node,
					pThis->gPrivate_elementIndex);
		}
	}
}

CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_tree_iterator_private_depthPush(
		Crx_C_Tree_Iterator * pThis, Crx_C_Tree_Private_Node * pNode,
		size_t pIndex)
{
	assert(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY);

	if(pThis->gPrivate_positions == NULL)
		{return false;}

	pThis->gPrivate_position__current++;

	if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
		{pThis->gPrivate_position__current->gNode = pNode;}
	else
	{
		assert(pNode->gPrivate_node__parent == pThis->gPrivate_node);

		pThis->gPrivate_node = pNode;
	}
	pThis->gPrivate_position__current->gIndex = pIndex;

	return true;
}
CRX__LIB__PRIVATE_C_FUNCTION() void crx_c_tree_iterator_private_depthPop(
		Crx_C_Tree_Iterator * pThis)
{
	assert(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY);

	if((pThis->gPrivate_positions != NULL) &&
			(pThis->gPrivate_position__current != pThis->gPrivate_positions))
	{
		pThis->gPrivate_position__current--;
		
		if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE)
			{pThis->gPrivate_node = pThis->gPrivate_node->gPrivate_node__parent;}
	}
}

CRX__LIB__PRIVATE_C_FUNCTION() bool crx_c_tree_iterator_private_isInInternalNode(
		Crx_C_Tree_Iterator * pThis)
{
	assert(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX);

	if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		assert(pThis->gPrivate_position__current != pThis->gPrivate_positions);

		return ((CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ? 
				pThis->gPrivate_position__current->gNode :
				pThis->gPrivate_node)->gPrivate_type != 0);
	}
	else
	{
		assert(pThis->gPrivate_node != NULL);

		return false;
	}
}
CRX__LIB__PRIVATE_C_FUNCTION() unsigned char * crx_c_tree_iterator_private_getIndex(
		Crx_C_Tree_Iterator * pThis)
{
	assert(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX);

	if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		if(pThis->gPrivate_position__current == pThis->gPrivate_positions)
			{return NULL;}
		else
		{
			if((CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ? 
					pThis->gPrivate_position__current->gNode : pThis->gPrivate_node)->gPrivate_type)
			{
				return crx_c_tree_private_getIndexFrom(pThis->gPrivate_tree,
						(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ?
						pThis->gPrivate_position__current->gNode : pThis->gPrivate_node),
						pThis->gPrivate_position__current->gIndex);
			}
			else
			{
				if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
					{return NULL;}
				else
				{
					return crx_c_tree_private_getIndexFrom(pThis->gPrivate_tree,
							(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ?
							pThis->gPrivate_position__current->gNode : pThis->gPrivate_node),
							pThis->gPrivate_position__current->gIndex);
				}
			}
		}
	}
	else
	{
		if(pThis->gPrivate_node == NULL)
			{return NULL;}
		else
		{
			if(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY)
				{return NULL;}
			else
			{
				return crx_c_tree_private_getIndexFrom(pThis->gPrivate_tree, pThis->gPrivate_node,
						pThis->gPrivate_elementIndex);
			}
		}
	}
}
CRX__LIB__PRIVATE_C_FUNCTION() unsigned char * crx_c_tree_iterator_private_getEntry(
		Crx_C_Tree_Iterator * pThis)
{
	if(!CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY)
	{
		if(pThis->gPrivate_position__current == pThis->gPrivate_positions)
			{return NULL;}
		else
		{
			if((CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ? 
					pThis->gPrivate_position__current->gNode :
					pThis->gPrivate_node)->gPrivate_type)
			{
				return crx_c_tree_private_getElementEntry(pThis->gPrivate_tree,
						(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ? 
						pThis->gPrivate_position__current->gNode : pThis->gPrivate_node), 
						pThis->gPrivate_position__current->gIndex);
			}
			else
			{
				return crx_c_tree_private_getElementEntry(pThis->gPrivate_tree,
						(CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE ?
						pThis->gPrivate_position__current->gNode : pThis->gPrivate_node), 
						pThis->gPrivate_position__current->gIndex);
			}
		}
	}
	else
	{
		if(pThis->gPrivate_node == NULL)
			{return NULL;}
		else
		{
			return crx_c_tree_private_getElementEntry(pThis->gPrivate_tree,
					pThis->gPrivate_node, pThis->gPrivate_elementIndex);
		}
	}
}




#undef CRX__C__TREE__PRIVATE__IS_BIT_SET
#undef CRX__C__TREE__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY
#undef CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY
#undef CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY2
#undef CRX__C__TREE__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY3
#undef CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION
#undef CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_DELEGATION3
#undef CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT
#undef CRX__C__TREE__PRIVATE__ECHO_IS_PERSISTANT3
#undef CRX__C__TREE__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH
#undef CRX__C__TREE__PRIVATE__ECHO_IS_PREEMPTIVE
#undef CRX__C__TREE__PRIVATE__ECHO_IS_TO_USE_RINGS
#undef CRX__C__TREE__PRIVATE__ECHO_HAS_INDEX
		
#undef CRX__C__TREE__ITERATOR__PRIVATE__ECHO_ARE_INDICES_IN_INTERNAL_NODES_ONLY
#undef CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY
#undef CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_ELEMENT_DATA_IN_LEAVES_ONLY2
#undef CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_TO_USE_DELEGATION
#undef CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PERSISTANT
/*#undef CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_CONSERVATIVE_IN_GROWTH*/
#undef CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_PREEMPTIVE
#undef CRX__C__TREE__ITERATOR__PRIVATE__ECHO_IS_TO_USE_RINGS
#undef CRX__C__TREE__ITERATOR__PRIVATE__ECHO_HAS_INDEX

CRX__LIB__C_CODE_END()

