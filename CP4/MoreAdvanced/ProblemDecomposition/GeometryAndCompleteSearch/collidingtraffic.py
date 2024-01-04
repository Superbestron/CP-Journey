from math import radians, cos, sin, sqrt, hypot

num_tc = int(input())

for _ in range(num_tc):
    n, r = input().split()
    n = int(n)
    r = float(r)
    boats = [[*map(float, input().split())] for _ in range(n)]

    for i in range(n):
        boats[i][2] = radians(boats[i][2])

    # Equation proof is here:
    # x  = p1.x - p2.x
    # y  = p1.y - p2.y
    # Vx = v1.x - v2.x
    # Vy = v1.y - v2.y
    # r^2 = (p1.x - p2.x)^2 + (p1.y - p2.y)^2
    #     = (x + Vx * t)^2 + (y + Vy * t)^2
    #     = x^2 + 2 * x * Vx * t + Vx^2 * t^2 + y^2 + 2 * y * Vy * t + Vy^2 * t^2
    #     = (Vx^2 + Vy^2) * t^2 + 2 * (x * Vx + y * Vy) * t + x^2 + y^2
    # (Vx^2 + Vy^2) * t^2 + 2 (x * Vx + y * Vy) t + x^2 + y^2 - r^2 = 0

    ans = 1e18
    for i in range(n):
        for j in range(i + 1, n):
            x0, y0, theta0, s0 = boats[i]
            x1, y1, theta1, s1 = boats[j]

            if hypot(x0 - x1, y0 - y1) <= r:
                ans = 0
                break

            dx = x0 - x1
            dy = y0 - y1

            dsx = s0 * sin(theta0) - s1 * sin(theta1)
            dsy = s0 * cos(theta0) - s1 * cos(theta1)

            a = dsx ** 2 + dsy ** 2
            b = 2 * (dx * dsx + dy * dsy)
            c = dx ** 2 + dy ** 2 - r ** 2

            discriminant = b ** 2 - 4 * a * c
            if discriminant < 0 or a == 0:
                continue

            time_to_collide = (-b - sqrt(discriminant)) / (2 * a)

            if time_to_collide <= 0:
                continue
            ans = min(ans, round(time_to_collide))

        if ans == 0:
            break

    if ans == 1e18:
        print("No collision.")
    else:
        print(ans)
