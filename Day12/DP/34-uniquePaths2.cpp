class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>>dp(m,vector<int>(n,-1));
        int res = paths(0,0,m,n,obstacleGrid,dp);
        return res;
    }
    int paths(int i,int j,int m,int n,vector<vector<int>>& obstacleGrid,vector<vector<int>>&dp){
        // Out of bounds
        if(i >= m || j >= n) {
            return 0;
        }
        if(dp[i][j]!=-1){
            return dp[i][j];
        }
        // Obstacle
        if(obstacleGrid[i][j] == 1) {
            return 0;
        }

        // Destination
        if(i == m-1 && j == n-1) {
            return 1;
        }

        int right = paths(i, j+1, m, n, obstacleGrid,dp);
        int down = paths(i+1, j, m, n, obstacleGrid,dp);

        return dp[i][j]=right + down;
    }
};