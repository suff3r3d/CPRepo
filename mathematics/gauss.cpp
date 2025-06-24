// Solve system of linear equations
// Required:
//  - Bitsex
// Time complexity (n^3)
// Verified:
//  - https://judge.yosupo.jp/problem/system_of_linear_equations
// Usage:
//  - solve_linear(A, b, w)
// Find the solution (x) and the basis for Ax = b
// The return is an (r + 1) * w matrix containing
// x_1, x_2, ..., x_w (solution)
// d_11, d_12, ..., d_1w - d_1
// ... (basis)
// d_r1, d_r2, ..., d_rw - d_r

// all solutions = x + c_1 * d_1 + c_2 * d_2 + ... + c_r * d_r (c_i : constant)
typedef long double ld;
const ld EPS = 1e-9;
template <typename T> bool isZero(T v) {
  if constexpr (is_same_v<T, ld>) {
    return abs(v) < EPS;
  }
  return v == 0;
}
bool notFound = false;
template <typename T>
vector<vector<T>> solve_linear(vector<vector<T>> &a, vector<T> b, int w) {
  int h = (int)a.size();
  if (h > 0) {
    assert((int)a[0].size() == w);
  }
  int r = 0;
  vector<int> used(w);
  vector<int> idxs;
  for (int c = 0; c < w; c++) {
    int id = -1;
    for (int i = r; i < h; i++) {
      if (!isZero(a[i][c])) {
        id = i;
        break;
      }
    }

    if (id == -1) {
      continue;
    }
    if (r != id) {
      swap(a[r], a[id]);
    }
    swap(b[r], b[id]);

    for (int i = r + 1; i < h; i++) {
      if (isZero(a[i][c])) {
        continue;
      }
      T coeff = a[i][c] / a[r][c];
      for (int j = c; j < w; j++) {
        a[i][j] -= coeff * a[r][j];
      }
      b[i] -= coeff * b[r];
    }

    r += 1;
    used[c] = 1;
    idxs.push_back(c);
    if (r == h) {
      break;
    }
  }
  for (int i = r; i < h; i++) {
    if (!isZero(b[i])) {
      return {};
    }
  }
  vector<vector<T>> sols;
  {
    vector<T> v(w);
    for (int i = r - 1; i >= 0; i--) {
      int f = idxs[i];
      v[f] = b[i];
      for (int j = f + 1; j < w; j++) {
        v[f] -= a[i][j] * v[j];
      }
      v[f] /= a[i][f];
    }
    sols.push_back(v);
  }
  for (int c = 0; c < w; c++) {
    if (used[c]) {
      continue;
    }
    vector<T> v(w);
    v[c] = T(1);
    for (int i = r - 1; i >= 0; i--) {
      int f = idxs[i];
      for (int j = f + 1; j < w; j++) {
        v[f] -= a[i][j] * v[j];
      }
      v[f] /= a[i][f];
    }
    sols.push_back(v);
  }
  return sols;
}
