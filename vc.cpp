#include<bits/stdc++.h>
 
using namespace std;
 
bool graph[1001][1001];
bool vis[1001][1001];
 
int i,j,k,v;
int n,e,x,y;
 
bool isVertexCover(int sz)
{
    int c,r,cnt=0;
    int set = (1 << sz) - 1;
    int limit = (1 << n);
    while (set < limit)
    {
        memset(vis,0,sizeof(vis));
        cnt = 0;
        for (j = 1, v = 0 ; j < limit ; j = j << 1, v++)
        {
            if (set & j)
            {
                for (k = 1 ; k <= n-1 ; k++)
                {
                    if (graph[v][k] && !vis[v][k])
                    {
                        vis[v][k] = 1;
                        vis[k][v] = 1;
                        cnt++;
                    }
                }
            }
        }
        if (cnt == e)
            return true;
        c = set & -set;
        r = set + c;
        set = (((r^set) >> 2) / c) | r;
    }
    return false;
}
 
int main()
{
	// cout<<"Enter number of vertices:";
	cin>>n;
	// cout<<"\nEnter number of Edges:";
	cin>>e;
	for(i=0;i<e;i++)
	{
		// cout<<"Enter the end-points of edge "<<i+1<<":";
		cin>>x>>y;
		// x--; y--;
		graph[x][y]=1;
		graph[y][x]=1;
	}
	cout<<"Enter the size of Vertex Cover to check for (should be less than number of vertices) :";
	cin>>k;
	if(isVertexCover(k))
	cout<<"Vertex Cover of size"<<" "<<k<<" exist.\n";
	else
	cout<<"Vertex Cover of size"<<" "<<k<<" does not exist.\n";
	return 0;
}