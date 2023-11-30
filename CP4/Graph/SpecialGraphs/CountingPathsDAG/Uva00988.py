import sys
from collections import deque

first = True
for line in sys.stdin:
    if first:
        first = False
    else:
        line = input()
        print()
    n = int(line)
    AL = [[] for i in range(n)]
    in_deg = [0 for i in range(n)]
    num = [0 for i in range(n)]
    num[0] = 1
    end = set()
    for i in range(n):
        ls = [*map(int, input().split())]
        if ls[0] == 0:
            end.add(i)
        ls = ls[1:]
        for j in ls:
            AL[i].append(j)
            in_deg[j] += 1
    q = deque()
    for idx, val in enumerate(in_deg):
        if val == 0:
            q.append(val)
    while q:
        u = q.popleft()
        for v in AL[u]:
            in_deg[v] -= 1
            num[v] += num[u]
            if in_deg[v] == 0:
                q.append(v)

    ans = 0
    for idx, val in enumerate(num):
        if idx in end:
            ans += val
    print(ans)
