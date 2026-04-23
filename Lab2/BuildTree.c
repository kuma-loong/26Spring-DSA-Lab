#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    if (preorderSize == 0 || inorderSize == 0) {
        return NULL;
    }
    struct TreeNode* root = createNode(preorder[0]);
    for (int i = 0; i < inorderSize; i++) {
        if (inorder[i] == preorder[0]) {
            root->left = buildTree(preorder + 1, i, inorder, i);
            root->right = buildTree(preorder + 1 + i, preorderSize - 1 - i, inorder + i + 1, inorderSize - 1 - i);
            break;
        }
    }
    return root;
    


}

void printTree(struct TreeNode* root) {
    if (root == NULL) {
        printf("null ");
        return;
    }

    struct TreeNode** queue = (struct TreeNode**)malloc(MAX_SIZE * sizeof(struct TreeNode*));
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front != rear) {
        struct TreeNode* current = queue[front++];
        if (current == NULL) {
            printf("null ");
        } else {
            printf("%d ", current->val);
            queue[(rear++)%MAX_SIZE] = current->left;
            queue[(rear++)%MAX_SIZE] = current->right;
        }
    }
}

int main() {
    int preorderSize;
    scanf("%d", &preorderSize);
    int* preorder = (int*)malloc(preorderSize * sizeof(int));
    for (int i = 0; i < preorderSize; i++) {
        scanf("%d", &preorder[i]);
    }

    int inorderSize = preorderSize;
    int* inorder = (int*)malloc(inorderSize * sizeof(int));
    for (int i = 0; i < inorderSize; i++) {
        scanf("%d", &inorder[i]);
    }

    struct TreeNode* root = buildTree(preorder, preorderSize, inorder, inorderSize);
    printTree(root);

    return 0;
}