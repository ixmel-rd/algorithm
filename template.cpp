// g++ main.cpp -std=c++14 -I . && a < in.txt
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#define loop(i, a, b) for (ll i = a; i < b; i++)
#define rep(i, a) loop(i, 0, a)
#define FOR(i, a) for (auto i : a)
#define pb push_back
#define all(in) in.begin(), in.end()
#define shosu(x) fixed << setprecision(x)
#define show1d(v)                                                              \
    rep(i, v.size()) cout << " " << v[i];                                      \
    cout << endl << endl;
#define show2d(v)                                                              \
    rep(i, v.size()) {                                                         \
        rep(j, v[i].size()) cout << " " << v[i][j];                            \
        cout << endl;                                                          \
    }                                                                          \
    cout << endl;
using namespace std;
typedef long long ll;
typedef ll Def;
typedef pair<Def, Def> pii;
typedef vector<Def> vi;
typedef vector<vi> vvi;
typedef vector<pii> vp;
typedef vector<vp> vvp;
typedef vector<string> vs;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef pair<Def, pii> pip;
typedef vector<pip> vip;
// #define mt make_tuple
// typedef tuple<ll,ll,ll> tp;
// typedef vector<tp> vt;
template <typename A, typename B> bool cmin(A &a, const B &b) {
    return a > b ? (a = b, true) : false;
}
template <typename A, typename B> bool cmax(A &a, const B &b) {
    return a < b ? (a = b, true) : false;
}
const double PI = acos(-1);
const double EPS = 1e-9;
Def inf = sizeof(Def) == sizeof(long long) ? 2e18 : 1e9 + 10;
ll dx[] = {0, 1, 0, -1};
ll dy[] = {1, 0, -1, 0};
#define yes cout << "Yes" << endl
#define no cout << "No" << endl

// using int128 = __int128_t;
#include <atcoder/all>
using namespace atcoder;
using mint = modint998244353;
#define showmod(out)                                                           \
    {                                                                          \
        for (ll i = 0; i < out.size(); i++)                                    \
            cout << " " << out[i].val();                                       \
        cout << endl;                                                          \
    }
typedef vector<mint> vm;
typedef vector<vm> vvm;

void solve() {}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int q = 1;
    // cin >> q;
    while (q--) {
        solve();
    }
}
