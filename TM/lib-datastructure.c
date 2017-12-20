#include<stdio.h>
//添字ヒープを使うための関数達!
int R=1,C=1,H[2000010],N[2000010];
//評価関数（いまはMAX）
int hyouka(int a,int b){
  if(C<b)return 1;
  if(C<a||b==0)return 0;
  return N[H[a]]>N[H[b]]?1:0;
}
//挿入関数
void hin(int a){
  int i=C++;
  for(N[H[0]=R]=a;hyouka(0,i/2);i/=2)H[i]=H[i/2];
  H[i]=R++;
}
//取り出す関数
int hout(){
  int rt=H[1],i,j=2,k=H[--C];
  for(i=1;hyouka(i,C);i=j)H[i]=H[j=i*2+1-hyouka(i*2,i*2+1)];
  H[j/2]=k;
  return rt;
}
//ヒープをヒープの形で表示
void prih(){
  int i,j=0;
  for(i=0;i<C;i++){
    if(i==1<<j){
      printf("\n");
      j++;
    }
    printf("%d ",N[H[i]]);
  }
  printf("\n");
}
//---------------------------------------------------------------
//セグメントツリーを使うための関数たち!
//NNは評価関数で選ばれない数値を入れる
int S[4*100010];
int T,NN=2147483647;
//評価関数（今はMIN）
int hyoka(int a,int b){return a<b?a:b;}
//セグ木を長さnの数列dで初期化、構成
void sset(int n,int *d){
  int i;
  for(T=1;T<n;T*=2);
  for(i=0;i<n;i++)S[T+i]=d[i];
  for(   ;i<T;i++)S[T+i]=NN;
  for(i=T-1;i;i--)S[i]=hyoka(S[i*2],S[i*2+1]);
}
//セグ木のupdate関数
//i番目の数値をnに変更、再構成
void sud(int i,int n){for(S[i+=T]=n;i/=2;)S[i]=hyoka(S[i*2],S[i*2+1]);}
//セグ木のfind関数
//[a,b)区間の呼び出しはsout(a,b,1,0,T);
int sout(int a,int b,int i,int l,int r){
  if(r<=a||b<=l)return NN;
  if(a<=l&&r<=b)return S[i];
  return hyoka(sout(a,b,i*2,l,(l+r)/2),sout(a,b,i*2+1,(l+r)/2,r));
}
//--------------------------------------------------------------------------
//添字セグメントツリーを使うための関数たち!
int T,S[4*200010],N[200010];
//評価関数（今はMIN）
int hyoka(int a,int b){return (a<0||b<0)?(a<0?b:a):N[a]<N[b]?a:b;}
//セグ木を長さnの数列dで初期化、構成
void sset(int n){
  int i;
  for(T=1;T<n;T*=2);
  for(i=0;i<T;i++)S[T+i]=i<n?i:-1;
  for(i=T-1;i;i--)S[i]=hyoka(S[i*2],S[i*2+1]);
}
//セグ木のupdate関数
//i番目の数値をnに変更、再構成
void sud(int i,int n){for(N[i+=T]=n;i/=2;)S[i]=hyoka(S[i*2],S[i*2+1]);}
//セグ木のfind関数
//[a,b)区間の呼び出しはsout(a,b,1,0,T);
int sout(int a,int b,int i,int l,int r){//printf("%d %d %d %d %d\n",a,b,i,l,r);
  if(r<=a||b<=l)return -1;
  if(a<=l&&r<=b)return S[i];
  return hyoka(sout(a,b,i*2,l,(l+r)/2),sout(a,b,i*2+1,(l+r)/2,r));
}

//--------------------------------------------------------------------
//BITを使うための関数たち!
//nが要素数
int n,B[100010]={0};
//BITのadd関数
//i番めの数値にnを足す
void badd(int i,int a){for(;i<=n;i+=i&-i)B[i]+=a;}
//BITのsum関数
//1からi番めの数の総和を返す
int  bsum(int i){
  int s=0;
  for(;i;i-=i&-i)s+=B[i];
  return s;
}
//--------------------------------------------------------------------
//Union-Find
int p[100010]={0};
int d[100010]={0};
int Find(int *a,int *b){
  int r,n;
  for(r=++(*a);p[r];r=p[r]);
  for(;n=p[*a];*a=n)p[*a]=r;
  for(r=++(*b);p[r];r=p[r]);
  for(;n=p[*b];*b=n)p[*b]=r;
  return *a-*b?1:0;
}
void Union(int a,int b){
  if(find(&a,&b)){
    d[a]<d[b]?(p[a]=b):(p[b]=a);
    if(d[a]=d[b])d[a]++;
  }
}
//Union-Find
int p[100010]={0};
int d[100010]={0};
int Find(int a,int b){
  for(r=++a;p[r];r=p[r]);
  for(;n=p[a];a=n)p[a]=r;
  for(r=++b;p[r];r=p[r]);
  for(;n=p[b];b=n)p[b]=r;
  return a-b?1:0;
}
void Union(int a,int b){
  if(Find(a,b)){
    for(++a;p[a];a=p[a]);
    for(++b;p[b];b=p[b]);
    d[a]<d[b]?(p[a]=b):(p[b]=a);
    if(d[a]==d[b])d[a]++;
  }
}
//-----------------------------------------------------------------
//平衡二分木を使うための関数たち!
int P[4][200010],H[200010],C[200010],R=1,N[200010];
//評価関数　左子なら負、同じなら0、右子なら正を返す
int hyouka(int i,int x){return x<=N[i]?x<N[i]?-1:0:1;}
//char N[1010][110];
//int hyouka(int i,char *s){return strcmp(s,N[i]);}
//平衡係数を求める関数
int h(int a){return a?H[P[2][a]]-H[P[1][a]]:0;}
//回転させる関数
void rot(int a,int t){//L==1,R==2
  int b=P[3-t][a],r=P[0][a];
  P[1][r]==a?(P[1][r]=b):(P[2][r]=b);
  if(P[t][b])P[0][P[t][b]]=a;
  P[3-t][a]=P[t][b];
  P[t][b]=P[0][b];
  P[0][b]=P[0][a];
  P[0][a]=b;
  C[a]=    C[P[1][a]]+C[P[2][a]] +1;
  H[a]=MAX(H[P[1][a]],H[P[2][a]])+1;
}
//新しい子を作る関数
void make(int p,int t,int x){
  P[t][p]=R;
  P[0][R]=p;
  N[R]=x;//strcpy(N[R],s);
  C[R]=1;
  H[R++]=1;
}
//平衡を保つ関数
void balance(int i){
  int r,t;
  for(;i;i=P[0][i]){
    r=h(i);
    C[i]=    C[P[1][i]]+C[P[2][i]] +1;
    H[i]=MAX(H[P[1][i]],H[P[2][i]])+1;
    t=(r+6)/4;
    if(r/2){
      if(h(P[t][i])*r==-2)rot(P[t][i],t);
      rot(i,3-t);
    }
  }//printf("%d\n",i);
}
//値を探す関数　なければ作って、その値の添字を返す
int mfind(int x){
  int i,j,r,n,t;
  if(P[1][0]==0){
    make(0,1,x);
    return 1;
  }
  for(i=P[1][0];r=hyouka(i,x);i=P[t][i]){//printf("%d %s\n",r,x);
    t=r<0?1:2;
    if(P[t][i]==0)make(i,t,x);
  }
  balance(P[0][i]);
  return i;
}
//その値を消す関数
void delete(int x){
  int n=mfind(x),m=n,r=P[0][m],t,j;
  if(P[1][m]){
    n=P[1][m];
    while(P[2][n])n=P[2][n];
    j=(P[0][n]-m)?P[0][n]:n;
    if(P[1][n])P[0][P[1][n]]=j;
    if(P[0][n]-m){
      P[2][P[0][n]]=P[1][n];
      P[0][P[1][m]]=n;
    }
    if(P[2][m])P[0][P[2][m]]=n;
    if(P[0][n]-m)P[1][n]=P[1][m];
    P[0][n]=P[0][m];
    P[2][n]=P[2][m];
  }
  else{
    n=P[2][m];
    j=n?n:r;
    if(n)P[0][n]=P[0][m];
  }  
  P[1][r]==m?(P[1][r]=n):(P[2][r]=n);
  balance(j);
}
//n(1=index)番目の添字を返す
int numm(int n){//1-index
  int i=P[1][0];
  while(1){//printf("%d\n",i);
    if(n==C[P[1][i]]+1)break;
    if(C[P[1][i]]<n){
      n-=C[P[1][i]]+1;
      i=P[2][i];
    }
    else i=P[1][i];
  }
  return i;
}
//平衡二分木を表示する関数
void prim(int n){
  int i;
  if(P[1][n])prim(P[1][n]);
  for(i=0;i<H[n];i++)printf("     ");
  printf("%d\n",N[n]);
  if(P[2][n])prim(P[2][n]);
}
