struct Point {
    long long x, y;
};

bool operator < (const Point & a, const Point & b) {
    return ii(a.x, a.y) < ii(b.x, b.y); 
}

ostream & operator << (ostream & out, const Point& a) {
    out << "(" << a.x << ", " << a.y << ")";
    return out;
}

istream & operator >> (istream & is, Point& a) {
    is >> a.x >> a.y;
    return is;
}

// A -> B -> C form counterclockwise direction
bool ccw(const Point &A, const Point &B, const Point &C) {
    return (B.x - A.x) * (C.y - A.y) - 1LL * (C.x - A.x) * (B.y - A.y) > 0;
}

// CONVEX HULL (CLOCKWISE)
// Source: from VNOI Wiki with small modification
// for speed might change to vector<Point>& p
vector<Point> convexHull(vector<Point> p) {
    int n = p.size();

    if (n < 3) {
        // cannot form convex hull
        return vector<Point>();
    }

    // SORT POINTS
    sort(p.begin(), p.end(), [](const Point &A, const Point &B) {
        if (A.x != B.x) return A.x < B.x;
        return A.y < B.y;
    });

    vector<Point> hull;
    hull.push_back(p[0]);

    // UPPER HULL
    for (int i = 1; i < n; ++i) {
        while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), p[i])) {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }

    // LOWER HULL
    for (int i = n - 2; i >= 0; --i) {
        while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), p[i])) {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }

    // REMOVE 1 OVERLAPPING
    if (n > 1) hull.pop_back();

    return hull;
}