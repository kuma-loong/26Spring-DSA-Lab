#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct TreeNode* buildTree() {
    char s[20];
    if (scanf("%s", s) == EOF || strcmp(s, "#") == 0) {
        return NULL;
    }
    struct TreeNode* root = createNode(atoi(s));
    root->left = buildTree();
    root->right = buildTree();
    return root;
}

int isMirror(struct TreeNode* t1, struct TreeNode* t2) {
    if (t1 == NULL && t2 == NULL) {
        return 1;
    }
    if (t1 == NULL || t2 == NULL) {
        return 0;
    }
    if (t1->val == t2->val) {
        return isMirror(t1->left, t2->right) && isMirror(t1->right, t2->left);
    }
    return 0;
}

int countMirrorCores(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int count = 0;
    // 首先递归计算左右子树中的镜像核心
    count += countMirrorCores(root->left);
    count += countMirrorCores(root->right);
    
    // 然后判断当前节点是否是镜像核心
    if (isMirror(root->left, root->right)) {
        count++;
    }
    
    return count;
}

int main() {
    struct TreeNode* root = buildTree();
    printf("%d\n", countMirrorCores(root));
    return 0;
}