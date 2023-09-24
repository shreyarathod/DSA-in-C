#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *
create_node(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void insert_at_pos(Node **head, int pos, int data)
{
    Node *node = create_node(data);
    if (pos == -1)
    {
        Node *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
    }
    else if (pos == 0)
    {
        node->next = *head;
        *head = node;
    }
    else
    {
        Node *temp = *head;
        for (int i = 0; i < pos - 1; i++)
        {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
    }
}

void delete_at_pos(Node **head, int pos)
{
    if (pos == -1)
    {
        Node *temp = *head;
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = NULL;
    }
    else if (pos == 0)
    {
        *head = (*head)->next;
    }
    else
    {
        Node *temp = *head;
        for (int i = 0; i < pos - 1; i++)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
    }
}

void delete_by_value(Node **head, int value)
{
    Node *temp = *head;
    if ((*head)->data == value)
    {
        *head = (*head)->next;
    }
    else
    {
        while (temp->next->data != value)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
    }
}

Node *
get_node_at_pos(Node **head, int pos)
{
    if (pos == -1)
    {
        Node *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        return temp;
    }
    else
    {
        Node *temp = *head;
        for (int i = 0; i < pos; i++)
        {
            temp = temp->next;
        }
        if (temp == NULL)
        {
            return NULL;
        }
        else
        {
            return temp;
        }
    }
}

Node *
find_first(Node **head, int value)
{
    Node *temp = *head;
    while (temp != NULL)
    {
        if (temp->data == value)
        {
            break;
        }
        else
        {
            temp = temp->next;
        }
    }
    if (temp == NULL)
    {
        return NULL;
    }
    else
    {
        return temp;
    }
}

void display(Node *head)
{
    if (head == NULL)
    {
        printf("Empty LinkedList.\n");
    }
    else
    {
        Node *temp = head;
        while (temp != NULL)
        {
            printf("-->%d", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void free_linkedlist(Node **head)
{
    Node* current= *head;
    while (current != NULL)
    {
        Node *temp=current;
       current=current->next;
       free(temp);
    }
    *head=NULL;
}

Node *
reverse(Node **head)
{
    Node *previous = NULL;
    Node *current = *head;
    Node *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    *head = previous;
    return *head;
}

// int main()
// {
//     struct Node *head = create_node(1);//creating a linked list 
//     insert_at_pos(&head, -1, 2);
//     insert_at_pos(&head, -1, 3);
//     printf("LinkedList");
//     display(head);

//     //inserting at end
//     insert_at_pos(&head, -1, 4);
//     printf("Inserting 4 at the end.\n");
    
//     display(head);
//      //inserting at front
//     insert_at_pos(&head, 0, 5);
//     printf("Inserting 5 at the front.\n");
   
//     display(head);
//     //inserting at index 1
//     insert_at_pos(&head, 1, 6);
//     printf("Inserting 6 at INDEX 1.\n");
    
//     display(head);
//    //inserting at index 2
//     insert_at_pos(&head, 2, 7);
//     printf("Inserting 7 at INDEX 2.\n");
   
//     display(head);

    
//    //deleting at end 
    
//     delete_at_pos(&head, -1);
//     printf("Deleting node at the end.\n");
//     display(head);
//     //deleting at front
//     delete_at_pos(&head, 0);
//     printf("Deleting node at the front.\n");
//     display(head);
//     //deleting node at index 2
//     delete_at_pos(&head, 2);
//     printf("Deleting node at INDEX 2.\n");
//     display(head);
//     // deleting node at index 1
//     delete_at_pos(&head, 1);
//     printf("Deleting node at INDEX 1.\n");  
//     display(head);

//     //deleting node by value
//     delete_by_value(&head, 3);
//     printf("Deleting node having value 3.\n");  
//     display(head);

//     //getting node at front
//     Node *temp = get_node_at_pos(&head, 0);
//     if (temp == NULL)
//     {
//         printf("Node not found.\n");
//     }
//     else
//     {
//         printf("Node at front:%d\n", temp->data);
//     }

//     //getting node at end
//     temp = get_node_at_pos(&head, -1);
//     if (temp == NULL)
//     {
//         printf("Node not found.\n");
//     }
//     else
//     {
//         printf("Node at end:%d\n", temp->data);
//     }
    
//     //getting node at index 2
//     temp = get_node_at_pos(&head, 2);
//     if (temp == NULL)
//     {
//         printf("Node not found.\n");
//     }
//     else
//     {
//         printf("Node at index 2:%d\n", temp->data);
//     }


//     //find first of value 6
//     Node *temp2 = find_first(&head, 6);
//     if (temp2 == NULL)
//     {
//         printf("Node not found.\n");
//     }
//     else
//     {
//         printf("Node of value %d found in the linked list.\n", temp2->data);
//     }

//     //find first of value 5
//     temp2 = find_first(&head, 5);
//     if (temp2 == NULL)
//     {
//         printf("Node not found.\n");
//     }
//     else
//     {
//         printf("Node of value %d found in the linked list.\n", temp2->data);
//     }
 


//     insert_at_pos(&head, -1, 4);
//     insert_at_pos(&head, -1, 5);
//     insert_at_pos(&head, -1, 2);
//     // reversing linked list 
//     printf("Reversing Linked List.\nBefore Reversing:\n");
//     display(head);
//     reverse(&head);
//     printf("After reversing:\n");
//     display(head);

//     //freeing linked list
//     printf("Freeing Linked List.\nBefore Freeing:\n");
//     display(head);
//     free_linkedlist(&head);
//     printf("After Freeing:\n");
//     display(head);
    
//     return 0;
// }