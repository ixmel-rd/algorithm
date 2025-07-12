vi split(string s) {
    stringstream ss(s); // ss<<s;
    vi vec;
    for (int i = 0; !ss.eof(); i++) {
        int t;
        ss >> t;
        vec.pb(t);
    }
    return vec;
}
vs split(string s, char c) {
    vs out;
    s += c;
    string t = "";
    rep(i, s.size()) if (s[i] == c) {
        out.pb(t);
        t = "";
    }
    else t += s[i];
    return out;
}