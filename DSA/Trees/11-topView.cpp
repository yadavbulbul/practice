#include<iostream>
#include<vector>
#include<queue>
#include<map>

using namespace std;

class Node {
  public:
    int data;
    Node* left, *right;
    Node(int data) {
        data = data;
        left = right = nullptr;
    }

};

class Solution {
  public:
    vector<int> topView(Node *root) {
        // code here
        vector<int>res;
        
        //map to store and check nodes in that line if exist we'll not take it
        map<int,int>mpp;
        //pair of node and the vertical line
        queue<pair<Node*,int>>q;
        q.push({root,0});
        
        while(!q.empty()){
            Node* node = q.front().first;
            int line = q.front().second;
            
            q.pop();
            if(mpp.find(line)==mpp.end()){
                mpp[line]=node->data;
            }
            if(node->left){
                q.push({node->left,line-1});
            }
            if(node->right){
                q.push({node->right,line+1});
            }
        }
        for(auto x:mpp){
            res.push_back(x.second);
        }
        return res;
    }
};