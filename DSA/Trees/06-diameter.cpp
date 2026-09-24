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
int diameter=0;
int calculateDiameter(TreeNode* node){
    if(node==nullptr){
        return 0;
    }

    int left = calculateDiameter(node->left);
    int right = calculateDiameter(node->right);
    int diameter = max(diameter,left+right);
    int height = 1 + max(left,right);
    return height;
}