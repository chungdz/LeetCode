#include<algorithm>
#include<vector>
#include<stack>
using namespace std;

/*
489

You are controlling a robot that is located somewhere in a room. The room is modeled as an m x n binary grid where 0 represents a wall and 1 represents an empty slot.

The robot starts at an unknown location in the root that is guaranteed to be empty, and you do not have access to the grid, but you can move the robot using the given API Robot.

You are tasked to use the robot to clean the entire room (i.e., clean every empty cell in the room). The robot with the four given APIs can move forward, turn left, or turn right. Each turn is 90 degrees.

When the robot tries to move into a wall cell, its bumper sensor detects the obstacle, and it stays on the current cell.

Design an algorithm to clean the entire room using the following APIs:

interface Robot {
  // returns true if next cell is open and robot moves into the cell.
  // returns false if next cell is obstacle and robot stays on the current cell.
  boolean move();

  // Robot will stay on the same cell after calling turnLeft/turnRight.
  // Each turn will be 90 degrees.
  void turnLeft();
  void turnRight();

  // Clean the current cell.
  void clean();
}
Note that the initial direction of the robot will be facing up. You can assume all four edges of the grid are all surrounded by a wall.

 

Custom testing:

The input is only given to initialize the room and the robot's position internally. You must solve this problem "blindfolded". In other words, you must control the robot using only the four mentioned APIs without knowing the room layout and the initial robot's position.

 

Example 1:


Input: room = [[1,1,1,1,1,0,1,1],[1,1,1,1,1,0,1,1],[1,0,1,1,1,1,1,1],[0,0,0,1,0,0,0,0],[1,1,1,1,1,1,1,1]], row = 1, col = 3
Output: Robot cleaned all rooms.
Explanation: All grids in the room are marked by either 0 or 1.
0 means the cell is blocked, while 1 means the cell is accessible.
The robot initially starts at the position of row=1, col=3.
From the top left corner, its position is one row below and three columns right.
Example 2:

Input: room = [[1]], row = 0, col = 0
Output: Robot cleaned all rooms.
 

Constraints:

m == room.length
n == room[i].length
1 <= m <= 100
1 <= n <= 200
room[i][j] is either 0 or 1.
0 <= row < m
0 <= col < n
room[row][col] == 1
All the empty cells can be visited from the starting position.




基本思想：

深搜，搜索所有的empty space

但是要让机器人跟着搜索的方向移动，所以需要记录移动轨迹，搜索迭代返回时，机器人也要跟着返回


**/


class Robot {
public:
    // Returns true if the cell in front is open and robot moves into the cell.
    // Returns false if the cell in front is blocked and robot stays in the current cell.
    bool move();

    // Robot will stay in the same cell after calling turnLeft/turnRight.
    // Each turn will be 90 degrees.
    void turnLeft();
    void turnRight();

    // Clean the current cell.
    void clean();
};

#define MAX_ROW 300
#define MAX_COL 600

class Solution {
    // assume face to north, but it does not matter where it face
    // south 0 west 1 north 2 east 3
    int front = 2;
    // action sequence, record to return back
    // represents in which direction move 1 step
    stack<int> movements;
    // room record for cleaning
    // 0: unknown 1: cleaned 2: wall
    char room[MAX_ROW][MAX_COL] = {0};
    Robot *rob;
public:
    void cleanRoom(Robot& robot) {
        rob = &robot;
        // assume is in the middle of grids
        // grids are big enough too hold all information
        clean_bfs(MAX_ROW / 2, MAX_COL / 2);
    }

    // bfs and clean
    void clean_bfs(int c_row, int c_col){
        // valid area if can enter
        // clean first
        rob->clean();
        room[c_row][c_col] = 1;
        // search up
        int up_row = c_row - 1;
        if(room[up_row][c_col] == 0){
            turn_to(2);
            if(rob->move()){
                movements.push(2);
                clean_bfs(up_row, c_col);
            }
            else{
                room[up_row][c_col] = 2;
            }
        }
        // search right
        int right_col = c_col + 1;
        if(room[c_row][right_col] == 0){
            turn_to(3);
            if(rob->move()){
                movements.push(3);
                clean_bfs(c_row, right_col);
            }
            else{
                room[c_row][right_col] = 2;
            }
        }
        // search down
        int down_row = c_row + 1;
        if(room[down_row][c_col] == 0){
            turn_to(0);
            if(rob->move()){
                movements.push(0);
                clean_bfs(down_row, c_col);
            }
            else{
                room[down_row][c_col] = 2;
            }
        }
        // search left
        int left_col = c_col - 1;
        if(room[c_row][left_col] == 0){
            turn_to(1);
            if(rob->move()){
                movements.push(1);
                clean_bfs(c_row, left_col);
            }
            else{
                room[c_row][left_col] = 2;
            }
        }


        // turn back
        if(!movements.empty()){
            step_back();
        }

        return;
    }

    void step_back(){
        int pre_move = movements.top();
        movements.pop();
        int opp_d = opposite_direction(pre_move);
        turn_to(opp_d);
        rob->move();
    }

    void turn_to(int dto){
        if(front == dto){
            return;
        }
        // south to east
        if(front == 0 && dto == 3){
            rob->turnLeft();
        }
        // east to south
        else if(front == 3 && dto == 0){
            rob->turnRight();
        }
        else{
            if(front < dto){
                int tnum = dto - front;
                while(tnum--){rob->turnRight();}
            }
            else{
                int tnum = front - dto;
                while(tnum--){rob->turnLeft();}
            }
        }

        front = dto;
        return;
    }

    int opposite_direction(int origin){
        if(origin == 0){return 2;}
        else if(origin == 1){return 3;}
        else if(origin == 2){return 0;}
        else{return 1;}
    }
};

