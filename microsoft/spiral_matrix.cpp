#include<algorithm>
#include<unordered_set>
#include<vector>
using namespace std;

/*
54

Spiral Matrix

Given an m x n matrix, return all elements of the matrix in spiral order.

 

Example 1:


Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]
Example 2:


Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 10
-100 <= matrix[i][j] <= 100

基本思想

写一个next point函数，计算下一个坐标
每次越界或者是回到之前访问过的点，就切换方向，方向切换顺序是固定的，所以用数组保存
*/

class Solution {
    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int m, n;
    int cur_dir = 0;
    int point[2] = {0, 0};
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        m = matrix.size();
        n = matrix[0].size();
        vector<int> res;
        res.push_back(matrix[0][0]);
        matrix[0][0] = -200;
        for(int i = 1;i < m * n;++i){
            next_point(matrix);
            res.push_back(matrix[point[0]][point[1]]);
            matrix[point[0]][point[1]] = -200;
        }
        return res;
    }

    void next_point(vector<vector<int>>& matrix){
        int nxt_r = point[0] + dir[cur_dir][0];
        int nxt_c = point[1] + dir[cur_dir][1];
        if(nxt_r < 0 || nxt_r >= m || nxt_c < 0 || nxt_c >= n || matrix[nxt_r][nxt_c] == -200){
            cur_dir = (cur_dir + 1) % 4;
            nxt_r = point[0] + dir[cur_dir][0];
            nxt_c = point[1] + dir[cur_dir][1];
        }
        point[0] = nxt_r;
        point[1] = nxt_c;
    }
};