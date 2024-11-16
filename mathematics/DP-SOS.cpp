/**
 * Usage: 
 * subset[x]: number of element which is submask of x
 * superset[x]: number of element which is superset of x
 * Common heuristic:
 * Number of element y such that x | y = x => y is subset of x
 * Number of element y such that x & y = x => y is superset of x
 * Number of element y such that x & y != 0 => n - subset[((1 << N) - 1) & ~x]
 * a_i >= 10^6 => Change N
 * Tested: https://cses.fi/problemset/task/1654
*/

const int N = 21;
int subset[1 << N], superset[1 << N];

void sum_over_subset() {
    for (int i = 0; i < N; i++) {
        for (int msk = 0; msk < (1 << N); msk++) {
            if (msk >> i & 1)       subset[msk] += subset[msk ^ (1 << i)];
        }
    }
}

void sum_over_superset() {
    for (int i = 0; i < N; i++) {
        for (int msk = 0; msk < (1 << N); msk++) {
            if (msk >> i & 1)       superset[msk ^ (1 << i)] += superset[msk];
        }
    }
}