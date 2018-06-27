class BRI{
	public:
	int n,N;
	vi order,inS,cmp;
	vp brg;
	vvi G,each_bcc;
	// N : scc後の頂点数
	// brg : 橋一覧
	// each_bcc : 二重連結成分のリスト
	// cmp : ある頂点がどの二重連結成分に含まれているか
	stack<int> roots, S;
	BRI(int size){
		n=size;
		G=vvi(n);
	}
	void add_edge(int s,int t){
		G[s].pb(t);
		G[t].pb(s);
	}
	void visit(int cur,int prev,int &k){
		order[cur]=++k;
		S.push(cur);
		inS[cur]=true;
		roots.push(cur);
		
		rep(i,G[cur].size()){
			int to=G[cur][i];
			if(!order[to])visit(to,cur,k);
			else if(to!=prev&&inS[to])
				while(order[roots.top()]>order[to])roots.pop();
		}
		
		if(cur==roots.top()){
			if(prev!=-1)brg.pb({prev,cur});
			vi bcc;
			while(1){
				int node=S.top();
				S.pop();
				inS[node]=false;
				bcc.pb(node);
				cmp[node]=N;
				if(node==cur)break;
			}
			N++;
			each_bcc.pb(bcc);
			roots.pop();
		}
	}
	void bri(){
		N=0;
		order=inS=cmp=vi(n);
		roots=S=stack<int>();
		int k=0;
		rep(i,n)if(order[i]==0)
			visit(i,-1,k);
	}
	vvi make(){
		vvi tG(N);
		rep(i,brg.size()){
			int a=brg[i].first,b=brg[i].second;
			tG[cmp[a]].pb(cmp[b]);
			tG[cmp[b]].pb(cmp[a]);
		}
		return tG;
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
	vvi G=bri.make();
}

	


