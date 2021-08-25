#include<vector>
#include<map>
#include<algorithm>
using namespace std;

/**
 * 
 * 253
 * 
 * 
Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.

 

Example 1:

Input: intervals = [[0,30],[5,10],[15,20]]
Output: 2
Example 2:

Input: intervals = [[7,10],[2,4]]
Output: 1
 

Constraints:

1 <= intervals.length <= 104
0 <= starti < endi <= 106
 * 
 * 
 * 基本思路
 * 
 * 分别排序开始时间，结束时间
 * 
 * 双指针遍历两个时间分别处理，结束时间到了就增加room，开始时间到了就减少room
 * 
 * 
 * **/

class Solution {
    int total_room = 1;
    int empty_room = 1;
    map<int, int> end_time2room_num;
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector<int> start_time, end_time;
        for(auto conf: intervals){
            start_time.push_back(conf[0]);
            end_time.push_back(conf[1]);
        }

        sort(start_time.begin(), start_time.end());
        sort(end_time.begin(), end_time.end());

        int total_size = intervals.size();
        int sp = 0, ep = 0;
        while(sp < total_size){
            if(end_time[ep] <= start_time[sp]){
                empty_room += 1;
                ep += 1;
            }
            else{
                if(empty_room < 1){
                    empty_room += 1;
                    total_room += 1;
                }

                empty_room -= 1;
                sp += 1;
            }
        }
        return total_room;
    }
};