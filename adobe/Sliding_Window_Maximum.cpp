#include<vector>
#include<map>
#include<algorithm>
using namespace std;

/*
239 Sliding Window Maximum

You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

 

Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:

Input: nums = [1], k = 1
Output: [1]

基本思想

map用来做排序
*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        map<int, int> ncount;
        int ns = nums.size();
        for(int i = 0;i < k;++i)
            if(ncount.find(nums[i]) != ncount.end())
                ncount[nums[i]] += 1;
            else
                ncount[nums[i]] = 1;
        
        vector<int> res;
        res.push_back(ncount.rbegin()->first);
        
        int s = 1, e = k;
        while(e < ns){
            // add e
            if(ncount.find(nums[e]) != ncount.end())
                ncount[nums[e]] += 1;
            else
                ncount[nums[e]] = 1;
            // del s
            ncount[nums[s - 1]] -= 1;
            if(ncount[nums[s - 1]] == 0)
                ncount.erase(nums[s - 1]);
            
            res.push_back(ncount.rbegin()->first);
            s += 1;
            e += 1;
        }

        return res;
    }
};