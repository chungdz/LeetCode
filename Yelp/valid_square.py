'''
593 Valid Square

Given the coordinates of four points in 2D space p1, p2, p3 and p4, return true if the four points construct a square.

The coordinate of a point pi is represented as [xi, yi]. The input is not given in any order.

A valid square has four equal sides with positive length and four equal angles (90-degree angles).

 

Example 1:

Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
Output: true
Example 2:

Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,12]
Output: false
Example 3:

Input: p1 = [1,0], p2 = [-1,0], p3 = [0,1], p4 = [0,-1]
Output: true
 

Constraints:

p1.length == p2.length == p3.length == p4.length == 2
-10^4 <= xi, yi <= 10^4

基本思想

使用普适的原则：四点距离相等，夹角90度
可以用向量计算的知识判断
'''

class Solution:
    def validSquare(self, p1: List[int], p2: List[int], p3: List[int], p4: List[int]) -> bool:
        plist = sorted([p1, p2, p3, p4], key=lambda x: (x[0], x[1]))
        return self.isGeneralizedType(plist)
    
    @staticmethod
    def isGeneralizedType(plist):

        d1 = Solution.distanceSquare(plist[0], plist[1])
        d2 = Solution.distanceSquare(plist[0], plist[2])
        d3 = Solution.distanceSquare(plist[-1], plist[1])
        d4 = Solution.distanceSquare(plist[-1], plist[2])
        if d1 <= 0:
            return False
        if d1 != d2:
            return False
        if d3 != d4:
            return False
        if d1 != d3:
            return False
        
        v1 = Solution.vector2P(plist[0], plist[1])
        v2 = Solution.vector2P(plist[0], plist[2])
        v3 = Solution.vector2P(plist[-1], plist[1])
        v4 = Solution.vector2P(plist[-1], plist[2])

        if not Solution.isVertical(v1, v2):
            return False
        if not Solution.isVertical(v1, v3):
            return False
        if not Solution.isVertical(v2, v4):
            return False
        if not Solution.isVertical(v3, v4):
            return False
        
        return True
    
    @staticmethod
    def distanceSquare(p1, p2):
        return (p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2
    
    @staticmethod
    def vector2P(p1, p2):
        return [p2[0]- p1[0], p2[1] - p1[1]]
    
    @staticmethod
    def isVertical(v1, v2):
        inner_product = v1[0] * v2[0] + v1[1] * v2[1]
        return inner_product == 0