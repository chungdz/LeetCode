'''
986 Interval List Intersections
You are given two lists of closed intervals, firstList and secondList, where firstList[i] = [starti, endi] and secondList[j] = [startj, endj]. Each list of intervals is pairwise disjoint and in sorted order.

Return the intersection of these two interval lists.

A closed interval [a, b] (with a <= b) denotes the set of real numbers x with a <= x <= b.

The intersection of two closed intervals is a set of real numbers that are either empty or represented as a closed interval. For example, the intersection of [1, 3] and [2, 4] is [2, 3].

 

Example 1:


Input: firstList = [[0,2],[5,10],[13,23],[24,25]], secondList = [[1,5],[8,12],[15,24],[25,26]]
Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
Example 2:

Input: firstList = [[1,3],[5,9]], secondList = []
Output: []
Example 3:

Input: firstList = [], secondList = [[4,8],[10,12]]
Output: []
Example 4:

Input: firstList = [[1,7]], secondList = [[3,10]]
Output: [[3,7]]
 

Constraints:

0 <= firstList.length, secondList.length <= 1000
firstList.length + secondList.length >= 1
0 <= starti < endi <= 10^9
endi < starti+1
0 <= startj < endj <= 10^9
endj < startj+1

基本思想

每次删除两个头中右端点小的那一个，因为它只可能和一个interval有交集
'''

class Solution:
    def intervalIntersection(self, firstList: List[List[int]], secondList: List[List[int]]) -> List[List[int]]:
        self.res = []
        while len(firstList) > 0 and len(secondList) > 0:
            if firstList[0][1] < secondList[0][1]:
                self.check_and_delete(firstList, secondList)
            elif firstList[0][1] > secondList[0][1]:
                self.check_and_delete(secondList, firstList)
            else:
                if firstList[0][0] > secondList[0][0]:
                    self.res.append(firstList[0])
                else:
                    self.res.append(secondList[0])
                firstList.pop(0)
                secondList.pop(0)

        return self.res
    
    def check_and_delete(self, l1, l2):
        if l1[0][1] >= l2[0][0]:
            self.res.append([max(l2[0][0], l1[0][0]), l1[0][1]])
        l1.pop(0)