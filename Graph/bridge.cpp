class BRI{
	public:
	int N;
	vi used;
	vvi G;
	vp bridge;
	void add_edge(int s,int t){
		G[s].pb(t);
		G[t].pb(s);
	}
	BRI(int size){
		N=size;
		G=vvi(N);
	}
	int dfs(int i,int prev,int &n){
		if(used[i])return used[i];
		int m=n;
		used[i]=n++;
		rep(j,G[i].size()){
			if(prev==G[i][j])continue;
			if(used[i]<used[G[i][j]])continue;
			int res=dfs(G[i][j],i,n);
			m=min(m,res);
			if(used[i]<res)bridge.pb(pii(min(i,G[i][j]),max(i,G[i][j])));
		}
		return m;
	}
	void bri(){
		used=vi(N);
		bridge=vp(0);
		int n=1;
		dfs(0,-1,n);
		sort(all(bridge));
		rep(i,bridge.size())cout<<bridge[i].first<<" "<<bridge[i].second<<endl;
	}
};
int main(){
	int n,m;
	cin>>n>>m;
	BRI bri(n);
	while(m--){
		int a,b;
		cin>>a>>b;
		bri.add_edge(a,b);
	}
	bri.bri();
}
