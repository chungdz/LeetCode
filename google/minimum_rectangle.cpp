#include<vector>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<stdlib.h>
#include<limits.h>
using namespace std;

/*
939

Minimum Area Rectangle
You are given an array of points in the X-Y plane points where points[i] = [xi, yi].

Return the minimum area of a rectangle formed from these points, with sides parallel to the X and Y axes. If there is not any such rectangle, return 0.

 

Example 1:


Input: points = [[1,1],[1,3],[3,1],[3,3],[2,2]]
Output: 4
Example 2:


Input: points = [[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
Output: 2
 

Constraints:

1 <= points.length <= 500
points[i].length == 2
0 <= xi, yi <= 4 * 10^4
All the given points are unique.

基本思想

暴力搜索 + 剪枝

点对枚举和边界枚举都是O(N^2)，但是边界枚举能ACCEPTED，点对枚举TLE

边界枚举的剪枝可能更有效

**/

/*

点对枚举, O(n^2)

**/

bool cmp(const vector<int>& v1, const vector<int>& v2){
    if(v1[0] == v2[0]){return v1[1] < v2[1];}
    else{return v1[0] < v2[0];}
}

class Solution {
    unordered_map<int, unordered_set<int>> mp;

    bool rec_exist(vector<int> p1, vector<int> p2){
        if(p1[0] == p2[0] || p1[1] == p2[1]){return false;}
        if(mp[p1[0]].find(p2[1]) == mp[p1[0]].end()){return false;}
        if(mp[p2[0]].find(p1[1]) == mp[p2[0]].end()){return false;}
        return true;
    }
public:
    int minAreaRect(vector<vector<int>>& points) {
        int ps = points.size();
        sort(points.begin(), points.end(), cmp);
        for(auto v: points){
            if(mp.find(v[0]) == mp.end()){mp[v[0]] = unordered_set<int>();}
            mp[v[0]].insert(v[1]);
        }

        int total_min = INT32_MAX;
        for(int i = 0;i < ps - 1;++i){
            int min_rec = INT32_MAX;
            int min_index = -1;
            int min_height_dis = INT32_MAX;
            for(int j = i + 1;j < ps;++j){
                if(rec_exist(points[i], points[j])){
                    if(min_index == -1){
                        min_index = j;
                        min_height_dis = abs(points[j][1] - points[i][1]);
                        min_rec = (points[j][0] - points[i][0]) * min_height_dis;
                    }
                    else{
                        int cur_height_dis = abs(points[j][1] - points[i][1]);
                        if(cur_height_dis >= min_height_dis){continue;}

                        min_height_dis = cur_height_dis;
                        int cur_rec = (points[j][0] - points[i][0]) * min_height_dis;
                        if(cur_rec < min_rec){
                            min_index = j;
                            min_rec = cur_rec;
                        }
                    }
                }
            }

            total_min = min(total_min, min_rec);
        }

        if(total_min == INT32_MAX){return 0;}
        return total_min;
    }
};

////////////////////////////////////////////////////////////////////

/*

边界枚举，也是O(N^2)的复杂度

**/



class Solution {
    unordered_map<int, unordered_map<int, int>> lastx;
    map<int, vector<int>> board;
    
public:
    int minAreaRect(vector<vector<int>>& points) {
        for(auto p: points){
            if(board.find(p[0]) == board.end()){
                board[p[0]] = vector<int>();
            }
            board[p[0]].push_back(p[1]);
        }

        int minimum = INT32_MAX;
        // every boarder of x
        for(auto i = board.begin();i != board.end();++i){
            int cur_x = i->first;
            int cur_size = i->second.size();
            if(cur_size < 2){continue;}
            sort(i->second.begin(), i->second.end());
            // every y in this boarder
            for(int j = 0;j < cur_size - 1;++j){
                int y1 = i->second[j];
                for(int k = j + 1;k < cur_size;++k){
                    int y2 = i->second[k];

                    if(lastx.find(y1) == lastx.end()){
                        lastx[y1] = unordered_map<int, int>();
                    }
                    else if(lastx[y1].find(y2) != lastx[y1].end()){
                        int pre_x = lastx[y1][y2];
                        int rec = (cur_x - pre_x) * (y2 - y1);
                        minimum = min(minimum, rec);
                    }
                    lastx[y1][y2] = cur_x;
                }
            }
        }

        if(minimum == INT32_MAX){minimum = 0;}
        return minimum;
    }
};
/*

unordered map 编译错误
map 时间花销提升了2倍

**/
typedef pair<int, int> point;

class Solution {
    map<point, int> lastx;
    map<int, vector<int>> board;
    
public:
    int minAreaRect(vector<vector<int>>& points) {
        for(auto p: points){
            if(board.find(p[0]) == board.end()){
                board[p[0]] = vector<int>();
            }
            board[p[0]].push_back(p[1]);
        }

        int minimum = INT32_MAX;
        // every boarder of x
        for(auto i = board.begin();i != board.end();++i){
            int cur_x = i->first;
            int cur_size = i->second.size();
            if(cur_size < 2){continue;}
            sort(i->second.begin(), i->second.end());
            // every y in this boarder
            for(int j = 0;j < cur_size - 1;++j){
                int y1 = i->second[j];
                for(int k = j + 1;k < cur_size;++k){
                    int y2 = i->second[k];

                    if(lastx.find(point(y1, y2)) != lastx.end()){
                        int pre_x = lastx[point(y1, y2)];
                        int rec = (cur_x - pre_x) * (y2 - y1);
                        minimum = min(minimum, rec);
                    }
                    lastx[point(y1, y2)] = cur_x;
                }
            }
        }

        if(minimum == INT32_MAX){minimum = 0;}
        return minimum;
    }
};