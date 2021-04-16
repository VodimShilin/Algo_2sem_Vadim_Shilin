#include <iostream>
#include <vector>
 
class Graph{
public:
    Graph(long long n, std::vector<std::pair<long long, long long>> pairs): n(n), m(pairs.size()), list_of_adjacency(n + 1), tin(n + 1), tout(n + 1){
        for (int i = 0; i < m; ++i) {
            list_of_adjacency[pairs[i].first].push_back(pairs[i].second);
        }
    }
 
    void consist_cycles() {
        try {
            std::vector<int8_t> color(n + 1, 0);
            std::vector<long long> parents(n + 1);
            for (int i = 1; i <= n; ++i) {
                if (color[i] != 0) {
                    continue;
                }
                dfs(i, color, parents);
            }
            return;
        } catch (found_grey x) {
            std::vector<long long> cycle;
            int i = x.parent;
            while (i != x.index) {
                cycle.push_back(i);
                i = x.parents[i];
            }
            cycle.push_back(x.index);
            throw cycle;
        }
    }
 
    void dfs(int v, std::vector<int8_t>& color, std::vector<long long>& parents, long long p = 0) {
        color[v] = 1;
        parents[v] = p;
        tin[v] = ++timer;
        for (size_t i = 0; i < list_of_adjacency[v].size(); ++i) {
            if (color[list_of_adjacency[v][i]] == 1) {
                throw found_grey(list_of_adjacency[v][i], v, parents);
            }
            if (color[list_of_adjacency[v][i]] != 0) {
                continue;
            }
            dfs(list_of_adjacency[v][i], color, parents, v);
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
    std::vector<long long> tin;
    std::vector<long long> tout;
    long long timer = 0;
    class found_grey{
    public:
        long long index;
        long long parent;
        std::vector<long long> parents;
        found_grey(long long x, long long parent, std::vector<long long> parents): index(x), parent(parent), parents(parents) {}
    };
};
 
int main() {
    long long n, m;
    std::cin >> n >> m;
    std::vector<std::pair<long long, long long>> pairs(m);
    for (int i = 0; i < m; ++i) {
        long long x, y;
        std::cin >> x >> y;
        pairs[i] = std::make_pair(x, y);
    }
    Graph g = Graph(n, pairs);
    try {
        g.consist_cycles();
        std::cout << "NO";
    } catch (std::vector<long long> cycle) {
        std::cout << "YES\n";
        for (int i = cycle.size() - 1; i >= 0; --i) {
            std::cout << cycle[i] << " ";
        }
    }
    return 0;
}

