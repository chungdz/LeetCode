#include<algorithm>
#include<string>
#include<map>
#include<set>
using namespace std;

/*

399

You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.

You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.

Return the answers to all queries. If a single answer cannot be determined, return -1.0.

Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.

 

Example 1:

Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
Explanation: 
Given: a / b = 2.0, b / c = 3.0
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
Example 2:

Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
Output: [3.75000,0.40000,5.00000,0.20000]
Example 3:

Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
Output: [0.50000,2.00000,-1.00000,-1.00000]
 

Constraints:

1 <= equations.length <= 20
equations[i].length == 2
1 <= Ai.length, Bi.length <= 5
values.length == equations.length
0.0 < values[i] <= 20.0
1 <= queries.length <= 20
queries[i].length == 2
1 <= Cj.length, Dj.length <= 5
Ai, Bi, Cj, Dj consist of lower case English letters and digits.



基本思想

图的寻路，先用节点关系建立图（双向边，逆边值为正边值的倒数），然后根据给定的起点终点寻路，路径值相乘就是结果
为了避免重复搜索，将已经探索过的路径值都记录下来，如果不存在路径，就返回-1.0，路径值也保存-1.0
这会使得新增很多路径，注意当做搜索时，还需要注意当前搜寻的路径的路径值是否合规（如果是-1.0说明路径非法）

用的深度优先搜索，最好用广度优先搜索（暂时没想出来怎么整），因为广度优先使得乘除法路径最短，避免精度丢失，
需要剔除被访问过的节点，因为有圈存在避免死循环

**/


class Solution {
    map<string, map<string, double>> graph;
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int total_size = equations.size();
        for(int i = 0;i < total_size;++i){
            string s = equations[i][0];
            string e = equations[i][1];
            double v = values[i];

            if(graph.find(s) == graph.end()){
                graph[s] = map<string, double>();
                graph[s][s] = 1.0;
            }
            if(graph.find(e) == graph.end()){
                graph[e] = map<string, double>();
                graph[e][e] = 1.0;
            }

            graph[s][e] = v;
            graph[e][s] = 1.0 / v;
        }

        vector<double> res;
        for(auto q: queries){
            string cur_start = q[0];
            string cur_end = q[1];
            set<string> cur_visited;

            res.push_back(search_path(cur_start, cur_end, cur_visited));
        }

        return res;
    }

    double search_path(string start, string end, set<string>& visited){
        if(graph.find(start) == graph.end() || graph.find(end) == graph.end()){return -1.0;}

        visited.insert(start);

        if(graph[start].find(end) != graph[start].end()){
            return graph[start][end];
        }

        for(auto mpair: graph[start]){
            string edge_to = mpair.first;
            double edge_value = mpair.second;
            if(edge_value == -1.0){continue;}

            if(visited.find(edge_to) != visited.end()){continue;}
            if(graph[edge_to].find(end) == graph[edge_to].end()){
                search_path(edge_to, end, visited);
            }
            if(graph[edge_to][end] != -1.0){
                graph[start][end] = edge_value * graph[edge_to][end];
                break;
            }
        }

        if(graph[start].find(end) == graph[start].end()){
            graph[start][end] = -1.0;
        }

        return graph[start][end];
    }
};