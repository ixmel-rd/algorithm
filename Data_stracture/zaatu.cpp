// AOJ 0509 (MLE)
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
int main(){
    int n,m;
    while(cin>>n>>m,n){
		vvi in(n,vi(4));
		rep(i,n)rep(j,4)cin>>in[i][j];
		vi x,y;
		rep(i,n)rep(j,4)if(j%2)y.pb(in[i][j]);
						else x.pb(in[i][j]);
		sort(all(x));sort(all(y));
		x.erase(unique(all(x)),x.end());
		y.erase(unique(all(y)),y.end());
		 
		vvi tmp=in;
		rep(i,n)rep(j,4)if(j%2)tmp[i][j]=find(all(y),tmp[i][j])-y.begin();
						else tmp[i][j]=find(all(x),tmp[i][j])-x.begin();

		vvi field(x.size(),vi(y.size()));
		rep(i,n){
			field[tmp[i][0]][tmp[i][1]]++;
			field[tmp[i][2]][tmp[i][1]]--;
			field[tmp[i][0]][tmp[i][3]]--;
			field[tmp[i][2]][tmp[i][3]]++;
		}
		rep(i,x.size())loop(j,1,y.size())field[i][j]+=field[i][j-1];
		rep(j,y.size())loop(i,1,x.size())field[i][j]+=field[i-1][j];
	 
		ll out=0;
		rep(i,x.size())rep(j,y.size())if(field[i][j])
			out+=(ll)(x[i+1]-x[i])*(y[j+1]-y[j]);
		cout<<out<<endl; //面積
		
//		rep(i,x.size()){rep(j,y.size())cout<<field[i][j];cout<<endl;}
		
		out=0;
		rep(i,x.size())rep(j,y.size())if(field[i][j])rep(k,4){
			int nx=i+dx[k];
			int ny=j+dy[k];
			if(nx<0||ny<0||nx>=x.size()||ny>=y.size()||!field[nx][ny])
				out+=(k%2?y[j+1]-y[j]:x[i+1]-x[i]);
		}
		if(m-1)cout<<out<<endl; //周囲の長さ
	}
}