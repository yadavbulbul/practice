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

pair<bool,int> check(TreeNode* node) {

    // base case
    if(node==nullptr){
        return {true,0};
    }

    // get left information
    pair<bool,int>left = check(node->left);

    // get right information
    pair<bool,int>right = check(node->right);

    // calculate current balance
    bool balanced = left.first && right.first && abs(left.second-right.second)<=1;

    // calculate current height
    int height = 1 + max(left.second,right.second);

    // return both
    return {balanced,height};
}