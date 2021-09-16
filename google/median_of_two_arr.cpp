#include<vector>
#include<algorithm>
using namespace std;

/*
4

Median of Two Sorted Arrays
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

 

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
Example 3:

Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.00000
Example 4:

Input: nums1 = [], nums2 = [1]
Output: 1.00000
Example 5:

Input: nums1 = [2], nums2 = []
Output: 2.00000
 

Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-10^6 <= nums1[i], nums2[i] <= 10^6


基本思路

不要从普通二分法来做，普通二分法分别从两序列中间找很麻烦

用缩减法，把问题看成找第k小的数，每次缩小k的数值的同时提高两数组的下限

**/

class Solution {
public:
    int getKthElement(const vector<int>& nums1, const vector<int>& nums2, int k) {
        
        int s1 = nums1.size();
        int s2 = nums2.size();
        int index1 = 0, index2 = 0;
        int cur_m = k;

        while(true){
            if(index1 >= s1){
                return nums2[cur_m + index2 - 1];
            }
            else if(index2 >= s2){
                return nums1[cur_m + index1 - 1];
            }
            else if(cur_m == 1){
                return min(nums1[index1], nums2[index2]);
            }

            int f1 = index1 + cur_m / 2 - 1;
            if(f1 >= s1){
                f1 = s1 - 1;
            }
            int f2 = index2 + cur_m / 2 - 1;
            if(f2 >= s2){
                f2 = s2 - 1;
            }

            if(nums1[f1] <= nums2[f2]){
                cur_m = cur_m - (f1 - index1 + 1);
                index1 = f1 + 1;
            }
            else{
                cur_m = cur_m - (f2 - index2 + 1);
                index2 = f2 + 1;
            }

        }
        
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int totalLength = nums1.size() + nums2.size();
        if (totalLength % 2 == 1) {
            return getKthElement(nums1, nums2, (totalLength + 1) / 2);
        }
        else {
            return (getKthElement(nums1, nums2, totalLength / 2) + getKthElement(nums1, nums2, totalLength / 2 + 1)) / 2.0;
        }
    }
};