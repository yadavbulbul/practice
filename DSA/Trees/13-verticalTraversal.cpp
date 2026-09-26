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
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        // map<int,vector<int>>mpp;
        map<int, map<int, multiset<int>>> mpp;
        //node,row,line(col)
        queue<pair<TreeNode*, pair<int,int>>> q;
        vector<vector<int>>res;
        q.push({root,{0,0}});

        while(!q.empty()){
            TreeNode* node = q.front().first;
            int line = q.front().second.second;
            int row= q.front().second.first;
            mpp[line][row].insert(node->val);
            q.pop();

            if(node->left){
                q.push({node->left,{row+1,line-1}});
            }
            if(node->right){
                q.push({node->right,{row+1,line+1}});
            }
        }
        for(auto x : mpp){
            vector<int> temp;
            for(auto y : x.second){
                for(auto val : y.second){
                    temp.push_back(val);
                }
            }
            res.push_back(temp);
        }
        return res;
    }
};