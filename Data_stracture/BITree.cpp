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
	Def query(int i){//sum
		Def s=0;
		while(i>0){
			s+=bit[i];
			i-=i&-i;
		}
		return s;
	}
	void add(int i,Def x){
		while(i<=n){
			bit[i]+=x;
			i+=i&-i;
		}
	}
};
