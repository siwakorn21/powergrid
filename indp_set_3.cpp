// C++ code to check if a given graph
// contains an independent set of size k
#include <bits/stdc++.h>
using namespace std;
 
// Function prototype
bool check(int[][5], vector<int> &, int);
 
// Function to construct a set of given size k
bool func(int graph[][5], vector<int> &arr,
          int k, int index, bool sol[])
{
    // Check if the selected set is independent or not.
    // Change the value of sol to True and return
    // if it is independent
    if (k == 0)
    {
        if (check(graph, arr, arr.size()))
        {
            sol[0] = true;
            return true;
        }
    }
    else
    {
        // Set of size k can be formed even if we don't
        // include the vertex at current index.
        if (index >= k)
        {
            vector<int> newvec(arr.begin(), arr.end());
            newvec.push_back(index);
            return (func(graph, newvec, k - 1,
                                index - 1, sol) or
                    func(graph, arr, k, index - 1, sol));
        }
 
        // Set of size k cannot be formed if we don't
        // include the vertex at current index.
        else
        {
            arr.push_back(index);
            return func(graph, arr, k - 1,
                          index - 1, sol);
        }
    }
}
 
// Function to check if the given set is
// independent or not
// arr --> set of size k (contains the
// index of included vertex)
bool check(int graph[][5], vector<int> &arr, int n)
{
    // Check if each vertex is connected to any other
    // vertex in the set or not
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (graph[arr[i]][arr[j]] == 1)
                return false;
    return true;
}
 
// Driver Code
int main()
{
    int graph[][5] = {{1, 1, 0, 0, 0},
                      {1, 1, 1, 1, 1},
                      {0, 1, 1, 0, 0},
                      {0, 1, 0, 1, 0},
                      {0, 1, 0, 0, 1}};
    int k;
    cout << "enter k: ";
    cin >> k;
    cout << endl;
    vector<int> arr; // Empty set
    bool sol[] = {false};
    int n = sizeof(graph) /
            sizeof(graph[0]);
    func(graph, arr, k, n - 1, sol);
    cout << n << endl;
 
    if (sol[0])
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}
 
// This code is contributed by
// sanjeev2552