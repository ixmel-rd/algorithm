void heihou_bunnkatu(){//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
	int a,b;
	cin>>a>>b;
	vi in(a);
	#define B 200
	vi t(a/B+1);
	while(in.size()%B)in.pb(0);
	while(b--){
		int c,d,e;
		cin>>c>>d>>e;d--;
		if(c==0){
			t[d/B]+=e;
			in[d]+=e;
		}else{
			int sum=0;
			while(d<e){
				if(d%B==0&&d+B<=e){
					sum+=t[d/B];
					d+=B-1;
				}else sum+=in[d];
				d++;
			}
			cout<<sum<<endl;
		}
	}
}
int main(){
	heihou_bunnkatu();
}