from functools import lru_cache

N = int(input())
for i in range(N):
    R, S, X, Y, W = map(int, input().split())
    success = (S - R + 1) / S
    failure = 1 - success


    @lru_cache(maxsize=None)
    def f(num_roll, num_success):
        if num_roll == Y:
            if num_success >= X:
                return W
            else:
                return 0
        return success * f(num_roll + 1, num_success + 1) + failure * f(num_roll + 1, num_success)
    if f(0, 0) > 1:
        print("yes")
    else:
        print("no")
