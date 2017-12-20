//ARC038C
typedef int SegT;
const int defvalue=inf;
class SegTree{
	public:
		vector<SegT>val;
		int n;
		SegT combine(SegT a,SegT b){return min(a,b);}
		SegTree(int size){
			n=1;
			while(n<size)n<<=1;
			val=vector<SegT>(2*n,defvalue);
		}
		SegTree(const vector<SegT> &in){
			n=1;
			while(n<in.size())n<<=1;
			val=vector<SegT>(2*n,defvalue);
			for(int i=n-1+in.size()-1;i>=0;i--){
				if(n-1<=i)val[i]=in[i-(n-1)];
				else val[i]=combine(val[i*2+1],val[i*2+2]);
			}
		}
		void update(int i,SegT a){
			i+=n-1;
			val[i]=a;
			while(i>0){
				i=(i-1)/2;
				val[i]=combine(val[i*2+1],val[i*2+2]);
			}
		}
		SegT query(int a,int b,int k=0,int l=0,int r=-1){//[a,b)
			if(r==-1)r=n;
			if(r<=a||b<=l)return defvalue;
			if(a<=l&&r<=b)return val[k];
			else return combine(query(a,b,k*2+1,l,(l+r)/2),query(a,b,k*2+2,(l+r)/2,r));
		}
		void tmp(){
			rep(i,val.size())cout<<" "<<val[i];cout<<endl;
		}
};
int main(){
	int n;
	cin>>n;
	vi in(n-1),co(n-1);
	rep(i,n-1)cin>>in[i]>>co[i];
	SegTree st(n);
	rep(i,st.n)st.update(i,-1);
	st.update(0,0);
	vi grundy(n-1);
	rep(i,n-1){
		int t=i+1-in[i];
		int r=0,l=n+1;
		while(l-r>1){
			int h=(l+r)/2;
			int k=st.query(0,h);
			if(k>=t)r=h;
			else l=h;
		}
		grundy[i]=r;
		st.update(r,i+1);
	}
	int out=0;
	rep(i,n-1)out^=(co[i]%2)*grundy[i];
	if(out)cout<<"First"<<endl;
	else cout<<"Second"<<endl;
}
