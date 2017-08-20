/******************************************************************************
* File Name : stack.h
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
typedef struct _stack StackHandle_t;

/******************************************************************************
* Global variables and structures
******************************************************************************/
typedef enum
{
    E_STACK_NONE,
    E_STACK_INIT,
    E_STACK_EMPTY,
    E_STACK_NOT_EMPTY,
    E_STACK_FULL,
} StackState_e;

typedef enum
{
    E_STACK_TOPDOWN,
    E_STACK_DOWNUP
} StackType_e;

typedef enum
{
    E_ERROR_NONE,
    E_ERROR_SIZE
} StackError_e;

struct _stack
{
    char *pcStackName;
    StackState_e eStackState;
    StackType_e eStackType;
    unsigned char *pucStackBuffer;
    unsigned char *pucStackPointer;
    unsigned int uiStackBufferSize;
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
void create_stack (StackHandle_t *ptStackHandle, char *pcName, StackType_e eType);
void init_stack (StackHandle_t *ptStackHandle, unsigned char *pucBuffer, unsigned int uiBufferSize);
void clear_stack (StackHandle_t *ptStackHandle);
StackError_e pop_data (StackHandle_t *ptStackHandle, void *pvPopData, unsigned int uiPopSize);
StackError_e push_data (StackHandle_t *ptStackHandle, void *pvPushData, unsigned int uiPushSize);
void print_stack (StackHandle_t *ptStackHandle);

/* end of file */
