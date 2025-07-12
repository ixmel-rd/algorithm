// LCP of s and s[i:s.size()-1]
// aaabaaaab
// 921034210
struct Z {
    vi a;
    Z() {}
    Z(string &s) : a(s.size()) {
        a[0] = s.size();
        int i = 1, j = 0;
        while (i < s.size()) {
            while (i + j < s.size() && s[j] == s[i + j])
                j++;
            a[i] = j;
            if (j == 0) {
                i++;
                continue;
            }
            int k = 1;
            while (i + k < s.size() && k + a[k] < j)
                a[i + k] = a[k], k++;
            i += k;
            j -= k;
        }
    }
};
int main() {
    string s;
    cin >> s;
    Z a(s);
}
