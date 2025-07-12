#define it vector<int>::iterator
bool next_combination(it first1, it last1, it first2, it last2) {
    if ((first1 == last1) || (first2 == last2))
        return false;
    it m1 = last1, m2 = last2;
    m2--;
    while (--m1 != first1 && !(*m1 < *m2))
        ;
    bool result = (m1 == first1) && !(*first1 < *m2);
    if (!result) {
        while (first2 != m2 && !(*m1 < *first2))
            first2++;
        first1 = m1;
        iter_swap(first1, first2);
        first1++;
        first2++;
    }
    if ((first1 != last1) && (first2 != last2)) {
        m1 = last1;
        m2 = first2;
        while ((m1 != first1) && (m2 != last2))
            iter_swap(--m1, m2++);
        reverse(first1, m1);
        reverse(first1, last1);
        reverse(m2, last2);
        reverse(first2, last2);
    }
    return !result;
}
bool next_combination(it first, it middle, it last) {
    return next_combination(first, middle, middle, last);
}
/*
n=5,r=3;
a=0 1 1 2 3
011 012 013 023 112 113 123
*/
// combination (begin,begin+r,end)
int main() {
    int n, r;
    cin >> n >> r;
    vi a(n);
    rep(i, n) cin >> a[i];
    sort(all(a));
    do {
        do {
            rep(i, n) cout << " " << a[i];
            cout << endl;
        } while (next_permutation(a.begin(), a.begin() + r));
    } while (next_combination(a.begin(), a.begin() + r, a.end()));
}
