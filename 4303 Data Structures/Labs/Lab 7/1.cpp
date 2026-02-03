#include<bits/stdc++.h>

using namespace std;

class GraphMT{
    vector<vector<int> > adj_mat;

    void DFSUtil(int curr, vector<bool>& visited){
        visited[curr] = true;
        cout << curr << " ";
        for (int i = 0 ; i < visited.size(); i++){
            if (adj_mat[curr][i] != 0 && !visited[i]){
                DFSUtil(i, visited);
            }
        }
    } 

public:
    GraphMT(int s){
        adj_mat = vector<vector<int> > (s, vector<int>(s, 0));
    }
    void add_edge(int u, int v){
        adj_mat[u][v] = adj_mat[v][u] = 1;
    }

    void print_graph(){
        int size_of_mt = adj_mat.size();
        for (int row = 0; row < size_of_mt; row++){
            for (int col = 0; col < size_of_mt; col++){
                cout << adj_mat[row][col] << " ";
            }
            cout << "\n";
        }
    }

    void BFS(int startt){
        vector<bool> visited (adj_mat.size(), false);
        cout << "BFS Traversal: ";
        
        queue<int> q;
        q.push(startt);
        visited[startt] = true;

        while(!q.empty()){
            int curr = q.front();
            q.pop();


            cout << curr << " ";

            for (int i = 0; i < adj_mat.size(); i++){
                if (adj_mat[curr][i] != 0 && !visited[i]){
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
        
    }

    void DFS(int startt){
        vector<bool> visited (adj_mat.size(), false);
        cout << "DFS Traversal: ";
        DFSUtil(startt, visited);
    }
};

class GraphLS{
    vector<vector<int> > adj_ls;

    void DFSUtil(int curr, vector<bool>& visited){
        visited[curr] = true;
        cout << curr << " ";
        for(int nei : adj_ls[curr]){
            if (!visited[nei]){
                DFSUtil(nei, visited);
            }
        }
    }

public:
    GraphLS(int s){
        adj_ls = vector<vector<int> > (s);
    }
    void add_edge(int u, int v){
        
        adj_ls[u].push_back(v);
        adj_ls[v].push_back(u);
        
    }

    void print_graph(){
        int size_of_ls = adj_ls.size();
        for (int row = 0; row < size_of_ls; row++){
            cout << row << "-> ";
            for (int nei : adj_ls[row]){
                cout << nei << " ";
            }
            cout << "\n";
        }
    }


    void BFS(int startt){
        vector<bool> visited (adj_ls.size(), false);
        cout << "BFS Traversal: ";
        
        queue<int> q;
        q.push(startt);
        visited[startt] = true;

        while(!q.empty()){
            int curr = q.front();
            q.pop();


            cout << curr << " ";

            for(int nei : adj_ls[curr]){
                if (!visited[nei]){
                    q.push(nei);
                    visited[nei] = true;
                }
            }
        
        }  
    }

    void DFS(int startt){
        vector<bool> visited (adj_ls.size(), false);
        cout << "DFS Traversal: ";
        DFSUtil(startt, visited);
    }

    void shortest_path(int startt){
        vector<bool> visited (adj_ls.size(), false);
        cout << "Distance from Node " << startt << endl;
        
        queue<int> q;
        q.push(startt);
        visited[startt] = true;

        int steps = 0;

        
        int distance[adj_ls.size()];
        memset(distance, -1, adj_ls.size());


        distance[startt] = 0;


        while(!q.empty()){
            int curr = q.front();
            q.pop();

            cout << curr << " ";

            for(int nei : adj_ls[curr]){
                if (!visited[nei]){
                    q.push(nei);
                    visited[nei] = true;
                    distance[nei] = distance[curr] + 1;
                }
            }
        
        } 

        
        for(int i = 0; i < adj_ls.size(); i++){
            cout << "Node " << i << ": "<< distance[i] << "\n";
        }

    }

};

int main(){
    int var, edge;
    cin >> var >> edge;
    GraphMT MT(var);
    GraphLS LS(var);

    for (int i = 0; i < edge; i++){
        int u, v;
        cin >> u >> v;
        MT.add_edge(u, v);
        LS.add_edge(u, v);
    }

    MT.print_graph();
    cout << endl;
    LS.print_graph();
    cout << endl;

    LS.shortest_path(0);
}