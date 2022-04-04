
'''
204. Count Primes

Given an integer n, return the number of prime numbers that are strictly less than n.

 

Example 1:

Input: n = 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
Example 2:

Input: n = 0
Output: 0
Example 3:

Input: n = 1
Output: 0
 

Constraints:

0 <= n <= 5 * 10^6
'''


'''
版本一
'''
class Solution:
    def countPrimes(self, n: int) -> int:
        nprime = [True] * (n + 1)
        totalp = 0
        for i in range(2, n):
            if nprime[i]:
                totalp += 1
                new_index = i * i
                while new_index < n:
                    nprime[new_index] = False
                    new_index += i
        return totalp

'''
C++ 可以过且比之前那个快，但是python会超时，可能是乘法和取模速度太慢
'''
class Solution:
    def countPrimes(self, n: int) -> int:
        nprime = [True] * (n + 1)
        primes = []
        for i in range(2, n):
            if nprime[i]:
                primes.append(i)

            for j in range(len(primes)):
                if i * primes[j] >= n:
                    break
                nprime[i * primes[j]] = False
                if i % primes[j] == 0:
                    break

        return len(primes)