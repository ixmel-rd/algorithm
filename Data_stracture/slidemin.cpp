vi slidemin(const vi &a,int k){
	int n=a.size();
	deque<int>deq;
	vi res;
	rep(i,n){
		while(deq.size()&&a[deq.back()]>=a[i])deq.pop_back();
		deq.pb(i);
		if(i-k+1>=0){
			res.pb(deq.front());
			if(deq.front()==i-k+1)deq.pop_front();tubo
//			while(deq.front()<=j-B+1)deq.pop_front();kyuri
		}
	}
	return res;
}