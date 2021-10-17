#include<algorithm>
#include<unordered_set>
using namespace std;

/*
141 Linked List Cycle

Given head, the head of a linked list, determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

Return true if there is a cycle in the linked list. Otherwise, return false.

 

Example 1:


Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
Example 2:


Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.
Example 3:


Input: head = [1], pos = -1
Output: false
Explanation: There is no cycle in the linked list.
 

Constraints:

The number of the nodes in the list is in the range [0, 104].
-10^5 <= Node.val <= 10^5
pos is -1 or a valid index in the linked-list.
 

Follow up: Can you solve it using O(1) (i.e. constant) memory?

基本思想

set保存位置
如果想用O(1)空间，那就要修改val为范围外的值做标记，或者是快慢指针，如果存在圈，快慢指针总会相遇
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *cur = head;
        unordered_set<ListNode*> record;
        while(cur != nullptr){
            if(!record.insert(cur).second)
                return true;
            cur = cur->next;
        }
        return false;
    }
};