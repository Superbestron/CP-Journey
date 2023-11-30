import sys

INF = 1000

for line in sys.stdin:
    w, h = map(int, line.split())
    n = int(input())
    arr = [[-1 for _ in range(h + 1)] for _ in range(w + 1)]
    freq = [0 for _ in range(n)]
    dict = {}
    for i in range(n):
        ls = input().split()
        dict[i] = ls[0]
        ls = [int(i) for i in ls[1:]]
        for j in range(ls[0], ls[2]):
            for k in range(ls[1], ls[3]):
                if arr[j][k] != -1:
                    arr[j][k] = INF
                else:
                    arr[j][k] = i

    unallocated = 0
    contested = 0
    for i in range(w):
        for j in range(h):
            if arr[i][j] == -1:
                unallocated += 1
            elif arr[i][j] == INF:
                contested += 1
            else:
                freq[arr[i][j]] += 1

    print(f"Total {h * w}")
    print(f"Unallocated {unallocated}")
    print(f"Contested {contested}")
    for i in range(n):
        print(f"{dict[i]} {freq[i]}")
    print()
    