#include<vector>
#include<algorithm>
using namespace std;

/*

56

Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

 

Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
Example 2:

Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 

Constraints:

1 <= intervals.length <= 10^4
intervals[i].length == 2
0 <= starti <= endi <= 10^4


基本思想

排序后合并


**/

bool comp(const vector<int>& v1, const vector<int>& v2){
    return v1[0] < v2[0];
}

/*
time limit exceed
**/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), comp);
        int index = 1;
        while(index < intervals.size()){
            int pre_end = intervals[index - 1][1];
            if(pre_end >= intervals[index][0]){
                if(pre_end <= intervals[index][1]){
                    intervals[index - 1][1] = intervals[index][1];
                }
                intervals.erase(intervals.begin() + index);
            }
            else{
                index++;
            }
        }
        return intervals;
    }
};

/*
优化，新建vector存储答案
**/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), comp);
        vector<vector<int>> res;
        res.push_back(intervals[0]);

        int index = 1;
        int res_index = 0;
        while(index < intervals.size()){
            int pre_end = res[res_index][1];
            if(pre_end >= intervals[index][0]){
                if(pre_end <= intervals[index][1]){
                    res[res_index][1] = intervals[index][1];
                }
            }
            else{
                res.push_back(intervals[index]);
                res_index++;
            }
            index++;
        }
        return res;
    }
};