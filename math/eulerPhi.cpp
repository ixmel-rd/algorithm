//oira- phi kansu
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
int main(){
	int n;
	cin>>n;
	cout<<eulerPhi(n)<<endl;
}