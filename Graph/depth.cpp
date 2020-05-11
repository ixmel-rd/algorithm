int n;
vvi G;
vi cal_depth(int s){
	vi dep(n,inf);
	dep[s]=0;
	queue<int>q;
	q.push(s);
	while(!q.empty()){
		int a=q.front();
		q.pop();
		rep(i,G[a].size()){
			int to=G[a][i];
			if(dep[to]>dep[a]+1){
				dep[to]=dep[a]+1;
				q.push(to);
			}
		}
	}
	return dep;
}
