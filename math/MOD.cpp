//行列累乗
#define MOD 1000000007
vvi mul(vvi A,vvi B){
	vvi C(A.size(),vi(B[0].size()));
	rep(i,A.size())rep(k,B.size())rep(j,B[0].size())
		(C[i][j]+=A[i][k]*B[k][j])%=MOD;
	return C;
}
vvi pow(vvi A,ll n){
	vvi B(A.size(),vi(A.size()));
	rep(i,A.size())B[i][i]=1;
	while(n){
		if(n&1)B=mul(B,A);
		A=mul(A,A);
		n>>=1;
	}
	return B;
}
//--------------------------------
//nCr mod m
#define MOD 1000000007
#define M 1000000
vector<ll> fact;
bool h=false;
void init(){
	h=true;
	fact=vector<ll>(M);
	fact[0]=fact[1]=1;
	loop(i,2,M)fact[i]=fact[i-1]*i%MOD;
}
// a^b mod MOD
ll powmod(ll a,ll b,ll m){
	ll out=1;
	ll p=a%m;
	while(b){
		if(b&1)out=out*p%m;
		p=p*p%m;
		b>>=1;
	}
	return out;
}
//nCr
ll nCr(ll n,ll r,ll m){
	if(!h)init();
	if(n<0||r<0||n<r)return 1;//??????
	ll out=fact[n]*powmod(fact[r]*fact[n-r]%m,m-2,m)%m;
	return out;
}
//nHr
ll nHr(ll n,ll r){
	if(!r&&n!=r)return 0;
	if(!r)return 1;
	return nCr(n+r-1,r-1);
}

//--------------------------------
#define MOD 1000000007
#define MAX 1000010
int sosu[MAX]={1,1,0};
vi sos;
bool h=false;
void init(){
	h=true;
	for(int i=2;i*i<=MAX;i++)if(!sosu[i])
	for(int j=i*2;j<MAX;j+=i)sosu[j]=true;
	rep(i,MAX)if(sosu[i]==0)sos.pb(i);
}
//nCr mod m
//n<1e7 r,m：任意
//前計算O(nloglogn) 本計算O(n/logn)
ll nCr(ll n,ll r,ll m){
	if(!h)init();
	if(n<0||r<0||r>n)return 0;
	if(r>n/2)r=n-r;
	vi A(n);
	rep(i,r)A[i]=n-i;
	rep(p,sos.size()){
		if(sos[p]>r)break;
		for(ll q=sos[p];q<=r;q*=sos[p]){
			int m=n%q;
			for(int i=m,j=0;j<r/q;i+=q,j++)A[i]/=sos[p];
		}
	}
	ll out=1;
	rep(i,r)(out*=A[i])%=m;
	return out;
}

//--------------------------------
//https://www.hackerrank.com/contests/infinitum10/challenges/cheese-and-random-toppings まだ解いてない
//Lucasの定理
//m:素数 n,r:任意
//前計算O() 本計算O(logn)
ll nCr_l(ll n,ll r,ll m){
	ll out=1;
	while(n>0){
		(out*=nCr(n%m,r%m,m))%=m;
		n/=m;r/=m;
	}
	return out;
}

//--------------------------------
//http://codeforces.com/gym/100633/problem/J
// extgcd(a=12707,b=12319,x,y) -> x=32,y=-33,return 97=gcd
ll extgcd(ll a,ll b,ll &x,ll &y){//ax+by=gcd(a,b)=d
	ll d=a;
	if(b!=0){
		d=extgcd(b,a%b,y,x);
		y-=(a/b)*x;
	}else{
		x=1;y=0;
	}
	return d;
}
// x= mod1 mod div1
// x= mod2 mod div2
// であるxを返す
ll crt(ll div1,ll mod1,ll div2,ll mod2){
	ll x,y;
	ll d=extgcd(div1,div2,x,y);
	if(d-1)assert(0);
	ll ndiv=div1*div2;
//	ll nmod=(x*(mod2-mod1)*div1+mod1)%ndiv;
	ll nmod=(mod1*div2%ndiv*(ndiv+y)%ndiv+mod2*div1%ndiv*(ndiv+x)%ndiv)%ndiv;
	return nmod;
}

#define MOD 1000000007
#define M 1000000
//Lucasの定理の拡張
//m=p^q m<1e7 n,r:任意 p:素数 p!=1
vi fact,ifact;
void init(ll p,ll q){
	int P=1;
	rep(i,q)P*=p;
	fact=ifact=vi(M);
	fact[0]=1;
	loop(i,1,P+1){
		if(i%p==0)fact[i]=fact[i-1];
		else fact[i]=fact[i-1]*i%P;
	}
	rep(i,P+1){
		ll out=1;
		ll mul=fact[i];
		for(ll n=P/p*(p-1)-1;n>0;n>>=1){
			if(n&1)(out*=mul)%=P;
			(mul*=mul)%=P;
		}
		ifact[i]=out;
	}
}
ll nCr(ll n,ll r,ll p,ll q){
	init(p,q);
	if(n<0||r<0||r>n)return 0;
	int P=1;
	rep(i,q)P*=p;
	ll z=n-r;
	int e0=0;
	for(ll u=n/p;u>0;u/=p)e0+=u;
	for(ll u=r/p;u>0;u/=p)e0-=u;
	for(ll u=z/p;u>0;u/=p)e0-=u;
	int em=0;
	for(ll u=n/P;u>0;u/=p)em+=u;
	for(ll u=r/P;u>0;u/=p)em-=u;
	for(ll u=z/P;u>0;u/=p)em-=u;
	
	ll out=1;
	while(n>0){
		out=out*fact[n%P]%P*ifact[r%P]%P*ifact[z%P]%P;
		n/=p;r/=p;z/=p;
	}
	rep(i,e0)(out*=p)%=P;
	if(!(p==2&&q>=3)&&em&1)out=(P-out)%P;
	return out;
}
int sosu[M]={1,1,0};
vi sos;
bool h=false;
void init(){
	h=true;
	for(int i=2;i*i<=M;i++)if(!sosu[i])
	for(int j=i*2;j<M;j+=i)sosu[j]=true;
	rep(i,M)if(sosu[i]==0)sos.pb(i);
}
//
//n,r:任意 m<1e7
ll nCr(ll n,ll r,ll m){
	if(!h)init();
	ll div=1,mod=0;
	rep(i,sos.size()){
		int co=0,s=1;
		while(m%sos[i]==0){
			co++;
			m/=sos[i];
			s*=sos[i];
		}
		if(co){
			mod=crt(s,nCr(n,r,sos[i],co),div,mod);
			div*=s;
		}
	}
	return mod;
}


