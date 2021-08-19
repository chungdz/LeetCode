#include<string>
#include<vector>
#include<algorithm>
using namespace std;

/**
 * 809
 * 
 * 
 * 
Sometimes people repeat letters to represent extra feeling. For example:

"hello" -> "heeellooo"
"hi" -> "hiiii"
In these strings like "heeellooo", we have groups of adjacent letters that are all the same: "h", "eee", "ll", "ooo".

You are given a string s and an array of query strings words. A query word is stretchy if it can be made to be equal to s by any number of applications of the following extension operation: choose a group consisting of characters c, and add some number of characters c to the group so that the size of the group is three or more.

For example, starting with "hello", we could do an extension on the group "o" to get "hellooo", but we cannot get "helloo" since the group "oo" has a size less than three. Also, we could do another extension like "ll" -> "lllll" to get "helllllooo". If s = "helllllooo", then the query word "hello" would be stretchy because of these two extension operations: query = "hello" -> "hellooo" -> "helllllooo" = s.
Return the number of query strings that are stretchy.

 

Example 1:

Input: s = "heeellooo", words = ["hello", "hi", "helo"]
Output: 1
Explanation: 
We can extend "e" and "o" in the word "hello" to get "heeellooo".
We can't extend "helo" to get "heeellooo" because the group "ll" is not size 3 or more.
Example 2:

Input: s = "zzzzzyyyyy", words = ["zzyy","zy","zyy"]
Output: 3
 

Constraints:

1 <= s.length, words.length <= 100
1 <= words[i].length <= 100
s and words[i] consist of lowercase letters.
 * 
 * 
 * 
 * 基本思路
 * 
 * 逐个比较，判断word是不是合规的，就是把s处理成 字符:数量 的s顺序相同的二元组
 * 
 * 再把word也处理成 字符:数量 的和word顺序相同二元组
 * 
 * 比较的时候，先比较长度，长度必须一致，再比较每个位置字符，字符必须一致
 * 
 * 最后比较数量，s中字符小于3时，数量必须一致，大于3时，word数量必须小于
 * 
 */


class Solution {
    char word_record[100][2];
    char cmp[100][2];
    int string_len;
    int word_len;

    int unique_value(char res[][2], string a){
        int cur_len = a.size();

        int ch_num = 1;
        res[0][0] = a[0];
        int res_index = 0;
        int cur_index = 0;
        int nxt_index;
        while(cur_index < cur_len){
            nxt_index = cur_index + 1;
            while(nxt_index < cur_len){
                if(a[nxt_index] != a[cur_index]){
                    res[res_index][1] = ch_num;
                    res_index += 1;

                    cur_index = nxt_index;
                    res[res_index][0] = a[cur_index];
                    ch_num = 1;

                    break;
                }
                else{
                    ch_num += 1;
                    nxt_index += 1;
                }
            }
            if(nxt_index >= cur_len){
                res[res_index][1] = ch_num;
                res_index += 1;
                break;
            }
        }
        return res_index;
    }

    bool isvalid(){
        if(string_len != word_len){return false;}
        for(int i = 0;i < string_len;++i){
            if(word_record[i][0] != cmp[i][0]){return false;}
            else{
                if(word_record[i][1] < 3 && cmp[i][1] != word_record[i][1]){return false;}
                else if(word_record[i][1] >= 3 && cmp[i][1] > word_record[i][1]){return false;}
            }
        }
        return true;
    }
public:
    int expressiveWords(string s, vector<string>& words) {
        string_len = unique_value(word_record, s);
        int ts = 0;
        for(string cs: words){
            word_len = unique_value(cmp, cs);
            if(isvalid()){ts += 1;}
        }
        return ts;
    }
};