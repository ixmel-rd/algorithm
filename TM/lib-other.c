#include<stdio.h>
int MIN(int a,int b){return a<b?a:b;}
double dMIN(double a,double b){return a<b?a:b;}
//大きい方を返す!
int MAX(int a,int b){return a<b?b:a;}
//最小経路の更新等!
int zMIN(int a,int b){return a*b?MIN(a,b):a+b;}
//数字を二進数表示　kは表示桁0詰め
void prib(int a,int k){while(k--)printf("%d",(a>>k)%2);}
//最大公約数を求める!
int gcd(int a,int b){return b?gcd(b,a%b):a;}
//最小公倍数を求める!
int lcm(int a,int b){return a*(b/gcd(a,b));}
//mを法としたaのn乗!
int mbk(long long a,int n,int m){return n?(mbk((a*a)%m,n/2,m)*(n%2?a:1))%m:1;}
//mを法としたaの逆元!
int inv(int a,int m){return mbk((long long)a,m-2,m);}
//mを法としたaCb!
int aCb(int a,int b,int m){
  long long s=1,i;
  if(b>a-b)b=a-b;
  for(i=0;i<b;i++)s=(((s*(a-i))%m)*inv(i+1,m))%m;  
  return (int)s;
}
//東、南、西、北!
int Y[]={0,1,0,-1};
int X[]={1,0,-1,0};

//lower_bound/upper_bound![l:r]
//添字lから添字rまでの、昇順に並んだdからn「以上」の値が初めて出てくる添字を返す
//return の=をとれば「より大きい」になる
int lub(int l,int r,int n,int *d){
  int m=(l+r)/2;
  if(l==r)return m;
  return n<=d[m]?lub(l,m,n,d):lub(m+1,r,n,d);
}
//長さn数列dの最長増加部分文字列のながさを返す!
int lis(int n,int *d){
  int r=0,i,s[10000]={d[0]};
  for(i=1;i<n;i++)s[r]<d[i]?(s[++r]=d[i]):(s[lub(0,r,d[i],s)]=d[i]);
  return r+1;
}
