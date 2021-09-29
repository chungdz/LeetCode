#include<vector>
#include<algorithm>
using namespace std;

/*
143
Reorder List

Solution
You are given the head of a singly linked-list. The list can be represented as:

L0 → L1 → … → Ln - 1 → Ln
Reorder the list to be on the following form:

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
You may not modify the values in the list's nodes. Only nodes themselves may be changed.

 

Example 1:


Input: head = [1,2,3,4]
Output: [1,4,2,3]
Example 2:


Input: head = [1,2,3,4,5]
Output: [1,5,2,4,3]
 

Constraints:

The number of nodes in the list is in the range [1, 5 * 10^4].
1 <= Node.val <= 1000

基本思想

用vector把每个list的指针记录下来，方便回溯和前进
**/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode* s = head, *e = head;
        vector<ListNode*> rec;
        while(e != nullptr){
            rec.push_back(e);
            e = e->next;
        }
        int rs = rec.size();
        e = rec[rs - 1];

        int eindex = rs - 1;
        int sindex = 0;
        while(true){
            if(s == e || s->next == e){break;}
            ListNode *pre_e = rec[eindex - 1];
            ListNode *nxt_s = rec[sindex + 1];

            pre_e->next = nullptr;
            s->next = e;
            e->next = nxt_s;

            eindex -= 1;
            sindex += 1;

            e = rec[eindex];
            s = rec[sindex];
        }
    }
};