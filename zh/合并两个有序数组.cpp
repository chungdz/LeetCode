/*
给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。

 

说明:

初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
 

示例:

输入:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

输出: [1,2,2,3,5,6]
*/

#include <vector>
using namespace std;
/*
解法一
将二放入一，然后使用sort来解决
时间复杂度(m + n)log(m + n)
*/

/*
解法二
双指针从头到尾遍历，放入新开的数组里面
时间复杂度(m + n)
空间复杂度(m + n)
*/

/*
解法三
双指针，从后往前插入排序
不需要新开数组
*/
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int lenth_1 = nums1.size();
        
        int p1 = m - 1;
        int p2 = n - 1;
        int pf = m + n - 1;

        while(pf >= 0){

            if(p1 < 0){
                while(p2 >= 0){
                    nums1[pf] = nums2[p2];
                    pf--;
                    p2--;
                }
                break;
            }
            else if(p2 < 0){
                break;
            }

            if(nums1[p1] > nums2[p2]){
                nums1[pf] = nums1[p1];
                p1--;
            }
            else{
                nums1[pf] = nums2[p2];
                p2--;
            }
            pf--;
        }

        return;
    }
};