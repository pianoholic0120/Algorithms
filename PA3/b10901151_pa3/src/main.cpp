#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<functional>
#include<algorithm>
using namespace std;

struct Edge{
    int u, v, w;
    Edge(int s, int d, int w) : u(s), v(d), w(w) {}
};

class Graph{
public:
    int V, E;
    vector<Edge> edges;
    vector<vector<pair<int, int>>> adjList;

    Graph(int V, int E) : V(V), E(E){ // constructor
        adjList.resize(V);
    }

    void addEdge(int u, int v, int w){
        Edge edge(u, v, w);
        edges.push_back(edge);
        adjList[u].emplace_back(v, w);
    }
    void sortEdges(){
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b){
            return a.w > b.w;
        });
    }
    int findParent(vector<int>& parent, int vertex){ // find in union set
        if(parent[vertex]==-1)  return vertex;
        return findParent(parent, parent[vertex]);
    }
    void unionSets(vector<int>& parent, int x, int y){
        int xParent = findParent(parent, x);
        int yParent = findParent(parent, y);
        parent[yParent] = xParent;
    }
    void findMaximumSpanningTree(multiset<Edge, function<bool(const Edge&, const Edge&)>>& remainingEdges){
        multiset<Edge, function<bool(const Edge&, const Edge&)>> setMST([](const Edge& a, const Edge& b){
            return a.w > b.w;
        });
        vector<int> parent(V, -1);
        for(const Edge& edge : edges){
            int uParent = findParent(parent, edge.u);
            int vParent = findParent(parent, edge.v);
            if(uParent != vParent){
                setMST.insert(edge);
                unionSets(parent, uParent, vParent);
            }else{
                remainingEdges.insert(edge);
            }
        }
        set<Edge, function<bool(const Edge&, const Edge&)>> edgesToRemove([](const Edge& a, const Edge& b){
            return a.w > b.w;
        });
        for(const Edge& edge : remainingEdges){
            int v = edge.v;
            if(adjList[v].empty()){
                edgesToRemove.insert(edge);
                setMST.insert(edge);
            }
        }
        for(const Edge& edge : edgesToRemove){
            multiset<Edge>::iterator pos = remainingEdges.find(edge);
            remainingEdges.erase(pos);
        }
    }
};

int main(int argc, char* argv[]){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    char ch;
    int V, E;
    fin >> ch >> V >> E;
    if(ch == 'u'){
        vector<Edge> edges;
        for(int i = 0; i < E; ++i){
            int v1, v2, w;
            fin >> v1 >> v2 >> w;
            edges.emplace_back(v1, v2, w);
        }
        Graph graph(V, E);
        for(const Edge& edge : edges){
            graph.addEdge(edge.u, edge.v, edge.w);
        }
        multiset<Edge, function<bool(const Edge&, const Edge&)>> remainingEdges([](const Edge& a, const Edge& b){
            return a.w > b.w;
        });
        graph.sortEdges();
        graph.findMaximumSpanningTree(remainingEdges);
        long long sum = 0;
        for(const Edge& edge : remainingEdges){
            sum += edge.w;
        }
        fout << sum << endl;
        for(const Edge& edge : remainingEdges){
            fout << edge.u << " " << edge.v << " " << edge.w << endl;
        }
    }
    else if(ch == 'd'){
        Graph graph(V, E);
        for(int i = 0; i < E; i++){
            int u, v, w;
            fin >> u >> v >> w;
            graph.addEdge(u, v, w);
        }
        int redundant;
        fin >> redundant; 
        multiset<Edge, function<bool(const Edge&, const Edge&)>> remainingEdges([](const Edge& a, const Edge& b) { return a.w > b.w; });
        graph.findMaximumSpanningTree(remainingEdges);
        long long outputw = 0;
        for(auto& edge : remainingEdges){
            outputw += edge.w;
        }
        fout << outputw << endl;
        for(auto& edge : remainingEdges){
            fout << edge.u << " " << edge.v << " " << edge.w << endl;
        }
    }

    fin.close();
    fout.close();
    return 0;
}