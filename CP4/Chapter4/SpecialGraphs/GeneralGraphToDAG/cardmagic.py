from collections import deque

MOD = 10 ** 9 + 9

N, K, T = map(int, input().split())

paths = [[0 for i in range(N)] for j in range(T + 1)]
visited = [[False for i in range(N)] for j in range(T + 1)]
queue = deque()
for i in range(1, K + 1):
    if T - i >= 0:
        paths[T - i][0] = 1
        queue.append((T - i, 0))


while queue:
    left, idx = queue.popleft()
    if idx == N - 1:
        continue
    for i in range(1, K + 1):
        if left - i < 0:
            break
        if not visited[left - i][idx + 1]:
            queue.append((left - i, idx + 1))
        visited[left - i][idx + 1] = True
        paths[left - i][idx + 1] = (paths[left][idx] + paths[left - i][idx + 1]) % MOD

print(paths[0][N - 1])
