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
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        
        if(root==nullptr){
            return false;
        }
         // Process current node
        targetSum -= root->val;
        if(root->left==nullptr && root->right==nullptr && targetSum==0){
            return true;
        }
        return hasPathSum(root->left,targetSum) || hasPathSum(root->right,targetSum);
        
    }
};