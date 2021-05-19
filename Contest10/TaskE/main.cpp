#include <iostream>
#include <vector>
#include <algorithm>

constexpr long long INF = 2'147'483'647;

struct Edge{
    Edge() = default;
    Edge(long long x, long long y, long long w, long long index): x(x), y(y), w(w), index(index) {}
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

//parents(n, -1) size(n, 1)
class Graph{
public:
    Graph(long long m, long long n, std::vector<std::vector<long long>>&& list, std::vector<long long> par_soch): m(m), n(n), list_of_adjacency(list),
        max_par_soch(par_soch), parents(n + m) , color(n + m), new_list_of_adjacency(n + m) {}

    void min_v_cover() {
        std::vector<bool> used_m(m, 0);
        std::vector<bool> used_n(n, 0);
        for (int i = 0; i < m; ++i) {
            if (max_par_soch[i] != -1) {
                used_m[i] = 1;
                used_n[max_par_soch[i]] = 1;
                new_list_of_adjacency[max_par_soch[i] + m].push_back(i);
                for (int j = 0; j < list_of_adjacency[i].size(); ++j) {
                    if (max_par_soch[i] != list_of_adjacency[i][j]) {
                        new_list_of_adjacency[i].push_back(list_of_adjacency[i][j] + m);
                    }
                }
            } else {
                for (int j = 0; j < list_of_adjacency[i].size(); ++j) {
                    new_list_of_adjacency[i].push_back(list_of_adjacency[i][j] + m);
                }
            }
        }
        /*for (int i = 0; i < n; ++i) {
            if (!used_n[i]) {
                for (int j = 0; j < list_of_adjacency[i + m].size(); ++j) {
                    if (!used_m[list_of_adjacency[i + m][j]]) {
                        int size = edges.size();
                        edges.emplace_back(list_of_adjacency[i + m][j], i + m, 1, size);
                    }
                }
            }
        }*/
        for (int i = 0; i < m; ++i) {
            if (!used_m[i]) {
                dfs(i);
            }
        }
        std::vector<long long> return_m;
        for (int i = 0; i < m; ++i) {
            if(color[i] == 0) {
                return_m.push_back(i);
            }
        }
        std::vector<long long> return_n;
        for (int i = 0; i < n; ++i) {
            if (color[m + i] == 2) {
                return_n.push_back(i);
            }
        }
        std::cout << return_m.size() + return_n.size() << "\n";
        std::cout << return_m.size() << " ";
        for (int i = 0; i < return_m.size(); ++i) {
            std::cout << return_m[i] + 1 << " ";
        }
        std::cout << '\n';
        std::cout << return_n.size() << " ";
        for (int i = 0; i < return_n.size(); ++i) {
            std::cout << return_n[i]  + 1 << " ";
        }
    }


    void dfs(long long v) {
        color[v] = 1;
        for (size_t i = 0; i < new_list_of_adjacency[v].size(); ++i) {
            if (color[new_list_of_adjacency[v][i]] != 0) {
                continue;
            }
            dfs(new_list_of_adjacency[v][i]);
        }
        color[v] = 2;
    }

private:
    long long n;
    long long m;
    std::vector<Edge> edges;
    std::vector<std::vector<long long>> matrix_of_adjacency;
    std::vector<long long> max_par_soch;
    std::vector<long long> parents;
    std::vector<int8_t> color;
    std::vector<std::vector<long long>> number_of_edge;
    std::vector<std::vector<long long>> list_of_adjacency;
    std::vector<std::vector<long long>> new_list_of_adjacency;
    std::vector<std::vector<long long>> matrix_of_incidence;
};

int main() {
    long long n, m;
    std::cin >> m >> n;
    std::vector<std::vector<long long>> list_of_adjacency(m + n);
    std::vector<long long> max_par_soch(m);
    for (int i = 0; i < m; ++i) {
        int size;
        std::cin >> size;
        for (int j = 0; j < size; ++j) {
            int v;
            std::cin >> v;
            list_of_adjacency[i].push_back(v - 1);
            list_of_adjacency[m + v - 1].push_back(i);
        }
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> max_par_soch[i];
        --max_par_soch[i];
    }
    Graph g = Graph(m, n, std::move(list_of_adjacency), std::move(max_par_soch));
    g.min_v_cover();
    return 0;
}
