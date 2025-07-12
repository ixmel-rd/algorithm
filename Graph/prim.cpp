// bool used[]
// vvi cost
// vi d
int prim() {
    int sum = 0;
    while (true) {
        int v = -1;
        rep(i, V) if (!used[i] && (v == -1 || d[i] < d[v])) v = i;
        if (v == -1)
            break;
        sum += d[v];
        used[v] = true;
        rep(u, V) d[u] = min(d[u], cost[v][u]);
    }
    return sum;
}
