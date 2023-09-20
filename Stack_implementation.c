#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int top;
    int size;
    int *arr;
};
typedef struct Stack STACK;

int is_empty(struct Stack *s) {
    if (s->top == -1) {
        return 1;
    } else {
        return 0;
    }
}

int is_full(struct Stack *s) {
    if (s->top == s->size - 1) {
        return 1;
    } else {
        return 0;
    }
}

void push(struct Stack *s, int data) {
    if (is_full(s) == 1) {
        printf("Stack is Full. (overflow)\n");
        return;
    } else {
        s->arr[++s->top] = data;
        return;
    }
}

int pop(struct Stack *s) {
    if (is_empty(s) == 1) {
        printf("Stack is empty. (underflow)\n");
        return -1;
    } else {
        int temp = s->arr[s->top];
        s->top--;
        return temp;
    }
}

int peek(struct Stack *s) {
    if (is_empty(s) == 1) {
        printf("Stack is empty. (underflow)\n");
        return -1;
    } else {
        return s->arr[s->top];
    }
}

void display(struct Stack *s) {
    if (is_empty(s) == 1) {
        printf("Stack is empty. (underflow)\n");
        return;
    } else {
        printf("The elements of the stack are:\n");
        for (int i = s->top; i >= 0; i--) {
            printf("%d\n", s->arr[i]);
        }
        printf("\n");
        return;
    }
}

int main() {
    struct Stack *s1=(struct Stack *)malloc(sizeof(struct Stack)); ;
    s1->top = -1;
    s1->size = 50;
    s1->arr = (int *)malloc(s1->size * sizeof(int));
   
    int ch;
    int data;
    do {
        printf("Enter the number for the operation you would like to execute.\n");
        printf("1. Push\n2. Pop\n3. Peek\n4. Display\n0. Terminate Program\n");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter the element you want to add: ");
                scanf("%d", &data);
                push(s1, data);
                break;
            case 2:
                data = pop(s1);
                printf("The popped element is :%d \n", data);
                break;
            case 3:
                data = peek(s1);
                printf("The element at the top of the stack is: %d \n", data);
                break;
            case 4:
                display(s1);
                break;
            case 0:
                printf("Program Terminated.\n");
                break;
        }
    } while (ch != 0);

    return 0;
}