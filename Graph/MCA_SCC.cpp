class SCC{//cmp(0 - kk-1) is scc's return. Same number is group. The number is no relatoin.
	public:
	int n;
	vvi G,rG,tG;
	vector<bool>used;
	vi vs,cmp;
	SCC(int size){
		n=size;
		G=rG=vvi(n);
		used=vector<bool>(n);
		cmp=vi(n);
		vs=vi(0);
	}
	void add_edge(int s,int t){
		G[s].pb(t);
		rG[t].pb(s);
	}
	void rdfs(int v,int k){
		used[v]=true;
		cmp[v]=k;
		rep(i,rG[v].size())if(!used[rG[v][i]])rdfs(rG[v][i],k);
	}
	void dfs(int v){
		used[v]=true;
		rep(i,G[v].size())if(!used[G[v][i]])dfs(G[v][i]);
		vs.pb(v);
	}
	int scc(){
		rep(i,n)used[i]=false;
		rep(v,n)if(!used[v])dfs(v);
		rep(i,n)used[i]=false;
		int kk=0;
		for(int i=vs.size()-1;i>=0;i--)if(!used[vs[i]])rdfs(vs[i],kk++);
		return kk;  
	}
	void make(int size){
		int N=size;
		tG=vvi(N);
		rep(i,n)rep(j,G[i].size())if(cmp[i]!=cmp[G[i][j]]){
			tG[cmp[i]].pb(cmp[G[i][j]]);
//			tG[cmp[G[i][j]]].pb(cmp[i]);
		}
	}
};
int main(){
	int n,m;
	cin>>n>>m;
	SCC scc(n);
	while(m--){
		int a,b;
		cin>>a>>b;
		scc.add_edge(a,b);
	}
	int N=scc.scc();
	scc.make(N);
}

//MCA
struct edge{
	int to,cost;
};
class MCA{
	public:
	int n,r;
	vector<vector<edge> >G,rG,tG,trG;
	vector<bool>used;
	MCA(int size,int R){
		r=R;
		n=size;
		rG=G=vector<vector<edge> >(n);
	}
	void add_edge(int s,int t,int cost){
		edge e={t,cost},ee={s,cost};
		G[s].pb(e);rG[t].pb(ee);
	}
	void dfs(int s){
		used[s]=true;
		rep(i,tG[s].size())if(!used[tG[s][i].to])dfs(tG[s][i].to);
	}
	int mca(){
		tG=trG=vector<vector<edge> >(n);
		rep(i,n)if(i!=r){
			int mi=inf;
			rep(j,rG[i].size())mi=min(mi,rG[i][j].cost);
			rep(j,rG[i].size())if(mi==rG[i][j].cost){
				edge e={i,rG[i][j].cost};
				tG[rG[i][j].to].pb(e);
				trG[i].pb(rG[i][j]);
				break;
			}
		}
		used=vector<bool>(n);
		dfs(r);
		bool h=true;
		rep(i,n)if(!used[i])h=false;
		if(h){//connect
			int sum=0;
			rep(i,n)rep(j,tG[i].size())sum+=tG[i][j].cost;
			return sum;		
		}else{// not connect
			SCC scc(n);
			rep(i,n)rep(j,tG[i].size())scc.add_edge(i,tG[i][j].to);
			int N=scc.scc();
			MCA mca(N,scc.cmp[r]);
			int sum=0;
			rep(i,n)rep(j,tG[i].size())if(scc.cmp[i]==scc.cmp[tG[i][j].to])sum+=tG[i][j].cost;
			rep(i,n)rep(j,G[i].size())if(scc.cmp[i]!=scc.cmp[G[i][j].to]){
				bool h=false;
				int To=G[i][j].to;//i -> To
				rep(k,n)if(To!=k&&scc.cmp[To]==scc.cmp[k])h=true;
				if(h){
					mca.add_edge(scc.cmp[i],scc.cmp[To],G[i][j].cost-trG[To][0].cost);
				}else{
					mca.add_edge(scc.cmp[i],scc.cmp[To],G[i][j].cost);
				}
			}
			return sum+mca.mca();
		}
		return false;
	}
};
int main(){
	int n,m,k;
	cin>>n>>m>>k;
	MCA mca(n,k);
	while(m--){
		int a,b,c;
		cin>>a>>b>>c;
		mca.add_edge(a,b,c);
	}
	cout<<mca.mca()<<endl;
}