/******************************************************************************
* File Name : listTest.c
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

#define TEST_LIST_NODE_NUM      10

/******************************************************************************
* Debug level
******************************************************************************/

/******************************************************************************
* Definitions, typdef & const data
******************************************************************************/

/******************************************************************************
* Global variables and structures
******************************************************************************/
ListNode_t s_tListNodeHead =
{
    .pcName = "HEAD",
    .eNodeState = E_LIST_HEAD,
    .ptPrev = &s_tListNodeHead,
    .ptNext = &s_tListNodeHead,
};

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

int main (void)
{
    unsigned char ucIndex = 0;
    char *aczNodeNames[TEST_LIST_NODE_NUM] = {"N_0", "N_1", "N_2", "N_3", "N_4",
                                              "N_5", "N_6", "N_7", "N_8", "N_9"};
    ListNode_t atTestNodes[TEST_LIST_NODE_NUM];

    printf("List Node Init & insert start\n");
    for (ucIndex = 0; ucIndex < TEST_LIST_NODE_NUM; ucIndex++)
    {
        init_listNode(&atTestNodes[ucIndex], aczNodeNames[ucIndex]);
        insert_listNode(&s_tListNodeHead, &atTestNodes[ucIndex]);
    }
    printf("List Node Init & insert End\n\n");

    printf("List Node Print Start-clockwise\n");
    print_listNode(&s_tListNodeHead, E_PRINT_CLOCKWISE);
    printf("List Node Print End\n\n");

    printf("List Node Print Start-counter clockwise\n");
    print_listNode(&s_tListNodeHead, E_PRINT_COUNTER_CLOCKWISE);
    printf("List Node Print End\n\n");

    printf("List Node Remove start\n");
    for (ucIndex = 0; ucIndex < TEST_LIST_NODE_NUM; ucIndex++)
    {
        remove_listNode(&atTestNodes[ucIndex]);
    }
    printf("List Node Remove End\n\n");

    printf("List Node Print Start-counter clockwise\n");
    print_listNode(&s_tListNodeHead, E_PRINT_COUNTER_CLOCKWISE);
    printf("List Node Print End\n\n");

    printf("List Node Init & insert Tail start\n");
    for (ucIndex = 0; ucIndex < TEST_LIST_NODE_NUM; ucIndex++)
    {
        init_listNode(&atTestNodes[ucIndex], aczNodeNames[ucIndex]);
        insert_listNodeTail(&s_tListNodeHead, &atTestNodes[ucIndex]);
    }
    printf("List Node Init & insert Tail End\n\n");

    printf("List Node Print Start-clockwise\n");
    print_listNode(&s_tListNodeHead, E_PRINT_CLOCKWISE);
    printf("List Node Print End\n\n");

    printf("List Node Remove start\n");
    for (ucIndex = 0; ucIndex < TEST_LIST_NODE_NUM; ucIndex++)
    {
        if (0 == (ucIndex % 2))
        {
            remove_listNode(&atTestNodes[ucIndex]);
        }
    }
    printf("List Node Remove End\n\n");

    printf("List Node Print Start-counter clockwise\n");
    print_listNode(&s_tListNodeHead, E_PRINT_COUNTER_CLOCKWISE);
    printf("List Node Print End\n\n");
}

// TODO, NOTE, XXX, BUG HACK, INFO, IDEA
// ERR

/* end of file */
