'''
149 Max Points on a Line

Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane, return the maximum number of points that lie on the same straight line.

 

Example 1:


Input: points = [[1,1],[2,2],[3,3]]
Output: 3
Example 2:


Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
 

Constraints:

1 <= points.length <= 300
points[i].length == 2
-10^4 <= xi, yi <= 10^4
All the points are unique.

基本思想

暴力搜索
两两组合成新的直线，匹配剩下的点
剪枝被搜索过的点
'''

class Solution:
    def maxPoints(self, points: List[List[int]]) -> int:
        plen = len(points)
        if plen <= 2:
            return plen

        epsilon = 1e-6

        visited = [[False] * plen for _ in range(plen)]
        max_count = 2
        for i in range(plen - 1):
            for j in range(i + 1, plen):
                if visited[i][j]:
                    continue

                slope, intercept = None, None
                if points[i][0] != points[j][0]:
                    slope, intercept = self.build_line(points[i][0], points[i][1], points[j][0], points[j][1])
                
                same_line = [i, j]
                for k in range(j + 1, plen):
                    
                    if slope is None:
                        if points[i][0] == points[k][0]:
                            same_line.append(k)
                        continue
                    
                    y_hat = slope * points[k][0] + intercept
                    if abs(points[k][1] - y_hat) < epsilon:
                        same_line.append(k)
                
                cur_len = len(same_line)
                for firstp in range(cur_len - 1):
                    for secondp in range(firstp + 1, cur_len):
                        visited[same_line[firstp]][same_line[secondp]] = True
                
                max_count = max(max_count, cur_len)
                
        return max_count
                    

    
    @staticmethod
    def build_line(x1, y1, x2, y2):
        k = (y1 - y2)/(x1 - x2)
        b = (x1 * y2 - x2 * y1) / (x1 - x2)

        return k, b
