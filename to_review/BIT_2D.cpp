#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

/*
基本思想

二维树状数组维持和, 对于m和n的矩阵，需要m + 1, n + 1的矩阵来做BIT的数组，因为BIT需要从1开始
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
