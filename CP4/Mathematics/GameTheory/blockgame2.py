def gcd(a, b):
    if b > a:
        return gcd(b, a)
    if b == 0:
        return False
    if a // b == 1:
        return not gcd(b, a % b)
    return True


x, y = map(int, input().split())
if gcd(x, y):
    print("win")
else:
    print("lose")
