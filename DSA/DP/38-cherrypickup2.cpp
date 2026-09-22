class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        //robo1 0 0
        //robo2 0 cols-1
        vector<vector<vector<int>>>dp(rows,vector<vector<int>>(cols,vector<int>(cols,-1)));
        int cherries = helper(0,0,cols-1,grid,rows,cols,dp);
        return cherries;
    }
    int helper(int i,int j1,int j2,vector<vector<int>>& grid,int rows,int cols,vector<vector<vector<int>>>&dp){
        //out of bound check
        if(i>=rows || j1<0 || j1>=cols || j2>=cols || j2<0){
            return 0;
        }

        if(dp[i][j1][j2]!=-1){
            return dp[i][j1][j2];
        }
        //base-condition
        if(i==rows-1){
            if(j1==j2){
                return grid[i][j1];
            }else{
                return grid[i][j1]+grid[i][j2];
            }
        }

        
        //explore all possibilities
        int maxi = 0;
        for(int dj1=-1;dj1<=1;dj1++){
            for(int dj2=-1;dj2<=1;dj2++){
                if(j1==j2){
                    maxi = max(maxi,grid[i][j1]+helper(i+1,j1+dj1,j2+dj2,grid,rows,cols,dp));
                }else{
                    maxi = max(maxi,grid[i][j1]+grid[i][j2]+helper(i+1,j1+dj1,j2+dj2,grid,rows,cols,dp));
                }
               
            }
        }
        return dp[i][j1][j2]=maxi;
    }
};