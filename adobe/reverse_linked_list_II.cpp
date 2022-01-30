#include<vector>
#include<algorithm>
using namespace std;

/*
92 Reverse Linked List

Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.

 

Example 1:


Input: head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]
Example 2:

Input: head = [5], left = 1, right = 1
Output: [5]
 

Constraints:

The number of nodes in the list is n.
1 <= n <= 500
-500 <= Node.val <= 500
1 <= left <= right <= n
 
基本思想

用vector记录
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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        vector<int> vals;
        ListNode *cur = head, *s;
        int cnt = 1;
        while(cur != nullptr){
            vals.push_back(cur->val);
            if(cnt == left){
                s = cur;
            }
            cur = cur->next;
            cnt += 1;
        }

        int ridx = right - 1;
        for(int i = ridx;i >= left - 1;--i){
            s->val = vals[i];
            s = s->next;
        }

        return head;
    }
};