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
	DIJ(Def size,Def l=1){
		n=size;
		L=l;
		G=vector<vector<edge> >(n);
	}
	void add_edge(Def a,Def b,Def c){
		edge e={b,c},ee={a,c};
		G[a].pb(e);
		G[b].pb(ee);
	}
	void dij(Def a,Def b,Def c,Def D){
		d=vector<vector<Def> >(n,vector<Def>(L+1,inf));
		d[s][L]=0;//now oktime ->time
//		rep(i,510)rep(j,50)rep(k,2)d[i][j][k]=INF;
//		d[0][D][0]=0;
		priority_queue<tp>q;
		q.push(tp(0,s,0));//time now v_0 n-1を通ったか
		while(!q.empty()){
			Def cost,pos,t;
			tie(cost,pos,t)=q.top();
			cost*=-1;
			q.pop();
			if(cost>d[pos][t])continue;
			rep(i,G[pos].size()){
				edge e=G[pos][i];
				Def to=e.to;
				Def ncost=cost+e.cost*v;
				Def nv=(a*v+b)%c;
				Def nt=t||(to==n-1);
				if(ncost<d[to][nv][nt]){
					d[to][nv][nt]=ncost;
					q.push(tp(-ncost,to,nv,nt));
				}
			}
		}
		ll out=INF;
		rep(i,50)out=min(out,d[0][i][1]);
		cout<<out<<endl;
	}
};


class DIJ{
	public:
	struct edge{
		int to,cost;
	};
	vector<vector<edge> >G;
	int n;
	vi d;//distance
	DIJ(int size){
		n=size;
		G=vector<vector<edge> >(n);
	}
	void add_edge(int a,int b,int c){
		edge e={b,c},ee={a,c};
		G[a].pb(e);
		G[b].pb(ee);
	}
	void dij(int s){
		d=vi(n,inf);
		d[s]=0;
		priority_queue<pii>q;
		q.push(pii(0,s));
		while(!q.empty()){
			pii p=q.top();
			q.pop();
			int pos=p.second,cost=-p.first;
			if(cost>d[pos])continue;
			rep(i,G[pos].size()){
				edge e=G[pos][i];
				int to=e.to;
				int nowcost=cost+e.cost;
				if(nowcost<d[to]){
					d[to]=nowcost;
					q.push(pii(-d[to],to));
				}
			}
		}
	}
};
int main(){
	int n,m,s;
	cin>>n>>m>>s;
	DIJ dij(n);
	while(m--){
		int a,b,c;
		cin>>a>>b>>c;
		dij.add_edge(a,b,c);
	}
	dij.dij(s);
	rep(i,n)if(dij.d[i]!=inf)cout<<dij.d[i]<<endl;
		else cout<<"INF"<<endl;
}




