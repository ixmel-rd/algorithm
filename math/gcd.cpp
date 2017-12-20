int gcd(int a,int b){
	return (b==0?a:gcd(b,a%b));
}
int extgcd(int a,int b,int &x,int &y){//ax+by=1
	int d=a;
	if(b!=0){
		d=extgcd(b,a%b,y,x);
		y-=(a/b)*x;
	}else{
		x=1;y=0;
	}
	return d;
}
