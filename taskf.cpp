#include <iostream>
#include <vector>

long long INF = 1'000'000'000;

const std::vector<long long> powers_of_two{1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192};

class element{
public:
    long long value = INF;
    long long index = -1;
    element* prev = nullptr;

    element() = default;
    element(long long value, long long index): value(value), index(index) {}
    element(long long value, long long index, element* prev): value(value), index(index), prev(prev) {}

    bool operator<(const element& second) const {
        return value < second.value;
    }
    bool operator>(const element& second) const {
        return value > second.value;
    }
};

int main() {
    long long n;
    std::cin >> n;
    std::vector<std::vector<long long>> adjacency(n, std::vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> adjacency[i][j];
        }
    }
    std::vector<std::vector<element>> dp(n, std::vector<element>(powers_of_two[n]));
    for (int i = 0; i < n; ++i) {
        dp[i][powers_of_two[i]] = {0, i};
    }
    for (int mask = 1; mask < powers_of_two[n]; ++mask) {
        for (int v = 0; v < n; ++v) {
            if (mask >> v & 1) {
                for (int u = 0; u < n; ++u) {
                    if ((mask >> u & 1)) {
                        if (dp[v][mask].value > dp[u][mask ^ powers_of_two[v]].value + adjacency[v][u]) {
                            dp[v][mask] = element(dp[u][mask ^ powers_of_two[v]].value + adjacency[v][u], v, &dp[u][mask ^ powers_of_two[v]]);
                        }
                    }
                }
            }
        }
    }
    element* min = &dp[0][powers_of_two[n] - 1];
    for (int i = 1; i < n; ++i) {
        if (dp[i][powers_of_two[n] - 1] < *min) {
            min = &dp[i][powers_of_two[n] - 1];
        }
    }
    std::cout << min->value << "\n";
    while (min != nullptr) {
        std::cout << min->index + 1 << " ";
        min = min->prev;
    }
    return 0;
}
