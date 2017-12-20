ll nCr(int n,int r){
	return (r==0|| n==r) ? 1 : nCr(n-1,r) + nCr(n-1,r-1);
}
