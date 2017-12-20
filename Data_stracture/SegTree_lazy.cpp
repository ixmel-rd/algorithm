// http://tsutaj.hatenablog.com/entry/2017/03/30/224339
//Range Add Query and Range Sum Query
typedef ll SegT;
const SegT defvalue=0;
struct LSTree{
public:
	int n;
	vector<SegT>node,lazy;
	SegT combine(SegT a,SegT b){return a+b;}
	LSTree(const vector<SegT> &v) {
		n=1;
		while(n<v.size())n<<=1;
		node=vector<SegT>(2*n,defvalue);
		lazy=vector<SegT>(2*n,defvalue);
		for(int i=n-1+v.size()-1;i>=0;i--){
			if(n-1<=i)node[i]=v[i-(n-1)];
			else node[i]=combine(node[i*2+1],node[i*2+2]);
		}
	}
	void eval(int k,int l,int r) {
		if(lazy[k]!= 0){
			node[k]+=lazy[k];
			if(r-l>1) {
				lazy[2*k+1]+=lazy[k]/2;
				lazy[2*k+2]+=lazy[k]/2;
			}
			lazy[k]=0;
		}
	}
	void update(int a,int b,SegT x,int k=0,int l=0,int r=-1){
		if(r<0)r=n;
		eval(k,l,r);
		if(b<=l||r<=a)return;
		if(a<=l&&r<=b){
			lazy[k]+=(r-l)*x;
			eval(k,l,r);
		}else{
			update(a,b,x,2*k+1,l,(l+r)/2);
			update(a,b,x,2*k+2,(l+r)/2,r);
			node[k]=combine(node[2*k+1],node[2*k+2]);
		}
	}
	SegT query(int a,int b,int k=0,int l=0,int r=-1){
		if(r<0)r=n;
		eval(k,l,r);
		if(b<=l||r<=a)return 0;
		if(a<=l&&r<=b)return node[k];
		else return combine(query(a,b,2*k+1,l,(l+r)/2),query(a,b,2*k+2,(l+r)/2,r));
	}
	void tmp(){
		rep(i,node.size())cout<<" "<<node[i];cout<<endl;
		rep(i,node.size())cout<<" "<<lazy[i];cout<<endl;
		cout<<endl;
	}
};
int main() {
	int n,q;
	cin>>n>>q;
    LSTree st(vector<ll>(n,0));
	while(q--){
		int a,s,t,x;
		cin>>a>>s>>t;
		if(!a)cin>>x;
		if(!a)st.update(s-1,t,x);
		else cout<<st.query(s-1,t)<<endl;
	}
}