//yukicoder 515
//http://tookunn.hatenablog.com/entry/2016/07/13/211148
//
//RMQ  ----  make:O(NlogN) update:muri query:O(1)
//
typedef int SegT;
const int defvalue=0;
class ST{//Sparse_table
	public:
		vector<SegT> A,log_table;
		vector<vector<SegT> >table;
		int n;
		SegT combine(SegT a,SegT b){return min(a,b);}
		ST(const vector<SegT> &in){
			n=in.size();
			A=in;
			log_table=vector<SegT>(n+1);
			loop(i,2,n+1)log_table[i]=log_table[i>>1]+1;
			table=vector<vector<SegT> >(n,vector<SegT>(log_table[n]+1));
			rep(i,n)table[i][0]=i;
			for(int k=1;(1<<k)<=n;k++){
				for(int i=0;i+(1<<k)<=n;i++){
					int first=table[i][k-1];
					int second=table[i+(1<<(k-1))][k-1];
					if(A[first]<A[second])table[i][k]=first;
					else table[i][k]=second;
				}
			}
		}
		SegT query(int s,int t){//[a,b] 0-index
			if(s>t)assert(1);
			int d=t-s+1;
			int k=log_table[d];
			int out;
			if(A[table[s][k]]<A[table[t-(1<<k)+1][k]])
				out=table[s][k];
			else out=table[t-(1<<k)+1][k];
//			return out;
			return A[out];
		}
		void tmp(){
			rep(i,n){
				rep(j,log_table[n]+1)cout<<" "<<table[i][j];
				cout<<endl;
			}
		}
};
