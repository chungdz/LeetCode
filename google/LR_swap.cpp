#include<vector>
#include<string>
#include<algorithm>
using namespace std;

/*
777

Swap Adjacent in LR String
In a string composed of 'L', 'R', and 'X' characters, like "RXXLRXRXL", a move consists of either replacing one occurrence of "XL" with "LX", or replacing one occurrence of "RX" with "XR". Given the starting string start and the ending string end, return True if and only if there exists a sequence of moves to transform one string to the other.

 

Example 1:

Input: start = "RXXLRXRXL", end = "XRLXXRRLX"
Output: true
Explanation: We can transform start to end following these steps:
RXXLRXRXL ->
XRXLRXRXL ->
XRLXRXRXL ->
XRLXXRRXL ->
XRLXXRRLX
Example 2:

Input: start = "X", end = "L"
Output: false
Example 3:

Input: start = "LLR", end = "RRL"
Output: false
Example 4:

Input: start = "XL", end = "LX"
Output: true
Example 5:

Input: start = "XLLR", end = "LXLX"
Output: false
 

Constraints:

1 <= start.length <= 10^4
start.length == end.length
Both start and end will only consist of characters in 'L', 'R', and 'X'.

基本思想

分情况讨论，出现需要检测的就往后遍历

**/

class Solution {
public:
    bool canTransform(string start, string end) {
        int ss = start.size();
        if(ss != end.size()){return false;}
        int index = 0;
        while(index < ss){
            if(start[index] == end[index]){++index;}
            else if(start[index] == 'R' and end[index] == 'X'){
                int next_X = -1;
                for(int k = index + 1;k < ss;++k){
                    if(start[k] == 'X'){
                        next_X = k;
                        break;
                    }
                    else if(start[k] == 'L'){break;}
                }
                if(next_X != -1){
                    swap(start[index], start[next_X]);
                    ++index;
                }
                else{return false;}
            }
            else if(start[index] == 'X' and end[index] == 'L'){
                int next_L = -1;
                for(int k = index + 1;k < ss;++k){
                    if(start[k] == 'R'){break;}
                    if(start[k] == 'L'){
                        next_L = k;
                        break;
                    }
                }
                if(next_L != -1){
                    swap(start[index], start[next_L]);
                    ++index;
                }
                else{return false;}
            }
            else{return false;}
        }
        return true;
    }
};

/*

优化，O（N），因为略过X直接看L和R的关系




**/

class Solution {
public:
    bool canTransform(string start, string end) {
        int ss = start.size();
        if(ss != end.size()){return false;}
        int sindex = 0;
        int eindex = 0;
        while(true){
            while(sindex < ss && start[sindex] == 'X'){++sindex;}
            while(eindex < ss && end[eindex] == 'X'){++eindex;}

            if(sindex >= ss){
                if(eindex >= ss){return true;}
                else{return false;}
            }
            else if(eindex >= ss){return false;}

            if(start[sindex] != end[eindex]){return false;}
            else{
                if(start[sindex] == 'L' && sindex < eindex){return false;}
                else if(start[sindex] == 'R' && sindex > eindex){return false;}
                else{
                    ++sindex;
                    ++eindex;
                }
            }

        }
        return true;
    }
};