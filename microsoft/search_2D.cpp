#include<algorithm>
#include<vector>
using namespace std;

/*
74 Search a 2D Matrix

Solution
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
 

Example 1:


Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true
Example 2:


Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-10^4 <= matrix[i][j], target <= 10^4

基本思想

二分法，搜索row的时候也应该用二分法
*/

class Solution {
    int m, n;
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        m = matrix.size();
        n = matrix[0].size();
        for(int i = 0;i < m - 1;++i){
            if(target >= matrix[i][0] && target <= matrix[i][n - 1]){
                vector<int>::iterator it = lower_bound(matrix[i].begin(), matrix[i].end(), target);
                if(it != matrix[i].end() && *it == target){return true;}
                else{return false;}
            }
        }
        if(target >= matrix[m - 1][0]){
            vector<int>::iterator it = lower_bound(matrix[m - 1].begin(), matrix[m - 1].end(), target);
            if(it != matrix[m - 1].end() && *it == target){return true;}
            else{return false;}
        }
        return false;
    }
};
        