#include<math.h>
#include<algorithm>
using namespace std;

/*
279 Perfect Squares

Given an integer n, return the least number of perfect square numbers that sum to n.

A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.

 

Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.
Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.
 

Constraints:

1 <= n <= 10^4

基本思想

完全背包问题
*/

/*
填表法 最快
*/

class Solution1 {
    int sq[100];
    int dp[10001] = {0};
    int sn, tn;
public:
    int numSquares(int n) {
        tn = n;
        sn = sqrt(n);
        for(int i = 1;i <= sn;++i){
            sq[i - 1] = i * i;
            table_iter(i - 1);
        }
        return dp[n];
    }
    
    void table_iter(int idx){
        int cur_num = sq[idx];
        for(int i = 0;i < tn;++i){
            int tmp = cur_num;
            int cnum = 1;
            if(i + tmp <= tn){
                int ntimes = dp[i] + cnum;
                if(dp[i + tmp] == 0 || dp[i + tmp] > ntimes)
                    dp[i + tmp] = ntimes;
                tmp += cur_num;
                cnum += 1;
            }
        }
    }
};

/*
普通动态规划 第二快
*/

class Solution2 {
    int sq[100];
    int dp[100][10001] = {0};
    int sn, tn;
public:
    int numSquares(int n) {
        tn = n;
        sn = sqrt(n);
        for(int i = 1;i <= sn;++i){
            sq[i - 1] = i * i;
        }
        return dfs(sn - 1, n);
    }
    
    int dfs(int idx, int left){
        if(idx == 0)
            return left;
        if(left == 0)
            return 0;
        if(dp[idx][left] != 0)
            return dp[idx][left];

        if(left >= sq[idx])
            dp[idx][left] = min(dfs(idx - 1, left), 1 + dfs(idx, left - sq[idx]));
        else
            dp[idx][left] = dfs(idx - 1, left);
        return dp[idx][left];
    }
};