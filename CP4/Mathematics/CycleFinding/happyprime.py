def f(num):
    sum = 0
    for idx, x in enumerate(num):
        x = int(x)
        sum += x * x
    return str(sum)


def isPrime(string):
    n = int(string)
    if n == 1:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True


P = int(input())
for i in range(P):
    K, m = [*input().split()]
    st = set()
    if not isPrime(m):
        print(K, m, "NO")
        continue
    isHappyPrime = False
    num = m
    while num not in st:
        st.add(num)
        num = f(num)
        if num == "1":
            isHappyPrime = True
            break

    print(K, m, "YES" if isHappyPrime else "NO")
