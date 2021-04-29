#include<iostream>
#include<cstring>
#define maxn 200

using namespace std;

bool gr[maxn][maxn];
  
bool isCover(int V, int k, int E)
{
    int set = (1 << k) - 1;
  
    int limit = (1 << V);
  
    bool vis[maxn][maxn];
  
    while (set < limit)
    {
        memset(vis, 0, sizeof vis);
  
        int cnt = 0;
  
        for (int j = 1, v = 1 ; j < limit ; j = j << 1, v++)
        {
            if (set & j)
            {
                for (int k = 1 ; k <= V ; k++)
                {
                    if (gr[v][k] && !vis[v][k])
                    {
                        vis[v][k] = 1;
                        vis[k][v] = 1;
                        cnt++;
                    }
                }
            }
        }
  
        if (cnt == E)
            return true;
  
        int c = set & -set;
        int r = set + c;
        set = (((r^set) >> 2) / c) | r;
    }
    return false;
}
  
int findMinCover(int n, int m)
{
    // Binary search the answer
    int left = 1, right = n;
    while (right > left)
    {
        int mid = (left + right) >> 1;
        cout << "New sol is " << left << endl;
        if (isCover(n, mid, m) == false)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}
  
void insertEdge(int u, int v)
{
    gr[u][v] = 1;
    gr[v][u] = 1;  // Undirected graph
}

int main()
{
    int V, E;
    cin >> V >> E;
    for (int i=0; i<E; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        insertEdge(v1, v2);
    }
    int min = findMinCover(V, E);
    cout << "New sol is " << min << endl;
    return 0;
}
