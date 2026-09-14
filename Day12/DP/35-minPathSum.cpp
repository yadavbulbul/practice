class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>>dp(m,vector<int>(n,-1));
        int res = helper(m-1,n-1,grid,m,n,dp);
        return res;
    }
    int helper(int i,int j,vector<vector<int>>& grid,int m,int n,vector<vector<int>>&dp){
        //out of bounds
        if(i <0 || j < 0) {
            return 1e9;;
        }
        
        //base case
        if(i==0 && j==0){
            return grid[i][j];
        }
        if(dp[i][j]!=-1){
            return dp[i][j];
        }
        
        int leftSum = grid[i][j]+helper(i,j-1,grid,m,n,dp);
        
        
        int upSum = grid[i][j]+helper(i-1,j,grid,m,n,dp);
        
        

        //select minimum;
        return dp[i][j]=min(leftSum,upSum);
    }
};