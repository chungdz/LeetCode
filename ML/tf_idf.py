import pandas as pd
import numpy as np
from tqdm import tqdm
import re
import math

punctuation = '!,;:?"\''
def removePunctuation(text):
    text = re.sub(r'[{}]+'.format(punctuation),'',text)
    return text.strip().lower()


x = open('tf_idf.txt', 'r', encoding='utf-8')
arr = x.readlines()
word_info = {}
line_tf_idf = []

index = 0
for line in tqdm(arr, desc='Scan sentences', total=len(arr)):

    cline = removePunctuation(line)
    words = cline.split()
    if(len(words) < 1):
        continue
    line_tf_idf.append(words)

    for w in words:
        if w not in word_info:
            word_info[w] = {
                "total": set(),
                "line_info": {
                    index: 1
                }
            }
        elif index not in word_info[w]["line_info"]:
            word_info[w]["line_info"][index] = 1
        else:
              word_info[w]["line_info"][index] += 1
    
        word_info[w]["total"].add(index)
    
    index += 1

for k, v in tqdm(word_info.items(), desc="word idf", total=len(word_info)):
    v["idf"] = math.log(len(arr) / (len(line_tf_idf) + 1))

tf_idf = []
for index, words in tqdm(enumerate(line_tf_idf), desc='td idf', total=len(line_tf_idf)):

    cur_arr = []
    cur_len = len(words)
    for w in words:
        wtf = word_info[w]["line_info"][index] / cur_len
        wtf_idf = wtf * word_info[w]["idf"]
        cur_arr.append(wtf_idf)
    tf_idf.append(cur_arr)

print(tf_idf)
            
