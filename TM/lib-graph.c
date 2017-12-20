#include<stdio.h>
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
//逆辺付き無向ブラフ
void mklsb(int v,int e,int *a,int *b,int *c){
  int i;
  for(i=0;i<v;i++)ta[i]=-1;
  for(i=0;i<e;i++){
    nt[i  ]=ta[to[i+e]=a[i]];
    nt[i+e]~ta[to[i  ]=b[i]];
    co[ta[a[i]]=i  ]=c[i];      
    co[ta[b[i]]=i+e]=0;
  }
}
//-----------------------------------------------------------
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
  for(t=0;t<r;t++){
    for(i=ta[q[t]];i+1;i=nt[i]){
      if(--c[b[i]]==0)q[r++]=b[i];
    }
  }
  return r;
}
//トポロジカルソート
//外でグラフを作る
int topo(int v,int e,int *ta,int *to,int *nt){
  int i,t,r,c[10010]={0};
  for(i=0;i<e;i++)c[to[i]]++;
  for(i=r=0;i<v;i++){
    if(c[i]==0)q[r++]=i;
  }
  for(t=0;t<r;t++){
    for(i=ta[q[t]];i+1;i=nt[i]){
      if(--c[b[i]]==0)q[r++]=b[i];
    }
  }
  return r;
}
//------------------------------------------------------
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
//ダイクストラ
//外でクラフを作る
void dijk(int v,int mi){
  int i,id[100010],f[100010]={0};
  H=C=1;
  while(f[mi]-1){
    f[mi]=1;
    for(i=ta[i];i+1;i=nt[i]){
      if(CO[to[i]]>CO[mi]+co[i])hin(CO[id[R]=to[i]]=CO[mi]+co[i]);
    }
    while(f[mi]&&C-1)mi=id[hout()];
  }
}
//--------------------------------------------------------------------
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
//-------------------------------------------------------------
//ベルマンフォード
//頂点数v、辺の数eのグラフでfr[i]からto[i]にco[i]の辺がはられている
//Cにsからの最小コストが入る
int C[100010]={0};
int blmn(int v,int e,int s,int *fr,int *to,int *co){
  int i,j,f;
  for(i=0;i<v;i++)C[i]=1e9;
  for(i=C[s]=0;i<v;i++){
    for(j=0;j<e;j++){
      if(C[fr[j]]-1e9&&C[to[j]]>C[fr[j]]+co[j]){
	C[to[j]]=C[fr[j]]+co[j];
	if(i==v-1)return 1;
      }
    }
  }
  return 0;
}
//-----------------------------------------------------------------
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
//呼び出す方
//外でクラフを作る
int maxf(int v,int e,int s,int t){
  int i,f,r;
  for(i=0;i<v;i++)F[i]=0;
  for(f=0;r=MF(s,t,e,1e9);f+=r){
    for(i=0;i<v;i++)F[i]=0;
  }
  return f;
}
//--------------------------------------------------------------------
//Dinicの関数たち
//グラフは外で作る
int ta[100010],to[100010],co[100010],nt[100010],it[100010],l[100010];
int MF(int e,int s,int t,int min){
  if(s==t)return min;
  int i,r;
  for(;it[s]+1;it[s]=nt[it[s]]){
    if(co[it[s]]==0||l[s]>=l[to[it[s]]])continue;
    r=MF(e,to[it[s]],t,MIN(min,co[it[s]]));
    co[it[s]]-=r;
    co[(it[s]+e)%(2*e)]+=r;
    if(r)return r;
  }
  return 0;
}
//呼び出す方
//頂点v、辺eのグラフでsからgに流す
int maxf(int v,int e,int s,int g){
  int i,a=0,q[100010],t,r,c=3;
  while(1){
    for(i=t=0;i<v;i++)l[i]=0;
    for(r=l[q[0]=s]=1;r-t;t++){
      for(i=ta[q[t]];i+1;i=nt[i]){
	if(co[i]&&l[to[i]]==0)l[q[r++]=to[i]]=l[q[t]]+1;
      }
    }
    if(l[g]==0)return a;
    for(i=0;i<v;i++)it[i]=ta[i];
    while(r=MF(e,s,g,1e9))a+=r;
  }
}
//---------------------------------------------------------------------
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
  int i;
  for(i=0;i<v;i++)ta[i]=-1;
  for(i=0;i<e;i++){
    nt[i  ]=ta[to[i+e]=a[i]];
    nt[i+e]=ta[to[i  ]=b[i]];
    co[ta[b[i]]=i+e]=co[ta[a[i]]=i]=c[i];
  }
  bfs(v,0);
  return bfs(v,g);
}
//呼び出す方
//グラフは外で作る
int tyokkei(int v){
  bfs(v,0);
  return bfs(v,g);
}
//---------------------------------------------------------------
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
//-------------------------------------------------------------------
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
//強連結成分分解
//外でグラフを作る
void scc(int v,int e){
  int id[10010],i,k;
  for(i=0;i<v;i++)f[i]=-1;
  for(i=k=0;i<v;i++){
    if(f[i]==-1)sdfs(e,i,-1,ta,to,nt,id);
  }
  for(i=r;i;i--){
    if(f[id[i-1]]==0)sdfs(e,id[i-1],id[i-1],ta,to,nt,id);
  }
}
//------------------------------------------------------------------
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
//---------------------------------------------------------------------
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
//----------------------------------------------------------------------
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
//橋を列挙する!
//非連結でも対応
int brig(int v,int e,int *a,int *b,int *c,int *d){
  int ta[100010],to[100010],nt[100010],p[100010],ans=0,co=0,i,j,f[100010]={0};
  for(i=0;i<v;i++)ta[i]=p[i]=-1;
  for(p[0]=i=0;i<e;i++){
    nt[i  ]=ta[to[i+e]=a[i]];
    nt[i+e]=ta[to[i  ]=b[i]];
    ta[b[ta[a[i]]=i]]=i+e;
  }
  for(i=r=0;i<v;i++){
    if(r<v)cdfs(i,ta,to,nt,p);
  }
  for(i=1;i<v;i++){//橋を配列に格納していく
    if(ord[p[i]]<low[i]){
      c[co  ]=p[i];
      d[co++]=  i ;
    }
  }
  return co;
}
//関節点や橋を求める
//グラフを外で作る
int r,ord[100010],low[100010];
void cdfs(int s,int *p){//printf("s%d %d\n",s,r);
  int i;
  ord[s]=low[s]=r++;
  for(i=ta[s];i+1;i=nt[i]){
    if(p[to[i]]==-1){
      p[to[i]]=s;
      cdfs(to[i],p);
      low[s]=MIN(low[s],low[to[i]]);
    }
    else if(to[i]-p[s])low[s]=MIN(low[s],ord[to[i]]);
  }
}
void arpo(int v,int e,int *a,int *b){
  int p[100010],ans=0,c=0,i,j,f[100010]={0};
  for(i=0;i<v;i++)p[i]=-1;
  cdfs(p[0]=0,p);
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
//非連結でも対応
int brig(int v,int e,int *a,int *b,int *c,int *d){
  int p[100010],ans=0,co=0,i,j;
  for(i=0;i<v;i++)p[i]=-1;
  for(i=r=p[0]=0;i<v;i++){
    if(r<v)cdfs(i,p);
  }
  for(i=1;i<v;i++){//橋を配列に格納していく
    if(ord[p[i]]<low[i]){
      c[co  ]=p[i];
      d[co++]=  i ;
    }
  }
  return co;
}
//------------------------------------------------------------------
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
//リストを表示
void prls(int v,int *ta,int *to,int *nt){
  int i,j;
  for(i=0;i<v;i++){
    printf("%d:",i+1);
    for(j=ta[i];j+1;j=nt[j])printf("%d ",to[j]+1);
    printf("\n");
  }
  printf("\n");
}
//---------------------------------------------------------------
//最小費用流!
int mifl(int v,int e,int f,int s,int t,int *a,int *b,int *c,int *d){
  int ta[110],to[2010],co[2010],nt[2010],ca[2010],u[110];
  int i,j,k,min,mi,ans=0,id[100010],fe[110],fv[110];
  int h[110]={0};
  for(i=0;i<v;i++)ta[i]=-1;
  for(i=0;i<e;i++){
    nt[i  ]=ta[to[i+e]=a[i]];
    nt[i+e]=ta[to[i  ]=b[i]];
    ca[i  ]=c[i];
    ca[i+e]=0;
    co[ta[a[i]]=i  ]= d[i];
    co[ta[b[i]]=i+e]=-d[i];
  }
  while(f>0){
    for(i=0;i<v;i++)CO[i]=M;
    for(i=0;i<v;i++)u[i]=0;
    R=C=1;
    fv[s]=fe[s]=-1;
    CO[mi=s]=0;
    while(u[mi]-1){
      u[mi]=1;
      for(i=ta[mi];i+1;i=nt[i]){
	if(ca[i]&&  CO[to[i]]>CO[mi]+co[          i]+h[          mi]-h[to[i]]){
	  hin(CO[id[R]=to[i]]=CO[mi]+co[fe[to[i]]=i]+h[fv[to[i]]=mi]-h[to[i]]);
	}
      }
      while(u[mi]&&C-1)mi=id[hout()];
    }
    if(CO[t]==M)return -1;
    for(i=0;i<v;i++)h[i]+=CO[i];
    min=f;
    for(i=t;i-s;i=fv[i])min=MIN(min,ca[fe[i]]);
    f-=min;
    ans+=h[t]*min;
    for(i=t;i-s;i=fv[i]){
      ca[fe[i]]-=min;
      ca[(fe[i]+e)%(2*e)]+=min;
    }
  }
  return ans;
}
//----------------------------------------------------------------
//LCAを求める関数たち!
//添字セグメントツリーを使う
//LCAの番号ならID[alac(a,b)]、LCAの高さならN[alca(a,b)]
int ta[100010],to[100010],nt[100010],r=0,fi[100010],ID[200010];
void ldfs(int s,int d){
  int i;
  N[fi[s]=r]=d;
  ID[r++]=s;
  for(i=ta[s];i+1;i=nt[i]){
    if(fi[to[i]]+1)continue;
    ldfs(to[i],d+1);
    N[r]=d;
    ID[r++]=s;
  }
}
//lcaのための準備　mainに直接書いてもいい
//pを親とする根付き木を作りオイラーツアー
void slca(int p){
  ldfs(p,r=0);
  sset(r);
}
//aとbのlcaを求める　添字が帰ってくる
int alca(int a,int b){return sout(MIN(fi[a],fi[b]),MAX(fi[a],fi[b])+1,1,0,T);}
//---------------------------------------------------------------------------
