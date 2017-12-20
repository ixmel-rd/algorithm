class TOPO{//out is tsort's return.
	public:
	vvi G;
	vi out;
	vector<bool>V;
	vi indeg;
	int n;
	TOPO(int size){
		n=size;
		G=vvi(n);
		out=vi(0);
		V=vector<bool>(n);
		indeg=vi(n);
	}
	void add_edge(int s,int t){
		G[s].pb(t);
	}
	void bfs(int s){
		queue<int>q;
		q.push(s);
		V[s]=true;
		while(!q.empty()){
			int u=q.front();q.pop();
			out.pb(u);
			rep(i,G[u].size()){
				int v=G[u][i];
				indeg[v]--;
				if(indeg[v]==0&&!V[v]){
					V[v]=true;
					q.push(v);
				}
			}
		}
	}
	void tsort(){
		rep(i,n)indeg[i]=0;
		rep(i,n)rep(j,G[i].size()){
			int v=G[i][j];
			indeg[v]++;
		}
		rep(i,n)if(indeg[i]==0&&!V[i])bfs(i);
//		rep(i,n)cout<<out[i]<<endl;
	}
};
int main(){
	int n,m,k;
	cin>>n>>m>>k;
	SCC sc(n);
	vector<string>tmp(n);
	rep(i,n)cin>>tmp[i];
	while(m--){
		int a,b;
		cin>>a>>b;
		a--;b--;
		sc.add_edge(a,b);
	}
	int N=sc.scc();
	vector<string>dp(N);
	TOPO tp(N);
	rep(i,n){
		dp[sc.cmp[i]]+=tmp[i];
		rep(j,sc.G[i].size()){
			int t=sc.G[i][j];
			if(sc.cmp[i]!=sc.cmp[t])tp.add_edge(sc.cmp[i],sc.cmp[t]);
		}
	}
	rep(i,N){
		sort(all(dp[i]));
		if(dp[i].size()>k)dp[i]=dp[i].substr(0,k);
		sort(all(tp.G[i]));
		tp.G[i].erase(unique(all(tp.G[i])),tp.G[i].end());
	}
	tp.tsort();
}
 

