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
int maxi=INT_MIN;
int maxPathSum(TreeNode* node){
    if(node==nullptr){
        return 0;
    }

    int left = max(0,maxPathSum(node->left));
    int right = max(0,maxPathSum(node->right));

    int currentPath = node->val + left + right;

    maxi = max(maxi, currentPath);

    //return only one side to parent
    return node->val + max(left,right);
}