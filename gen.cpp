/**
 * Usage:
 * 1. Compile and run "your_code.cpp" and "brute.cpp" on example
 * 2. Only modify gen_test() function
 * 3. Run gen.cpp
 * Note: Use gen_test() if only want to generate testcases, use check() if need stress testing
 * Default OS: Linux
 * In Windows: change "diff" to "fc", remove "./"
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const string NAME = "test";
const int NTEST = 5;

ll randint(ll l, ll r) {
    return uniform_int_distribution<ll> (l,r) (rng);
}

ll randdouble(double l, double r) {
    return uniform_real_distribution<double> (l,r) (rng);
}

void gen_test() {
    ofstream gen("test.inp");
    // gen code ( inp << . . . << . . . )
    int n = randint(1,10);
    gen << n << endl;
    for (int i = 1; i <= n; i++)        gen << randint(-1,10) << " ";
    gen.close();
}

void check() {
    for (int iTest = 1; iTest <= NTEST; iTest++) {
        gen_test();

        system(("./" + NAME + ".exe < test.inp > test.out").c_str());     
        system("./brute.exe < test.inp > test.ans"); 

        if (system("diff test.out test.ans"))
        { // fc : Windows <−> diff : Linux
            cout << "Test " << iTest << ": WRONG!\n";
            return;
        }
        cout << "Test " << iTest << ": CORRECT!\n";
    }
}

signed main()
{
    srand(time(NULL));
    return 0;
}
