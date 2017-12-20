#define N 1000
#define MOD 100000000
class Calc{
    public:
    ll carry, borrow,w,remainder;
	ll z[N];
	void ladd(ll a[], ll b[]){
		carry=0;
		for(int i=N-1;i>=0;i--){
			z[i]=a[i]+b[i]+carry;
			if(z[i]<MOD)carry=0;
			else{
				z[i]-=MOD;
				carry=1;
			}
		}
	}
	void lsub(ll a[], ll b[]){
		borrow=0;
		for(int i=N-1;i>=0;i--){
			z[i]=a[i]-b[i]-borrow;
			if(z[i]>=0)borrow=0;
			else{
				z[i]+=MOD;
				borrow=1;
			}
		}
	}
	void lmul(ll c[], ll d){
		carry=0;
		for(int i=N-1;i>=0;i--){
			w=c[i];
			z[i]=(w*d+carry)%MOD;
			carry=(w*d+carry)/MOD;
		}
	}
	void ldiv(ll c[],ll d){
		remainder=0;
		for(int i=0;i<N;i++){
			w=c[i];
			z[i]=(w+remainder)/d;
			remainder=((w+remainder)%d)*MOD;
		}
	}
	void displayL(ll s[]){
		int t=0;
		for(;t<N;t++)if(s[t]){
			printf("%d",s[t]);
			break;
		}
		for(t++;t<N;t++)printf("%08d",s[t]);
		printf("\n");
	}
	void displayS(ll s){
		for(int i=0;i<N-1;i++)printf("%8s"," ");
		printf("%08d\n",s);
	}
};
