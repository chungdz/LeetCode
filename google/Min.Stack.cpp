#include <stack>
#include <list>
using namespace std;

/*

155

Min Stack

Solution
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the MinStack class:

MinStack() initializes the stack object.
void push(val) pushes the element val onto the stack.
void pop() removes the element on the top of the stack.
int top() gets the top element of the stack.
int getMin() retrieves the minimum element in the stack.
 

Example 1:

Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
 

Constraints:

-231 <= val <= 231 - 1
Methods pop, top and getMin operations will always be called on non-empty stacks.
At most 3 * 104 calls will be made to push, pop, top, and getMin.


基本思想

包装stack和list，list用作储存值和排序，stack用作储存stack位置

**/

class MinStack {
    list<int> values;
    stack<list<int>::iterator> pos;
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int val) {
        if(values.empty()){
            pos.push(values.insert(values.begin(), val));
        }
        else{
            bool isadded = false;
            for(auto it = values.begin();it != values.end();++it){
                if(val < *it){
                    pos.push(values.insert(it, val));
                    isadded = true;
                    break;
                }
            }
            if(!isadded){
                pos.push(values.insert(values.end(), val));
            }
        }
    }
    
    void pop() {
        list<int>::iterator top_it = pos.top();
        pos.pop();
        values.erase(top_it);
    }
    
    int top() {
        return *pos.top();
    }
    
    int getMin() {
        return *values.begin();
    }
};