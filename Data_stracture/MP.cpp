// max common lenght prefix of s[0:i] and suffix of s[0:i]
// aabaabaaa
//_010123452
//  syuki of s[0:i] is i-mp[i]
// abababcaa
// 122222778
struct MP {
    vi a;
    MP() {}
    MP(string &s) : a(s.size() + 1, -1) {
        for (int i = 0, j = -1; i < s.size(); a[++i] = ++j)
            while (j >= 0 && s[i] != s[j])
                j = a[j];
    }
};
