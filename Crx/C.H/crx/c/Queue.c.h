CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_construct(Crx_C_Queue * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint, 
		size_t pNodeCapacity CRX_DEFAULT(0));
{
	assert(pNodeCapacity < 256);

	pThis->gPrivate_typeBluePrint = pTypeBluePrint;
	pThis->gPrivate_rootNode = NULL;
	pThis->gPrivate_lastNode = NULL;
	pThis->gPrivate_length = 0;
	pThis->gPRIVATE__NODE_CAPACITY = ((pNodeCapacity == 0) ? 4 : pNodeCapacity);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_copyConstruct(Crx_C_Queue * pThis,
		Crx_C_Queue const * CRX_NOT_NULL pQueue)
{
	if(!pQueue->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	pThis->gPrivate_typeBluePrint = pQueue->gPrivate_typeBluePrint;

	if(pQueue->gPrivate_rootNode != NULL)
	{
		pThis->gPrivate_lastNode = NULL;
		pThis->gPrivate_rootNode = crx_c_queue_private_copyNodes(
				pQueue->gPrivate_rootNode, &(pThis->gPrivate_lastNode));
	}
	else
	{
		pThis->gPrivate_rootNode = NULL;
		pThis->gPrivate_lastNode = NULL;
	}

	if(pQueue->gPrivate_rootNode != NULL)
		{pThis->gPrivate_length = pQueue->gPrivate_length;}
	else
	{
		pThis->gPrivate_lastNode = NULL;
		pThis->gPrivate_length = 0;
	}

	pThis->gPRIVATE__NODE_CAPACITY = pQueue->gPRIVATE__NODE_CAPACITY;
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Queue * crx_c_queue_new(
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint, 
		size_t pNodeCapacity CRX_DEFAULT(0))
{
	Crx_C_Queue * vReturn = (Crx_C_Queue *)(calloc(1,
			sizeof(Crx_C_Queue)));

	if(vReturn != NULL)
		{crx_c_queue_construct(vReturn, pTypeBluePrint, pNodeCapacity);}

	return vReturn;
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Queue * crx_c_queue_moveNew(
		Crx_C_Queue * CRX_NOT_NULL pQueue)
{
	Crx_C_Queue * vReturn = (Crx_C_Queue *)(calloc(1,
			sizeof(Crx_C_Queue)));

	if(vReturn != NULL)
		{memcpy(vReturn, pQueue, sizeof(Crx_C_Queue));}

	return vReturn;
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Queue * crx_c_queue_copyNew(
		Crx_C_Queue const * CRX_NOT_NULL pQueue)
{
	CRX_SCOPE_META
	if(!pQueue->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}
	
	CRX_SCOPE
	Crx_C_Queue * vReturn = (Crx_C_Queue *)(calloc(1,
			sizeof(Crx_C_Queue)));

	if(vReturn != NULL)
		{crx_c_queue_copyConstruct(vReturn, pQueue);}

	return vReturn;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_destruct(Crx_C_Queue * pThis)
{
	if(pThis->pThis->gPrivate_rootNode != NULL)
		{crx_c_queue_private_removeNodes(pThis->gPrivate_rootNode);}
	
	CRX__C__TYPE_BLUE_PRINT__GENERIC__FINALIZE(pThis->gPrivate_typeBluePrint);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_free(Crx_C_Queue * pThis)
	{free(pThis);}

CRX__C__TYPE_BLUE_PRINT__GENERIC__DEFINE_GET_BLUE_PRINT(
		Crx_C_Queue, crx_c_queue_,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__FALSE, CRXM__FALSE,
		true, true,
		(pThis->gPrivate_typeBluePrint->gIS_COPYABLE != NULL), true,
		false, false)

CRX__LIB__PRIVATE_C_FUNCTION() Crx_C_Queue_Private_Node * crx_c_queue_private_copyNodes(
		Crx_C_Queue * pThis, Crx_C_Queue_Private_Node * pNode__start,
		Crx_C_Queue_Private_Node * * pNode__lastNode)
{
	CRX_SCOPE_META
	if(pNode__start != NULL)
		{return NULL;}

	CRX_SCOPE
	Crx_C_Queue_Private_Node * vCurrentNode = pNode__start->gPrivate_next;
	Crx_C_Queue_Private_Node * vCurrentNode__out =
			crx_c_queue_private_node_copyNew(pNode__start);
	Crx_C_Queue_Private_Node * vReturn = vCurrentNode__out;

	while(vCurrentNode != NULL)
	{
		vCurrentNode__out->gPrivate_next =
				crx_c_queue_private_node_copyNew(vCurrentNode);

		if(vCurrentNode__out->gPrivate_next != NULL)
		{
			vCurrentNode__out->gPrivate_next->gPrivate_prev = vCurrentNode__out;

			vCurrentNode = vCurrentNode->gPrivate_next;
			vCurrentNode__out = vCurrentNode__out->gPrivate_next;
		}
		else
			{break;}
	}

	if(vCurrentNode__out != NULL)
	{
		if(pNode__lastNode != NULL)
			{*pNode__lastNode = vCurrentNode__out;}
	}
	else
	{
		crx_c_queue_private_removeNodes(vReturn);
		vReturn = NULL;
	}

	return vReturn;
}

CRX__LIB__PRIVATE_C_FUNCTION() Crx_C_Queue_Private_Node * crx_c_queue_private_removeNodes( \
		Crx_C_Queue * pThis, Crx_C_Queue_Private_Node * pNode__start)
{
	Crx_C_Queue_Private_Node * vCurrentNode = pNode__start;
	Crx_C_Queue_Private_Node * vNextNode = NULL;

	if(pNode__start->gPrivate_prev != NULL)
		{pNode__start->gPrivate_prev->gPrivate_next = NULL;}

	while(vCurrentNode != NULL)
	{
		vNextNode = pNode__start->gPrivate_next;

		crx_c_queue_private_node_destruct(vCurrentNode);
		crx_c_queue_private_node_free(vCurrentNode);

		vCurrentNode = vNextNode;
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_empty(Crx_C_Queue * pThis)
{
	if(pThis->pThis->gPrivate_rootNode != NULL)
	{
		crx_c_queue_private_removeNodes(pThis->gPrivate_rootNode);

		pThis->gPrivate_rootNode = NULL;
		pThis->gPrivate_lastNode = NULL;
		pThis->gPrivate_length = 0;
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_queue_getLength(Crx_C_Queue const * pThis)
	{return pThis->gPrivate_length;}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_tryMoveAndPush(Crx_C_Queue * pThis,
		pELEMENT_TYPE * pElement)
{
	if((pThis->gPrivate_lastNode == NULL) ||
			!crx_c_queue_private_node_hasRoomForPush(pThis->gPrivate_lastNode))
	{
		Crx_C_Queue_Private_Node tNode = crx_c_queue_private_node_new(
				(uint8_t)((pThis->gPrivate_lastNode == NULL) ?
						(pThis->gPRIVATE__NODE_CAPACITY / 2) : 0),
				pThis->gPRIVATE__NODE_CAPACITY);

		if(tNode != NULL)
		{
			if(pThis->gPrivate_lastNode != NULL)
			{
				pThis->gPrivate_lastNode->gPrivate_next = tNode;
				tNode->gPrivate_prev = pThis->gPrivate_lastNode->gPrivate_prev;
			}
			else
				{pThis->gPrivate_rootNode = tNode;}

			pThis->gPrivate_lastNode = tNode;
		}
	}

	if((pThis->gPrivate_lastNode != NULL) &&
			crx_c_queue_private_node_hasRoomForPush(pThis->gPrivate_lastNode))
	{
		return crx_c_queue_private_node_tryMoveAndPush(
				pThis->gPrivate_lastNode, pElement);
	}
	else
		{return false;}

}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_push(Crx_C_Queue * pThis,
		pELEMENT_TYPE * pElement)
{
	CRX_SCOPE_META
	if(!pThis->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	CRX_SCOPE
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(
			pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
	bool vReturn;

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(((pELEMENT_TYPE *)vElement), pElement);

		vReturn = crx_c_queue_tryMoveAndPush(pThis, ((pELEMENT_TYPE *)vElement));
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			vReturn = crx_c_queue_tryMoveAndPush(pThis, ((pELEMENT_TYPE *)vElement));
		}
		else
			{vReturn = crx_c_queue_tryMoveAndPush(pThis, ((pELEMENT_TYPE *)pElement));}
	}

	if(((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) ||
			(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || 
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)))
	{
		if(vReturn)
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
				{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(((pELEMENT_TYPE *)vElement));}
		}
		else
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
				{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(((pELEMENT_TYPE *)vElement));}
		}
	}

	return vReturn;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_pop(Crx_C_Queue * pThis)
{
	if(pThis->gPrivate_length > 0)
	{
		if((pThis->gPrivate_lastNode->gPrivate_length == 0) &&
				(pThis->gPrivate_lastNode != pThis->gPrivate_rootNode))
		{
			Crx_C_Queue_Private_Node * tNode =
					pThis->gPrivate_lastNode->gPrivate_prev;

			tNode->gPrivate_next = NULL;

			crx_c_queue_private_node_destruct(pThis->gPrivate_lastNode);
			crx_c_queue_private_node_free(pThis->gPrivate_lastNode);

			pThis->gPrivate_lastNode = tNode;
		}

		crx_c_queue_private_node_pop(pThis->gPrivate_lastNode);
		pThis->gPrivate_length = pThis->gPrivate_length - 1;
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_tryMoveAndPushToFront(Crx_C_Queue * pThis, \
		pELEMENT_TYPE * pElement)
{
	if((pThis->gPrivate_lastNode == NULL) ||
			!crx_c_queue_private_node_hasRoomForPush(pThis->gPrivate_lastNode))
	{
		Crx_C_Queue_Private_Node tNode = crx_c_queue_private_node_new(
				(uint8_t)((pThis->gPrivate_lastNode == NULL) ?
						(pThis->gPRIVATE__NODE_CAPACITY / 2) : 
						pThis->gPRIVATE__NODE_CAPACITY - 1),
				pThis->gPRIVATE__NODE_CAPACITY);

		if(tNode != NULL)
		{
			if(pThis->gPrivate_rootNode != NULL)
			{
				tNode->gPrivate_next = pThis->gPrivate_rootNode;
				pThis->gPrivate_rootNode->gPrivate_prev = tNode;
			}
			else
				{pThis->gPrivate_lastNode = tNode;}

			pThis->gPrivate_rootNode = tNode;
		}
	}

	if((pThis->gPrivate_rootNode != NULL) &&
			crx_c_queue_private_node_hasRoomForPushToFront(
					pThis->gPrivate_rootNode))
	{
		return crx_c_queue_private_node_tryMoveAndPushToFront(
				pThis->gPrivate_rootNode, pElement);
	}
	else
		{return false;}

}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_pushToFront(Crx_C_Queue * pThis,
		pELEMENT_TYPE * pElement)
{
	CRX_SCOPE_META
	if(!pThis->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	CRX_SCOPE
	unsigned char * vElement = (unsigned char *) CRX__ALLOCA(
			pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
	bool vReturn;

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(((pELEMENT_TYPE *)vElement), pElement);

		vReturn = crx_c_queue_tryMoveAndPushToFront(pThis, ((pELEMENT_TYPE *)vElement));
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			vReturn = crx_c_queue_tryMoveAndPushToFront(pThis, ((pELEMENT_TYPE *)vElement));
		}
		else
			{vReturn = crx_c_queue_tryMoveAndPushToFront(pThis, ((pELEMENT_TYPE *)pElement));}
	}

	if(((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL) ||
			(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)) && 
			((pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL) || 
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)))
	{
		if(vReturn)
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
				{(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(((pELEMENT_TYPE *)vElement));}
		}
		else
		{
			if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
				{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(((pELEMENT_TYPE *)vElement));}
		}
	}

	return vReturn;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_popFromFront(Crx_C_Queue * pThis)
{
	if(pThis->gPrivate_length > 0)
	{
		if((pThis->gPrivate_rootNode->gPrivate_length == 0) &&
				(pThis->gPrivate_rootNode != pThis->gPrivate_lastNode))
		{
			Crx_C_Queue_Private_Node * tNode =
					pThis->gPrivate_rootNode->gPrivate_next;

			tNode->gPrivate_prev = NULL;

			crx_c_queue_private_node_destruct(pThis->gPrivate_rootNode);
			crx_c_queue_private_node_free(pThis->gPrivate_rootNode);

			pThis->gPrivate_rootNode = tNode;
		}

		crx_c_queue_private_node_popFromFront(pThis->gPrivate_rootNode);
		pThis->gPrivate_length = pThis->gPrivate_length - 1;
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() pELEMENT_TYPE * crx_c_queue_get(Crx_C_Queue * pThis)
{
	assert(pThis->gPrivate_length > 0);

	Crx_C_Queue_Private_Node * vNode =
			((pThis->gPrivate_lastNode->gPrivate_length != 0) ? pThis->gPrivate_lastNode :
			pThis->gPrivate_lastNode->gPrivate_prev);

	return (tNode->gPrivate_elements + (vNode->gPrivate_startIndex +
			vNode->gPrivate_length - 1) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
}

CRX__LIB__PUBLIC_C_FUNCTION() pELEMENT_TYPE const * crx_c_queue_constantGet(
		Crx_C_Queue const * pThis)
	{return crx_c_queue_get((Crx_C_Queue *)pThis);}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_copyGetTo(Crx_C_Queue const * pThis,
		pELEMENT_TYPE * pReturn)
{
	CRX_SCOPE_META
	if(!pThis->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	CRX_SCOPE
	pELEMENT_TYPE * vElement = crx_c_queue_get(Crx_C_Queue * pThis);

	if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pReturn);}

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
		{(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(pReturn, vElement);}
	else
		{memcpy(pReturn, vElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() pELEMENT_TYPE * crx_c_queue_getFront(Crx_C_Queue * pThis)
{
	assert(pThis->gPrivate_length > 0);

	Crx_C_Queue_Private_Node * vNode =
			((pThis->gPrivate_rootNode->gPrivate_length != 0) ? pThis->gPrivate_rootNode :
			pThis->gPrivate_rootNode->gPrivate_next);

	return (vNode->gPrivate_elements + (vNode->gPrivate_startIndex * 
			pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
}
CRX__LIB__PUBLIC_C_FUNCTION() pELEMENT_TYPE const * crx_c_queue_constantGetFront(
		Crx_C_Queue const * pThis)
	{return crx_c_queue_getFront((Crx_C_Queue *)pThis);}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_copyGetFrontTo(Crx_C_Queue const * pThis,
		pELEMENT_TYPE * pReturn)
{
	CRX_SCOPE_META
	if(!pThis->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	CRX_SCOPE
	pELEMENT_TYPE * vElement = crx_c_queue_getFront(Crx_C_Queue * pThis);

	if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pReturn);}

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
		{(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(pReturn, vElement);}
	else
		{memcpy(pReturn, vElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);}
	CRX_SCOPE_END
}



CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_queue_private_node_getByteSizeOf(
		Crx_C_Queue_Private_Node const * CRX_NOT_NULL pNode)
{
	return (sizeof(Crx_C_Queue_Private_Node) +
			((pNode->gPRIVATE__NODE_CAPACITY - 1) * pNode->gPrivate_typeBluePrint->gBYTE_SIZE));
}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_queue_private_node_getByteSizeFor(
		Crx_C_TypeBluePrint const * pTypeBluePrint, uint8_t pNodeCapacity)
{
	return (sizeof(Crx_C_Queue_Private_Node) +
			((pNodeCapacity - 1) * pTypeBluePrint->gBYTE_SIZE));
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_private_node_construct(
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint,
		Crx_C_Queue_Private_Node * pThis, uint8_t pStartIndex, uint8_t pNodeCapacity)
{
	pThis->gPrivate_typeBluePrint = pTypeBluePrint;
	pThis->gPrivate_next = NULL;
	pThis->gPrivate_prev = NULL;
	pThis->gPrivate_length = 0;
	pThis->gPrivate_startIndex = pStartIndex;
	pThis->gPRIVATE__NODE_CAPACITY = pNodeCapacity;
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_private_node_copyConstruct(
		Crx_C_Queue_Private_Node * pThis,
		Crx_C_Queue_Private_Node const * pNode)
{
	if(!pNode->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	pThis->gPrivate_typeBluePrint = pNode->gPrivate_typeBluePrint;
	pThis->gPrivate_next = NULL;
	pThis->gPrivate_prev = NULL;
	pThis->gPrivate_length = pNode->gPrivate_length;
	pThis->gPrivate_startIndex = pNode->gPrivate_startIndex;
	pThis->gPRIVATE__NODE_CAPACITY = pNode->gPRIVATE__NODE_CAPACITY;

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		CRX_FOR(size_t tI = 0, tI < pNode->gPrivate_length, tI++)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(pThis->gPrivate_elements +
							((pThis->gPrivate_startIndex + tI) * 
							pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					pNode->gPrivate_elements + ((pThis->gPrivate_startIndex + tI) * 
							pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}
		CRX_ENDFOR
	}
	else
	{
		memcpy(pThis->gPrivate_elements + 
						(pThis->gPrivate_startIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
				pNode->gPrivate_elements +
						(pThis->gPrivate_startIndex * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
				pThis->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Queue_Private_Node * crx_c_queue_private_node_new(
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint,
		uint8_t pStartIndex, uint8_t pNodeCapacity)
{
	Crx_C_Queue_Private_Node * vReturn = NULL;
			((Crx_C_Queue_Private_Node *) calloc(1,
			crx_c_queue_private_node_getByteSizeFor(pTypeBluePrint, pNodeCapacity)));

	if(vReturn != NULL)
	{
		crx_c_queue_private_node_construct(vReturn, pTypeBluePrint, pStartIndex,
				pNodeCapacity);
	}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_Queue_Private_Node * crx_c_queue_private_node_copyNew( \
		Crx_C_Queue_Private_Node const * pNode)
{
	if(!pNode->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	Crx_C_Queue_Private_Node * vReturn = 
			((Crx_C_Queue_Private_Node *) calloc(1,
			crx_c_queue_private_node_getByteSizeOf(pNode)));

	if(vReturn != NULL)
		{crx_c_queue_private_node_copyConstruct(vReturn, pNode);}

	return vReturn;
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_private_node_destruct(
		Crx_C_Queue_Private_Node * pThis)
{
	if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT == NULL)
		{return;}

	CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements +
				((pThis->gPrivate_startIndex + tI) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
	}
	CRX_ENDFOR
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_private_node_free(
		Crx_C_Queue_Private_Node * pThis)
	{free(pThis);}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_private_node_tryMoveAndPush(
		Crx_C_Queue_Private_Node * pThis, pELEMENT_TYPE * pElement)
{
	if((pThis->gPrivate_startIndex + pThis->gPrivate_length) < (pThis->gPRIVATE__NODE_CAPACITY - 1))
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements +
					((pThis->gPrivate_startIndex + 1) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
					pElement);
		}
		else
		{
			memcpy(pThis->gPrivate_elements + ((pThis->gPrivate_startIndex + 1) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement, 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}

		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_private_node_hasRoomForPush(
		Crx_C_Queue_Private_Node * pThis)
{
	return ((pThis->gPrivate_startIndex + pThis->gPrivate_length) <
			(pThis->gPRIVATE__NODE_CAPACITY - 1));
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_private_node_pop(
		Crx_C_Queue_Private_Node * pThis)
{
	if(pThis->gPrivate_length > 0)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements + 
					((pThis->gPrivate_startIndex + pThis->gPrivate_length - 1]) *
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}

		pThis->gPrivate_length = pThis->gPrivate_length - 1;
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_private_node_tryMoveAndPushToFront(
		Crx_C_Queue_Private_Node * pThis, pELEMENT_TYPE * pElement)
{
	if(pThis->gPrivate_startIndex > 0)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		(
			(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements +
					((pThis->gPrivate_startIndex - 1) * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
					pElement);
		)
		(
			memcpy(pThis->gPrivate_elements + ((pThis->gPrivate_startIndex - 1) * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		)

		return true;
	}
	else
		{return false;}
}
CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_queue_private_node_hasRoomForPushToFront(
		Crx_C_Queue_Private_Node * pThis)
	{return (pThis->gPrivate_startIndex > 0);}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_queue_private_node_popFromFront(
		Crx_C_Queue_Private_Node * pThis)
{
	if(pThis->gPrivate_length > 0)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(
					pThis->gPrivate_elements + (pThis->gPrivate_startIndex * 
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}

		pThis->gPrivate_length = pThis->gPrivate_length - 1;

		if(pThis->gPrivate_startIndex < (pThis->gPRIVATE__NODE_CAPACITY - 1))
			{pThis->gPrivate_startIndex = pThis->gPrivate_startIndex + 1;}
	}
}