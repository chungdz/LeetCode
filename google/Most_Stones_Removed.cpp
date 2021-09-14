#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;

/*











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

