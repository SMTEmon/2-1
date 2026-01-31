#include <bits/stdc++.h>

using namespace std;

class GraphWithAdjMatrix
{
    vector<vector<int>> adj_mat;

    void DFSUtil(int curr, vector<bool> &visited)
    {
        visited[curr] = true;
        cout << curr << " ";

        for (int nei = 0; nei < adj_mat.size(); nei++)
        {
            if (adj_mat[curr][nei] != 0 && !visited[nei])
            {
                DFSUtil(nei, visited);
            }
        }
    }

public:
    GraphWithAdjMatrix(int n)
    {
        adj_mat = vector<vector<int>>(n, vector<int>(n, 0));
    }

    void add_edge(int u, int v)
    {
        adj_mat[u][v] = adj_mat[v][u] = 1;
    }

    void print_mat()
    {
        int matSize = adj_mat.size();
        for (int row = 0; row < matSize; row++)
        {
            for (int col = 0; col < matSize; col++)
            {
                cout << adj_mat[row][col] << " ";
            }
            cout << "\n";
        }
    }

    void BFS(int startt)
    {
        int size_of_mat = adj_mat.size();
        vector<bool> visited(size_of_mat, false);
        queue<int> q;

        visited[startt] = true;
        q.push(startt);

        cout << "Start BFS from " << startt << ": ";

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            if (!visited[curr])
            {
                visited[curr] = true;

                cout << curr << " ";
            }

            for (int nei = 0; nei < size_of_mat; nei++)
            {
                if (adj_mat[curr][nei] != 0 && !visited[nei])
                {
                    q.push(nei);
                }
            }
        }
    }

    void DFSbyRec(int startt)
    {
        vector<bool> visited(adj_mat.size(), false);
        cout << "Starting DFS from " << startt << ": ";

        DFSUtil(startt, visited);

        cout << "\n";
    }

    void DFSbyIt(int startt)
    {
        vector<bool> visited(adj_mat.size(), false);
        stack<int> s;

        s.push(startt);

        cout << "Starting DFS from " << startt << ": ";

        while (!s.empty())
        {
            int curr = s.top();
            s.pop();
            cout << curr << " ";

            for (int nei = 0; nei < adj_mat.size(); nei++)
            {
                if (adj_mat[curr][nei] != 0 && !visited[nei])
                {
                    visited[nei] = true;
                    s.push(nei);
                }
            }
        }
    }
};

// int main()
// {
//     GraphWithAdjMatrix g(4);
//     g.add_edge(0, 1);
//     g.add_edge(0, 2);
//     g.add_edge(1, 3);
//     g.add_edge(2, 3);

//     g.print_mat();
// }