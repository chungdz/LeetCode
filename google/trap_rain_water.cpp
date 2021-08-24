#include<vector>
#include<map>
#include<algorithm>
using namespace std;

/**
 * 42
 * 
 * 
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

 

Example 1:


Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9
 

Constraints:

n == height.length
1 <= n <= 2 * 10^4
0 <= height[i] <= 10^5
 * 
 * 
 * 基本思路
 * 
 * 移动窗口，每次找到两个蓄水的bar，从左往右找最大值或者是最高点
 * 
 * 
 * 
 * 基本思路2
 * 
 * 下标i的雨水等于左边的最高点和右边的最高点的最小值
 * 
 * 
 */

class Solution {
    
    int total_water(int l, int r, vector<int>& height){
        int total_sum = 0;
        int water_height = min(height[l], height[r]);
        for(int i = l + 1;i < r;++i){
            total_sum += water_height - height[i];
        }
        return total_sum;
    }
public:
    int trap(vector<int>& height) {
        int total_len = height.size();

        int left = 0;
        int l_height = height[0];
        int sum_w = 0;
        while(left < total_len - 1){
            int right = left + 1;
            int max_right = -1;
            int max_pos;
            while(right < total_len){
                if(height[right] > max_right){
                    max_right = height[right];
                    max_pos = right;
                }   
                if(max_right >= l_height){break;}
                right += 1;
            }

            sum_w += total_water(left, max_pos, height);
            left = max_pos;
            l_height = max_right;
        }

        return sum_w;
    }
};


class Solution {
    
    int left_max[100000];
    int right_max[100000];
public:
    int trap(vector<int>& height) {
        int total_len = height.size();

        int cur_max = height[0];
        left_max[0] = cur_max;
        for(int i = 1;i < total_len;++i){
            cur_max = max(cur_max, height[i]);
            left_max[i] = cur_max;
        }

        cur_max = height[total_len - 1];
        right_max[total_len - 1] = cur_max;
        for(int i = total_len - 2;i >= 0;--i){
            cur_max = max(cur_max, height[i]);
            right_max[i] = cur_max;
        }

        int sum_w = 0;
        int cur_w;
        for(int i = 1;i < total_len - 1;++i){
            cur_w = min(left_max[i], right_max[i]) - height[i];
            if(cur_w > 0){
                sum_w += cur_w;
            }
        }

        return sum_w;
    }
};