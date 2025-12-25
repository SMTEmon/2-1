#include <bits/stdc++.h>

using namespace std;

class GraphwAL
{
    vector<vector<int>> adj_Nodes;

    void DFSUtil(int curr, vector<bool> &visited)
    {
        visited[curr] = true;
        cout << curr << " ";

        for (int nei : adj_Nodes[curr])
        {
            if (!visited[nei])
            {
                DFSUtil(nei, visited);
            }
        }
    }

public:
    GraphwAL(int n)
    {
        adj_Nodes = vector<vector<int>>(n);
    }
    void add_edge(int u, int v)
    {
        if (u >= adj_Nodes.size() || v >= adj_Nodes.size())
            adj_Nodes.resize(max(u, v) + 1);

        adj_Nodes[u].push_back(v);
        adj_Nodes[v].push_back(u);
    }

    void print_graph()
    {
        int size_of_adj = adj_Nodes.size();

        for (int node = 0; node < size_of_adj; node++)
        {
            int adj_nei = adj_Nodes[node].size();

            for (int nei = 0; nei < adj_nei; nei++)
            {
                cout << adj_Nodes[node][nei] << " ";
            }

            cout << "\n";
        }
    }

    void bfs(int startVer)
    {
        vector<bool> visited(adj_Nodes.size(), false);
        queue<int> q;

        visited[startVer] = true;
        q.push(startVer);

        cout << "BFS starting from: " << startVer << ": ";

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            cout << curr << " ";

            for (int nei : adj_Nodes[curr])
            {
                if (!visited[nei])
                {
                    visited[nei] = true;
                    q.push(nei);
                }
            }
        }

        cout << "\n";
    }

    void DFSbyRec(int startt)
    {
        vector<bool> visited(adj_Nodes.size(), false);

        cout << "Starting DFS from " << startt << ": ";

        DFSUtil(startt, visited);

        cout << "\n";
    }

    void DFSbyIt(int startt)
    {
        vector<bool> visited(adj_Nodes.size(), false);

        stack<int> s;
        s.push(startt);

        cout << "Started DFS from " << startt << ": ";

        while (!s.empty())
        {
            int curr = s.top();
            s.pop();

            if (!visited[curr])
            {
                visited[curr] = true;
                cout << curr << " ";
            }

            for (int nei : adj_Nodes[curr])
            {
                if (!visited[nei])
                {
                    s.push(nei);
                }
            }
        }

        cout << "\n";
    }
};
