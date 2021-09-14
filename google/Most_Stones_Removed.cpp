#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;

/*
947

On a 2D plane, we place n stones at some integer coordinate points. Each coordinate point may have at most one stone.

A stone can be removed if it shares either the same row or the same column as another stone that has not been removed.

Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith stone, return the largest possible number of stones that can be removed.

 

Example 1:

Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5
Explanation: One way to remove 5 stones is as follows:
1. Remove stone [2,2] because it shares the same row as [2,1].
2. Remove stone [2,1] because it shares the same column as [0,1].
3. Remove stone [1,2] because it shares the same row as [1,0].
4. Remove stone [1,0] because it shares the same column as [0,0].
5. Remove stone [0,1] because it shares the same row as [0,0].
Stone [0,0] cannot be removed since it does not share a row/column with another stone still on the plane.
Example 2:

Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3
Explanation: One way to make 3 moves is as follows:
1. Remove stone [2,2] because it shares the same row as [2,0].
2. Remove stone [2,0] because it shares the same column as [0,0].
3. Remove stone [0,2] because it shares the same row as [0,0].
Stones [0,0] and [1,1] cannot be removed since they do not share a row/column with another stone still on the plane.
Example 3:

Input: stones = [[0,0]]
Output: 0
Explanation: [0,0] is the only stone on the plane, so you cannot remove it.
 

Constraints:

1 <= stones.length <= 1000
0 <= xi, yi <= 10^4
No two stones are at the same coordinate point.


S1

每次将图出入度大于零且最小的去掉，有问题
指针的排序问题解决

S2

并查集

因为连通图的特性，连通图内所有节点一定有一个方法使得消去只剩下1

去除的石头 = 总的石头 - 连通图个数

**/

struct graph_nodes{
    set<graph_nodes*> relations;
    int cur_pos;

    bool operator< (const graph_nodes &v)const{
        return relations.size() < v.relations.size();
    }
};

bool less_cmp(const graph_nodes *n1, const graph_nodes *n2){
    return n1->relations.size() < n2->relations.size();
}

class Solution {
    map<int, vector<int>> x_same;
    map<int, vector<int>> y_same;
    vector<pair<graph_nodes*, int>> ordered_nodes;
    vector<graph_nodes*> node_list;
public:
    int removeStones(vector<vector<int>>& stones) {
        int total_stone = stones.size();
        if(total_stone < 2){return 0;}
        // find same coordinate
        for(int i = 0;i < total_stone;++i){
            x_same[stones[i][0]].push_back(i);
            y_same[stones[i][1]].push_back(i);
            graph_nodes *new_node = new graph_nodes();
            node_list.push_back(new_node);
        }
        // build graph
        for(auto p: x_same){
            int cur_size = p.second.size();
            if(cur_size < 2){continue;}
            for(int i = 0;i < cur_size - 1;++i){
                for(int j = i + 1;j < cur_size;++j){
                    graph_nodes *n1 = node_list[p.second[i]];
                    graph_nodes *n2 = node_list[p.second[j]];
                    n1->relations.insert(n2);
                    n2->relations.insert(n1);
                }
            }
        }

        for(auto p: y_same){
            int cur_size = p.second.size();
            if(cur_size < 2){continue;}
            for(int i = 0;i < cur_size - 1;++i){
                for(int j = i + 1;j < cur_size;++j){
                    graph_nodes *n1 = node_list[p.second[i]];
                    graph_nodes *n2 = node_list[p.second[j]];
                    n1->relations.insert(n2);
                    n2->relations.insert(n1);
                }
            }
        }
        // order the nodes
        sort(node_list.begin(), node_list.end(), less_cmp);
        // remove relation size 0 nodes
        while(node_list.front()->relations.size() < 1){
            if(node_list.size() <= 1){return 0;}
            node_list.erase(node_list.begin());
        }
        // pick nodes with least relations but not zero
        int res = 0;
        while(node_list.size() > 1){
            res += 1;
            graph_nodes *cur_node = node_list.front();
            for(graph_nodes* neighbor: cur_node->relations){
                // erase cur_node
                neighbor->relations.erase(cur_node);
            }
            node_list.erase(node_list.begin());
            if(node_list.size() <= 1){break;}
            // sort again
            sort(node_list.begin(), node_list.end(), less_cmp);
            while(node_list.front()->relations.size() < 1){
                node_list.erase(node_list.begin());
            }
        }

        return res;
    }
};

template <class T>
class UnionFind{
    map<T, T> parent;
    int union_count = 0;
public:
    T find_parent(T cur_n){
        if(parent.find(cur_n) == parent.end()){
            parent[cur_n] = cur_n;
            union_count++;
            return cur_n;
        }
        else{
            if(parent[cur_n] != cur_n){
                parent[cur_n] = find_parent(parent[cur_n]);
                return parent[cur_n];
            }

            return cur_n;
        }
    }

    void union_two(T cur_x, T cur_y){
        T p1 = find_parent(cur_x);
        T p2 = find_parent(cur_y);
        if(p1 != p2){
            parent[p1] = p2;
            union_count--;
        }
    }

    int check_count(){return union_count;}
};

class Solution {
    map<int, vector<int>> x_same;
    map<int, vector<int>> y_same;
    UnionFind<int> uf;
public:
    int removeStones(vector<vector<int>>& stones) {
        int total_stone = stones.size();
        
        // find same coordinate
        for(int i = 0;i < total_stone;++i){
            x_same[stones[i][0]].push_back(i);
            y_same[stones[i][1]].push_back(i);
            uf.find_parent(i);
        }
        // build union
        for(auto p: x_same){
            int cur_size = p.second.size();
            if(cur_size < 2){continue;}
            for(int i = 0;i < cur_size - 1;++i){
                for(int j = i + 1;j < cur_size;++j){
                    uf.union_two(p.second[i], p.second[j]);
                }
            }
        }

        for(auto p: y_same){
            int cur_size = p.second.size();
            if(cur_size < 2){continue;}
            for(int i = 0;i < cur_size - 1;++i){
                for(int j = i + 1;j < cur_size;++j){
                    uf.union_two(p.second[i], p.second[j]);
                }
            }
        }
        
        return total_stone - uf.check_count();
    }
};

