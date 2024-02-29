from collections import deque

directions = [(0, 1), (1, 0), (-1, 0), (0, -1)]

h, w, s = map(int, input().split())
v = [input().strip() for _ in range(h)]

start, end = None, None
for i in range(h):
    for j in range(w):
        if v[i][j] == '@':
            start = (i, j)
        elif v[i][j] == '$':
            end = (i, j)

queue = deque([start])
dist = [[-1] * w for _ in range(h)]
dist[start[0]][start[1]] = 0

while queue:
    x, y = queue.popleft()
    for d in directions:
        new_x, new_y = x + d[0], y + d[1]
        if not (0 <= new_x < h and 0 <= new_y < w):
            continue
        if v[new_x][new_y] != '.' and v[new_x][new_y] != '$':
            continue
        if dist[new_x][new_y] != -1:
            continue
        dist[new_x][new_y] = dist[x][y] + 1
        queue.append((new_x, new_y))

print(f"Your destination will arrive in {s * dist[end[0]][end[1]]} meters")
