'''
640 Solve the Equation

Solve a given equation and return the value of 'x' in the form of a string "x=#value". The equation contains only '+', '-' operation, the variable 'x' and its coefficient. You should return "No solution" if there is no solution for the equation, or "Infinite solutions" if there are infinite solutions for the equation.

If there is exactly one solution for the equation, we ensure that the value of 'x' is an integer.

 

Example 1:

Input: equation = "x+5-3+x=6+x-2"
Output: "x=2"
Example 2:

Input: equation = "x=x"
Output: "Infinite solutions"
Example 3:

Input: equation = "2x=x"
Output: "x=0"
 

Constraints:

3 <= equation.length <= 1000
equation has exactly one '='.
equation consists of integers with an absolute value in the range [0, 100] without any leading zeros, and the variable 'x'.

基本思想

字符串处理
把属于x的左边，不属于x的放右边
需要处理特殊情况
'''

class Solution:
    def solveEquation(self, equation: str) -> str:
        left_s, right_s = equation.split('=')
        if left_s[0] != '-':
            left_s = '+' + left_s
        if right_s[0] != '-':
            right_s = '+' + right_s
        
        lx, ln = self.parse_side(left_s)
        rx, rn = self.parse_side(right_s)

        xall = lx - rx
        nall = rn - ln

        if xall == 0 and nall == 0:
            return "Infinite solutions"
        elif xall == 0 and nall != 0:
            return "No solution"
        else:
            return "x={}".format(nall // xall)
        
    def parse_side(self, eq):
        xsum = 0
        nsum = 0
        start = 0
        elen = len(eq)
        while start < elen:
            end = start + 1
            while end < elen and eq[end] != "+" and eq[end] != '-':
                end += 1
            cur_p = eq[start: end]
            isX, cur_num = self.parse_one(cur_p)
            if isX:
                xsum += cur_num
            else:
                nsum += cur_num
            
            start = end
        
        return xsum, nsum
        
    
    def parse_one(self, s):
        sign = 1
        if s[0] == '-':
            sign = -1
        
        isX = False
        if s[-1] == 'x':
            np = s[1:-1]
            isX = True
        else:
            np = s[1:]
        
        if isX and len(np) == 0:
            num = sign
        else:
            num = sign * int(np)
        
        return isX, num

