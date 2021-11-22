#include<vector>
#include<numeric>
#include<algorithm>
#include<iostream>
using namespace std;

/*
25 Reverse Nodes in k-Group

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may be changed.

 

Example 1:


Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]
Example 2:


Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]
Example 3:

Input: head = [1,2,3,4,5], k = 1
Output: [1,2,3,4,5]
Example 4:

Input: head = [1], k = 1
Output: [1]
 

Constraints:

The number of nodes in the list is in the range sz.
1 <= sz <= 5000
0 <= Node.val <= 1000
1 <= k <= sz
 

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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *newhead = nullptr, *start = head, *end = head, *previous;
        int cur_g = 0;
        while(start != nullptr){
            if(cur_g == k){
                ListNode *cur_head = reverseAll(start, end);
                if(newhead == nullptr){
                    newhead = cur_head;
                    previous = start;
                }
                else{
                    previous->next = cur_head;
                    previous = start;
                }
                start = end;
                cur_g = 0;
            }
            else if(end != nullptr){
                end = end->next;
                cur_g += 1;
            }
            else{
                break;
            }

        }

        return newhead;

    }
    // reverse [head, tail)
    ListNode* reverseAll(ListNode* head, ListNode* tail){
        ListNode *pre = tail, *cur = head, *nxt = head->next;
        while(true){
            cur->next = pre;
            if(nxt == tail){
                break;
            }
            pre = cur;
            cur = nxt;
            nxt = cur->next;
        }
        // printValue(cur);

        return cur;
    }

    void printValue(ListNode* head){
        while(head != nullptr){
            cout << head->val << " ";
            head = head->next;
        }
        cout << endl;
    }
};