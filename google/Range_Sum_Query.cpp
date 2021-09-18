#include<vector>
#include<map>
#include<algorithm>
#include<memory.h>
using namespace std;

/*
307

Range Sum Query - Mutable

Given an integer array nums, handle multiple queries of the following types:

Update the value of an element in nums.
Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.
Implement the NumArray class:

NumArray(int[] nums) Initializes the object with the integer array nums.
void update(int index, int val) Updates the value of nums[index] to be val.
int sumRange(int left, int right) Returns the sum of the elements of nums between indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).
 

Example 1:

Input
["NumArray", "sumRange", "update", "sumRange"]
[[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
Output
[null, 9, null, 8]

Explanation
NumArray numArray = new NumArray([1, 3, 5]);
numArray.sumRange(0, 2); // return 1 + 3 + 5 = 9
numArray.update(1, 2);   // nums = [1, 2, 5]
numArray.sumRange(0, 2); // return 1 + 2 + 5 = 8
 

Constraints:

1 <= nums.length <= 3 * 10^4
-100 <= nums[i] <= 100
0 <= index < nums.length
-100 <= val <= 100
0 <= left <= right < nums.length
At most 3 * 10^4 calls will be made to update and sumRange.

基本思想

线段树基本例题

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