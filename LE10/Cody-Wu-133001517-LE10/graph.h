#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <queue>
#include <unordered_set>
using namespace std;

class Graph {
    private:
        int n;
        typedef pair<int, int> Edge;
        vector<list<Edge>> v;
        
    public:
        Graph(int size = 2) {
            n = size;
            v.resize(n);
        }

        void addEdge(int x, int y, int w) {
            Edge first (y, w);
            v[x].push_front(first);

            Edge second (x, w);
            v[y].push_front(second);
        }

        void print() {
            for(int i = 0; i < n; i++) {
                cout << "Node " << i << " is connected to: ";
                for (pair<int,int> j : v[i]) {
                    if(j.first != -1){
                        cout << j.first << " : "<< j.second<<", ";
                    }
                }
                cout << endl;
            }
        }

        vector<pair<int, int>> dijkstra(int startNode) {
            vector<pair<int, int>> p(n, {INT_MAX, -1});
            p[startNode] = {0, -1};
            
            priority_queue<pair<int, int>> pq;
            pq.push({0, startNode});

            while (!pq.empty()) {
                int z = pq.top().second;
                int zdist = pq.top().first;
                pq.pop();

                if (zdist > p[z].first) {
                    continue;
                }

                for (list<Edge>::iterator iter = v[z].begin(); iter != v[z].end(); iter++) {
                    Edge& edge = *iter;
                    int w = edge.first;
                    int weight = edge.second;

                    if (p[z].first + weight < p[w].first) {
                        p[w] = {p[z].first + weight, z};
                        pq.push({p[w].first, w});
                    }
                }
            }

            return p;
        }

        string printShortestPath(int startNode, int endNode) {
           
            vector<pair<int, int>> shortest = dijkstra(startNode);

            if (shortest[endNode].first == INT_MAX) {
                return "";
            }

            string path = to_string(endNode);
            int currentNode = endNode;

            while (currentNode != -1) {
                path = to_string(currentNode) + " " + path;
                currentNode = shortest[currentNode].second;
            }
            
            return path;
                    
        }
};
