# you can write to stdout for debugging purposes, e.g.
# print("this is a debug message")

'''
用M个1*1的砖和N个2*2的砖，铺地板得到最大方块，返回方块的边长
'''

import math

def solution(M, N):
    # write your code in Python 3.6
    total_area = M + N * 4
    max_line = int(math.sqrt(total_area))
    for i in range(max_line, 0, -1):
        cur_area = i * i
        if i % 2 == 1:
            max_2_num = ((i - 1) / 2) * ((i - 1) / 2)
        else:
            max_2_num = (i / 2) * (i / 2)
        
        real_2_num = max(N, max_2_num)
        real_2_area = 4 * real_2_num
        remain_area = cur_area - real_2_area
        if remain_area <= M:
            return i

    return 0
        