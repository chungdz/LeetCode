#include<vector>
#include<algorithm>
using namespace std;

/*
341 Flatten Nested List Iterator

You are given a nested list of integers nestedList. Each element is either an integer or a list whose elements may also be integers or other lists. Implement an iterator to flatten it.

Implement the NestedIterator class:

NestedIterator(List<NestedInteger> nestedList) Initializes the iterator with the nested list nestedList.
int next() Returns the next integer in the nested list.
boolean hasNext() Returns true if there are still some integers in the nested list and false otherwise.
Your code will be tested with the following pseudocode:

initialize iterator with nestedList
res = []
while iterator.hasNext()
    append iterator.next() to the end of res
return res
If res matches the expected flattened list, then your code will be judged as correct.

 

Example 1:

Input: nestedList = [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].
Example 2:

Input: nestedList = [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].
 

Constraints:

1 <= nestedList.length <= 500
The values of the integers in the nested list is in the range [-106, 106]

基本思想

存储vector迭代器和vector指针
在has next中做完所有判断，包括是否到尾部，是否需要添加新的元素，直到找到第一个integer

*/

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
*/

class NestedInteger {
public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class NestedIterator {
    vector<vector<NestedInteger>::iterator> listp;
    vector<vector<NestedInteger>*> lists;
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        listp.push_back(nestedList.begin());
        lists.push_back(&nestedList);
    }
    
    int next() {
        int res = listp.back()->getInteger();
        listp.back()++;
        return res;
    }
    
    bool hasNext() {
        vector<NestedInteger>::iterator it = listp.back();
        vector<NestedInteger> *cur_list = lists.back();
        while(true){
            if(it == cur_list->end()){
                listp.pop_back();
                lists.pop_back();
                if(listp.size() > 0){
                    it = listp.back();
                    cur_list = lists.back();
                }
                else
                    return false;
            }
            else if(!it->isInteger()){
                cur_list = &(it->getList());
                listp.back()++;
                listp.push_back(cur_list->begin());
                lists.push_back(cur_list);
                it = listp.back();
            }
            else
                break;
        }
        
        return true;
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */