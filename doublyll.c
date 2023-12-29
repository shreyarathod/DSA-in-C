#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int val;
    struct Node *prev;
    struct Node *next;
} Node;

Node *create_node(int val)
{
    // printf("create a new DLL node using this function");
    Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->prev = NULL;
    node->next = NULL;
    node->val = val;
    return node;
}

// pos == 0 indicates start of the DLL
// pos == -1 indicates end of the DLL
// pos == n indicates intermediate node pos
// is_after = true => insert after 'pos'
// is_after = false => insert before'pos'
void insert_at_pos(Node **header, Node **trailer, int pos, bool is_after, int data)
{
    // printf("This should add a node at given position of the DLL");
    Node *node = create_node(data);
    Node *temp = *header;
    if (is_after==true)
    {
        if (pos == -1)
        {
            Node * current = * header;
            while(current->next != NULL){
                current=current->next;

            }

            current->next=node;
            node->prev=current;
            *trailer=node;
        }
        else if(pos == 0){
           node->next= (*header)->next;
           (*header)->next = node;
           node->prev=*header;
           if(node->next)
           node->next->prev=node;

        }
        else
        {
            for (int i = 0; i < pos; i++)
            {
                temp = temp->next;
            }
            node->next = temp->next;
            temp->next = node;
            node->prev = temp;
            if(node->next)
            node->next->prev = node;
        }
    }
    else
    {
        if (pos == -1)
        {
            node->next=*trailer;
            node->prev=(*trailer)->prev;
            (*trailer)->prev=node;
            if(node->prev)
            node->prev->next=node;
            else
            *header=node;
        }
        else if(pos == 0){
       
        node->next=*header;
        (*header)->prev=node;
        *header=node;

        }
        else{
        for (int i = 0; i < pos; i++)
        {
            temp = temp->next;
        }
        node->prev = temp->prev;
        temp->prev = node;
        node->next = temp;
        if(node->prev)
        node->prev->next = node;
        }
    }
}

// pos == 0 indicates start of the DLL
// pos == -1 indicates end of the DLL
// pos == n indicates intermediate node pos
void delete_at_pos(Node **header, Node **trailer, int pos)
{
    // printf("This should add a node at given position of the DLL");
    if (pos == 0)
    {
        *header = (*header)->next;
        (*header)->prev = NULL;
    }
    else if (pos == -1)
    {
        *trailer = (*trailer)->prev;
        (*trailer)->next = NULL;
    }
    else
    {
        Node *temp = *header;
        for (int i = 0; i < pos - 1; i++)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        temp->next->prev = temp;
    }
}

void reverse(Node **header, Node **trailer)
{
    // printf("This should reverse the doubly linked list");
    Node *current = *header;
    Node *previous = NULL;
    Node *nextelement = NULL;
    while (current != NULL)
    {
        nextelement = current->next;
        current->next = previous;
        current->prev = nextelement;
        previous = current;
        current = nextelement;
    }
    *header = previous; 
}



void swap(Node** header, Node** trailer, int pos_1, int pos_2) {
    // Ensure that pos_1 is less than or equal to pos_2.
    if (pos_1 > pos_2) {
        int temp = pos_1;
        pos_1 = pos_2;
        pos_2 = temp;
    }

    Node* node_1 = *header;
    Node* node_2 = *header;
    Node* prev_node_1 = NULL;
    Node* prev_node_2 = NULL;

    // Find node_1, prev_node_1, node_2, and prev_node_2.
    int i;
    for (i = 0; node_1 != NULL && i < pos_1; i++) {
        prev_node_1 = node_1;
        node_1 = node_1->next;
    }

    for (i = 0; node_2 != NULL && i < pos_2; i++) {
        prev_node_2 = node_2;
        node_2 = node_2->next;
    }

    // Check if either node_1 or node_2 is NULL (out of range).
    if (node_1 == NULL || node_2 == NULL) {
        printf("Invalid positions for swap.\n");
        return;
    }

    // Update prev and next pointers to perform the swap.
    if (prev_node_1 != NULL) {
        prev_node_1->next = node_2;
    } else {
        // If node_1 is the first node, update the header.
        *header = node_2;
    }

    if (prev_node_2 != NULL) {
        prev_node_2->next = node_1;
    } else {
        // If node_2 is the first node, update the header.
        *header = node_1;
    }

    // Swap next pointers of node_1 and node_2.
    Node* temp_next = node_1->next;
    node_1->next = node_2->next;
    node_2->next = temp_next;

    // Update prev pointers.
    if (node_1->next != NULL) {
        node_1->next->prev = node_1;
    }
    
    if (node_2->next != NULL) {
        node_2->next->prev = node_2;
    }

    // Update trailer pointer if necessary.
    if (node_1 == *trailer) {
        *trailer = node_2;
    } else if (node_2 == *trailer) {
        *trailer = node_1;
    }
}

void display(Node *header, Node *trailer)
{
    // printf("display the entire DLL. The '->' can be replaced by '<-->' for display");
    Node *temp_node = header;
    printf("Head ");
    while (temp_node != NULL)
    {
        printf("<-->%d", temp_node->val);
        temp_node = temp_node->next;
    }
    printf(" <--> Tail\n");
}

int main()
{
    Node *header = create_node(1);
    Node *trailer = header;
    display(header, trailer);
    insert_at_pos(&header, &trailer, 0, true, 2);
    display(header, trailer);
    insert_at_pos(&header, &trailer, 0, false, 3);
    display(header, trailer);
    insert_at_pos(&header, &trailer, 1, true, 4);
    display(header, trailer);
    insert_at_pos(&header, &trailer, 2, false, 5);
    display(header, trailer);
    insert_at_pos(&header, &trailer, -1, true, 7);
    display(header, trailer);
     insert_at_pos(&header, &trailer, -1, false, 8);
    display(header, trailer);
    delete_at_pos(&header,&trailer,0);
    display(header, trailer);
    delete_at_pos(&header,&trailer,1);
    display(header, trailer);
    delete_at_pos(&header,&trailer,-1);
    display(header, trailer);
    reverse(&header,&trailer);
    display(header, trailer);

    swap(&header,&trailer,0,1);
    display(header,trailer);
    

}

