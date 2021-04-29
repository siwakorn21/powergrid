#include<iostream>
#include<vector>
#include<cstring>
#include<omp.h>

using namespace std;

// void printAdj(vector<vector<int>> &G)
// {
//     for (int i=0; i<G.size(); i++)
//     {
//         for (int j=0; j<G.size() ; j++)
//         {
//             cout << G[i][j] << " ";
//         }
//         cout << endl;
//     }
// }

void insertEdge(vector<vector<int>> &G, int u, int v)
{
    G[u][v] = 1;
    G[v][u] = 1;  // Undirected graph
}

void removeEdge(vector<vector<int>> &G, int u, int v)
{
    G[u][v] = 0;
    G[v][u] = 0;
}

bool hasVertexCover(vector<vector<int>> &G, int k, vector<int> vc)
{
    if (vc.size() > k) return false;
    int V = G.size();
    vector<bool> cover(V, false);
    for (auto it : vc) 
    {
        cover[it] = true;
    }
    for (int i=0; i<vc.size(); i++)
    {
        for (int j=0; j<G.size(); j++)
        {
            cover[j] = G[vc[i]][j] == 1 ? true : cover[j];
        }
    }
    for (auto x : cover)
    {
        if (x == false) return false;
    }
    return true;
}

void GenAllSubset(vector<int> a, int reqLen, int s, int currLen, bool check[], int len, vector<vector<int>> &G, bool &found) {
    if (found) return;
    if(currLen > reqLen)
        return;
    else if (currLen == reqLen) {
        vector<int> vc;
        vector<int> ans(G.size(), 0);
        for (int i = 0; i < len; i++) {
            if (check[i] == true) {
                vc.push_back(i);
                ans[i] = 1;
            }
        }
        bool res = hasVertexCover(G, vc.size(), vc);
        if (res)
        {
            cout << "Minimum solution is " << vc.size() << " node(s)." << endl;
            found = true;
            for (int i = 0; i < G.size(); i++)
            {
                cout << ans[i];
            }
            cout << endl;
        }

        return;
    }
    if (s == len) {
        return;
    }
    check[s] = true;
    GenAllSubset(a, reqLen, s + 1, currLen + 1, check, len, G, found);
    check[s] = false;
    GenAllSubset(a, reqLen, s + 1, currLen, check, len, G, found);
}

int main()
{
    int V, E;
    cin >> V;
    cin >> E;
    bool ch[V];
    vector<vector<int>> G(V, vector<int> (V, 0));
    vector<int> vertexes;
    omp_set_num_threads(8);
    for (int i =0; i<V; i++)
    {
        vertexes.push_back(i);
        ch[i] = false;
    }
    for (int i=0; i<E; i++)
    {
        int u,v;
        cin >> u >> v;
        insertEdge(G, u, v);
    }
    bool found = false;
    for (int i=1; i<= V; i++)
    {
        GenAllSubset(vertexes, i, 0, 0, ch, V, G, found);
        if (found) break;
    }
    
    return 0;
}