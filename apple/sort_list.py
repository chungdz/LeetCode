# Definition for singly-linked list.
import numpy as np
from sortedcontainers import SortedList

'''
148 Sort List

Given the head of a linked list, return the list after sorting it in ascending order.

 

Example 1:


Input: head = [4,2,1,3]
Output: [1,2,3,4]
Example 2:


Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]
Example 3:

Input: head = []
Output: []
 

Constraints:

The number of nodes in the list is in the range [0, 5 * 104].
-105 <= Node.val <= 105
 

Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?
'''

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
# TLE
class Solution1:
    def sortList(self, head: ListNode) -> ListNode:
        if head is None:
            return None
        if head.next is None:
            return head
        
        cur_mid = head
        smaller = ListNode()
        sp = smaller
        larger = ListNode()
        lp = larger
        
        tmp = head.next
        isEqual = True
        while not tmp is None:
            if tmp.val <= cur_mid.val:
                sp.next = tmp
                sp = sp.next
            else:
                lp.next = tmp
                lp = lp.next
            
            if tmp.val != cur_mid.val:
                isEqual = False
            tmp = tmp.next
        
        sp.next = None
        lp.next = None

        if isEqual:
            cur_mid.next = smaller.next
            return cur_mid

        sorted_smaller = self.sortList(smaller.next)
        sorted_larger = self.sortList(larger.next)

        if not sorted_smaller is None:
            sp = sorted_smaller
            while not sp.next is None:
                sp = sp.next
            sp.next = cur_mid
            cur_mid.next = sorted_larger
            return sorted_smaller
        else:
            cur_mid.next = sorted_larger
            return cur_mid

# merge sort acc
class Solution:
    def sortList(self, head: ListNode) -> ListNode:
        if head is None:
            return None
        if head.next is None:
            return head
        
        fp = head
        sp = ListNode(next=head)
        while not fp is None:
            sp = sp.next
            fp = fp.next
            if not fp is None:
                fp = fp.next
        
        sright = self.sortList(sp.next)
        sp.next = None
        sleft = self.sortList(head)

        return self.merge_list(sleft, sright)

    def merge_list(self, sleft, sright):

        nh = ListNode()
        curp = nh
        lp = sleft
        rp = sright

        while not lp is None or not rp is None:

            if lp is None:
                curp.next = rp
                rp = rp.next
                curp = curp.next
            elif rp is None:
                curp.next = lp
                lp = lp.next
                curp = curp.next
            elif lp.val <= rp.val:
                curp.next = lp
                lp = lp.next
                curp = curp.next
            else:
                curp.next = rp
                rp = rp.next
                curp = curp.next

        curp.next = None
        return nh.next

        

