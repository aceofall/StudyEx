/******************************************************************************
* File Name : stackTest.c
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
#define TEST_STACK_NUM                  2
#define TEST_STACK_MEMSIZE              1024
#define TEST_PUSH_DATA_NUM              100

/******************************************************************************
* Global variables and structures
******************************************************************************/
static StackHandle_t s_tTestTopHdl, s_tTestBottomHdl;

/******************************************************************************
* External variables and functions
******************************************************************************/

/******************************************************************************
* Static variables and structures
******************************************************************************/
static unsigned char s_aucStackMemory[TEST_STACK_NUM][TEST_STACK_MEMSIZE];
static char s_cTestPattern[] = "TEST_PATTERN";
static char s_cTestData[10];

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
    char *aczStackNames[TEST_STACK_NUM] = {"STACK_TOPDOWN", "STACK_DOWNUP"};

    printf("Stack Create & init Start\n");
    create_stack(&s_tTestTopHdl, aczStackNames[E_STACK_TOPDOWN], E_STACK_TOPDOWN);
    init_stack (&s_tTestTopHdl, s_aucStackMemory[E_STACK_TOPDOWN], TEST_STACK_MEMSIZE);
    create_stack(&s_tTestBottomHdl, aczStackNames[E_STACK_DOWNUP], E_STACK_DOWNUP);
    init_stack (&s_tTestBottomHdl, s_aucStackMemory[E_STACK_DOWNUP], TEST_STACK_MEMSIZE);
    printf("Stack Create & init End\n");

    printf("Push Test Start\n");
    for (ucIndex = 0; ucIndex < TEST_PUSH_DATA_NUM; ucIndex++)
    {
        push_data (&s_tTestTopHdl, &ucIndex, 1);
        push_data (&s_tTestBottomHdl, &ucIndex, 1);
    }
    printf("Push Test End\n");

    print_stack(&s_tTestTopHdl);
    print_stack(&s_tTestBottomHdl);

    printf("Clear Test Start\n");
    clear_stack(&s_tTestTopHdl);
    clear_stack(&s_tTestBottomHdl);
    printf("Clear Test End\n");

    print_stack(&s_tTestTopHdl);
    print_stack(&s_tTestBottomHdl);

    printf("Push Pop Test Start\n");
    push_data (&s_tTestTopHdl, &s_cTestPattern[0], 1);
    print_stack(&s_tTestTopHdl);
    push_data (&s_tTestTopHdl, &s_cTestPattern[1], 1);
    print_stack(&s_tTestTopHdl);
    push_data (&s_tTestTopHdl, &s_cTestPattern[2], 1);
    print_stack(&s_tTestTopHdl);
    push_data (&s_tTestTopHdl, &s_cTestPattern[3], 1);
    print_stack(&s_tTestTopHdl);
    pop_data (&s_tTestTopHdl, &s_cTestData[0], 1);
    print_stack(&s_tTestTopHdl);
    pop_data (&s_tTestTopHdl, &s_cTestData[1], 1);
    print_stack(&s_tTestTopHdl);
    pop_data (&s_tTestTopHdl, &s_cTestData[2], 1);
    print_stack(&s_tTestTopHdl);
    pop_data (&s_tTestTopHdl, &s_cTestData[3], 1);
    print_stack(&s_tTestTopHdl);
    printf("Push Pop Test End\n");

}

// TODO, NOTE, XXX, BUG HACK, INFO, IDEA
// ERR

/* end of file */
