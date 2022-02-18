import itertools

'''
679 24 Game

You are given an integer array cards of length 4. You have four cards, each containing a number in the range [1, 9]. You should arrange the numbers on these cards in a mathematical expression using the operators ['+', '-', '*', '/'] and the parentheses '(' and ')' to get the value 24.

You are restricted with the following rules:

The division operator '/' represents real division, not integer division.
For example, 4 / (1 - 2 / 3) = 4 / (1 / 3) = 12.
Every operation done is between two numbers. In particular, we cannot use '-' as a unary operator.
For example, if cards = [1, 1, 1, 1], the expression "-1 - 1 - 1 - 1" is not allowed.
You cannot concatenate numbers together
For example, if cards = [1, 2, 1, 2], the expression "12 + 12" is not valid.
Return true if you can get such expression that evaluates to 24, and false otherwise.

 

Example 1:

Input: cards = [4,1,8,7]
Output: true
Explanation: (8-4) * (7-1) = 24
Example 2:

Input: cards = [1,2,1,2]
Output: false
 

Constraints:

cards.length == 4
1 <= cards[i] <= 9

基本思想：
递归+暴力搜索

有两个东西需要搜索，一个是数字顺序，用全排列去for循环搜索，一个是符号搜索，3个符号每个符号4种一共4^3种空间，并且要考虑括号，
所以有6种组合运算方式

主要最后一个测试用例8 8 3 3需要用小数近似整数，所以判断不能直接用==，要用阈值判断
'''

class Solution:
    def judgePoint24(self, cards: List[int]) -> bool:
        
        self.ops = ['+', '-', '*', '/']
        self.res = False
        
        norder = itertools.permutations(cards)
        for no in norder:
            self.c = no
            self.iter_op([], 3)
        
        return self.res
    
    def iter_op(self, clist, left):
        if left == 0:
            self.iter_order(clist)
            return
        
        for op in self.ops:
            clist.append(op)
            self.iter_op(clist, left - 1)
            clist.pop()
        
        return
    
    def cal(self, n1, n2, op):
        if op == '+':
            return n1 + n2
        elif op == '-':
            return n1 - n2
        elif op == '*':
            return n1 * n2
        elif op == '/' and n2 != 0:
            return n1 / n2
        
        return None

    def iter_order(self, clist):
        
        nlist = []
        nlist.append(self.cal(self.c[0], self.c[1], clist[0]))
        nlist += self.c[2:]
        self.cal_all(clist[1:], nlist)

        nlist = []
        nlist.append(self.c[0])
        nlist.append(self.cal(self.c[1], self.c[2], clist[1]))
        nlist.append(self.c[3])
        self.cal_all([clist[0], clist[2]], nlist)

        nlist = []
        nlist += self.c[:2]
        nlist.append(self.cal(self.c[2], self.c[3], clist[2]))
        self.cal_all(clist[:2], nlist)
    
    def cal_all(self, clist, nlist):
        tmp1 = self.cal(nlist[0], nlist[1], clist[0])
        if not tmp1 is None: 
            r1 = self.cal(tmp1, nlist[2], clist[1])
        else:
            r1 = None

        tmp2 = self.cal(nlist[1], nlist[2], clist[1])
        if not tmp2 is None:
            r2 = self.cal(nlist[0], tmp2, clist[0])
        else:
            r2 = None
        if self.is24(r1) or self.is24(r2):
            self.res = True
        return 
    
    def is24(self, n):
        if n is None:
            return False
        epsilon = 1e-7
        return abs(n - 24) < epsilon
