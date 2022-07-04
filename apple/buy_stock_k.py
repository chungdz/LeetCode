'''
188 Best Time to Buy and Sell Stock IV

You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
 

Constraints:

0 <= k <= 100
0 <= prices.length <= 1000
0 <= prices[i] <= 1000
'''

class Solution:
    def maxProfit(self, k: int, prices: List[int]) -> int:
        self.plen = len(prices)
        self.dp = [[-1] * self.plen for _ in range(k)]
        self.prices = prices
        return self.dfs(k - 1, 0)
    
    def dfs(self, transaction, index):
        if transaction < 0:
            return 0
        if index >= self.plen - 1:
            return 0
        if self.dp[transaction][index] != -1:
            return self.dp[transaction][index]
        
        max_profit = -1
        for rp in range(index + 1, self.plen):
            cur_gain = self.prices[rp] - self.prices[index]
            if cur_gain >= 0:
                max_profit = max(cur_gain + self.dfs(transaction - 1, rp + 1), max_profit)
            else:
                max_profit = max(self.dfs(transaction, rp), max_profit)
                break
        
        self.dp[transaction][index] = max_profit
        return self.dp[transaction][index]

'''
和123题官方题解类似，另一种DP，用的空间更多，但是时间更少
而且可以从二维降成1维，可以保持两个数组来滚动完成

buy[i][j] 表示到了第i天进行了j次交易，并且手里有股票时的最大收益
sell[i][j] 表示到了第i天进行了j次交易，并且手里没有股票时的最大收益

buy[i][j] = max(buy[i-1][j], sell[i-1][j] - prices[i])
sell[i][j] = max(sell[i-1][j], buy[i-1][j-1] + prices[i])

由于每次都从前一行更新，所以只需要两行就可以更新完成

i从0开始一直到plen - 1结束
j从1开始一直到k结束

注意，
buy[i][0]=-min(prices[:i+1])，默认购买+出售算一次交易，所以初始化的时候持有股票，只购买未出售，所以初始化为-prices[:i+1]中的
最大值，即之前价格最低的时候持有
'''
class Solution:
    def maxProfit(self, k: int, prices: List[int]) -> int:
        plen = len(prices)
        if plen < 1:
            return 0
        # 实际上是把第1天的buy和sell初始化为-prices[0]和0
        buy = [[-prices[0]] * (k + 1) for _ in range(2)]
        sell = [[0] * (k + 1) for _ in range(2)]
        cur_row = 1
        pre_row = 0
        
        for i in range(1, plen):
            buy[cur_row][0] = max(-prices[i], buy[pre_row][0])
            # 不需要 sell[cur_row][0] = 0 因为一直都等于零
            for j in range(1, k + 1):
                buy[cur_row][j] = max(buy[pre_row][j], sell[pre_row][j] - prices[i])
                sell[cur_row][j] = max(sell[pre_row][j], buy[pre_row][j - 1] + prices[i])
            
            cur_row, pre_row = pre_row, cur_row
        
        return max(sell[pre_row])
