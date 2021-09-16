#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
using namespace std;

/*


You are given an array of integers a and two integers l and r. You task is to calculate a boolean array b, where b[i] = true if there exists an integer x, such that a[i] = (i + 1) * x and l ≤ x ≤ r. Otherwise, b[i] should be set to false.

Example

For a = [8, 5, 6, 16, 5], l = 1, and r = 3, the output should be boundedRatio(a, l, r) = [false, false, true, false, true].

For a[0] = 8, we need to find a value of x such that 1 * x = 8, but the only value that would work is x = 8 which doesn't satisfy the boundaries 1 ≤ x ≤ 3, so b[0] = false.
For a[1] = 5, we need to find a value of x such that 2 * x = 5, but there is no integer value that would satisfy this equation, so b[1] = false.
For a[2] = 6, we can choose x = 2 because 3 * 2 = 6 and 1 ≤ 2 ≤ 3, so b[2] = true.
For a[3] = 16, there is no an integer 1 ≤ x ≤ 3, such that 4 * x = 16, so b[3] = false.
For a[4] = 5, we can choose x = 1 because 5 * 1 = 5 and 1 ≤ 1 ≤ 3, so b[4] = true.
Input/Output

[execution time limit] 0.5 seconds (cpp)

[input] array.integer a

An array of integers.

Guaranteed constraints:
1 ≤ a.length ≤ 100,
1 ≤ a[i] ≤ 106.

[input] integer l

An integer representing the lower bound for x.

Guaranteed constraints:
1 ≤ l ≤ 104.

[input] integer r

An integer representing the upper bound for x.

Guaranteed constraints:
1 ≤ r ≤ 104,
l ≤ r.

[output] array.boolean

A boolean array.

[C++] Syntax Tips

// Prints help message to the console
// Returns a string
string helloWorld(string name) {
    cout << "This prints to the console when you Run Tests" << endl;
    return "Hello, " + name;
}








**/

vector<bool> boundedRatio(vector<int> a, int l, int r) {
    vector<bool> b;
    int total_size = a.size();
    for(int i = 0;i < total_size;++i){
        int remain = a[i] % (i + 1);
        if(remain == 0){
            int target = a[i] / (i + 1);
            if(target >= l && target <= r){
                b.push_back(true);
                continue;
            }
        }
        b.push_back(false);
    }
}

/*


Codewriting

Given an array of integers a, your task is to calculate the digits that occur the most number of times in the array. Return the array of these digits in ascending order.

Example

For a = [25, 2, 3, 57, 38, 41], the output should be mostFrequentDigits(a) = [2, 3, 5].

Here are the number of times each digit appears in the array:

0 -> 0
1 -> 1
2 -> 2
3 -> 2
4 -> 1
5 -> 2
6 -> 0
7 -> 1
8 -> 1
The most number of times any number occurs in the array is 2, and the digits which appear 2 times are 2, 3 and 5. So the answer is [2, 3, 5].

Input/Output

[execution time limit] 0.5 seconds (cpp)

[input] array.integer a

An array of positive integers.

Guaranteed constraints:
1 ≤ a.length ≤ 103,
1 ≤ a[i] < 100.

[output] array.integer

The array of most frequently occurring digits, sorted in ascending order.

[C++] Syntax Tips

// Prints help message to the console
// Returns a string
string helloWorld(string name) {
    cout << "This prints to the console when you Run Tests" << endl;
    return "Hello, " + name;
}


**/

vector<int> mostFrequentDigits(vector<int> a) {
    int digit_num[10] = {0};
    for(int elem: a){
        if(elem < 10){
            digit_num[elem] += 1;
        }
        else{
            int high, low;
            low = elem % 10;
            high = elem / 10;

            digit_num[high] += 1;
            digit_num[low] += 1;
        }
    }

    int max_num = *(max_element(digit_num, digit_num + 10));
    vector<int> res;
    for(int i = 0;i < 10;++i){
        if(digit_num[i] == max_num){
            res.push_back(i);
        }
    }

    return res;
}


/*

Given a square matrix of integers m, your task is to rearrange its numbers in the following way:

First, sort its values in ascending order of how frequently the number occurs in m. In the case of a tie, sort the equally frequent numbers by their values, in ascending order.
Second, place the sorted numbers diagonally, starting from the bottom right corner, like this:
element ordering
Example

For

m = [[ 1, 4, -2],
     [-2, 3,  4],
     [ 3, 1,  3]]
the output should be

sortMatrixByOccurrences(m) = [[3,  3,  4],
                              [3,  4,  1],
                              [1, -2, -2]]
First we look at the frequency of each number:

Number 1 occurs 2 times;
Number -2 occurs 2 times;
Number 3 occurs 3 times;
Number 4 occurs 2 times.
Because numbers 1, -2, and 4 occur the same number of times, we sort them by their values in ascending order. Number 3 occurs the most numbers of times, so it goes after all other numbers. Finally, after sorting we get the following array: [-2, -2, 1, 1, 4, 4, 3, 3, 3]

After sorting, the numbers should be placed diagonally starting from the bottom right corner, as follows:

[[3,  3,  4],
 [3,  4,  1],
 [1, -2, -2]]
Input/Output

[execution time limit] 0.5 seconds (cpp)

[input] array.array.integer m

A square matrix of integers.

Guaranteed constraints:
1 ≤ m.length ≤ 40,
m[i].length = m.length,
-1000 ≤ m[i][j] ≤ 1000.

[output] array.array.integer

The matrix m rearranged according to the specifications above.

[C++] Syntax Tips

// Prints help message to the console
// Returns a string
string helloWorld(string name) {
    cout << "This prints to the console when you Run Tests" << endl;
    return "Hello, " + name;
}

1234
vector<vector<int>> sortMatrixByOccurrences(vector<vector<int>> m) {

}

TESTS
CUSTOM TESTS
Test 1
Input:
m:
[[1,4,-2], 
 [-2,3,4], 
 [3,1,3]]
Expected Output:
[[3,3,4], 
 [3,4,1], 
 [1,-2,-2]]
Click the "Run Tests" button to see output and console logs.
Test 2
Test 3
Test 4
Test 5
Test 6
Test 7
Test 8
Test 9
Test 10
Test 11
Test 12
Test 13
Test 14
MORE

**/
bool comp(const pair<int, int>& p1, const pair<int, int>& p2){
    if(p1.second == p2.second){
        return p1.first < p2.first;
    }
    else{
        return p1.second < p2.second;
    }
}

pair<int, int> next_pos(int crow, int ccol, int csize){
    int nrow, ncol;
    if(crow == 0){
        ncol = 0;
        nrow = ccol - 1;
    }
    else if(ccol == csize - 1){
        nrow = csize - 1;
        ncol = crow - 1;
    }
    else{
        nrow = crow - 1;
        ncol = ccol + 1;
    }

    return pair<int, int>(nrow, ncol);
}


vector<vector<int>> sortMatrixByOccurrences(vector<vector<int>> m){
    map<int, int> number_record;
    int lens = m.size();
    for(auto v: m){
        for(int elem: v){
            if(number_record.find(elem) == number_record.end()){
                number_record[elem] = 1;
            }
            else{
                number_record[elem] += 1;
            }
        }
    }
    vector<pair<int, int>> ordered_record;
    for(auto it: number_record){
        ordered_record.push_back(pair<int, int>(it.first, it.second));
    }

    sort(ordered_record.begin(), ordered_record.end(), comp);
    int total_num = lens * lens;

    int cur_row = lens - 1;
    int cur_col = lens - 1;
    int cur_index = 0;
    vector<vector<int>> res;
    for(int j = 0;j < lens;++j){
        res.push_back(vector<int>(lens, 0));
    }
    while(total_num--){
        res[cur_row][cur_col] = ordered_record[cur_index].first;
        ordered_record[cur_index].second -= 1;
        if(ordered_record[cur_index].second < 1){cur_index++;}

        pair<int, int> cor = next_pos(cur_row, cur_col, lens);
        cur_row = cor.first;
        cur_col = cor.second;
    }
    return res;
}

/*

You are given two integer arrays a, b and one array of distinct integers c. Your task is to check whether b is the longest contiguous subarray of a consisting only of elements from c, i.e.

Each of the elements of b belong to c,
a contains b as a contiguous subarray,
b is the longest of the contiguous subarrays of a which satisfy the first two conditions.
Return true if all the above conditions are met, and false otherwise.

NOTE: If there is a tie for the longest contiguous subarrays of a consisting of elements from c, the answer is still considered true if b is one of these longest contiguous subarrays.

Example

For a = [1, 1, 5, 1, 2], b = [1, 2], and c = [2, 1], the output should be longestSubarrayCheck(a, b, c) = true.

All three conditions are met:

All of the elements of b belong to c,
a contains b as a contiguous subarray (a[3..4] = b),
b is the longest of these contiguous subarrays. To prove this, let's look at all the contiguous subarrays of length greater than 2:
a[0..2] = [1, 1, 5] contains 5, which doesn't belong to c.
a[0..3] = [1, 1, 5, 1] contains 5, which doesn't belong to c.
a[0..4] = [1, 1, 5, 1, 2] contains 5, which doesn't belong to c.
a[1..3] = [1, 5, 1] contains 5, which doesn't belong to c.
a[1..4] = [1, 5, 1, 2] contains 5, which doesn't belong to c.
a[2..4] = [5, 1, 2] contains 5, which doesn't belong to c.
Therefore b is the longest contiguous subarray of a consisting only of elements from c, so the answer is true.

For a = [1, 2, 3, 6, 1, 1, 1], b = [1, 2, 3], and c = [2, 1], the output should be longestSubarrayCheck(a, b, c) = false.

Although b is a contiguous subarray of a, it contains the element b[2] = 3 which does not appear in c, therefore it does not meet the conditions. So the answer is false.

For a = [1, 2, 2, 3, 2, 1, 3], b = [3, 2, 1, 3], and c = [2, 1, 3], the output should be longestSubarrayCheck(a, b, c) = false.

All of the elements of a belong to c, and b.length < a.length, so b couldn't possibly be the longest contiguous subarray consisting of elements from c. So, the answer is false.

Input/Output

[execution time limit] 0.5 seconds (cpp)

[input] array.integer a

An array of integers.

Guaranteed constraints:
1 ≤ a.length ≤ 105,
0 ≤ a[i] ≤ 109.

[input] array.integer b

An array of integers.

Guaranteed constraints:
1 ≤ b.length ≤ 105,
0 ≤ b[i] ≤ 109.

[input] array.integer c

An array of distinct integers.

Guaranteed constraints:
1 ≤ c.length ≤ 105,
0 ≤ c[i] ≤ 109.

[output] boolean

Return true if b is the longest contiguous subarray of a consisting of elements from c, otherwise return false.

[C++] Syntax Tips

// Prints help message to the console
// Returns a string
string helloWorld(string name) {
    cout << "This prints to the console when you Run Tests" << endl;
    return "Hello, " + name;
}


**/

bool longestSubarrayCheck(vector<int> a, vector<int> b, vector<int> c) {
    
    int max_len = 0;
    int b_len = b.size();
    int a_len = a.size();
    set<int> c_ele(c.begin(), c.end());
    // check b all in c
    for(int b_elem: b){
        if(c_ele.find(b_elem) == c_ele.end()){
            return false;
        }
    }
    // check a for longest
    int start = 0;
    int clen = 0;
    int pointer = 0;
    bool has_b = false;
    while(pointer < a_len){
        
        if(c_ele.find(a[pointer]) != c_ele.end()){
            if(pointer < a_len){
                clen++;
                pointer++;
            }
            if(pointer >= a_len){
                max_len = max(max_len, clen);
                if(max_len > b_len){return false;}
                else if(max_len == b_len){
                    bool check_equal = true;
                    for(int ap = 0;ap < b_len;ap++){
                        if(a[start + ap] != b[ap]){
                            check_equal = false;
                            break;
                        }
                    }
                    has_b = has_b | check_equal;
                }
            }
        }
        else{
            max_len = max(max_len, clen);
            if(max_len > b_len){return false;}
            else if(max_len == b_len){
                bool check_equal = true;
                for(int ap = 0;ap < b_len;ap++){
                    if(a[start + ap] != b[ap]){
                        check_equal = false;
                        break;
                    }
                }
                has_b = has_b | check_equal;
            }
            
            start = start + clen + 1;
            pointer = start;
            clen = 0;
        }
    }

    return has_b;
}
