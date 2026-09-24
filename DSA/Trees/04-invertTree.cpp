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

TreeNode* invertTree(TreeNode* node){
    if(node==nullptr){
        return node;
    }
    swap(node->left,node->right);
    invertTree(node->left);
    invertTree(node->right);
    return node;
}