#include<iostream>
#include<vector>
#include<queue>

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
    bool ifLeafNode(Node* node){
        if(node->left == nullptr && node->right==nullptr){
            return true;
        }
        return false;
    }
    void addLeftBoundary(Node* node,vector<int>&res){
        while(node){
            if(!ifLeafNode(node)){
                res.push_back(node->data);
            }
            if(node->left){
                node=node->left;
            }else{
                node=node->right;
            }
            
            
        }
    }
    void addRightBoundary(Node* node,vector<int>&res){
        vector<int>temp;
        while(node){
            if(!ifLeafNode(node)){
                temp.push_back(node->data);
            }
            if(node->right){
                node=node->right;
            }else{
                node=node->left;
            }
            
        }
        for(int i=temp.size()-1;i>=0;i--){
            
            res.push_back(temp[i]);
        }
            
    }
    void addLeaves(Node* node,vector<int>&res){
        if(ifLeafNode(node)){
            res.push_back(node->data);
            return;
        }
        if(node->left){
            addLeaves(node->left,res);
        }
        if(node->right){
            addLeaves(node->right,res);
        }
        
    }
    vector<int> boundaryTraversal(Node *root) {
        // code here
        vector<int>res;
        if(root==nullptr){
            return res;
        }
        if(!ifLeafNode(root)){
            res.push_back(root->data);
        }
        addLeftBoundary(root->left,res);
        addLeaves(root,res);
        addRightBoundary(root->right,res);
        return res;
    }
};