#include <random>
vvi G;
vi Rand(100000);
ll MOD = 1000000009;
ll Hash(int a, int deg, int prev) {
    vi in;
    ll out = 1;
    rep(i, G[a].size()) if (G[a][i] != prev)(
        out *= (Rand[deg] + Hash(G[a][i], deg + 1, a)) % MOD) %= MOD;
    return out;
}
int main() {
    random_device rnd;
    rep(i, 100000) Rand[i] = rnd() % MOD;
    int n;
    cin >> n;
    G = vvi(n);
    rep(i, n - 1) {
        int a, b;
        cin >> a >> b;
        G[a].pb(b);
        G[b].pb(a);
    }
    ll out = Hash(0, 0, -1);
    cout << out << endl;
}
