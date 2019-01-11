#include<iostream>
#include<complex>
#include<vector>
#include<string>
#include<algorithm>	
#include<map>
#include<set>
#include<utility>
#include<cmath>
#include<cstring>
#include<queue>
#include<stack>
#include<cstdio>
#include<sstream>
#include<iomanip>
#include<assert.h>
#define loop(i,a,b) for(int i=a;i<b;i++) 
#define rep(i,a) loop(i,0,a)
#define pb push_back
#define all(in) in.begin(),in.end()
#define shosu(x) fixed<<setprecision(x)
using namespace std;
//kaewasuretyuui
typedef long long ll;
typedef int Def;
typedef pair<Def,Def> pii;
typedef vector<Def> vi;
typedef vector<vi> vvi;
typedef vector<pii> vp;
typedef vector<vp> vvp;
typedef vector<string> vs;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef pair<Def,pii> pip;
typedef vector<pip>vip;
//#define mt make_tuple
//typedef tuple<double,int,double> tp;
//typedef vector<tp> vt;
template<typename A,typename B>bool cmin(A &a,const B &b){return a>b?(a=b,true):false;}
template<typename A,typename B>bool cmax(A &a,const B &b){return a<b?(a=b,true):false;}
const double PI=acos(-1);
const double EPS=1e-7;
Def inf = sizeof(Def) == sizeof(long long) ? 2e18 : 1e9;
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
typedef complex<double> P;
typedef vector<P> G;
typedef vector<double> vd;
typedef vector<vd> vvd;

struct L : public vector<P> {
  L(const P &a, const P &b) {
    push_back(a); push_back(b);
  }
};
struct C{
	P c;double r;
	C(const P &c,double r):c(c),r(r){}
};
#define curr(P, i) P[i]
#define next(P, i) P[(i+1)%P.size()]
#define diff(P, i) (next(P, i) - curr(P, i))
namespace std {
	bool operator < (const P& a, const P& b) {
		return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
		//return imag(a) != imag(b) ? imag(a) < imag(b) : real(a) < real(b);  
	}
	bool operator == (const P& a, const P& b) {
		return a.real()==b.real()&&a.imag()==b.imag();
	}
}
P pin(){
	double x,y;
	char d;
	cin>>x>>y;
	P p(x,y);
	return p;
}
void PIN(P* a,int n){
	rep(i,n)a[i]=pin();
}
double dot(P a,P b){
	return real(conj(a)*b);
}
double cross(P a,P b){
	return imag(conj(a)*b);
}
int ccw(P a, P b, P c) {
  b -= a; c -= a;
  if (cross(b, c) > 0)   return +1;       // counter clockwise
  if (cross(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;                               // a--c--b on line
}
P projection(L a,P p){
	double t=dot(p-a[0],a[0]-a[1])/norm(a[0]-a[1]);
	return a[0]+t*(a[0]-a[1]);
}
P reflection(L a,P p){
	return p+2.0*(projection(a,p)-p);
}
bool intersectLL(const L &l, const L &m) {
  return abs(cross(l[1]-l[0], m[1]-m[0])) > EPS || // non-parallel
         abs(cross(l[1]-l[0], m[0]-l[0])) < EPS;   // same line
}
bool intersectLS(const L &l, const L &s) {
  return cross(l[1]-l[0], s[0]-l[0])*       // s[0] is left of l
         cross(l[1]-l[0], s[1]-l[0]) < EPS; // s[1] is right of l
}
bool intersectLP(const L &l, const P &p) {
  return abs(cross(l[1]-p, l[0]-p)) < EPS;
}
bool intersectSS(const L &s, const L &t) {
  return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
         ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}
bool intersectSP(const L &s, const P &p) {
  return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0]) < EPS; // triangle inequality
}
double distanceLP(const L &l, const P &p) {
	return abs(p - projection(l, p));
}
double distanceLL(const L &l, const L &m) {
  return intersectLL(l, m) ? 0 : distanceLP(l, m[0]);
}
double distanceLS(const L &l, const L &s) {
  if (intersectLS(l, s)) return 0;
  return min(distanceLP(l, s[0]), distanceLP(l, s[1]));
}
double distanceSP(const L &s, const P &p) {
  const P r = projection(s, p);
  if (intersectSP(s, r)) return abs(r - p);
  return min(abs(s[0] - p), abs(s[1] - p));
}
double distanceSS(const L &s, const L &t) {
  if (intersectSS(s, t)) return 0;
  return min(min(distanceSP(s, t[0]), distanceSP(s, t[1])),
             min(distanceSP(t, s[0]), distanceSP(t, s[1])));
}
/*bool intersectCS(C c,const L &l){
    return (distanceLP(l,c.c) < c.r+EPS &&
            (c.r < abs(c.c-l[0]) + EPS || c.r < abs(c.c-l[1]) + EPS));
}*/
int intersectCS(C c,L l){
	if(norm(projection(l,c.c)-c.c)-c.r*c.r>EPS)return 0;
	const double d1=abs(c.c-l[0]),d2=abs(c.c-l[1]);
	if(d1<c.r+EPS&&d2<c.r+EPS)return 0;
	if(d1<c.r-EPS&&d2>c.r+EPS||d1>c.r+EPS&&d2<c.r-EPS)return 1;
	const P h=projection(l,c.c);
	if(dot(l[0]-h,l[1]-h)<0)return 2;
	return 0;
}
P crosspointSS(L a,L b){
	double t1=abs(cross(a[1]-a[0],b[0]-a[0]));
	double t2=abs(cross(a[1]-a[0],b[1]-a[0]));
	return b[0]+(b[1]-b[0])*t1/(t1+t2);
}
L crosspointCL(C c,L l){
	P pr=projection(l,c.c);
	P e=(l[1]-l[0])/abs(l[1]-l[0]);
	double tmp=c.r*c.r-norm(pr-c.c);
	if(abs(tmp)<EPS)tmp=0;
	double t=sqrt(tmp);
	P a=pr+t*e;
	P b=pr-t*e;
	if(b<a)swap(a,b);
	return L(a,b);
}
L crosspointCS(C c,L l){
	if(intersectCS(c,l)==2)return crosspointCL(c,l);
	L ret=crosspointCL(c,l);
	if(dot(l[0]-ret[0],l[1]-ret[0])<0)ret[1]=ret[0];
	else ret[0]=ret[1];
	return ret;
}
L crosspointCC(C a,C b){
	P tmp=b.c-a.c;
	double d=abs(tmp);
	double q=acos((a.r*a.r+d*d-b.r*b.r)/(2*a.r*d));
	double t=arg(tmp);//atan(tmp.imag()/tmp.real());
	P p1=a.c+polar(a.r,t+q);
	P p2=a.c+polar(a.r,t-q);
	if(p2<p1)swap(p1,p2);
	return L(p1,p2);
}
P crosspointLL(const L &l, const L &m) {
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
  return m[0] + B / A * (m[1] - m[0]);
}
double area(const G &g){
    double S =0;
    for(int i =0;i <g.size();i++){
        S +=(cross(g[i],g[(i+1)%g.size()]));
    }
    return abs(S/2.0);
}
bool isconvex(const G &g){
	int n=g.size();
	rep(i,n)if(ccw(g[(i+n-1)%n],g[i%n],g[(i+1)%n])==-1)return false;
	return true;
}
int inconvex(const G& g, const P& p) {
	bool in = false;
	int n=g.size();
	rep(i,n){
		P a=g[i%n]-p;
		P b=g[(i+1)%n]-p;
		if(imag(a)>imag(b))swap(a, b);
		if(imag(a)<EPS&&0<imag(b))if(cross(a,b)<0)in=!in;
		if(abs(cross(a,b))<EPS&&dot(a,b)<EPS)return 1;//ON
	}
	return in?2:0;//IN : OUT;
}
G convex_hull(G &ps) {
    int n=ps.size(),k=0;
	sort(ps.begin(), ps.end());
	G ch(2*n);
	for(int i=0;i<n;ch[k++]=ps[i++])//lower-hull
		while(k>=2&&ccw(ch[k-2],ch[k-1],ps[i])==-1)--k;//<=0  ->  ==-1
	for(int i=n-2,t=k+1;i>=0;ch[k++]=ps[i--])//upper-hull
		while(k>=t&&ccw(ch[k-2],ch[k-1],ps[i])==-1)--k;//
	ch.resize(k-1);
	return ch;
}
double convex_diameter(const G &pt) {
  const int n = pt.size();
  int is = 0, js = 0;
  for (int i = 1; i < n; ++i) {
    if (imag(pt[i]) > imag(pt[is])) is = i;
    if (imag(pt[i]) < imag(pt[js])) js = i;
  }
  double maxd = norm(pt[is]-pt[js]);

  int i, maxi, j, maxj;
  i = maxi = is;
  j = maxj = js;
  do {
    if (cross(diff(pt,i), diff(pt,j)) >= 0) j = (j+1) % n;
    else i = (i+1) % n;
    if (norm(pt[i]-pt[j]) > maxd) {
      maxd = norm(pt[i]-pt[j]);
      maxi = i; maxj = j;
    }
  } while (i != is || j != js);
  return sqrt(maxd); /* farthest pair is (maxi, maxj). */
}//convex_diameter(g)
G convex_cut(const G& g, const L& l) {
  G Q;
  for (int i = 0; i < g.size(); ++i) {
    P a= curr(g, i), b= next(g, i);
    if (ccw(l[0], l[1], a) != -1) Q.push_back(a);
    if (ccw(l[0], l[1], a)*ccw(l[0], l[1], b) < 0)
      Q.push_back(crosspointLL(L(a,b), l));
  }
  return Q;
}
P turn(P p,double t){
	return p*exp(P(.0,t*PI/180.0));
}
P turn2(P p,double t){
	return p*exp(P(.0,t));
}
vector<L> tangentCC(C a,C b){
	if(a.r<b.r)swap(a,b);
	double d=abs(a.c-b.c);
	vector<L>l;
	if(d<EPS)return l;
	if(a.r+b.r<d-EPS){//hanareteiru
		double t=acos((a.r+b.r)/d);
		t=t*180/PI;
		l.pb(L(a.c+turn(a.r/d*(b.c-a.c),t),b.c+turn(b.r/d*(a.c-b.c),t)));
		l.pb(L(a.c+turn(a.r/d*(b.c-a.c),-t),b.c+turn(b.r/d*(a.c-b.c),-t)));
	}else if(a.r+b.r<d+EPS){//kuttuiteiru soto
		P p=a.c+a.r/d*(b.c-a.c);
		l.pb(L(p,p+turn(b.c-a.c,90)));
	}
	if(abs(a.r-b.r)<d-EPS){//majiwatteiru
		double t1=acos((a.r-b.r)/d);
		t1=t1*180/PI;
		double t2=180-t1;
		l.pb(L(a.c+turn(a.r/d*(b.c-a.c),t1),b.c+turn(b.r/d*(a.c-b.c),-t2)));
		l.pb(L(a.c+turn(a.r/d*(b.c-a.c),-t1),b.c+turn(b.r/d*(a.c-b.c),t2)));
	}else if(abs(a.r-b.r)<d+EPS){//kuttuiteiru uti
		P p=a.c+a.r/d*(b.c-a.c);
		l.pb(L(p,p+turn(b.c-a.c,90)));
	}
	return l;
}
void printL(const L &out){
	printf("%0.9f %0.9f %0.9f %0.9f\n",out[0].real(),out[0].imag(),out[1].real(),out[1].imag());
}
C CIN(){
	P p=pin();
	double r;
	cin>>r;
	return C(p,r);
}
bool para(L a,L b){
	return (abs(cross(a[1]-a[0],b[1]-b[0]))<EPS);
}
//余弦定理
double LawOfCosines(double a,double b,double c){
	return acos((b*b+c*c-a*a)/(2.*b*c));
}
//外接円
pair<P,double> circumccircle(P a,P b,P c){
	double dA=abs(b-c),dB=abs(a-c),dC=abs(a-b);
	double angA=LawOfCosines(dA,dB,dC);
	double angB=LawOfCosines(dB,dC,dA);
	double angC=LawOfCosines(dC,dA,dB);
	double A=sin(2.*angA),B=sin(2.*angB),C=sin(2.*angC);
	double x=(a.real()*A+b.real()*B+c.real()*C)/(A+B+C);
	double y=(a.imag()*A+b.imag()*B+c.imag()*C)/(A+B+C);
	P p(x,y);
	double r=dA/sin(angA)/2.;
	return {p,r};
}
//内接円
pair<P,double> incircle(P a,P b,P c){
	double dA=abs(b-c),dB=abs(a-c),dC=abs(a-b);
	L l1(a,b+dC/(dB+dC)*(c-b));
	L l2(b,a+dC/(dA+dC)*(c-a));
	P p=crosspointLL(l1,l2);
	double r=abs(p-projection(L(a,b),p));
	return {p,r};
}
int main(){
}
