#include<vector>
#include<algorithm>
using namespace std;

/*
723 Candy Crush

This question is about implementing a basic elimination algorithm for Candy Crush.

Given an m x n integer array board representing the grid of candy where board[i][j] represents the type of candy. A value of board[i][j] == 0 represents that the cell is empty.

The given board represents the state of the game following the player's move. Now, you need to restore the board to a stable state by crushing candies according to the following rules:

If three or more candies of the same type are adjacent vertically or horizontally, crush them all at the same time - these positions become empty.
After crushing all candies simultaneously, if an empty space on the board has candies on top of itself, then these candies will drop until they hit a candy or bottom at the same time. No new candies will drop outside the top boundary.
After the above steps, there may exist more candies that can be crushed. If so, you need to repeat the above steps.
If there does not exist more candies that can be crushed (i.e., the board is stable), then return the current board.
You need to perform the above rules until the board becomes stable, then return the stable board.

 

Example 1:


Input: board = [[110,5,112,113,114],[210,211,5,213,214],[310,311,3,313,314],[410,411,412,5,414],[5,1,512,3,3],[610,4,1,613,614],[710,1,2,713,714],[810,1,2,1,1],[1,1,2,2,2],[4,1,4,4,1014]]
Output: [[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[110,0,0,0,114],[210,0,0,0,214],[310,0,0,113,314],[410,0,0,213,414],[610,211,112,313,614],[710,311,412,613,714],[810,411,512,713,1014]]
Example 2:

Input: board = [[1,3,5,5,2],[3,4,3,3,1],[3,2,4,5,2],[2,4,4,5,5],[1,4,4,1,1]]
Output: [[1,3,0,0,0],[3,4,0,5,2],[3,2,0,3,1],[2,4,0,5,2],[1,4,3,1,1]]
 

Constraints:

m == board.length
n == board[i].length
3 <= m, n <= 50
1 <= board[i][j] <= 2000

基本思想：

滑动窗口，横向搜索，纵向搜索，移动模块
*/

typedef pair<int, int> point;

/*
For rules that all connected together
*/

class Solution1 {
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<point> searchp;
    int m, n;
public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        m = board.size();
        n = board[0].size();
        while(true){
            vector<vector<int>> marked(m, vector<int>(n, 0));
            vector<vector<int>> visited(m, vector<int>(n, 0));
            bool finished = true;
            for(int i = 0;i < m;++i){
                for(int j = 0;j < n;++j){
                    if(visited[i][j] != 0 || board[i][j] == 0)
                        continue;
                    
                    searchp.clear();
                    int curn = dfs(i, j, board[i][j], board, visited);
                    if(curn >= 3){
                        for(point p: searchp){
                            marked[p.first][p.second] = 1;
                        }
                        finished = false;
                    }
                }
            }

            if(finished)
                break;
            
            for(int j = 0;j < n;++j)
                moveBoard(j, board, marked);
        }

        return board;
    }

    void moveBoard(int column, vector<vector<int>>& board, vector<vector<int>>& marked){
        int curM = 0;
        for(int i = m - 1;i >= 0;--i){
            if(marked[i][column] != 0){
                curM += 1;
            }
            else{
                board[i + curM][column] = board[i][column];
            }
        }
        for(int i = 0;i < curM;++i){
            board[i][column] = 0;
        }
        return;
    }

    int dfs(int x, int y, int target, vector<vector<int>>& board, vector<vector<int>>& visited){
        if(board[x][y] != target || visited[x][y] == 1){
            return 0;
        }

        searchp.push_back(point(x, y));
        visited[x][y] = 1;
        int total = 1;
        for(int i = 0;i < 4;++i){
            int newx = x + dir[i][0];
            int newy = y + dir[i][1];
            if(isValid(newx, newy)){
                total += dfs(newx, newy, target, board, visited);
            }
        }
        return total;
    }

    bool isValid(int x, int y){
        if(x >= 0 && x < m && y >= 0 && y < n)
            return true;
        return false;
    }
};

/*
for rules only 3 vertical or 3 horizontal
*/

class Solution {
    int m, n;
public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        m = board.size();
        n = board[0].size();
        while(true){
            vector<vector<int>> marked(m, vector<int>(n, 0));
            bool finished = true;
            for(int i = 0;i < m;++i){
                if(check_horizontal(i, board, marked))
                    finished = false;
            }
            for(int j = 0;j < n;++j){
                if(check_vertical(j, board, marked))
                    finished = false;
            }

            if(finished)
                break;
            
            for(int j = 0;j < n;++j)
                moveBoard(j, board, marked);
        }

        return board;
    }

    void moveBoard(int column, vector<vector<int>>& board, vector<vector<int>>& marked){
        int curM = 0;
        for(int i = m - 1;i >= 0;--i){
            if(marked[i][column] != 0){
                curM += 1;
            }
            else{
                board[i + curM][column] = board[i][column];
            }
        }
        for(int i = 0;i < curM;++i){
            board[i][column] = 0;
        }
        return;
    }

    bool check_vertical(int column, vector<vector<int>>& board, vector<vector<int>>& marked){
        int sp = 0;
        bool res = false;
        while(sp < m){
            if(board[sp][column] == 0){
                sp += 1;
                continue;
            }
            
            int ep = sp + 1;
            while(ep < m && board[ep][column] == board[sp][column]){
                ep += 1;
            }
            int length = ep - sp;
            if(length >= 3){
                for(int k = sp;k < ep;++k)
                    marked[k][column] = 1;
                res = true;
            }
            sp = ep;
        }
        return res;
    }

    bool check_horizontal(int row, vector<vector<int>>& board, vector<vector<int>>& marked){
        int sp = 0;
        bool res = false;
        while(sp < n){
            if(board[row][sp] == 0){
                sp += 1;
                continue;
            }

            int ep = sp + 1;
            while(ep < n && board[row][ep] == board[row][sp])
                ep += 1;
            int length = ep - sp;
            if(length >= 3){
                for(int k = sp;k < ep;++k)
                    marked[row][k] = 1;
                res = true;
            }
            sp = ep;
        }
        return res;
    }
};