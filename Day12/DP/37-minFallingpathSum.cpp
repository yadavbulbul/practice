class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int ans = INT_MAX;
        vector<vector<int>>dp(n,vector<int>(n,INT_MAX));
        // We can start from ANY column in the first row
        for(int col = 0; col < n; col++) {
            ans = min(ans, helper(0, col, matrix, n,dp));
        }

        return ans;
    }
    int helper(int row,int col,vector<vector<int>>& matrix,int n,vector<vector<int>>&dp){
        // Out of bounds
        if(col < 0 || col >= n) {
            return 1e9;
        }

        // Reached last row
        if(row == n-1) {
            return matrix[row][col];
        }

        if(dp[row][col]!=INT_MAX){
            return dp[row][col];
        }
        
        int choice1 = matrix[row][col]+helper(row+1,col-1,matrix,n,dp);
        int choice2 = matrix[row][col]+helper(row+1,col,matrix,n,dp);
        int choice3 = matrix[row][col]+helper(row+1,col+1,matrix,n,dp);

        return dp[row][col]=min(min(choice1,choice2),choice3);
        
    }
};