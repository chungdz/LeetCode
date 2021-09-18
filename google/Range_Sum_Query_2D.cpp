#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

/*

308

Range Sum Query 2D - Mutable

Solution
Given a 2D matrix matrix, handle multiple queries of the following types:

Update the value of a cell in matrix.
Calculate the sum of the elements of matrix inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
Implement the NumMatrix class:

NumMatrix(int[][] matrix) Initializes the object with the integer matrix matrix.
void update(int row, int col, int val) Updates the value of matrix[row][col] to be val.
int sumRegion(int row1, int col1, int row2, int col2) Returns the sum of the elements of matrix inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
 

Example 1:


Input
["NumMatrix", "sumRegion", "update", "sumRegion"]
[[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]], [2, 1, 4, 3], [3, 2, 2], [2, 1, 4, 3]]
Output
[null, 8, null, 10]

Explanation
NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);
numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e. sum of the left red rectangle)
numMatrix.update(3, 2, 2);       // matrix changes from left image to right image
numMatrix.sumRegion(2, 1, 4, 3); // return 10 (i.e. sum of the right red rectangle)
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
-10^5 <= matrix[i][j] <= 10^5
0 <= row < m
0 <= col < n
-10^5 <= val <= 10^5
0 <= row1 <= row2 < m
0 <= col1 <= col2 < n
At most 10^4 calls will be made to sumRegion and update.


基本思想

二维树状数组维持和


**/

/*

for record the sum of A[mm][nn]

since BIT can not start at 0, all index from array A will be added 1

**/

class BIT_2D{
    int **bit;
    int m, n;

    int lowbit(int t){
        return t & -t;
    } 
public:
    BIT_2D(int mm, int nn){
        m = mm;
        n = nn;
        bit = new int*[m + 1];
        // plus one for a[i][j] would be a[i + 1][j + 1]
        for(int i = 0;i <= m;++i){
            bit[i] = new int[n + 1];
            for(int j = 0;j <= n;++j){
                bit[i][j] = 0;
            }
        }
    }

    int _sum(int x, int y){
        x = x + 1;
        y = y + 1;
        int s = 0;
        for(int i = x;i > 0;i -= lowbit(i)){
            for(int j = y;j > 0;j -= lowbit(j)){
                s += bit[i][j];
            }
        }
        return s;
    }

    void _add(int x, int y, int val){
        x = x + 1;
        y = y + 1;
        for(int i = x;i <= m;i += lowbit(i)){
            for(int j = y;j <= n;j += lowbit(j)){
                bit[i][j] += val;
            }
        }
    }

    void _print(){
        for(int i = 0;i <= m;++i){
            for(int j = 0;j <= n;++j)
            {cout << bit[i][j] << ' ';}
            cout << endl;
        }
        
        cout << endl;
    }
};


class NumMatrix {
    BIT_2D *bit;
    vector<vector<int>> my_mtr;
public:
    NumMatrix(vector<vector<int>>& matrix){
        int mm = matrix.size();
        int nn = matrix[0].size();
        bit = new BIT_2D(mm, nn);

        for(int i = 0;i < mm;++i){
            for(int j = 0;j < nn;++j){
                bit->_add(i, j, matrix[i][j]);
            }
        }

        my_mtr = matrix;
    }
    
    void update(int row, int col, int val) {
        int change = val - my_mtr[row][col];
        bit->_add(row, col, change);
        my_mtr[row][col] = val;
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        
        int r1 = bit->_sum(row1 - 1, col1 - 1);
        int r2 = bit->_sum(row1 - 1, col2);
        int r3 = bit->_sum(row2, col1 - 1);
        int r4 = bit->_sum(row2, col2);

        return r4 - r3 - r2 + r1;
    }
};
