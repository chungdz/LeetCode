/*
在排序数组中查找元素的第一个和最后一个位置
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

你的算法时间复杂度必须是 O(log n) 级别。

如果数组中不存在目标值，返回 [-1, -1]。

示例 1:

输入: nums = [5,7,7,8,8,10], target = 8
输出: [3,4]
示例 2:

输入: nums = [5,7,7,8,8,10], target = 6
输出: [-1,-1]
*/
#include <vector>
using namespace std;
/*
二分查找
当找到target的时候，更新vector，并且继续向两边二分
*/
class Solution {
    int my_t;
    vector<int> *my_v;
    int v_size;
    vector<int> result = {-1, -1};
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        my_t = target;
        my_v = &nums;
        v_size = nums.size();
        if(v_size != 0){
            iter_search(0, v_size - 1);
        }
        return result;
    }

    void iter_search(int begin, int end){
        /*判断是否越界*/
        if(begin > end){return;}
        /*判断是否长度为1*/
        if(begin == end){
            if((*my_v)[begin] == my_t){
                renew(begin);
                return;
            }
            else{return;}
        }
        /*查看是不是在这个范围里面*/
        if(my_t < (*my_v)[begin] || my_t > (*my_v)[end]){return;}
        /*二分查找*/
        else{
            int mid = (begin + end) / 2;
            if((*my_v)[mid] == my_t){
                renew(mid);
                iter_search(mid + 1, end);
                iter_search(begin, mid - 1);
            }
            else if((*my_v)[mid] < my_t){iter_search(mid + 1, end);}
            else{iter_search(begin, mid - 1);}
        }   
    }

    void renew(int pos){
        if(result[0] == -1){
            result[0] = pos;
            result[1] = pos;
            return;
        }
        
        if(pos < result[0]){result[0] = pos;}
        else if(pos > result[1]){result[1] = pos;}
    }
};