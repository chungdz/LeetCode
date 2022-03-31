#include<algorithm>
#include<iostream>
using namespace std;

/*
234 Palindrome Linked List

Given the head of a singly linked list, return true if it is a palindrome.

 

Example 1:


Input: head = [1,2,2,1]
Output: true
Example 2:


Input: head = [1,2]
Output: false
 

Constraints:

The number of nodes in the list is in the range [1, 10^5].
0 <= Node.val <= 9
 

Follow up: Could you do it in O(n) time and O(1) space?

基本思想

reverse后半部分
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
    bool isPalindrome(ListNode* head) {
        int whole_cnt = 0;
        ListNode *curn = head;
        while(curn != nullptr){
            whole_cnt += 1;
            curn = curn->next;
        }
        int halfe = (whole_cnt - 1) / 2;
        int idx = 0;
        curn = head;
        while(idx < halfe){
            idx += 1;
            curn = curn->next;
        }
        ListNode *mid = curn;
        mid->next = reverseList(mid->next);

        curn = head;
        ListNode *secn = mid->next;
        while(secn != nullptr){
            if(curn->val != secn->val)
                return false;
            curn = curn->next;
            secn = secn->next;
        }
        return true;
    }

    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
    }

    void print_list(ListNode *head){
        ListNode* it = head;
        while(it != nullptr){
            cout << it->val << ' ';
            it = it->next;
        }
        cout << endl;
        return;
    }
};