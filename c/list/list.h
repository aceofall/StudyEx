/******************************************************************************
* File Name : list.h
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

/* local header files */

/******************************************************************************
* Debug level
******************************************************************************/

/******************************************************************************
* Definitions, typdef & const data
******************************************************************************/
typedef struct _node ListNode_t;

/******************************************************************************
* Global variables and structures
******************************************************************************/
typedef enum
{
    E_LIST_INIT,
    E_LIST_INSERTED,
    E_LIST_NOT_INSERTED,
    E_LIST_HEAD
} ListState_e;

enum
{
    E_PRINT_CLOCKWISE,
    E_PRINT_COUNTER_CLOCKWISE
};

struct _node
{
    char *pcName;
    ListState_e eNodeState;
    ListNode_t *ptPrev;
    ListNode_t *ptNext;
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
void init_listNode (ListNode_t *ptInitNode, char *pcName);
void insert_listNode (ListNode_t *ptHeadNode, ListNode_t *ptNewNode);
void insert_listNodeTail (ListNode_t *ptHeadNode, ListNode_t *ptNewNode);
void remove_listNode (ListNode_t *ptPurgeNode);
unsigned char isLast_listNode (ListNode_t *ptCheckNode, ListNode_t *ptListHeadNode, unsigned char ucPrintDirection);
unsigned char isEmpty_listNode (ListNode_t *ptCheckNode);
void print_listNode (ListNode_t *ptHeadNode, unsigned char ucPrintDirection);

/* end of file */
