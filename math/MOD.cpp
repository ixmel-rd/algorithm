//行列累乗
const int MOD=1000000007;
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
//簡易nCr
ll nCr(int n,int r){
	return (r==0|| n==r) ? 1 : nCr(n-1,r) + nCr(n-1,r-1);
}
//--------------------------------
//nCr mod m
//n<1e7 r,m：任意
//前計算O(nloglogn) 本計算O(n/logn)
// need prinme
ll nCr(ll n,ll r,ll m){
	if(n<0||r<0||r>n)return 0;
	if(r>n/2)r=n-r;
	vi A(n);
	rep(i,r)A[i]=n-i;
	rep(p,sosu.size()){
		if(sosu[p]>r)break;
		for(ll q=sosu[p];q<=r;q*=sosu[p]){
			int m=n%q;
			for(int i=m,j=0;j<r/q;i+=q,j++)A[i]/=sosu[p];
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
// 中国剰余定理
// x % d1 = m1
// x % d2 = m2
// であるxを返す
ll crt(ll d1,ll m1,ll d2, ll m2){
	ll p,q;
	ll d=extgcd(d1,d2,p,q);
	if((m2-m1)%d!=0)return -1;
	ll m=d1*(d2/d);
	ll tmp=(m2-m1)/d*p%(d2/d);
	tmp=m1+d1*tmp;
	ll r=(tmp%m+m)%m;
	return r;
}

const int M=100000;
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

//need prime
//n,r:任意 m<1e7
ll nCr(ll n,ll r,ll m){
	if(!h)init();
	ll div=1,mod=0;
	rep(i,sosu.size()){
		int co=0,s=1;
		while(m%sosu[i]==0){
			co++;
			m/=sosu[i];
			s*=sosu[i];
		}
		if(co){
			mod=crt(s,nCr(n,r,sosu[i],co),div,mod);
			div*=s;
		}
	}
	return mod;
}


