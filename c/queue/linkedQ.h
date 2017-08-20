/******************************************************************************
* File Name : linkedQ.h
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
typedef struct _QNode QNode_t;
typedef struct _linkedQ LinkedQ_t;

/******************************************************************************
* Global variables and structures
******************************************************************************/
typedef enum
{
    E_LINKED_Q_INIT,
    E_LINKED_Q_EMPTY,
    E_LINKED_Q_NOT_EMPTY,
    E_LINKED_Q_FULL
} LinkedQState_e;

typedef enum
{
    E_ERROR_NONE,
    E_ERROR_NOT_ENOUGH,
    E_ERROR_RANGE,
    E_ERROR_FULL,
    E_ERROR_EMPTY,
} LinkedQError_e;

struct _QNode
{
    unsigned char ucData;
    QNode_t *ptLink;
};

struct _linkedQ
{
    char *pcName;
    LinkedQState_e eState;
    QNode_t *ptFront;
    QNode_t *ptRear;
    unsigned int uiUsedQSize;
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
void init_linkedQ (LinkedQ_t *ptlinkedQHandle, char *pcName);
LinkedQError_e pushData_linkedQ (LinkedQ_t *ptlinkedQHandle, unsigned char *pcDataBuf, unsigned int uiDataSize);
LinkedQError_e getData_linkedQ (LinkedQ_t *ptlinkedQHandle, unsigned char *pcDataBuf, unsigned int uiDataSize);
unsigned int getUsedSize_linkedQ (LinkedQ_t *ptlinkedQHandle);
unsigned char getData1Byte_linkedQ(LinkedQ_t *ptlinkedQHandle);
void clear_linkedQ (LinkedQ_t *ptlinkedQHandle);
void print_linkedQ (LinkedQ_t *ptlinkedQHandle);

/* end of file */
