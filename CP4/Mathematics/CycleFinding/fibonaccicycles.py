Q = int(input())

a, b, k = 0, 0, 0


def f():
    global a, b, k
    temp = b
    b = (a + b) % k
    a = temp
    return b


for i in range(Q):
    a = b = 1
    s = {}
    k = int(input())
    ctr = 1
    while True:
        num = f()
        ctr += 1
        if num in s:
            print(s[num])
            break
        s[num] = ctr
