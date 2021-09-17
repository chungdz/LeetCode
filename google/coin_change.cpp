#include<vector>
#include<algorithm>
#include<memory.h>
using namespace std;

/*

322

Coin Change

Solution
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.

 

Example 1:

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
Example 2:

Input: coins = [2], amount = 3
Output: -1
Example 3:

Input: coins = [1], amount = 0
Output: 0
Example 4:

Input: coins = [1], amount = 1
Output: 1
Example 5:

Input: coins = [1], amount = 2
Output: 2
 

Constraints:

1 <= coins.length <= 12
1 <= coins[i] <= 2^31 - 1
0 <= amount <= 10^4

基本思想

完全背包问题

dp[i][j]表示在用前i + 1个银币凑成j元的时候，需要的最小硬币的数量

dp[i][j] = min k{k + dp[i + 1][j - coins[i] * k]} 保证coins[i] * k不超过j，并且只比较合规的

**/

class Solution {
    int dp[13][10001];
    int coin_num;
public:
    int coinChange(vector<int>& coins, int amount) {
        coin_num = coins.size();
        memset(dp, -1, sizeof(int) * 10001 * 13);
        for(int i = 0;i < 13;++i){
            dp[i][0] = 0;
        }

        dfs(0, amount, coins);

        int min_coin_num = 10001;
        for(int i = 0;i < coin_num;++i){
            if(dp[i][amount] != -2){
                min_coin_num = min(min_coin_num, dp[i][amount]);
            }
        }

        if(min_coin_num == 10001){
            min_coin_num = -1;
        }
        return min_coin_num;
    }

    int dfs(int coin_index, int remain, vector<int>& coins){
        if(dp[coin_index][remain] != -1){
            return dp[coin_index][remain];
        }
        if(coin_index >= coin_num && remain > 0){
            return -2;
        }
        // maximum coin num
        int max_num = remain / coins[coin_index];
        int min_coin_num = 10001;
        for(int i = 0;i <= max_num;++i){
            int res = dfs(coin_index + 1, remain - i * coins[coin_index], coins);
            if(res != -2){
                int cur_coin = i + res;
                min_coin_num = min(min_coin_num, cur_coin);
            }
        }

        if(min_coin_num == 10001){
            dp[coin_index][remain] = -2;
        }
        else{
            dp[coin_index][remain] = min_coin_num;
        }

        return dp[coin_index][remain];
    }
};

/*

优化dp结构

只保存amount不保存coin


**/

class Solution {
    int dp[10001];
    int coin_num;
public:
    int coinChange(vector<int>& coins, int amount) {
        coin_num = coins.size();
        memset(dp, -1, sizeof(dp));
        dp[0] = 0;
        dfs(amount, coins);
        return dp[amount] == -2?-1: dp[amount];
    }

    int dfs(int remain, vector<int>& coins){
        if(dp[remain] != -1){return dp[remain];}

        int min_c = 10001;
        for(int i = 0;i < coin_num;++i){
            int next_remain = remain - coins[i];
            if(next_remain >= 0){
                int res = dfs(next_remain, coins);
                if(res != -2){
                    int cur_coin = 1 + res;
                    min_c = min(min_c, cur_coin);
                }
            }
        }

        if(min_c == 10001){
            min_c = -2;
        }

        dp[remain] = min_c;
        return min_c;
    }
};