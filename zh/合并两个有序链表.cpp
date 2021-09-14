/*

21

合并两个有序链表
将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

示例：

输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4
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
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/*
考的是算法层面的东西

双指针移动，右边小于等于左边就先右边

如果一方已经走到头了，就直接复制另一方的全部到当前指针

结果给个head指针和当前指针
*/

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *head = new ListNode(-1);
        ListNode *p1 = l1, *p2 = l2, *p = head;
        while(p1 != NULL && p2 != NULL){
            if(p1->val <= p2->val){
                p->next = p1;
                p1 = p1->next;
                p = p->next;
            }
            else{
                p->next = p2;
                p2 = p2->next;
                p = p->next;
            }
        }

        if(p1 != NULL){
            p->next = p1;
        }
        else if(p2 != NULL){
            p->next = p2;
        }
        else{
            p->next = NULL;
        }

        return head->next;
    }
};