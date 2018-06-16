class ART{//Articulation Pionts. kansetsuten
	public:
	int n;
	vvi G;
	vector<bool>visit;
	vi prenum,parent,lowest;
	int co;
	ART(int size){
		n=size;
		G=vvi(n);
		prenum=parent=lowest=vi(n);
	}
	void add_edge(int a,int b){
		G[a].pb(b);
		G[b].pb(a);
	}
	void dfs(int now,int pre){
		prenum[now]=lowest[now]=co;
		co++;
		visit[now]=true;
		int next;
		rep(i,G[now].size()){
			next=G[now][i];
			if(!visit[next]){
				parent[next]=now;
				dfs(next,now);
				lowest[now]=min(lowest[now],lowest[next]);
			}else if(next!=pre)lowest[now]=min(lowest[now],prenum[next]);
		}
	}
	void art(){
		visit=vector<bool>(n);
		co=1;
		dfs(0,-1);//0==root
		set<int>ap;
		int np=0;
		loop(i,1,n){
			int p=parent[i];
			if(!p)np++;
			else if(prenum[p]<=lowest[i])ap.insert(p);
		}
		if(np>1)ap.insert(0);
		for(set<int>::iterator it=ap.begin();it!=ap.end();it++)
			cout<<(*it)<<endl;
	}
};
int main(){
	int n,m;
	cin>>n>>m;
	ART art(n);
	while(m--){
		int a,b;
		cin>>a>>b;
		art.add_edge(a,b);
	}
	art.art();
}