import bisect
import sys

ls = [1, 1]
for i in range(2, 51):
    ls.append(ls[i - 1] * i)

for line in sys.stdin:
    st = dict()
    n, k = map(int, line.split())
    for i in range(1, n + 1):
        st[i] = True
    idx = bisect.bisect(ls, k) - 1
    ans = []
    while idx >= 1:
        while idx + 1 < len(st):
            item = next(iter(st))
            ans.append(item)
            st.pop(item)
        divide = k // ls[idx]
        k -= divide * ls[idx]
        item = 1
        for idx, item in enumerate(st):
            if divide == idx:
                ans.append(item)
                st.pop(item)
                break
        idx = bisect.bisect(ls, k) - 1
    for item in st:
        ans.append(item)
    for i in ans:
        print(i, end=' ')
    print()