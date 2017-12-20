class TreeDP{//c++11
	public:
	struct edge{
		int to,cost;
	};
	int n;
	vi dist;
	vector<vector<edge> >G;
	TreeDP(int size){
		n=size;
		dist=vi(n);
		G=vector<vector<edge> >(n);
	}
	void add_edge(int a,int b,int c){
		edge e={b,c},ee={a,c};
		G[a].pb(e);
		G[b].pb(ee);
	}
	void dfs1(int a,int par){
		rep(i,G[a].size()){
			edge e=G[a][i];
			if(e.to==par)continue;
			dfs1(e.to,a);
			dist[a]=max(dist[a],dist[e.to]+e.cost);
		}
	}
	int dfs2(int a,int d_par,int par){
		vp d_child;
		d_child.pb({0,-1});
		rep(i,G[a].size()){
			edge e=G[a][i];
			if(e.to==par)d_child.pb({d_par+e.cost,e.to});
			else d_child.pb({dist[e.to]+e.cost,e.to});
		}
		sort(d_child.rbegin(),d_child.rend());
		int ret=d_child[0].first+d_child[1].first;
		rep(i,G[a].size()){
			edge e=G[a][i];
			if(e.to==par)continue;
			ret=max(ret,dfs2(e.to,d_child[d_child[0].second==e.to].first,a));
		}
		return ret;
	}
	int dp(){
		dfs1(n/2,-1);
		return dfs2(n/2,0,-1);
	}
};






