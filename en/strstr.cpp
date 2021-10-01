#include<algorithm>
#include<string>
#include<vector>
using namespace std;

/*
28 Implement strStr()

Implement strStr().

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Clarification:

What should we return when needle is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().

 

Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1
Example 3:

Input: haystack = "", needle = ""
Output: 0
 

Constraints:

0 <= haystack.length, needle.length <= 5 * 10^4
haystack and needle consist of only lower-case English characters.

基本思想

KMP的实现

**/

vector<int> getNext(string pattern)
{
    vector<int> next;
	next.push_back(-1);
	int i = 0, j = -1;
    int sl = pattern.size();

	while (i < sl)
	{
		if (j == -1 || pattern[i] == pattern[j])
		{
			++i;
			++j;
			next.push_back(j);
		}	
		else
			j = next[j];
	}
    return next;
}

class Solution {
public:
    int strStr(string haystack, string needle) {
        int i = 0; 
	    int j = 0;

        int hs = haystack.size();
        int ns = needle.size();

        vector<int> next = getNext(needle);
        while(i < hs && j < ns){
            if(j == -1 || haystack[i] == needle[j]){
                ++i;
                ++j;
            }
            else{
                j = next[j];
            }
        }

        if(j == ns){
            return i - j;
        }
        else{
            return -1;
        }
    }
};