#include<algorithm>
#include<vector>
using namespace std;

/*
240 Search a 2D Matrix II

Write an efficient algorithm that searches for a target value in an m x n integer matrix. The matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
 

Example 1:


Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true
Example 2:


Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
Output: false
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= n, m <= 300
-10^9 <= matrix[i][j] <= 10^9
All the integers in each row are sorted in ascending order.
All the integers in each column are sorted in ascending order.
-10^9 <= target <= 10^9

基本思想

solution 1 一行行做二分
solution 2 matrix级别的二分
1比2快
solution 3 Z字行走
从右上角开始，如果数字比target大，就往左，如果小，就往下，等于就返回
*/

class Solution1 {
    int m, n;
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        m = matrix.size();
        n = matrix[0].size();
        for(int i = 0;i < m;++i){
            if(target >= matrix[i][0]){
                vector<int>::iterator it = lower_bound(matrix[i].begin(), matrix[i].end(), target);
                if(it != matrix[i].end() && *it == target){return true;}
            }
        }
        return false;
    }
};

class Solution2 {
    int m, n;
    int tar;
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        m = matrix.size();
        n = matrix[0].size();
        tar = target;
        return search_split(matrix, 0, n - 1, 0, m - 1);
    }

    bool search_split(vector<vector<int>>& matrix, int l, int r, int t, int b){
        if(l > r){return false;}
        if(t > b){return false;}

        int rmid = (t + b) / 2;
        int cmid = (l + r) / 2;
        if(matrix[rmid][cmid] == tar){
            return true;
        }

        bool res = false;
        if(matrix[rmid][cmid] > tar){
            res |= search_split(matrix, l, cmid - 1, t, b);
            if(res){return res;}
            res |= search_split(matrix, cmid, r, t, rmid - 1);
        }
        else{
            res |= search_split(matrix, l, cmid, rmid + 1, b);
            if(res){return res;}
            res |= search_split(matrix, cmid + 1, r, t, b);
        }
        return res;
    }
};

class Solution {
    int m, n;
    int tar;
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        m = matrix.size();
        n = matrix[0].size();
        tar = target;
        return search_z(matrix, 0, n - 1);
    }

    bool search_z(vector<vector<int>>& matrix, int r, int c){
        if(r >= m){return false;}
        if(c < 0){return false;}

        if(matrix[r][c] > tar)
            return search_z(matrix, r, c - 1);
        else if(matrix[r][c] < tar)
            return search_z(matrix, r + 1, c);
        else
            return true;
    }
};


        