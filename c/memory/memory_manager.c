//
//	메모리 관리 함수들을 모아 놓은 파일.
//	smalloc이 구현되어 있다.
//

#include "memory_manager.h"

#define MAL_MARK "MAL"	// smalloc의 헤더인지 나타내는 MARK
#define MAL_LENGTH 3	// MARK의 길이

//smalloc 구조체의 헤더
//할당된 구조 안에서 메모리 관리를 위한 구조체이다.

typedef struct struct_heap
{
    INT8U ID[3];					// 선택된 메모리 위치가 헤더인지 구분하는 MARK
    INT8U is_alloc;				// alloc인지 free인지 구분
    struct struct_heap * next;	// 다음에 할당된 list검색
}HEAP_T;

void QUEUE_Init(QUEUE_T * myqueue, INT8U * pBuf, INT32U size)
{
    myqueue->pBuf = myqueue->rp = myqueue->wp = pBuf;
    myqueue->size = size;
}

int QUEUE_PutData(QUEUE_T * myqueue, INT8U * data, INT32U size)
{
    int write_size;

    if((INT32U)QUEUE_GetRemainSize(myqueue) < size)
        return 0;

    if(myqueue->wp + size < myqueue->pBuf + myqueue->size)
    {
        dab_memcpy(myqueue->wp, data, size);
        myqueue->wp += size;
    }
    else
    {
        write_size = myqueue->pBuf + myqueue->size - myqueue->wp;
        dab_memcpy(myqueue->wp, data, write_size);
        dab_memcpy(myqueue->pBuf, &data[write_size], size - write_size);
        myqueue->wp = myqueue->pBuf + size - write_size;
    }

    return size;
}

int QUEUE_GetData(QUEUE_T * myqueue, INT8U * data, INT32U size)
{
    int read_size;

    if((INT32U)QUEUE_GetStoredSize(myqueue) < size)
        return 0;

    if(myqueue->rp + size > myqueue->pBuf + myqueue->size)
    {
        read_size = myqueue->pBuf + myqueue->size - myqueue->rp;
        dab_memcpy(data, myqueue->rp, read_size);
        dab_memcpy(&data[read_size], myqueue->pBuf, size - read_size);
        myqueue->rp = myqueue->pBuf + size - read_size;
    }
    else
    {
        dab_memcpy(data, myqueue->rp, size);
        myqueue->rp += size;
    }

    return size;
}

int QUEUE_GetRemainSize(QUEUE_T * myqueue)
{
    if(myqueue->wp >= myqueue->rp)
    {
        return (int)(myqueue->size - (myqueue->wp - myqueue->rp)); //myqueue->pBuf + size - myqueue->wp + myqueue->rp - myqueue->pBuf
    }
    else
    {
        return (int)(myqueue->rp - myqueue->wp);
    }
}

int QUEUE_GetStoredSize(QUEUE_T * myqueue)
{
    if(myqueue->wp < myqueue->rp)
    {
        return (int)(myqueue->size - (myqueue->rp - myqueue->wp));
    }
    else
    {
        return (int)(myqueue->wp - myqueue->rp);
    }
}

#if 0
static HEAP_T * p_heap_start = NULL;
static INT32U heap_size = 0;

void SMALLOC_CreateBuffer(void * buf, INT32U size)
{
    p_heap_start = buf;
    heap_size = size;

    dab_memcpy(p_heap_start->ID, MAL_MARK, MAL_LENGTH);
    p_heap_start->is_alloc = 0;
    p_heap_start->next = (HEAP_T *)((INT8U *)p_heap_start + heap_size - sizeof(HEAP_T));

    dab_memcpy((p_heap_start->next)->ID, MAL_MARK, MAL_LENGTH);
    (p_heap_start->next)->is_alloc = 1;
    (p_heap_start->next)->next = NULL;
}

#if 0
INT8U * SMALLOC_ResizeBuffer(int size)
{
    HEAP_T * end_pos;

    if( (INT8U *)p_heap_start == (INT8U *)srealloc(p_heap_start, heap_size + size))
    {
        end_pos = (HEAP_T *)((INT8U *)p_heap_start + heap_size - sizeof(HEAP_T));
        end_pos->is_alloc = 0;
        end_pos->next = (INT8U *)end_pos + size;

        dab_memcpy((end_pos->next)->ID, MAL_MARK, MAL_LENGTH);
        (end_pos->next)->is_alloc = 1;
        (end_pos->next)->next = NULL;

        heap_size = size;

        return p_heap_start;
    }
    else
    {
        return NULL;
    }
}
#endif

void * smalloc(INT32U real_size)
{
    HEAP_T * cur_pos;
    HEAP_T * freebuf_start;
    HEAP_T * backup_next;
    INT32U size;

    size = (real_size + 3) & 0xfffffffcul;

    cur_pos = p_heap_start;
    freebuf_start = NULL;

    while(1)
    {
        if(cur_pos->is_alloc == 0)
        {
            if(freebuf_start == 0)
                freebuf_start = cur_pos;

            if(dab_memcmp((cur_pos->next)->ID, MAL_MARK, MAL_LENGTH))
                return NULL;

            //size만큼 잡고 중간에 header를 붙일 공간도 필요함.
            if( (INT32U)((INT8U*)cur_pos->next - (INT8U*)freebuf_start) >= size + sizeof(HEAP_T))
                break;
        }
        else
            freebuf_start = NULL;

        cur_pos = cur_pos->next;

        if(cur_pos->next == NULL)
            return NULL;
    }

    //중간에 헤더를 하나 더 만들 여유가 있으면 만든다.
    if( (INT32U)((INT8U*)cur_pos->next - (INT8U*)freebuf_start) > size + 2 * sizeof(HEAP_T))
    {
        freebuf_start->is_alloc = 1;
        backup_next = cur_pos->next;
        freebuf_start->next = (HEAP_T *)((INT8U *)freebuf_start + size + sizeof(HEAP_T));

        dab_memcpy((freebuf_start->next)->ID, MAL_MARK, MAL_LENGTH);
        ((HEAP_T *)freebuf_start->next)->is_alloc = 0;
        ((HEAP_T *)freebuf_start->next)->next = backup_next;
    }
    //만들 여유가 없으면 그냥 여분의 메모리 공간을 남기지만 할당한다.
    else
    {
        freebuf_start->is_alloc = 1;
        freebuf_start->next = cur_pos->next;
    }

    return (INT8U *)freebuf_start + sizeof(HEAP_T);
}

void sfree(INT8U * p_addr)
{
    HEAP_T * cur_pos;

    if((INT32U)p_addr < (INT32U)p_heap_start )
        return;

    cur_pos = (HEAP_T *)(p_addr - sizeof(HEAP_T));

    if(dab_memcmp(cur_pos->ID, MAL_MARK, MAL_LENGTH))
        return;

    cur_pos->is_alloc = 0;
}
#endif

/////////////////////////////////////////////////////////////////////////
//ex
typedef struct
{
    HEAP_T * p_heap_start;
    INT32U heap_size;
    HEAP_T * p_curHeap;
}SMALLOC_T;

static SMALLOC_T smalloc_t[MAX_CH_NUM + 1];

void SMALLOC_CreateBufferEx(int ch_id, void * buf, INT32U size)
{
    smalloc_t[ch_id].p_heap_start = smalloc_t[ch_id].p_curHeap = buf;
    smalloc_t[ch_id].heap_size = size;

    dab_memcpy(smalloc_t[ch_id].p_heap_start->ID, MAL_MARK, MAL_LENGTH);
    smalloc_t[ch_id].p_heap_start->is_alloc = 0;
    smalloc_t[ch_id].p_heap_start->next = (HEAP_T *)((INT8U *)(smalloc_t[ch_id].p_heap_start) + smalloc_t[ch_id].heap_size - sizeof(HEAP_T));

    dab_memcpy((smalloc_t[ch_id].p_heap_start->next)->ID, MAL_MARK, MAL_LENGTH);
    (smalloc_t[ch_id].p_heap_start->next)->is_alloc = 1;
    (smalloc_t[ch_id].p_heap_start->next)->next = NULL;
}

void * smallocEx(int ch_id, INT32U real_size)
{
    int ret;
    HEAP_T * cur_pos;
    HEAP_T * freebuf_start;
    HEAP_T * backup_next;
    INT32U size;

    if(real_size == 0)
        return NULL;

    size = (real_size + 3) & 0xfffffffcul;

    cur_pos = smalloc_t[ch_id].p_curHeap;
    freebuf_start = NULL;
    ret = 1;

    while(1)
    {
        if(cur_pos->is_alloc == 0)
        {
            if(freebuf_start == 0)
                freebuf_start = cur_pos;

            if(dab_memcmp((cur_pos->next)->ID, MAL_MARK, MAL_LENGTH))
            {
                ret= 0;
                goto END_OF_FUNC;
            }

            //size만큼 잡고 중간에 header를 붙일 공간도 필요함.
            if( (INT32U)((INT8U*)cur_pos->next - (INT8U*)freebuf_start) >= size + sizeof(HEAP_T))
                break;
        }
        else
            freebuf_start = NULL;

        cur_pos = cur_pos->next;

        if(cur_pos->next == NULL)
        {
            ret= 0;
            goto END_OF_FUNC;
        }
    }

    //중간에 헤더를 하나 더 만들 여유가 있으면 만든다.
    if( (INT32U)((INT8U*)cur_pos->next - (INT8U*)freebuf_start) > size + 2 * sizeof(HEAP_T))
    {
        freebuf_start->is_alloc = 1;
        backup_next = cur_pos->next;
        freebuf_start->next = (HEAP_T *)((INT8U *)freebuf_start + size + sizeof(HEAP_T));

        dab_memcpy((freebuf_start->next)->ID, MAL_MARK, MAL_LENGTH);
        ((HEAP_T *)freebuf_start->next)->is_alloc = 0;
        ((HEAP_T *)freebuf_start->next)->next = backup_next;
    }
    //만들 여유가 없으면 그냥 여분의 메모리 공간을 남기지만 할당한다.
    else
    {
        freebuf_start->is_alloc = 1;
        freebuf_start->next = cur_pos->next;
    }

END_OF_FUNC:
    if(ret)
    {
        smalloc_t[ch_id].p_curHeap = freebuf_start;
        return (INT8U *)freebuf_start + sizeof(HEAP_T);
    }

    smalloc_t[ch_id].p_curHeap = smalloc_t[ch_id].p_heap_start->next;
    return NULL;

}

void sfreeEx(int ch_id, INT8U * p_addr)
{
    HEAP_T * cur_pos;

    if((INT32U)p_addr < (INT32U)smalloc_t[ch_id].p_heap_start )
        return;

    cur_pos = (HEAP_T *)(p_addr - sizeof(HEAP_T));

    if(dab_memcmp(cur_pos->ID, MAL_MARK, MAL_LENGTH))
        return;

    smalloc_t[ch_id].p_curHeap = smalloc_t[ch_id].p_heap_start;
    cur_pos->is_alloc = 0;
}

void * sreallocEx(int ch_id, INT8U * pBuf, INT32U real_size)
{
    HEAP_T * cur_pos;
    HEAP_T * freebuf_start;
    HEAP_T * backup_next;
    INT32U size;

    if(pBuf == NULL)
        return smallocEx(ch_id, real_size);

    if((INT32U)pBuf < (INT32U)smalloc_t[ch_id].p_heap_start )
        return;

    freebuf_start = (HEAP_T *)(pBuf - sizeof(HEAP_T));

    size = (real_size + 3) & 0xfffffffcul;

    if(dab_memcmp(freebuf_start->ID, MAL_MARK, MAL_LENGTH) || freebuf_start->is_alloc == 0)
        return NULL;

    cur_pos = freebuf_start->next;
    while(cur_pos)
    {
        if(dab_memcmp(cur_pos->ID, MAL_MARK, MAL_LENGTH))
            return NULL;

        if(cur_pos->is_alloc == 0)
        {
            //size만큼 잡고 중간에 header를 붙일 공간도 필요함.
            if( (INT32U)((INT8U*)cur_pos->next - (INT8U*)freebuf_start) >= size + sizeof(HEAP_T))
                break;
        }
        //연속된 빈공간이 없음.
        else
            return NULL;
        cur_pos = cur_pos->next;
    }

    //빈공간 있음.

    //중간에 헤더를 하나 더 만들 여유가 있으면 만든다.
    if( (INT32U)((INT8U*)cur_pos->next - (INT8U*)freebuf_start) > size + 2 * sizeof(HEAP_T))
    {
        freebuf_start->is_alloc = 1;
        backup_next = cur_pos->next;
        freebuf_start->next = (HEAP_T *)((INT8U *)freebuf_start + size + sizeof(HEAP_T));

        memset((INT8U *)cur_pos, 0, sizeof(HEAP_T));

        dab_memcpy((freebuf_start->next)->ID, MAL_MARK, MAL_LENGTH);
        ((HEAP_T *)freebuf_start->next)->is_alloc = 0;
        ((HEAP_T *)freebuf_start->next)->next = backup_next;
    }
    //sizeof(HEAP_T)의 크기 만큼, 만들 여유가 없으면 그냥 여분의 메모리 공간을 남기지만 할당한다.
    else
    {
        freebuf_start->is_alloc = 1;
        freebuf_start->next = cur_pos->next;

        memset((INT8U *)cur_pos, 0, sizeof(HEAP_T));
    }

    return (INT8U *)freebuf_start + sizeof(HEAP_T);
}

/////////////////////////////////////////////////////////////////////////

typedef union
{
    int val;
    char val_dim[4];
}VAL_4BYTE_U;

INT8U bit_mask[8] = {0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};

//전체 32bit까지 가져올 수 있다.
int GetBitsEx(INT8U * pBuf, int start_bit_pos, int bit_num)
{
    int reading_pos;
    int writing_pos;
    int read_size;

    VAL_4BYTE_U ret;

    //intital
    ret.val = 0;
    reading_pos = start_bit_pos + bit_num;
    writing_pos = 0;

    read_size = reading_pos & 0x07;

    if(read_size == 0)
        read_size = 8;

    if(bit_num < read_size)
        read_size = bit_num;

    //little endian 기준.
    while(bit_num > 0)
    {
        ret.val_dim[writing_pos >> 3] |= ((pBuf[(reading_pos - 1) >> 3] >> ((((reading_pos>>3) + 1) * 8 - reading_pos) & 0x07) ) & bit_mask[read_size - 1] ) << (writing_pos &0x07);

        bit_num -= read_size;

        //next
        reading_pos -= read_size;
        writing_pos += read_size;

        read_size = (bit_num < (8-read_size)) ? bit_num : 8 - read_size;

        if(read_size == 0)
            read_size = (bit_num < (8-read_size)) ? bit_num : 8 - read_size;
        //read_size = 8 - read_size;
    }

    return ret.val;
}

void dab_memcpy(void * inp1, void * inp2, int length)
{
    INT8U *dest, *src;

    dest = inp1;
    src = inp2;

    while(length --)
    {
        *dest ++ = *src ++;
    }
}

int dab_memcmp(void * inp1, void * inp2, int length)
{
    INT8U * src1, * src2;

    src1 = inp1;
    src2 = inp2;

    while(length--)
    {
        if(*src1++ != *src2 ++)
            return 1;
    }

    return 0;
}
