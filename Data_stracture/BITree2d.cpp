class BIT2d{
	public:
	vvi B2;
	int H,W;
	BIT2d(int h,int w){
		B2=vvi(h+1,vi(w+1));
		H=h,W=w;
	}
	void b2add(int h,int w,int a){
		int i,j;
		for(i=h;i<=H;i+=i&-i){
			for(j=w;j<=W;j+=j&-j)B2[i][j]+=a;
		}
	}
	int b2sum(int h,int w){
		int s=0,i,j;
		for(i=h;i;i-=i&-i)
			for(j=w;j;j-=j&-j)s+=B2[i][j];
		return s;
	}
};
