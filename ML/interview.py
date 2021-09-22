from sklearn.metrics import roc_auc_score

label = []
for i in range(20):
    label.append(1)

for i in range(80):
    label.append(0)

y1 = []
for i in range(20):
    y1.append(1)

for i in range(80):
    y1.append(0)

roc_auc_score(label, y1)

y2 = []
for i in range(19):
    y2.append(1)

for i in range(81):
    y2.append(0)


y3 = []
for i in range(18):
    y3.append(1)

for i in range(82):
    y3.append(0)


y3 = []
for i in range(23):
    y3.append(1)

for i in range(77):
    y3.append(0)

'''
label 有 20 positive 80 negative 请问AUC的差最小是多少

'''

'''
逻辑回归里面对什么东西是假设线性的
'''

'''
神经网络避免梯度爆炸/缩小 怎么办（batch normalization）
'''

'''
elbow curve计算K-means的中心点数量（已给定elbow curve和阈值epsilon）
'''

'''
计算item之间的user Jaccard相似度来推荐相似物品
'''