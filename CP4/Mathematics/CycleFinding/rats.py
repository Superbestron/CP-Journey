from functools import lru_cache

P = int(input())


@lru_cache(maxsize=None)
def f(x):
    string = str(x)
    reversed = string[::-1]
    x += int(reversed)
    sum = str(x)
    sum = sorted(sum)
    c = ''.join(sum)
    return int(c)


def is_creeper(x):
    string = str(x)
    if string.startswith("1233") and string.endswith("4444"):
        string = string[4:-4]
        return all(c == '3' for c in string)
    elif string.startswith("5566") and string.endswith("7777"):
        string = string[4:-4]
        return all(c == '6' for c in string)


for i in range(0, P):
    K, M, L = map(int, input().split())
    print(K, end=' ')
    if is_creeper(L):
        print(f"C {1}")
        continue
    dict = set()
    dict.add(str(L))
    creeper = False
    cycle = False
    idx = -1
    for j in range(M - 1):
        L = f(L)
        if is_creeper(L):
            creeper = True
            idx = j + 2
            break
        elif dict.__contains__(str(L)):
            cycle = True
            idx = j + 2
            break
        dict.add(str(L))
    if creeper:
        print(f"C {idx}")
    elif cycle:
        print(f"R {idx}")
    else:
        print(L)
