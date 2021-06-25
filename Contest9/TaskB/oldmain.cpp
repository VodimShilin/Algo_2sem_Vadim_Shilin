#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <algorithm>

const long long INF = 9e18;

struct element {
    element(long long another, long long value): another(another), value(value) {}
    long long another;
    long long value;
};

struct triple {
    triple(long long first, long long second, long long dist): first(first), second(second), dist(dist) {}
    long long first;
    long long second;
    long long dist;
};

class Graph{
public:
    Graph(long long n, long long m, const std::vector<std::vector<element>>& list_of_adjacency): n(n), m(m), list_of_adjacency(list_of_adjacency) {}

    int find_smallest_cycle() {
        long long min_ = INF;
        for (int i = 0; i < n; ++i) {
            long long x = k_bfs(i);
            min_ = std::min(min_, x);
        }
        return min_;
    }

    int k_bfs(int index) {
        std::vector<std::queue<triple>> q(11 * n + 1);
        std::vector<long long> dist(n, INF);
        std::vector<bool> vertices(n, 0);
        q[0].push({index, -1, 0});
        dist[index] = 0;
        for (int i = 0; i < 11 * n + 1; ++i) {
            if (i > 1) {i = i;}
            while (!q[i].empty()) {
                int v = q[i].front().first;
                int par = q[i].front().second;
                if (vertices[v]) {
                    return dist[par] + dist[v] + q[i].front().dist;
                }
                q[i].pop();
                vertices[v] = 1;
                for (auto to: list_of_adjacency[v]) {
                    if (!vertices[to.another]) {
                        dist[to.another] = dist[v] + to.value;
                    }
                    if (to.another != par) {
                        q[dist[to.another]].push({to.another, v, to.value});
                    }
                }
            }
        }
    }

private:
    long long n;
    long long m;
    std::vector<std::pair<long long, long long>> pairs;
    std::vector<std::vector<long long>> matrix_of_adjacency;
    std::vector<std::vector<long long>> number_of_edge;
    std::vector<std::vector<element>> list_of_adjacency;
    std::vector<std::vector<long long>> matrix_of_incidence;
};

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::vector<std::vector<element>> list_of_adjacency(n);
    for (int i = 0; i < m; ++i) {
        long long first, second, length;
        std::cin >> first >> second >> length;
        --first;
        --second;
        element x = {second, length};
        list_of_adjacency[first].push_back(x);
        element y = {first, length};
        list_of_adjacency[second].push_back(y);
    }
    Graph g = Graph(n, m, list_of_adjacency);
    std::cout << g.find_smallest_cycle();
    return 0;
}
