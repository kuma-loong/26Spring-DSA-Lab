#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct TreeNode {
    long long key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(long long key) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* insert(TreeNode *root, long long key) {
    if (root == NULL) {
        return createNode(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    return root;
}

TreeNode* findMin(TreeNode *root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}

TreeNode* delete(TreeNode *root, long long key) {
    if (root == NULL) {
        return NULL;
    }

    if (key < root->key) {
        root->left = delete(root->left, key);
    } else if (key > root->key) {
        root->right = delete(root->right, key);
    } else {
        if (root->left == NULL) {
            TreeNode *right = root->right;
            free(root);
            return right;
        }
        if (root->right == NULL) {
            TreeNode *left = root->left;
            free(root);
            return left;
        }

        TreeNode *successor = findMin(root->right);
        root->key = successor->key;
        root->right = delete(root->right, successor->key);
    }
    return root;
}

bool lowerBound(TreeNode *root, long long target, long long *ans) {
    bool found = false;
    while (root != NULL) {
        if (root->key >= target) {
            *ans = root->key;
            found = true;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return found;
}

bool upperBound(TreeNode *root, long long target, long long *ans) {
    bool found = false;
    while (root != NULL) {
        if (root->key <= target) {
            *ans = root->key;
            found = true;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return found;
}

TreeNode* lowestCommonAncestor(TreeNode *root, long long a, long long b) {
    while (root != NULL) {
        if (b < root->key) {
            root = root->left;
        } else if (a > root->key) {
            root = root->right;
        } else {
            return root;
        }
    }
    return NULL;
}

void freeTree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int n;
    TreeNode *root = NULL;

    if (scanf("%d", &n) != 1) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        char op;
        long long x, y;
        scanf(" %c", &op);

        if (op == 'I') {
            scanf("%lld", &x);
            root = insert(root, x);
        } else if (op == 'D') {
            scanf("%lld", &x);
            root = delete(root, x);
        } else if (op == 'Q') {
            scanf("%lld %lld", &x, &y);
            if (x > y) {
                long long tmp = x;
                x = y;
                y = tmp;
            }

            long long first, last;
            if (!lowerBound(root, x, &first) || first > y ||
                !upperBound(root, y, &last) || last < x) {
                printf("\n");
                continue;
            }

            TreeNode *node = lowestCommonAncestor(root, first, last);
            if (node == NULL) {
                printf("\n");
            } else {
                printf("%lld\n", node->key);
            }
        }
    }

    freeTree(root);
    return 0;
}
