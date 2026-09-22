class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n);
        for(int i = 0; i < n; i++) {
            dp[i] = vector<int>(i + 1, INT_MAX);
        }
        int res = helper(triangle,n,0,0,dp);
        return res;
    }
    int helper(vector<vector<int>>& triangle,int n,int row,int i,vector<vector<int>> &dp){
        if(row==n-1){
            return dp[row][i]=triangle[row][i];
        }
        if(dp[row][i]!=INT_MAX){
            return dp[row][i];
        }
        int choice1 = triangle[row][i]+helper(triangle,n,row+1,i,dp);
        int choice2 = triangle[row][i]+helper(triangle,n,row+1,i+1,dp);
        return dp[row][i]=min(choice1,choice2);
    }
};