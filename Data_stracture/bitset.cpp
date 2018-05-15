//AGC 020
int main(){
	
	bitset<4000010>dp(1);
	int n;
	cin>>n;
	int sum=0;
	rep(i,n){
		int a;cin>>a;
		sum+=a;
		dp|=dp<<a;
	}
	loop(i,(sum+1)/2,1000000000)if(dp[i]){
		cout<<i<<endl;
		return 0;
	}
}
