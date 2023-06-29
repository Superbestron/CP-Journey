from collections import deque

R, N, A, B, X = map(int, input().split())
arr = [[-2 for i in range(2 * R - 1)] for j in range(2 * R - 1)]
directions = [[1, 0], [1, 1], [0, 1], [-1, 0], [-1, -1], [0, -1]]
cells = map(int, input().split())
mp = {}

# Build Grid
counter = 1
for i in range(R):
    for j in range(R + i):
        arr[i][j] = -1
        mp[counter] = (i, j)
        counter += 1
for i in range(R, 2 * R - 1):
    for j in range(i - R + 1, 2 * R - 1):
        arr[i][j] = -1
        mp[counter] = (i, j)
        counter += 1

for cell in cells:
    i, j = mp[cell]
    arr[i][j] = -2

q = deque()
q.append(mp[A])
src_x, src_y = mp[A]
arr[src_x][src_y] = 0
dest_x, dest_y = mp[B]

while q:
    x, y = q.popleft()
    for direction in directions:
        new_x, new_y = x + direction[0], y + direction[1]
        if new_x < 0 or new_x == 2 * R - 1 or new_y < 0 or new_y == 2 * R - 1:
            continue
        if arr[new_x][new_y] == -2:
            continue
        if arr[new_x][new_y] == -1:
            arr[new_x][new_y] = arr[x][y] + 1
            if new_x == dest_x and new_y == dest_y:
                break
            q.append((new_x, new_y))

if arr[dest_x][dest_y] < 0 or arr[dest_x][dest_y] > N:
    print("No")
else:
    print(arr[dest_x][dest_y])
