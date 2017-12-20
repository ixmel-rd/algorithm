struct edge{int to,cap,rev;};//ikisaki youryou gyakuhen
class MF{//max flow
	public:
	int n;
	vector<vector<edge> >G;//[MAX];
	vi level,iter;//[MAX];
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
	void bfs(int s){
		level=vi(n,-1);
		queue<int>q;
		level[s]=0;
		q.push(s);
		while(!q.empty()){
			int v=q.front();q.pop();
			for(int i=0;i<G[v].size();i++){
				edge &e=G[v][i];
				if(e.cap>0&&level[e.to]<0){
					level[e.to]=level[v]+1;
					q.push(e.to);
				}
			}
		}
	}
	int dfs(int v,int t, int f) {
		if(v==t)return f;
		for(int &i=iter[v];i<G[v].size();i++){
			edge &e=G[v][i];
			if(level[v]>=level[e.to]||e.cap<=0) continue;
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
		int flow=0;
		while(1){
			bfs(s);
			if(level[t]<0)return flow;
			iter=vi(n);
			int f;
			while((f=dfs(s,t,inf))>0)flow+=f;
		}
	}
};
