#!/usr/bin/env python
import sys
import heapq
data_fn = sys.argv[1]
query_fn = sys.argv[2]
query_start = int(sys.argv[3])
query_end = int(sys.argv[4])
top_cnt = int(sys.argv[5])
query_list = []
data_list = []
def cal_ip(a, b):
    return sum([x*y for x, y in zip(a, b)])
with open(data_fn) as f:
    for aline in f:
        fields = aline.split(",")
        data_list.append([float(x) for x in fields])
print "loaded data {}".format(len(data_list))
cnt = 0
with open(query_fn) as f:
    for aline in f:
        if cnt < query_start:
            cnt += 1
        elif cnt >= query_start and cnt <= query_end:
            fields = aline.split(",")
            query_list.append([float(x) for x in fields])
            cnt += 1
        else:
            break
print "loaded query {}".format(len(query_list))
cnt = 0
for a_query in query_list:
    h = []
    for i in range(len(data_list)):
        ip_v = cal_ip(a_query, data_list[i])
        if len(h) < top_cnt:
            heapq.heappush(h, (ip_v, i))
        else:
            heapq.heappushpop(h, (ip_v, i))
    ret = heapq.nlargest(top_cnt, h)
    ret_str = "{}".format(cnt)
    for a in ret:
        ret_str += "\t{}\t{}".format(a[1], a[0])
    print ret_str
    cnt += 1
