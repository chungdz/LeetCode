#include<vector>
#include<map>
#include<algorithm>
#include<memory.h>
using namespace std;

/*
SUM 线段树 (307)
**/

class Segment_Tree{
    int *tree_nodes;
    int n;
public:
    Segment_Tree(int number){
        n = 1;
        while(n < number){
            n *= 2;
        }
        // even if number == n, the tree nodes are not exceed 2 * n - 1
        // because inner nodes number is n - 1, and leaf number is n
        // if number < n, we treat remain nodes as blank nodes
        // when query, as there are intervals, could not lead to error
        tree_nodes = new int[2 * n - 1];
        // as it is a sum tree I init it all to zero for robustness
        memset(tree_nodes, 0, sizeof(int) * (2 * n - 1));
    }

    void update(int index, int a){
        // add leaf offset to index
        index += n - 1;
        tree_nodes[index] = a;
        // update their father
        while(index > 0){
            index = (index - 1) / 2;
            tree_nodes[index] = tree_nodes[index * 2 + 1] + tree_nodes[index * 2 + 2];
        }
    }

    // query [a, b] in the index-th node with interval [l, r]
    // first query from outside should be (a, b, 0, 0, n - 1)
    int query(int a, int b, int index, int l, int r){
        if(r < a || b < l){return 0;}
        if(a <= l && b >= r){return tree_nodes[index];}
        else{
            int s1 = query(a, b, index * 2 + 1, l, (l + r) / 2);
            int s2 = query(a, b, index * 2 + 2, 1 + (l + r) / 2, r);

            return s1 + s2;
        }
    }

    int size(){
        return n;
    }
};

class NumArray {
    Segment_Tree *st;
public:
    NumArray(vector<int>& nums) {
        int ns = nums.size();
        st = new Segment_Tree(ns);

        for(int i = 0;i < ns;++i){
            st->update(i, nums[i]);
        }
    }
    
    void update(int index, int val) {
        st->update(index, val);
    }
    
    int sumRange(int left, int right) {
        return st->query(left, right, 0, 0, st->size() - 1);
    }
};