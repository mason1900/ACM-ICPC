/*
Exclusive-OR
Time Limit: 3000MS		Memory Limit: Unknown

Description

You are not given n non-negative integers X0, X1,..., Xn-1 less than 220, but they do exist, and their values never change.
I'll gradually provide you some facts about them, and ask you some questions.
There are two kinds of facts, plus one kind of question:

Format	 Meaning
I p v	 I tell you Xp = v
I p q v	 I tell you Xp XOR Xq = v
Q k p1 p2...pk	 Please tell me the value of Xp1 XOR Xp2 XOR...XOR Xpk


Input
There will be at most 10 test cases. Each case begins with two integers n and Q (1n20, 000, 2Q40, 000). Each of the following lines contains either a fact or a question, formatted as stated above. The k parameter in the questions will be a positive integer not greater than 15, and the v parameter in the facts will be a non-negative integer less than 220. The last case is followed by n = Q = 0, which should not be processed.
Output
For each test case, print the case number on its own line, then the answers, one on each one. If you can't deduce the answer for a particular question, from the facts I provide you before that question, print ``I don't know.", without quotes. If the i-th fact (don't count questions) cannot be consistent with all the facts before that, print ``The first i facts are conflicting.", then keep silence for everything after that (including facts and questions). Print a blank line after the output of each test case.
Sample Input
2 6 
I 0 1 3
Q 1 0 
Q 2 1 0
I 0 2 
Q 1 1 
Q 1 0 
3 3 
I 0 1 6
I 0 2 2
Q 2 1 2
2 4 
I 0 1 7
Q 2 0 1
I 0 1 8
Q 2 0 1
0 0
Sample Output
Case 1: 
I don't know. 
3 
1 
2 

Case 2: 
4 

Case 3: 
7 
The first 2 facts are conflicting.

*/


//Result:2011-10-10 16:08:51	Accepted	3234	234MS	524K	2241 B	G++	Foc_Kuuy
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x
#define SIZE 20010
#define GOD n
#define pb push_back
#define mp make_pair

typedef struct node
{
	int father;
	int val;
}node;

node array[SIZE];
int n,q;

inline void init(int n)
{
	//初始化
	memset(array,0,sizeof(array));
	for(int i=0;i<=n;i++) array[i].father=i;
}

int find(int a)
{
	if(a==array[a].father) return a;
	else
	{
		int t=array[a].father;
		array[a].father=find(t);
		array[a].val^=array[t].val;
		//带权值的并查集，更新权值
	}
	return array[a].father;
}

bool Lunion(int a,int b,int v)
{
	int fa=find(a);
	int fb=find(b);
	if(fa==fb) return v==(array[a].val^array[b].val);
	//如果a<->b的边存在，则v==(a.val^FATHER ^ FATHER^b.val)==a.val^b.val
	if(fa==GOD) swap(fa,fb);
	//如果fa是上帝节点，则a是有确定值的，变换fa,fb是为了下面操作的统一
	array[fa].father=fb;//上帝节点是不能有父节点的 ;-)
	array[fa].val=(array[a].val^array[b].val^v);
	//fa->fb的权值就为a.val^b.val^v
	return true;
}


int main()
{
	freopen("input.txt","r",stdin);
	char cmd[1024];
	int cas=1;
	while(scanf("%d%d",&n,&q)!=EOF&&n&&q)
	{
		print("Case "<<cas<<":");
		cas++;
		int nr=0;
		bool err=false;
		init(n);
		for(int i=0;i<q;i++)
		{
			scanf("%s",cmd);
			if(err)
			{
				gets(cmd);
				continue;
			}
			if(*cmd=='I')
			{
				nr++;
				int x,y,v;
				gets(cmd);

				if(sscanf(cmd,"%d%d%d",&x,&y,&v)==2)
				{
					swap(y,v);
					y=GOD;
					//如果是赋值操作，就转化为a->GOD=v
				}
				
				if(!Lunion(x,y,v))
				{
					err=true;
					print("The first "<<nr<<" facts are conflicting.");
				}
			}
			else
			{
				int k;
				scanf("%d",&k);
				int ans=0;
				vector< pair<int,int> > vec;
				for(int j=0;j<k;j++)
				{
					int x;
					scanf("%d",&x);
					int rx=find(x);
					ans^=array[x].val;
					int l;
					for(l=0;l<(int)vec.size();l++)
					{
						if(vec[l].first==rx) break;
					}
					if(l==(int)vec.size()) vec.pb(mp(rx,1));
					else vec[l].second^=1;
				}
				//求一个集合的XOR值的要求是所有的节点都在一棵树上
				//所以求的值会是和Father进行XOR运算的值，如果Father节点出现两次，就XOR没了
				//余下的Father节点只会是GOD节点，因为GOD节点没有Father
				bool flag=true;
				int sz=vec.size();
				for(int j=0;j<sz;j++)
				{
					if(vec[j].second)
					{
						int rx=find(vec[j].first);
						if(rx!=GOD)
						{
							flag=false;
							break;
						}
					}
				}
				//如果找到的Father节点不是GOD，就BREAK，回报I don't know.
				if(flag) print(ans);
				else print("I don't know.");
			}
		}
		print("");
	}
	return 0;
}
