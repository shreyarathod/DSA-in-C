#include "Queue_implementation.c"
#include <stdio.h>
#include <stdlib.h>

struct NQueues
{
    int *front;
    int *rear;
    unsigned total_queues;
    unsigned size_per_queue;
    struct Queue *array[50];
};

struct NQueues *createNQueues(int n, int capacity_per_queue)
{
    struct NQueues *Nq = (struct NQueues *)malloc(sizeof(struct NQueues));
    Nq->total_queues = n;
    Nq->size_per_queue = capacity_per_queue;
    // Nq->array = (struct Queue **)malloc(n * sizeof(struct Queue *));

    for (int i = 0; i < n; i++)
    {
        Nq->array[i] = initialize_queue(capacity_per_queue);
    }

    return Nq;
}

void add_episode(struct NQueues *Nq, int episode_id, int queue_number)
{
    enqueue(Nq->array[queue_number], episode_id);
}

char watch_next_episode(struct NQueues *Nq, int queue_number)
{
    char ep_temp = dequeue(Nq->array[queue_number]);
    return ep_temp;
}

void display_queue(struct NQueues *Nq, int queue_number)
{
    display(Nq->array[queue_number]);
}

void display_all(struct NQueues *Nq)
{
    for (int i = 0; i < Nq->total_queues; i++)
    {
        int q_temp = i + 1;
        printf("Displaying Queue %d:\n", q_temp);
        display(Nq->array[i]);
        printf("\n");
    }
}


int main () 
{
    struct NQueues *Nq = createNQueues(2,10);
    add_episode(Nq,65,0);
    add_episode(Nq,66,0);
    add_episode(Nq,67,0);
    add_episode(Nq,68,0);
    add_episode(Nq,69,0);

    add_episode(Nq,97,1);
    add_episode(Nq,98,1);
    add_episode(Nq,99,1);
    add_episode(Nq,100,1);
    add_episode(Nq,101,1);

    display_all(Nq);//prints ascii value of all ep numbers since the queues store char values

    
    char watched_ep = watch_next_episode(Nq,0);
    printf("The episode you watched: %d i.e %c\n", watched_ep, watched_ep);//prints ep id and corresponding ascii value
    printf("Remaining Queue after watched eps:\n");
    display_queue(Nq, 0);
    printf("\n");



    watched_ep = watch_next_episode(Nq,1);
    printf("The episode you watched: %d i.e %c\n", watched_ep, watched_ep);//prints ep id and corresponding ascii value
    printf("Remaining Queue after watched eps:\n");
    display_queue(Nq, 1);
    printf("\n");

    display_all(Nq);
}