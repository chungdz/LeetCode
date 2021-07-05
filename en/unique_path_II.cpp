#include<vector>
using namespace std;

class Solution {
    int m;
    int n;
    vector<vector<int>> *myGrid;
    vector<vector<int>> record;

    int check_path(int row, int column){
        if(record[row][column] != -1){
            return record[row][column];
        }
        // find path
        int next_row = row + 1;
        int next_column = column + 1;
        int total_path = 0;
        if(next_row < m && (*myGrid)[next_row][column] != 1){
            total_path += check_path(next_row, column);
        }
        if(next_column < n && (*myGrid)[row][next_column] != 1){
            total_path += check_path(row, next_column);
        }
        record[row][column] = total_path;
        return total_path;
    }

public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        m = obstacleGrid.size();
        n = obstacleGrid[0].size();
        myGrid = &obstacleGrid;
        for(int i = 0;i < m;i++){
            record.push_back(vector<int>(n, -1));
        }

        if((*myGrid)[m - 1][n - 1] == 1){return 0;}
        else{record[m - 1][n - 1] = 1;}
        if((*myGrid)[0][0] == 1){return 0;}
        return check_path(0, 0);
    }
};