#include<string>
#include<set>
using namespace std;

/**
 * 681. Next Closest Time
 * 
Given a time represented in the format "HH:MM", form the next closest time by reusing the current digits. There is no limit on how many times a digit can be reused.

You may assume the given input string is always valid. For example, "01:34", "12:09" are all valid. "1:34", "12:9" are all invalid.

 

Example 1:

Input: time = "19:34"
Output: "19:39"
Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39, which occurs 5 minutes later.
It is not 19:33, because this occurs 23 hours and 59 minutes later.
Example 2:

Input: time = "23:59"
Output: "22:22"
Explanation: The next closest time choosing from digits 2, 3, 5, 9, is 22:22.
It may be assumed that the returned time is next day's time since it is smaller than the input time numerically.
 

Constraints:

time.length == 5
time is a valid time in the form "HH:MM".
0 <= HH < 24
0 <= MM < 60
 * 
 * 
 * 
 * 基本思路
 * 
 * 暴力搜索，搜索所有的字符组合
 * 
 * 得到的时间进行有效判断
 * 
 * 如果得到的时间小于当前时间，在小时上加24
 * 
 * 时间间隔用 小时 * 60 + 分钟 来表示并相减
 * 
 */


class Solution {
    int min_interval = 24 * 60;
    string min_string;
    int dn[4];
    int dsize;
    int search_res[4];
    int mhour, mminute;
public:
    string nextClosestTime(string time) {
        // record the different number
        set<int> number_t;
        for(char c: time){
            if(isdigit(c)){number_t.insert(c - '0');}
        }
        dsize = number_t.size();
        int dindex = 0;
        for(int c: number_t){
            dn[dindex] = c;
            dindex++;
        }
        // record current hour and minute
        mhour = (time[0] - '0') * 10 + (time[1] - '0');
        mminute = (time[3] - '0') * 10 + (time[4] - '0');
        min_string = time;
        // brute force search
        search_time(0);
        return min_string;
    }

    void search_time(int cur_index){
        if(cur_index >= 4){
            check_valid();
            return;
        }

        for(int j = 0;j < dsize;++j){
            search_res[cur_index] = dn[j];
            search_time(cur_index + 1);
        }

        return;
    }

    void check_valid(){
        int chour = search_res[0] * 10 + search_res[1];
        int cminute = search_res[2] * 10 + search_res[3];
        if(chour >= 24 || cminute >= 60){
            return;
        }

        // next day
        int thour = chour;
        if(thour < mhour){thour += 24;}
        else if(thour == mhour){
            if(cminute <= mminute){
                thour += 24;
            }
        }
        // interval
        int inter = thour * 60 + cminute - (mhour * 60 + mminute);
        // update
        if(inter < min_interval){
            min_interval = inter;
            string s_hour = to_string(chour);
            string s_minute = to_string(cminute);
            if(s_hour.size() < 2){s_hour = "0" + s_hour;}
            if(s_minute.size() < 2){s_minute = "0" + s_minute;}
            min_string = s_hour + ":" + s_minute;
        }
        return;
    }
};