/*
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。

注意：你不能在买入股票前卖出股票。

 

示例 1:

输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
示例 2:

输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
*/
#include <vector>
using namespace std;

/*
解法一，从后向前遍历，记录最大值，如果当前值大于等于最大值，那么收益为0，如果小于，收益为最大值减去当前值
返回最大收益
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max_profit = 0;
        int length = prices.size();
        int max_price = prices[length - 1];

        for(int i = length - 2;i >= 0;i--){
            if(prices[i] < max_price){
                int cur_profit = max_price - prices[i];
                if(cur_profit > max_profit){
                    max_profit = cur_profit;
                }
            }
            else if(prices[i] > max_price){
                max_price = prices[i];
            }
        }

        return max_profit;
    }
};