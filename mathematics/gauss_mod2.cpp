// Solve system of linear equations (mod 2)
// Required:
//  - Bitsex
// Time complexity (n^3 / 64)
// Verified:
//  - https://judge.yosupo.jp/problem/system_of_linear_equations_mod_2
// Usage:
//  - solve_linear(A, b, w)
// Find the solution (x) and the basis for Ax = b
// The return is an (r + 1) * w matrix containing
// x_1, x_2, ..., x_w (solution)
// d_11, d_12, ..., d_1w - d_1
// ... (basis)
// d_r1, d_r2, ..., d_rw - d_r

// all solutions = x + c_1 * d_1 + c_2 * d_2 + ... + c_r * d_r (c_i : constant)
vector<Bitsex> solve_linear(vector<Bitsex> a, Bitsex b, int w) {
  int h = a.size();
  if (h > 0) {
    assert((int)a[0].size() == w);
  }
  int r = 0;
  for (int c = 0; c < w; c++) {
    if (r == h) {
      break;
    }
    for (int i = r + 1; i < h; i++) {
      if (a[i][c]) {
        swap(a[i], a[r]);
        if (b[r] != b[i]) {
          b[r] = !b[r];
          b[i] = !b[i];
        }
        break;
      }
    }

    if (!a[r][c]) {
      continue;
    }
    for (int i = 0; i < h; i++) {
      if (i != r && a[i][c]) {
        b[i] = b[i] ^ b[r];
        a[i] ^= a[r];
      }
    }

    r += 1;
  }

  for (int i = r; i < h; i++) {
    if (b[i]) {
      return {};
    }
  }

  vector<Bitsex> res(1, Bitsex(w));

  vector<int> pivot(w, -1);
  int p = 0;
  for (int i = 0; i < r; i++) {
    while (!a[i][p]) {
      p += 1;
    }
    res[0][p] = bool(b[i]);
    pivot[p] = i;
  }

  for (int c = 0; c < w; c++) {
    if (pivot[c] == -1) {
      Bitsex x(w);
      x[c] = 1;
      for (int i = 0; i < c; i++) {
        if (pivot[i] != -1 && a[pivot[i]][c]) {
          x[i] = 1;
        }
      }
      res.push_back(x);
    }
  }
  return res;
}
