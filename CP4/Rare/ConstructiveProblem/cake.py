p, q, n = map(int, input().split())
AL = [[] for i in range(p)]
for i in range(n):
    r, c = map(int, input().split())
    r -= 1
    c -= 1
    AL[r].append(c)

for i in range(p):
    AL[i].sort()

curr_uncovered_row = 0
ans = []
for i in range(p):
    curr_uncovered_col = 0
    row_covered = False
    for idx in AL[i]:
        ans.append((curr_uncovered_row, curr_uncovered_col, i, idx))
        curr_uncovered_col = idx + 1
        row_covered = True
    if row_covered:
        curr_uncovered_row = i + 1
        # check back
        if ans:
            top_r, top_c, btm_r, btm_c = ans[-1]
            ans.pop()
            ans.append((top_r, top_c, btm_r, q - 1))

for top_r, top_c, btm_r, btm_c in ans:
    if btm_r == curr_uncovered_row - 1:
        print(top_r + 1, top_c + 1, p, btm_c + 1)
    else:
        print(top_r + 1, top_c + 1, btm_r + 1, btm_c + 1)
print(0)
