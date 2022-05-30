'''
309. Best Time to Buy and Sell Stock with Cooldown

You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:

After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: prices = [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]
Example 2:

Input: prices = [1]
Output: 0
 

Constraints:

1 <= prices.length <= 5000
0 <= prices[i] <= 1000

解决方案一：
1维动态规划
dp[i] = max(遍历要买的 + dp[last + 2], 不操作，dp[j > i])

时间复杂度 n^2

2维动态规划
我们用 f[i]f[i] 表示第 ii 天结束之后的「累计最大收益」。根据题目描述，由于我们最多只能同时买入（持有）一支股票，并且卖出股票后有冷冻期的限制，因此我们会有三种不同的状态：

我们目前持有一支股票，对应的「累计最大收益」记为 f[i][0]；

我们目前不持有任何股票，并且处于冷冻期中，对应的「累计最大收益」记为 f[i][1]；

我们目前不持有任何股票，并且不处于冷冻期中，对应的「累计最大收益」记为 f[i][2]。

这里的「处于冷冻期」指的是在第 i 天结束之后的状态。也就是说：如果第 i 天结束之后处于冷冻期，那么第 i+1 天无法买入股票。

如何进行状态转移呢？在第 i 天时，我们可以在不违反规则的前提下进行「买入」或者「卖出」操作，此时第 i 天的状态会从第 i-1 天的状态转移而来；我们也可以不进行任何操作，此时第 i 天的状态就等同于第 i-1 天的状态。那么我们分别对这三种状态进行分析：

对于 f[i][0]，我们目前持有的这一支股票可以是在第 i-1 天就已经持有的，对应的状态为 f[i-1][0]；或者是第 i 天买入的，那么第 i-1 天就不能持有股票并且不处于冷冻期中，对应的状态为 f[i-1][2] 加上买入股票的负收益 因此状态转移方程为：

f[i][0] = max(f[i-1][0], f[i-1][2] - prices[i])

对于 f[i][1]，我们在第 i 天结束之后处于冷冻期的原因是在当天卖出了股票，那么说明在第 i-1 天时我们必须持有一支股票，对应的状态为 f[i-1][0] 加上卖出股票的正收益 因此状态转移方程为：

f[i][1] = f[i-1][0] + prices[i]

对于 f[i][2]，我们在第 i 天结束之后不持有任何股票并且不处于冷冻期，说明当天没有进行任何操作，即第 i-1 天时不持有任何股票：如果处于冷冻期，对应的状态为 f[i-1][1]；如果不处于冷冻期，对应的状态为 f[i-1][2]。因此状态转移方程为：

f[i][2] = max(f[i-1][1], f[i-1][2])

这样我们就得到了所有的状态转移方程。如果一共有 n 天，那么最终的答案即为：

max(f[n-1][0], f[n-1][1], f[n-1][2])

注意到如果在最后一天（第 n-1 天）结束之后，手上仍然持有股票，那么显然是没有任何意义的。因此更加精确地，最终的答案实际上是 f[n-1][1] 和 f[n-1][2] 中的较大值，即：

max(f[n-1][1], f[n-1][2])

细节

我们可以将第 00 天的情况作为动态规划中的边界条件：

  
f[0][0] = -prices[0]
f[0][1] = 0
f[0][2] = 0

在第 0 天时，如果持有股票，那么只能是在第 0 天买入的，对应负收益 -prices[0]；如果不持有股票，那么收益为零。注意到第 0 天实际上是不存在处于冷冻期的情况的，但我们仍然可以将对应的状态 f[0][1] 置为零，这其中的原因留给读者进行思考。

这样我们就可以从第 1 天开始，根据上面的状态转移方程进行进行动态规划，直到计算出第 n-1 天的结果。
时间复杂度n
'''

class Solution1:
    def maxProfit(self, prices: List[int]) -> int:
        self.plen = len(prices)
        self.dp = [-1] * self.plen
        self.p = prices
        return self.dfs(0)
        
    def dfs(self, index):
            
        if index >= self.plen:
            return 0
        
        if self.dp[index] != -1:
            return self.dp[index]

        cur_min = self.p[index]
        max_profit = 0
        for i in range(index + 1, self.plen):
            profit = self.p[i] - cur_min
            cur_min = min(self.p[i], cur_min)
            cur_profit1 = profit + self.dfs(i + 2)
            cur_profit2 = self.dfs(i)
            max_profit = max(max_profit, cur_profit1, cur_profit2)
        
        self.dp[index] = max_profit
        return self.dp[index]

class Solution2:
    def maxProfit(self, prices: List[int]) -> int:
        if not prices:
            return 0
        
        n = len(prices)
        # f[i][0]: 手上持有股票的最大收益
        # f[i][1]: 手上不持有股票，并且处于冷冻期中的累计最大收益
        # f[i][2]: 手上不持有股票，并且不在冷冻期中的累计最大收益
        f = [[-prices[0], 0, 0]] + [[0] * 3 for _ in range(n - 1)]
        for i in range(1, n):
            f[i][0] = max(f[i - 1][0], f[i - 1][2] - prices[i])
            f[i][1] = f[i - 1][0] + prices[i]
            f[i][2] = max(f[i - 1][1], f[i - 1][2])
        
        return max(f[n - 1][1], f[n - 1][2])
