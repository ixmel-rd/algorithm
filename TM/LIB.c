#include<stdio.h>
#include<string.h>
#include<math.h>
#define M 100000000
//小さい方を返す!
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
//隣接リストを作る
int ta[100010],nt[200010],to[200010],co[200010];
//無向グラフ
void mkls(int v,int e,int *a,int *b,int *c){
  int i;
  for(i=0;i<v;i++)ta[i]=-1;
  for(i=0;i<e;i++){
    nt[i  ]=ta[to[i+e]=a[i]];
    nt[i+e]=ta[to[i  ]=b[i]];
    co[ta[b[i]]=i+e]=co[ta[a[i]]=i]=c[i];
  }
}
//有向グラフ
void mklsd(int v,int e,int *a,int *b,int *c){
  int i;
  for(i=0;i<v;i++)ta[i]=-1;
  for(i=0;i<e;i++){
    nt[i]=ta[a[i]];
    to[i]=b[i];
    co[ta[a[i]]=i]=c[i];
  }
}
//トポロジカルソート
//qにソートされたノード番号が入る
int q[10010];
int topo(int v,int e,int *a,int *b){
  int ta[10010],nt[100010],i,t,r,c[10010]={0};
  for(i=0;i<e;i++)c[b[i]]++;
  for(i=r=0;i<v;i++){
    ta[i]=-1;
    if(c[i]==0)q[r++]=i;
  }
  for(i=0;i<e;i++){
    nt[i]=ta[a[i]];
    ta[a[i]]=i;
  }
  for(t=0;t<v;t++){
    for(i=ta[q[t]];i+1;i=nt[i]){
      if(--c[b[i]]==0)q[r++]=b[i];
    }
  }
  return r;
}
//ElogVのダイクストラ!
//頂点数v、辺の数eのグラフでfr[i]からto[i]にco[i]の辺がはられている
//COにmiからの最小コストが入る
int CO[100010];
void dijk(int v,int e,int *fr,int *to,int *co,int mi){
  int i,id[100010],ta[100010],nt[100010],f[100010]={0};
  for(i=0;i<v;i++)ta[i]=-1;
  for(i=0;i<v;i++)CO[i]=1000000000;
  for(i=CO[mi]=0;i<e;i++){
    nt[i]=ta[fr[i]];
    ta[fr[i]]=i;
  }
  while(f[mi]-1){
    f[mi]=1;
    for(i=ta[mi];i+1;i=nt[i]){
      if(CO[to[i]]>CO[mi]+co[i])hin(CO[id[R]=to[i]]=CO[mi]+co[i]);
    }
    while(f[mi]&&C-1)mi=id[hout()];
  }
}
//ワーシャルフロイド
//頂点数v、辺数eのグラフでaからbにコストcの辺がはられている
int d[1000][1000];
int M=2100000000;
int wafl(int v,int e,int *a,int *b,int *c){
  int i,j,k;
  for(i=0;i<v;i++){
    for(j=0;j<v;j++)d[i][j]=M;
    d[i][i]=0;
  }
  for(i=0;i<e;i++)d[a[i]][b[i]]=c[i];
  for(k=0;k<v;k++){
    for(i=0;i<v;i++){
      for(j=0;j<v;j++){
	if(d[i][k]==M||d[k][j]==M)continue;
	if(d[i][j]>d[i][k]+d[k][j])d[i][j]=d[i][k]+d[k][j];
      }
    }
  }
  for(i=0;i<v;i++){
    if(d[i][i])return 1;
  }
  return 0;
}
//ベルマンフォード
//頂点数v、辺の数eのグラフでfr[i]からto[i]にco[i]の辺がはられている
//Cにsからの最小コストが入る
int C[100010]={0};
int blmn(int v,int e,int s,int *fr,int *to,int *co){
  int i,j,f;
  for(i=0;i<v;i++)C[i]=1000000000;
  for(i=C[s]=0;i<v;i++){
    for(j=0;j<e;j++){
      if(C[fr[j]]-1000000000&&C[to[j]]>C[fr[j]]+co[j]){
	C[to[j]]=C[fr[j]]+co[j];
	if(i==v-1)return 1;
      }
    }
  }
  return 0;
}

//最大流のための関数たち!
//本体
int ta[1010],to[1000010],nt[1000010],co[1000010],F[1010];
int MF(int s,int t,int e,int min){
  if(s==t||min==0)return min;
  int i,r;
  F[s]=1;
  for(i=ta[s];i+1;i=nt[i]){
    if(F[to[i]])continue;
    r=MF(to[i],t,e,MIN(min,co[i]));
    co[i]-=r;
    co[(i+e)%(2*e)]+=r;
    if(r)return r;
  }
  return 0;
}
//呼び出す方
//sからtへの最大流を求める　ノード数v辺の数e　aからbへキャパcのフローが流れる
int maxf(int s,int t,int v,int e,int *a,int *b,int *c){
  int i,f,r;
  for(i=0;i<v;i++)ta[i]=-1;
  for(i=0;i<e;i++){
    nt[i  ]=ta[to[i+e]=a[i]];
    nt[i+e]=ta[to[i  ]=b[i]];
    co[ta[a[i]]=i  ]=c[i];
    co[ta[b[i]]=i+e]=0;
  }
  for(f=0;r=MF(s,t,e,1000000000);f+=r){
    for(i=0;i<v;i++)F[i]=0;
  }
  return f;
}
/*//Vは頂点の数,Dは隣接行列　　自分で作る
int V,D[1000][1000]={0};
int F[1000]={0};
//本体
int MF(int s,int t,int min){
  if(s==t)return min;
  int i,r;
  F[s]=1;
  for(i=0;i<V;i++){
    if(F[i]||D[s][i]==0)continue;
    r=MF(i,t,MIN(min,D[s][i]));
    D[s][i]-=r;
    D[i][s]+=r;
    if(r)return r;
  }
  return 0;
}
//呼び出す方
//sからtまでの最大流を求める
int maxf(int s,int t){
  int i,a,b=0;
  for(;a=MF(s,t,10000000);b+=a){
    for(i=0;i<V;i++)F[i]=0;
  }
  return b;
}
//*/
//木の直径を求めるための関数たち!
int ta[100010],nt[200010],to[200010],co[200010],g;
//本体
int bfs(int v,int s){
  int q[1000000],C[100010],t=0,r=1,i,max=0;
  for(i=0;i<v;i++)C[i]=1000000000;
  for(C[q[0]=s]=0;r-t;t++){
    for(i=ta[q[t]];i+1;i=nt[i]){
      if(C[to[i]]>C[q[t]]+co[i])C[q[r++]=to[i]]=C[q[t]]+co[i];
      if(max<C[to[i]])max=C[g=to[i]];
    }
  }
  return max;
}//*/
//呼び出す方
//頂点数v、辺数eのaからbにコストcの辺がはられた木の直径を求める
int tyokkei(int v,int e,int *a,int *b,int *c){
  int i,max=0,j;
  for(i=0;i<v;i++)ta[i]=-1;
  for(i=0;i<e;i++){
    nt[i  ]=ta[to[i+e]=a[i]];
    nt[i+e]=ta[to[i  ]=b[i]];
    co[ta[b[i]]=i+e]=co[ta[a[i]]=i]=c[i];
  }
  bfs(v,0);
  return bfs(v,g);
}
//最小全域木（クラスカル法）!
int mitr(int v,int e,int *a,int *b,int *c){
  int i,r,n,s=0,mi,d[100010]={0};
  int p[100010]={0};
  for(i=0;i<e;i++)hin(c[i]);
  for(i=0;i<e;i++){
    mi=hout()-1;
    for(r=++a[mi];p[r];r=p[r]);
    for(;n=p[a[mi]];a[mi]=n)p[a[mi]]=r;
    for(r=++b[mi];p[r];r=p[r]);
    for(;n=p[b[mi]];b[mi]=n)p[b[mi]]=r;
    if(a[mi]-b[mi]){
      s+=c[mi];
      d[a[mi]]<d[b[mi]]?(p[a[mi]]=b[mi]):(p[b[mi]]=a[mi]);
      if(d[a[mi]]==d[b[mi]])d[a[mi]]++;
    }
  }
  return s;
}
//強連結成分分解!
//cmpにはそのノードの強連結成分の一つのノードが入る（同じ強連結では同じノード）
int cmp[100010],r=0,f[10010];
void sdfs(int e,int s,int k,int *ta,int *to,int *nt,int *id){
  int i;
  f[s]++;
  for(i=ta[s];i+1;i=nt[i]){
    if(i<e&&k<0&&f[to[i]]<0||i>=e&&k>=0&&!f[to[i]])sdfs(e,to[i],k,ta,to,nt,id);
  }
  k<0?(id[r++]=s):(cmp[s]=k);
}
void scc(int v,int e,int *a,int *b){
  int ta[10010],to[60010],nt[60010],id[10010],i,k;
  for(i=0;i<v;i++)f[i]=ta[i]=-1;
  for(i=0;i<e;i++){
    nt[i  ]=ta[to[i+e]=a[i]];
    nt[i+e]=ta[to[i  ]=b[i]];
    ta[a[i]]=i;
    ta[b[i]]=i+e;
  }
  for(i=k=0;i<v;i++){
    if(f[i]==-1)sdfs(e,i,-1,ta,to,nt,id);
  }
  for(i=r;i;i--){
    if(f[id[i-1]]==0)sdfs(e,id[i-1],id[i-1],ta,to,nt,id);
  }
}
/*int ta[10010],to[60010],nt[60010],id[10010],cmp[100010],r=0,f[10010]={0};
void sdfs(int e,int s,int k){
  int i;
  f[s]++;
  for(i=ta[s];i+1;i=nt[i]){
    if(i<e&&k<0&&f[to[i]]==0||i>=e&&k>=0&&f[to[i]]==1)sdfs(e,to[i],k);
  }
  k<0?(id[r++]=s):(cmp[s]=k);
}
//呼び出す方
void scc(int v,int e,int *a,int *b){
  int i,k;
  for(i=0;i<v;i++)ta[i]=-1;
  for(i=0;i<e;i++){
    nt[i  ]=ta[to[i+e]=a[i]];
    nt[i+e]=ta[to[i  ]=b[i]];
    ta[a[i]]=i;
    ta[b[i]]=i+e;
  }
  for(i=k=0;i<v;i++){
    if(f[i]==0)sdfs(e,i,-1);
  }
  for(i=r;i;i--){
    if(f[id[i-1]]==1)sdfs(e,id[i-1],id[i-1]);
  }
  }//*/

//強連結成分分解した後に辺の再構成を行う
void reco(int v,int e){
  int i,j,b;
  for(i=0;i<v;i++){
    if(i==cmp[i])continue;
    for(j=ta[i];nt[j]+1;j=nt[j]);
    nt[j]=ta[cmp[i]];
    ta[cmp[i]]=ta[i];
    ta[i]=-1;
  }
  for(i=0;i<v;i++){
    int f[100010]={b=0};
    for(j=ta[i];j+1;j=nt[j]){
      if(j>=e||f[to[j]=cmp[to[j]]]||i==to[j])continue;
      f[to[j]]=1;
      if(b)nt[b]=j;
      b=j;
    }
    b?(nt[b]=-1):(ta[i]=-1);
  }
}
//最小全域有向木
//ノード数v、辺の数e、kを根としてaからbへコストcの辺がはられている
int mca(int v,int e,int k,int *a,int *b,int *c){
  int i,j,t,r,s,p=0,mi[110],q[10010],bk[110]={0};
  for(i=0;i<v;i++)Ta[i]=mi[i]=-1;//隣接リストを作る
  for(i=0;i<e;i++){
    Nt[i]=Ta[a[i]];
    Co[Ta[a[i]]=i]=c[i];
    bk[a[i]]=bk[To[i]=b[i]]=1;
  }
  for(i=0;i<v;i++)p+=bk[i];
  for(i=0;i<e;i++){//刺さるMIN辺を求める
    if(mi[To[i]]==-1||Co[mi[To[i]]]>Co[i])mi[To[i]]=i;
  }
  mi[q[t=0]=k]=-1;
  for(r=1;r-t;t++){
    for(j=Ta[q[t]];j+1;j=Nt[j])mi[q[r++]=To[j]]==j?s+=Co[j]:r--;
  }
  if(r==p)return s;
  for(i=r=0;i<v;i++){
    bk[i]=0;
    for(j=Ta[i];j+1;j=Nt[j]){
      if(mi[b[r]=To[j]]==j)a[r++]=i;
    }
  }
  scc(v,r,a,b);//強連結成分分解でどれが閉路か調べる
  for(i=0;i<v;i++)bk[cmp[i]]++;
  for(i=r=s=0;i<v;i++){
    for(j=Ta[i];j+1;j=Nt[j]){
      if((a[r]=cmp[i])==(b[r]=cmp[To[j]])){
	if(j==mi[To[j]])s+=Co[j];
      }
      else c[r++]=bk[cmp[To[j]]]-1?Co[j]-Co[mi[To[j]]]:Co[j];
    }
  }
  return mca(v,r,k,a,b,c)+s;
}
//関節点を求める関数たち!
int r,ord[100010],low[100010];
void cdfs(int s,int *ta,int *to,int *nt,int *p){//printf("s%d %d\n",s,r);
  int i;
  ord[s]=low[s]=r++;
  for(i=ta[s];i+1;i=nt[i]){
    if(p[to[i]]==-1){
      p[to[i]]=s;
      cdfs(to[i],ta,to,nt,p);
      low[s]=MIN(low[s],low[to[i]]);
    }
    else if(to[i]-p[s])low[s]=MIN(low[s],ord[to[i]]);
  }
}
void arpo(int v,int e,int *a,int *b){
  int ta[100010],to[100010],nt[100010],p[100010],ans=0,c=0,i,j,f[100010]={0};
  for(i=0;i<v;i++)ta[i]=p[i]=-1;
  for(p[0]=i=0;i<e;i++){
    nt[i  ]=ta[to[i+e]=a[i]];
    nt[i+e]=ta[to[i  ]=b[i]];
    ta[b[ta[a[i]]=i]]=i+e;
  }
  cdfs(0,ta,to,nt,p);
  for(i=1;i<v;i++){
    if(p[i]){
      if(ord[p[i]]<=low[i])f[p[i]]=1;
    }
    else c++;
  }
  if(c>1)f[0]=1;
  for(i=0;i<v;i++){
    if(f[i])printf("%d\n",i);
  }
}

//リストを表示
void prls(int v){
  int i,j;
  for(i=0;i<v;i++){
    printf("%d:",i);
    for(j=ta[i];j+1;j=nt[j])printf("%d ",to[j]);
    printf("\n");
  }
  printf("\n");
}

//k桁の数字を並べ替えてできた数字nはr番めに小さい
int stpint(int *n,int k){
  int i,j,r=0,c,a[10]={1,1,1,1,1,1,1,1,1,1};
  int m=1;
  for(i=0;i<k;i++)m*=i+1;
  for(i=0;i<k;i++){
    m/=k-i;
    for(j=c=0;j<n[i];j++)c+=a[j];
    r+=c*m;
    a[j]=0;
  }
  return r;
}
//文字列を数字にする!
int strint(char* a){
  int n,i;
  for(i=n=0;a[i];i++)n=n*10+a[i]-'0';
  return n;
}
//数字を文字列にし、sに格納!
void intstr(int n,char* s){
  int i,j=0;
  for(i=n;i  ;i/=10)s[++j]=0;
  for(i=n;j--;i/=10)s[j]=i%10+'0';
}
//文字列の数字の大きさを比較　return はstrcmpと同じ!
//#include<string.h>
int strnum(char* a,char* b){
  int la=strlen(a),lb=strlen(b);
  return la-lb?la-lb:strcmp(a,b);
}
//aとbの最長部分文字列の長さを返す!
int lcs(char *a,char *b){
  int i,j,d[1010][1010]={0};
  for(i=0;a[i];i++){
    for(j=0;b[j];j++)d[i+1][j+1]=a[i]-b[j]?MAX(d[i+1][j],d[i][j+1]):d[i][j]+1;
  }
  return d[i][j];
}

//文字列の数値の足し算
void stradd(char *a,char *b,char *d){
  int la=strlen(a),lb=strlen(b),i,na,nb,u=0;
  char c[50000];
  for(i=0;i<MAX(la,lb);i++){
    na=nb=0;
    if(i<la)na=a[la-i-1]-'0';
    if(i<lb)nb=b[lb-i-1]-'0';
    na+=nb+u;
    u=na/10;
    c[i]=na%10+'0';
  }
  if(u)c[i++]='1';
  c[i]=0;//printf("%s\n",c);
  for(i=la=strlen(c);i;i--)d[la-i]=c[i-1];
  d[la]=0;
}
//next permitation
//0なら終了、1ならある
int nxpt(char *s){
  int i,l=strlen(s),max=0,f[260]={0};
  for(l--;l+1&&max<=s[l];l--)f[max=s[l]]++;
  if(l<0)return 0;
  f[s[l]]++;
  for(i=s[l]+1;f[i]==0;i++);
  f[s[l]=i]--;
  for(i=0;s[++l];f[s[l]=i]--){
    while(f[i]==0)i++;
  }
  return 1;
}
//構文解析のための関数たち！
char s[110];
int p=0;
double f(double a,int b,double c){
  if(b==2)return a+c;
  if(b==3)return a-c;
  if(b==4)return a*c;
  return a/c;
}
double kobun(){
  int i,r=0,o[3];
  double n[3],a;
  char c[]={")=+-*/"};
  while(1){
    for(a=0;'0'<=s[p]&&s[p]<='9';p++)a=a*10+s[p]-'0';
    if(s[p]=='('){
      p++;
      a=f();
    }
    for(i=0;s[p]-c[i];i++);
    for(;r&&o[r-1]/2>=i/2;r--)a=f(n[r-1],o[r-1],a);
    n[r]=a;
    o[r++]=i;
    p++;
    if(i/2==0)return n[0];
  }
  return 0;
}

//p0とp1を通る直線と、p2とp3を通る直線の交差判定
int ifcl(int p0[2],int p1[2],int p2[2],int p3[2]){
  int x=p1[0]-p0[0],x0=p2[0]-p0[0],x1=p3[0]-p0[0],x2=p2[0]-p1[0],x3=p3[0]-p1[0];
  int y=p1[1]-p0[1],y0=p2[1]-p0[1],y1=p3[1]-p0[1],y2=p2[1]-p1[1],y3=p3[1]-p1[1];
  return (x*y0-y*x0)*(x*y1-y*x1)<0&&(x*y2-y*x2)*(x*y3-y*x3)<0?1:0;
}
//p0とp1を通る直線のp2に一番近い点をx,yに格納!
void ashi(int p0[2],int p1[2],int p2[2],double *x,double *y){
  int x1=p1[0]-p0[0],x2=p2[0]-p0[0],y1=p1[1]-p0[1],y2=p2[1]-p0[1];
  *x=1.0*(x1*x2+y1*y2)/(x1*x1+y1*y1)*x1+p0[0];
  *y=1.0*(x1*x2+y1*y2)/(x1*x1+y1*y1)*y1+p0[1];
}
//p0とp1を通る直線とp2の距離!
//足が線分の上か判断できる
double drpl(int p0[2],int p1[2],int p2[2]){
  int a=p0[1]-p1[1],b=p0[0]-p1[0],c=p0[0]*p1[1]-p1[0]*p0[1];
  int d=p2[1]-p1[1],e=p2[0]-p1[0];
  int f=p2[1]-p0[1],g=p2[0]-p0[0];
  if(a*d+b*e<0||a*f+b*g>0)return -1;
  return abs(p2[0]*a-p2[1]*b+c)/hypot(a,b);
}
//直線の交点を求める!
//0なら交点なし　1なら交点あり
//p0とp1を通る直線とp2とp3を通る直線の交点をx,yに格納
int cpll(int  p0[2],int p1[2],int p2[2],int p3[2],double *x,double *y){
  int a=p1[0]-p0[0],c=p2[0]-p0[0],e=p3[0]-p2[0];
  int b=p1[1]-p0[1],d=p2[1]-p0[1],f=p3[1]-p2[1];
  if(b*e-a*f==0)return 0;
  *x=p2[0]+1.0*e*(a*d-b*c)/(b*e-a*f);
  *y=p2[1]+1.0*f*(a*d-b*c)/(b*e-a*f);
  return 1;
}
//円と直線の交点!
//0なら交点なし　1なら交点あり
//p0とp1を通る直線と中心p2半径rの円の交点をs,tに格納
int cplc(int p0[2],int p1[2],int p2[2],int r,double s[2],double t[2]){
  int x1=p1[0]-p0[0],y1=p1[1]-p0[1],x2=p2[0]-p0[0],y2=p2[1]-p0[1];
  long long a=x1*x1+y1*y1,b=x1*x2+y1*y2,c=x2*x2+y2*y2-r*r;
  if(b*b<a*c)return 0;
  s[0]=p0[0]+x1*(b+sqrt(b*b-a*c))/a;
  s[1]=p0[1]+y1*(b+sqrt(b*b-a*c))/a;
  t[0]=p0[0]+x1*(b-sqrt(b*b-a*c))/a;
  t[1]=p0[1]+y1*(b-sqrt(b*b-a*c))/a;
  return 1;
}
/*int cplc(int p0[2],int p1[2],int p2[2],int r,double s[2],double t[2]){
  double p3[2],x1=p1[0]-p0[0],y1=p1[1]-p0[1],l;
  ashi(p0,p1,p2,p3);
  l=r*r-(p3[0]-p2[0])*(p3[0]-p2[0])-(p3[1]-p2[1])*(p3[1]-p2[1]);
  if(l<0)return 0;
  s[0]=p3[0]+x1/hypot(x1,y1)*sqrt(l);
  s[1]=p3[1]+y1/hypot(x1,y1)*sqrt(l);
  t[0]=p3[0]-x1/hypot(x1,y1)*sqrt(l);
  t[1]=p3[1]-y1/hypot(x1,y1)*sqrt(l);
  return 1;
  }//*/  
//円と円の交点!
//0なら交点ナシ　1なら交点アリ
//中心p0、半径r0の円と中心p1、半径r0の円の交点をs、tに格納
int cpcc(int p0[2],int r0,int p1[2],int r1,double s[2],double t[2]){
  int x1=p1[0]-p0[0],y1=p1[1]-p0[1],sx=y1,sy=-x1,a=x1*x1+y1*y1,b=r0*r0-r1*r1+a;
  double c=sqrt(a),d=b/(2*c),e=sqrt(r0*r0-(long long)b*b/(4.0*a));  
  if(a>(r0+r1)*(r0+r1))return 0;
  s[0]=p0[0]+(x1*d+sx*e)/c;
  s[1]=p0[1]+(y1*d+sy*e)/c;
  t[0]=p0[0]+(x1*d-sx*e)/c;
  t[1]=p0[1]+(y1*d-sy*e)/c;
  return 1;
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
//Union-Find 0を根として扱う
int main(){
  int q,a,b,r,n,m,p[10010]={0};
  int d[10010]={0};
  scanf("%d %d",&n,&m);
  while(m--){
    scanf("%d %d %d",&q,&a,&b);
    for(r=++a;p[r];r=p[r]);
    for(;n=p[a];a=n)p[a]=r;
    for(r=++b;p[r];r=p[r]);
    for(;n=p[b];b=n)p[b]=r;
    if(q)printf("%d\n",a-b?0:1); 
    else if(a-b){
      d[a]<d[b]?(p[a]=b):(p[b]=a);
      if(d[a]==d[b])d[a]++;
    }
  }
  return 0;
}
