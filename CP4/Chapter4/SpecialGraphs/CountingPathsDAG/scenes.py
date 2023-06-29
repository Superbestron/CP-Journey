from collections import deque

MOD = 10 ** 9 + 7

n, w, h = map(int, input().split())

paths = [[0 for i in range(w)] for j in range(n + 1)]
visited = [[False for i in range(w)] for j in range(n + 1)]
queue = deque()
for i in range(h + 1):
    if n - i >= 0:
        paths[n - i][0] = 1
        queue.append((n - i, 0))


while queue:
    left, idx = queue.popleft()
    if idx == w - 1:
        continue
    for i in range(h + 1):
        if left - i < 0:
            continue
        if not visited[left - i][idx + 1]:
            queue.append((left - i, idx + 1))
        visited[left - i][idx + 1] = True
        paths[left - i][idx + 1] = (paths[left][idx] + paths[left - i][idx + 1]) % MOD

sum = 0
for i in range(n + 1):
    sum = (paths[i][w - 1] + sum) % MOD

print((MOD + sum - min(h + 1, (n // w + 1))) % MOD)
