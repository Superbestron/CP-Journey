import math
from collections import deque

N = int(input())
AL = [[] for i in range(N)]
in_degree = [0] * N
for i in range(N - 1):
    A, B, X, T = map(int, input().split())
    A -= 1
    B -= 1
    AL[B].append((A, X, T))
    in_degree[A] += 1

start = [int(x) if int(x) != -1 else 0 for x in input().split()]

q = deque()
for i in range(N):
    if in_degree[i] == 0:
        q.append(i)

while q:
    u = q.popleft()
    for v, x, t in AL[u]:
        in_degree[v] -= 1
        if in_degree[v] == 0:
            q.append(v)
        if t == 1:
            start[v] = max(start[v], (100 / x) * math.sqrt(start[u]))
        else:
            start[v] = max(start[v], (100 / x) * start[u])
print(start[0])
