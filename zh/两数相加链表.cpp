/*

445
两数相加
给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <string>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int nxt_plus = 0;
        ListNode *result = new ListNode(-1);
        ListNode *p1 = l1, *p2 = l2, *my_point = result;
        while(p1 && p2){
            int cur_num = nxt_plus + p1->val + p2->val;
            nxt_plus = cur_num / 10;
            my_point->next = new ListNode(cur_num % 10);

            p1 = p1->next;
            p2 = p2->next;
            my_point = my_point->next;
        }
        ListNode *remain = p1 ? p1 : p2;

        while(remain){
            int cur_num = nxt_plus + remain->val;
            nxt_plus = cur_num / 10;
            my_point->next = new ListNode(cur_num % 10);
            remain = remain->next;
            my_point = my_point->next;
        }

        while(nxt_plus != 0){
            int cur_num = nxt_plus;
            nxt_plus = cur_num / 10;
            my_point->next = new ListNode(cur_num % 10);
            my_point = my_point->next;
        }

        return result->next;
    }
};