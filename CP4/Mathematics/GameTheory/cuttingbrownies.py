from functools import lru_cache


@lru_cache(maxsize=None)
def f(r, c):
    win = False
    for i in range(1, r // 2 + 1):
        win = win or (not f(c, i) and not f(c, r - i))
    return win


n = int(input())
for i in range(n):
    ls = [*input().split()]
    c, r, isHarry = int(ls[0]), int(ls[1]), ls[2] == "Harry"
    win = f(r, c) if isHarry else f(c, r)
    if isHarry and win:
        print("Harry can win")
    elif isHarry and not win:
        print("Harry cannot win")
    elif win:
        print("Vicky can win")
    else:
        print("Vicky cannot win")
