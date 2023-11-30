import math

M, N, R = map(float, input().split())
ax, ay, bx, by = map(int, input().split())

min_y = min(ay, by)

ans = 1e9
for y in range(0, min_y + 1):
    ans = min(ans, (abs(ax - bx) / M) * (y / N) * R * math.pi + (min_y - y) * 2 / N * R)
ans += abs(ay - by) / N * R
print(ans)
