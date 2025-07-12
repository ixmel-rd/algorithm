// Rolling Hash
// long long にして使うこと
class RHash {
  public:
    int n;
    vi base, mo; // mod
    vvi hash;
    vvi po; // pow

    RHash(string s) {
        base = {1009, 9973};
        mo = {1000000007, 1000000009};

        n = s.size();
        hash = vvi(n + 1, vi(2));
        po = vvi(n + 1, vi(2, 1));

        rep(i, n) rep(j, 2) {
            hash[i + 1][j] = (hash[i][j] + s[i]) * base[j] % mo[j];
            po[i + 1][j] = po[i][j] * base[j] % mo[j];
        }
    }
    pii get(int l, int r) { // [l,r)
        Def t[2];
        rep(i, 2) t[i] =
            ((hash[r][i] - hash[l][i] * po[r - l][i]) % mo[i] + mo[i]) % mo[i];
        return {t[0], t[1]};
    }
};
