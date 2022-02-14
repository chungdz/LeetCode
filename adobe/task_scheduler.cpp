#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>
#include<unordered_set>
using namespace std;

/*
621 Task Scheduler

Given a characters array tasks, representing the tasks a CPU needs to do, where each letter represents a different task. Tasks could be done in any order. Each task is done in one unit of time. For each unit of time, the CPU could complete either one task or just be idle.

However, there is a non-negative integer n that represents the cooldown period between two same tasks (the same letter in the array), that is that there must be at least n units of time between any two same tasks.

Return the least number of units of times that the CPU will take to finish all the given tasks.

 

Example 1:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: 
A -> B -> idle -> A -> B -> idle -> A -> B
There is at least 2 units of time between any two same tasks.
Example 2:

Input: tasks = ["A","A","A","B","B","B"], n = 0
Output: 6
Explanation: On this case any permutation of size 6 would work since n = 0.
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
And so on.
Example 3:

Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
Output: 16
Explanation: 
One possible solution is
A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle -> idle -> A
 

Constraints:

1 <= task.length <= 104
tasks[i] is upper-case English letter.
The integer n is in the range [0, 100].

基本思想

贪心：使用最大堆每次从可以做的task里面找最大的来做
*/

typedef pair<char, int> Point;

struct CustomCompare
{
    bool operator()(const Point& lhs, const Point& rhs)
    {
        return lhs.second < rhs.second;
    }
};

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        priority_queue<Point, vector<Point>, CustomCompare> q;
        unordered_map<char, int> tnum;
        unordered_map<char, int> blocked;
        for(char c: tasks)
            if(tnum.find(c) != tnum.end())
                tnum[c] += 1;
            else
                tnum[c] = 1;
    
        // cout << tnum.size() << endl;
        for(auto it: tnum){
            q.push(Point(it.first, it.second));
        }
        
        int steps = 0;
        while(tnum.size() > 0){
            // cout << "q size " << q.size() << endl;
            if(q.size() > 0){
                Point p = q.top();
                q.pop();
                tnum[p.first] -= 1;
                // cout << "cur num " << tnum[p.first] << endl;
                if(tnum[p.first] > 0)
                    blocked[p.first] = n + 1;
                else{
                    // cout << "erase " << p.first << endl;
                    tnum.erase(p.first);
                }
                    
            }
            // else
            //     cout << "idle" << endl;
        
            // cout << "start releasing" << endl;
            vector<char> to_delete;
            for(auto &itb:blocked){
                itb.second -= 1;
                // cout << "itb second" << itb.second << endl;
                if(itb.second < 1){
                    char ckey = itb.first;
                    q.push(Point(ckey, tnum[ckey]));
                    to_delete.push_back(ckey);
                }
            }
            for(auto c: to_delete)
                blocked.erase(c);
            // cout << "loop finished" << endl;
            steps += 1;
        }
        return steps;
    }
};