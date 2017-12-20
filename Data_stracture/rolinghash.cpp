//ARC055C ABCAC
#define MAX 200020
ll hs[2][MAX];
ll MOD[2]={1000000007,1000000009};
ll x[2]={114514973,114514979};
ll power[2][MAX];
int main(){
	string s;
	cin>>s;
	
	rep(i,2){
		power[i][0]=1;
		rep(j,MAX-1)power[i][j+1]=power[i][j]*x[i]%MOD[i];
	}
	rep(i,2)rep(j,s.size())
		hs[i][j+1]=(hs[i][j]+power[i][j]*(s[j]-'a'))%MOD[i];
	
	ll out=0;
	for(int i=s.size()-2;i*2>s.size();i--){
		if(s[0]!=s[i]||s[i-1]!=s[s.size()-1])continue;
		int n=s.size()-i;
		int l=0,r=n;
		while(r-l>1){
			int h=(l+r)/2;
			bool H=false;
			rep(j,2){
				ll a=(hs[j][h]-hs[j][0]+MOD[j])%MOD[j];
				ll b=(hs[j][i+h]-hs[j][i]+MOD[j])%MOD[j];
				if(a*power[j][i]%MOD[j]==b)H=true;
			}
			if(H)l=h;
			else r=h;
		}
		int L=l;
		l=0,r=n;
		while(r-l>1){
			int h=(l+r)/2;
			bool H=false;
			rep(j,2){
				ll a=(hs[j][i]-hs[j][i-h]+MOD[j])%MOD[j];
				ll b=(hs[j][s.size()]-hs[j][s.size()-h]+MOD[j])%MOD[j];
				if(a*power[j][s.size()-i]%MOD[j]==b)H=true;
			}
			if(H)l=h;
			else r=h;
		}
		int R=l;
		if(L+R>=n)out+=L+R-n+1;
	}
	cout<<out<<endl;
}
