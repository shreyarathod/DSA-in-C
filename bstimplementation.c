#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;


// Function for creating a new BST node
TreeNode* createNode(int data) {
	struct TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
	node->data=data;
	node->left=NULL;
	node->right=NULL;
	return node;

}

// Function to insert a new value into the BST
TreeNode* insert(TreeNode* root, int data){
	if(root==NULL){
		TreeNode * node = createNode(data);
		return node;
 	}else if(data<root->data){
		root->left=insert(root->left,data);
	}else{
		root->right=insert(root->right,data);
	}
	return root;
}


// Function to delete a node with given value from the BST
TreeNode* delete(TreeNode* root, int data){
	if(root==NULL){
		printf("BinarySearchTree is Empty");
		return root;
	}else if(data<root->data){
		root->left=delete(root->left,data);
	}else if(data>root->data){
		root->right=delete(root->right,data);
	}else{
		//IF THE NODE HAS ONE OR NO CHILD
		if(root->left==NULL){
			TreeNode * temp = root->right;
			free(root);
			return temp;
		}else if(root->right == NULL){
			TreeNode * temp = root->left;
			free(root);
			return temp;
		}
		//IF THE NODE HAS 2 CHILDREN
		TreeNode * successor = root->right;
		while(successor!=NULL || successor->left==NULL){
			successor = successor->left;
		}
		root->data=successor->data;
		free(successor);
		return root;
	}
	
	return root;

}


// Function to display the BST in-order
void display(TreeNode* root){
    if(root==NULL){
		return;
	}
	else{
		display(root->left);
		printf("%d ", root->data);
		display(root->right);
	}

}


TreeNode* minValueNode(TreeNode* root){
	if(root->left==NULL){
		return root;
	}
	
	minValueNode(root->left);
}

TreeNode* maxValueNode(TreeNode* root){
    if(root->right==NULL){
		return root;
	}
	maxValueNode(root->right);
}

TreeNode* findNode(struct TreeNode* root, int data){
	if( root==NULL ){
        printf("\nNODE NOT FOUND!!");
		return root;
	}else if(root->data == data){
        return root;

    }else if(data<root->data){
		return findNode(root->left,data);
	}else if (data>root->data){
		return findNode(root->right,data);
	}else{
		printf("\nNODE NOT FOUND!!");
		return NULL;
	}

}

void swapValues(TreeNode* root, int data_1, int data_2){
    TreeNode * temp1 = findNode(root,data_1);
    TreeNode * temp2 = findNode(root,data_2);
    temp1->data = data_2;
    temp2->data = data_1;
}

int main (){
    TreeNode * root = createNode(10);
    insert(root,5);
    insert(root,15);
    insert(root,3);
    insert(root,8);
    insert(root,20);
	insert(root,1);
	insert(root,2);
	insert(root,30);
	printf("Binary Search Tree:");
    display(root);
    printf("\n");
	
    delete(root,1);
    delete(root,2);
	delete(root,30);
	printf("After Deletion:");
    display(root);
    printf("\n");

    TreeNode *temp = minValueNode(root);
    printf("\nMin Value Node: %d",temp->data);
    temp = maxValueNode(root);
    printf("\nMax Value Node: %d",temp->data);
   
    
	printf("\nBefore Swapping:");
	display(root);
    swapValues(root,5,3 );
	printf("\nAfter Swapping:");
    display(root);
    
	printf("\nFor Node having value 8:");
	temp=findNode(root,8);
    printf("Node Found : %d",temp->data);

	printf("\nFor Node having value 11:");
    temp=findNode(root,11);
    

	return 0;
}