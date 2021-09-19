#include<vector>
#include<string>
#include<algorithm>
using namespace std;

/*
731

My Calendar II

Solution
You are implementing a program to use as your calendar. We can add a new event if adding the event will not cause a triple booking.

A triple booking happens when three events have some non-empty intersection (i.e., some moment is common to all the three events.).

The event can be represented as a pair of integers start and end that represents a booking on the half-open interval [start, end), the range of real numbers x such that start <= x < end.

Implement the MyCalendarTwo class:

MyCalendarTwo() Initializes the calendar object.
boolean book(int start, int end) Returns true if the event can be added to the calendar successfully without causing a triple booking. Otherwise, return false and do not add the event to the calendar.
 

Example 1:

Input
["MyCalendarTwo", "book", "book", "book", "book", "book", "book"]
[[], [10, 20], [50, 60], [10, 40], [5, 15], [5, 10], [25, 55]]
Output
[null, true, true, true, false, true, true]

Explanation
MyCalendarTwo myCalendarTwo = new MyCalendarTwo();
myCalendarTwo.book(10, 20); // return True, The event can be booked. 
myCalendarTwo.book(50, 60); // return True, The event can be booked. 
myCalendarTwo.book(10, 40); // return True, The event can be double booked. 
myCalendarTwo.book(5, 15);  // return False, The event ca not be booked, because it would result in a triple booking.
myCalendarTwo.book(5, 10); // return True, The event can be booked, as it does not use time 10 which is already double booked.
myCalendarTwo.book(25, 55); // return True, The event can be booked, as the time in [25, 40) will be double booked with the third event, the time [40, 50) will be single booked, and the time [50, 55) will be double booked with the second event.
 

Constraints:

0 <= start < end <= 10^9
At most 1000 calls will be made to book


基本思想

排序 + 插入
前后查找
理论上滑动窗口从当前位置[i - 2, i + 2]就行了，但是不明白为什么只有访问[i - 3, i + 3]才行
**/

bool cmp(const pair<int, int>& p1, const pair<int, int>& p2){
    if(p1.first == p2.first){
        return p1.second < p2.second;
    }
    else{
        return p1.first < p2.first;
    }
}

class MyCalendarTwo {
    vector<pair<int, int>> booked;

    bool check_inter(pair<int, int> v1, pair<int, int> v2){
        if(v1.second <= v2.first || v1.first >= v2.second){return false;}
        return true;
    }
public:
    MyCalendarTwo() {
        
    }
    
    bool book(int start, int end) {
        if(booked.size() < 1){
            booked.push_back(pair<int, int>(start, end));
            return true;
        }
        else{
            pair<int, int> cur_trans(start, end);
            vector<pair<int, int>>::iterator it = lower_bound(booked.begin(), booked.end(), cur_trans, cmp);

            vector<pair<int, int>>::iterator pre = it, nxt = it;

            int cnt = 3;
            vector<pair<int, int>> neighbors;
            while(pre != booked.begin()){
                --pre;
                --cnt;
                if(check_inter(*pre, cur_trans)){
                    neighbors.insert(neighbors.begin(), *pre);
                }
                if(cnt == 0){break;}
            }

            cnt = 3;
            while(nxt != booked.end()){
                if(check_inter(*nxt, cur_trans)){
                    neighbors.push_back(*nxt);
                }
                ++nxt;
                --cnt;
                if(cnt == 0){break;}
            }
            
            int nsize = neighbors.size();
            if(neighbors.size() < 2){
                booked.insert(it, cur_trans);
                return true;
            }

            for(int i = 0;i < nsize - 1;++i){
                if(check_inter(neighbors[i], neighbors[i + 1])){
                    return false;
                }
            }

            booked.insert(it, cur_trans);
            return true;
        }
    }
};