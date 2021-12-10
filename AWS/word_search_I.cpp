#include<string>
#include<unordered_map>
#include<vector>
#include<unordered_set>
using namespace std;

/*
79 word search

Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

 

Example 1:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true
Example 2:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true
Example 3:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false
 

Constraints:

m == board.length
n = board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board and word consists of only lowercase and uppercase English letters.
 

Follow up: Could you use search pruning to make your solution faster with a larger board?

基本思想:

DFS + 剪枝

**/

class Solution {
    char search_record[15][15] = {0};
    int m, n;
    int direction[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    string cword;
public:
    bool exist(vector<vector<char>>& board, string word) {
        cword = word;
        m = board.size();
        n = board[0].size();
        // dfs all node
        for(int i = 0;i < m;++i){
            for(int j = 0;j < n;++j){
                char cur_c = board[i][j];
                if(dfs(i, j, 0, board)){
                    return true;
                }
            }
        }
        return false;
    }

    bool dfs(int crow, int ccol, int windex, vector<vector<char>>& board){
        if(board[crow][ccol] != cword[windex]){
            return false;
        }
        if(windex == cword.size() - 1){
            return true;
        }

        search_record[crow][ccol] = 1;
        for(int d = 0;d < 4;++d){
            int nxt_row = crow + direction[d][0];
            int nxt_col = ccol + direction[d][1];
            if(nxt_row >= 0 && nxt_row < m && nxt_col >=0 && nxt_col < n && search_record[nxt_row][nxt_col] == 0){
                if(dfs(nxt_row, nxt_col, windex + 1, board)){
                    return true;
                }
            }
        }

        search_record[crow][ccol] = 0;
        return false;
    }
};