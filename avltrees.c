// Create an AVLNode ADT and complete the following functions:
// 1. createNode  
// 2. displayAVLTree
// 3. getHeight
// 4. rotateRight
// 5. rotateLeft
// 6. getBalance
// 7. insert
// 8. freeAVLTree

#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

// complete this function
AVLNode* createNode(int data){
   AVLNode* new_node = (AVLNode*)malloc(sizeof(AVLNode));
   new_node->data = data;
   new_node->left = NULL;
   new_node->right = NULL;
   new_node->height = 1;
   return new_node;
}

int getHeight(AVLNode* node){
   if(node == NULL){
      return 0;
   }
   return node->height;                                                                                                
}

// get balance factor of given node
int getBalance(AVLNode* node){
   if(node==NULL){
      return 0;
   }
   return getHeight(node->left) - getHeight(node->right);
}

int max(int a,int b){
    if(a>b){
        return a;
    }
    return b;
}

void printLevelOrder(AVLNode* root, int level){
   if(root==NULL){
      return;
   }
   if(level == 0){
      printf("%d ", root->data);
   }
   else{
   printLevelOrder(root->left, level-1);
   printLevelOrder(root->right, level-1);
   }
}

// Display the level-order traversal of the Tree
void displayAVLTree(AVLNode* root){
   if(root==NULL){
      return;
   }
   int height = max(getHeight(root->left),getHeight(root->right)) + 1;
   for(int i=0; i<height; i++){
      printf("Level %d: ",i);
      printLevelOrder(root,i);
      printf("\n");
   }
}

// function for performing a right rotate
AVLNode* rotateRight(AVLNode* y){
   AVLNode* x = y->left;
   AVLNode* T2 = x->right;
   x->right=y;
   y->left=T2;
   y->height = max(getHeight(y->right),getHeight(y->left)) + 1;
   x->height = max(getHeight(x->right),getHeight(x->left)) + 1;
   return x;
}

// function for performing a left rotate
AVLNode* rotateLeft(AVLNode* x){
   AVLNode* y = x->right;
   AVLNode* T2 = y->left;
   y->left=x;
   x->right=T2;
   y->height = max(getHeight(y->right),getHeight(y->left)) + 1;
   x->height = max(getHeight(x->right),getHeight(x->left)) + 1;
   return y;
}

// This inserts a node with 'data' into the AVL tree.
// Please ensure that your function covers all 4 possible rotation cases
void insert(AVLNode** root, int data) {
    if (*root == NULL) {
        *root = createNode(data);
        return;
    }

    if (data < (*root)->data)
        insert(&(*root)->left, data);
    else if (data > (*root)->data)
        insert(&(*root)->right, data);
    else
        return; // Avoid duplicates

    // Update the height of the current node
        (*root)->height = 1 + max(getHeight((*root)->left) , getHeight((*root)->right));
    // Get the balance factor and perform rotations if needed
    int balance = getBalance(*root);

    if (balance > 1) {
        if (data < (*root)->left->data) {
            // Left Left case
            *root = rotateRight(*root);
        } else {
            // Left Right case
            (*root)->left = rotateLeft((*root)->left);
            *root = rotateRight(*root);
        }
    } else if (balance < -1) {
        if (data > (*root)->right->data) {
            // Right Right case
            *root = rotateLeft(*root);
        } else {
            // Right Left case
            (*root)->right = rotateRight((*root)->right);
            *root = rotateLeft(*root);
        }
    }
}

// This frees the memory used by the AVL tree
void freeAVLTree(AVLNode* root){
   if(root==NULL){
      return;
   }
   freeAVLTree(root->left);
   freeAVLTree(root->right);
   free(root);
}

int main(){
   AVLNode* root = createNode(10);
   insert(&root,5);
   insert(&root,3);
   insert(&root,1);
   insert(&root,5);
   displayAVLTree(root);  
}



