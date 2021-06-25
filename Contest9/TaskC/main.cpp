#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <algorithm>

const int INF = 2'147'483'647;

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
    Graph(long long n, const std::vector<std::vector<long long>>& matrix_of_adjacency): n(n), matrix_of_adjacency(matrix_of_adjacency) {}

    void print_matrix_of_adjacency() {
        floyd();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << matrix_of_adjacency[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    void floyd() {
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    matrix_of_adjacency[i][j] = std::min(matrix_of_adjacency[i][j], matrix_of_adjacency[i][k] + matrix_of_adjacency[k][j]);
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
    std::vector<std::vector<long long>> list_of_adjacency;
    std::vector<std::vector<long long>> matrix_of_incidence;
};

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<long long>> g(n, std::vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> g[i][j];
        }
    }
    Graph gr = Graph(n, g);
    gr.print_matrix_of_adjacency();
    return 0;
}
