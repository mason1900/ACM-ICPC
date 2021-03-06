//Result:2012-09-14 13:53:24	Accepted	1007	906MS	3436K	1854 B	C++	Wizmann
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x
#define SIZE 100010

const double eps=1e-8;
const double inf=1e100;

inline int zero(double x)
{
	if(x>eps) return 1;
	else if(x<-eps) return -1;
	else return 0;
}

struct point
{
	double x,y;
	point(){}
	point(double ix,double iy)
	{
		x=ix;y=iy;
	}
};

inline double mul(double x)
{
	return x*x;
}

inline double xmult(const point &sp,const point &ep,const point &op)
{
	return ((sp.x-op.x)*(ep.y-op.y)-(sp.y-op.y)*(ep.x-op.x));
}

inline double pntDis(const point &a,const point &b)
{
	return sqrt(mul(a.x-b.x)+mul(a.y-b.y));
}

bool cmpX(const point &a,const point &b)
{
	return a.x>b.x;
}

bool cmpY(const point &a,const point &b)
{
	return a.y<b.y;
}

point array[SIZE];
point ym[SIZE];

double minDisPointPair(int st,int end,point *ip)
{
	double res=inf;
	if(end-st<19)
	{
		for(int i=st;i<=end;i++)
		{
			for(int j=i+1;j<=end;j++)
			{
				res=min(res,pntDis(ip[i],ip[j]));
			}
		}
		return res;
	}
	else
	{
		int mid=(st+end)>>1;
		res=min(minDisPointPair(st,mid,ip),minDisPointPair(mid+1,end,ip));
		int yn=0;
		
		for(int i=st;i<=end;i++)
		{
			if(ip[i].x>=ip[mid].x-res && ip[i].x<=ip[mid].x+res) ym[yn++]=ip[i];
		}
		sort(ym,ym+yn,cmpY);
		for(int i=0;i<yn;i++)
		{
			for(int j=i+1;j<yn;j++)
			{
				if(ym[j].y-ym[i].y>=res) break;
				res=min(res,pntDis(ym[i],ym[j]));
			}
		}
		return res;
	}
}

int n;

int main()
{
	freopen("input.txt","r",stdin);
	double a,b;
	while(input(n) && n)
	{
		for(int i=0;i<n;i++)
		{
			scanf("%lf%lf",&a,&b);
			array[i]=point(a,b);
		}
		sort(array,array+n,cmpX);
		printf("%.2lf\n",minDisPointPair(0,n-1,array)/2.0);
	}
}
	
