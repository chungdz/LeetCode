#include<vector>
#include<set>
#include<algorithm>
#include<queue>
using namespace std;

/*
218 The Skyline Problem

A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Given the locations and heights of all the buildings, return the skyline formed by these buildings collectively.

The geometric information of each building is given in the array buildings where buildings[i] = [lefti, righti, heighti]:

lefti is the x coordinate of the left edge of the ith building.
righti is the x coordinate of the right edge of the ith building.
heighti is the height of the ith building.
You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

The skyline should be represented as a list of "key points" sorted by their x-coordinate in the form [[x1,y1],[x2,y2],...]. Each key point is the left endpoint of some horizontal segment in the skyline except the last point in the list, which always has a y-coordinate 0 and is used to mark the skyline's termination where the rightmost building ends. Any ground between the leftmost and rightmost buildings should be part of the skyline's contour.

Note: There must be no consecutive horizontal lines of equal height in the output skyline. For instance, [...,[2 3],[4 5],[7 5],[11 5],[12 7],...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...,[2 3],[4 5],[12 7],...]

 

Example 1:


Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
Explanation:
Figure A shows the buildings of the input.
Figure B shows the skyline formed by those buildings. The red points in figure B represent the key points in the output list.
Example 2:

Input: buildings = [[0,2,3],[2,5,3]]
Output: [[0,3],[5,0]]
 

Constraints:

1 <= buildings.length <= 10^4
0 <= left_i < right_i <= 2^31 - 1
1 <= height_i <= 2^31 - 1
buildings is sorted by lefti in non-decreasing order.

基本思想

滑动窗口
找到所有边缘，去重排序遍历
对每个边缘
用最大堆保存建筑（用高度比较），加入合规的，去除堆顶不合规的（右边坐标小于等于当前边缘），堆顶合规的是这个边缘的高度
没有合规的高度就是零

插入最终结果时，检查是否与前一个高度重复，重复就不加入
*/

struct tmp2{
    bool operator() (vector<int>& a, vector<int>& b) 
    {
        return a[2] < b[2]; 
    }
};

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        priority_queue<vector<int>, vector<vector<int>>, tmp2> mq;
        set<int> edge_point;
        for(auto v: buildings){
            edge_point.insert(v[0]);
            edge_point.insert(v[1]);
        }
        vector<vector<int>> res;
        int bi = 0;
        int bs = buildings.size();
        for(auto ep: edge_point){
            while(bi < bs && (buildings[bi][0] <= ep && buildings[bi][1] > ep)){
                mq.push(buildings[bi]);
                bi += 1;
            }
            vector<int> tmpt;
            while(!mq.empty()){
                tmpt = mq.top();
                if(tmpt[1] <= ep){
                    mq.pop();
                }
                else{
                    break;
                }
            }

            int cur_height;
            if(!mq.empty()){
                tmpt = mq.top();
                cur_height = tmpt[2];
            }
            else{
                cur_height = 0;
            }

            if(res.size() > 0 && cur_height == res.back()[1]){
                continue;
            }
            else{
                res.push_back(vector({ep, cur_height}));
            }
        }

        return res;
    }
};