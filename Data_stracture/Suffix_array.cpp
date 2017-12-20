namespace SuffixArray {
	template<class T>
	void induce(int n,const vector<T>& s,vector<bool>& ls,vi& sa,vi& l_basm,int B){
		vi buf=l_basm;
		rep(i,n+1){
			if (sa[i]>=1&&!ls[sa[i]-1]){
				int bc = s[sa[i]-1];
				sa[buf[bc]++] = sa[i]-1;
			}
		}
		buf=l_basm;
		for(int i=n;i>0;i--) {
			if(sa[i]>=1&&ls[sa[i]-1]){
				int bc=s[sa[i]-1];
				sa[--buf[bc+1]]=sa[i]-1;
			}
		}
	}
	template<class T>
	void SA(int n,const vector<T>& s,vi& sa,int B=200){
		vector<bool>ls(n+1);//L:false S:true
		vi l_ba(B+1),s_ba(B+1);
		ls[n]=true;
		for(int i=n-1;i>=0;i--) {
			if(i==n-1||s[i]>s[i+1])ls[i]=false;
			else if(s[i]<s[i+1])ls[i]=true;
			else ls[i]=ls[i+1];
			if(!ls[i])l_ba[(int)s[i]]++;
			else s_ba[(int)s[i]]++;
		}
		vi v,lms(n+1,-1);
		int c=0;
		loop(i,1,n)if(!ls[i-1]&&ls[i]){
			lms[i]=c++;
			v.pb(i);
		}
		vi l_basm(B+1),s_basm(B+1);
		l_basm[0]=1;s_basm[0]=1+l_ba[0];
		loop(i,1,B+1){
			l_basm[i]=s_basm[i-1]+s_ba[i-1];
			s_basm[i]=l_basm[i]+l_ba[i];
		}
		if(v.size()){
			vi v2=v;
			vi buf=s_basm;
			sa=vi(n+1,-1);
			sa[0]=n;
			rep(i,v.size()){
				int c=s[v[i]];
				sa[buf[c]++]=v[i];
			}
			induce(n,s,ls,sa,l_basm,B);
			int c=0;
			loop(i,1,n+1)if(lms[sa[i]]!=-1)v[c++]=sa[i];
			vi s2(v.size());
			vi sa2(v.size()+1);
			c=0;
			s2[lms[v[0]]]=0;
			loop(i,1,v.size()){
				int l=v[i-1],r=v[i];
				while(1){
					if(s[l]!=s[r]){c++;break;}
					l++;r++;
					if(lms[l]!=-1||lms[r]!=-1){
						if(lms[l]==-1||lms[r]==-1)c++;
						break;
					}
				}
				s2[lms[v[i]]]=c;
			}
			SA(v.size(),s2,sa2,c);
			loop(i,1,v.size()+1)v[i-1]=v2[sa2[i]];
		}
		vi buf=s_basm;
		sa=vi(n+1,-1);
		sa[0]=n;
		rep(i,v.size()){
			int c=s[v[i]];
			sa[buf[c]++]=v[i];
		}
		induce(n,s,ls,sa,l_basm,B);
	}
	template <class T>
	void LCP(int n,const vector<T>& s,const vi& sa,vi& lcp) {
		vi rsa(n+1);
		rep(i,n+1)rsa[sa[i]]=i;
		int h=0;
		rep(i,n){
			int j=sa[rsa[i]-1];
			if(h>0)h--;
			for(;j+h<n&&i+h<n;h++)if(s[j+h]!=s[i+h])break;
			lcp[rsa[i]-1]=h;
		}
	}
}
int main(){
	vector<char>s;
	char c;
	while(cin>>c)s.pb(c);
	int n=s.size();
	static vi sa(100100),lcp(100100);
	SuffixArray::SA(n,s,sa);
	SuffixArray::LCP(n,s,sa,lcp);
	ll out=0;
	loop(i,1,n+1)out+=(long long)(n-sa[i])*(n-sa[i]+1)/2-(ll)lcp[i]*(lcp[i]+1)/2;
	cout<<out<<endl;
}
