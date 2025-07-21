const int MOD = 998244353;
const int M = 300000;
vm fact, rev;
bool do_init = false;
void init() {
    do_init = true;
    fact = rev = vm(M);
    fact[0] = fact[1] = 1;
    loop(i, 2, M) fact[i] = fact[i - 1] * i;
    rev[M - 1] = fact[M - 1].pow(MOD - 2);
    for (int i = M - 2; i >= 0; i--)
        rev[i] = rev[i + 1] * (i + 1);
}
mint nCr(ll n, ll r) {
    if (!do_init)
        init();
    if (n < 0 || r < 0 || n < r)
        return 1; // 0 or 1
    mint out = fact[n] * rev[r] * rev[n - r];
    return out;
}
