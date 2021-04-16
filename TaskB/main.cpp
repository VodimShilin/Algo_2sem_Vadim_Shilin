#include <iostream>
#include <vector>

class Graph{
public:
    Graph(long long n, std::vector<long long> parents): n(n), m(n - 1), list_of_adjacency(n + 1), parents(parents), tin(n + 1), tout(n + 1) {
        for (int i = 1; i <= n; ++i) {
            list_of_adjacency[parents[i]].push_back(i);
        }
    }

    void do_dfs() {
        std::vector<int8_t> color(n + 1, 0);
        long long index_head = 0;
        for (int i = 1; i <= n; ++i) {
            if (parents[i] == 0) {
                index_head = i;
                break;
            }
        }
        dfs(index_head, color);
    }

    void dfs(int v, std::vector<int8_t>& color) {
        color[v] = 1;
        tin[v] = ++timer;
        for (size_t i = 0; i < list_of_adjacency[v].size(); ++i) {
            if (color[list_of_adjacency[v][i]] != 0) {
                continue;
            }
            dfs(list_of_adjacency[v][i], color);
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
    std::vector<std::pair<long long, long long>> pairs;
    std::vector<std::vector<long long>> matrix_of_adjacency;
    std::vector<std::vector<long long>> number_of_edge;
    std::vector<std::vector<long long>> list_of_adjacency;
    std::vector<std::vector<long long>> matrix_of_incidence;
    std::vector<long long> parents;
    std::vector<long long> tin;
    std::vector<long long> tout;
    long long timer = 0;
};

int main() {
    long long n;
    long long m;
    std::cin >> n;
    std::vector<long long> parents(n + 1);
    for (int i = 1; i <= n; ++i) {
        long long x;
        std::cin >> x;
        parents[i] = x;
    }
    Graph g = Graph(n, parents);
    g.do_dfs();
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        long long x, y;
        std::cin >> x >> y;
        if (g.t_in(x) < g.t_in(y) && g.t_out(x) > g.t_out(y)) {
            std::cout << 1 << "\n";
        } else {
            std::cout << 0 << "\n";
        }
    }
    return 0;
}
