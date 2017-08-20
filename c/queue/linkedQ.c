/******************************************************************************
* File Name : linkedQ.c
* Author :
* Description :
*
* Copyright (c) 2017 Son Jung Hee (aceofall@naver.com)
* All right reserved
******************************************************************************/

/******************************************************************************
* header and definitions
******************************************************************************/
/* global header files */
#include <stdio.h>
#include <stdlib.h>

/* local header files */
#include "linkedQ.h"

/******************************************************************************
* Debug level
******************************************************************************/

/******************************************************************************
* Definitions, typdef & const data
******************************************************************************/
#define PRINT_BYTE_NUM      4

/******************************************************************************
* Global variables and structures
******************************************************************************/

/******************************************************************************
* External variables and functions
******************************************************************************/

/******************************************************************************
* Static variables and structures
******************************************************************************/

/******************************************************************************
* Static function prototypes
******************************************************************************/
static void linkedQ_memcpy (void *pvDest, const void *pvSrc, unsigned int uiSize);
static void linkedQ_memset (void *pvSrc, int iData, unsigned int uiSize);

/******************************************************************************
* Function :
* Description :
* Input :
* Output :
* Return :
******************************************************************************/
//printf("[%d][%s]\n", __LINE__, __func__);
void init_linkedQ (LinkedQ_t *ptlinkedQHandle, char *pcName)
{
    ptlinkedQHandle->pcName = pcName;
    ptlinkedQHandle->eState = E_LINKED_Q_INIT;
    ptlinkedQHandle->ptFront = ptlinkedQHandle->ptRear = NULL;
	ptlinkedQHandle->uiUsedQSize = 0;
}

void clear_linkedQ (LinkedQ_t *ptlinkedQHandle)
{
    ptlinkedQHandle->eState = E_LINKED_Q_EMPTY;
    ptlinkedQHandle->ptFront = NULL;
    ptlinkedQHandle->ptRear = NULL;
}

static void linkedQ_memcpy (void *pvDest, const void *pvSrc, unsigned int uiSize)
{
    unsigned char *pucSrc, *pucDest;

    pucSrc = (unsigned char *)pvSrc;
    pucDest = (unsigned char *)pvDest;

    while (uiSize--)
    {
        *pucDest++ = *pucSrc++;
    }
}

static void linkedQ_memset (void *pvSrc, int iData, unsigned int uiSize)
{
    unsigned char *pucSrc;

    pucSrc = (unsigned char *)pvSrc;

    while (uiSize--)
    {
        *pucSrc++ = iData;
    }
}

LinkedQError_e pushData_linkedQ (LinkedQ_t *ptlinkedQHandle, unsigned char *pcDataBuf, unsigned int uiDataSize)
{
    unsigned int uiIndex = 0;
    QNode_t *ptAllocQNode = NULL, *ptTempQNode = NULL;

    if (NULL != ptlinkedQHandle->ptRear) {
        ptTempQNode = ptlinkedQHandle->ptRear;
    }

    for (uiIndex = 0; uiIndex < uiDataSize; uiIndex++) {
        ptAllocQNode = (LinkedQ_t *) malloc(sizeof(struct _QNode));
        linkedQ_memset(ptAllocQNode, 0, sizeof(struct _QNode));

        ptAllocQNode->ucData = *(pcDataBuf++);
		if (NULL != ptTempQNode) {
			ptTempQNode->ptLink = ptAllocQNode;
		} else{
			ptlinkedQHandle->ptFront = ptAllocQNode;
		}
		ptTempQNode = ptAllocQNode;
    }

	ptlinkedQHandle->uiUsedQSize += uiDataSize;
    ptlinkedQHandle->ptRear = ptAllocQNode;

    return E_ERROR_NONE;
}

LinkedQError_e getData_linkedQ (LinkedQ_t *ptlinkedQHandle, unsigned char *pcDataBuf, unsigned int uiDataSize)
{
    unsigned int uiIndex = 0, uiUsedSize = 0;
    QNode_t *ptFreeQNode = NULL, *ptTempQNode = NULL;

    uiUsedSize = getUsedSize_linkedQ(ptlinkedQHandle);
    if (uiUsedSize < uiDataSize) {
        return E_ERROR_RANGE;
    }

	ptTempQNode = ptlinkedQHandle->ptFront;
	if (NULL == ptTempQNode) {
		return E_ERROR_EMPTY;
	}

    for (uiIndex = 0; uiIndex < uiDataSize; uiIndex++) {
        *(pcDataBuf++) = ptTempQNode->ucData;
		ptFreeQNode = ptTempQNode;
		ptTempQNode = ptTempQNode->ptLink;
		free (ptFreeQNode);
	}

	ptlinkedQHandle->uiUsedQSize -= uiDataSize;
    ptlinkedQHandle->ptFront = ptTempQNode;

    return E_ERROR_NONE;
}

unsigned char getData1Byte_linkedQ(LinkedQ_t *ptlinkedQHandle)
{
    unsigned char ucData = 0;

    getData_linkedQ (ptlinkedQHandle, &ucData, 1);

    return ucData;
}

unsigned int getUsedSize_linkedQ (LinkedQ_t *ptlinkedQHandle)
{
    unsigned int uiUsedSize = 0;

	uiUsedSize = ptlinkedQHandle->uiUsedQSize;

    return uiUsedSize;
}

void print_linkedQ (LinkedQ_t *ptlinkedQHandle)
{
    unsigned int uiIndex = 0;
    QNode_t *ptPrintQNode = NULL, *ptTempQNode = NULL;
    unsigned int uiUsedSize = 0;

    uiUsedSize = getUsedSize_linkedQ(ptlinkedQHandle);

// printf("[%d][%s] uiFrontIndex: %d\n", __LINE__, __func__, uiFrontIndex);
// printf("[%d][%s] uiRearIndex: %d\n", __LINE__, __func__, uiRearIndex);

	ptPrintQNode = ptlinkedQHandle->ptFront;

    printf("linkedQ: %s\n", ptlinkedQHandle->pcName);
    printf("%04d: %04x ", uiIndex++, ptPrintQNode->ucData);
    while(1)
    {
        if (uiIndex % PRINT_BYTE_NUM == 0)
        {
            printf("\n");
        }

		ptPrintQNode = ptPrintQNode->ptLink;
        if (NULL == ptPrintQNode)
        {
            break;
        }
//printf("\n[%d][%s]\n", __LINE__, __func__);
		printf("%04d: %04x ", uiIndex++, ptPrintQNode->ucData);
    }
    printf("END\n");
}

// TODO, NOTE, XXX, BUG HACK, INFO, IDEA
// ERR

/* end of file */
