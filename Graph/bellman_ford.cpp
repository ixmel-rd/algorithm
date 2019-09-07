class BEL{
	public:
	struct edge{
		Def to,cost;
	};
	vector<vector<edge> >G;
	Def n;
	vector<Def>d;//distance
	BEL(Def size){
		n=size;
		G=vector<vector<edge> >(n);
	}
	void add_edge(Def a,Def b,Def c){
		edge e={b,c},ee={a,c};
		G[a].pb(e);
//		G[b].pb(ee);
	}
	int bel(Def s){// return 1 -> negative cycle
		d=vector<Def>(n,inf);
		d[s]=0;
 
		vector<Def>used(n);
		rep(i,2*n){
			rep(j,n)rep(k,G[j].size()){
				edge e=G[j][k];
				if(d[j]!=inf&&d[e.to]>d[j]+e.cost){
					d[e.to]=d[j]+e.cost;
					if(i>=n)used[e.to]=true;
				}
				if(used[j])used[e.to]=true;
			}
		}
		if(used[n-1])d[n-1]=inf;
		return d[n-1];
	}
};
int main(){
	int n,m,r;
	cin>>n>>m>>r;
	BEL bel(n);
	rep(i,m){
		int a,b,c;
		cin>>a>>b>>c;
		bel.add_edge(a,b,c);
	}
	int a=bel.bel(r);
	if(a==inf)cout<<"NEGATIVE CYCLE"<<endl;
	else rep(i,n)if(bel.d[i]>inf/2)cout<<"INF"<<endl;
	else cout<<bel.d[i]<<endl;
}
