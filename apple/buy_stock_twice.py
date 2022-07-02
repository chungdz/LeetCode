'''
123 Best Time to Buy and Sell Stock III

You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete at most two transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
Example 2:

Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.
Example 3:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
 

Constraints:

1 <= prices.length <= 105
0 <= prices[i] <= 105
'''

'''
dp[i][j] 表示从j开始还有i次交易机会，最大值
转移方程：
    cur_gain = self.prices[rp] - self.prices[index]
    if cur_gain > 0:
        max_profit = max(cur_gain + self.dfs(transaction - 1, rp + 1), max_profit)
    else:
        max_profit = max(self.dfs(transaction, rp), max_profit)
        break
'''

class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        self.plen = len(prices)
        self.dp = [[-1] * self.plen for _ in range(2)]
        self.prices = prices
        return self.dfs(1, 0)
    
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
状态更迭

思路与算法

由于我们最多可以完成两笔交易，因此在任意一天结束之后，我们会处于以下五个状态中的一种：

未进行过任何操作；

只进行过一次买操作；buy1

进行了一次买操作和一次卖操作，即完成了一笔交易；sell1

在完成了一笔交易的前提下，进行了第二次买操作；buy2

完成了全部两笔交易。sell2

由于第一个状态的利润显然为0，因此我们可以不用将其记录。对于剩下的四个状态，我们分别将它们的最大利润记为
'''
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        buy1 = buy2 = -prices[0]
        sell1 = sell2 = 0
        for i in range(1, n):
            buy1 = max(buy1, -prices[i])
            sell1 = max(sell1, buy1 + prices[i])
            buy2 = max(buy2, sell1 - prices[i])
            sell2 = max(sell2, buy2 + prices[i])
        return sell2
