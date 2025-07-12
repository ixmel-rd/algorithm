// const int MOD=1000000007;
const int MOD = 998244353;
const int M = 300000;
vi fact, rev;
bool do_init = false;
ll powmod(ll a, ll b, ll m = MOD) {
    ll out = 1;
    ll p = a % m;
    while (b) {
        if (b & 1)
            out = out * p % m;
        p = p * p % m;
        b >>= 1;
    }
    return out;
}
void init() {
    do_init = true;
    fact = rev = vector<ll>(M);
    fact[0] = fact[1] = 1;
    loop(i, 2, M) fact[i] = fact[i - 1] * i % MOD;
    rev[M - 1] = powmod(fact[M - 1], MOD - 2, MOD);
    for (int i = M - 2; i >= 0; i--)
        rev[i] = rev[i + 1] * (i + 1) % MOD;
}
// nCr
ll nCr(ll n, ll r, ll m = MOD) {
    if (!do_init)
        init();
    if (n < 0 || r < 0 || n < r)
        return 1; // 0 or 1
    ll out = fact[n] * rev[r] % m * rev[n - r] % m;
    ;
    return out;
}
// nHr
ll nHr(ll n, ll r) {
    if (!r && n != r)
        return 0;
    if (!r)
        return 1;
    return nCr(n + r - 1, r - 1);
}
