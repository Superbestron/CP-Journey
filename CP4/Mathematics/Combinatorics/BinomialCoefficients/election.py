from functools import lru_cache

T = int(input())
EPS = 1e-12


@lru_cache(maxsize=None)
def comb(n, r):
    if r == 0 or r == n: return 1
    return comb(n - 1, r - 1) + comb(n - 1, r)


def binomcdf(n, p, x):
    return sum([comb(n, i) * p ** i * (1 - p) ** (n - i) for i in range(x + 1)])


for _ in range(T):
    n, v1, v2, w = map(int, input().split())
    min_to_win = n // 2 + 1
    if v2 >= min_to_win:
        print("RECOUNT!")
        continue
    if v1 >= min_to_win:
        print("GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!")
        continue

    trials = n - v1 - v2
    if trials + v1 < min_to_win:
        print("RECOUNT!")
        continue
    p_win = 1 - binomcdf(trials, 0.5, min_to_win - v1 - 1)
    p_win *= 100
    if p_win - w > EPS:
        print("GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!")
    else:
        print("PATIENCE, EVERYONE!")
