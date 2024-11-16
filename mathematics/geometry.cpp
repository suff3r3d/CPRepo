#define pt pair<long long, long long>
#define x first
#define y second

struct Line {
    pt a, ab;
    Line(pt _a, pt _ab): a(_a), ab(_ab) {}
};

pt operator - (const pt& a, const pt& b) {return make_pair(a.x - b.x, a.y - b.y);}
ll operator * (const pt& a, const pt& b) {return a.x*b.x + a.y*b.y;}
ll operator ^ (const pt& a, const pt& b) {return a.x*b.y - a.y*b.x;}

pt refine(pt a) { // only for pt = pair<ll, ll>
    ll g = gcd(a.x, a.y);
    if (!g) return a;
    if (g < 0) g = -g;
    a.x /= g, a.y /= g;
    return a;
}

int dir(pt a, pt b, pt c) { // a -> b -> c
    ll x = (b - a) ^ (c - a);
    if (x == 0) return 0; // colinear
    else if (x > 0) return 1; // counterclockwise
    else return -1; // clockwise
}
