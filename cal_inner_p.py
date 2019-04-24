#!/usr/bin/env python
import sys
import math 
data_fn = sys.argv[1]
query_fn = sys.argv[2]
data_idx = int(sys.argv[3])
query_idx = int(sys.argv[4])
metric_type = sys.argv[5]

data = []
query = []

cnt = 0
with open(data_fn) as f:
    for aline in f:
        if cnt == data_idx:
            data = [float(x) for x in aline.split(",")]
            break
        cnt += 1

cnt = 0
with open(query_fn) as f:
    for aline in f:
        if cnt == query_idx:
            query = [float(x) for x in aline.split(",")]
            break
        cnt += 1
if metric_type == "ip":
    print sum([x * y for (x, y) in zip(query, data)])
else:
    print math.sqrt(sum([(x - y) ** 2 for (x, y) in zip(query, data)]))
    print sum([(x - y) ** 2 for (x, y) in zip(query, data)])
