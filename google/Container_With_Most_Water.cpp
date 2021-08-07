#include<vector>
#include<map>
#include<algorithm>
using namespace std;

/****
 * 11
 * 
 * 
 * Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of the line i is at (i, ai) and (i, 0). Find two lines, which, together with the x-axis forms a container, such that the container contains the most water.

Notice that you may not slant the container.

 

Example 1:


Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
Example 2:

Input: height = [1,1]
Output: 1
Example 3:

Input: height = [4,3,2,1,4]
Output: 16
Example 4:

Input: height = [1,2,1]
Output: 2
 

Constraints:

n == height.length
2 <= n <= 105
0 <= height[i] <= 104
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * /

/***
 * 
 * S1
 * 
 * 先把右边遍历一遍建立map
 * 
 * 然后从左边开始暴力搜索
 * 
 * 剪枝：离中心更近的点应该比离两端更近的点数值大
 * 
 * 
*/

class Solution {
    map<int, int> height_2_index;
public:
    int maxArea(vector<int>& height) {
        int total_len = height.size();

        int max_right = height[total_len - 1];
        height_2_index[max_right] = total_len - 1;
        for(int i = total_len - 2;i > 0;--i){
            int cur_height = height[i];
            if(cur_height <= max_right){continue;}
            max_right = cur_height;
            height_2_index[max_right] = i;
        }

        int max_area = 0;
        int max_left = height[0] - 1;
        for(int i = 0;i < total_len - 1;++i){
            int cur_height = height[i];
            if(cur_height <= max_left){continue;}
            max_left = cur_height;

            for(auto mpair: height_2_index){
                if(mpair.second <= i){break;}

                if(mpair.first < cur_height){
                    int area = mpair.first * (mpair.second - i);
                    max_area = max(area, max_area);
                }
                else{
                    int area = cur_height * (mpair.second - i);
                    max_area = max(area, max_area);
                    break;
                }
            }
        }

        return max_area;
    }
};

/***
 * S2
 * 
 * 
 * 
 * 双指针
 * 每次移动height小的那边
 * 
 * 
*/


class Solution {
public:
    int maxArea(vector<int>& height) {
        int max_area = 0;
        int left_point = 0;
        int right_point = height.size() - 1;
        while(right_point > left_point){
            int left_height = height[left_point];
            int right_height = height[right_point];
            int area;
            if(left_height <= right_height){
                area = left_height * (right_point - left_point); 
                left_point++;
            }
            else{
                area = right_height * (right_point - left_point);
                right_point--;
            }
            max_area = max(area, max_area);

        }
        return max_area;
    }
};