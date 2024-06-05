/*
 * ajesznqueue.h
 *
 *  Created on: Jun 3, 2024
 *      Author: Ajeszny
 */

#ifndef INC_AJESZNQUEUE_H_
#define INC_AJESZNQUEUE_H_
#include <stdlib.h>

typedef struct queue_node_t {
	void* stored;
	size_t size;
	struct queue_node_t* next;
} queue_node;

typedef struct queue_t {
	queue_node* head;
	queue_node* tail;
	size_t size;
}queue;

size_t pop(queue* q, void* element);
void push(queue* q, void* element, size_t size);
void flush(queue* q, void stream(char));

#endif /* INC_AJESZNQUEUE_H_ */
