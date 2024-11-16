const ll MOD = 1e9 + 7;
ll mul(ll a, ll b){return (a%MOD)*(b%MOD)%MOD;}
ll add(ll a, ll b){return ((a+MOD)%MOD + (b+MOD)%MOD)%MOD;}
ll fpow(ll a, ll b){
    ll res=1;
    while (b){
        if (b & 1) res=mul(res,a);
        b>>=1;
        a=mul(a,a);
    }
    return res;
}
ll inv(ll a) {return fpow(a,MOD-2);}

// Euler's totient function. Source: cp-algorithms.com
vector<ll> phi_1_to_n(int n) {
    vector<ll> phi(n + 1);
    for (int i = 0; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
    return phi;
}

void factorial(vector<ll>& fact, int n) {
	fact.assign(n + 1, 0);
	fact[0] = 1;
	for (ll i = 1; i <= n; i++) fact[i] = mul(fact[i - 1], i);
}
void inv_factorial(vector<ll>& invfact, int n) {
	invfact.assign(n + 1, 0);
	invfact[0] = 1;
	for (ll i = 1; i <= n; i++) invfact[i] = mul(invfact[i - 1], inv(i));
}