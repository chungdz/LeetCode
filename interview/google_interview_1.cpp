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


There is a string S consisting of N letters 'a' and 'b'. In one move, a single letter can be removed. Removing the first or the last letter in the string costs 1 and removing any other letter costs 2. After removing a letter from the middle, the two remaining parts are joined.

For example, given S = "abaab", removing the central letter 'a' from S costs 2. The string that would remain after this operation is "abab".

What is the minimum cost needed to obtain a string without any letter 'b'?

Write a function:

class Solution { public int solution(String S); }

that, given a string S, returns the minimum cost of removals so that the remaining sequence does not contain any letter 'b'.

Examples:

1. Given S = "aabaa", the function should return 2. After removing 'b' from the middle, the remaining sequence contains no 'b's.

2. Given S = "abbaaba", the function should return 5. We can perform the following operations: abbaaba → bbaaba → baaba → aaba → aaa. The cost of these operations is 1 + 1 + 1 + 2 = 5. Another option is: abbaaba → bbaaba → baaba → aaba → aab → aa, resulting in a cost of 1 + 1 + 1 + 1 + 1 = 5.

3. Given S = "bbb", the function should return 3. We can keep removing the last letter from the string until the string is empty.

4. Given S = "abbbaabaabbba", the function should return 10. We can remove the middle letter 'b' (cost 2), then the first four letters ("abbb") and the last four letters ("bbba"), each at a cost of 4.

Write an efficient algorithm for the following assumptions:

N is an integer within the range [1..100,000];
string S consists only of the characters 'a' and/or 'b'.
Keyboard navigation: Use Tab to advance the cursor. To exit the editor, press the ctrl and [ keys.
1
class Solution {
2
​
3
  public static int solution(String S) {
4
    System.err.println("Tip: Use System.err.println() to write debug messages on the output tab.");
5
    return 0;
6
  }
7
}
8

**/

// abbaabab
// 012345678
// 1 0 2 1 0

vector<int> b_pos;

int min_path(){
    int bs = b_pos.size();
    if(bs == 2){
        if(b_pos[0] >= 1 && b_pos[1] >= 1){
            return 2;
        }
        return 1 + min(b_pos[0], b_pos[1]);
    }

    // from front
    // method 1
    int rec = b_pos[0];
    b_pos.erase(b_pos.begin());
    int m1 = 1 + rec + min_path();
    // method 2
    int rec_2 = b_pos[0];
    b_pos[0] += rec;
    int m2 = 2 + min_path();
    // recover
    b_pos[0] = rec_2;
    b_pos.insert(b_pos.begin(), rec);

    // from back
    // method 3
    int rec_back = b_pos[bs - 1];
    b_pos.pop_back();
    int m3 = 1 + rec_back + min_path();
    // method 4
    int rec_back_2 = b_pos[bs - 2];
    b_pos[bs - 2] += rec_back;
    int m4 = 2 + min_path();
    // recover
    b_pos[bs - 2] = rec_back_2;
    b_pos.push_back(rec_back);

    int m12 = min(m1, m2);
    int m34 = min(m3, m4);

    return min(m12, m34);
}

int solution(string S) {

    int ss = S.size();
    int pre_b = -1;
    for(int i = 0;i < ss;++i){
        if(S[i] == 'b'){
            b_pos.push_back(i - pre_b - 1);
            pre_b = i;
        }
    }
    b_pos.push_back(ss - pre_b - 1);
    
    return min_path();
}

