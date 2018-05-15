//AOJ 2848 takoyaki
typedef int SegT;
const SegT defvalue=0;
SegT combine(SegT a,SegT b){return a+b;}
class SegTree{
	public:
		vector<SegT>val;
		int n;
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
			val[i]+=a;
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
		SegT get(int x){
			return val[n-1+x];
		}
		void tmp(){
			rep(i,val.size())cout<<" "<<val[i];cout<<endl;
		}
};
class SegTree_2d{
	public:
		vector<SegTree>val;
		int n;
		SegTree_2d(int h,int w){
			n=1;
			while(n<h)n<<=1;
			val=vector<SegTree>(2*n,SegTree(w));
		}
		SegTree_2d(const vector<vector<SegT> > &in){
			n=1;
			while(n<in.size())n<<=1;
			val=vector<SegTree>(2*n,SegTree(in[0].size()));
			for(int i=n-1+in.size()-1;i>=0;i--){
				if(i-(n-1)<0)
					rep(j,val[i].val.size())
						val[i].val[j]=combine(val[i*2+1].val[j],val[i*2+2].val[j]);
				else val[i]=SegTree(in[i-(n-1)]);
			}
		}
		void update(int x,int y,SegT a){
			x+=n-1;
			val[x].update(y,a);
			while(x>0){
				x=(x-1)/2;
				val[x].update(y,a);
//				val[x].update(y,combine(val[x*2+1].val[y+n-1],val[x*2+2].val[y+n-1]));
			}
		}
		SegT query(int x1,int y1,int x2,int y2,int k=0,int l=0,int r=-1){//[a,b)
			if(r==-1)r=n;
			if(r<=x1||x2<=l)return defvalue;
			if(x1<=l&&r<=x2)return val[k].query(y1,y2);
			else return combine(query(x1,y1,x2,y2,k*2+1,l,(l+r)/2),query(x1,y1,x2,y2,k*2+2,(l+r)/2,r));
		}
		SegT get(int x,int y){
			return val[n-1+x].get(y);
		}
		void tmp(){
			rep(i,val.size())val[i].tmp();
		}
};
int main(){
	int n,m,T,q;
	cin>>n>>m>>T>>q;
	SegTree_2d st1(n,m),st2(n,m);
	vvi ma;
	while(q--){
		int t,c;cin>>t>>c;
		int x1,x2,y1,y2;
		cin>>x1>>y1;
		if(c==2)cin>>x2>>y2;
		x1--,y1--;
		while(ma.size()&&ma[0][0]<=t){
			st1.update(ma[0][1],ma[0][2],-1);
			st2.update(ma[0][1],ma[0][2],1);
			ma.erase(ma.begin());
		}
		if(c==0){
			st1.update(x1,y1,1);
			ma.pb({t+T,x1,y1});
		}else if(c==1){
			if(st2.get(x1,y1))st2.update(x1,y1,-1);
		}else{
			cout<<st2.query(x1,y1,x2,y2)<<" "<<st1.query(x1,y1,x2,y2)<<endl;
		}
	}
}
