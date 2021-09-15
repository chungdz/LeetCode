/*
剑指offer II 021

删除链表的倒数第N个节点
给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。

示例：

给定一个链表: 1->2->3->4->5, 和 n = 2.

当删除了倒数第二个节点后，链表变为 1->2->3->5.
说明：

给定的 n 保证是有效的。

进阶：

你能尝试使用一趟扫描实现吗？
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

/*
解法一：扫描两遍，第一遍记录长度，第二遍删除
解法二：扫描一遍，记下每一个指针的位置，然后直接删除
解法三：双指针，指针间隔n移动
*/

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        
    }
};