ls = list(map(int, input().split()))[1:]


def recurse(arr, ctr):
    ctr += 1
    if len(arr) == 1:
        return arr[0] * 2, ctr
    diff = arr[1] - arr[0]
    can = True
    temp = [diff]
    for i in range(2, len(arr)):
        diff_t = arr[i] - arr[i - 1]
        if diff_t != diff:
            can = False
        temp.append(diff_t)
    if can:
        return arr[-1] + diff, ctr
    else:
        nxt, ctr = recurse(temp, ctr)
        return arr[-1] + nxt, ctr


ans, deg = recurse(ls, 0)
print(deg, ans)
