#include<vector>
#include<algorithm>
using namespace std;

/*
57

You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] represent the start and the end of the ith interval and intervals is sorted in ascending order by starti. You are also given an interval newInterval = [start, end] that represents the start and end of another interval.

Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).

Return intervals after the insertion.

 

Example 1:

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
Example 2:

Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
Example 3:

Input: intervals = [], newInterval = [5,7]
Output: [[5,7]]
Example 4:

Input: intervals = [[1,5]], newInterval = [2,3]
Output: [[1,5]]
Example 5:

Input: intervals = [[1,5]], newInterval = [2,7]
Output: [[1,7]]
 

Constraints:

0 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 105
intervals is sorted by starti in ascending order.
newInterval.length == 2
0 <= start <= end <= 105

基本思想

二分查找，建立新数组用作存储

**/

bool comp(const vector<int>& v1, const vector<int>& v2){
    return v1[0] < v2[0];
}

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>>::iterator it = lower_bound(intervals.begin(), intervals.end(), newInterval, comp);
        int cur_index = it - intervals.begin();
        if(cur_index > 0){cur_index -= 1;}
        intervals.insert(it, newInterval);
        
        vector<vector<int>> res;
        int res_index;
        for(res_index = 0;res_index <= cur_index;++res_index){
            res.push_back(intervals[res_index]);
        }
        
        int index = res_index;
        res_index--;
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