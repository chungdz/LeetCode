from typing import _promote

'''
348 Design Tic-Tac-Toe

Assume the following rules are for the tic-tac-toe game on an n x n board between two players:

A move is guaranteed to be valid and is placed on an empty block.
Once a winning condition is reached, no more moves are allowed.
A player who succeeds in placing n of their marks in a horizontal, vertical, or diagonal row wins the game.
Implement the TicTacToe class:

TicTacToe(int n) Initializes the object the size of the board n.
int move(int row, int col, int player) Indicates that the player with id player plays at the cell (row, col) of the board. The move is guaranteed to be a valid move.
 

Example 1:

Input
["TicTacToe", "move", "move", "move", "move", "move", "move", "move"]
[[3], [0, 0, 1], [0, 2, 2], [2, 2, 1], [1, 1, 2], [2, 0, 1], [1, 0, 2], [2, 1, 1]]
Output
[null, 0, 0, 0, 0, 0, 0, 1]

Explanation
TicTacToe ticTacToe = new TicTacToe(3);
Assume that player 1 is "X" and player 2 is "O" in the board.
ticTacToe.move(0, 0, 1); // return 0 (no one wins)
|X| | |
| | | |    // Player 1 makes a move at (0, 0).
| | | |

ticTacToe.move(0, 2, 2); // return 0 (no one wins)
|X| |O|
| | | |    // Player 2 makes a move at (0, 2).
| | | |

ticTacToe.move(2, 2, 1); // return 0 (no one wins)
|X| |O|
| | | |    // Player 1 makes a move at (2, 2).
| | |X|

ticTacToe.move(1, 1, 2); // return 0 (no one wins)
|X| |O|
| |O| |    // Player 2 makes a move at (1, 1).
| | |X|

ticTacToe.move(2, 0, 1); // return 0 (no one wins)
|X| |O|
| |O| |    // Player 1 makes a move at (2, 0).
|X| |X|

ticTacToe.move(1, 0, 2); // return 0 (no one wins)
|X| |O|
|O|O| |    // Player 2 makes a move at (1, 0).
|X| |X|

ticTacToe.move(2, 1, 1); // return 1 (player 1 wins)
|X| |O|
|O|O| |    // Player 1 makes a move at (2, 1).
|X|X|X|
 

Constraints:

2 <= n <= 100
player is 1 or 2.
0 <= row, col < n
(row, col) are unique for each different call to move.
At most n2 calls will be made to move.
 

Follow-up: Could you do better than O(n^2) per move() operation?

基本思想

创建row col diagonal来记录count
'''

class TicTacToe:

    def __init__(self, n: int):
        self.board = [[-1] * n for _ in range(n)]
        self.n = n

        self.p_row = [[0] * n for _ in range(2)]
        self.p_col = [[0] * n for _ in range(2)]
        self.p_diagonal = [[0] * 2 for _ in range(2)]

    def move(self, row: int, col: int, player: int) -> int:
        pindex = player - 1
        self.board[row][col] = pindex

        self.p_row[pindex][row] += 1
        if self.p_row[pindex][row] == self.n:
            # print('row', self.p_row[pindex])
            return player
        self.p_col[pindex][col] += 1
        if self.p_col[pindex][col] == self.n:
            # print('col', self.p_col[pindex])
            return player
        if row == col:
            self.p_diagonal[pindex][0] += 1
            if self.p_diagonal[pindex][0] == self.n:
                # print('diagonal', self.p_diagonal[pindex])
                return player
        if row + col == self.n - 1:
            self.p_diagonal[pindex][1] += 1
            if self.p_diagonal[pindex][1] == self.n:
                # print('reverse diagonal', self.p_diagonal[pindex])
                return player

        return 0