#include<vector>
#include<map>
#include<algorithm>
using namespace std;

/*
连续删除K个值，使得A的极值最小，返回最小极值
*/

int solution(vector<int> &A, int K) {
    // write your code in C++14 (g++ 6.2.0)
    int as = A.size();
    int start = 0;
    int end = K - 1;
    map<int, int> left_remain;
    map<int, int> right_remain;
    for(int i = K;i < as;++i){
        if(right_remain.find(A[i]) == right_remain.end()){
            right_remain[A[i]] = 1;
        }
        else{
            right_remain[A[i]] += 1;
        }
    }
    int amp = right_remain.rbegin()->first - right_remain.begin()->first;
    while(true){
        int left = A[start];
        start += 1;
        end += 1;
        if(end >= as){break;}

        int right = A[end];

        if(left_remain.find(left) == left_remain.end()){
            left_remain[left] = 1;
        }
        else{
            left_remain[left] += 1;
        }
        right_remain[right] -= 1;
        if(right_remain[right] == 0){
            right_remain.erase(right);
        }

        if(right_remain.size() > 0){
            int camp = max(left_remain.rbegin()->first, right_remain.rbegin()->first) - 
                            min(left_remain.begin()->first, right_remain.begin()->first);
            amp = min(camp, amp);
        }
        else{
            int camp = left_remain.rbegin()->first - left_remain.begin()->first;
            amp = min(camp, amp);
        }
    }
    return amp;
}