#include<queue>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

/**
 * 210
 * 
 * There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].
Example 2:

Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].
Example 3:

Input: numCourses = 1, prerequisites = []
Output: [0]
 

Constraints:

1 <= numCourses <= 2000
0 <= prerequisites.length <= numCourses * (numCourses - 1)
prerequisites[i].length == 2
0 <= ai, bi < numCourses
ai != bi
All the pairs [ai, bi] are distinct.
 * 
 * 
 * 
 * 基本思路
 * 
 * 建立图，定义为拓扑图
 * 
 * 宽度优先遍历拓扑图
 * 
 * 
 * 
 * 
 * 
 */

class Solution {
    map<int, int> parents_num;
    map<int, vector<int>> children;
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        for(int i = 0;i < numCourses;++i){
            parents_num[i] = 0;
            children[i] = vector<int>();
        }

        for(auto k: prerequisites){
            parents_num[k[0]] += 1;
            children[k[1]].push_back(k[0]);
        }

        queue<int> bfs;
        for(auto mit: parents_num){
            if(mit.second == 0)
                bfs.push(mit.first);
        }

        vector<int> res;
        while(!bfs.empty()){
            int cur_index = bfs.front();
            res.push_back(cur_index);
            for(auto c: children[cur_index]){
                parents_num[c] -= 1;
                if(parents_num[c] == 0){
                    bfs.push(c);
                }
            }
            bfs.pop();
        }

        if(res.size() < numCourses){res.clear();}
        return res;
    }
};