from collections import defaultdict, deque

# Lots of edge cases for this one...
# I'll explain below how to avoid them

AL = defaultdict(list)
c, l = map(int, input().split())
for i in range(l):
    a, b = map(int, input().split())
    AL[a].append(b)
    AL[b].append(a)

queue = deque()
d = [-1 for i in range(c)]
temp = []
diameter_per_cc = []
cc = []

for i in range(c):
    if d[i] != -1:
        continue
    d[i] = 0
    queue.append(i)
    max_idx = -1
    while queue:
        u = queue.popleft()
        max_idx = u
        for nbr in AL[u]:
            if d[nbr] != -1:
                continue
            d[nbr] = d[u] + 1
            queue.append(nbr)
    temp.append(max_idx)

d = [-1 for i in range(c)]
for t in temp:
    queue.append(t)
    d[t] = 0
    max_dist = -1
    while queue:
        u = queue.popleft()
        max_dist = d[u]
        for nbr in AL[u]:
            if d[nbr] != -1:
                continue
            d[nbr] = d[u] + 1
            queue.append(nbr)
    cc.append((max_dist + 1) // 2)
    diameter_per_cc.append(max_dist)
cc.sort(reverse=True)
diameter_per_cc.sort(reverse=True)

# Notice for all, you needed to compare with the maximum diameter of all CCs

if len(cc) == 1:
    print(max(cc[0], diameter_per_cc[0]))
else:  # greedily connect all the CCs (except the largest CC) with the largest CC
    if len(cc) <= 2:
        print(max(cc[0] + cc[1] + 1, diameter_per_cc[0]))
    else:
        print(max(max(cc[0] + cc[1] + 1, cc[1] + cc[2] + 2), diameter_per_cc[0]))
