from collections import deque

MOD = 2 ** 31 - 1

n = int(input())
arr = []
for i in range(n):
    arr.append(input())

directions = [[1, 0], [0, 1]]
queue = deque()
queue.append((0, 0))
paths = [[0] * n for i in range(n)]
visited = [[False] * n for i in range(n)]
paths[0][0] = 1
visited[0][0] = True

while queue:
    x, y = queue.popleft()
    for direction in directions:
        new_x = x + direction[0]
        new_y = y + direction[1]
        if new_x < 0 or new_x == n or new_y < 0 or new_y == n:
            continue
        if arr[new_x][new_y] == '#':
            continue
        if not visited[new_x][new_y]:
            queue.append((new_x, new_y))
        visited[new_x][new_y] = True
        paths[new_x][new_y] = (paths[x][y] + paths[new_x][new_y]) % MOD

if paths[n - 1][n - 1] == 0:
    directions = [[1, 0], [0, 1], [-1, 0], [0, -1]]
    queue.append((0, 0))
    visited = [[False] * n for i in range(n)]
    visited[0][0] = True

    while queue:
        x, y = queue.popleft()
        for direction in directions:
            new_x = x + direction[0]
            new_y = y + direction[1]
            if new_x < 0 or new_x == n or new_y < 0 or new_y == n:
                continue
            if arr[new_x][new_y] == '#':
                continue
            if not visited[new_x][new_y]:
                queue.append((new_x, new_y))
            visited[new_x][new_y] = True

    if not visited[n - 1][n - 1]:
        print("INCONCEIVABLE")
    else:
        print("THE GAME IS A LIE")
else:
    print(paths[n - 1][n - 1])