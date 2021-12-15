#include<algorithm>
#include<vector>
#include<queue>
#include<unordered_map>
#include<stack>
using namespace std;

/*
895 Design a stack-like data structure to push elements to the stack and pop the most frequent element from the stack.

Implement the FreqStack class:

FreqStack() constructs an empty frequency stack.
void push(int val) pushes an integer val onto the top of the stack.
int pop() removes and returns the most frequent element in the stack.
If there is a tie for the most frequent element, the element closest to the stack's top is removed and returned.
 

Example 1:

Input
["FreqStack", "push", "push", "push", "push", "push", "push", "pop", "pop", "pop", "pop"]
[[], [5], [7], [5], [7], [4], [5], [], [], [], []]
Output
[null, null, null, null, null, null, null, 5, 7, 5, 4]

Explanation
FreqStack freqStack = new FreqStack();
freqStack.push(5); // The stack is [5]
freqStack.push(7); // The stack is [5,7]
freqStack.push(5); // The stack is [5,7,5]
freqStack.push(7); // The stack is [5,7,5,7]
freqStack.push(4); // The stack is [5,7,5,7,4]
freqStack.push(5); // The stack is [5,7,5,7,4,5]
freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes [5,7,5,7,4].
freqStack.pop();   // return 7, as 5 and 7 is the most frequent, but 7 is closest to the top. The stack becomes [5,7,5,4].
freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes [5,7,4].
freqStack.pop();   // return 4, as 4, 5 and 7 is the most frequent, but 4 is closest to the top. The stack becomes [5,7].
 

Constraints:

0 <= val <= 109
At most 2 * 104 calls will be made to push and pop.
It is guaranteed that there will be at least one element in the stack before calling pop.

基本思想：
优先队列，先频数再时间戳，push时间是O(nlogn)，pop时间是O(nlogn)
2
多优先级栈，每个优先级用频数表示，push和pop都是O(1)的时间
*/

class FStackNode {
public:
    int val;
    int frequency;
    int timestamp;

    FStackNode(int v, int f, int t){
        val = v;
        frequency = f;
        timestamp = t;
    }
};

class Cmp{
public:
    bool operator() (const FStackNode &v1, const FStackNode &v2){
        if(v1.frequency == v2.frequency)
            return v1.timestamp < v2.timestamp;
        else
            return v1.frequency < v2.frequency;
    }
};

class FreqStack1 {
    unordered_map<int, int> frequency;
    int timestamp = 0;
    priority_queue<FStackNode, vector<FStackNode>, Cmp> pq;
public:
    void push(int val) {
        if(frequency.find(val) == frequency.end())
            frequency[val] = 1;
        else
            frequency[val] += 1;

        pq.push(FStackNode(val, frequency[val], timestamp));

        timestamp += 1;
    }
    
    int pop() {
        FStackNode cn = pq.top();
        pq.pop();
        frequency[cn.val] -= 1;
        return cn.val;
    }
};

class FreqStack {
    unordered_map<int, int> frequency;
    unordered_map<int, stack<int>> pstack;
    int maxfreq = 0;
public:
    void push(int val) {
        if(frequency.find(val) == frequency.end())
            frequency[val] = 1;
        else
            frequency[val] += 1;

        if(frequency[val] > maxfreq)
            maxfreq = frequency[val];
        if(pstack.find(frequency[val]) == pstack.end())
            pstack[frequency[val]] = stack<int>();
        pstack[frequency[val]].push(val);
    }
    
    int pop() {
        int res = pstack[maxfreq].top();
        pstack[maxfreq].pop();
        if(pstack[maxfreq].empty())
            maxfreq -= 1;
        frequency[res] -= 1;
        return res;
    }
};