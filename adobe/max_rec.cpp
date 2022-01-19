#include<vector>
#include<algorithm>
using namespace std;

/*
84 Largest Rectangle in Histogram

Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

 

Example 1:


Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.
Example 2:


Input: heights = [2,4]
Output: 4
 

Constraints:

1 <= heights.length <= 10^5
0 <= heights[i] <= 10^4

基本思想

单调栈的应用

栈中保存index，保证height[index]的值单调递增，如果遇到比栈顶小的元素，就弹栈并计算面积
*/

class Solution {
    vector<int> monotonous_stack;
public:
    int largestRectangleArea(vector<int>& heights) {
        int hs = heights.size();
        int rec_max = -1;
        monotonous_stack.push_back(0);
        heights.push_back(-1);
        for(int i = 1;i <= hs;++i){
            
            while(monotonous_stack.size() > 0 && heights[i] < heights[monotonous_stack.back()]){
                int top_height = heights[monotonous_stack.back()];
                monotonous_stack.pop_back();
                int left;
                if(monotonous_stack.size() > 0){
                    left = monotonous_stack.back();
                }
                else{
                    left = -1;
                }
                int length = i - left - 1;
                rec_max = max(rec_max, top_height * length);
            }
            
            monotonous_stack.push_back(i);
        }
        return rec_max;
    }
};