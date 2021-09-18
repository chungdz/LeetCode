#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
380

Insert Delete GetRandom O(1)

Solution
Implement the RandomizedSet class:

RandomizedSet() Initializes the RandomizedSet object.
bool insert(int val) Inserts an item val into the set if not present. Returns true if the item was not present, false otherwise.
bool remove(int val) Removes an item val from the set if present. Returns true if the item was present, false otherwise.
int getRandom() Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the same probability of being returned.
You must implement the functions of the class such that each function works in average O(1) time complexity.

 

Example 1:

Input
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
Output
[null, true, false, true, 2, true, false, 2]

Explanation
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
randomizedSet.insert(2); // 2 was already in the set, so return false.
randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.
 

Constraints:

-2^31 <= val <= 2^31 - 1
At most 2 * 105 calls will be made to insert, remove, and getRandom.
There will be at least one element in the data structure when getRandom is called.

基本思想

map 保证 查询insert 和remove为常数时间
vector 保证随机访问为常数时间

问题在于remove的时候vector会导致指针位置错位

方法是把remove的元素和最后一个调换，更新对应的map和vector值

**/

class RandomizedSet {
    unordered_map<int, int> vector_pos;
    vector<int> values;
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(vector_pos.find(val) != vector_pos.end()){
            return false;
        }
        values.push_back(val);
        vector_pos[val] = values.size() - 1;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(vector_pos.find(val) == vector_pos.end()){
            return false;
        }
        int back_val = values.back();
        // elem from back cover the removed value
        values[vector_pos[val]] = back_val;
        vector_pos[back_val] = vector_pos[val];

        values.pop_back();
        vector_pos.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int cap = values.size();
        if(cap == 0){return -1;}
        int index = (rand() % cap);
        return values[index];
    }
};

