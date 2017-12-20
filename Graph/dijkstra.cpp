//bool used[]
//vvi cost
//vi d
void dijkstra(){
	while(true){
		int v=-1;
		rep(i,V)if(!used[i]&&(v==-1||d[i]<d[v]))v=i;
		if(v==-1)break;
		used[v]=true;
		rep(u,V)d[u]=min(d[u],d[v]+cost[v][u]);
	}
}
