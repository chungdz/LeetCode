'''
714 Best Time to Buy and Sell Stock with Transaction Fee

You are given an array prices where prices[i] is the price of a given stock on the ith day, and an integer fee representing a transaction fee.

Find the maximum profit you can achieve. You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: prices = [1,3,2,8,4,9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
- Buying at prices[0] = 1
- Selling at prices[3] = 8
- Buying at prices[4] = 4
- Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
Example 2:

Input: prices = [1,3,7,5,10,3], fee = 3
Output: 6
 

Constraints:

1 <= prices.length <= 5 * 10^4
1 <= prices[i] < 5 * 10^4
0 <= fee < 5 * 10^4
'''

'''
原始动态规划思路
'''
class Solution:
    def maxProfit(self, prices: List[int], fee: int) -> int:
        self.plen = len(prices)
        self.dp = [-1] * self.plen
        self.prices = prices
        self.fee = fee
        return self.dfs(0)
    
    def dfs(self, index):
        if index >= self.plen - 1:
            return 0
        if self.dp[index] != -1:
            return self.dp[index]
        
        max_profit = 0
        for rp in range(index, self.plen):
            cur_gain = self.prices[rp] - self.prices[index]
            if cur_gain >= 0:
                max_profit = max(cur_gain - self.fee + self.dfs(rp + 1), max_profit)
            else:
                max_profit = max(self.dfs(rp), max_profit)
                break
        
        self.dp[index] = max_profit
        return self.dp[index]

'''
标准答案 解题思路

buy: 持有股票
sell: 不持有股票

buy的更新为要么持有之前的股票，要么持有今天的股票+之前sell的收益
sell的更新要么不持有，和之前sell一致，要么在今天卖出

'''
class Solution:
    def maxProfit(self, prices: List[int], fee: int) -> int:
        plen = len(prices)
        buy = -prices[0] - fee
        sell = 0

        for i in range(1, plen):
            new_buy = max(buy, sell - prices[i] - fee)
            new_sell = max(sell, buy + prices[i])

            buy = new_buy
            sell = new_sell

        return sell
