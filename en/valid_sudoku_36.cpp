#include<vector>
#include<ctype.h>
using namespace std;

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