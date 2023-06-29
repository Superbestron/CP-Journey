from collections import deque

R, K = map(int, input().split())
arr = [[-2 for i in range(2 * R - 1)] for j in range(2 * R - 1)]
directions = [[1, 0], [1, 1], [0, 1], [-1, 0], [-1, -1], [0, -1]]
houses = [int(x) for x in input().split()]
mp = {}

# Build Grid
counter = 1
for i in range(R):
    for j in range(R + i):
        arr[i][j] = -2
        mp[counter] = (i, j)
        counter += 1
for i in range(R, 2 * R - 1):
    for j in range(i - R + 1, 2 * R - 1):
        arr[i][j] = -2
        mp[counter] = (i, j)
        counter += 1

for house in houses:
    i, j = mp[house]
    arr[i][j] = -1

# increase grid size by 1
for row in arr:
    row.append(0)
    row.insert(0, 0)
arr.append([0] * (2 * R + 1))
arr.insert(0, [0] * (2 * R + 1))

q = deque()
ans = 0

# insert edges
for i in range(2 * R + 1):
    q.append((i, 0))
    q.append((i, 2 * R))
    q.append((0, i))
    q.append((2 * R, i))
q = deque(set(q))

while q:
    x, y = q.popleft()
    for direction in directions:
        new_x, new_y = x + direction[0], y + direction[1]
        if new_x < 0 or new_x == 2 * R + 1 or new_y < 0 or new_y == 2 * R + 1:
            continue
        if arr[new_x][new_y] == -1:
            ans += 1
            continue
        if arr[new_x][new_y] == -2:
            q.append((new_x, new_y))
            arr[new_x][new_y] = 1
print(ans)
