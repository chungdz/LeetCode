#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

/**
 * 剑指 Offer 51. 数组中的逆序对
 * 
 * 
在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

 

示例 1:

输入: [7,5,6,4]
输出: 5
 

限制：

0 <= 数组长度 <= 50000
 * 
 * 
 * 基本思想
 * 
 * BIT 树状数组 求逆序对
 * 
 * 遍历离散化后的a数组的每一个a[i]
 *  
 *  i - mbit._sum(a[i]) 表示的是第i个数（从0开始）之前，有mbit._sum(a[i])个比它小的数出现过了，
 *  所以 i - mbit._sum(a[i]) 表示的是剩下的比它大的数的数量，就是逆序对
 *
 *  mbit._add(a[i], 1) 记录出现的a[i]这个数
 * 
 * 能解决数组内数字重复的情况，已经通过力扣题
 */

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


vector<int> discretize_array(vector<int>& origin, int start = 0){
    
    vector<int> s(origin);
    sort(s.begin(), s.end());
    vector<int>::iterator new_end = unique(s.begin(), s.end());

    int total_size = origin.size();
    vector<int> res(total_size);
    for(int i = 0;i < total_size;++i){
        res[i] = lower_bound(s.begin(), new_end, origin[i]) - s.begin() + 1;
    }
    return res;
}


class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int total_size = nums.size();
        if(total_size <= 0){return 0;}

        vector<int> new_nums = discretize_array(nums, 1);

        BIT mbit(total_size);
        int ans = 0;
        for(int j = 0;j < total_size;++j){
            ans += j - mbit._sum(new_nums[j]);
            mbit._add(new_nums[j], 1);
        }

        return ans;
    }
};