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


void levelTraversal(TreeNode* node){

    if(node == nullptr){
        return;
    }
    queue<TreeNode*>q;
    q.push(node);
    cout<<"level order traversal"<<endl;
    while(!q.empty()){
        TreeNode* node = q.front();
        
        cout<<node->val<<" ";
        q.pop();
        if(node->left!=nullptr){
            q.push(node->left);
        }
        if(node->right!=nullptr){
            q.push(node->right);
        }
    }
}

vector<vector<int>> BFS(TreeNode* node){
    
    vector<vector<int>>res;
    if(node == nullptr){
        return res;
    }
    queue<TreeNode*>q;
    q.push(node);

    while(!q.empty()){
        int qSize = q.size();
        vector<int>temp;
        for(int i=0;i<qSize;i++){
            TreeNode* node = q.front();
            temp.push_back(node->val);
            q.pop();
            if(node->left!=nullptr){
                q.push(node->left);
            }
            if(node->right!=nullptr){
                q.push(node->right);
            }

        }
        res.push_back(temp);
    }
    return res;
}

