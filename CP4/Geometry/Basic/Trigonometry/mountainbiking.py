import math

N, g = map(float, input().split())
N = int(N)

ls = []
for i in range(N):
    d_i, tetha_i = map(int, input().split())
    ls.append((d_i, tetha_i))

for i in range(N):
    curr_v2 = 0
    for j in range(i, N):
        length, tetha_i = ls[j]
        curr_v2 = curr_v2 + 2 * g * math.cos(tetha_i / 180 * math.pi) * length
    print(math.sqrt(curr_v2))
