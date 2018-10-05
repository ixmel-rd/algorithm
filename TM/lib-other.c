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
//線形計画法を解く関数たち
double M[10][30]={};
//本体　シンプレックス法
int Simplex(int h,int w,int *ans){
  int i,j,mi,mj,k=w;
  double t,eps=1e-9;
  while(k--){
    mi=mj=-1;
    for(j=0;j<w;j++){
      if(M[h][j]+eps>0)continue;
      if(mj==-1||M[h][j]<M[h][mj])mj=j;
    }
    if(mj==-1)return 0;
    for(i=0;i<h;i++){
      if(M[i][w]/M[i][mj]+eps<0)continue;
      if(mi==-1||M[i][w]/M[i][mj]<M[mi][w]/M[mi][mj])mi=i;
    }
    if(mi==-1)return 2;
    t=M[mi][mj];
    for(j=0;j<=w;j++)M[mi][j]/=t;
    for(i=0;i<=h;i++){
      t=i==mi?0:M[i][mj];
      for(j=0;j<=w;j++)M[i][j]-=M[mi][j]*t;
    }
    ans[mi]=mj;
  }
  return 1;
}
//呼ぶ方
//MAX z=c^tx  Ax op(<= 0,= 1,>= 2) b
//h式の数　w変数の数
//return 0 正常終了 1:解ナシ 2:バグ
//d[h][w+h]が答え
//x_ans[i]==d[i][w+h]　other x==0
int senkei(int h,int w,double A[10][30],double *b,double *c,int *op,int *ans){
  double t;
  int i,j;
  for(i=0;i<h;i++){
    for(j=0;j<w;j++)M[i][j]=A[i][j];
    if(op[i]==0)M[i][w+i]=M[h][w+i]=1;
    if(op[i]==2){
      M[i][w+i]=-1;
      M[i][w+h+i]=M[h][w+h+i]=1;
    }
    M[i][w+h+h]=c[i];
    ans[i]=w+h*(op[i]/2)+i;
  }
  for(i=0;i<h;i++){
    t=ans[i]<h+w?0:M[h][ans[i]];
    for(j=0;j<=w+h+h;j++)M[h][j]-=M[i][j]*t;
  }
  if(i=Simplex(h,w+h+h,ans))return i;
  for(i=0;i<=h;i++)M[i][h+w]=M[i][w+h+h];
  for(j=0;j< w;j++)M[h][j]=-b[j];
  for(j=0;j<=h;j++)M[h][w+j]=0;
  for(i=0;i<h;i++){
    t=M[h][ans[i]];
    for(j=0;j<=h+w;j++)M[h][j]-=M[i][j]*t;
  }
  return Simplex(h,h+w,ans);
}
