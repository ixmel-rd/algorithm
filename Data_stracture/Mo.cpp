
//heihou bunkatu
//offline
//not update query
//wakaru [l,r] -> [l-1,r],[l+1,r],[l,r-1][l,r+1]
struct Mo{
	vi left,right,order;
	vector<bool>v;
	int width;
	int nl,nr,ptr;
	
	Mo(int n):width((int)sqrt(n)),nl(0),nr(0),ptr(0),v(n){}
	
	void add(int l,int r){
		left.pb(l);right.pb(r);
	}
	void build(){
		order.resize(left.size());
		rep(i,order.size())order[i]=i;
		sort(all(order),[&](int a,int b){
			if(left[a]/width!=left[b]/width)return left[a]<left[b];
			return right[a]<right[b];
		});
	}
	void distribute(int idx){
		v[idx].flip();
		if(v[idx])insert(idx);
		else erase(idx);
	}
	int next(){
		if(ptr==order.size())return -1;
		const auto id=order[ptr];
		while(nl>left[id])distribute(--nl);
		while(nr<right[id])distribute(nr++);
		while(nl<left[id])distribute(nl++);
		while(nr>right[id])distribute(--nr);
		return order[ptr++];
	}
	
	
	
	void insert(int idx);
	void erase(int idx);
};

int n,m,sum;
vi in,co;
void Mo::insert(int a){
	co[in[a]]++;
	sum+=in[a]*(co[in[a]]*2-1);
}
void Mo::erase(int a){
	sum-=in[a]*(co[in[a]]*2-1);
	co[in[a]]--;
}

signed main(){
	cin>>n>>m;
	in=vi(n+1);
	co=vi(1000010);
	rep(i,n)scanf("%lld",&in[i]);
	Mo mo(n);
	rep(i,m){
		int a,b;
		scanf("%lld %lld",&a,&b);
		a--;
		mo.add(a,b);
	}
	mo.build();
	vi out(m);
	rep(i,m){
		int idx=mo.next();
		out[idx]=sum;
	}
	rep(i,m)printf("%lld\n",out[i]);
}




