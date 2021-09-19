#include<vector>
#include<string>
#include<algorithm>
using namespace std;

/*

843

Guess the Word
This is an interactive problem.

You are given an array of unique strings wordlist where wordlist[i] is 6 letters long, and one word in this list is chosen as secret.

You may call Master.guess(word) to guess a word. The guessed word should have type string and must be from the original list with 6 lowercase letters.

This function returns an integer type, representing the number of exact matches (value and position) of your guess to the secret word. Also, if your guess is not in the given wordlist, it will return -1 instead.

For each test case, you have exactly 10 guesses to guess the word. At the end of any number of calls, if you have made 10 or fewer calls to Master.guess and at least one of these guesses was secret, then you pass the test case.

 

Example 1:

Input: secret = "acckzz", wordlist = ["acckzz","ccbazz","eiowzz","abcczz"], numguesses = 10
Output: You guessed the secret word correctly.
Explanation:
master.guess("aaaaaa") returns -1, because "aaaaaa" is not in wordlist.
master.guess("acckzz") returns 6, because "acckzz" is secret and has all 6 matches.
master.guess("ccbazz") returns 3, because "ccbazz" has 3 matches.
master.guess("eiowzz") returns 2, because "eiowzz" has 2 matches.
master.guess("abcczz") returns 4, because "abcczz" has 4 matches.
We made 5 calls to master.guess and one of them was the secret, so we pass the test case.
Example 2:

Input: secret = "hamada", wordlist = ["hamada","khaled"], numguesses = 10
Output: You guessed the secret word correctly.
 

Constraints:

1 <= wordlist.length <= 100
wordlist[i].length == 6
wordlist[i] consist of lowercase English letters.
All the strings of wordlist are unique.
secret exists in wordlist.
numguesses == 10

暴力搜索 + 剪枝

剪枝1：对每个词做邻接矩阵，adj[i][j]表示两词相同位置数量，当前词是i的情况下，下一个词一定在adj[i][j] = master(i)的j中

剪枝2：对每个词做分析，如果master(i) = 0，那么词i所有位置都是错误的
如果master(i) > 0，如果能确定所有错误词的位置，就能推导出正确字符的位置，反之亦然。排除所有有错误字符或者没有正确字符的词

剪枝3：如果两词语adj[i][j] = master(i) = master(j)，那么正确字符就是他们相同的字符


**/

class Master {
public:
    int guess(string word);
};

class Solution {
    int adj[100][100];
    bool used[100] = {0};
    // 0: no guess
    // 1: do not insert here
    bool word_error_pos[6][26] = {0};
    // do have this character
    char word_guess[6] = {0};
    // wait to get parsed
    vector<pair<string, int>> wqueue;

    int word_len = 6;
    int guess_num = 10;

    int comp(string s1, string s2){
        int scnt = 0;
        for(int i = 0;i < word_len;++i){
            if(s1[i] == s2[i]){
                scnt += 1;
            }
        }
        return scnt;
    }

    // success fetch info or not
    bool fetch_info(string cur_word, int res){
        // from error ch get right ch
        // from right ch get error ch
        if(res == 0){
            for(int i = 0;i < word_len;++i){
                word_error_pos[i][cur_word[i] - 'a'] = true;
            }
            return true;
        }
        // res > 0
        int error_confirm_num = 0;
        int correct_confirm_num = 0;
        for(int i = 0;i < word_len;++i){
            if(word_error_pos[i][cur_word[i] - 'a']){error_confirm_num += 1;}
            else if(cur_word[i] == word_guess[i]){correct_confirm_num += 1;}
        }

        if(error_confirm_num == word_len - res){
            for(int i = 0;i < word_len;++i){
                if(!word_error_pos[i][cur_word[i] - 'a']){word_guess[i] = cur_word[i];}
            }
            return true;
        }
        else if(correct_confirm_num == res){
            for(int i = 0;i < word_len;++i){
                if(!cur_word[i] == word_guess[i]){word_error_pos[i][cur_word[i] - 'a'] = true;}
            }
            return true;
        }
        return false;
    }

    void parse(string cur_word, int res){
        if(fetch_info(cur_word, res)){
            int qs = wqueue.size();
            for(int i = qs - 1;i >= 0;--i){
                if(fetch_info(wqueue[i].first, wqueue[i].second)){
                    swap(wqueue[qs - 1], wqueue[i]);
                    wqueue.pop_back();
                }
            }
        }
        else{
            wqueue.push_back(pair<string, int>(cur_word, res));
        }
    }

    bool isValid(string cur_word){
        for(int i = 0;i < word_len;++i){
            if(word_error_pos[i][cur_word[i] - 'a']){return false;}
            else if(word_guess[i] != 0 && cur_word[i] != word_guess[i]){return false;}
        }
        return true;
    }
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        int ws = wordlist.size();
        if(ws < 2){
            master.guess(wordlist[0]);
            return;
        }

        for(int i = 0;i < ws - 1;++i){
                adj[i][i] = word_len;
            for(int j = i + 1;j < ws;++j){
                int scnt = comp(wordlist[i], wordlist[j]);
                adj[i][j] = scnt;
                adj[j][i] = scnt;
            }
        }

        int cur_guess = 0;
        int pre_guess = -1;
        int pre_res = -1;
        while(guess_num--){
            int res = master.guess(wordlist[cur_guess]);
            parse(wordlist[cur_guess], res);
            used[cur_guess] = true;

            if(res == word_len){break;}
            // if less than previous, return to previous
            if(res < pre_res){
                cur_guess = pre_guess;
                res = pre_res;
            }
            else if(res == pre_res && adj[cur_guess][pre_guess] == res){
                for(int i = 0;i < word_len;++i){
                    if(wordlist[cur_guess][i] == wordlist[pre_guess][i]){word_guess[i] = wordlist[cur_guess][i];}
                }
            }

            int nxt_guess = -1;
            for(int k = 0;k < ws;++k){
                if(used[k]){
                    continue;
                }
                else if(adj[cur_guess][k] == res){
                    if(isValid(wordlist[k])){nxt_guess = k;}
                    else{
                        used[k] = true;
                        continue;
                    }
                }
            }
            if(nxt_guess == -1){
                for(int k = 0;k < ws;++k){
                    if(!used[k]){
                        if(isValid(wordlist[k])){nxt_guess = k;}
                        else{
                            used[k] = true;
                            continue;
                        }
                    }
                }
                pre_guess = -1;
                pre_res = -1;
                cur_guess = nxt_guess;
            }
            else{
                pre_guess = cur_guess;
                pre_res = res;
                cur_guess = nxt_guess;
            } 
        }
    }
};