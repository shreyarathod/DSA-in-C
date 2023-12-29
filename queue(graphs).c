/*
 * File: queue.c
 * Author: Siddhartha Chandra
 * Email: siddhartha_chandra@spit.ac.in
 * Created: September 1, 2023
 * Description: This program implements a Queue ADT for Graphs
 */


// Build a Queue Abstract Data structure and perform operations on it 
// Operations:
// 1. display
// 2. isFull
// 3. isEmpty
// 4. enqueue
// 5. dequeue
// 6. front
// 7. rear

#include "datatypes(graph).h"

// 0 -> Initialize
Queue* initialize_queue(unsigned size){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->size = size;
    queue->front = -1;
    queue->rear = -1;
    
    queue->array = (Vertex *)malloc(queue->size * sizeof(Vertex));
    if (queue->array == NULL) {
        free(queue);
        exit(EXIT_FAILURE);
    }
    return queue;
}


// 0 -> display
void display_queue(Queue* queue){
    if (isEmpty(queue))
        printf("The queue is empty\n\n");
    else {
        printf("front --> ");
        for (int i=queue->front; i != queue->rear; i = (i + 1) % queue->size)
            printf("%d ", queue->array[i]);

        // additionally display rear element of queue
        printf("%d ", rear(queue));
        printf("<-- rear\n\n");
    }
}

// 1 -> isEmpty
int isEmpty(Queue* queue){
    return (queue->front == -1 && queue->rear == -1);
}

// 3 -> isFull
int isFull(Queue* queue){
    int next_pos = (queue->rear + 1) % queue->size;
    return queue->front == next_pos;
}

// 4 -> enqueue
void enqueue(Queue *queue, Vertex vertex){
    if (isFull(queue)){
        printf("Error: Queue is already full!\n");
    }
    else{
        // if empty queue, both front and rear get assigned to 0
        // else only rear moves by 1
        if (isEmpty(queue))
            queue->front = queue->rear = 0;
        else
            queue->rear = (queue->rear + 1) % queue->size;
        
        queue->array[queue->rear] = vertex;
    }
    
}

// 5 -> dequeue
Vertex dequeue(Queue* queue){
    if (isEmpty(queue)) {
        printf("Error: Queue is empty!\n");
        return -1;
    }
    else {
        Vertex res;
        res = queue->array[queue->front];
        if (queue->front == queue->rear)    
            queue->front = queue->rear = -1;
        else 
            queue->front = (queue->front + 1) % queue->size;
        
        return res;
    }
}

// 6 -> front
Vertex front(Queue* queue){
    if (isEmpty(queue)) {
        printf("Error: Queue is empty!\n");
        return -1;
    }
    return queue->array[queue->front];
}

// 7 -> rear
Vertex rear(Queue* queue){
    if (isEmpty(queue)) {
        printf("Error: Queue is empty!\n");
        return -1;
    }
    return queue->array[queue->rear];
}