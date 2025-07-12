typedef int SegT;
const SegT defvalue = 0;
class SegTree {
  private:
    vector<SegT> val;
    int n;
    SegT combine(SegT a, SegT b) { return gcd(a, b); }

  public:
    SegTree(int size) {
        n = 1;
        while (n < size)
            n <<= 1;
        val = vector<SegT>(2 * n, defvalue);
    }
    SegTree(const vector<SegT> &in) {
        n = 1;
        while (n < in.size())
            n <<= 1;
        val = vector<SegT>(2 * n, defvalue);
        for (int i = n - 1 + in.size() - 1; i >= 0; i--) {
            if (n - 1 <= i)
                val[i] = in[i - (n - 1)];
            else
                val[i] = combine(val[i * 2 + 1], val[i * 2 + 2]);
        }
    }
    void update(int i, SegT a) {
        i += n - 1;
        val[i] = a;
        while (i > 0) {
            i = (i - 1) / 2;
            val[i] = combine(val[i * 2 + 1], val[i * 2 + 2]);
        }
    }
    SegT query(int a, int b, int k = 0, int l = 0, int r = -1) { //[a,b)
        if (r == -1)
            r = n;
        if (r <= a || b <= l)
            return defvalue;
        if (a <= l && r <= b)
            return val[k];
        else
            return combine(query(a, b, k * 2 + 1, l, (l + r) / 2),
                           query(a, b, k * 2 + 2, (l + r) / 2, r));
    }
    void tmp() {
        rep(i, val.size()) cout << " " << val[i];
        cout << endl;
    }
};

///////////////////////////////------------------------------
// yukicoder   nijizenkasiki(No.510)
#define MOD 1000000007
typedef vvi SegT;
vvi defvalue;
vvi defvalue2;
SegT f(SegT A, SegT B) {
    vvi C(A.size(), vi(B[0].size()));
    rep(i, A.size()) rep(k, B.size())
        rep(j, B[0].size())(C[i][j] += A[i][k] * B[k][j]) %= MOD;
    return C;
}
class SegTree {
  private:
    vector<SegT> val;
    int n;
    SegT combine(SegT a, SegT b) { return f(b, a); }

  public:
    SegTree(int size) {
        n = 1;
        while (n < size)
            n <<= 1;
        val = vector<SegT>(2 * n, defvalue);
    }
    SegTree(const vector<SegT> &in) {
        n = 1;
        while (n < in.size())
            n <<= 1;
        val = vector<SegT>(2 * n, defvalue);
        for (int i = n - 1 + in.size() - 1; i >= 0; i--) {
            if (n - 1 <= i)
                val[i] = in[i - (n - 1)];
            else
                val[i] = combine(val[i * 2 + 1], val[i * 2 + 2]);
        }
    }
    void update(int q, int i, ll a) {
        i += n - 1;
        if (!q)
            val[i][0][2] = a;
        else {
            val[i][1][1] = a;
            val[i][2][1] = 2 * a;
            val[i][2][2] = a * a % MOD;
        }
        while (i > 0) {
            i = (i - 1) / 2;
            val[i] = combine(val[i * 2 + 1], val[i * 2 + 2]);
        }
    }
    SegT query(int a, int b, int k = 0, int l = 0, int r = -1) { //[a,b)
        if (r == -1)
            r = n;
        if (r <= a || b <= l)
            return defvalue2;
        if (a <= l && r <= b)
            return val[k];
        else
            return combine(query(a, b, k * 2 + 1, l, (l + r) / 2),
                           query(a, b, k * 2 + 2, (l + r) / 2, r));
    }
    void tmp() {
        rep(i, val.size()) {
            cout << i << endl;
            rep(j, 4) {
                rep(k, 4) cout << " " << val[i][j][k];
                cout << endl;
            }
            cout << endl;
        }
    }
};
int main() {
    vvi r = vvi(4, vi(4));
    r[0][0] = r[1][3] = r[2][3] = r[3][3] = 1;
    defvalue = r;
    r = vvi(4, vi(4));
    r[0][0] = r[1][1] = r[2][2] = r[3][3] = 1;
    defvalue2 = r;
    int n, q;
    cin >> n >> q;
    SegTree st(n + 1);
    int x, y;
    while (q--) {
        //		st.tmp();
        int a, b;
        char c;
        cin >> c;
        if (c == 'x') {
            cin >> a >> b;
            st.update(0, a, b);
        } else if (c == 'y') {
            cin >> a >> b;
            st.update(1, a, b);
        } else if (c == 'a') {
            cin >> a;
            vvi t = st.query(0, a);
            cout << (t[0][0] + t[0][1] + t[0][2] + t[0][3]) % MOD << endl;
        };
    }
}