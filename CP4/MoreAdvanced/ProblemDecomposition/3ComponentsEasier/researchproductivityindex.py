from functools import lru_cache

n = int(input())
ls = [*map(int, input().split())]
ls = [i / 100 for i in ls]

ls = sorted(ls, reverse=True)
ans = 0

for sz, elem in enumerate(ls):
    @lru_cache
    def f(idx, val):
        if idx == sz + 1:
            if val == 0:
                return 0
            return val ** (val / (sz + 1))
        return ls[idx] * f(idx + 1, val + 1) + (1 - ls[idx]) * f(idx + 1, val)
    ans = max(ans, f(0, 0))

print(ans)
