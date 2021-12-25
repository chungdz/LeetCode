'''
311 Sparse Matrix Multiplication

Given two sparse matrices mat1 of size m x k and mat2 of size k x n, return the result of mat1 x mat2. You may assume that multiplication is always possible.

 

Example 1:


Input: mat1 = [[1,0,0],[-1,0,3]], mat2 = [[7,0,0],[0,0,0],[0,0,1]]
Output: [[7,0,0],[-7,0,3]]
Example 2:

Input: mat1 = [[0]], mat2 = [[0]]
Output: [[0]]
 

Constraints:

m == mat1.length
k == mat1[i].length == mat2.length
n == mat2[i].length
1 <= m, n, k <= 100
-100 <= mat1[i][j], mat2[i][j] <= 100

基本思想

矩阵乘法：c_ij = a_i * b_j
如果矩阵是稀疏矩阵，就把a_i和b_j从list变成dict，只加乘有相同位置的非零数字
'''

class Solution:
    def multiply(self, mat1: List[List[int]], mat2: List[List[int]]) -> List[List[int]]:
        m = len(mat1)
        k = len(mat1[0])
        n = len(mat2[0])

        mdict = []
        for mi in mat1:
            midict = {}
            for index, mij in enumerate(mi):
                if mij != 0:
                    midict[index] = mij
            mdict.append(midict)
        
        ndict = []
        for j in range(n):
            njdict = {}
            for i in range(k):
                if mat2[i][j] != 0:
                    njdict[i] = mat2[i][j]
            ndict.append(njdict)
        
        res = []
        for midict in mdict:
            new_row = []
            for njdict in ndict:
                new_row.append(self.sparse_vect_product(midict, njdict))
            res.append(new_row)
        
        return res

    @staticmethod
    def sparse_vect_product(v1, v2):
        total = 0
        for k, v in v1.items():
            if k in v2:
                total += v * v2[k]
        return total