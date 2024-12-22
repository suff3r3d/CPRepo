// use in Mo algo (the order of segment [l_i, r_i]) (use in extreme cases, works very well)

int hilbertOrder(int x, int y) {
  const int lg = __lg(max(x, y) * 2 + 1) | 1;
  const int maxn = (int(1) << lg) - 1;
  int ret = 0;
  for (int s = int(1) << (lg - 1); s > 0; s >>= 1) {
    bool rx = x & s, ry = y & s;
    ret = (ret << 2) | (rx ? ry ? 2 : 1 : ry ? 3 : 0);
    if (!rx) {
      if (ry) {
        x ^= maxn;
        y ^= maxn;
      }
      swap(x, y);
    }
  }
  return ret;
}
