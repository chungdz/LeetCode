#include<vector>
#include<algorithm>
using namespace std;

/***
 * 849
 * 
 * 
You are given an array representing a row of seats where seats[i] = 1 represents a person sitting in the ith seat, and seats[i] = 0 represents that the ith seat is empty (0-indexed).

There is at least one empty seat, and at least one person sitting.

Alex wants to sit in the seat such that the distance between him and the closest person to him is maximized. 

Return that maximum distance to the closest person.

 

Example 1:


Input: seats = [1,0,0,0,1,0,1]
Output: 2
Explanation: 
If Alex sits in the second open seat (i.e. seats[2]), then the closest person has distance 2.
If Alex sits in any other open seat, the closest person has distance 1.
Thus, the maximum distance to the closest person is 2.
Example 2:

Input: seats = [1,0,0,0]
Output: 3
Explanation: 
If Alex sits in the last seat (i.e. seats[3]), the closest person is 3 seats away.
This is the maximum distance possible, so the answer is 3.
Example 3:

Input: seats = [0,1]
Output: 1
 

Constraints:

2 <= seats.length <= 2 * 10^4
seats[i] is 0 or 1.
At least one seat is empty.
At least one seat is occupied.
 * 
 * 
 * 基本思想
 * 
 * 记录有人的位置，然后遍历间隔，开头和结尾特殊查看
 * 
*/

class Solution {
    vector<int> seat_record;
public:
    int maxDistToClosest(vector<int>& seats) {
        int seat_size = seats.size();
        for(int i = 0;i < seat_size;++i){
            if(seats[i] == 1){
                seat_record.push_back(i);
            }
        }

        int max_len = -1;
        int cur_len;
        // check 0
        if(seat_record[0] > 0){
            cur_len = seat_record[0];
            max_len = max(max_len, cur_len);
        }

        int people_num = seat_record.size();
        for(int i = 0;i < people_num - 1;++i){
            int dis = seat_record[i + 1] - seat_record[i];
            if(dis <= 1){continue;}
            cur_len = dis / 2;
            max_len = max(max_len, cur_len);
        }

        // check last
        cur_len = (seat_size - 1) - seat_record[people_num - 1];
        if(cur_len > 0){
            max_len = max(max_len, cur_len);
        }

        return max_len;
    }
};