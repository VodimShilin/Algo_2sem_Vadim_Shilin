#include <iostream>
#include <vector>
#include <algorithm>

constexpr long long INF = 2'147'483'647;

struct Edge{
    Edge() = default;
    Edge(const Edge&) = default;
    Edge(Edge&& another): x(another.x), y(another.y), w(another.w), index(another.index) {}
    Edge reverse() {
        std::swap(x, y);
        return *this;
    }
    Edge& operator=(const Edge&) = default;

    bool operator>(const Edge& another) const {
        return w > another.w;
    }
    bool operator<(const Edge& another) const {
        return w < another.w;
    }
    bool operator==(const Edge& another) const {
        return w == another.w;
    }

    long long x;
    long long y;
    long long w;
    long long index;
};

std::istream& operator>>(std::istream& in, Edge& e) {
    in >> e.x >> e.y >> e.w;
    --e.x;
    --e.y;
    return in;
}


class Graph{
public:
    Graph(long long n, std::vector<Edge>&& edge): n(n), m(edge.size()), edges(std::move(edge)), matrix_of_adjacency(n),
        parents(n, -1), size(n, 1){
        for (int i = 0; i < m; ++i) {
            matrix_of_adjacency[edges[i].x].push_back(edges[i]);
            matrix_of_adjacency[edges[i].y].push_back(edges[i].reverse());
        }
    }

    long long Kruskal() {
        std::sort(edges.begin(), edges.end());
        long long sum = 0;
        for (int i = 0; i < m; ++i) {
            if (unite(edges[i].x, edges[i].y))
                sum += edges[i].w;
        }
        return sum;
    }

    long long get(long long v) {
        if (parents[v] == -1)
            return v;
        else
            return parents[v] = get(parents[v]);
    }

    bool unite(long long u, long long v) {
        u = get(u);
        v = get(v);
        if (u == v)
            return false;
        if (size[u] < size[v])
            std::swap(u, v);
        parents[v] = u;
        size[u] += size[v];
        return true;
    }

private:
    long long n;
    long long m;
    std::vector<Edge> edges;
    std::vector<std::vector<Edge>> matrix_of_adjacency;
    std::vector<long long> parents;
    std::vector<long long> size;
    std::vector<std::vector<long long>> number_of_edge;
    std::vector<std::vector<long long>> list_of_adjacency;
    std::vector<std::vector<long long>> matrix_of_incidence;
};

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i];
        edges[i].index = i;
    }
    Graph g = Graph(n, std::move(edges));
    std::cout << g.Kruskal();
    return 0;
}
