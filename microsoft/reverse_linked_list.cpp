struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
206
Given the head of a singly linked list, reverse the list, and return the reversed list.

 

Example 1:


Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]
Example 2:


Input: head = [1,2]
Output: [2,1]
Example 3:

Input: head = []
Output: []
 

Constraints:

The number of nodes in the list is the range [0, 5000].
-5000 <= Node.val <= 5000
 

Follow up: A linked list can be reversed either iteratively or recursively. Could you implement both?

基本思想
维持三个指针pre cur nxt滚动，调整链表方向
*/

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr){return head;}
        ListNode *pre = nullptr, *cur = head, *nxt = head->next;
        while(true){
            cur->next = pre;
            if(nxt == nullptr){
                break;
            }
            pre = cur;
            cur = nxt;
            nxt = cur->next;
        }
        return cur;
    }
};