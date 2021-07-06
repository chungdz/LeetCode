#include<vector>
using namespace std;


/***
题目：
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and space is marked as 1 and 0 respectively in the grid.

Constraints:

m == obstacleGrid.length
n == obstacleGrid[i].length
1 <= m, n <= 100
obstacleGrid[i][j] is 0 or 1. 1 represents obstacle

 * ***/

/***
 * 基本思路： 递归，暴力搜索，加和子单元所有路径
 * 优化：记录被搜索过的子单元的路径数量（动态规划）
 * 
 * **/


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