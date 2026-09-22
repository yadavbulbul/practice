// class Solution {
// public:
//     int uniquePaths(int m, int n) {
//         vector<vector<int>>dp(m,vector<int>(n,-1));
//         int ans = paths(0,0,m,n,dp);
//         return ans;
//     }

//     int paths(int i,int j,int m,int n,vector<vector<int>>&dp){
//         if(i==m-1 && j==n-1){
//             return 1;
//         }
        
//         if(i>m-1 || j>n-1){
//             return 0;
//         }
//         if(dp[i][j]!=-1){
//             return dp[i][j];
//         }
        
//         int left = paths(i+1,j,m,n,dp);
//         int right = paths(i,j+1,m,n,dp);
  
//         return dp[i][j]=left+right;
//     }
// };

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>>dp(m,vector<int>(n,-1));
        dp[0][0]=1;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){

                if(i == 0 && j == 0)
                    continue;

                int up = 0;
                int left = 0;

                if(i > 0)
                    up = dp[i-1][j];

                if(j > 0)
                    left = dp[i][j-1];

                dp[i][j] = up + left;
            }
        }
        return dp[m-1][n-1];
    }

   
};

