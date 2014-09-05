/// @file	memory_manager.h
///	@brief	메모리 관리 함수들을 정의한 헤더
///	@author Kimsuho
/// @date	March, 22, 2006
/// @par 메모리 관련 함수들을 모아놓을 생각이다.

///	@brief smalloc을 위한 버퍼 초기화
/// @remark 외부의 버퍼 포인터와 크기를 가져와서 버퍼를 초기화 시킨다.
/// @return 없음.
/// @par 요구사항: commontype.h가 필요함.

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
/// @brief smalloc을 위한 buffer를 초기화 한다.
/// @remark smalloc, sfree을 위한 buffer를, buffer pointer와 크기를 인자로 하여 초기화 한다.
/// @return NULL
void SMALLOC_CreateBuffer(void * buf, INT32U size);

/// @brief malloc과 비슷한 smalloc을 수행한다.
/// @remark size를 인자로 받아서, 초기화한 버퍼 중에 해당 크기 만큼을 리턴한다.
/// @return void *로 리턴하므로 호출하는 쪽에서는 형변환하여 사용.
void * smalloc(INT32U size);

/// @brief free와 비슷한 sfree를 수행한다.
/// @remark smalloc으로 할당받은 주소를 인자로 사용하여 해당 주소를 풀어준다.
/// @return 없음.
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
