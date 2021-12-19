#include<vector>
#include<string>
#include<algorithm>
using namespace std;

/*
957 Prison Cells After N Days

There are 8 prison cells in a row and each cell is either occupied or vacant.

Each day, whether the cell is occupied or vacant changes according to the following rules:

If a cell has two adjacent neighbors that are both occupied or both vacant, then the cell becomes occupied.
Otherwise, it becomes vacant.
Note that because the prison is a row, the first and the last cells in the row can't have two adjacent neighbors.

You are given an integer array cells where cells[i] == 1 if the ith cell is occupied and cells[i] == 0 if the ith cell is vacant, and you are given an integer n.

Return the state of the prison after n days (i.e., n such changes described above).

 

Example 1:

Input: cells = [0,1,0,1,1,0,0,1], n = 7
Output: [0,0,1,1,0,0,0,0]
Explanation: The following table summarizes the state of the prison on each day:
Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
Day 7: [0, 0, 1, 1, 0, 0, 0, 0]
Example 2:

Input: cells = [1,0,0,1,0,0,1,0], n = 1000000000
Output: [0,0,1,1,1,1,1,0]
 

Constraints:

cells.length == 8
cells[i] is either 0 or 1.
1 <= n <= 10^9


基本思想： 
找循环
储存循环用char来储存，节省空间，所以有用到位运算
*/

class Solution {
    vector<char> nums;
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int n) {
        vector<int> pred = cells, nxtd;
        char pren, nxtn;
        while(true){
            nxtd = nextday(pred);
            nxtn = v2num(nxtd);

            if(nums.size() > 0 && nxtn == nums[0])
                break;
            // for(char n: nxtd){
            //     cout << int(n) << " ";
            // }
            // cout << endl << int(nxtn) << endl;
            nums.push_back(nxtn);
            pren = nxtn;
            pred = nxtd;
        }

        int modr = (n - 1) % nums.size();
        return num2v(nums[modr]);
    }

    char v2num(vector<int>& cells){
        char cur_num = 0;
        char cur_add = 1;
        for(int i = 7;i >= 0;--i){
            cur_num += cells[i] * cur_add;
            cur_add *= 2;
        }
        return cur_num;
    }

    vector<int> num2v(char num){
        vector<int> res;
        for(int i = 0;i < 8;++i){
            int cur_pos = 1 & num;
            res.push_back(cur_pos);
            num = num >> 1;
        }
        reverse(res.begin(), res.end());
        return res;
    }

    vector<int> nextday(vector<int>& cells){
        vector<int> nextd(8, 0);
        for(int i = 0;i < 8;++i){
            if(i - 1 >= 0 && i + 1 < 8){
                if(cells[i - 1] == cells[i + 1]){
                    nextd[i] = 1;
                }
            }
            else{
                nextd[i] = 0;
            }
        }
        return nextd;
    }
};