//LCP of s and s[i:s.size()-1]
//aaabaaaab
//921034210
struct Z{
	vi a;
	Z(){}
	Z(string& s):a(s.size()){
		a[0]=s.size();
		int i=1,j=0;
		while(i<s.size()){
			while(i+j<s.size()&&s[j]==s[i+j])j++;
			a[i]=j;
			if(j==0){i++;continue;}
			int k=1;
			while(i+k<s.size()&&k+a[k]<j)a[i+k]=a[k],k++;
			i+=k;j-=k;
		}
	}
};
int main(){
	string s;
	cin>>s;
	Z a(s);
	reverse(all(s));
	Z b(s);
	reverse(all(s));
	ll out=0;
	int n=s.size();
	for(int i=n-2;i*2>n;i--)if(s[0]==s[i]&&s[i-1]==s[s.size()-1]){
		int t=n-i;
		int l=a.a[i];
		int r=min(n-i,b.a[t]);
		if(l==t)l--;
		if(r==t)r--;
		if(l+r>=t)out+=l+r-t+1;
	}
	cout<<out<<endl;
}
