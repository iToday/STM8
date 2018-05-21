/***********************************************************
Ring buffer define implement
		 -
************************************************************/
#include "../typedef.h"

uint8_t is_empty(PRING_BUFFER ring){

    return ring->head_pos == ring->tail_pos;
}

uint8_t head(PRING_BUFFER ring){
    return ring->buffer[ring->head_pos];
}

uint8_t push(PRING_BUFFER ring, uint8_t data){
    
    if (ring->tail_pos < RING_BUFFER_SIZE 
        && ring->tail_pos != ring->head_pos -1){
        
        ring->buffer[ring->tail_pos ++] = data; 

        if (ring->tail_pos >= RING_BUFFER_SIZE){

            if (ring->head_pos > 1)
                ring->tail_pos = 0;
            else{
                ring->tail_pos = RING_BUFFER_SIZE - 1;               
            }
        }

        return true;
    }

    return false;
}

uint8_t pop(PRING_BUFFER ring){

    uint8_t data = 0;
    
    if (ring->head_pos != ring->tail_pos){

        data = ring->head(ring);
        
        ring->head_pos ++;
        
        if (ring->head_pos > ring->tail_pos 
            && ring->head_pos >= RING_BUFFER_SIZE)
            ring->head_pos = 0;        
    }

    return data;
}

uint8_t get(PRING_BUFFER ring, uint8_t offset){

    if (offset < ring->length(ring)){
        
        uint8_t index = ring->head_pos + offset;

        if (index >= RING_BUFFER_SIZE)
            index -= RING_BUFFER_SIZE;

        return ring->buffer[index];
    }

    return 0;
}

uint8_t set(PRING_BUFFER ring, uint8_t offset, uint8_t data){
    
    if (offset < ring->length(ring)){
        
        uint8_t index = ring->head_pos + offset;

        if (index >= RING_BUFFER_SIZE)
            index -= RING_BUFFER_SIZE;

        ring->buffer[index] = data;

        return true;
    }

    return false;
}

uint8_t length(PRING_BUFFER ring){
    
    if (ring->head_pos <= ring->tail_pos)
        return ring->tail_pos - ring->head_pos;
    else
        return RING_BUFFER_SIZE - (ring->head_pos - ring->tail_pos);
}

void clear(PRING_BUFFER ring){
    ring->head_pos = ring->tail_pos = 0;
}

void for_each(PRING_BUFFER ring, on_each each){

    if (each == NULL)
        return;

    uint8_t len = ring->length(ring);

    uint8_t index = 0;
    uint8_t pos = 0;

    for (index = 0; index < len; index ++){
        pos = ring->head_pos + index;

        if (pos >= RING_BUFFER_SIZE)
            pos -= RING_BUFFER_SIZE;

        if (each(index, len, ring->buffer[pos]))
            break;
    }
}

void clone(struct ring_buffer* ring, uint8_t* buf){
    
    uint8_t len = ring->length(ring);

    uint8_t index = 0;
    uint8_t pos = 0;

    for (index = 0; index < len; index ++){
        pos = ring->head_pos + index;

        if (pos >= RING_BUFFER_SIZE)
            pos -= RING_BUFFER_SIZE;

        buf[index] = ring->buffer[pos];
    }
}

void init_ring_buffer(PRING_BUFFER ring){

    if (ring != NULL){

        ring->is_empty = is_empty;
        ring->head = head;
        ring->push = push;
        ring->pop = pop;
        ring->length = length;
        ring->clear = clear;
        ring->get = get;
        ring->set = set;
        ring->for_each = for_each;
        ring->clone = clone;

        ring->head_pos = ring->tail_pos = 0;
    }
}

