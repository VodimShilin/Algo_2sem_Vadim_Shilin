#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <set>

const long long INF = 1e18;

struct triple {
    triple() = default;
    triple(long long first, long long second, long long dist): first(first), second(second), dist(dist) {}
    long long first;
    long long second;
    long long dist;
};

struct element {
    element(long long value, long long dist): value(value), dist(dist) {}
    long long value;
    long long dist;
    bool operator>(const element& another) const {
        return dist > another.dist || (dist == another.dist && value > another.value);
    }
    bool operator<(const element& another) const {
        return dist < another.dist || (dist == another.dist && value < another.value);
    }
    bool operator==(const element& another) const {
        return dist == another.dist && value == another.value;
    }
};

class Graph{
public:
    Graph(long long n, long long m, const std::vector<triple>& edges): n(n), m(m), list_of_adjacency(n + 1), used(n + 1) {
        for (int i = 0; i < m; ++i) {
            list_of_adjacency[edges[i].first].push_back({edges[i].second, edges[i].dist});
            list_of_adjacency[edges[i].second].push_back({edges[i].first, edges[i].dist});
        }
    }
    long long dijkstra(long long v, long long u) {
        std::set<element> q;
        std::vector<long long> dist(n + 1, INF);
        dist[v] = 0;
        q.insert({v, 0});
        while (!q.empty()) {
            auto x = q.begin()->value;
            q.erase(q.begin());
            for (auto to: list_of_adjacency[x]) {
                if (dist[to.value] > dist[x] + to.dist) {
                    dist[to.value] = dist[x] + to.dist;
                    q.insert({to.value, dist[to.value]});
                }
            }
        }
        return dist[u];
    }
private:
    long long n;
    long long m;
    std::vector<std::pair<long long, long long>> pairs;
    std::vector<std::vector<long long>> matrix_of_adjacency;
    std::vector<std::vector<long long>> number_of_edge;
    std::vector<std::vector<element>> list_of_adjacency;
    std::vector<std::vector<long long>> matrix_of_incidence;
    std::vector<bool> used;
};

int main() {
    long long n, m, s, t;
    std::cin >> n >> m >> s >> t;
    std::vector<triple> edges(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i].first >> edges[i].second >> edges[i].dist;
    }
    Graph g = Graph(n, m, edges);
    long long ans = g.dijkstra(s, t);
    if (ans == INF) {
        std::cout << -1;
    } else {
        std::cout << ans;
    }
    return 0;
}
