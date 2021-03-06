#include<vector>
#include<algorithm>
using namespace std;

/*

852

Let's call an array arr a mountain if the following properties hold:

arr.length >= 3
There exists some i with 0 < i < arr.length - 1 such that:
arr[0] < arr[1] < ... arr[i-1] < arr[i]
arr[i] > arr[i+1] > ... > arr[arr.length - 1]
Given an integer array arr that is guaranteed to be a mountain, return any i such that arr[0] < arr[1] < ... arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1].

 

Example 1:

Input: arr = [0,1,0]
Output: 1
Example 2:

Input: arr = [0,2,1,0]
Output: 1
Example 3:

Input: arr = [0,10,5,2]
Output: 1
Example 4:

Input: arr = [3,4,5,1]
Output: 2
Example 5:

Input: arr = [24,69,100,99,79,78,67,36,26,19]
Output: 2
 

Constraints:

3 <= arr.length <= 10^4
0 <= arr[i] <= 10^6
arr is guaranteed to be a mountain array.
 

Follow up: Finding the O(n) is straightforward, could you find an O(log(n)) solution?


基本思想

如果是正常暴力搜索，直接从0搜索到peak的位置就行了，o(n)复杂度

可以二分查找


**/

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        return search_peak(arr, 0, arr.size());
    }

    int search_peak(vector<int>& arr, int l, int r){

        int mid = (l + r) / 2;
        if(arr[mid - 1] < arr[mid]){
            if(arr[mid + 1] < arr[mid]){
                return mid;
            }

            int new_l = mid + 1;
            return search_peak(arr, new_l, r);
        }
        else{
            int new_r = mid;
            return search_peak(arr, l, new_r);
        }

    }
};