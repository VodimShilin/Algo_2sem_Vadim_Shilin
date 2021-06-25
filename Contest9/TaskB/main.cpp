#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <algorithm>

const long long INF = 9e18;

struct Vertice {
    Vertice(long long self, long long another, long long value, long long index): self(self), another(another), value(value), index_edge(index) {}
    long long self;
    long long another;
    long long value;
    long long index_edge;
};

struct Edge {
    Edge() = default;
    Edge(long long first, long long second, long long dist, long long index): first(first), second(second), dist(dist), index(index) {}
    long long first;
    long long second;
    long long dist;
    long long index;
};

class Graph{
public:
    Graph(long long n, long long m): n(n), m(m), list_of_adjacency(n), edges(m) {
        for (int i = 0; i < m; ++i) {
            long long first, second, length;
            std::cin >> first >> second >> length;
            --first;
            --second;
            list_of_adjacency[first].push_back({first, second, length, i});
            list_of_adjacency[second].push_back({second, first, length, i});
            //edges[i] = {first, second, length, i};
        }
    }

    long long find_smallest_cycle() {
        long long min_ = INF;
        for (int i = 0; i < n; ++i) {
            long long x = k_bfs(i);
            min_ = std::min(min_, x);
        }
        return min_;
    }

    long long k_bfs(long long index) {
        std::vector<std::queue<long long>> q(11 * n + 1);
        std::vector<std::pair<long long, long long>> dist(n, {INF, INF});
        std::vector<bool> used_edge(m);
        dist[index] = {0, 0};
        q[0].push(index);
        for (int i = 0; i < 11 * n + 1; ++i) {
            while (!q[i].empty()) {
                long long v = q[i].front();
                if (v != index && dist[v].second != INF) {
                    return dist[v].first + dist[v].second;
                }
                q[i].pop();
                for (int j = 0; j < list_of_adjacency[v].size(); ++j) {
                    if (used_edge[list_of_adjacency[v][j].index]) continue;
                    if (dist[list_of_adjacency[v][j].second].first == INF) {
                        dist[list_of_adjacency[v][j].second].first = dist[v].first + list_of_adjacency[v][j].dist;
                        q[dist[list_of_adjacency[v][j].second].first].push(list_of_adjacency[v][j].second);
                    } else if (dist[v].first + list_of_adjacency[v][j].dist < dist[list_of_adjacency[v][j].second].second) {
                        dist[list_of_adjacency[v][j].second].second = dist[v].first + list_of_adjacency[v][j].dist;
                        if (dist[list_of_adjacency[v][j].second].second < dist[list_of_adjacency[v][j].second].first) {
                            std::swap(dist[list_of_adjacency[v][j].second].first, dist[list_of_adjacency[v][j].second].second);
                            q[dist[list_of_adjacency[v][j].second].first].push(list_of_adjacency[v][j].second);
                        } else {
                            q[dist[list_of_adjacency[v][j].second].second].push(list_of_adjacency[v][j].second);
                        }
                    }
                    used_edge[list_of_adjacency[v][j].index] = 1;
                }
            }
        }
    }

private:
    long long n;
    long long m;
    std::vector<std::vector<long long>> matrix_of_adjacency;
    std::vector<std::vector<long long>> number_of_edge;
    std::vector<std::vector<Edge>> list_of_adjacency;
    std::vector<std::vector<long long>> matrix_of_incidence;
    std::vector<Edge> edges;
};

int main() {
    long long n, m;
    std::cin >> n >> m;
    Graph g = Graph(n, m);
    std::cout << g.find_smallest_cycle();
    return 0;
}
