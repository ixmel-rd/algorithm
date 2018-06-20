int LIS(vi in){//Longest Increasing Subsequence
	int n=in.size();
	vi out(n+1,inf);
	rep(i,n){
		*lower_bound(all(out),in[i])=in[i];
	}
	return lower_bound(all(out),inf)-out.begin();
}


