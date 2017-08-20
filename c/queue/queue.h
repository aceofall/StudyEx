/******************************************************************************
* File Name : queue.h
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

/******************************************************************************
* Global variables and structures
******************************************************************************/
typedef enum
{
    E_QUEUE_INIT,
    E_QUEUE_EMPTY,
    E_QUEUE_NOT_EMPTY,
    E_QUEUE_FULL
} QueueState_e;

typedef enum
{
    E_ERROR_NONE,
    E_ERROR_NOT_ENOUGH,
    E_ERROR_RANGE,
    E_ERROR_FULL,
    E_ERROR_EMPTY,
} QueueError_e;

typedef struct _queue
{
    char *pcName;
    QueueState_e eState;
    unsigned char *pcFront;
    unsigned char *pcRear;
    unsigned char *pcQueueBuffer;
    unsigned int uiQueueSize;
} Queue_t;

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
void init_queue (Queue_t *ptQueueHandle, char *pcName, unsigned char *pcBuf, unsigned int uiBufSize);
QueueError_e pushData_queue (Queue_t *ptQueueHandle, unsigned char *pcDataBuf, unsigned int uiDataSize);
QueueError_e getData_queue (Queue_t *ptQueueHandle, unsigned char *pcDataBuf, unsigned int uiDataSize);
unsigned int getUsedSize_queue (Queue_t *ptQueueHandle);
unsigned int getRemainSize_queue (Queue_t *ptQueueHandle);
unsigned char getData1Byte_queue(Queue_t *ptQueueHandle);
void clear_queue (Queue_t *ptQueueHandle);
void print_queue (Queue_t *ptQueueHandle);

/* end of file */
