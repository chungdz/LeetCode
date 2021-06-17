/*
合并区间
给出一个区间的集合，请合并所有重叠的区间。

示例 1:

输入: [[1,3],[2,6],[8,10],[15,18]]
输出: [[1,6],[8,10],[15,18]]
解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
示例 2:

输入: [[1,4],[4,5]]
输出: [[1,5]]
解释: 区间 [1,4] 和 [4,5] 可被视为重叠区间。
*/

#include <vector>
#include <iostream>
using namespace std;


/*
解法
根据左位置排序

排序之后根据新的位置来合并
*/
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        
    }
};