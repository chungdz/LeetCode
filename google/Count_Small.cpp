#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

/*
315

Count of Smaller Numbers After Self

Solution
You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

 

Example 1:

Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Example 2:

Input: nums = [-1]
Output: [0]
Example 3:

Input: nums = [-1,-1]
Output: [0,0]
 

Constraints:

1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4

基本思想

树状数组的典型应用题

题目要求维持对每个i来说，i右边每个数字的数量，然后返回小于i的数值的数量和

在这里数值不超过正负10000，所以直接给每个数字加上大于10000的offset，使得它们都能被树状数组保存，如果数值距离太大，需要先离散化

**/

class BIT{
    int *bit;
    int n;
public:
    BIT(int number){
        n = number;
        bit = new int[n + 1];
        for(int j = 1;j <= n;++j){
            bit[j] = 0;
        }
    }

    int _sum(int i){
        int s = 0;
        while(i > 0){
            s += bit[i];
            i -= i & -i;
        }
        return s;
    }

    void _add(int i, int x){
        while(i <= n){
            bit[i] += x;
            i += i & -i;
        }
    }

    void _print(){
        for(int i = 1;i <= n;++i){cout << bit[i] << ' ';}
        cout << endl;
    }
};

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        BIT csum(25000);
        int offset = 11000;
        int all_size = nums.size();

        vector<int> res;
        for(int i = all_size - 1;i >= 0;--i){
            int tree_pos = nums[i] + offset;
            int cur_sum = csum._sum(tree_pos - 1);
            res.push_back(cur_sum);
            csum._add(tree_pos, 1);
        }

        reverse(res.begin(), res.end());
        return res;
    }
};