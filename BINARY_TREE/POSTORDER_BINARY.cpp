#include <vector>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};



vector<int> postorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> s;
    TreeNode* last = nullptr;
    while (root || !s.empty()) {
        if (root) {
            s.push(root);
            root = root->left;
        } else {
            TreeNode* node = s.top();
            if (node->right && node->right != last) {
                root = node->right;
            } else {
                result.push_back(node->val);
                last = node;
                s.pop();
            }
        }
    }
    return result;
}