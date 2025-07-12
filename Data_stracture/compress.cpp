int idx(vi &a, int i) { return lower_bound(all(a), i) - a.begin(); }
void compress(vi &a) {
    sort(all(a));
    a.erase(unique(all(a)), a.end());
}
