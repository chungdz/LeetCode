# 方法二：DFS 序列上做串匹配
# 思路和算法

# 这个方法需要我们先了解一个「小套路」：一棵子树上的点在 DFS 序列（即先序遍历）中是连续的。了解了这个「小套路」之后，我们可以确定解决这个问题的方向就是：把 ss 和 tt 先转换成 DFS 序，然后看 tt 的 DFS 序是否是 ss 的 DFS 序的「子串」。

# 这样做正确吗？ 假设 ss 由两个点组成，11 是根，22 是 11 的左孩子；tt 也由两个点组成，11 是根，22 是 11 的右孩子。这样一来 ss 和 tt 的 DFS 序相同，可是 tt 并不是 ss 的某一棵子树。由此可见「ss 的 DFS 序包含 tt 的 DFS 序」是「tt 是 ss 子树」的 必要不充分条件，所以单纯这样做是不正确的。

# 为了解决这个问题，我们可以引入两个空值 lNull 和 rNull，当一个节点的左孩子或者右孩子为空的时候，就插入这两个空值，这样 DFS 序列就唯一对应一棵树。处理完之后，就可以通过判断 「ss 的 DFS 序包含 tt 的 DFS 序」来判断答案。



# 在判断「ss 的 DFS 序包含 tt 的 DFS 序」的时候，可以暴力匹配，也可以使用 KMP 或者 Rabin-Karp 算法，在使用 Rabin-Karp 算法的时候，要注意串中可能有负值。

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isSubtree(self, s: TreeNode, t: TreeNode) -> bool:
        s_arr = []
        t_arr = []
        self.arr_generate(s, s_arr)
        self.arr_generate(t, t_arr)
        next_arr = self.kmp_pattern(t_arr)

        return self.kmp_match(s_arr, t_arr, next_arr)
    
    def arr_generate(self, tn: TreeNode, arr: []):
        if tn is None:
            arr.append('none')
            return
        else:
            arr.append(tn.val)
        
        self.arr_generate(tn.left, arr)
        self.arr_generate(tn.right, arr)
    
    @staticmethod
    def kmp_pattern(pat: []) -> []:
        lenp = len(pat)
        next_arr = []
        next_arr.append(-1)
        j = 0
        k = -1
        while j < lenp - 1:
            if k == -1 or pat[k] == pat[j]:
                k += 1
                j += 1
                if pat[j] != pat[k]:
                    next_arr.append(k)
                else:
                    next_arr.append(next_arr[k])
            else:
                k = next_arr[k]
        
        return next_arr
    
    @staticmethod
    def kmp_match(s_arr: [], t_arr: [], next_arr: []) -> bool:
        sp = 0
        slen = len(s_arr)
        tp = 0
        tlen = len(t_arr)

        while sp < slen and tp < tlen:
            if (s_arr[sp] == 'none' and t_arr[tp] == 'none') or (s_arr[sp] != 'none' and t_arr[tp] != 'none' and s_arr[sp] == t_arr[tp]) or tp == -1:
                sp += 1
                tp += 1
            else:
                tp = next_arr[tp]
            
        if tp == tlen:
            return True
        
        return False