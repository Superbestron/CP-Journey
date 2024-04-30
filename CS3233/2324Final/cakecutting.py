from fractions import Fraction

rint = lambda: int(input())
rints = lambda: list(map(int, input().strip().split()))

EPS = 1e-9


class Point:
    def __init__(self, x=0, y=0): self.x = x; self.y = y
    def __lt__(self, o): return self.y < o.y if abs(self.x - o.x) < EPS else self.x < o.x
    def __eq__(self, o): return abs(self.x - o.x) < EPS and abs(self.y - o.y) < EPS
    def __hash__(self): return hash((self.x, self.y))
    def __repr__(self): return f"({self.x}, {self.y})"


class LineSegment:
    def __init__(self, p1, p2): self.p1 = p1; self.p2 = p2
    def __eq__(self, o): return self.p1 == o.p1 and self.p2 == o.p2
    def __hash__(self): return hash((self.p1, self.p2))


def orientation(p, q, r):  # 1 if r is clockwise, 2 if r is counterclockwise, 0 if collinear, of pq
    pq = (q.y - p.y) * (r.x - q.x)
    rq = (r.y - q.y) * (q.x - p.x)
    if abs(pq - rq) < 1e-9: return 0  # Collinear
    return 1 if pq > rq else 2  # Clockwise or Counterclockwise


def on_segment(p, q, r):  # Check if point q is in bounding box of p and r
    return max(p.x, r.x) >= q.x >= min(p.x, r.x) and max(p.y, r.y) >= q.y >= min(p.y, r.y)


# if 1 intersection, return 1 and Point
# if infinite intersections, return -1 and LineSegment
# if no intersection, return 0 and None
def intersect(p1, q1, p2, q2):
    if p1 == q1:  # line segment 1 is a point
        if p2 == q2:  # line segment 2 is a point
            if p1 == p2:
                return 1, Point(p1.x, p1.y)  # same point
            else:
                return 0, None  # different points
        else:
            if orientation(p2, q2, p1) == 0:  # collinear
                if on_segment(p2, p1, q2):
                    return 1, Point(p1.x, p1.y)  # p1 is on line 2
                else:
                    return 0, None  # p1 is not on line 2
            else:
                return 0, None  # not collinear

    if p2 == q2:  # line segment 2 is a point, line segment 1 is not a point
        if orientation(p1, q1, p2) == 0:  # collinear
            if on_segment(p1, p2, q1):
                return 1, Point(p2.x, p2.y)  # p2 is on line 1
            else:
                return 0, None  # p2 is not on line 1
        else:
            return 0, None  # not collinear

    o1 = orientation(p1, p2, q1)
    o2 = orientation(p1, q2, q1)
    o3 = orientation(p2, p1, q2)
    o4 = orientation(p2, q1, q2)

    x1, y1 = p1.x, p1.y
    x2, y2 = q1.x, q1.y
    x3, y3 = p2.x, p2.y
    x4, y4 = q2.x, q2.y

    if (y2 - y1) * (x4 - x3) == (y4 - y3) * (x2 - x1):  # Parallel
        if o1 == 0:  # all 0 -> collinear
            # One segment is totally in the other
            if on_segment(p2, p1, q2) and on_segment(p2, q1, q2): return -1, LineSegment(p1, q1)
            if on_segment(p1, p2, q1) and on_segment(p1, q2, q1): return -1, LineSegment(p2, q2)

            # Both segments are disjoint
            if not on_segment(p1, p2, q1) and not on_segment(p1, q2, q1): return (0, None)  # line 2 not touching line 1

            # One segment is touching the other
            if on_segment(p2, p1, q2):  # line 1 is touching line 2
                if p1 == p2 or p1 == q2:
                    return 1, p1  # p1 is a line 2 point
                else:  # p1 in line 2, is p2 or q2 in line 1?
                    if on_segment(p1, p2, q1):
                        return -1, LineSegment(p1, p2)  # q2 ... p1 ... p2 ... q1
                    else:
                        return -1, LineSegment(p1, q2)  # q1 ... q2 ... p1 ... p2, on_segment(p1, q2, q1)

            if on_segment(p2, q1, q2):
                if q1 == p2 or q1 == q2:
                    return 1, q1  # q1 is a line 2 point
                else:  # q1 in line 2, is p2 or q2 in line 1?
                    if on_segment(p1, p2, q1):
                        return -1, LineSegment(p2, q1)  # p1 ... p2 ... q1 ... q2
                    else:
                        return -1, LineSegment(q1, q2)  # p2 ... q1 ... q2 ... p1, on_segment(q1, q2, p1)

        else:
            return 0, None

    if o1 != o2 and o3 != o4:  # Segments intersect at one point
        x_num = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4))
        y_num = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4))
        denom = ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))

        # Calculate intersection point using Fraction
        x_intersect = Fraction(x_num, denom)
        y_intersect = Fraction(y_num, denom)
        return 1, Point(x_intersect, y_intersect)
    return 0, None


n = rint()
segs = []
for _ in range(n):
    x1, y1, x2, y2 = rints()
    p1 = Point(x1, y1)
    p2 = Point(x2, y2)
    segs.append((p1, p2))
ans = 1
for i in range(n):
    intersections = set()
    x1, y1 = segs[i]
    for j in range(i):
        x2, y2 = segs[j]
        res, pt = intersect(x1, y1, x2, y2)
        if res == 1 and pt not in (x1, y1, x2, y2):
            intersections.add(pt)
    ans += len(intersections) + 1
print(ans)
