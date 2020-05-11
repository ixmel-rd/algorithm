ll gcd(ll a,ll b){
	return (b==0?a:gcd(b,a%b));
}
ll lcm(ll a,ll b){
	return a/gcd(a,b)*b;
}
//http://codeforces.com/gym/100633/problem/J
// extgcd(a=12707,b=12319,x,y) -> x=32,y=-33,return 97=gcd
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
const int M=100000;
int sos[M]={1,1};//0->prime  1->not prime
vi sosu;
void prime(){
	for(int i=2;i*i<=M;i++)if(sos[i]==0)
	for(int j=i*2;j<M;j+=i)sos[j]=1;
	rep(i,M)if(sos[i]==0)sosu.pb(i);
}
