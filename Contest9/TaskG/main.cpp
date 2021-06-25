#include <iostream>
#include <vector>
#include <set>

class Graph{
public:
    Graph(long long n, long long a, long long b, long long c): n(n), a(a), b(b), c(c) {}

    template<long long A, long long B, long long C>
    void insert(long long x) {
        floor.insert(x + A);
        floor.insert(x + B);
        floor.insert(x + C);
    }

    template<long long A, long long B>

    long long corrective() {
        if (a == 1) return n;

        floor.insert(0);
        auto x = floor.begin();
        is_reachable += 1;
        floor.insert(*x + a);
        floor.insert(*x + b);
        floor.insert(*x + c);
        while (!floor.empty()) {
            ++x;
            if (*x >= n) break;
            //floor.erase(floor.begin());
            is_reachable += 1;
            floor.insert(*x + a);
            floor.insert(*x + b);
            floor.insert(*x + c);
        }
        return is_reachable;
    }

private:
    long long n;
    long long m;
    long long a, b, c;
    long long is_reachable = 0;
    std::set<long long> floor;
    std::vector<std::pair<long long, long long>> pairs;
    std::vector<std::vector<long long>> matrix_of_adjacency;
    std::vector<std::vector<long long>> number_of_edge;
    std::vector<std::vector<long long>> list_of_adjacency;
    std::vector<std::vector<long long>> matrix_of_incidence;
};
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    long long h, a, b, c;
    std::cin >> h >> a >> b >> c;
    if (a > b) {
        std::swap(a, b);
    }
    if (b > c) {
        std::swap(b, c);
    }
    if (a > b) {
        std::swap(a, b);
    }
    Graph g = Graph(h, a, b, c);
    std::cout << g.corrective();
    return 0;
}
