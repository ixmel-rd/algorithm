// top front right left back bottom
// ri[top][front]=right
int ri[6][6] = {{0, 3, 5, 2, 4, 0}, {4, 0, 1, 6, 0, 3}, {2, 6, 0, 0, 1, 5},
                {5, 1, 0, 0, 6, 2}, {3, 0, 6, 1, 0, 4}, {0, 4, 2, 5, 3, 0}};
// front
void S(vector<int> &in) {
    int tmp = in[1];
    in[1] = in[0];
    in[0] = in[4];
    in[4] = in[5];
    in[5] = tmp;
}
// right
void E(vector<int> &in) {
    int tmp = in[2];
    in[2] = in[0];
    in[0] = in[3];
    in[3] = in[5];
    in[5] = tmp;
}
// turn
void T(vector<int> &in) {
    int tmp = in[1];
    in[1] = in[2];
    in[2] = in[4];
    in[4] = in[3];
    in[3] = tmp;
}
int main() {
    vector<int> in(6);
    rep(i, 6) cin >> in[i];
    vector<int> out(6);
    rep(i, 6) cin >> out[i];
    bool h = false;
    rep(i, 5) {
        S(in);
        if (in[0] == out[0]) {
            h = true;
            break;
        }
    }
    if (!h) {
        rep(i, 5) {
            E(in);
            if (in[0] == out[0])
                break;
        }
    }
    rep(i, 5) {
        T(in);
        if (in[1] == out[1])
            break;
    }
    h = true;
    rep(i, 6) if (in[i] != out[i]) h = false;
    if (h)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}