/*
 * ajesznqueue.c
 *
 *  Created on: Jun 3, 2024
 *      Author: Ajeszny
 */
#include "ajesznqueue.h"

size_t pop(queue* q, void* element){
	if (q->size == 0) {
		return 0;
	}
	memcpy(element, q->head->stored, q->head->size);
	--q->size;
	queue_node* former_head = q->head;
	q->head = former_head->next;
	return free_node(former_head);
}

void push(queue* q, void* element, size_t size){
	void* dummy = malloc(size + sizeof(queue_node));
	if (!dummy) return;

	queue_node* new_tail = malloc(sizeof(queue_node));
	new_tail->next = 0;
	if (!q->tail) {
		q->head = new_tail;
	} else {
		q->tail->next = new_tail;

	}
	q->tail = new_tail;
	new_tail->size = size;
	new_tail->stored = malloc(size);
	memcpy(new_tail->stored, element, new_tail->size);
	++q->size;
}

int free_node(queue_node* f) {
	int retval = f->size;
	free(f->stored), free(f);
	return retval;
}

void flush(queue* q, void stream(char)) {
	while(q->size > 0) {
		for (int i = 0; i < q->head->size; ++i) {
			stream(*((char*)q->head->stored + i));
		}
		queue_node* next_node = q->head;
		q->head = q->head->next;
		free_node(next_node);
		--q->size;
	}
	q->head = 0;
	q->tail = 0;
}
