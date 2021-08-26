#include<vector>
#include<map>
#include<algorithm>
using namespace std;

/**
 * 
 * 857
 * Minimum Cost to Hire K Workers
 * 
 * 
There are n workers. You are given two integer arrays quality and wage where quality[i] is the quality of the ith worker and wage[i] is the minimum wage expectation for the ith worker.

We want to hire exactly k workers to form a paid group. To hire a group of k workers, we must pay them according to the following rules:

Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
Every worker in the paid group must be paid at least their minimum-wage expectation.
Given the integer k, return the least amount of money needed to form a paid group satisfying the above conditions. Answers within 10-5 of the actual answer will be accepted.

 

Example 1:

Input: quality = [10,20,5], wage = [70,50,30], k = 2
Output: 105.00000
Explanation: We pay 70 to 0th worker and 35 to 2nd worker.
Example 2:

Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], k = 3
Output: 30.66667
Explanation: We pay 4 to 0th worker, 13.33333 to 2nd and 3rd workers separately.
 

Constraints:

n == quality.length == wage.length
1 <= k <= n <= 10^4
1 <= quality[i], wage[i] <= 10^4
 * 
 * 
 * 
 * 
 * 
 * 基本思路
 * 
 * 分为两步处理
 * 
 * 第一步，计算每个人的性价比ratio（工资/质量），从低到高排列，由于性价比只能向上兼容，所以只有第k个人之后的ratio是可行的
 * 
 * 第二步，遍历第k个人到第n个人，对每个人，用他们的性价比，乘以排他们之前的人的质量，得到需要付出的工资
 * 
 * 这就需要维护一个最小和，代表这个人之前的哪k个人加和的质量最小，用最大堆来维护，每次新加一个人，就把堆中的质量最大值pop掉
 * 
 * 然后把质量和加上新人的质量减去最大质量
 * 
 * 
 */

bool comp(const pair<int, double> &a, const pair<int, double> &b){
        return a.second < b.second;
};

class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int total_worker = quality.size();
        vector<pair<int, double>> origin_ratio;
        for(int i = 0;i < total_worker;++i){
            origin_ratio.push_back(pair<int, double>(quality[i], (double)wage[i] / quality[i]));
        }
        sort(origin_ratio.begin(), origin_ratio.end(), comp);

        // init start from inde k - 1
        double ratio = origin_ratio[k - 1].second;
        int sum_quality = 0;
        // record the k workers who have min quality
        // it is a max heap
        vector<int> min_quality;
        for(int i = 0;i < k;++i){
            sum_quality += origin_ratio[i].first;
            min_quality.push_back(origin_ratio[i].first);
        }
        double sum_payment = sum_quality * ratio;
        make_heap(min_quality.begin(), min_quality.end());

        for(int i = k;i < total_worker;++i){
            ratio = origin_ratio[i].second;
            // add worker in heap
            min_quality.push_back(origin_ratio[i].first);
            push_heap(min_quality.begin(), min_quality.end());
            // pop out the max quality worker
            pop_heap(min_quality.begin(), min_quality.end());

            sum_quality = sum_quality + origin_ratio[i].first - min_quality.back();
            min_quality.pop_back();
            sum_payment = min(sum_payment, sum_quality * ratio);
        }

        return sum_payment;
    }
};