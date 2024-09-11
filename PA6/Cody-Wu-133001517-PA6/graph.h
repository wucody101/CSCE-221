#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Graph {
    private:
        unordered_map<int, unordered_map<int, int>> adjList;

    public:
        Graph() {};

        bool contains_vertex(int u) {
            return adjList.find(u) != adjList.end();
        }

        bool contains_edge(int u, int v) {
            if (contains_vertex(u) && contains_vertex(v)) {
                return adjList[u].find(v) != adjList[u].end();
            }

            return false;
        }

        void addVertex(int u) {
            if (!contains_vertex(u)) {
                adjList[u] = unordered_map<int, int>();
            }
        }

        void addEdge(int u, int v, int w) {
            addVertex(u);
            addVertex(v);
            adjList[u][v] = w;
            adjList[v][u] = w;
        }

        void removeEdge(int u, int v) {
            if (contains_edge(u, v)) {
                adjList[u].erase(v);
                adjList[v].erase(u);
            }
        }

        void removeVertex(int id) {
            if (contains_vertex(id)) {
                for (unordered_map<int, int>::iterator iter = adjList[id].begin(); iter != adjList[id].end(); iter++) {
                    int temp = (*iter).first;
                    adjList[temp].erase(id);
                }
                adjList.erase(id);
            }
        }

        int numVertices() {
            return adjList.size();
        }

        int getEdgeWeight(int u, int v) {
            if (contains_edge(u, v)) {
                return adjList[u][v];
            }
            
            return -1;
        }

        vector<pair<int, int>> primMST() {
            vector<pair<int, int>> result;
            unordered_set<int> visited;

            if (!adjList.empty()) {
                int first = adjList.begin()->first;
                visited.insert(first);
                
                while (visited.size() < adjList.size()) {
                    int min = INT_MAX;
                    pair<int, int> minEdge = {-1, -1};

                    for (auto iter = visited.begin(); iter != visited.end(); iter++) {
                        for (auto it = adjList[*iter].begin(); it != adjList[*iter].end(); it++) {
                            int vertex = (*it).first;
                            int weight = (*it).second;

                            if (visited.find(vertex) == visited.end() && weight < min) {
                                min = weight;
                                minEdge = {(*iter), vertex};
                            }
                        }
                    }

                    if (minEdge.first != -1 && minEdge.second != -1) {
                        result.push_back(minEdge);
                        visited.insert(minEdge.second);
                    }
                }
            }

            return result;
        }
};
