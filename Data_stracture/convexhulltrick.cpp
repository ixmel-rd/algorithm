class CHT{//http://satanic0258.hatenablog.com/entry/2016/08/16/181331
	public:
	// 直線群(配列)
	vp lines;
	// 最小値(最大値)を求めるxが単調であるか
	bool isMonotonicX;
	// 最小/最大を判断する関数 初期min l<=rならmax
	bool comp(Def l,Def r){
		return l>=r;
	}

	// コンストラクタ ( クエリが単調であった場合はflag = trueとする )
	// compFunc (初期値はmin) l<=rならmax
	CHT(bool flagX=false){
		isMonotonicX=flagX;
	};

	// 直線l1, l2, l3のうちl2が不必要であるかどうか
	bool check(pii l1,pii l2,pii l3){
		if(l1<l3)swap(l1,l3);
		return (l3.second-l2.second)*(l2.first-l1.first)>=(l2.second-l1.second)*(l3.first-l2.first);
	}

	// 直線y=ax+bを追加する
	void add(Def a,Def b) {
		pii line(a,b);
		while(lines.size()>=2&&check(*(lines.end()-2),lines.back(),line))
			lines.pop_back();
		lines.emplace_back(line);
	}
	// i番目の直線f_i(x)に対するxの時の値を返す
	Def f(Def i, Def x) {
		return lines[i].first*x+lines[i].second;
	}
	// i番目の直線f_i(x)に対するxの時の値を返す
	Def f(pii line,Def x) {
		return line.first*x+line.second;
	}
	// 直線群の中でxの時に最小(最大)となる値を返す
	Def get(Def x){
		// 最小値(最大値)クエリにおけるxが単調
		if(isMonotonicX){
			static int head = 0;
			while(lines.size()-head>=2&&comp(f(head,x),f(head+1,x)))head++;
			return f(head,x);
		}else{
			int low=-1,high=lines.size()-1;
			while(high-low>1){
				int mid=(high+low)/2;
				(comp(f(mid,x),f(mid+1,x))?low:high)=mid;
			}
			return f(high,x);
		}
	}
};
int main(){//https://beta.atcoder.jp/contests/colopl2018-final-open/tasks/colopl2018_final_c
	int n;
	cin>>n;
	CHT cht(0);
	rep(i,n){
		int a;cin>>a;
		cht.add(-2*i,a+i*i);
	}
	rep(i,n)cout<<cht.get(i)+i*i<<endl;
}
