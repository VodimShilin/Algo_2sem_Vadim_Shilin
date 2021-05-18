#include <iostream>
#include <vector>

constexpr long long INF = 2'147'483'647;

struct Edge{
    Edge() = default;
    Edge(const Edge&) = default;
    Edge(Edge&& another): x(another.x), y(another.y), w(another.w), index(another.index) {}
    Edge reverse() {
        std::swap(x, y);
        return *this;
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
    Graph(long long n, std::vector<Edge>&& edge): n(n), m(edge.size()), edges(std::move(edge)), min_edge_into_vertice(n, -1),
        matrix_of_adjacency(n) {
        for (int i = 0; i < m; ++i) {
            if (edges[i].y == 0 && (min_edge_into_vertice[edges[i].x] == -1 || edges[min_edge_into_vertice[edges[i].x]].w > edges[i].w)) {
                min_edge_into_vertice[edges[i].x] = i;
            }
            if (edges[i].x == 0 && (min_edge_into_vertice[edges[i].y] == -1 || edges[min_edge_into_vertice[edges[i].y]].w > edges[i].w)) {
                min_edge_into_vertice[edges[i].y] = i;
            }
            matrix_of_adjacency[edges[i].x].push_back(edges[i]);
            matrix_of_adjacency[edges[i].y].push_back(edges[i].reverse());
        }
    }

    long long Prime() {
        if (n == 1) return 0;
        std::vector<bool> used(n, 0);
        long long sum = 0;
        used[0] = 1;
        for (int i = 1; i < n; ++i) {
            long long min = -1;
            for (int j = 0; j < n; ++j) {
                if (!used[j] and min_edge_into_vertice[j] != -1 and (min == -1 or edges[min_edge_into_vertice[j]].w < edges[min_edge_into_vertice[min]].w)) {
                    min = j;
                }
            }
            used[min] = 1;
            sum += edges[min_edge_into_vertice[min]].w;
            for (int j = 0; j < matrix_of_adjacency[min].size(); ++j) {
                if (!used[matrix_of_adjacency[min][j].y] and (min_edge_into_vertice[matrix_of_adjacency[min][j].y] == -1 or edges[min_edge_into_vertice[matrix_of_adjacency[min][j].y]].w > matrix_of_adjacency[min][j].w)) {
                    min_edge_into_vertice[matrix_of_adjacency[min][j].y] = matrix_of_adjacency[min][j].index;
                }
            }
        }
        return sum;
    }

private:
    long long n;
    long long m;
    std::vector<Edge> edges;
    std::vector<long long> min_edge_into_vertice;
    std::vector<std::vector<Edge>> matrix_of_adjacency;
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
    std::cout << g.Prime();
    return 0;
}
