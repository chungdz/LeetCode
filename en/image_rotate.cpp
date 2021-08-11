#include<vector>
using namespace std;

/***
 * 
 * 48
 * 
 * You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
    You have to rotate the image in-place, which means you have to modify the input 2D matrix directly.
    DO NOT allocate another 2D matrix and do the rotation.

    matrix.length == n
    matrix[i].length == n
    1 <= n <= 20
    -1000 <= matrix[i][j] <= 1000
 * 
 * 基本思路，一圈一圈的旋转
 * 旋转时，从第一行开始要么一个一个的旋转，要么一组一组（边长减一的数量）的旋转，我选择一组一组旋转
 * 
 * 
 * **/

class Solution {
    int length;
    int tmp_array[20];
    vector<vector<int>> *my_matrix;
public:
    void rotate(vector<vector<int>>& matrix) {
        my_matrix = &matrix;
        length = matrix.size();

        int origin_row = 0;
        int origin_column = 0;
        int end_row = length - 1;
        int end_column = length - 1;

        int tmp_len = length;
        while(tmp_len > 1){
            edge_rotate(origin_row, origin_column, end_row, end_column, tmp_len);
            tmp_len -= 2;
            origin_row += 1;
            origin_column += 1;
            end_row -= 1;
            end_column -= 1;
        }

        return;
    }

    void edge_rotate(int srow, int scolumn, int erow, int ecolumn, int slen){
        // save tmporary variables
        for(int i = 0;i < slen - 1;i++){
            tmp_array[i] = (*my_matrix)[erow - i][scolumn];
        }
        //rotate bottom to left
        for(int i = 0;i < slen - 1;i++){
            (*my_matrix)[erow - i][scolumn] = (*my_matrix)[erow][ecolumn - i];
        }
        //rotate right to bottom
        for(int i = 0;i < slen - 1;i++){
            (*my_matrix)[erow][ecolumn - i] = (*my_matrix)[srow + i][ecolumn];
        }
        //rotate top to right
        for(int i = 0;i < slen - 1;i++){
            (*my_matrix)[srow + i][ecolumn] = (*my_matrix)[srow][scolumn + i];
        }
        //rotate left to top
        for(int i = 0;i < slen - 1;i++){
            (*my_matrix)[srow][scolumn + i] = tmp_array[i];
        }

        return;
    }
};