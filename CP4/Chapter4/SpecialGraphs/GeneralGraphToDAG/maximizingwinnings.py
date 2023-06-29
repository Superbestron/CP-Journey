while True:
    n = int(input())
    if n == 0:
        break
    arr = [[] for i in range(n)]
    for i in range(n):
        arr[i] = [int(i) for i in input().split()]

    m = int(input())
    memo_max = [[-1 for j in range(n)] for i in range(m)]
    memo_min = [[1e9 for j in range(n)] for i in range(m)]

    for i in range(n):
        memo_min[0][i] = memo_max[0][i] = arr[0][i]  # from room 1 to room (i + 1)
    for k in range(m - 1):
        for i in range(n):  # in room i
            if memo_min[k][i] == 1e9:
                continue
            for j in range(n):
                memo_min[k + 1][j] = min(memo_min[k + 1][j], arr[i][j] + memo_min[k][i])
        for i in range(n):
            if memo_max[k][i] == -1:
                continue
            for j in range(n):
                memo_max[k + 1][j] = max(memo_max[k + 1][j], arr[i][j] + memo_max[k][i])
    print(max(memo_max[m - 1]), min(memo_min[m - 1]))

    