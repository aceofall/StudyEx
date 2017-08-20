/******************************************************************************
* File Name : queue.c
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

/* local header files */
#include "queue.h"

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
static void queue_memcpy (void *pvDest, const void *pvSrc, unsigned int uiSize);
static void queue_memset (void *pvSrc, int iData, unsigned int uiSize);

/******************************************************************************
* Function :
* Description :
* Input :
* Output :
* Return :
******************************************************************************/
//printf("[%d][%s]\n", __LINE__, __func__);
void init_queue (Queue_t *ptQueueHandle, char *pcName, unsigned char *pcBuf, unsigned int uiBufSize)
{
    ptQueueHandle->pcName = pcName;
    ptQueueHandle->eState = E_QUEUE_INIT;
    ptQueueHandle->pcQueueBuffer = pcBuf;
    ptQueueHandle->uiQueueSize = uiBufSize;
    ptQueueHandle->pcFront = ptQueueHandle->pcRear = pcBuf;
}

void clear_queue (Queue_t *ptQueueHandle)
{
    ptQueueHandle->eState = E_QUEUE_EMPTY;
    ptQueueHandle->pcFront = ptQueueHandle->pcQueueBuffer;
    ptQueueHandle->pcRear = ptQueueHandle->pcQueueBuffer;
}

static void queue_memcpy (void *pvDest, const void *pvSrc, unsigned int uiSize)
{
    unsigned char *pucSrc, *pucDest;

    pucSrc = (unsigned char *)pvSrc;
    pucDest = (unsigned char *)pvDest;

    while (uiSize--)
    {
        *pucDest++ = *pucSrc++;
    }
}

static void queue_memset (void *pvSrc, int iData, unsigned int uiSize)
{
    unsigned char *pucSrc;

    pucSrc = (unsigned char *)pvSrc;

    while (uiSize--)
    {
        *pucSrc++ = iData;
    }
}

QueueError_e pushData_queue (Queue_t *ptQueueHandle, unsigned char *pcDataBuf, unsigned int uiDataSize)
{
    unsigned int uiQueueFragSize = 0;

    // Push Size Over!!
    if (uiDataSize > ptQueueHandle->uiQueueSize)
    {
        return E_ERROR_RANGE;
    }

    if ((ptQueueHandle->pcRear + uiDataSize) < (ptQueueHandle->pcQueueBuffer + ptQueueHandle->uiQueueSize))
    {
        // Just normal push case
        queue_memcpy(ptQueueHandle->pcRear, pcDataBuf, uiDataSize);

        if ((ptQueueHandle->pcRear < ptQueueHandle->pcFront) && ((ptQueueHandle->pcRear + uiDataSize) > ptQueueHandle->pcFront)) {
            ptQueueHandle->pcRear += uiDataSize;
            ptQueueHandle->pcFront = ptQueueHandle->pcRear + 1;
            ptQueueHandle->eState = E_QUEUE_FULL;
        } else {
            ptQueueHandle->pcRear += uiDataSize;
            ptQueueHandle->eState = E_QUEUE_NOT_EMPTY;
        }
        return E_ERROR_NONE;
    } else {
        // Circular push case
        uiQueueFragSize = ptQueueHandle->pcQueueBuffer + ptQueueHandle->uiQueueSize - ptQueueHandle->pcRear;
        queue_memcpy(ptQueueHandle->pcRear, pcDataBuf, uiQueueFragSize);
        queue_memcpy(ptQueueHandle->pcQueueBuffer, pcDataBuf + uiQueueFragSize, uiDataSize - uiQueueFragSize);

        if (ptQueueHandle->pcRear < ptQueueHandle->pcFront) {
            ptQueueHandle->pcRear = ptQueueHandle->pcQueueBuffer + uiDataSize - uiQueueFragSize;
            ptQueueHandle->pcFront = ptQueueHandle->pcRear + 1;
            ptQueueHandle->eState = E_QUEUE_FULL;
        } else {
            // Move to new rear position
            ptQueueHandle->pcRear = ptQueueHandle->pcQueueBuffer + uiDataSize - uiQueueFragSize;

            // Is full?
            if (ptQueueHandle->pcRear > ptQueueHandle->pcFront) {
                ptQueueHandle->pcFront = ptQueueHandle->pcRear + 1;
                ptQueueHandle->eState = E_QUEUE_FULL;
            } else {
                ptQueueHandle->eState = E_QUEUE_NOT_EMPTY;
            }
        }
        return E_ERROR_NONE;
    }
    return E_ERROR_NONE;
}

QueueError_e getData_queue (Queue_t *ptQueueHandle, unsigned char *pcDataBuf, unsigned int uiDataSize)
{
    unsigned int uiRemainSize = 0, uiUsedSize = 0, uiQueueFragSize = 0;

    uiUsedSize = getUsedSize_queue(ptQueueHandle);
    if (uiUsedSize < uiDataSize) {
        return E_ERROR_RANGE;
    }

    if (ptQueueHandle->pcFront + uiDataSize < ptQueueHandle->pcQueueBuffer + ptQueueHandle->uiQueueSize) {
        // Just normal pop case
        queue_memcpy(pcDataBuf, ptQueueHandle->pcFront, uiDataSize);
        ptQueueHandle->pcFront += uiDataSize;
        if (ptQueueHandle->pcRear <= ptQueueHandle->pcFront) {
            ptQueueHandle->pcRear = ptQueueHandle->pcFront;
            ptQueueHandle->eState = E_QUEUE_EMPTY;
        } else {
            ptQueueHandle->eState = E_QUEUE_NOT_EMPTY;
        }
        return E_ERROR_NONE;
    } else {
        // Circular pop case
        uiQueueFragSize = ptQueueHandle->pcQueueBuffer + ptQueueHandle->uiQueueSize - ptQueueHandle->pcFront;
        queue_memcpy(pcDataBuf, ptQueueHandle->pcFront, uiQueueFragSize);
        queue_memcpy(ptQueueHandle->pcQueueBuffer, pcDataBuf + uiQueueFragSize, uiDataSize - uiQueueFragSize);

        // Move to new front position
        ptQueueHandle->pcFront = ptQueueHandle->pcQueueBuffer + uiDataSize - uiQueueFragSize;

        if (ptQueueHandle->pcFront < ptQueueHandle->pcRear) {
            ptQueueHandle->eState = E_QUEUE_NOT_EMPTY;
        } else {
            // front is same to rear
            ptQueueHandle->pcRear = ptQueueHandle->pcFront;
            ptQueueHandle->eState = E_QUEUE_EMPTY;
        }
        return E_ERROR_NONE;
    }
    return E_ERROR_NONE;
}

unsigned char getData1Byte_queue(Queue_t *ptQueueHandle)
{
    unsigned char ucData = 0;

    getData_queue (ptQueueHandle, &ucData, 1);

    return ucData;
}

unsigned int getUsedSize_queue (Queue_t *ptQueueHandle)
{
    unsigned int uiUsedSize = 0;

    if ((ptQueueHandle->pcRear - ptQueueHandle->pcFront) > 0) {
        uiUsedSize = ptQueueHandle->pcRear - ptQueueHandle->pcFront;
    } else {
        uiUsedSize = ptQueueHandle->uiQueueSize + ptQueueHandle->pcRear - ptQueueHandle->pcFront;
    }

    return uiUsedSize;
}

unsigned int getRemainSize_queue (Queue_t *ptQueueHandle)
{
    unsigned int uiRemainSize = 0;

    if ((ptQueueHandle->pcRear - ptQueueHandle->pcFront) > 0) {
        uiRemainSize = ptQueueHandle->uiQueueSize - (ptQueueHandle->pcRear - ptQueueHandle->pcFront);
    } else {
        uiRemainSize = ptQueueHandle->uiQueueSize + (ptQueueHandle->pcRear - ptQueueHandle->pcFront);
    }

    return uiRemainSize;
}

void print_queue (Queue_t *ptQueueHandle)
{
    unsigned int uiIndex = 0, uiFrontIndex = 0, uiRearIndex = 0;
    unsigned int uiUsedSize = 0;

    uiUsedSize = getUsedSize_queue(ptQueueHandle);
    uiFrontIndex = ptQueueHandle->pcFront - ptQueueHandle->pcQueueBuffer;
    uiRearIndex = ptQueueHandle->pcRear - ptQueueHandle->pcQueueBuffer;

// printf("[%d][%s] uiFrontIndex: %d\n", __LINE__, __func__, uiFrontIndex);
// printf("[%d][%s] uiRearIndex: %d\n", __LINE__, __func__, uiRearIndex);

    printf("QUEUE: %s\n", ptQueueHandle->pcName);
    printf("%04d: %04x(%c) ", uiIndex++, *(ptQueueHandle->pcFront + uiIndex), *(ptQueueHandle->pcFront + uiIndex));
    while(1)
    {
        if (uiIndex % PRINT_BYTE_NUM == 0)
        {
            printf("\n");
        }
        printf("%04d: %04x(%c) ", uiIndex, *(ptQueueHandle->pcFront + uiIndex), *(ptQueueHandle->pcFront + uiIndex));
        uiIndex++;

        if ((uiFrontIndex + uiIndex) % ptQueueHandle->uiQueueSize == uiRearIndex)
        {
            break;
        }
    }
    printf("END\n");
}

// TODO, NOTE, XXX, BUG HACK, INFO, IDEA
// ERR

/* end of file */
