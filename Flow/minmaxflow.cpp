class MFL{
	public:
	MF flow;
	int S,T;
	int sum_lb;
	
	MFL(int n) : flow(n),S(n-2),T(n-1),sum_lb(0){ }
	
	void add_edge(int u,int v,int lb,int ub){
		if(u==v||ub==0)return;
		flow.add_edge(u,v,ub-lb);
		flow.add_edge(S,v,lb);
		flow.add_edge(u,T,lb);
		sum_lb+=lb;
	}
	int mfl(int s,int t){
		int S=this->S,T=this->T;
		int a=flow.mf(S,T);
		int b=flow.mf(s,T);
		int c=flow.mf(S,t);
		int d=flow.mf(s,t);
		return (a+c==sum_lb&&a+b==sum_lb)?b+d:-1;
	}
};
int main(){
	int n,m;
	cin>>n>>m;
	MFL mfl(2+n);
	rep(i,m){
		int a,b,c;
		cin>>a>>b>>c;
		mfl.add_edge(a,b,0,c);
	}
	cout<<mfl.mfl(0,n-1)<<endl;
}
