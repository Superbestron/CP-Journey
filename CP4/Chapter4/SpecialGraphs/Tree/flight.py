import math
from collections import defaultdict, deque

AL = defaultdict(list)
EL = []
removed_edge = (0, 0)
n = int(input())
for i in range(n - 1):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    AL[a].append(b)
    AL[b].append(a)
    EL.append((a, b))

d = [-1 for _ in range(n)]
p = [-1 for _ in range(n)]
min_diam = 1e9
remove_ans = (0, 0)
join_ans = (0, 0)
q = deque()


def bfs(start):
    global d, p, removed_edge
    q.append(start)
    d[start] = 0
    u = 0
    while q:
        u = q.popleft()
        for nbr in AL[u]:
            if d[nbr] != -1:
                continue
            if (u, nbr) == removed_edge or (nbr, u) == removed_edge:
                continue
            d[nbr] = d[u] + 1
            p[nbr] = u
            q.append(nbr)
    return u, d[u]


# For every edge removed, try to connect the 2 centres of the CC
for a, b in EL:
    removed_edge = (a, b)
    d = [-1 for _ in range(n)]
    t1, _ = bfs(a)
    t2, _ = bfs(b)
    d = [-1 for _ in range(n)]
    p = [-1 for _ in range(n)]
    idx1, d1 = bfs(t1)
    idx2, d2 = bfs(t2)
    centre_d1, centre_d2 = math.ceil(d1 / 2), math.ceil(d2 / 2)
    diam = max(centre_d1 + centre_d2 + 1, d1, d2)
    if diam < min_diam:
        remove_ans = (a, b)
        min_diam = diam
        for i in range(centre_d1):
            idx1 = p[idx1]
        for i in range(centre_d2):
            idx2 = p[idx2]
        join_ans = (idx1, idx2)

print(min_diam)
print(remove_ans[0] + 1, remove_ans[1] + 1)
print(join_ans[0] + 1, join_ans[1] + 1)
