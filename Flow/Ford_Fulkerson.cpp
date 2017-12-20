struct edge{int to,cap,rev;};//ikisaki youryou gyakuhen
class MF{//max flow
	public:
	int n;
	vector<vector<edge> >G;//[MAX];
	vector<bool>used;//[MAX];
	MF(int size){
		n=size;
		G=vector<vector<edge> >(n);
	}
	void add_edge(int from, int to, int cap){
		edge q={to,cap,int(G[to].size())};
		G[from].push_back(q);
		q={from,0,int(G[from].size()-1)};
		G[to].push_back(q);
	}
	int dfs(int v,int t, int f) {
		if(v==t)return f;
		used[v]=1;
		for(int i=0;i<G[v].size();i++){
			edge &e=G[v][i];
			if(used[e.to]||e.cap<=0) continue;
			int d =dfs(e.to,t,min(f,e.cap));
			if(d>0){
				e.cap-=d;
				G[e.to][e.rev].cap+=d;
				return d;
			}
		}
		return 0;
	}
	int mf(int s,int t) {//from s to t,ford_fulkerson
		int flow=0,f;
		while(1){
			used=vector<bool>(n,false);
			f=dfs(s,t,inf);
			if(f==0)return flow;
			flow+=f;
		}
	}
};
