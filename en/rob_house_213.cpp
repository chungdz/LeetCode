#include<vector>
#include<algorithm>
using namespace std;


/***
 * You are a professional robber planning to rob houses along a street. 
 * Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. 
 * That means the first house is the neighbor of the last one. 
 * Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.
 * Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
 * 
 * 1 <= nums.length <= 100
 * 0 <= nums[i] <= 1000
 * 
 * 198变种，将198代码复制过来，然后把房子分为两种情况，选第一个和不选第一个，就变成了198的断开形式，内存还没有优化到最好
 * 
 * **/

class Solution {
public:
    int rob(vector<int>& nums) {

        int length = nums.size();
        if(length == 1){return nums[0];}
        else if(length == 2){return max(nums[0], nums[1]);}

        // rob 第一个house，第二位和最后一位都不能选，断开成正常的rob
        vector<int> subv1(nums.begin() + 2, nums.end() - 1);
        int price_1 = nums[0] + rob_no_cycle(subv1);
        //不rob 第一个house
        vector<int> subv2(nums.begin() + 1, nums.end());
        int price_2 = rob_no_cycle(subv2);

        return max(price_1, price_2);
    }

    int rob_no_cycle(vector<int>& nums){
        vector<int> max_income;
        int length = nums.size();

        if (length == 0){return 0;}
        else if(length == 1){return nums[0];}
        else if(length == 2){return max(nums[0], nums[1]);}

        max_income.push_back(nums[0]);
        max_income.push_back(nums[1]);
        max_income.push_back(nums[0] + nums[2]);

        if(length == 3){return max(max_income[1], max_income[2]);}

        for(int i = 3;i < length;i++){
            // 要么加i - 2的位置，要么加i - 3的位置
            max_income.push_back(nums[i] + max(max_income[i - 2], max_income[i - 3]));
        }

        return max(max_income[length - 1], max_income[length - 2]);
    }
};