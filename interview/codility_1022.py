'''
问题1 找到数组里不存在的最小正整数
用set存储然后遍历的
'''

'''
问题2 字符串处理，给出E和L作为HH:MM，计算双方的时间差，然后计算停车价格
入场费2，首个小时3，之后每小时4
'''
import math

def solution(E, L):
    # write your code in Python 3.6
    res = 2

    eh = int(E[:2])
    em = int(E[-2:])

    lh = int(L[:2])
    lm = int(L[-2:])

    gap_h = (lh - eh) * 60
    gap_m = lm - em
    gap_t = gap_h + gap_m

    res += 3
    if gap_t <= 60:
        return res
    
    gap_t -= 60
    sh = math.ceil(gap_t / 60)
    
    res += 4 * sh
    return res
    