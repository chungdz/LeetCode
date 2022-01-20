#include<vector>
#include<algorithm>
using namespace std;

/*
85 Maximal Rectangle

Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

 

Example 1:


Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.
Example 2:

Input: matrix = [["0"]]
Output: 0
Example 3:

Input: matrix = [["1"]]
Output: 1
 

Constraints:

rows == matrix.length
cols == matrix[i].length
1 <= row, cols <= 200
matrix[i][j] is '0' or '1'.

基本思想

84题的扩展，把每一行看成84题（从柱状图中找最大矩形）来解决
*/

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
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
                rec_max = max(rec_max, top_height * length);
            }
            
            monotonous_stack.push_back(i);
        }
        return rec_max;
    }
};