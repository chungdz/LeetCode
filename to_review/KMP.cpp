#include<algorithm>
#include<string>
#include<vector>
using namespace std;

/*
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