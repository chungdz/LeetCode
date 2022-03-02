'''
362 Design Hit Counter
Design a hit counter which counts the number of hits received in the past 5 minutes (i.e., the past 300 seconds).

Your system should accept a timestamp parameter (in seconds granularity), and you may assume that calls are being made to the system in chronological order (i.e., timestamp is monotonically increasing). Several hits may arrive roughly at the same time.

Implement the HitCounter class:

HitCounter() Initializes the object of the hit counter system.
void hit(int timestamp) Records a hit that happened at timestamp (in seconds). Several hits may happen at the same timestamp.
int getHits(int timestamp) Returns the number of hits in the past 5 minutes from timestamp (i.e., the past 300 seconds).
 

Example 1:

Input
["HitCounter", "hit", "hit", "hit", "getHits", "hit", "getHits", "getHits"]
[[], [1], [2], [3], [4], [300], [300], [301]]
Output
[null, null, null, null, 3, null, 4, 3]

Explanation
HitCounter hitCounter = new HitCounter();
hitCounter.hit(1);       // hit at timestamp 1.
hitCounter.hit(2);       // hit at timestamp 2.
hitCounter.hit(3);       // hit at timestamp 3.
hitCounter.getHits(4);   // get hits at timestamp 4, return 3.
hitCounter.hit(300);     // hit at timestamp 300.
hitCounter.getHits(300); // get hits at timestamp 300, return 4.
hitCounter.getHits(301); // get hits at timestamp 301, return 3.
 

Constraints:

1 <= timestamp <= 2 * 109
All the calls are being made to the system in chronological order (i.e., timestamp is monotonically increasing).
At most 300 calls will be made to hit and getHits.

基本思想

用数组记录timestamp和增加数量
'''


class HitCounter:

    def __init__(self):
        self.hit_list = []
        self.sumc = 0

    def hit(self, timestamp: int) -> None:
        self.sumc += 1
        if len(self.hit_list) < 1 or self.hit_list[-1][0] < timestamp:
            self.hit_list.append([timestamp, 1])
        else:
            self.hit_list[-1][1] += 1
        
        self.update(timestamp)

    def getHits(self, timestamp: int) -> int:
        self.update(timestamp)
        return self.sumc
    
    def update(self, ts):
        mint = ts - 300
        while len(self.hit_list) > 0 and self.hit_list[0][0] <= mint:
            self.sumc -= self.hit_list[0][1]
            self.hit_list.pop(0)
        return
        
