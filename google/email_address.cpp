#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

/***
 * Every valid email consists of a local name and a domain name, separated by the '@' sign. Besides lowercase letters, the email may contain one or more '.' or '+'.

For example, in "alice@leetcode.com", "alice" is the local name, and "leetcode.com" is the domain name.
If you add periods '.' between some characters in the local name part of an email address, mail sent there will be forwarded to the same address without dots in the local name. Note that this rule does not apply to domain names.

For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward to the same email address.
If you add a plus '+' in the local name, everything after the first plus sign will be ignored. This allows certain emails to be filtered. Note that this rule does not apply to domain names.

For example, "m.y+name@email.com" will be forwarded to "my@email.com".
It is possible to use both of these rules at the same time.

Given an array of strings emails where we send one email to each email[i], return the number of different addresses that actually receive mails.

 

Example 1:

Input: emails = ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
Output: 2
Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive mails.
Example 2:

Input: emails = ["a@leetcode.com","b@leetcode.com","c@leetcode.com"]
Output: 3
 

Constraints:

1 <= emails.length <= 100
1 <= emails[i].length <= 100
email[i] consist of lowercase English letters, '+', '.' and '@'.
Each emails[i] contains exactly one '@' character.
All local and domain names are non-empty.
Local names do not start with a '+' character.
 * 
 * 
 * 
 * 基本思路：分割字符串
 * C++不像python有split和re.sub，要自己写
 * 在处理完字符串后local name和domain name要重新拼接起来并且用@连接
 * 
 * 
 * 
 * **/

class Solution {

    vector<string> tokenize(string s, string del = " "){
        int start = 0;
        int end = s.find(del);
        vector<string> all_substr;
        while (end != -1) {
            all_substr.push_back(s.substr(start, end - start));
            start = end + del.size();
            end = s.find(del, start);
        }
        all_substr.push_back(s.substr(start, end - start));
        return all_substr;
    }

    string sub_char(string s, string chars){
        for (char c: chars){
            s.erase(std::remove(s.begin(), s.end(), c), s.end());
        }
        return s;
    }

public:
    int numUniqueEmails(vector<string>& emails) {
        set<string> final_address;
        for(string cur_s: emails){
            vector<string> arr = tokenize(cur_s, "@");
            //local name in index 0 domain name in index 1
            vector<string> valid_local = tokenize(arr[0], "+");
            //valid local index is 0
            string final_valid = sub_char(valid_local[0], ".");
            string final_name = final_valid + "@" + arr[1];
            final_address.insert(final_name);
        }
        return final_address.size();
    }
};