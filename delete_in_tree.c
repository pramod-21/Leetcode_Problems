/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* findMin(struct TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    } 
    else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    } 
    else {
        // Case 1: Node has no child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // Case 2: Node has one child
        else if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        // Case 3: Node has two children
        else {
            struct TreeNode* temp = findMin(root->right); // Find inorder successor
            root->val = temp->val; // Copy value
            root->right = deleteNode(root->right, temp->val); // Delete successor
        }
    }
    return root;
}