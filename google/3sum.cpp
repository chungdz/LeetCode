#include<vector>
#include<map>
#include<algorithm>
using namespace std;


/***
 * 
 * 15
 * 
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

 

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Example 2:

Input: nums = []
Output: []
Example 3:

Input: nums = [0]
Output: []
 

Constraints:

0 <= nums.length <= 3000
-10^5 <= nums[i] <= 10^5
 * 
 * 
 * 基本思想：
 * 
 * 暴力搜索，因为是三个数，要么两正一负，要么两负一正，要么三个零
 * 
 * 搜索的时候从有序数组里两个正数结合，查找负数；两个负数结合，查找正数；这样可以避免全局搜索带来的重复答案
 * 
 * 用map记录每个数和他们的数量，便于查询对应的数是否存在
 * 
 * 如果某些数字数量大于1，需要额外考虑两个重复数字的组合
 * 
*/

class Solution {
    vector<vector<int>> results;
    map<int, int> bin;
    int nums_record[3000];

    bool check_valid(int num1, int num2){
        int num3 = - (num1 + num2);
        if(bin.find(num3) != bin.end()){
            vector<int> tmp;
            tmp.push_back(num1);
            tmp.push_back(num2);
            tmp.push_back(num3);
            results.push_back(tmp);
            return true;
        }
        return false;
    }
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if(nums.size() < 3){return results;}

        for(auto n: nums){
            if(bin.find(n) == bin.end()){
                bin[n] = 1;
            }
            else{
                bin[n] += 1;
            }
        }

        map<int, int>::iterator zero_it = bin.lower_bound(0);
        // all numbers are negative
        if(zero_it == bin.end()){return results;}
        int split_line = zero_it->first;
        //check if there're 3 zeros
        if(split_line == 0 && zero_it->second >= 3){results.push_back(vector<int>({0, 0, 0}));}
        // all numbers are >= 0
        if(zero_it == bin.begin()){return results;}

        int split_index;
        int index = 0;
        for(auto mit: bin){
            nums_record[index] = mit.first;
            if(mit.first == split_line){split_index = index;}
            ++index;
        }
        int num_size = index;
        int max_num = nums_record[num_size - 1];
        int min_num = nums_record[0];
        // search start from >= 0
        for(int pos_index = split_index;pos_index < num_size;++pos_index){
            int cur_number = nums_record[pos_index];
            if(cur_number != 0 && bin[cur_number] > 1){check_valid(cur_number, cur_number);}

            for(int num2_index = pos_index + 1;num2_index < num_size;++num2_index){
                int num2 = nums_record[num2_index];
                if(-(cur_number + num2) < min_num){break;}
                check_valid(cur_number, num2);
            }
        }
        // search from < 0
        for(int neg_index = split_index - 1;neg_index >= 0;--neg_index){
            int cur_number = nums_record[neg_index];
            if(bin[cur_number] > 1){check_valid(cur_number, cur_number);}

            for(int num2_index = neg_index - 1;num2_index >= 0;--num2_index){
                int num2 = nums_record[num2_index];
                if(-(cur_number + num2) > max_num){break;}
                check_valid(cur_number, num2);
            }
        }

        return results;
    }
};