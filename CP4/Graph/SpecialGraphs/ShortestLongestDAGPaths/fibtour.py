from collections import defaultdict
from collections import deque

n, m = map(int, input().split())
mansions = [int(x) for x in input().split()]
in_degree = [0] * n
d = [0] * n
mp = {0: 1, 1: 1}
MAX = 10 ** 18
AL = defaultdict(list)
one_to_one = False


def fib_generator(a, b, idx):
    if b >= MAX:
        return
    mp[b] = idx
    fib_generator(b, a + b, idx + 1)


fib_generator(1, 2, 2)

for i in range(n):
    if mansions[i] not in mp:
        mp[mansions[i]] = 0

for i in range(m):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    if mp[mansions[a]] == 0 or mp[mansions[b]] == 0:
        continue
    if mp[mansions[a]] == 1 + mp[mansions[b]]:
        AL[b].append(a)
        in_degree[a] += 1
    elif mp[mansions[b]] == 1 + mp[mansions[a]]:
        AL[a].append(b)
        in_degree[b] += 1
    elif mp[mansions[a]] == 1 and mp[mansions[b]] == 1:
        one_to_one = True

queue = deque()
for i in range(n):
    if mp[mansions[i]] > 0 and in_degree[i] == 0:
        d[i] = 1
        if mansions[i] == 1 and one_to_one:
            d[i] = 2
        queue.append(i)

while queue:
    u = queue.popleft()
    for neighbour in AL[u]:
        in_degree[neighbour] -= 1
        if in_degree[neighbour] == 0:
            queue.append(neighbour)
        d[neighbour] = d[u] + 1

print(max(d))
