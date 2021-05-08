#include <iostream>
#include <vector>

const long long INF = 9e18;
const long long MINUS_INF = -9e18;

struct triple {
    triple() = default;
    triple(long long first, long long second, long long dist): first(first), second(second), dist(dist) {}
    long long first;
    long long second;
    long long dist;
};

class Graph{
public:
    Graph(long long n, long long m, std::vector<triple> pairs): n(n), m(m), pairs(pairs), list_of_adjacency(n + 1), tin(n + 1),
                                                                tout(n + 1), dist(n + 1, INF), color(n + 1, 0) {
        for (int i = 0; i < m; ++i) {
            list_of_adjacency[pairs[i].first].push_back({pairs[i].second, pairs[i].dist});
        }
    }

    std::vector<long long> ford_bellman(long long s) {
        dist[s] = 0;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (dist[pairs[j].first] != INF) {
                    dist[pairs[j].second] = std::min(dist[pairs[j].second], pairs[j].dist + dist[pairs[j].first]);
                }
            }
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (std::abs(dist[pairs[j].second]) != INF && dist[pairs[j].second] > pairs[j].dist + dist[pairs[j].first]) {
                    do_dfs(pairs[j].second);
                }
            }
        }
        return dist;
    }

    void do_dfs(int v) {

        std::vector<long long> parents;
        dfs(v);
    }

    void dfs(int v) {
        color[v] = 1;
        dist[v] = MINUS_INF;
        tin[v] = ++timer;
        for (size_t i = 0; i < list_of_adjacency[v].size(); ++i) {
            if (color[list_of_adjacency[v][i].first] != 0) {
                continue;
            }
            dfs(list_of_adjacency[v][i].first);
        }
        tout[v] = ++timer;
        color[v] = 2;
    }

    long long t_in(long long index) {
        return tin[index];
    }

    long long t_out(long long index) {
        return tout[index];
    }

private:
    long long n;
    long long m;
    std::vector<triple> pairs;
    std::vector<std::vector<bool>> matrix_of_adjacency;
    std::vector<std::vector<std::pair<long long, long long>>> list_of_adjacency;
    std::vector<std::vector<std::pair<long long, long long>>> reverse_list_of_adjacency;
    std::vector<int8_t> color;
    std::vector<long long> dist;
    std::vector<long long> tin;
    std::vector<long long> tout;
    std::vector<long long> ret;
    long long timer = 0;
};

int main() {
    long long n;
    long long m;
    long long s;
    std::cin >> n >> m >> s;
    std::vector<triple> pairs(m);
    for (int i = 0; i < m; ++i) {
        long long first, second, dist;
        std::cin >> first >> second >> dist;
        pairs[i] = {first, second, dist};
    }
    Graph g = Graph(n, m, pairs);
    std::vector<long long> ans = g.ford_bellman(s);
    for (int i = 1; i <= n; ++i) {
        if (ans[i] == INF) {
            std::cout << '*' << "\n";
        } else if (ans[i] == MINUS_INF) {
            std::cout << '-' << "\n";
        } else {
            std::cout << ans[i] << "\n";
        }
    }
    return 0;
}
