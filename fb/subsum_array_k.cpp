#include<vector>
#include<algorithm>
#include<memory.h>
#include<unordered_map>
using namespace std;

/*
560
Subarray Sum Equals K

Solution
Given an array of integers nums and an integer k, return the total number of continuous subarrays whose sum equals to k.

 

Example 1:

Input: nums = [1,1,1], k = 2
Output: 2
Example 2:

Input: nums = [1,2,3], k = 3
Output: 2
 

Constraints:

1 <= nums.length <= 2 * 104
-1000 <= nums[i] <= 1000
-10^7 <= k <= 10^7

TLE思想

线段树query n^2 log(n)

暴力滑动窗口1/2 n^2

剪枝滑动窗口1/2 n^2

ACC思想
sum[i, j] = sum[0, j] - sum[0, i];
对每个j，找到sum[0, 1] = sum[0, j] - k
可以用map储存j之前的i的和以及对应的次数
**/

class Segement_Tree{
    int *tree_arr;
    int number;
public:
    Segement_Tree(int n){
        number = 1;
        while(number < n){
            number *= 2;
        }
        tree_arr = new int[2 * number - 1];
        memset(tree_arr, 0, sizeof(int) * (2 * number - 1));
    }

    void update(int index, int num){
        int cur_ind = index + number - 1;
        tree_arr[cur_ind] = num;
        while(cur_ind > 0){
            cur_ind = (cur_ind - 1) / 2;
            tree_arr[cur_ind] = tree_arr[cur_ind * 2 + 1] + tree_arr[cur_ind * 2 + 2];
        }
    }

    int range_sum(int a, int b, int index, int l, int r){
        if(r < a || l > b){return 0;}
        if(a <= l && b >= r){return tree_arr[index];}
        else{
            int s1 = range_sum(a, b, index * 2 + 1, l, (l + r) / 2);
            int s2 = range_sum(a, b, index * 2 + 2, (l + r) / 2 + 1, r);
            return s1 + s2;
        }
    }

    int size(){
        return number;
    }
};

class Solution_1 {
public:
    int subarraySum(vector<int>& nums, int k) {
        int ns = nums.size();
        Segement_Tree st(ns);
        for(int i = 0;i < ns;++i){
            st.update(i, nums[i]);
        }
        int sumk = 0;
        for(int i = 0;i < ns;++i){
            for(int j = i;j < ns;++j){
                if(st.range_sum(i, j, 0, 0, st.size() - 1) == k){
                    sumk += 1;
                };
            }
        }
        return sumk;
    }
};

class Solution_2 {
public:
    int subarraySum(vector<int>& nums, int k) {
        int ns = nums.size();
        int pre_num = 0;
        int res = 0;
        for(int i = 0;i < ns;++i){
            int lstart = 0;
            int rstart = i;
            pre_num += nums[i];
            int cur_sum = pre_num;
            while(true){
                if(cur_sum == k){res += 1;}
                rstart += 1;
                if(rstart >= ns){
                    break;
                }
                cur_sum -= nums[lstart];
                lstart += 1;
                cur_sum += nums[rstart];
            }
        }

        return res;
    }
};

class Solution_3{
public:
    int subarraySum(vector<int>& nums, int k) {
        int ns = nums.size();
        vector<int> right_max(ns, 0);
        vector<int> right_min(ns, 0);
        right_max[ns - 1] = nums[ns - 1];
        right_min[ns - 1] = nums[ns - 1];
        for(int i = ns - 2;i >= 0;--i){
            if(right_max[i + 1] >= 0){
                right_max[i] = nums[i] + right_max[i + 1];
            }
            else{
                right_max[i] = nums[i];
            }

            if(right_min[i + 1] < 0){
                right_min[i] = nums[i] + right_min[i + 1];
            }
            else{
                right_min[i] = nums[i];
            }
        }

        int res = 0;
        for(int i = 0;i < ns;++i){
            int cur_sum = 0;
            for(int j = i;j < ns;++j){
                if(cur_sum + right_max[j] < k){break;}
                else if(cur_sum + right_min[j] > k){break;}
                cur_sum += nums[j];
                if(cur_sum == k){
                    res += 1;
                }
            }
        }

        return res;
    }
};

class Solution{
    unordered_map<int, int> pre_sum;
public:
    int subarraySum(vector<int>& nums, int k) {
        int ns = nums.size();

        int res = 0;
        int cur_sum = 0;
        for(int i = 0;i < ns;++i){
            cur_sum += nums[i];
            int to_find = cur_sum - k;
            if(pre_sum.find(to_find) != pre_sum.end()){
                res += pre_sum[to_find];
            }

            if(pre_sum.find(cur_sum) == pre_sum.end()){
                pre_sum[cur_sum] = 1;
            }
            else{
                pre_sum[cur_sum] += 1;
            }
        }

        return res;
    }
};