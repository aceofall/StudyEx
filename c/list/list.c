/******************************************************************************
* File Name : list.c
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
#include "list.h"

/******************************************************************************
* Debug level
******************************************************************************/

/******************************************************************************
* Definitions, typdef & const data
******************************************************************************/

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

/******************************************************************************
* Function :
* Description :
* Input :
* Output :
* Return :
******************************************************************************/
void init_listNode (ListNode_t *ptInitNode, char *pcName)
{
//printf("[%d][%s]\n", __LINE__, __func__);
    ptInitNode->pcName = pcName;
    ptInitNode->eNodeState = E_LIST_INIT;
    ptInitNode->ptPrev = ptInitNode;
    ptInitNode->ptNext = ptInitNode;
// printf("[%d][%s] pcName: %s\n", __LINE__, __func__, pcName);
}

static void _insert_listNode(ListNode_t *ptNewNode, ListNode_t *ptPrevNode, ListNode_t *ptNextNode)
{
    ptPrevNode->ptNext = ptNewNode;
    ptNewNode->ptPrev = ptPrevNode;
    ptNewNode->ptNext = ptNextNode;
    ptNextNode->ptPrev = ptNewNode;
}

void insert_listNode (ListNode_t *ptHeadNode, ListNode_t *ptNewNode)
{
//printf("[%d][%s]\n", __LINE__, __func__);
    _insert_listNode(ptNewNode, ptHeadNode, ptHeadNode->ptNext);
//printf("[%d][%s]\n", __LINE__, __func__);
    ptNewNode->eNodeState = E_LIST_INSERTED;
// printf("[%d][%s] name: %s\n", __LINE__, __func__, ptNewNode->pcName);
}

void insert_listNodeTail (ListNode_t *ptHeadNode, ListNode_t *ptNewNode)
{
    _insert_listNode(ptNewNode, ptHeadNode->ptPrev, ptHeadNode);
    ptNewNode->eNodeState = E_LIST_INSERTED;
}

static void _remove_listNode (ListNode_t *ptPrevNode, ListNode_t *ptNextNode)
{
    ptPrevNode->ptNext = ptNextNode;
    ptNextNode->ptPrev = ptPrevNode;
}

void remove_listNode (ListNode_t *ptPurgeNode)
{
    _remove_listNode(ptPurgeNode->ptPrev, ptPurgeNode->ptNext);
    ptPurgeNode->eNodeState = E_LIST_NOT_INSERTED;
    ptPurgeNode->ptNext = NULL;
    ptPurgeNode->ptPrev = NULL;
}

unsigned char isLast_listNode (ListNode_t *ptCheckNode, ListNode_t *ptListHeadNode, unsigned char ucPrintDirection)
{
    if (E_PRINT_CLOCKWISE == ucPrintDirection)
    {
        if (ptCheckNode->ptNext == ptListHeadNode)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (ptCheckNode->ptPrev == ptListHeadNode)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

unsigned char isEmpty_listNode (ListNode_t *ptListHeadNode)
{
    if (ptListHeadNode->ptNext == ptListHeadNode)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void print_listNode (ListNode_t *ptHeadNode, unsigned char ucPrintDirection)
{
    unsigned char ucIndex = 0;
    ListNode_t *ptTempNode = ptHeadNode;

    if (E_PRINT_CLOCKWISE == ucPrintDirection)
    {
        while(1)
        {
            printf("NODE: %s =>\n", ptTempNode->pcName);
            if (1 == isLast_listNode(ptTempNode, ptHeadNode, ucPrintDirection))
            {
                break;
            }
            ptTempNode = ptTempNode->ptNext;
        }
        printf("END\n");
    }
    else
    {
        while(1)
        {
            printf("<= NODE: %s\n", ptTempNode->pcName);
            if (1 == isLast_listNode(ptTempNode, ptHeadNode, ucPrintDirection))
            {
                break;
            }
            ptTempNode = ptTempNode->ptPrev;
        }
        printf("END\n");
    }
}

// TODO, NOTE, XXX, BUG HACK, INFO, IDEA
// ERR

/* end of file */
