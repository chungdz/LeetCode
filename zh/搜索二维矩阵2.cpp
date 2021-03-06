/*
240

搜索二维矩阵 II
编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target。该矩阵具有以下特性：

每行的元素从左到右升序排列。
每列的元素从上到下升序排列。
示例:

现有矩阵 matrix 如下：

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
给定 target = 5，返回 true。

给定 target = 20，返回 false。
*/
#include <vector>
using namespace std;

/*
解法：
竖向二分，先从二维中心查询，大就往下走，小就往上走，四块区域总有三块有数字

根据第一个和最后一个确立区间，进行横向二分
*/

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        
    }
};