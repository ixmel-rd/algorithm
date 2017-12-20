#include<stdio.h>
#include<math.h>
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
