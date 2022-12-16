class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int color = 2;
        unordered_map<int, int> sizes;                              // This portion of the function creates an unordered map that represents
        for (int i = 0; i < grid.size(); i++) {                     // island sizes. It checks for whether or not there is a 1 on the grid
            for (int j = 0; j < grid[0].size(); j++) {              // or not, and if it does, it will assign a color to that specific area.
                if (grid[i][j] == 1) {                              // The function will continue to loop until it checks every index of the
                    int count = 0;                                  // grid, assigning values to them.
                    colorize(grid, i, j, color, count);
                    sizes[color] = count;
                    color++;
                }
            }
        }
        int res = 1;                                                // This portion of the function will check the unordered map to see which
        for (auto kv : sizes) {                                     // island (by assigned color) is the biggest.
            res = max(res, kv.second);
        }
        for (int i = 0; i < grid.size(); i++) {                     // If the biggest island has adjacented islands near it, this portion of
            for (int j = 0; j < grid[0].size(); j++) {              // the function will check if the neigboring islands are bigger, replacing
                if (grid[i][j] == 0) {                              // the current island if so.
                    res = max(res, change(grid, sizes, i, j));
                }
            }
        }

        return res;                                                 // Returns the size of the biggest island.
    }
    
    void colorize(vector<vector<int>>& grid, int i, int j, int color, int& count) {
        count++;
        grid[i][j] = color;                                         // This other function helps mark places on the grid with a specific color
        if (i - 1 >= 0 && grid[i - 1][j] == 1) {                    // and recurrs by checking if areas around a specific location is adjacent
            colorize(grid, i - 1, j, color, count);                 // land. It will count the size of the said color island on resolution.
        } if (i + 1 < grid.size() && grid[i + 1][j] == 1) {
            colorize(grid, i + 1, j, color, count);
        } if (j - 1 >= 0 && grid[i][j - 1] == 1) {
            colorize(grid, i, j - 1, color, count);
        } if (j + 1 < grid[0].size() && grid[i][j + 1] == 1) {
            colorize(grid, i, j + 1, color, count);
        }
    }
    
    int change(vector<vector<int>>& grid, unordered_map<int, int>& sizes, int i, int j)
    {
        set<int> neighbors;                                         // This other function helps discover neighboring islands that are next to
        if (i - 1 >= 0 && grid[i - 1][j] > 1) {                     // an indicated location. It creates a set that notes grid areas that count
            neighbors.insert(grid[i - 1][j]);                       // as island. It will then count up and return the size of that neighboring
        } if (i + 1 < grid.size() && grid[i + 1][j] > 1) {          // island.
            neighbors.insert(grid[i + 1][j]);
        } if (j - 1 >= 0 && grid[i][j - 1] > 1) {
            neighbors.insert(grid[i][j - 1]);
        } if (j + 1 < grid[0].size() && grid[i][j + 1] > 1) {
            neighbors.insert(grid[i][j + 1]);
        }
                                                                
        int res = 1;
        for (int c:neighbors) {
            res += sizes[c];
        }

        return res;
    }
};
