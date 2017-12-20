class BIT{
	public:
	//[1,i]
	int n;
	vi bit;
//	int bit[MAZ_N+1];
	BIT(int size){
		n=size;
		bit=vi(n+1);
	}
	int query(int i){//sum
		int s=0;
		while(i>0){
			s+=bit[i];
			i-=i&-i;
		}
		return s;
	}
	void add(int i,int x){
		while(i<=n){
			bit[i]+=x;
			i+=i&-i;
		}
	}
};
