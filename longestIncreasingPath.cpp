class Solution {
    vector<vector<int>> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };      // This portion of the solution initializes some variables and
    int rows, cols, longest = 0;                                                // vectors as directions for simplicity.
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {                    // This portion of the function checks the size of the matrix.
        rows = matrix.size();                                                   // If the matrix has no size (0), the function will return
        if(!rows) {                                                             // empty. Otherwise, it will note both the number of rows and
            return 0;                                                           // columns that the matrix has, then sets up a second matrix and 
        }                                                                       // queue to keep count of the possible longest paths.
        cols = matrix[0].size();
        vector<vector<int>> Indegree(rows, vector<int>(cols));
        queue<pair<int, int>> q;
        
        for(int i = 0; i < rows; i++) {                                         // This portion of the function checks whether or not a 
            for(int j = 0; j < cols; j++) {                                     // specific cell on the matrix has any cells around it that are 
                for(auto &d: directions) {                                      // out-of-bounds. Otherwise, it counts all the possible
                    int x = i + d[0];                                           // increasing path ending points within the secondary matrix.
                    int y = j + d[1];
                    if(x >= 0 && x < rows && y >= 0 && y < cols) {
                        if(matrix[x][y] < matrix[i][j]) {
                            Indegree[i][j]++;
                        }
                    }
                }
                if(!Indegree[i][j]) {                                           // If there is no increasing path points possible at the moment,
                    q.push({i, j});                                             // the points are pushed into a queue.
                }
            }
        }
        while(!q.empty()){                                                      // This portion of the function notes the size of the queue if
            int size = q.size();                                                // it isn't empty, then checks the current matrix cell location.
            while(size--){                                                      // The function will then check every other direction for
                pair<int,int> current = q.front();                              // neighboring cells. After another out-of-bounds check, if a
                q.pop();                                                        // cell with a greater increment is found, the function will note
                for(auto &d: directions){                                       // the current length of the longest path and said cell. Once that
                    int x = current.first + d[0];                               // is done, the current matrix cell is scrubbed and the function
                    int y = current.second + d[1];                              // will loop until the entire matrix is checked.
                    if(x >= 0 && x < rows && y >= 0 && y < cols){
                        if(matrix[x][y] > matrix[current.first][current.second] && --Indegree[x][y] == 0) {
                            q.push({x,y});
                        }
                    }
                }
            }
            longest++;                                                          // Once the queue is empty, the function will return the length
        }                                                                       // of the longest increasing path.
        return longest;
    }
};
