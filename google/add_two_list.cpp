#include<vector>
#include<math.h>
#include<algorithm>
using namespace std;

/**
 * 2
 * 
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

 

Example 1:


Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.
Example 2:

Input: l1 = [0], l2 = [0]
Output: [0]
Example 3:

Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
 

Constraints:

The number of nodes in each linked list is in the range [1, 100].
0 <= Node.val <= 9
It is guaranteed that the list represents a number that does not have leading zeros.
 * 
 * 基本思想
 * 
 * 链表上的加法
 * 
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
/**
 * 
 * 
 * 
 * right order
 * 
 * 
 * 
 * 
 * 
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        vector<int> v1, v2;
        while(l1 != nullptr){
            v1.push_back(l1->val);
            l1 = l1->next;
        }
        while(l2 != nullptr){
            v2.push_back(l2->val);
            l2 = l2->next;
        }
        int s1 = v1.size();
        int s2 = v2.size();
        vector<int> *longv, *shortv;
        int ps, pl;
        if(s1 <= s2){
            shortv = &v1;
            ps = s1 - 1;
            longv = &v2;
            pl = s2 - 1;
        }
        else{
            shortv = &v2;
            ps = s2 - 1;
            longv = &v1;
            pl = s1 - 1;
        }

        int add_one = 0;
        ListNode *res = nullptr, *nxt = nullptr;
        while(pl >= 0){
            int n1 = (*longv)[pl];
            int n2;
            if(ps >= 0){n2 = (*shortv)[ps];}
            else{n2 = 0;}

            int n3 = n1 + n2 + add_one;
            if(n1 + n2 > 9){
                add_one = 1;
                n3 = n3 - 10;
            }
            else{
                add_one = 0;
            }

            res = new ListNode(n3, nxt);
            nxt = res;
            res = nullptr;

            --pl;
            --ps;
        }

        if(add_one == 1){
            res = new ListNode(1, nxt);
            nxt = res;
            res = nullptr;
        }
        return nxt;
    }
};

/**
 * @brief 
 * 
 * reverse order
 * 
 * 
 * 
 * 
 * 
 * 
 */

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        int add_one = 0;
        ListNode *head = new ListNode(0);
        ListNode *p = head;

        while(l1 != nullptr || l2 != nullptr){

            int n1, n2;
            if(l1 != nullptr){
                n1 = l1->val;
                l1 = l1->next;
            }
            else{n1 = 0;}

            if(l2 != nullptr){
                n2 = l2->val;
                l2 = l2->next;
            }
            else{n2 = 0;}

            int n3 = n1 + n2 + add_one;
            if(n3 > 9){
                add_one = 1;
                n3 = n3 - 10;
            }
            else{
                add_one = 0;
            }

            p->next = new ListNode(n3);
            p = p->next;
        }

        if(add_one == 1){
            p->next = new ListNode(1);
            p = p->next;
        }
        return head->next;
    }
};