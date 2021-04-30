#include<iostream>
#include<vector>
#include <fstream>
#include <string>
// #include<omp.h>

using namespace std;

void printAdj(vector<vector<int>> &G)
{
    for (int i=0; i<G.size(); i++)
    {
        for (int j=0; j<G.size() ; j++)
        {
            cout << G[i][j] << " ";
        }
        cout << endl;
    }
}

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

void GenAllSubset(vector<int> a, int reqLen, int s, int currLen, bool check[], int len, vector<vector<int>> &G, bool &found, char *outfile) {
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
            ofstream out;
            out.open(outfile);
            out << "Minimum solution is " << vc.size() << " node(s)." << endl;
            cout << "Minimum solution is " << vc.size() << " node(s)." << endl;
            found = true;
            for (int i = 0; i < G.size(); i++)
            {
                out << ans[i];
                cout << ans[i];
            }
            out << endl;
            cout << endl;
        }

        return;
    }
    if (s == len) {
        return;
    }
    check[s] = true;
    GenAllSubset(a, reqLen, s + 1, currLen + 1, check, len, G, found, outfile);
    check[s] = false;
    GenAllSubset(a, reqLen, s + 1, currLen, check, len, G, found, outfile);
}

int main(int argc, char *argv[])
{
    int V, E;

    vector<int> vertexes;
    vector<vector<int>> G;

    char *filename = argv[1];

    std::ifstream input(filename);
 
    int c = 0;
    for( std::string line; getline( input, line ); )
    {
        if (c == 0)
        {
            V = stoi(line);
            G.resize(V, vector<int> (V, 0));
        } else if (c == 1)
        {
            E  =stoi(line);
        } else
        {
            string delimiter = " ";
            auto pos = line.find(delimiter);
            string u_str = line.substr(0, pos);
            string v_str = line.substr(pos, line.size());
            // cout << u_str << "sadasdd" << endl;
            int u = stoi(u_str);
            int v = stoi(v_str);
            insertEdge(G, u, v);
        }
        c++;
    }
    // printAdj(G);
    // // Use a while loop together with the getline() function to read the file line by line
    // while (getline (MyReadFile, text)) {
    // // Output the text from the file
    //     cout << text;
    // }

    // Close the file
    // MyReadFile.close();
    // cin >> V;
    // cin >> E;
    // omp_set_num_threads(8);
    bool ch[V];
    for (int i =0; i<V; i++)
    {
        vertexes.push_back(i);
        ch[i] = false;
    }
    // for (int i=0; i<E; i++)
    // {
    //     int u,v;
    //     cin >> u >> v;
    //     insertEdge(G, u, v);
    // }
    bool found = false;
    char *outfile = argv[2];
    for (int i=1; i<= V; i++)
    {
        GenAllSubset(vertexes, i, 0, 0, ch, V, G, found, outfile);
        if (found) break;
    }
    
    return 0;
}