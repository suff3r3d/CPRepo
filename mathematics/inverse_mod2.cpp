vector<Bitsex> inverse(vector<Bitsex> a) {
  int n = int(a.size());
  vector<Bitsex> b(n, Bitsex(n));
  for (int i = 0; i < n; i++) {
    b[i][i] = 1;
  }
  for (int i = 0; i < n; i++) {
    for (int k = i + 1; k < n; k++) {
      if (a[k][i]) {
        swap(a[k], a[i]);
        swap(b[k], b[i]);
        break;
      }
    }
    if (!a[i][i]) {
      return {};
    }
    for (int k = 0; k < n; k++) {
      if (i == k) {
        continue;
      }
      if (a[k][i]) {
        a[k] ^= a[i];
        b[k] ^= b[i];
      }
    }
  }
  return b;
}

bool det(vector<Bitsex> a) {
  int n = int(a.size());
  for (int i = 0; i < n; i++) {
    for (int k = i + 1; k < n; k++) {
      if (a[k][i]) {
        swap(a[k], a[i]);
        break;
      }
    }
    if (!a[i][i]) {
      return 0;
    }
    for (int k = i + 1; k < n; k++) {
      if (a[k][i]) {
        a[k] ^= a[i];
      }
    }
  }
  return 1;
}
