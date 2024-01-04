h0 = int(input())
while True:
    if h0 % 2 == 0:
        if (h0 // 2 * (3 * h0 + 1) % 4) == 0:
            print(h0)
            break
    else:
        if ((3 * h0 + 1) // 2 * h0) % 4 == 0:
            print(h0)
            break
    h0 += 1
