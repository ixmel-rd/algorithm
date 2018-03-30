#include<stdio.h>
#include<string.h>
//文字列を数字にする!
int strint(char* a){
  int n,i;
  for(i=n=0;a[i];i++)n=n*10+a[i]-'0';
  return n;
}
//------------------------------------------------------------------
//数字を文字列にし、sに格納!
void intstr(int n,char* s){
  int i,j=0;
  for(i=n;i  ;i/=10)s[++j]=0;
  for(i=n;j--;i/=10)s[j]=i%10+'0';
}
//-------------------------------------------------------------------
//文字列の数字の大きさを比較　return はstrcmpと同じ!
//#include<string.h>
int strnum(char* a,char* b){
  int la=strlen(a),lb=strlen(b);
  return la-lb?la-lb:strcmp(a,b);
}
//---------------------------------------------------------------------
//aとbの最長部分文字列の長さを返す!
int lcs(char *a,char *b){
  int i,j,d[1010][1010]={0};
  for(i=0;a[i];i++){
    for(j=0;b[j];j++)d[i+1][j+1]=a[i]-b[j]?MAX(d[i+1][j],d[i][j+1]):d[i][j]+1;
  }
  return d[i][j];
}
//-------------------------------------------------------------------
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
//-------------------------------------------------------------------
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
//------------------------------------------------------------------------
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
//------------------------------------------------------------------------
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
//--------------------------------------------------------------------
//ローリングハッシュ
long long a[2]={101,103};
long long M[2]={1e9+7,1e9+9};
long long d[2][300010],k[2][300010];
void init(char *s){//!
  int i,j;
  for(i=0;i<2;i++){
    k[i][0]=1;
    for(j=d[i][0]=0;s[j];j++){
      d[i][j+1]=(d[i][j]*a[i]+(s[j]-'a'+1))%M[i];
      k[i][j+1]=(k[i][j]*a[i])%M[i];
    }
  }
}
int getlr(int l,int r,int i){return (M[i]*M[i]+d[i][r]-d[i][l]*k[i][r-l])%M[i];}
void gets(char *s,int *h){
  int i,j;
  for(i=0;i<2;i++){
    for(j=h[i]=0;s[j];j++)h[i]+=k[i][j]*(s[j]-'0');
  }
}
int match(int l,int r,int *h){
  int i,j=1;
  for(i=0;i<2;i++)j*=getlr(l,r,i)-h[i]?1:0;
  return j;
}
