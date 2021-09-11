#include<vector>
#include<algorithm>
using namespace std;

/*
329


Given an m x n integers matrix, return the length of the longest increasing path in matrix.

From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).

 

Example 1:


Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].
Example 2:


Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
Example 3:

Input: matrix = [[1]]
Output: 1
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
0 <= matrix[i][j] <= 2^31 - 1




基本思想

动态规划

因为是增长路径，所以访问过的节点在之后不会再次访问，使得动态规划成为可能


当前节点为起点的最大路径 = 四周的最大路径（四周中matrix value大于当前节点的才合规） + 1



**/

class Solution {
    int max_value[201][201] = {0};
    int max_path = 0;
    int row, column;
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        row = matrix.size();
        column = matrix[0].size();
        for(int i = 0;i < row;++i){
            for(int j = 0;j < column;++j){
                max_path = max(max_path, cur_value(i, j, matrix));
            }
        }
        return max_path;
    }

    int cur_value(int m, int n, vector<vector<int>>& matrix){
        if(max_value[m][n] != 0){return max_value[m][n];}

        int cur_max = 1;
        if(m - 1 >= 0 && matrix[m - 1][n] > matrix[m][n]){cur_max = max(cur_max, 1 + cur_value(m - 1, n, matrix));}
        if(n - 1 >= 0 && matrix[m][n - 1] > matrix[m][n]){cur_max = max(cur_max, 1 + cur_value(m, n - 1, matrix));}
        if(m + 1 < row && matrix[m + 1][n] > matrix[m][n]){cur_max = max(cur_max, 1 + cur_value(m + 1, n, matrix));}
        if(n + 1 < column && matrix[m][n + 1] > matrix[m][n]){cur_max = max(cur_max, 1 + cur_value(m, n + 1, matrix));}

        max_value[m][n] = cur_max;
        return cur_max;
    }
};