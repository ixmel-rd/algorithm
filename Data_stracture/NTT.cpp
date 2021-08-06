//参考：https://kazuma8128.hatenablog.com/entry/2018/05/31/144519
#define MOD 924844033
#define R 5
ll powmod(ll a,ll b,ll m=MOD){
	ll out=1;
	ll p=a%m;
	while(b){
		if(b&1)out=out*p%m;
		p=p*p%m;
		b>>=1;
	}
	return out;
}

void ntt(vi& a,bool B){
	int n=a.size(),h=0;
	while(1<<h<n)h++;
	rep(i,n){
		int j=0;
		rep(k,h)if(i&1<<k)j+=1<<(h-k-1);
		if(i<j)swap(a[i],a[j]);
	}
	for(int i=1;i<n;i*=2){
		ll w=powmod(R,(MOD-1)/(i*2));
		if(B)w=powmod(w,MOD-2,MOD);
		for(int j=0;j<n;j+=i*2){
			ll wn=1;
			rep(k,i){
				ll s=a[j+k],t=a[i+j+k]*wn%MOD;
				a[j+k]=(s+t)%MOD;
				a[i+j+k]=(s-t+MOD)%MOD;
				(wn*=w)%=MOD;
			}
		}
	}
	if(B){
		ll v=powmod(n,MOD-2,MOD);
		rep(i,n)(a[i]*=v)%=MOD;
	}
}

// a[i]*b[j]=c[i+j]
vi Conv(vi a,vi b){
	int s=a.size()+b.size()-1,t=1;
	while(t<s)t*=2;
	a.resize(t);
	b.resize(t);
	ntt(a,0);ntt(b,0);
	rep(i,t)(a[i]*=b[i])%=MOD;
	ntt(a,1);
	a.resize(s);
	return a;
}
