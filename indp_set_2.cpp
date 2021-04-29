#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

bool check(vector<vector<int>> &, vector<int> &, int);

bool func(vector<vector<int>> &graph, vector<int> &arr,
          int k, int index, bool sol[])
{
    if (k == 0)
    {
        if (check(graph, arr, arr.size()))
        {
            sol[0] = true;
            return true;
        } else
        {
            return false;
        }
    }
    else
    {
        if (index >= k)
        {
            vector<int> newvec(arr.begin(), arr.end());
            newvec.push_back(index);
            return (func(graph, newvec, k - 1,
                                index - 1, sol) or
                    func(graph, arr, k, index - 1, sol));
        }
 
        else
        {
            arr.push_back(index);
            return func(graph, arr, k - 1,
                          index - 1, sol);
        }
    }
}
 
bool check(vector<vector<int>> &graph, vector<int> &arr, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (graph[arr[i]][arr[j]] == 1)
                return false;
    return true;
}

int findMax(vector<vector<int>> &graph, vector<int> &arr,bool sol[])
{
    int k = 1;
    int n = graph.size();
    bool limit = false;
    int v = graph.size();
    while (!limit)
    {
        bool result = func(graph, arr, k, n-1, sol);
        // cout << result << endl;
        if (result)
        {
            cout << "My new sol is " << v - k << endl;
            k++;
        }
        else
        {
            limit = true;
        }
    }
    return k;
}

 
int main()
{
    int V, E;
    cin >> V;
    cin >> E;
    // int graph[V][V];
    vector<vector<int>> graph(V, vector<int> (V, 0));
    for (int i=0; i<E; i++)
    {
        int u,v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
    }
    vector<int> arr; // Empty set
    bool sol[] = {false};
    int n = graph.size();
    int max = findMax(graph, arr, sol);
    cout << "My new sol is " << V - max << endl;
}
