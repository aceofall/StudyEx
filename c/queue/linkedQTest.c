/******************************************************************************
* File Name : linkedQTest.c
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
#include "linkedQ.h"

/******************************************************************************
* Debug level
******************************************************************************/

/******************************************************************************
* Definitions, typdef & const data
******************************************************************************/
#define QUEUE_MAX_NUM           200
#define QUEUE_TEST_DATA_NUM     100

/******************************************************************************
* Global variables and structures
******************************************************************************/
LinkedQ_t s_tLinkQ;

/******************************************************************************
* External variables and functions
******************************************************************************/

/******************************************************************************
* Static variables and structures
******************************************************************************/
unsigned char s_aucQueueBuffer[QUEUE_MAX_NUM];
unsigned char s_testBuffer[QUEUE_MAX_NUM/2];
char s_acTestData[] = "I am a programmer!, I want a big salary!! \
But it's not easy! Could you give more money!!!";

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
    unsigned char ucIndex = 0, ucPopData = 0;
    char *acName = "TEST_LINK_Q";

    init_linkedQ(&s_tLinkQ, acName);

    printf("Queue push start\n");
    for (ucIndex = 0; ucIndex < QUEUE_TEST_DATA_NUM; ucIndex++)
    {
        pushData_linkedQ(&s_tLinkQ, &ucIndex, 1);
    }
    printf("Queue push end\n\n");
    print_linkedQ(&s_tLinkQ);

    printf("Queue pop start\n");
    for (ucIndex = 0; ucIndex < QUEUE_TEST_DATA_NUM/2; ucIndex++)
    {
        ucPopData = getData1Byte_linkedQ(&s_tLinkQ);
    }
    printf("Queue pop end\n\n");
    print_linkedQ(&s_tLinkQ);

    pushData_linkedQ(&s_tLinkQ, s_acTestData, sizeof(s_acTestData));
    print_linkedQ(&s_tLinkQ);
    getData_linkedQ(&s_tLinkQ, s_testBuffer, QUEUE_MAX_NUM/2);

    printf("Queue Print Start\n");
    print_linkedQ(&s_tLinkQ);
    printf("Queue Print End\n\n");
}

// TODO, NOTE, XXX, BUG HACK, INFO, IDEA
// ERR

/* end of file */
