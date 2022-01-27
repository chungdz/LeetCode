#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;

/*
并查集

**/

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

