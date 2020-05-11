//oira- phi kansu
// nと互いに素なi(1<=i<=n)の個数
// O(sqrt(n))
// n=12 -> 1,5,7,11 (out=4)
int eulerPhi(int n){
	int out=n;
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			out-=out/i;
			while(n%i==0)n/=i;
		}
	}
	if(n>1)out-=out/n;
	return out;
}
