#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
struct Stack {
    int top; 
    char arr[SIZE];
};
typedef struct Stack STACK;


void initialize(struct Stack *s){
    s->top=-1;


}

int is_empty(struct Stack *s) {
    if (s->top == -1) {
        return 1;
    } else {
        return 0;
    }
}

int is_full(struct Stack *s) {
    if (s->top == SIZE- 1) {
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

int oper_precedence(char operator){
    switch(operator){
    case '+': return 1;
             
    case '-': return 1;
                       
    case '*': return 2;
              
    case '/': return 2;
              
    case '^': return 3;
              
    default: return 0;
    }

}

int is_operator(char operator){
    if(operator == '+' || operator == '-'){
        return 1;
    }
    else if(operator == '*' || operator == '/'){
        return 2;
    }
    return 0; 
}

void infix_to_prefix(char infix[], char prefix[]){
    struct Stack s;
    initialize (&s);
    
    int i=0;
    int len=strlen(infix);
    char reversed_infix[len];
    for(int j=len-1; j>=0;j--){
        reversed_infix[len-j-1]=infix[j];
    }
    
    for(int j=0;j<len;j++){
        char temp=reversed_infix[j];
        
        if(infix[j]==' '){
            continue;
        }else if(is_operator (temp)){
            while(!is_empty(&s) && oper_precedence(peek(&s))>= oper_precedence (temp)) {
                prefix[i]=pop(&s);
                i++;
            }
            push(&s, temp);
        }else if(temp==')') {
            push(&s,temp);
        }else if (temp=='('){
            while(!is_empty(&s) && peek(&s)!=')'){
                prefix[i]=pop(&s);
                i++;
            }
            if(!is_empty(&s) && peek(&s)==')'){
                pop(&s);
            }
        }else{
            prefix[i]=temp;
            i++;
        }
}

while(!is_empty(&s)) {
    prefix[i]=pop(&s);
    i++;
}

int start = 0;
int end = i-1;
while (start<end){
char temp2 = prefix[start];
        prefix[start] = prefix[end];
        prefix[end] = temp2;
        start++;
        end--;
    }
}



int main () {
    char infix[100];
    char prefix[100];
    
    printf("Enter the Infix expression:");
    fgets(infix,sizeof(infix), stdin);
    
    infix_to_prefix(infix, prefix);
    printf("\nThe Prefix expression is:");
    printf("%s\n",prefix);
}
