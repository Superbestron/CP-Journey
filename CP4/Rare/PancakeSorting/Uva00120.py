from sys import stdin

for line in stdin:
    s = [int(x) for x in line.split()]
    n = len(s)
    print(line.strip())
    inv = {e: idx for idx, e in enumerate(sorted(s))}
    s = [inv[x] for x in s]
    for i in range(n - 1):
        idx = -1
        for j in range(n):
            if s[j] == n - i - 1:
                idx = j
                break
        if idx == n - i - 1:
            continue
        # Flip to top if not at top
        if idx != 0:
            s = s[:idx + 1][::-1] + s[idx + 1:]
            print(n - idx, end=' ')
        s = s[:n - i][::-1] + s[n - i:]
        print(i + 1, end=' ')
    print(0)
