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
#include <regex>
using namespace std;

/*

You are given an array A representing heights of students. All the students are asked to stand in rows. The students arrive by one, sequentially (as their heights appear in A). For the i-th student, if there is a row in which all the students are taller than A[i], the student will stand in one of such rows. If there is no such row, the student will create a new row. Your task is to find the minimum number of rows created.


Write a function that, given a non-empty array A containing N integers, denoting the heights of the students, returns the minimum number of rows created.


For example, given A = [5, 4, 3, 6, 1], the function should return 2.


Students will arrive in sequential order from A[0] to A[N−1]. So, the first student will have height = 5, the second student will have height = 4, and so on.


For the first student, there is no row, so the student will create a new row.


Row1 = [5]

For the second student, all the students in Row1 have height greater than 4. So, the student will stand in Row1.


Row1 = [5, 4]

Similarly, for the third student, all the students in Row1 have height greater than 3. So, the student will stand in Row1.


Row1 = [5, 4, 3]

For the fourth student, there is no row in which all the students have height greater than 6. So, the student will create a new row.


Row1 = [5, 4, 3]

Row2 = [6]

For the fifth student, all the students in Row1 and Row2 have height greater than 1. So, the student can stand in either of the two rows.


Row1 = [5, 4, 3, 1]

Row2 = [6]

Since two rows are created, the function should return 2.


Assume that:


N is an integer within the range [1..1,000]

each element of array A is an integer within the range [1..10,000]


In your solution, focus on correctness. The performance of your solution will not be the focus of the assessment


**/

vector<int> lines;

int solution(vector<int> A)
{
    // Your solution goes here.
    for(int student: A){
        auto it = upper_bound(lines.begin(), lines.end(), student);
        if(it != lines.end()){
            lines.erase(it);
            it = lower_bound(lines.begin(), lines.end(), student);
            lines.insert(it, student);
        }
        else{
            lines.push_back(student);
        }
    }
    cerr << lines.size() << endl;
    return lines.size(); 
}

/*
There are some processes that need to be executed. Amount of a load that process causes on a server that runs it, is being represented by a single integer. Total load caused on a server is the sum of the loads of all the processes that run on that server. You have at your disposal two servers, on which mentioned processes can be run. Your goal is to distribute given processes between those two servers in the way that, absolute difference of their loads will be minimized.



Write a function that, given an array A of N integers, of which represents loads caused by successive processes, the function should return the minimum absolute difference of server loads.



For example, given array A such that:

  A[0] = 1

  A[1] = 2

  A[2] = 3

  A[3] = 4

  A[4] = 5



your function should return 1. We can distribute the processes with loads 1, 2, 4 to the first server and 3, 5 to the second one, so that their total loads will be 7 and 8, respectively, and the difference of their loads will be equal to 1.



Assume that:

N is an integer within the range [1..1,000]

the sum of the elements of array A does not exceed 100,000


In your solution, focus on correctness. The performance of your solution will not be the focus of the assessment.

**/

int solution(vector<int> A)
{
    int as = A.size();
    if(as < 2){return A[0];}
    
    sort(A.begin(), A.end(), greater<int>());
    int l1 = A[0];
    int l2 = A[1];
    for(int i = 2;i < as;++i){
        if(l1 < l2){
            l1 += A[i];
        }
        else{
            l2 += A[i];
        }
    }

    // Put your solution here
    cerr << l1 << " " << l2 << endl;
    return abs(l1 - l2); 
}