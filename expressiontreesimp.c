/*
 * File: expression_tree_preorder.c
 * Author: Siddhartha Chandra
 * Email: siddhartha_chandra@spit.ac.in
 * Created: October 17, 2023
 * Description: Create an expression tree from a preorder traversal. 
 *  Additionally, add function to evaluate a given expression tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack(expt).c"
// #include "datatypes(expt).h"


// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to perform an operation on 2 operands
float perform_operation(char op, float left, float right){
    switch (op) {
            case '+':
                return left + right;
            case '-':
                return left - right;
            case '*':
                return left * right;
            case '/':
                if (right != 0) {
                    return left / right;
                } else {
                    fprintf(stderr, "Error: Division by zero\n");
                    exit(EXIT_FAILURE);
                }
            default:
                fprintf(stderr, "Error: Unknown operator %c\n", op);
                exit(EXIT_FAILURE);
        }
}



// TODO: To be completed
ExprTreeNode *create_node(OpType op_type, Data data){
    ExprTreeNode * ETnode = (ExprTreeNode*)malloc(sizeof(ExprTreeNode));
    ETnode->type = op_type;
    ETnode->data = data;
    ETnode->left = NULL;
    ETnode->right = NULL;
    return ETnode;
}


// TODO: To be completed
// NOTE: Use the stack 'display' in this function to display stack state right after a given character in the expression has been processed.
// Do this for all characters of the expression string
ExprTreeNode *create_ET_from_prefix(char *prefix_expression){
    Stack * stack = initialize_stack(15);
    int i = 0;
    while(prefix_expression[i]!='\0'){
        i++;
    }
    for(int j = i-1;j>=0;j--){
        if(isOperator(prefix_expression[j])){

           Data data;
           data.operation = prefix_expression[j];
           ExprTreeNode * node = create_node(OPERATOR,data);
           node->left = pop(stack);
           node->right = pop(stack);
           push(stack,node);

        }else {
            Data data ;
            data.operand = (float)(prefix_expression[j]-'0');
            ExprTreeNode * node = create_node(OPERAND, data);
            push(stack, node);

        }
    }
    return pop(stack);
}


// TODO: To be completed
float evaluate_ET(ExprTreeNode* root){
    if(root->type == OPERAND){
        return root->data.operand;
    }

     float left = evaluate_ET(root->left);
     float right = evaluate_ET(root->right);
     return perform_operation(root->data.operation , left , right);
    
}

// preorder 
void preorder_ET (ExprTreeNode * root){
    if(root == NULL){
        return ;
    }
    //prints root
    if(root->type == OPERAND){
        printf("%f ", root->data.operand);
    }else {
        printf("%c ", root->data.operation);
    }

    //print left subtree 
    preorder_ET(root->left);
    //print right subtree
    preorder_ET(root->right);
    

}

int main (){
    // //test case 1
    // char prefix_expression[] = "+53";
    // ExprTreeNode * node = create_ET_from_prefix(prefix_expression);
    // preorder_ET(node);
    
    // //test case 2
    // char prefix_expression[] = "*+246";
    // ExprTreeNode * node = create_ET_from_prefix(prefix_expression);
    // preorder_ET(node);
     
    // //test case 3
    // char prefix_expression[] = "-/842";
    // ExprTreeNode *node = create_ET_from_prefix(prefix_expression);
    // preorder_ET(node);
    
    // //test case 4
    // char prefix_expression[] = "+*3+247";
    // ExprTreeNode *node = create_ET_from_prefix(prefix_expression);
    // preorder_ET(node);
    
    //test case 5
    char prefix_expression[] = "/+1-42*32";
    ExprTreeNode *node = create_ET_from_prefix(prefix_expression);
    preorder_ET(node);
    
    

    return 0;
}
