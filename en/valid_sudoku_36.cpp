#include<vector>
#include<ctype.h>
using namespace std;

/***
 * Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.

board.length == 9
board[i].length == 9
board[i][j] is a digit or '.'.
 * 
 * 
 * 基本思路：遍历搜索
 * 基本思想：暴力搜索每一行，每一列，每一个子格，查看是否重复。
 * 优化：将搜索过的结果记录，记录方式以数字作为key，出现过的行、列、子格作为value。避免重复扫描。
 * 如果出现过的任一达到两次以上，即为不合格。
 * 
 * 
 * **/

class Solution {
    // first 9 row second 9 column third 9 grid
    int digit_record[10][27] = {0};

    int row_offset = 0;
    int column_offset = 9;
    int grid_offset = 18;

    int find_grid(int row, int column){
        int grid_row = row / 3;
        int grid_column = column / 3;

        return grid_row * 3 + grid_column;
    }
public:
    bool isValidSudoku(vector<vector<char>>& board) {

        for(int i = 0;i < 9;i++){
            for(int j = 0;j < 9;j++){
                if(isdigit(board[i][j])){
                    int cur_num = board[i][j] - '0';
                    digit_record[cur_num][row_offset + i] += 1;
                    digit_record[cur_num][column_offset + j] += 1;
                    int grid_num = find_grid(i, j);
                    digit_record[cur_num][grid_offset + grid_num] += 1;

                    if(digit_record[cur_num][row_offset + i] > 1 || digit_record[cur_num][column_offset + j] > 1 || digit_record[cur_num][grid_offset + grid_num] > 1){
                        return false;
                    }
                }
            }
        }

        return true;
    }
};