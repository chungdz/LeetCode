#include<vector>
#include<algorithm>
using namespace std;

/*
221 Maximal Square

Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

 

Example 1:


Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 4
Example 2:


Input: matrix = [["0","1"],["1","0"]]
Output: 1
Example 3:

Input: matrix = [["0"]]
Output: 0
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 300
matrix[i][j] is '0' or '1'.

基本思想

85题的特殊版，限定边长需要一致

也可用动态规划解题
*/

class Solution1 {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> heights_2D(m, vector<int>(n, 0));
        for(int j = 0;j < n;++j)
            for(int i = 0;i < m;++i)
                if(matrix[i][j] == '0')
                    heights_2D[i][j] = 0;
                else if(i - 1 < 0 || matrix[i - 1][j] == '0')
                    heights_2D[i][j] = 1;
                else
                    heights_2D[i][j] = heights_2D[i - 1][j] + 1;
        
        int res = -1;
        for(int i = 0;i < m;++i)
            res = max(res, (largestRectangleArea(heights_2D[i])));
        return res;
    }

    int largestRectangleArea(vector<int>& heights) {
        int hs = heights.size();
        int rec_max = -1;
        vector<int> monotonous_stack;
        monotonous_stack.push_back(0);
        heights.push_back(-1);
        for(int i = 1;i <= hs;++i){
            
            while(monotonous_stack.size() > 0 && heights[i] < heights[monotonous_stack.back()]){
                int top_height = heights[monotonous_stack.back()];
                monotonous_stack.pop_back();
                int left;
                if(monotonous_stack.size() > 0){
                    left = monotonous_stack.back();
                }
                else{
                    left = -1;
                }
                int length = i - left - 1;
                int square_l = min(length, top_height);
                rec_max = max(rec_max, square_l * square_l);
            }
            
            monotonous_stack.push_back(i);
        }
        return rec_max;
    }
};

/*
动态规划

dp[i][j]表示以i, j为右下角的正方形最大边长

当matrix[i][j] == 1时
dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1
or
dp[i][j] = 1 (i == 0 || j == 0)

else
dp[i][j] = 0
*/

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int res = 0;
        for(int i = 0;i < m;++i)
            for(int j = 0;j < n;++j)
            {
                if(matrix[i][j] == '0')
                    continue;
                else if(i == 0 || j == 0)
                    dp[i][j] = 1;
                else
                    dp[i][j] = 1 + min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);
                res = max(dp[i][j], res);
            }
        
        return res * res;     
    }
};