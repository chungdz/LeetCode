/*
11

盛最多水的容器
给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

说明：你不能倾斜容器，且 n 的值至少为 2。
*/

/*
解法一：
宽搜索，从最宽的开始搜索，逐渐变窄
在搜索时，可以剪枝，把低于当前最低高度的边置为零

超出时间限制
*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int lenth = height.size();

        int c_len = lenth;
        int max_area = 0;
        int min_height = 0;
        while(c_len--){
            for(int i = 0;i + c_len < lenth;i++){
                int cur_height = min(height[i], height[i + c_len]);
                if(cur_height > min_height){
                    int area = cur_height * c_len;
                    if(area > max_area){
                        max_area = area;
                    }
                    min_height = cur_height;
                }
            }
        }
        return max_area;
    }
};

/*
解法二：
双指针，每次移动高度短的一边
*/