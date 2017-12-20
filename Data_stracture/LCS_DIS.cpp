int DIS(string s,string t){
	//編集距離
	vvi dp(s.size()+2,vi(t.size()+2,inf));
	dp[0][0]=0;
	rep(i,s.size()+1)rep(j,t.size()+1){
		if(i<s.size()&&j<t.size()&&s[i]==t[j])dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]);
		dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]+1);
		dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);
		dp[i][j+1]=min(dp[i][j+1],dp[i][j]+1);
	}
	return dp[s.size()][t.size()];
}
//--------------------------------------
int LCS(string s,string t){
	vvi dp(s.size()+1,vi(t.size()+1));
	rep(i,s.size())rep(j,t.size()){
		if(s[i]==t[j])dp[i+1][j+1]=max(dp[i+1][j+1],dp[i][j]+1);
		dp[i+1][j+1]=max(dp[i+1][j+1],max(dp[i+1][j],dp[i][j+1]));//
	}
	return dp[s.size()][t.size()];
}
string LCS(string &a,string &b){
	const int LMAX=300;
	int m=a.size(),n=b.size();
	int dp[LMAX+1][LMAX+1],from[LMAX+1][LMAX+1];
	rep(i,m+1)dp[i][0]=0,from[i][0]=-1;
	rep(i,n+1)dp[0][i]=0,from[0][i]=-1;
	rep(i,m)rep(j,n){
		if(a[i]==b[j]){
			dp[i+1][j+1]=dp[i][j]+1;
			from[i+1][j+1]=2;
		}else{
			if(dp[i][j+1]<dp[i+1][j]){
				dp[i+1][j+1]=dp[i+1][j];
				from[i+1][j+1]=1;
			}else{
				dp[i+1][j+1]=dp[i][j+1];
				from[i+1][j+1]=0;
			}
		}
	}
	int idx=dp[m][n];
	string out(idx,'!');
	for(int i=m,j=n;~from[i][j];){
		switch(from[i][j]){
			case 0:i--;break;
			case 1:j--;break;
			case 2:i--;j--;idx--;out[idx]=a[i];break;
		}
	}
	return out;
}






