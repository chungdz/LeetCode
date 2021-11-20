from functools import cmp_to_key

nums = [(3, 20), (4, 10), (3, 40), (5, 10), (3, 80), (3, 40)]
# 升序
def mycmp(x, y):
    if x[0] == y [0]:
        if x[1] < y[1]:
            return -1
        elif x[1] > y[1]:
            return 1
        else:
            return 0
    else:
        if x[0] < y[0]:
            return -1
        elif x[0] > y[0]:
            return 1
    
nums1 = sorted(nums, key=cmp_to_key(mycmp))
print(nums1)
# 外升序内降序
def mycmp2(x, y):
    if x[0] == y [0]:
        if x[1] < y[1]:
            return 1
        elif x[1] > y[1]:
            return -1
        else:
            return 0
    else:
        if x[0] < y[0]:
            return -1
        elif x[0] > y[0]:
            return 1

nums2 = sorted(nums, key=cmp_to_key(mycmp2))
print(nums2)
# 外升序
def mycmp3(x, y):
    if x[0] < y [0]:
        return -1
    elif x[0] > y [0]:
        return 1
    return 0

nums3 = sorted(nums, key=cmp_to_key(mycmp3))
print(nums3)



