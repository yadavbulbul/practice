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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>res;
        if(root==nullptr){
            return {};
        }

        queue<TreeNode*>q;
        q.push(root);
        //true means left to right
        //false means right to left
        bool flag = true;
        while(!q.empty()){
            int size = q.size();
            vector<int>temp(size,-1);
            for(int i=0;i<size;i++){
                TreeNode* node = q.front();
                q.pop();
                int index;
                if(flag){
                    index=i;
                }else{
                    index=size-1-i;
                }
                temp[index]=node->val;

                if(node->left !=nullptr){
                    q.push(node->left);
                }
                if(node->right !=nullptr){
                    q.push(node->right);
                }

            }
            res.push_back(temp);
            flag=!flag;
        }
        return res;
    }
};

