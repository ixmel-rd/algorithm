int det(vvi mat){
	ll n=mat.size();
	ll out=1;
	rep(i,n){
		int pivot=i;
		loop(j,i+1,n)if(abs(mat[j][i])>abs(mat[pivot][i]))pivot=j;
		swap(mat[pivot],mat[i]);
		out*=mat[i][i]*(i!=pivot?-1:1);
		if(abs(mat[i][i])==0)break;
		loop(j,i+1,n)for(int k=n-1;k>=i;k--){
			mat[j][k]-=mat[i][k]*mat[j][i]/mat[i][i];
			if(mat[j][k]==-1)mat[j][k]=1;
		}
	}
	return out;
}
