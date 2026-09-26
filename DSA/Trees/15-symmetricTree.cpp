#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<set>

using namespace std;

class TreeNode{
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val,TreeNode* left,TreeNode* right){
        this->val=val;
        this->left=left;
        this->right=right;
    }

    TreeNode(int val){
        this->val=val;
        this->left=nullptr;
        this->right=nullptr;
    }
};
class Solution {
public:
    bool isSymmetric(TreeNode* root) {

        if(root == nullptr)
            return true;

        return check(root->left, root->right);
    }

    bool check(TreeNode* left, TreeNode* right) {

        if(left == nullptr && right == nullptr)
            return true;

        if(left == nullptr || right == nullptr)
            return false;

        if(left->val != right->val)
            return false;

        return check(left->left, right->right) &&
            check(left->right, right->left);
    }
};