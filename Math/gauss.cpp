// ガウスの消去法
//  SpecialThanks
//  https://atcoder.jp/contests/yahoo-procon2019-qual/submissions/4227001
#define BIT_N 333
typedef bitset<BIT_N> Bit;
vector<Bit> gauss(vector<Bit> &v, ll &ran) {
    ran = 0;
    rep(i, BIT_N) {
        int pla = -1;
        for (int j = ran; j < v.size(); j++) {
            if (v[j][i] == 1) {
                pla = j;
                break;
            }
        }

        if (pla != -1) {
            swap(v[ran], v[pla]);
            for (int j = 0; j < v.size(); j++) {
                if (j != ran && v[j][i] == 1)
                    v[j] ^= v[ran];
            }
            ran++;
        }
    }
    return v;
}
