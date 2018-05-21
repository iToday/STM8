

#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

#include "../typedef.h"

#define RING_BUFFER_SIZE 128

#define INVALID_POS (0xFF)

typedef uint8_t (*on_each)(uint8_t offset, uint8_t len, uint8_t data);

#define PRING_BUFFER_CALL(TYPE, FUNC, args...) (TYPE)->FUNC((TYPE),args)
#define PRING_BUFFER_CALL_VOID(TYPE, FUNC) (TYPE)->FUNC((TYPE))

#define RING_BUFFER_CALL(TYPE, FUNC, args...) (TYPE).FUNC(&(TYPE),args)
#define RING_BUFFER_CALL_VOID(TYPE, FUNC) (TYPE).FUNC(&(TYPE))

typedef struct ring_buffer{

    uint8_t buffer[RING_BUFFER_SIZE];

    uint8_t head_pos;
    uint8_t tail_pos;

    uint8_t (*is_empty)(struct ring_buffer* ring);
    uint8_t (*head)(struct ring_buffer* ring);
    uint8_t (*push)(struct ring_buffer* ring, uint8_t data);
    uint8_t (*pop)(struct ring_buffer* ring);
    uint8_t (*length)(struct ring_buffer* ring);

    uint8_t (*get)(struct ring_buffer* ring, uint8_t offset);
    uint8_t (*set)(struct ring_buffer* ring, uint8_t offset, uint8_t data);

    void (*for_each)(struct ring_buffer* ring, on_each each);
    
    void (*clear)(struct ring_buffer* ring);
    void (*clone)(struct ring_buffer* ring, uint8_t* buf);
    
}RING_BUFFER, *PRING_BUFFER;


void init_ring_buffer(PRING_BUFFER ring);

#endif	//_I2C_H
