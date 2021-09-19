#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<set>
#include <iostream>
#include <queue>
#include <stdlib.h>
using namespace std;

/*

We are given an array A consisting of N integers. Find the maximum K (from 0 to N − 1) such that there exists a pair of positions (i, j) satisfying K = |i − j| = |A[i] − A[j]|, where |x| denotes absolute value of x. In other words, the distance between positions is equal to the difference between values. A position together with itself (when i = j) is always a valid pair for K = 0 (look at the third example).

Write a function:

class Solution { public int solution(int[] A); }

that, given an array A of N integers, returns the maximum possible K.

Examples:

1. Given A = [2, 2, 2, 1], the function should return 1. The furthest valid pair is A[2] = 2 and A[3] = 1, as 1 = |2 − 3| = |2 − 1|.

2. Given A = [2, 4, 6, 7, 4, 7, 2], the function should return 5. The furthest valid pair is A[0] and A[5].

3. Given A = [100, 100, 100], the function should return 0. The only valid pairs are: A[0] and A[0], A[1] and A[1], A[2] and A[2].

4. Given A = [1000000000], the function should return 0. The only valid pair is: A[0] and A[0].

Write an efficient algorithm for the following assumptions:

N is an integer within the range [1..100,000];

each element of array A is an integer within the range [0..1,000,000,000].


**/

/// 2, 4, 6, 7, 4, 7, 2
/// 0, 1, 2, 3, 4, 5, 6, 7
/// 0

int solution(vector<int> A){
    int as = A.size();
    int k = 0;
    for(int i = 0;i < as - 1;++i){
        int max_add = as - i - 1;
        for(int lens = max_add;lens >= k + 1;--lens){
            if(abs(A[i + lens] - A[i]) == lens){
                k = lens;
                break;
            }
        }
    }

    return k;
}