class Solution:
    def titleToNumber(self, columnTitle: str) -> int:
        columnTitle = columnTitle[::-1]
        res = 0
        curp = 1
        for c in columnTitle:
            res += c * curp 
            curp *= 26
        return res
