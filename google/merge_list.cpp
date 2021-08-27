/**
 * 21
 * 
 * 
Merge two sorted linked lists and return it as a sorted list. The list should be made by splicing together the nodes of the first two lists.

 

Example 1:


Input: l1 = [1,2,4], l2 = [1,3,4]
Output: [1,1,2,3,4,4]
Example 2:

Input: l1 = [], l2 = []
Output: []
Example 3:

Input: l1 = [], l2 = [0]
Output: [0]
 

Constraints:

The number of nodes in both lists is in the range [0, 50].
-100 <= Node.val <= 100
Both l1 and l2 are sorted in non-decreasing order.
 * 
 * 
 * 
 * 
 * 
 * 基本思想
 * 
 * 把首数小的当成主链，另一个当成被合并的链
 * 
 * 每次都保证主链mainp指针指向的数小于被合并的链指针side指向的数
 * 
 * 移动主链指针直到mianp的下一个位置的数大于side的数，插入side
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == nullptr){
            if(l2 == nullptr){
                return nullptr;
            }
            return l2;
        }
        else if(l2 == nullptr){
            return l1;
        }

        ListNode *mainp, *head, *side;
        if(l1->val <= l2->val){
            head = l1;
            mainp = l1;
            side = l2;
        }
        else{
            head = l2;
            mainp = l2;
            side = l1;
        }

        while(true){

            if(mainp->next == nullptr){
                mainp->next = side;
                break;
            }

            while(side->val > mainp->next->val){
                mainp = mainp->next;
                if(mainp->next == nullptr){break;}
            }

            if(mainp->next == nullptr){
                mainp->next = side;
                break;
            }

            ListNode *cur = side, *nxt = mainp->next;
            side = side->next;
            mainp->next = cur;
            cur->next = nxt;
            mainp = cur;

            if(side == nullptr){break;}
        }

        return head;
    }
};