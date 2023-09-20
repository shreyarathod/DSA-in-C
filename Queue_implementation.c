#include <stdio.h>
#include <stdlib.h>

struct Queue
{
    int front;
    int rear;
    unsigned size;
    char *arr;
};

struct Queue *initialize_queue(unsigned size)
{
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->size = size;
    q->front = -1;
    q->rear = -1;
    q->arr = (char*)malloc(q->size*sizeof(char));
    return q;
}

int is_empty(struct Queue *q)
{
    return q->front == -1 && q->rear == -1;
}

int is_full(struct Queue *q)
{
    if (q->front == (q->rear + 1) % q->size)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char front(struct Queue *q)
{
    return q->arr[q->front];
}

char rear(struct Queue *q)
{
    return q->arr[q->rear];
}

void enqueue(struct Queue *q, char item)
{
    if (is_full(q))
    {
        printf("Cannot Add Elements.Queue is full!(Overflow)");
        return;
    }
    else if (is_empty(q))
    {
        q->front = 0;
        q->rear = 0;
       
    }
    else
    {
        q->rear = (q->rear + 1) % q->size;
       
    }
     q->arr[q->rear] = item;
}

char dequeue(struct Queue *q)
{
    char temp;
    if (is_empty(q))
    {
        printf("Cannot Remove Elements. Queue is empty!(Underflow)");
        return'0';
    }
    else
    {
        temp = q->arr[q->front];
        if (q->front == 0 && q->rear==0)
        {    
            temp = q->arr[q->front];
            q->rear = -1;
            q->front = -1;
         
        }
        else
        {
            temp = q->arr[q->front];
            q->arr[q->front]='0';
            q->front = (q->front + 1) % q->size;
           
        }
    } 
     return temp;
}

void display(struct Queue *q)
{
    for (int i = q->front; i <= q->rear; i++)
    {
        printf("%c", q->arr[i]);
    }
}

// int main()
// {
//     struct Queue *q = initialize_queue(4);
//     enqueue(q, 'A');
//     enqueue(q, 'B');
//     enqueue(q, 'C');
//     enqueue(q, 'D');
//     printf("Queue after adding elements:\n");
//     display(q);
//     printf("\n");

//     dequeue(q);
//     printf("Queue after removing an element:\n");
//     display(q);
//     printf("\n");


//     char fr = front(q);
//     char re = rear(q);
//     printf("Front:%c",fr);
//     printf("\n");
//     printf("Rear:%c\n",re);

//     //enqueueing element until Queue is full
//      enqueue(q, 'E');
//      enqueue(q, 'F');
//      printf("\n");
//      //dequeueing elements until queue becomes empty
//       dequeue(q);
//       dequeue(q);
//       dequeue(q);
//       dequeue(q);
//       dequeue(q);

//     return 0;
// }