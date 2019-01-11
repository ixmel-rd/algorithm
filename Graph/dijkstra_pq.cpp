typedef ll Def;
class DIJ{
	public:
	struct edge{
		Def to,cost;
	};
	vector<vector<edge> >G;
	Def n,L;
	vector<vector<Def> >d;//distance
//	Def d[510][50][2];
	DIJ(Def size,Def l){
		n=size;
		L=l;//??????
		G=vector<vector<edge> >(n);
	}
	void add_edge(Def a,Def b,Def c){
		edge e={b,c},ee={a,c};
		G[a].pb(e);
		G[b].pb(ee);
	}
	void dij(Def s,Def g){
		d=vector<vector<Def> >(n,vector<Def>(L+1,inf));
		d[s][0]=0;
//		rep(i,510)rep(j,50)rep(k,2)d[i][j][k]=INF;
//		d[0][D][0]=0;
		priority_queue<tp>q;
		q.push(tp(0,s,0));
		while(!q.empty()){
			Def cost,pos,t;
			tie(cost,pos,t)=q.top();
			cost*=-1;
			q.pop();
			if(cost>d[pos][t])continue;
			rep(i,G[pos].size()){
				edge e=G[pos][i];
				Def to=e.to;
				Def ncost=cost+;//??????
				Def nt=t+;//??????
				if(ncost<d[to][nt]){
					d[to][nt]=ncost;
					q.push(tp(-ncost,to,nt));
				}
			}
		}
	}
};


class DIJ{
	public:
	struct edge{
		Def to,cost;
	};
	vector<vector<edge> >G;
	Def n;
	vi d;//distance
	DIJ(Def size){
		n=size;
		G=vector<vector<edge> >(n);
	}
	void add_edge(Def a,Def b,Def c){
		edge e={b,c},ee={a,c};
		G[a].pb(e);
		G[b].pb(ee);
	}
	void dij(Def s){
		d=vi(n,inf);
		d[s]=0;
		priority_queue<pii>q;
		q.push(pii(0,s));
		while(!q.empty()){
			pii p=q.top();
			q.pop();
			Def pos=p.second,cost=-p.first;
			if(cost>d[pos])continue;
			rep(i,G[pos].size()){
				edge e=G[pos][i];
				Def to=e.to;
				Def nowcost=cost+e.cost;
				if(nowcost<d[to]){
					d[to]=nowcost;
					q.push(pii(-d[to],to));
				}
			}
		}
	}
};
