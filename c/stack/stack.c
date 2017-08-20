/******************************************************************************
* File Name : stack.c
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
#include "stack.h"

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
static void stack_memcpy (StackType_e eType, void *pvDest, const void *pvSrc, unsigned int uiSize);
static void stack_memset (StackType_e eType, void *pvSrc, int iData, unsigned int uiSize);

/******************************************************************************
* Function :
* Description :
* Input :
* Output :
* Return :
******************************************************************************/
//printf("[%d][%s]\n", __LINE__, __func__);

void create_stack (StackHandle_t *ptStackHandle, char *pcName, StackType_e eType)
{
    ptStackHandle->pcStackName = pcName;
    ptStackHandle->eStackState = E_STACK_NONE;
    ptStackHandle->eStackType = eType;
}

void init_stack (StackHandle_t *ptStackHandle, unsigned char *pucBuffer, unsigned int uiBufferSize)
{
    ptStackHandle->eStackState = E_STACK_INIT;
    ptStackHandle->pucStackBuffer = pucBuffer;
    ptStackHandle->uiStackBufferSize = uiBufferSize;

    if (E_STACK_TOPDOWN == ptStackHandle->eStackType)
    {
        ptStackHandle->pucStackPointer = pucBuffer;
    }
    else
    {
        ptStackHandle->pucStackPointer = pucBuffer + uiBufferSize;
    }
}

void clear_stack (StackHandle_t *ptStackHandle)
{
    ptStackHandle->eStackState = E_STACK_EMPTY;
    stack_memset (ptStackHandle->eStackType, ptStackHandle->pucStackBuffer, 0, ptStackHandle->uiStackBufferSize);

    if (E_STACK_TOPDOWN == ptStackHandle->eStackType)
    {
        ptStackHandle->pucStackPointer = ptStackHandle->pucStackBuffer;
    }
    else
    {
        ptStackHandle->pucStackPointer = ptStackHandle->pucStackBuffer + ptStackHandle->uiStackBufferSize;
    }
}

static void stack_memcpy (StackType_e eType, void *pvDest, const void *pvSrc, unsigned int uiSize)
{
    unsigned char *pucSrc, *pucDest;

    pucSrc = (unsigned char *)pvSrc;
    pucDest = (unsigned char *)pvDest;

    if (E_STACK_TOPDOWN == eType)
    {
        while (uiSize--)
        {
            *pucDest++ = *pucSrc++;
        }
    }
    else
    {
        while (uiSize--)
        {
            *pucDest-- = *pucSrc++;
        }
    }
}

static void stack_memset (StackType_e eType, void *pvSrc, int iData, unsigned int uiSize)
{
    unsigned char *pucSrc;

    pucSrc = (unsigned char *)pvSrc;

    if (E_STACK_TOPDOWN == eType)
    {
        while (uiSize--)
        {
            *pucSrc++ = iData;
        }
    }
    else
    {
        while (uiSize--)
        {
            *pucSrc-- = iData;
        }
    }
}

StackError_e push_data (StackHandle_t *ptStackHandle, void *pvPushData, unsigned int uiPushSize)
{
    if (E_STACK_TOPDOWN == ptStackHandle->eStackType)
    {
        if ((ptStackHandle->pucStackPointer + uiPushSize) <= (ptStackHandle->pucStackBuffer + ptStackHandle->uiStackBufferSize))
        {
            stack_memcpy (E_STACK_TOPDOWN, ptStackHandle->pucStackPointer, pvPushData, uiPushSize);
            ptStackHandle->pucStackPointer += uiPushSize;

            if (ptStackHandle->pucStackPointer == (ptStackHandle->pucStackBuffer + ptStackHandle->uiStackBufferSize))
            {
                ptStackHandle->eStackState = E_STACK_FULL;
            }
            else
            {
                ptStackHandle->eStackState = E_STACK_NOT_EMPTY;
            }
        }
        else
        {
            return E_ERROR_SIZE;
        }
    }
    else
    {
        if ((ptStackHandle->pucStackPointer - uiPushSize) >= (ptStackHandle->pucStackBuffer))
        {
            stack_memcpy (E_STACK_DOWNUP, ptStackHandle->pucStackPointer, pvPushData, uiPushSize);
            ptStackHandle->pucStackPointer -= uiPushSize;

            if (ptStackHandle->pucStackPointer == ptStackHandle->pucStackBuffer)
            {
                ptStackHandle->eStackState = E_STACK_FULL;
            }
            else
            {
                ptStackHandle->eStackState = E_STACK_NOT_EMPTY;
            }
        }
        else
        {
            return E_ERROR_SIZE;
        }
    }

    return E_ERROR_NONE;
}

StackError_e pop_data (StackHandle_t *ptStackHandle, void *pvPopData, unsigned int uiPopSize)
{
    unsigned int uiUseSize = 0;

    if (E_STACK_TOPDOWN == ptStackHandle->eStackType)
    {
        uiUseSize = ptStackHandle->pucStackPointer - ptStackHandle->pucStackBuffer;

        if (uiUseSize >= uiPopSize)
        {
            stack_memcpy (E_STACK_TOPDOWN, pvPopData, ptStackHandle->pucStackPointer, uiPopSize);
            ptStackHandle->pucStackPointer -= uiPopSize;

            if (ptStackHandle->pucStackPointer == ptStackHandle->pucStackBuffer)
            {
                ptStackHandle->eStackState = E_STACK_EMPTY;
            }
            else
            {
                ptStackHandle->eStackState = E_STACK_NOT_EMPTY;
            }
        }
        else
        {
            return E_ERROR_SIZE;
        }
    }
    else
    {
        uiUseSize = (ptStackHandle->pucStackBuffer + ptStackHandle->uiStackBufferSize) - ptStackHandle->pucStackPointer;

        if (uiUseSize >= uiPopSize)
        {
            stack_memcpy (E_STACK_DOWNUP, pvPopData, ptStackHandle->pucStackPointer, uiPopSize);
            ptStackHandle->pucStackPointer += uiPopSize;

            if (ptStackHandle->pucStackPointer == (ptStackHandle->pucStackBuffer + ptStackHandle->uiStackBufferSize))
            {
                ptStackHandle->eStackState = E_STACK_EMPTY;
            }
            else
            {
                ptStackHandle->eStackState = E_STACK_NOT_EMPTY;
            }
        }
        else
        {
            return E_ERROR_SIZE;
        }
    }

    return E_ERROR_NONE;
}

void print_stack (StackHandle_t *ptStackHandle)
{
    unsigned int uiIndex = 0;
    unsigned int uiUsedSize = 0;

    if (E_STACK_TOPDOWN == ptStackHandle->eStackType)
    {
        uiUsedSize = ptStackHandle->pucStackPointer - ptStackHandle->pucStackBuffer;
    }
    else
    {
        uiUsedSize = ptStackHandle->pucStackBuffer + ptStackHandle->uiStackBufferSize - ptStackHandle->pucStackPointer;
    }

    if (0 == uiUsedSize)
    {
        printf("Stack: [%s] is Empty\n", ptStackHandle->pcStackName);
        return;
    }

    printf("Stack: [%s] Display Start\n", ptStackHandle->pcStackName);

    if (E_STACK_TOPDOWN == ptStackHandle->eStackType)
    {
        printf("0x%p: %04x ", &ptStackHandle->pucStackBuffer[0], ptStackHandle->pucStackBuffer[0]);
        for (uiIndex = 1; uiIndex < uiUsedSize; uiIndex++)
        {
            if (uiIndex % PRINT_BYTE_NUM == 0)
            {
                printf("\n");
            }
            printf("0x%p: %04x ", &ptStackHandle->pucStackBuffer[uiIndex], ptStackHandle->pucStackBuffer[uiIndex]);
        }
    }
    else
    {
        printf("0x%p: %04x ", &ptStackHandle->pucStackBuffer[ptStackHandle->uiStackBufferSize], ptStackHandle->pucStackBuffer[ptStackHandle->uiStackBufferSize]);
        for (uiIndex = 1; uiIndex < uiUsedSize; uiIndex++)
        {
            if (uiIndex % PRINT_BYTE_NUM == 0)
            {
                printf("\n");
            }
            printf("0x%p: %04x ", &ptStackHandle->pucStackBuffer[ptStackHandle->uiStackBufferSize - uiIndex], ptStackHandle->pucStackBuffer[ptStackHandle->uiStackBufferSize - uiIndex]);
        }
    }
    printf("\nStack: [%s] Display End\n", ptStackHandle->pcStackName);
    fflush(stdout);
}

// TODO, NOTE, XXX, BUG HACK, INFO, IDEA
// ERR

/* end of file */
