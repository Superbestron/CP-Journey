from functools import lru_cache

s = input()


@lru_cache(maxsize=None)
def dp(l, r):
    length = r - l
    substr = s[l:r]
    for i in range(1, (length // 2) + 1):
        if length % i == 0:
            if s[l:l + i] * (length // i) == substr:
                return dp(l, l + i)
    ans = length
    for i in range(l + 1, r):
        ans = min(ans, dp(l, i) + dp(i, r))
    return ans


print(dp(0, len(s)))
