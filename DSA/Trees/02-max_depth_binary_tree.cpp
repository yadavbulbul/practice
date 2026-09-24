#include<iostream>
#include<vector>
#include<queue>

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

int maxDepth(TreeNode* node){
    if(node==nullptr){
        return 0;
    }

    int left = maxDepth(node->left);

    int right = maxDepth(node->right);

    return 1 + max(left,right);
}