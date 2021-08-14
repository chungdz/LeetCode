/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

#include <string.h>
#include <vector>
using namespace std;

/***
 * 158
 * 
 * Given a file and assume that you can only read the file using a given method read4, implement a method read to read n characters. Your method read may be called multiple times.

Method read4:

The API read4 reads four consecutive characters from file, then writes those characters into the buffer array buf4.

The return value is the number of actual characters read.

Note that read4() has its own file pointer, much like FILE *fp in C.
 * 
 * 
 * 
 * 
 * 
 * 类的应用，需要在类中设置一个buffer
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
*/



int read4(char *buf4);

class Solution {
    vector<char> inner_buf;
    bool eof = false;
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {

        if(eof && inner_buf.size() <= 0){return 0;}

        int tmp = n;
        char buf4[5];
        while(tmp > 0 && !eof){
            int rn = read4(buf4);
            for(int k = 0;k < rn;++k){
                inner_buf.push_back(buf4[k]);
            }
            if(rn < 4){
                eof = true;
                break;
            }
            tmp -= 4;
        }
        
        int res_size = 0;
        for(int i = 0;i < n;++i){
            if(inner_buf.size() <= 0){break;}
            buf[i] = inner_buf[0];
            ++res_size;
            inner_buf.erase(inner_buf.begin());
        }
        return res_size;
    }
};