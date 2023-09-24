#include"LL_implementation.c"
#include<stdio.h>
#include<math.h>
Node* add_two_numbers(Node* l1, Node* l2){
    int num1,num2,count,data1;
    num1=0;
    num2=0;
    count=0;
   
    data1=0;
    Node* temp1 = reverse(&l1);
    while(temp1!=NULL){
        data1 = temp1->data;
        num1=num1+(data1 * pow(10,count));
        temp1=temp1->next;
        count++;
    }

    count=0;

     Node* temp2 = reverse(&l2);
     while(temp2!=NULL){
        data1 = temp2->data;
        num2=num2+(data1 * pow(10,count));
        temp2=temp2->next;
        count++;
    }

    int sum=num1+num2;
    int digit=sum%10;
    sum=sum/10;
    Node * sum_head=create_node(digit);

    while(sum!=0){
        digit=sum%10;
        insert_at_pos(&sum_head,-1,digit);
        sum=sum/10;
    }

    Node *sum_ll=reverse(&sum_head);
    return sum_ll;

} 


int main(){
    Node * head1 = create_node(7);
    insert_at_pos(&head1,-1,1);
    insert_at_pos(&head1,-1,4);
    insert_at_pos(&head1,-1,6);
    printf("List A");
    display(head1);

    Node * head2 = create_node(9);
    insert_at_pos(&head2,-1,7);
    insert_at_pos(&head2,-1,2);
    printf("List B");
    display(head2);

    Node * sum = add_two_numbers(head1,head2);
    printf("Sum");
    display(sum);

 return 0;

}
