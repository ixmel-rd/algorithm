ll gcd(ll a,ll b){
	return (b==0?a:gcd(b,a%b));
}
ll lcm(ll a,ll b){
	return a/gcd(a,b)*b;
}
int extgcd(int a,int b,int &x,int &y){//ax+by=1
	int d=a;
	if(b!=0){
		d=extgcd(b,a%b,y,x);
		y-=(a/b)*x;
	}else{
		x=1;y=0;
	}
	return d;
}
//素数
init(){
	const int M=10000;
	int sosu[M]={1,1,0};
	for(int i=2;i*i<M;i++)if(sosu[i]==0)
	for(int j=i*2;j<M;j+=i)sosu[j]=1;
	vi sos;
	rep(i,M)if(sosu[i]==0)sos.pb(i);
}
