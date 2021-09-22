import pandas as pd
import numpy as np
from tqdm import tqdm
import re
import math
import random

rand_prediction = []
rand_label = []

for i in range(1000):
    rand_prediction.append(random.randint(0, 1))
    rand_label.append(random.randint(0, 1))

score_info = {
    "TP": 0,
    "FP": 0,
    "TN": 0,
    "FN": 0,
}

for pred, lab in tqdm(zip(rand_prediction, rand_label)):
    if lab == 1:
        if pred == 1:
            score_info["TP"] += 1
        else:
            score_info["FN"] += 1
    else:
        if pred == 1:
            score_info["FP"] += 1
        else:
            score_info["TN"] += 1

acc = (score_info["TP"] + score_info["TN"]) / 1000
precision = score_info["TP"] / (score_info["TP"] + score_info["FP"])
recall = score_info["TP"] / (score_info["TP"] + score_info["FN"])
F1 = 2 * precision * recall / (precision + recall)

print(acc, precision, recall, F1)
        
    

