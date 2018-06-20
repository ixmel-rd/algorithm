struct edge{
	int to,cap,cost,rev;
};
typedef vector<edge> ve;
typedef vector<ve> vve;
class MCF{	//Minimum Cost Flow
	public:
	int n;
	vve G;
	vi h,dist,prev,pree;
	MCF(int size){
		n=size;
		G=vve(n);
		h=dist=prev=pree=vi(n);
	}
	void add_edge(int s,int t,int ca,int co){
		edge e={t,ca,co,G[t].size()};
		G[s].pb(e);
		edge ee={s,0,-co,G[s].size()-1};
		G[t].pb(ee);
	}
	int mcf(int s,int t,int f){
		int out=0;
		h=vi(n);
		while(f>0){			
			priority_queue<pii,vector<pii> >q;
			dist=vi(n,inf);
			dist[s]=0;
			q.push(pii(0,s));
			while(!q.empty()){
				pii p=q.top();q.pop();
				int v=p.second;
				if(dist[v]<-p.first)continue;
				rep(i,G[v].size()){
					edge &e=G[v][i];
					if(e.cap>0&&dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
						dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
						prev[e.to]=v;
						pree[e.to]=i;
						q.push(pii(-dist[e.to],e.to));
					}
				}
			}
			if(dist[t]==inf)return -1;
			rep(i,n)h[i]+=dist[i];
			int d=f;
			for(int v=t;v!=s;v=prev[v])d=min(d,G[prev[v]][pree[v]].cap);
			f-=d;
			out+=d*h[t];
			for(int v=t;v!=s;v=prev[v]){
				edge &e=G[prev[v]][pree[v]];
				e.cap-=d;
				G[v][e.rev].cap+=d;
			}
		}
		return out;	
	}
};
int main(){
	int n,m,f;
	cin>>n>>m>>f;
	MCF mcf(n);
	while(m--){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		mcf.add_edge(a,b,c,d);
	}
	cout<<mcf.mcf(0,n-1,f)<<endl;;
}