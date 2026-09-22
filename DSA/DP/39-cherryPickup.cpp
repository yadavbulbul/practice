class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        // Both routes are reversed so both people
        // travel from (0,0) -> (rows-1,cols-1)
        int cherries = helper(0, 0, 0, 0, rows, cols, grid);

        return max(0, cherries);
    }

    int helper(int i1, int j1, int i2, int j2, int rows, int cols,vector<vector<int>>& grid) {

        // Out of bounds
        if (i1 >= rows || j1 >= cols || i2 >= rows || j2 >= cols) {
            return -1e9;
        }

        // Thorn
        if (grid[i1][j1] == -1 || grid[i2][j2] == -1) {
            return -1e9;
        }

        // Current cherries
        int cherries;

        if (i1 == i2 && j1 == j2) {
            // Same cell -> count only once
            cherries = grid[i1][j1];
        } else {
            // Different cells -> count both
            cherries = grid[i1][j1] + grid[i2][j2];
        }

        // Both reached destination
        if (i1 == rows - 1 && j1 == cols - 1 && i2 == rows - 1 &&
            j2 == cols - 1) {
            return cherries;
        }

        // Four possibilities
        int option1 = helper(i1 + 1, j1, i2 + 1, j2, rows, cols, grid);

        int option2 = helper(i1 + 1, j1, i2, j2 + 1, rows, cols, grid);

        int option3 = helper(i1, j1 + 1, i2 + 1, j2, rows, cols, grid);

        int option4 = helper(i1, j1 + 1, i2, j2 + 1, rows, cols, grid);

        int best = max({option1, option2, option3, option4});

        return cherries + best;
    }
};