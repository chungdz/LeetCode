/**
 * 19
 * 
 * 
Given the head of a linked list, remove the nth node from the end of the list and return its head.

 

Example 1:


Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
Example 2:

Input: head = [1], n = 1
Output: []
Example 3:

Input: head = [1,2], n = 1
Output: [1]
 

Constraints:

The number of nodes in the list is sz.
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz
 * 
 * 
 * 链表日常
 * 
 * 
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *cur = head, *pre = nullptr;
        int lsize = 0;
        while(cur != nullptr){
            lsize += 1;
            cur = cur->next;
        }

        int del_p = lsize - n;
        cur = head;
        while(del_p--){
            pre = cur;
            cur = cur->next;
        }
        // del_p = 0
        if(pre == nullptr){
            return cur->next;
        }
        else{
            pre->next = cur->next;
            return head;
        }
    }
};