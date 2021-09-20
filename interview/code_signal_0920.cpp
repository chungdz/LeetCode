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
Let's say a triple (a, b, c) is a zigzag if either a < b > c or a > b < c.

Given an array of integers numbers, your task is to check all the triples of its consecutive elements for being a zigzag. More formally, your task is to construct an array of length numbers.length - 2, where the ith element of the output array equals 1 if the triple (numbers[i], numbers[i + 1], numbers[i + 2]) is a zigzag, and 0 otherwise.

Example

For numbers = [1, 2, 1, 3, 4], the output should be isZigzag(numbers) = [1, 1, 0].

(numbers[0], numbers[1], numbers[2]) = (1, 2, 1) is a zigzag, because 1 < 2 > 1;
(numbers[1], numbers[2] , numbers[3]) = (2, 1, 3) is a zigzag, because 2 > 1 < 3;
(numbers[2], numbers[3] , numbers[4]) = (1, 3, 4) is not a zigzag, because 1 < 3 < 4;
For numbers = [1, 2, 3, 4], the output should be isZigzag(numbers) = [0, 0];

Since all the elements of numbers are increasing, there are no zigzags.

For numbers = [1000000000, 1000000000, 1000000000], the output should be isZigzag(numbers) = [0].

Since all the elements of numbers are the same, there are no zigzags.

Input/Output

[execution time limit] 0.5 seconds (cpp)

[input] array.integer numbers

An array of integers.

Guaranteed constraints:
3 ≤ numbers.length ≤ 100,
1 ≤ numbers[i] ≤ 109.

[output] array.integer

Return an array, where the ith element equals 1 if the triple (numbers[i], numbers[i + 1], numbers[i + 2]) is a zigzag, and 0 otherwise.

[C++] Syntax Tips

// Prints help message to the console
// Returns a string
string helloWorld(string name) {
    cout << "This prints to the console when you Run Tests" << endl;
    return "Hello, " + name;
}
**/

vector<int> isZigzag(vector<int> numbers) {
    vector<int> res;
    // 0 bigger, 1 smaller, 2 equall
    int pre;
    if(numbers[2] > numbers[1]){
        if(numbers[0] > numbers[1]){
            res.push_back(1);
        }
        else{
            res.push_back(0);
        }
        pre = 0;
    }
    else if(numbers[2] < numbers[1]){
        if(numbers[0] < numbers[1]){
            res.push_back(1);
        }
        else{
            res.push_back(0);
        }
        pre = 1;
    }
    else{
        res.push_back(0);
        pre = 0;
    }
    int ns = numbers.size();
    for(int i = 3;i < ns;++i){
        int cur;
        if(numbers[i] > numbers[i - 1]){
            cur = 0;
        }
        else if(numbers[i] < numbers[i - 1]){
            cur = 1;
        }
        else{
            cur = 2;
        }

        if((cur == 0 && pre == 1) || (cur == 1 && pre == 0)){
            res.push_back(1);
        }   
        else{
            res.push_back(0);
        }

        pre = cur;
    }

    return res;
}

/*
You are given an array of non-negative integers numbers. You are allowed to choose any number from this array and swap any two digits in it. If after the swap operation the number contains leading zeros, they can be omitted and not considered (eg: 010 will be considered just 10).

Your task is to check whether it is possible to apply the swap operation at most once, so that the elements of the resulting array are strictly increasing.

Example

For numbers = [1, 5, 10, 20], the output should be makeIncreasing(numbers) = true.

The initial array is already strictly increasing, so no actions are required.

For numbers = [1, 3, 900, 10], the output should be makeIncreasing(numbers) = true.

By choosing numbers[2] = 900 and swapping its first and third digits, the resulting number 009 is considered to be just 9. So the updated array will look like [1, 3, 9, 10], which is strictly increasing.

For numbers = [13, 31, 30], the output should be makeIncreasing(numbers) = false.

The initial array elements are not increasing.
By swapping the digits of numbers[0] = 13, the array becomes [31, 31, 30] which is not strictly increasing;
By swapping the digits of numbers[1] = 31, the array becomes [13, 13, 30] which is not strictly increasing;
By swapping the digits of numbers[2] = 30, the array becomes [13, 31, 3] which is not strictly increasing;
So, it's not possible to obtain a strictly increasing array, and the answer is false.

Input/Output

[execution time limit] 0.5 seconds (cpp)

[input] array.integer numbers

An array of non-negative integers.

Guaranteed constraints:
1 ≤ numbers.length ≤ 103,
0 ≤ numbers[i] ≤ 103.

[output] boolean

Return true if it is possible to obtain a strictly increasing array by applying the digit-swap operation at most once, and false otherwise.

[C++] Syntax Tips

// Prints help message to the console
// Returns a string
string helloWorld(string name) {
    cout << "This prints to the console when you Run Tests" << endl;
    return "Hello, " + name;
}

test 18 unpassed with no reason

**/

int swap_digits(int origin){
    string cur_num = to_string(origin);
    reverse(cur_num.begin(), cur_num.end());
    return stoi(cur_num);
}

bool check_valid(int num, int i, vector<int>& numbers){
    int ns = numbers.size();
    if(i > 0){
        if(numbers[i - 1] >= num){
            return false;
        }
    }

    if(i < ns - 1){
        if(num >= numbers[i + 1]){
            return false;
        }
    }

    return true;
}

bool makeIncreasing(vector<int> numbers) {
    bool swapped = false;
    int ns = numbers.size();
    for(int i = 1;i < ns;++i){
        if(numbers[i] <= numbers[i - 1]){
            if(swapped){return false;}

            if(check_valid(swap_digits(numbers[i]), i, numbers)){
                numbers[i] = swap_digits(numbers[i]);
                swapped = true;
                ++i;
            }
            else if(check_valid(swap_digits(numbers[i - 1]), i - 1, numbers)){
                numbers[i - 1] = swap_digits(numbers[i - 1]);
                swapped = true;
            }
            else{
                return false;
            }
        }
    }

    return true;
}

/*

Given a matrix of integers, we'd like to consider the sum of the elements within the area of a 45° rotated rectangle. More formally, the area is bounded by two diagonals parallel to the main diagonal and two diagonals parallel to the secondary diagonal. The dimensions of the rotated rectangle are defined by the number of elements along the borders of the rectangle.

dimensions

Given integers a and b representing the dimensions of the rotated rectangle, and matrix (a matrix of integers), your task is to find the greatest sum of integers contained within an a x b rotated rectangle.

Note: The order of the dimensions is not important - consider all a x b and b x a rectangles.

Example

For

matrix = [[1, 2, 3, 4, 0],
          [5, 6, 7, 8, 1],
          [3, 2, 4, 1, 4],
          [4, 3, 5, 1, 6]]
a = 2, and b = 3, the output should be rotatedRectSum(matrix, a, b) = 36.

example 1

For

matrix = [[-2, 3, 5, -1],
          [4, 3, -10, 10]]
a = 1, and b = 1, the output should be rotatedRectSum(matrix, a, b) = 10.

example 2

The rotated rectangle with dimensions 1x1 is just one element, so the answer is the maximal element in matrix.

For

matrix = [[-2, 3],
          [4, 3]]
a = 1, and b = 2, the output should be rotatedRectSum(matrix, a, b) = 7.

example 3

Input/Output

[execution time limit] 0.5 seconds (cpp)

[input] array.array.integer matrix

A matrix of integers.

Guaranteed constraints:
1 ≤ matrix.length, matrix[i].length ≤ 50,
-10^3 ≤ matrix[i][j] ≤ 10^3.

[input] integer a

The first rotated rectangle dimension.

Guaranteed constraints:
1 ≤ a ≤ 25.

[input] integer b

The second rotated rectangle dimension.
It's guaranteed that at least one rotated rectangle will fit in the given matrix.

Guaranteed constraints:
a ≤ b ≤ 25.

[output] integer

The maximal sum of elements of a rotated rectangle with dimensions a and b.

[C++] Syntax Tips

// Prints help message to the console
// Returns a string
string helloWorld(string name) {
    cout << "This prints to the console when you Run Tests" << endl;
    return "Hello, " + name;
}

已过test case

**/
int m, n;
typedef pair<int, int> point;

bool is_valid(point cur_point){
    if(cur_point.first >= 0 && cur_point.first < m){
        if(cur_point.second >= 0 && cur_point.second < n){
            return true;
        }
    }
    return false;
}

int range_sum(int x, int y, int a, int b, vector<vector<int>>& matrix){
    a = a - 1;
    b = b - 1;

    bool valid = true;
    point up = point(x - a, y + a);
    valid &= is_valid(up);
    point right = point(up.first + b, up.second + b);
    valid &= is_valid(right);
    point bottom = point(x + b, y + b);
    valid &= is_valid(bottom);
    
    if(!valid){return INT32_MIN;}

    point left_2 = point(x, y + 1);
    point up_2 = point(up.first + 1, up.second);
    point right_2 = point(right.first, right.second - 1);
    point bottom_2 = point(bottom.first - 1, bottom.second);

    // cout << x << " " << y << " " << up.first << " " << up.second << endl;
    // another lines
    int res = 0;
    for(int i = x, j = y;i >= up.first, j <= up.second;i -= 1, j += 1){
        for(int k = 0;k <= b;++k){
            res += matrix[i + k][j + k];
        }
    }

    for(int i = left_2.first, j = left_2.second;i >= up_2.first, j <= up_2.second;i -= 1, j += 1){
        for(int k = 0;k <= b - 1;++k){
            res += matrix[i + k][j + k];
        } 
    }

    return res;
}

int rotatedRectSum(vector<vector<int>> matrix, int a, int b) {
    m = matrix.size();
    n = matrix[0].size();
    int max_sum = INT32_MIN;
     
    for(int i = 0;i < m;++i){
        for(int j = 0;j < n;++j){
            max_sum = max(max_sum, range_sum(i, j, a, b, matrix));
            max_sum = max(max_sum, range_sum(i, j, b, a, matrix));
        }
    }

    return max_sum;
}

int main() {
    vector<vector<int>> matrix;
    matrix.push_back(vector<int>({1, 2, 3, 4, 0}));
    matrix.push_back(vector<int>({5, 6, 7, 8, 1}));
    matrix.push_back(vector<int>({3, 2, 4, 1, 4}));
    matrix.push_back(vector<int>({4, 3, 5, 1, 6}));
    cout << rotatedRectSum(matrix, 2, 3) << endl;
}


/*

Your task to check whether it is possible to construct a given array of integers from a bunch of given pieces.

More formally, you are given an array of distinct non-negative integers arr and an array of integer arrays pieces. Your task is to check whether it is possible to arrange the arrays of pieces in such a way that they can be concatenated to form an array equal to arr (containing all the same elements in the same order).

Example

For arr = [1, 2, 5, 3] and pieces = [[5], [1, 2], [3]], the output should be shuffleThePieces(arr, pieces) = true.

The arrays of pieces can be arranged in the order [1, 2], [5], and [3], which would be equal to arr = [1, 2, 5, 3] when concatenated.

For arr = [1, 2, 5, 3, 6] and pieces = [[1, 2], [5], [6, 3]], the output should be shuffleThePieces(arr, pieces) = false.

example

There are no arrangements of pieces that would result in an array equal to arr.

For arr = [1, 5, 4, 3, 2, 8] and pieces = [[4, 3], [1, 5], [2]], the output should be shuffleThePieces(arr, pieces) = false.

Since the sum of the lengths of the arrays of pieces isn't equal to the length of arr, there's no way they could become equal, so the answer is false.

For arr = [1, 5, 4, 3, 2, 8] and pieces = [[1, 5, 5], [3, 2], [8]], the output should be shuffleThePieces(arr, pieces) = false.

Since the elements of arr aren't equal to the elements of the arrays of pieces, there's no way they could become equal, so the answer is false.

Input/Output

[execution time limit] 0.5 seconds (cpp)

[input] array.integer arr

An array of pairwise distinct non-negative integers.

Guaranteed constraints:
1 ≤ arr.length ≤ 105,
0 ≤ arr[i] ≤ 109.

[input] array.array.integer pieces

An array of arrays of non-negative integers. The total count of integers in pieces doesn't exceed 105.

Guaranteed constraints:
1 ≤ pieces.length ≤ 105,
1 ≤ pieces[i].length ≤ 105,
0 ≤ pieces[i][j] ≤ 109.

[output] boolean

Return true if it's possible to rearrange the arrays of pieces and concatenate them, such that the resulting array is equal to arr, otherwise return false.

[C++] Syntax Tips

// Prints help message to the console
// Returns a string
string helloWorld(string name) {
    cout << "This prints to the console when you Run Tests" << endl;
    return "Hello, " + name;
}


**/

class Trie {
public:
    int piece_index;
    bool has_word = false;
    map<int, Trie*> children;

    /** Initialize your data structure here. */
    Trie() {}
    
    /** Inserts a word into the trie. */
    void insert(vector<vector<int>>& pieces, int index) {
        Trie *cur_node = this;
        for(int cint: pieces[index]){
            if(cur_node->children.find(cint) == cur_node->children.end()){
                Trie *nc = new Trie();
                cur_node->children[cint] = nc;
            }
            cur_node = cur_node->children[cint];
        }
        cur_node->has_word = true;
        cur_node->piece_index = index;
    }

    Trie* find_child(int cint){
        Trie *cur_node = this;
        if(cur_node->children.find(cint) == cur_node->children.end()){
            return nullptr;
        }
        cur_node = cur_node->children[cint];
        return cur_node;
    }
};

bool used[100000] = {0};
int ps;
int as;
Trie *root;

bool isValid(int arr_index, vector<int>& arr, vector<vector<int>>& pieces){
    if(arr_index >= as){return true;}

    bool res = false;
    Trie *curn = root;
    int i = arr_index;
    while(true){
        int cur_num = arr[i];
        Trie *nxt = curn->find_child(cur_num);
        if(nxt != nullptr){curn = nxt;}
        else{break;}
        // check if has piece
        if(curn->has_word && !used[curn->piece_index]){
            used[curn->piece_index] = true;
            res |= isValid(i + 1, arr, pieces);
            if(res){break;}
            used[curn->piece_index] = false;
        }

        ++i;
        if(i >= as){
            break;
        }
    }

    return res;
}

bool shuffleThePieces(vector<int> arr, vector<vector<int>> pieces) {
    ps = pieces.size();
    as = arr.size();
    root = new Trie();
    int psum = 0;
    for(int i = 0;i < ps;++i){
        root->insert(pieces, i);
        psum += pieces[i].size();
    }
    if(psum != as){return false;}
    return isValid(0, arr, pieces);
}