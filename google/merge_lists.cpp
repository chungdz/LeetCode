#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

/**
 * 23 

You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

 

Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6
Example 2:

Input: lists = []
Output: []
Example 3:

Input: lists = [[]]
Output: []
 

Constraints:

k == lists.length
0 <= k <= 10^4
0 <= lists[i].length <= 500
-10^4 <= lists[i][j] <= 10^4
lists[i] is sorted in ascending order.
The sum of lists[i].length won't exceed 10^4.
 * 
 * 
 * 
 * 
 * 基本思路：
 * 
 * merge sort的双指针法
 * 
 * 存储还可以优化，现在是新建了一个链表，其实可以在原有的链表上操作
 * 
 * 
 * 
 * 
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

void print_LN(ListNode* p){
    cout << "list: ";
    while(p != nullptr){
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}

class Solution {
    ListNode* merge_two(ListNode* l1, ListNode* l2){
        if(l1 == nullptr){
            if(l2 == nullptr){
                return nullptr;
            }
            return l2;
        }
        else if(l2 == nullptr){return l1;}

        ListNode *p1 = l1, *p2 = l2, *p3, *header;
        // determine header value
        if(p1->val <= p2->val){
            header = new ListNode(p1->val);
            p1 = p1->next;
        }
        else{
            header = new ListNode(p2->val);
            p2 = p2->next;
        }

        p3 = header;
        while(p1 != nullptr && p2 != nullptr){
            if(p1->val <= p2->val){
                p3->next = new ListNode(p1->val);
                p1 = p1->next;
            }
            else{
                p3->next = new ListNode(p2->val);
                p2 = p2->next;
            }
            p3 = p3->next;
        }

        // check p1 or p2 remaining number
        while(p1 != nullptr){
            p3->next = new ListNode(p1->val);
            p1 = p1->next;
            p3 = p3->next;
        }

        while(p2 != nullptr){
            p3->next = new ListNode(p2->val);
            p2 = p2->next;
            p3 = p3->next;
        }
        
        return header;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int cur_size = lists.size();
        if(cur_size == 0){return nullptr;}

        vector<ListNode*> *cur_list = &lists;
        vector<ListNode*> *new_list = new vector<ListNode*>();
        while(cur_size > 1){
            for(int i = 0;i < cur_size;i += 2){
                if(i != cur_size - 1){
                    ListNode* merged = merge_two((*cur_list)[i], (*cur_list)[i + 1]);
                    new_list->push_back(merged);
                }
                else{
                    new_list->push_back((*cur_list)[i]);
                }
            }
            swap(new_list, cur_list);
            cur_size = cur_list->size();
            new_list->clear();
        }
        return (*cur_list)[0];
    }
};