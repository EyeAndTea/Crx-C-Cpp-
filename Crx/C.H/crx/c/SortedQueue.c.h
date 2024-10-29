CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_sortedQueue_construct(Crx_C_SortedQueue * pThis,
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint, 
		Crx_C_TypeBluePrint_GetOrderOfObjects pFunc_getOrderOfElements, bool pIsReversed, 
		size_t pCapacity CRX_DEFAULT(0))
{
	CRX_SCOPE_META
	assert((pCapacity == 0) || ((pCapacity & (pCapacity - 1)) == 0));

	CRX_SCOPE
	size_t vCapacity = ((pCapacity > 0) ? pCapacity : 4);

	pThis->gPrivate_typeBluePrint = pTypeBluePrint;
	pThis->gPrivate_length = 0;
	pThis->gFunc_getOrderOfElements = pFunc_getOrderOfElements;
	pThis->gPrivate_isReversed = pIsReversed;

	if(vCapacity > 0)
	{
		pThis->gPrivate_elements = (pELEMENT_TYPE *)(malloc(
				vCapacity * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

		if(pThis->gPrivate_elements != NULL)
			{pThis->gPrivate_capacity = vCapacity;}
		else
			{pThis->gPrivate_capacity = 0;}
	}
	else
	{
		pThis->gPrivate_elements = NULL;
		pThis->gPrivate_capacity = 0;
	}
	CRX_SCOPE_END
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_sortedQueue_copyConstruct(Crx_C_SortedQueue * pThis,
		Crx_C_SortedQueue const * pSortedQueue)
{
	if(!pQueue->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	crx_c_sortedQueue_construct(pThis, pSortedQueue->gPrivate_typeBluePrint
			pSortedQueue->gFunc_getOrderOfElements,
			pSortedQueue->gPrivate_isReversed,
			pSortedQueue->gPrivate_capacity);

	if((pSortedQueue->gPrivate_length > 0) &&
			(pThis->gPrivate_capacity > pSortedQueue->gPrivate_length))
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
		{
			CRX_FOR(size_t tI = 0, tI < pSortedQueue->gPrivate_length, tI++)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(
						pThis->gPrivate_elements + (tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
						pSortedQueue->gPrivate_elements + 
								(tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
			}
			CRX_ENDFOR
		}
		else
		{
			memcpy(pThis->gPrivate_elements,
					pSortedQueue->gPrivate_elements,
					pSortedQueue->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
		}

		pThis->gPrivate_length = pSortedQueue->gPrivate_length;
	}
}

CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_SortedQueue * crx_c_sortedQueue_new(
		Crx_C_TypeBluePrint const * CRX_NOT_NULL pTypeBluePrint, 
		Crx_C_TypeBluePrint_GetOrderOfObjects pFunc_getOrderOfElements, 
		bool pIsReversed, size_t pCapacity CRX_DEFAULT(0))
{
	Crx_C_SortedQueue * vReturn = (Crx_C_SortedQueue *)(calloc(1,
			sizeof(Crx_C_SortedQueue)));

	if(vReturn != NULL)
	{
		crx_c_sortedQueue_construct(vReturn, pTypeBluePrint, pFunc_getOrderOfElements, 
				pIsReversed, pCapacity);
	}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_SortedQueue * crx_c_sortedQueue_moveNew(
		Crx_C_SortedQueue * CRX_NOT_NULL pSortedQueue)
{
	Crx_C_SortedQueue * vReturn = (Crx_C_SortedQueue *)(calloc(1,
			sizeof(Crx_C_SortedQueue)));

	if(vReturn != NULL)
		{memcpy(vReturn, pSortedQueue, sizeof(Crx_C_SortedQueue));}

	return vReturn;
}
CRX__LIB__PUBLIC_C_FUNCTION() Crx_C_SortedQueue * crx_c_sortedQueue_copyNew(
		Crx_C_SortedQueue const * CRX_NOT_NULL pSortedQueue)
{
	CRX_SCOPE_META
	if(!pQueue->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	CRX_SCOPE
	Crx_C_SortedQueue * vReturn = (Crx_C_SortedQueue *)(calloc(1,
			sizeof(Crx_C_SortedQueue)));

	if(vReturn != NULL)
		{crx_c_sortedQueue_copyConstruct(vReturn, pSortedQueue);}

	return vReturn;
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_sortedQueue_destruct(Crx_C_SortedQueue * pThis)
{
	if(pThis->gPrivate_elements != NULL)
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{
			CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements + 
						(tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
			}
			CRX_ENDFOR
		}

		free(pThis->gPrivate_elements);
		pThis->gPrivate_elements = NULL;
	}

	CRX__C__TYPE_BLUE_PRINT__GENERIC__FINALIZE(pThis->gPrivate_typeBluePrint);
}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_sortedQueue_free(Crx_C_SortedQueue * pThis)
	{free(pThis);}

CRX__C__TYPE_BLUE_PRINT__GENERIC__DEFINE_GET_BLUE_PRINT(
		Crx_C_SortedQueue, crx_c_sortedQueue_,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__TRUE, CRXM__TRUE,
		CRXM__FALSE, CRXM__FALSE,
		true, true,
		(pThis->gPrivate_typeBluePrint->gIS_COPYABLE != NULL), true,
		false, false)

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_sortedQueue_ensureCapacity(Crx_C_SortedQueue * pThis,
		size_t pCapacity)
{
	CRX_SCOPE_META
	if(pCapacity <= pThis->gPrivate_capacity)
		{return true;}
	else if(pCapacity > ((pSIZE_T_MAX >> 1) + 1))
		{return false;}

	CRX_SCOPE
	size_t vCapacity = ((pThis->gPrivate_capacity == 0 ? 1 : pThis->gPrivate_capacity) << 1); \

	while(vCapacity < pCapacity)
		{vCapacity = (vCapacity << 1);}

	if(pThis->gPrivate_elements == NULL)
	{
		pThis->gPrivate_elements = (pELEMENT_TYPE *)(malloc(vCapacity *
				pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

		if(pThis->gPrivate_elements != NULL)
		{
			pThis->gPrivate_capacity = vCapacity;

			return true;
		}
		else
			{return false;}
	}
	else
	{
		if((pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL) || 
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL))
		{
			pELEMENT_TYPE * tElements = (pELEMENT_TYPE *)(malloc(vCapacity *
					pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

			if(tElements != NULL)
			{
				if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
				{
					CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++)
					{
						(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(tElements + tI,
								pThis->gPrivate_elements + 
								(tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
					}
					CRX_ENDFOR
				}
				else
				{
					memcpy(tElements, pThis->gPrivate_elements,
							pThis->gPrivate_length * pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
				}

				if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
				{
					CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++)
					{
						(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(
								pThis->gPrivate_elements + 
								(tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
					}
					CRX_ENDFOR
				}

				free(pThis->gPrivate_elements);
				pThis->gPrivate_elements = tElements;

				pThis->gPrivate_capacity = vCapacity;

				return true;
			}
			else
				{return false;}
		}
		else
		{
			pELEMENT_TYPE * tElements = (pELEMENT_TYPE *)(realloc(pThis->gPrivate_elements,
					vCapacity * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));

			if(tElements != NULL)
			{
				pThis->gPrivate_elements = tElements;

				pThis->gPrivate_capacity = vCapacity;

				return true;
			}
			else
				{return false;}
		}
	}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_sortedQueue_getLength(Crx_C_SortedQueue const * pThis)
	{return pThis->gPrivate_length;}
CRX__LIB__PUBLIC_C_FUNCTION() size_t crx_c_sortedQueue_getCapacity(Crx_C_SortedQueue const * pThis)
	{return pThis->gPrivate_capacity;}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_sortedQueue_tryMoveAndPush(Crx_C_SortedQueue * pThis,
		pELEMENT_TYPE * CRX_NOT_NULL pElement)
{
	CRX_SCOPE_META
	if((pThis->gPrivate_capacity == pThis->gPrivate_length) &&
			!crx_c_sortedQueue_ensureCapacity(pThis, pThis->gPrivate_capacity + 1))
		{return false;}

	CRX_SCOPE
	size_t vIndexOfCurrentNode = pThis->gPrivate_length;

	if(vIndexOfCurrentNode > 0)
	{
		size_t tIndexOfParentOfCurrentNode =
				CRX__C__SortedQueue__GET_PARENT_NODE_INDEX(vIndexOfCurrentNode);

		if(!pThis->gPrivate_isReversed)
		{
			while((*(pThis->gPrivate_isReversed))(pThis->gPrivate_elements + 
					(tIndexOfParentOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
					pElement) > 0)
			{
				if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
				{
					(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + 
							(vIndexOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
							pThis->gPrivate_elements + 
							(tIndexOfParentOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
				}
				else
				{
					memcpy(pThis->gPrivate_elements + 
									(vIndexOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							pThis->gPrivate_elements + (tIndexOfParentOfCurrentNode * 
									pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
				}

				if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
				{
					(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(pThis->gPrivate_elements +
							(tIndexOfParentOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
				}

				vIndexOfCurrentNode = tIndexOfParentOfCurrentNode;

				if(vIndexOfCurrentNode > 0)
				{
					tIndexOfParentOfCurrentNode =
							CRX__C__SortedQueue__GET_PARENT_NODE_INDEX(vIndexOfCurrentNode);
				}
				else
					{break;}
			}
		}
		else
		{
			while((*(pThis->gPrivate_isReversed))(pThis->gPrivate_elements + 
					(tIndexOfParentOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
					pElement) < 0)
			{
				if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
				{
					(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + 
							(vIndexOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
							pThis->gPrivate_elements + 
							(tIndexOfParentOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
				}
				else
				{
					memcpy(pThis->gPrivate_elements + 
									(vIndexOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							pThis->gPrivate_elements + (tIndexOfParentOfCurrentNode * 
									pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
							pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
				}

				if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
				{
					(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(pThis->gPrivate_elements +
							(tIndexOfParentOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
				}

				vIndexOfCurrentNode = tIndexOfParentOfCurrentNode;

				if(vIndexOfCurrentNode > 0)
				{
					tIndexOfParentOfCurrentNode =
							CRX__C__SortedQueue__GET_PARENT_NODE_INDEX(vIndexOfCurrentNode);
				}
				else
					{break;}
			}
		}
	}

	if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + 
				(vIndexOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), pElement);
	}
	else
	{
		memcpy(pThis->gPrivate_elements + 
				(vIndexOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
				pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
	}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() bool crx_c_sortedQueue_push(Crx_C_SortedQueue * pThis,
		pELEMENT_TYPE * CRX_NOT_NULL pElement)
{
	CRX_SCOPE_META
	if(!pThis->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	CRX_SCOPE
	unsigned char * vElement = (unsigned char *)CRX__ALLOCA(
			pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
	bool vReturn;

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
	{
		(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(((pELEMENT_TYPE *)vElement), 
				pElement);

		vReturn = crx_c_sortedQueue_tryMoveAndPush(pThis, ((pELEMENT_TYPE *)vElement));
	}
	else
	{
		if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
		{
			memcpy(vElement, pElement, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);

			vReturn = crx_c_sortedQueue_tryMoveAndPush(pThis, ((pELEMENT_TYPE *)vElement));
		}
		else
			{return crx_c_sortedQueue_tryMoveAndPush(pThis, ((pELEMENT_TYPE *)pElement));}
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

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_sortedQueue_popFromFront(Crx_C_SortedQueue * pThis) \
{
	CRX_SCOPE_META
	if(pThis->gPrivate_length == 0)
		{return true;}

	CRX_SCOPE
	size_t vIndexOfCurrentNode = 0;

	if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements);}

	pThis->gPrivate_length = pThis->gPrivate_length - 1;

	if(!pThis->gPrivate_isReversed)
	{
		while(vIndexOfCurrentNode < pThis->gPrivate_length)
		{
			size_t tIndexOfChildToMove /*= ?*/;

			if((*(pThis->gPrivate_isReversed))(pThis->gPrivate_elements +
							(CRX__C__SortedQueue__GET_LEFT_CHILD_NODE_INDEX(vIndexOfCurrentNode) * 
							pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					pThis->gPrivate_elements +
							(CRX__C__SortedQueue__GET_RIGHT_CHILD_NODE_INDEX(vIndexOfCurrentNode) * 
							pThis->gPrivate_typeBluePrint->gBYTE_SIZE)) < 0)
			{
				tIndexOfChildToMove =
						CRX__C__SortedQueue__GET_LEFT_CHILD_NODE_INDEX(vIndexOfCurrentNode);
			}
			else
			{
				tIndexOfChildToMove =
						CRX__C__SortedQueue__GET_RIGHT_CHILD_NODE_INDEX(vIndexOfCurrentNode);
			}

			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + 
						(vIndexOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
						pThis->gPrivate_elements + 
						(tIndexOfChildToMove * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
			}
			else
			{
				memcpy(pThis->gPrivate_elements + 
								(vIndexOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						pThis->gPrivate_elements + 
								(tIndexOfChildToMove * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}

			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(pThis->gPrivate_elements + 
						(tIndexOfChildToMove * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
			}

			vIndexOfCurrentNode = tIndexOfChildToMove;
		}
	}
	else
	{
		while(vIndexOfCurrentNode < pThis->gPrivate_length)
		{
			size_t tIndexOfChildToMove /*= ?*/;

			if((*(pThis->gPrivate_isReversed))(pThis->gPrivate_elements +
							(CRX__C__SortedQueue__GET_LEFT_CHILD_NODE_INDEX(vIndexOfCurrentNode) * 
							pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
					pThis->gPrivate_elements +
							(CRX__C__SortedQueue__GET_RIGHT_CHILD_NODE_INDEX(vIndexOfCurrentNode) * 
							pThis->gPrivate_typeBluePrint->gBYTE_SIZE)) > 0)
			{
				tIndexOfChildToMove =
						CRX__C__SortedQueue__GET_LEFT_CHILD_NODE_INDEX(vIndexOfCurrentNode);
			}
			else
			{
				tIndexOfChildToMove =
						CRX__C__SortedQueue__GET_RIGHT_CHILD_NODE_INDEX(vIndexOfCurrentNode);
			}

			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT != NULL)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_CONSTRUCT)(pThis->gPrivate_elements + 
						(vIndexOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE), 
						pThis->gPrivate_elements + 
						(tIndexOfChildToMove * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
			}
			else
			{
				memcpy(pThis->gPrivate_elements + 
								(vIndexOfCurrentNode * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						pThis->gPrivate_elements + 
								(tIndexOfChildToMove * pThis->gPrivate_typeBluePrint->gBYTE_SIZE),
						pThis->gPrivate_typeBluePrint->gBYTE_SIZE);
			}

			if(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT != NULL)
			{
				(pThis->gPrivate_typeBluePrint->gFUNC__MOVE_DESTRUCT)(pThis->gPrivate_elements + 
						(tIndexOfChildToMove * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
			}

			vIndexOfCurrentNode = tIndexOfChildToMove;
		}
	}
	CRX_SCOPE_END
}

CRX__LIB__PUBLIC_C_FUNCTION() pELEMENT_TYPE * crx_c_sortedQueue_getFront(Crx_C_SortedQueue * pThis)
{
	assert(pThis->gPrivate_length > 0);

	return pThis->gPrivate_elements;
}
CRX__LIB__PUBLIC_C_FUNCTION() pELEMENT_TYPE const * crx_c_sortedQueue_constantGetFront(
		Crx_C_SortedQueue const * pThis)
	{return crx_c_sortedQueue_getFront((Crx_C_SortedQueue *)pThis);}
CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_sortedQueue_copyGetFrontTo(Crx_C_SortedQueue const * pThis,
		pELEMENT_TYPE * CRX_NOT_NULL pReturn)
{
	if(!pThis->gPrivate_typeBluePrint->gIS_COPYABLE)
		{abort();}

	if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
		{(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pReturn);}

	if(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT != NULL)
		{(pThis->gPrivate_typeBluePrint->gFUNC__COPY_CONSTRUCT)(pReturn, pThis->gPrivate_elements);}
	else
		{memcpy(pReturn, pThis->gPrivate_elements, pThis->gPrivate_typeBluePrint->gBYTE_SIZE);}
}

CRX__LIB__PUBLIC_C_FUNCTION() void crx_c_sortedQueue_empty(Crx_C_SortedQueue * pThis)
{
	if(pThis->gPrivate_length == 0)
		{return;}

	if(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT != NULL)
	{
		CRX_FOR(size_t tI = 0, tI < pThis->gPrivate_length, tI++)
		{
			(pThis->gPrivate_typeBluePrint->gFUNC__DESTRUCT)(pThis->gPrivate_elements + 
					(tI * pThis->gPrivate_typeBluePrint->gBYTE_SIZE));
		}
		CRX_ENDFOR
	}

	pThis->gPrivate_length = 0;
}
