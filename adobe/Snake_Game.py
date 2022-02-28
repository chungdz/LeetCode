'''
353 Design Snake Game
Design a Snake game that is played on a device with screen size height x width. Play the game online if you are not familiar with the game.

The snake is initially positioned at the top left corner (0, 0) with a length of 1 unit.

You are given an array food where food[i] = (ri, ci) is the row and column position of a piece of food that the snake can eat. When a snake eats a piece of food, its length and the game's score both increase by 1.

Each piece of food appears one by one on the screen, meaning the second piece of food will not appear until the snake eats the first piece of food.

When a piece of food appears on the screen, it is guaranteed that it will not appear on a block occupied by the snake.

The game is over if the snake goes out of bounds (hits a wall) or if its head occupies a space that its body occupies after moving (i.e. a snake of length 4 cannot run into itself).

Implement the SnakeGame class:

SnakeGame(int width, int height, int[][] food) Initializes the object with a screen of size height x width and the positions of the food.
int move(String direction) Returns the score of the game after applying one direction move by the snake. If the game is over, return -1.
 

Example 1:


Input
["SnakeGame", "move", "move", "move", "move", "move", "move"]
[[3, 2, [[1, 2], [0, 1]]], ["R"], ["D"], ["R"], ["U"], ["L"], ["U"]]
Output
[null, 0, 0, 1, 1, 2, -1]

Explanation
SnakeGame snakeGame = new SnakeGame(3, 2, [[1, 2], [0, 1]]);
snakeGame.move("R"); // return 0
snakeGame.move("D"); // return 0
snakeGame.move("R"); // return 1, snake eats the first piece of food. The second piece of food appears at (0, 1).
snakeGame.move("U"); // return 1
snakeGame.move("L"); // return 2, snake eats the second food. No more food appears.
snakeGame.move("U"); // return -1, game over because snake collides with border
 

Constraints:

1 <= width, height <= 10^4
1 <= food.length <= 50
food[i].length == 2
0 <= ri < height
0 <= ci < width
direction.length == 1
direction is 'U', 'D', 'L', or 'R'.
At most 104 calls will be made to move.

基本思想

用list记录贪吃蛇的每个位置，每次移动，如果没吃到东西，就弹出尾巴插入头部，如果吃到东西，就不弹出尾巴

注意判断是否撞墙，是否吃到自己，吃到尾巴不算失败
'''

class SnakeGame:

    def __init__(self, width: int, height: int, food: List[List[int]]):
        self.fidx = 0
        self.f = food
        self.w = width
        self.h = height
        self.panel = [[0] * width for _ in range(height)]
        self.d = {
            "R": [0, 1],
            "L": [0, -1],
            "U": [-1, 0],
            "D": [1, 0]
        }
        self.plist = [[0, 0]]
        self.panel[0][0] = 1
        self.length = 1
        self.set_food()
    
    def set_food(self):
        if self.fidx < len(self.f):
            posx, posy = self.f[self.fidx]
            self.panel[posx][posy] = 2
            self.fidx += 1
    
    def isValid(self, r, c):
        if r < self.h and r >= 0 and c < self.w and c >= 0:
            return True
        return False

    def move(self, direction: str) -> int:
        head = self.plist[0]
        tail = self.plist[-1]
        # calculate if it hits wall or itself
        nx = self.d[direction][0] + head[0]
        ny = self.d[direction][1] + head[1]
        if not self.isValid(nx, ny):
            return -1
        eat_food = False
        if self.panel[nx][ny] == 1:
            if tail[0] != nx or tail[1] != ny:
                return -1
        elif self.panel[nx][ny] == 2:
            eat_food = True
            self.length += 1
        # move
        if not eat_food:
            self.plist.pop()
            self.panel[tail[0]][tail[1]] = 0
        
        self.plist.insert(0, [nx, ny])
        self.panel[nx][ny] = 1
        # set 
        if eat_food:
            self.set_food()
        
        return self.length - 1
        