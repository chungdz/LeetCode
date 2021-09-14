/*

200

给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。

示例 1:

输入:
11110
11010
11000
00000
输出: 1
示例 2:

输入:
11000
11000
00100
00011
输出: 3
解释: 每座岛屿只能由水平和/或竖直方向上相邻的陆地连接而成。
*/
#include <vector>
using namespace std;


/*
解法一（深搜）：
从左到右，从上倒下，如果遇见一个1，就加一个岛屿数量，然后从当前的1开始探索所有和1相连的地方，并把所有相连的地方改成2
*/
class Solution {
    int row;
    int col;
public:
    int numIslands(vector<vector<char>>& grid) {
        row = grid.size();
        if(row == 0){return 0;}
        col = grid[0].size();
        if(col == 0){return 0;}

        int islands = 0;
        for(int i = 0;i < row;i++){
            for(int j = 0;j < col;j++){
                if(grid[i][j] == '1'){
                    islands++;
                    dye(i, j, grid);
                }
            }
        }

        return islands;
    }

    void dye(int cur_row, int cur_col, vector<vector<char>>& grid){
        grid[cur_row][cur_col] = '2';
        
        if(cur_row + 1 < row && grid[cur_row + 1][cur_col] == '1'){dye(cur_row + 1, cur_col, grid);}
        if(cur_row - 1 >= 0 && grid[cur_row - 1][cur_col] == '1'){dye(cur_row - 1, cur_col, grid);}
        if(cur_col + 1 < col && grid[cur_row][cur_col + 1] == '1'){dye(cur_row, cur_col + 1, grid);}
        if(cur_col - 1 >= 0 && grid[cur_row][cur_col - 1] == '1'){dye(cur_row, cur_col - 1, grid);}
    }
};

/*
解法二：广搜
*/

/*
解法三：并查集，找到新的1就合并，需要记录
*/