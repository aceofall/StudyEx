/// @file	memory_manager.h
///	@brief	�޸� ���� �Լ����� ������ ���
///	@author Kimsuho
/// @date	March, 22, 2006
/// @par �޸� ���� �Լ����� ��Ƴ��� �����̴�.

///	@brief smalloc�� ���� ���� �ʱ�ȭ
/// @remark �ܺ��� ���� �����Ϳ� ũ�⸦ �����ͼ� ���۸� �ʱ�ȭ ��Ų��.
/// @return ����.
/// @par �䱸����: commontype.h�� �ʿ���.

#ifndef __MEMORY_MANAGER_H__
#define __MEMORY_MANAGER_H__

//queue
typedef struct queue_t
{
    INT8U * pBuf;
    INT32U size;
    INT8U * rp;
    INT8U * wp;
}QUEUE_T;

#if 0
/// @brief smalloc�� ���� buffer�� �ʱ�ȭ �Ѵ�.
/// @remark smalloc, sfree�� ���� buffer��, buffer pointer�� ũ�⸦ ���ڷ� �Ͽ� �ʱ�ȭ �Ѵ�.
/// @return NULL
void SMALLOC_CreateBuffer(void * buf, INT32U size);

/// @brief malloc�� ����� smalloc�� �����Ѵ�.
/// @remark size�� ���ڷ� �޾Ƽ�, �ʱ�ȭ�� ���� �߿� �ش� ũ�� ��ŭ�� �����Ѵ�.
/// @return void *�� �����ϹǷ� ȣ���ϴ� �ʿ����� ����ȯ�Ͽ� ���.
void * smalloc(INT32U size);

/// @brief free�� ����� sfree�� �����Ѵ�.
/// @remark smalloc���� �Ҵ���� �ּҸ� ���ڷ� ����Ͽ� �ش� �ּҸ� Ǯ���ش�.
/// @return ����.
void sfree(INT8U * p_addr);
#else
void SMALLOC_CreateBufferEx(int ch_id, void * buf, INT32U size);
void * smallocEx(int ch_id, INT32U real_size);
void sfreeEx(int ch_id, INT8U * p_addr);
void * sreallocEx(int ch_id, INT8U * pBuf, INT32U real_size);
#endif

void QUEUE_Init(QUEUE_T * myqueue, INT8U * pBuf, INT32U size);
int QUEUE_PutData(QUEUE_T * myqueue, INT8U * data, INT32U size);
int QUEUE_GetData(QUEUE_T * myqueue, INT8U * data, INT32U size);
int QUEUE_GetRemainSize(QUEUE_T * myqueue);
int QUEUE_GetStoredSize(QUEUE_T * myqueue);

int GetBitsEx(INT8U * pBuf, int start_bit_pos, int bit_num);
#endif
