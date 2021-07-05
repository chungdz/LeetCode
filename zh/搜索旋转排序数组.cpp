/*
搜索旋转排序数组
假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。

你可以假设数组中不存在重复的元素。

你的算法时间复杂度必须是 O(log n) 级别。

示例 1:

输入: nums = [4,5,6,7,0,1,2], target = 0
输出: 4
示例 2:

输入: nums = [4,5,6,7,0,1,2], target = 3
输出: -1
*/
#include <vector>
using namespace std;

/*
解法一：
二分迭代搜索

具体搜索方式看下注释
*/
class Solution {
    int my_t;
    vector<int> *my_v;
    int v_size;
public:
    int search(vector<int>& nums, int target) {
        my_t = target;
        my_v = &nums;
        v_size = nums.size();
        if(v_size == 0){return -1;}
        return iter_search(0, v_size - 1);
    }

    int iter_search(int begin, int end){
        /*判断是否越界*/
        if(begin > end){return -1;}
        /*判断是否长度为1*/
        if(begin == end){
            if((*my_v)[begin] == my_t){return begin;}
            else{return -1;}
        }
        /*判断是否旋转，如果不旋转*/
        if((*my_v)[begin] < (*my_v)[end]){
            /*查看是不是在这个范围里面*/
            if(my_t < (*my_v)[begin] || my_t > (*my_v)[end]){return -1;}
            /*二分查找*/
            else{
                int mid = (begin + end) / 2;
                if((*my_v)[mid] == my_t){return mid;}
                else if((*my_v)[mid] < my_t){return iter_search(mid + 1, end);}
                else{return iter_search(begin, mid - 1);}
            }
        }
        /*如果旋转*/
        else{
            int mid = (begin + end) / 2;
            if((*my_v)[mid] == my_t){return mid;}
            else{
                int left = iter_search(begin, mid - 1);
                int right = iter_search(mid + 1, end);
                if(left != -1){return left;}
                else if(right != -1){return right;}
                else{return -1;}
            }
        }
    }
};