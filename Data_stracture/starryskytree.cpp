class SST{
	public:
	int n;
	vi a,b;
	SST(int size){
		n=pow(2,ceil(log2(size)));
		a=b=vi(2*n-1);
	}
	void range_add(int l,int r,int z){//[l,r)+=z
		range_add(0,0,n,l,r,z);
	}
	void range_add(int i,int il,int ir,int l,int r,int z){//[l,r)
		if(l<=il&&ir<=r){
			a[i]+=z;
			b[i]+=z;
		}else if(ir<=l||r<=il){
			
		}else{
			range_add(2*i+1,il,(il+ir)/2,l,r,z);
			range_add(2*i+2,(il+ir)/2,ir,l,r,z);
			b[i]=a[i]+max(b[2*i+1],b[2*i+2]);//max
		}
	}
	int range_max(int l,int r){
		return range_max(0,0,n,l,r);
	}
	int range_max(int i,int il,int ir,int l,int r){
		if(l<=il&&ir<=r){
			return b[i];
		}else if(ir<=l||r<=il){
			return 0;
		}else{
			return a[i]+max(
				range_max(2*i+1,il,(il+ir)/2,l,r),
				range_max(2*i+2,(il+ir)/2,ir,l,r));
		}
	}
	void open(){
		rep(i,a.size())cout<<" "<<a[i];cout<<endl;
		rep(i,b.size())cout<<" "<<b[i];cout<<endl;
	}
};
